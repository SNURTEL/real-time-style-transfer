#!/usr/bin/env python3

import os
import argparse
import requests
from enum import Enum
from pathlib import Path
from tqdm import tqdm

class Model(str, Enum):
    style_monet = "style_monet"
    style_cezanne = "style_cezanne"
    style_ukiyoe = "style_ukiyoe"
    style_vangogh = "style_vangogh"


def _clone_repo(dir):
    os.system(
        f"git clone --depth=1 https://github.com/junyanz/pytorch-CycleGAN-and-pix2pix.git {dir}"
    )


def _fetch_checkpoints(model: Model) -> Path:
    # os.system(f"bash ./scripts/download_cyclegan_model.sh {model_name}")
    url = f"http://efrosgans.eecs.berkeley.edu/cyclegan/pretrained_models/{model.value}.pth"
    response = requests.get(url, stream=True)
    total_size = int(response.headers.get("content-length", 0))
    block_size = 1024
    
    out_file = Path(f"./checkpoints/{model.value}_pretrained/latest_net_G.pth")
    os.makedirs(out_file.parent, exist_ok=True)
    try:
        with tqdm(
            total=total_size, unit="B", unit_scale=True, desc=f'Download "{model.value}" to {out_file}'
        ) as progress_bar:
            with open(out_file, "wb") as file:
                for data in response.iter_content(block_size):
                    progress_bar.update(len(data))
                    file.write(data)

            if total_size != 0 and progress_bar.n != total_size:
                raise RuntimeError("Could not download file")
    except KeyboardInterrupt as e:
        print("Stopping...")
        out_file.unlink()
        raise e


def _trace_model(model: Model, out_path: Path):
    import sys

    sys.path.append(str(Path.cwd()))

    import torch
    from options.test_options import TestOptions
    from models import create_model
    
    sys.argv = f"test.py --dataroot dfsd --name {model.value}_pretrained --model test --no_dropout".split(
        " "
    )

    # from repo's `test.py`

    opt = TestOptions().parse()
    # hard-code some parameters for test
    opt.num_threads = 0  # test code only supports num_threads = 0
    opt.batch_size = 1  # test code only supports batch_size = 1
    opt.serial_batches = True  # disable data shuffling; comment this line if results on randomly chosen images are needed.
    opt.no_flip = (
        True  # no flip; comment this line if results on flipped images are needed.
    )
    opt.display_id = (
        -1
    )  # no visdom display; the test code saves the results to a HTML file.
    # dataset = create_dataset(opt)  # create a dataset given opt.dataset_mode and other options
    model = create_model(opt)  # create a model given opt.model and other options
    model.setup(opt)  # regular setup: load and print networks; create schedulers
    model.eval()

    # `model` is just a wrapper for internal nn.Module under `.netG.module`
    example = torch.rand(1, 3, 256, 256).cuda()
    traced = torch.jit.trace(model.netG.module, example_inputs=example)
    traced.save(out_path)
    
def get_model(model: Model) -> Path:
    cwd = Path.cwd()
    project_dir = cwd.parent if str(cwd).endswith("scripts") else cwd
    tmp_dir = project_dir / "models/tmp"
    cyclegan_dir = tmp_dir / "cyclegan"
    traced_model_path = project_dir / "models" / Path(f"{model.value}.ts")

    try:
        if cyclegan_dir.exists():
            print("-- Pre-treined CycleGAN repo dir exists, skipping clone")
        else:
            print(f"-- Cloning repo to {cyclegan_dir.absolute()}")
            _clone_repo(cyclegan_dir)

        os.chdir(cyclegan_dir)
        checkpoints_dir = Path(f"checkpoints/{model.value}_pretrained")

        if checkpoints_dir.exists():
            print("-- Model dir exists, skipping fetch")
        else:
            print(f"Fetching model checkpoints to {checkpoints_dir.absolute()}")
            _fetch_checkpoints(model)


        if traced_model_path.exists():
            print("-- Traced model file exists, skipping trace")
        else:
            print("-- Tracing model")
            _trace_model(model, traced_model_path)

        print(f"\n-- All done!\n-- Model saved to {traced_model_path.absolute()}")
    finally:
        os.chdir(cwd)
    
    return traced_model_path
    


def main() -> Path:
    parser = argparse.ArgumentParser()
    parser.add_argument("model",  nargs='?', choices=[m.value for m in Model])
    args = parser.parse_args()
    model = Model(args.model)
    
    return get_model(model)


if __name__ == "__main__":
    main()

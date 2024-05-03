import os
from pathlib import Path

MODEL_NAME = "style_vangogh"
DATASET_NAME = "vangogh2photo"
TRACED_MODEL_NAME = f"{MODEL_NAME}.ts"

def _clone_repo(dir):
    os.system(f"git clone --depth=1 https://github.com/junyanz/pytorch-CycleGAN-and-pix2pix.git {dir}")

def _fetch_checkpoints(model_name):
    os.system(f"bash ./scripts/download_cyclegan_model.sh {model_name}")

def _trace_model(out_path):
    import os
    import sys
    sys.path.append(str(Path.cwd()))

    import torch
    from options.test_options import TestOptions
    from models import create_model


    sys.argv = f"test.py --dataroot dfsd --name {MODEL_NAME}_pretrained --model test --no_dropout".split(" ")

    # from repo's `test.py`

    opt = TestOptions().parse()
    # hard-code some parameters for test
    opt.num_threads = 0   # test code only supports num_threads = 0
    opt.batch_size = 1    # test code only supports batch_size = 1
    opt.serial_batches = True  # disable data shuffling; comment this line if results on randomly chosen images are needed.
    opt.no_flip = True    # no flip; comment this line if results on flipped images are needed.
    opt.display_id = -1   # no visdom display; the test code saves the results to a HTML file.
    # dataset = create_dataset(opt)  # create a dataset given opt.dataset_mode and other options
    model = create_model(opt)      # create a model given opt.model and other options
    model.setup(opt)               # regular setup: load and print networks; create schedulers
    model.eval()

    # `model` is just a wrapper for internal nn.Module under `.netG.module`
    example = torch.rand(1, 3, 256, 256).cuda()
    traced = torch.jit.trace(model.netG.module, example_inputs=example)
    traced.save(out_path)
    

def main():
    cwd = Path.cwd()
    project_dir = cwd.parent if str(cwd).endswith('scripts') else cwd
    tmp_dir = project_dir / "models/tmp"
    cyclegan_dir = tmp_dir / "cyclegan"

    if cyclegan_dir.exists():
        print("-- Pre-treined CycleGAN repo dir exists, skipping clone")
    else:
        print(f"-- Cloning repo to {cyclegan_dir.absolute()}")
        _clone_repo(cyclegan_dir)

    os.chdir(cyclegan_dir)
    checkpoints_dir = Path(f"checkpoints/{MODEL_NAME}_pretrained")

    if checkpoints_dir.exists():
        print("-- Model dir exists, skipping fetch")
    else:
        print(f"Fetching model checkpoints to {checkpoints_dir.absolute()}")
        _fetch_checkpoints(MODEL_NAME)

    traced_model_file = project_dir / f"models/{TRACED_MODEL_NAME}"

    if traced_model_file.exists():
        print("-- Traced model file exists, skipping trace")
    else:
        print("-- Tracing model")
        _trace_model(traced_model_file)

    print(f"\n-- All done!\n-- Model saved to {traced_model_file.absolute()}") 
    

if __name__ == "__main__":
    main()
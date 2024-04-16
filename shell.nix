let
  nixpkgs = fetchTarball "https://github.com/NixOS/nixpkgs/tarball/nixos-22.11";
  pkgs = import nixpkgs {
    config = {};
    config.allowUnfree = true;
    config.segger-jlink.acceptLicense = true;
    overlays = [];
  };
in

pkgs.mkShellNoCC {
  packages = with pkgs; [
     gcc
     libstdcxx5
     glibc
#    gnumake
#    gcc
#    cmake
#    ninja
#    libtorch-bin
#    opencv3
#     cudatoolkit linuxPackages.nvidia_x11
#     cudaPackages.cudnn
#    cudatoolkit
#    cudaPackages.cuda_cudart
  ];
   shellHook = ''
      export PATH=${pkgs.cudatoolkit}/bin:$PATH
      export CUDA_CUDART_LIBRARY=${pkgs.cudaPackages.cuda_cudart}
      export CUDA_PATH=${pkgs.cudatoolkit}
      export CUDA_HOME=${pkgs.cudatoolkit}
      export LD_LIBRARY_PATH=${pkgs.linuxPackages.nvidia_x11}/lib:${pkgs.ncurses5}/lib
      export EXTRA_LDFLAGS="-L/lib -L${pkgs.linuxPackages.nvidia_x11}/lib"
      export EXTRA_CCFLAGS="-I/usr/include"
   '';
}

# https://github.com/NixOS/nixpkgs/issues/279706

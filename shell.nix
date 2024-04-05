let
  nixpkgs = fetchTarball "https://github.com/NixOS/nixpkgs/tarball/nixos-23.11";
  pkgs = import nixpkgs {
    config = {};
    config.allowUnfree = true;
    config.segger-jlink.acceptLicense = true;
    overlays = [];
  };
in

pkgs.mkShellNoCC {
  packages = with pkgs; [
    cmake
    ninja
    libtorch-bin
    opencv3
    cudatoolkit
  ];
}
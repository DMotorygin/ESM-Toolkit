# ESM-Toolkit
Toolkit for reading and writing of ESM files used in TES3 Morrowind

Steps to build:
1. Install [vcpkg](https://vcpkg.io/)
2. Switch to the repository root.
3. Install the dependencies:
   
   `vcpkg install --triplet=x64-windows`

   Optionally, set the environment variable `VCPKG_DEFAULT_TRIPLET=x64-windows` and omit the `--triplet` parameter.
4. Configure project via `CMake`, e.g. with the following command: `cmake -B ../build -DCMAKE_INSTALL_PREFIX=../install` (root makefile is in ../sources/ folder)
5. In order to launch need to set command arguments with path to Morrowind .esm file and to .xml file where results will be dumped

Features:
Currently can only read .esm file of TES3 Morrowind, save its contents into memory as set of objects and dump its contents into .xml file.

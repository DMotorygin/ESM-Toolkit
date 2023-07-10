# ESM-Toolkit
Toolkit for reading and writing of ESM files used in TES3 Morrowind

Steps to build:
1. Install vcpkg;
2. Ensure that VCPKG_DEFAULT_TRIPLET enviromental variable is set to x64-windows;
3. Set VCPKG_ROOT enviromental variable;
4. Install LibXml2 via vcpkg;
5. Configure project via cmake, e.g. with the following command: cmake -B ../build -DCMAKE_INSTALL_PREFIX=../install (root makefile is in ../sources/ folder)
6. In order to launch need to set command arguments with path to Morrowind .esm file and to .xml file where results will be dumped

Features:
Currently can only read .esm file of TES3 Morrowind, save its contents into memory as set of objects and dump its contents into .xml file.

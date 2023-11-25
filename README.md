# HorizonGUI

[![Release](https://img.shields.io/badge/Release-v1.0-blueviolet)](https://github.com/Horizon-NTH/HorizonGUI/releases)
[![Language](https://img.shields.io/badge/Language-C%2B%2B-0052cf)](https://en.wikipedia.org/wiki/C++)
[![Licence](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

![HorizonGUI Logo](https://github.com/Horizon-NTH/HorizonGUI/blob/master/assets/HorizonGUI.svg)

## Introduction

**HorizonGUI** is a Graphic User Interface library made in C++ with OpenGL.

## Installation Instructions

> You can also simply install a pre-built version [here](https://github.com/Horizon-NTH/HorizonGUI/releases).

### Get Source Code

You first need to clone the repository. Make sure to use [git](https://git-scm.com) and don't forget to include `--recurse-submodules` when cloning.

```bash
git clone https://github.com/Horizon-NTH/HorizonGUI.git --recurse-submodules
```

You will now able to choose between [script](#script-installation) or [manual](#manual-installation) installation

- ### Script Installation

  Use the [`install.sh`](https://github.com/Horizon-NTH/HorizonGUI/blob/master/install.sh) script to compile the library. You can choose the API type you want to build by passing an argument to the script: 
  `-d` / `--dynamic` for dynamic or `-s` / `--static` for static. You can also erase build files by adding `-e` / `--erase`.

  ```bash
  ./install.sh --dynamic -e
  ```

- ### Manual Installation

  #### Create Build Environment

  Ensure you have [CMake](https://cmake.org/) installed. Generate the build environment using CMake. You can choose the API type to **STATIC** (default is **DYNAMIC**) by setting the `API_TYPE` variable to 
  `ON`:

  ```bash
  cd HorizonGUI
  mkdir build && cd build
  cmake .. [-DAPI_TYPE=ON]
  ```

  #### Build

  - ##### CMake

    Build directly using CMake:

    ```bash
    cmake --build .
    ```

    This command will create all the lib files you need in `HorizonGUI/lib`.

  - ##### Microsoft Visual Studio

    Alternatively, you can use [Microsoft Visual Studio](https://visualstudio.microsoft.com/) to launch the project and build it. Open the `horizongui.sln` file with Microsoft Visual Studio.

## Documentation

Please refer to the [wiki](https://github.com/Horizon-NTH/HorizonGUI/wiki).

## Dependencies

- **[OpenGL](https://www.opengl.org)** is used for all graphics in the application.
- **[GLFW](https://www.glfw.org)** is used to create windows, contexts, and handle user input.
- **[Glad](https://glad.dav1d.de)** is used to load OpenGL functions.
- **[Freetype](https://freetype.org/index.html)** is used to load fonts and render text.
- **[STB](https://github.com/nothings/stb)** is used to load and save images.
- **[GLM](https://glm.g-truc.net/0.9.9/index.html)** is used for mathematical operations.

## License

HorizonGUI is licensed under the [MIT license](https://github.com/Horizon-NTH/HorizonGUI/blob/master/LICENSE).

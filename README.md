# HorizonGUI

[![Release](https://img.shields.io/badge/Release-v4.0-blueviolet)](https://github.com/Horizon-NTH/HorizonGUI/releases)
[![Language](https://img.shields.io/badge/Language-C%2B%2B-0052cf)](https://en.wikipedia.org/wiki/C++)
[![Licence](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

![HorizonGUI Logo](https://github.com/Horizon-NTH/HorizonGUI/blob/master/assets/HorizonGUI.svg)

## Introduction

**HorizonGUI** is a Graphic User Interface library made in C++ with OpenGL. There are also Python bindings available.

## Installation Instructions

* [C++ library](#c-library)
* [Python binding](#python-binding)

### C++ library

> You can also simply install a pre-built version [here](https://github.com/Horizon-NTH/HorizonGUI/releases).

#### Get Source Code

You first need to clone the repository. Make sure to use [git](https://git-scm.com) and don't forget to
include `--recurse-submodules` when cloning.

```bash
git clone https://github.com/Horizon-NTH/HorizonGUI.git --recurse-submodules
```

You will now able to choose between [script](#script-installation) or [manual](#manual-installation) installation

#### Script Installation

Use the [`install.sh`](https://github.com/Horizon-NTH/HorizonGUI/blob/master/install.sh) script to compile the
library. You can also erase build files by adding `-e` / `--erase`.

  ```bash
  ./install.sh -e
  ```

#### Manual Installation

##### Create Build Environment

Ensure you have [CMake](https://cmake.org/) installed. Generate the build environment using CMake:

  ```bash
  cd HorizonGUI
  mkdir build && cd build
  cmake ..
  ```

##### Build

###### CMake

Build directly using CMake:

```bash
cmake --build .
```

This command will create all the lib files you need in `HorizonGUI/lib`.

###### Microsoft Visual Studio

Alternatively, you can use [Microsoft Visual Studio](https://visualstudio.microsoft.com/) to launch the project
and build it. Open the `horizongui.sln` file with Microsoft Visual Studio.

### Python binding

To install the Python bindings, you can install it from [PyPi](https://pypi.org/project/hgui/) using this command:

```bash
pip install hgui
```

Or you can build it from source using those commands:

```bash
git clone https://github.com/Horizon-NTH/HorizonGUI.git --recurse-submodules
cd HorizonGUI
pip install ./python
```

> **Note**: Both methods can take some time due to the compilation of the underlying C++ library.

Once the installation is complete, you can import the module into your Python script using the following statement:

```python
import hgui
```

## Documentation

Please refer to the [wiki](https://github.com/Horizon-NTH/HorizonGUI/wiki).

## Dependencies

- **[OpenGL](https://www.opengl.org)** is used for all graphics in the application.
- **[GLFW](https://www.glfw.org)** is used to create windows, contexts, and handle user input.
- **[Glad](https://glad.dav1d.de)** is used to load OpenGL functions.
- **[Freetype](https://freetype.org/index.html)** is used to load fonts and render text.
- **[STB](https://github.com/nothings/stb)** is used to load and save images.
- **[GLM](https://glm.g-truc.net/0.9.9/index.html)** is used for mathematical operations.
- **[OpenAL-Soft](https://github.com/kcat/openal-soft/tree/master)** is used to play sound.
- **[Libsndfile](http://www.mega-nerd.com/libsndfile/)** is used to load audio file.
- **[Pybind11](https://github.com/pybind/pybind11)** is used to create python binding.

## License

HorizonGUI is licensed under the [MIT license](https://github.com/Horizon-NTH/HorizonGUI/blob/master/LICENSE).

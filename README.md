# HorizonGUI

## Introduction

**HorizonGUI** is a Graphic User Interface library in c++ with OpenGl

## Install Instructions

* Get source code

    You first need to clone with [git](https://git-scm.com) the [repository](https://github.com/Horizon-NTH/HorizonGUI.git)

    ⚠️ Watch out! The repository contains submodules, don't forget to add --recurse-submodules when cloning.  


```bash
    git clone https://github.com/Horizon-NTH/HorizonGUI.git --recurse-submodules
```

* Create build environment

    You need to use [CMake](https://cmake.org/) to generate the build environment for this project. So you have to make sure that you have a working CMake installation on your system.

```bash
    cd HorizonGUI
    mkdir build && cd build
    cmake ..
```

* Build

  * **CMake**

    You can build directly using [CMake](https://cmake.org/).

    ```bash
    cmake --build .
    ```

    This command will create all the .lib files you need in `HorizonGUI/bin`.

  * **Microsoft Visual Studio**

    You can also use [Microsoft Visual Studio](https://visualstudio.microsoft.com/) to launch the project and build it. Simply open the `horizongui.sln` file with Microsoft Visual Studio.

## DependenciesCreate window and handle input

* **[OpenGL](https://www.opengl.org)** is used for all graphics in the application.

* **[GLFW](https://www.glfw.org)** is used to create windows, contexts and handle user input.

* **[Glad](https://glad.dav1d.de)** is used to load OpenGL functions.

* **[Freetype](https://freetype.org/index.html)** is used to load fonts and render text.

* **[STB](https://github.com/nothings/stb)** is used to load and save images.

* **[GLM](https://glm.g-truc.net/0.9.9/index.html)** is used for mathematical operations.
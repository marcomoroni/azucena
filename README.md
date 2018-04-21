# [Azucena](https://marcomoroni.github.io/azucena/) 

[![Build status](https://ci.appveyor.com/api/projects/status/8sqlliuqw0d2a50g?svg=true)](https://ci.appveyor.com/project/marcomoroni/azucena)

## Instructions to build the repo

1. Clone it
2. Run

    ```
    git submodule update --init --recursive
    ```
    
3. Use [CMake](https://cmake.org/) to generate a Visual Studio project on a new folder
4. Open the Visual Studio project and set `AZUCENA` as startup project
5. Build it

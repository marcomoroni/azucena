<p align="center">
	<img src="https://raw.githubusercontent.com/marcomoroni/azucena/master/docs/img/logo_big.png" alt="logo" />
</p>

# [Azucena](https://marcomoroni.github.io/azucena/)

<p align="center">
	<a href="https://ci.appveyor.com/project/marcomoroni/azucena"><img src="https://ci.appveyor.com/api/projects/status/8sqlliuqw0d2a50g?svg=true" alt="Build status" /></a>
</p>

### Instructions to build the repo

1. Clone it
2. Run

    ```
    git submodule update --init --recursive
    ```
    
3. Use [CMake](https://cmake.org/) to generate a Visual Studio project on a new folder
4. Open the Visual Studio project and set `AZUCENA` as startup project
5. Build it

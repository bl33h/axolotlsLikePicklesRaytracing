# axolotlsLikePicklesRaytracing
It is a graphics application showcasing ray tracing techniques. The project includes the implementation of a resource manager for handling image loading and rendering, rendering of a skybox based on a provided texture file, and representation of spheres with ray intersection calculations.

<p align="center">
  <br>
  <img src="https://media4.giphy.com/media/v1.Y2lkPTc5MGI3NjExcGRoZ2JyazI0aWw3NjlvZHhmcDNueWt0N3BpYnMwYzRpZzZxNGxqaCZlcD12MV9pbnRlcm5hbF9naWZfYnlfaWQmY3Q9Zw/Uj1BComkoSCwmRkSL2/giphy.gif" alt="pic" width="500">
  <br>
</p>

<p align="center">
  <a href="#Files">Files</a> •
  <a href="#Features">Features</a> •
  <a href="#how-to-use">How To Use</a>
</p>

## Files
- main.cpp: The main application file handling game logic, input, and rendering.
- resourceManager.h: Header file for the resource manager class.
- skybox.cpp: Implementation file for the Skybox class.
- skybox.h: Header file for the Skybox class.
- sphere.cpp: Implementation file for the Sphere class.
- sphere.h: Header file for the Sphere class.
- colors.h: Header file defining color structures.
- materials.h: Header file defining material structures.
  
## Features
The main features of the graphics application include:
- Implementation of a resource manager for handling image loading and rendering.
- Skybox rendering based on a provided texture file.
- Sphere object representation with ray intersection calculations.

## How To Use

To clone and run this application, you'll need [WSL (Windows Subsystem for Linux)](https://learn.microsoft.com/en-us/windows/wsl/install) and the following tools installed on it: [Git](https://git-scm.com), [C++ compiler](https://www.fdi.ucm.es/profesor/luis/fp/devtools/mingw.html), [CMake](https://cmake.org/download/), [Make](https://linuxhint.com/install-make-ubuntu/), [glm](https://sourceforge.net/projects/glm.mirror/), [tbb](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onetbb.html), and [SDL2](https://www.oreilly.com/library/view/rust-programming-by/9781788390637/386c15eb-41b2-41b4-bd65-154a750a58d8.xhtml). From your command line:

```bash
# Clone this repository
$ git clone https://github.com/bl33h/axolotlsLikePicklesRaytracing

# Open the project
$ cd axolotlsLikePicklesRaytracing

# Give execution permissions
$ chmod +x configure.sh
$ chmod +x build.sh
$ chmod +x run.sh

# Run the app
$ ./run.sh

# RESkelly

Rendering Engine Skelly - A barebones and modular graphics engine solution for applications.

## Headline

RESkelly has reached the 0.1 release!

In this release, basic rendering, windowing and handlers are available.
You can directly access the Shader and Buffers to create graphics, but at this time creating complex applications can prove too costly.

Please check the release notes for further information.

## Introduction

RESkelly, or Skelly for short, uses C++ to provide a very simple solution for rendering panels, objects and other features into applications, called Body projects.

Each body is able to call upon different plugins of Skelly to implement different functionalities to the application.

Currently, the only supported OS are linux-based systems. Windows and MacOS support is planned in future stages.

## Installation and Setup

This project requires a C/C++ compiler in order to build and link the code. GCC has been used as the main compiler for development.
CMake and Makefiles are also used to automate building, linking and running the project. Those can be installed in Linux through the following commands:

```sh
sudo apt install gcc
sudo apt install Makefile
sudo apt install cmake
```

At this time, this project also requires OpenGL and auxiliary headers associated with rendering to function properly. The following packages should be available:

```sh
sudo apt install libglu1-mesa-dev freeglut3-dev mesa-common-dev libxinerama-dev libxcursor-dev libxi-dev
```

After installing the necessary packages, clone the repository and use the commands below to generate CMake outputs and run the project files within the `output/` folder:

```sh
# From project root, this creates the cmake structure for all projects
make
# Builds and links all projects
cd output/; make
# Run the linked executable
./body/body_exec

```

---

It is possible to have multiple, independent body projects by using the same template basis (obtained in the cloning process) and adding the project to the project.list file in root folder. We advise maintaining the main body template for sanity purposes and adding your own application to the list.

The creation of multiple projects is automated via the Makefile in the root folder:

```sh
make project NAME=<YOUR_PROJECT_NAME>
```

## Development

The project is currently in its early stages, and thus several functionalities are undergoing planning, development and integration:

 - Logging and Debugging
 - Basic project configurations for GUI and system
 - Initial Plugins and Components

### Challenges

Besides the project main features, some issues need to be addressed. These have been introduced during main feature implementation, and require considerable time to be addressed. They are as follows:

- Avoid third-party applications: ImGui is too complete a solution to be swapped in mid to long terms, but spdlog should eventually be changed to an internal tool;
- CMake parametrized projects: CMake architecture is duplicating files and does not allow for individualized runs. It should compile/link Skelly as a central hub and all projects should have their own structures, linked directly to it;

## Style Guide

### Coding

This project is heavily guided by the CppCoreGuidelines convention of rules for modern C++.

As of version 0.x, naming conventions are as follows:
- Folders and files in camelCase, where applicable;
- Public variables and functions in camelCase;
- Protected variables and functions in m_camelCase;
- Private variables and functions in _m_camelCase, where applicable;
- Classes in CamelCase;
- Namespaces in lowercase;
- Definitions in uppercase;
- Type definitions in t_camelCase;

Coding conventions are as follows:
- 4 space tabulation;
- Avoid redundant keywords such as inline within classes;
- Do not use raw pointers unless absolutely necessary;
### Infrastructure

This project uses CMake to generate all structures required for building.

There will be a `CMakeLists.txt` file in the top layer of the project and in each major structure: The Skelly engine and the Body projects.
- TopCM creates environment variables and calls subdirectory building recipes;
- SkellyCM handles the engine libraries and is included by TopCM;
- BodyCM handles the template libs and links everything together into a project-specific executable;

Changes to Skelly Engine require changes to SkellyCM. Changes to a Body feature require conditional changes to the BodyCM available in the template Body.

All CMake system build files should use the absolute pathing stemming from TopCM and dynamically named variables to affect all available Bodies.

Project configurations are included from `./config/project.config` into TopCM.

This project can use Pre-compiled headers(PCH), and as such all new libraries that can be considered frequently used everywhere by both Skelly and Bodies should be considered to be added to the `pch.h` header. If it is such, `pch.h` should be updated and impacted headers should include the new libraries within the `#ifndef PCH_ENABLED` clause.

PCH is currently not being focused, and will be worked on when compile times are a bigger concern in this project.
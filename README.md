# RESkelly

Rendering Engine Skelly - A barebones and modular graphics engine solution for diverse applications.

## Introduction

RESkelly, or Skelly for short, uses mainly C++ and C to provide a very basic solution for rendering panels, objects and other features into applications, called the bodies.

Each body is able to call upon different plugins of Skelly to implement different functionalities to the application.

Currently, the only supported OS are linux-based systems. Windows and MacOS support is planned in future stages.

## Installation and Setup

This project requires a C/C++ compiler in order to build and link the code. GCC has been used as the main compiler for development.
CMake and Makefiles are also used to automate building, linking and running the project. Those can be installed in Linux through the following command:

```sh
sudo apt install gcc
sudo apt install Makefile
sudo apt install cmake
```

After cloning the repository, generate CMake outputs and run the appropriate project files within the output/ folder:

```sh
# Creates the cmake structure for all projects
make structure
# Builds and links all projects
cd output/; make
# Run the linked executable
./body/body_exec
```

It is possible to have multiple, independent body projects by using the same template basis (obtained in the cloning process) and adding the project to the project.list file in root folder. We advise maintaining the main body template for sanity purposes and adding your own application to the list.

The creation of multiple projects is automated via the Makefile in the root folder:

```sh
make project NAME=<YOUR_PROJECT_NAME>
```

It is possible to have multiple, independent body projects by using the same template basis (obtained in the cloning process) and adding the project to the project.list file in root folder. We advise maintaining the main body template for sanity purposes and adding your own application to the list.

## Development

The project is currently at its early stages, and thus several functionalities are undergoing planning, development and integration:

 - Logging and Debugging
 - Initial entry state
 - Basic project configurations for GUI and system
 - Initial Plugins and Components

### Style Guide

This project is heavily guided by the CppCoreGuidelines convention of rules for modern C++.

This project uses absolute pathing for system build files via the CMake application.
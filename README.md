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

## Development

The project is currently at its early stages, and thus several functionalities are undergoing planning, development and integration:

 - Logging and Debugging
 - Initial entry state
 - Basic project configurations for GUI and system
 - Initial Plugins and Components

### Challenges

Besides the project main features, some issues need to be addressed at some point in development. These have been introduced during main feature implementation, and require considerable time to be addressed. They are as follows:

- Internal logging solution: Logging should not be vendor-based, and should have individual behavior depending on features being logged:
  - Logging should have colors, preferably unmangled functions, timestamp and generally return messages.
- CMake parametrized projects: CMake creates subdirectories based on the number of projects the user wishes to work with, but needs to use the central Skelly application.
  - Currently, it is not possible to run Make from within each project output dir and have CMake automatically populate the necessary files on the Skelly application.
  - 2 Features are necessary: One to allow the user to generate only Skelly files in the top output folder, and other to automatically check for those necessary top folder files when generating from the output project folders from below.

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

### Infrastructure

This project uses CMake to generate all strucure required for building.

There will be a `CMakeLists.txt` file in the top layer of the project and in each major structure: The Skelly engine and the Body projects.
- TopCM creates environment variables and calls subdirectory building recipes;
- SkellyCM handles the engine libraries and is included by TopCM;
- BodyCM handles the template libs and links everything together into a project-specific executable;

Changes to Skelly Engine should net changes to SkellyCM. Changes to a Body feature should net conditional changes to the BodyCM available in the template Body.

ALl CMake system build files should use the absolute pathing stemming from TopCM and dynamically named variables to affect all available Bodies.
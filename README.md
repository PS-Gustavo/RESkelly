# RESkelly

Rendering Engine Skelly - A barebones and modular graphics engine solution for diverse applications.

## Introduction

RESkelly, or Skelly for short, uses mainly C++ and C to provide a very basic solution for rendering panels, objects and other features into an application, called the body.

The body is able to call upon different plugins of Skelly to implement different functionalities to the application.

Currently, the only supported OS are linux-based systems. Windows support is planned in future stages.

## Installation and Setup

This project requires a C/C++ compiler in order to build and link the code. GCC has been used as the main compiler for development.
Makefiles are also used to automate building, linking and running the project. It can be installed in Linux through the following command:

```sh
sudo apt-install Makefile
```

After cloning the repository, building and running can be done through calling the following Make recipes in the project root folder:

```sh
# Builds the project
make
# Runs the resulting build
make run
# Builds and then runs the output
make brun 
```

## Development

The project is currently at its early stages, and thus several implementations are still undergoing planning:

 - Logging and Debugging
 - Initial entry state
 - Basic project configurations for GUI and system
 - Initial Plugins and Components

### Style Guide

This project is heavily guided by the CppCoreGuidelines convention of rules for modern C++.
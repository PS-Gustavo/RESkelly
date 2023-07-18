message(STATUS "Importing project configurations")

## Rendering API
#  Pick one of the available APIs below.
#  DirectX should only be used with Windows!
#  Metal should only be used with iOS!
set(USING_OPENGL ON)
#set(USING_VULKAN OFF)
#set(USING_DIRECTX OFF)
#set(USING_METAL OFF)

## Verbose mode
#  Runs all build steps using the --verbose flag
set(CMAKE_VERBOSE_MAKEFILE OFF)

## Debug mode
#  Activates a set of configurations geared towards code debugging.
#  Warning: Performance may slow down considerably with debug mode active.
set(DEBUG_ENABLED ON)

## Benchmarks
#  Measures time for all compile steps in the build
set(BENCHMARK_ENABLED OFF)

## PCH usage
#  Enables usage of the Pre-Compiled Header(PCH) for the project targets.
set(PCH_ENABLED OFF)
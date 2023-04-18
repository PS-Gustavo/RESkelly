message(STATUS "Importing project configurations")

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
set(PCH_ENABLED ON)
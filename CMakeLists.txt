# Sets the minimum required version of CMake for the project
cmake_minimum_required(VERSION 3.21)

# Sets the project name and version
project(AUDIO_PLUGIN_TEMPLATE VERSION 1.0.0)

# Adds the JUCE library
add_subdirectory(lib/JUCE)

# Adds the source code directory
add_subdirectory(src)
# InstruAI

This repository contains the beginnings of a JUCE-based VST3 instrument.
The plugin will allow users to type a text prompt or load an audio sample,
then generate an array of samples distributed across MIDI notes and velocity
layers.

## Building

1. Clone the JUCE framework into a folder named `JUCE` next to the project:
   ```sh
   git submodule add https://github.com/juce-framework/JUCE JUCE
   ```
2. Generate the build system with CMake:
   ```sh
   cmake -B build -S .
   cmake --build build
   ```

The current codebase is an initial skeleton featuring a simple user interface
with a text editor, buttons, and a piano keyboard component.

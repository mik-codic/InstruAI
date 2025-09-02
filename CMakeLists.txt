cmake_minimum_required(VERSION 3.15)
project(InstruAI VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Expect JUCE to be available in a subdirectory named JUCE or via FETCHCONTENT
# Users should add JUCE as a submodule or adjust the path accordingly.
add_subdirectory(JUCE)

juce_add_plugin(InstruAI
    COMPANY_NAME "InstruAI"
    PLUGIN_MANUFACTURER_CODE InAI
    PLUGIN_CODE InsA
    FORMATS VST3
    PRODUCT_NAME "InstruAI"
    IS_SYNTH TRUE
    NEEDS_MIDI_INPUT TRUE
    NEEDS_MIDI_OUTPUT FALSE
    IS_MIDI_EFFECT FALSE
    EDITOR_WANTS_KEYBOARD_FOCUS TRUE
)

target_sources(InstruAI PRIVATE
    Source/PluginProcessor.cpp
    Source/PluginEditor.cpp
)

target_link_libraries(InstruAI PRIVATE
    juce::juce_audio_utils
)

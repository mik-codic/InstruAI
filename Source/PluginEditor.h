#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class InstruAIaudioProcessorEditor : public juce::AudioProcessorEditor,
                                     private juce::Button::Listener
{
public:
    InstruAIaudioProcessorEditor(InstruAIaudioProcessor&);
    ~InstruAIaudioProcessorEditor() override;

    void paint(juce::Graphics&) override;
    void resized() override;

private:
    void buttonClicked(juce::Button* button) override;

    InstruAIaudioProcessor& processor;

    juce::MidiKeyboardState keyboardState;
    juce::MidiKeyboardComponent keyboardComponent;

      juce::TextEditor promptEditor;
      juce::TextButton loadSampleButton { "Load Sample" };
      juce::TextButton generateButton { "Generate" };

      juce::Slider sampleCountSlider;
      juce::Label sampleCountLabel;
      juce::Slider velocityLayerSlider;
      juce::Label velocityLayerLabel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(InstruAIaudioProcessorEditor)
};

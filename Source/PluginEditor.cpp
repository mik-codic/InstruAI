#include "PluginEditor.h"
#include "PluginProcessor.h"

InstruAIaudioProcessorEditor::InstruAIaudioProcessorEditor(InstruAIaudioProcessor& p)
    : AudioProcessorEditor(&p), processor(p),
      keyboardComponent(keyboardState, juce::MidiKeyboardComponent::horizontalKeyboard)
{
    addAndMakeVisible(keyboardComponent);

    addAndMakeVisible(promptEditor);
    promptEditor.setMultiLine(true);
    promptEditor.setText("Enter text prompt...");

    addAndMakeVisible(loadSampleButton);
    loadSampleButton.addListener(this);

    addAndMakeVisible(generateButton);
    generateButton.addListener(this);

    sampleCountLabel.setText("N", juce::dontSendNotification);
    addAndMakeVisible(sampleCountLabel);
    sampleCountSlider.setRange(1, 8, 1);
    sampleCountSlider.setValue(1);
    addAndMakeVisible(sampleCountSlider);

    velocityLayerLabel.setText("M", juce::dontSendNotification);
    addAndMakeVisible(velocityLayerLabel);
    velocityLayerSlider.setRange(1, 4, 1);
    velocityLayerSlider.setValue(1);
    addAndMakeVisible(velocityLayerSlider);

    setSize(600, 200);
}

InstruAIaudioProcessorEditor::~InstruAIaudioProcessorEditor() = default;

void InstruAIaudioProcessorEditor::paint(juce::Graphics& g)
{
    g.fillAll(juce::Colours::black);
}

void InstruAIaudioProcessorEditor::resized()
{
    auto area = getLocalBounds().reduced(10);
    auto topArea = area.removeFromTop(40);
    promptEditor.setBounds(topArea.removeFromLeft(area.getWidth() - 320));
    loadSampleButton.setBounds(topArea.removeFromLeft(100));
    generateButton.setBounds(topArea.removeFromLeft(100));
    sampleCountLabel.setBounds(topArea.removeFromLeft(20));
    sampleCountSlider.setBounds(topArea.removeFromLeft(50));
    velocityLayerLabel.setBounds(topArea.removeFromLeft(20));
    velocityLayerSlider.setBounds(topArea.removeFromLeft(50));
    keyboardComponent.setBounds(area);
}

void InstruAIaudioProcessorEditor::buttonClicked(juce::Button* button)
{
    if (button == &loadSampleButton)
    {
        juce::FileChooser chooser("Select an audio file");
        if (chooser.browseForFileToOpen())
        {
            processor.loadSample(chooser.getResult());
        }
    }
    else if (button == &generateButton)
    {
        juce::String prompt = promptEditor.getText();
        juce::ignoreUnused(prompt);
        // TODO: trigger generation from text prompt
    }
}

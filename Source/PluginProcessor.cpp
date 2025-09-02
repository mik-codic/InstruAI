#include "PluginProcessor.h"
#include "PluginEditor.h"

InstruAIaudioProcessor::InstruAIaudioProcessor()
    : AudioProcessor(BusesProperties().withOutput("Output", juce::AudioChannelSet::stereo(), true))
{
    formatManager.registerBasicFormats();

    for (int i = 0; i < 8; ++i)
        sampler.addVoice(new juce::SamplerVoice());
}

InstruAIaudioProcessor::~InstruAIaudioProcessor() = default;

void InstruAIaudioProcessor::prepareToPlay(double sampleRate, int samplesPerBlock)
{
    juce::ignoreUnused(sampleRate, samplesPerBlock);
}

void InstruAIaudioProcessor::releaseResources()
{
}

bool InstruAIaudioProcessor::isBusesLayoutSupported(const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono() &&
        layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
    return true;
}

void InstruAIaudioProcessor::processBlock(juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    buffer.clear();
    sampler.renderNextBlock(buffer, midiMessages, 0, buffer.getNumSamples());
}

juce::AudioProcessorEditor* InstruAIaudioProcessor::createEditor()
{
    return new InstruAIaudioProcessorEditor(*this);
}

void InstruAIaudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    juce::ignoreUnused(destData);
}

void InstruAIaudioProcessor::setStateInformation(const void* data, int sizeInBytes)
{
    juce::ignoreUnused(data, sizeInBytes);
}

void InstruAIaudioProcessor::loadSample(const juce::File& file)
{
    std::unique_ptr<juce::AudioFormatReader> reader(formatManager.createReaderFor(file));
    if (reader != nullptr)
    {
        juce::BigInteger notes;
        notes.setRange(0, 128, true);

        auto sound = std::make_unique<juce::SamplerSound>(file.getFileName(), *reader, notes,
                                                          60, 0.0, 0.0,
                                                          reader->lengthInSamples / reader->sampleRate);
        sampler.addSound(sound.release());
    }
}

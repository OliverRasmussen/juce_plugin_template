#pragma once

#include <JuceHeader.h>

//==============================================================================
class PluginProcessor final : public juce::AudioProcessor
{
public:
    //==============================================================================
    PluginProcessor();
    ~PluginProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    /**
    * @brief Validates an audio buffer by checking for NaN, Inf, and out-of-range values.
    * Useful for detecting and preventing unexpected audio buffer data that would lead to audio artifacts.
    * @param buffer The audio buffer to validate.
    * @param minValue The minimum value allowed in the buffer. Default is -1.0f.
    * @param maxValue The maximum value allowed in the buffer. Default is 1.0f.
     */
    void validateAudioBuffer (const juce::AudioBuffer<float>& buffer, float minValue = -1.0f, float maxValue = 1.0f)
    {
        int numChannels = buffer.getNumChannels();
        int numSamples = buffer.getNumSamples();

        for (int channel = 0; channel < numChannels; ++channel)
        {
            const float* channelData = buffer.getReadPointer (channel);

            for (int sample = 0; sample < numSamples; ++sample)
            {
                float sampleValue = channelData[sample];

                // Assert if NaN, Inf, or out-of-range values are found
                jassert (!std::isnan (sampleValue));
                jassert (!std::isinf (sampleValue));
                jassert (sampleValue >= minValue && sampleValue <= maxValue);
            }
        }
    }

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PluginProcessor)
};

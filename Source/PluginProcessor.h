/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class MidigenAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    MidigenAudioProcessor();
    ~MidigenAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //================================= I ADDED THIS:
    float playbackSpeed;
    int scaleType; // 1:Major - 2:Minor
    int scaleName; //1c 2c# 3d 4eb 5e 6f 7f# 8g 9g# 10a 11bb 12b 
    int mode; //1notes 2chords 3both
    float melodyRandomness;
    float timeRandomness;

    //=============================================================
    int generateRandomNote();
    int generateRandomSilence();

    int minMidiNoteValue;
    int maxMidiNoteValue;
    int octaveNumbers;
    int majorScaleNotes[7];
    int minorScaleNotes[7];

    AudioParameterFloat* speed;


private:
    //============================================================================== I ADDED THESE
    int currentNote, lastNoteValue;
    int time;
    float rate;
    SortedSet<int> notes;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MidigenAudioProcessor)
};


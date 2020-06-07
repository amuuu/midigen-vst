/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidigenAudioProcessor::MidigenAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
    addParameter(speed = new AudioParameterFloat("speed", "Arp Speed", 0.0, 1.0, 0.5));
}

MidigenAudioProcessor::~MidigenAudioProcessor()
{
}

//==============================================================================
const String MidigenAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MidigenAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MidigenAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MidigenAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MidigenAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MidigenAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MidigenAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MidigenAudioProcessor::setCurrentProgram (int index)
{
}

const String MidigenAudioProcessor::getProgramName (int index)
{
    return {};
}

void MidigenAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void MidigenAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..

    notes.clear();                          // [1]
    currentNote = 0;                        // [2]
    lastNoteValue = -1;                     // [3]
    time = 0;                               // [4]
    rate = static_cast<float> (sampleRate); // [5]
    playbackSpeed = 0;
}

void MidigenAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MidigenAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MidigenAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    buffer.clear();
    //int bpm = AudioPlayHead::getCurrentPosition(currentPositionInfo);

    //midiMessages.addEvent(MidiMessage::noteOn(1, 12, (juce::uint8)127), 0);
    //midiMessages.addEvent(MidiMessage::noteOff(1, 12), 1000);

    // the audio buffer in a midi effect will have zero channels!
    //jassert(buffer.getNumChannels() == 0);

    // however we use the buffer to get timing information
    auto numSamples = buffer.getNumSamples();

    // get note duration
    auto noteDuration = static_cast<int> (std::ceil(rate * 0.25f * (0.1f + (1.0f - (*speed)))));

    MidiMessage msg;
    int ignore;

    for (MidiBuffer::Iterator it(midiMessages); it.getNextEvent(msg, ignore);)
    {
        if (msg.isNoteOn())  notes.add(msg.getNoteNumber());
        else if (msg.isNoteOff()) notes.removeValue(msg.getNoteNumber());
    }

    midiMessages.clear();

    if ((time + numSamples) >= noteDuration)
    {
        auto offset = jmax(0, jmin((int)(noteDuration - time), numSamples - 1));

        if (lastNoteValue > 0)
        {
            midiMessages.addEvent(MidiMessage::noteOff(1, lastNoteValue), offset);
            lastNoteValue = -1;
        }

        if (notes.size() > 0)
        {
            currentNote = (currentNote + 1) % notes.size();
            lastNoteValue = notes[currentNote];
            midiMessages.addEvent(MidiMessage::noteOn(1, lastNoteValue, (uint8)127), offset);
        }

    }

    time = (time + numSamples) % noteDuration;
}

//==============================================================================
bool MidigenAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* MidigenAudioProcessor::createEditor()
{
    return new MidigenAudioProcessorEditor (*this);
}

//==============================================================================
void MidigenAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MidigenAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MidigenAudioProcessor();
}

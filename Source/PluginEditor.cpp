/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MidigenAudioProcessorEditor::MidigenAudioProcessorEditor (MidigenAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (600, 300);


    //////////////// Arp Speed slider and label
    speedSlider.setRange(0.0, 1.0, 0.0625);
    speedSlider.setTextValueSuffix("");
    speedSlider.addListener(this);
    addAndMakeVisible(&speedSlider);
    speedSlider.setValue(1, dontSendNotification);
    speedLabel.setText("Speed", dontSendNotification);
    speedLabel.attachToComponent(&speedSlider, true);
    addAndMakeVisible(&speedLabel);
    
    
    //////////////// Melody Randomness slider and label
    melodyRandomnessSlider.setRange(0.0, 1.0, 0.02);
    melodyRandomnessSlider.setTextValueSuffix("%");
    melodyRandomnessSlider.addListener(this);
    addAndMakeVisible(&melodyRandomnessSlider);
    melodyRandomnessSlider.setValue(0.0, dontSendNotification);
    melodyRandomnessLabel.setText("Melody Randomness", dontSendNotification);
    melodyRandomnessLabel.attachToComponent(&melodyRandomnessSlider, true);
    addAndMakeVisible(&melodyRandomnessLabel);

    //////////////// Time Randomness slider and label
    timeRandomnessSlider.setRange(0.0, 1.0, 0.02);
    timeRandomnessSlider.setTextValueSuffix("%");
    timeRandomnessSlider.addListener(this);
    addAndMakeVisible(&timeRandomnessSlider);
    timeRandomnessSlider.setValue(0.0, dontSendNotification);
    timeRandomnessLabel.setText("Time Randomness", dontSendNotification);
    timeRandomnessLabel.attachToComponent(&timeRandomnessSlider, true);
    addAndMakeVisible(&timeRandomnessLabel);

    //////////////// Octave Numbers slider and label
    octaveNumbersSlider.setRange(1, 5, 1);
    octaveNumbersSlider.setTextValueSuffix("");
    octaveNumbersSlider.addListener(this);
    octaveNumbersSlider.setValue(3, dontSendNotification);
    addAndMakeVisible(&octaveNumbersSlider);

    octaveNumbersLabel.setText("Octave Number", dontSendNotification);
    octaveNumbersLabel.attachToComponent(&octaveNumbersSlider, true);
    addAndMakeVisible(&octaveNumbersLabel);


    //////////////// Major and Minor buttons
    addAndMakeVisible(&majorButton);
    addAndMakeVisible(&minorButton);
    majorButton.setClickingTogglesState(true);
    minorButton.setClickingTogglesState(true);
    
    majorButton.onClick = [this] {updateScaleTypeToggleState(&majorButton, "Major"); };
    minorButton.onClick = [this] {updateScaleTypeToggleState(&minorButton, "Minor"); };
    majorButton.setRadioGroupId(ScaleButtons);
    minorButton.setRadioGroupId(ScaleButtons);

    addAndMakeVisible(&scaleTypeLabel);
    scaleTypeLabel.setText("Scale Type", dontSendNotification);
    scaleTypeLabel.attachToComponent(&majorButton, true);

    //////////////// Scale Name combobox
    addAndMakeVisible(&scaleNameMenu);
    scaleNameMenu.addItem("C", 1);
    scaleNameMenu.addItem("C#", 2);
    scaleNameMenu.addItem("D", 3);
    scaleNameMenu.addItem("Eb", 4);
    scaleNameMenu.addItem("E", 5);
    scaleNameMenu.addItem("F", 6);
    scaleNameMenu.addItem("F#", 7);
    scaleNameMenu.addItem("G", 8);
    scaleNameMenu.addItem("G#", 9);
    scaleNameMenu.addItem("A", 10);
    scaleNameMenu.addItem("Bb", 11);
    scaleNameMenu.addItem("B", 12);
    scaleNameMenu.setSelectedId(1);
    scaleNameMenu.onChange = [this] { scaleNameMenuChanged(); };

    addAndMakeVisible(&scaleNameLabel);
    scaleNameLabel.setText("Scale Name", dontSendNotification);
    scaleNameLabel.attachToComponent(&scaleNameMenu, true);

    //////////////// Mode combobox
    addAndMakeVisible(&modeMenu);
    modeMenu.addItem("Notes", 1);
    modeMenu.addItem("Chords", 2);
    modeMenu.addItem("Notes+Chords", 3);
    modeMenu.setSelectedId(1);
    modeMenu.onChange = [this] { modeMenuChanged(); };

    addAndMakeVisible(&modeLabel);
    modeLabel.setText("Generating Mode", dontSendNotification);
    modeLabel.attachToComponent(&modeMenu, true);



}

MidigenAudioProcessorEditor::~MidigenAudioProcessorEditor()
{
}

//==============================================================================
void MidigenAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (ResizableWindow::backgroundColourId));

    g.setColour (Colours::white);
    g.setFont (15.0f);
    g.drawFittedText ("MIDIGEN", 0, 0, getWidth(), 30, Justification::centred, 1);
}

void MidigenAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..

    auto sliderLeft = 120;

    speedSlider.setBounds(sliderLeft, 20, getWidth() - sliderLeft - 10, 60);
    
    melodyRandomnessSlider.setBounds(sliderLeft, 50, getWidth() - sliderLeft - 10, 60);
    
    majorButton.setBounds(sliderLeft, 110, 60, 30);
    minorButton.setBounds(sliderLeft+65, 110, 60, 30);

    scaleNameMenu.setBounds(sliderLeft+230, 110, 60, 30);

    modeMenu.setBounds(sliderLeft, 150, 130, 30);

    modeMenu.setBounds(sliderLeft, 150, 130, 30);
    
    octaveNumbersSlider.setBounds(sliderLeft, 180, getWidth() - sliderLeft - 10, 60);
    
    timeRandomnessSlider.setBounds(sliderLeft, 210, getWidth() - sliderLeft - 10, 60);

}

void MidigenAudioProcessorEditor::sliderValueChanged(Slider* slider)
{
    if (slider == &speedSlider) {
        processor.playbackSpeed = float(speedSlider.getValue());
    }
    else if (slider == &octaveNumbersSlider) {
        processor.octaveNumbers = float(octaveNumbersSlider.getValue());
    }
    else if (slider == &timeRandomnessSlider) {
        processor.timeRandomness = float(timeRandomnessSlider.getValue());
    }
    else if (slider == &melodyRandomnessSlider) {
        // not implemented yet
    }
}


void MidigenAudioProcessorEditor::updateScaleTypeToggleState(Button* button, String name)
{
    auto state = button->getToggleState();
    String stateString = state ? "ON" : "OFF";
    //Logger::outputDebugString(name + " Button changed to " + scaleState);
    
    if (name == "Major" && stateString == "ON") {
        processor.scaleType = 1;
    }
    else if (name=="Minor" && stateString == "ON") {
        processor.scaleType = 0;
    }
}

void MidigenAudioProcessorEditor::scaleNameMenuChanged() {
    processor.scaleName = int(scaleNameMenu.getSelectedId());
}

void MidigenAudioProcessorEditor::modeMenuChanged() {
    processor.mode = int(modeMenu.getSelectedId());
}
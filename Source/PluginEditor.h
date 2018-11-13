/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"
#include "SpectrumComponent.h"

//==============================================================================
/**
*/


class Spectrum_analyser_testAudioProcessorEditor  : public AudioProcessorEditor, public Timer
{

public:
    Spectrum_analyser_testAudioProcessorEditor (Spectrum_analyser_testAudioProcessor&);
    ~Spectrum_analyser_testAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override; 
	void timerCallback() override;

private:
	TextButton buttonWindow;
	SpectrumComponent sc;
    Spectrum_analyser_testAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Spectrum_analyser_testAudioProcessorEditor)
};

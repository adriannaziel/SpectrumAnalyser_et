/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "FFTProcessor.h"

#define FFT_ORDER 12

//==============================================================================
/**
*/

//enum WINDOW_TYPE {
//	BH,
//	HANN,
//	HAMMING,
//	RECTANGULAR,
//	BLACKMANN
//};

class Spectrum_analyser_testAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    Spectrum_analyser_testAudioProcessor();
    ~Spectrum_analyser_testAudioProcessor();


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

	bool isFFTBlockReady();
	void processFFT();
	void changeWindow(); // nie wiem czy tu..
	String getWindowName(); // nie wiem czy tu..
	float * getFFTData();
	int getFFTSize();//TMP!!!!!!!!!!!




private:	
	SpectrumProcessor spectrum_processor;


	//==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Spectrum_analyser_testAudioProcessor)
};

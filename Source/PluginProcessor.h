/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/**
*/

enum WINDOW_TYPE {
	BH,
	HANN,
	HAMMING,
	RECTANGULAR,
	BLACKMANN
};

class Spectrum_analyser_testAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    Spectrum_analyser_testAudioProcessor();
    ~Spectrum_analyser_testAudioProcessor();

	void pushNextSampleIntoFifo(float sample) noexcept;

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


	void doProcessing();
	void changeWindow();
	String getWindowName();

	enum // moze zamiast enuma to ustawic   a moze enum ok?
	{
		fftOrder = 12,
		fftSize = 1 << fftOrder, // 2^ ??
		scopeSize = fftSize
	};

	int fftOrder2;
	int fftSize2;
	dsp::FFT forwardFFT;
	dsp::WindowingFunction<float> window;
	WINDOW_TYPE window_type;
	float  fifo[fftSize];
	float fftData [2 * fftSize];


	int fifoIndex = 0;
	bool nextFFTBlockReady = false;
	float scopeData[scopeSize];
	float scopeData2[scopeSize];

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Spectrum_analyser_testAudioProcessor)
};

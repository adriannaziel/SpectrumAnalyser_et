/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Spectrum_analyser_testAudioProcessor::Spectrum_analyser_testAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ),fftOrder2(12), forwardFFT(fftOrder),
	window(fftSize, dsp::WindowingFunction<float>::hamming)
#endif
{
	fftSize2 = 1 << fftOrder2;
	window_type = HAMMING;

}

Spectrum_analyser_testAudioProcessor::~Spectrum_analyser_testAudioProcessor()
{
}

//==============================================================================
const String Spectrum_analyser_testAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Spectrum_analyser_testAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool Spectrum_analyser_testAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool Spectrum_analyser_testAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double Spectrum_analyser_testAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Spectrum_analyser_testAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int Spectrum_analyser_testAudioProcessor::getCurrentProgram()
{
    return 0;
}

void Spectrum_analyser_testAudioProcessor::setCurrentProgram (int index)
{
}

const String Spectrum_analyser_testAudioProcessor::getProgramName (int index)
{
    return {};
}

void Spectrum_analyser_testAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void Spectrum_analyser_testAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void Spectrum_analyser_testAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool Spectrum_analyser_testAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void Spectrum_analyser_testAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();


	for (int i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
	{
		buffer.clear(i, 0, buffer.getNumSamples());
	}


	if (buffer.getNumChannels() > 0)
	{
		auto* channelData = buffer.getReadPointer(0);

		for (auto i = 0; i < buffer.getNumSamples(); ++i)
			pushNextSampleIntoFifo(channelData[i]);
	}
}


void Spectrum_analyser_testAudioProcessor::pushNextSampleIntoFifo(float sample) noexcept
{

	if (fifoIndex == fftSize)
	{
		if (!nextFFTBlockReady)
		{
			zeromem(fftData, sizeof(fftData));
			memcpy(fftData, fifo, sizeof(fifo));
			nextFFTBlockReady = true;
		}

		fifoIndex = 0;
	}

	fifo[fifoIndex++] = sample;
}



//==============================================================================
bool Spectrum_analyser_testAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* Spectrum_analyser_testAudioProcessor::createEditor()
{
    return new Spectrum_analyser_testAudioProcessorEditor (*this);
}

//==============================================================================
void Spectrum_analyser_testAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void Spectrum_analyser_testAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void Spectrum_analyser_testAudioProcessor::doProcessing()
{
	
	window.multiplyWithWindowingTable(fftData, fftSize);
	forwardFFT.performFrequencyOnlyForwardTransform(fftData);
}



void Spectrum_analyser_testAudioProcessor::changeWindow()
{
	if (window_type == BH) {
		window.fillWindowingTables(fftSize, dsp::WindowingFunction<float>::hann);
		window_type = HANN;
	}
	else if (window_type == HANN) {
			window.fillWindowingTables(fftSize, dsp::WindowingFunction<float>::hamming);
		window_type = HAMMING;
	}

	else  if (window_type == HAMMING) {
		  window.fillWindowingTables(fftSize, dsp::WindowingFunction<float>::rectangular);
		window_type = RECTANGULAR;
	}
	else  if (window_type == RECTANGULAR) {
		window.fillWindowingTables(fftSize, dsp::WindowingFunction<float>::blackman);
		window_type = BLACKMANN;
	}
	else  if (window_type == BLACKMANN) {
		window.fillWindowingTables(fftSize, dsp::WindowingFunction<float>::blackmanHarris);
		window_type = BH;
	}

}

String Spectrum_analyser_testAudioProcessor::getWindowName()
{
	if (window_type == BH) {
		return "blackmann-harris";
	}
	else if (window_type == HANN) {
		return "hann";

	}
	else if (window_type == HAMMING) {
		return "hamming";
	}
	else  if (window_type == BLACKMANN) {
		return "blackmann";
	}
	else  if (window_type == RECTANGULAR) {
		return "rectangular";

	}

}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Spectrum_analyser_testAudioProcessor();
}

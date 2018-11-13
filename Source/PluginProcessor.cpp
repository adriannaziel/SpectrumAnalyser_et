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
	: AudioProcessor(BusesProperties()
#if ! JucePlugin_IsMidiEffect
#if ! JucePlugin_IsSynth
		.withInput("Input", AudioChannelSet::stereo(), true)
#endif
		.withOutput("Output", AudioChannelSet::stereo(), true)
#endif
	) 
#endif
{
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
			spectrum_processor.pushNextSampleIntoFifo(channelData[i]);
	}
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

bool Spectrum_analyser_testAudioProcessor::isFFTBlockReady()
{
	return spectrum_processor.nextFFTBlockReady;
}

void Spectrum_analyser_testAudioProcessor::processFFT()
{
	spectrum_processor.doProcessing();
	spectrum_processor.nextFFTBlockReady = false;
}





void Spectrum_analyser_testAudioProcessor::changeWindow()
{
	spectrum_processor.changeWindow();
}

String Spectrum_analyser_testAudioProcessor::getWindowName()
{
	WINDOW_TYPE wt = spectrum_processor.window_type;
	if (wt == BH) {
		return "blackmann-harris";
	}
	else if (wt == HANN) {
		return "hann";

	}
	else if (wt == HAMMING) {
		return "hamming";
	}
	else  if (wt == BLACKMANN) {
		return "blackmann";
	}
	else  if (wt == RECTANGULAR) {
		return "rectangular";

	}

}

float * Spectrum_analyser_testAudioProcessor::getFFTData()
{
	return spectrum_processor.fftData;
}

int Spectrum_analyser_testAudioProcessor::getFFTSize()
{
	return spectrum_processor.fftSize/2 ;
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Spectrum_analyser_testAudioProcessor();
}

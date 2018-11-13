/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"



//==============================================================================
Spectrum_analyser_testAudioProcessorEditor::Spectrum_analyser_testAudioProcessorEditor (Spectrum_analyser_testAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
	setOpaque(true);
	startTimerHz(30);
	setSize(1000, 350);
	setResizable(true, true);

	buttonWindow.setButtonText(processor.getWindowName());
	buttonWindow.onClick = [this] {
		processor.changeWindow();
		buttonWindow.setButtonText(processor.getWindowName());
	};
	addAndMakeVisible(buttonWindow);

	addAndMakeVisible(sc);

}


Spectrum_analyser_testAudioProcessorEditor::~Spectrum_analyser_testAudioProcessorEditor()
{
}

//==============================================================================
void Spectrum_analyser_testAudioProcessorEditor::paint (Graphics& g)
{
	g.fillAll(Colours::black);
	g.setOpacity(1.0f);
	sc.prepareToPaintSpectrum(processor.getFFTSize(), processor.getFFTData()); // moze spectrum component bedziesie laczyl ze spectrum processorem? 
}

void Spectrum_analyser_testAudioProcessorEditor::resized()
{
	buttonWindow.setBounds(20, 20, 100, 20);
	sc.setBounds(0, 50, getWidth(), getHeight()-50);
}

void Spectrum_analyser_testAudioProcessorEditor::timerCallback()
{


	if (processor.isFFTBlockReady() )
	{
		//processor.doProcessing();
		//processor.nextFFTBlockReady = false;
		processor.processFFT();
		sc.prepareToPaintSpectrum(processor.getFFTSize() , processor.getFFTData());
		sc.repaint();
	}



}



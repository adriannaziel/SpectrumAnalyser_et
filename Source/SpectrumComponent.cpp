/*
  ==============================================================================

    SpectrumComponent.cpp
    Created: 11 Nov 2018 9:40:21am
    Author:  lenovo

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SpectrumComponent.h"

const int SpectrumComponent::frequenciesForLines[] = { 20, 30, 40, 50, 60, 70, 80, 90, 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000, 20000 };
const int SpectrumComponent::numberOfLines = 28;
//==============================================================================
SpectrumComponent::SpectrumComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.

	setSize(600, 400);  //?!!!!!!!!
}

SpectrumComponent::~SpectrumComponent()
{
}

void SpectrumComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

	g.setColour(Colours::whitesmoke);
	for (int i = 0; i < numberOfLines; ++i)
	{
		const double proportion = frequenciesForLines[i] / (44100 / 2.0);
		int xPos = transformToLog(proportion) * (getWidth());
		g.drawVerticalLine(xPos, 0.0f, getHeight() - 40);
	}
	g.drawText("20", 70, 245, 50, 50, Justification::centred);
	//g.drawText("30", 100, 245, 50, 50, Justification::centred);
	g.drawText("100", 220, 245, 50, 50, Justification::centred);
	g.drawText("200", 310, 245, 50, 50, Justification::centred);
	g.drawText("1000", 530, 245, 50, 50, Justification::centred);
	g.drawText("2000", 620, 245, 50, 50, Justification::centred);
	g.drawText("10000", 865, 245, 50, 50, Justification::centred);
	g.drawText("200000", 950, 245, 50, 50, Justification::centred);

	g.setColour(Colours::deeppink);
	paintSpectrum(g);
}

void SpectrumComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void SpectrumComponent::paintSpectrum(Graphics & g)
{
	//numBins = numBins / 2; // tmp potem zmienic zeby przyjmowalo od razu fftsize / 2
	//	const float* data = ;// processor.fftData;

	float x = 0;
	float y = 0;

	float h = getHeight() - 40;



	//const float yInPercent = data[0]>0 ? float(0.5 + (Decibels::gainToDecibels(data[0]) / 100.0f)) : -0.01;
	// to dziala w miare ok ale za duzo zostaje na gorze i do -80 db

	float yy = spectrum_data[0]> 0 ? float(0.5 + (Decibels::gainToDecibels(spectrum_data[0]) / 150)) : -0.01;
	y = h - h * yy; // 200+ Decibels::gainToDecibels(data[i]) ; //
					//y = y - 300;

	if (y > h) {
		y = h;
	}
	if (x < 80) {
		x = 80;
	}

	last_x = x;
	last_y = y;



	for (int i = 1; i < number_of_bins; i += 5)
	{
		x = transformToLog((float)i / number_of_bins) * (getWidth());
		const float yInPercent = spectrum_data[i]> 0 ? float(0.5 + (Decibels::gainToDecibels(spectrum_data[i]) / 150)) : -0.01;
		y = h - h * yInPercent; // 200+ Decibels::gainToDecibels(data[i]) ; //
								//y=y - 300; //?

		if (y > h) {
			y = h;
		}
		if (x < 80) {
			x = 80;
			y = last_y;
		}

		// y = data[0] > 0 ?  jmap(jlimit(-60.0f, 0.0f, Decibels::gainToDecibels(data[i])), -60.0f, 0.0f, h, 10.0f) : h;
		// y = jmap(jlimit(-100.0f, 6.0f, Decibels::gainToDecibels(data[i])), -100.0f, 0.0f, 0.0f, 1.0f);
		// y = jmap(y, h, 0.0f);
		// y =  -1 * Decibels::gainToDecibels(data[i],-60.0f);


		g.drawLine(last_x, last_y, x, y);
		last_x = x;
		last_y = y;
	}

}

void SpectrumComponent::prepareToPaintSpectrum(int numBins, float * data)
{
	number_of_bins = numBins;
	spectrum_data = data;
	//repaint();
}

float SpectrumComponent::transformToLog(float between0and1)
{
	const float minimum = 1.0f;
	const float maximum = 1000.0f;
	return log10(minimum + ((maximum - minimum) * between0and1)) / log10(maximum);
}
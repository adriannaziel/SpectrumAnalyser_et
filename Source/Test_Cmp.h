/*
  ==============================================================================

    Test_Cmp.h
    Created: 11 Nov 2018 9:40:21am
    Author:  lenovo

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class Test_Cmp    : public Component
{
public:
    Test_Cmp();
    ~Test_Cmp();

	void paint(Graphics& g) override;
	void prepareToPaintSpectrum(int numberOfBins, float * spectrumData);
	float transformToLog(float valueToTransform); //name
	void resized() override;
	void paintSpectrum(Graphics & g);





private:
	float last_x;
	float last_y;
	int number_of_bins;
	float* spectrum_data;
	static const int frequenciesForLines[];
	static const int numberOfLines;    


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Test_Cmp)
};

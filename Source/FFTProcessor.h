/*
  ==============================================================================

    FFTProcessor.h
    Created: 12 Nov 2018 2:16:02pm
    Author:  lenovo

  ==============================================================================
*/
#include "../JuceLibraryCode/JuceHeader.h"
#pragma once

enum WINDOW_TYPE {
	BH,
	HANN,
	HAMMING,
	RECTANGULAR,
	BLACKMANN
};

class SpectrumProcessor {
public:

	SpectrumProcessor(): forwardFFT(fftOrder), window(fftSize, dsp::WindowingFunction<float>::hamming){
		window_type = HAMMING;
	}

	enum // moze zamiast enuma to ustawic   a moze enum ok?
	{
		fftOrder = 12,
		fftSize = 1 << fftOrder, // 2^ ??
	};



	float fftData[2 * fftSize];
	bool nextFFTBlockReady = false;



	float  fifo[fftSize];
	dsp::FFT forwardFFT;
	dsp::WindowingFunction<float> window;
	int fifoIndex = 0;
	WINDOW_TYPE window_type;


	void pushNextSampleIntoFifo(float sample) noexcept {
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

	void doProcessing()
	{
		window.multiplyWithWindowingTable(fftData, fftSize);
		forwardFFT.performFrequencyOnlyForwardTransform(fftData);
	}

	void changeWindow()
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

	String getWindowName()  //Nie wiem czy to jest potrzebne tutaj ale na razie wrzucam
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


private:




};
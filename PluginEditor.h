/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "UI/OscComponent.h"
#include "UI/AdsrComponent.h"
#include "UI/FilterComponent.h"
#include "UI/HorizontalMeter.h"
#include "UI/ADSRGraph.h"
//==============================================================================
/**
*/
class TapSynthAudioProcessorEditor  : public juce::AudioProcessorEditor , public juce::Timer, public juce::Slider::Listener

{
public:
    TapSynthAudioProcessorEditor (TapSynthAudioProcessor&);
    ~TapSynthAudioProcessorEditor() override;

    void timerCallback() override;
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(juce::Slider*);
  

private:

    int rectArray[500] = { 0 };

    juce::Slider a, d, s, r;

    TapSynthAudioProcessor& audioProcessor;
    OscComponent osc1;
    OscComponent osc2;
    AdsrComponent adsr;
    FilterComponent filter;
    Gui::HorizontalMeter horizontalMeterL, horizontalMeterR;
    adsr_graphic adsrG;
    juce::ImageComponent logoComponent;
    juce::Image logo;
    
    
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TapSynthAudioProcessorEditor)
};

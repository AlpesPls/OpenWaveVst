/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"
#include "UI/AdsrComponent.h"


//==============================================================================
TapSynthAudioProcessorEditor::TapSynthAudioProcessorEditor (TapSynthAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p), osc1 (audioProcessor.apvts, "OSC1", "OSC1GAIN", "OSC1PITCH"), osc2 (audioProcessor.apvts, "OSC2", "OSC2GAIN", "OSC2PITCH"), adsr (audioProcessor.apvts), filter (audioProcessor.apvts, "FILTERTYPE", "FILTERFREQ", "FILTERRES")
{
    setSize (700, 470);
    addAndMakeVisible (osc1);
    addAndMakeVisible (osc2);
    addAndMakeVisible(adsr);
    addAndMakeVisible (filter);
    addAndMakeVisible(horizontalMeterL);
    addAndMakeVisible(horizontalMeterR);
    
    

    getLookAndFeel().setColour(juce::Slider::thumbColourId, juce::Colours::deepskyblue);

    startTimerHz(24);

    a.addListener(this); 
    d.addListener(this); 
    s.addListener(this); 
    r.addListener(this);  

  
    logo = juce::ImageCache::getFromMemory(BinaryData::WhatsApp_Image_20240223_at_14_11_45_4ad02145removebgpreview_png, BinaryData::WhatsApp_Image_20240223_at_14_11_45_4ad02145removebgpreview_pngSize);
    logoComponent.setImage(logo);
    addAndMakeVisible(logoComponent);

}

TapSynthAudioProcessorEditor::~TapSynthAudioProcessorEditor()
{
}

void TapSynthAudioProcessorEditor::timerCallback()
{
    horizontalMeterL.setLevel(audioProcessor.getRmsValue(0));
    horizontalMeterR.setLevel(audioProcessor.getRmsValue(1));
    horizontalMeterL.repaint();
    horizontalMeterR.repaint();
    
}

void TapSynthAudioProcessorEditor::sliderValueChanged(juce::Slider* slider) {
   adsrG.update(a.getValue(), d.getValue(), s.getValue(), r.getValue());
   
}

//==============================================================================
void TapSynthAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
   
 
}

void TapSynthAudioProcessorEditor::resized()
{
    adsr.setBounds(getWidth() / 2 + 20, 35, getWidth() / 2 - 10, 250);
    a.setBounds(400, 345, 50, 50); 
    d.setBounds(450, 345, 50, 50); 
    s.setBounds(500, 345, 50, 50); 
    r.setBounds(550, 345, 50, 50); 
    osc1.setBounds(15, 25, getWidth() / 2, 115);
    osc2.setBounds(15, 165, getWidth() / 2, 115);
    filter.setBounds(15, 300, getWidth() / 2, 115);

    horizontalMeterL.setBounds(15, 430, 200, 15);
    horizontalMeterR.setBounds(15, 450, 200, 15);

    adsrG.setBounds(15, 300, 350, 85);
    logoComponent.setBounds(350, 300, 350, 110);
    

   


   

}



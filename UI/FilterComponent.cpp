/*
  ==============================================================================

    FilterComponent.cpp
    Created: 30 Jan 2024 2:27:40pm
    Author:  kekw

  ==============================================================================
*/

#include <JuceHeader.h>
#include "FilterComponent.h"

//==============================================================================

FilterComponent::FilterComponent(juce::AudioProcessorValueTreeState& apvts, juce::String filtertypeSelectorId, juce::String filterfreqId, juce::String filterResId )
{
    juce::StringArray Choices{ "Low-Pass", "Band-Pass", "High-Pass" };
    filterTypeSelector.addItemList(Choices, 1);
    addAndMakeVisible(filterTypeSelector);

    filterTypeSelectorAtt = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, filtertypeSelectorId, filterTypeSelector);


    filterSelectorLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    filterSelectorLabel.setFont(0);
    filterSelectorLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(filterSelectorLabel);

    setSliderWithLabel(filterFreqSlider, filterFreqLabel, apvts, filterfreqId, filterFreqAttachment);
    setSliderWithLabel(filterResSlider, filterResLabel, apvts, filterResId, filterResAttachment);
}

FilterComponent::~FilterComponent()
{
}


void FilterComponent::paint (juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.setColour(juce::Colours::black);
    g.fillRect(bounds);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("Filter", labelSpace.withX(5), juce::Justification::left);
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);
  
}

void FilterComponent::resized()
{
    const auto startY = 30;
    const auto sliderWidth = 100;
    const auto sliderHeight = 90;
    const auto labelOffset = 10;
    const auto labelHeight = 20;

    filterTypeSelector.setBounds(10, startY + 5, 90, 70);
    filterSelectorLabel.setBounds(10, startY - labelOffset, 90, labelHeight);

    filterFreqSlider.setBounds(filterTypeSelector.getRight() + 10, 25, 76, sliderHeight); 
    filterFreqLabel.setBounds(filterFreqSlider.getX(), filterFreqSlider.getY() - 15, filterFreqSlider.getWidth(), labelHeight);
    filterFreqLabel.setColour(juce::Label::textColourId, juce::Colours::white); 

    filterResSlider.setBounds(filterFreqSlider.getRight() + 10, 25, 76, sliderHeight);
    filterResLabel.setBounds(filterResSlider.getX(), filterResSlider.getY() - 15, filterResSlider.getWidth(), labelHeight);
    filterResLabel.setColour(juce::Label::textColourId, juce::Colours::white); 

}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void FilterComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
{
    slider.setSliderStyle(juce::Slider::SliderStyle::Rotary);
    slider.setTextBoxStyle(juce::Slider::NoTextBox, true, 50, 25);
    addAndMakeVisible(slider);

    attachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, paramId, slider);

    label.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    label.setFont(15.0f);
    label.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(label);
}


#include <JuceHeader.h>
#include "OscComponent.h"


//==============================================================================
OscComponent::OscComponent (juce::AudioProcessorValueTreeState& apvts, juce::String oscId, juce::String gainId, juce::String pitchId)
{
    juce::StringArray oscChoices { "Sine", "Saw", "Square" };
    oscSelector.addItemList (oscChoices, 1);
    oscSelector.setSelectedItemIndex (0);
    addAndMakeVisible (oscSelector);

    oscSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, oscId, oscSelector);

    
    waveSelectorLabel.setColour(juce::Label::ColourIds::textColourId, juce::Colours::white);
    waveSelectorLabel.setFont(0);
    waveSelectorLabel.setJustificationType(juce::Justification::left);
    addAndMakeVisible(waveSelectorLabel);

    setSliderWithLabel(gainSlider, gainLabel, apvts, gainId, gainAttachment);
    setSliderWithLabel(pitchSlider, pitchLabel, apvts, pitchId, pitchAttachment);
    
    oscSelAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ComboBoxAttachment>(apvts, oscId, oscSelector);
    
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, gainId, gainSlider);
    
    pitchAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(apvts, pitchId, pitchSlider);
}

OscComponent::~OscComponent()
{
}

void OscComponent::paint(juce::Graphics& g)
{
    auto bounds = getLocalBounds().reduced(5);
    auto labelSpace = bounds.removeFromTop(25.0f);

    g.setColour(juce::Colours::black);
    g.fillRect(bounds);
    g.setColour(juce::Colours::white);
    g.setFont(20.0f);
    g.drawText("Oscillator", labelSpace.withX(5), juce::Justification::left);   
    g.drawRoundedRectangle(bounds.toFloat(), 5.0f, 2.0f);

}

void OscComponent::resized()
{
    const auto startY = 30;
    const auto sliderWidth = 100;
    const auto sliderHeight = 110;
    const auto labelOffset = 10;
    const auto labelHeight = 20;

    oscSelector.setBounds(10, startY + 5, 90, 70); 
    waveSelectorLabel.setBounds(10, startY - labelOffset, 90, labelHeight); 
     
    gainSlider.setBounds(oscSelector.getRight() + 10, 15, 76, sliderHeight); 
     // Example of customizing slider color  
    gainSlider.setColour(juce::Slider::trackColourId, juce::Colours::grey); // Example of customizing slider color 
    gainLabel.setBounds(gainSlider.getX(), gainSlider.getY() - 5, gainSlider.getWidth(), labelHeight); 
    gainLabel.setColour(juce::Label::textColourId, juce::Colours::white); // Example of customizing label color 

    pitchSlider.setBounds(gainSlider.getRight() + 10, 15, 76, sliderHeight);
    // Example of customizing slider color 
    pitchSlider.setColour(juce::Slider::trackColourId, juce::Colours::grey); // Example of customizing slider color 
    pitchLabel.setBounds(pitchSlider.getX(), pitchSlider.getY() - 5, pitchSlider.getWidth(), labelHeight); 
    pitchLabel.setColour(juce::Label::textColourId, juce::Colours::white); // Example of customizing label color 
    


}

using Attachment = juce::AudioProcessorValueTreeState::SliderAttachment;

void OscComponent::setSliderWithLabel(juce::Slider& slider, juce::Label& label, juce::AudioProcessorValueTreeState& apvts, juce::String paramId, std::unique_ptr<Attachment>& attachment)
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


#include <JuceHeader.h>
#include "AdsrComponent.h"
#include "ADSRGraph.h"

//==============================================================================
AdsrComponent::AdsrComponent (juce::AudioProcessorValueTreeState& apvts)
{
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    attackAttachment = std::make_unique<SliderAttachment>(apvts,  "ATTACK",  attackSlider);
    decayAttachment = std::make_unique<SliderAttachment>(apvts,   "DECAY",   decaySlider);
    sustainAttachment = std::make_unique<SliderAttachment>(apvts, "SUSTAIN", sustainSlider);
    releaseAttachment = std::make_unique<SliderAttachment>(apvts, "RELEASE", releaseSlider);
    
    setSliderParams (attackSlider);
    setSliderParams (decaySlider);
    setSliderParams (sustainSlider);
    setSliderParams (releaseSlider);

    a_default = 500;
    d_default = 500;
    s_default = 1;
    r_default = 500;

}

AdsrComponent::~AdsrComponent()
{
}

void AdsrComponent::setRange(float maxAttack, float maxDecay, float maxRelease) {
    attackSlider.setRange(0, maxAttack, 1);
    decaySlider.setRange(0, maxDecay, 1);
    sustainSlider.setRange(0, 1, .001); //sustain is always a scale from 0-1
    releaseSlider.setRange(0, maxRelease, 1);
    graphic.setMaxes(maxAttack, maxDecay, maxRelease);
}


void AdsrComponent::setDefaults(float a, float d, float s, float r) {
    a_default = a;
    d_default = d;
    s_default = s;
    r_default = r;
    attackSlider.setValue(a);
    attackSlider.setDoubleClickReturnValue(true, a);
    decaySlider.setValue(d);
    decaySlider.setDoubleClickReturnValue(true, d);
    sustainSlider.setValue(s);
    sustainSlider.setDoubleClickReturnValue(true, s);
    releaseSlider.setValue(r);
    releaseSlider.setDoubleClickReturnValue(true, r);
    repaint();
    graphic.repaint();
}


 void AdsrComponent::sliderValueChanged(juce::Slider* slider) {
     graphic.update(attackSlider.getValue(), decaySlider.getValue(), sustainSlider.getValue(), releaseSlider.getValue());
}

 void AdsrComponent::addListener(Listener* listener)
 {
 }

 void AdsrComponent::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::black);
}

 float AdsrComponent::getA() {
     return attackSlider.getValue();
 }
 float AdsrComponent::getD() {
     return decaySlider.getValue();
 }
 float AdsrComponent::getS() {
     return sustainSlider.getValue();
 }
 float AdsrComponent::getR() {
     return releaseSlider.getValue();
 }

void AdsrComponent::resized()
{
    const auto bounds = getLocalBounds().reduced(10);
    const auto padding = 10;
    const auto sliderWidth = bounds.getWidth() / 4 - padding;
    const auto sliderHeight = bounds.getHeight();
    const auto sliderStartX = 0;
    const auto sliderStartY = 0;

    attackSlider.setBounds(sliderStartX, sliderStartY, sliderWidth, sliderHeight);
    decaySlider.setBounds(attackSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    sustainSlider.setBounds(decaySlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    releaseSlider.setBounds(sustainSlider.getRight() + padding, sliderStartY, sliderWidth, sliderHeight);
    graphic.setBounds(0, 0, getWidth(), getHeight() / 2); 
}



void AdsrComponent::setSliderParams (juce::Slider& slider)
{
    slider.setSliderStyle (juce::Slider::SliderStyle::LinearVertical);
    slider.setTextBoxStyle (juce::Slider::TextBoxBelow, true, 50, 15);
    slider.setColour (juce::Slider::ColourIds::textBoxTextColourId, juce::Colours::whitesmoke);
    addAndMakeVisible (slider);
   
}

void AdsrComponent::changeLine(juce::Colour color, int thickness) {
    graphic.setLine(color, thickness);
}

void AdsrComponent::changeLine(juce::Colour color) {
    graphic.setLine(color, 3);
}

void AdsrComponent::changeBackground(juce::Colour color) {
    graphic.SetBackgroundColor(color);
}




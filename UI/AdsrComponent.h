#pragma once

#include <JuceHeader.h>
#include "ADSRGraph.h"

//==============================================================================
/*
*/
class AdsrComponent : public juce::Component
{
public:
    AdsrComponent (juce::AudioProcessorValueTreeState& apvts);
    ~AdsrComponent() override;

    class JUCE_API Listener
    {
    public:
        virtual ~Listener() {}
        virtual void adsrValueChanged(AdsrComponent* adsr) = 0;
    };

    void addListener(Listener* listener);
    void paint (juce::Graphics&) override;
    void sliderValueChanged(juce::Slider* slider);
    void changeBackground(juce::Colour);
    void changeLine(juce::Colour, int);
    void changeLine(juce::Colour);
    float getA();
    float getD();
    float getS();
    float getR();
    void resized() override;
    void setDefaults(float, float, float, float);
   

private:
    void setSliderParams (juce::Slider& slider);
    
    juce::Slider attackSlider;
    juce::Slider decaySlider;
    juce::Slider sustainSlider;
    juce::Slider releaseSlider;
    float a_default, d_default, s_default, r_default;
    adsr_graphic graphic;
    void setRange(float, float, float);


    
    using SliderAttachment = juce::AudioProcessorValueTreeState::SliderAttachment;
    
    std::unique_ptr<SliderAttachment> attackAttachment;
    std::unique_ptr<SliderAttachment> decayAttachment;
    std::unique_ptr<SliderAttachment> sustainAttachment;
    std::unique_ptr<SliderAttachment> releaseAttachment;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AdsrComponent)
};

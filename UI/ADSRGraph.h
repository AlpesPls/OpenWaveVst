/*
  ==============================================================================

    ADSRgraph.h
    Created: 6 Feb 2024 5:46:14pm
    Author:  kekw

  ==============================================================================
*/

#pragma once

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class adsr_graphic : public juce::Component
{
    float attack, decay, sustain, release;
public:
    adsr_graphic();
    ~adsr_graphic();
    void paint(juce::Graphics&) override;
    void resized() override;
    void setLine(juce::Colour, int);
    void SetBackgroundColor(juce::Colour);
    void update(float, float, float, float);
    void setMaxes(float, float, float);
    void setText(juce::String, juce::Colour);
private:
    float amax, dmax, smax, rmax;
    juce::String text;
    juce::Colour lineColor;
    juce::Colour backColor;
    juce::Colour textColor;
    int lineThickness;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(adsr_graphic)
};
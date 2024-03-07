
#pragma once

#include <JuceHeader.h>

namespace Gui
{
	class HorizontalMeter : public juce::Component
	{
	public:
		void paint(juce::Graphics& g) override
		{
			auto bounds = getLocalBounds().toFloat();
		
			g.fillRoundedRectangle(bounds, 5.f);

			g.setColour(juce::Colours::deepskyblue);
			const auto scaledA = 
			juce::jmap(level, -60.f, +6.f, 0.f, static_cast<float>(getWidth()));
			g.fillRoundedRectangle(bounds.removeFromLeft(scaledA), 5.f);

		}

		void setLevel(const float value) { level = value; }
	private:
		float level = -60.f;
	};
} 
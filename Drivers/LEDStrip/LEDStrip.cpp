/*
 * LEDStrip.cpp
 *
 *  Created on: 27 αταψ 2015
 *      Author: Vitaly
 */

#include "LEDStrip.h"
#include "Color.h"

namespace Drivers {

// Input a value 0 to 255 to get a color value.
// The colors are a transition r - g - b - back to r.
uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if(WheelPos < 85) {
   return (CColor::GetColor32(255 - WheelPos * 3, 0, WheelPos * 3));
  } else if(WheelPos < 170) {
    WheelPos -= 85;
   return (CColor::GetColor32(0, WheelPos * 3, 255 - WheelPos * 3));
  } else {
   WheelPos -= 170;
   return (CColor::GetColor32(WheelPos * 3, 255 - WheelPos * 3, 0));
  }
}

CLEDStrip::CLEDStrip(int iPin, int iNumOfLEDs) :
	m_iDataPin(iPin),
	m_iNumOfLEDs(iNumOfLEDs),
	m_cLEDStrip(iNumOfLEDs, iPin, NEO_GRB + NEO_KHZ800)
{
}

CLEDStrip::~CLEDStrip()
{
}

bool CLEDStrip::Init()
{
	// Setup the strip
	m_cLEDStrip.begin();

	// Initialize all LEDs to "off" (default)
	m_cLEDStrip.show();

	return (true);
}

void CLEDStrip::Off()
{
	m_cLEDStrip.clear();
	m_cLEDStrip.show();
}

bool CLEDStrip::Animate_ColorWipe(uint32_t uiColor, int iDelay)
{
	// TODO: Convert to data-members
	static int 				iCurrLED 	= 0;
	static unsigned long 	ulLastTime 	= 0;

	// Get current time
	unsigned long ulCurrTime = millis();

	// ???
	if (ulLastTime != 0 && (ulCurrTime - ulLastTime) < iDelay)
		return (false);

	// Light up a LED
	m_cLEDStrip.setPixelColor(iCurrLED++, uiColor);
	m_cLEDStrip.show();

	// Update the time
	ulLastTime = ulCurrTime;

	// Didn't finish yet
	if (iCurrLED < m_iNumOfLEDs)
		return (false);

	// FINISHED - Reset the values
	iCurrLED 	= 0;
	ulLastTime 	= 0;

	return (true);
}

bool CLEDStrip::Animate_TheaterChase(uint32_t uiColor, int iCycles, int iGap, int iDelay)
{
	static int 				iCurrCycle 	= 0;
	static int 				iCurrGap 	= 0;

	static unsigned long 	ulLastTime 	= 0;

	// Get current time
	unsigned long 			ulCurrTime 	= millis();

	if (ulLastTime == 0)
	{
		// Turn every X+iGap LED
		for (int i = 0; i < m_iNumOfLEDs; i += iGap)
		{
			uint32_t uiLEDColor = uiColor;

			// Smooth Rainbow
			if (uiLEDColor == 0)
				uiLEDColor = Wheel((i+iCurrCycle) % 255);
			// Split Rainbow
			else if (uiLEDColor == 1)
				uiLEDColor = Wheel(((i * 256 / m_cLEDStrip.numPixels()) + iCurrCycle) & 255);

			// Set LED color
			m_cLEDStrip.setPixelColor(i + iCurrGap, uiLEDColor);
		}

		m_cLEDStrip.show();

		// Set the time
		ulLastTime = ulCurrTime;
	}

	// Wait iDelay before moving to the next cycle
	if ((ulCurrTime - ulLastTime) < iDelay)
		return (false);

	// Turn off all light LEDs
	for (int i = 0; i < m_iNumOfLEDs; i += iGap)
		m_cLEDStrip.setPixelColor(i + iCurrGap, 0);

	// Reset the time
	ulLastTime = 0;

	// Check current GAP
	if (++iCurrGap < iGap)
		return (false);

	iCurrGap = 0;

	// If the animation hasn't finished yet
	if (++iCurrCycle < iCycles)
		return (false);

	// FINISHED - Reset the values
	iCurrGap 	= 0;
	iCurrCycle 	= 0;
	ulLastTime 	= 0;

//	  uint16_t i, j;
//
//	  for(j=0; j<256; j++) {
//	    for(i=0; i<m_cLEDStrip.numPixels(); i++) {
//	      m_cLEDStrip.setPixelColor(i, Wheel((i+j) & 255));
//	    }
//	    m_cLEDStrip.show();
//	    delay(iDelay);
//	  }

//	  uint16_t i, j;
//
//	  for(j=0; j<256*5; j++) { // 5 cycles of all colors on wheel
//	    for(i=0; i< m_cLEDStrip.numPixels(); i++) {
//	      m_cLEDStrip.setPixelColor(i, Wheel(((i * 256 / m_cLEDStrip.numPixels()) + j) & 255));
//	    }
//	    m_cLEDStrip.show();
//	    delay(iDelay);
//	  }

	return (true);
}

} // namespace Drivers

/*
 * LEDStrip.h
 *
 *  Created on: 27 αταψ 2015
 *      Author: Vitaly
 */

#ifndef LEDSTRIP_H_
#define LEDSTRIP_H_

#include "Library/Adafruit_NeoPixel.h"

namespace Drivers {

class CLEDStrip
{

/*
 * Private data-members:
 */
private:

	/*!
	 * Number of the pin the strip is connected to.
	 */
	int 				m_iDataPin;

	/*!
	 * Total number of LEDs in the strip.
	 */
	int 				m_iNumOfLEDs;

	/*!
	 * LED strip controller class instance.
	 */
	Adafruit_NeoPixel	m_cLEDStrip;

/*
 * Public methods:
 */
public:

	/*!
	 * Constructor.
	 *
	 * @param [in] iPin PIN number of the LEDs DATA.
	 * @param [in] iNumOfLeds Number of LEDs in the strip.
	 */
	CLEDStrip(int iPin, int iNumOfLEDs);

	/*!
	 * Destructor.
	 */
	virtual ~CLEDStrip();

	/*!
	 * Initialize the LED strip.
	 *
	 * @return true on success or false on failure.
	 */
	bool Init();

	/*!
	 * Turn off all the LEDs.
	 */
	void Off();

	bool Animate_ColorWipe(uint32_t uiColor, int iDelay);
	bool Animate_TheaterChase(uint32_t uiColor, int iCycles, int iGap, int iDelay);

};

} // namespace Drivers

#endif // LEDSTRIP_H_

/*
 * Button.cpp
 *
 *  Created on: 15 באפר 2014
 *      Author: Vitaly
 */

#include "Button.h"

#include "Arduino.h" // Arduino APIs

namespace Drivers {

// Minimal interval for button debouncing in milliseconds
#define MIN_DEBOUNCE_INTERVAL	10

CButton::CButton(uint8_t uiPinNum, ELevel eLevel) :
	m_uiPinNum(uiPinNum),
	m_eLevel(eLevel),
	m_fLastState(false),
	m_uiPressedTimestamp(0),
	m_uiStateChangeTimestamp(0)
{
	// Decide whether the pin should be set to INPUT or
	// the internal pull-up resistor should be used as well.
	if (m_eLevel == eActiveLow)
		pinMode(m_uiPinNum, INPUT_PULLUP);
	else
		pinMode(m_uiPinNum, INPUT);
}

CButton::~CButton()
{
}

bool CButton::IsPressed()
{
	int iState = digitalRead(m_uiPinNum);

	// Check whether the button is pressed
	if (((m_eLevel == eActiveLow)  && (iState == 0)) ||
		((m_eLevel == eActiveHigh) && (iState == 1)))
		return (true);

	return (false);
}

int CButton::Held(uint32_t uiPeriod)
{
	bool 		fCurrState = IsPressed();
	uint32_t	uiCurrTimestamp = millis();

	// Prevent ghost readings
	if (uiCurrTimestamp < m_uiStateChangeTimestamp + MIN_DEBOUNCE_INTERVAL)
		return (0);

	// Press detection
	if (fCurrState == true && m_fLastState == false)
	{
		m_fLastState 				= true;
		m_uiPressedTimestamp 		= uiCurrTimestamp;
		m_uiStateChangeTimestamp	= uiCurrTimestamp;
	}
	// Release detection
	else if (fCurrState == false && m_fLastState == true)
	{
		m_fLastState				= false;
		m_uiPressedTimestamp		= 0;
		m_uiStateChangeTimestamp	= uiCurrTimestamp;
	}
	// Button is held pressed
	else if (fCurrState == true && m_fLastState == true)
	{
		// Check whether the given period has elapsed
		if (uiCurrTimestamp - m_uiPressedTimestamp >= uiPeriod)
		{
			// In order to avoid flooding the caller, update the
			// pressed time-stamp value
			m_uiPressedTimestamp = uiCurrTimestamp;
			return (2);
		}
		else
			return (1);
	}

	return (0);
}

} // namespace Drivers

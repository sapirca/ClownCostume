/*
 * ADXL345.cpp
 *
 *  Created on: 28 αταψ 2015
 *      Author: Vitaly
 */

#include "ADXL345.h"

namespace Drivers {

CADXL345::CADXL345(int32_t iSensorID) :
	m_cADXL345(iSensorID),
	m_dlLastValue(0),
	m_eCurrMovementState(eMovement_Static),
	m_ulLastValueTime(0),
	m_ulLastChangeTime(0)
{
}

CADXL345::~CADXL345()
{
}

bool CADXL345::Init()
{
	// Attempt to initialize the sensor
	if (m_cADXL345.begin() == false)
		return (false);

	// Set the range for the sensor
	m_cADXL345.setRange(ADXL345_RANGE_16_G);

	return (true);
}

double CADXL345::Value()
{
	sensors_event_t sSensorEvent;
	double dlValue = 0;

	// Read data from the sensor
	m_cADXL345.getEvent(&sSensorEvent);

	// Calculate the value
	dlValue = sqrt((sSensorEvent.acceleration.x * sSensorEvent.acceleration.x) +
			  	   (sSensorEvent.acceleration.y * sSensorEvent.acceleration.y) +
			  	   (sSensorEvent.acceleration.z * sSensorEvent.acceleration.z));

	return (dlValue);
}

CADXL345::EMovement CADXL345::DetectMovement(int iInterval, int iTimeout)
{
	unsigned long ulCurrTime = millis();

	// Check whether a sample should be read from the sensor
	if (ulCurrTime < m_ulLastValueTime + iInterval)
		return (m_eCurrMovementState);

	// Read the current value from the sensor
	double dlCurrValue = Value();

	if (m_dlLastValue == 0)
		m_dlLastValue = dlCurrValue;

	// Calculate the difference from the previous sample
	double dlDiffValue = fabs(dlCurrValue - m_dlLastValue);

	// Adopt the current value
	m_dlLastValue = dlCurrValue;

	// No Movement
	if (dlDiffValue < 2)
	{
		if (m_eCurrMovementState > eMovement_Static)
		{
			if (ulCurrTime < m_ulLastChangeTime + iTimeout)
				return (m_eCurrMovementState);

//			Serial.println(dlDiffValue);

			m_eCurrMovementState = eMovement_Static;
			m_ulLastChangeTime = ulCurrTime;
		}
	}
	// Light Movement
	else if (dlDiffValue >= 2 && dlDiffValue < 6)
	{
		if (m_eCurrMovementState < eMovement_Light)
		{
//			Serial.println(dlDiffValue);

			m_eCurrMovementState = eMovement_Light;
			m_ulLastChangeTime = ulCurrTime;
		}
	}
	// Hard Movement
	else
	{
		if (m_eCurrMovementState < eMovement_Hard)
		{
//			Serial.println(dlDiffValue);

			m_eCurrMovementState = eMovement_Hard;
			m_ulLastChangeTime = ulCurrTime;
		}
	}

	return (m_eCurrMovementState);
}

} // namespace Drivers

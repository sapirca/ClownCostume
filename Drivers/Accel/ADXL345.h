/*
 * ADXL345.h
 *
 *  Created on: 28 αταψ 2015
 *      Author: Vitaly
 */

#ifndef ADXL345_H_
#define ADXL345_H_

#include "Library/Adafruit_ADXL345_U.h"

namespace Drivers {

class CADXL345
{

/*
 * Public definitions:
 */
public:

	enum EMovement
	{
		eMovement_Static = 0,
		eMovement_Light,
		eMovement_Hard
	};

/*
 * Private data-members:
 */
private:

	/*!
	 * Low level driver for the sensor.
	 */
	Adafruit_ADXL345_Unified	m_cADXL345;

	/*!
	 * Last measured sensor value.
	 */
	double						m_dlLastValue;

	EMovement					m_eCurrMovementState;

	/*!
	 * Time-stamp of the last read value.
	 */
	unsigned long				m_ulLastValueTime;

	/*!
	 * Time-stamp of the last movement state change.
	 */
	unsigned long				m_ulLastChangeTime;

/*
 * Public methods:
 */
public:

	/*!
	 * Constructor.
	 *
	 * @param [in] iSensorID User defined sensor ID.
	 */
	CADXL345(int32_t iSensorID = 12345);

	/*!
	 * Destructor.
	 */
	virtual ~CADXL345();

	/*!
	 * Initialize the accelerometer sensor.
	 */
	bool Init();

	/*!
	 * Return the current value read from the sensor.
	 * The returned value is a combination of all 3 axis.
	 */
	double Value();

	/*!
	 * Movement detection method.
	 *
	 * @param [in] iInterval Interval in milliseconds between two samples.
	 * @param [in] iTimeout Time in milliseconds before return to static mode.
	 */
	EMovement DetectMovement(int iInterval, int iTimeout);
};

} // namespace Drivers

#endif // ADXL345_H_

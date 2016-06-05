/*
 * IR.h
 *
 *  Created on: 27 αταψ 2015
 *      Author: Vitaly
 */

#ifndef IR_H_
#define IR_H_

#include "Library/IRremote.h"

namespace Drivers {

class CIR
{

/*
 * Public types:
 */
public:

	/*!
	 * IR Remote button codes.
	 */
	typedef enum
	{
		// No Value / Unknown Value
		eButton_NoVal = 0,
		eButton_Unknown,

		// Control
		eButton_Power,
		eButton_Mode,
		eButton_Mute,
		eButton_EQ,

		// Media
		eButton_Play,
		eButton_Prev,
		eButton_Next,
		eButton_VolDown,
		eButton_VolUp,
		eButton_Repeat,

		// Numbers
		eButton_Num0,
		eButton_Num1,
		eButton_Num2,
		eButton_Num3,
		eButton_Num4,
		eButton_Num5,
		eButton_Num6,
		eButton_Num7,
		eButton_Num8,
		eButton_Num9

	} EButton;

/*
 * Private data-members:
 */
private:

	/*!
	 * IR sensor input pin number.
	 */
	int		m_iPin;

	/*!
	 * IR Receiver class instance.
	 */
	IRrecv	m_cIRRecv;

	/*!
	 * Last detected button.
	 */
	EButton	m_eLastButton;

/*
 * Public methods:
 */
public:

	/*!
	 * Constructor.
	 *
	 * @param [in] iPin IR sensor input pin number.
	 */
	CIR(int iPin);

	/*!
	 * Destructor.
	 */
	virtual ~CIR();

	/*!
	 * Initialize the IR driver.
	 *
	 * @return true on success or false on failure.
	 */
	bool Init();

	/*!
	 * Returns the latest read value from the sensor.
	 */
	EButton Value();

	/*!
	 * Returns the string name of the button.
	 *
	 * @param [in] eButton The button value.
	 */
	static const char* ToString(EButton eButton);
};

} // namespace Drivers

#endif // IR_H_

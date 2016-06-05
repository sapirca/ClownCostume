/*
 * IR.cpp
 *
 *  Created on: 27 αταψ 2015
 *      Author: Vitaly
 */

#include "IR.h"

namespace Drivers {

//////////////////////////////////////////////////////////////////////////////
////////////////////////// Local Module Definitions //////////////////////////
//////////////////////////////////////////////////////////////////////////////

/*!
 * Internal button representation structure.
 */
struct SButton
{
	// Remote Button
	CIR::EButton	eButton;

	// IR Value
	unsigned long	ulValue;

	// Button string name
	const char*		strName;
};

//////////////////////////////////////////////////////////////////////////////
/////////////////////////// Local Module Variables ///////////////////////////
//////////////////////////////////////////////////////////////////////////////

/*!
 * Array of supported remote buttons.
 */
static SButton s_arrButtons[] = {

	// Control Buttons
	{ CIR::eButton_Power, 	0xFFA25D, "Power" 	},
	{ CIR::eButton_Mode, 	0xFF629D, "Mode" 	},
	{ CIR::eButton_Mute, 	0xFFE21D, "Mute" 	},
	{ CIR::eButton_EQ, 		0xFFE01F, "EQ" 		},

	// Media Buttons
	{ CIR::eButton_Play, 	0xFF22DD, "Play" 	},
	{ CIR::eButton_Prev, 	0xFF02FD, "Prev" 	},
	{ CIR::eButton_Next, 	0xFFC23D, "Next" 	},
	{ CIR::eButton_VolDown, 0xFFA857, "VolDown" },
	{ CIR::eButton_VolUp, 	0xFF906F, "VolUp" 	},
	{ CIR::eButton_Repeat, 	0xFF9867, "Repeat" 	},

	// Numbers
	{ CIR::eButton_Num0, 	0xFF6897, "Num 0" 	},
	{ CIR::eButton_Num1, 	0xFF30CF, "Num 1" 	},
	{ CIR::eButton_Num2, 	0xFF18E7, "Num 2" 	},
	{ CIR::eButton_Num3, 	0xFF7A85, "Num 3" 	},
	{ CIR::eButton_Num4, 	0xFF10EF, "Num 4" 	},
	{ CIR::eButton_Num5, 	0xFF38C7, "Num 5" 	},
	{ CIR::eButton_Num6, 	0xFF5AA5, "Num 6" 	},
	{ CIR::eButton_Num7, 	0xFF42BD, "Num 7" 	},
	{ CIR::eButton_Num8, 	0xFF4AB5, "Num 8" 	},
	{ CIR::eButton_Num9, 	0xFF52AD, "Num 9" 	}

};

// Number of buttons in the array
#define NUM_OF_BUTTONS	(sizeof(s_arrButtons) / sizeof(SButton))

//////////////////////////////////////////////////////////////////////////////
/////////////////////////////// Implementation ///////////////////////////////
//////////////////////////////////////////////////////////////////////////////

CIR::CIR(int iPin) :
	m_iPin(iPin),
	m_cIRRecv(iPin),
	m_eLastButton(CIR::eButton_Unknown)
{
}

CIR::~CIR()
{
}

bool CIR::Init()
{
	// Enable the IR input pin
	m_cIRRecv.enableIRIn();

	return (true);
}

CIR::EButton CIR::Value()
{
	decode_results sIRResult;

	// Check whether some value was received from the IR sensor
	if (!m_cIRRecv.decode(&sIRResult))
		return (CIR::eButton_NoVal);

//	Serial.println(sIRResult.value, HEX);

	// Reset the IR sensor state (to receive the next value)
	m_cIRRecv.resume();

	// If the value is 0xFFFFFF, return with NoVal
	if (sIRResult.value == 0xFFFFFFFF)
		return (CIR::eButton_NoVal);

	// Attempt to match the received value
	for (int i = 0; i < NUM_OF_BUTTONS; i++)
		if (s_arrButtons[i].ulValue == sIRResult.value)
			return ((m_eLastButton = s_arrButtons[i].eButton));

	// Unknown value received
	return (CIR::eButton_Unknown);
}

const char* CIR::ToString(CIR::EButton eButton)
{
	// Search for the button
	for (int i = 0; i < NUM_OF_BUTTONS; i++)
		if (s_arrButtons[i].eButton == eButton)
			return (s_arrButtons[i].strName);

	return ("Invalid");
}

} // namespace Drivers

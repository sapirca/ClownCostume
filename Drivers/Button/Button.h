/*
 * Button.h
 *
 *  Created on: 15 באפר 2014
 *      Author: Vitaly
 */

#ifndef BUTTON_H_
#define BUTTON_H_

#include <stdint.h>

namespace Drivers {

/*!
 * \brief The CButton class implements button related logic.
 */
class CButton
{

/*
 * Public class definitions:
 */
public:

	/*!
	 * Enumerates the supported logic levels.
	 */
	enum ELevel
	{
		eActiveLow 	= 0, /*!< Pressed when the line is low */
		eActiveHigh = 1, /*!< Pressed when the line is high */
	};

/*
 * Private data-members:
 */
private:

	/*!
	 * The PIN number of the button.
	 */
	uint8_t		m_uiPinNum;

	/*!
	 * The level at which the button is active.
	 */
	ELevel		m_eLevel;

	/*!
	 * The last state of the button (true for pressed)
	 */
	bool		m_fLastState;

	/*!
	 * The time-stamp of the first moment at which we
	 * detected that the button is pressed.
	 */
	uint32_t	m_uiPressedTimestamp;

	/*!
	 * A time-stamp of the last button state change.
	 * Used for debouncing the button readings.
	 */
	uint32_t	m_uiStateChangeTimestamp;

/*
 * Public methods:
 */
public:

	/*!
	 * Constructor.
	 *
	 * @param [in] uiPinNum The PIN number of the button.
	 * @param [in] eLevel The level at which the button is pressed.
	 */
	CButton(uint8_t uiPinNum, ELevel eLevel = eActiveLow);

	/*!
	 * Destructor.
	 */
	virtual ~CButton();

	/*!
	 * Returns "true" if the button is pressed or "false" otherwise.
	 */
	bool IsPressed();

	/*!
	 * Returns the following values:
	 * 0 - Not pressed.
	 * 1 - Pressed.
	 * 2 - Held for the given period of time.
	 */
	int Held(uint32_t uiPeriod);

};

} // namespace Drivers

#endif /* BUTTON_H_ */

// Do not remove the include below
#include "Clown.h"

//#define ARDUINO_LED
#define ARDUINO_SOUND

#if defined(ARDUINO_LED)

#include "Drivers/Accel/ADXL345.h"
#include "Drivers/LEDStrip/Color.h"
#include "Drivers/LEDStrip/LEDStrip.h"
using namespace Drivers;

static CADXL345		s_cADXL345;
static CLEDStrip	s_cLEDStrip(9, 20);
//static CLEDStrip	s_cLEDStrip(4, 51);

#elif defined(ARDUINO_SOUND)

#include "Drivers/IR/IR.h"
#include "Drivers/Button/Button.h"
using namespace Drivers;

// TODO: TEMP
#include "Drivers/Sound/Library/SFEMP3Shield.h"

//static CIR 			s_cIR(5);
static SFEMP3Shield s_cMP3Player;

static int			s_iButtonPressed = 0;
static CButton		s_cButton1(3,  CButton::eActiveLow);
static CButton		s_cButton2(4,  CButton::eActiveLow);
static CButton		s_cButton3(5,  CButton::eActiveLow);
static CButton		s_cButton4(A0, CButton::eActiveLow);
static CButton		s_cButton5(A1, CButton::eActiveLow);
static CButton		s_cButton6(A2, CButton::eActiveLow);
static CButton		s_cButton7(A3, CButton::eActiveLow);

#endif

//The setup function is called once at startup of the sketch
void setup()
{
	int err;

	// Initialize the serial port
	Serial.begin(9600);

	// Initialize the IR sensor
//	s_cIR.Init();

#if defined(ARDUINO_LED)

	// Initialize the LED strip
	s_cLEDStrip.Init();

	if (s_cADXL345.Init() == false)
	{
		Serial.println("ADXL345 failed to initialize!");

		// Hang
		while (1) delay(100);
	}

#elif defined(ARDUINO_SOUND)

//	Serial.println("Skipping MP3 module...");

	// Initialize the MP3 Player
	if ((err = s_cMP3Player.begin()) != 0)
	{
		Serial.print("MP3 Player failed to initialize: ");
		Serial.println(err);

		// Hang
		while (1) delay(100);
	}

	s_cMP3Player.SetVolume(0, 0);

#endif

}

// The loop function is called in an endless loop
void loop()
{
#if defined(ARDUINO_LED)

	// LED
//	{
//		static int i = 0;
//
//		if (i == 0)
//		{
////			if (s_cLEDStrip.Animate_ColorWipe(CColor::GetColor32(CColor::Red), 50))
////			if (s_cLEDStrip.Animate_TheaterChase(CColor::GetColor32(CColor::Red), 10, 3, 50))
//			if (s_cLEDStrip.Animate_TheaterChase(0, 256, 3, 50))
//				i = 1;
//		}
//		else if (i == 1)
//		{
////			if (s_cLEDStrip.Animate_ColorWipe(CColor::GetColor32(CColor::Green), 50))
////			if (s_cLEDStrip.Animate_TheaterChase(CColor::GetColor32(CColor::Green), 10, 3, 50))
//			if (s_cLEDStrip.Animate_TheaterChase(1, 256, 3, 50))
//				i = 2;
//		}
//		else if (i == 2)
//		{
////			if (s_cLEDStrip.Animate_ColorWipe(CColor::GetColor32(CColor::Blue), 50))
//			if (s_cLEDStrip.Animate_TheaterChase(CColor::GetColor32(CColor::Blue), 10, 4, 50))
////			if (s_cLEDStrip.Animate_TheaterChase(0, 256, 3, 50))
//				i = 0;
//		}
//	}

	switch (s_cADXL345.DetectMovement(100, 1000))
	{
		case CADXL345::eMovement_Static: s_cLEDStrip.Off(); break;
		case CADXL345::eMovement_Light: s_cLEDStrip.Animate_TheaterChase(1, 256, 3, 150); break;
		case CADXL345::eMovement_Hard: s_cLEDStrip.Animate_TheaterChase(1, 256, 3, 50); break;
	}

//	static double 	dlVal = 0;
//	double 			dlCurrVal = s_cADXL345.Value();
//
//	dlVal = (dlVal * 0.9f) + (dlCurrVal * 0.1f);
//
//	Serial.println(dlVal);
//	delay(100);

#elif defined(ARDUINO_SOUND)

	CIR::EButton eIRButton;

	// Check for values from the IR sensor
//	if ((eIRButton = s_cIR.Value()) != CIR::eButton_NoVal)
//		Serial.println(CIR::ToString(eIRButton));

//	int chIn = Serial.read();
//
////	switch (eIRButton)
//	switch (chIn)
//	{
//		case 's'/*CIR::eButton_Play*/: s_cMP3Player.stopTrack(); break;
//
//		case '1'/*CIR::eButton_Num1*/:
//		case '2'/*CIR::eButton_Num2*/:
//		case '3'/*CIR::eButton_Num3*/:
//		case '4'/*CIR::eButton_Num4*/:
//		{
//			if (s_cMP3Player.isPlaying())
//				s_cMP3Player.stopTrack();
//
//			//s_cMP3Player.playTrack(eIRButton - CIR::eButton_Num0);
//			s_cMP3Player.playTrack(chIn - '0');
//
//		} break;
//	}

	int iButtonPressed = 0;

	if (s_cButton1.IsPressed())
		iButtonPressed = 1;
//	else if (s_cButton2.IsPressed())
//		iButtonPressed = 2;
	else if (s_cButton3.IsPressed())
		iButtonPressed = 3;
	else if (s_cButton4.IsPressed())
		iButtonPressed = 4;
	else if (s_cButton5.IsPressed())
		iButtonPressed = 5;
	else if (s_cButton6.IsPressed())
		iButtonPressed = 6;
	else if (s_cButton7.IsPressed())
		iButtonPressed = 7;

	// New button press
	if (  iButtonPressed > 0 &&
		((iButtonPressed != s_iButtonPressed) || (s_cMP3Player.isPlaying() == false)))
	{
		Serial.print("Pressed: ");
		Serial.println(iButtonPressed);

		// Stop the music (if playing)
		if (s_cMP3Player.isPlaying())
			s_cMP3Player.stopTrack();

		// Play the track
		if (iButtonPressed < 7)
			s_cMP3Player.playTrack(iButtonPressed);

		// Store the last pressed button
		s_iButtonPressed = iButtonPressed;
	}


#endif
}

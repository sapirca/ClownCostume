/*
 * Color.h
 *
 *  Created on: 28 αταψ 2015
 *      Author: Vitaly
 */

#ifndef COLOR_H_
#define COLOR_H_

#include <stdint.h>

namespace Drivers {

class CColor
{

/*
 * Public definitions:
 */
public:

	/*!
	 * Defines an RGB color.
	 */
	struct SColor
	{
		uint8_t R;
		uint8_t G;
		uint8_t B;
	};

	/*!
	 * Enumerates some of most popular colors.
	 */
	enum EColor
	{
		eColor_Invalid = -1,	/*!< Invalid color value */

		Alice_Blue = 0,
		Antique_White,
		Aqua,
		Aquamarine,
		Azure,
		Beige,
		Bisque,
		Black,
		Blanched_Almond,
		Blue,
		Blue_Violet,
		Brown,
		Burlywood,
		Cadet_Blue,
		Chartreuse,
		Chocolate,
		Coral,
		Cornflower_Blue,
		Cornsilk,
		Cyan,
		Dark_Blue,
		Dark_Cyan,
		Dark_Goldenrod,
		Dark_Gray,
		Dark_Green,
		Dark_Khaki,
		Dark_Magenta,
		Dark_Olive_Green,
		Dark_Orange,
		Dark_Orchid,
		Dark_Red,
		Dark_Salmon,
		Dark_Sea_Green,
		Dark_Slate_Blue,
		Dark_Slate_Gray,
		Dark_Turquoise,
		Dark_Violet,
		Deep_Pink,
		Deep_Sky_Blue,
		Dim_Gray,
		Dodger_Blue,
		Firebrick,
		Floral_White,
		Forest_Green,
		Fuschia,
		Gainsboro,
		Ghost_White,
		Gold,
		Goldenrod,
		Gray,
		Green,
		Green_Yellow,
		Honeydew,
		Hot_Pink,
		Indian_Red,
		Ivory,
		Khaki,
		Lavender,
		Lavender_Blush,
		Lawn_Green,
		Lemon_Chiffon,
		Light_Blue,
		Light_Coral,
		Light_Cyan,
		Light_Goldenrod,
		Light_Goldenrod_Yellow,
		Light_Gray,
		Light_Green,
		Light_Pink,
		Light_Salmon,
		Light_Sea_Green,
		Light_Sky_Blue,
		Light_Slate_Blue,
		Light_Slate_Gray,
		Light_Steel_Blue,
		Light_Yellow,
		Lime,
		Lime_Green,
		Linen,
		Magenta,
		Maroon,
		Medium_Aquamarine,
		Medium_Blue,
		Medium_Orchid,
		Medium_Purple,
		Medium_Sea_Green,
		Medium_Slate_Blue,
		Medium_Spring_Green,
		Medium_Turquoise,
		Medium_Violet_Red,
		Midnight_Blue,
		Mint_Cream,
		Misty_Rose,
		Moccasin,
		Navajo_White,
		Navy,
		Old_Lace,
		Olive,
		Olive_Drab,
		Orange,
		Orange_Red,
		Orchid,
		Pale_Goldenrod,
		Pale_Green,
		Pale_Turquoise,
		Pale_Violet_Red,
		Papaya_Whip,
		Peach_Puff,
		Peru,
		Pink,
		Plum,
		Powder_Blue,
		Purple,
		Red,
		Rosy_Brown,
		Royal_Blue,
		Saddle_Brown,
		Salmon,
		Sandy_Brown,
		Sea_Green,
		Seashell,
		Sienna,
		Silver,
		Sky_Blue,
		Slate_Blue,
		Slate_Gray,
		Snow,
		Spring_Green,
		Steel_Blue,
		Tan,
		Teal,
		Thistle,
		Tomato,
		Turquoise,
		Violet,
		Violet_Red,
		Wheat,
		White,
		White_Smoke,
		Yellow,
		Yellow_Green,

		eColor_NumOfColors 		/*!< Total number of predefined colors */
	};

/*
 * Private methods:
 */
private:

	/*!
	 * Constructor.
	 */
	CColor();

/*
 * Public methods:
 */
public:

	/*!
	 * Destructor.
	 */
	virtual ~CColor();

	/*!
	 * Returns the RGB value of the given color.
	 *
	 * @param [in] eColor The requested color.
	 * @param [out] sColor The RGB values of the requested color.
	 *
	 * @returns true on success of false if the requested color is invalid.
	 */
	static bool GetColorRGB(EColor eColor, SColor& sColor);

	/*!
	 * Returns a 32bit representation of the color.
	 *
	 * @param [in] eColor The requested color.
	 */
	static uint32_t GetColor32(EColor eColor);

	/*!
	 * Returns a 32bit representation of the color.
	 *
	 * @param [in] r Value of RED.
	 * @param [in] g Value of GREEN.
	 * @param [in] b Value of BLUE.
	 */
	static uint32_t GetColor32(uint8_t r, uint8_t g, uint8_t b);

};

} // namespace Drivers

#endif // COLOR_H_

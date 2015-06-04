#ifndef _RGB_H
#define _RGB_H
#include <stdint.h>

struct Color{
	uint8_t m_red;
	uint8_t m_green;
	uint8_t m_blue;
	Color(uint8_t red, uint8_t green, uint8_t blue): m_red(red), m_green(green), m_blue(blue) {}
};

class RGBColor{
	uint8_t m_blue, m_green, m_red;
	uint8_t normalize(int k);
public:
	RGBColor(): m_blue(255), m_green(255), m_red(255) {}
	RGBColor(const RGBColor& p);
	RGBColor(uint8_t red, uint8_t green, uint8_t blue);
	const Color getColor() const;
	void changeColor(const RGBColor& p);
	void changeColor(uint8_t red = 255, uint8_t green = 255, uint8_t blue = 255);
	RGBColor& operator= (const RGBColor& p);
	RGBColor operator+ (int k);
	RGBColor operator- (int k);
};

#endif
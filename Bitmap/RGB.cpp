#include "RGB.h"

uint8_t RGBColor::normalize (int k){
	if(k < 0) k = 0;
	else if(k > 255) k = 255;
	return k;
}

RGBColor::RGBColor(const RGBColor& p){
	m_red = p.m_red;
	m_green = p.m_green;
	m_blue = p.m_blue;
}

RGBColor::RGBColor(uint8_t red, uint8_t green, uint8_t blue){
	m_red = red;
	m_green = green;
	m_blue = blue;
}

const Color RGBColor::getColor() const{
	return Color(m_red, m_green, m_blue);
}

void RGBColor::changeColor(const RGBColor& p){
	m_red = p.m_red;
	m_green = p.m_green;
	m_blue = p.m_blue;
}

void RGBColor::changeColor(uint8_t red, uint8_t green, uint8_t blue){
	m_red = red;
	m_green = green;
	m_blue = blue;
}

RGBColor& RGBColor::operator= (const RGBColor& p){
	m_red = p.m_red;
	m_green = p.m_green;
	m_blue = p.m_blue;
	return *this;
}

RGBColor RGBColor::operator+ (int k){
	RGBColor result;
	int tmp;
	tmp = k + m_red;
	if(tmp >= 0 && tmp <= 255) result.m_red = tmp;
	tmp = k + m_green;
	if(tmp >= 0 && tmp <= 255) result.m_green = tmp;
	tmp = k + m_blue;
	if(tmp >= 0 && tmp <= 255) result.m_blue = tmp;
	return result;
}

RGBColor RGBColor::operator- (int k){
	RGBColor result;
	int tmp;
	tmp = (int)m_red - k;
	if(tmp >= 0 && tmp <= 255) result.m_red = tmp;
	tmp = (int)m_green - k;
	if(tmp >= 0 && tmp <= 255) result.m_green = tmp;
	tmp = (int)m_blue - k;
	if(tmp >= 0 && tmp <= 255) result.m_blue = tmp;
	return result;
}
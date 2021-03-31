#include "BaseWidget.h"
#include "BaseWidget.h"
#include "../cwsdk.h"

float* cube::BaseWidget::DrawBaseWidgetText(FloatVector2* vec, std::wstring* text, float x, float y)
{
	return ((float* (*)(cube::BaseWidget*, FloatVector2*, std::wstring*, float, float))CWOffset(0x269210))(this, vec, text, x, y);
}

void cube::BaseWidget::SetDrawColor(FloatRGBA *color)
{
	this->draw_color = *color;
}

void cube::BaseWidget::SetDrawColor(char r, char g, char b, char a)
{
	float f_red = (float)r / 255.0;
	float f_green = (float)g / 255.0;
	float f_blue = (float)b / 255.0;
	float f_alpha = (float)a / 255.0;
	FloatRGBA color(f_red, f_green, f_blue, f_alpha);
	this->SetDrawColor(&color);
}

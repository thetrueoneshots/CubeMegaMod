#include "FloatRGBA.h"

FloatRGBA::FloatRGBA() {
	this->red = 0.0;
	this->green = 0.0;
	this->blue = 0.0;
	this->alpha = 0.0;
}

FloatRGBA::FloatRGBA(float red, float green, float blue, float alpha){
    this->red = red;
    this->green = green;
    this->blue = blue;
    this->alpha = alpha;
}

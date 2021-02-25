#ifndef COLORRGB_H
#define COLORRGB_H

template <typename T>
class ColorRGB {
    public:
        T red;
        T green;
        T blue;

		ColorRGB() {
			this->red = (T)0;
			this->green = (T)0;
			this->blue = (T)0;
		}

		ColorRGB(T red, T green, T blue) {
			this->red = red;
			this->green = green;
			this->blue = blue;
		}
};

#define FloatRGB ColorRGB<float>
#define ByteRGB ColorRGB<unsigned char>

#endif // COLORRGB_H

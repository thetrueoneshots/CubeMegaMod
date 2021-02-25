#ifndef RGBA_H
#define RGBA_H

template <typename T>
class RGBA {
    public:
        T red;
        T green;
        T blue;
        T alpha;
		RGBA() {
			this->red = (T)0;
			this->green = (T)0;
			this->blue = (T)0;
			this->alpha = (T)0;
		}

		RGBA(T red, T green, T blue, T alpha) {
			this->red = red;
			this->green = green;
			this->blue = blue;
			this->alpha = alpha;
		}
};

#define FloatRGBA RGBA<float>
#define ByteRGBA RGBA<unsigned char>

#endif // RGBA_H

#ifndef BYTERGBA_H
#define BYTERGBA_H


class ByteRGBA {
    public:
		unsigned char red;
		unsigned char green;
		unsigned char blue;
		unsigned char alpha;
        ByteRGBA();
        ByteRGBA(unsigned char red, unsigned char green, unsigned char blue, unsigned char alpha);
    };


#endif // BYTERGBA_H

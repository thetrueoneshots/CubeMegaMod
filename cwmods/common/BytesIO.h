#ifndef COMMON_BYTESIO_H
#define COMMON_BYTESIO_H

#include <vector>
#include "types.h"

class BytesIO {

private:
	std::vector<u8> bytes;
	i32 offset;
	// 4 bytes padding

public:
	BytesIO();
	BytesIO(const u8* buffer, i32 size);
	BytesIO(std::vector<u8>& vec);

	i32 Size();
	i32 Offset();
	void Seek(i32 index);

	template <typename T>
	bool Has() {
		return (Offset() - Size()) >= sizeof(T);
	}

	template <typename T>
	T Peak() {
		return *(T*)&bytes[offset];
	}

	template <typename T>
	T Read() {
		T result = Peak<T>();
		offset += sizeof(T);
		return result;
	}

	template <typename T>
	void Write(T element) {
		i32 requiredSize = offset + sizeof(T);
		if (Size() < requiredSize) {
			bytes.resize(requiredSize);
		}
		else {
			bytes.reserve(requiredSize);
		}
		*(T*)&bytes[offset] = element;
		offset += sizeof(T);
	}

	std::vector<u8>& Vector();

	u8* Data();
};

static_assert(sizeof(BytesIO) == 0x20, "BytesIO is not the correct size.");

#endif // COMMON_BYTESIO_H

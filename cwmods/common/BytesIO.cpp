#include "BytesIO.h"

BytesIO::BytesIO() {
	Seek(0);
}

BytesIO::BytesIO(const u8* buffer, i32 size) {
	bytes.resize(size);
	memcpy(bytes.data(), buffer, size);
	Seek(0);
}

BytesIO::BytesIO(std::vector<u8>& vec) {
	bytes.resize(vec.size());
	memcpy(bytes.data(), vec.data(), vec.size());
	Seek(0);
}

i32 BytesIO::Size() {
	return bytes.size();
}

i32 BytesIO::Offset() {
	return offset;
}

void BytesIO::Seek(i32 index) {
	offset = index;
}

std::vector<u8>& BytesIO::Vector() {
	return bytes;
}

u8* BytesIO::Data() {
	return bytes.data();
}
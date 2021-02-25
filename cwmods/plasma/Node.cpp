#include "Node.h"
#include "../cwsdk.h"

void plasma::Node::Translate(plasma::Vector<2, float>* base, plasma::Vector<2, float>* offset) {
	((void(*)(plasma::Node*, plasma::Vector<2, float>*, plasma::Vector<2, float>*))CWOffset(0x334510))(this, base, offset);
}
void plasma::Node::Translate(float baseX, float baseY, float offsetX, float offsetY) {
	plasma::Vector<2, float> base;
	plasma::Vector<2, float> offset;
	base.Set(0, baseX);
	base.Set(1, baseY);
	offset.Set(0, offsetX);
	offset.Set(1, offsetY);
	this->Translate(&base, &offset);
}
i32 plasma::Node::Draw(u32 flags) {
	return ((i32(*)(plasma::Node*, u32))CWOffset(0x330B20))(this, flags);
}
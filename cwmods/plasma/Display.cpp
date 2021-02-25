#include "Display.h"

void plasma::Display::SetVisibility(int frame, int value) {
    this->visibility.data.at(frame) = value;
}

int plasma::Display::GetVisibility(int frame) {
    return this->visibility.data.at(frame);
}

int plasma::Display::GetFrameCount() {
    return this->visibility.data.size();
}

#ifndef DBUTTON_H
#define DBUTTON_H
#include "cwsdk.h"

class DButton {
private:
	time_t last_time;
	BYTE oldState;
	BYTE currentState;

public:
	int diKey;
	DButton(int diKey);
	void Update(BYTE* diKeys);
	int Pressed();
	void SetKey(int dikey);
	const char* GetKeyName();

};
#endif // DBUTTON_H
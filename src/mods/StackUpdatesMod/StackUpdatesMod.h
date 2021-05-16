#pragma once
#include "../../CubeMod.h"

class StackUpdatesMod : public CubeMod
{
public:
	StackUpdatesMod() {
		m_Name = "Stack Updates Mod";
		m_FileName = "StackUpdatesMod";
		m_ID = 12;
		m_Version = { 1, 0, 0 };
	}
	
	void Initialize();
};
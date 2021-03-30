#pragma once

#include <Windows.h>
#include <psapi.h>
#include <sstream>
#include <vector>
#include <iostream>
#include "../main.h"

#define CUBE_EXE_NAME "cubeworld.exe"

class MemoryHelper
{
public:
	static MODULEINFO GetModuleInfo(HMODULE module_handle)
	{
		MODULEINFO module_info;
		GetModuleInformation(GetCurrentProcess(), module_handle, &module_info, sizeof(MODULEINFO));

		return module_info;
	}

	static MODULEINFO GetModuleInfo(char* module)
	{
		return GetModuleInfo(GetModuleHandle(module));
	}

	static uint64_t GetCubeBase()
	{
		static auto cube_info = GetModuleInfo(CUBE_EXE_NAME);
		return (uint64_t)cube_info.lpBaseOfDll;
	}

	/**
	 * Searches the cubeworld module for any instance of a specified string, and replaces it in memory
	 * @param search
	 * @param replace
	 */
	static void FindAndReplaceString(std::wstring search, std::wstring replace)
	{
		MODULEINFO module_info;
		HMODULE module_handle = GetModuleHandle(CUBE_EXE_NAME);
		if (!module_handle) return;

		GetModuleInformation(GetCurrentProcess(), module_handle, &module_info, sizeof(MODULEINFO));

		uint64_t base_address = (uint64_t)module_info.lpBaseOfDll;
		uint64_t module_size = module_info.SizeOfImage;

		auto search_cstr = search.c_str();
		auto search_len = search.size();

		for (uint64_t i = 0; i < module_size - search_len * 2; i++)
		{
			uint16_t* check_addr = (uint16_t*)(base_address + i);

			bool found = true;
			for (int b = 0; b < search_len; b++)
			{
				uint16_t pattern_byte = search_cstr[b];
				uint16_t check_byte = check_addr[b];

				//If any don't match its not the right pattern
				if (pattern_byte != check_byte)
				{
					found = false;
					break;
				}
			}

			if (found)
			{
				//Replace it :D
				PatchMemory((void*)check_addr, (void*)replace.c_str(), replace.size() * 2 + 2);
			}
		}
	}

	//Default to cubeworld module
	static uint64_t FindPattern(std::string pattern, bool get_end = false)
	{
		return FindPattern(CUBE_EXE_NAME, pattern, get_end);
	}

	static uint64_t FindPattern(std::string module, std::string pattern, bool get_end = false)
	{
		std::vector<uint8_t> pattern_bytes;

		std::istringstream iss(pattern);
		for (std::string s; iss >> s;)
		{
			if (s == "?" || s == "??") pattern_bytes.push_back(NULL);
			else pattern_bytes.push_back(std::stoi(s, 0, 16));
		}

		MODULEINFO module_info;
		HMODULE module_handle = GetModuleHandle(module.c_str());
		if (!module_handle) return 0;

		GetModuleInformation(GetCurrentProcess(), module_handle, &module_info, sizeof(MODULEINFO));

		uint64_t base_address = (uint64_t)module_info.lpBaseOfDll;
		uint64_t module_size = module_info.SizeOfImage;

		for (uint64_t i = 0; i < module_size - pattern_bytes.size(); i++)
		{
			uint64_t check_addr = base_address + i;

			bool found = true;
			for (int b = 0; b < pattern_bytes.size(); b++)
			{
				uint8_t pattern_byte = pattern_bytes[b];
				uint8_t check_byte = *(uint8_t*)(check_addr + b);

				//NULL byte can match anything
				if (pattern_byte == NULL) continue;

				//If any don't match its not the right pattern
				if (pattern_byte != check_byte)
				{
					found = false;
					break;
				}
			}

			if (found)
			{
				if (get_end) check_addr = check_addr + pattern_bytes.size();

				return check_addr;
			}
		}

		return 0;
	}

	static void PatchMemory(void* dst, void* src, uint64_t size)
	{
		DWORD OldProtection;
		if (VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &OldProtection))
		{
			memcpy(dst, src, size);
			VirtualProtect(dst, size, OldProtection, &OldProtection);
		}
	}

	template<class T>
	static void PatchMemory(uint64_t dst, T src)
	{
		PatchMemory((void*)dst, src);
	}

	template<class T>
	static void PatchMemory(void* dst, T src)
	{
		if (!dst) return;

		DWORD OldProtection;
		auto size = sizeof(T);
		if (VirtualProtect(dst, size, PAGE_EXECUTE_READWRITE, &OldProtection))
		{
			memcpy(dst, &src, size);
			VirtualProtect(dst, size, OldProtection, &OldProtection);
		}
	}
};

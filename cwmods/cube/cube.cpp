#include "cube.h"

cube::Game* cube::GetGame() {
	return *(cube::Game**)(CWOffset(0x551A80));
}

ID3D11Device* cube::GetID3D11Device() {
	return *(ID3D11Device**)(CWOffset(0x551A90));
}

ID3D11DeviceContext* cube::GetID3D11DeviceContext() {
	return *(ID3D11DeviceContext**)(CWOffset(0x551A98));
}

void* cube::GetSteamNetworkingContext() {
	return CWOffset(0x5314F0);
}

void* cube::GetSteamUserContext() {
	return CWOffset(0x5314C0);
}

void* cube::SteamInternal_ContextInit(void* context) {
	auto contextInitPtr = *(void**)CWOffset(0x42CD90);
	return *((void**(*)(void*))contextInitPtr)(context);
}

ISteamNetworking* cube::SteamNetworking() {
	return (ISteamNetworking*)cube::SteamInternal_ContextInit(cube::GetSteamNetworkingContext());
}

ISteamUser* cube::SteamUser() {
	return (ISteamUser*)cube::SteamInternal_ContextInit(cube::GetSteamUserContext());
}
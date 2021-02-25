#include "Client.h"
#include "../cwsdk.h"

void cube::Client::JoinSteamID(long long steamID) {
    ((void(*)(cube::Client*, long long))CWOffset(0x3D820))(this, steamID);
}

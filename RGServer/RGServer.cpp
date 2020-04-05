// RGServer.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <windows.h>

#include "RGProtocol.h"
#include "RGProc.h"

extern P_TOS_REQ_ENTER_LOBBY tos_req_enter_lobby;

int main(int argc, char* argv[])
{
	strcpy(tos_req_enter_lobby.hdr.strContentName, "pjmc");
	MsgProc((LPP_COMMON)&tos_req_enter_lobby);
	SendMsg(TO_CLIENT, (LPP_COMMON)&tos_req_enter_lobby);
	return 0;
}



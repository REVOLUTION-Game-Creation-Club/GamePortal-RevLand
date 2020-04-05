#include <windows.h>
#include <stdio.h>
#include "RGProtocol.h"
#include "RGProc.h"

DWORD ProcTosReqEnterLobby(LPP_COMMON lpPacket)
{
	printf("%s", lpPacket->p_tos_req_enter_lobby.hdr.strContentName);
	return NO_ERROR;
}

DWORD ProcTosReqEnterRoom(LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD ProcTosReqMakeRoom(LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD ProcTosNtfExitGame(LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD ProcTosNtfUserState(LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD ProcTosNtfUpdateRoom(LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD ProcTocAckEnterLobby(LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD ProcTocAckEnterRoom(LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD ProcTocAckMakeRoom(LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD ProcTocNtfRoomList(LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD ProcTocNtfUserList(LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD ProcTocNtfUpdateRoom(LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD ProcTocNtfUpdateUser(LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD ProcTocNtfServerState(LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD ProcTorReqEnterRoom(LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD ProcTorReqUpdateUser(LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD ProcTorNtfExitRoom(LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD ProcTomAckEnterRoom(LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD ProcTomAckUpdateUser(LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD ProcTomNtfUpdateRoom(LPP_COMMON lpPacket)
{
	return NO_ERROR;
}


DWORD SendTosReqEnterLobby(TOWHOM toWhom, LPP_COMMON lpPacket)
{
	printf("%s", lpPacket->p_tos_req_enter_lobby.hdr.strContentName);
	return NO_ERROR;
}

DWORD SendTosReqEnterRoom(TOWHOM toWhom, LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD SendTosReqMakeRoom(TOWHOM toWhom, LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD SendTosNtfExitGame(TOWHOM toWhom, LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD SendTosNtfUserState(TOWHOM toWhom, LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD SendTosNtfUpdateRoom(TOWHOM toWhom, LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD SendTocAckEnterLobby(TOWHOM toWhom, LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD SendTocAckEnterRoom(TOWHOM toWhom, LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD SendTocAckMakeRoom(TOWHOM toWhom, LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD SendTocNtfRoomList(TOWHOM toWhom, LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD SendTocNtfUserList(TOWHOM toWhom, LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD SendTocNtfUpdateRoom(TOWHOM toWhom, LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD SendTocNtfUpdateUser(TOWHOM toWhom, LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD SendTocNtfServerState(TOWHOM toWhom, LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD SendTorReqEnterRoom(TOWHOM toWhom, LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD SendTorReqUpdateUser(TOWHOM toWhom, LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD SendTorNtfExitRoom(TOWHOM toWhom, LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD SendTomAckEnterRoom(TOWHOM toWhom, LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD SendTomAckUpdateUser(TOWHOM toWhom, LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD SendTomNtfUpdateRoom(TOWHOM toWhom, LPP_COMMON lpPacket)
{
	return NO_ERROR;
}

DWORD (*lpMsgProc[])(LPP_COMMON lppCommon) =
{
	NULL,
	ProcTosReqEnterLobby,
	ProcTosReqEnterRoom,
	ProcTosReqMakeRoom,
	ProcTosNtfExitGame,
	ProcTosNtfUserState,
	ProcTosNtfUpdateRoom,
	ProcTocAckEnterLobby,
	ProcTocAckEnterRoom,
	ProcTocAckMakeRoom,
	ProcTocNtfRoomList,
	ProcTocNtfUserList,
	ProcTocNtfUpdateRoom,
	ProcTocNtfUpdateUser,
	ProcTocNtfServerState,
	ProcTorReqEnterRoom,
	ProcTorReqUpdateUser,
	ProcTorNtfExitRoom,
	ProcTomAckEnterRoom,
	ProcTomAckUpdateUser,
	ProcTomNtfUpdateRoom,
	NULL,
};

DWORD (*lpSendMsg[])(TOWHOM toWhom, LPP_COMMON lppCommon) =
{
	NULL,
	SendTosReqEnterLobby,
	SendTosReqEnterRoom,
	SendTosReqMakeRoom,
	SendTosNtfExitGame,
	SendTosNtfUserState,
	SendTosNtfUpdateRoom,
	SendTocAckEnterLobby,
	SendTocAckEnterRoom,
	SendTocAckMakeRoom,
	SendTocNtfRoomList,
	SendTocNtfUserList,
	SendTocNtfUpdateRoom,
	SendTocNtfUpdateUser,
	SendTocNtfServerState,
	SendTorReqEnterRoom,
	SendTorReqUpdateUser,
	SendTorNtfExitRoom,
	SendTomAckEnterRoom,
	SendTomAckUpdateUser,
	SendTomNtfUpdateRoom,
	NULL,
};

DWORD MsgProc(LPP_COMMON lppCommon)
{
	return (*lpMsgProc[lppCommon->common_hdr.rpType])(lppCommon);
}

DWORD SendMsg(TOWHOM toWhom, LPP_COMMON lppCommon)
{
	return (*lpSendMsg[lppCommon->common_hdr.rpType])(toWhom, lppCommon);
}
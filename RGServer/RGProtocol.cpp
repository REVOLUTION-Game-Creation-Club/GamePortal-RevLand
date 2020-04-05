#include <windows.h>
#include "RGProtocol.h"

P_TOS_REQ_ENTER_LOBBY tos_req_enter_lobby =
{
	{
		sizeof(P_TOS_REQ_ENTER_LOBBY),
		{0},
		TOS_REQ_ENTER_LOBBY,
		0
	}
};

P_TOS_REQ_ENTER_ROOM tos_req_enter_room =
{
	{
		sizeof(P_TOS_REQ_ENTER_ROOM),
		{0},
		TOS_REQ_ENTER_ROOM,
		0
	}
};

P_TOS_REQ_MAKE_ROOM tos_req_make_room = 
{
	{
		sizeof(P_TOS_REQ_MAKE_ROOM),
		{0},
		TOS_REQ_MAKE_ROOM,
		0
	}
};

P_TOS_NTF_EXIT_GAME tos_ntf_exit_game = 
{
	{
		sizeof(P_TOS_NTF_EXIT_GAME),
		{0},
		TOS_NTF_EXIT_GAME,
		0
	}
};

P_TOS_NTF_USER_STATE tos_ntf_user_state =
{
	{
		sizeof(P_TOS_NTF_USER_STATE),
		{0},
		TOS_NTF_USER_STATE,
		0
	}
};

P_TOS_NTF_UPDATE_ROOM tos_ntf_update_room =
{
	{
		sizeof(P_TOS_NTF_UPDATE_ROOM),
		{0},
		TOS_NTF_UPDATE_ROOM,
		0
	}
};

P_TOC_ACK_ENTER_LOBBY toc_ack_enter_lobby =
{
	{
		sizeof(P_TOC_ACK_ENTER_LOBBY),
		{0},
		TOC_ACK_ENTER_LOBBY,
		0
	}
};

P_TOC_ACK_ENTER_ROOM toc_ack_enter_room =
{
	{
		sizeof(P_TOC_ACK_ENTER_ROOM),
		{0},
		TOC_ACK_ENTER_ROOM,
		0
	}
};

P_TOC_ACK_MAKE_ROOM toc_ack_make_room =
{	
	{
		sizeof(P_TOC_ACK_MAKE_ROOM),
		{0},
		TOC_ACK_MAKE_ROOM,
		0
	}
};

P_TOC_NTF_ROOM_LIST toc_ntf_room_list =
{	
	{
		sizeof(P_TOC_NTF_ROOM_LIST),
		{0},
		TOC_NTF_ROOM_LIST,
		0
	}
};

P_TOC_NTF_USER_LIST toc_ntf_user_list =
{	
	{
		sizeof(P_TOC_NTF_USER_LIST),
		{0},
		TOC_NTF_USER_LIST,
		0
	}
};

P_TOC_NTF_UPDATE_ROOM toc_ntf_update_room =
{	
	{
		sizeof(P_TOC_NTF_UPDATE_ROOM),
		{0},
		TOC_NTF_UPDATE_ROOM,
		0
	}
};

P_TOC_NTF_UPDATE_USER toc_ntf_update_user =
{	
	{
		sizeof(P_TOC_NTF_UPDATE_USER),
		{0},
		TOC_NTF_UPDATE_USER,
		0
	}
};

P_TOC_NTF_SERVER_STATE toc_ntf_server_state =
{	
	{
		sizeof(P_TOC_NTF_SERVER_STATE),
		{0},
		TOC_NTF_SERVER_STATE,
		0
	}
};

P_TOR_REQ_ENTER_ROOM tor_req_enter_room =
{	
	{
		sizeof(P_TOR_REQ_ENTER_ROOM),
		{0},
		TOR_REQ_ENTER_ROOM,
		0
	}
};

P_TOR_REQ_UPDATE_USER tor_req_update_user =
{	
	{
		sizeof(P_TOR_REQ_UPDATE_USER),
		{0},
		TOR_REQ_UPDATE_USER,
		0
	}
};

P_TOR_NTF_EXIT_ROOM tor_ntf_exit_room =
{	
	{
		sizeof(P_TOR_NTF_EXIT_ROOM),
		{0},
		TOR_NTF_EXIT_ROOM,
		0
	}
};

P_TOM_ACK_ENTER_ROOM tom_ack_enter_room =
{	
	{
		sizeof(P_TOM_ACK_ENTER_ROOM),
		{0},
		TOM_ACK_ENTER_ROOM,
		0
	}
};

P_TOM_ACK_UPDATE_USER tom_ack_update_user =
{	
	{
		sizeof(P_TOM_ACK_UPDATE_USER),
		{0},
		TOM_ACK_UPDATE_USER,
		0
	}
};

P_TOM_NTF_UPDATE_ROOM tom_ntf_update_room =
{	
	{
		sizeof(P_TOM_NTF_UPDATE_ROOM),
		{0},
		TOM_NTF_UPDATE_ROOM,
		0
	}
};
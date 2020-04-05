#ifndef _RGProtocol_H_
#define _RGProtocol_H_

// 약자 표기
//
// TOS : To Server		: 서버에게 보내는 메시지
// TOC : To Client		: 클라이언트에게 보내는 메시지
// TOR : To Room Major	: 방장에게 보내는 메시지
// TOM : To Room Member	: 방원에게 보내는 메시지
//
// NTF : Notify			: 통지
// REQ : Request		: 요청
// ACK : Acknowledge	: 응답
//

typedef enum {
	NO_TO = 0,
	TO_SERVER,
	TO_CLIENT,
	TO_OTHERS,
	TO_ROOM_MAJOR,
	TO_ROOM_MEMBER,
} TOWHOM;

typedef enum {
	
	NO_PROTOCOL = 0,

	TOS_REQ_ENTER_LOBBY,	// 서버에게 대기실 입장을 요청한다
	TOS_REQ_ENTER_ROOM,		// 서버에게 방 입장을 요청한다
	TOS_REQ_MAKE_ROOM,		// 서버에게 방 생성을 요청한다
	TOS_NTF_EXIT_GAME,		// 서버에게 게임 종료를 알린다
	TOS_NTF_USER_STATE,		// 서버에게 유저 상태를 알린다
	TOS_NTF_UPDATE_ROOM,	// 방장이 서버에게 갱신된 방 정보를 알린다

	TOC_ACK_ENTER_LOBBY,	// 클라이언트에게 대기실 입장 요청에 대한 응답을 한다
	TOC_ACK_ENTER_ROOM,		// 클라이언트에게 방 입장 요청에 대한 응답을 한다
	TOC_ACK_MAKE_ROOM,		// 클라이언트에게 방 생성 요청에 대한 응답을 한다
	TOC_NTF_ROOM_LIST,		// 클라이언트에게 방 목록을 알린다
	TOC_NTF_USER_LIST,		// 클라이언트에게 유저 목록을 알린다
	TOC_NTF_UPDATE_ROOM,	// 클라이언트에게 갱신된 방 정보를 알린다
	TOC_NTF_UPDATE_USER,	// 클라이언트에게 갱신된 유저 정보를 알린다
	TOC_NTF_SERVER_STATE,	// 클라이언트에게 서버 상태를 알린다

	TOR_REQ_ENTER_ROOM,		// 방장에게 방 입장을 요청한다
	TOR_REQ_UPDATE_USER,	// 방장에게 유저 정보 갱신을 요청한다
	TOR_NTF_EXIT_ROOM,		// 방장에게 방 퇴장을 알린다

	TOM_ACK_ENTER_ROOM,		// 방원에게 방 입장 요청에 대한 응답을 한다
	TOM_ACK_UPDATE_USER,	// 방원에게 유정 정보 갱신 요청을 응답한다
	TOM_NTF_UPDATE_ROOM,	// 방원에게 방 정보를 알린다

	END_PROTOCOL,

} RGPCT; // Rev Game Procotol

typedef enum 
{
	NO_ERR = 0,
	ERR_NO_DEFINE,
} RGERROR;

// Protocol 상관관계
/*
	[S] : 서버
	[C] : 요청한 클라이언트
	[OC]: 서버에 접속한 다른 클라이언트
	[M] : 요청한 방원
	[AM]: 같은 방에 있는 방원

	TOS_REQ_ENTER_LOBBY
	[C] : TOC_ACK_ENTER_LOBBY

		IF ACCEPT REQUEST
			[C] : TOC_NTF_USER_LIST
			[C] : TOC_NTF_ROOM_LIST
			[OC]: TOC_NTF_UPDATE_USER

	TOS_REQ_ENTER_ROOM
	[C] : TOC_ACK_ENTER_ROOM

  		IF ACCEPT REQUEST
			[OC]: TOC_NTF_UPDATE_ROOM
			[OC]: TOC_NTF_UPDATE_USER

	TOS_REQ_MAKE_ROOM
	[C] : TOC_ACK_MAKE_ROOM

	  	IF ACCEPT REQUEST
			[OC]: TOC_NTF_UPDATE_ROOM
			[OC]: TOC_NTF_UPDATE_USER
		
	TOS_NTF_EXIT_GAME
	[OC]: TOC_NTF_UPDATE_ROOM
	[OC]: TOC_NTF_UPDATE_USER

	TOS_NTF_USER_STATE
	[OC]: TOC_NTF_UPDATE_ROOM
	[OC]: TOC_NTF_UPDATE_USER

	TOC_NTF_SERVER_STATE
	
	TOR_REQ_ENTER_ROOM
	[M] : TOM_ACK_ENTER_ROOM

		IF ACCEPT REQUEST
			[AM]: TOM_NTF_UPDATE_ROOM
			[S] : TOS_NTF_UPDATE_ROOM

	TOR_REQ_UPDATE_USER
	[M] : TOM_ACK_UPDATE_USER
		
		IF ACCEPT REQUEST
		[AM]: TOM_NTF_UPDATE_ROOM
		[S] : TOS_NTF_UPDATE_ROOM

	TOR_NTF_EXIT_ROOM
	[AM]: TOM_NTF_UPDATE_ROOM
	[S] : TOS_NTF_UPDATE_ROOM
*/

typedef struct {
	DWORD dwLength;			 // 패킷 길이
	char strContentName[16]; // Content 이름
	RGPCT rpType;			 // Protocol의 종류 
	DWORD dwKey;			 // 보안 key
} HEADER;

typedef struct {
	HEADER hdr;
} P_TOS_REQ_ENTER_LOBBY, *LPP_TOS_REQ_ENTER_LOBBY;

typedef struct {
	HEADER hdr;
} P_TOS_REQ_ENTER_ROOM, *LPP_TOS_REQ_ENTER_ROOM;

typedef struct {
	HEADER hdr;
} P_TOS_REQ_MAKE_ROOM, *LPP_TOS_REQ_MAKE_ROOM;

typedef struct {
	HEADER hdr;
} P_TOS_NTF_EXIT_GAME, *LPP_TOS_NTF_EXIT_GAME;

typedef struct {
	HEADER hdr;
} P_TOS_NTF_USER_STATE, *LPP_TOS_NTF_USER_STATE;

typedef struct {
	HEADER hdr;
} P_TOS_NTF_UPDATE_ROOM, *LPP_TOS_NTF_UPDATE_ROOM;

typedef struct {
	HEADER hdr;
} P_TOC_ACK_ENTER_LOBBY, *LPP_TOC_ACK_ENTER_LOBBY;

typedef struct {
	HEADER hdr;
} P_TOC_ACK_ENTER_ROOM, *LPP_TOC_ACK_ENTER_ROOM;

typedef struct {
	HEADER hdr;
} P_TOC_ACK_MAKE_ROOM, *LPP_TOC_ACK_MAKE_ROOM;

typedef struct {
	HEADER hdr;
} P_TOC_NTF_ROOM_LIST, *LPP_TOC_NTF_ROOM_LIST;

typedef struct {
	HEADER hdr;
} P_TOC_NTF_USER_LIST, *LPP_TOC_NTF_USER_LIST;

typedef struct {
	HEADER hdr;
} P_TOC_NTF_UPDATE_ROOM, *LPP_TOC_NTF_UPDATE_ROOM;

typedef struct {
	HEADER hdr;
} P_TOC_NTF_UPDATE_USER, *LPP_TOC_NTF_UPDATE_USER;

typedef struct {
	HEADER hdr;
} P_TOC_NTF_SERVER_STATE, *LPP_TOC_NTF_SERVER_STATE;

typedef struct {
	HEADER hdr;
} P_TOR_REQ_ENTER_ROOM, *LPP_TOR_REQ_ENTER_ROOM;

typedef struct {
	HEADER hdr;
} P_TOR_REQ_UPDATE_USER, *LPP_TOR_REQ_UPDATE_USER;

typedef struct {
	HEADER hdr;
} P_TOR_NTF_EXIT_ROOM, *LPP_TOR_NTF_EXIT_ROOM;

typedef struct {
	HEADER hdr;
} P_TOM_ACK_ENTER_ROOM, *LPP_TOM_ACK_ENTER_ROOM;

typedef struct {
	HEADER hdr;
} P_TOM_ACK_UPDATE_USER, *LPP_TOM_ACK_UPDATE_USER;

typedef struct {
	HEADER hdr;
} P_TOM_NTF_UPDATE_ROOM, *LPP_TOM_NTF_UPDATE_ROOM;
	
typedef union {
	HEADER					common_hdr;
	P_TOS_REQ_ENTER_LOBBY	p_tos_req_enter_lobby;
	P_TOS_REQ_ENTER_ROOM	p_tos_req_enter_room;
	P_TOS_REQ_MAKE_ROOM		p_tos_req_make_room;
	P_TOS_NTF_EXIT_GAME		p_tos_ntf_exit_game;
	P_TOS_NTF_USER_STATE	p_tos_ntf_user_state;
	P_TOS_NTF_UPDATE_ROOM	p_tos_ntf_update_room;

	P_TOC_ACK_ENTER_LOBBY	p_toc_ack_enter_lobby;
	P_TOC_ACK_ENTER_ROOM	p_toc_ack_enter_room;
	P_TOC_ACK_MAKE_ROOM		p_toc_ack_make_room;
	P_TOC_NTF_ROOM_LIST		p_toc_ntf_room_list;
	P_TOC_NTF_USER_LIST		p_toc_ntf_user_list;
	P_TOC_NTF_UPDATE_ROOM	p_toc_ntf_update_room;
	P_TOC_NTF_UPDATE_USER	p_toc_ntf_update_user;
	P_TOC_NTF_SERVER_STATE	p_toc_ntf_server_state;

	P_TOR_REQ_ENTER_ROOM	p_tor_req_enter_room;
	P_TOR_REQ_UPDATE_USER	p_tor_req_update_user;
	P_TOR_NTF_EXIT_ROOM		p_tor_ntf_exit_room;

	P_TOM_ACK_ENTER_ROOM	p_tom_ack_enter_room;
	P_TOM_ACK_UPDATE_USER	p_tom_ack_update_user;
	P_TOM_NTF_UPDATE_ROOM	p_tom_ntf_update_room;

} P_COMMON, *LPP_COMMON;

#endif
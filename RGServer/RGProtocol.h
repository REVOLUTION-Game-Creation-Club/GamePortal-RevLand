#ifndef _RGProtocol_H_
#define _RGProtocol_H_

// ���� ǥ��
//
// TOS : To Server		: �������� ������ �޽���
// TOC : To Client		: Ŭ���̾�Ʈ���� ������ �޽���
// TOR : To Room Major	: ���忡�� ������ �޽���
// TOM : To Room Member	: ������� ������ �޽���
//
// NTF : Notify			: ����
// REQ : Request		: ��û
// ACK : Acknowledge	: ����
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

	TOS_REQ_ENTER_LOBBY,	// �������� ���� ������ ��û�Ѵ�
	TOS_REQ_ENTER_ROOM,		// �������� �� ������ ��û�Ѵ�
	TOS_REQ_MAKE_ROOM,		// �������� �� ������ ��û�Ѵ�
	TOS_NTF_EXIT_GAME,		// �������� ���� ���Ḧ �˸���
	TOS_NTF_USER_STATE,		// �������� ���� ���¸� �˸���
	TOS_NTF_UPDATE_ROOM,	// ������ �������� ���ŵ� �� ������ �˸���

	TOC_ACK_ENTER_LOBBY,	// Ŭ���̾�Ʈ���� ���� ���� ��û�� ���� ������ �Ѵ�
	TOC_ACK_ENTER_ROOM,		// Ŭ���̾�Ʈ���� �� ���� ��û�� ���� ������ �Ѵ�
	TOC_ACK_MAKE_ROOM,		// Ŭ���̾�Ʈ���� �� ���� ��û�� ���� ������ �Ѵ�
	TOC_NTF_ROOM_LIST,		// Ŭ���̾�Ʈ���� �� ����� �˸���
	TOC_NTF_USER_LIST,		// Ŭ���̾�Ʈ���� ���� ����� �˸���
	TOC_NTF_UPDATE_ROOM,	// Ŭ���̾�Ʈ���� ���ŵ� �� ������ �˸���
	TOC_NTF_UPDATE_USER,	// Ŭ���̾�Ʈ���� ���ŵ� ���� ������ �˸���
	TOC_NTF_SERVER_STATE,	// Ŭ���̾�Ʈ���� ���� ���¸� �˸���

	TOR_REQ_ENTER_ROOM,		// ���忡�� �� ������ ��û�Ѵ�
	TOR_REQ_UPDATE_USER,	// ���忡�� ���� ���� ������ ��û�Ѵ�
	TOR_NTF_EXIT_ROOM,		// ���忡�� �� ������ �˸���

	TOM_ACK_ENTER_ROOM,		// ������� �� ���� ��û�� ���� ������ �Ѵ�
	TOM_ACK_UPDATE_USER,	// ������� ���� ���� ���� ��û�� �����Ѵ�
	TOM_NTF_UPDATE_ROOM,	// ������� �� ������ �˸���

	END_PROTOCOL,

} RGPCT; // Rev Game Procotol

typedef enum 
{
	NO_ERR = 0,
	ERR_NO_DEFINE,
} RGERROR;

// Protocol �������
/*
	[S] : ����
	[C] : ��û�� Ŭ���̾�Ʈ
	[OC]: ������ ������ �ٸ� Ŭ���̾�Ʈ
	[M] : ��û�� ���
	[AM]: ���� �濡 �ִ� ���

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
	DWORD dwLength;			 // ��Ŷ ����
	char strContentName[16]; // Content �̸�
	RGPCT rpType;			 // Protocol�� ���� 
	DWORD dwKey;			 // ���� key
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
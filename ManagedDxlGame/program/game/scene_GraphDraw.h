#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "cardEffect.h"


extern int Cursor_hdl;												//�J�[�h���I�𒆂̕\���p
extern int TextWindow_hdl;											//�e�L�X�g�E�B���h�E�\���p

extern int Poster_Text_gpc_hdl;										//�����\���p�̉摜

extern int target_gpc_hdl;					//�^�[�Q�b�g�̉摜

extern int wallpaper_Title;			//�^�C�g����ʂ̔w�i

extern int wallpaper_Stage1;		//Stage1�̔w�i

extern int wallpaper_Stage2;		//Stage2�̔w�i

extern int wallpaper_Stage3;		//Stage3�̔w�i


extern int CardBase_gpc_hdl;										//�J�[�h�̊�b�p�̉摜

const tnl::Vector3 PLAYER_HAND_FIRST_POS = { 250, 360, 0 };		//�v���C���[�̎�D��1���ڂ̕\���ʒu

const int HAND_SPACE = 200;										//��D�̉摜�̊Ԋu

//�ǎ��p�̒萔
enum {
	WALLPAPER_TITLE,		//�^�C�g���̕ǎ�
	WALLPAPER_STAGE1,		// STAGE1�̕ǎ�
	WALLPAPER_STAGE2,		// STAGE2�̕ǎ�
	WALLPAPER_STAGE3,		// STAGE3�̕ǎ�
	WALLPAPER_STAGE4,		// STAGE4�̕ǎ�
	WALLPAPER_MAX			// �ǎ��̐�
};

extern int wallpaper[WALLPAPER_MAX];		//�w�i�p�̔z��




class Status_CardType {			//�J�[�h�̏�������p��class

public:
	std::string name_ = "piyo";
	int gpc_hdl_ = 0;
	int cardtype_ = 0;
	int handtype_ = 0;

	void init(std::string name, int gpc_hdl, int cardtype);
};

class Status_HandType {
public:
	std::string name_ = "piyo";
	int gpc_hdl_ = 0;
	int handtype_ = 0;

	void init(std::string name, int gpc_hdl, int handtype);

};

extern Status_CardType CardType[CARDTYPE_MAX];		//�J�[�h�̎�ނ�class
extern Status_HandType HandType[HANDTYPE_MAX];		//����(����񂯂�̎�)��class


void GraphLoad_Start();		//�ŏ��Ɉ�x�����ǂݍ��މ摜�֌W

void CardGraphLoad();		//�J�[�h�֌W�̉摜��ǂݍ��ޗp

void CardGraphDraw();		//�J�[�h�֌W�̉摜��\������


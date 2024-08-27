#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "scene_CardDraw.h"
#include "character.h"
#include "cardEffect.h"

extern int Chara_Summon;										//�����_���ŏo�Ă���L�����N�^�[�p�ϐ�

const int CHARA_COUNT_MAX = 4;									//���Ԃ̐��̍ő�l

extern int Chara_Field[CHARA_COUNT_MAX];						//��ɂ���L�����N�^�[�̔ԍ��p�̔z��

extern bool chara_field_flag[/*CHARA_MAX*/];	//��ɏo�Ă���L�����N�^�[���m�F����p��flag


//�J�[�h�̎��
enum {
	CARDTYPE_SUMMON,			//�J�[�h�̎�ށF����
	CARDTYPE_SKILL,				//�J�[�h�̎�ށF�X�L��
	CARDTYPE_ITEM,				//�J�[�h�̎�ށF�A�C�e��
	CARDTYPE_MAX				//�J�[�h�̎�ނ̐�
};


//�J�[�h�̑���
enum {
	HANDTYPE_ROCK,								//�����F�O�[
	HANDTYPE_PAPER,								//�����F�`���L
	HANDTYPE_SCISSORS,							//�����F�p�[
	HANDTYPE_MAX								//�����̐�
};

void cardeffect_InDeck();

void cardeffect_Summon();

void Chara_Field_Draw();


class Status_Card {			//�J�[�h�̎�ނƃ����_���Ɍ��肵������������p��class

public:

	int cardtype_ = CARDTYPE_MAX;						//�R�D�A��D���̃J�[�h�̎�ނ�����p
	int handtype_ = HANDTYPE_MAX;						//�R�D�A��D���̃J�[�h�̑���������p
	//std::string ex_ = "aaa";							//�J�[�h�̎�ނɊւ��������

	void init(int cardtype, int handtype);

};


extern Status_Card CardType_Deck[DECK_VOLUME];			//�R�D�̃J�[�h�̎�ށA����������p
extern Status_Card CardType_Hand[DECK_VOLUME];			//��D�̃J�[�h�̎�ށA����������p



extern int card_gpc_hdl_summon;				//�����̃J�[�h�摜
extern int card_gpc_hdl_skill;				//�X�L���̃J�[�h�摜
extern int card_gpc_hdl_item;				//�A�C�e���̃J�[�h�摜

void skilleffect();

void cardeffect_Skill();


enum {
	ITEM_BUFF,			//�o�t�A�C�e��
	ITEM_HEAL,			//�񕜃A�C�e��
	ITEM_ANALYSIS,		//���̓A�C�e��
	ITEM_MAX			//�A�C�e����
};

class Effect_Item {			//�A�C�e���Ɋւ���class

public:

	std::string name_ = "aaa";							//�J�[�h�̖��O
	int type_ = ITEM_MAX;								//�A�C�e���̎��
	int gpc_hdl_ = 0;									//�A�C�e���̉摜
	int turn_ = 0;										//���ʂ̎����^�[����
	std::string ex_ = "aaa";							//�A�C�e���Ɋւ��������

	void init(std::string name, int type, int gpc_hdl, int turn, std::string ex);

};

void cardeffect_Item();


enum {
	TURNCOUNT_START,		//�^�[���v���̊J�n�n�_
	TURNCOUNT_END,			//�^�[���v���̏I���n�_
	TURNCOUNT_MAX			//�^�[���̌v����
};

class Effect_Item_Buff {									//�o�t�A�C�e���Ɋւ���class

public:

	float atk_ = 1;								//�U���o�t�̔{��
	float damage_ = 1;							//�A�C�e���̉摜
	int turncount[TURNCOUNT_MAX] = { -1 };		//�o�t�̌o�߃^�[���̌v���p

	void init(float atk, float damage);

};

//extern int scene_ItemEffect_Effect = ITEMEFFECT_EFFECT_ONCE;		//���ʂ̏������s���ۂ̃V�[���J�ڗp
//
//const float ItemHeal_value = 0.5f;		//�񕜃A�C�e���̉񕜊���

enum {		
	ITEMBUFF_OFF,		//ItemBuff_flag = false
	ITEMBUFF_ON,		//ItemBuff_flag = true
	ITEMBUFF_MAX		//ItemBuff_flag �̗v�f��
};

extern Effect_Item_Buff Item_Buff[ITEMBUFF_MAX];


extern int ItemBuff_flag_size;		//ItemBuff_flag�̃T�C�Y�p

extern bool ItemBuff_flag;		//�A�C�e���ɂ��o�t�����邩���肷��t���O

extern bool Item_Analysis_flag;		//���̓A�C�e���̌��ʒ������ʂ���t���O

void cardeffect_Item_Off();	//�A�C�e���̏�����؂鏈��

void cardeffect_Item();	//�A�C�e���̏���
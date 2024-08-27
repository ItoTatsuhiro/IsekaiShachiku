#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "character.h"
#include "cardEffect.h"


const int FIELD_CHARA_MAX = 5;							//��ɏo����L�����N�^�[�̍ő吔

extern int Chara_Number_Field[FIELD_CHARA_MAX];			//�L�����N�^�[�̔ԍ�������p�̔z��

extern int Chara_Count_Field;									//��ɂ���L�����N�^�[�̐�



enum {
	CHARA_FIGHTER,			//�i����
	CHARA_KNIGHT,			//�R�m
	CHARA_SAMURAI,			//��
	CHARA_THIEF,			//����
	CHARA_WIZARD,			//���@�g��
	CHARA_YOU,				//��l��
	CHARA_MAX				//�L�����N�^�[�̐�
};

enum {
	ENEMY_YOU,				//�h�b�y���Q���K�[
	ENEMY_DEVIL,			//����
	ENEMY_DRAGON,			//�h���S��
	ENEMY_DEVILKING,		//����
	ENEMY_MAX				//�G�̐�
};


const tnl::Vector3 CHARA_WINDOW_POS = { 100, 600, 0 };				//��l�ڂ̃L�����N�^�[�̕\��
//const tnl::Vector3 CHARA_BACK_BOARD_POS = { 640, 600, 0 };


const tnl::Vector3 ENEMY_POS = { 720, 250, 0 };				//�G�L�����N�^�[�̕\���ʒu

const tnl::Vector3 ENEMY_WINDOW_POS = { ENEMY_POS.x +100, ENEMY_POS.y, 0 };				//�G�L�����N�^�[�p�w�i�摜�̕\���ʒu

//const tnl::Vector3 ENEMY_WINDOW_SIZE = { 450, 300, 0 };		//�G�L�����N�^�[��\������E�B���h�E�̑傫��





class Status_Chara {									//�L�����N�^�[�J�[�h�p��class

public:
	std::string name_ = "piyo";
	int hp_max_ = 100;									//�L�����N�^�[�̗͍̑ő�l
	int hp_ = 0;										//�L�����N�^�[�̗̑�
	int atk_ = 10;										//�L�����N�^�[�̍U����
	int gpc_hdl_ = 0;									//�L�����N�^�[�̉摜

	void init(std::string name, int hp_max, int atk, int gpc_hdl);

	void draw(int card_num);

};

extern Status_Chara Chara[CHARA_MAX];					//�L�����N�^�[�̏ڍחp��class


class Status_Enemy {									//�G�L�����N�^�[�p��class

public:
	std::string name_ = "piyo";							//�G�L�����N�^�[�̖��O
	int hp_max_ = 100;									//�G�L�����N�^�[�̗͍̑ő�l
	int hp_ = 0;										//�G�L�����N�^�[�̗̑�
	int atk_ = 10;										//�G�L�����N�^�[�̍U����
	int gpc_hdl_ = 0;									//�G�L�����N�^�[�̉摜
	std::string ex_ = "piyo";							//�G�L�����N�^�[�̐�����

	void init(std::string name, int hp_max, int atk, int gpc_hdl, std::string ex);

	void draw();

};

extern Status_Enemy Enemy[ENEMY_MAX];					//�G�L�����N�^�[�̏ڍחp��class



class Action_Enemy {									//�G�L�����N�^�[�̍s���p��class

public:
	std::string name_ = "�U��";							//�G�̋Z�̖��O
	int atk_mag_ = 1;									//�G�̍U���͂ɂ�����{��, mag = magnification�̗�
	int gpc_hdl_ = 0;									//�G�̋Z�̃J�[�h�摜
	int handtype_ = 0;						//�G�̋Z�̑���

	void init(std::string name, int atk_mag, int gpc_hdl, int handtype);		

	void draw();										//�J�[�h�̉摜��\������p

	void damage();										//�_���[�W�̏���������p

};

//�G�̍s���̎�ޗp�̒萔
enum {
	ACTION_1_ENEMY,					//�G�̍s��1
	ACTION_MAX_ENEMY				//�G�̍s���̐�
};

extern Action_Enemy action_Enemy[ENEMY_MAX][ACTION_MAX_ENEMY];		//�G�̍s��������p



void sceneCardGame_CharaSet();				//�����L�����N�^�[�̏���ݒ肷��p

void sceneCardGame_EnemySet();				//�G�L�����N�^�[�̏���ݒ肷��p

void sceneCardGame_Action_EnemySet();		//�G�̍s����ݒ肷��p


#pragma once
#include "../dxlib_ext/dxlib_ext.h"

extern int SelectHandNumber_Player;									//�I�����Ă����D�̔ԍ�
extern int SelectHandCard_hdl_Player;								//�I��������D�̉摜

extern bool CardGamePlay;		//�J�[�h�Q�[���𑱍s����t���O

//const tnl::Vector3 PLAYER_HAND_FIRST_POS = { 250, 360, 0 };		//�v���C���[�̎�D��1���ڂ̕\���ʒu
//const tnl::Vector3 CPU_HAND_FIRST_POS = { 300, 150, 0 };		//cpu�̎�D��1���ڂ̕\���ʒu
//const int HAND_SPACE = 100;										//��D�̉摜�̊Ԋu


extern int CardGameScene;



const tnl::Vector3 TEXTWINDOW_POS = { 640, 620, 0 };			//�e�L�X�g�E�B���h�E�̈ʒu
const tnl::Vector3 TEXT_IN_WINDOW_POS = { TEXTWINDOW_POS.x - 500, TEXTWINDOW_POS.y - 50, 0 };		//�e�L�X�g�E�B���h�E���̃e�L�X�g�̈ʒu

extern bool hand_select_frag;									//true�̂Ƃ��J�[�h��I���ł���
extern bool entcardcheck_flag;									//�E�B���h�E���̃e�L�X�g�\���̃t���O

extern bool entcardcheck_flag_Enter;

const tnl::Vector3 USECARD_PLAYER_POS = { 640, 400, 0 };		//�v���C���[�̎g�p����J�[�h�̕\���ʒu
const tnl::Vector3 USECARD_ENEMY_POS = { USECARD_PLAYER_POS.x, USECARD_PLAYER_POS.y - 250, 0 };			//�G�̎g�p����J�[�h�̕\���ʒu




//�m�F�p�̒萔
enum {
	YES,
	NO
};

extern int ActionNumber_Enemy;									//�G�̍s���Ɋ��蓖�ĂĂ���ԍ�

extern bool select_check_flag;									//�m�F��YES��NO��؂�ւ��\�ɂ���p
extern int Select_Check;										//YES��NO�̑I�����Ă����������p
extern int UseCard_gpc_hdl;										//��ɏo���p�̃J�[�h
extern int UseCard_Cardtype;									//��ɏo���J�[�h�̎��
extern int UseCard_Handtype;									//��ɏo���J�[�h�̑���(����񂯂�̎�)

//�J�[�h�Q�[�����̃V�[���؂�ւ��p
enum {

	GAME_START,													//�J�[�h�Q�[�����n�܂����ŏ��Ɉ�x������������V�[��
	GAME_STARTTEXT,												//�J�[�h�Q�[�����n�܂����ŏ��ɊJ�n�̃e�L�X�g��\��������
	GAME_TURNSET,												//���^�[���K�v�ȕϐ������Z�b�g����V�[��
	GAME_DRAW,													//�J�[�h�������V�[��
	GAME_HANDSELECT,											//��D����g�p����J�[�h��I������V�[��
	GAME_R_P_S_BATTLE,											//����񂯂�̑����𔻕ʂ���V�[��
	GAME_CARDEFFECT,											//�J�[�h�̌��ʂ���������V�[��
	GAME_CHARABATTLE,											//�L�����N�^�[���o�g������V�[��
	GAME_END,													//�Q�[�����I��������V�[��
	GAME_SCENEMAX												//�V�[���̐�
};


extern bool BackDark_flag;										//���ɕ\�����Ă���w�i�̕����̋P�x�𗎂Ƃ��������Ǘ�����p�̃t���O

extern int EnemyInStage;										//���݂̃X�e�[�W�̓G

extern bool turnset_flag;

extern int TurnCount;											//�^�[�����J�E���g����p�̕ϐ�


void sceneCardGame_Start();										//�J�[�h�Q�[���J�n���ɓǂݍ��ޓ��e

void TextWindowDraw();											//�e�L�X�g�\���p�̃E�B���h�E��\������


void sceneCardGameMain();										//�J�[�h�Q�[���̏������s���V�[��

void sceneCardGame_EnemyDraw();									//�G�L�����N�^�[��\�����鏈��

void sceneCardGameEnd();										//�J�[�h�Q�[���V�[�����I�������鏈��
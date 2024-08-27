#include "../dxlib_ext/dxlib_ext.h"
#include "character.h"
#include "scene_CardDraw.h"


int Chara_Number_Field[FIELD_CHARA_MAX] = { 0 };	//�L�����N�^�[�̔ԍ�������p�̔z��

int Chara_Count_Field = 0;								//��ɂ���L�����N�^�[�̐�

const int CHARA_GPC_SPACE = 200;						//�L�����N�^�[�̉摜���m�̋���





void Status_Chara::init(std::string name, int hp_max, int atk, int gpc_hdl) {
	name_ = name;
	hp_max_ = hp_max;
	atk_ = atk;
	gpc_hdl_ = gpc_hdl;

	hp_ = hp_max;		//����hp��hp�̍ő�l�̒l�ŏ�����

}



Status_Chara Chara[CHARA_MAX];																	//�L�����N�^�[�̏ڍחp��class



void sceneCardGame_CharaSet() {																	//Start�Ŏ��s����p



	int temp[CHARA_MAX + 1] = { 0 };															//�摜������p�̔z��


	temp[CHARA_YOU] = LoadGraph("graphics/mygame/character/you.png");							//��l���̉摜�̐ݒ�			

	Chara[CHARA_YOU].init("���Ȃ�", 200, 10, temp[CHARA_YOU]);									//��l���̏ڍׂ̐ݒ�
	



	temp[CHARA_FIGHTER] = LoadGraph("graphics/mygame/character/fighter.png");					//�i���Ƃ̉摜�̐ݒ�			

	Chara[CHARA_FIGHTER].init("�i����", 80, 25, temp[CHARA_FIGHTER]);							//�i���Ƃ̏ڍׂ̐ݒ�





	temp[CHARA_KNIGHT] = LoadGraph("graphics/mygame/character/knight.png");						//�R�m�̉摜�̐ݒ�			

	Chara[CHARA_KNIGHT].init("�R�m", 100, 15, temp[CHARA_KNIGHT]);								//�R�m�̏ڍׂ̐ݒ�




	temp[CHARA_SAMURAI] = LoadGraph("graphics/mygame/character/samurai.png");					//���̉摜�̐ݒ�			

	Chara[CHARA_SAMURAI].init("��", 85, 20, temp[CHARA_SAMURAI]);								//���̏ڍׂ̐ݒ�


	

	temp[CHARA_THIEF] = LoadGraph("graphics/mygame/character/thief.png");						//�����̉摜�̐ݒ�			

	Chara[CHARA_THIEF].init("����", 70, 12, temp[CHARA_THIEF]);									//�����̏ڍׂ̐ݒ�




	temp[CHARA_WIZARD] = LoadGraph("graphics/mygame/character/wizard.png");					//���@�g���̉摜�̐ݒ�			

	Chara[CHARA_WIZARD].init("���@�g��", 60, 30, temp[CHARA_WIZARD]);							//���@�g���̏ڍׂ̐ݒ�




}


void Status_Chara::draw(int card_num) {
	
	

	DrawRotaGraph(CHARA_WINDOW_POS.x + (card_num * CHARA_GPC_SPACE), CHARA_WINDOW_POS.y, 0.4f, 0, CharaBack_paper_dpc_hdl, true);				//�L�����N�^�[�̔w�i�̕\��(���莆)

	DrawRotaGraph(CHARA_WINDOW_POS.x + (card_num * CHARA_GPC_SPACE), CHARA_WINDOW_POS.y - 25, 0.25f, 0, gpc_hdl_, true);						//�L�����N�^�[�̉摜��\��

	//hp_ = hp_max_;																															//hp��hp�̍ő�l�̒l������(��)

	SetFontSize(15);

	DrawStringEx(CHARA_WINDOW_POS.x - 25 + (card_num * CHARA_GPC_SPACE), CHARA_WINDOW_POS.y + 40, 0, "%s", name_.c_str());						//�L�����N�^�[�̖��O��\��

	DrawStringEx(CHARA_WINDOW_POS.x - 60 + (card_num * CHARA_GPC_SPACE), CHARA_WINDOW_POS.y + 60, 0, "HP : %d / %d", hp_, hp_max_);				//�L�����N�^�[��HP��\��

	DrawStringEx(CHARA_WINDOW_POS.x - 60 + (card_num * CHARA_GPC_SPACE), CHARA_WINDOW_POS.y + 80, 0, "ATK : %d", atk_);							//�L�����N�^�[�̍U���͂�\��

}
					
//�G�̏ڍחp��class

void Status_Enemy::init(std::string name, int hp_max, int atk, int gpc_hdl, std::string ex) {
	name_ = name;
	hp_max_ = hp_max;
	atk_ = atk;
	gpc_hdl_ = gpc_hdl;
	ex_ = ex;

	hp_ = hp_max_;																						//hp��hp�̍ő�l�̒l������(��)

}

Status_Enemy Enemy[ENEMY_MAX];


void sceneCardGame_EnemySet() {																	//GAME_START�Ŏ��s����p

	int temp[ENEMY_MAX] = { 0 };																//�摜������p�̔z��


	temp[ENEMY_YOU] = LoadGraph("graphics/mygame/Enemy/you.png");							//�h�b�y���Q���K�[�̉摜�̐ݒ�			

	Enemy[ENEMY_YOU].init("�h�b�y���Q���K�[", 200, 20, temp[ENEMY_YOU], "���Ȃ��̓����琶�܂ꂽ���g�̑��݁B\n���Ȃ����В{�ł���Ȃ�΁A�ނ��܂��В{�ł���B");			//�h�b�y���Q���K�[�̏ڍׂ̐ݒ�

	temp[ENEMY_DEVIL] = LoadGraph("graphics/mygame/Enemy/devil.png");						//�����̉摜�̐ݒ�			

	Enemy[ENEMY_DEVIL].init("����", 400, 30, temp[ENEMY_DEVIL], "�����̎艺�̉��������B\n�����Ƃ͂�����ʎВ{�̂��Ȃ��ɂ͂��܂�ɂ�����B");							//�����̏ڍׂ̐ݒ�

	temp[ENEMY_DRAGON] = LoadGraph("graphics/mygame/Enemy/dragon.png");						//�h���S���̉摜�̐ݒ�			

	Enemy[ENEMY_DRAGON].init("�h���S��", 800, 45, temp[ENEMY_DRAGON], "�����R�����̃h���S���B\n��N���������̑̂ɂ́A�В{�̐n�͒ʂ�Ȃ��B");						//�h���S���̏ڍׂ̐ݒ�

	temp[ENEMY_DEVILKING] = LoadGraph("graphics/mygame/Enemy/devil_king.png");				//�����̉摜�̐ݒ�			

	Enemy[ENEMY_DEVILKING].init("����", 1500, 60, temp[ENEMY_DEVILKING], "���a�������������̉��B\n�z�ɂ�����ꂽ���z�̌��܋��𓾂���΁A�E�T�������ł͂Ȃ��B");					//�����̏ڍׂ̐ݒ�

}

void Status_Enemy::draw() {

	//DrawBoxEx(ENEMY_WINDOW_POS, ENEMY_WINDOW_SIZE.x, ENEMY_WINDOW_SIZE.y, true, -1);					//�G�̔w�i�Ɏl�p�`������

	DrawRotaGraph(ENEMY_WINDOW_POS.x, ENEMY_WINDOW_POS.y, 0.85f, 0, EnemyBack_paper_dpc_hdl, true);		//�L�����N�^�[�̔w�i�̕\��(���莆)


	DrawRotaGraph(ENEMY_POS.x, ENEMY_POS.y, 0.5f, 0, gpc_hdl_, true);									//�G�L�����N�^�[�̉摜��\��


	SetFontSize(15);

	DrawStringEx(ENEMY_POS.x + 150, ENEMY_POS.y - 50, 0, "%s", name_.c_str());							//�G�L�����N�^�[�̖��O��\��

	DrawStringEx(ENEMY_POS.x +150, ENEMY_POS.y + 50, 0, "HP : %d / %d", hp_, hp_max_);					//�G�L�����N�^�[��HP��\��

}


void Action_Enemy::init(std::string name, int atk_mag, int gpc_hdl, int handtype) {
	name_ = name;				//�G�̍s���̖��O
	atk_mag_ = atk_mag;			//�U���͂ɂ�����{��
	gpc_hdl_ = gpc_hdl;			//�摜�n���h��
	handtype_ = handtype;		//����

}

Action_Enemy action_Enemy[ENEMY_MAX][ACTION_MAX_ENEMY] = {};



void sceneCardGame_Action_EnemySet() {

	int temp[ACTION_MAX_ENEMY] = { 0 };

	temp[ACTION_1_ENEMY] = LoadGraph("graphics/mygame/Enemy/action/battle.png");
	action_Enemy[ENEMY_YOU][ACTION_1_ENEMY].init("�U��", 1, temp[ACTION_1_ENEMY], HANDTYPE_ROCK);		//ENEMY_YOU�̍s��1�̏��

	action_Enemy[ENEMY_DEVIL][ACTION_1_ENEMY].init("�U��", 1, temp[ACTION_1_ENEMY], HANDTYPE_ROCK);		//ENEMY_DEVIL�̍s��1�̏��

	action_Enemy[ENEMY_DRAGON][ACTION_1_ENEMY].init("�U��", 1, temp[ACTION_1_ENEMY], HANDTYPE_ROCK);		//ENEMY_DRAGON�̍s��1�̏��

	action_Enemy[ENEMY_DEVILKING][ACTION_1_ENEMY].init("�U��", 1, temp[ACTION_1_ENEMY], HANDTYPE_ROCK);		//ENEMY_DEVILKING�̍s��1�̏��

}




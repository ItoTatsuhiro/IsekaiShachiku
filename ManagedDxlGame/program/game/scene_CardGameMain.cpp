#include "../dxlib_ext/dxlib_ext.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "gm_main.h"
#include "scene_CardDraw.h"
#include "scene_Check.h" 
#include "scene_CardGameMain.h"
#include "character.h"
#include "cardEffect.h"
#include "scene_GraphDraw.h"
#include "scene_Menu.h"
#include "Sound.h"


//-----------------------------------------------------------------------------------------------------------------------------------
//extern�ς̕ϐ�

int SelectHandNumber_Player = 0;								//�I�����Ă����D�̔ԍ�
int SelectHandCard_hdl_Player = 0;								//�I��������D�̉摜

int CardGameScene = 0;											//�Q�[�����̃V�[���p�̐؂�ւ��p

bool CardGamePlay = true;		//�J�[�h�Q�[���𑱍s����t���O

bool hand_select_frag = true;									//true�̂Ƃ��J�[�h��I���ł���
bool entcardcheck_flag = false;									//�m�F�p�̃E�B���h�E��\��������p�̃t���O

bool entcardcheck_flag_Enter = false;							//�m�F�̏����ɓ������ۂ�Enter�L�[�Ō��肵�Ȃ��悤�ɂ��邽�߂̃t���O

bool select_check_flag = true;									//�m�F��YES��NO��؂�ւ��\�ɂ���p
int Select_Check = YES;											//YES��NO�̑I�����Ă����������p


int ActionNumber_Enemy = 0;										//�G�̍s���Ɋ��蓖�ĂĂ���ԍ�

bool turnset_flag = true;										// 1�^�[�����ɕK�v�ȕϐ������Z�b�g�������p�̃t���O

int TurnCount = 0;												//�^�[�����J�E���g����p�̕ϐ�


enum {
	RESULT_WIN,			//����񂯂�̌��ʁF����
	RESULT_DRAW,		//����񂯂�̌��ʁF��������
	RESULT_LOSE,		//����񂯂�̌��ʁF�s�k
	RESULT_MAX			//����񂯂�̌��ʐ�
};

class RPS_RESULT {										//����񂯂�̏��s��class

public:
	std::string name_ = "piyo";							//����񂯂�̌��ʂ̖��O
	int type_ = RESULT_WIN;								//���ʂ̏�Ԃ̒l
	float atk_ = 1;										//���ʂɂ��U���͂̕ϓ�
	float damage_ = 1;									//���ʂɂ��󂯂�_���[�W�̕ϓ�

	void init(std::string name, int type, float atk, float damage);

};

void RPS_RESULT::init(std::string name, int type, float atk, float damage) {
	name_ = name;
	type_ = type;
	atk_ = atk;
	damage_ = damage;
}


RPS_RESULT Result[RESULT_MAX];

void ResultInit() {

	Result[RESULT_WIN].init("����", RESULT_WIN, 1.2f, 0.8f);

	Result[RESULT_DRAW].init("��������", RESULT_DRAW, 1.0f, 1.0f);

	Result[RESULT_LOSE].init("�s�k", RESULT_LOSE, 0.8f, 1.2f);

}



int g_result = RESULT_MAX;				//����񂯂�̌���

int EnemyInStage = ENEMY_YOU;			//���݂̃X�e�[�W�̓G

int scene_CardEffect = 0;				//�J�[�h���ʂ̏������s���ۂ�switch�p

int atk_CharaAll = 0;					//�����S�̂̍U���͂̍��v

int scene_CharaBattle = 0;				//�L�����N�^�[���o�g������V�[����switch�p

int target = 0;							//�G�̍U���Ώ�

bool BackDark_flag = false;				//���̉摜���Â�����t���O



//const tnl::Vector3 TEXT_CARDSEL_POS = { 500, 50, 0 };			//�e�L�X�g�E�B���h�E�̈ʒu


void sceneCardGame_TurnSet() {			//���^�[���Z�b�g����p�̕ϐ���

	SelectHandNumber_Player = 0;

	entcardcheck_flag_Enter = false;

	entcardcheck_flag = false;

	hand_select_frag = true;

	//CardGameScene = 0;

	hand_select_frag = true;

	entcardcheck_flag = false;

	entcardcheck_flag_Enter = false;

	select_check_flag = true;

	scene_CardEffect = 0;

	atk_CharaAll = 0;

	scene_CharaBattle = 0;

	target = 0;

	turnset_flag = false;

	
}



void sceneCardGame_Start() {

	CardGameScene = 0;

	DeckCount_Player = DECK_VOLUME;
	HandCount_Player = 0;

	cardeffect_InDeck();

	CardGraphLoad();

	sceneCardGame_CharaSet();

	sceneCardGame_EnemySet();

	Chara_Field[0] = CHARA_YOU;

	Chara_Count_Field = 1;

	sceneCardGame_Action_EnemySet();

	ResultInit();

	turnset_flag = true;

	// bool a = turnset_flag;

	TurnCount = 0;

	//CardGameScene++;

}


void sceneCardGame_FirstDraw() {							//������D��z��
	for (int i = 0; i < HAND_VOLUME - 1; i++) {
		sceneCardGame_CardDraw_Player();
	/*	sceneCardGame_CardDraw_Cpu();*/
	}
	//CardGameScene = GAME_HANDSELECT;
}


void TextWindowDraw() {
	DrawRotaGraph(TEXTWINDOW_POS.x, TEXTWINDOW_POS.y, 1.0f, 0, TextWindow_hdl, true);
	DrawStringEx(TEXT_IN_WINDOW_POS.x + 850, TEXT_IN_WINDOW_POS.y + 100, -1, "Enter�Ŏ��ɐi�݂܂�");
}



void sceneCardGame_SelectCardCheck() {


	SetFontSize(20);
	DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "�I�������J�[�h���o���܂����H"/*\nSelect_Check = %d\nselect_check_flag = %d*//*, Select_Check, select_check_flag*/);
	DrawStringEx(TEXT_IN_WINDOW_POS.x + 500, TEXT_IN_WINDOW_POS.y, -1, "YES\nNO");

	DrawRotaGraph(TEXT_IN_WINDOW_POS.x + 480, TEXT_IN_WINDOW_POS.y + 10 + 20 * Select_Check, 0.5f, M_PI * 3 / 4, Cursor_hdl, true);
	//select_check_flag = true;


	if (select_check_flag) {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			Select_Check++;
			sound_se_sel();
			if (Select_Check > NO) {						//NO�Ł����������Ƃ�YES�ɖ߂�
				Select_Check = YES;
			}
		}

		//�����������Ƃ��ɑI�𒆂̃J�[�h������ɂ��炷
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			Select_Check--;
			sound_se_sel();
			if (Select_Check < YES) {						//YES�Ł����������Ƃ�NO�ɖ߂�
				Select_Check = NO;
			}
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) && entcardcheck_flag_Enter == true) {

			if (Select_Check == YES) {															//YES��Enter���������Ƃ��Ɉȉ��̏������s��

				for (int j = 0; j < HAND_VOLUME; j++) {											//��D�̑I�������J�[�h�̈ʒu�����̃J�[�h��O�ɂ��炷���ƂőI�������J�[�h���R�D�������
					if (j >= SelectHandNumber_Player) {
						HandCard_hdl_Player[j] = HandCard_hdl_Player[j + 1];
					}
				}
				sound_se_enter();
				sound_se_cardput();

				HandCount_Player--;						

				entcardcheck_flag = false;														//�m�F�̕\��������
				select_check_flag = false;

				CardGameScene++;																//�V�[�������ɐi�߂�


			}
			else {

				sound_se_cardpass();
				entcardcheck_flag = false;														//�I���̉�ʂɖ߂�
				hand_select_frag = true;
			}

		}

		else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE) && entcardcheck_flag_Enter == true) {
			sound_se_cardpass();
			entcardcheck_flag = false;
			hand_select_frag = true;
		}
	}
																								//��D�̃J�[�h��I�������ۂ�Enter�Ŋm�F�̏������������Ȃ��悤�ɂ��邽�߂̏���
	if (entcardcheck_flag_Enter) {																//�m�F�p�̃t���O��true�̂Ƃ�(2���[�v��)
		entcardcheck_flag_Enter = false;														//�t���O��false�ɂ���
	}

	else {																						//�m�F�p�̃t���O��false�̂Ƃ�(1���[�v��)
		entcardcheck_flag_Enter = true;															//�t���O��true�ɂ���
	}


}



void ActionSelect_Enemy() {		//�G�̍s�������肷��

	ActionNumber_Enemy = rand() % ACTION_MAX_ENEMY;				//�G�̍s�������肷��

	action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_ = ( rand() % HANDTYPE_MAX );			//�G�̍s���̑��������肷��

}



void sceneCardGame_HandSelect() {

	BackDark_flag = true;

	SetDrawBright(255, 255, 255);		// �ȉ��̓��e��ʏ�̋P�x�ŕ\������



	if (entcardcheck_flag == false) {
		TextWindowDraw();

		SetFontSize(20);

		DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "�J�[�h��I�����Ă�������");

		SetFontSize(18);

		if (CardType_Hand[SelectHandNumber_Player].cardtype_ == CARDTYPE_SUMMON) {
			DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y + 40, -1, "�J�[�h�F����...\n  ��������������J�[�h�ł��B�^�[�����ɔ������鑍�U���̃_���[�W���オ��܂��B");
		}
		else if (CardType_Hand[SelectHandNumber_Player].cardtype_ == CARDTYPE_SKILL) {
			DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y + 40, -1, "�J�[�h�F�X�L��...\n  �����_���őI�΂ꂽ�A�_���[�W�̔�������X�L�����g�p���܂��B\n  �X�L���ɂ���ė^����_���[�W�ʂ��ς��܂��B");
		}
		if (CardType_Hand[SelectHandNumber_Player].cardtype_ == CARDTYPE_ITEM) {
			DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y + 40, -1, "�J�[�h�F�A�C�e��...\n  �o�g����⏕����A�C�e����I�����Ďg�p���܂��B");
		}

		
	}

	//�I�𒆂̃J�[�h�̏�ɃJ�[�\����\������

	DrawRotaGraphF(PLAYER_HAND_FIRST_POS.x + SelectHandNumber_Player * HAND_SPACE, PLAYER_HAND_FIRST_POS.y - 150, 1.0f, M_PI * 5 / 4, Cursor_hdl, true);


	if (hand_select_frag) {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) {
			SelectHandNumber_Player++;
			sound_se_sel();
			if (SelectHandNumber_Player > HandCount_Player - 1) {		//�I�����Ă���J�[�h����D�̖����𒴂����Ƃ�0�ɂ��ǂ�
				SelectHandNumber_Player = 0;
			}
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
			SelectHandNumber_Player--;
			sound_se_sel();
			if (SelectHandNumber_Player < 0) {					//�I�����Ă���J�[�h��0����������Ƃ���D�����̒l�ɂ��ǂ�
				SelectHandNumber_Player = HandCount_Player - 1;
			}
		}


		//ENTER���������Ƃ��ɑI�𒆂̎�D�̃J�[�h�����肷��
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

			sound_se_cardput();

			entcardcheck_flag = true;		//�m�F�p�̃e�L�X�g��\������
			hand_select_frag = false;		//�J�[�h�I��p�̃J�[�\���𓮂��Ȃ��悤�ɂ���

			entcardcheck_flag_Enter = false;

		}

	}

	if (entcardcheck_flag) {
		TextWindowDraw();
		sceneCardGame_SelectCardCheck();
	}
}



void sceneCardGame_R_P_S_Battle() {

	//BackDark_flag = true;				//�w�i���Â�����



	SetDrawBright(255, 255, 255);		// �ȉ��̓��e��ʏ�̋P�x�ŕ\������


	DrawRotaGraph(USECARD_PLAYER_POS.x, USECARD_PLAYER_POS.y, 0.4f, 0, CardBase_gpc_hdl, true);				//�J�[�h�̃x�[�X�̉摜��\������


	DrawRotaGraph(USECARD_PLAYER_POS.x, USECARD_PLAYER_POS.y, 0.3f, 0, CardType[CardType_Hand[SelectHandNumber_Player].cardtype_].gpc_hdl_, true);		//�I�������J�[�h�̉摜��\��������

	DrawRotaGraph(USECARD_PLAYER_POS.x + 55, USECARD_PLAYER_POS.y - 70, 0.15f, 0, HandType[CardType_Hand[SelectHandNumber_Player].handtype_].gpc_hdl_, true);		//�I�������J�[�h�̑�����\��������

	//DrawStringEx(100, 300, -1, " PLAYERHAND = %d", CardType_Hand[SelectHandNumber_Player].handtype_);		//�m�F�p

	DrawStringEx(USECARD_PLAYER_POS.x - 20, USECARD_PLAYER_POS.y + 60, 0, "%s", CardType[CardType_Hand[SelectHandNumber_Player].cardtype_].name_.c_str());		//�J�[�h�̖��O��\��������


	DrawRotaGraph(USECARD_ENEMY_POS.x, USECARD_ENEMY_POS.y, 0.4f, 0, CardBase_gpc_hdl, true);				//�J�[�h�̃x�[�X�̉摜��\������


	DrawRotaGraph(USECARD_ENEMY_POS.x, USECARD_ENEMY_POS.y, 0.3f, 0, action_Enemy[EnemyInStage][ActionNumber_Enemy].gpc_hdl_, true);		//�G�̃J�[�h�̉摜��\��������

	DrawRotaGraph(USECARD_ENEMY_POS.x + 55, USECARD_ENEMY_POS.y - 70, 0.15f, 0, HandType[action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_].gpc_hdl_, true);		//�G�̍s���̑�����\��������

	//DrawStringEx(100, 350, -1, " ENEMYHAND = %d", action_Enemy[ENEMY_YOU][ActionNumber_Enemy].handtype_);		//�m�F�p

	DrawStringEx(USECARD_ENEMY_POS.x - 20, USECARD_ENEMY_POS.y + 60, 0, "%s", action_Enemy[EnemyInStage][ActionNumber_Enemy].name_.c_str());		//�G�̍s���̖��O��\��������

	TextWindowDraw();





	//����񂯂�̏��s����̏���
	if (CardType_Hand[SelectHandNumber_Player].handtype_ == HANDTYPE_ROCK) {
		if (action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_ == HANDTYPE_ROCK) {
			g_result = RESULT_DRAW;
		}
		if (action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_ == HANDTYPE_PAPER) {
			g_result = RESULT_LOSE;
		}
		if (action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_ == HANDTYPE_SCISSORS) {
			g_result = RESULT_WIN;
		}
	}
	if (CardType_Hand[SelectHandNumber_Player].handtype_ == HANDTYPE_PAPER) {
		if (action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_ == HANDTYPE_PAPER) {
			g_result = RESULT_DRAW;
		}
		if (action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_ == HANDTYPE_SCISSORS) {
			g_result = RESULT_LOSE;
		}
		if (action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_ == HANDTYPE_ROCK) {
			g_result = RESULT_WIN;
		}
	}
	if (CardType_Hand[SelectHandNumber_Player].handtype_ == HANDTYPE_SCISSORS) {
		if (action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_ == HANDTYPE_SCISSORS) {
			g_result = RESULT_DRAW;
		}
		if (action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_ == HANDTYPE_ROCK) {
			g_result = RESULT_LOSE;
		}
		if (action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_ == HANDTYPE_PAPER) {
			g_result = RESULT_WIN;
		}
	}


	SetFontSize(20);
	//���s�ɉ������e�L�X�g�̕\��
	if (g_result == RESULT_WIN) {
		DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "���Ȃ��̏����I\n�����̎m�C���オ�����I");
	}
	else if (g_result == RESULT_DRAW) {
		DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "���������ł�");
	}
	else if (g_result == RESULT_LOSE) {
		DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "���Ȃ��̕���!\n�����̎m�C�����������I");
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

		CardType_Deck[DeckCount_Player] = CardType_Hand[SelectHandNumber_Player];		//�g�p�����J�[�h���R�D�ɖ߂�
		DeckCount_Player++;																//�R�D�����𑝂₷


		BackDark_flag = false;				//�w�i�𖾂邭����
		CardGameScene++;					//�V�[�������ɐi�߂�

	}
}

void sceneCardGame_CardEffect() {

	enum {
		CARDEFFECT_CARDTYPETEXT,		//�J�[�h�̎�ނɉ����ăe�L�X�g��\��
		CARDEFFECT_CARDTYPE_EFFECT,		//�J�[�h�̎�ނɉ����Č��ʂ�����
		CARDEFFECT_MAX
	};

	TextWindowDraw();

	SetFontSize(20);

	switch (scene_CardEffect) {
	case CARDEFFECT_CARDTYPETEXT:

		DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "�J�[�h�F%s�̌��ʔ����I", CardType[CardType_Hand[SelectHandNumber_Player].cardtype_].name_.c_str());		//��������J�[�h��\��

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			scene_CardEffect++;					//�V�[�������ɐi�߂�
		}

		break;

	case CARDEFFECT_CARDTYPE_EFFECT:


		if (CardType_Hand[SelectHandNumber_Player].cardtype_ == CARDTYPE_SUMMON) {
			cardeffect_Summon();
		}
		else if (CardType_Hand[SelectHandNumber_Player].cardtype_ == CARDTYPE_SKILL) {
			cardeffect_Skill();
		}
		else if (CardType_Hand[SelectHandNumber_Player].cardtype_ == CARDTYPE_ITEM) {
			cardeffect_Item();
		}


			
		break;
	}
}

enum {
	DAMAGE_CHARA,		//�L�����N�^�[�̗^����_���[�W
	DAMAGE_ENEMY,		//�G�̗^����_���[�W
	DAMAGE_MAX
};

int damage[DAMAGE_MAX] = {};

void CharaOut() {		//���������ꂽ�Ƃ��̏���

	for (int i = 0; i < Chara_Count_Field; i++) {

		if (Chara[Chara_Field[i]].hp_ < 0) {
			Chara[Chara_Field[i]].hp_ = 0;


			for (int j = 0; j < Chara_Count_Field; j++) {
				if (j >= i) {
					Chara_Field[j] = Chara_Field[j + 1];
				}
			}

			chara_field_flag[Chara_Field[i]] = false;				//���ꂽ�L�����N�^�[��flag��false�ɂ���

			Chara_Count_Field--;

		}

		

		//DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "%s������Ă��܂����I", Chara[Chara_Field[i]].name_.c_str());

	}

}


void sceneCardGame_CharaBattle() {

	

	enum {
		CHARABATTLE_ATTACK_CHARA,
		CHARABATTLE_ATTACKTEXT_CHARA,
		CHARABATTLE_ATTACK_ENEMY,
		CHARABATTLE_ATTACKTEXT_ENEMY
	};


 

	TextWindowDraw();

	SetFontSize(20);

	switch (scene_CharaBattle) {
	case CHARABATTLE_ATTACK_CHARA:

		for (int i = 0; i < Chara_Count_Field; i++) {
			atk_CharaAll += Chara[Chara_Field[i]].atk_;		//��̃L�����N�^�[�S���̍U���͂����v����
		}

		damage[DAMAGE_CHARA] = ( atk_CharaAll * Result[g_result].atk_ * Item_Buff[ItemBuff_flag_size].atk_ );				//�G�ɗ^����_���[�W�����肷��

		Enemy[EnemyInStage].hp_ -= damage[DAMAGE_CHARA];				//�G�Ƀ_���[�W��^����

		scene_CharaBattle++;
		sound_se_sel();
		break;

	case CHARABATTLE_ATTACKTEXT_CHARA:



		target = rand() % Chara_Count_Field;		//�U���Ώۂ̑I��

		DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "�����̑��U���I\n%s��%d�̃_���[�W��^�����I", Enemy[EnemyInStage].name_.c_str(), damage[DAMAGE_CHARA]);		//�X�L���ɑΉ������e�L�X�g��\��

		if (Enemy[EnemyInStage].hp_ <= 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			CardGameScene = GAME_END;
		}

		else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			scene_CharaBattle++;
		}
		break;

	case CHARABATTLE_ATTACK_ENEMY:

		damage[DAMAGE_ENEMY] = Enemy[EnemyInStage].atk_ * action_Enemy[EnemyInStage][ActionNumber_Enemy].atk_mag_ * Result[g_result].damage_ * Item_Buff[ItemBuff_flag_size].damage_;

		Chara[Chara_Field[target]].hp_ -= damage[DAMAGE_ENEMY];		//�Ώۂɍs���̔{���ɉ������_���[�W(����񂯂�̌��ʕ␳����)��^����

		scene_CharaBattle++;
		sound_se_sel();
		break;

	case CHARABATTLE_ATTACKTEXT_ENEMY:

		//�G�̍U���̃e�L�X�g��\��
		DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "%s��%s�I\n%s��%d�̃_���[�W���󂯂��I", Enemy[EnemyInStage].name_.c_str(), action_Enemy[EnemyInStage][ActionNumber_Enemy].name_.c_str(), Chara[Chara_Field[target]].name_.c_str(), damage[DAMAGE_ENEMY]);


		if (Enemy[EnemyInStage].hp_ <= 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			CardGameScene = GAME_END;
		}

		else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			CharaOut();
			sound_se_sel();
			TurnCount++;
			CardGameScene = GAME_TURNSET;
			turnset_flag = true;
		}
		break;
	}
}

enum {
	END_WIN,		//�����G���h
	END_LOSE,		//�s�k�G���h
	END_MAX			//�G���h��
};

int endswitch = END_MAX;		//�����Ɣs�k�̐؂�ւ�
//int Poster_Text_gpc_hdl = 0;	//�����\���̎��̉摜�p

void sceneCardGameEnd() {

	if (endswitch == END_MAX) {

		if (Enemy[EnemyInStage].hp_ <= 0) {			//�G��HP��0�����ɂȂ����Ƃ�
			Enemy[EnemyInStage].hp_ = 0;			//�G��HP��0�ɂ���
			endswitch = END_WIN;						//�������̏������s��
		}
		else if (Chara[CHARA_YOU].hp_ <= 0) {
			Chara[CHARA_YOU].hp_ = 0;				//��l����HP��0�ɂ���
			endswitch = END_LOSE;					//�s�k���̏������s��
		}
	}




	TextWindowDraw();

	const tnl::Vector3 END_TEXT_POS = { 500, 300, 0 };

	DrawRotaGraph(END_TEXT_POS.x + 150, END_TEXT_POS.y + 20, 0.5f, 0, Poster_Text_gpc_hdl, true);		//�e�L�X�g�̔w�i�\��

	SetFontSize(50);
	if (endswitch == END_WIN) {
		DrawStringEx(END_TEXT_POS.x, END_TEXT_POS.y, 0, "Stage Clear�I");		//�������̃e�L�X�g��\��
	}
	else if(endswitch == END_LOSE) {
		DrawStringEx(END_TEXT_POS.x, END_TEXT_POS.y, 0, "Game Over...");			//�s�k���̃e�L�X�g��\��
	}
	SetFontSize(20);
	DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "%s�ɏ��������I\n\n�X�y�[�X�L�[�Ń^�C�g���ɖ߂�܂�", Enemy[EnemyInStage].name_.c_str());

	//if (CardGamePlay = true) {
	//	Enemy[EnemyInStage].hp_ = 0;			//�G��HP��0�ɂ���
	//	CardGamePlay = false;				//�J�[�h�Q�[���̏������s���t���O
	//}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		sound_se_enter();
		scene_GameMain = GAMEMAIN_TITLE;
	}

}


void CardGameStart_Text() {
	const tnl::Vector3 START_TEXT_POS = { 500, 300, 0 };

	DrawRotaGraph(START_TEXT_POS.x + 160, START_TEXT_POS.y + 20, 0.5f, 0, Poster_Text_gpc_hdl, true);		//�e�L�X�g�̔w�i�\��

	SetFontSize(50);
	DrawStringEx(START_TEXT_POS.x, START_TEXT_POS.y, 0, "Battle Start�I");		//�������̃e�L�X�g��\��

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		CardGameScene = GAME_TURNSET;
		sound_se_sel();
	}
}

void CardGame_TurnText() {
	const tnl::Vector3 TURN_TEXT_POS = { 500, 300, 0 };

	DrawRotaGraph(TURN_TEXT_POS.x + 160, TURN_TEXT_POS.y + 20, 0.5f, 0, Poster_Text_gpc_hdl, true);		//�e�L�X�g�̔w�i�\��

	SetFontSize(50);
	DrawStringEx(TURN_TEXT_POS.x + 100, TURN_TEXT_POS.y, 0, "Turn %d", TurnCount + 1);		//�^�[���J�n���̃e�L�X�g��\��


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		sound_se_sel();
		CardGameScene = GAME_DRAW;
	}
}




void sceneCardGameMain() {


	if (BackDark_flag) {
		SetDrawBright(128, 128, 128);// ���̉�ʂ��Â�����
	}

		DrawRotaGraph(640, 360, 1.4f, 0, wallpaper[Select_Enemy + 1], true);		//�w�i��\��������

		Enemy[EnemyInStage].draw();												//�G�L�����N�^�[��\������(��)


		for (int i = 0; i < Chara_Count_Field; i++) {

			Chara[Chara_Field[i]].draw(i);										//��̃L�����N�^�[��\������

		}


		if (CardGamePlay) {

			switch (CardGameScene) {
			case GAME_START:

				sceneCardGame_Start();
				CardGameScene++;;

				break;

			case GAME_STARTTEXT:

				CardGameStart_Text();

				break;
			case GAME_TURNSET:

				if (turnset_flag) {
					ActionSelect_Enemy();			//�G�̍s�������肷��
					cardeffect_Item_Off();
					sceneCardGame_TurnSet();
				}
				if (!turnset_flag) {
					CardGame_TurnText();
				}
				break;
			case GAME_DRAW:

				if (TurnCount == 0) {
					sceneCardGame_FirstDraw();
				}

				sceneCardGame_CardDraw_Player();
				

				CardGameScene++;

				break;

			case GAME_HANDSELECT:

				CardGraphDraw();
				sceneCardGame_HandSelect();


				break;

			case GAME_R_P_S_BATTLE:

				sceneCardGame_R_P_S_Battle();

				break;

			case GAME_CARDEFFECT:

				sceneCardGame_CardEffect();

				break;

			case GAME_CHARABATTLE:

				sceneCardGame_CharaBattle();

				break;

			case GAME_END:

				sceneCardGameEnd();

				break;
			}
		}


//�f�o�b�O�p
// 
	//DrawStringEx(10, 10, 0, "SCENE = %d", CardGameScene);
	//DrawStringEx(10, 50, 0, "Handcount = %d", HandCount_Player);
	//DrawStringEx(10, 90, 0, "DeckCount_Player = %d", DeckCount_Player);
	//DrawStringEx(10, 130, 0, "TurnCount = %d", TurnCount);
	//DrawStringEx(10, 170, 0, "Buff = %d", ItemBuff_flag);



	//DrawStringEx(100, 100, 0, "Chara_Count_Field = %d", Chara_Count_Field);				//Chara_Count_Field�m�F�p

	

	//cpu�̎�D��\��������
	//for (int i = 0; i < HandCount_Cpu; i++) {

	//	DrawRotaGraphF(CPU_HAND_FIRST_POS.x + i * HAND_SPACE, CPU_HAND_FIRST_POS.y, 0.25f, 0, HandCard_Cpu[i], true);
	//}



}

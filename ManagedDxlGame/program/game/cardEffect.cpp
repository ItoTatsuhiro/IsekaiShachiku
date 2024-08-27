#include "../dxlib_ext/dxlib_ext.h"
#include "scene_CardDraw.h"
#include "scene_CardGameMain.h"
#include "character.h"
#include "cardEffect.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "scene_GraphDraw.h"
#include "Sound.h"


int Chara_Summon = 0;									//�����_���ŏo�Ă���L�����N�^�[�p�ϐ�

int Chara_Field[CHARA_COUNT_MAX] = { 0 };				//��ɂ���L�����N�^�[�̔ԍ��p�̔z��


int scene_SkillEffect = 0;			//�X�L���̓��e���X�C�b�`���ŏ�������p

int skill_random = 0;				//�����_���Ɏg�p����X�L�������肷��p

bool chara_field_flag[CHARA_MAX] = { false };	//��ɏo�Ă���L�����N�^�[���m�F����p��flag


void Status_Card::init(int cardtype, int handtype) {
	cardtype_ = cardtype;						//�R�D�A��D���̃J�[�h�̎�ނ�����p
	handtype_ = handtype;						//�R�D�A��D���̃J�[�h�̑���������p
}


Status_Card CardType_Deck[DECK_VOLUME];			//�R�D�̃J�[�h�̎�ށA����������p
Status_Card CardType_Hand[DECK_VOLUME];			//��D�̃J�[�h�̎�ށA����������p

class Status_Skill {			//�X�L���̓��e������p��class

public:

	int atk_ = 0;								//�X�L���̃_���[�W�̔{��
	std::string text_ = "aaa";						//�R�D�A��D���̃J�[�h�̑���������p

	void init(int atk, std::string text);

};

void Status_Skill::init(int atk, std::string text) {

	atk_ = atk;
	text_ = text;

}


enum {
	SKILL_CHAINSAW,
	SKILL_MONEY,
	SKILL_TACKLE,
	SKILL_MAX
};

Status_Skill Skill[SKILL_MAX];

bool cardeffectflag = false;				//�J�[�h�̏������s���������f���邽�߂̃t���O


void cardeffect_InDeck() {											//�J�[�h�̌��ʂ��J�[�h�̖������z��ɓ���鏈��

	for (int i = 0; i < DECK_VOLUME; i++) {

		CardType_Deck[i].init(i % CARDTYPE_MAX, rand() % HANDTYPE_MAX);

	}
}



void cardeffect_Summon() {

	if (Chara_Count_Field < FIELD_CHARA_MAX) {

		if (cardeffectflag == false) {



			Chara_Summon = rand() % (CHARA_MAX - 1);			//�L�����N�^�[(��l���ȊO)�̒����烉���_���Ɉ�̑I��

			if (chara_field_flag[Chara_Summon] == false) {			//��������Ă���L�����N�^�[�ȊO���I�΂ꂽ�Ƃ��ȉ����s��

				Chara_Field[Chara_Count_Field] = Chara_Summon;		//�z��ɑI�΂ꂽ�L�����N�^�[�̔ԍ�������

				chara_field_flag[Chara_Summon] = true;				//���������L�����N�^�[��flag��true�ɂ���

				Chara_Count_Field++;								//��ɂ���L�����N�^�[�̐������Z����

				cardeffectflag = true;								//�J�[�h�̏������s�����̂�true�ɂ���
			}
		}
		if (cardeffectflag == true) {								//�J�[�h�̏������s��ꂽ���ƂɃe�L�X�g�̕\������ю��̃V�[���ւ̑J�ڂ��s��

			DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "\n%s���������ꂽ�I", Chara[Chara_Summon].name_.c_str());

			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				cardeffectflag = false;
				CardGameScene++;
			}
		}
	}
	else if (Chara_Count_Field == FIELD_CHARA_MAX) {

		for (int i = 0; i < Chara_Count_Field; i++) {
			Chara[Chara_Field[i]].hp_ += (Chara[Chara_Field[i]].hp_max_ * 0.3f);		//�����̗̑͂��񕜂���

			if (Chara[Chara_Field[i]].hp_ > Chara[Chara_Field[i]].hp_max_) {
				Chara[Chara_Field[i]].hp_ = Chara[Chara_Field[i]].hp_max_;						//�̗͂̍ő�l�𒴂����Ƃ��ő�l�ɂ���
			}
		}

		DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "�ꂪ�����ς��Œǉ��ŏ����ł��Ȃ������I\n�]�����͂Ŗ������񕜂����I");
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			cardeffectflag = false;
			CardGameScene++;
		}
	}
	

	//if (cardeffectflag == true) {								//�J�[�h�̏������s��ꂽ���ƂɃe�L�X�g�̕\������ю��̃V�[���ւ̑J�ڂ��s��

	//	DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "\n%s���������ꂽ�I", Chara[Chara_Summon].name_.c_str());

	//	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
	//		cardeffectflag = false;
	//		CardGameScene++;
	//	}
	//}
}

void Chara_Field_Draw() {								

	for (int i = 0; i < Chara_Count_Field; i++) {

		Chara[Chara_Field[i]].draw(i);					//��ɂ���L�����N�^�[��\������

	}

}

void skilleffect() {

	Skill[SKILL_CHAINSAW].init(15, "���Ȃ��̓`�F�[���\�[�œG��؂�t�����I");

	Skill[SKILL_MONEY].init(8, "���Ȃ��͌��œG���͂������I");

	Skill[SKILL_TACKLE].init(12, "���Ȃ��͓G�ɑ̓����肵���I");
}


void cardeffect_Skill() {



	enum {
		SKILLEFFECT_LOAD,
		SKILLEFFECT_TEXT_EFFECT,
		SKILLEFFECT_DAMAGE,
		SKILLEFFECT_DAMAGETEXT,
		SKILLEFFECT_MAX
	};


	if (cardeffectflag == false) {


		switch (scene_SkillEffect) {
		case SKILLEFFECT_LOAD:

			skill_random = rand() % SKILL_MAX;		//�����_���Ɏg�p����X�L�������肷��

			skilleffect();


			scene_SkillEffect++;

			break;

		case SKILLEFFECT_TEXT_EFFECT:

			if (skill_random == SKILL_CHAINSAW) {
				DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, Skill[SKILL_CHAINSAW].text_.c_str());		//�X�L���ɑΉ������e�L�X�g��\��
			}
			else if (skill_random == SKILL_MONEY) {
				DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, Skill[SKILL_MONEY].text_.c_str());			//�X�L���ɑΉ������e�L�X�g��\��
			}
			else if (skill_random == SKILL_TACKLE) {
				DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, Skill[SKILL_TACKLE].text_.c_str());		//�X�L���ɑΉ������e�L�X�g��\��
			}

			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

				scene_SkillEffect++;
			}
			break;

		case SKILLEFFECT_DAMAGE:


			Enemy[EnemyInStage].hp_ -= Chara[CHARA_YOU].atk_ * Skill[skill_random].atk_;										//�G�Ƀ_���[�W��^����

			scene_SkillEffect++;

			break;


		case SKILLEFFECT_DAMAGETEXT:

			DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "%s��%d�̃_���[�W��^�����I", Enemy[EnemyInStage].name_.c_str(), Chara[CHARA_YOU].atk_* Skill[skill_random].atk_);		//�^�����_���[�W��\��


			if (Enemy[EnemyInStage].hp_ <= 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				CardGameScene = GAME_END;
			}

			//	���̃V�[���ֈڂ�
			else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				
				cardeffectflag = false;
				scene_SkillEffect = SKILLEFFECT_LOAD;
				CardGameScene++;
			}
			break;
		}
	}
}


//class Effect_Item {			//�A�C�e���Ɋւ���class
//
//public:
//
//	std::string name_ = "aaa";							//�J�[�h�̖��O
//	int type_ = ITEM_MAX;								//�A�C�e���̎��
//	int gpc_hdl_ = 0;									//�A�C�e���̉摜
//	std::string ex_ = "aaa";							//�A�C�e���Ɋւ��������
//
//	void init(std::string name, int type, int gpc_hdl, std::string ex);
//
//};


void Effect_Item::init(std::string name, int type, int gpc_hdl, int turn, std::string ex) {
	name_ = name;						//�A�C�e����
	type_ = type;						//�A�C�e���̎��
	gpc_hdl_ = gpc_hdl;					//�A�C�e���̉摜�n���h��
	turn_ = turn;						//���ʂ̎����^�[��
	ex_ = ex;							//�A�C�e���̐�����
}

Effect_Item Item[ITEM_MAX];



//enum {
//	ITEM_BUFF,			//�o�t�A�C�e��
//	ITEM_HEAL,			//�񕜃A�C�e��
//	ITEM_ANALYSIS,		//���̓A�C�e��
//	ITEM_MAX			//�A�C�e����
//};


int scene_ItemEffect = 0;		//�A�C�e���̌��ʂ̃V�[���Ǘ��p

const tnl::Vector3 ITEMSEL_GPC_POS = { 400, 360, 0 };		//�A�C�e���̉摜�I���ʒu

enum {
	ITEMEFFECT_INIT,
	ITEMEFFECT_SELECT,
	ITEMEFFECT_EFFECT

};

int Sel_Item = ITEM_BUFF;		//�I�����Ă���A�C�e��
bool Sel_Item_flag = true;		//�A�C�e����I���ł���悤�ɂȂ�t���O




void Effect_Item_Buff::init(float atk, float damage) {
	atk_ = atk;
	damage_ = damage;
}


//enum {
//	ITEMBUFF_OFF,		//ItemBuff_flag = false
//	ITEMBUFF_ON,		//ItemBuff_flag = true
//	ITEMBUFF_MAX		//ItemBuff_flag �̗v�f��
//};

bool ItemBuff_flag = false;		//�A�C�e���ɂ��o�t�����邩���肷��t���O

int ItemBuff_flag_size = ITEMBUFF_OFF;		//ItemBuff_flag�̃T�C�Y�p

//���ʂ̏������s���ۂ̃V�[���J�ڗp
enum {
	ITEMEFFECT_EFFECT_ONCE,		//��x�̂ݏ���������ʂ̏��������s���V�[��
	ITEMEFFECT_EFFECT_TEXT		//���ʂ̃e�L�X�g���\������V�[��
};

int scene_ItemEffect_Effect = ITEMEFFECT_EFFECT_ONCE;		//���ʂ̏������s���ۂ̃V�[���J�ڗp

const float ItemHeal_value = 0.5f;		//�񕜃A�C�e���̉񕜊���

Effect_Item_Buff Item_Buff[ITEMBUFF_MAX];


int Item_Analysis_turn = 3;		// ���̓A�C�e���̌��ʃ^�[��
int Item_Analysis_turn_start = 0;		// ���̓A�C�e���̊J�n�^�[��
bool Item_Analysis_flag = false;		//���̓A�C�e���̌��ʒ������ʂ���t���O


void ItemInit() {
	int temp[ITEM_MAX] = { 0 };

	temp[ITEM_BUFF] = LoadGraph("graphics/mygame/item/buff.png");
	Item[ITEM_BUFF].init("�M�^�[(����)", ITEM_BUFF, temp[ITEM_BUFF], 3, "�A�C�e���F�M�^�[...\n �M�^�[�����t���Ė������ە����܂��B\n (�^����_���[�W�Ǝ󂯂�_���[�W�����^�[���������܂��B)");

	temp[ITEM_HEAL] = LoadGraph("graphics/mygame/item/heal.png");
	Item[ITEM_HEAL].init("�L(��)", ITEM_HEAL, temp[ITEM_HEAL], 1, "�A�C�e���F�L...\n �L�ɖ�����܂��B\n (�����S�̗̂̑͂���芄���������܂��B)");

	temp[ITEM_ANALYSIS] = LoadGraph("graphics/mygame/item/analysis.png");
	Item[ITEM_ANALYSIS].init("PC(����)", ITEM_ANALYSIS, temp[ITEM_ANALYSIS], 3, "�A�C�e���FPC...\n �G�𕪐͂��܂��B\n (�G�̍U���̑���(����񂯂�̎�)�����^�[���\������܂��B)");

	Item_Buff[ITEMBUFF_OFF].init(1.0f, 1.0f);		//�o�t�Ȃ��̔{��
	Item_Buff[ITEMBUFF_ON].init(1.2f, 0.8f);		//�o�t����̔{��

}


void cardeffect_Item_Off() {

	if (TurnCount - Item_Buff[ITEMBUFF_ON].turncount[TURNCOUNT_START] == Item[ITEM_BUFF].turn_ && ItemBuff_flag == true) {
		ItemBuff_flag = false;

		ItemBuff_flag_size = ITEMBUFF_OFF;

		Item_Buff[ITEMBUFF_OFF].turncount[TURNCOUNT_END] = TurnCount;
	}

	if (TurnCount - Item_Analysis_turn_start > Item_Analysis_turn && Item_Analysis_flag == true) {
		Item_Analysis_flag = false;
	}

}



void cardeffect_Item() {

	BackDark_flag = true;
	TextWindowDraw();

	SetDrawBright(255, 255, 255);

	switch (scene_ItemEffect) {
	case ITEMEFFECT_INIT:
		sound_se_cardpass();
		ItemInit();
		Sel_Item_flag = true;
		scene_ItemEffect++;

		break;

	case ITEMEFFECT_SELECT:

		if (Sel_Item_flag) {

			//�E�L�[���������Ƃ���Sel_Item������₷
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) {
				Sel_Item++;
				sound_se_sel();
				if (Sel_Item == ITEM_MAX) {						//Item�̐��ȏ�ɂȂ����Ƃ������l�ɖ߂�
					Sel_Item = ITEM_BUFF;
				}
			}

			//���L�[���������Ƃ���Sel_Item������炷
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
				Sel_Item--;
				sound_se_sel();
				if (Sel_Item < ITEM_BUFF) {						//Item�̏����l����������Ƃ��ɍő�l��Item�ɂ���
					Sel_Item = ITEM_ANALYSIS;
				}
			}





			DrawRotaGraph(ITEMSEL_GPC_POS.x + 200 * Sel_Item, ITEMSEL_GPC_POS.y - 150, 0.8f, M_PI * 5 / 4, Cursor_hdl, true);		//�I��p�̃J�[�\����\������

			SetFontSize(20);

			DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y , -1, Item[Sel_Item].ex_.c_str());						//�A�C�e���J�[�h�̐�����\������

			for (int i = 0; i < ITEM_MAX; i++) {

				DrawRotaGraphF(ITEMSEL_GPC_POS.x + i * HAND_SPACE, ITEMSEL_GPC_POS.y, 0.4f, 0, CardBase_gpc_hdl, true);				//�A�C�e���̃J�[�h�̔w�i��\��������

				DrawRotaGraphF(ITEMSEL_GPC_POS.x + i * HAND_SPACE, ITEMSEL_GPC_POS.y, 0.5f, 0, Item[i].gpc_hdl_, true);				//�A�C�e���̃J�[�h�̉摜��\��������

				SetFontSize(15);

				DrawStringEx(ITEMSEL_GPC_POS.x - 35 + i * HAND_SPACE, ITEMSEL_GPC_POS.y + 60, 0, "%s", Item[i].name_.c_str());		//�J�[�h�̖��O��\��������
			}

			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				sound_se_enter();
				Sel_Item_flag = false;
				scene_ItemEffect++;
			}
		}
		break;

	case ITEMEFFECT_EFFECT:

		switch (scene_ItemEffect_Effect) {
		case ITEMEFFECT_EFFECT_ONCE:
			if (Sel_Item == ITEM_BUFF) {
				if (ItemBuff_flag == false) {
					ItemBuff_flag = true;

					if (Item_Buff[ITEMBUFF_ON].turncount[TURNCOUNT_START] != TurnCount) {
						ItemBuff_flag_size = ITEMBUFF_ON;

						Item_Buff[ITEMBUFF_ON].turncount[TURNCOUNT_START] = TurnCount;
					}
				}
			}
			else if (Sel_Item == ITEM_HEAL) {

				for (int i = 0; i < Chara_Count_Field; i++) {
					Chara[Chara_Field[i]].hp_ += (Chara[Chara_Field[i]].hp_max_ * ItemHeal_value);		//�����̗̑͂��񕜂���

					if (Chara[Chara_Field[i]].hp_ > Chara[Chara_Field[i]].hp_max_) {
						Chara[Chara_Field[i]].hp_ = Chara[Chara_Field[i]].hp_max_;						//�̗͂̍ő�l�𒴂����Ƃ��ő�l�ɂ���
					}
				}
			}
			else if (Sel_Item == ITEM_ANALYSIS) {

				Item_Analysis_flag = true;
				Item_Analysis_turn_start = TurnCount;

			}

			scene_ItemEffect_Effect++;

			break;

		case ITEMEFFECT_EFFECT_TEXT:

			if (Sel_Item == ITEM_BUFF) {
				DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "�J�[�h�F�M�^�[�̌��ʁI\n �M�^�[�̉��t�Ŗ����̎m�C���オ�����I");		//�J�[�h�̌��ʂ�\��������
			}
			if (Sel_Item == ITEM_HEAL) {
				DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "�J�[�h�F�L�̌��ʁI\n �L�ɖ�����Ė����̗̑͂��񕜂����I");		//�J�[�h�̌��ʂ�\��������
			}
			if (Sel_Item == ITEM_ANALYSIS) {
				DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "�J�[�h�FPC�̌��ʁI\n �G�𕪐͂��đ���̍s����\�������I");		//�J�[�h�̌��ʂ�\��������
			}


			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				BackDark_flag = false;
				scene_ItemEffect = ITEMEFFECT_INIT;
				scene_ItemEffect_Effect = ITEMEFFECT_EFFECT_ONCE;
				CardGameScene++;
			}
		}


		//if (Sel_Item == ITEM_BUFF) {

		//	if (ItemBuff_flag == false) {
		//		ItemBuff_flag = true;

		//		if (Item_Buff[ITEMBUFF_ON].turncount[TURNCOUNT_START] != TurnCount) {
		//			ItemBuff_flag_size = ITEMBUFF_ON;

		//			Item_Buff[ITEMBUFF_ON].turncount[TURNCOUNT_START] = TurnCount;
		//		}
		//	}

		//	DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "�J�[�h�F�M�^�[�̌��ʁI\n �M�^�[�̉��t�Ŗ����̎m�C���オ�����I");		//�J�[�h�̌��ʂ�\��������

		//		Sel_Item_flag = false;
		//		CardGameScene++;
		//	}if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		//	

		//}
		/*else if (Sel_Item == ITEM_HEAL) {

			;




		}*/

	}

}
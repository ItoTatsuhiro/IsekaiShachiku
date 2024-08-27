#include "../dxlib_ext/dxlib_ext.h"
#include "scene_CardDraw.h"
#include "scene_GraphDraw.h"
#include "cardEffect.h"
#include "character.h"
#include "scene_CardGameMain.h"


int Cursor_hdl = 0;													//�J�[�h���I�𒆂̕\���p

int TextWindow_hdl = 0;												//�e�L�X�g�E�B���h�E�̕\���p

int CardBase_gpc_hdl = 0;											//�J�[�h�̊�b�p�̉摜

int CardType_gpc_hdl[CARDTYPE_MAX] = {0};							//�J�[�h�̎�ޖ��̉摜�p�̔z��

int Poster_Text_gpc_hdl = 0;			//�����\���̎��̉摜�p

int target_gpc_hdl = 0;					//�^�[�Q�b�g�̉摜

//enum {
//	WALLPAPER_TITLE,		//�^�C�g���̕ǎ�
//	WALLPAPER_STAGE1,		// STAGE1�̕ǎ�
//	WALLPAPER_STAGE2,		// STAGE2�̕ǎ�
//	WALLPAPER_STAGE3,		// STAGE3�̕ǎ�
//	WALLPAPER_STAGE4,		// STAGE4�̕ǎ�
//	WALLPAPER_MAX			// �ǎ��̐�
//};

int wallpaper[WALLPAPER_MAX] = { 0 };		//�w�i�p�̔z��




void Status_CardType::init(std::string name, int gpc_hdl, int cardtype) {
	name_ = name;				//�J�[�h�̎�ނ̖��O
	gpc_hdl_ = gpc_hdl;			//�J�[�h�̎�ނ̉摜
	cardtype_ = cardtype;		//�J�[�h�̎��

}



void Status_HandType::init(std::string name, int gpc_hdl, int handtype) {
	name_ = name;				//�����̖��O
	gpc_hdl_ = gpc_hdl;			//�����̉摜
	handtype_ = handtype;		//�����̐���
}





Status_CardType CardType[CARDTYPE_MAX];		//�J�[�h�̎�ނ�class
Status_HandType HandType[HANDTYPE_MAX];		//����(����񂯂�̎�)��class


void GraphLoad_Start() {			//GameStart��Load����摜�ǂݍ��ݗp


	Cursor_hdl = LoadGraph("graphics/mygame/cursor.png");

	TextWindow_hdl = LoadGraph("graphics/mygame/textwindow.png");

	Poster_Text_gpc_hdl = LoadGraph("graphics/mygame/poster_text.png");							//�����\���̎��̉摜�p

	wallpaper[WALLPAPER_TITLE] = LoadGraph("graphics/mygame/wallpaper/angel.png");		//�^�C�g����ʂ̔w�i

	wallpaper[WALLPAPER_STAGE1] = LoadGraph("graphics/mygame/wallpaper/forest.png");		//Stage1�̔w�i

	wallpaper[WALLPAPER_STAGE2] = LoadGraph("graphics/mygame/wallpaper/otsukimi.png");		//Stage2�̔w�i

	wallpaper[WALLPAPER_STAGE3] = LoadGraph("graphics/mygame/wallpaper/cave.jpg");			//Stage3�̔w�i

	wallpaper[WALLPAPER_STAGE4] = LoadGraph("graphics/mygame/wallpaper/hinode.png");		//Stage4�̔w�i

}


void CardGraphLoad() {				//�J�[�h�֌W�̉摜�ǂݍ��ݗp

//�f�o�b�O�p�[�[�[�[�[�[�[

		CardBase_gpc_hdl = LoadGraph("graphics/mygame/character/poster.png");						//�J�[�h�̃x�[�X�̉摜

		Poster_Text_gpc_hdl = LoadGraph("graphics/mygame/poster_text.png");							//�����\���̎��̉摜�p

		////wallpaper_gpc_hdl_battle = LoadGraph("graphics/mygame/wallpaper.jpg");						//�o�g�����̔w�i

		CharaBack_paper_dpc_hdl = LoadGraph("graphics/mygame/character/poster.png");				//�L�����N�^�[�̔w�i�̉摜

		EnemyBack_paper_dpc_hdl = LoadGraph("graphics/mygame/Enemy/poster_enemy.png");				//�G�̔w�i�̉摜

		target_gpc_hdl = LoadGraph("graphics/mygame/Enemy/target.png");								//���j���[��ʂŕ\��������^�[�Q�b�g


		int temp_cardtype[CARDTYPE_MAX] = { 0 };	//�J�[�h�̉摜���ꎞ�I�ɓ����p�̔z��

		//�J�[�h�̎�ނ̏��
		temp_cardtype[CARDTYPE_SUMMON] = LoadGraph("graphics/mygame/cardgraph/summon.png");		//�J�[�h�F�����̉摜
		CardType[CARDTYPE_SUMMON].init("����", temp_cardtype[CARDTYPE_SUMMON], CARDTYPE_SUMMON);

		temp_cardtype[CARDTYPE_SKILL] = LoadGraph("graphics/mygame/cardgraph/skill.png");		//�J�[�h�F�X�L���̉摜
		CardType[CARDTYPE_SKILL].init("�X�L��", temp_cardtype[CARDTYPE_SKILL], CARDTYPE_SKILL);

		temp_cardtype[CARDTYPE_ITEM] = LoadGraph("graphics/mygame/cardgraph/item.png");			//�J�[�h�F�A�C�e���̉摜
		CardType[CARDTYPE_ITEM].init("�A�C�e��", temp_cardtype[CARDTYPE_ITEM], CARDTYPE_ITEM);

		int temp_handtype[HANDTYPE_MAX] = { 0 };

		temp_handtype[HANDTYPE_ROCK] = LoadGraph("graphics/mygame/handtype/handtype_rock.png");				//�����F�O�[�̉摜
		HandType[HANDTYPE_ROCK].init("�O�[", temp_handtype[HANDTYPE_ROCK], HANDTYPE_ROCK);

		temp_handtype[HANDTYPE_PAPER] = LoadGraph("graphics/mygame/handtype/handtype_paper.png");			//�����F�p�[�̉摜
		HandType[HANDTYPE_PAPER].init("�p�[", temp_handtype[HANDTYPE_PAPER], HANDTYPE_PAPER);

		temp_handtype[HANDTYPE_SCISSORS] = LoadGraph("graphics/mygame/handtype/handtype_scissors.png");		//�����F�`���L�̉摜
		HandType[HANDTYPE_SCISSORS].init("�`���L", temp_handtype[HANDTYPE_SCISSORS], HANDTYPE_SCISSORS);

	//}


	//�R�D�ɃJ�[�h�̎�ނ��ƂɑΉ������摜�����鏈��
	for (int j = 0; j < DeckCount_Player;  j++) {

		int i = j % CARDTYPE_MAX;

		DeckCard_hdl_Player[j] = CardType[i].gpc_hdl_;			
		
		//�摜�̑��ɃJ�[�h�̎�ނ�����p�̔z�������
			
	}



	////�R�D�ɃJ�[�h�̎�ނ��ƂɑΉ������摜�����鏈��
	//for (int j = 0; j++; j < DeckCount_Player) {
	//	for (int i = 0; i++; i < CARDTYPE_MAX) {
	//		if (CardType_Deck[j] = i) {
	//			DeckCard_hdl_Player[j] = CardType[i].gpc_hdl_;
	//		}
	//	}
	//}

}

tnl::Vector3 EnemyHAND_GPC_POS = { PLAYER_HAND_FIRST_POS.x, PLAYER_HAND_FIRST_POS.y - 250, 0};		//�G�̑I���������\������ʒu

void CardGraphDraw() {


		SetDrawBright(255, 255, 255);		// ���̉�ʂ��Â�����

		if (Item_Analysis_flag) {
			DrawRotaGraphF(EnemyHAND_GPC_POS.x, EnemyHAND_GPC_POS.y, 0.4f, 0, CardBase_gpc_hdl, true);				//�G�̎�̔w�i��\��������
			DrawRotaGraph(EnemyHAND_GPC_POS.x, EnemyHAND_GPC_POS.y, 0.25f, 0, HandType[action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_].gpc_hdl_, true);		//��D�̃J�[�h�̑�����\��������

			DrawStringEx(EnemyHAND_GPC_POS.x - 45, EnemyHAND_GPC_POS.y + 60, 0, "�G�̎�F%s", HandType[action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_].name_.c_str());		//�J�[�h�̖��O��\��������
		}

		for (int i = 0; i < HandCount_Player; i++) {
			DrawRotaGraphF(PLAYER_HAND_FIRST_POS.x + i * HAND_SPACE, PLAYER_HAND_FIRST_POS.y, 0.4f, 0, CardBase_gpc_hdl, true);				//��D�̃J�[�h�̔w�i��\��������

			DrawRotaGraphF(PLAYER_HAND_FIRST_POS.x + i * HAND_SPACE, PLAYER_HAND_FIRST_POS.y, 0.3f, 0, CardType[CardType_Hand[i].cardtype_].gpc_hdl_, true);		//��D�̃J�[�h�̉摜��\��������


			DrawRotaGraph(PLAYER_HAND_FIRST_POS.x + 55 + i * HAND_SPACE, PLAYER_HAND_FIRST_POS.y - 70, 0.15f, 0, HandType[CardType_Hand[i].handtype_].gpc_hdl_, true);		//��D�̃J�[�h�̑�����\��������

			DrawStringEx(PLAYER_HAND_FIRST_POS.x - 35 + i * HAND_SPACE, PLAYER_HAND_FIRST_POS.y + 60, 0, "%s", CardType[CardType_Hand[i].cardtype_].name_.c_str());		//�J�[�h�̖��O��\��������

		}

}
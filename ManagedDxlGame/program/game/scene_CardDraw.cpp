#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "scene_CardDraw.h"
#include "cardEffect.h"
#include "scene_GraphDraw.h"
#include "Sound.h"


int DeckCard_hdl_Player[DECK_VOLUME] = { 0 };		//�v���C���[�̎R�D�p�̔z��
int DeckCount_Player = DECK_VOLUME;	 				//�v���[���[�̎R�D�̎c�薇��
int HandCard_hdl_Player[DECK_VOLUME] = { 0 };		//�v���C���[�̎�D�p�̔z��
int HandCount_Player = 0;							//�v���C���[�̎�D����

int handtypenumber[DECK_VOLUME] = { 0 };						//�����_���ł���񂯂�̎�����肷��p�̕ϐ�

int HandCard_Cardtype[DECK_VOLUME] = { 0 };		//�v���C���[�̎�D�̃J�[�h�̎�ނ�ۑ�����z��


//int Deck_hdl_Cpu[DECK_VOLUME];				//cpu�̎R�D�p�̔z��
//int DeckCount_Cpu = DECK_VOLUME;			//cpu�̎R�D�̎c�薇��
//int HandCard_Cpu[DECK_VOLUME] = { 0 };		//cpu�̎�D�p�̔z��
//int HandCount_Cpu = 0;						//cpu�̎�D����

int Deck_hdl[DECK_VOLUME];					//�R�D�p�̔z��(�ꎞ����p)
int DeckCount = DECK_VOLUME;				//�R�D�̎c�薇��(�ꎞ����p)
int HandCard[DECK_VOLUME] = { 0 };			//��D�p�̔z��(�ꎞ����p)
int HandCount = 0;							//��D����(�ꎞ����p)



int wallpaper_gpc_hdl_battle = 0;															//�w�i�̐ݒ�
int CharaBack_paper_dpc_hdl = 0;															//�L�����N�^�[�̔w�i�̐ݒ�(���莆)
int EnemyBack_paper_dpc_hdl = 0;															//�G�L�����N�^�[�̔w�i�̐ݒ�(���莆)





//�J�[�h�̃f�[�^���R�D�ɓ����p�̊֐�
//void sceneCardGraph() {
//
//	DeckCard_hdl_Player[0] = LoadGraph("graphics/mygame/test_card0.png");
//	DeckCard_hdl_Player[1] = LoadGraph("graphics/mygame/test_card1.png");
//	DeckCard_hdl_Player[2] = LoadGraph("graphics/mygame/test_card2.png");
//	DeckCard_hdl_Player[3] = LoadGraph("graphics/mygame/test_card3.png");
//	DeckCard_hdl_Player[4] = LoadGraph("graphics/mygame/test_card4.png");
//	DeckCard_hdl_Player[5] = LoadGraph("graphics/mygame/test_card5.png");
//	DeckCard_hdl_Player[6] = LoadGraph("graphics/mygame/test_card6.png");
//	DeckCard_hdl_Player[7] = LoadGraph("graphics/mygame/test_card7.png");
//	DeckCard_hdl_Player[8] = LoadGraph("graphics/mygame/test_card8.png");
//	DeckCard_hdl_Player[9] = LoadGraph("graphics/mygame/test_card9.png");
//
//	//Deck_hdl_Cpu[0] = LoadGraph("graphics/mygame/test_card0.png");
//	//Deck_hdl_Cpu[1] = LoadGraph("graphics/mygame/test_card1.png");
//	//Deck_hdl_Cpu[2] = LoadGraph("graphics/mygame/test_card2.png");
//	//Deck_hdl_Cpu[3] = LoadGraph("graphics/mygame/test_card3.png");
//	//Deck_hdl_Cpu[4] = LoadGraph("graphics/mygame/test_card4.png");
//	//Deck_hdl_Cpu[5] = LoadGraph("graphics/mygame/test_card5.png");
//	//Deck_hdl_Cpu[6] = LoadGraph("graphics/mygame/test_card6.png");
//	//Deck_hdl_Cpu[7] = LoadGraph("graphics/mygame/test_card7.png");
//	//Deck_hdl_Cpu[8] = LoadGraph("graphics/mygame/test_card8.png");
//	//Deck_hdl_Cpu[9] = LoadGraph("graphics/mygame/test_card9.png");
//
//	wallpaper_gpc_hdl_battle = LoadGraph("graphics/mygame/wallpaper.jpg");
//
//	CharaBack_paper_dpc_hdl = LoadGraph("graphics/mygame/character/poster.png");
//	EnemyBack_paper_dpc_hdl = LoadGraph("graphics/mygame/Enemy/poster_enemy.png");
//
//
//}




void sceneCardGame_CardDraw() {														//�R�D����J�[�h����������


	if (DeckCount > 0) {

		int DrawCardNumber = 0;						//�����_���ň������J�[�h�̔ԍ�

		DrawCardNumber = rand() % DeckCount;										//�v���C���[�̎R�D����J�[�h������

		CardType_Hand[HandCount_Player].init(CardType_Deck[DrawCardNumber].cardtype_, CardType_Deck[DrawCardNumber].handtype_);		



		HandCard[HandCount] = Deck_hdl[DrawCardNumber];

		//�������J�[�h�����ɑ���
		for (int j = 0; j < DECK_VOLUME; j++) {
			if (j >= DrawCardNumber) {
				Deck_hdl[j] = Deck_hdl[j + 1];
				CardType_Deck[j] = CardType_Deck[j + 1];
			}
		}



		//�R�D�̈������J�[�h��0�ɂ���
		for (int i = 0; i < DECK_VOLUME; i++) {
			if (i <= HandCount) {
				Deck_hdl[DECK_VOLUME - (1 + i)] = 0;
			}
		}


		if (DeckCount + HandCount == DECK_VOLUME) {

			DeckCount--;	//�c��R�D���������炷
			HandCount++;	//��D�����𑝂₷

		}
		else {
			HandCount = DECK_VOLUME - DeckCount;

			DeckCount--;	//�c��R�D���������炷
			HandCount++;	//��D�����𑝂₷
		}
	}
}

void sceneCardGame_CardDraw_Player() {

	for (int i = 0; i < DECK_VOLUME; i++) {
		Deck_hdl[i] = DeckCard_hdl_Player[i];		//�v���C���[�̕ϐ�������
		HandCard[i] = HandCard_hdl_Player[i];		//�v���C���[�̕ϐ�������
	}

	DeckCount = DeckCount_Player;
	HandCount = HandCount_Player;

	sceneCardGame_CardDraw();
	sound_se_cardpass();

	for (int i = 0; i < DECK_VOLUME; i++) {
		DeckCard_hdl_Player[i] = Deck_hdl[i];
		HandCard_hdl_Player[i] = HandCard[i];
	}

	DeckCount_Player = DeckCount;				//�v���C���[�̕ϐ��ɕԂ�
	HandCount_Player = HandCount;				//�v���C���[�̕ϐ��ɕԂ�

}

//void sceneCardGame_CardDraw_Cpu() {
//
//	for (int i = 0; i < DECK_VOLUME; i++) {
//		Deck_hdl[i] = Deck_hdl_Cpu[i];
//		HandCard[i] = HandCard_Cpu[i];
//	}
//
//	DeckCount = DeckCount_Cpu;
//	HandCount = HandCount_Cpu;
//
//	sceneCardGame_CardDraw();
//
//	for (int i = 0; i < DECK_VOLUME; i++) {
//		Deck_hdl_Cpu[i] = Deck_hdl[i];
//		HandCard_Cpu[i] = HandCard[i];
//	}
//
//	DeckCount_Cpu = DeckCount;
//	HandCount_Cpu = HandCount;
//
//}




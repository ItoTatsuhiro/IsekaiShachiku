#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "scene_CardDraw.h"
#include "cardEffect.h"
#include "scene_GraphDraw.h"
#include "Sound.h"


int DeckCard_hdl_Player[DECK_VOLUME] = { 0 };		//プレイヤーの山札用の配列
int DeckCount_Player = DECK_VOLUME;	 				//プレーヤーの山札の残り枚数
int HandCard_hdl_Player[DECK_VOLUME] = { 0 };		//プレイヤーの手札用の配列
int HandCount_Player = 0;							//プレイヤーの手札枚数

int handtypenumber[DECK_VOLUME] = { 0 };						//ランダムでじゃんけんの手を決定する用の変数

int HandCard_Cardtype[DECK_VOLUME] = { 0 };		//プレイヤーの手札のカードの種類を保存する配列


//int Deck_hdl_Cpu[DECK_VOLUME];				//cpuの山札用の配列
//int DeckCount_Cpu = DECK_VOLUME;			//cpuの山札の残り枚数
//int HandCard_Cpu[DECK_VOLUME] = { 0 };		//cpuの手札用の配列
//int HandCount_Cpu = 0;						//cpuの手札枚数

int Deck_hdl[DECK_VOLUME];					//山札用の配列(一時代入用)
int DeckCount = DECK_VOLUME;				//山札の残り枚数(一時代入用)
int HandCard[DECK_VOLUME] = { 0 };			//手札用の配列(一時代入用)
int HandCount = 0;							//手札枚数(一時代入用)



int wallpaper_gpc_hdl_battle = 0;															//背景の設定
int CharaBack_paper_dpc_hdl = 0;															//キャラクターの背景の設定(張り紙)
int EnemyBack_paper_dpc_hdl = 0;															//敵キャラクターの背景の設定(張り紙)





//カードのデータを山札に入れる用の関数
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




void sceneCardGame_CardDraw() {														//山札からカードを引く処理


	if (DeckCount > 0) {

		int DrawCardNumber = 0;						//ランダムで引いたカードの番号

		DrawCardNumber = rand() % DeckCount;										//プレイヤーの山札からカードを引く

		CardType_Hand[HandCount_Player].init(CardType_Deck[DrawCardNumber].cardtype_, CardType_Deck[DrawCardNumber].handtype_);		



		HandCard[HandCount] = Deck_hdl[DrawCardNumber];

		//引いたカードを後ろに送る
		for (int j = 0; j < DECK_VOLUME; j++) {
			if (j >= DrawCardNumber) {
				Deck_hdl[j] = Deck_hdl[j + 1];
				CardType_Deck[j] = CardType_Deck[j + 1];
			}
		}



		//山札の引いたカードを0にする
		for (int i = 0; i < DECK_VOLUME; i++) {
			if (i <= HandCount) {
				Deck_hdl[DECK_VOLUME - (1 + i)] = 0;
			}
		}


		if (DeckCount + HandCount == DECK_VOLUME) {

			DeckCount--;	//残り山札枚数を減らす
			HandCount++;	//手札枚数を増やす

		}
		else {
			HandCount = DECK_VOLUME - DeckCount;

			DeckCount--;	//残り山札枚数を減らす
			HandCount++;	//手札枚数を増やす
		}
	}
}

void sceneCardGame_CardDraw_Player() {

	for (int i = 0; i < DECK_VOLUME; i++) {
		Deck_hdl[i] = DeckCard_hdl_Player[i];		//プレイヤーの変数を入れる
		HandCard[i] = HandCard_hdl_Player[i];		//プレイヤーの変数を入れる
	}

	DeckCount = DeckCount_Player;
	HandCount = HandCount_Player;

	sceneCardGame_CardDraw();
	sound_se_cardpass();

	for (int i = 0; i < DECK_VOLUME; i++) {
		DeckCard_hdl_Player[i] = Deck_hdl[i];
		HandCard_hdl_Player[i] = HandCard[i];
	}

	DeckCount_Player = DeckCount;				//プレイヤーの変数に返す
	HandCount_Player = HandCount;				//プレイヤーの変数に返す

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




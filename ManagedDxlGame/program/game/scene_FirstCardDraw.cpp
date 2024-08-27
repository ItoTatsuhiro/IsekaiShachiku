//#include "../dxlib_ext/dxlib_ext.h"
//#include "gm_main.h"
//#include "scene_CardDraw.h"
//
//
//int PlayerDeck_hdl[DECK_VOLUME];			//プレイヤーの山札用の配列
//int PlayerDeckCount = DECK_VOLUME;			//プレーヤーの山札の残り枚数
//int PlayerHandCard[DECK_VOLUME] = { 0 };	//プレイヤーの手札用の配列
//int PlayerHandCount = 0;					//プレイヤーの手札枚数
//
//int CpuDeck_hdl[DECK_VOLUME];				//cpuの山札用の配列
//int CpuDeckCount = DECK_VOLUME;				//cpuの山札の残り枚数
//int CpuHandCard[DECK_VOLUME] = { 0 };		//cpuの手札用の配列
//int CpuHandCount = 0;						//cpuの手札枚数
//
//
//
//
////初回のプレイヤー用手札を重複なく配る用の関数
//void sceneFirstDraw() {
//
//
//
//	//初期手札の枚数分プレイヤーの山札からカードを引く
//	for (int i = 0; i < HAND_VOLUME; i++) {
//
//		int CardNumber = rand() % (PlayerDeckCount);
//		PlayerHandCard[PlayerDeckCount] = PlayerDeck_hdl[CardNumber];
//
//		for (int j = 0; j < DECK_VOLUME; j++) {
//
//			if (j >= CardNumber) {
//
//				PlayerDeck_hdl[j] = PlayerDeck_hdl[j + 1];
//
//			}
//
//		}
//
//		PlayerDeckCount --;	// プレイヤーの残り山札枚数を減らす
//		PlayerHandCount ++;	// プレイヤーの手札枚数を増やす
//
//	}
//
//
//	//プレイヤーの山札の引いたカードをnullにする
//	for (int i = 0; i < HAND_VOLUME; i++) {
//
//		PlayerDeck_hdl[i + (DECK_VOLUME - HAND_VOLUME)] = NULL;
//
//	}
//
//	//初期手札の枚数分cpuの山札からカードを引く
//	for (int i = 0; i < HAND_VOLUME; i++) {
//
//		int CardNumber = rand() % (DECK_VOLUME - i);
//		CpuHandCard[i] = CpuDeck_hdl[CardNumber];
//
//		for (int j = 0; j < DECK_VOLUME; j++) {
//
//			if (j >= CardNumber) {
//
//				CpuDeck_hdl[j] = CpuDeck_hdl[j + 1];
//
//			}
//
//		}
//
//		CpuDeckCount--;	//cpuの残り山札枚数を減らす
//		CpuHandCount++;	//cpuの手札枚数を増やす
//	}
//
//	//cpuの山札の引いたカードをnullにする
//	for (int i = 0; i < HAND_VOLUME; i++) {
//
//		CpuDeck_hdl[i + (DECK_VOLUME - HAND_VOLUME)] = NULL;
//
//	}
//
//}
//
//
//
//

#pragma once

void sceneCardGame_CardDraw();
void sceneCardGame_CardDraw_Player();
void sceneCardGame_CardDraw_Cpu();

const int HAND_VOLUME = 5;						// 初期手札枚数
const int DECK_VOLUME = 10;						// 初期山札枚数

extern int wallpaper_gpc_hdl_battle;			//戦闘中の背景の画像
extern int CharaBack_paper_dpc_hdl;				//キャラクターの背景の張り紙の画像
extern int EnemyBack_paper_dpc_hdl;				//敵キャラクターの背景の設定(張り紙)

//extern int handtypenumber_random[DECK_VOLUME];			//ランダムでじゃんけんの手を決定する用の変数

extern int DrawCardNumber;						//ランダムで引いたカードの番号


extern int DeckCard_hdl_Player[DECK_VOLUME];	//プレイヤーの山札用の画像用の配列
extern int DeckCount_Player;					//プレイヤーの山札の残り枚数
extern int HandCard_hdl_Player[DECK_VOLUME];	//プレイヤーの手札用の配列
extern int HandCount_Player;					//プレイヤーの手札枚数

extern int HandCard_Cardtype[DECK_VOLUME];	//プレイヤーの手札のカードが山札の何番目に保管されていたかを保存する配列


//extern int Deck_hdl_Cpu[DECK_VOLUME];			//cpuの山札用の配列
//extern int DeckCount_Cpu;						//cpuの山札の残り枚数
//extern int HandCard_Cpu[DECK_VOLUME];			//cpuの手札用の配列
//extern int HandCount_Cpu;						//cpuの手札枚数

extern int Deck_hdl[DECK_VOLUME];				//山札用の配列(一時代入用)
extern int DeckCount;							//山札の残り枚数(一時代入用)
extern int HandCard[DECK_VOLUME];				//手札用の配列(一時代入用)
extern int HandCount;							//手札枚数(一時代入用)

void sceneCardGraph();

void sceneFirstDraw();

void CardWrite();


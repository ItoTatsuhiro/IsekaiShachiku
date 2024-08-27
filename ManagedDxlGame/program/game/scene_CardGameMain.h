#pragma once
#include "../dxlib_ext/dxlib_ext.h"

extern int SelectHandNumber_Player;									//選択している手札の番号
extern int SelectHandCard_hdl_Player;								//選択した手札の画像

extern bool CardGamePlay;		//カードゲームを続行するフラグ

//const tnl::Vector3 PLAYER_HAND_FIRST_POS = { 250, 360, 0 };		//プレイヤーの手札の1枚目の表示位置
//const tnl::Vector3 CPU_HAND_FIRST_POS = { 300, 150, 0 };		//cpuの手札の1枚目の表示位置
//const int HAND_SPACE = 100;										//手札の画像の間隔


extern int CardGameScene;



const tnl::Vector3 TEXTWINDOW_POS = { 640, 620, 0 };			//テキストウィンドウの位置
const tnl::Vector3 TEXT_IN_WINDOW_POS = { TEXTWINDOW_POS.x - 500, TEXTWINDOW_POS.y - 50, 0 };		//テキストウィンドウ内のテキストの位置

extern bool hand_select_frag;									//trueのときカードを選択できる
extern bool entcardcheck_flag;									//ウィンドウ内のテキスト表示のフラグ

extern bool entcardcheck_flag_Enter;

const tnl::Vector3 USECARD_PLAYER_POS = { 640, 400, 0 };		//プレイヤーの使用するカードの表示位置
const tnl::Vector3 USECARD_ENEMY_POS = { USECARD_PLAYER_POS.x, USECARD_PLAYER_POS.y - 250, 0 };			//敵の使用するカードの表示位置




//確認用の定数
enum {
	YES,
	NO
};

extern int ActionNumber_Enemy;									//敵の行動に割り当てている番号

extern bool select_check_flag;									//確認のYESとNOを切り替え可能にする用
extern int Select_Check;										//YESとNOの選択している方を入れる用
extern int UseCard_gpc_hdl;										//場に出す用のカード
extern int UseCard_Cardtype;									//場に出すカードの種類
extern int UseCard_Handtype;									//場に出すカードの属性(じゃんけんの手)

//カードゲーム内のシーン切り替え用
enum {

	GAME_START,													//カードゲームが始まった最初に一度だけ処理するシーン
	GAME_STARTTEXT,												//カードゲームが始まった最初に開始のテキストを表示させる
	GAME_TURNSET,												//毎ターン必要な変数等をセットするシーン
	GAME_DRAW,													//カードを引くシーン
	GAME_HANDSELECT,											//手札から使用するカードを選択するシーン
	GAME_R_P_S_BATTLE,											//じゃんけんの相性を判別するシーン
	GAME_CARDEFFECT,											//カードの効果を処理するシーン
	GAME_CHARABATTLE,											//キャラクターがバトルするシーン
	GAME_END,													//ゲームを終了させるシーン
	GAME_SCENEMAX												//シーンの数
};


extern bool BackDark_flag;										//後ろに表示している背景の部分の輝度を落とす処理を管理する用のフラグ

extern int EnemyInStage;										//現在のステージの敵

extern bool turnset_flag;

extern int TurnCount;											//ターンをカウントする用の変数


void sceneCardGame_Start();										//カードゲーム開始時に読み込む内容

void TextWindowDraw();											//テキスト表示用のウィンドウを表示する


void sceneCardGameMain();										//カードゲームの処理を行うシーン

void sceneCardGame_EnemyDraw();									//敵キャラクターを表示する処理

void sceneCardGameEnd();										//カードゲームシーンを終了させる処理
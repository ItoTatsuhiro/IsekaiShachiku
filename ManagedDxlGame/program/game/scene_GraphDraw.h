#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "cardEffect.h"


extern int Cursor_hdl;												//カード等選択中の表示用
extern int TextWindow_hdl;											//テキストウィンドウ表示用

extern int Poster_Text_gpc_hdl;										//文字表示用の画像

extern int target_gpc_hdl;					//ターゲットの画像

extern int wallpaper_Title;			//タイトル画面の背景

extern int wallpaper_Stage1;		//Stage1の背景

extern int wallpaper_Stage2;		//Stage2の背景

extern int wallpaper_Stage3;		//Stage3の背景


extern int CardBase_gpc_hdl;										//カードの基礎用の画像

const tnl::Vector3 PLAYER_HAND_FIRST_POS = { 250, 360, 0 };		//プレイヤーの手札の1枚目の表示位置

const int HAND_SPACE = 200;										//手札の画像の間隔

//壁紙用の定数
enum {
	WALLPAPER_TITLE,		//タイトルの壁紙
	WALLPAPER_STAGE1,		// STAGE1の壁紙
	WALLPAPER_STAGE2,		// STAGE2の壁紙
	WALLPAPER_STAGE3,		// STAGE3の壁紙
	WALLPAPER_STAGE4,		// STAGE4の壁紙
	WALLPAPER_MAX			// 壁紙の数
};

extern int wallpaper[WALLPAPER_MAX];		//背景用の配列




class Status_CardType {			//カードの情報を入れる用のclass

public:
	std::string name_ = "piyo";
	int gpc_hdl_ = 0;
	int cardtype_ = 0;
	int handtype_ = 0;

	void init(std::string name, int gpc_hdl, int cardtype);
};

class Status_HandType {
public:
	std::string name_ = "piyo";
	int gpc_hdl_ = 0;
	int handtype_ = 0;

	void init(std::string name, int gpc_hdl, int handtype);

};

extern Status_CardType CardType[CARDTYPE_MAX];		//カードの種類のclass
extern Status_HandType HandType[HANDTYPE_MAX];		//属性(じゃんけんの手)のclass


void GraphLoad_Start();		//最初に一度だけ読み込む画像関係

void CardGraphLoad();		//カード関係の画像を読み込む用

void CardGraphDraw();		//カード関係の画像を表示する


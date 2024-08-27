#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "character.h"
#include "cardEffect.h"


const int FIELD_CHARA_MAX = 5;							//場に出せるキャラクターの最大数

extern int Chara_Number_Field[FIELD_CHARA_MAX];			//キャラクターの番号を入れる用の配列

extern int Chara_Count_Field;									//場にいるキャラクターの数



enum {
	CHARA_FIGHTER,			//格闘家
	CHARA_KNIGHT,			//騎士
	CHARA_SAMURAI,			//侍
	CHARA_THIEF,			//盗賊
	CHARA_WIZARD,			//魔法使い
	CHARA_YOU,				//主人公
	CHARA_MAX				//キャラクターの数
};

enum {
	ENEMY_YOU,				//ドッペルゲンガー
	ENEMY_DEVIL,			//悪魔
	ENEMY_DRAGON,			//ドラゴン
	ENEMY_DEVILKING,		//魔王
	ENEMY_MAX				//敵の数
};


const tnl::Vector3 CHARA_WINDOW_POS = { 100, 600, 0 };				//一人目のキャラクターの表示
//const tnl::Vector3 CHARA_BACK_BOARD_POS = { 640, 600, 0 };


const tnl::Vector3 ENEMY_POS = { 720, 250, 0 };				//敵キャラクターの表示位置

const tnl::Vector3 ENEMY_WINDOW_POS = { ENEMY_POS.x +100, ENEMY_POS.y, 0 };				//敵キャラクター用背景画像の表示位置

//const tnl::Vector3 ENEMY_WINDOW_SIZE = { 450, 300, 0 };		//敵キャラクターを表示するウィンドウの大きさ





class Status_Chara {									//キャラクターカード用のclass

public:
	std::string name_ = "piyo";
	int hp_max_ = 100;									//キャラクターの体力最大値
	int hp_ = 0;										//キャラクターの体力
	int atk_ = 10;										//キャラクターの攻撃力
	int gpc_hdl_ = 0;									//キャラクターの画像

	void init(std::string name, int hp_max, int atk, int gpc_hdl);

	void draw(int card_num);

};

extern Status_Chara Chara[CHARA_MAX];					//キャラクターの詳細用のclass


class Status_Enemy {									//敵キャラクター用のclass

public:
	std::string name_ = "piyo";							//敵キャラクターの名前
	int hp_max_ = 100;									//敵キャラクターの体力最大値
	int hp_ = 0;										//敵キャラクターの体力
	int atk_ = 10;										//敵キャラクターの攻撃力
	int gpc_hdl_ = 0;									//敵キャラクターの画像
	std::string ex_ = "piyo";							//敵キャラクターの説明文

	void init(std::string name, int hp_max, int atk, int gpc_hdl, std::string ex);

	void draw();

};

extern Status_Enemy Enemy[ENEMY_MAX];					//敵キャラクターの詳細用のclass



class Action_Enemy {									//敵キャラクターの行動用のclass

public:
	std::string name_ = "攻撃";							//敵の技の名前
	int atk_mag_ = 1;									//敵の攻撃力にかかる倍率, mag = magnificationの略
	int gpc_hdl_ = 0;									//敵の技のカード画像
	int handtype_ = 0;						//敵の技の属性

	void init(std::string name, int atk_mag, int gpc_hdl, int handtype);		

	void draw();										//カードの画像を表示する用

	void damage();										//ダメージの処理をする用

};

//敵の行動の種類用の定数
enum {
	ACTION_1_ENEMY,					//敵の行動1
	ACTION_MAX_ENEMY				//敵の行動の数
};

extern Action_Enemy action_Enemy[ENEMY_MAX][ACTION_MAX_ENEMY];		//敵の行動を入れる用



void sceneCardGame_CharaSet();				//味方キャラクターの情報を設定する用

void sceneCardGame_EnemySet();				//敵キャラクターの情報を設定する用

void sceneCardGame_Action_EnemySet();		//敵の行動を設定する用


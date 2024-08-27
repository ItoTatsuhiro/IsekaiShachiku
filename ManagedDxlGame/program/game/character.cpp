#include "../dxlib_ext/dxlib_ext.h"
#include "character.h"
#include "scene_CardDraw.h"


int Chara_Number_Field[FIELD_CHARA_MAX] = { 0 };	//キャラクターの番号を入れる用の配列

int Chara_Count_Field = 0;								//場にいるキャラクターの数

const int CHARA_GPC_SPACE = 200;						//キャラクターの画像同士の距離





void Status_Chara::init(std::string name, int hp_max, int atk, int gpc_hdl) {
	name_ = name;
	hp_max_ = hp_max;
	atk_ = atk;
	gpc_hdl_ = gpc_hdl;

	hp_ = hp_max;		//現在hpをhpの最大値の値で初期化

}



Status_Chara Chara[CHARA_MAX];																	//キャラクターの詳細用のclass



void sceneCardGame_CharaSet() {																	//Startで実行する用



	int temp[CHARA_MAX + 1] = { 0 };															//画像を入れる用の配列


	temp[CHARA_YOU] = LoadGraph("graphics/mygame/character/you.png");							//主人公の画像の設定			

	Chara[CHARA_YOU].init("あなた", 200, 10, temp[CHARA_YOU]);									//主人公の詳細の設定
	



	temp[CHARA_FIGHTER] = LoadGraph("graphics/mygame/character/fighter.png");					//格闘家の画像の設定			

	Chara[CHARA_FIGHTER].init("格闘家", 80, 25, temp[CHARA_FIGHTER]);							//格闘家の詳細の設定





	temp[CHARA_KNIGHT] = LoadGraph("graphics/mygame/character/knight.png");						//騎士の画像の設定			

	Chara[CHARA_KNIGHT].init("騎士", 100, 15, temp[CHARA_KNIGHT]);								//騎士の詳細の設定




	temp[CHARA_SAMURAI] = LoadGraph("graphics/mygame/character/samurai.png");					//侍の画像の設定			

	Chara[CHARA_SAMURAI].init("侍", 85, 20, temp[CHARA_SAMURAI]);								//侍の詳細の設定


	

	temp[CHARA_THIEF] = LoadGraph("graphics/mygame/character/thief.png");						//盗賊の画像の設定			

	Chara[CHARA_THIEF].init("盗賊", 70, 12, temp[CHARA_THIEF]);									//盗賊の詳細の設定




	temp[CHARA_WIZARD] = LoadGraph("graphics/mygame/character/wizard.png");					//魔法使いの画像の設定			

	Chara[CHARA_WIZARD].init("魔法使い", 60, 30, temp[CHARA_WIZARD]);							//魔法使いの詳細の設定




}


void Status_Chara::draw(int card_num) {
	
	

	DrawRotaGraph(CHARA_WINDOW_POS.x + (card_num * CHARA_GPC_SPACE), CHARA_WINDOW_POS.y, 0.4f, 0, CharaBack_paper_dpc_hdl, true);				//キャラクターの背景の表示(張り紙)

	DrawRotaGraph(CHARA_WINDOW_POS.x + (card_num * CHARA_GPC_SPACE), CHARA_WINDOW_POS.y - 25, 0.25f, 0, gpc_hdl_, true);						//キャラクターの画像を表示

	//hp_ = hp_max_;																															//hpにhpの最大値の値を入れる(仮)

	SetFontSize(15);

	DrawStringEx(CHARA_WINDOW_POS.x - 25 + (card_num * CHARA_GPC_SPACE), CHARA_WINDOW_POS.y + 40, 0, "%s", name_.c_str());						//キャラクターの名前を表示

	DrawStringEx(CHARA_WINDOW_POS.x - 60 + (card_num * CHARA_GPC_SPACE), CHARA_WINDOW_POS.y + 60, 0, "HP : %d / %d", hp_, hp_max_);				//キャラクターのHPを表示

	DrawStringEx(CHARA_WINDOW_POS.x - 60 + (card_num * CHARA_GPC_SPACE), CHARA_WINDOW_POS.y + 80, 0, "ATK : %d", atk_);							//キャラクターの攻撃力を表示

}
					
//敵の詳細用のclass

void Status_Enemy::init(std::string name, int hp_max, int atk, int gpc_hdl, std::string ex) {
	name_ = name;
	hp_max_ = hp_max;
	atk_ = atk;
	gpc_hdl_ = gpc_hdl;
	ex_ = ex;

	hp_ = hp_max_;																						//hpにhpの最大値の値を入れる(仮)

}

Status_Enemy Enemy[ENEMY_MAX];


void sceneCardGame_EnemySet() {																	//GAME_STARTで実行する用

	int temp[ENEMY_MAX] = { 0 };																//画像を入れる用の配列


	temp[ENEMY_YOU] = LoadGraph("graphics/mygame/Enemy/you.png");							//ドッペルゲンガーの画像の設定			

	Enemy[ENEMY_YOU].init("ドッペルゲンガー", 200, 20, temp[ENEMY_YOU], "あなたの内から生まれた分身の存在。\nあなたが社畜であるならば、彼もまた社畜である。");			//ドッペルゲンガーの詳細の設定

	temp[ENEMY_DEVIL] = LoadGraph("graphics/mygame/Enemy/devil.png");						//悪魔の画像の設定			

	Enemy[ENEMY_DEVIL].init("悪魔", 400, 30, temp[ENEMY_DEVIL], "魔王の手下の下級悪魔。\n下級とはいえ一般社畜のあなたにはあまりにも強大。");							//悪魔の詳細の設定

	temp[ENEMY_DRAGON] = LoadGraph("graphics/mygame/Enemy/dragon.png");						//ドラゴンの画像の設定			

	Enemy[ENEMY_DRAGON].init("ドラゴン", 800, 45, temp[ENEMY_DRAGON], "魔王軍幹部のドラゴン。\n千年生きたその体には、社畜の刃は通らない。");						//ドラゴンの詳細の設定

	temp[ENEMY_DEVILKING] = LoadGraph("graphics/mygame/Enemy/devil_king.png");				//魔王の画像の設定			

	Enemy[ENEMY_DEVILKING].init("魔王", 1500, 60, temp[ENEMY_DEVILKING], "平和を脅かす魔物の王。\n奴にかけられた多額の懸賞金を得られれば、脱サラも夢ではない。");					//魔王の詳細の設定

}

void Status_Enemy::draw() {

	//DrawBoxEx(ENEMY_WINDOW_POS, ENEMY_WINDOW_SIZE.x, ENEMY_WINDOW_SIZE.y, true, -1);					//敵の背景に四角形を書く

	DrawRotaGraph(ENEMY_WINDOW_POS.x, ENEMY_WINDOW_POS.y, 0.85f, 0, EnemyBack_paper_dpc_hdl, true);		//キャラクターの背景の表示(張り紙)


	DrawRotaGraph(ENEMY_POS.x, ENEMY_POS.y, 0.5f, 0, gpc_hdl_, true);									//敵キャラクターの画像を表示


	SetFontSize(15);

	DrawStringEx(ENEMY_POS.x + 150, ENEMY_POS.y - 50, 0, "%s", name_.c_str());							//敵キャラクターの名前を表示

	DrawStringEx(ENEMY_POS.x +150, ENEMY_POS.y + 50, 0, "HP : %d / %d", hp_, hp_max_);					//敵キャラクターのHPを表示

}


void Action_Enemy::init(std::string name, int atk_mag, int gpc_hdl, int handtype) {
	name_ = name;				//敵の行動の名前
	atk_mag_ = atk_mag;			//攻撃力にかかる倍率
	gpc_hdl_ = gpc_hdl;			//画像ハンドル
	handtype_ = handtype;		//属性

}

Action_Enemy action_Enemy[ENEMY_MAX][ACTION_MAX_ENEMY] = {};



void sceneCardGame_Action_EnemySet() {

	int temp[ACTION_MAX_ENEMY] = { 0 };

	temp[ACTION_1_ENEMY] = LoadGraph("graphics/mygame/Enemy/action/battle.png");
	action_Enemy[ENEMY_YOU][ACTION_1_ENEMY].init("攻撃", 1, temp[ACTION_1_ENEMY], HANDTYPE_ROCK);		//ENEMY_YOUの行動1の情報

	action_Enemy[ENEMY_DEVIL][ACTION_1_ENEMY].init("攻撃", 1, temp[ACTION_1_ENEMY], HANDTYPE_ROCK);		//ENEMY_DEVILの行動1の情報

	action_Enemy[ENEMY_DRAGON][ACTION_1_ENEMY].init("攻撃", 1, temp[ACTION_1_ENEMY], HANDTYPE_ROCK);		//ENEMY_DRAGONの行動1の情報

	action_Enemy[ENEMY_DEVILKING][ACTION_1_ENEMY].init("攻撃", 1, temp[ACTION_1_ENEMY], HANDTYPE_ROCK);		//ENEMY_DEVILKINGの行動1の情報

}




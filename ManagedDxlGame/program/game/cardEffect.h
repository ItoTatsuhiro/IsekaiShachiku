#pragma once
#include "../dxlib_ext/dxlib_ext.h"
#include "scene_CardDraw.h"
#include "character.h"
#include "cardEffect.h"

extern int Chara_Summon;										//ランダムで出てくるキャラクター用変数

const int CHARA_COUNT_MAX = 4;									//仲間の数の最大値

extern int Chara_Field[CHARA_COUNT_MAX];						//場にいるキャラクターの番号用の配列

extern bool chara_field_flag[/*CHARA_MAX*/];	//場に出ているキャラクターを確認する用のflag


//カードの種類
enum {
	CARDTYPE_SUMMON,			//カードの種類：召喚
	CARDTYPE_SKILL,				//カードの種類：スキル
	CARDTYPE_ITEM,				//カードの種類：アイテム
	CARDTYPE_MAX				//カードの種類の数
};


//カードの属性
enum {
	HANDTYPE_ROCK,								//属性：グー
	HANDTYPE_PAPER,								//属性：チョキ
	HANDTYPE_SCISSORS,							//属性：パー
	HANDTYPE_MAX								//属性の数
};

void cardeffect_InDeck();

void cardeffect_Summon();

void Chara_Field_Draw();


class Status_Card {			//カードの種類とランダムに決定した属性を入れる用のclass

public:

	int cardtype_ = CARDTYPE_MAX;						//山札、手札等のカードの種類を入れる用
	int handtype_ = HANDTYPE_MAX;						//山札、手札等のカードの属性を入れる用
	//std::string ex_ = "aaa";							//カードの種類に関する説明文

	void init(int cardtype, int handtype);

};


extern Status_Card CardType_Deck[DECK_VOLUME];			//山札のカードの種類、属性を入れる用
extern Status_Card CardType_Hand[DECK_VOLUME];			//手札のカードの種類、属性を入れる用



extern int card_gpc_hdl_summon;				//召喚のカード画像
extern int card_gpc_hdl_skill;				//スキルのカード画像
extern int card_gpc_hdl_item;				//アイテムのカード画像

void skilleffect();

void cardeffect_Skill();


enum {
	ITEM_BUFF,			//バフアイテム
	ITEM_HEAL,			//回復アイテム
	ITEM_ANALYSIS,		//分析アイテム
	ITEM_MAX			//アイテム数
};

class Effect_Item {			//アイテムに関するclass

public:

	std::string name_ = "aaa";							//カードの名前
	int type_ = ITEM_MAX;								//アイテムの種類
	int gpc_hdl_ = 0;									//アイテムの画像
	int turn_ = 0;										//効果の持続ターン数
	std::string ex_ = "aaa";							//アイテムに関する説明文

	void init(std::string name, int type, int gpc_hdl, int turn, std::string ex);

};

void cardeffect_Item();


enum {
	TURNCOUNT_START,		//ターン計測の開始地点
	TURNCOUNT_END,			//ターン計測の終了地点
	TURNCOUNT_MAX			//ターンの計測回数
};

class Effect_Item_Buff {									//バフアイテムに関するclass

public:

	float atk_ = 1;								//攻撃バフの倍率
	float damage_ = 1;							//アイテムの画像
	int turncount[TURNCOUNT_MAX] = { -1 };		//バフの経過ターンの計測用

	void init(float atk, float damage);

};

//extern int scene_ItemEffect_Effect = ITEMEFFECT_EFFECT_ONCE;		//効果の処理を行う際のシーン遷移用
//
//const float ItemHeal_value = 0.5f;		//回復アイテムの回復割合

enum {		
	ITEMBUFF_OFF,		//ItemBuff_flag = false
	ITEMBUFF_ON,		//ItemBuff_flag = true
	ITEMBUFF_MAX		//ItemBuff_flag の要素数
};

extern Effect_Item_Buff Item_Buff[ITEMBUFF_MAX];


extern int ItemBuff_flag_size;		//ItemBuff_flagのサイズ用

extern bool ItemBuff_flag;		//アイテムによるバフがあるか判定するフラグ

extern bool Item_Analysis_flag;		//分析アイテムの効果中か判別するフラグ

void cardeffect_Item_Off();	//アイテムの処理を切る処理

void cardeffect_Item();	//アイテムの処理
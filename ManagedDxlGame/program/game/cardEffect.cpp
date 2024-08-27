#include "../dxlib_ext/dxlib_ext.h"
#include "scene_CardDraw.h"
#include "scene_CardGameMain.h"
#include "character.h"
#include "cardEffect.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "scene_GraphDraw.h"
#include "Sound.h"


int Chara_Summon = 0;									//ランダムで出てくるキャラクター用変数

int Chara_Field[CHARA_COUNT_MAX] = { 0 };				//場にいるキャラクターの番号用の配列


int scene_SkillEffect = 0;			//スキルの内容をスイッチ文で処理する用

int skill_random = 0;				//ランダムに使用するスキルを決定する用

bool chara_field_flag[CHARA_MAX] = { false };	//場に出ているキャラクターを確認する用のflag


void Status_Card::init(int cardtype, int handtype) {
	cardtype_ = cardtype;						//山札、手札等のカードの種類を入れる用
	handtype_ = handtype;						//山札、手札等のカードの属性を入れる用
}


Status_Card CardType_Deck[DECK_VOLUME];			//山札のカードの種類、属性を入れる用
Status_Card CardType_Hand[DECK_VOLUME];			//手札のカードの種類、属性を入れる用

class Status_Skill {			//スキルの内容を入れる用のclass

public:

	int atk_ = 0;								//スキルのダメージの倍率
	std::string text_ = "aaa";						//山札、手札等のカードの属性を入れる用

	void init(int atk, std::string text);

};

void Status_Skill::init(int atk, std::string text) {

	atk_ = atk;
	text_ = text;

}


enum {
	SKILL_CHAINSAW,
	SKILL_MONEY,
	SKILL_TACKLE,
	SKILL_MAX
};

Status_Skill Skill[SKILL_MAX];

bool cardeffectflag = false;				//カードの処理を行ったか判断するためのフラグ


void cardeffect_InDeck() {											//カードの効果をカードの枚数分配列に入れる処理

	for (int i = 0; i < DECK_VOLUME; i++) {

		CardType_Deck[i].init(i % CARDTYPE_MAX, rand() % HANDTYPE_MAX);

	}
}



void cardeffect_Summon() {

	if (Chara_Count_Field < FIELD_CHARA_MAX) {

		if (cardeffectflag == false) {



			Chara_Summon = rand() % (CHARA_MAX - 1);			//キャラクター(主人公以外)の中からランダムに一体選ぶ

			if (chara_field_flag[Chara_Summon] == false) {			//召喚されているキャラクター以外が選ばれたとき以下を行う

				Chara_Field[Chara_Count_Field] = Chara_Summon;		//配列に選ばれたキャラクターの番号を入れる

				chara_field_flag[Chara_Summon] = true;				//召喚したキャラクターのflagをtrueにする

				Chara_Count_Field++;								//場にいるキャラクターの数を加算する

				cardeffectflag = true;								//カードの処理を行ったのでtrueにする
			}
		}
		if (cardeffectflag == true) {								//カードの処理が行われたあとにテキストの表示および次のシーンへの遷移を行う

			DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "\n%sが召喚された！", Chara[Chara_Summon].name_.c_str());

			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				cardeffectflag = false;
				CardGameScene++;
			}
		}
	}
	else if (Chara_Count_Field == FIELD_CHARA_MAX) {

		for (int i = 0; i < Chara_Count_Field; i++) {
			Chara[Chara_Field[i]].hp_ += (Chara[Chara_Field[i]].hp_max_ * 0.3f);		//味方の体力を回復する

			if (Chara[Chara_Field[i]].hp_ > Chara[Chara_Field[i]].hp_max_) {
				Chara[Chara_Field[i]].hp_ = Chara[Chara_Field[i]].hp_max_;						//体力の最大値を超えたとき最大値にする
			}
		}

		DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "場がいっぱいで追加で召喚できなかった！\n余った力で味方が回復した！");
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			cardeffectflag = false;
			CardGameScene++;
		}
	}
	

	//if (cardeffectflag == true) {								//カードの処理が行われたあとにテキストの表示および次のシーンへの遷移を行う

	//	DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "\n%sが召喚された！", Chara[Chara_Summon].name_.c_str());

	//	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
	//		cardeffectflag = false;
	//		CardGameScene++;
	//	}
	//}
}

void Chara_Field_Draw() {								

	for (int i = 0; i < Chara_Count_Field; i++) {

		Chara[Chara_Field[i]].draw(i);					//場にいるキャラクターを表示する

	}

}

void skilleffect() {

	Skill[SKILL_CHAINSAW].init(15, "あなたはチェーンソーで敵を切り付けた！");

	Skill[SKILL_MONEY].init(8, "あなたは拳で敵をはたいた！");

	Skill[SKILL_TACKLE].init(12, "あなたは敵に体当たりした！");
}


void cardeffect_Skill() {



	enum {
		SKILLEFFECT_LOAD,
		SKILLEFFECT_TEXT_EFFECT,
		SKILLEFFECT_DAMAGE,
		SKILLEFFECT_DAMAGETEXT,
		SKILLEFFECT_MAX
	};


	if (cardeffectflag == false) {


		switch (scene_SkillEffect) {
		case SKILLEFFECT_LOAD:

			skill_random = rand() % SKILL_MAX;		//ランダムに使用するスキルを決定する

			skilleffect();


			scene_SkillEffect++;

			break;

		case SKILLEFFECT_TEXT_EFFECT:

			if (skill_random == SKILL_CHAINSAW) {
				DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, Skill[SKILL_CHAINSAW].text_.c_str());		//スキルに対応したテキストを表示
			}
			else if (skill_random == SKILL_MONEY) {
				DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, Skill[SKILL_MONEY].text_.c_str());			//スキルに対応したテキストを表示
			}
			else if (skill_random == SKILL_TACKLE) {
				DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, Skill[SKILL_TACKLE].text_.c_str());		//スキルに対応したテキストを表示
			}

			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

				scene_SkillEffect++;
			}
			break;

		case SKILLEFFECT_DAMAGE:


			Enemy[EnemyInStage].hp_ -= Chara[CHARA_YOU].atk_ * Skill[skill_random].atk_;										//敵にダメージを与える

			scene_SkillEffect++;

			break;


		case SKILLEFFECT_DAMAGETEXT:

			DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "%sに%dのダメージを与えた！", Enemy[EnemyInStage].name_.c_str(), Chara[CHARA_YOU].atk_* Skill[skill_random].atk_);		//与えたダメージを表示


			if (Enemy[EnemyInStage].hp_ <= 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				CardGameScene = GAME_END;
			}

			//	次のシーンへ移る
			else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				
				cardeffectflag = false;
				scene_SkillEffect = SKILLEFFECT_LOAD;
				CardGameScene++;
			}
			break;
		}
	}
}


//class Effect_Item {			//アイテムに関するclass
//
//public:
//
//	std::string name_ = "aaa";							//カードの名前
//	int type_ = ITEM_MAX;								//アイテムの種類
//	int gpc_hdl_ = 0;									//アイテムの画像
//	std::string ex_ = "aaa";							//アイテムに関する説明文
//
//	void init(std::string name, int type, int gpc_hdl, std::string ex);
//
//};


void Effect_Item::init(std::string name, int type, int gpc_hdl, int turn, std::string ex) {
	name_ = name;						//アイテム名
	type_ = type;						//アイテムの種類
	gpc_hdl_ = gpc_hdl;					//アイテムの画像ハンドル
	turn_ = turn;						//効果の持続ターン
	ex_ = ex;							//アイテムの説明文
}

Effect_Item Item[ITEM_MAX];



//enum {
//	ITEM_BUFF,			//バフアイテム
//	ITEM_HEAL,			//回復アイテム
//	ITEM_ANALYSIS,		//分析アイテム
//	ITEM_MAX			//アイテム数
//};


int scene_ItemEffect = 0;		//アイテムの効果のシーン管理用

const tnl::Vector3 ITEMSEL_GPC_POS = { 400, 360, 0 };		//アイテムの画像選択位置

enum {
	ITEMEFFECT_INIT,
	ITEMEFFECT_SELECT,
	ITEMEFFECT_EFFECT

};

int Sel_Item = ITEM_BUFF;		//選択しているアイテム
bool Sel_Item_flag = true;		//アイテムを選択できるようになるフラグ




void Effect_Item_Buff::init(float atk, float damage) {
	atk_ = atk;
	damage_ = damage;
}


//enum {
//	ITEMBUFF_OFF,		//ItemBuff_flag = false
//	ITEMBUFF_ON,		//ItemBuff_flag = true
//	ITEMBUFF_MAX		//ItemBuff_flag の要素数
//};

bool ItemBuff_flag = false;		//アイテムによるバフがあるか判定するフラグ

int ItemBuff_flag_size = ITEMBUFF_OFF;		//ItemBuff_flagのサイズ用

//効果の処理を行う際のシーン遷移用
enum {
	ITEMEFFECT_EFFECT_ONCE,		//一度のみ処理する効果の処理等を行うシーン
	ITEMEFFECT_EFFECT_TEXT		//効果のテキスト等表示するシーン
};

int scene_ItemEffect_Effect = ITEMEFFECT_EFFECT_ONCE;		//効果の処理を行う際のシーン遷移用

const float ItemHeal_value = 0.5f;		//回復アイテムの回復割合

Effect_Item_Buff Item_Buff[ITEMBUFF_MAX];


int Item_Analysis_turn = 3;		// 分析アイテムの効果ターン
int Item_Analysis_turn_start = 0;		// 分析アイテムの開始ターン
bool Item_Analysis_flag = false;		//分析アイテムの効果中か判別するフラグ


void ItemInit() {
	int temp[ITEM_MAX] = { 0 };

	temp[ITEM_BUFF] = LoadGraph("graphics/mygame/item/buff.png");
	Item[ITEM_BUFF].init("ギター(強化)", ITEM_BUFF, temp[ITEM_BUFF], 3, "アイテム：ギター...\n ギターを演奏して味方を鼓舞します。\n (与えるダメージと受けるダメージが一定ターン増減します。)");

	temp[ITEM_HEAL] = LoadGraph("graphics/mygame/item/heal.png");
	Item[ITEM_HEAL].init("猫(回復)", ITEM_HEAL, temp[ITEM_HEAL], 1, "アイテム：猫...\n 猫に癒されます。\n (味方全体の体力が一定割合増加します。)");

	temp[ITEM_ANALYSIS] = LoadGraph("graphics/mygame/item/analysis.png");
	Item[ITEM_ANALYSIS].init("PC(分析)", ITEM_ANALYSIS, temp[ITEM_ANALYSIS], 3, "アイテム：PC...\n 敵を分析します。\n (敵の攻撃の属性(じゃんけんの手)が一定ターン表示されます。)");

	Item_Buff[ITEMBUFF_OFF].init(1.0f, 1.0f);		//バフなしの倍率
	Item_Buff[ITEMBUFF_ON].init(1.2f, 0.8f);		//バフありの倍率

}


void cardeffect_Item_Off() {

	if (TurnCount - Item_Buff[ITEMBUFF_ON].turncount[TURNCOUNT_START] == Item[ITEM_BUFF].turn_ && ItemBuff_flag == true) {
		ItemBuff_flag = false;

		ItemBuff_flag_size = ITEMBUFF_OFF;

		Item_Buff[ITEMBUFF_OFF].turncount[TURNCOUNT_END] = TurnCount;
	}

	if (TurnCount - Item_Analysis_turn_start > Item_Analysis_turn && Item_Analysis_flag == true) {
		Item_Analysis_flag = false;
	}

}



void cardeffect_Item() {

	BackDark_flag = true;
	TextWindowDraw();

	SetDrawBright(255, 255, 255);

	switch (scene_ItemEffect) {
	case ITEMEFFECT_INIT:
		sound_se_cardpass();
		ItemInit();
		Sel_Item_flag = true;
		scene_ItemEffect++;

		break;

	case ITEMEFFECT_SELECT:

		if (Sel_Item_flag) {

			//右キーを押したときにSel_Itemを一つ増やす
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) {
				Sel_Item++;
				sound_se_sel();
				if (Sel_Item == ITEM_MAX) {						//Itemの数以上になったとき初期値に戻す
					Sel_Item = ITEM_BUFF;
				}
			}

			//左キーを押したときにSel_Itemを一つ減らす
			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
				Sel_Item--;
				sound_se_sel();
				if (Sel_Item < ITEM_BUFF) {						//Itemの初期値を下回ったときに最大値のItemにする
					Sel_Item = ITEM_ANALYSIS;
				}
			}





			DrawRotaGraph(ITEMSEL_GPC_POS.x + 200 * Sel_Item, ITEMSEL_GPC_POS.y - 150, 0.8f, M_PI * 5 / 4, Cursor_hdl, true);		//選択用のカーソルを表示する

			SetFontSize(20);

			DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y , -1, Item[Sel_Item].ex_.c_str());						//アイテムカードの説明を表示する

			for (int i = 0; i < ITEM_MAX; i++) {

				DrawRotaGraphF(ITEMSEL_GPC_POS.x + i * HAND_SPACE, ITEMSEL_GPC_POS.y, 0.4f, 0, CardBase_gpc_hdl, true);				//アイテムのカードの背景を表示させる

				DrawRotaGraphF(ITEMSEL_GPC_POS.x + i * HAND_SPACE, ITEMSEL_GPC_POS.y, 0.5f, 0, Item[i].gpc_hdl_, true);				//アイテムのカードの画像を表示させる

				SetFontSize(15);

				DrawStringEx(ITEMSEL_GPC_POS.x - 35 + i * HAND_SPACE, ITEMSEL_GPC_POS.y + 60, 0, "%s", Item[i].name_.c_str());		//カードの名前を表示させる
			}

			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				sound_se_enter();
				Sel_Item_flag = false;
				scene_ItemEffect++;
			}
		}
		break;

	case ITEMEFFECT_EFFECT:

		switch (scene_ItemEffect_Effect) {
		case ITEMEFFECT_EFFECT_ONCE:
			if (Sel_Item == ITEM_BUFF) {
				if (ItemBuff_flag == false) {
					ItemBuff_flag = true;

					if (Item_Buff[ITEMBUFF_ON].turncount[TURNCOUNT_START] != TurnCount) {
						ItemBuff_flag_size = ITEMBUFF_ON;

						Item_Buff[ITEMBUFF_ON].turncount[TURNCOUNT_START] = TurnCount;
					}
				}
			}
			else if (Sel_Item == ITEM_HEAL) {

				for (int i = 0; i < Chara_Count_Field; i++) {
					Chara[Chara_Field[i]].hp_ += (Chara[Chara_Field[i]].hp_max_ * ItemHeal_value);		//味方の体力を回復する

					if (Chara[Chara_Field[i]].hp_ > Chara[Chara_Field[i]].hp_max_) {
						Chara[Chara_Field[i]].hp_ = Chara[Chara_Field[i]].hp_max_;						//体力の最大値を超えたとき最大値にする
					}
				}
			}
			else if (Sel_Item == ITEM_ANALYSIS) {

				Item_Analysis_flag = true;
				Item_Analysis_turn_start = TurnCount;

			}

			scene_ItemEffect_Effect++;

			break;

		case ITEMEFFECT_EFFECT_TEXT:

			if (Sel_Item == ITEM_BUFF) {
				DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "カード：ギターの効果！\n ギターの演奏で味方の士気が上がった！");		//カードの効果を表示させる
			}
			if (Sel_Item == ITEM_HEAL) {
				DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "カード：猫の効果！\n 猫に癒されて味方の体力が回復した！");		//カードの効果を表示させる
			}
			if (Sel_Item == ITEM_ANALYSIS) {
				DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "カード：PCの効果！\n 敵を分析して相手の行動を予測した！");		//カードの効果を表示させる
			}


			if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
				BackDark_flag = false;
				scene_ItemEffect = ITEMEFFECT_INIT;
				scene_ItemEffect_Effect = ITEMEFFECT_EFFECT_ONCE;
				CardGameScene++;
			}
		}


		//if (Sel_Item == ITEM_BUFF) {

		//	if (ItemBuff_flag == false) {
		//		ItemBuff_flag = true;

		//		if (Item_Buff[ITEMBUFF_ON].turncount[TURNCOUNT_START] != TurnCount) {
		//			ItemBuff_flag_size = ITEMBUFF_ON;

		//			Item_Buff[ITEMBUFF_ON].turncount[TURNCOUNT_START] = TurnCount;
		//		}
		//	}

		//	DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "カード：ギターの効果！\n ギターの演奏で味方の士気が上がった！");		//カードの効果を表示させる

		//		Sel_Item_flag = false;
		//		CardGameScene++;
		//	}if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		//	

		//}
		/*else if (Sel_Item == ITEM_HEAL) {

			;




		}*/

	}

}
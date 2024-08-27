#include "../dxlib_ext/dxlib_ext.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "gm_main.h"
#include "scene_CardDraw.h"
#include "scene_Check.h" 
#include "scene_CardGameMain.h"
#include "character.h"
#include "cardEffect.h"
#include "scene_GraphDraw.h"
#include "scene_Menu.h"
#include "Sound.h"


//-----------------------------------------------------------------------------------------------------------------------------------
//extern済の変数

int SelectHandNumber_Player = 0;								//選択している手札の番号
int SelectHandCard_hdl_Player = 0;								//選択した手札の画像

int CardGameScene = 0;											//ゲーム中のシーン用の切り替え用

bool CardGamePlay = true;		//カードゲームを続行するフラグ

bool hand_select_frag = true;									//trueのときカードを選択できる
bool entcardcheck_flag = false;									//確認用のウィンドウを表示させる用のフラグ

bool entcardcheck_flag_Enter = false;							//確認の処理に入った際のEnterキーで決定しないようにするためのフラグ

bool select_check_flag = true;									//確認のYESとNOを切り替え可能にする用
int Select_Check = YES;											//YESとNOの選択している方を入れる用


int ActionNumber_Enemy = 0;										//敵の行動に割り当てている番号

bool turnset_flag = true;										// 1ターン毎に必要な変数等をセットし直す用のフラグ

int TurnCount = 0;												//ターンをカウントする用の変数


enum {
	RESULT_WIN,			//じゃんけんの結果：勝利
	RESULT_DRAW,		//じゃんけんの結果：引き分け
	RESULT_LOSE,		//じゃんけんの結果：敗北
	RESULT_MAX			//じゃんけんの結果数
};

class RPS_RESULT {										//じゃんけんの勝敗のclass

public:
	std::string name_ = "piyo";							//じゃんけんの結果の名前
	int type_ = RESULT_WIN;								//結果の状態の値
	float atk_ = 1;										//結果による攻撃力の変動
	float damage_ = 1;									//結果による受けるダメージの変動

	void init(std::string name, int type, float atk, float damage);

};

void RPS_RESULT::init(std::string name, int type, float atk, float damage) {
	name_ = name;
	type_ = type;
	atk_ = atk;
	damage_ = damage;
}


RPS_RESULT Result[RESULT_MAX];

void ResultInit() {

	Result[RESULT_WIN].init("勝利", RESULT_WIN, 1.2f, 0.8f);

	Result[RESULT_DRAW].init("引き分け", RESULT_DRAW, 1.0f, 1.0f);

	Result[RESULT_LOSE].init("敗北", RESULT_LOSE, 0.8f, 1.2f);

}



int g_result = RESULT_MAX;				//じゃんけんの結果

int EnemyInStage = ENEMY_YOU;			//現在のステージの敵

int scene_CardEffect = 0;				//カード効果の処理を行う際のswitch用

int atk_CharaAll = 0;					//味方全体の攻撃力の合計

int scene_CharaBattle = 0;				//キャラクターがバトルするシーンのswitch用

int target = 0;							//敵の攻撃対象

bool BackDark_flag = false;				//後ろの画像を暗くするフラグ



//const tnl::Vector3 TEXT_CARDSEL_POS = { 500, 50, 0 };			//テキストウィンドウの位置


void sceneCardGame_TurnSet() {			//毎ターンセットする用の変数等

	SelectHandNumber_Player = 0;

	entcardcheck_flag_Enter = false;

	entcardcheck_flag = false;

	hand_select_frag = true;

	//CardGameScene = 0;

	hand_select_frag = true;

	entcardcheck_flag = false;

	entcardcheck_flag_Enter = false;

	select_check_flag = true;

	scene_CardEffect = 0;

	atk_CharaAll = 0;

	scene_CharaBattle = 0;

	target = 0;

	turnset_flag = false;

	
}



void sceneCardGame_Start() {

	CardGameScene = 0;

	DeckCount_Player = DECK_VOLUME;
	HandCount_Player = 0;

	cardeffect_InDeck();

	CardGraphLoad();

	sceneCardGame_CharaSet();

	sceneCardGame_EnemySet();

	Chara_Field[0] = CHARA_YOU;

	Chara_Count_Field = 1;

	sceneCardGame_Action_EnemySet();

	ResultInit();

	turnset_flag = true;

	// bool a = turnset_flag;

	TurnCount = 0;

	//CardGameScene++;

}


void sceneCardGame_FirstDraw() {							//初期手札を配る
	for (int i = 0; i < HAND_VOLUME - 1; i++) {
		sceneCardGame_CardDraw_Player();
	/*	sceneCardGame_CardDraw_Cpu();*/
	}
	//CardGameScene = GAME_HANDSELECT;
}


void TextWindowDraw() {
	DrawRotaGraph(TEXTWINDOW_POS.x, TEXTWINDOW_POS.y, 1.0f, 0, TextWindow_hdl, true);
	DrawStringEx(TEXT_IN_WINDOW_POS.x + 850, TEXT_IN_WINDOW_POS.y + 100, -1, "Enterで次に進みます");
}



void sceneCardGame_SelectCardCheck() {


	SetFontSize(20);
	DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "選択したカードを出しますか？"/*\nSelect_Check = %d\nselect_check_flag = %d*//*, Select_Check, select_check_flag*/);
	DrawStringEx(TEXT_IN_WINDOW_POS.x + 500, TEXT_IN_WINDOW_POS.y, -1, "YES\nNO");

	DrawRotaGraph(TEXT_IN_WINDOW_POS.x + 480, TEXT_IN_WINDOW_POS.y + 10 + 20 * Select_Check, 0.5f, M_PI * 3 / 4, Cursor_hdl, true);
	//select_check_flag = true;


	if (select_check_flag) {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			Select_Check++;
			sound_se_sel();
			if (Select_Check > NO) {						//NOで↓を押したときYESに戻す
				Select_Check = YES;
			}
		}

		//↓を押したときに選択中のカードを一つ左にずらす
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			Select_Check--;
			sound_se_sel();
			if (Select_Check < YES) {						//YESで↑を押したときNOに戻す
				Select_Check = NO;
			}
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN) && entcardcheck_flag_Enter == true) {

			if (Select_Check == YES) {															//YESでEnterを押したときに以下の処理を行う

				for (int j = 0; j < HAND_VOLUME; j++) {											//手札の選択したカードの位置より後ろのカードを前にずらすことで選択したカードを山札から消す
					if (j >= SelectHandNumber_Player) {
						HandCard_hdl_Player[j] = HandCard_hdl_Player[j + 1];
					}
				}
				sound_se_enter();
				sound_se_cardput();

				HandCount_Player--;						

				entcardcheck_flag = false;														//確認の表示を消す
				select_check_flag = false;

				CardGameScene++;																//シーンを次に進める


			}
			else {

				sound_se_cardpass();
				entcardcheck_flag = false;														//選択の画面に戻す
				hand_select_frag = true;
			}

		}

		else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_ESCAPE) && entcardcheck_flag_Enter == true) {
			sound_se_cardpass();
			entcardcheck_flag = false;
			hand_select_frag = true;
		}
	}
																								//手札のカードを選択した際のEnterで確認の処理が反応しないようにするための処理
	if (entcardcheck_flag_Enter) {																//確認用のフラグがtrueのとき(2ループ目)
		entcardcheck_flag_Enter = false;														//フラグをfalseにする
	}

	else {																						//確認用のフラグがfalseのとき(1ループ目)
		entcardcheck_flag_Enter = true;															//フラグをtrueにする
	}


}



void ActionSelect_Enemy() {		//敵の行動を決定する

	ActionNumber_Enemy = rand() % ACTION_MAX_ENEMY;				//敵の行動を決定する

	action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_ = ( rand() % HANDTYPE_MAX );			//敵の行動の属性を決定する

}



void sceneCardGame_HandSelect() {

	BackDark_flag = true;

	SetDrawBright(255, 255, 255);		// 以下の内容を通常の輝度で表示する



	if (entcardcheck_flag == false) {
		TextWindowDraw();

		SetFontSize(20);

		DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "カードを選択してください");

		SetFontSize(18);

		if (CardType_Hand[SelectHandNumber_Player].cardtype_ == CARDTYPE_SUMMON) {
			DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y + 40, -1, "カード：召喚...\n  味方を召喚するカードです。ターン毎に発生する総攻撃のダメージが上がります。");
		}
		else if (CardType_Hand[SelectHandNumber_Player].cardtype_ == CARDTYPE_SKILL) {
			DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y + 40, -1, "カード：スキル...\n  ランダムで選ばれた、ダメージの発生するスキルを使用します。\n  スキルによって与えるダメージ量が変わります。");
		}
		if (CardType_Hand[SelectHandNumber_Player].cardtype_ == CARDTYPE_ITEM) {
			DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y + 40, -1, "カード：アイテム...\n  バトルを補助するアイテムを選択して使用します。");
		}

		
	}

	//選択中のカードの上にカーソルを表示する

	DrawRotaGraphF(PLAYER_HAND_FIRST_POS.x + SelectHandNumber_Player * HAND_SPACE, PLAYER_HAND_FIRST_POS.y - 150, 1.0f, M_PI * 5 / 4, Cursor_hdl, true);


	if (hand_select_frag) {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RIGHT)) {
			SelectHandNumber_Player++;
			sound_se_sel();
			if (SelectHandNumber_Player > HandCount_Player - 1) {		//選択しているカードが手札の枚数を超えたとき0にもどす
				SelectHandNumber_Player = 0;
			}
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_LEFT)) {
			SelectHandNumber_Player--;
			sound_se_sel();
			if (SelectHandNumber_Player < 0) {					//選択しているカードが0を下回ったとき手札枚数の値にもどす
				SelectHandNumber_Player = HandCount_Player - 1;
			}
		}


		//ENTERを押したときに選択中の手札のカードを決定する
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

			sound_se_cardput();

			entcardcheck_flag = true;		//確認用のテキストを表示する
			hand_select_frag = false;		//カード選択用のカーソルを動かないようにする

			entcardcheck_flag_Enter = false;

		}

	}

	if (entcardcheck_flag) {
		TextWindowDraw();
		sceneCardGame_SelectCardCheck();
	}
}



void sceneCardGame_R_P_S_Battle() {

	//BackDark_flag = true;				//背景を暗くする



	SetDrawBright(255, 255, 255);		// 以下の内容を通常の輝度で表示する


	DrawRotaGraph(USECARD_PLAYER_POS.x, USECARD_PLAYER_POS.y, 0.4f, 0, CardBase_gpc_hdl, true);				//カードのベースの画像を表示する


	DrawRotaGraph(USECARD_PLAYER_POS.x, USECARD_PLAYER_POS.y, 0.3f, 0, CardType[CardType_Hand[SelectHandNumber_Player].cardtype_].gpc_hdl_, true);		//選択したカードの画像を表示させる

	DrawRotaGraph(USECARD_PLAYER_POS.x + 55, USECARD_PLAYER_POS.y - 70, 0.15f, 0, HandType[CardType_Hand[SelectHandNumber_Player].handtype_].gpc_hdl_, true);		//選択したカードの属性を表示させる

	//DrawStringEx(100, 300, -1, " PLAYERHAND = %d", CardType_Hand[SelectHandNumber_Player].handtype_);		//確認用

	DrawStringEx(USECARD_PLAYER_POS.x - 20, USECARD_PLAYER_POS.y + 60, 0, "%s", CardType[CardType_Hand[SelectHandNumber_Player].cardtype_].name_.c_str());		//カードの名前を表示させる


	DrawRotaGraph(USECARD_ENEMY_POS.x, USECARD_ENEMY_POS.y, 0.4f, 0, CardBase_gpc_hdl, true);				//カードのベースの画像を表示する


	DrawRotaGraph(USECARD_ENEMY_POS.x, USECARD_ENEMY_POS.y, 0.3f, 0, action_Enemy[EnemyInStage][ActionNumber_Enemy].gpc_hdl_, true);		//敵のカードの画像を表示させる

	DrawRotaGraph(USECARD_ENEMY_POS.x + 55, USECARD_ENEMY_POS.y - 70, 0.15f, 0, HandType[action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_].gpc_hdl_, true);		//敵の行動の属性を表示させる

	//DrawStringEx(100, 350, -1, " ENEMYHAND = %d", action_Enemy[ENEMY_YOU][ActionNumber_Enemy].handtype_);		//確認用

	DrawStringEx(USECARD_ENEMY_POS.x - 20, USECARD_ENEMY_POS.y + 60, 0, "%s", action_Enemy[EnemyInStage][ActionNumber_Enemy].name_.c_str());		//敵の行動の名前を表示させる

	TextWindowDraw();





	//じゃんけんの勝敗判定の処理
	if (CardType_Hand[SelectHandNumber_Player].handtype_ == HANDTYPE_ROCK) {
		if (action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_ == HANDTYPE_ROCK) {
			g_result = RESULT_DRAW;
		}
		if (action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_ == HANDTYPE_PAPER) {
			g_result = RESULT_LOSE;
		}
		if (action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_ == HANDTYPE_SCISSORS) {
			g_result = RESULT_WIN;
		}
	}
	if (CardType_Hand[SelectHandNumber_Player].handtype_ == HANDTYPE_PAPER) {
		if (action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_ == HANDTYPE_PAPER) {
			g_result = RESULT_DRAW;
		}
		if (action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_ == HANDTYPE_SCISSORS) {
			g_result = RESULT_LOSE;
		}
		if (action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_ == HANDTYPE_ROCK) {
			g_result = RESULT_WIN;
		}
	}
	if (CardType_Hand[SelectHandNumber_Player].handtype_ == HANDTYPE_SCISSORS) {
		if (action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_ == HANDTYPE_SCISSORS) {
			g_result = RESULT_DRAW;
		}
		if (action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_ == HANDTYPE_ROCK) {
			g_result = RESULT_LOSE;
		}
		if (action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_ == HANDTYPE_PAPER) {
			g_result = RESULT_WIN;
		}
	}


	SetFontSize(20);
	//勝敗に応じたテキストの表示
	if (g_result == RESULT_WIN) {
		DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "あなたの勝利！\n味方の士気が上がった！");
	}
	else if (g_result == RESULT_DRAW) {
		DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "引き分けです");
	}
	else if (g_result == RESULT_LOSE) {
		DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "あなたの負け!\n味方の士気が下がった！");
	}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

		CardType_Deck[DeckCount_Player] = CardType_Hand[SelectHandNumber_Player];		//使用したカードを山札に戻す
		DeckCount_Player++;																//山札枚数を増やす


		BackDark_flag = false;				//背景を明るくする
		CardGameScene++;					//シーンを次に進める

	}
}

void sceneCardGame_CardEffect() {

	enum {
		CARDEFFECT_CARDTYPETEXT,		//カードの種類に応じてテキストを表示
		CARDEFFECT_CARDTYPE_EFFECT,		//カードの種類に応じて効果を処理
		CARDEFFECT_MAX
	};

	TextWindowDraw();

	SetFontSize(20);

	switch (scene_CardEffect) {
	case CARDEFFECT_CARDTYPETEXT:

		DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "カード：%sの効果発動！", CardType[CardType_Hand[SelectHandNumber_Player].cardtype_].name_.c_str());		//発動するカードを表示

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			scene_CardEffect++;					//シーンを次に進める
		}

		break;

	case CARDEFFECT_CARDTYPE_EFFECT:


		if (CardType_Hand[SelectHandNumber_Player].cardtype_ == CARDTYPE_SUMMON) {
			cardeffect_Summon();
		}
		else if (CardType_Hand[SelectHandNumber_Player].cardtype_ == CARDTYPE_SKILL) {
			cardeffect_Skill();
		}
		else if (CardType_Hand[SelectHandNumber_Player].cardtype_ == CARDTYPE_ITEM) {
			cardeffect_Item();
		}


			
		break;
	}
}

enum {
	DAMAGE_CHARA,		//キャラクターの与えるダメージ
	DAMAGE_ENEMY,		//敵の与えるダメージ
	DAMAGE_MAX
};

int damage[DAMAGE_MAX] = {};

void CharaOut() {		//味方がやられたときの処理

	for (int i = 0; i < Chara_Count_Field; i++) {

		if (Chara[Chara_Field[i]].hp_ < 0) {
			Chara[Chara_Field[i]].hp_ = 0;


			for (int j = 0; j < Chara_Count_Field; j++) {
				if (j >= i) {
					Chara_Field[j] = Chara_Field[j + 1];
				}
			}

			chara_field_flag[Chara_Field[i]] = false;				//やられたキャラクターのflagをfalseにする

			Chara_Count_Field--;

		}

		

		//DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "%sがやられてしまった！", Chara[Chara_Field[i]].name_.c_str());

	}

}


void sceneCardGame_CharaBattle() {

	

	enum {
		CHARABATTLE_ATTACK_CHARA,
		CHARABATTLE_ATTACKTEXT_CHARA,
		CHARABATTLE_ATTACK_ENEMY,
		CHARABATTLE_ATTACKTEXT_ENEMY
	};


 

	TextWindowDraw();

	SetFontSize(20);

	switch (scene_CharaBattle) {
	case CHARABATTLE_ATTACK_CHARA:

		for (int i = 0; i < Chara_Count_Field; i++) {
			atk_CharaAll += Chara[Chara_Field[i]].atk_;		//場のキャラクター全員の攻撃力を合計する
		}

		damage[DAMAGE_CHARA] = ( atk_CharaAll * Result[g_result].atk_ * Item_Buff[ItemBuff_flag_size].atk_ );				//敵に与えるダメージを決定する

		Enemy[EnemyInStage].hp_ -= damage[DAMAGE_CHARA];				//敵にダメージを与える

		scene_CharaBattle++;
		sound_se_sel();
		break;

	case CHARABATTLE_ATTACKTEXT_CHARA:



		target = rand() % Chara_Count_Field;		//攻撃対象の選択

		DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "味方の総攻撃！\n%sに%dのダメージを与えた！", Enemy[EnemyInStage].name_.c_str(), damage[DAMAGE_CHARA]);		//スキルに対応したテキストを表示

		if (Enemy[EnemyInStage].hp_ <= 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			CardGameScene = GAME_END;
		}

		else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			scene_CharaBattle++;
		}
		break;

	case CHARABATTLE_ATTACK_ENEMY:

		damage[DAMAGE_ENEMY] = Enemy[EnemyInStage].atk_ * action_Enemy[EnemyInStage][ActionNumber_Enemy].atk_mag_ * Result[g_result].damage_ * Item_Buff[ItemBuff_flag_size].damage_;

		Chara[Chara_Field[target]].hp_ -= damage[DAMAGE_ENEMY];		//対象に行動の倍率に応じたダメージ(じゃんけんの結果補正あり)を与える

		scene_CharaBattle++;
		sound_se_sel();
		break;

	case CHARABATTLE_ATTACKTEXT_ENEMY:

		//敵の攻撃のテキストを表示
		DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "%sの%s！\n%sは%dのダメージを受けた！", Enemy[EnemyInStage].name_.c_str(), action_Enemy[EnemyInStage][ActionNumber_Enemy].name_.c_str(), Chara[Chara_Field[target]].name_.c_str(), damage[DAMAGE_ENEMY]);


		if (Enemy[EnemyInStage].hp_ <= 0 && tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			CardGameScene = GAME_END;
		}

		else if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
			CharaOut();
			sound_se_sel();
			TurnCount++;
			CardGameScene = GAME_TURNSET;
			turnset_flag = true;
		}
		break;
	}
}

enum {
	END_WIN,		//勝利エンド
	END_LOSE,		//敗北エンド
	END_MAX			//エンド数
};

int endswitch = END_MAX;		//勝利と敗北の切り替え
//int Poster_Text_gpc_hdl = 0;	//文字表示の紙の画像用

void sceneCardGameEnd() {

	if (endswitch == END_MAX) {

		if (Enemy[EnemyInStage].hp_ <= 0) {			//敵のHPが0未満になったとき
			Enemy[EnemyInStage].hp_ = 0;			//敵のHPを0にする
			endswitch = END_WIN;						//勝利時の処理を行う
		}
		else if (Chara[CHARA_YOU].hp_ <= 0) {
			Chara[CHARA_YOU].hp_ = 0;				//主人公のHPを0にする
			endswitch = END_LOSE;					//敗北時の処理を行う
		}
	}




	TextWindowDraw();

	const tnl::Vector3 END_TEXT_POS = { 500, 300, 0 };

	DrawRotaGraph(END_TEXT_POS.x + 150, END_TEXT_POS.y + 20, 0.5f, 0, Poster_Text_gpc_hdl, true);		//テキストの背景表示

	SetFontSize(50);
	if (endswitch == END_WIN) {
		DrawStringEx(END_TEXT_POS.x, END_TEXT_POS.y, 0, "Stage Clear！");		//勝利時のテキストを表示
	}
	else if(endswitch == END_LOSE) {
		DrawStringEx(END_TEXT_POS.x, END_TEXT_POS.y, 0, "Game Over...");			//敗北時のテキストを表示
	}
	SetFontSize(20);
	DrawStringEx(TEXT_IN_WINDOW_POS.x, TEXT_IN_WINDOW_POS.y, -1, "%sに勝利した！\n\nスペースキーでタイトルに戻ります", Enemy[EnemyInStage].name_.c_str());

	//if (CardGamePlay = true) {
	//	Enemy[EnemyInStage].hp_ = 0;			//敵のHPを0にする
	//	CardGamePlay = false;				//カードゲームの処理を行うフラグ
	//}

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_SPACE)) {
		sound_se_enter();
		scene_GameMain = GAMEMAIN_TITLE;
	}

}


void CardGameStart_Text() {
	const tnl::Vector3 START_TEXT_POS = { 500, 300, 0 };

	DrawRotaGraph(START_TEXT_POS.x + 160, START_TEXT_POS.y + 20, 0.5f, 0, Poster_Text_gpc_hdl, true);		//テキストの背景表示

	SetFontSize(50);
	DrawStringEx(START_TEXT_POS.x, START_TEXT_POS.y, 0, "Battle Start！");		//勝利時のテキストを表示

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		CardGameScene = GAME_TURNSET;
		sound_se_sel();
	}
}

void CardGame_TurnText() {
	const tnl::Vector3 TURN_TEXT_POS = { 500, 300, 0 };

	DrawRotaGraph(TURN_TEXT_POS.x + 160, TURN_TEXT_POS.y + 20, 0.5f, 0, Poster_Text_gpc_hdl, true);		//テキストの背景表示

	SetFontSize(50);
	DrawStringEx(TURN_TEXT_POS.x + 100, TURN_TEXT_POS.y, 0, "Turn %d", TurnCount + 1);		//ターン開始時のテキストを表示


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {
		sound_se_sel();
		CardGameScene = GAME_DRAW;
	}
}




void sceneCardGameMain() {


	if (BackDark_flag) {
		SetDrawBright(128, 128, 128);// 後ろの画面を暗くする
	}

		DrawRotaGraph(640, 360, 1.4f, 0, wallpaper[Select_Enemy + 1], true);		//背景を表示させる

		Enemy[EnemyInStage].draw();												//敵キャラクターを表示する(仮)


		for (int i = 0; i < Chara_Count_Field; i++) {

			Chara[Chara_Field[i]].draw(i);										//場のキャラクターを表示する

		}


		if (CardGamePlay) {

			switch (CardGameScene) {
			case GAME_START:

				sceneCardGame_Start();
				CardGameScene++;;

				break;

			case GAME_STARTTEXT:

				CardGameStart_Text();

				break;
			case GAME_TURNSET:

				if (turnset_flag) {
					ActionSelect_Enemy();			//敵の行動を決定する
					cardeffect_Item_Off();
					sceneCardGame_TurnSet();
				}
				if (!turnset_flag) {
					CardGame_TurnText();
				}
				break;
			case GAME_DRAW:

				if (TurnCount == 0) {
					sceneCardGame_FirstDraw();
				}

				sceneCardGame_CardDraw_Player();
				

				CardGameScene++;

				break;

			case GAME_HANDSELECT:

				CardGraphDraw();
				sceneCardGame_HandSelect();


				break;

			case GAME_R_P_S_BATTLE:

				sceneCardGame_R_P_S_Battle();

				break;

			case GAME_CARDEFFECT:

				sceneCardGame_CardEffect();

				break;

			case GAME_CHARABATTLE:

				sceneCardGame_CharaBattle();

				break;

			case GAME_END:

				sceneCardGameEnd();

				break;
			}
		}


//デバッグ用
// 
	//DrawStringEx(10, 10, 0, "SCENE = %d", CardGameScene);
	//DrawStringEx(10, 50, 0, "Handcount = %d", HandCount_Player);
	//DrawStringEx(10, 90, 0, "DeckCount_Player = %d", DeckCount_Player);
	//DrawStringEx(10, 130, 0, "TurnCount = %d", TurnCount);
	//DrawStringEx(10, 170, 0, "Buff = %d", ItemBuff_flag);



	//DrawStringEx(100, 100, 0, "Chara_Count_Field = %d", Chara_Count_Field);				//Chara_Count_Field確認用

	

	//cpuの手札を表示させる
	//for (int i = 0; i < HandCount_Cpu; i++) {

	//	DrawRotaGraphF(CPU_HAND_FIRST_POS.x + i * HAND_SPACE, CPU_HAND_FIRST_POS.y, 0.25f, 0, HandCard_Cpu[i], true);
	//}



}

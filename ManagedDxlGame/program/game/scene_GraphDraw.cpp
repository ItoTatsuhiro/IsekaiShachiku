#include "../dxlib_ext/dxlib_ext.h"
#include "scene_CardDraw.h"
#include "scene_GraphDraw.h"
#include "cardEffect.h"
#include "character.h"
#include "scene_CardGameMain.h"


int Cursor_hdl = 0;													//カード等選択中の表示用

int TextWindow_hdl = 0;												//テキストウィンドウの表示用

int CardBase_gpc_hdl = 0;											//カードの基礎用の画像

int CardType_gpc_hdl[CARDTYPE_MAX] = {0};							//カードの種類毎の画像用の配列

int Poster_Text_gpc_hdl = 0;			//文字表示の紙の画像用

int target_gpc_hdl = 0;					//ターゲットの画像

//enum {
//	WALLPAPER_TITLE,		//タイトルの壁紙
//	WALLPAPER_STAGE1,		// STAGE1の壁紙
//	WALLPAPER_STAGE2,		// STAGE2の壁紙
//	WALLPAPER_STAGE3,		// STAGE3の壁紙
//	WALLPAPER_STAGE4,		// STAGE4の壁紙
//	WALLPAPER_MAX			// 壁紙の数
//};

int wallpaper[WALLPAPER_MAX] = { 0 };		//背景用の配列




void Status_CardType::init(std::string name, int gpc_hdl, int cardtype) {
	name_ = name;				//カードの種類の名前
	gpc_hdl_ = gpc_hdl;			//カードの種類の画像
	cardtype_ = cardtype;		//カードの種類

}



void Status_HandType::init(std::string name, int gpc_hdl, int handtype) {
	name_ = name;				//属性の名前
	gpc_hdl_ = gpc_hdl;			//属性の画像
	handtype_ = handtype;		//属性の数字
}





Status_CardType CardType[CARDTYPE_MAX];		//カードの種類のclass
Status_HandType HandType[HANDTYPE_MAX];		//属性(じゃんけんの手)のclass


void GraphLoad_Start() {			//GameStartでLoadする画像読み込み用


	Cursor_hdl = LoadGraph("graphics/mygame/cursor.png");

	TextWindow_hdl = LoadGraph("graphics/mygame/textwindow.png");

	Poster_Text_gpc_hdl = LoadGraph("graphics/mygame/poster_text.png");							//文字表示の紙の画像用

	wallpaper[WALLPAPER_TITLE] = LoadGraph("graphics/mygame/wallpaper/angel.png");		//タイトル画面の背景

	wallpaper[WALLPAPER_STAGE1] = LoadGraph("graphics/mygame/wallpaper/forest.png");		//Stage1の背景

	wallpaper[WALLPAPER_STAGE2] = LoadGraph("graphics/mygame/wallpaper/otsukimi.png");		//Stage2の背景

	wallpaper[WALLPAPER_STAGE3] = LoadGraph("graphics/mygame/wallpaper/cave.jpg");			//Stage3の背景

	wallpaper[WALLPAPER_STAGE4] = LoadGraph("graphics/mygame/wallpaper/hinode.png");		//Stage4の背景

}


void CardGraphLoad() {				//カード関係の画像読み込み用

//デバッグ用ーーーーーーー

		CardBase_gpc_hdl = LoadGraph("graphics/mygame/character/poster.png");						//カードのベースの画像

		Poster_Text_gpc_hdl = LoadGraph("graphics/mygame/poster_text.png");							//文字表示の紙の画像用

		////wallpaper_gpc_hdl_battle = LoadGraph("graphics/mygame/wallpaper.jpg");						//バトル時の背景

		CharaBack_paper_dpc_hdl = LoadGraph("graphics/mygame/character/poster.png");				//キャラクターの背景の画像

		EnemyBack_paper_dpc_hdl = LoadGraph("graphics/mygame/Enemy/poster_enemy.png");				//敵の背景の画像

		target_gpc_hdl = LoadGraph("graphics/mygame/Enemy/target.png");								//メニュー画面で表示させるターゲット


		int temp_cardtype[CARDTYPE_MAX] = { 0 };	//カードの画像を一時的に入れる用の配列

		//カードの種類の情報
		temp_cardtype[CARDTYPE_SUMMON] = LoadGraph("graphics/mygame/cardgraph/summon.png");		//カード：召喚の画像
		CardType[CARDTYPE_SUMMON].init("召喚", temp_cardtype[CARDTYPE_SUMMON], CARDTYPE_SUMMON);

		temp_cardtype[CARDTYPE_SKILL] = LoadGraph("graphics/mygame/cardgraph/skill.png");		//カード：スキルの画像
		CardType[CARDTYPE_SKILL].init("スキル", temp_cardtype[CARDTYPE_SKILL], CARDTYPE_SKILL);

		temp_cardtype[CARDTYPE_ITEM] = LoadGraph("graphics/mygame/cardgraph/item.png");			//カード：アイテムの画像
		CardType[CARDTYPE_ITEM].init("アイテム", temp_cardtype[CARDTYPE_ITEM], CARDTYPE_ITEM);

		int temp_handtype[HANDTYPE_MAX] = { 0 };

		temp_handtype[HANDTYPE_ROCK] = LoadGraph("graphics/mygame/handtype/handtype_rock.png");				//属性：グーの画像
		HandType[HANDTYPE_ROCK].init("グー", temp_handtype[HANDTYPE_ROCK], HANDTYPE_ROCK);

		temp_handtype[HANDTYPE_PAPER] = LoadGraph("graphics/mygame/handtype/handtype_paper.png");			//属性：パーの画像
		HandType[HANDTYPE_PAPER].init("パー", temp_handtype[HANDTYPE_PAPER], HANDTYPE_PAPER);

		temp_handtype[HANDTYPE_SCISSORS] = LoadGraph("graphics/mygame/handtype/handtype_scissors.png");		//属性：チョキの画像
		HandType[HANDTYPE_SCISSORS].init("チョキ", temp_handtype[HANDTYPE_SCISSORS], HANDTYPE_SCISSORS);

	//}


	//山札にカードの種類ごとに対応した画像を入れる処理
	for (int j = 0; j < DeckCount_Player;  j++) {

		int i = j % CARDTYPE_MAX;

		DeckCard_hdl_Player[j] = CardType[i].gpc_hdl_;			
		
		//画像の他にカードの種類を入れる用の配列をつくる
			
	}



	////山札にカードの種類ごとに対応した画像を入れる処理
	//for (int j = 0; j++; j < DeckCount_Player) {
	//	for (int i = 0; i++; i < CARDTYPE_MAX) {
	//		if (CardType_Deck[j] = i) {
	//			DeckCard_hdl_Player[j] = CardType[i].gpc_hdl_;
	//		}
	//	}
	//}

}

tnl::Vector3 EnemyHAND_GPC_POS = { PLAYER_HAND_FIRST_POS.x, PLAYER_HAND_FIRST_POS.y - 250, 0};		//敵の選択した手を表示する位置

void CardGraphDraw() {


		SetDrawBright(255, 255, 255);		// 後ろの画面を暗くする

		if (Item_Analysis_flag) {
			DrawRotaGraphF(EnemyHAND_GPC_POS.x, EnemyHAND_GPC_POS.y, 0.4f, 0, CardBase_gpc_hdl, true);				//敵の手の背景を表示させる
			DrawRotaGraph(EnemyHAND_GPC_POS.x, EnemyHAND_GPC_POS.y, 0.25f, 0, HandType[action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_].gpc_hdl_, true);		//手札のカードの属性を表示させる

			DrawStringEx(EnemyHAND_GPC_POS.x - 45, EnemyHAND_GPC_POS.y + 60, 0, "敵の手：%s", HandType[action_Enemy[EnemyInStage][ActionNumber_Enemy].handtype_].name_.c_str());		//カードの名前を表示させる
		}

		for (int i = 0; i < HandCount_Player; i++) {
			DrawRotaGraphF(PLAYER_HAND_FIRST_POS.x + i * HAND_SPACE, PLAYER_HAND_FIRST_POS.y, 0.4f, 0, CardBase_gpc_hdl, true);				//手札のカードの背景を表示させる

			DrawRotaGraphF(PLAYER_HAND_FIRST_POS.x + i * HAND_SPACE, PLAYER_HAND_FIRST_POS.y, 0.3f, 0, CardType[CardType_Hand[i].cardtype_].gpc_hdl_, true);		//手札のカードの画像を表示させる


			DrawRotaGraph(PLAYER_HAND_FIRST_POS.x + 55 + i * HAND_SPACE, PLAYER_HAND_FIRST_POS.y - 70, 0.15f, 0, HandType[CardType_Hand[i].handtype_].gpc_hdl_, true);		//手札のカードの属性を表示させる

			DrawStringEx(PLAYER_HAND_FIRST_POS.x - 35 + i * HAND_SPACE, PLAYER_HAND_FIRST_POS.y + 60, 0, "%s", CardType[CardType_Hand[i].cardtype_].name_.c_str());		//カードの名前を表示させる

		}

}
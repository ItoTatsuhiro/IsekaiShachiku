#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "character.h"
#include "scene_CardGameMain.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "scene_GraphDraw.h"
#include "Sound.h"


const tnl::Vector3 TEXT_MENU_TITLE_POS = { 500, 60, 0 };		//ステージ選択のタイトルの文字の座標
const tnl::Vector3 TEXT_STAGESEL_POS = { 100, 250, 0 };			//ステージ選択の文字の座標

int Select_Enemy = ENEMY_YOU;		//メニュー画面で選択する敵(ステージ)用の変数


void scene_Menu() {

	DrawRotaGraph(640, 360, 0.7f, 0, wallpaper[Select_Enemy + 1], true);		//選択中のステージによって表示中の背景を変える


	DrawRotaGraph(TEXT_MENU_TITLE_POS.x + 120, TEXT_MENU_TITLE_POS.y + 20, 0.4f, 0, Poster_Text_gpc_hdl, true);
	SetFontSize(30);
	DrawStringEx(TEXT_MENU_TITLE_POS.x, TEXT_MENU_TITLE_POS.y, 0, "エネミーセレクト");


	DrawRotaGraph(TEXT_STAGESEL_POS.x + 150, TEXT_STAGESEL_POS.y + ENEMY_MAX / 2 * 80, 1.0f, 0, CharaBack_paper_dpc_hdl, true);		//Stage選択の文字の背景画像

	//ステージの文字を記載
	SetFontSize(25);
	for (int i = 0; i < ENEMY_MAX; i++) {
		DrawStringEx(TEXT_STAGESEL_POS.x, TEXT_STAGESEL_POS.y + i * 100, 0, "STAGE%d：%s", i + 1, Enemy[i].name_.c_str());
	}

	//カーソルの表示
	DrawRotaGraph(TEXT_STAGESEL_POS.x - 30, TEXT_STAGESEL_POS.y + 15 + 100 * Select_Enemy, 1.0f, M_PI * 3 / 4, Cursor_hdl, true);


	DrawRotaGraph(TEXT_STAGESEL_POS.x + 750, TEXT_STAGESEL_POS.y + ENEMY_MAX / 2 * 80, 1.2f, 0, EnemyBack_paper_dpc_hdl, true);				//Stage選択の敵情報の背景画像

	DrawRotaGraph(TEXT_STAGESEL_POS.x + 900, TEXT_STAGESEL_POS.y + ENEMY_MAX / 2 * 80, 0.6f, 0, Enemy[Select_Enemy].gpc_hdl_, true);		//Stage選択の敵のキャラクター画像

	DrawRotaGraph(TEXT_STAGESEL_POS.x + 900, TEXT_STAGESEL_POS.y + ENEMY_MAX / 2 * 80, 1.0f, 0, target_gpc_hdl, true);						//Stage選択の敵のキャラクターのターゲット画像

	SetFontSize(30);
	DrawStringEx(TEXT_STAGESEL_POS.x + 580, TEXT_STAGESEL_POS.y - 50, 0, "～TARGET INFORMATION～");		//

	DrawStringEx(TEXT_STAGESEL_POS.x + 450, TEXT_STAGESEL_POS.y, 0, "名前：%s", Enemy[Select_Enemy].name_.c_str());				//敵情報：名前

	DrawStringEx(TEXT_STAGESEL_POS.x + 450, TEXT_STAGESEL_POS.y + 100, 0, "HP：%d", Enemy[Select_Enemy].hp_);					//敵情報：HP

	DrawStringEx(TEXT_STAGESEL_POS.x + 450, TEXT_STAGESEL_POS.y + 200, 0, "ATTACK：%d", Enemy[Select_Enemy].atk_);				//敵情報：攻撃力

	SetFontSize(20);
	DrawStringEx(TEXT_STAGESEL_POS.x + 450, TEXT_STAGESEL_POS.y + 300, 0, "情報：\n %s", Enemy[Select_Enemy].ex_.c_str());				//敵情報：フレーバーテキスト




	if (select_check_flag) {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			Select_Enemy++;
			sound_se_sel();

			if (Select_Enemy > ENEMY_MAX - 1) {						//NOで↓を押したときYESに戻す
				Select_Enemy = ENEMY_YOU;
				
			}
		}

		//↓を押したときに選択中のカードを一つ左にずらす
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			Select_Enemy--;
			sound_se_sel();

			if (Select_Enemy < ENEMY_YOU) {						//YESで↑を押したときNOに戻す
				Select_Enemy = (ENEMY_MAX - 1);
			}
		}
	}


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

		select_check_flag = false;
		CardGameScene = 0;
		sound_se_enter();

		EnemyInStage = Select_Enemy;			//選択した敵が出てくる状態にする
		CardGamePlay = true;
		//sceneCardGame_Start();
		scene_GameMain = GAMEMAIN_CARDGAME;		//カードゲームシーンに遷移

	}



}
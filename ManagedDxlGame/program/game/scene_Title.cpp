#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "scene_GraphDraw.h"
#include "scene_CardGameMain.h"
#include "Sound.h"


void scene_Title() {

	DrawRotaGraph(640, 360, 0.7f, 0, wallpaper[WALLPAPER_TITLE], true);

	DrawRotaGraph(640, 300, 1.0f, 0, Poster_Text_gpc_hdl, true);

	SetFontSize(80);
	DrawStringEx(450, 230, 0, "異世界社畜");

	SetFontSize(40);
	DrawStringEx(300, 350, 0, "〜魔王討伐から始める脱サラへの道〜");

	SetFontSize(25);
	DrawStringEx(450, 550, 0, "Enterキーを押してください");

	select_check_flag = true;

	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

		sceneCardGame_Start();
		sound_se_enter();
		scene_GameMain = GAMEMAIN_MENU;

	}

}
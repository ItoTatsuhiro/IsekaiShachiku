#include <time.h>
#include <string>
#include "../dxlib_ext/dxlib_ext.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "gm_main.h"
#include "scene_CardDraw.h"
#include "scene_Check.h"
#include "scene_CardGameMain.h"
#include "character.h"
#include "scene_GraphDraw.h"
#include "scene_Title.h"
#include "scene_Menu.h"
#include "Sound.h"


int scene_GameMain = 0;		//ゲーム全体のシーン


//------------------------------------------------------------------------------------------------------------
// ゲーム起動時に１度だけ実行されます
void gameStart(){
	srand(time(0));

	//sceneCardGame_Start();

	GraphLoad_Start();


}

//------------------------------------------------------------------------------------------------------------
// 毎フレーム実行されます
void gameMain(float delta_time) {

	//enum {
	//	GAMEMAIN_TITLE,
	//	GAMEMAIN_MENU,
	//	GAMEMAIN_CARDGAME,
	//	
	//};


	Sound_bgm();

	switch (scene_GameMain) {
	case GAMEMAIN_TITLE:

		sound_se_Load();
		scene_Title();

		break;

	case GAMEMAIN_MENU:

		scene_Menu();

		break;

	case GAMEMAIN_CARDGAME:

		sceneCardGameMain();

		break;




	}
}

//------------------------------------------------------------------------------------------------------------
// ゲーム終了時に１度だけ実行されます
void gameEnd() {

}

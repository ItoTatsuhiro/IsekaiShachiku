#pragma once
void gameStart();
void gameMain( float delta_time );
void gameEnd();

extern int scene_GameMain;		//ゲーム全体のシーン

enum {
	GAMEMAIN_TITLE,			//タイトルシーン
	GAMEMAIN_MENU,			//メニュー画面
	GAMEMAIN_CARDGAME,		//カードゲームのシーン
	
};

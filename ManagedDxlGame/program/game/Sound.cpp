#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "scene_CardGameMain.h"
#include "scene_Title.h"
#include "character.h"
#include "scene_Menu.h"

enum {
	BGM_TITLE,					//タイトル画面のBGM
	BGM_MENU,					//メニュー画面のBGM
	BGM_CARDGAME,				//カードゲームのBGM
	BGM_MAX						//BGMの数
};

int sound_bgm_hdl[BGM_MAX];



void Sound_bgm() {

//サウンドのロード,再生


	switch (scene_GameMain) {
	case GAMEMAIN_TITLE:

		if (sound_bgm_hdl[BGM_CARDGAME] != 0) {
			DeleteSoundMem(sound_bgm_hdl[BGM_CARDGAME]);		//メニュー画面用の曲を止める(消去する)
			sound_bgm_hdl[BGM_CARDGAME] = 0;
		}

		if (!sound_bgm_hdl[BGM_TITLE]) {
			sound_bgm_hdl[BGM_TITLE] = LoadSoundMem("sound/bgm/Short_RPG_02(title).mp3");		//タイトル画面用のBGMをロード
			ChangeVolumeSoundMem(60, sound_bgm_hdl[BGM_TITLE]);
		}

		PlaySoundMem(sound_bgm_hdl[BGM_TITLE], DX_PLAYTYPE_LOOP, false);

		break;

	case GAMEMAIN_MENU:

		if (sound_bgm_hdl[BGM_TITLE] != 0) {
			StopSoundMem(sound_bgm_hdl[BGM_TITLE]);		//タイトル用の曲を止める(消去する)
			sound_bgm_hdl[BGM_TITLE] = 0;
		}

		if (!sound_bgm_hdl[BGM_MENU]) {
			sound_bgm_hdl[BGM_MENU] = LoadSoundMem("sound/bgm/Short_RPG_04(menu).mp3");		//タイトル画面用のBGMをロード
			ChangeVolumeSoundMem(60, sound_bgm_hdl[BGM_MENU]);
		}

		PlaySoundMem(sound_bgm_hdl[BGM_MENU], DX_PLAYTYPE_LOOP, false);

		break;

	case GAMEMAIN_CARDGAME:


		if (sound_bgm_hdl[BGM_MENU] != 0) {
			DeleteSoundMem(sound_bgm_hdl[BGM_MENU]);		//メニュー画面用の曲を止める(消去する)
			sound_bgm_hdl[BGM_MENU] = 0;
		}

		if (!sound_bgm_hdl[BGM_CARDGAME]) {
			if (Select_Enemy == ENEMY_YOU) {
				sound_bgm_hdl[BGM_CARDGAME] = LoadSoundMem("sound/bgm/Short_mistery_017(cardgame_doppel).mp3");		//カードゲーム(敵：ドッペルゲンガー)用のBGMをロード
			}
			else if (Select_Enemy == ENEMY_DEVIL) {
				sound_bgm_hdl[BGM_CARDGAME] = LoadSoundMem("sound/bgm/Short_Game_Fusion_04(cardgame_devil).mp3");		//カードゲーム(敵：悪魔)用のBGMをロード
			}
			else if (Select_Enemy == ENEMY_DRAGON) {
				sound_bgm_hdl[BGM_CARDGAME] = LoadSoundMem("sound/bgm/RPG_Battle_01(cardgame_dragon).mp3");		//タイトル画面用のBGMをロード
			}
			else if (Select_Enemy == ENEMY_DEVILKING) {
				sound_bgm_hdl[BGM_CARDGAME] = LoadSoundMem("sound/bgm/Cinema_01(cardgame_devilking).mp3");		//タイトル画面用のBGMをロード
			}
			ChangeVolumeSoundMem(60, sound_bgm_hdl[BGM_CARDGAME]);
		}
		PlaySoundMem(sound_bgm_hdl[BGM_CARDGAME], DX_PLAYTYPE_LOOP, false);

		break;

	}

}

enum {
	SE_CARD_PASS,			//カードを配るときのSE
	SE_CARD_PUT,			//カードを置くときのSE
	SE_SEL,					//選択肢を選択するときのSE				
	SE_ENTER,				//選択肢を決定したときのSE
	SE_MAX					//SEの数
};

int sound_se_hdl[SE_MAX] = { 0 };

void sound_se_Load() {

	if (sound_se_hdl[SE_CARD_PASS] == 0) {
		
		sound_se_hdl[SE_CARD_PASS] = LoadSoundMem("sound/se/cardpass.mp3");

		sound_se_hdl[SE_CARD_PUT] = LoadSoundMem("sound/se/cardput.mp3");

		sound_se_hdl[SE_SEL] = LoadSoundMem("sound/se/sel.mp3");

		sound_se_hdl[SE_ENTER] = LoadSoundMem("sound/se/enter.mp3");

		for (int i = 0; i < SE_MAX; i++) {
			ChangeVolumeSoundMem(100, sound_se_hdl[i]);
		}
	}
}

void sound_se_cardpass() {
	PlaySoundMem(sound_se_hdl[SE_CARD_PASS], DX_PLAYTYPE_BACK);		//カードを配るSEを再生する
}

void sound_se_cardput() {
	PlaySoundMem(sound_se_hdl[SE_CARD_PUT], DX_PLAYTYPE_BACK);		//カードを置くSEを再生する
}

void sound_se_sel() {
	PlaySoundMem(sound_se_hdl[SE_SEL], DX_PLAYTYPE_BACK);		//選択肢を選択する際のseを再生する
}

void sound_se_enter() {
	PlaySoundMem(sound_se_hdl[SE_ENTER], DX_PLAYTYPE_BACK);		//選択肢を決定するSEを再生する
}
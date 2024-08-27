#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "scene_CardGameMain.h"
#include "scene_Title.h"
#include "character.h"
#include "scene_Menu.h"

enum {
	BGM_TITLE,					//�^�C�g����ʂ�BGM
	BGM_MENU,					//���j���[��ʂ�BGM
	BGM_CARDGAME,				//�J�[�h�Q�[����BGM
	BGM_MAX						//BGM�̐�
};

int sound_bgm_hdl[BGM_MAX];



void Sound_bgm() {

//�T�E���h�̃��[�h,�Đ�


	switch (scene_GameMain) {
	case GAMEMAIN_TITLE:

		if (sound_bgm_hdl[BGM_CARDGAME] != 0) {
			DeleteSoundMem(sound_bgm_hdl[BGM_CARDGAME]);		//���j���[��ʗp�̋Ȃ��~�߂�(��������)
			sound_bgm_hdl[BGM_CARDGAME] = 0;
		}

		if (!sound_bgm_hdl[BGM_TITLE]) {
			sound_bgm_hdl[BGM_TITLE] = LoadSoundMem("sound/bgm/Short_RPG_02(title).mp3");		//�^�C�g����ʗp��BGM�����[�h
			ChangeVolumeSoundMem(60, sound_bgm_hdl[BGM_TITLE]);
		}

		PlaySoundMem(sound_bgm_hdl[BGM_TITLE], DX_PLAYTYPE_LOOP, false);

		break;

	case GAMEMAIN_MENU:

		if (sound_bgm_hdl[BGM_TITLE] != 0) {
			StopSoundMem(sound_bgm_hdl[BGM_TITLE]);		//�^�C�g���p�̋Ȃ��~�߂�(��������)
			sound_bgm_hdl[BGM_TITLE] = 0;
		}

		if (!sound_bgm_hdl[BGM_MENU]) {
			sound_bgm_hdl[BGM_MENU] = LoadSoundMem("sound/bgm/Short_RPG_04(menu).mp3");		//�^�C�g����ʗp��BGM�����[�h
			ChangeVolumeSoundMem(60, sound_bgm_hdl[BGM_MENU]);
		}

		PlaySoundMem(sound_bgm_hdl[BGM_MENU], DX_PLAYTYPE_LOOP, false);

		break;

	case GAMEMAIN_CARDGAME:


		if (sound_bgm_hdl[BGM_MENU] != 0) {
			DeleteSoundMem(sound_bgm_hdl[BGM_MENU]);		//���j���[��ʗp�̋Ȃ��~�߂�(��������)
			sound_bgm_hdl[BGM_MENU] = 0;
		}

		if (!sound_bgm_hdl[BGM_CARDGAME]) {
			if (Select_Enemy == ENEMY_YOU) {
				sound_bgm_hdl[BGM_CARDGAME] = LoadSoundMem("sound/bgm/Short_mistery_017(cardgame_doppel).mp3");		//�J�[�h�Q�[��(�G�F�h�b�y���Q���K�[)�p��BGM�����[�h
			}
			else if (Select_Enemy == ENEMY_DEVIL) {
				sound_bgm_hdl[BGM_CARDGAME] = LoadSoundMem("sound/bgm/Short_Game_Fusion_04(cardgame_devil).mp3");		//�J�[�h�Q�[��(�G�F����)�p��BGM�����[�h
			}
			else if (Select_Enemy == ENEMY_DRAGON) {
				sound_bgm_hdl[BGM_CARDGAME] = LoadSoundMem("sound/bgm/RPG_Battle_01(cardgame_dragon).mp3");		//�^�C�g����ʗp��BGM�����[�h
			}
			else if (Select_Enemy == ENEMY_DEVILKING) {
				sound_bgm_hdl[BGM_CARDGAME] = LoadSoundMem("sound/bgm/Cinema_01(cardgame_devilking).mp3");		//�^�C�g����ʗp��BGM�����[�h
			}
			ChangeVolumeSoundMem(60, sound_bgm_hdl[BGM_CARDGAME]);
		}
		PlaySoundMem(sound_bgm_hdl[BGM_CARDGAME], DX_PLAYTYPE_LOOP, false);

		break;

	}

}

enum {
	SE_CARD_PASS,			//�J�[�h��z��Ƃ���SE
	SE_CARD_PUT,			//�J�[�h��u���Ƃ���SE
	SE_SEL,					//�I������I������Ƃ���SE				
	SE_ENTER,				//�I���������肵���Ƃ���SE
	SE_MAX					//SE�̐�
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
	PlaySoundMem(sound_se_hdl[SE_CARD_PASS], DX_PLAYTYPE_BACK);		//�J�[�h��z��SE���Đ�����
}

void sound_se_cardput() {
	PlaySoundMem(sound_se_hdl[SE_CARD_PUT], DX_PLAYTYPE_BACK);		//�J�[�h��u��SE���Đ�����
}

void sound_se_sel() {
	PlaySoundMem(sound_se_hdl[SE_SEL], DX_PLAYTYPE_BACK);		//�I������I������ۂ�se���Đ�����
}

void sound_se_enter() {
	PlaySoundMem(sound_se_hdl[SE_ENTER], DX_PLAYTYPE_BACK);		//�I���������肷��SE���Đ�����
}
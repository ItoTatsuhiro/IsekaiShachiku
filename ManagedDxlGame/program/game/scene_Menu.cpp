#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "character.h"
#include "scene_CardGameMain.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "scene_GraphDraw.h"
#include "Sound.h"


const tnl::Vector3 TEXT_MENU_TITLE_POS = { 500, 60, 0 };		//�X�e�[�W�I���̃^�C�g���̕����̍��W
const tnl::Vector3 TEXT_STAGESEL_POS = { 100, 250, 0 };			//�X�e�[�W�I���̕����̍��W

int Select_Enemy = ENEMY_YOU;		//���j���[��ʂőI������G(�X�e�[�W)�p�̕ϐ�


void scene_Menu() {

	DrawRotaGraph(640, 360, 0.7f, 0, wallpaper[Select_Enemy + 1], true);		//�I�𒆂̃X�e�[�W�ɂ���ĕ\�����̔w�i��ς���


	DrawRotaGraph(TEXT_MENU_TITLE_POS.x + 120, TEXT_MENU_TITLE_POS.y + 20, 0.4f, 0, Poster_Text_gpc_hdl, true);
	SetFontSize(30);
	DrawStringEx(TEXT_MENU_TITLE_POS.x, TEXT_MENU_TITLE_POS.y, 0, "�G�l�~�[�Z���N�g");


	DrawRotaGraph(TEXT_STAGESEL_POS.x + 150, TEXT_STAGESEL_POS.y + ENEMY_MAX / 2 * 80, 1.0f, 0, CharaBack_paper_dpc_hdl, true);		//Stage�I���̕����̔w�i�摜

	//�X�e�[�W�̕������L��
	SetFontSize(25);
	for (int i = 0; i < ENEMY_MAX; i++) {
		DrawStringEx(TEXT_STAGESEL_POS.x, TEXT_STAGESEL_POS.y + i * 100, 0, "STAGE%d�F%s", i + 1, Enemy[i].name_.c_str());
	}

	//�J�[�\���̕\��
	DrawRotaGraph(TEXT_STAGESEL_POS.x - 30, TEXT_STAGESEL_POS.y + 15 + 100 * Select_Enemy, 1.0f, M_PI * 3 / 4, Cursor_hdl, true);


	DrawRotaGraph(TEXT_STAGESEL_POS.x + 750, TEXT_STAGESEL_POS.y + ENEMY_MAX / 2 * 80, 1.2f, 0, EnemyBack_paper_dpc_hdl, true);				//Stage�I���̓G���̔w�i�摜

	DrawRotaGraph(TEXT_STAGESEL_POS.x + 900, TEXT_STAGESEL_POS.y + ENEMY_MAX / 2 * 80, 0.6f, 0, Enemy[Select_Enemy].gpc_hdl_, true);		//Stage�I���̓G�̃L�����N�^�[�摜

	DrawRotaGraph(TEXT_STAGESEL_POS.x + 900, TEXT_STAGESEL_POS.y + ENEMY_MAX / 2 * 80, 1.0f, 0, target_gpc_hdl, true);						//Stage�I���̓G�̃L�����N�^�[�̃^�[�Q�b�g�摜

	SetFontSize(30);
	DrawStringEx(TEXT_STAGESEL_POS.x + 580, TEXT_STAGESEL_POS.y - 50, 0, "�`TARGET INFORMATION�`");		//

	DrawStringEx(TEXT_STAGESEL_POS.x + 450, TEXT_STAGESEL_POS.y, 0, "���O�F%s", Enemy[Select_Enemy].name_.c_str());				//�G���F���O

	DrawStringEx(TEXT_STAGESEL_POS.x + 450, TEXT_STAGESEL_POS.y + 100, 0, "HP�F%d", Enemy[Select_Enemy].hp_);					//�G���FHP

	DrawStringEx(TEXT_STAGESEL_POS.x + 450, TEXT_STAGESEL_POS.y + 200, 0, "ATTACK�F%d", Enemy[Select_Enemy].atk_);				//�G���F�U����

	SetFontSize(20);
	DrawStringEx(TEXT_STAGESEL_POS.x + 450, TEXT_STAGESEL_POS.y + 300, 0, "���F\n %s", Enemy[Select_Enemy].ex_.c_str());				//�G���F�t���[�o�[�e�L�X�g




	if (select_check_flag) {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			Select_Enemy++;
			sound_se_sel();

			if (Select_Enemy > ENEMY_MAX - 1) {						//NO�Ł����������Ƃ�YES�ɖ߂�
				Select_Enemy = ENEMY_YOU;
				
			}
		}

		//�����������Ƃ��ɑI�𒆂̃J�[�h������ɂ��炷
		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_UP)) {
			Select_Enemy--;
			sound_se_sel();

			if (Select_Enemy < ENEMY_YOU) {						//YES�Ł����������Ƃ�NO�ɖ߂�
				Select_Enemy = (ENEMY_MAX - 1);
			}
		}
	}


	if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

		select_check_flag = false;
		CardGameScene = 0;
		sound_se_enter();

		EnemyInStage = Select_Enemy;			//�I�������G���o�Ă����Ԃɂ���
		CardGamePlay = true;
		//sceneCardGame_Start();
		scene_GameMain = GAMEMAIN_CARDGAME;		//�J�[�h�Q�[���V�[���ɑJ��

	}



}
#pragma once
void gameStart();
void gameMain( float delta_time );
void gameEnd();

extern int scene_GameMain;		//�Q�[���S�̂̃V�[��

enum {
	GAMEMAIN_TITLE,			//�^�C�g���V�[��
	GAMEMAIN_MENU,			//���j���[���
	GAMEMAIN_CARDGAME,		//�J�[�h�Q�[���̃V�[��
	
};

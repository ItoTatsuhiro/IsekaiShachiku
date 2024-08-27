#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "scene_CardDraw.h"



//��D�ƃf�b�L�̃J�[�h���m�F����e�X�g�p�̊֐�
void CardCheck() {

	if (DeckCount_Player > 0) {

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_RETURN)) {

			for (int i = 0; i < 5; i++) {
				sceneCardGame_CardDraw_Player();
			}
		}

		if (tnl::Input::IsKeyDownTrigger(eKeys::KB_DOWN)) {
			sceneCardGame_CardDraw_Player();
		}
	}

	DrawStringEx(50, 50, -1, "�v���C���[�f�b�L��");
	DrawStringEx(850, 50, -1, "�R���s���[�^�[�f�b�L��");

	DrawStringEx(250, 600, -1, "�v���C���[��D��");
	DrawStringEx(250, 100, -1, "cpu��D��");

	for (int i = 0; i < HandCount_Player; i++)
	{
		DrawRotaGraphF(250 + i * 50, 650, 0.25f, 0, HandCard_hdl_Player[i], true);		//�v���C���[�̎�D��\��������

		//DrawRotaGraphF(250 + i * 50, 150, 0.25f, 0, HandCard_Cpu[i], true);			//cpu�̎�D��\��������
	}

	for (int i = 0; i < DECK_VOLUME; i++) {

		int DeckCardCount = i + 1;

		//DrawStringEx(300, 100 + i * 50, -1, "�R�D%d���ڂ͉��ł�", DeckCardCount);
		DrawRotaGraphF(50, 100 + i * 50, 0.25f, 0, DeckCard_hdl_Player[i], true);

		//DrawStringEx(800, 100 + i * 50, -1, "�R�D%d���ڂ͉��ł�", DeckCardCount);
		//DrawRotaGraphF(850, 100 + i * 50, 0.25f, 0, Deck_hdl_Cpu[i], true);
	}

	DrawStringEx(50, 600, -1, "�R�D�̎c�薇����%d�ł�", DeckCount_Player);
	DrawStringEx(50, 650, -1, "��D�̎c�薇���� %d�ł�", HandCount_Player);

	//DrawStringEx(850, 600, -1, "�R�D�̎c�薇����%d�ł�", DeckCount_Cpu);
	//DrawStringEx(850, 650, -1, "��D�̎c�薇����%d�ł�", HandCount_Cpu);



}

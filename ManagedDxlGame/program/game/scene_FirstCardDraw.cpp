//#include "../dxlib_ext/dxlib_ext.h"
//#include "gm_main.h"
//#include "scene_CardDraw.h"
//
//
//int PlayerDeck_hdl[DECK_VOLUME];			//�v���C���[�̎R�D�p�̔z��
//int PlayerDeckCount = DECK_VOLUME;			//�v���[���[�̎R�D�̎c�薇��
//int PlayerHandCard[DECK_VOLUME] = { 0 };	//�v���C���[�̎�D�p�̔z��
//int PlayerHandCount = 0;					//�v���C���[�̎�D����
//
//int CpuDeck_hdl[DECK_VOLUME];				//cpu�̎R�D�p�̔z��
//int CpuDeckCount = DECK_VOLUME;				//cpu�̎R�D�̎c�薇��
//int CpuHandCard[DECK_VOLUME] = { 0 };		//cpu�̎�D�p�̔z��
//int CpuHandCount = 0;						//cpu�̎�D����
//
//
//
//
////����̃v���C���[�p��D���d���Ȃ��z��p�̊֐�
//void sceneFirstDraw() {
//
//
//
//	//������D�̖������v���C���[�̎R�D����J�[�h������
//	for (int i = 0; i < HAND_VOLUME; i++) {
//
//		int CardNumber = rand() % (PlayerDeckCount);
//		PlayerHandCard[PlayerDeckCount] = PlayerDeck_hdl[CardNumber];
//
//		for (int j = 0; j < DECK_VOLUME; j++) {
//
//			if (j >= CardNumber) {
//
//				PlayerDeck_hdl[j] = PlayerDeck_hdl[j + 1];
//
//			}
//
//		}
//
//		PlayerDeckCount --;	// �v���C���[�̎c��R�D���������炷
//		PlayerHandCount ++;	// �v���C���[�̎�D�����𑝂₷
//
//	}
//
//
//	//�v���C���[�̎R�D�̈������J�[�h��null�ɂ���
//	for (int i = 0; i < HAND_VOLUME; i++) {
//
//		PlayerDeck_hdl[i + (DECK_VOLUME - HAND_VOLUME)] = NULL;
//
//	}
//
//	//������D�̖�����cpu�̎R�D����J�[�h������
//	for (int i = 0; i < HAND_VOLUME; i++) {
//
//		int CardNumber = rand() % (DECK_VOLUME - i);
//		CpuHandCard[i] = CpuDeck_hdl[CardNumber];
//
//		for (int j = 0; j < DECK_VOLUME; j++) {
//
//			if (j >= CardNumber) {
//
//				CpuDeck_hdl[j] = CpuDeck_hdl[j + 1];
//
//			}
//
//		}
//
//		CpuDeckCount--;	//cpu�̎c��R�D���������炷
//		CpuHandCount++;	//cpu�̎�D�����𑝂₷
//	}
//
//	//cpu�̎R�D�̈������J�[�h��null�ɂ���
//	for (int i = 0; i < HAND_VOLUME; i++) {
//
//		CpuDeck_hdl[i + (DECK_VOLUME - HAND_VOLUME)] = NULL;
//
//	}
//
//}
//
//
//
//

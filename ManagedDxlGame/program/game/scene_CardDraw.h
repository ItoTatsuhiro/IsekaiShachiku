#pragma once

void sceneCardGame_CardDraw();
void sceneCardGame_CardDraw_Player();
void sceneCardGame_CardDraw_Cpu();

const int HAND_VOLUME = 5;						// ������D����
const int DECK_VOLUME = 10;						// �����R�D����

extern int wallpaper_gpc_hdl_battle;			//�퓬���̔w�i�̉摜
extern int CharaBack_paper_dpc_hdl;				//�L�����N�^�[�̔w�i�̒��莆�̉摜
extern int EnemyBack_paper_dpc_hdl;				//�G�L�����N�^�[�̔w�i�̐ݒ�(���莆)

//extern int handtypenumber_random[DECK_VOLUME];			//�����_���ł���񂯂�̎�����肷��p�̕ϐ�

extern int DrawCardNumber;						//�����_���ň������J�[�h�̔ԍ�


extern int DeckCard_hdl_Player[DECK_VOLUME];	//�v���C���[�̎R�D�p�̉摜�p�̔z��
extern int DeckCount_Player;					//�v���C���[�̎R�D�̎c�薇��
extern int HandCard_hdl_Player[DECK_VOLUME];	//�v���C���[�̎�D�p�̔z��
extern int HandCount_Player;					//�v���C���[�̎�D����

extern int HandCard_Cardtype[DECK_VOLUME];	//�v���C���[�̎�D�̃J�[�h���R�D�̉��Ԗڂɕۊǂ���Ă�������ۑ�����z��


//extern int Deck_hdl_Cpu[DECK_VOLUME];			//cpu�̎R�D�p�̔z��
//extern int DeckCount_Cpu;						//cpu�̎R�D�̎c�薇��
//extern int HandCard_Cpu[DECK_VOLUME];			//cpu�̎�D�p�̔z��
//extern int HandCount_Cpu;						//cpu�̎�D����

extern int Deck_hdl[DECK_VOLUME];				//�R�D�p�̔z��(�ꎞ����p)
extern int DeckCount;							//�R�D�̎c�薇��(�ꎞ����p)
extern int HandCard[DECK_VOLUME];				//��D�p�̔z��(�ꎞ����p)
extern int HandCount;							//��D����(�ꎞ����p)

void sceneCardGraph();

void sceneFirstDraw();

void CardWrite();


#include "../dxlib_ext/dxlib_ext.h"
#include "gm_main.h"
#include "scene_CardDraw.h"



//手札とデッキのカードを確認するテスト用の関数
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

	DrawStringEx(50, 50, -1, "プレイヤーデッキ↓");
	DrawStringEx(850, 50, -1, "コンピューターデッキ↓");

	DrawStringEx(250, 600, -1, "プレイヤー手札↓");
	DrawStringEx(250, 100, -1, "cpu手札↓");

	for (int i = 0; i < HandCount_Player; i++)
	{
		DrawRotaGraphF(250 + i * 50, 650, 0.25f, 0, HandCard_hdl_Player[i], true);		//プレイヤーの手札を表示させる

		//DrawRotaGraphF(250 + i * 50, 150, 0.25f, 0, HandCard_Cpu[i], true);			//cpuの手札を表示させる
	}

	for (int i = 0; i < DECK_VOLUME; i++) {

		int DeckCardCount = i + 1;

		//DrawStringEx(300, 100 + i * 50, -1, "山札%d枚目は下です", DeckCardCount);
		DrawRotaGraphF(50, 100 + i * 50, 0.25f, 0, DeckCard_hdl_Player[i], true);

		//DrawStringEx(800, 100 + i * 50, -1, "山札%d枚目は下です", DeckCardCount);
		//DrawRotaGraphF(850, 100 + i * 50, 0.25f, 0, Deck_hdl_Cpu[i], true);
	}

	DrawStringEx(50, 600, -1, "山札の残り枚数は%dです", DeckCount_Player);
	DrawStringEx(50, 650, -1, "手札の残り枚数は %dです", HandCount_Player);

	//DrawStringEx(850, 600, -1, "山札の残り枚数は%dです", DeckCount_Cpu);
	//DrawStringEx(850, 650, -1, "手札の残り枚数は%dです", HandCount_Cpu);



}

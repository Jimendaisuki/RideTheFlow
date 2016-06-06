#include "MenuPanel.h"
#include "../../Def.h"
#include "../../graphic/Sprite.h"
#include "../../input/GamePad.h"
#include "../../input/Keyboard.h"
#include "../../math/Math.h"
#include "../../time/Time.h"

const Vector2 HD = Vector2(1920, 1080);
const Vector2 SCREEN_CENTER = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
const Vector2 RES_SIZE_1 = Vector2(175, 967);
const Vector2 RES_SIZE_2 = Vector2(1574, 967);
const Vector2 TEXT_SIZE = Vector2(150.0f, 700.0f);
const float MOVE_WIDTH = (RES_SIZE_2.x - RES_SIZE_1.x) / 2;
const float DELEY_TIME = 0.0f;

void MenuPanel::Initialize()
{
	/* 初期設定 */
	scale.x = (float)WINDOW_WIDTH  / HD.x;
	scale.y = (float)WINDOW_HEIGHT / HD.y;
	drawPosition = SCREEN_CENTER;

	time = 0;

	/* 巻物設定 */
	rollAlpha = 0;
	rollBakcAlpha = 0;
	size = Point::Zero;
	rect.left	= 0;
	rect.top	= 0;
	rect.right	= RES_SIZE_1.x;
	rect.bottom = RES_SIZE_1.y;
	
	/* テキスト設定 */
	textAlpha = 0;
	selectNum = 0;
	for (int i = 0; i < 3; i++)
	{
		selects[i] = 0;
	}

	/* マニュアル */
	nowPage = 1;
	prePage = 0;
	for (int i = 0; i < 4; i++)
	{
		pages[i] = 0.0f;
	}

	/* 実行用設定 */
	isAction = true;
	status = MENU_STATUS::BEGIN;
}

void MenuPanel::Update()
{
	if (!isAction) return;
	
	switch (status)
	{
	case BEGIN:		// 巻物が左に移動
		time += Time::DeltaTime;
		moveVec = MOVE_WIDTH * scale.x * bez.Get(CBezier::eSlow_Lv5, CBezier::eSlow_Lv5, Math::Clamp(time, 0.0f, 1.0f));
		drawPosition = SCREEN_CENTER - Vector2(moveVec, 0.0f);
		rollAlpha = time;
		if (time >= 1)
		{
			status = MENU_STATUS::OPEN;
			rollBakcAlpha = 1.0f;
			time = -DELEY_TIME;
		}
		break;
	case OPEN:		// 巻物開く
		time += Time::DeltaTime;
		moveVec = MOVE_WIDTH * scale.x * 2 * bez.Get(CBezier::eSlow_Lv5, CBezier::eSlow_Lv5, time);
		size = Point(moveVec / scale.x, 0) + RES_SIZE_1.ToPoint();
		rect.left = moveVec / scale.x;
		rect.right = rect.left + RES_SIZE_1.x;

		if (time >= 1.0f)
		{
			time = 1.0f;
			status = MENU_STATUS::SELECT;
		}
		break;
	case SELECT:	// セレクト
		// MANUAL → SELECT
		if (pages[prePage] > 0.0f)
		{
			pages[prePage] -= Time::DeltaTime;
			return;
		}
		// OPEN → SELECT
		if (textAlpha < 1.0f)
		{
			textAlpha += Time::DeltaTime;
			return;
		}

		// 選択肢によるアルファ変更
		for (int i = 0; i < 3; i++)
		{
			selects[i] = 0;
		}
		selects[selectNum] = 1;

		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LEFT))	selectNum++;
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::RIGHT))	selectNum--;
		if (selectNum > 2) selectNum = 0;
		if (selectNum < 0) selectNum = 2;

		// ステータス変更
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::N))
		{
			if (selectNum == 0)	status = MENU_STATUS::CLOSE;
			else if (selectNum == 1)
			{
				prePage = 0;
				nowPage = 1;
				status = MENU_STATUS::MANUAL;
			}
			else if (selectNum == 2) status = MENU_STATUS::CLOSE;
		}
		break;
	case MANUAL:	// 操作説明画面
		// SELECT → MANUAL
		if (textAlpha >= 0.0f)
		{
			textAlpha -= Time::DeltaTime * 2.0f;
			for (int i = 0; i < 3; i++)
			{
				selects[selectNum] = textAlpha;
			}
			return;
		}
		// フェードアウト
		if (pages[prePage] > 0.0f)
		{
			pages[prePage] -= Time::DeltaTime;
			return;
		}
		pages[prePage] = Math::Clamp(pages[prePage], 0.0f, 1.0f);
		// フェードイン
		if (pages[nowPage] < 1.0f) 
		{
			pages[nowPage] += Time::DeltaTime;
			break;
		}
		pages[nowPage] = Math::Clamp(pages[nowPage], 0.0f, 1.0f);

		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::B))
		{
			if (nowPage <= 1)
			{
				status = MENU_STATUS::SELECT;
				prePage = 1;
				nowPage = 0;
				return;
			}
			prePage = nowPage;
			nowPage--;
		}		
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::N))
		{
			if (nowPage > 3)
			{
				status = MENU_STATUS::SELECT;
				prePage = 4;
				nowPage = 1;
				return;
			}
			prePage = nowPage;
			nowPage++;
		}
		break;
	case CLOSE:		// 巻物閉じる
		if (textAlpha > 0.0f)
		{
			textAlpha -= Time::DeltaTime;
			for (int i = 0; i < 3; i++)
			{
				selects[i] -= Time::DeltaTime;
				selects[i] = Math::Clamp(selects[i], 0.0f, 1.0f);
			}
			return;
		}
		time -= Time::DeltaTime;

		moveVec = MOVE_WIDTH * scale.x * 2 * bez.Get(CBezier::eSlow_Lv5, CBezier::eSlow_Lv5, time);
		size = Point(moveVec / scale.x, 0) + RES_SIZE_1.ToPoint();
		rect.left = moveVec / scale.x;
		rect.right = rect.left + RES_SIZE_1.x;

		if (time <= 0.0f)
		{
			time = 0.0f;
			rollBakcAlpha = 0.0f;
			status = MENU_STATUS::END;
		}
		break;
	case END:		// フェードアウトから終了
		if (rollAlpha >= 0.0f) rollAlpha -= Time::DeltaTime;
		else isAction = false;
		break;
	default:
		isAction = false;
		break;
	}
}

void MenuPanel::Draw(Scene scene) const
{
	/* 巻物の描画 */
	Sprite::GetInstance().Draw(SPRITE_ID::MENU_ROLL_3_SPRITE, drawPosition + Vector2(moveVec, 0.0f), size, RES_SIZE_1 / 2, rollBakcAlpha, scale, 180.0f, true, false);
	Sprite::GetInstance().Draw(SPRITE_ID::MENU_ROLL_2_SPRITE, drawPosition, rect, RES_SIZE_1 / 2, rollAlpha, scale, 0.0f, true, false);
	Sprite::GetInstance().Draw(SPRITE_ID::MENU_ROLL_1_SPRITE, drawPosition, RES_SIZE_1 / 2, rollAlpha, scale, 0.0f);

	/* セレクト描画 */
	if (scene == Scene::Title) DrawMenu();
	else if (scene == Scene::GamePlay) DrawPause();

	/* マニュアル描画 */
	Sprite::GetInstance().Draw(SPRITE_ID::MANUAL_1_SPRITE, SCREEN_CENTER, RES_SIZE_2 / 2, pages[1], scale, 0.0f);
	Sprite::GetInstance().Draw(SPRITE_ID::MANUAL_2_SPRITE, SCREEN_CENTER, RES_SIZE_2 / 2, pages[2], scale, 0.0f);
	Sprite::GetInstance().Draw(SPRITE_ID::MANUAL_3_SPRITE, SCREEN_CENTER, RES_SIZE_2 / 2, pages[3], scale, 0.0f);
	Sprite::GetInstance().Draw(SPRITE_ID::MANUAL_4_SPRITE, SCREEN_CENTER, RES_SIZE_2 / 2, pages[4], scale, 0.0f);
}

void MenuPanel::DrawMenu() const
{
	/* テキストの描画 */
	Vector2 textDrawPos_s = Vector2(SCREEN_CENTER.x + (moveVec - SCREEN_CENTER.x) * 3.0f / 4.0f, WINDOW_HEIGHT / 5.0f);
	Sprite::GetInstance().Draw(SPRITE_ID::START_GAME_BACK_SPRITE, textDrawPos_s, Vector2(TEXT_SIZE.x / 2, 0.0f), textAlpha, scale, true, false);
	Vector2 textDrawPos_m = Vector2(SCREEN_CENTER.x + (moveVec - SCREEN_CENTER.x) * 1.0f / 4.0f, WINDOW_HEIGHT / 5.0f);
	Sprite::GetInstance().Draw(SPRITE_ID::MANUAL_BACK_SPRITE, textDrawPos_m, Vector2(TEXT_SIZE.x / 2, 0.0f), textAlpha, scale, true, false);
	Vector2 textDrawPos_b = Vector2(SCREEN_CENTER.x - (moveVec - SCREEN_CENTER.x) * 2.0f / 3.0f, WINDOW_HEIGHT / 5.0f);
	Sprite::GetInstance().Draw(SPRITE_ID::EXIT_GAME_BACK_SPRITE, textDrawPos_b, Vector2(TEXT_SIZE.x / 2, 0.0f), textAlpha, scale, true, false);

	/* テキスト強調用 */
	Sprite::GetInstance().Draw(SPRITE_ID::START_GAME_SPRITE, textDrawPos_s, Vector2(TEXT_SIZE.x / 2, 0.0f), selects[0], scale, true, false);
	Sprite::GetInstance().Draw(SPRITE_ID::MANUAL_SPRITE, textDrawPos_m, Vector2(TEXT_SIZE.x / 2, 0.0f), selects[1], scale, true, false);
	Sprite::GetInstance().Draw(SPRITE_ID::EXIT_GAME_SPRITE, textDrawPos_b, Vector2(TEXT_SIZE.x / 2, 0.0f), selects[2], scale, true, false);
	float posX[3] = { textDrawPos_s.x, textDrawPos_m.x, textDrawPos_b.x };
	Sprite::GetInstance().Draw(SPRITE_ID::POINT_SPRITE, Vector2(posX[selectNum], WINDOW_HEIGHT / 6.0f), Vector2(24.0f, 24.0f), selects[selectNum], Vector2(scale.x), true, false);

	/* 中心から移動用
	Point size = Point(move * 2 / scale.x, 0) + RES_SIZE_1.ToPoint();
	rect.left = 0.0f + move / scale.x;
	rect.right = rect.left + RES_SIZE_1.x;
	Sprite::GetInstance().Draw(SPRITE_ID::MENU_ROLL_3_SPRITE, SCREEN_CENTER + Vector2(move, 0.0f), size, RES_SIZE_1 / 2, alpha, scale, 180.0f, true, false);
	Sprite::GetInstance().Draw(SPRITE_ID::MENU_ROLL_2_SPRITE, SCREEN_CENTER - Vector2(move, 0.0f), rect, RES_SIZE_1 / 2, alpha, scale, 0.0f, true, false);
	*/
}

void MenuPanel::DrawPause() const
{
	/* テキストの描画 */
	Vector2 textDrawPos_s = Vector2(SCREEN_CENTER.x + (moveVec - SCREEN_CENTER.x) * 3.0f / 4.0f, WINDOW_HEIGHT / 5.0f);
	Sprite::GetInstance().Draw(SPRITE_ID::BACK_TO_GAME_BACK_SPRITE, textDrawPos_s, Vector2(TEXT_SIZE.x / 2, 0.0f), textAlpha, scale, true, false);
	Vector2 textDrawPos_m = Vector2(SCREEN_CENTER.x + (moveVec - SCREEN_CENTER.x) * 1.0f / 4.0f, WINDOW_HEIGHT / 5.0f);
	Sprite::GetInstance().Draw(SPRITE_ID::MANUAL_BACK_SPRITE, textDrawPos_m, Vector2(TEXT_SIZE.x / 2, 0.0f), textAlpha, scale, true, false);
	Vector2 textDrawPos_b = Vector2(SCREEN_CENTER.x - (moveVec - SCREEN_CENTER.x) * 2.0f / 3.0f, WINDOW_HEIGHT / 5.0f);
	Sprite::GetInstance().Draw(SPRITE_ID::BACK_TO_MENU_BACK_SPRITE, textDrawPos_b, Vector2(TEXT_SIZE.x / 2, 0.0f), textAlpha, scale, true, false);

	/* テキスト強調用 */
	Sprite::GetInstance().Draw(SPRITE_ID::BACK_TO_GAME_SPRITE, textDrawPos_s, Vector2(TEXT_SIZE.x / 2, 0.0f), selects[0], scale, true, false);
	Sprite::GetInstance().Draw(SPRITE_ID::MANUAL_SPRITE, textDrawPos_m, Vector2(TEXT_SIZE.x / 2, 0.0f), selects[1], scale, true, false);
	Sprite::GetInstance().Draw(SPRITE_ID::BACK_TO_MENU_SPRITE, textDrawPos_b, Vector2(TEXT_SIZE.x / 2, 0.0f), selects[2], scale, true, false);
	float posX[3] = { textDrawPos_s.x, textDrawPos_m.x, textDrawPos_b.x };
	Sprite::GetInstance().Draw(SPRITE_ID::POINT_SPRITE, Vector2(posX[selectNum], WINDOW_HEIGHT / 6.0f), Vector2(24.0f, 24.0f), selects[selectNum], Vector2(scale.x), true, false);
}

void MenuPanel::DrawManual() const
{

}

void MenuPanel::Action()
{
	if (isAction) return;
	Initialize();
}

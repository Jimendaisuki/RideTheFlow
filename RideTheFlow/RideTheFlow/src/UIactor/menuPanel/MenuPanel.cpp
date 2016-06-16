#include "MenuPanel.h"
#include "../../Def.h"
#include "../../graphic/Sprite.h"
#include "../../input/GamePad.h"
#include "../../input/Keyboard.h"
#include "../../math/Math.h"
#include "../../time/Time.h"
#include "../../world/IWorld.h"
#include "../../actor/Actor.h"
#include "../../game/GameFrame.h"

const Vector2 SCREEN_CENTER = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
const Vector2 Scale = Vector2((float)WINDOW_WIDTH / 1920.0f, (float)WINDOW_HEIGHT / 1080.0f);
const Vector2 RES_SIZE_1 = Vector2(175, 967);
const Vector2 RES_SIZE_2 = Vector2(1574, 967);
const Vector2 TEXT_SIZE = Vector2(150.0f, 700.0f);
const float MOVE_WIDTH = (RES_SIZE_2.x - RES_SIZE_1.x) / 2;
const float DELEY_TIME = 0.1f;
const float LX[6] = { 0.0f, WINDOW_WIDTH / 3.0f * 1.3f, WINDOW_WIDTH / 10.0f, 0.0f, WINDOW_WIDTH / 8.0f, WINDOW_WIDTH / 3.0f };
const float LY[6] = { 0.0f, -WINDOW_HEIGHT / 15.0f * 1.3f, 0, WINDOW_HEIGHT * 3.0f / 7.0f, WINDOW_HEIGHT * 9.0f / 10.0f, WINDOW_HEIGHT };
const float RX[5] = { WINDOW_WIDTH, WINDOW_WIDTH * 0.9f, WINDOW_WIDTH * 1.1f, WINDOW_WIDTH , WINDOW_WIDTH * 0.8f};
const float RY[5] = { 0.0f, WINDOW_HEIGHT / 10.0f, WINDOW_HEIGHT * 0.25f, WINDOW_HEIGHT * 0.6f, WINDOW_HEIGHT };
float LV[6] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
float RV[5] = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};

void MenuPanel::Initialize()
{
	/* 初期設定 */
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
	
	/* 雲設定 */
	alphaTime = 0.0f;

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
	textScale = 1.0f;


	/* 実行用設定 */
	isAction	 = false;
	isBackSelect = false;
	isEnd		 = false;
	status = MENU_PANEL_STATUS::BEGIN;
}

void MenuPanel::Update()
{
	if (!isAction) return;
	
	switch (status)
	{
	case BEGIN:		// 巻物が左に移動
		// ポーズ時の暗転 
		if (scene == Scene::GamePlay)
		{
			if (backAlpha < 0.7f)
			{
				backAlpha += Time::DeltaTime * 4;
				backAlpha = Math::Clamp(backAlpha, 0.0f, 0.7f);
			}
		}
		// 処理
		time += Time::DeltaTime;
		rollAlpha = time;
		alphaTime = time;

		moveVec = MOVE_WIDTH * Scale.x * bez.Get(CBezier::eSlow_Lv5, CBezier::eSlow_Lv5, Math::Clamp(time, 0.0f, 1.0f));
		drawPosition = SCREEN_CENTER - Vector2(moveVec, 0.0f);

		// ステータス切り替え
		if (time >= 1)
		{
			status = MENU_PANEL_STATUS::OPEN;
			rollBakcAlpha = 1.0f;
			time = -DELEY_TIME;
		}
		break;
	case OPEN:		// 巻物開く
		// 処理
		time += Time::DeltaTime;

		moveVec = MOVE_WIDTH * Scale.x * 2 * bez.Get(CBezier::eSlow_Lv5, CBezier::eSlow_Lv5, time);
		size = Point(moveVec / Scale.x, 0) + RES_SIZE_1.ToPoint();
		rect.left = moveVec / Scale.x;
		rect.right = rect.left + RES_SIZE_1.x;

		// ステータス切り替え
		if (time >= 1.0f)
		{
			time = 1.0f;
			status = MENU_PANEL_STATUS::SELECT;
		}
		break;
	case SELECT:	// セレクト
		// MANUAL → SELECT
		if (pages[prePage] > 0.0f)
		{
			pages[prePage] -= Time::DeltaTime;
			return;
		}
		pages[prePage] = 0.0f;
		// OPEN → SELECT
		if (textAlpha < 1.0f)
		{
			textAlpha += Time::DeltaTime;
			return;
		}
		textAlpha = 1.0f;
		// 選択肢によるアルファ変更
		for (int i = 0; i < 3; i++)
			selects[i] = 0;
		selects[selectNum] = 1;

		// 入力処理
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LEFT) || 
			GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::LEFT))	
			selectNum++;
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::RIGHT) ||
			GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::RIGHT))
			selectNum--;
		if (selectNum > 2) selectNum = 0;
		if (selectNum < 0) selectNum = 2;

		// ステータス切り替え
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::N) ||
			GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1))
		{
			if (selectNum == 0)
			{
				if (scene == Scene::Menu)
					status = MENU_PANEL_STATUS::PUSH;
				else if (scene == Scene::GamePlay)
					status = MENU_PANEL_STATUS::CLOSE;
			}
			else if (selectNum == 1)
			{
				prePage = 0;
				nowPage = 1;
				status = MENU_PANEL_STATUS::MANUAL;
			}
			else if (selectNum == 2)
			{
				if (scene == Scene::Menu)
					GameFrame::GameEnd();
				else if (scene == Scene::GamePlay)
				{
					isBackSelect = true;
					Close();
				}
			}
		}
		break;
	case MANUAL:	// 操作説明画面
		// SELECT → MANUAL
		if (textAlpha > 0.0f)
		{
			textAlpha -= Time::DeltaTime * 2.0f;
			for (int i = 0; i < 3; i++)
				selects[selectNum] = textAlpha;
			return;
		}
		textAlpha = 0.0f;
		// フェードアウト
		if (pages[prePage] > 0.0f)
		{
			pages[prePage] -= Time::DeltaTime;
			break;
		}
		pages[prePage] = 0.0f;
		// フェードイン
		if (pages[nowPage] < 1.0f) 
		{
			pages[nowPage] += Time::DeltaTime;
			break;
		}
		pages[nowPage] = 1.0f;

		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::B) ||
			GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM2))
		{
			if (nowPage <= 1)
			{
				status = MENU_PANEL_STATUS::SELECT;
				prePage = 1;
				nowPage = 0;
				return;
			}
			prePage = nowPage;
			nowPage--;
		}		
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::N) ||
			GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM1))
		{
			if (nowPage > 3)
			{
				status = MENU_PANEL_STATUS::SELECT;
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

		moveVec = MOVE_WIDTH * Scale.x * 2 * bez.Get(CBezier::eSlow_Lv5, CBezier::eSlow_Lv5, time);
		size = Point(moveVec / Scale.x, 0) + RES_SIZE_1.ToPoint();
		rect.left = moveVec / Scale.x;
		rect.right = rect.left + RES_SIZE_1.x;

		if (time <= 0.0f)
		{
			time = 0.0f;
			rollBakcAlpha = 0.0f;
			status = MENU_PANEL_STATUS::END;
		}
		break;
	case PUSH:
		selects[selectNum] -= Time::DeltaTime * 2.5f;
		textScale += Time::DeltaTime / 5.0;
		isEnd = true;
		break;
	case END:		// フェードアウトから終了
		if (rollAlpha > 0.0f)
		{
			rollAlpha -= Time::DeltaTime;
			alphaTime = rollAlpha;
		}
		else
		{
			if (backAlpha > 0)
			{
				backAlpha -= Time::DeltaTime * 3;
				return;
			}
			rollAlpha = 0.0f;
			backAlpha = 0.0f;
			isAction = false;
			isEnd = true;
		}
		break;
	default:
		isAction = false;
		break;
	}

	/* 雲処理 */
	for (int i = 0; i < 6; i++)
	{	// 左側
		Vector2 position = Vector2(-100.0f, LY[i]);
		LV[i] = (LX[i] - position.x) * bez.Get(CBezier::eNoAccel, CBezier::eSlow_Lv5, alphaTime);
	}
	for (int i = 0; i < 5; i++)
	{	// 右側
		Vector2 position = Vector2(WINDOW_WIDTH + 100.0f, RY[i]);
		RV[i] = (RX[i] - position.x) * bez.Get(CBezier::eNoAccel, CBezier::eSlow_Lv5, alphaTime);
	}
}

void MenuPanel::Draw() const
{
	if (scene == Scene::GamePlay) Sprite::GetInstance().Draw(SPRITE_ID::BLACK_SCREEN, Vector2::Zero, Vector2::Zero, backAlpha, Vector2(WINDOW_WIDTH / 800.0f, WINDOW_HEIGHT / 600.0f), 0.0f, false, false);
	
	/* 巻物の描画 */
	Sprite::GetInstance().Draw(SPRITE_ID::MENU_ROLL_3_SPRITE, drawPosition + Vector2(moveVec, 0.0f), size, RES_SIZE_1 / 2 - Vector2(-5, 0), rollBakcAlpha, Scale, 180.0f, true, false);
	Sprite::GetInstance().Draw(SPRITE_ID::MENU_ROLL_2_SPRITE, drawPosition, rect, RES_SIZE_1 / 2, rollAlpha, Scale, 0.0f, true, false);
	Sprite::GetInstance().Draw(SPRITE_ID::MENU_ROLL_1_SPRITE, drawPosition, RES_SIZE_1 / 2, rollAlpha, Scale, 0.0f);

	for (int i = 0; i < 6; i++)
	{
		Vector2 position = Vector2(-100.0f, LY[i]);
		Sprite::GetInstance().Draw(SPRITE_ID::TORNADO_SPRITE, position + Vector2(LV[i], 0.0f), Vector2(400, 300), alphaTime, Vector2(Scale.x, 0.8f * Scale.y));
	}
	for (int i = 0; i < 5; i++)
	{
		Vector2 position = Vector2(WINDOW_WIDTH + 100.0f, RY[i]);
		Sprite::GetInstance().Draw(SPRITE_ID::TORNADO_SPRITE, position + Vector2(RV[i], 0.0f), Vector2(400, 300), alphaTime, Vector2(Scale.x, 0.8f * Scale.y));
	}

	/* セレクト描画 */
	if (scene == Scene::Menu) DrawMenu();
	else if (scene == Scene::GamePlay) DrawPause();

	/* マニュアル描画 */
	Sprite::GetInstance().Draw(SPRITE_ID::MANUAL_1_SPRITE, SCREEN_CENTER, RES_SIZE_2 / 2, pages[1], Scale, 0.0f);
	Sprite::GetInstance().Draw(SPRITE_ID::MANUAL_2_SPRITE, SCREEN_CENTER, RES_SIZE_2 / 2, pages[2], Scale, 0.0f);
	Sprite::GetInstance().Draw(SPRITE_ID::MANUAL_3_SPRITE, SCREEN_CENTER, RES_SIZE_2 / 2, pages[3], Scale, 0.0f);
	Sprite::GetInstance().Draw(SPRITE_ID::MANUAL_4_SPRITE, SCREEN_CENTER, RES_SIZE_2 / 2, pages[4], Scale, 0.0f);
}

void MenuPanel::DrawMenu() const
{
	/* テキストの描画 */
	Vector2 textDrawPos_s = Vector2(SCREEN_CENTER.x + (moveVec - SCREEN_CENTER.x) * 3.0f / 4.0f, WINDOW_HEIGHT / 2.0f);
	Sprite::GetInstance().Draw(SPRITE_ID::START_GAME_BACK_SPRITE, textDrawPos_s, TEXT_SIZE / 2.0f, textAlpha, Scale, true, false);
	Vector2 textDrawPos_m = Vector2(SCREEN_CENTER.x + (moveVec - SCREEN_CENTER.x) * 1.0f / 4.0f, WINDOW_HEIGHT / 2.0f);
	Sprite::GetInstance().Draw(SPRITE_ID::MANUAL_BACK_SPRITE, textDrawPos_m, TEXT_SIZE / 2.0f, textAlpha, Scale, true, false);
	Vector2 textDrawPos_b = Vector2(SCREEN_CENTER.x - (moveVec - SCREEN_CENTER.x) * 2.0f / 3.0f, WINDOW_HEIGHT / 2.0f);
	Sprite::GetInstance().Draw(SPRITE_ID::EXIT_GAME_BACK_SPRITE, textDrawPos_b, TEXT_SIZE / 2.0f, textAlpha, Scale, true, false);

	/* テキスト強調用 */
	Sprite::GetInstance().Draw(SPRITE_ID::START_GAME_SPRITE, textDrawPos_s, TEXT_SIZE / 2.0f, selects[0], Scale * textScale, true, false);
	Sprite::GetInstance().Draw(SPRITE_ID::MANUAL_SPRITE, textDrawPos_m, TEXT_SIZE / 2.0f, selects[1], Scale * textScale, true, false);
	Sprite::GetInstance().Draw(SPRITE_ID::EXIT_GAME_SPRITE, textDrawPos_b, TEXT_SIZE / 2.0f, selects[2], Scale * textScale, true, false);
	float posX[3] = { textDrawPos_s.x, textDrawPos_m.x, textDrawPos_b.x };
	Sprite::GetInstance().Draw(SPRITE_ID::POINT_SPRITE, Vector2(posX[selectNum], WINDOW_HEIGHT / 6.0f), Vector2(24.0f, 24.0f), selects[selectNum], Vector2(Scale.x), true, false);

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
	Vector2 textDrawPos_s = Vector2(SCREEN_CENTER.x + (moveVec - SCREEN_CENTER.x) * 3.0f / 4.0f, WINDOW_HEIGHT / 2.0f);
	Sprite::GetInstance().Draw(SPRITE_ID::BACK_TO_GAME_BACK_SPRITE, textDrawPos_s, TEXT_SIZE / 2.0f, textAlpha, Scale, true, false);
	Vector2 textDrawPos_m = Vector2(SCREEN_CENTER.x + (moveVec - SCREEN_CENTER.x) * 1.0f / 4.0f, WINDOW_HEIGHT / 2.0f);
	Sprite::GetInstance().Draw(SPRITE_ID::MANUAL_BACK_SPRITE, textDrawPos_m, TEXT_SIZE / 2.0f, textAlpha, Scale, true, false);
	Vector2 textDrawPos_b = Vector2(SCREEN_CENTER.x - (moveVec - SCREEN_CENTER.x) * 2.0f / 3.0f, WINDOW_HEIGHT / 2.0f);
	Sprite::GetInstance().Draw(SPRITE_ID::BACK_TO_MENU_BACK_SPRITE, textDrawPos_b, TEXT_SIZE / 2.0f, textAlpha, Scale, true, false);

	/* テキスト強調用 */
	Sprite::GetInstance().Draw(SPRITE_ID::BACK_TO_GAME_SPRITE, textDrawPos_s, TEXT_SIZE / 2.0f, selects[0], Scale * textScale, true, false);
	Sprite::GetInstance().Draw(SPRITE_ID::MANUAL_SPRITE, textDrawPos_m, TEXT_SIZE / 2.0f, selects[1], Scale * textScale, true, false);
	Sprite::GetInstance().Draw(SPRITE_ID::BACK_TO_MENU_SPRITE, textDrawPos_b, TEXT_SIZE / 2.0f, selects[2], Scale * textScale, true, false);
	float posX[3] = { textDrawPos_s.x, textDrawPos_m.x, textDrawPos_b.x };
	Sprite::GetInstance().Draw(SPRITE_ID::POINT_SPRITE, Vector2(posX[selectNum], WINDOW_HEIGHT / 6.0f), Vector2(24.0f, 24.0f), selects[selectNum], Vector2(Scale.x), true, false);
}

// 未実行なら実行
void MenuPanel::Action(Scene scene_)
{
	if (isAction) return;
	/* 現在のシーンを取得 */
	scene = scene_;
	Initialize();
	isAction = true;
}
// 実行中か？
bool MenuPanel::IsAction() const
{
	return isAction;
}

bool MenuPanel::IsBackSelect() const
{
	return isBackSelect;
}

bool MenuPanel::IsEnd() const
{
	return isEnd;
}

void MenuPanel::Close()
{
	status = MENU_PANEL_STATUS::CLOSE;
}

void MenuPanel::Stop()
{
	isAction = false;
}
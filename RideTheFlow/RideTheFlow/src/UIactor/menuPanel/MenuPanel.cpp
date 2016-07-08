#include "MenuPanel.h"
#include "../../Def.h"
#include "../../graphic/Sprite.h"
#include "../../input/GamePad.h"
#include "../../input/Keyboard.h"
#include "../../game/Random.h"
#include "../../math/Math.h"
#include "../../time/Time.h"
#include "../../world/IWorld.h"
#include "../../actor/Actor.h"
#include "../../game/GameFrame.h"
#include "../../sound/Sound.h"
#include "../fadePanel/FadePanel.h"

const Vector2 SCREEN_CENTER = Vector2(WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
const Vector2 Scale = Vector2((float)WINDOW_WIDTH / 1920.0f, (float)WINDOW_HEIGHT / 1080.0f);
const Vector2 RES_SIZE_1 = Vector2(175, 967);
const Vector2 RES_SIZE_2 = Vector2(1574, 967);
const Vector2 TEXT_SIZE = Vector2(150.0f, 700.0f);
const float MOVE_WIDTH = (RES_SIZE_2.x - RES_SIZE_1.x) / 2;
const float DELEY_TIME = 0.1f;
const std::array<float, 6> LX = { 0.0f, WINDOW_WIDTH / 3.0f * 1.3f, WINDOW_WIDTH / 10.0f, 0.0f, WINDOW_WIDTH / 8.0f, WINDOW_WIDTH / 3.0f };
const std::array<float, 6> LY = { 0.0f, -WINDOW_HEIGHT / 15.0f * 1.3f, 0, WINDOW_HEIGHT * 3.0f / 7.0f, WINDOW_HEIGHT * 9.0f / 10.0f, WINDOW_HEIGHT };
const std::array<float, 5> RX = { WINDOW_WIDTH, WINDOW_WIDTH * 0.9f, WINDOW_WIDTH * 1.1f, WINDOW_WIDTH, WINDOW_WIDTH * 0.8f };
const std::array<float, 5> RY = { 0.0f, WINDOW_HEIGHT / 10.0f, WINDOW_HEIGHT * 0.25f, WINDOW_HEIGHT * 0.6f, WINDOW_HEIGHT };
std::array<float, 6> LV = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
std::array<float, 5> RV = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };

MenuPanel::MenuPanel(Scene currentScene) :
scene(currentScene)
{

}

MenuPanel::~MenuPanel()
{

}

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
	for (int i = 0; i < 5; i++)
	{
		pages[i] = 0.0f;
	}
	textScale = 1.0f;

	/* 雲設定 */
	SetCloud();

	backAlpha = 0.0f;
	currentButton = 0;
	isPush = false;

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

		if (!Sound::GetInstance().IsPlaySE(SE_ID::MENU_ROLL_SE))
			Sound::GetInstance().PlaySE(SE_ID::MENU_ROLL_SE);
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
			break;
		}
		pages[prePage] = 0.0f;
		// OPEN → SELECT
		if (textAlpha < 1.0f)
		{
			textAlpha += Time::DeltaTime;
			break;
		}
		textAlpha = 1.0f;
		// 選択肢によるアルファ変更
		for (int i = 0; i < 3; i++)
			selects[i] = 0;
		selects[selectNum] = 1;


		DINPUT_JOYSTATE input;
		GetJoypadDirectInputState(DX_INPUT_PAD1, &input);
		currentButton = 0;

		// 十字キー
		if (!isPush && input.POV[0] != -1)
		{
			currentButton = input.POV[0];
			isPush = true;
		}
		if (input.POV[0] == -1 && isPush)
			isPush = false;

		// 入力処理
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LEFT) ||
			GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::LEFT) ||
			currentButton == 27000)
		{
			Sound::GetInstance().PlaySE(SE_ID::SWITCH_SE);
			selectNum++;
		}
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::RIGHT) ||
			GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::RIGHT) ||
			currentButton == 9000)
		{
			Sound::GetInstance().PlaySE(SE_ID::SWITCH_SE);
			selectNum--;
		}
		if (selectNum > 2) selectNum = 0;
		if (selectNum < 0) selectNum = 2;

		/* ステータス切り替え */
		// 強制閉じる
		if ((scene == Scene::GamePlay) && 
			(Keyboard::GetInstance().KeyTriggerDown(KEYCODE::B) ||
			 GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM9) ||
			 GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM3)))
		{
			Close();
			break;
		}
		// ×ボタン
		if ((scene == Scene::Menu) &&
			(Keyboard::GetInstance().KeyTriggerDown(KEYCODE::B) ||
			 GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM3)))
		{
			Sound::GetInstance().PlaySE(SE_ID::BACK_SE);
			FadePanel::GetInstance().SetOutTime(0.5f);
			isBackSelect = true;
			Close();
			break;
		}

		// 通常処理
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE) ||
			GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM2))
		{
			if (selectNum == 0)
			{	// 右
				Sound::GetInstance().PlaySE(SE_ID::ENTER_SE);
				status = MENU_PANEL_STATUS::PUSH;
			}
			else if (selectNum == 1)
			{	// 中
				prePage = 0;
				nowPage = 1;
				Sound::GetInstance().PlaySE(SE_ID::ENTER_SE);
				status = MENU_PANEL_STATUS::PUSH;
			}
			else if (selectNum == 2)
			{	// 左
				if (scene == Scene::Menu)
				{
					isBackSelect = true;
					Sound::GetInstance().PlaySE(SE_ID::ENTER_SE);
					status = MENU_PANEL_STATUS::PUSH;
				}
				else if (scene == Scene::GamePlay)
				{
					isBackSelect = true;
					Sound::GetInstance().PlaySE(SE_ID::BACK_SE);
					status = MENU_PANEL_STATUS::PUSH;
				}
			}
		}
		break;
	case MANUAL:	// 操作説明画面
		// SELECT → MANUAL
		if (textAlpha > 0.0f)
		{
			textAlpha -= Time::DeltaTime * 2.0f;
			//for (int i = 0; i < 3; i++)
			//	selects[selectNum] = textAlpha;
			break;
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

		// 強制閉じる
		if (GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM9))
		{
			pages[nowPage] = 0;
			if (scene == Scene::Menu)
			{
				selectNum = 0;
				Sound::GetInstance().PlaySE(SE_ID::ENTER_SE);
				status = MENU_PANEL_STATUS::PUSH;
			}
			else
			{
				Sound::GetInstance().PlaySE(SE_ID::BACK_SE);
				status = MENU_PANEL_STATUS::CLOSE;
			}
		}

		// 戻る
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::B) ||
			GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM3))
		{
			Sound::GetInstance().PlaySE(SE_ID::BACK_SE);
			if (nowPage <= 1)
			{
				status = MENU_PANEL_STATUS::SELECT;
				prePage = 1;
				nowPage = 0;
				break;
			}
			prePage = nowPage;
			nowPage--;
		}		
		// 進む
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE) ||
			GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM2))
		{
			Sound::GetInstance().PlaySE(SE_ID::ENTER_SE);
			if (nowPage > 3)
			{
				status = MENU_PANEL_STATUS::SELECT;
				prePage = 4;
				nowPage = 1;
				break;
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
			break;
		}
		time -= Time::DeltaTime;
		if (!Sound::GetInstance().IsPlaySE(SE_ID::MENU_ROLL_SE))
			Sound::GetInstance().PlaySE(SE_ID::MENU_ROLL_SE);

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
		if (selects[selectNum] <= 0.0f)
		{
			if (scene == Scene::GamePlay)
			{	// ゲームプレイシーン
				if (selectNum == 0)
					status = MENU_PANEL_STATUS::CLOSE;
				else if (selectNum == 1)
					status = MENU_PANEL_STATUS::MANUAL;
				else if (selectNum == 2)
				{
					FadePanel::GetInstance().FadeOut();
					status = MENU_PANEL_STATUS::NONE;
				}
			}
			else
			{	// メニューシーン
				if (selectNum == 0)
					isEnd = true;
				else if (selectNum == 1)
					status = MENU_PANEL_STATUS::MANUAL;
				else if (selectNum == 2)
					GameFrame::GameEnd();
			}
			textScale = 1.0f;
			if (!FadePanel::GetInstance().IsAction())
			{
				isAction = false;
				isEnd = true;
			}
			break;
		}
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
				break;
			}
			tornadoAlpha = 0;
			rollAlpha = 0.0f;
			backAlpha = 0.0f;
			isAction = false;
			isEnd = true;
		}
		break;
	default:
		if (!FadePanel::GetInstance().IsAction())
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

	for (int i = 0; i < 8; i++)
	{
		if (tornadoPos[i].x <= -400.0f && tornadoVel[i] < 0)
		{
			tornadoPos[i].x = WINDOW_WIDTH + 250.0f;
			tornadoPos[i].y += Random::GetInstance().Range(-10.0f, 10.0f);
		}

		if (tornadoPos[i].x >= (WINDOW_WIDTH + 400.0f) && tornadoVel[i] > 0)
		{
			tornadoPos[i].x = -250.0f;
			tornadoPos[i].y += Random::GetInstance().Range(-10.0f, 10.0f);
		}
		
		tornadoVel[i] *= Random::GetInstance().Range(0.8f, 1.3f);
		tornadoVel[i] = Math::Clamp(tornadoVel[i], -100.0f, 100.0f);
		tornadoPos[i].x += tornadoVel[i] * Time::DeltaTime;
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

	for (int i = 0; i < 8; i++)
	{
		Sprite::GetInstance().Draw(SPRITE_ID::TORNADO_SPRITE, tornadoPos[i], Vector2(400, 300), tornadoAlpha, Vector2(Scale.x, 0.8f * Scale.y));
	}
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
void MenuPanel::Action()
{
	if (isAction) return;
	Initialize();
	isAction = true;
	tornadoAlpha = 1.0f;
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

void MenuPanel::SetCloud()
{
	tornadoAlpha = 1.0f;

	for (int i = 0; i < 4; i++)
	{
		tornadoPos[i].x = -250.f - Random::GetInstance().Range(0.0f, 300.0f) * (i % 2 + 1);
		tornadoPos[i + 4].x = WINDOW_WIDTH + 250.f + Random::GetInstance().Range(0.0f, 300.0f) * (i % 2 + 1);

		if (i % 2 == 0)
		{
			tornadoPos[i].y = Random::GetInstance().Range(-50.0f, 200.0f);
			tornadoPos[i + 4].y = Random::GetInstance().Range(-50.0f, 200.0f);
		}
		else
		{
			tornadoPos[i].y = WINDOW_HEIGHT - Random::GetInstance().Range(-50.0f, 200.0f);
			tornadoPos[i + 4].y = WINDOW_HEIGHT - Random::GetInstance().Range(-50.0f, 200.0f);
		}

		float num = 30.0f * (i % 2 + 2);

		tornadoVel[i] = Random::GetInstance().Range(10.0f * (i % 2 + 1), num);
		tornadoVel[i + 4] = Random::GetInstance().Range(-num, -10.0f * (i % 2 + 1));
	}
}
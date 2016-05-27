#include "TitleScene.h"
#include "../AllInclude.h"
#include "../game/WorkFolder.h"
#include "../graphic/Model.h"
#include "../graphic/Sprite.h"
#include "../sound/Sound.h"
#include "../input/Keyboard.h"
#include "../game/Random.h"
#include "../graphic/TextDraw.h"
#include <sstream>
#include <iomanip>
#include "Scene.h"
#include "../actor/AnimTestActor.h"

#include "../UIactor/Effect.h"
#include "../actor/Stage.h"
#include "../actor/TitleCameraActor.h"
#include "../time/Time.h"

#include "../actor/CameraActor.h"
#include "../math/Math.h"
#include "../UIactor/Damege.h"
#include "../UIactor/Stamina.h"

#include "../UIactor/fadePanel/FadePanel.h"

//コンストラクタ
TitleScene::TitleScene()
{

}

//デストラクタ
TitleScene::~TitleScene()
{

}

float fpsTimer = 0.0f;
float fps;
int effectNum = 0;

int	modelHandle = 0;
int frameCount = 0;
int frameNum = 0;
int frameParentCount = 0;
int frameChildCount = 0;

float testStamina = 0;
float testMaxStamina = 100;
float testHP = 100;

TITLE_STATUS status;

/* 竜巻ポリゴン用データ */
const Vector3 stormPos = Vector3(400.0f, 300.0f, 0.0f);
const Vector2 sizehalf = Vector2(150, 150);
int texhandle;
float x[4] = { stormPos.x + sizehalf.x / 2.0f, stormPos.x - sizehalf.x * 3, stormPos.x - sizehalf.x / 2.0f, stormPos.x + sizehalf.x * 3 };
float y[4] = { stormPos.y - sizehalf.y, stormPos.y + sizehalf.y, stormPos.y + sizehalf.y, stormPos.y - sizehalf.y };
float u[4] = { 0, 0, 1, 1 };
float v[4] = { 0, 1, 1, 0 };
VERTEX2D Vertex2D_1[6];
VERTEX2D Vertex2D_2[6];
float amount_1 = 0;
float amount_2 = 0;
int count_1 = 0;
int count_2 = 0;
const float stormAlphaEndTime = 2.5f;
const int stormMaxAlpha = 255 / 3;
int stormAlpha = 0;

/* タイトルテキスト用データ */
const float titleAlphaEndTime = 4.0f;
float titleAlpha = 0;
float pressTextAlpha = 0;
float pressTextBackAlpha = 0;
float pressAlphaTime = 0;

//開始
void TitleScene::Initialize()
{
	timer = 0.0f;
	objectcount = 0;
	mIsEnd = false;
	status = TITLE_STATUS::TITLE_BEGIN;
	wo.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wo));
	//wo.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<TitleCameraActor>(wo));
	
	modelHandle = Model::GetInstance().GetHandle(MODEL_ID::TEST_STAGE);
	frameCount = MV1GetFrameNum(modelHandle);
	frameParentCount = MV1GetFrameParent(modelHandle, frameNum);
	frameChildCount = MV1GetFrameChildNum(modelHandle, frameNum);

	position = Vector3::Zero;

	wo.UIAdd(EFFECT_ID::STAMINA_EFFECT, std::make_shared<Stamina>(wo, testMaxStamina, testStamina));
	wo.UIAdd(EFFECT_ID::DAMAGE_EFFECT, std::make_shared<Damege>(wo, testHP));

	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Position.Set(Vector3(0, 500, -200));
	Camera::GetInstance().Target.Set(position);
	Camera::GetInstance().Up.Set(Vector3::Up);

	FadePanel::GetInstance().Initialize();
	FadePanel::GetInstance().FadeIn(2.0f);

	/* ポリゴンデータ */
	stormAlpha = 0;
	for (int i = 0; i < 4; i++)
	{
		auto start = (i + count_1) % 4;
		auto end = (i + 1 + count_1) % 4;
		Vertex2D_1[i].pos = Vector3(x[start], y[end], 0.0f).ToVECTOR();
		Vertex2D_1[i].rhw = 1.0f;
		Vertex2D_1[i].dif = GetColorU8(255, 255, 255, stormAlpha);
		Vertex2D_1[i].u = u[i];
		Vertex2D_1[i].v = v[i];
	}
	Vertex2D_1[4] = Vertex2D_1[0];
	Vertex2D_1[5] = Vertex2D_1[2];

	for (int i = 0; i < 6; i++)
	{
		Vertex2D_2[i] = Vertex2D_1[i];
	}

	texhandle = LoadGraph("res/Sprite/title_storm.png");
	amount_1 = 0;
	amount_2 = 0;
	count_1 = 0;
	count_2 = 0;

	/* タイトルテキストデータ */
	titleAlpha = 0;
}

void TitleScene::Update()
{
	// シーン終了
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE))
	{
		mIsEnd = true;
	}
	
	switch (status)
	{
	case TITLE_BEGIN:
		if (!FadePanel::GetInstance().IsAction()) 
			status = TITLE_STATUS::TITLE_DRAGON_IN;
		break;
	case TITLE_DRAGON_IN:
		status = TITLE_STATUS::TITLE_TEXTURE_IN;
		break;
	case TITLE_TEXTURE_IN:
		stormAlpha += (255.0f * Time::DeltaTime) / stormAlphaEndTime;
		stormAlpha = Math::Clamp(stormAlpha, 0, stormMaxAlpha);
		for (int i = 0; i < 6; i++)
		{
			Vertex2D_1[i].dif.a = stormAlpha;
		}
		
		if (stormAlpha >= 255 / 4)
		{
			titleAlpha += Time::DeltaTime / titleAlphaEndTime;
			titleAlpha = Math::Clamp(titleAlpha, 0.0f, 1.0f);
		}

		if (titleAlpha >= 1.0f)
			status = TITLE_STATUS::TITLE_STANDBY;
		break;
	case TITLE_STANDBY:
		if (pressTextAlpha <= 1) pressTextAlpha += Time::DeltaTime;
		pressAlphaTime += Time::DeltaTime * 3;
		pressTextBackAlpha = Math::Sin(Math::Degree(pressAlphaTime));

		// シーン終了
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE))
		{
			FadePanel::GetInstance().FadeOut(1.0f);
			status = TITLE_STATUS::TITLE_END;
		}
		break;
	case TITLE_END:
		if (!FadePanel::GetInstance().IsAction())
			mIsEnd = true;
		break;
	default:
		break;
	}

	fpsTimer += Time::DeltaTime;
	if (fpsTimer > 1.0f)
	{
		fps = 1.0f / Time::DeltaTime;
		fpsTimer = 0.0f;
	}

	if (!FadePanel::GetInstance().IsAction())
	{
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A)) position.x--;
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::D)) position.x++;
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::W)) position.y++;
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::S)) position.y--;
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::E)) position.z--;
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::Q)) position.z++;

		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::UP)) frameNum++;
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::DOWN)) frameNum--;
		if (frameNum > frameCount - 1) frameNum = 0;
		if (frameNum < 0) frameNum = frameCount - 1;
		frameParentCount = MV1GetFrameParent(modelHandle, frameNum);
		frameChildCount = MV1GetFrameChildNum(modelHandle, frameNum);

		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Z)) effectNum++;
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::X)) effectNum--;
		effectNum = Math::Clamp(effectNum, 0, 4);

		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::C)){
			FadePanel::GetInstance().FadeOut(1.0f);
		}
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::V)){
			FadePanel::GetInstance().FadeIn(1.0f);
		}

		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::R))testHP++;
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::F))testHP--;
		testHP = Math::Clamp(testHP, 0.0f, 100.0f);

		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::T))testStamina++;
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::G))testStamina--;
	}

	wo.Update();
	FadePanel::GetInstance().Update();

	Camera::GetInstance().Position.Set(Vector3(0, 100, -200));
	Camera::GetInstance().Target.Set(Vector3(0, 100, 0));
	Camera::GetInstance().Update();

	/* 竜巻ポリゴンの計算 */
	amount_1 += Time::DeltaTime / 4.0f;
	amount_2 += Time::DeltaTime / 16.0f;

	//for (int i = 0; i < 4; i++)
	//{
	//	auto start = (i + count) % 4;
	//	auto end = (i + 1 + count) % 4;
	//	Vertex2D_1[i].pos = Vector3::Lerp(Vector3(x_1[start], y_1[start]), Vector3(x_1[end], y_1[end]), amount).ToVECTOR();
	//}
	for (int i = 0; i < 4; i++)
	{
		auto start = (i + count_1) % 4;
		auto end = (i + 1 + count_1) % 4;
		Vector3 NowPos = Vector3::Lerp(Vector3(x[start], y[start]), Vector3(x[end], y[end]), amount_1);
		float length = Vector3(NowPos - stormPos).Length();
		length *= 1.0f + 0.5f - Math::Abs(0.5f - amount_1);
		Vector3 toVec = (NowPos - stormPos).Normalized();
		Vertex2D_1[i].pos = stormPos + toVec * length;

		start = (i + count_2) % 4;
		end = (i + 1 + count_2) % 4;
		NowPos = Vector3::Lerp(Vector3(x[start], y[start]), Vector3(x[end], y[end]), amount_2);
		length = Vector3(NowPos - stormPos).Length();
		length *= 1.0f + 0.5f - Math::Abs(0.5f - amount_2);
		toVec = (NowPos - stormPos).Normalized();
		Vertex2D_2[i].pos = stormPos + toVec * length;
	}

	if (amount_1 >= 1.0f)
	{
		amount_1 = 0.0f;
		count_1++;
	}
	if (amount_2 >= 1.0f)
	{
		amount_2 = 0.0f;
		count_2++;
	}

	Vertex2D_1[4] = Vertex2D_1[0];
	Vertex2D_1[5] = Vertex2D_1[2];
	Vertex2D_2[4] = Vertex2D_2[0];
	Vertex2D_2[5] = Vertex2D_2[2];
}

//描画
void TitleScene::Draw() const
{
	wo.Draw();

	TextDraw::GetInstance().Draw("TitleScene");
	//DrawFormatString(0, 20, GetColor(255, 255, 255), "FPS:		%f", fps);
	//DrawFormatString(0, 160, GetColor(255, 0, 0), "R,F		: ダメージ演出");
	//DrawFormatString(0, 180, GetColor(255, 0, 0), "T,G		: スタミナ増減");
	//DrawFormatString(0, 200, GetColor(0, 0, 0), "FrameNum  : %d", frameNum);
	//DrawFormatString(0, 220, GetColor(0, 0, 0), "FrameName : %s", MV1GetFrameName(modelHandle, frameNum));
	//DrawFormatString(0, 240, GetColor(0, 0, 0), "FramePare : %d", frameParentCount);
	//DrawFormatString(0, 260, GetColor(0, 0, 0), "FrameChild: %d", frameChildCount);
	//Vector3 position = Vector3::ToVECTOR(MV1GetFramePosition(modelHandle, frameNum));
	//DrawFormatString(0, 280, GetColor(0, 0, 0), "FramePos  : [%f] [%f] [%f]", position.x, position.y, position.z);


	FadePanel::GetInstance().Draw();

	/* 竜巻 */
	DrawPolygon2D(Vertex2D_1, 2, texhandle, true);
	DrawPolygon2D(Vertex2D_2, 2, texhandle, true);
	/* テキスト */
	// タイトル
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_TEXT, Vector2(stormPos.x, stormPos.y), Vector2(450, 175), titleAlpha, Vector2(0.6f), true, false);
	// エニープッシュ
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_PRESS_BACK, Vector2(stormPos.x, stormPos.y + 200), Vector2(500, 50), pressTextBackAlpha, Vector2(0.6f), true, false);
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_PRESS, Vector2(stormPos.x, stormPos.y + 200), Vector2(500, 50), pressTextAlpha, Vector2(0.6f), true, false);

}

//終了しているか？
bool TitleScene::IsEnd() const
{
	return mIsEnd;
}

//次のシーンを返す
Scene TitleScene::Next() const
{
	return Scene::GamePlay;
}

void TitleScene::End()
{
	wo.Clear();
}
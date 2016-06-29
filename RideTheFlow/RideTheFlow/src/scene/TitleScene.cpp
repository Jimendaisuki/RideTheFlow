#include "TitleScene.h"
#include "../AllInclude.h"
#include "../Def.h"
#include "../game/WorkFolder.h"
#include "../graphic/Model.h"
#include "../graphic/Sprite.h"
#include "../input/GamePad.h"
#include "../input/Keyboard.h"
#include "../sound/Sound.h"

#include "../math/Math.h"
#include "../time/Time.h"

#include "../actor/Player.h"
#include "../actor/Stage.h"
#include "../actor/CameraActor.h"
#include "../actor/TitleCameraActor.h"
#include "../actor/StageGenerator.h"
#include "../UIactor/fadePanel/FadePanel.h"
#include "../CloudSetting.h"
#include "../actor/Cloud.h"
#include "../game/Random.h"

/* 竜巻ポリゴン用データ */
const Vector3 STORM_POS = Vector3(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 5.0f * 2.0f, 0.0f);
const Vector2 SIZE_HALF = Vector2(150, 150);
const float x[4] = { STORM_POS.x + SIZE_HALF.x / 2.0f, STORM_POS.x - SIZE_HALF.x * 3, STORM_POS.x - SIZE_HALF.x / 2.0f, STORM_POS.x + SIZE_HALF.x * 3 };
const float y[4] = { STORM_POS.y - SIZE_HALF.y, STORM_POS.y + SIZE_HALF.y, STORM_POS.y + SIZE_HALF.y, STORM_POS.y - SIZE_HALF.y };
const float u[4] = { 0, 0, 1, 1 };
const float v[4] = { 0, 1, 1, 0 };
const int	StormMaxAlpha		= 255 / 3;
const float StormAlphaEndTime	= 6.0f;
/* タイトルテキスト用データ */
const float TitleAlphaEndTime	= 2.0f;
/* スクリーン用データ */
const float endScreenPos = -(WINDOW_WIDTH / 2.0f);

//コンストラクタ
TitleScene::TitleScene()
{
	// 竜巻テクスチャハンドル
	texhandle = LoadGraph("res/Sprite/title_storm.png");
	// ポリゴンデータ作成
	for (int i = 0; i < 4; i++)
	{
		auto start	= i % 4;
		auto end	= (i + 1) % 4;
		Vertex2D_1[i].pos = Vector3(x[start], y[start], 0.0f).ToVECTOR();
		Vertex2D_1[i].rhw = 1.0f;
		Vertex2D_1[i].dif = GetColorU8(255, 255, 255, 0);
		Vertex2D_1[i].u = u[i];
		Vertex2D_1[i].v = v[i];
	}
	Vertex2D_1[4] = Vertex2D_1[0];
	Vertex2D_1[5] = Vertex2D_1[2];
	for (int i = 0; i < 6; i++)
		Vertex2D_2[i] = Vertex2D_1[i];
}

//デストラクタ
TitleScene::~TitleScene()
{
	DeleteGraph(texhandle);
}

//開始
void TitleScene::Initialize()
{
	mIsEnd = false;
	status = TITLE_STATUS::TITLE_BEGIN;
	wo.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wo));
	wo.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<TitleCameraActor>(wo));
	wo.Add(ACTOR_ID::EFFECT_ACTOR, std::make_shared<StageGenerator>(wo, "TitleStage", false));
	wo2.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wo, true));

	for (int i = 0; i < CLOUD_LOW_POSITION_NUM; i++)
	{
		wo.Add(ACTOR_ID::CLOUD_ACTOR, std::make_shared<Cloud>(wo, Vector3(Random::GetInstance().Range(-5000.0f, 5000.0f), 0.0f, Random::GetInstance().Range(-5000.0f, 5000.0f))));
	}
	for (int i = 0; i < CLOUD_HIGH_POSITION_NUM; i++)
	{
		wo.Add(ACTOR_ID::CLOUD_ACTOR, std::make_shared<Cloud>(wo, Vector3(Random::GetInstance().Range(-5000.0f, 5000.0f), 1400.0f, Random::GetInstance().Range(-5000.0f, 5000.0f))));
	}

	/* ポリゴンデータ */
	amount_1 = 0;
	amount_2 = 0;
	count_1 = 0;
	count_2 = 0;
	stormAlpha = 0;
	stormAlphaTime = 0.0f;
	for (int i = 0; i < 6; i++)
	{
		Vertex2D_1[i].dif.a = stormAlpha;
		Vertex2D_2[i] = Vertex2D_1[i];
	}

	/* タイトルテキストデータ */
	titleAlpha = 0;
	pressAlphaTime = 0;
	pressTextAlpha = 0;
	pressTextBackAlpha = 0;
	pressScale = 0;

	/* スクリーンデータ */
	screenHandle = MakeScreen(WINDOW_WIDTH * 1.5f, WINDOW_HEIGHT, TRUE);

	screenPos = WINDOW_WIDTH / 4;
	slideTime = 0;
	isTitle = false;

	/* 音 */
	Sound::GetInstance().StopBGM();
	Sound::GetInstance().PlayBGM(BGM_ID::TITLE_BGM, DX_PLAYTYPE_LOOP);

	/* フェード */
	FadePanel::GetInstance().SetInTime(3.0f);
	FadePanel::GetInstance().SetOutTime(2.0f);
}

void TitleScene::Update()
{	
	switch (status)
	{
	case TITLE_BEGIN:
		// 開始フェードイン
		if (!FadePanel::GetInstance().IsAction()) 
			status = TITLE_STATUS::TITLE_DRAGON_IN;
		break;
	case TITLE_DRAGON_IN:
		// ドラゴンが動く
		if (slideTime < 1)
		{
			screenPos = Math::Lerp(350.0f, endScreenPos, slideTime);
			slideTime += Time::DeltaTime / 3.0f;
		}
		else
			status = TITLE_STATUS::TITLE_TEXTURE_IN;
		break;
	case TITLE_TEXTURE_IN:
		// 竜巻とテキスト描画開始
		stormAlphaTime += (Time::DeltaTime / StormAlphaEndTime);
		stormAlpha = (int)(StormMaxAlpha * stormAlphaTime);
		stormAlpha = Math::Clamp(stormAlpha, 0, StormMaxAlpha);
		for (int i = 0; i < 6; i++)
		{
			Vertex2D_1[i].dif.a = stormAlpha;
			Vertex2D_2[i].dif.a = stormAlpha;
		}
		
		if (stormAlpha >= StormMaxAlpha / 3)
			titleAlpha += Time::DeltaTime / TitleAlphaEndTime;

		if (titleAlpha >= 1.0f)
			status = TITLE_STATUS::TITLE_STANDBY;
		break;
	case TITLE_STANDBY:
		// 入力待機
		if (pressTextAlpha < 1) 
			pressTextAlpha += Time::DeltaTime;
		pressAlphaTime += Time::DeltaTime * 60 * 3;
		pressAlphaTime = (float)((int)pressAlphaTime % 360);
		pressTextBackAlpha = Math::Sin(pressAlphaTime);

		// シーン終了
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE) ||
			GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM9))
		{
			Sound::GetInstance().PlaySE(SE_ID::ENTER_SE);
			FadePanel::GetInstance().FadeOut();
			status = TITLE_STATUS::TITLE_END;
		}
		break;
	case TITLE_END:
		// フェードアウト
		pressTextAlpha -= Time::DeltaTime;
		pressTextAlpha = Math::Clamp(pressTextAlpha, 0.0f, 1.0f);
		pressTextBackAlpha = pressTextAlpha;
		pressScale = (1.0f - pressTextAlpha) / 8.0f;
		if (!FadePanel::GetInstance().IsAction())
			mIsEnd = true;
		break;
	default:
		status = TITLE_STATUS::TITLE_BEGIN;
		break;
	}

	/* 竜巻ポリゴンの計算 */
	TornadoCalculation();

	/* 各種更新 */
	wo.Update();
	wo2.Update();

	Camera::GetInstance().SetRange(0.1f, 40000.0f);

	/* タイトルロゴ */
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Z))
		isTitle = !isTitle;
}

//描画
void TitleScene::Draw() const
{
	wo.Draw();

	if (isTitle)
		return;

	/* 竜巻 */
	DrawPolygon2D(Vertex2D_1, 2, texhandle, true);
	DrawPolygon2D(Vertex2D_2, 2, texhandle, true);
	DrawPolygon2D(Vertex2D_1, 2, Model::GetInstance().GetHandle(MODEL_ID::TEST_MODEL), true);

	/* 龍 */
	SetDrawScreen(screenHandle);
	ClearDrawScreen();
	SetCameraPositionAndTarget_UpVecY(
		VGet(200.0f, 0.0f, 0.0f),
		VGet(0.0f, 0.0f, 0.0f));
	wo2.Draw();
	SetDrawScreen(DX_SCREEN_BACK);
	DrawGraphF(screenPos, -100.0f, screenHandle, TRUE);
	
	/* テキスト */
	// タイトル
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_TEXT_SPRITE, Vector2(STORM_POS.x, STORM_POS.y), Vector2(450, 175), titleAlpha, Vector2(0.6f), true, false);
	// エニープッシュ
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_PRESS_BACK_SPRITE, Vector2(STORM_POS.x, STORM_POS.y + WINDOW_HEIGHT / 3), Vector2(500, 50), pressTextBackAlpha, Vector2(0.6f + pressScale), true, false);
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_PRESS_SPRITE, Vector2(STORM_POS.x, STORM_POS.y + WINDOW_HEIGHT / 3), Vector2(500, 50), pressTextAlpha, Vector2(0.6f + pressScale), true, false);
}

//終了しているか？
bool TitleScene::IsEnd() const
{
	return mIsEnd;
}

//次のシーンを返す
Scene TitleScene::Next() const
{
	return Scene::Menu;
}

void TitleScene::End()
{
	wo.Clear();
	wo2.Clear();
	DeleteGraph(screenHandle);
	Sound::GetInstance().StopBGM();
}

// 竜巻計算用
void TitleScene::TornadoCalculation()
{
	amount_1 += Time::DeltaTime / 4.0f;
	amount_2 += Time::DeltaTime / 16.0f;
	if (amount_1 > 1.0f)
	{
		amount_1 = 0.0f;
		count_1++;
	}
	if (amount_2 > 1.0f)
	{
		amount_2 = 0.0f;
		count_2++;
	}
	// 頂点の移動
	VertexMove(Vertex2D_1, count_1, amount_1);
	VertexMove(Vertex2D_2, count_2, amount_2);
	// 共有頂点データコピー
	Vertex2D_1[4] = Vertex2D_1[0];
	Vertex2D_1[5] = Vertex2D_1[2];
	Vertex2D_2[4] = Vertex2D_2[0];
	Vertex2D_2[5] = Vertex2D_2[2];
}

// 頂点移動
void TitleScene::VertexMove(VERTEX2D vertexs_[], int count_, float time_)
{
	for (int i = 0; i < 4; i++)
	{
		auto start = (i + count_) % 4;
		auto end   = (i + count_ + 1) % 4;
		const Vector3 midPos = Vector3(x[start], y[start], 0.0f) + ((Vector3(x[end], y[end], 0.0f) - Vector3(x[start], y[start], 0.0f)) / 2.0f);
		Vector3 v = midPos - STORM_POS;
		Vector3 toVec = v.Normalized() * v.Length() * 2.0f;
		Vector3 dirPos = STORM_POS + toVec;
		const float a = 1.0f - time_;
		Vector3 nowPosition = Vector3::Zero;
		nowPosition.x = a*a*x[start] + 2 * a*time_*dirPos.x + time_*time_*x[end];
		nowPosition.y = a*a*y[start] + 2 * a*time_*dirPos.y + time_*time_*y[end];
		vertexs_[i].pos = nowPosition;
	}
}

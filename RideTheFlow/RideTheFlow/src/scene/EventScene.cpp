#include "EventScene.h"
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

#include "../actor/Stage.h"
#include "../actor/CameraActor.h"
#include "../actor/TitleCameraActor.h"

#include "../UIactor/fadePanel/FadePanel.h"
#include "../actor/Player.h"
#include "../actor/tornado/Tornado.h"
#include "../actor/Cloud.h"
#include "../CloudSetting.h"
#include "../actor/StageGenerator.h"
#include "../game/Random.h"

/* 竜巻ポリゴン用データ */
const Vector3 STORM_POS = Vector3(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 5.0f * 2.0f, 0.0f);
const Vector2 SIZE_HALF = Vector2(150, 150);
const float x[4] = { STORM_POS.x + SIZE_HALF.x / 2.0f, STORM_POS.x - SIZE_HALF.x * 3, STORM_POS.x - SIZE_HALF.x / 2.0f, STORM_POS.x + SIZE_HALF.x * 3 };
const float y[4] = { STORM_POS.y - SIZE_HALF.y, STORM_POS.y + SIZE_HALF.y, STORM_POS.y + SIZE_HALF.y, STORM_POS.y - SIZE_HALF.y };
const float u[4] = { 0, 0, 1, 1 };
const float v[4] = { 0, 1, 1, 0 };
const int	StormMaxAlpha = 255 / 3;
const float StormAlphaEndTime = 6.0f;
/* タイトルテキスト用データ */
const float TitleAlphaEndTime = 2.0f;
/* スクリーン用データ */
const float endScreenPos = -(WINDOW_WIDTH / 2.0f);

//コンストラクタ
EventScene::EventScene()
{
	// 竜巻テクスチャハンドル
	texhandle = LoadGraph("res/Sprite/title_storm.png");
	// ポリゴンデータ作成
	for (int i = 0; i < 4; i++)
	{
		auto start = i % 4;
		auto end = (i + 1) % 4;
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
EventScene::~EventScene()
{

}

//開始
void EventScene::Initialize()
{
	wo.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wo, false, true, Vector3::Zero, Vector3::Forward));
	wo.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wo));

	timer = 0.0f;
	mIsEnd = false;
	status = EVENT_STATUS::EVENT_BEGIN;

	/* フォグ関係 */
	currentFogFar = 0;
	maxFogFar = 0;
	correctionFog = 50;
	fogTime = 0;
	fogPeriod = 1;
	SetFogEnable(TRUE);
	SetFogColor(180, 180, 200);
	SetFogStartEnd(0, 0);

	prePos = Vector3::Zero;
	velocity = Vector3::Zero;
	t = 1;

	isStageLook = false;

	gongCount = 0;
	stormVol = 1.0f;

	Camera::GetInstance().SetRange(0.1f, 40000.0f);

	/* 音 */
	Sound::GetInstance().PlayBGM(BGM_ID::INTRO_BGM);
	Sound::GetInstance().PlaySE(SE_ID::SAND_STORM_SE, DX_PLAYTYPE_LOOP);

	/* フェード */
	FadePanel::GetInstance().SetInTime(2.0f);
	FadePanel::GetInstance().SetOutTime(2.0f);

	// 以下マスターはいらない
	/* タイトルテキストデータ */
	titleAlpha = 0;
	isTitle = false;
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
}

void EventScene::Update()
{
	/* 各種更新 */
	wo.Update();

	/* イベントカット */
	if ((!FadePanel::GetInstance().IsAction()) &&
		(GamePad::GetInstance().ButtonTriggerDown(PADBUTTON::NUM8) ||
		Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE)))
	{
		FadePanel::GetInstance().FadeOut();
		status = EVENT_END;
	}

	/* カメラ設定 */
	Vector3 playerPos = wo.GetPlayer()->GetParameter().mat.GetPosition();
	Vector3 playerRight = Vector3::Left;

	switch (status)
	{
	case EVENT_BEGIN:
		if (maxFogFar < 150)
			maxFogFar += 30 * Time::GetInstance().deltaTime();
		if (fogTime >= 360)
		{
			fogTime = 0;
			fogPeriod = Random::GetInstance().Range(1.0f, 3.0f);
			correctionFog = Random::GetInstance().Range(30.0f, 50.0f);
		}

		targetPos = playerPos;
		cameraPos = playerPos + playerRight * 100;
		currentFogFar = maxFogFar + correctionFog * Math::Sin(fogTime);

		prePos = playerPos;

		if (timer > 5.0f && currentFogFar > 150)
		{
			status = EVENT_STATUS::EVENT_DRAGON_OUT;
		}
		break;
	case EVENT_DRAGON_OUT:
		currentFogFar = maxFogFar + 300 * Math::Abs(Math::Sin(fogTime / 4.0f));
		velocity = playerPos - prePos;
		prePos = playerPos;
		targetPos = playerPos;
		cameraPos += velocity * t;
		if (t > 0)
			t -= Time::GetInstance().deltaTime();
		t = Math::Clamp(t, 0.0f, 1.0f);

		if ((playerPos - cameraPos).Length() >= 500 && !isTitle &&
			!FadePanel::GetInstance().IsAction())
		{
			FadePanel::GetInstance().FadeOut();
			status = EVENT_STATUS::EVENT_DRAGON_END;
		}
		break;
	case EVENT_DRAGON_END:
		if (!FadePanel::GetInstance().IsAction())
		{
			wo.GetPlayer()->SetIsDead(true);
			wo.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<StageGenerator>(wo, "TitleStage", false));
			for (int i = 0; i < CLOUD_LOW_POSITION_NUM; i++)
				wo.Add(ACTOR_ID::CLOUD_ACTOR, std::make_shared<Cloud>(wo, Vector3(Random::GetInstance().Range(-5000.0f, 5000.0f), 0.0f, Random::GetInstance().Range(-5000.0f, 5000.0f))));
			for (int i = 0; i < CLOUD_HIGH_POSITION_NUM; i++)
				wo.Add(ACTOR_ID::CLOUD_ACTOR, std::make_shared<Cloud>(wo, Vector3(Random::GetInstance().Range(-5000.0f, 5000.0f), 1400.0f, Random::GetInstance().Range(-5000.0f, 5000.0f))));

			currentFogFar = 60000;

			targetPos = Vector3(0.0f, 1840.0f, -15264.0f);
			cameraPos = Vector3(2225.0f, -312.0f, 4587.0f);

			isStageLook = true;
			stormVol = 0;

			Sound::GetInstance().SetSEVolume(SE_ID::SAND_STORM_SE, stormVol);
			Sound::GetInstance().SetSEVolume(SE_ID::STORMAKED_SE, 0.0f);
			Sound::GetInstance().PlaySE(SE_ID::SAND_STORM_SE);
			FadePanel::GetInstance().SetOutTime(0.5f);
			FadePanel::GetInstance().FadeIn();
			status = EVENT_STATUS::EVENT_STAGE_IN;
		}
		break;
	case EventScene::EVENT_STAGE_IN:
		currentFogFar -= 7500.0f * Time::GetInstance().deltaTime();
		
		stormVol = 10000.0f / currentFogFar;
		stormVol = Math::Clamp(stormVol, 0.2f, 1.0f);
		Sound::GetInstance().SetSEVolume(SE_ID::SAND_STORM_SE, stormVol);
		if (currentFogFar < 10000 && stormVol >= 1.0f)
		{
			wo.Add(ACTOR_ID::TORNADO_ACTOR, std::make_shared<Tornado>(wo, Vector3(3000.0f, 0.0f, 0.0f), Vector2(100), Vector3::Zero, 800.0f, true));
			status = EventScene::EVENT_GONG;
		}
		break;
	case EventScene::EVENT_GONG:
		if ((!Sound::GetInstance().IsPlaySE(SE_ID::STORMAKED_SE)) &&
			(!Sound::GetInstance().IsPlaySE(SE_ID::GONG_SE)))
		{
			Sound::GetInstance().PlaySE(SE_ID::GONG_SE);
			gongCount++;
		}
		if (gongCount >= 3)
		{
			FadePanel::GetInstance().FadeOut();
			status = EVENT_END;
		}
		break;
	case EventScene::EVENT_END:
		if (!FadePanel::GetInstance().IsAction())
			mIsEnd = true;
		break;
	}


	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Z))
		isTitle = !isTitle;
	if (isTitle)
	{
		// 竜巻とテキスト描画開始
		stormAlphaTime += (Time::GetInstance().deltaTime() / StormAlphaEndTime);
		stormAlpha = (int)(StormMaxAlpha * stormAlphaTime);
		stormAlpha = Math::Clamp(stormAlpha, 0, StormMaxAlpha);
		for (int i = 0; i < 6; i++)
		{
			Vertex2D_1[i].dif.a = stormAlpha;
			Vertex2D_2[i].dif.a = stormAlpha;
		}

		if (stormAlpha >= StormMaxAlpha / 2)
			titleAlpha += Time::GetInstance().deltaTime() / TitleAlphaEndTime;
	}
	else
	{
		titleAlpha = 0;
		stormAlphaTime = 0;
		stormAlpha = 0;
		for (int i = 0; i < 6; i++)
		{
			Vertex2D_1[i].dif.a = stormAlpha;
			Vertex2D_2[i].dif.a = stormAlpha;
		}
	}


	/* 竜巻ポリゴンの計算 */
	TornadoCalculation();

	/* カメラ設定 */
	Camera::GetInstance().Position.Set(cameraPos);
	Camera::GetInstance().Target.Set(targetPos);
	Camera::GetInstance().Update();

	SetFogStartEnd(0, currentFogFar);

	timer += Time::GetInstance().deltaTime();
	fogTime += fogPeriod;
}

//描画
void EventScene::Draw() const
{
	wo.Draw();

	if (isStageLook)
	{
		Model::GetInstance().Draw(MODEL_ID::GONG_MODEL, Vector3(1648.6f, -93.0f, 4023.7f), 1, Vector3(0.0f, 90.0f, 0.0f), Vector3(4.0f), true);
		Model::GetInstance().Draw(MODEL_ID::GONG_MODEL, Vector3(1819.4f, -93.0f, 4032.3f), 1, Vector3(0.0f, 90.0f, 0.0f), Vector3(4.0f), true);
	}

	/* 竜巻 */
	DrawPolygon2D(Vertex2D_1, 2, texhandle, true);
	DrawPolygon2D(Vertex2D_2, 2, texhandle, true);
	DrawPolygon2D(Vertex2D_1, 2, Model::GetInstance().GetHandle(MODEL_ID::TEST_MODEL), true);

	/* テキスト */
	// タイトル
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_TEXT_SPRITE, Vector2(STORM_POS.x, STORM_POS.y), Vector2(450, 175), titleAlpha, Vector2(0.6f), true, false);
}

//終了しているか？
bool EventScene::IsEnd() const
{
	return mIsEnd;
}

//次のシーンを返す
Scene EventScene::Next() const
{
	return Scene::GamePlay;
}

Scene EventScene::GetCurrentScene() const
{
	return Scene::Event;
}

void EventScene::End()
{
	wo.Clear();
	SetLightPosition(Vector3::Zero.ToVECTOR());
	SetLightDirection(Vector3(0.5f, -0.5f, -0.5f).ToVECTOR());
	SetFogEnable(FALSE);
	Sound::GetInstance().StopSE(SE_ID::SAND_STORM_SE);
	Sound::GetInstance().SetSEVolume(SE_ID::SAND_STORM_SE, 1.0f);
	Sound::GetInstance().SetSEVolume(SE_ID::STORMAKED_SE, 0.0f);
}

// 竜巻計算用
void EventScene::TornadoCalculation()
{
	amount_1 += Time::GetInstance().deltaTime() / 4.0f;
	amount_2 += Time::GetInstance().deltaTime() / 16.0f;
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
void EventScene::VertexMove(VERTEX2D vertexs_[], int count_, float time_)
{
	for (int i = 0; i < 4; i++)
	{
		auto start = (i + count_) % 4;
		auto end = (i + count_ + 1) % 4;
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

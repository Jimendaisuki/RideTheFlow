#include"EndhingScene.h"
#include "../math/Math.h"
#include "../math/Vector2.h"
#include "../game/Random.h"
#include "../time/Time.h"
#include "../input/Keyboard.h"
#include "../input/GamePad.h"
#include "../sound/Sound.h"
#include "../actor/Player.h"
#include "../actor/Stage.h"
#include "../actor/StageGenerator.h"
#include "../actor/Cloud.h"
#include "../CloudSetting.h"
#include "../camera/Camera.h"
#include "../UIactor/fadePanel/FadePanel.h"
#include "../UIactor/Clear.h"
#include "../game/WorkFolder.h"

float const LENGTH = 6000.0f;
float const HEIGHT = 2000.0f;

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
EndhingScene::EndhingScene()
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
EndhingScene::~EndhingScene()
{
}

//開始
void EndhingScene::Initialize()
{
	mIsEnd = false;
	status = ENDING_STATUS::ENDING_DRAGON_OUT;
	wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wa));
	wa.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<StageGenerator>(wa, "TitleStage", false , true));

	isTitle = false;

	/* フォグ関係 */
	SetFogEnable(TRUE);
	SetFogColor(180, 180, 200);
	currentFog = 20000;
	SetFogStartEnd(0.0f, currentFog);

	/* カメラ関係 */
	targetPos = Vector3(0.0f, 1840.0f, -15264.0f);
	cameraPos = Vector3(2225.0f, -312.0f, 4587.0f);
	Camera::GetInstance().Position.Set(cameraPos);
	Camera::GetInstance().Target.Set(targetPos);
	Camera::GetInstance().Update();

	wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wa, false, true, Vector3(2200.0f, -200.0f, 4200.0f), Vector3(-0.5f, 0.8f, -1.0f)));
	for (int i = 0; i < CLOUD_LOW_POSITION_NUM; i++)
		wa.Add(ACTOR_ID::CLOUD_ACTOR, std::make_shared<Cloud>(wa, Vector3(Random::GetInstance().Range(-5000.0f, 5000.0f), 0.0f, Random::GetInstance().Range(-5000.0f, 5000.0f))));
	for (int i = 0; i < CLOUD_HIGH_POSITION_NUM; i++)
		wa.Add(ACTOR_ID::CLOUD_ACTOR, std::make_shared<Cloud>(wa, Vector3(Random::GetInstance().Range(-5000.0f, 5000.0f), 1400.0f, Random::GetInstance().Range(-5000.0f, 5000.0f))));

	status = ENDING_DRAGON_OUT;
	currentFog = 1000;
	length = 0;
	seVol = 1.0f;

	/* サウンド */
	Sound::GetInstance().SetSEVolume(SE_ID::SAND_STORM_SE, seVol);
	Sound::GetInstance().PlaySE(SE_ID::SAND_STORM_SE);

	/* フェード */
	FadePanel::GetInstance().SetInTime(1.0f);
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

void EndhingScene::Update()
{
	wa.Update();

	switch (status)
	{
	case EndhingScene::ENDING_DRAGON_OUT:
		length = (cameraPos - wa.GetPlayer()->GetParameter().mat.GetPosition()).Length();
		seVol = (1.0f - length / 1500.0f) * 3.0f;
		seVol = Math::Clamp(seVol, 0.0f, 1.0f);
		Sound::GetInstance().SetSEVolume(SE_ID::SAND_STORM_SE, seVol);
		if (length >= 1500.0f)
		{
			if (!isTitle)
				wa.UIAdd(UI_ID::CLEAR_UI, std::make_shared<Clear>(wa));
			wa.GetPlayer()->SetIsDead(true);
			velocity = (cameraPos.Normalized() + Vector3(0.5f, 0.5f, 0.5f)).Normalized() * 2.0f;
			Sound::GetInstance().PlayBGM(BGM_ID::CLEAR_BGM);
			status = ENDING_CLEAR;
		}
		break;
	case EndhingScene::ENDING_CLEAR:
		currentFog += 6000 * Time::DeltaTime;
		targetPos += velocity;
		cameraPos += velocity;
		if (currentFog >= 40000)
			status = EndhingScene::ENDING_END;
		break;
	case EndhingScene::ENDING_END:
		targetPos += velocity;
		cameraPos += velocity;
		currentFog += 8000 * Time::DeltaTime;

		if (!Sound::GetInstance().IsPlayBGM() &&
			FadePanel::GetInstance().IsFullBlack())
		{
			mIsEnd = true;
			return;
		}
		if (!FadePanel::GetInstance().IsAction())
		{
			FadePanel::GetInstance().SetOutTime(8.0f);
			FadePanel::GetInstance().FadeOut();
		}
		break;
	default:
		break;
	}


	SetFogStartEnd(0, currentFog);

	/* カメラ */
	Camera::GetInstance().Up.Set(Vector3::Up);
	Camera::GetInstance().SetRange(0.1f, 40000.0f);
	Camera::GetInstance().Position.Set(cameraPos);
	Camera::GetInstance().Target.Set(targetPos);
	Camera::GetInstance().Update();

	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Z))
		isTitle = !isTitle;
	if (isTitle)
	{
		// 竜巻とテキスト描画開始
		stormAlphaTime += (Time::DeltaTime / StormAlphaEndTime);
		stormAlpha = (int)(StormMaxAlpha * stormAlphaTime);
		stormAlpha = Math::Clamp(stormAlpha, 0, StormMaxAlpha);
		for (int i = 0; i < 6; i++)
		{
			Vertex2D_1[i].dif.a = 84;
			Vertex2D_2[i].dif.a = 84;
		}

		titleAlpha = 1.0f;
		//if (stormAlpha >= StormMaxAlpha / 2)
		//	titleAlpha += Time::DeltaTime / TitleAlphaEndTime;
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
}

//描画
void EndhingScene::Draw() const
{
	wa.Draw();

	/* 竜巻 */
	DrawPolygon2D(Vertex2D_1, 2, texhandle, true);
	DrawPolygon2D(Vertex2D_2, 2, texhandle, true);
	//DrawPolygon2D(Vertex2D_1, 2, Model::GetInstance().GetHandle(MODEL_ID::TEST_MODEL), true);

	/* テキスト */
	// タイトル
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_TEXT_SPRITE, Vector2(STORM_POS.x, STORM_POS.y), Vector2(450, 175), titleAlpha, Vector2(0.6f), true, false);
}

//終了しているか？
bool EndhingScene::IsEnd() const
{
	return mIsEnd;
}

//次のシーンを返す
Scene EndhingScene::Next() const
{
	return Scene::Title;
}

void EndhingScene::End()
{
	wa.Clear();
	Sound::GetInstance().StopBGM();
	SetFogEnable(FALSE);
}

// 竜巻計算用
void EndhingScene::TornadoCalculation()
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
void EndhingScene::VertexMove(VERTEX2D vertexs_[], int count_, float time_)
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
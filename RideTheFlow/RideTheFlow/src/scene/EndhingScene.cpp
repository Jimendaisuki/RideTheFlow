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

float const LENGTH = 6000.0f;
float const HEIGHT = 2000.0f;

//コンストラクタ
EndhingScene::EndhingScene()
{
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

	//angle = 0.0f;
	//float x = Math::Sin(angle) * LENGTH;
	//float z = Math::Cos(angle) * LENGTH;
	//cameraPos = Vector3(x, HEIGHT, z);
	//targetPos = Vector3::Zero;

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

	wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wa, false, true, Vector3(2100.0f, -100.0f, 4100.0f), Vector3(-0.5f, 0.8f, -1.0f)));
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
}

void EndhingScene::Update()
{
	wa.Update();

	switch (status)
	{
	//case EndhingScene::ENDING_BEGIN:
	//	angle += Time::DeltaTime * 40.0;
	//	x = Math::Sin(angle) * LENGTH;
	//	z = Math::Cos(angle) * LENGTH;
	//	cameraPos = Vector3(x, HEIGHT, z);
	//	targetPos = Vector3::Up * 2000.0f;
	//	if (angle > 360.0f)
	//	{
	//		FadePanel::GetInstance().FadeOut();
	//		status = ENDING_FADEOUT;
	//	}
	//	break;
	//case EndhingScene::ENDING_FADEOUT:
	//	angle += Time::DeltaTime * 40.0;
	//	x = Math::Sin(angle) * LENGTH;
	//	z = Math::Cos(angle) * LENGTH;
	//	cameraPos = Vector3(x, HEIGHT, z);
	//	targetPos = Vector3::Up * 2000.0f;
	//	if (!FadePanel::GetInstance().IsAction())
	//	{
	//		wa.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wa, false, true, Vector3(2100.0f, -100.0f, 4100.0f), Vector3(-0.5f, 0.8f, -1.0f)));
	//		status = ENDING_DRAGON_OUT;
	//		currentFog = 1000;
	//		FadePanel::GetInstance().SetInTime(1.0f);
	//		FadePanel::GetInstance().FadeIn();
	//	}
	//	break;
	case EndhingScene::ENDING_DRAGON_OUT:
		length = (cameraPos - wa.GetPlayer()->GetParameter().mat.GetPosition()).Length();
		seVol = (1.0f - length / 1500.0f) * 3.0f;
		seVol = Math::Clamp(seVol, 0.0f, 1.0f);
		Sound::GetInstance().SetSEVolume(SE_ID::SAND_STORM_SE, seVol);
		if (length >= 1500.0f)
		{
			wa.UIAdd(UI_ID::CLEAR_UI, std::make_shared<Clear>(wa));
			wa.GetPlayer()->SetIsDead(true);
			velocity = (cameraPos.Normalized() + Vector3(0.5f, 0.5f, 0.5f)).Normalized() * 10.0f;
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

		if (!Sound::GetInstance().IsPlayBGM())
		{
			mIsEnd = true;
			return;
		}
		if (!FadePanel::GetInstance().IsAction())
		{
			FadePanel::GetInstance().SetOutTime(3.0f);
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
}

//描画
void EndhingScene::Draw() const
{
	wa.Draw();
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
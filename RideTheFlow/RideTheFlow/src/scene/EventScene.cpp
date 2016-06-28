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
#include "../actor/StageGenerator.h"
#include "../game/Random.h"

/* �����|���S���p�f�[�^ */
const Vector3 STORM_POS = Vector3(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 5.0f * 2.0f, 0.0f);
const Vector2 SIZE_HALF = Vector2(150, 150);
const float x[4] = { STORM_POS.x + SIZE_HALF.x / 2.0f, STORM_POS.x - SIZE_HALF.x * 3, STORM_POS.x - SIZE_HALF.x / 2.0f, STORM_POS.x + SIZE_HALF.x * 3 };
const float y[4] = { STORM_POS.y - SIZE_HALF.y, STORM_POS.y + SIZE_HALF.y, STORM_POS.y + SIZE_HALF.y, STORM_POS.y - SIZE_HALF.y };
const float u[4] = { 0, 0, 1, 1 };
const float v[4] = { 0, 1, 1, 0 };
const int	StormMaxAlpha = 255 / 3;
const float StormAlphaEndTime = 6.0f;
/* �^�C�g���e�L�X�g�p�f�[�^ */
const float TitleAlphaEndTime = 2.0f;
/* �X�N���[���p�f�[�^ */
const float endScreenPos = -(WINDOW_WIDTH / 2.0f);

//�R���X�g���N�^
EventScene::EventScene()
{
	// �����e�N�X�`���n���h��
	texhandle = LoadGraph("res/Sprite/title_storm.png");
	// �|���S���f�[�^�쐬
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

//�f�X�g���N�^
EventScene::~EventScene()
{

}

//�J�n
void EventScene::Initialize()
{
	wo.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wo, false));
	wo.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wo));

	timer = 0.0f;
	mIsEnd = false;
	status = EVENT_STATUS::EVENT_BEGIN;

	/* �|���S���f�[�^ */
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

	/* �^�C�g���e�L�X�g�f�[�^ */
	titleAlpha = 0;

	currentFogFar = 0;
	maxFogFar = 0;
	correctionFog = 50;
	fogTime = 0;
	fogPeriod = 1;

	SetFogEnable(TRUE);
	SetFogColor(180, 180, 200);
	SetFogStartEnd(0, 0);

	isTitle = false;

	prePos = Vector3::Zero;
	velocity = Vector3::Zero;
	t = 1;

	//Sound::GetInstance().PlayBGM(BGM_ID::INGAME_BGM);

	Camera::GetInstance().SetRange(0.1f, 40000.0f);
	FadePanel::GetInstance().SetInTime(3.0f);
}

void EventScene::Update()
{
	/* �e��X�V */
	wo.Update();

	//if (!Sound::GetInstance().IsPlayBGM())
	//	Sound::GetInstance().PlayBGM(BGM_ID::INGAME_BGM);

	/* �J�����ݒ� */
	Vector3 playerPos = wo.GetPlayer()->GetParameter().mat.GetPosition();
	Vector3 playerRight = -wo.GetPlayer()->GetParameter().mat.GetLeft().Normalized();

	switch (status)
	{
	case EVENT_BEGIN:
		if (maxFogFar < 150)
			maxFogFar += 30 * Time::DeltaTime;
		if (fogTime >= 360)
		{
			fogTime = 0;
			fogPeriod = Random::GetInstance().Range(1.0f, 3.0f);
			correctionFog - Random::GetInstance().Range(30.0f, 50.0f);
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
			t -= Time::DeltaTime;
		t = Math::Clamp(t, 0.0f, 1.0f);

		if ((playerPos - cameraPos).Length() >= 500 && !isTitle)
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
			currentFogFar = 60000;

			targetPos = Vector3(0.0f, 1840.0f, -15264.0f);
			cameraPos = Vector3(2225.0f, -312.0f, 4587.0f);

			//SetLightPosition(Vector3(2225.0f * 30, 312.0f * 100, 4587.0f * 30).ToVECTOR());
			//SetLightDirection(-Vector3(2225.0f * 10, 312.0f * 100, 4587.0f * 10).Normalized());

			FadePanel::GetInstance().FadeIn();
			status = EVENT_STATUS::EVENT_STAGE_IN;
		}
		break;
	case EventScene::EVENT_STAGE_IN:
		currentFogFar -= 6000 * Time::DeltaTime;
		if (currentFogFar < 10000)
		{
			wo.Add(ACTOR_ID::TORNADO_ACTOR, std::make_shared<Tornado>(wo, Vector3(3000.0f, 0.0f, 0.0f), Vector2(100), Vector3::Zero, 200.0f));
			status = EventScene::EVENT_GONG;
		}
		break;
	case EventScene::EVENT_GONG:
		Sound::GetInstance().PlaySE(SE_ID::GONG_SE);
		status = TITLE_END;
		break;
	default:
		break;
	}


	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Z))
		isTitle = !isTitle;

	if (isTitle)
	{
		// �����ƃe�L�X�g�`��J�n
		stormAlphaTime += (Time::DeltaTime / StormAlphaEndTime);
		stormAlpha = (int)(StormMaxAlpha * stormAlphaTime);
		stormAlpha = Math::Clamp(stormAlpha, 0, StormMaxAlpha);
		for (int i = 0; i < 6; i++)
		{
			Vertex2D_1[i].dif.a = stormAlpha;
			Vertex2D_2[i].dif.a = stormAlpha;
		}

		if (stormAlpha >= StormMaxAlpha / 2)
			titleAlpha += Time::DeltaTime / TitleAlphaEndTime;
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


	/* �����|���S���̌v�Z */
	TornadoCalculation();

	/* �J�����ݒ� */
	Camera::GetInstance().Position.Set(cameraPos);
	Camera::GetInstance().Target.Set(targetPos);


	SetFogStartEnd(0, currentFogFar);
	Camera::GetInstance().Update();

	timer += Time::DeltaTime;
	fogTime += fogPeriod;

	/* �ȉ��f�o�b�O�p */
	// �V�[���I��
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE))
	{
		mIsEnd = true;
	}
}

//�`��
void EventScene::Draw() const
{
	wo.Draw();

	Model::GetInstance().Draw(MODEL_ID::GONG_MODEL, Vector3(1648.6f, -93.0f, 4023.7f), 1, Vector3(0.0f, 90.0f, 0.0f), Vector3(4.0f), true);
	Model::GetInstance().Draw(MODEL_ID::GONG_MODEL, Vector3(1819.4f, -93.0f, 4032.3f), 1, Vector3(0.0f, 90.0f, 0.0f), Vector3(4.0f), true);

	/* ���� */
	DrawPolygon2D(Vertex2D_1, 2, texhandle, true);
	DrawPolygon2D(Vertex2D_2, 2, texhandle, true);
	DrawPolygon2D(Vertex2D_1, 2, Model::GetInstance().GetHandle(MODEL_ID::TEST_MODEL), true);

	/* �e�L�X�g */
	// �^�C�g��
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_TEXT_SPRITE, Vector2(STORM_POS.x, STORM_POS.y), Vector2(450, 175), titleAlpha, Vector2(0.6f), true, false);
}

//�I�����Ă��邩�H
bool EventScene::IsEnd() const
{
	return mIsEnd;
}

//���̃V�[����Ԃ�
Scene EventScene::Next() const
{
	return Scene::GamePlay;
}

void EventScene::End()
{
	wo.Clear();
	SetLightPosition(Vector3::Zero.ToVECTOR());
	SetLightDirection(Vector3(0.5f, -0.5f, -0.5f).ToVECTOR());
	SetFogEnable(FALSE);
	Sound::GetInstance().StopBGM();
}

// �����v�Z�p
void EventScene::TornadoCalculation()
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
	// ���_�̈ړ�
	VertexMove(Vertex2D_1, count_1, amount_1);
	VertexMove(Vertex2D_2, count_2, amount_2);
	// ���L���_�f�[�^�R�s�[
	Vertex2D_1[4] = Vertex2D_1[0];
	Vertex2D_1[5] = Vertex2D_1[2];
	Vertex2D_2[4] = Vertex2D_2[0];
	Vertex2D_2[5] = Vertex2D_2[2];
}

// ���_�ړ�
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
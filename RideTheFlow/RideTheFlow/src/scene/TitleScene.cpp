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

#include "../actor/Stage.h"
#include "../actor/CameraActor.h"
#include "../actor/TitleCameraActor.h"

#include "../UIactor/fadePanel/FadePanel.h"
#include "../UIactor/menuPanel/MenuPanel.h"
#include "../UIactor/Clear.h"
#include "../UIactor/Failure.h"
#include "../UIactor/MiniMap.h"
#include "../actor/Player.h"

float	fpsTimer = 0.0f;
float	fps;
int		effectNum = 0;

int	modelHandle = 0;
int frameCount = 0;
int frameNum = 0;
int frameParentCount = 0;
int frameChildCount = 0;

float testStamina = 0;
float testMaxStamina = 100;
float testHP = 0;

/* 竜巻ポリゴン用データ */
const Vector3 STORM_POS = Vector3(WINDOW_WIDTH / 2.0f, WINDOW_HEIGHT / 5.0f * 2.0f, 0.0f);
const Vector2 SIZE_HALF = Vector2(150, 150);
const float x[4] = { STORM_POS.x + SIZE_HALF.x / 2.0f, STORM_POS.x - SIZE_HALF.x * 3, STORM_POS.x - SIZE_HALF.x / 2.0f, STORM_POS.x + SIZE_HALF.x * 3 };
const float y[4] = { STORM_POS.y - SIZE_HALF.y, STORM_POS.y + SIZE_HALF.y, STORM_POS.y + SIZE_HALF.y, STORM_POS.y - SIZE_HALF.y };
const float u[4] = { 0, 0, 1, 1 };
const float v[4] = { 0, 1, 1, 0 };
const int	StormMaxAlpha		= 255 / 3;
const float StormAlphaEndTime	= 2.5f;
/* タイトルテキスト用データ */
const float TitleAlphaEndTime	= 4.0f;

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

}

//開始
void TitleScene::Initialize()
{
	timer = 0.0f;
	mIsEnd = false;
	status = TITLE_STATUS::TITLE_BEGIN;
	wo.Add(ACTOR_ID::STAGE_ACTOR, std::make_shared<Stage>(wo));
	//wo.Add(ACTOR_ID::CAMERA_ACTOR, std::make_shared<TitleCameraActor>(wo));
	
	//WorkFolder::SetWorkFolder("res/Model/");
	//Model::GetInstance().Load("dra_test.pmx", MODEL_ID::TEST_MODEL, false);

	modelHandle = Model::GetInstance().GetHandle(MODEL_ID::TEST_STAGE);
	frameCount = MV1GetFrameNum(modelHandle);
	frameParentCount = MV1GetFrameParent(modelHandle, frameNum);
	frameChildCount = MV1GetFrameChildNum(modelHandle, frameNum);

	position = Vector3::Zero;
	
	//wo.UIAdd(UI_ID::FAILERE_UI, std::make_shared<Failure>(wo));
	//wo.UIAdd(UI_ID::CLEAR_UI, std::make_shared<Clear>(wo));

	/* マップテスト用 */
	//wo.Add(ACTOR_ID::PLAYER_ACTOR, std::make_shared<Player>(wo));
	/*wo.UIAdd(UI_ID::MINIMAP_UI, std::make_shared<MiniMap>(wo));
*/
	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Position.Set(Vector3(0, 500, -200));
	Camera::GetInstance().Target.Set(position);
	Camera::GetInstance().Up.Set(Vector3::Up);


	/* ポリゴンデータ */
	amount_1 = 0;
	amount_2 = 0;
	count_1 = 0;
	count_2 = 0;
	stormAlpha = 0;
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

	MenuPanel::GetInstance().Initialize();

	/* フェード */
	FadePanel::GetInstance().Initialize();
	FadePanel::GetInstance().FadeIn(2.0f);
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
		status = TITLE_STATUS::TITLE_TEXTURE_IN;
		break;
	case TITLE_TEXTURE_IN:
		// 竜巻とテキスト描画開始
		stormAlpha += (255.0f * Time::DeltaTime) / StormAlphaEndTime;
		stormAlpha = Math::Clamp(stormAlpha, 0, StormMaxAlpha);
		for (int i = 0; i < 6; i++)
		{
			Vertex2D_1[i].dif.a = stormAlpha;
			Vertex2D_2[i].dif.a = stormAlpha;
		}
		
		if (stormAlpha >= 255 / 4)
			titleAlpha += Time::DeltaTime / TitleAlphaEndTime;

		if (titleAlpha >= 1.0f)
			status = TITLE_STATUS::TITLE_STANDBY;
		break;
	case TITLE_STANDBY:
		// 入力待機
		if (pressTextAlpha < 1) 
			pressTextAlpha += Time::DeltaTime;
		pressAlphaTime += Time::DeltaTime * 60 * 3;
		pressAlphaTime = (int)pressAlphaTime % 360;
		pressTextBackAlpha = Math::Sin(pressAlphaTime);

		// シーン終了
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Z) ||
			GamePad::GetInstance().AnyTriggerDown())
		{
			FadePanel::GetInstance().FadeOut(2.0f);
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

	/* 各種更新 */
	MenuPanel::GetInstance().Update();
	FadePanel::GetInstance().Update();
	wo.Update();

	/* 以下デバッグ用 */
	// シーン終了
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::SPACE))
	{
		mIsEnd = true;
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

		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::X)){
			FadePanel::GetInstance().FadeOut(0.2f, 0.7f);
		}
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::C)){
			FadePanel::GetInstance().FadeOut(0.5f);
		}
		if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::V)){
			FadePanel::GetInstance().FadeIn(0.5f);
		}

		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::R))testHP++;
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::F))testHP--;
		testHP = Math::Clamp(testHP, 0.0f, 100.0f);

		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::T))testStamina++;
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::G))testStamina--;
	}

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::M))MenuPanel::GetInstance().Action(Scene::GamePlay);


	Camera::GetInstance().Position.Set(Vector3(0, 100, -100));
	Camera::GetInstance().Target.Set(Vector3(0, 100, 0));
	Camera::GetInstance().Update();
}

//描画
void TitleScene::Draw() const
{
	wo.Draw();

	if (!IsStatusBegEnd()) FadePanel::GetInstance().Draw();

	/* 竜巻 */
	DrawPolygon2D(Vertex2D_1, 2, texhandle, true);
	DrawPolygon2D(Vertex2D_2, 2, texhandle, true);

	/* テキスト */
	// タイトル
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_TEXT_SPRITE, Vector2(STORM_POS.x, STORM_POS.y), Vector2(450, 175), titleAlpha, Vector2(0.6f), true, false);
	// エニープッシュ
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_PRESS_BACK_SPRITE, Vector2(STORM_POS.x, STORM_POS.y + WINDOW_HEIGHT / 3), Vector2(500, 50), pressTextBackAlpha, Vector2(0.6f + pressScale), true, false);
	Sprite::GetInstance().Draw(SPRITE_ID::TITLE_PRESS_SPRITE, Vector2(STORM_POS.x, STORM_POS.y + WINDOW_HEIGHT / 3), Vector2(500, 50), pressTextAlpha, Vector2(0.6f + pressScale), true, false);

	MenuPanel::GetInstance().Draw();
	if (IsStatusBegEnd()) FadePanel::GetInstance().Draw();

	DrawFormatString(0, 0, GetColor(255, 255, 255), "TitleScene");
	DrawFormatString(0, 20, GetColor(255, 255, 255), "FPS:		%.1f", fps);
	DrawFormatString(0, 220, GetColor(255, 0, 0), "M		: メニュー");
	DrawFormatString(0, 240, GetColor(255, 0, 0), "N		: ○");
	DrawFormatString(0, 260, GetColor(255, 0, 0), "B		: ×");
	DrawFormatString(0, 280, GetColor(255, 0, 0), "C		: フェードアウト");
	DrawFormatString(0, 300, GetColor(255, 0, 0), "V		: フェードイン");
	//DrawFormatString(0, 200, GetColor(0, 0, 0), "FrameNum  : %d", frameNum);
	//DrawFormatString(0, 220, GetColor(0, 0, 0), "FrameName : %s", MV1GetFrameName(modelHandle, frameNum));
	//DrawFormatString(0, 240, GetColor(0, 0, 0), "FramePare : %d", frameParentCount);
	//DrawFormatString(0, 260, GetColor(0, 0, 0), "FrameChild: %d", frameChildCount);
	//Vector3 position = Vector3::ToVECTOR(MV1GetFramePosition(modelHandle, frameNum));
	//DrawFormatString(0, 280, GetColor(0, 0, 0), "FramePos  : [%f] [%f] [%f]", position.x, position.y, position.z);
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
}

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

bool TitleScene::IsStatusBegEnd() const
{
	return (status == TITLE_STATUS::TITLE_BEGIN) || (status == TITLE_STATUS::TITLE_END);
}
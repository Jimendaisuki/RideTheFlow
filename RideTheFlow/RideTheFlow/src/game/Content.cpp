#include "Content.h"
#include "../game/WorkFolder.h"
#include "../graphic/Model.h"
#include "../graphic/Sprite.h"
#include "../sound/Sound.h"
#include "../Def.h"
#include "../math/Math.h"

// 画像を読み込む
void Content::LoadSprite(Sprite& sprite, Model& model)
{
	WorkFolder::SetWorkFolder("res/Sprite/");
	sprite.Load("body.png", SPRITE_ID::PLAYER_SPRITE);
	sprite.Load("images.png", SPRITE_ID::ENEMY_SPRITE);
	//sprite.Load("title.png");
	//model.Load2D("particleSprite.png");
}

// ３Ｄモデルを読み込む
void Content::LoadModel(Model& model, bool async)
{
	WorkFolder::SetWorkFolder("res/Model/");

	model.Load("Plane.x", MODEL_ID::PLANE_MODEL, async, 0, true);
	model.Load("X-G1.x", MODEL_ID::PLAYER_MODEL, async);
	model.Load("ryuu.pmd", MODEL_ID::TEST_MODEL, async);
	model.Load("renga.x", MODEL_ID::BOX_MODEL, async);

	model.Load("cylinder.x", MODEL_ID::TORNADO_MODEL, async);
	model.Load("box_x1.x", MODEL_ID::CASTLE_MODEL , async);

	model.Load("sandstage.x", MODEL_ID::STAGE_MODEL, async);
	model.Load("sky_dome_11.x", MODEL_ID::SKY_MODEL, async);
	model.Load("boonStage.pmd", MODEL_ID::TEST_STAGE, async);


	WorkFolder::SetWorkFolder("res/Model2D/");

	model.Load2D("smoke.png", MODEL_ID::RIGHT_GRAY_2D_MODEL);

	//model.Load("m1.pmx", async);
	//model.Load("m3.pmd", async);
}

// 音楽を読み込む
void Content::LoadSound(Sound& sound)
{
	WorkFolder::SetWorkFolder("res/Sound/");

	sound.LoadSE("button.mp3", SE_ID::BUTTON_SE, 0.9f);

	//sound.LoadBGM("title.mp3");
	//sound.LoadSE("se.wav", 0.9f);

	sound.SetAllBGMVolume(BGMVOLUME);
	sound.SetAllSEVolume(SEVOLUME);
}

void Content::EnableASync()
{
	SetUseASyncLoadFlag(TRUE);
}
void Content::DisableASync()
{
	SetUseASyncLoadFlag(FALSE);
}

template <typename T>
int Content::GetASyncLoadCount(T& content)
{
	return (content.GetCount() - GetASyncLoadNum() + 1);
}
template <>
int Content::GetASyncLoadCount(Sound& content)
{
	return ((content.GetCountBGM() + content.GetCountSE()) - GetASyncLoadNum() + 1);
}
int Content::GetASyncLoadAllCount(Model& model, Sprite& sprite, Sound& sound)
{
	auto count = model.GetCount() + sprite.GetCount() + sound.GetCountBGM() + sound.GetCountSE();
	return (count - GetASyncLoadNum() + 1);
}
bool Content::IsASync()
{
	return GetASyncLoadNum() > 0;
}
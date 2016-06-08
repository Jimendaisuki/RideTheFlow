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
	sprite.Load("smoke.png", SPRITE_ID::BEGIN_SPRITE);
	sprite.Load("sand.png", SPRITE_ID::SAND_SPRITE);
	sprite.Load("speedLine.png", SPRITE_ID::SPEED_SPRITE);
	sprite.Load("blood.png", SPRITE_ID::BLOOD_SPRITE);
	sprite.Load("damage.png", SPRITE_ID::DAMAGE_SPRITE);
	sprite.Load("staminagauge.png", SPRITE_ID::STAMINA_SPRITE);
	sprite.Load("staminaback.png", SPRITE_ID::STAMINA_BACK_SPRITE);
	sprite.Load("title_kiryuu.png", SPRITE_ID::TITLE_TEXT);
	sprite.Load("title_pressany.png", SPRITE_ID::TITLE_PRESS);
	sprite.Load("title_pressanyback.png", SPRITE_ID::TITLE_PRESS_BACK);

	//sprite.Load("title.png");
	//model.Load2D("particleSprite.png");
}

// ３Ｄモデルを読み込む
void Content::LoadModel(Model& model, bool async)
{
	WorkFolder::SetWorkFolder("res/Model/");

	model.Load("Plane.x", MODEL_ID::PLANE_MODEL, async, 0, true);
	model.Load("ryuu.pmd", MODEL_ID::TEST_MODEL, async);
	model.Load("renga.x", MODEL_ID::BOX_MODEL, async);

	model.Load("cylinder.x", MODEL_ID::TORNADO_MODEL, async);


	//model.Load("boonStage.pmd", MODEL_ID::STAGE_MODEL, async);
	model.Load("map.pmd", MODEL_ID::STAGE_MODEL, async);
	model.Load("map.pmd", MODEL_ID::TEST_STAGE, async);

	model.Load("sky_dome_11.x", MODEL_ID::SKY_MODEL, async);
	model.Load("arrow.pmd", MODEL_ID::ARROW_MODEL, async);
	model.Load("wind.x", MODEL_ID::WIND_MODEL, async);
	model.Load("cloud.x", MODEL_ID::CLOUD_MODEL, async);
	model.Load("tornadopoly.x", MODEL_ID::TORNADOPOLY_MODEL, async);
	//model.Load("boonStage.pmd", MODEL_ID::TEST_STAGE, async);
	//model.Load("cameramap.pmd", MODEL_ID::TEST_STAGE, async);

	model.Load("ballista.mv1", MODEL_ID::BALLISTA_MODEL, async);
	model.Load("ballista_arrow.mv1", MODEL_ID::BALLISTA_ARROW_MODEL, async);
	model.Load("cannon.mv1", MODEL_ID::CANNON_MODEL, async);
	model.Load("cannon_ball.mv1", MODEL_ID::CANNON_BALL_MODEL, async);

	
	model.Load("gong.mv1", MODEL_ID::GONG_MODEL, async);
	model.Load("home.mv1", MODEL_ID::HOME_MODEL, async);
	model.Load("isle_1.mv1", MODEL_ID::ISLE_1_MODEL, async);
	model.Load("isle_2.mv1", MODEL_ID::ISLE_2_MODEL, async);
	model.Load("isle_3.mv1", MODEL_ID::ISLE_3_MODEL, async);

	model.Load("ship.mv1", MODEL_ID::SHIP_MODEL, async);
	model.Load("dragonspear.pmx", MODEL_ID::DORAGON_SPEAR_MODEL);
	model.Load("dragonspear_tube.pmx", MODEL_ID::DORAGON_SPEAR_TUBE_MODEL);

	model.Load("dragonspear_tube.pmx", MODEL_ID::DORAGON_SPEAR_TUBE_MODEL);

	model.Load("Castle/castle_Master.pmx", MODEL_ID::CASTLE_MASTER_MODEL, async);
	model.Load("Castle/castle_base.pmx", MODEL_ID::CASTLE_BASE_MODEL, async);
	model.Load("Castle/castle_Top.pmx", MODEL_ID::CASTLE_TOP_MODEL, async);
	model.Load("Castle/castle_Top2.pmx", MODEL_ID::CASTLE_TOP2_MODEL, async);

	WorkFolder::SetWorkFolder("res/Model2D/");
	
	model.Load2D("smoke_black.png", MODEL_ID::SMOKE_2D, 2, Point(1, 2), Point(300, 200));
	model.Load2D("sand.png", MODEL_ID::SAND_2D);
	model.Load2D("wind.png", MODEL_ID::WIND_2D);

	

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
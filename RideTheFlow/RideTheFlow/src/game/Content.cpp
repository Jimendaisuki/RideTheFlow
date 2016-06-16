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
	/* エフェクト */
	sprite.Load("speedLine.png", SPRITE_ID::SPEED_SPRITE);
	sprite.Load("blood.png", SPRITE_ID::BLOOD_SPRITE);
	sprite.Load("damage.png", SPRITE_ID::DAMAGE_SPRITE);
	/* ミニマップ */
	sprite.Load("minimap.png", SPRITE_ID::MINIMAP_SPRITE);
	sprite.Load("playerpoint.png", SPRITE_ID::MAP_PLAYER_SPRITE);
	sprite.Load("enemypoint.png", SPRITE_ID::ENEMY_SPRITE);
	/* スタミナゲージ */
	sprite.Load("staminagauge.png", SPRITE_ID::STAMINA_SPRITE);
	sprite.Load("staminaback.png", SPRITE_ID::STAMINA_BACK_SPRITE);
	/* タイトルシーン */
	sprite.Load("title_kiryuu.png", SPRITE_ID::TITLE_TEXT_SPRITE);
	sprite.Load("title_pressany.png", SPRITE_ID::TITLE_PRESS_SPRITE);
	sprite.Load("title_pressanyback.png", SPRITE_ID::TITLE_PRESS_BACK_SPRITE);
	/* メニュー・ポーズ */
	sprite.Load("roll_1.png", SPRITE_ID::MENU_ROLL_1_SPRITE);
	sprite.Load("roll_2.png", SPRITE_ID::MENU_ROLL_2_SPRITE);
	sprite.Load("roll_3.png", SPRITE_ID::MENU_ROLL_3_SPRITE);
	sprite.Load("startgame.png", SPRITE_ID::START_GAME_SPRITE);
	sprite.Load("startgameback.png", SPRITE_ID::START_GAME_BACK_SPRITE);
	sprite.Load("backtogame.png", SPRITE_ID::BACK_TO_GAME_SPRITE);
	sprite.Load("backtogameback.png", SPRITE_ID::BACK_TO_GAME_BACK_SPRITE);
	sprite.Load("backtomenu.png", SPRITE_ID::BACK_TO_MENU_SPRITE);
	sprite.Load("backtomenuback.png", SPRITE_ID::BACK_TO_MENU_BACK_SPRITE);
	sprite.Load("exitgame.png", SPRITE_ID::EXIT_GAME_SPRITE);
	sprite.Load("exitgameback.png", SPRITE_ID::EXIT_GAME_BACK_SPRITE);
	sprite.Load("manual.png", SPRITE_ID::MANUAL_SPRITE);
	sprite.Load("manualback.png", SPRITE_ID::MANUAL_BACK_SPRITE);
	sprite.Load("manual1.png", SPRITE_ID::MANUAL_1_SPRITE);
	sprite.Load("manual2.png", SPRITE_ID::MANUAL_2_SPRITE);
	sprite.Load("manual3.png", SPRITE_ID::MANUAL_3_SPRITE);
	sprite.Load("manual4.png", SPRITE_ID::MANUAL_4_SPRITE);
	sprite.Load("point.png", SPRITE_ID::POINT_SPRITE);
	sprite.Load("tornadopolytex.png", SPRITE_ID::TORNADO_SPRITE);
	/* ゲームリザルト */
	sprite.Load("failedback.png", SPRITE_ID::FAILED_BACK_1_SPRITE);
	sprite.Load("failed.png", SPRITE_ID::FAILED_SPRITE);
	sprite.Load("clear.png", SPRITE_ID::CLEAR_SPRITE);
	/* フェード */
	sprite.Load("blackscreen.png", SPRITE_ID::BLACK_SCREEN);

	//sprite.Load("title.png");
	//model.Load2D("particleSprite.png");
}

// ３Ｄモデルを読み込む
void Content::LoadModel(Model& model, bool async)
{
	WorkFolder::SetWorkFolder("res/Model/");

	model.Load("Plane.x", MODEL_ID::PLANE_MODEL, async, 0, true);
	model.Load("dra_test.pmx", MODEL_ID::TEST_MODEL, async);
	model.Load("renga.x", MODEL_ID::BOX_MODEL, async);
	model.Load("cylinder.x", MODEL_ID::TORNADO_MODEL, async);
	model.Load("map.pmd", MODEL_ID::STAGE_MODEL, async);
	model.Load("map.pmd", MODEL_ID::TEST_STAGE, async);

	model.Load("sky_dome_11.x", MODEL_ID::SKY_MODEL, async);
	model.Load("arrow.mv1", MODEL_ID::ARROW_MODEL, async);
	model.Load("wind.x", MODEL_ID::WIND_MODEL, async);
	model.Load("cloud.x", MODEL_ID::CLOUD_MODEL, async);
	model.Load("sand.x", MODEL_ID::SAND_MODEL, async);
	model.Load("tornadopoly.x", MODEL_ID::TORNADOPOLY_MODEL, async);

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
	model.Load("dragonspear.mv1", MODEL_ID::DORAGON_SPEAR_MODEL);
	model.Load("dragonspear_tube.mv1", MODEL_ID::DORAGON_SPEAR_TUBE_MODEL);

	model.Load("Castle/castle_1.mv1", MODEL_ID::CASTLE_MASTER_MODEL, async);
	model.Load("Castle/castle_2.mv1", MODEL_ID::CASTLE_BASE_MODEL, async);
	model.Load("Castle/castle_4.mv1", MODEL_ID::CASTLE_TOP_MODEL, async);
	model.Load("Castle/castle_3.mv1", MODEL_ID::CASTLE_TOP2_MODEL, async);

	model.Load("sun.x", MODEL_ID::CASTLE_ADD_MODEL, async);

	WorkFolder::SetWorkFolder("res/Model2D/");
	
	model.Load2D("smoke_black.png", MODEL_ID::SMOKE_2D, 2, Point(1, 2), Point(300, 200));
	model.Load2D("sand.png", MODEL_ID::SAND_2D);
	model.Load2D("wind.png", MODEL_ID::WIND_2D);
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
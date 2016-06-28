#include "Content.h"
#include "../game/WorkFolder.h"
#include "../graphic/Model.h"
#include "../graphic/Sprite.h"
#include "../sound/Sound.h"
#include "../Def.h"
#include "../math/Math.h"
#include "../SEVolumeSetting.h"
#include "../BGMVolumeSetting.h"

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
	model.Load("dra_test.mv1", MODEL_ID::TEST_MODEL, async);
	model.Load("dra_test_title.mv1", MODEL_ID::TEST_TITLE_MODEL, async);
	
	//model.Load("dragon.mv1", MODEL_ID::TEST_MODEL, async);
	model.Load("renga.x", MODEL_ID::BOX_MODEL, async);
	model.Load("cylinder.x", MODEL_ID::TORNADO_MODEL, async);
	model.Load("map.pmd", MODEL_ID::STAGE_MODEL, async);
	model.Load("field.mv1", MODEL_ID::TEST_STAGE, async);
	model.Load("action_range.mv1", MODEL_ID::STAGE_ACTION_RANGE_MODEL, async);
	model.Load("sky_dome_11.X", MODEL_ID::SKY_MODEL, async);

	model.Load("arrow.mv1", MODEL_ID::ARROW_MODEL, async);
	model.Load("wind.mv1", MODEL_ID::WIND_MODEL, async);
	model.Load("wind_blue.mv1", MODEL_ID::WIND_BLUE_MODEL, async);
	model.Load("cloud.mv1", MODEL_ID::CLOUD_MODEL, async);
	model.Load("sand.mv1", MODEL_ID::SAND_MODEL, async);
	model.Load("tornadopoly.mv1", MODEL_ID::TORNADOPOLY_MODEL, async);

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

	model.Load("smoke.mv1", MODEL_ID::CASTLE_ADD_MODEL, async);
	model.Load("airball.mv1", MODEL_ID::AIR_BALL_MODEL, async);

	model.Load("castle_break1.mv1",MODEL_ID::CASTLE_BREAK_1_MODEL,async);
	model.Load("castle_break2.mv1",MODEL_ID::CASTLE_BREAK_2_MODEL,async);
	model.Load("castle_break3.mv1",MODEL_ID::CASTLE_BREAK_3_MODEL,async);
	model.Load("castle_break4.mv1",MODEL_ID::CASTLE_BREAK_4_MODEL,async);
	model.Load("castle_break5.mv1",MODEL_ID::CASTLE_BREAK_5_MODEL,async);
	model.Load("castle_break6.mv1",MODEL_ID::CASTLE_BREAK_6_MODEL,async);
	model.Load("castle_break7.mv1",MODEL_ID::CASTLE_BREAK_7_MODEL,async);

	model.Load("human_low_ballista.mv1", MODEL_ID::HUMAN_BALLISTA_MODEL, async);
	model.Load("human_low_cannon.mv1", MODEL_ID::HUMAN_CANNON_MODEL, async);
	model.Load("human_archer2.mv1", MODEL_ID::HUMAN_ARCHER_MODEL, async);
	
	model.Load("s_parts1.mv1", SHIP_BREAK_1_MODEL, async);
	model.Load("s_parts2.mv1", SHIP_BREAK_2_MODEL, async);
	model.Load("s_parts3.mv1", SHIP_BREAK_3_MODEL, async);
	model.Load("s_parts4.mv1", SHIP_BREAK_4_MODEL, async);
	model.Load("s_parts5.mv1", SHIP_BREAK_5_MODEL, async);
	model.Load("s_parts6.mv1", SHIP_BREAK_6_MODEL, async);
	model.Load("s_parts7.mv1", SHIP_BREAK_7_MODEL, async);
	model.Load("s_parts9.mv1", SHIP_BREAK_9_MODEL, async);
	model.Load("s_parts11.mv1", SHIP_BREAK_11_MODEL, async);

	model.Load("isle1_break1.mv1", MODEL_ID::ISLE_1_BREAK_1_MODEL, async);
	model.Load("isle1_break3.mv1", MODEL_ID::ISLE_1_BREAK_3_MODEL, async);
	model.Load("isle1_break4.mv1", MODEL_ID::ISLE_1_BREAK_4_MODEL, async);
	model.Load("isle2_break1.mv1", MODEL_ID::ISLE_2_BREAK_1_MODEL, async);
	model.Load("isle2_break2.mv1", MODEL_ID::ISLE_2_BREAK_2_MODEL, async);
	model.Load("isle2_break3.mv1", MODEL_ID::ISLE_2_BREAK_3_MODEL, async);
	model.Load("isle2_break4.mv1", MODEL_ID::ISLE_2_BREAK_4_MODEL, async);
	model.Load("isle3_break1.mv1", MODEL_ID::ISLE_3_BREAK_1_MODEL, async);
	model.Load("isle3_break2.mv1", MODEL_ID::ISLE_3_BREAK_2_MODEL, async);
	model.Load("isle3_break3.mv1", MODEL_ID::ISLE_3_BREAK_3_MODEL, async);
	model.Load("isle3_break4.mv1", MODEL_ID::ISLE_3_BREAK_4_MODEL, async);

	WorkFolder::SetWorkFolder("res/Model2D/");
	
	model.Load2D("smoke_black.png", MODEL_ID::SMOKE_2D, 2, Point(1, 2), Point(300, 200));
	model.Load2D("sand.png", MODEL_ID::SAND_2D);
	model.Load2D("wind.png", MODEL_ID::WIND_2D);
}

// 音楽を読み込む
void Content::LoadSound(Sound& sound)
{
	WorkFolder::SetWorkFolder("res/Sound/GAME_BGM/");
	sound.LoadBGM("clear_bgm.mp3", BGM_ID::CLEAR_BGM,CLEAR_BGM_VOL);
	sound.LoadBGM("failed_bgm.mp3", BGM_ID::FAILED_BGM, FAILED_BGM_VOL);
	sound.LoadBGM("ingame_bgm.mp3", BGM_ID::INGAME_BGM, INGAME_BGM_VOL);
	sound.LoadBGM("intro_bgm.mp3", BGM_ID::INTRO_BGM, INTRO_BGM_VOL);
	sound.LoadBGM("menu_bgm.mp3", BGM_ID::MENU_BGM, MENU_BGM_VOL);
	sound.LoadBGM("title_bgm.mp3", BGM_ID::TITLE_BGM, TITLE_BGM_VOL);

	WorkFolder::SetWorkFolder("res/Sound/SE/");
	sound.LoadSE("arrowfire_se.wav", SE_ID::ARROW_FIRE_SE, ARROW_FIRE_SE_VOL);
	sound.LoadSE("arrowwind_se.wav", SE_ID::ARROW_WIND_SE, ARROW_WIND_SE_VOL);
	sound.LoadSE("back_se.wav", SE_ID::BACK_SE, BACK_SE_VOL);
	sound.LoadSE("ballistafire_se.wav", SE_ID::BALLISTA_FIRE_SE, BALLISTA_FIRE_SE_VOL);
	sound.LoadSE("ballistawind_se.wav", SE_ID::BALLISTA_WIND_SE, BALLISTA_WIND_SE_VOL);
	sound.LoadSE("cannonfire_se.wav", SE_ID::CANON_FIRE_SE, CANON_FIRE_SE_VOL);
	sound.LoadSE("canonwind_se.wav", SE_ID::CANON_WIND_SE, CANON_WIND_SE_VOL);
	sound.LoadSE("castlebrake_se.wav", SE_ID::CASTLE_BREAK_SE, CASTLE_BREAK_SE_VOL);
	sound.LoadSE("castlehit_se.wav", SE_ID::CASTLE_HIT_SE, CASTLE_HIT_SE_VOL);
	sound.LoadSE("construction_se.wav", SE_ID::CONSTRUCTION_SE, CONSTRUCTION_SE_VOL);
	sound.LoadSE("dragondead_se.wav", SE_ID::DRAGON_DEAD_SE, DRAGON_DEAD_SE_VOL);
	sound.LoadSE("dragonhit_se.wav", SE_ID::DRAGON_HIT_SE, DRAGON_HIT_SE_VOL);
	sound.LoadSE("dragonshouting_se.wav", SE_ID::DRAGON_SHOUTING_SE, DRAGON_SHOUTING_SE_VOL);
	sound.LoadSE("dragonspear_se.wav", SE_ID::DRAGONSPEAR_SE, DRAGONSPEAR_SE_VOL);
	sound.LoadSE("enter_se.wav", SE_ID::ENTER_SE, ENTER_SE_VOL);
	sound.LoadSE("gong_se.wav", SE_ID::GONG_SE, GONG_SE_VOL);
	sound.LoadSE("islebrake_se.wav", SE_ID::ISLE_BREAK_SE, ISLE_BREAK_SE_VOL);
	sound.LoadSE("islehit_se.wav", SE_ID::ISLE_HIT_SE, ISLE_HIT_SE_VOL);
	sound.LoadSE("menuroll_se.wav", SE_ID::MENU_ROLL_SE, MENU_ROLL_SE_VOL);
	sound.LoadSE("middlewind_se.wav", SE_ID::MIDDLE_WIND_SE, MIDDLE_WIND_SE_VOL);
	sound.LoadSE("normalwind_se.wav", SE_ID::NORMAL_WIND_SE, NORMAL_WIND_SE_VOL);
	sound.LoadSE("sandstorm_se.wav", SE_ID::SAND_STORM_SE, SAND_STORM_SE_VOL);
	sound.LoadSE("scream1_se.wav", SE_ID::SCREAM_1_SE, SCREAM_1_SE_VOL);
	sound.LoadSE("scream2_se.wav", SE_ID::SCREAM_2_SE, SCREAM_2_SE_VOL);
	sound.LoadSE("scream3_se.wav", SE_ID::SCREAM_3_SE, SCREAM_3_SE_VOL);
	sound.LoadSE("scream4_se.wav", SE_ID::SCREAM_4_SE, SCREAM_4_SE_VOL);
	sound.LoadSE("scream5_se.wav", SE_ID::SCREAM_5_SE, SCREAM_5_SE_VOL);
	sound.LoadSE("stormaked_se.wav", SE_ID::STORMAKED_SE, STORMAKED_SE_VOL);
	sound.LoadSE("strongwind_se.wav", SE_ID::STRONGWIND_SE, STRONGWIND_SE_VOL);
	sound.LoadSE("switch_se.wav", SE_ID::SWITCH_SE, SWITCH_SE_VOL);

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
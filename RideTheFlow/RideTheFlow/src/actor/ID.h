#pragma once

//描画順はここで調整可能
enum ACTOR_ID{
	BEGIN_ACTOR,
	
	//======透明度を扱わない======//
	STAGE_ACTOR,
	FOG_ACTOR,
	ISLAND_ACTOR,
	PLAYER_ACTOR,
	ENEMY_ACTOR,
	SHIP_ENEMY_ACTOR,
	ARMY_ENEMY_ACTOR,
	ENEMY_BULLET,
	CAMERA_ACTOR,
	CASTLE_ACTOR,

	//======透明度を扱う======//
	PARTICLE_ACTOR,
	TORNADO_ACTOR,
	SAND_ACTOR,
	CLOUD_ACTOR,
	WIND_ACTOR,
	AIR_GUN_ACTOR,
	
	//========2DUI========//
	EFFECT_ACTOR,

	END_ACTOR
};

enum COL_ID{
	BEGIN_COL,
	SPHERE_SPHERE_COL,
	SPHERE_CAPSULE,
	PLAYER_STAGE_COL,
	PLAYER_SHIPENEMY_COL,
	PLAYER_DORAGONSPEAR_COL,
	PLAYER_DORAGONSPEAR_WITHIN_COL,
	TORNADO_CASTLE_COL,
	TORNADO_ISLAND_COL,
	TORNADO_STAGE_COL,
	TORNADO_ENEMY_COL,
	CLOUD_TORNADO_COL,
	PLAYER_TORNADO_COL,
	PLAYER_WIND_COL,
	CLOUD_WIND_COL,
	PLAYERTOCASTLELINE_CLOUD_COL,
	ARMYENEMY_STAGE_COL,
	BULLET_WIND_COL,
	CASTLE_CASTLE_COL,
	SHIP_ISLAND_COL,
	ENEMY_WIND_COL,
	CASTLE_WIND_COL,
	END_COL
};

enum SPRITE_ID{
	BEGIN_SPRITE,
	PLAYER_SPRITE,
	ENEMY_SPRITE,
	TORNADO_SPRITE,
	CASTLE_SPRITE,
	SAND_SPRITE,
	/* エフェクト */
	SPEED_SPRITE,
	BLOOD_SPRITE,
	DAMAGE_SPRITE,
	/* ミニマップ */
	MINIMAP_SPRITE,
	MAP_PLAYER_SPRITE,
	/* スタミナゲージ */
	STAMINA_BACK_SPRITE,
	STAMINA_SPRITE,
	/* タイトルシーン */
	TITLE_TEXT_SPRITE,
	TITLE_PRESS_SPRITE,
	TITLE_PRESS_BACK_SPRITE,
	/* メニュー・ポーズ */
	MENU_ROLL_1_SPRITE,
	MENU_ROLL_2_SPRITE,
	MENU_ROLL_3_SPRITE,
	START_GAME_SPRITE,
	START_GAME_BACK_SPRITE,
	BACK_TO_GAME_SPRITE,
	BACK_TO_GAME_BACK_SPRITE,
	BACK_TO_MENU_SPRITE,
	BACK_TO_MENU_BACK_SPRITE,
	EXIT_GAME_SPRITE,
	EXIT_GAME_BACK_SPRITE,
	MANUAL_SPRITE,
	MANUAL_BACK_SPRITE,
	MANUAL_1_SPRITE,
	MANUAL_2_SPRITE,
	MANUAL_3_SPRITE,
	MANUAL_4_SPRITE,
	POINT_SPRITE,
	/* ゲームリザルト */
	FAILED_BACK_2_SPRITE,
	FAILED_BACK_1_SPRITE,
	FAILED_SPRITE,
	CLEAR_SPRITE,
	/* フェード */
	BLACK_SCREEN,
	END_SPRITE
};

enum MODEL_ID{
	BEGIN_MODEL,
	TEST_MODEL,
	PLANE_MODEL,
	BOX_MODEL,
	PLAYER_MODEL,
	TORNADO_MODEL,
	CASTLE_TOP_MODEL,
	CASTLE_TOP2_MODEL,
	CASTLE_BASE_MODEL,
	CASTLE_MASTER_MODEL,
	ARROW_MODEL,
	TEST_STAGE,
	STAGE_MODEL,
	STAGE_ACTION_RANGE_MODEL,
	SKY_MODEL,
	SMOKE_MODEL2D,
	RIGHT_GRAY_2D_MODEL,
	SMOKE_2D,
	SAND_2D,
	WIND_2D,
	WIND_MODEL,
	CLOUD_MODEL,
	SAND_MODEL,
	TORNADOPOLY_MODEL,
	BALLISTA_MODEL,
	BALLISTA_ARROW_MODEL,
	CANNON_MODEL,
	CANNON_BALL_MODEL,
	DORAGON_SPEAR_MODEL,
	DORAGON_SPEAR_TUBE_MODEL,
	GONG_MODEL,
	HOME_MODEL,
	ISLE_1_MODEL,
	ISLE_2_MODEL,
	ISLE_3_MODEL,
	SHIP_MODEL,
	CASTLE_ADD_MODEL,
	AIR_BALL_MODEL,
	CASTLE_BREAK_1_MODEL,
	CASTLE_BREAK_2_MODEL,
	CASTLE_BREAK_3_MODEL,
	CASTLE_BREAK_4_MODEL,
	CASTLE_BREAK_5_MODEL,
	CASTLE_BREAK_6_MODEL,
	CASTLE_BREAK_7_MODEL,
	END_MODEL,
};

enum BGM_ID{
	BEGIN_BGM,
	END_BGM
};

enum SE_ID{
	BEGIN_SE,
	BUTTON_SE,
	END_SE
};

enum UI_ID{
	// 下層ほど手前に描画
	BEGIN_UI,
	/* ゲーム内エフェクト */
	SPEED_UI,
	BLOOD_UI,
	DAMAGE_UI,
	/* ゲーム内UI */
	STAMINA_UI,
	MINIMAP_UI,
	ENEMY_POINT_UI,
	FLOWROOT_UI,
	PLAYER_ARROW_UI,
	MENU_UI,
	/* リザルトUI */
	FAILERE_UI,
	CLEAR_UI,
	END_UI
};
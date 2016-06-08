#pragma once

//描画順はここで調整可能
enum ACTOR_ID{
	BEGIN_ACTOR,
	
	//======透明度を扱わない======//
	STAGE_ACTOR,
	ISLAND_ACTOR,
	PLAYER_ACTOR,
	ENEMY_ACTOR,
	ENEMY_BULLET,
	CAMERA_ACTOR,
	CASTLE_ACTOR,

	//======透明度を扱う======//
	PARTICLE_ACTOR,
	SAND_ACTOR,
	CLOUD_ACTOR,
	WIND_ACTOR,
	TORNADO_ACTOR,
	
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
	END_COL
};

enum SPRITE_ID{
	BEGIN_SPRITE,
	PLAYER_SPRITE,
	ENEMY_SPRITE,
	TORNADO_SPRITE,
	CASTLE_SPRITE,
	SAND_SPRITE,
	SPEED_SPRITE,
	BLOOD_SPRITE,
	DAMAGE_SPRITE,
	STAMINA_BACK_SPRITE,
	STAMINA_SPRITE,
	TITLE_TEXT,
	TITLE_PRESS,
	TITLE_PRESS_BACK,
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
	STAGE_MODEL,
	SKY_MODEL,
	SMOKE_MODEL2D,
	RIGHT_GRAY_2D_MODEL,
	SMOKE_2D,
	SAND_2D,
	WIND_2D,
	WIND_MODEL,
	CLOUD_MODEL,
	TORNADOPOLY_MODEL,
	TEST_STAGE,
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

enum EFFECT_ID{
	BEGIN_EFFECT,
	STAMINA_EFFECT,
	SPEED_EFFECT,
	BLOOD_EFFECT,
	DAMAGE_EFFECT,
	END_EFFECT
};
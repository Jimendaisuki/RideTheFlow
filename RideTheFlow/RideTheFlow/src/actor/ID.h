#pragma once

enum ACTOR_ID{
	BEGIN_ACTOR,
	STAGE_ACTOR,
	PLAYER_ACTOR,
	ENEMY_ACTOR,
	ENEMY_BULLET,
	CAMERA_ACTOR,
	TORNADO_ACTOR,
	CASTLE_ACTOR,
	ISLAND_ACTOR,
	SAND_ACTOR,
	PARTICLE_ACTOR,
	INTENSIVELINE_ACTOR,
	END_ACTOR
};

enum COL_ID{
	BEGIN_COL,
	SPHERE_SPHERE_COL,
	SPHERE_CAPSULE,
	TORNADO_CASTLE_COL,
	TORNADO_ISLAND_COL,
	TORNADO_STAGE_COL,
	PLAYER_TORNADO_COL,
	END_COL
};

enum SPRITE_ID{
	BEGIN_SPRITE,
	PLAYER_SPRITE,
	ENEMY_SPRITE,
	TORNADO_SPRITE,
	CASTLE_SPRITE,
	SAND_SPRITE,
	INTENSIVELINE_SPRITE,
	END_SPRITE
};

enum MODEL_ID{
	BEGIN_MODEL,
	TEST_MODEL,
	PLANE_MODEL,
	BOX_MODEL,
	PLAYER_MODEL,
	TORNADO_MODEL,
	CASTLE_MODEL,
	ARROW_MODEL,
	STAGE_MODEL,
	SKY_MODEL,
	SMOKE_MODEL2D,
	RIGHT_GRAY_2D_MODEL,
	SMOKE_2D,
	SAND_2D,
	TEST_STAGE,
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

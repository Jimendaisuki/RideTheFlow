#pragma once
#include "../Def.h"
#include "../math/Vector2.h"

// 共通スケール
const float MINI_MAP_SCALE = 0.6f;

// ミニマップリソースサイズ
const Vector2 MINI_MAP_SIZE = Vector2(512.0f, 512.0f);

// ステージモデルサイズ
//const Vector2 STAGE_SIZE = Vector2(2048.0f, 2048.0f);
const Vector2 STAGE_SIZE = Vector2(70 * 240, 70 * 240);

// ミニマップ描画位置
const Vector2 MAP_DRAW_POSITION = Vector2(WINDOW_WIDTH, 350) - MINI_MAP_SIZE / 2.0f * MINI_MAP_SCALE;

// リサイズ
const float RE_SIZE_SCALE = MINI_MAP_SIZE.x / 2 / STAGE_SIZE.x * MINI_MAP_SCALE;
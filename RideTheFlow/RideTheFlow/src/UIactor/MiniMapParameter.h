#pragma once
#include "../Def.h"
#include "../math/Vector2.h"

// ���ʃX�P�[��
const float MINI_MAP_SCALE = 0.6f;

// �~�j�}�b�v���\�[�X�T�C�Y
const Vector2 MINI_MAP_SIZE = Vector2(512.0f, 512.0f);

// �X�e�[�W���f���T�C�Y
const Vector2 STAGE_SIZE = Vector2(2048.0f, 2048.0f);

// �~�j�}�b�v�`��ʒu
const Vector2 MAP_DRAW_POSITION = Vector2(WINDOW_WIDTH, WINDOW_HEIGHT) - MINI_MAP_SIZE / 2.0f * MINI_MAP_SCALE;

// ���T�C�Y
const float RE_SIZE_SCALE = MINI_MAP_SIZE.x / 2 / STAGE_SIZE.x * MINI_MAP_SCALE;
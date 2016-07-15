#pragma once

//空気砲の死ぬまでに進む距離
static const float WindBallLimitLength = 1500.0f;
//空気砲のスピード
static const float WindBallSpeed = 1000.0f;

//竜巻が死ぬまでの時間(秒)
static const float TornadoLifeLimit = 20.0f;
//竜巻のスピード
static const float TornadoSpeed = 600.0f;
//竜巻パーティクルの上昇スピード最大と最小(ランダム)
static const float TornadoParticleRizeSpeedMax = 1000.0f;
static const float TornadoParticleRizeSpeedMin = 1000.0f;

//流れが死ぬまでの時間(秒)
static const float WindFlowLifeLimit = 30.0f;
//流れがタックルされたときの飛んでくスピード
static const float WindFlowSpeed = 400.0f;

//城増築時の煙
//数
static const int CastleAddSmokeNum = 10;
//大きさ
//大きさのベース
static const float CastleAddSmokeSize = 0.1f;
//ベースに加える最大と最小(ランダム)
static const float CastleAddSmokeSizePlusMax = 0.01f;
static const float CastleAddSmokeSizePlusMin = -0.02f;
//消えるまでの時間(城や飛行船がダメージ食らった時の煙にも適用)
static const float SmokeLifeLimit = 2.0f;



//城や飛行船がダメージ食らった時の煙
//数
static const int DamageSmokeNum = 10;
//大きさ
static const float DamageSmokeSizeCastle = 0.05f;
static const float DamageSmokeSizeShip = 0.05f;
//大きさに加えるランダム
static const float DamageSmokeSizePlusMax = 0.01f;
static const float DamageSmokeSizePlusMin = -0.02f;
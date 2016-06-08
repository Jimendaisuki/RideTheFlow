#pragma once

//プレイヤーのどのぐらい前に攻撃するか
const float CastleCameraFrontAttack = 10.0f;

//城の上に積み重なる城の段数
const int Rank = 4;
//城が積みあがる時間(秒)
const float RankUpSecond = 8.0f;


/***城の大砲***/
//城の大砲が攻撃してくる範囲
const float CastleCannonAttackRange = 400.0f;
//城の大砲の攻撃クールタイム(秒)
const float CastleCannonSecondAttack = 5.0f;
//城が一回に出す大砲の弾の数
const int CastleCannonNumber = 1;

//城の大砲からプレイヤーが見えてないときの一回に出す大砲の弾の数
const int CastleCannonNotLookAttack = 1;
//城の大砲からプレイヤーが見えてないときの攻撃クールタイム(秒)
const float CastleCannonNotLookSecondAttack = 10.0f;


//城の大砲の精度(数値が小さいほど高精度)
const float CastleCannonArrowAccuracy = 50.0f;



////城モデルの高さの３倍(スケール弄ってるから)
//const float CastleHeight = 30.0f;
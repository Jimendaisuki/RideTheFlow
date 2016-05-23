#pragma once

//城の上に積み重なる城の段数
const int Rank = 3;
//城が積みあがる時間(秒)
const float RankUpSecond = 5.0f;
//城が攻撃してくる範囲
const float AttackRange = 400.0f;
//城の攻撃クールタイム(秒)
const float SecondAttack = 0.5f;
//城が一回に出す矢の本数(本)
const int ArrowNumber = 1;

//城がプレイヤーが見えてないときの一回に出す矢の本数(本)
const int NotLookArrow = 1;
//城がプレイヤーが見えてないときの攻撃クールタイム(秒)
const float NotLookSecondAttack = 4.0f;


//攻撃の精度(数値が小さいほど高精度)
const float ArrowAccuracy = 50.0f;
//城モデルの高さの３倍(スケール弄ってるから)
const float CastleHeight = 30.0f;
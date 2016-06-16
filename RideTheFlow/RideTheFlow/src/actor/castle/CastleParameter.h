#pragma once



//プレイヤーのどのぐらい前に攻撃するか
const float CastleCameraFrontAttack = 10.0f;
//マスター城のHP
const float MasterCastleHp = 10.0f;
//ベース(砲台とかある)の城のHP
const float BaseCastleHp = 10.0f;

//城がトルネードで受けるダメージ
const float CastleDamegeTornado = 2.5f;
//城が流れで受けるダメージ
const float CastleDamegeWind = 0.5f;

//城の無敵時間
const float CastleInvincibleTime = 3.0f;

//城の上に積み重なる城の段数
const int Rank = 1;
//城が積みあがる時間(秒)
const float RankUpSecond = 8.0f;

//城が排出する軍隊の時間
const float SpawnArmyEnemyTime = 5.0f;
//城が排出する軍隊の最大軍隊数
const int SpawnMaxArmyEnemy = 10;

/**浮島の城限定**/
//城が排出する船の時間
const float SpawnShipEnemyTime = 100.0f;
//城が排出する船の最大船数
const int SpawnMaxShipEnemey = 5;

/***城の大砲***/
//城の大砲が攻撃してくる範囲
const float CastleCannonAttackRange = 400.0f;
//城の大砲の攻撃クールタイム(秒)
const float CastleCannonSecondAttack = 5.0f;
//城が一回に出す大砲の弾の数
const int CastleCannonNumber = 1;
//城の大砲の旋回速度
const float CastleCannonSwingSpeed = 20.0f;
//城の大砲からプレイヤーが見えてないときの一回に出す大砲の弾の数
const int CastleCannonNotLookAttack = 1;
//城の大砲からプレイヤーが見えてないときの攻撃クールタイム(秒)
const float CastleCannonNotLookSecondAttack = 10.0f;


//城の大砲の精度(数値が小さいほど高精度)
const float CastleCannonArrowAccuracy = 50.0f;

/***城の兵士***/
//城の兵士が攻撃してくる範囲
const float CastleSoldierAttackRange = 400.0f;
//城の兵士の攻撃クールタイム(秒)
const float CastleSoldierSecondAttack = 5.0f;
//城が一回に出す兵士の矢の数
const int CastleSoldierNumber = 1;

//城の兵士からプレイヤーが見えてないときの一回に出す兵士の矢の数
const int CastleSoldierNotLookAttack = 1;
//城の兵士からプレイヤーが見えてないときの攻撃クールタイム(秒)
const float CastleSoldierNotLookSecondAttack = 10.0f;



////城モデルの高さの３倍(スケール弄ってるから)
//const float CastleHeight = 30.0f;
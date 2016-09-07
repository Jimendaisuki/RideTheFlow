#pragma once

//プレイヤーのどのぐらい前に攻撃するか
const float CastleCameraFrontAttack = 10.0f;

//マスター城のHP
const float MasterCastleHp = 20.0f;
//間の城のHP
const float BaseCastleHp = 10.0f;

//城がトルネードで受けるダメージ
const float CastleDamegeTornado = 10.0f;
//城が流れで受けるダメージ
const float CastleDamegeWind = 0.5f;
//城が空気砲で受けるダメージ
const float CastleDamageWindBall = 5.0f;

//城の無敵時間
const float CastleInvincibleTime = 3.0f;

//城の上に積み重なる城の段数
const int Rank = 5;
//城が積みあがる時間(秒)
const float RankUpSecond = 2.0f;

//城が排出する軍隊の時間
const float SpawnArmyEnemyTime = 5.0f;
//城が排出する軍隊の最大軍隊数
const int SpawnMaxArmyEnemy = 25;

/**浮島の城限定**/
//城が排出する船の時間
const float SpawnShipEnemyTime = 5.0f;
//城が排出する船の最大船数
const int SpawnMaxShipEnemey = 5;

/***城の大砲***/
//城の大砲が攻撃してくる範囲
const float CastleCannonAttackRange = 1000.0f;
//城の大砲の攻撃クールタイム(秒)
const float CastleCannonSecondAttack = 5.0f;
//城が一回に出す大砲の弾の数
const int CastleCannonNumber = 1;
//城の大砲の旋回速度
const float CastleCannonSwingSpeed = 100.0f;
//城の大砲からプレイヤーが見えてないときの一回に出す大砲の弾の数
const int CastleCannonNotLookAttack = 0;
//城の大砲からプレイヤーが見えてないときの攻撃クールタイム(秒)
const float CastleCannonNotLookSecondAttack = 0.0f;
//城の大砲の初速度
const float CastleCannonInitialVelocity = 100.0f;

//城の大砲の攻撃精度(小さいほど高精度)
const float CastleCannonBulletAccuracy = 1.0f;

/***城のバリスター***/
//城のバリスターが攻撃してくる範囲
const float CastleVaristorAttackRange = 1000.0f;
//城のバリスターの攻撃クールタイム(秒)
const float CastleVaristorSecondAttack = 5.0f;
//城が一回に出すバリスターの矢の数
const int CastleVaristorNumber = 1;
//城のバリスターの旋回速度
const float CastleVaristorSwingSpeed = 100.0f;
//城のバリスターからプレイヤーが見えてないときの一回に出すバリスターの矢の数
const int CastleVaristorNotLookAttack = 0;
//城のバリスターからプレイヤーが見えてないときの攻撃クールタイム(秒)
const float CastleVaristorNotLookSecondAttack = 0.0f;
//城のバリスターの初速度
const float CastleVaristorInitialVelocity = 100.0f;

//城のバリスタ攻撃精度(小さいほど高精度)
const float CastleVaristorArrowAccuracy = 10.0f;





/***城の兵士***/
//城の兵士が攻撃してくる範囲
const float CastleSoldierAttackRange = 0.0f;
//城の兵士の攻撃クールタイム(秒)
const float CastleSoldierSecondAttack = 0.0f;
//城が一回に出す兵士の矢の数
const int CastleSoldierNumber = 0;

//城の兵士からプレイヤーが見えてないときの一回に出す兵士の矢の数
const int CastleSoldierNotLookAttack = 0;
//城の兵士からプレイヤーが見えてないときの攻撃クールタイム(秒)
const float CastleSoldierNotLookSecondAttack = 0.0f;
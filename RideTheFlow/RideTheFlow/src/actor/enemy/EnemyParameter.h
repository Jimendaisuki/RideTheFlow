#pragma once

/****攻撃力関係****/
//矢の攻撃力
const float ArrowPower = 1.0f;
//大砲の攻撃力
const float CannonPower = 5.0f;
//バリスタの攻撃力
const float VaristorPower = 2.0f;
//龍激走の攻撃力
const float DoragonSperarPower = 10.0f;


/****敵の攻撃の大きさ****/
//矢の大きさ
const float ArrowSize = 4.0f;
//砲弾の大きさ
const float ConnonBulletSize = 10.0f;
//バリスタ弾の大きさ
const float VaristorBulletSize = 6.0f;

/***敵の攻撃のスピード***/
//矢のスピード
const float ArrowSpeed = 5.0f;
//砲弾のスピード
const float CannonSpeed = 5.0f;
//バリスタのスピード
const float VaristorSpeed = 5.0f;

/***共通***/
//どのくらいカメラの前の場所に通常攻撃するか(ダッシュ中は無効)
const float cameraFrontAttack = 10.0f;

/****敵軍隊****/
//軍隊のスピード
const float ArmySpeed = 50.0f;
//軍隊の攻撃クールタイム
const float ArmyAttackTime = 5.0f;
//軍隊の攻撃範囲
const float ArmyRange = 3000.0f;
//軍隊がプレイヤーから見てどこまで近づくか(度数)　　例:0度にした場合プレイヤーの真下にまで移動する
const float ArmyNear = 45.0f;
//軍隊が一回に発射する矢の本数
const int ArmyArrorwNum = 10;

//軍隊からプレイヤーが見えていないときの攻撃クールタイム
const float NotLookArmyAttackTime = 20.0f;
//軍隊からプレイヤーが見えていないときの一回に発射する矢の本数
const float NotLookArmyArrorwNum = 0;

//軍隊の攻撃精度
const float ArmyArrowAccuracy = 100.0f;
//軍隊の攻撃が流れの影響を受ける割合
const float ArmyWindPercentage = 100.0f;


/****敵バリスタ****/

//バリスタの攻撃クールタイム
const float VaristorAttackTime = 5.0f;
//バリスタが一回に発射する矢の数
const int VaristorArrorwNum = 2;
//バリスタの攻撃範囲
const float VaristorRange = 1000.0f;
//バリスタが発射できるZを軸にした最高角度（度）
const float VaristorAttackMaxAngle = 90.0f;
//バリスタが発射できるZを軸にした最小角度（度）
const float VaristorAttackMinAngle = -90.0f;
//バリスタの初速度
const float VaristorInitialVelocity = 100.0f;
//バリスタの旋回速度
const float VaristorSwingSpeed = 100.0f;

//バリスタからプレイヤーが見えていないときの攻撃クールタイム
const float NotLookVaristorAttackTime = 10.0f;
//バリスタからプレイヤーが見えていないときの一回に発射する矢の本数
const float NotLookVaristorArrowNum = 0;

//バリスタ攻撃精度(小さいほど高精度)
const float VaristorArrowAccuracy = 10.0f;
//バリスタの攻撃が流れの影響を受ける割合
const float VaristorWindPercentage = 75.0f;



/****敵大砲****/

//大砲の攻撃クールタイム
const float CannonAttackTime = 0.1f;
//大砲の攻撃範囲
const float CannonRange = 1000.0f;
//大砲が一回に発射する砲弾の数
const int CannonShellNum = 1;
//大砲の発射できるZを軸にした最高角度（度）
const float  CannonAttackMaxAngle = 90.0f;
//大砲の発射できるZを軸にした最低角度（度）
const float CannonAttackMinAngle = -90.0f;
//大砲の玉の初速度
const float CannonInitialVelocity = 200.0f;
//大砲の旋回速度
const float ConnonSwingSpeed = 100.0f;

//大砲からプレイヤーが見えていないときの攻撃クールタイム
const float NotLookCannonAttackTime = 30.0f;
//大砲からプレイヤーが見えていないときの一回に発射する砲弾の数
const float NotLookCannonShellNum = 0;

//大砲攻撃精度(小さいほど高精度)
const float CannonShellAccuracy = 10.0f;
//大砲の攻撃が流れの影響を受ける割合
const float CannonWindPercentage = 50.0f;


/****敵の船****/

//船のHP
const float ShipHp = 10.0f;
//船がトルネードで受けるダメージ
const float ShipDamegeTornado = 10.0f;
//船が流れで受けるダメージ
const float ShipDamegeWind = 5.0f;
//船が空気砲で受けるダメージ
const float ShipDamegeWindBall = 5.0f;

//船の無敵時間
const float ShipInvincibleTime = 3.0f;


//船のスピード
const float ShipSpeed = 50.0f;
//船の高さを変えるスピード
const float ShipUpDownSpeed = 50.0f;
//船の旋回速度
const float ShipSwingSpeed = 50.0f;
//船バリスタの攻撃クールタイム
const float ShipVaristorAttackTime = 2.0f;
//船バリスタが一回に発射する矢の数
const int ShipVaristorArrorwNum = 2;
//船バリスタの攻撃範囲
const float ShipVaristorRange = 1000.0f;
//船バリスタが発射できるZを軸にした最高角度（度）
const float ShipVaristorAttackMaxAngle = 90.0f;
//船バリスタが発射できるZを軸にした最小角度（度）
const float ShipVaristorAttackMinAngle = -90.0f;
//船バリスタの初速度
const float ShipVaristorInitialVelocity = 200.0f;
//船バリスタの旋回速度
const float ShipVaristorSwingSpeed = 100.0f;

//船バリスタからプレイヤーが見えていないときの攻撃クールタイム
const float ShipNotLookVaristorAttackTime = 10.0f;
//船バリスタからプレイヤーが見えていないときの一回に発射する矢の本数
const float ShipNotLookVaristorArrowNum = 0;


//船大砲の攻撃クールタイム
const float ShipCannonAttackTime = 2.0f;
//船大砲の攻撃範囲
const float ShipCannonRange = 1000.0f;
//船大砲が一回に発射する砲弾の数
const int ShipCannonShellNum = 2;
//船大砲の発射できるZを軸にした最高角度（度）
const float  ShipCannonAttackMaxAngle = 90.0f;
//船大砲の発射できるZを軸にした最低角度（度）
const float ShipCannonAttackMinAngle = -90.0f;
//船大砲の玉の初速度
const float ShipCannonInitialVelocity = 200.0f;
//船大砲の旋回速度
const float ShipConnonSwingSpeed = 100.0f;

//船大砲からプレイヤーが見えていないときの攻撃クールタイム
const float ShipNotLookCannonAttackTime = 30.0f;
//船大砲からプレイヤーが見えていないときの一回に発射する砲弾の数
const float ShipNotLookCannonShellNum = 0;


/***撃龍槍***/

//撃龍槍のクールタイム
const float DoragonSpearAttackTime = 5.0f;
//プレイヤーが撃龍槍圏内に入った時から攻撃する時までの時間
const float DoragonSpearWithinTime = 1.0f;
//撃龍槍が最大に伸びるまでの時間
const float DoragonSpearMaxTime = 10.0f;
//撃龍槍が完全に出てそこにとどまる時間
const float DoragonSpearStopTime = 1.0f;

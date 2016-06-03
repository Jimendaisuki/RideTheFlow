#pragma once

/***共通***/
//どのくらいカメラの前の場所に通常攻撃するか(ダッシュ中は無効)
const float cameraFrontAttack = 10.0f;


/****敵軍隊****/

//軍隊のスピード
const float ArmySpeed = 50.0f;
//軍隊の攻撃クールタイム
const float ArmyAttackTime = 0.5f;
//軍隊の攻撃範囲
const float ArmyRange = 200.0f;
//軍隊がプレイヤーから見てどこまで近づくか(度数)　　例:0度にした場合プレイヤーの真下にまで来る
const float ArmyNear = 45.0f;
//軍隊が一回に発射する矢の本数
const int ArmyArrorwNum = 10;

//軍隊からプレイヤーが見えていないときの攻撃クールタイム
const float NotLookArmyAttackTime = 20.0f;
//軍隊からプレイヤーが見えていないときの一回に発射する矢の本数
const float NotLookArmyArrorwNum = 5;

//軍隊の攻撃精度
const float ArmyArrowAccuracy = 50.0f;
//軍隊の攻撃が流れの影響を受ける割合
const float ArmyWindPercentage = 80.0f;


/****敵バリスタ****/

//バリスタの弾スピード
const float VaristorSpeed = 3.0f;
//バリスタの攻撃クールタイム
const float VaristorAttackTime = 5.0f;
//バリスタが一回に発射する矢の数
const int VaristorArrorwNum = 2;
//バリスタの攻撃範囲
const float VaristorRange = 300.0f;
//バリスタが発射できるZを軸にした最高角度（度）
const float VaristorAttackMaxAngle = 45.0f;
//バリスタが発射できるZを軸にした最小角度（度）
const float VaristorAttackMinAngle = -45.0f;
//バリスタの初速度
const float VaristorInitialVelocity = 60.0f;
//バリスタの旋回速度
const float VaristorSwingSpeed = 50.0f;

//バリスタからプレイヤーが見えていないときの攻撃クールタイム
const float NotLookVaristorAttackTime = 10.0f;
//バリスタからプレイヤーが見えていないときの一回に発射する矢の本数
const float NotLookVaristorArrowNum = 2;

//バリスタ攻撃精度(小さいほど高精度)
const float VaristorArrowAccuracy = 10.0f;
//バリスタの攻撃が流れの影響を受ける割合
const float VaristorWindPercentage = 100.0f;



/****敵大砲****/

//大砲の弾スピード
const float CannonSpeed = 3.0f;
//大砲の攻撃クールタイム
const float CannonAttackTime = 10.0f;
//大砲の攻撃範囲
const float CannonRange = 300.0f;
//大砲が一回に発射する砲弾の数
const int CannonShellNum = 1;
//大砲の発射できるZを軸にした最高角度（度）
const float  CannonAttackMaxAngle = 45.0f;
//大砲の発射できるZを軸にした最低角度（度）
const float CannonAttackMinAngle = -45.0f;
//大砲の玉の初速度
const float CannonInitialVelocity = 100.0f;
//大砲の旋回速度
const float ConnonSwingSpeed = 50.0f;

//大砲からプレイヤーが見えていないときの攻撃クールタイム
const float NotLookCannonAttackTime = 30.0f;
//大砲からプレイヤーが見えていないときの一回に発射する砲弾の数
const float NotLookCannonShellNum = 1;

//大砲攻撃精度(小さいほど高精度)
const float CannonShellAccuracy = 10.0f;
//大砲の攻撃が流れの影響を受ける割合
const float CannonWindPercentage = 100.0f;


/****敵の船****/

//船のスピード
const float ShipSpeed = 3.0f;
//船の攻撃クールタイム
const float ShipAttackTime = 10.0f;
//船の攻撃範囲
const float ShipRange = 300.0f;
//船が一回に発射する砲弾の数
const int ShipShellNum = 1;
//船の発射できるZを軸にした最高角度（度）
const float  ShipAttackMaxAngle = 45.0f;
//船の発射できるZを軸にした最低角度（度）
const float ShipAttackMinAngle = -45.0f;
//船の玉の初速度
const float ShipInitialVelocity = 100.0f;
//船の旋回速度
const float ShipSwingSpeed = 50.0f;

//船からプレイヤーが見えていないときの攻撃クールタイム
const float NotLookShipAttackTime = 30.0f;
//船からプレイヤーが見えていないときの一回に発射する砲弾の数
const float NotLookShipShellNum = 1;

//船攻撃精度(小さいほど高精度)
const float ShipAttackAccuracy = 10.0f;
//船の攻撃が流れの影響を受ける割合
const float ShipWindPercentage = 100.0f;

#pragma once

/***共通***/
//どのくらいカメラの前の場所に通常攻撃するか(ダッシュ中は無効)
const float cameraFrontAttack = 75.0f;


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



/****敵バリスタ****/

//バリスタの攻撃クールタイム
const float VaristorAttackTime = 1.0f;
//バリスタが一回に発射する矢の数
const int VaristorArrorwNum = 2;
//バリスタの攻撃範囲
const float VaristorRange = 300.0f;
//バリスタが発射できるZを軸にした最高角度（度）
const float VaristorAttackMaxAngle = 45.0f;
//バリスタが発射できるZを軸にした最小角度（度）
const float VaristorAttackMinAngle = -45.0f;

//バリスタからプレイヤーが見えていないときの攻撃クールタイム
const float NotLookVaristorAttackTime = 10.0f;
//バリスタからプレイヤーが見えていないときの一回に発射する矢の本数
const float NotLookVaristorArrowNum = 2;

//バリスタ攻撃精度
const float VaristorArrowAccuracy = 50.0f;



/****敵大砲****/

//大砲の攻撃クールタイム
const float CannonAttackTime = 5.0f;
//大砲の攻撃範囲
const float CannonRange = 300.0f;
//大砲が一回に発射する砲弾の数
const int CannonShellNum = 1;
//大砲の発射できるZを軸にした最高角度（度）
const float  CannonAttackMaxAngle = 30.0f;
//大砲の発射できるZを軸にした最低角度（度）
const float CannonAttackMinAngle = -50.0f;
//大砲の玉の初速度
const float CannonInitialVelocity = 5.0f;
//大砲の旋回速度
const float ConnonSwingSpeed = 0.02f;

//大砲からプレイヤーが見えていないときの攻撃クールタイム
const float NotLookCannonAttackTime = 30.0f;
//大砲からプレイヤーが見えていないときの一回に発射する砲弾の数
const float NotLookCannonShellNum = 1;

//大砲攻撃精度
const float CannonShellAccuracy = 40.0f;
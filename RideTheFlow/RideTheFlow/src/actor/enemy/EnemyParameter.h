#pragma once

//軍隊のスピード
const float ArmySpeed = 50.0f;
//軍隊の攻撃クールタイム
const float ArmyAttackTime = 0.5f;
//軍隊の攻撃範囲
const float ArmyRange = 200.0f;
//軍隊がプレイヤーから見てどこまで近づくか(度数)　　例:0度にした場合プレイヤーの真下にまでくる
const float ArmyNear = 45.0f;
//軍隊が一回に発射する矢の本数
const int ArmyArrorwNum = 10;

//軍隊からプレイヤーが見えていないときの攻撃クールタイム
const float NotLookArmyAttackTime = 20.0f;
//軍隊からプレイヤーが見えていないときの一回に発射する矢の本数
const float NotLookArmyArrorwNum = 5;

//軍隊の攻撃精度
const float ArmyArrowAccuracy = 50.0f;
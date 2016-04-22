#pragma once
#include "ID.h"
#include <memory>
#include "../math/Vector3.h"

//あたり判定のパラメータ
struct CollisionParameter{
	bool	colFlag = false;		//当ったかどうかのフラグ		//敵からの攻撃（罠）か？
	Vector3 colPos = Vector3::Zero;
};

// カプセル
struct  Capsule{
	Vector3	startPos;			// カプセルの始点
	Vector3 endPos;				// カプセルの終点
	float	radius;				// 半径
};
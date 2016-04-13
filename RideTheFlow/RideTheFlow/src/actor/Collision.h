#pragma once
#include "ID.h"
#include <memory>

//あたり判定のパラメータ
struct CollisionParameter{
	bool colFlag = true;		//当ったかどうかのフラグ		//敵からの攻撃（罠）か？
};
#pragma once
#include "ID.h"
#include <memory>
#include "../math/Vector3.h"
#include "../actor/Actor.h"

//あたり判定のパラメータ
struct CollisionParameter{
	bool		colFlag	= false;				//当ったかどうかのフラグ		//敵からの攻撃（罠）か？
	bool        colAll = false;
	int			colID;
	Vector3		colPos = Vector3::Zero;			// 当たったポジション
	Vector3		colVelosity = Vector3::Zero;
};

// 線分
struct Line{
	Vector3 startPos	= Vector3::Zero;	// 始点
	Vector3 endPos		= Vector3::Zero;	// 終点
};
// 箱
struct Box{
	Vector3 min	= Vector3::Zero;			// 箱の頂点
	Vector3 max = Vector3::Zero;			// 箱の対角にある頂点
};
// 球
struct Sphere{
	Vector3	position = Vector3::Zero;	// 球の位置
	float	radius = 0;					// 球の半径
};
// カプセル
struct  Capsule{
	Vector3	startPos	= Vector3::Zero;	// カプセルの始点
	Vector3 endPos		= Vector3::Zero;	// カプセルの終点
	float	radius		= 0;				// 半径
};
// モデル
struct ModelData{
	int		MHandle		= 0;
	int		MFrameIndex	= -1;
};

class Collisin{
	public:
	static Collisin &GetInstace(){
		static Collisin c;
		return c;
	}

	// 線と箱の当たり判定
	CollisionParameter SegmentBoxAABB(const Line& line, const Box& box) const;
	// 線と球の当たり判定
	CollisionParameter SegmentSphere(const Line& line, const Sphere& s) const;

	// 球と球のあたり判定
	CollisionParameter SphereSphere(const Sphere& s1, const Sphere& s2) const;
	// 球とカプセルの当たり判定
	CollisionParameter SphereCapsule(const Sphere& s, const Capsule& c) const;

	// カプセルとカプセルの当たり判定
	CollisionParameter CapsuleCapsule(const Capsule& c1, const Capsule& c2) const;
	// カプセルと点の当たり判定
	CollisionParameter CapsulePoint(const Capsule& c, const Vector3& p) const;
	// カプセルとAABBの当たり判定
	//CollisionParameter CapsuleAABBSegment(const Actor& other)const;

	// モデルと線分の当たり判定
	CollisionParameter ModelLine(const ModelData& model, const Line& line) const;
	// モデルと球の当たり判定
	CollisionParameter ModelSphere(const ModelData& model, const Sphere& s) const;
	// モデルとカプセルの当たり判定
	CollisionParameter ModelCapsule(const ModelData& model, const Capsule& c) const;

	// 円柱と箱の当たり判定
	//CollisionParameter CylinderBox(const Actor& other)const;

	//
	CollisionParameter PushedBack_SphereCapsule(const Sphere& s, const Capsule& c) const;
	//
	Vector3 PushedBack_CapsuleCapsule(const Capsule& c1, const Capsule& c2) const;

	CollisionParameter PushedBack_SphereSphere(const Sphere& s1, const Sphere& s2) const;
};

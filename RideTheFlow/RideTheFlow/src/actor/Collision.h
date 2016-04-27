#pragma once
#include "ID.h"
#include <memory>
#include "../math/Vector3.h"

//あたり判定のパラメータ
struct CollisionParameter{
	bool		colFlag	= false;				//当ったかどうかのフラグ		//敵からの攻撃（罠）か？
	Vector3		colPos	= Vector3::Zero;		// 当たったポジション
	int			colID;
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

struct Sphere{
	Vector3	position	= Vector3::Zero;	// 球の位置
	float	radius		= 0;				// 球の半径
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
	// 線と箱の当たり判定
	static CollisionParameter SegmentBoxAABB(const Line& line, const Box& box);
	// 線と球の当たり判定
	static CollisionParameter SegmentSphere(const Line& line, const Sphere& s);

	// 球と球のあたり判定
	static CollisionParameter SphereSphere(const Sphere& s1, const Sphere& s2);
	// 球とカプセルの当たり判定
	static CollisionParameter SphereCapsule(const Sphere& s, const Capsule& c);

	// カプセルとカプセルの当たり判定
	static CollisionParameter CapsuleCapsule(const Capsule& c1, const Capsule& c2);
	// カプセルと点の当たり判定
	static CollisionParameter CapsulePoint(const Capsule& c, const Vector3& p);
	// カプセルとAABBの当たり判定
	//CollisionParameter CapsuleAABBSegment(const Actor& other)const;

	// モデルと線分の当たり判定
	static CollisionParameter ModelLine(const ModelData& model, const Line& line);
	// モデルと球の当たり判定
	static CollisionParameter ModelSphere(const ModelData& model, const Sphere& s);
	// モデルとカプセルの当たり判定
	static CollisionParameter ModelCapsule(const ModelData& model, const Capsule& c);

	// 円柱と箱の当たり判定
	//CollisionParameter CylinderBox(const Actor& other)const;
};

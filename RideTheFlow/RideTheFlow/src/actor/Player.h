#pragma once
#include "Actor.h"
#include "../math/Vector3.h"
#include <memory>

struct TackleParameter{
	bool tackleFlag, tackleEndFlag,tackleAttackFlag,dashFlag;
	Matrix4 tackleRotate;
	float tackleAngle;
	Vector3 tackleT;
};

class Player :public Actor, public std::enable_shared_from_this<Player>
{
public:
	Player(IWorld& world);
	~Player();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
	TackleParameter& ReturnTackleParameter(){
		return tp;
	}


private:
	//デバック表示まとめ
	void ParameterDraw()const;
	//デバックコード(デバック表示されているもののボーンのナンバー)
	int boneSelect;

	//計算用のポジション
	Vector3 position;
	//くねくねさせる為のangle２つ
	float upAngle, leftAngle;
	//カメラの上下左右のrotate
	float rotateUp, rotateLeft;
	//マイフレームpositionを保存するもの
	std::vector<Vector3> posStorage;
	//初期ボーン
	Vector3* vertexVec;

	//移動量
	Vector3 vec;

	//トルネードが発生するまでの時間
	float tornadeTimer;

	//ダメージを受けた際のパラメーター
	bool damageFlag;
	float damageCount;

	//タックルのパラメーター
	TackleParameter tp;

	//加速ゲージの回復中
	bool dashHealFlag;
	//加速用のスピード
	float dashSpeed;
	//加速できる時間
	float dashTime;
	std::vector<Vector3> dashPosStorage;

	//posStorageに何もないときのボーンの方向
	Vector3 nonPosStorageVec;

	//回転のディレイをかけるために用いる前フレームのベクトル(y = 0.01fの理由はぴったりだとバグを生じるから)
	Vector3 beforeVec;

	//アニメーションの再生タイム
	float animTime, totalTime;
	//モデルハンドルを取得する(アニメーションのために)
	int modelHandle, animIndex;
	//アニメーションのブレンド
	float animBlend;
	//待機アニメーションをアタッチしたかどうか判断
	bool waitAnimSet;
};
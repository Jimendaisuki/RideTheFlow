#pragma once
#include "Actor.h"
#include "../math/Vector3.h"
#include <memory>
class WindFlow;
class Tornado;

struct TackleParameter{
	bool tackleFlag, tackleEndFlag,dashFlag,tackleColFlag,tornadoTatchFlag,airGunFlag;
	Matrix4 tackleRotate;
	float tackleAngle;
	Vector3 tackleT;
	float animTime;
};

class Player :public Actor, public std::enable_shared_from_this<Player>
{
public:
	Player(IWorld& world,bool title_ = false,bool event_ = false,Vector3 position_ = Vector3(0,0,0),Vector3 eventVec_ = Vector3(0, 0, -1));
	~Player();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;
	TackleParameter& ReturnTackleParameter(){
		return tp;
	}

	std::vector<Vector3>& ReturnBonePosStorage(){
		return bonePosStorage;
	}

	std::vector<Vector3>& ReturnDashPosStorage(){
		return dashPosStorage;
	}

	void SpearHitActionStart(){
		spearHit = !spearHit;
		for (int i = 0; i < 109; i++) {
			deadBeforeLocalMatrix[i] = Matrix4::ToMatrix4(MV1GetFrameLocalMatrix(modelHandle, i + 1));
		}
		animIndex = MV1AttachAnim(modelHandle, 4, -1, FALSE);
		totalTime = MV1GetAttachAnimTotalTime(modelHandle, animIndex);

		tp.animTime = 0.0f;
		animBlend = 0.0f;

		tp.tackleFlag = false;
		tp.dashFlag = false;
		spearEndFlag = false;
	}

	void Damage(Actor& bullet,float damage,bool allow = false);

	bool ReturnDead(){ return dead; }

	bool OverHeat() { return dashHealFlag; }

private:
	Vector3 eventVec;

	bool spearHit = false;
	bool spearEndFlag = false;
	Vector3 spearVec = Vector3(0, 0, 0);
	
	bool dead2 = false;
	Matrix4* deadBeforeLocalMatrix;
	int deadMatrixSet = 0;

	bool allowNoDamageFlag = false;
	float allowNoDamageTime = 0.0f;
	bool dashAfter = false;
	float dashAfterTime = 0.0f;
	bool title,event;
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
	//ボーンの位置
	std::vector<Vector3> bonePosStorage;

	//移動量
	Vector3 vec;

	//ダメージを受けた際のパラメーター
	bool damageFlag;
	float damageCount;
	bool dead;

	//タックルのパラメーター
	TackleParameter tp;

	//加速ゲージの回復中
	bool dashHealFlag;
	//加速用のスピード
	float dashSpeed;
	//加速できる時間
	float dashTime;
	std::vector<Vector3> dashPosStorage;
	std::vector<int> tornadoPosStorage;
	std::shared_ptr<WindFlow> windFlowPtr;
	std::shared_ptr<Tornado> tornadoPtr;
	float tackleForTornadoTime;

	bool tornadoFlag;

	//posStorageに何もないときのボーンの方向
	Vector3 nonPosStorageVec;

	//回転のディレイをかけるために用いる前フレームのベクトル(y = 0.01fの理由はぴったりだとバグを生じるから)
	Vector3 beforeVec;

	//アニメーションの再生タイム
	float totalTime;
	//モデルハンドルを取得する(アニメーションのために)
	int modelHandle, animIndex;
	//アニメーションのブレンド
	float animBlend;
	//待機アニメーションをアタッチしたかどうか判断
	bool waitAnimSet;

	bool moveFlag = true;
	bool initMove;

	int	 DupModelHandle;
};
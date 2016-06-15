#pragma once

#include "../math/Vector3.h"

class Camera
{
private:
	Camera(){
		free_Position.Set(Vector3(0,0,0));// 視点の座標
		free_Target.Set(Vector3(0,0,1));	// 注視点の座標
		free_Up.Set(Vector3(0,1,0));
	}
	~Camera() = default;

public:
	static Camera &GetInstance(){
		static Camera c;
		return c;
	}

	///<summary>
	/// カメラの視点座標関係
	///</summary>
	class CPosition
	{
	private:
		Vector3 m_position;
	public:
		Vector3 Get() const { return m_position; }
		void Set(Vector3 position){ m_position = position; }
	};

	///<summary>
	/// カメラの注視点座標関係
	///</summary>
	class CTarget
	{
	private:
		Vector3 m_target;

	public:
		Vector3 Get() const { return m_target; }
		void Set(Vector3 target){ m_target = target; }
	};

	///<summary>
	/// カメラの上方向関係
	///</summary>
	class CUp
	{
	private:
		Vector3 m_up;
	public:
		Vector3 Get() const { return m_up; }
		void Set(Vector3 up){ m_up = up; }
	};


	///<summary>
	/// カメラの更新処理
	///</summary>
	void Update();

	///<summary>
	/// カメラの描画距離を設定する（手前距離、奥距離）
	///</summary>
	void SetRange(float Near, float Far);

	///<summary>
	/// カメラの回転角度を設定する（座標、垂直回転角度・水平回転角度・捻り回転角度）
	///</summary>
	void SetRotation(Vector3 rotate);

	///<summary>
	/// 指定した座標がカメラの視界に入っているか否か
	///</summary>
	int IsCheckView(Vector3 position);

	///<summary>
	/// カメラの視野角を設定する
	///</summary>
	void SetViewAngle(float degree);

public:
	CPosition Position;// 視点の座標
	CTarget Target;	// 注視点の座標
	CUp Up;			// 上方向
	CPosition free_Position;// 視点の座標
	CTarget free_Target;	// 注視点の座標
	CUp free_Up;
	Vector3 startTarget;
	float speed = 5.0f;
	float rotateSpeed = 1.0f;
	float rotateUp = 0.0f;
	Vector3 beforeVec = Vector3(0,0,1);
	bool freeCamera = false;
};
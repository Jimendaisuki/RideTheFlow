#pragma once

#include "../math/Vector3.h"

class Camera
{
public:
	Camera();
	~Camera() = default;

	///<summary>
	/// カメラの描画距離を設定する（手前距離、奥距離）
	///</summary>
	void SetRange(float Near, float Far);

	///<summary>
	/// カメラの視点座標関係
	///</summary>
	class CPosition
	{
	public:
		Vector3 m_position;

		Vector3 get() const { return m_position; }
		void set(Vector3 position){ m_position = position; }
	};

	///<summary>
	/// カメラの注視点座標関係
	///</summary>
	class CTarget
	{
	public:
		Vector3 m_target;

		Vector3 get() const { return m_target; }
		void set(Vector3 target){ m_target = target; }
	};

	///<summary>
	/// カメラの上方向関係
	///</summary>
	class CUp
	{
	public:
		Vector3 m_up;

		Vector3 get() const { return m_up; }
		void set(Vector3 up){ m_up = up; }
	};

	///<summary>
	/// カメラの回転角度を設定する（座標、垂直回転角度・水平回転角度・捻り回転角度）
	///</summary>
	void SetRotation(Vector3 rotate);

	///<summary>
	/// カメラの更新処理
	///</summary>
	void Update();

	///<summary>
	/// 指定した座標がカメラの視界に入っているか否か
	///</summary>
	int IsCheckView(Vector3 position);

public:
	CPosition Position;// 視点の座標
	CTarget Target;	// 注視点の座標
	CUp Up;			// 上方向

};
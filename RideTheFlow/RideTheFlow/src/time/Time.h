#pragma once

class Time
{
public:
	Time();

	///<summary>
	/// 更新処理
	///</summary>
	void Update();

	///<summary>
	/// 前フレームと今フレームの時間差
	///</summary>
	static float DeltaTime;

private:
	int savetime;// 前フレームの時間を保存
};
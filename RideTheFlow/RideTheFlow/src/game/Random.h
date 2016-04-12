#pragma once

#include <random>

class Random
{
public:
	Random();
	Random(int seed);
	~Random() = default;

	///<summary>
	/// 整数型の乱数を生成する（最小値、最大値）
	///</summary>
	int Range(int min, int max);

	///<summary>
	/// 実数型の乱数を生成する（最小値、最大値）
	///</summary>
	float Range(float min, float max);

	///<summary>
	/// 起点値の乱数を生成する（起点値、分散値）
	///</summary>
	float Point(float point, float variance);

private:
	std::random_device m_rnd_dev;	// 初期シード
	std::mt19937 m_mt;			// 乱数生成器

};
#pragma once

#include <random>

class Random
{
public:
	Random();
	Random(int seed);
	~Random() = default;

	///<summary>
	/// �����^�̗����𐶐�����i�ŏ��l�A�ő�l�j
	///</summary>
	int Range(int min, int max);

	///<summary>
	/// �����^�̗����𐶐�����i�ŏ��l�A�ő�l�j
	///</summary>
	float Range(float min, float max);

	///<summary>
	/// �N�_�l�̗����𐶐�����i�N�_�l�A���U�l�j
	///</summary>
	float Point(float point, float variance);

private:
	std::random_device m_rnd_dev;	// �����V�[�h
	std::mt19937 m_mt;			// ����������

};
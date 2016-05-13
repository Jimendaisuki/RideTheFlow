#pragma once
#include "Actor.h"
#include <vector>

//�_�b�V�����ɐ������闬��
class WindFlow :public Actor
{
public:
	WindFlow(IWorld& world, std::vector<Vector3>& positions_);
	~WindFlow();
	virtual void Update() override;
	virtual void Draw() const override;
	virtual void OnCollide(Actor& other, CollisionParameter colpara) override;

private:
	std::vector<Vector3> positions;

private:
	//���W������
	static const int SplitNum;
	//����̍����Œ�l�@����̍����`�Œ�l�܂ł��c�̒���
	static const float HeightMin;
};
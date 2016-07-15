#pragma once
#include "UIActor.h"
#include "MiniMap.h"
#include "../actor/Player.h"
#include <array>

class FlowRoot : public UIActor
{
	struct DrawPoints
	{
		Point	p1;
		Point	p2;
		Point	p3;
		Point	p4;
	};
public:
	FlowRoot(IWorld& world_, Player* player_, Vector2* point_, std::array<int, 10> piece);
	~FlowRoot();
	virtual void Update() override;
	virtual void Draw() const override;

private:
	// �v���C���[�|�C���^
	Player*		player;
	// �v���C���[�A���[�|�W�V�����|�C���^
	Vector2*	arrowPos;
	// �`��p�S�_
	DrawPoints	p;
	// �t���[���J�E���g
	int			count;
	// ����J�E���g
	float			flowCount;
	// ����I������
	float		deadTime;
	// �I���t���O
	bool		isEnd;
	// �������\�[�X�n���h���z��
	std::array<int, 10>		resPiece;
	// �v���C���[�O�Ճ��X�g
	std::list<Point>		playerTraces;
	// �O�Օ`��p�|�C���g���X�g
	std::list<DrawPoints>	drawPoints;
};
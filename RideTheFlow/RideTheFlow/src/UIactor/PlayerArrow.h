#pragma once
#include "UIActor.h"
#include "../actor/Player.h"
#include <array>

class PlayerArrow : public UIActor
{
public:
	PlayerArrow(IWorld& world, Player* player);
	~PlayerArrow();
	virtual void Update() override;
	virtual void Draw() const override;

private:
	// �v���C���[�|�C���^
	Player*		player;
	// �`��|�W�V����
	Vector2		drawPos_;
	// ��]�p�x
	float		angle_;
	// �_�b�V���t���O
	bool		isDash;
	// �O�t���[���_�b�V���t���O
	bool		prevDash;
	// �������\�[�X�n���h��
	std::array<int, 10>	resPiece;
};
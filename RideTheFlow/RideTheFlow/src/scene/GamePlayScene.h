#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"

class  GamePlayScene :public IScene{
public:
	//�R���X�g���N�^ 
	GamePlayScene();
	//�f�X�g���N�^
	~GamePlayScene();

	//�X�V�O������
	virtual void Initialize() override;
	//�X�V����
	virtual void Update()override;
	//�`�揈��
	virtual void Draw() const override;
	//�I�����Ă��邩�H
	virtual bool IsEnd() const override;
	//���̃V�[����Ԃ�
	virtual Scene Next() const override;
	//�I��������
	virtual void End()override;

private:
	Vector3 cameraPos;
	bool mIsEnd;
	World wa;
};
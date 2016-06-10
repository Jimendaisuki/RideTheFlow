#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"


class  MenuScene :public IScene
{
enum MENU_STATUS
{
	BEGIN = 0,
	STANBAY = 1,
	END = 2
};

public:
	//�R���X�g���N�^ 
	MenuScene();
	//�f�X�g���N�^
	~MenuScene();

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
	void VertexMove(VERTEX2D vertexs_[], int count_, float time_);
	bool IsStatusBegEnd() const;

private:
	bool mIsEnd;
	World wo;
	MENU_STATUS	status;
};
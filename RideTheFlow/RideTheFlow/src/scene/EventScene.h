#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"

class  EventScene :public IScene
{
	enum EVENT_STATUS
	{
		EVENT_BEGIN,
		EVENT_DRAGON_OUT,
		TITLE_TEXTURE_IN,
		TITLE_STANDBY,
		TITLE_END
	};

public:
	//�R���X�g���N�^ 
	EventScene();
	//�f�X�g���N�^
	~EventScene();

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
	void TornadoCalculation();
	void VertexMove(VERTEX2D vertexs_[], int count_, float time_);

private:
	float timer;
	bool mIsEnd;
	World wo;

	// �^�C�g���X�e�[�^�X
	EVENT_STATUS status;

	/* �����|���S���p�f�[�^ */
	int			texhandle;
	int			stormAlpha;
	int			count_1;
	int			count_2;
	float		stormAlphaTime;
	float		amount_1;
	float		amount_2;
	VERTEX2D	Vertex2D_1[6];
	VERTEX2D	Vertex2D_2[6];

	/* �^�C�g���e�L�X�g�p�f�[�^ */
	float titleAlpha;

	/* Fog */
	float currentFogFar;
	float maxFogFar;
	float correctionFog;
	float fogTime;
	float fogPeriod;

	Vector3 cameraPos;
	float length;
};
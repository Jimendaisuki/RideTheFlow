#pragma once

#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include <array>

class  TitleScene : public IScene
{
enum TITLE_STATUS
{
	TITLE_BEGIN,
	TITLE_DRAGON_IN,
	TITLE_TEXTURE_IN,
	TITLE_STANDBY,
	TITLE_END,
	GO_PV,
};

public:
	//�R���X�g���N�^ 
	TitleScene();
	//�f�X�g���N�^
	~TitleScene();

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
	void Pass();

private:
	bool  mIsEnd;
	World wo,wo2;

	// �^�C�g���X�e�[�^�X
	TITLE_STATUS status;

	/* �����|���S���p�f�[�^ */
	int			texhandle;
	int			stormAlpha;
	int			count_1;
	int			count_2;
	float		stormAlphaTime;
	float		amount_1;
	float		amount_2;
	std::array<VERTEX2D, 6>	Vertex2D_1;
	std::array<VERTEX2D, 6>	Vertex2D_2;

	/* �^�C�g���e�L�X�g�p�f�[�^ */
	float titleAlpha;
	float pressTextAlpha;
	float pressTextBackAlpha;
	float pressAlphaTime;
	float pressScale;

	/* �ʃX�N���[�� */
	int		screenHandle;
	float	screenPos;
	float	slideTime;

	bool	isTitle;
	float	timer;
};
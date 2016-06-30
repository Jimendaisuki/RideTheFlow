#include "IScene.h"
#include "ISceneMediator.h"
#include "../world/World.h"
#include <vector>

class  EndhingScene :public IScene{
public:
	enum ENDING_STATUS
	{
		ENDING_BEGIN = 0,
		ENDING_FADEOUT = 1,
		ENDING_DRAGON_OUT = 2,
		ENDING_CLEAR = 3,
		ENDING_END = 4
	};

public:
		//�R���X�g���N�^ 
	EndhingScene();
	//�f�X�g���N�^
	~EndhingScene();

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
	bool mIsEnd;
	World wa;
	ENDING_STATUS	status;

	float		length;
	float		seVol;
	float		angle;
	float		currentFog;
	Vector3		cameraPos;
	Vector3		targetPos;
	Vector3		velocity;

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
	bool	isTitle;
};
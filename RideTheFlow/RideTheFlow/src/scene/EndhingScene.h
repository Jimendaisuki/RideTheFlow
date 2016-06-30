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
};
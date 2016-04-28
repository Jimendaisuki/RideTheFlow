#include "Player.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../graphic/Sprite.h"
#include "../graphic/Model.h"
#include "../input/Keyboard.h"
#include "../time/Time.h"
#include "../graphic/Anime.h"
#include "../math/Math.h"
#include "../camera/Camera.h"
#include "../math/Quaternion.h"
#include "tornado\Tornado.h"

//�{�[���̐�
const int boneCount = 33;
//�g�̎��g
const float waveCount = 0.52f;
//���f���̃X�P�[��
const Vector3 scale = Vector3(0.01f, 0.01f, 0.01f);

/*************************************************�����N�N���ς���Ƃ���*************************************************/
//test�R�[�h�A�����̐؂�ւ�true�̎�����Ȃ�
bool changeMotion = true;

//changeMotion��true�̎��ɔ��f�����
//���˂��˂�Left����]���x
const float leftAngleSpeed = 270.0f;
//���˂��˂�Up����]���x
const float upAngleSpeed = 225.0f;

//changeMotion��false�̎��ɔ��f�����
//���˂��˂�Left����]���x
const float angleSpeed = 270.0f;

//�X�s�[�h
const float speed = 100.0f;
//��]�X�s�[�h
const float rotateSpeed = 250.0f;
/************************************************************************************************************************/

Player::Player(IWorld& world) :
Actor(world),
position(Vector3(0,0,0)),
tornadeTimer(0.0f)
{
	parameter.isDead = false;
	parameter.radius = 3.0f;

	//PlayerActor�̃}�g���b�N�X
	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);

	upAngle = 0;
	leftAngle = 0;
	boneSelect = 0;
	speedRegulation = 0;
	rotateUp = 0;
	rotateLeft = 0;

	rotateMat = new Matrix4[boneCount];
	for (int i = 0; i < boneCount; i++){
		rotateMat[i] = Matrix4::Identity;	
	}

	vertexVec = new Vector3[boneCount];
	deletePosStorageCount = 0;

	damageFlag = false;
	damageCount = 0;

	

	tackleFlag = false;
	tackleCount = 0.0f;
}
Player::~Player(){
	SAFE_DELETE_ARRAY(rotateMat);
	SAFE_DELETE_ARRAY(vertexVec);
	posStorage.clear();
}


void Player::Update(){

	//����
	Vector3 vec = Vector3::Zero;

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::UP))
		rotateLeft += rotateSpeed * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::DOWN))
		rotateLeft -= rotateSpeed * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT))
		rotateUp += rotateSpeed * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT))
		rotateUp -= rotateSpeed * Time::DeltaTime;

	rotateLeft = Math::Clamp(rotateLeft, -70.0f, 70.0f);

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A))
		vec.x += speed * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::D))
		vec.x -= speed * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::W))
		vec.z += speed * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::S))
		vec.z -= speed * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LSHIFT))
		tackleFlag = true;

	Vector3 cameraPos = Camera::GetInstance().Position.Get();
	//cameraPos.y = 0;

	if (!tackleFlag){
		position += (vec.z * (position - (cameraPos - Vector3(0,30,0)))).Normalized() * speed * Time::DeltaTime;
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::W) &&
			(Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT) ||
			Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT))){
			tornadeTimer += Time::DeltaTime;
		}
		else{
			tornadeTimer = 0;
		}

		if (tornadeTimer > 3.0f)
		{
			tornadeTimer = 0.0f;
			world.Add(ACTOR_ID::TORNADO_ACTOR, std::make_shared<Tornado>(world, position, Vector2(1, 1), Vector3::Zero));
		}

		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A) ||
			Keyboard::GetInstance().KeyStateDown(KEYCODE::D) ||
			Keyboard::GetInstance().KeyStateDown(KEYCODE::W) ||
			Keyboard::GetInstance().KeyStateDown(KEYCODE::S)){
			posStorage.push_back(position);
		}
	}
	else{
		world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::PLAYER_TORNADO_COL);
		tackleCount += Time::DeltaTime;
		parameter.height = (position - cameraPos).Normalized() * 30.0f;
		if (tackleCount > 2.0f){
			tackleCount = 0.0f;
			tackleFlag = false;
		}
	}

	//�{�[���̏��؂�ւ�
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::X))
		boneSelect++;
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Z))
		boneSelect--;

	////�{�[���̏��؂�ւ�
	//if (Keyboard::GetInstance().KeyStateDown(KEYCODE::Z))
	//	rotateY += 360.0f * Time::DeltaTime;
	//if (Keyboard::GetInstance().KeyStateDown(KEYCODE::X))
	//	rotateY -= 360.0f * Time::DeltaTime
	Matrix4 playerRot = Matrix4::Identity;
	Vector3 front = (Vector3(0, 0, 1) * 200.0f * Matrix4::RotateX(rotateLeft) * Matrix4::RotateY(rotateUp)).Normalized();
	playerRot.SetFront(front);
	Vector3 up = Vector3(0, 1, 0).Normalized();
	Vector3 left = Vector3::Cross(front, up).Normalized();
	up = Vector3::Cross(up, left).Normalized();

	playerRot.SetUp(up);
	playerRot.SetLeft(left);
	//�}�g���b�N�X�̍Čv�Z
	parameter.mat =
		Matrix4::Scale(scale) *
		playerRot * 
		Matrix4::Translate(position);

	//���˂��˂̊p�x�̃X�s�[�h
	if (changeMotion){
		upAngle -= leftAngleSpeed * Time::DeltaTime;
		leftAngle -= upAngleSpeed * Time::DeltaTime;
	}
	else{
		upAngle -=
			angleSpeed * Time::DeltaTime * Math::Cos(Math::Degree((Math::Sin(upAngle) + 1) / 2.0f));
		leftAngle -=
			angleSpeed * Time::DeltaTime * Math::Cos(Math::Degree((Math::Sin(upAngle) + 1) / 2.0f));
	}

	upAngle = Math::InfinityClamp(upAngle, 0.0f, 360.0f);
	leftAngle = Math::InfinityClamp(leftAngle, 0.0f, 360.0f);
	speedRegulation = Math::InfinityClamp(speedRegulation, 0.0f, 360.0f);


	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Position.Set(
		Vector3(0,0,1) * 250.0f * Matrix4::RotateX(rotateLeft) * Matrix4::RotateY(rotateUp) +  
		parameter.mat.GetPosition() + Vector3(0,30,0));
	Camera::GetInstance().Target.Set(parameter.mat.GetPosition());
	Camera::GetInstance().Up.Set(Vector3(0,1,0));
	Camera::GetInstance().Update();


	Vector3* copyVertexVec = new Vector3[boneCount];

	for (int i = 0; i < boneCount; i++){
		//�{�[���̏�Ԃ����Z�b�g
		MV1ResetFrameUserLocalMatrix(Model::GetInstance().GetHandle(MODEL_ID::TEST_MODEL), i + 1);
		//�����ʒu�{�[���̈ʒu���擾
		vertexVec[i] = Matrix4::ToMatrix4(
			MV1GetFrameLocalWorldMatrix(Model::GetInstance().GetHandle(MODEL_ID::TEST_MODEL), i + 1)).GetPosition() *
			Matrix4::Scale(scale);

		copyVertexVec[i] = vertexVec[i];
	}

	int storageCount = 0;
	Vector3 startPos = position;
	vertexVec[0] = position;

	deletePosStorageCount = posStorage.size();
	for (int i = posStorage.size() - 1; i >= 0; i--){
		if (storageCount + 1 >= boneCount){
			break;
		}
		else{
			deletePosStorageCount--;
		}
		if (Vector3::Length(startPos - posStorage[i]) >= Vector3::Length(copyVertexVec[storageCount] - copyVertexVec[storageCount + 1])){
			vertexVec[storageCount + 1] = startPos + (posStorage[i] - startPos).Normalized() * Vector3::Length(copyVertexVec[storageCount] - copyVertexVec[storageCount + 1]);
			startPos = vertexVec[storageCount + 1];
			storageCount++;
		}
	}
	while (!(storageCount + 1 >= boneCount)){
		vertexVec[storageCount + 1] = startPos + Vector3(0, 0, 1).Normalized() * Vector3::Length(copyVertexVec[storageCount] - copyVertexVec[storageCount + 1]);
		startPos = vertexVec[storageCount + 1];
		storageCount++;
	}


	int defaltSize = posStorage.size();
	for (int i = 0; i < deletePosStorageCount; i++)
	posStorage.erase(posStorage.begin());

	//deletePosStorageCount = 0;

	SAFE_DELETE_ARRAY(copyVertexVec);
	if (damageFlag){
		damageCount += Time::DeltaTime;
		if (damageCount > 1.0f){
			damageFlag = false;
			damageCount = 0;
		}
	}
}
void Player::Draw() const{
	//���̐������p�ӂ���
	Vector3* drawVertexVec = new Vector3[boneCount];
	Matrix4* drawMatrixVec = new Matrix4[boneCount];
	Vector3* copyVertexVec = new Vector3[boneCount];

	//������
	for (int i = 0; i < boneCount; i++){
		drawVertexVec[i] = vertexVec[i];
		drawMatrixVec[i] = parameter.mat;
	}


	for (int i = 0; i < boneCount; i++){
		copyVertexVec[i] = vertexVec[i];
	}
	
	//�擪�����_�Ɉړ�
	drawVertexVec[0] = vertexVec[0];

	//�擪�̍��������߂�׍Œ��_�̈ʒu�܂ł̌v�Z���s��
	for (int count = 1; count <= (boneCount / (int)(2.0f / waveCount)); count++){
		Matrix4 drawMat = 
			//�{�[���̒������߂ē�����
			Matrix4::Translate(vertexVec[count] - vertexVec[count - 1]) *
			//Left���AFront����ɉ�]
			//Quaternion::RotateAxis(parameter.mat.GetLeft().Normalized(), Math::Sin(upAngle + (count * 360.0f / (float)(boneCount * waveCount))) * 20.0f) *
			//Quaternion::RotateAxis(parameter.mat.GetUp().Normalized(), Math::Sin(leftAngle + (count * 360.0f / (float)(boneCount * waveCount))) * 20.0f) *
			Matrix4::Translate(drawVertexVec[count - 1]);
		drawVertexVec[count] = drawMat.GetPosition();
	}

	//�擪�̍�������
	//drawVertexVec[0] = -drawVertexVec[boneCount / (int)(2.0f / waveCount)];

	//�ړ��ʂ��������v���C���[�̃}�g���b�N�X���쐬
	Matrix4 paramMatSubTrans = parameter.mat;
	paramMatSubTrans.SetPosition(Vector3(0, 0, 0));


	//�}�g���b�N�X���Čv�Z
	drawMatrixVec[0] =
		Matrix4::Scale(scale) *
		Matrix4::Translate(drawVertexVec[0]);

	//�擪�̍�����ݒ肵����ԂōČv�Z
	for (int count = 1; count < boneCount; count++){
		Matrix4 drawMat = 
			Matrix4::Translate(vertexVec[count] - vertexVec[count - 1]) *			
			//Quaternion::RotateAxis(parameter.mat.GetLeft().Normalized(), Math::Sin(upAngle + (count * 360.0f / (float)(boneCount * waveCount))) * 20.0f) *
			//Quaternion::RotateAxis(parameter.mat.GetUp().Normalized(), Math::Sin(leftAngle + (count * 360.0f / (float)(boneCount * waveCount))) * 20.0f) *
			Matrix4::Translate(drawVertexVec[count - 1]);

		drawVertexVec[count] = drawMat.GetPosition();
		rotateMat[count] = Matrix4::Identity;
		Vector3 front = (drawVertexVec[count] - drawVertexVec[count - 1]).Normalized();
		rotateMat[count].SetFront(front);
		Vector3 up = Vector3(0,1,0).Normalized();
		Vector3 left = Vector3::Cross(front, up).Normalized();
		up = Vector3::Cross(left, front).Normalized();
		rotateMat[count].SetUp(up);
		rotateMat[count].SetLeft(left);

		//rotateMat[count] = Matrix4::Translate(front);
		drawMatrixVec[count] =
			Matrix4::Scale(scale) * 
			rotateMat[count] *
			//Quaternion::RotateAxis(parameter.mat.GetLeft().Normalized(), Math::Sin(upAngle + (count * 360.0f / (float)(boneCount * waveCount))) * 20.0f) *
			//Quaternion::RotateAxis(parameter.mat.GetUp().Normalized(), Math::Sin(leftAngle + (count * 360.0f / (float)(boneCount * waveCount))) * 20.0f) *
			Matrix4::Translate(drawVertexVec[count]);
	}


	//���΍��W�ɕϊ����Z�b�g
	for (int count = 0; count < boneCount; count++){
		Matrix4 beforeInvMat = Matrix4::Identity;
		//�e�̋t�s��������Ă���
		for (int count2 = 0; count2 < count; count2++){
			beforeInvMat *= Matrix4::Inverse(Matrix4::ToMatrix4(MV1GetFrameLocalMatrix(Model::GetInstance().GetHandle(MODEL_ID::TEST_MODEL), count2 + 1)));
		}
		MV1SetFrameUserLocalMatrix(Model::GetInstance().GetHandle(MODEL_ID::TEST_MODEL), count + 1,
			Matrix4::ToMATRIX(
			drawMatrixVec[count] *
			//drawInv //*
			beforeInvMat
			));
	}

	Model::GetInstance().Draw(MODEL_ID::TEST_MODEL, Vector3::Zero, 1.0f);
	if (damageFlag){
		DrawSphere3D(parameter.mat.GetPosition(), 10, 32, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
	}

	if (tackleFlag)
	DrawCapsule3D(position, position + parameter.height, parameter.radius, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
	
	//ParameterDraw();
	//for (int count = 0; count < boneCount - 1; count++){
	//	int Color = GetColor(255, 0, 0);
	//	if (count % 2 == 0)Color = GetColor(0, 255, 0);
	//	DrawLine3D(Vector3::ToVECTOR(drawVertexVec[count]), Vector3::ToVECTOR(drawVertexVec[count + 1]), Color);
	//}

	SAFE_DELETE_ARRAY(drawVertexVec);
	SAFE_DELETE_ARRAY(drawMatrixVec);
	SAFE_DELETE_ARRAY(copyVertexVec);
}


void Player::ParameterDraw() const{

	int ModelHandle = Model::GetInstance().GetHandle(MODEL_ID::TEST_MODEL);
	// �t���[�����̕`��
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Name         %s", MV1GetFrameName(ModelHandle, boneSelect));

	// �e�t���[�����̕`��
	int Parent = MV1GetFrameParent(ModelHandle, boneSelect);
	if (Parent == -2)
	{
		DrawFormatString(0, 16, GetColor(255, 255, 255), "Parent Name  None");
	}
	else
	{
		DrawFormatString(0, 16, GetColor(255, 255, 255), "Parent Name  %s", MV1GetFrameName(ModelHandle, Parent));
	}

	// �q�t���[���̐���`��
	DrawFormatString(0, 32, GetColor(255, 255, 255), "Child Num    %d", MV1GetFrameChildNum(ModelHandle, boneSelect));

	// �t���[���̃��[���h���W�̕`��
	VECTOR Position = position;// MV1GetFramePosition(ModelHandle, boneSelect);
	DrawFormatString(0, 48, GetColor(255, 255, 255), "Position     x:%f y:%f z:%f", Position.x, Position.y, Position.z);

	// �ϊ��s���`�悷��
	MATRIX Matrix = rotateMat[boneSelect].ToMATRIX();// MV1GetFrameLocalMatrix(ModelHandle, boneSelect);
	DrawFormatString(0, 64, GetColor(255, 255, 255), "   Matrix    %f %f %f %f", Matrix.m[0][0], Matrix.m[0][1], Matrix.m[0][2], Matrix.m[0][3]);
	DrawFormatString(0, 80, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[1][0], Matrix.m[1][1], Matrix.m[1][2], Matrix.m[1][3]);
	DrawFormatString(0, 96, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[2][0], Matrix.m[2][1], Matrix.m[2][2], Matrix.m[2][3]);
	DrawFormatString(0, 112, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[3][0], Matrix.m[3][1], Matrix.m[3][2], Matrix.m[3][3]);

	// �t���[���̃��[�J�����W���烏�[���h���W�ɕϊ�����s���`�悷��
	Matrix = MV1GetFrameLocalWorldMatrix(ModelHandle, boneSelect);
	DrawFormatString(0, 128, GetColor(255, 255, 255), "LW Matrix    %f %f %f %f", Matrix.m[0][0], Matrix.m[0][1], Matrix.m[0][2], Matrix.m[0][3]);
	DrawFormatString(0, 144, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[1][0], Matrix.m[1][1], Matrix.m[1][2], Matrix.m[1][3]);
	DrawFormatString(0, 160, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[2][0], Matrix.m[2][1], Matrix.m[2][2], Matrix.m[2][3]);
	DrawFormatString(0, 176, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[3][0], Matrix.m[3][1], Matrix.m[3][2], Matrix.m[3][3]);

	// �t���[���̕\����Ԃ�`��
	DrawFormatString(0, 192, GetColor(255, 255, 255), "Visible      %d", MV1GetFrameVisible(ModelHandle, boneSelect));

	// �t���[���ɔ������v�f�����邩�ǂ�����`��
	DrawFormatString(0, 208, GetColor(255, 255, 255), "Semi Trans   %d", MV1GetFrameSemiTransState(ModelHandle, boneSelect));

	// �t���[���Ɋ܂܂�郁�b�V���̐���`��
	DrawFormatString(0, 224, GetColor(255, 255, 255), "Mesh Num     %d", MV1GetFrameMeshNum(ModelHandle, boneSelect));

	// �t���[���Ɋ܂܂��O�p�`�|���S���̐���`��
	DrawFormatString(0, 240, GetColor(255, 255, 255), "Triangle Num %d", MV1GetFrameTriangleNum(ModelHandle, boneSelect));

	//// �t���[���ɔ������v�f�����邩�ǂ�����`��
	DrawFormatString(0, 256, GetColor(255, 255, 255), "FPS   %d", (int)(1.0f / Time::DeltaTime));

	//// �t���[���ɔ������v�f�����邩�ǂ�����`��
	DrawFormatString(0, 272, GetColor(255, 255, 255), "speedRegulation   %d", posStorage.size());
}
void Player::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (other.GetParameter().id != ACTOR_ID::TORNADO_ACTOR && !damageFlag){
		damageFlag = true;
	}
}
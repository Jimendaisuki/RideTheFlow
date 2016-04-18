#include "Player.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../graphic/Sprite.h"
#include "../graphic/Model.h"
#include "../input/Keyboard.h"
#include "../time/Time.h"
#include "../graphic/Anime.h"
#include "../math/Math.h"

const float Range = 0.05f;
const int ropeCount = 1000;

Player::Player(IWorld& world) :
Actor(world),
position(Vector3(3,0,0)),
otherVertex(Vector3(0,0,0)),
vertexVec(new Vector3[ropeCount])
{
	parameter.isDead = false;
	parameter.radius = 3.0f;
	vertexVec[0] = position;
	for (int count = 1; count < ropeCount - 1; count++){
		vertexVec[count] = Vector3(count * 3.0f, 0.0f, 0.0f);
	}

	parameter.mat =
		Matrix4::Scale(Vector3(0.3f, 0.3f, 0.3f)) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);
	angle = 0;
}
Player::~Player(){
	SAFE_DELETE_ARRAY(vertexVec);
}
void Player::Update()
{
	world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::SPHERE_SPHERE_COL);
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A))
		position.x -= 10.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::D))
		position.x += 10.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::W))
		position.y += 10.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::S))
		position.y -= 10.0f * Time::DeltaTime;

	if (Keyboard::GetInstance().AnyStateDown()){
		angle += 360.0f * Time::DeltaTime;
		position.y += 1.0f * Math::Sin(angle);
	}

	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::RIGHT))
		i++;
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LEFT))
		i--;

	parameter.mat =
		Matrix4::Scale(Vector3(1, 1, 1)) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(90) *
		Matrix4::Translate(position);

	vertexVec[0] = position;
	for (int count = 0; count < ropeCount - 1; count++){
		float d = Range - Vector3::Distance(vertexVec[count], vertexVec[count + 1]);
		Vector3 otherToPosVec = Vector3::Normalize(vertexVec[count] - vertexVec[count + 1]);
		vertexVec[count + 1] -= otherToPosVec * d;
	}

}
void Player::Draw() const{
	// �Q�Ԗڂ̃t���[���ɉ��ɓ����̃��[�J���s����Z�b�g����
	//Model::GetInstance().Draw(MODEL_ID::TEST_MODEL, parameter.mat.GetPosition() + Vector3(0.0f,0.0f,0.0f), 1.0f, Vector3(0, 0, 0));// Vector3(Matrix4::Pitch(parameter.mat), Matrix4::Yaw(parameter.mat), Matrix4::Roll(parameter.mat)));

	for (int count = 0; count< ropeCount - 1; count++){
		DrawLine3D(Vector3::ToVECTOR(vertexVec[count]), Vector3::ToVECTOR(vertexVec[count + 1]), GetColor(255, 255, 255));
	}

	DrawSphere3D(Vector3::ToVECTOR(vertexVec[0]), 1.0f, 32, GetColor(255, 255, 255), GetColor(255, 255, 255),FALSE);
	int ModelHandle = Model::GetInstance().GetHandle(MODEL_ID::TEST_MODEL);
	//for (int a = 1; a < 18; a++){
	//	MV1SetFrameUserLocalMatrix(ModelHandle, a, MGetTranslate(VGet(0.0f, 5.0f * Math::Sin(angle + a * 5), 0.0f)));
	//}

	// �t���[�����̕`��
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Name         %s", MV1GetFrameName(ModelHandle, i));

	// �e�t���[�����̕`��
	int Parent = MV1GetFrameParent(ModelHandle, i);
	if (Parent == -2)
	{
		DrawFormatString(0, 16, GetColor(255, 255, 255), "Parent Name  None");
	}
	else
	{
		DrawFormatString(0, 16, GetColor(255, 255, 255), "Parent Name  %s", MV1GetFrameName(ModelHandle, Parent));
	}

	// �q�t���[���̐���`��
	DrawFormatString(0, 32, GetColor(255, 255, 255), "Child Num    %d", MV1GetFrameChildNum(ModelHandle, i));

	// �t���[���̃��[���h���W�̕`��
	VECTOR Position = MV1GetFramePosition(ModelHandle, i);
	DrawFormatString(0, 48, GetColor(255, 255, 255), "Position     x:%f y:%f z:%f", Position.x, Position.y, Position.z);

	// �ϊ��s���`�悷��
	MATRIX Matrix = MV1GetFrameLocalMatrix(ModelHandle, i);
	DrawFormatString(0, 64, GetColor(255, 255, 255), "   Matrix    %f %f %f %f", Matrix.m[0][0], Matrix.m[0][1], Matrix.m[0][2], Matrix.m[0][3]);
	DrawFormatString(0, 80, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[1][0], Matrix.m[1][1], Matrix.m[1][2], Matrix.m[1][3]);
	DrawFormatString(0, 96, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[2][0], Matrix.m[2][1], Matrix.m[2][2], Matrix.m[2][3]);
	DrawFormatString(0, 112, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[3][0], Matrix.m[3][1], Matrix.m[3][2], Matrix.m[3][3]);

	// �t���[���̃��[�J�����W���烏�[���h���W�ɕϊ�����s���`�悷��
	Matrix = MV1GetFrameLocalWorldMatrix(ModelHandle, i);
	DrawFormatString(0, 128, GetColor(255, 255, 255), "LW Matrix    %f %f %f %f", Matrix.m[0][0], Matrix.m[0][1], Matrix.m[0][2], Matrix.m[0][3]);
	DrawFormatString(0, 144, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[1][0], Matrix.m[1][1], Matrix.m[1][2], Matrix.m[1][3]);
	DrawFormatString(0, 160, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[2][0], Matrix.m[2][1], Matrix.m[2][2], Matrix.m[2][3]);
	DrawFormatString(0, 176, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[3][0], Matrix.m[3][1], Matrix.m[3][2], Matrix.m[3][3]);

	// �t���[���̕\����Ԃ�`��
	DrawFormatString(0, 192, GetColor(255, 255, 255), "Visible      %d", MV1GetFrameVisible(ModelHandle, i));

	// �t���[���ɔ������v�f�����邩�ǂ�����`��
	DrawFormatString(0, 208, GetColor(255, 255, 255), "Semi Trans   %d", MV1GetFrameSemiTransState(ModelHandle, i));

	// �t���[���Ɋ܂܂�郁�b�V���̐���`��
	DrawFormatString(0, 224, GetColor(255, 255, 255), "Mesh Num     %d", MV1GetFrameMeshNum(ModelHandle, i));

	// �t���[���Ɋ܂܂��O�p�`�|���S���̐���`��
	DrawFormatString(0, 240, GetColor(255, 255, 255), "Triangle Num %d", MV1GetFrameTriangleNum(ModelHandle, i));

	// �t���[���ɔ������v�f�����邩�ǂ�����`��
	DrawFormatString(0, 256, GetColor(255, 255, 255), "Pitch   %f", Matrix4::Pitch(parameter.mat));

	float a = Matrix4::Yaw(parameter.mat);
	// �t���[���Ɋ܂܂�郁�b�V���̐���`��
	DrawFormatString(0, 272, GetColor(255, 255, 255), "Yaw     %f", Matrix4::Yaw(parameter.mat));

	// �t���[���Ɋ܂܂��O�p�`�|���S���̐���`��
	DrawFormatString(0, 288, GetColor(255, 255, 255), "Roll	   %f", Matrix4::Roll(parameter.mat));

	// �t���[���Ɋ܂܂��O�p�`�|���S���̐���`��
	DrawFormatString(0, 304, GetColor(255, 255, 255), "Sin	   %f", Math::Sin(angle));

	DrawSphere3D(Position, 1.0f, 32, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);

}
void Player::OnCollide(Actor& other, CollisionParameter colpara)
{
	position = Vector3(0, 0, 0);
}
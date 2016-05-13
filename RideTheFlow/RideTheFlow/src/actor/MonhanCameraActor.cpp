#include "MonhanCameraActor.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../camera/Camera.h"
#include "../input/Keyboard.h"
#include "../graphic/TextDraw.h"
#include "../time/Time.h"
#include <string>
#include "../math/Math.h"
#include "Player.h"
#include "Effect.h"
const Vector3 cameraUpMove = Vector3(0, 30, 0);
const Vector3 cameraDistance = 150.0f;
const float rotateSpeed = 250.0f;
/**�^�b�N�����J�����֌W**/
//�J�����̍���
const float UpCamera = 30.0f;
//�J�������ǂ̂��炢�v���C���[�̌��Ɉ�����
const float BackCamera = 150.0f;

/**�_�b�V�����̃J�����֌W**/
//�_�b�V�����̎���p(�x)
const float MaxFov = 120.0f;
//�J�����̍���
const float UpDashCamera = 200.0f;
//�J�������ǂ̂��炢�v���C���[�̌��Ɉ�����
const float BackDashCamera = 300.0f;

MonhanCameraActor::MonhanCameraActor(IWorld& world) :Actor(world),
restPosition(Vector3::Zero),
velocity(Vector3::Zero),
posSeve(true)
{
	parameter.isDead = false;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	rotateUp = 0;
	rotateLeft = 0;
	position = Vector3(0, 0, 1) * 250.0f * Matrix4::RotateX(rotateLeft) * Matrix4::RotateY(rotateUp) +
		playerMat.GetPosition() + cameraUpMove;
	restPosition = position;

	fov = 60.0f;

	test1 = 0.0f;

	springParameter.stiffness = 3.0f;
	springParameter.friction = 0.1f;
	springParameter.mass = 2.0f;

	testPositionSeve = Vector3::Zero;
	posSeveStart = Vector3(0, 0, 1) * cameraDistance * Matrix4::RotateX(rotateLeft) * Matrix4::RotateY(rotateUp) +
		playerMat.GetPosition() + cameraUpMove;
}
MonhanCameraActor::~MonhanCameraActor()
{

}
void MonhanCameraActor::Update()
{
	TackleParameter tp;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
		tp = static_cast<Player*>(const_cast<Actor*>(&other))->ReturnTackleParameter();
	});
	Vector3 left = Vector3::Cross(tp.tackleT, Vector3(0, 1, 0).Normalized()).Normalized();
	Vector3 up = Vector3::Cross(left, tp.tackleT).Normalized();
	//�^�b�N�����ĂȂ�
	if (!tp.tackleFlag)
		//�J�����ړ�
	{
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::UP))
			rotateLeft += rotateSpeed * Time::DeltaTime;
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::DOWN))
			rotateLeft -= rotateSpeed * Time::DeltaTime;
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT))
			rotateUp += rotateSpeed * Time::DeltaTime;
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT))
			rotateUp -= rotateSpeed * Time::DeltaTime;
		rotateLeft = Math::Clamp(rotateLeft, -70.0f, 70.0f);
		restPosition = Vector3(0, 0, 1) * cameraDistance * Matrix4::RotateX(rotateLeft) * Matrix4::RotateY(rotateUp) +
			playerMat.GetPosition() + cameraUpMove;

		//�_�b�V������
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LSHIFT))
		{
			Effect::GetInstance().DashEffect(world, playerMat.GetPosition());
			restPosition = playerMat.GetPosition() + tp.tackleT*(-BackDashCamera) + up*UpDashCamera;
			if (posSeve)
			{
				posSeve = false;
				posSeveStart = position;
				test1 = Vector3::Distance(restPosition, position);
			}
			fov = Math::Lerp(60.0f, MaxFov, Vector3::Distance(posSeveStart, position) / test1);
		}
		else if (Vector3::Distance(posSeveStart, position) / test1!=0)
		{
			fov = Math::Lerp(60.0f, MaxFov, Vector3::Distance(posSeveStart, position) / test1);
			posSeve = true;
		}
	}
	else
	{
		//�^�b�N����
		restPosition = playerMat.GetPosition()+tp.tackleT*(-BackCamera)+up*UpCamera;
		rotateUp = atan2(playerMat.GetPosition().x - position.x, playerMat.GetPosition().z - position.z) * 180 / 3.1415f + 180;
	}
	
	//�o�l�J����(�|�W�V����)
	Vector3 stretch = (position - restPosition);
	Vector3 force = -springParameter.stiffness * stretch;
	Vector3 acceleration = force / springParameter.mass;
	velocity =springParameter.friction * (velocity + acceleration);
	position += velocity;

	Camera::GetInstance().Position.Set(position);
	Camera::GetInstance().Target.Set(playerMat.GetPosition());
	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Up.Set(Vector3(0, 1, 0));
	Camera::GetInstance().SetViewAngle(fov);
	Camera::GetInstance().Update();
}
void MonhanCameraActor::Draw() const
{
	DrawFormatString(0, 128, GetColor(0, 0, 0), "playerPosition   %f %f %f", playerMat.GetPosition().x, playerMat.GetPosition().y, playerMat.GetPosition().z);
	DrawFormatString(0, 192, GetColor(0, 0, 0), "cameraPosition   %f %f %f", position.x, position.y, position.z);
	DrawFormatString(0, 256, GetColor(0, 0, 0), "Angle   %f", rotateUp);
	DrawFormatString(0, 356, GetColor(0, 0, 0), "Fov   %f", fov);
}
void MonhanCameraActor::OnCollide(Actor& other, CollisionParameter colpara)
{

}
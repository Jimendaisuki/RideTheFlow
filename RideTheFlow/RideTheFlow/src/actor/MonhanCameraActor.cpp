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
const float rotateSpeed = 250.0f;

/**タックル中カメラ関係**/
//カメラの高さ
const float UpCamera = 30.0f;
//カメラをどのぐらいプレイヤーの後ろに引くか
const float BackCamera = 150.0f;

/**ダッシュ中のカメラ関係**/
//ダッシュ中の視野角(度)
const float MaxFov = 80.0f;
//カメラの高さ
const float UpDashCamera = 30.0f;
//カメラをどのぐらいプレイヤーの後ろに引くか
const float BackDashCamera = 100.0f;

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

	targetPos = playerMat.GetPosition();
	fov = 60.0f;

	springParameter.stiffness = 3.0f;
	springParameter.friction = 0.1f;
	springParameter.mass = 2.0f;
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
	//タックルしてない
	if (!tp.tackleFlag)
		//カメラ移動
	{
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::UP))
			rotateLeft += rotateSpeed * Time::DeltaTime;
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::DOWN))
			rotateLeft -= rotateSpeed * Time::DeltaTime;
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT))
			rotateUp += rotateSpeed * Time::DeltaTime;
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT))
			rotateUp -= rotateSpeed * Time::DeltaTime;
		rotateLeft = Math::Clamp(rotateLeft, -50.0f, 50.0f);
		restPosition = Vector3(0, 0, 1) * 250.0f * Matrix4::RotateX(rotateLeft) * Matrix4::RotateY(rotateUp) +
			playerMat.GetPosition() + cameraUpMove;
		targetPos = playerMat.GetPosition();

		//ダッシュ処理
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LSHIFT))
		{
			Effect::GetInstance().DashEffect(world, playerMat.GetPosition());
			if (posSeve)
			{
				posSeve = false;
				posSeveEnd = playerMat.GetPosition() + tp.tackleT*(-BackDashCamera) + up*UpDashCamera;
				posSeveStart = restPosition;
			}
			leapTimer += 3 * Time::DeltaTime;
			leapTimer = Math::Clamp(leapTimer, 0.0f, 1.0f);
			restPosition = Math::Lerp(posSeveStart, posSeveEnd, leapTimer);
			fov = Math::Lerp(60.0f, MaxFov, leapTimer);
			rotateUp = atan2(playerMat.GetPosition().x - position.x, playerMat.GetPosition().z - position.z) * 180 / 3.1415f + 180;
			Camera::GetInstance().SetViewAngle(fov);
		}
		else
		{
			leapTimer -= 3 * Time::DeltaTime;
			leapTimer = Math::Clamp(leapTimer, 0.0f, 1.0f);
			restPosition = Math::Lerp(Vector3(0, 0, 1) * 250.0f * Matrix4::RotateX(rotateLeft) * Matrix4::RotateY(rotateUp) +
				playerMat.GetPosition() + cameraUpMove, posSeveEnd, leapTimer);
			leapTimer = Math::Clamp(leapTimer, 0.0f, 1.0f);
			fov = Math::Lerp(60.0f, 80.0f, leapTimer);
			posSeve = true;
			Camera::GetInstance().SetViewAngle(fov);
		}
	}
	else
	{
		//タックル中
		restPosition = playerMat.GetPosition()+tp.tackleT*(-BackCamera)+up*UpCamera;
		targetPos = playerMat.GetPosition() + tp.tackleT*20.0f;
		rotateUp = atan2(playerMat.GetPosition().x - position.x, playerMat.GetPosition().z - position.z) * 180 / 3.1415f + 180;
	}
	
	//バネカメラ(ポジション)
	Vector3 stretch = (position - restPosition);
	Vector3 force = -springParameter.stiffness * stretch;
	Vector3 acceleration = force / springParameter.mass;
	velocity =springParameter.friction * (velocity + acceleration);
	position += velocity;

	Camera::GetInstance().Position.Set(position);
	Camera::GetInstance().Target.Set(targetPos);
	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Up.Set(Vector3(0, 1, 0));
	Camera::GetInstance().Update();
}
void MonhanCameraActor::Draw() const
{
	DrawFormatString(0, 128, GetColor(0, 0, 0), "playerPosition   %f %f %f", playerMat.GetPosition().x, playerMat.GetPosition().y, playerMat.GetPosition().z);
	DrawFormatString(0, 192, GetColor(0, 0, 0), "cameraPosition   %f %f %f", position.x, position.y, position.z);
	DrawFormatString(0, 256, GetColor(0, 0, 0), "Angle   %f", leapTimer);
	DrawFormatString(0, 356, GetColor(0, 0, 0), "Fov   %f", fov);
}
void MonhanCameraActor::OnCollide(Actor& other, CollisionParameter colpara)
{

}
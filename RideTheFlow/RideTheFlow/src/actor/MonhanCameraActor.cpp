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
#include "../UIactor/Effect.h"

const Vector3 cameraUpMove = Vector3(0, 30, 0);
const Vector3 cameraDistance = 150.0f;
const float rotateSpeed = 250.0f;
/**タックル中カメラ関係**/
//カメラの高さ
const float UpCamera = 50.0f;
//カメラをどのぐらいプレイヤーの後ろに引くか
const float BackCamera = 150.0f;

/**ダッシュ中のカメラ関係**/
//ダッシュ中の視野角(度)
const float MaxFov = 120.0f;
//カメラの高さ
const float UpDashCamera = 200.0f;
//カメラをどのぐらいプレイヤーの後ろに引くか
const float BackDashCamera = 300.0f;

MonhanCameraActor::MonhanCameraActor(IWorld& world) :Actor(world),
velocity(Vector3::Zero),
posMove1(false),
posMove2(false),
playerPosSeve(Vector3::Zero),
leapTimer(0.0f)
{
	parameter.isDead = false;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	rotateUp = 0;
	rotateLeft = 0;
	position = DefaultCamera();
	restPosition = position;
	fov = 60.0f;

	springParameter.stiffness = 3.0f;
	springParameter.friction = 0.1f;
	springParameter.mass = 2.0f;

	posSeveStart = DefaultCamera();

	test = Vector3::Zero;
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
	test=tp.tackleT;
	//プレイヤーの向き取得
	Vector3 left = Vector3::Cross(tp.tackleT, Vector3(0, 1, 0).Normalized()).Normalized();
	Vector3 up = Vector3::Cross(left, tp.tackleT).Normalized();

	if (!tp.tackleFlag&&!tp.dashFlag&&!posMove2)
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
		restPosition = DefaultCamera();
	}

	if ((int)tp.animTime == 30 && !posMove1)
	{
		posMove1 = true;
		posSeveStart = position;
		posSeveEnd = playerMat.GetPosition() + tp.tackleT*(-BackCamera) + up*UpCamera;
		playerPosSeve = playerMat.GetPosition();
	}
	else if (!posMove1 && (int)tp.animTime < 30)
	{
		restPosition += Vector3::Direction(position, playerMat.GetPosition()).Normalized() / 1.2f;
	}

	if (posMove1)
	{
		leapTimer += 5.0f*Time::DeltaTime;
		restPosition = Vector3::Lerp(posSeveStart, posSeveEnd, leapTimer);
		if (leapTimer >= 1.0f)
		{
			rotateLeft = -20.0f;
			rotateUp = atan2(playerMat.GetPosition().x - restPosition.x, playerMat.GetPosition().z - restPosition.z) * 180 / 3.1415f + 180;
			posSeveStart = restPosition;
			posSeveEnd = DefaultCamera();
			leapTimer = 0.0f;
			posMove1 = false;
			posMove2 = true;
		}
	}
	if (posMove2)
	{
		leapTimer += 1.0f / 2.0f*Time::DeltaTime;
		restPosition = Vector3::Lerp(posSeveStart, posSeveEnd, leapTimer)+(playerMat.GetPosition()-playerPosSeve);
		if (leapTimer >= 1.0f)
		{
			leapTimer = 0.0f;
			posMove2 = false;
		}
	}




	if (tp.dashFlag)
	{
		//ダッシュ処理
		Effect::GetInstance().DashEffect(world, playerMat.GetPosition());

		//rotateUp = atan2(playerMat.GetPosition().x - position.x, playerMat.GetPosition().z - position.z) * 180 / 3.1415f + 180;
		//restPosition = DefaultCamera();
		//if (posSeve)
		//{
		//	posSeve = false;
		//	posSeveStart = position;
		//	test1 = Vector3::Distance(restPosition, position);
		//}
		//fov = Math::Lerp(60.0f, MaxFov, Vector3::Distance(posSeveStart, position) / test1);
	}
	else
	{
		playerPosSeve = playerMat.GetPosition();
	}
	//バネカメラ(ポジション)
	Vector3 stretch = (position - restPosition);
	Vector3 force = -springParameter.stiffness * stretch;
	Vector3 acceleration = force / springParameter.mass;
	velocity =springParameter.friction * (velocity + acceleration);
	position += velocity;

	Camera::GetInstance().Position.Set(position);
	Camera::GetInstance().Target.Set(playerMat.GetPosition());
	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Up.Set(Vector3(0, 1, 0));
	//Camera::GetInstance().SetViewAngle(fov);
	Camera::GetInstance().Update();
}
void MonhanCameraActor::Draw() const
{
	DrawFormatString(0, 128, GetColor(0, 0, 0), "startPosition   %f %f %f", test.x, test.y, test.z);
	//DrawFormatString(0, 192, GetColor(0, 0, 0), "endPosition   %f %f %f", );
	DrawFormatString(0, 256, GetColor(0, 0, 0), "Angle   %f", rotateUp);
	DrawFormatString(0, 356, GetColor(0, 0, 0), "Fov   %f",leapTimer);
	DrawLine3D(Vector3::ToVECTOR((test*100+playerMat.GetPosition())),Vector3::ToVECTOR(playerMat.GetPosition()),2);
}
void MonhanCameraActor::OnCollide(Actor& other, CollisionParameter colpara)
{

}

Vector3 MonhanCameraActor::DefaultCamera()
{
	return Vector3(0, 0, 1) * cameraDistance * Matrix4::RotateX(rotateLeft) * Matrix4::RotateY(rotateUp) +
		playerMat.GetPosition() + cameraUpMove;
}
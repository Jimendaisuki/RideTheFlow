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
#include "../input/GamePad.h"

const Vector3 cameraUpMove = Vector3(0, 30, 0);
const Vector3 cameraDistance = 150.0f;
const float rotateSpeed = 250.0f;
/**タックル中カメラ関係**/
//カメラの高さ
const float UpCamera = 75.0f;
//カメラをどのぐらいプレイヤーの後ろに引くか
const float BackCamera = 250.0f;

/**ダッシュ中のカメラ関係**/
//ダッシュ中の視野角(度)
const float MaxFov = 120.0f;
//カメラの高さ
const float UpDashCamera = 200.0f;
//カメラをどのぐらいプレイヤーの後ろに引くか
const float BackDashCamera = 300.0f;

MonhanCameraActor::MonhanCameraActor(IWorld& world) :Actor(world),
playerPosSeve(Vector3::Zero),
velocity(Vector3::Zero),
posMove1(true),
posMove2(true),
cameraFovFlag(true),
cameraFovEndFlag(true),
posEnd(false),
rotateUp(0.0f),
rotateLeft(0.0f),
rotateVelo(0.0f),
leapTimer(0.0f),
restLeapTimer(0.0f),
tackleLeapTimer(0.0f),
fovVelo(0.0f)
{
	//パラメーター設定
	parameter.isDead = false;
	parameter.id = ACTOR_ID::CAMERA_ACTOR;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	//バネ設定
	springParameter.stiffness = 3.0f;
	springParameter.friction = 0.1f;
	springParameter.mass = 2.0f;

	springTargetParameter.stiffness = 5.0f;
	springTargetParameter.friction = 0.1f;
	springTargetParameter.mass = 2.0f;


	position = DefaultCamera();
	restPosition = position;
	fov = 60.0f;
	posSeveStart = DefaultCamera();
	restRotate = rotateLeft;
	
	startTarget = Vector3::Zero;
	endTarget = Vector3::Zero;

	

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

	//プレイヤーの向き取得
	Vector3 left = Vector3::Cross(tp.tackleT, Vector3(0, 1, 0).Normalized()).Normalized();
	Vector3 up = Vector3::Cross(left, tp.tackleT).Normalized();

	//デフォルトでのカメラ
	if (!tp.tackleFlag&&!tp.dashFlag&&posMove2)
	{
		Vector2 rStick = GamePad::GetInstance().RightStick();

		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::UP) || rStick.y < 0.0f)
			rotateLeft += rotateSpeed * Time::DeltaTime;
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::DOWN) || rStick.y > 0.0f)
			rotateLeft -= rotateSpeed * Time::DeltaTime;
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT) || rStick.x > 0.0f)
			rotateUp += rotateSpeed * Time::DeltaTime;
		if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT) || rStick.x < 0.0f)
			rotateUp -= rotateSpeed * Time::DeltaTime;

		rotateUp = (int)rotateUp % 360;
		rotateLeft = Math::Clamp(rotateLeft, -70.0f, 70.0f);
		restPosition = DefaultCamera();
	}


	//タックル
	if (tp.tackleFlag)
	{
		if (posEnd)
		{
			posEnd = false;
			posSeveStart = position;
			posSeveEnd = Vector3::Direction(parameter.mat.GetPosition(), playerMat.GetPosition())*50.0f + parameter.mat.GetPosition();
		}

		if ((int)tp.animTime < 170)
		{
			if (tackleLeapTimer <= 1.0f)
				tackleLeapTimer += 12.0f / 20.0f*Time::DeltaTime;
			restPosition = Vector3::Lerp(posSeveStart, posSeveEnd, tackleLeapTimer);
		}
		if ((int)tp.animTime >= 170 && posMove2)
		{
			if (posMove1)
			{
				tackleLeapTimer = 0.0f;
				posMove1 = false;
				rotateUp = Math::Atan2(playerMat.GetPosition().x - (-playerMat.GetFront().x + playerMat.GetPosition().x),
					playerMat.GetPosition().z - (-playerMat.GetFront().z + playerMat.GetPosition().z))
					* 180 / 3.1415f + 180;
				posSeveStart = position;
				
				if (tp.tornadoTatchFlag)
				{
					rotateLeft = 0.0f;
					posSeveEnd = Vector3(0, 0, 1) * 300 * Matrix4::RotateX(rotateLeft) * Matrix4::RotateY(rotateUp) +
						playerMat.GetPosition() + cameraUpMove;
				}
				else
				{
					rotateLeft = -25;
					posSeveEnd = playerMat.GetPosition()
						+ tp.tackleT*(-BackCamera) + up*UpCamera;
				}
			}
			restPosition = Vector3::Lerp(posSeveStart, posSeveEnd, tackleLeapTimer);
			tackleLeapTimer += 3.0f*Time::DeltaTime;
			if (tackleLeapTimer >= 3.0f)
			{
				posMove2 = false;
				rotateUp = Math::Atan2(playerMat.GetPosition().x - restPosition.x,
					playerMat.GetPosition().z - restPosition.z)
					* 180 / 3.1415f + 180;
				posSeveStart = position;
				posSeveEnd = DefaultCamera();
				tackleLeapTimer = 0.0f;
			}
		}
	}
	else
	{
		posEnd = true;
	}
	if (!posMove2)
	{
		tackleLeapTimer += 1.3f*Time::DeltaTime;
		restPosition = Vector3::Lerp(posSeveStart, posSeveEnd, tackleLeapTimer);
		if (tackleLeapTimer >= 1.0f)
		{
			posMove2 = true;
			posMove1 = true;
			tackleLeapTimer = 0.0f;
		}
	}

	//タックル
	//if (tp.tackleFlag)
	//{
	//	if (posEnd)
	//	{
	//		posEnd = false;
	//		posSeveStart = position;
	//		posSeveEnd = Vector3::Direction(parameter.mat.GetPosition(), playerMat.GetPosition())*50.0f+parameter.mat.GetPosition();
	//	}

	//	if ((int)tp.animTime < 170)
	//	{
	//		if (tackleLeapTimer <= 1.0f)
	//			tackleLeapTimer += 12.0f / 20.0f*Time::DeltaTime;
	//		restPosition = Vector3::Lerp(posSeveStart, posSeveEnd, tackleLeapTimer);
	//	}
	//	if ((int)tp.animTime >= 170 && posMove2)
	//	{
	//		if (posMove1)
	//		{
	//			tackleLeapTimer = 0.0f;
	//			posMove1 = false;
	//			rotateUp = Math::Atan2(playerMat.GetPosition().x - (-playerMat.GetFront().x+playerMat.GetPosition().x),
	//				playerMat.GetPosition().z - (-playerMat.GetFront().z + playerMat.GetPosition().z))
	//				* 180 / 3.1415f + 180;

	//			posSeveStart = position;

	//			if (tp.tornadoTatchFlag||true)
	//			{
	//				posSeveEnd = Vector3(0, 0, 1) * 200 * Matrix4::RotateX(-40) * Matrix4::RotateY(rotateUp) +
	//					playerMat.GetPosition() + cameraUpMove;
	//				restCameraTarget = Vector3(playerMat.GetPosition().x, posSeveEnd.y, playerMat.GetPosition().z);
	//			}
	//			else
	//			{
	//				posSeveEnd = playerMat.GetPosition()
	//					+ tp.tackleT*(-BackCamera) + up*UpCamera;
	//			}
	//		}
	//		restPosition = Vector3::Lerp(posSeveStart, posSeveEnd, tackleLeapTimer);
	//		tackleLeapTimer += 3.0f*Time::DeltaTime;
	//		if (tackleLeapTimer >= 3.0f)
	//		{
	//			restCameraTarget = playerMat.GetPosition();
	//			posMove2 = false;
	//			rotateLeft = -25;
	//			rotateUp = Math::Atan2(playerMat.GetPosition().x - restPosition.x,
	//				playerMat.GetPosition().z - restPosition.z)
	//				* 180 / 3.1415f + 180;
	//			posSeveStart = position;
	//			
	//			posSeveEnd = DefaultCamera();
	//			tackleLeapTimer = 0.0f;
	//		}
	//	}
	//}
	//else
	//{
	//	restCameraTarget = playerMat.GetPosition();
	//	posEnd = true;
	//}
	//if (!posMove2)
	//{
	//	tackleLeapTimer += 1.3f*Time::DeltaTime;
	//	restPosition = Vector3::Lerp(posSeveStart, posSeveEnd, tackleLeapTimer);
	//	if (tackleLeapTimer >= 1.0f)
	//	{
	//		posMove2 = true;
	//		posMove1 = true;
	//		tackleLeapTimer = 0.0f;
	//	}
	//}
	//SpringTarget();
	//cameraTarget += targetVelo;


	//ダッシュ処理
	if (tp.dashFlag)
	{
		restPosition = DashCmaera();
		springParameter.stiffness = 3.0f;
		restLeapTimer = 1.0f;
		fov = Math::Lerp(60.0f, MaxFov, leapTimer);
	}
	else
	{
		restLeapTimer = 0.0f;
		fov = Math::Lerp(60.0f, MaxFov, leapTimer);
	}
	leapTimer += SpringFov(restLeapTimer, leapTimer);

	//バネカメラ
	Vector3 stretch = (position - restPosition);
	Vector3 force = -springParameter.stiffness * stretch;
	Vector3 acceleration = force / springParameter.mass;
	velocity = springParameter.friction * (velocity + acceleration);
	position += velocity;

	parameter.mat = Matrix4::Translate(position);
	Camera::GetInstance().Position.Set(position);
	Camera::GetInstance().Target.Set(playerMat.GetPosition());
	Camera::GetInstance().SetRange(0.1f, 40000.0f);
	Camera::GetInstance().Up.Set(Vector3(0, 1, 0));
	Camera::GetInstance().SetViewAngle(fov);
	Camera::GetInstance().Update();
}
void MonhanCameraActor::Draw() const
{
	//DrawLine3D(Vector3::ToVECTOR(playerMat.GetPosition()), Vector3::ToVECTOR(playerMat.GetUp().Normalized()*100.0f + playerMat.GetPosition()), 1);
}
void MonhanCameraActor::OnCollide(Actor& other, CollisionParameter colpara)
{

}

Vector3 MonhanCameraActor::DefaultCamera()
{
	return Vector3(0, 0, 1) * cameraDistance * Matrix4::RotateX(rotateLeft) * Matrix4::RotateY(rotateUp) +
		playerMat.GetPosition() + cameraUpMove;
}
Vector3 MonhanCameraActor::DashCmaera()
{
	restRotate = -45.0f;
	rotateUp = atan2(playerMat.GetPosition().x - restPosition.x,
		playerMat.GetPosition().z - restPosition.z) * 180 / 3.1415f + 180;

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT))
		rotateUp += rotateSpeed * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT))
		rotateUp -= rotateSpeed * Time::DeltaTime;


	float stretchRotate = (rotateLeft - restRotate);
	float forceRotate = -0.8f * stretchRotate;
	float accelerationRotate = forceRotate / 2.0f;
	rotateVelo = 0.1f* (rotateVelo + accelerationRotate);
	rotateLeft += rotateVelo;

	rotateLeft = Math::Clamp(rotateLeft, -70.0f, 70.0f);

	return Vector3(0, 0, 1) * 200 * Matrix4::RotateX(rotateLeft) * Matrix4::RotateY(rotateUp) +
		playerMat.GetPosition() + cameraUpMove;
}
float MonhanCameraActor::SpringFov(float rest, float pos)
{
	float stretchFov = (pos - rest);
	float forceFov = -0.4f * stretchFov;
	float accelerationFov = forceFov / 2.0f;
	fovVelo = 0.1f* (fovVelo + accelerationFov);
	return fovVelo;
}
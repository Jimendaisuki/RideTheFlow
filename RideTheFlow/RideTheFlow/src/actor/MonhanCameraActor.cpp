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
	parameter.id = ACTOR_ID::CAMERA_ACTOR;
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

	cameraMovePos = Vector3::Zero;

	posSeveFlag = true;
	cameraFovFlag = true;
	cameraFovEndFlag = false;

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


	//タックル処理
	if (tp.tackleFlag)
	{
		//30フレーム目
		if ((int)tp.animTime == 30 && !posMove1)
		{
			posMove1 = true;
			posSeveStart = position;
			posSeveEnd = playerMat.GetPosition() + tp.tackleT*(-BackCamera) + up*UpCamera;
			playerPosSeve = playerMat.GetPosition();
		}
		//30フレームまではカメラを近づける
		else if (!posMove1 && (int)tp.animTime < 30)
		{
			restPosition += Vector3::Direction(position, playerMat.GetPosition()).Normalized() / 1.2f;
		}
		//30フレーム後の処理
		if (posMove1)
		{
			leapTimer += 5.0f*Time::DeltaTime;
			restPosition = Vector3::Lerp(posSeveStart, posSeveEnd, leapTimer);
			if (leapTimer >= 1.0f)
			{
				rotateLeft = -20.0f;
				rotateUp = atan2(playerMat.GetPosition().x - restPosition.x,
					playerMat.GetPosition().z - restPosition.z) * 180 / 3.1415f + 180;
				posSeveStart = restPosition;
				posSeveEnd = DefaultCamera();
				leapTimer = 0.0f;
				posMove1 = false;
				posMove2 = true;
			}
		}
	}
	//タックル後カメラを元の位置に戻す
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

	//ダッシュ処理
	if (tp.dashFlag)
	{
		//カメラが止まる範囲設定
		cameraMovePos = Vector3(restPosition.x, playerMat.GetPosition().y, restPosition.z);
		Effect::GetInstance().DashEffect(world, playerMat.GetFront().Normalized() * 100 + playerMat.GetPosition());
		if (posSeveFlag)
		{
			//ダッシュカメラの初期設定
			posSeveFlag = false;
			dashCameraDistance = Vector3::Distance(playerMat.GetPosition(),
				Vector3(DashCmaera().x,playerMat.GetPosition().y,
				DashCmaera().z));
			restPosition = DashCmaera()
				+Vector3::Direction(restPosition,playerMat.GetPosition()).Normalized()
				*Vector3(150,0,150);
			springParameter.stiffness = 0.5f;
		}
	    //視野角設定
		if (cameraFovFlag)
		{
			fov = Math::Lerp(60.0f,MaxFov,leapTimer);
			leapTimer += Time::DeltaTime;
			if (leapTimer >= 1.0f)
			{
				leapTimer = 1.0f;
				cameraFovFlag = false;
			}
		}
		//一定の範囲を超えたら追尾
		if (Vector3::Distance(playerMat.GetPosition(), cameraMovePos) >= dashCameraDistance)
		{
			restPosition = DashCmaera();
		}
		else
		{
			rotateUp = atan2(playerMat.GetPosition().x - restPosition.x,
				playerMat.GetPosition().z - restPosition.z) * 180 / 3.1415f + 180;
		}
	}
	//ダッシュ後の後処理
	else if (!posSeveFlag)
	{
		cameraFovEndFlag = true;
		cameraFovFlag = true;
		posSeveFlag = true;
		springParameter.stiffness = 4.0f;
	}
	//ダッシュ後視野角を戻す
	if (cameraFovEndFlag)
	{
		//rotateLeft = -45;
		leapTimer-=3*Time::DeltaTime;
		fov = Math::Lerp(60.0f,MaxFov,leapTimer);
		if (leapTimer <= 0.0f)
		{
			leapTimer = 0.0f;
			cameraFovEndFlag = false;
			springParameter.stiffness = 3.0f;
		}
	}

	//バネカメラ
	Vector3 stretch = (position - restPosition);
	Vector3 force = -springParameter.stiffness * stretch;
	Vector3 acceleration = force / springParameter.mass;
	velocity =springParameter.friction * (velocity + acceleration);
	position += velocity;



	parameter.mat = Matrix4::Translate(position);
	Camera::GetInstance().Position.Set(position);
	Camera::GetInstance().Target.Set(playerMat.GetPosition());
	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Up.Set(Vector3(0, 1, 0));
	Camera::GetInstance().SetViewAngle(fov);
	Camera::GetInstance().Update();
}
void MonhanCameraActor::Draw() const
{
	//DrawFormatString(0, 128, GetColor(0, 0, 0), "camerPosition   %f %f %f", parameter.mat.GetPosition().x, parameter.mat.GetPosition().y, parameter.mat.GetPosition().z);
	//DrawFormatString(0, 400, GetColor(0, 0, 0), "セーブ距離   %f", dashCameraDistance);
	//DrawFormatString(0, 464, GetColor(0, 0, 0), "実際距離   %f", Vector3::Distance(playerMat.GetPosition(), cameraMovePos));
	//DrawFormatString(0, 256, GetColor(0, 0, 0), "rotateup   %f", rotateUp);
	DrawFormatString(0, 356, GetColor(0, 0, 0), "視野角   %f",fov);
	//DrawSphere3D(Vector3::ToVECTOR(parameter.mat.GetFront()*20+parameter.mat.GetPosition()), 5.0f, 1, GetColor(255, 255, 255), 1, true);

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
	rotateLeft = -45;
	return Vector3(0, 0, 1) *150 * Matrix4::RotateX(rotateLeft) * Matrix4::RotateY(rotateUp) +
		playerMat.GetPosition() + cameraUpMove;
}
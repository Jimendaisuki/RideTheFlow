#include "SpringCameraActor.h"
#include "Collision.h"
#include "../world/IWorld.h"
#include "../camera/Camera.h"
#include "../input/Keyboard.h"
#include "../graphic/TextDraw.h"
#include "../time/Time.h"
#include <string>
#include "../math/Math.h"
const Vector3 cameraUpMove = Vector3(0, 30, 0);
const float rotateSpeed = 250.0f;

SpringCameraActor::SpringCameraActor(IWorld& world) :Actor(world),
velocity(Vector3::Zero),
restPosition(Vector3::Zero),
stiffness(0.2f),
friction(0.5f),
mass(2.0f)

{
	parameter.isDead = false;
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	position = playerMat.GetPosition();
	restPosition = position;
	rotateUp = 0;
	rotateLeft = 0;


	rotateVelocity = Vector3::Zero;
}
SpringCameraActor::~SpringCameraActor()
{

}
void SpringCameraActor::Update()
{
	world.EachActor(ACTOR_ID::PLAYER_ACTOR, [&](const Actor& other){
		playerMat = other.GetParameter().mat;
	});
	//restPosition = playerMat.GetPosition();
	//// バネの伸び具合を計算
	//Vector3 stretch = (position - restPosition);
	//// バネの力を計算
	//Vector3 force = -stiffness * stretch;
	//// 加速度を追加
	//Vector3 acceleration = force / mass;
	//// 移動速度を計算
	//velocity = friction * (velocity + acceleration);
	//// 座標の更新
	//position += velocity;

	//point = playerMat.GetPosition();
	//Camera::GetInstance().Position.Set(position + playerMat.GetFront().Normalized() * 100.0f + playerMat.GetUp().Normalized() * 60.0f);
	//Camera::GetInstance().Target.Set(point);
	//Camera::GetInstance().Update();

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::UP))
		velocity.y += 5.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::DOWN))
		velocity.y -= 5.0f * Time::DeltaTime;

	Math::Clamp(velocity.y, -5.0f, 5.0f);



	//if (Keyboard::GetInstance().KeyStateDown(KEYCODE::UP))
		//rotateLeft += rotateSpeed * Time::DeltaTime;
	//if (Keyboard::GetInstance().KeyStateDown(KEYCODE::DOWN))
	//	rotateLeft -= rotateSpeed * Time::DeltaTime;
	//if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT))
	//	rotateUp += rotateSpeed * Time::DeltaTime;
	//if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT))
	//	rotateUp -= rotateSpeed * Time::DeltaTime;

	//rotateLeft = Math::Clamp(rotateLeft, -70.0f, 70.0f);

	position = Vector3(0, 0, 1) * 250.0f * Matrix4::RotateX(rotateLeft) * Matrix4::RotateY(rotateUp) +
		playerMat.GetPosition() + cameraUpMove;

	parameter.mat =
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);

	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Position.Set(position);
	Camera::GetInstance().Target.Set(playerMat.GetPosition());
	Camera::GetInstance().Up.Set(Vector3(0, 1, 0));
	Camera::GetInstance().Update();
}
void SpringCameraActor::Draw() const
{
	//TextDraw::GetInstance().Draw(Point(0,16), target.GetScale());
}
void SpringCameraActor::OnCollide(Actor& other, CollisionParameter colpara)
{

}
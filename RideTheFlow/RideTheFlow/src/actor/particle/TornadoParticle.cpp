#include "TornadoParticle.h"
#include "../../time/Time.h"
#include "../../math/Math.h"
#include "../../game/Random.h"
#include "../../camera/Camera.h"

TornadoParticle::TornadoParticle(std::weak_ptr<Tornado> tornade_, float radius)
:
tornade(tornade_),
tornadePos(tornade._Get()->GetParameter().mat.GetPosition()),
tornadeMove(Vector3::Zero),
tornadeRadius(Random::GetInstance().Range(radius, radius + 10.0f)),
tornadeAddRadius(Random::GetInstance().Range(10.0f, 20.0f)),
tornadeSpeed(700.0f),
tornadeDegree(Random::GetInstance().Range(1.0f, 360.0f)),
risingSpeed(Random::GetInstance().Range(80.0f, 90.0f)),
risingAddSpeed(Random::GetInstance().Range(0, 2)),
tornadeAddPosition(Vector3::Zero),
position(tornade_._Get()->GetParameter().mat.GetPosition()),
up(Vector3::Zero),
front(Vector3::Zero),
left(Vector3::Zero),
rotmat(Matrix4::Identity),
frame(Random::GetInstance().Range(1, 2))
{
	lifeParam.lifeTime = 0.0f;
	lifeParam.lifeTimeLimit = Random::GetInstance().Range(20.0f, 25.0f);
	lifeParam.isDead = false;

	moveParam.pos = tornadePos;

	drawParam.drawID = MODEL_ID::TORNADOPOLY_MODEL;
	//drawParam.drawID = MODEL_ID::TORNADOPOLY_MODEL;
	drawParam.size = 30.0f;
	drawParam.alpha = 0.8f;
}

void TornadoParticle::OnUpdate()
{
	//竜巻の動きと座標を取得
	Vector3 pos = tornade._Get()->GetParameter().mat.GetPosition();
	tornadeMove = pos - tornadePos;
	tornadePos = pos;

	//タイマー増加
	tornadeDegree += tornadeSpeed * Time::DeltaTime;
	risingSpeed += risingAddSpeed * Time::DeltaTime;
	tornadeRadius += tornadeAddRadius * Time::DeltaTime;

	//回転の座標を加える前の座標
	position += tornadeMove;
	position.y += risingSpeed * Time::DeltaTime;

	//回転の座標
	tornadeAddPosition = Vector3(
		Math::Cos(tornadeDegree) * tornadeRadius,
		0.0f,
		Math::Sin(tornadeDegree) * tornadeRadius);

	//セルフビルボード計算
	up = Vector3::Normalize(Camera::GetInstance().Up.Get());
	front = Vector3::Normalize(Camera::GetInstance().Target.Get() - Camera::GetInstance().Position.Get());
	left = Vector3::Cross(up, front);

	//最終的な計算結果
	rotmat.SetFront(front);
	rotmat.SetUp(up);
	rotmat.SetLeft(left);
	moveParam.pos = position + tornadeAddPosition;
}

void TornadoParticle::Draw() const
{
	//Model::GetInstance().Draw2DBlend(drawParam.drawID, moveParam.pos, frame, drawParam.size, Vector2(50.0f, 0.0f),0.0f,
	//	false, drawParam.blendMode, drawParam.alpha);

	Model::GetInstance().Draw(drawParam.drawID, moveParam.pos, drawParam.alpha, rotmat.GetRotateDegree(), drawParam.size, true);
}
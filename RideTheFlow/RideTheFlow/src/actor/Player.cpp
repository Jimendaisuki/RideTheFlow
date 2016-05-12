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
#include "../game/Random.h"

//ボーンの数
const int boneCount = 33;
//波の周波
const float waveCount = 0.52f;
//モデルのスケール
const Vector3 scale = Vector3(0.01f);

const Vector3 cameraUpMove = Vector3(0, 30, 0);

/*************************************************リンク君が変えるところ*************************************************/
//testコード、動きの切り替えtrueの時強弱なし
bool changeMotion = true;

//changeMotionがtrueの時に反映される
//くねくねの上下の回転速度
const float leftAngleSpeed = 270.0f;
//くねくねの上下の回転の振れ幅
const float leftMoveRange = 10.0f;
//くねくねの左右の回転速度
const float upAngleSpeed = 225.0f;
//くねくねの左右の回転の振れ幅
const float upMoveRange = 10.0f;

//changeMotionがfalseの時に反映される
//くねくねのLeft軸回転速度
const float angleSpeed = 270.0f;

//スピード
const float speed = 100.0f;
//回転スピード
const float rotateSpeed = 150.0f;
//回転時のAngle
const float ryuuRotateAngle = 2.5f;

//タックルのアニメーションのスピード
const float tackleAnimSpeed = 20.0f;
//タックルの入り出の時のブレンドスピード(上記のスピード÷１０位が目安っぽい(?))
const float tackleAnimBlendSpeed = 2.0f;
//タックルのアニメーションのどのフレームであたり判定を出すか
const float tackleAnimAttackTiming = 37.0f;

//待機モーションへのブレンド率
const float waitAnimBlendSpeed = 2.0f;

//加速できる時間
const float dashMaxTime = 5.0f;
//加速する際の加速度
const float dashAccele = 1.0f;
//加速時の最大スピード
const float dashMaxSpeed = 1.5f;
//加速ゲージの回復速度
const float dashHealSpeed = 2.0f;

//ノーマル時or停止時からの加速度
const float normalSpeedAccele = 1.0f;
/************************************************************************************************************************/

Player::Player(IWorld& world) :
Actor(world),
position(Vector3(0,0,0)),
tornadeTimer(0.0f)
{
	//paramterの初期化
	parameter.isDead = false;
	parameter.radius = 3.0f;
	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);

	//くねくねさせる為のangle２つ
	upAngle = 0;
	leftAngle = 0;
	
	//デバックコード(デバック表示されているもののボーンのナンバー)
	boneSelect = 0;

	//カメラの上下左右のrotate
	rotateUp = 0;
	rotateLeft = 0;

	//ダメージを受けた際のパラメーターの初期化
	damageFlag = false;
	damageCount = 0;

	//タックルのパラメーターの初期化
	tp.tackleFlag = false;
	tp.tackleEndFlag = false;
	tp.tackleRotate = Matrix4::Identity;
	tp.tackleAngle = 0;
	tp.tackleT = Vector3(0, 0, -1);

	//左スティック(WASD)が入力されたどうか判断する
	leftStickMove = false;

	//回転のディレイをかけるために用いる前フレームのベクトル(y = 0.01fの理由はぴったりだとバグを生じるから)
	beforeVec = Vector3(0.0f,0.01f,-1.0f);

	//モデルハンドルを取得する(アニメーションのために)
	modelHandle = Model::GetInstance().GetHandle(MODEL_ID::TEST_MODEL);
	//アニメーションの再生タイム
	animTime = 0;
	//アニメーションのブレンド
	animBlend = 0;
	//待機アニメーションをアタッチしたかどうか判断
	waitAnimSet = false;

	//初期ボーン
	vertexVec = new Vector3[boneCount];
	//posStorageに何もないときのボーンの方向
	nonPosStorageVec = Vector3(0, 0, 1);
	for (int i = 0; i < boneCount; i++){
		//ボーンの状態をリセット
		MV1ResetFrameUserLocalMatrix(modelHandle, i + 1);
		//初期位置ボーンの位置を取得
		vertexVec[i] = Matrix4::ToMatrix4(
			MV1GetFrameLocalWorldMatrix(modelHandle, i + 1)).GetPosition() *
			Matrix4::Scale(scale);
	}

	//加速ゲージの回復中
	dashHealFlag = false;
	//加速用のスピード
	dashSpeed = 1.0f;
	//加速できる時間
	dashTime = 0.0f;
}
Player::~Player(){
	SAFE_DELETE_ARRAY(vertexVec);
	posStorage.clear();
}


void Player::Update(){
	//左スティック(WASD)が入力されているか調べるために毎度初期化
	leftStickMove = false;
	//操作
	Vector3 vec = Vector3::Zero;

	auto input = DINPUT_JOYSTATE();

	// 入力状態を取得
	GetJoypadDirectInputState(DX_INPUT_PAD1, &input);
	Vector3 rightStick = Vector3(input.Rx, input.Ry, input.Rz).Normalized();
	Vector3 leftStick = Vector3(input.X, input.Y, input.Z).Normalized();

	bool padInputFlag = false;
	if (Vector3::Length(rightStick) > 0.01f || Vector3::Length(rightStick) > 0.01f){
		padInputFlag = true;
	}

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::UP))
		rotateLeft += rotateSpeed * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::DOWN))
		rotateLeft -= rotateSpeed * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::RIGHT))
		rotateUp += rotateSpeed * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LEFT))
		rotateUp -= rotateSpeed * Time::DeltaTime;

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A)){
		vec.x += speed * Time::DeltaTime;
		leftStickMove = true;
		if (!tp.tackleFlag){
			animBlend -= waitAnimBlendSpeed * Time::DeltaTime;
		}
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::D)){
		vec.x -= speed * Time::DeltaTime;
		leftStickMove = true;
		if (!tp.tackleFlag){
			animBlend -= waitAnimBlendSpeed * Time::DeltaTime;
		}
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::W)){
		vec.z += speed * Time::DeltaTime;
		leftStickMove = true;
		if (!tp.tackleFlag){
			animBlend -= waitAnimBlendSpeed * Time::DeltaTime;
		}
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::S)){
		vec.z -= speed * Time::DeltaTime;
		leftStickMove = true;
		if (!tp.tackleFlag){
			animBlend -= waitAnimBlendSpeed * Time::DeltaTime;
		}
	}
	
	if (padInputFlag){
		rotateLeft += rightStick.y * rotateSpeed * Time::DeltaTime;
		rotateUp += rightStick.x * rotateSpeed * Time::DeltaTime;
		vec.x += leftStick.x * speed * Time::DeltaTime;
		vec.z += leftStick.y * speed * Time::DeltaTime;
	}
	rotateLeft = Math::Clamp(rotateLeft, -70.0f, 70.0f);

	Vector3 cameraPos = Camera::GetInstance().Position.Get();
	Vector3 cameraFront = (position - (cameraPos - cameraUpMove)).Normalized();
	Vector3 cameraLeft = Vector3::Cross(cameraFront, Vector3(0, 1, 0)).Normalized();
	vec.Normalize();
	Vector3 trueVec = (cameraFront * vec.z + cameraLeft * vec.x).Normalized();

	if (!leftStickMove){
		if (!tp.tackleFlag){
			//animBlend += waitAnimBlendSpeed * Time::DeltaTime;
		}
	}
	else{
		if (!tp.tackleFlag){
			tp.tackleT = trueVec;
		}
	}
	
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LCTRL) && leftStickMove && !tp.tackleFlag){
		tp.tackleFlag = true;
		animIndex = MV1AttachAnim(modelHandle, 0, -1, FALSE);
		totalTime = MV1GetAttachAnimTotalTime(modelHandle, animIndex);
		tp.tackleT = trueVec;
		animTime = 0.0f;
	}

	if (dashTime >= dashMaxTime){
		dashHealFlag = true;
	}
	if (dashTime <= 0.0f){
		dashHealFlag = false;
	}
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::LSHIFT) && leftStickMove){
		if (dashHealFlag){
			dashPosStorage.clear();
			dashSpeed -= dashAccele * Time::DeltaTime;
			dashTime -= dashHealSpeed * Time::DeltaTime;
		}
		else{
			dashPosStorage.push_back(position);
			dashTime += Time::DeltaTime;
			dashSpeed += dashAccele * Time::DeltaTime;
		}
	}
	else{
		dashPosStorage.clear();
		dashSpeed -= dashAccele * Time::DeltaTime;
		dashTime -= dashHealSpeed * Time::DeltaTime;
	}

	dashSpeed = Math::Clamp(dashSpeed, 1.0f, dashMaxSpeed);
	dashTime = Math::Clamp(dashTime, 0.0f, dashMaxTime);

	if (!tp.tackleFlag){
		if (!waitAnimSet)
		animIndex = MV1AttachAnim(modelHandle, 1, -1, FALSE);
		animTime = MV1GetAttachAnimTotalTime(modelHandle, animIndex);
		waitAnimSet = true;
		Vector3 cross = Vector3::Cross(beforeVec.Normalized(), trueVec.Normalized()).Normalized();

		float crossAngle = Vector3::Inner(trueVec, beforeVec);
		if (crossAngle >= 0)crossAngle = ryuuRotateAngle;
		else crossAngle = -ryuuRotateAngle;

		position += (Vector3::Length(trueVec) * 
			beforeVec *
			Quaternion::RotateAxis(cross, crossAngle)).Normalized() * speed * dashSpeed * Time::DeltaTime;
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
			beforeVec = (beforeVec * Quaternion::RotateAxis(cross, crossAngle)).Normalized();
		}
	}
	else{
		// 再生時間を進める
		animTime += tackleAnimSpeed * Time::DeltaTime;

		if (totalTime - animTime < tackleAnimSpeed * Time::DeltaTime * 60.0f && !tp.tackleEndFlag){
			tp.tackleEndFlag = true;
			posStorage.clear();
			nonPosStorageVec = -tp.tackleT;
			beforeVec = tp.tackleT;
		}

		if (tp.tackleEndFlag)animBlend -= tackleAnimBlendSpeed * Time::DeltaTime;
		else animBlend += tackleAnimBlendSpeed * Time::DeltaTime;

		// 再生時間がアニメーションの総再生時間に達したら再生時間を０に戻す
		if (animTime >= totalTime - 10.0f)
		{
			animTime = 0.0f;
			tp.tackleFlag = false;
			tp.tackleEndFlag = false;
			animBlend = 0.0f;
			waitAnimSet = false;
		}
		if (animTime > tackleAnimAttackTiming){
			world.SetCollideSelect(shared_from_this(), ACTOR_ID::TORNADO_ACTOR, COL_ID::PLAYER_TORNADO_COL);
			parameter.height = tp.tackleT.Normalized() * 30.0f;
		}
	}

	animBlend = Math::Clamp(animBlend, 0.0f, 1.0f);

	//ボーンの情報切り替え
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::X))
		boneSelect++;
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::Z))
		boneSelect--;

	////ボーンの情報切り替え
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
	//マトリックスの再計算
	parameter.mat =
		Matrix4::Scale(scale) *
		playerRot * 
		Matrix4::Translate(position);

	//くねくねの角度のスピード
	if (changeMotion){
		upAngle -= leftAngleSpeed * Random::GetInstance().Range(0.5f,1.5f) * dashSpeed * Time::DeltaTime;
		leftAngle -= upAngleSpeed * Random::GetInstance().Range(0.5f,1.5f) * dashSpeed * Time::DeltaTime;
	}
	else{
		upAngle -=
			angleSpeed * dashSpeed * Time::DeltaTime * Math::Cos(Math::Degree((Math::Sin(upAngle) + 1) / 2.0f));
		leftAngle -=
			angleSpeed * dashSpeed * Time::DeltaTime * Math::Cos(Math::Degree((Math::Sin(upAngle) + 1) / 2.0f));
	}

	upAngle = Math::InfinityClamp(upAngle, 0.0f, 360.0f);
	leftAngle = Math::InfinityClamp(leftAngle, 0.0f, 360.0f);

	Camera::GetInstance().SetRange(0.1f, 9999.0f);
	Camera::GetInstance().Position.Set(
		Vector3(0,0,1) * 250.0f * Matrix4::RotateX(rotateLeft) * Matrix4::RotateY(rotateUp) +  
		parameter.mat.GetPosition() + cameraUpMove);
	Camera::GetInstance().Target.Set(parameter.mat.GetPosition());
	Camera::GetInstance().Up.Set(Vector3(0,1,0));
	Camera::GetInstance().Update();
	
	Vector3* copyVertexVec = new Vector3[boneCount];

	for (int i = 0; i < boneCount; i++){
		copyVertexVec[i] = vertexVec[i];
	}

	int storageCount = 0;
	Vector3 startPos = position;
	vertexVec[0] = position;

	int deletePosStorageCount = posStorage.size();
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
		vertexVec[storageCount + 1] = startPos + nonPosStorageVec.Normalized() * Vector3::Length(copyVertexVec[storageCount] - copyVertexVec[storageCount + 1]);
		startPos = vertexVec[storageCount + 1];
		storageCount++;
	}


	int defaltSize = posStorage.size();
	for (int i = 0; i < deletePosStorageCount; i++)
	posStorage.erase(posStorage.begin());

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
	//骨の数だけ用意する
	Vector3* drawVertexVec = new Vector3[boneCount];
	Matrix4* drawMatrixVec = new Matrix4[boneCount];
	Matrix4* localDrawMatrixVec = new Matrix4[boneCount];
	Matrix4* localAnimDrawMatrixVec = new Matrix4[boneCount];

	//初期化
	for (int i = 0; i < boneCount; i++){
		drawVertexVec[i] = vertexVec[i];
		drawMatrixVec[i] = parameter.mat;
	}

	//先頭を原点に移動
	drawVertexVec[0] = vertexVec[0];

	////先頭の高さを求める為最頂点の位置までの計算を行う
	//for (int count = 1; count <= (boneCount / (int)(2.0f / waveCount)); count++){
	//	Vector3 boneFront = (vertexVec[count] - vertexVec[count - 1]).Normalized();
	//	Vector3 boneUp = Vector3(0, 1, 0);
	//	Vector3 boneLeft = Vector3::Cross(boneFront, boneUp).Normalized();
	//	boneUp = Vector3::Cross(boneLeft, boneFront).Normalized();
	//
	//	Matrix4 drawMat = 
	//		//ボーンの長さ求めて動かす
	//		Matrix4::Translate(vertexVec[count] - vertexVec[count - 1]) *
	//		//Left軸、Front軸基準に回転
	//		Quaternion::RotateAxis(boneLeft, Math::Sin(upAngle + (count * 360.0f / (float)(boneCount * waveCount))) * leftMoveRange) *
	//		Quaternion::RotateAxis(boneUp, Math::Sin(leftAngle + (count * 360.0f / (float)(boneCount * waveCount))) * upMoveRange) *
	//		Matrix4::Translate(drawVertexVec[count - 1]);
	//	drawVertexVec[count] = drawMat.GetPosition();
	//}
	//
	//先頭の高さを代入
	//drawVertexVec[0] = -drawVertexVec[boneCount / (int)(2.0f / waveCount)];

	//マトリックスも再計算
	drawMatrixVec[0] =
		Matrix4::Scale(scale) *
		Matrix4::Translate(drawVertexVec[0]);

	//先頭の高さを設定した状態で再計算
	for (int count = 1; count < boneCount; count++){
		Vector3 boneFront = (vertexVec[count] - vertexVec[count - 1]).Normalized();
		Vector3 boneUp = Vector3(0, 1, 0);
		Vector3 boneLeft = Vector3::Cross(boneFront, boneUp).Normalized();
		boneUp = Vector3::Cross(boneLeft, boneFront).Normalized();

		Matrix4 drawMat =
			Matrix4::Translate(vertexVec[count] - vertexVec[count - 1]) *
			Quaternion::RotateAxis(boneLeft, Math::Sin(upAngle + (count * 360.0f / (float)(boneCount * waveCount))) * leftMoveRange) *
			Quaternion::RotateAxis(boneUp, Math::Sin(leftAngle + (count * 360.0f / (float)(boneCount * waveCount))) * upMoveRange) *
			Matrix4::Translate(drawVertexVec[count - 1]);

		Matrix4 rotateMat;
		drawVertexVec[count] = drawMat.GetPosition();
		rotateMat = Matrix4::Identity;
		Vector3 front = (drawVertexVec[count] - drawVertexVec[count - 1]).Normalized();
		Vector3 up = Vector3(0, 1, 0).Normalized();
		Vector3 left = Vector3::Cross(up, front).Normalized();
		up = Vector3::Cross(front, left).Normalized();
		front = Vector3::Cross(left, up).Normalized();
		rotateMat.SetFront(front);
		rotateMat.SetUp(up);
		rotateMat.SetLeft(left);

		drawMatrixVec[count] =
			Matrix4::Scale(scale) *
			rotateMat *
			Matrix4::Translate(drawVertexVec[count]);
	}

	//相対座標に変換しセット
	for (int count = 0; count < boneCount; count++){
		localDrawMatrixVec[count] = drawMatrixVec[count];

		Matrix4 beforeInvMat = Matrix4::Identity;
		//親の逆行列をかけていく
		for (int count2 = 0; count2 < count; count2++){
			beforeInvMat *= Matrix4::Inverse(localDrawMatrixVec[count2]);
		}
		localDrawMatrixVec[count] = (drawMatrixVec[count] * beforeInvMat);
		localAnimDrawMatrixVec[count] = Matrix4::ToMatrix4(MV1GetAttachAnimFrameLocalMatrix(modelHandle, animIndex, count + 1));
	}

	Vector3 animSubVec = position - localAnimDrawMatrixVec[0].GetPosition();
	Matrix4 animSubRotate = Matrix4::Identity;
	animSubRotate.SetFront(localAnimDrawMatrixVec[1].GetFront().Normalized());
	animSubRotate.SetUp(localAnimDrawMatrixVec[1].GetUp().Normalized());
	animSubRotate.SetLeft(localAnimDrawMatrixVec[1].GetLeft().Normalized());

	Vector3 front = -tp.tackleT.Normalized();
	Vector3 up = Vector3(0, 1, 0).Normalized();
	Vector3 left = Vector3::Cross(up, front).Normalized();
	up = Vector3::Cross(front, left).Normalized();
	front = Vector3::Cross(left, up).Normalized();
	Matrix4 rotateY = Matrix4::Identity;	
	rotateY.SetFront(front);
	rotateY.SetUp(up);
	rotateY.SetLeft(left);

	localAnimDrawMatrixVec[0] =
		Matrix4::Scale(scale) *
		Matrix4::Translate(position);

	localAnimDrawMatrixVec[1] =
		Matrix4::Scale(localAnimDrawMatrixVec[1].GetScale())*
		animSubRotate *
		rotateY *
		Matrix4::Translate(localAnimDrawMatrixVec[1].GetPosition());

	// 再生時間をセットする
	MV1SetAttachAnimTime(modelHandle, animIndex, animTime);

	for (int count = 0; count < boneCount; count++){
		MV1SetFrameUserLocalMatrix(modelHandle, count + 1,
			Matrix4::ToMATRIX(
			Matrix4::Slerp(
			localDrawMatrixVec[count]
			,localAnimDrawMatrixVec[count], animBlend)
			));
	}

	Model::GetInstance().Draw(MODEL_ID::TEST_MODEL, Vector3::Zero, 1.0f);
	//if (damageFlag){
	//	DrawSphere3D(parameter.mat.GetPosition(), 10, 32, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);
	//}

	//if (tackleFlag)
	//DrawCapsule3D(position, position + parameter.height, parameter.radius, 8, GetColor(0, 255, 0), GetColor(255, 255, 255), TRUE);
	
	ParameterDraw();

	if (dashPosStorage.size() > 1)
	for (int count = 0; count < dashPosStorage.size() - 1; count++){
		int Color = GetColor(0, 0, 255);
		DrawLine3D(dashPosStorage[count],dashPosStorage[count + 1], Color);
	}

	SAFE_DELETE_ARRAY(drawVertexVec);
	SAFE_DELETE_ARRAY(drawMatrixVec);
	SAFE_DELETE_ARRAY(localDrawMatrixVec);
	SAFE_DELETE_ARRAY(localAnimDrawMatrixVec);
}


void Player::ParameterDraw() const{

	int ModelHandle = modelHandle;
	// フレーム名の描画
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Name         %s", MV1GetFrameName(ModelHandle, boneSelect));

	// 親フレーム名の描画
	int Parent = MV1GetFrameParent(ModelHandle, boneSelect);
	if (Parent == -2)
	{
		DrawFormatString(0, 16, GetColor(255, 255, 255), "Parent Name  None");
	}
	else
	{
		DrawFormatString(0, 16, GetColor(255, 255, 255), "Parent Name  %s", MV1GetFrameName(ModelHandle, Parent));
	}

	// 子フレームの数を描画
	DrawFormatString(0, 32, GetColor(255, 255, 255), "Child Num    %d", MV1GetFrameChildNum(ModelHandle, boneSelect));

	// フレームのワールド座標の描画
	VECTOR Position = tp.tackleT;// MV1GetFramePosition(ModelHandle, boneSelect);
	DrawFormatString(0, 48, GetColor(255, 255, 255), "Position     x:%f y:%f z:%f", Position.x, Position.y, Position.z);

	// 変換行列を描画する
	MATRIX Matrix =  MV1GetFrameLocalMatrix(ModelHandle, boneSelect);
	DrawFormatString(0, 64, GetColor(255, 255, 255), "   Matrix    %f %f %f %f", Matrix.m[0][0], Matrix.m[0][1], Matrix.m[0][2], Matrix.m[0][3]);
	DrawFormatString(0, 80, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[1][0], Matrix.m[1][1], Matrix.m[1][2], Matrix.m[1][3]);
	DrawFormatString(0, 96, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[2][0], Matrix.m[2][1], Matrix.m[2][2], Matrix.m[2][3]);
	DrawFormatString(0, 112, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[3][0], Matrix.m[3][1], Matrix.m[3][2], Matrix.m[3][3]);

	// フレームのローカル座標からワールド座標に変換する行列を描画する
	Matrix = MV1GetFrameLocalWorldMatrix(ModelHandle, boneSelect);
	DrawFormatString(0, 128, GetColor(255, 255, 255), "LW Matrix    %f %f %f %f", Matrix.m[0][0], Matrix.m[0][1], Matrix.m[0][2], Matrix.m[0][3]);
	DrawFormatString(0, 144, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[1][0], Matrix.m[1][1], Matrix.m[1][2], Matrix.m[1][3]);
	DrawFormatString(0, 160, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[2][0], Matrix.m[2][1], Matrix.m[2][2], Matrix.m[2][3]);
	DrawFormatString(0, 176, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[3][0], Matrix.m[3][1], Matrix.m[3][2], Matrix.m[3][3]);

	// フレームの表示状態を描画
	DrawFormatString(0, 192, GetColor(255, 255, 255), "Visible      %d", MV1GetFrameVisible(ModelHandle, boneSelect));

	// フレームに半透明要素があるかどうかを描画
	DrawFormatString(0, 208, GetColor(255, 255, 255), "Semi Trans   %d", MV1GetFrameSemiTransState(ModelHandle, boneSelect));

	// フレームに含まれるメッシュの数を描画
	DrawFormatString(0, 224, GetColor(255, 255, 255), "Mesh Num     %d", MV1GetFrameMeshNum(ModelHandle, boneSelect));

	// フレームに含まれる三角形ポリゴンの数を描画
	DrawFormatString(0, 240, GetColor(255, 255, 255), "Triangle Num %d", MV1GetFrameTriangleNum(ModelHandle, boneSelect));

	//// フレームに半透明要素があるかどうかを描画
	DrawFormatString(0, 256, GetColor(255, 255, 255), "FPS   %d", (int)(1.0f / Time::DeltaTime));

	float gageColorNum = 255.0f * ((dashMaxTime - dashTime) / dashMaxTime);
	DWORD gageColor = GetColor(255, gageColorNum, gageColorNum);
	if (dashHealFlag)gageColor = GetColor(0, 0, 255);
	//// フレームに半透明要素があるかどうかを描画
	DrawFormatString(0, 272, gageColor, "DashGage   %2.1ff/%2.1ff %s", dashTime, dashMaxTime, dashHealFlag ? "(OVERHEAT)" : "");

	DrawFormatString(0, 288, damageFlag ? GetColor(255, 0, 0) : GetColor(255,255, 255), "Status");
}
void Player::OnCollide(Actor& other, CollisionParameter colpara)
{
	if (other.GetParameter().id != ACTOR_ID::TORNADO_ACTOR && !damageFlag){
		damageFlag = true;
	}
}
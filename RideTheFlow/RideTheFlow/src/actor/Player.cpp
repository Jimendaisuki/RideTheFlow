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

//ボーンの数
const int boneCount = 33;
//波の周波
const float waveCount = 0.52f;
//モデルのスケール
const Vector3 scale = Vector3(0.01f, 0.01f, 0.01f);
//スピード
const float speed = 100.0f;

/*************************************************リンク君が変えるところ*************************************************/
//testコード、動きの切り替えtrueの時強弱なし
bool changeMotion = false;

//changeMotionがtrueの時に反映される
//くねくねのLeft軸回転速度
const float leftAngleSpeed = 270.0f;
//くねくねのUp軸回転速度
const float upAngleSpeed = 225.0f;

//changeMotionがfalseの時に反映される
//くねくねのLeft軸回転速度
const float angleSpeed = 270.0f;
/************************************************************************************************************************/

Player::Player(IWorld& world) :
Actor(world),
position(Vector3(0,0,0))
{
	parameter.isDead = false;
	parameter.radius = 3.0f;

	//PlayerActorのマトリックス
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
}
Player::~Player(){
}

float rotateY = 0;
void Player::Update(){
	//操作
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A))
		position.x -= speed * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::D))
		position.x += speed * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::W))
		position.y += speed * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::S))
		position.y -= speed * Time::DeltaTime;

	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::F))
		position.z += speed * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::R))
		position.z -= speed * Time::DeltaTime;

	//ボーンの情報切り替え
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::RIGHT))
		boneSelect++;
	if (Keyboard::GetInstance().KeyTriggerDown(KEYCODE::LEFT))
		boneSelect--;

	//ボーンの情報切り替え
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::Z))
		rotateY += 360.0f * Time::DeltaTime;
	if (Keyboard::GetInstance().KeyStateDown(KEYCODE::X))
		rotateY -= 360.0f * Time::DeltaTime;

	//マトリックスの再計算
	parameter.mat =
		Matrix4::Scale(scale) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateX(0) *
		Matrix4::RotateY(0) *
		Matrix4::Translate(position);

	//くねくねの角度のスピード
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
	Camera::GetInstance().Position.Set(parameter.mat.GetFront().Normalized() * Matrix4::RotateY(rotateY) * 150.0f + Vector3(0, 60, 0) + parameter.mat.GetPosition());
	Camera::GetInstance().Target.Set(parameter.mat.GetPosition());
	Camera::GetInstance().Up.Set(parameter.mat.GetUp());
	Camera::GetInstance().Update();
}
void Player::Draw() const{
	//骨の数だけ用意する
	Vector3*vertexVec = new Vector3[boneCount];
	Vector3* drawVertexVec = new Vector3[boneCount];
	Matrix4* drawMatrixVec = new Matrix4[boneCount];

	//初期化
	for (int i = 0; i < boneCount; i++){
		//ボーンの状態をリセット
		MV1ResetFrameUserLocalMatrix(Model::GetInstance().GetHandle(MODEL_ID::TEST_MODEL), i + 1);
		//初期位置ボーンの位置を取得
		vertexVec[i] = Matrix4::ToMatrix4(
			MV1GetFrameLocalWorldMatrix(Model::GetInstance().GetHandle(MODEL_ID::TEST_MODEL), i + 1)).GetPosition() *
			parameter.mat;
		drawVertexVec[i] = vertexVec[i];
		drawMatrixVec[i] = parameter.mat;
	}
	
	//先頭を原点に移動
	drawVertexVec[0] = Vector3(position.x, -position.y, position.z);

	//先頭の高さを求める為最頂点の位置までの計算を行う
	for (int count = 1; count <= (boneCount / (int)(2.0f / waveCount)); count++){
		Matrix4 drawMat = 
			//ボーンの長さ求めて動かす
			Matrix4::Translate(vertexVec[count] - vertexVec[count - 1]) *
			//Left軸基準に回転
			Quaternion::RotateAxis(parameter.mat.GetLeft().Normalized(), Math::Sin(upAngle + (count * 360.0f / (float)(boneCount * waveCount))) * 20.0f) *
			//Front軸基準に回転
			Quaternion::RotateAxis(parameter.mat.GetUp().Normalized(), Math::Sin(leftAngle + (count * 360.0f / (float)(boneCount * waveCount))) * 20.0f) *
			Matrix4::Translate(drawVertexVec[count - 1]);
		drawVertexVec[count] = drawMat.GetPosition();
	}

	//先頭の高さを代入
	drawVertexVec[0].y = -drawVertexVec[boneCount / (int)(2.0f / waveCount)].y;

	//移動量を引いたプレイヤーのマトリックスを作成
	Matrix4 paramMatSubTrans = parameter.mat;
	paramMatSubTrans.SetPosition(Vector3(0, 0, 0));

	//マトリックスも再計算
	drawMatrixVec[0] = paramMatSubTrans * Matrix4::Translate(drawVertexVec[0]);

	//先頭の高さを設定した状態で再計算
	for (int count = 1; count < boneCount; count++){
		Matrix4 drawMat = 
			Matrix4::Translate(vertexVec[count] - vertexVec[count - 1]) *
			Quaternion::RotateAxis(parameter.mat.GetLeft().Normalized(), Math::Sin(upAngle + (count * 360.0f / (float)(boneCount * waveCount))) * 20.0f)*
			Quaternion::RotateAxis(parameter.mat.GetUp().Normalized(), Math::Sin(leftAngle + (count * 360.0f / (float)(boneCount * waveCount))) * 20.0f) *
			Matrix4::Translate(drawVertexVec[count - 1]);

		drawVertexVec[count] = drawMat.GetPosition();

		drawMatrixVec[count] =
			paramMatSubTrans *
			Quaternion::RotateAxis(parameter.mat.GetLeft().Normalized(), Math::Sin(upAngle + (count * 360.0f / (float)(boneCount * waveCount))) * 20.0f)*
			Quaternion::RotateAxis(parameter.mat.GetUp().Normalized(), Math::Sin(leftAngle + (count * 360.0f / (float)(boneCount * waveCount))) * 20.0f) *
			Matrix4::Translate(drawVertexVec[count]);
	}

	SAFE_DELETE_ARRAY(vertexVec);
	SAFE_DELETE_ARRAY(drawVertexVec);

	//相対座標に変換しセット
	for (int count = 0; count < boneCount; count++){
		Matrix4 beforeInvMat = Matrix4::Identity;
		//親の逆行列をかけていく
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

	SAFE_DELETE_ARRAY(drawMatrixVec);

	Model::GetInstance().Draw(MODEL_ID::TEST_MODEL , Vector3::Zero, 1.0f);
	
	ParameterDraw();
	//for (int count = 1; count < boneCount - 1; count++){
	//	int Color = GetColor(255, 0, 0);
	//	if (count % 2 == 0)Color = GetColor(0, 255, 0);
	//	DrawLine3D(Vector3::ToVECTOR(drawMatrixVec[count].GetPosition()), Vector3::ToVECTOR(drawMatrixVec[count + 1].GetPosition()), Color);
	//}
	//
	//DrawSphere3D(Vector3::ToVECTOR(drawMatrixVec[boneSelect].GetPosition()), 5.0f, 32, GetColor(255,0,0), GetColor(255, 0,0),FALSE);	
}


void Player::ParameterDraw() const{

	int ModelHandle = Model::GetInstance().GetHandle(MODEL_ID::TEST_MODEL);
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
	VECTOR Position = MV1GetFramePosition(ModelHandle, boneSelect);
	DrawFormatString(0, 48, GetColor(255, 255, 255), "Position     x:%f y:%f z:%f", Position.x, Position.y, Position.z);

	// 変換行列を描画する
	MATRIX Matrix = MV1GetFrameLocalMatrix(ModelHandle, boneSelect);
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

	//// フレームに半透明要素があるかどうかを描画
	DrawFormatString(0, 272, GetColor(255, 255, 255), "speedRegulation   %f", (Math::Cos(speedRegulation) + 1.0f) / 2.0f);
}
void Player::OnCollide(Actor& other, CollisionParameter colpara)
{
	//position = Vector3(0, 0, 0);
}
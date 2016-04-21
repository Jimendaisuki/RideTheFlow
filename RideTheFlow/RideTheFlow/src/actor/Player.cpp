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

const float Range = 3.0f;
const int ropeCount = 33;
const float updownRange = 1.0f;
const float waveCount = 0.5f;
const float scale = 0.01f;

Player::Player(IWorld& world) :
Actor(world),
position(Vector3(0,0,0)),
otherVertex(Vector3(0,0,0)),
vertexVec(new Vector3[ropeCount]),
drawVertexVec(new Vector3[ropeCount]),
modelVertexVec(new Vector3[ropeCount]),
drawMatrixVec(new Matrix4[ropeCount])
{
	parameter.isDead = false;
	parameter.radius = 3.0f;
	vertexVec[0] = position;
	for (int count = 0; count < ropeCount; count++){
		MATRIX mmm = MV1GetFrameLocalWorldMatrix(Model::GetInstance().GetHandle(MODEL_ID::TEST_MODEL), count + 1);
		modelVertexVec[count] = Vector3(mmm.m[3][0], mmm.m[3][1], mmm.m[3][2]) *
			Matrix4::Scale(Vector3(scale, scale, scale)) *
			Matrix4::RotateZ(0) *
			Matrix4::RotateX(0) *
			Matrix4::RotateY(90) *
			Matrix4::Translate(position);
	;
		vertexVec[count] = modelVertexVec[count];// Vector3(count * Range - 60.0f, 0.0f, 0.0f);
		drawVertexVec[count] = vertexVec[count];
		drawMatrixVec[count] = Matrix4::Identity;
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

	//if (Keyboard::GetInstance().KeyStateDown(KEYCODE::A) || Keyboard::GetInstance().KeyStateDown(KEYCODE::S)){
	//	angle += 360.0f * Time::DeltaTime;
	//	position.y += updownRange * Math::Sin(angle);
	//}

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

	//drawVertexVec[0].y = Math::Sin(-angle) * 20.0f;// *(float)ropeCount / 2.0f / 20.0f;
	drawVertexVec[0].y = 0;
	for (int count = 1; count <= (ropeCount / (int)(2.0f / waveCount)); count++){
		Matrix4 drawMat = Matrix4::Translate(Vector3(Vector3::Length(vertexVec[count] - vertexVec[count - 1]), 0.0f, 0.0f)) *
			Matrix4::RotateZ(Math::Sin(angle + (count * 360.0f / (float)(ropeCount * waveCount))) * 20.0f) *
			Matrix4::Translate(drawVertexVec[count - 1]);
		drawVertexVec[count] = drawMat.GetPosition();
		//Matrix4::RotateZ(Math::Sin(angle + count * (360.0f / (float)ropeCount)) * 180.0f);
	}
	drawVertexVec[0].y = -drawVertexVec[ropeCount / (int)(2.0f / waveCount)].y;
	drawMatrixVec[0] =
		Matrix4::Scale(Vector3(scale, scale, scale)) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateY(90) *
		Matrix4::RotateZ(0)  *
		Matrix4::Translate(drawVertexVec[0])
		;

	for (int count = 1; count < ropeCount; count++){
		Matrix4 drawMat = Matrix4::Translate(Vector3(Vector3::Length(vertexVec[count] - vertexVec[count - 1]), 0.0f, 0.0f)) *
			Matrix4::RotateZ(Math::Sin(angle + (count * 360.0f / (float)(ropeCount * waveCount))) * 20.0f) *
			Matrix4::Translate(drawVertexVec[count - 1]);
		drawVertexVec[count] = drawMat.GetPosition();
		drawMatrixVec[count] =
			Matrix4::Scale(Vector3(scale, scale, scale)) *
			Matrix4::RotateZ(0) *
			Matrix4::RotateY(90) *
			Matrix4::RotateZ(Math::Sin(angle + (count * 360.0f / (float)(ropeCount * waveCount))) * 20.0f)  *
			Matrix4::Translate(drawVertexVec[count] + parameter.mat.GetPosition())
			;
		//Matrix4::RotateZ(Math::Sin(angle + count * (360.0f / (float)ropeCount)) * 180.0f);
	}

	Matrix4 drawInv = 
		Matrix4::Inverse(
		Matrix4::Scale(Vector3(scale, scale, scale)) *
		Matrix4::RotateZ(0) *
		Matrix4::RotateY(90) *
		Matrix4::RotateZ(0) *
		Matrix4::Translate(parameter.mat.GetPosition()));

	for (int count = 0; count < ropeCount; count++){
		Matrix4 beforeInvMat = Matrix4::Identity;
		for (int count2 = 0; count2 < count; count2++){
			beforeInvMat *= Matrix4::Inverse(Matrix4::ToMatrix4(MV1GetFrameLocalMatrix(Model::GetInstance().GetHandle(MODEL_ID::TEST_MODEL),count2 + 1)));
		}
		MV1ResetFrameUserLocalMatrix(Model::GetInstance().GetHandle(MODEL_ID::TEST_MODEL), count + 1);
		MV1SetFrameUserLocalMatrix(Model::GetInstance().GetHandle(MODEL_ID::TEST_MODEL), count + 1,
			Matrix4::ToMATRIX(
			drawMatrixVec[count] * 
			//drawInv //*
			beforeInvMat
			));
	}

	angle -= 180.0f * Time::DeltaTime;
	
	//vertexVec[0] = position;
	//for (int count = 0; count < ropeCount - 1; count++){
	//	float d = Range - Vector3::Distance(vertexVec[count], vertexVec[count + 1]);
	//	Vector3 otherToPosVec = Vector3::Normalize(vertexVec[count] - vertexVec[count + 1]);
	//	vertexVec[count + 1] -= otherToPosVec * d;
	//}
}
void Player::Draw() const{
	ParameterDraw();
	// ２番目のフレームに下に動くのローカル行列をセットする
	Model::GetInstance().Draw(MODEL_ID::TEST_MODEL , Vector3::Zero, 1.0f);// , Vector3(0, 90, 0));// , Vector3(0.01f, 0.01f, 0.01f));/// Vector3(0.01f, 0.01f, 0.01f));// Vector3(Matrix4::Pitch(parameter.mat), Matrix4::Yaw(parameter.mat), Matrix4::Roll(parameter.mat)));

	for (int count = 0; count< ropeCount - 1; count++){
		int Color = GetColor(255, 0, 0);
		if (count % 2 == 0)Color = GetColor(0, 255, 0);
		DrawLine3D(Vector3::ToVECTOR(drawVertexVec[count] + parameter.mat.GetPosition()), Vector3::ToVECTOR(drawVertexVec[count + 1] + parameter.mat.GetPosition()), Color);
	}

	DrawSphere3D(Vector3::ToVECTOR(drawVertexVec[0] + parameter.mat.GetPosition()), 0.5f, 32, GetColor(255, 255, 255), GetColor(255, 255, 255), FALSE);
	
	//int ModelHandle = Model::GetInstance().GetHandle(MODEL_ID::TEST_MODEL);
	//MV1SetFrameUserLocalMatrix(ModelHandle, 1, MGetTranslate(
	//	Vector3::Zero));
	//for (int a = 2; a <= ropeCount; a++){
	//	Matrix4 inv = Matrix4::Identity;
	//	//inv = Matrix4::Inverse(Matrix4::ToMatrix4(MV1GetFrameLocalMatrix(ModelHandle, 1))) * inv;
	//	for (int b = 1; b < a; b++){
	//		inv = Matrix4::Inverse(Matrix4::ToMatrix4(MV1GetFrameLocalMatrix(ModelHandle, b))) * inv;
	//	}
	//	inv = Matrix4::Identity;
	//
	//	Matrix4 matFrame;
	//	Matrix4 rotateFrame = Matrix4::Identity;
	//	rotateFrame.SetFront(Vector3::Normalize(Vector3(-1,0,0)));
	//	rotateFrame.SetUp(Vector3(0, 1, 0));
	//	rotateFrame.SetLeft(Vector3::Normalize(-Vector3::Cross(Vector3::Normalize(vertexVec[a - 2] - vertexVec[a - 1]), Vector3(0, 1, 0))));
	//	matFrame = Matrix4::Scale(Vector3(1, 1, 1))  * Matrix4::Translate((vertexVec[a - 1] - vertexVec[a - 2]) / scale);
	//	MV1SetFrameUserLocalMatrix(ModelHandle, a, MMult(
	//		Matrix4::ToMATRIX(matFrame), Matrix4::ToMATRIX(inv)));
	//		//		Matrix4::ToMatrix4(GetCameraViewMatrix()) * 
	//		//		Matrix4::ToMatrix4(GetCameraProjectionMatrix()))));
	//		//VGet(3 * a, 0, 0) * inv
	//		//));
	//}
	//VECTOR Position = MV1GetFramePosition(ModelHandle, i);
	//DrawSphere3D(Position, 1.0f, 32, GetColor(255, 0, 0), GetColor(255, 0, 0), TRUE);


}


void Player::ParameterDraw() const{
	//DrawSphere3D(Vector3::ToVECTOR(vertexVec[0]), 1.0f, 32, GetColor(255, 255, 255), GetColor(255, 255, 255),FALSE);

	int ModelHandle = Model::GetInstance().GetHandle(MODEL_ID::TEST_MODEL);
	// フレーム名の描画
	DrawFormatString(0, 0, GetColor(255, 255, 255), "Name         %s", MV1GetFrameName(ModelHandle, i));

	// 親フレーム名の描画
	int Parent = MV1GetFrameParent(ModelHandle, i);
	if (Parent == -2)
	{
		DrawFormatString(0, 16, GetColor(255, 255, 255), "Parent Name  None");
	}
	else
	{
		DrawFormatString(0, 16, GetColor(255, 255, 255), "Parent Name  %s", MV1GetFrameName(ModelHandle, Parent));
	}

	// 子フレームの数を描画
	DrawFormatString(0, 32, GetColor(255, 255, 255), "Child Num    %d", MV1GetFrameChildNum(ModelHandle, i));

	// フレームのワールド座標の描画
	VECTOR Position = MV1GetFramePosition(ModelHandle, i);
	DrawFormatString(0, 48, GetColor(255, 255, 255), "Position     x:%f y:%f z:%f", Position.x, Position.y, Position.z);

	// 変換行列を描画する
	MATRIX Matrix = MV1GetFrameLocalMatrix(ModelHandle, i);
	DrawFormatString(0, 64, GetColor(255, 255, 255), "   Matrix    %f %f %f %f", Matrix.m[0][0], Matrix.m[0][1], Matrix.m[0][2], Matrix.m[0][3]);
	DrawFormatString(0, 80, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[1][0], Matrix.m[1][1], Matrix.m[1][2], Matrix.m[1][3]);
	DrawFormatString(0, 96, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[2][0], Matrix.m[2][1], Matrix.m[2][2], Matrix.m[2][3]);
	DrawFormatString(0, 112, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[3][0], Matrix.m[3][1], Matrix.m[3][2], Matrix.m[3][3]);

	// フレームのローカル座標からワールド座標に変換する行列を描画する
	Matrix = MV1GetFrameLocalWorldMatrix(ModelHandle, i);
	DrawFormatString(0, 128, GetColor(255, 255, 255), "LW Matrix    %f %f %f %f", Matrix.m[0][0], Matrix.m[0][1], Matrix.m[0][2], Matrix.m[0][3]);
	DrawFormatString(0, 144, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[1][0], Matrix.m[1][1], Matrix.m[1][2], Matrix.m[1][3]);
	DrawFormatString(0, 160, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[2][0], Matrix.m[2][1], Matrix.m[2][2], Matrix.m[2][3]);
	DrawFormatString(0, 176, GetColor(255, 255, 255), "             %f %f %f %f", Matrix.m[3][0], Matrix.m[3][1], Matrix.m[3][2], Matrix.m[3][3]);

	// フレームの表示状態を描画
	DrawFormatString(0, 192, GetColor(255, 255, 255), "Visible      %d", MV1GetFrameVisible(ModelHandle, i));

	// フレームに半透明要素があるかどうかを描画
	DrawFormatString(0, 208, GetColor(255, 255, 255), "Semi Trans   %d", MV1GetFrameSemiTransState(ModelHandle, i));

	// フレームに含まれるメッシュの数を描画
	DrawFormatString(0, 224, GetColor(255, 255, 255), "Mesh Num     %d", MV1GetFrameMeshNum(ModelHandle, i));

	// フレームに含まれる三角形ポリゴンの数を描画
	DrawFormatString(0, 240, GetColor(255, 255, 255), "Triangle Num %d", MV1GetFrameTriangleNum(ModelHandle, i));

	// フレームに半透明要素があるかどうかを描画
	DrawFormatString(0, 256, GetColor(255, 255, 255), "vertexVec.x   %f", Matrix4::ToMatrix4(Matrix).GetScale().x);

	float a = Matrix4::Yaw(parameter.mat);
	// フレームに含まれるメッシュの数を描画
	DrawFormatString(0, 272, GetColor(255, 255, 255), "vertexVec.y     %f", Matrix4::ToMatrix4(Matrix).GetScale().y);

	// フレームに含まれる三角形ポリゴンの数を描画
	DrawFormatString(0, 288, GetColor(255, 255, 255), "vertexVec.z	   %f", Matrix4::ToMatrix4(Matrix).GetScale().z);
	// フレームに含まれる三角形ポリゴンの数を描画
	DrawFormatString(0, 304, GetColor(255, 255, 255), "boneCount	   %d", MV1GetFrameNum(ModelHandle));
}
void Player::OnCollide(Actor& other, CollisionParameter colpara)
{
	position = Vector3(0, 0, 0);
}
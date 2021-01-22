#include "GameScene.h"
#include"Model.h"
#include"Collision.h"
#include <cassert>
#include <sstream>
#include <iomanip>

using namespace DirectX;

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
	safe_delete(spriteBG);
	//safe_delete(particleMan);
	safe_delete(light);
	safe_delete(objSkydome);
	safe_delete(objGround);
	safe_delete(objFighter);
	safe_delete(modelSkydome);
	safe_delete(modelGround);
	safe_delete(modelFighter);
	safe_delete(modelLay);
	safe_delete(objLay);
	safe_delete(objSphere);
	safe_delete(objSphere2);
	safe_delete(objCur);
	safe_delete(modelSphere);
	safe_delete(modelSphere2);
	safe_delete(modelCur);
	safe_delete(tri);
	safe_delete(objtri);
}

void GameScene::Initialize(DirectXCommon* dxCommon, Input* input, Audio * audio)
{
	// nullptrチェック
	assert(dxCommon);
	assert(input);
	assert(audio);

	this->dxCommon = dxCommon;
	this->input = input;
	this->audio = audio;

	// カメラ生成
	camera = new DebugCamera(WinApp::window_width, WinApp::window_height, input);

	// 3Dオブジェクトにカメラをセット
	Object3d::SetCamera(camera);

	// デバッグテキスト用テクスチャ読み込み
	if (!Sprite::LoadTexture(debugTextTexNumber, L"Resources/debugfont.png")) {
		assert(0);
		return;
	}
	// デバッグテキスト初期化
	debugText.Initialize(debugTextTexNumber);

	// テクスチャ読み込み
	if (!Sprite::LoadTexture(1, L"Resources/background.png")) {
		assert(0);
		return;
	}
	// 背景スプライト生成
	spriteBG = Sprite::Create(1, { 0.0f,0.0f });
	// パーティクルマネージャ生成
	//particleMan = ParticleManager::Create(dxCommon->GetDevice(), camera);

	// テクスチャ2番に読み込み
	Sprite::LoadTexture(2, L"Resources/tex1.png");

	// モデル読み込み
	modelSkydome = Model::CreateFromOBJ("skydome");
	modelGround = Model::CreateFromOBJ("ground");
	modelFighter = Model::CreateFromOBJ("chr_sword");
	modelSphere = Model::CreateFromOBJ("sphere",true);
	modelSphere2 = Model::CreateFromOBJ("sphere",true);
	tri = Model::CreateFromOBJ("triangle");
	modelCur = Model::CreateFromOBJ("Cur");
	modelLay = Model::CreateFromOBJ("Lay_mat");

	// 3Dオブジェクト生成
	objSkydome = Object3d::Create(modelSkydome);
	objGround = Object3d::Create(modelGround);
	objFighter = Object3d::Create(modelFighter);
	objSphere = Object3d::Create(modelSphere);
	objSphere2 = Object3d::Create(modelSphere2);
	objtri = Object3d::Create(tri);
	objCur = Object3d::Create(modelCur);
	objLay = Object3d::Create(modelLay);

	objFighter->SetPosition({ +1,0,0 });
	objSphere->SetPosition({ 2,1,0 });
	objSphere2->SetPosition({ 2,1,20 });
	objtri->SetPosition({ 0,1,0 });
	objtri->SetRotation({90,0,-90});
	objtri->SetScale({ 2,2,2 });


	sphere1.center = XMVectorSet(2, 1, 0, 1);
	sphere1.radius = 1.0f;

	sphere2.center = XMVectorSet(2, 1, 20, 1);
	sphere2.radius = 1.0f;

	plane.normal = XMVectorSet(0, 1, 0, 0); // 法線ベクトル
	plane.distance = 0.0f; // 原点(0,0,0)からの距離

	// 三角形の初期値を設定
	triangle.p0 = XMVectorSet(-1.0f, 1, -1.0f, 1);//左手前
	triangle.p1 = XMVectorSet(-1.0f, 1, +1.0f, 1);//左奥
	triangle.p2 = XMVectorSet(+1.0f, 1, -1.0f, 1);//右手前
	triangle.normal = XMVectorSet(0.0f, 1.0f, 0.0f, 0);//上向き

	// カメラ注視点をセット
	camera->SetTarget({ 1, 1, 0 });
	camera->SetDistance(3.0f);

	objCur->SetRotation(XMFLOAT3(0, 90, 0));
	objCur->SetScale(XMFLOAT3(1,0.2,0.2));

	hit2 = false;
	hit3 = false;
	hit4 = false;

	hit7 = false;
	//レイの初期値設定
	number = 0;
	n = 0.71;//レイが真横の時の処理
	objLay->SetRotation({ 0,number,90 });
	objLay->SetPosition({ 0,1,0 });
	lay.start = XMVectorSet( 0,1,0,0 );
	lay.dir = XMVectorSet(1,0,0,0);

	light = Light::Create();
	light->SetLightColor({ 1,1,1 });
	Object3d::SetLight(light);

	rot1 = false;
}

void GameScene::Update()
{
	// パーティクル生成
	//CreateParticles();

	camera->Update();
	//particleMan->Update();
	XMFLOAT3 position = objSphere->GetPosition();
	XMFLOAT3 position2 = objSphere2->GetPosition();
	XMFLOAT3 rotation2 = objSphere2->GetRotation();
	XMFLOAT3 layRot = objLay->GetRotation();
	float a;
	XMVECTOR p;
	objSphere->Update();
	objSphere2->Update();
	objLay->Update();

	// 球移動
	{
		XMVECTOR moveZ = XMVectorSet(0, 0, 0.01f, 0);
		if (input->PushKey(DIK_W)) { sphere1.center += moveZ;}
		else if (input->PushKey(DIK_S)) { sphere1.center -= moveZ;}
		XMVECTOR moveY = XMVectorSet(0, 0.01f, 0, 0);
		if (input->PushKey(DIK_UP)) {sphere1.center += moveY;}
		else if (input->PushKey(DIK_DOWN)) { sphere1.center -= moveY; }
		XMVECTOR moveX = XMVectorSet(0.01f, 0, 0, 0);
		if (input->PushKey(DIK_D)) { sphere1.center += moveX;}
		else if (input->PushKey(DIK_A)) { sphere1.center -= moveX;}
	}
	{
		if (input->PushKey(DIK_W)) { position.z += 0.01f; }
		else if (input->PushKey(DIK_S)) { position.z -= 0.01f; }
		if (input->PushKey(DIK_UP)) { position.y += 0.01f; }
		else if (input->PushKey(DIK_DOWN)) { position.y -= 0.01f; }
		if (input->PushKey(DIK_D)) { position.x += 0.01f; }
		else if (input->PushKey(DIK_A)) { position.x -= 0.01f; }

		objSphere->SetPosition(position); 
	}

	/*if(input->PushKey(DIK_1)){
		lay.dir = XMVectorSet(0, 1, 1, 0);
		number = 45;
		objLay->SetRotation({ 0,number,90 });
		rot1 = true;
	}*/

	/*XMFLOAT3 curp = objCur->GetPosition();
	Input::MouseMove mouseMove = input->GetMouseMove();
	curp.x += mouseMove.lX*0.01f;
	curp.y += -mouseMove.lY*0.01f;
	objCur->SetPosition(curp);*/

	/*if (input->PushKey(DIK_B))
	{
		curp.x = 0;
		curp.y = 2;
		objCur->SetPosition(curp);
	}*/

	//position.z += 0.001f;
	//objSphere->SetPosition(position);

	XMVECTOR inter;
	bool hit = Collision::CheckSphere2Plane(sphere1, plane, &inter);
	if (hit) {
		debugText.Print("SpherePlaneHIT", 50, 50, 1.0f);
	}

	//球と球の当たり判定
	XMVECTOR position_sub = XMVectorSet(
		position.x - position2.x,
		position.y - position2.y,
		position.z - position2.z,
		0);

	position_sub = XMVector3Length(position_sub);
	float distance = position_sub.m128_f32[0];

	if (distance <= sphere1.radius + sphere2.radius) {
		debugText.Print("Sphere*2Hit", 50, 100, 1.0f);
	}
	else
	{
		//debugText.Print("Sphere*2NotHit", 50, 200, 1.0f);
	}

	XMVECTOR inter2;
	bool hit3 = Collision::CheckSphere2Triangle(sphere1,
		triangle, &inter2);
	if (hit3) {
		debugText.Print("SphereTriangleHIT", 50, 300, 1.0f);
	}

	//レイの操作
	/*XMFLOAT3 layposition = objLay->GetPosition();
	{
		XMVECTOR moveZ = XMVectorSet(0, 0, 0.01f, 0);
		if (input->PushKey(DIK_NUMPAD8)) { lay.start += moveZ; layposition.z += 0.01f; }
		else if (input->PushKey(DIK_NUMPAD2)) { lay.start -= moveZ; layposition.z -= 0.01f; }
		XMVECTOR moveX = XMVectorSet(0.01f, 0, 0, 0);
		if (input->PushKey(DIK_NUMPAD6)) { lay.start += moveX; layposition.x += 0.01f; }
		else if (input->PushKey(DIK_NUMPAD4)) { lay.start -= moveX; layposition.x -= 0.01f; }
		XMVECTOR moveY = XMVectorSet(0, 0.01f, 0, 0);
		if (input->PushKey(DIK_NUMPADPLUS)) { lay.start += moveY; layposition.y += 0.01f; }
		else if (input->PushKey(DIK_NUMPADMINUS)) { lay.start -= moveY; layposition.y -= 0.01f; }
		objLay->SetPosition(layposition);
	}*/

	//レイと平面の当たり判定
	XMVECTOR inter3;
	float distance2;
	bool hit4 = Collision::CheckLay2Plane(lay, plane, &distance2, &inter3);
	if(hit4)
	{
		debugText.Print("LayPlane Hit", 50, 350, 1.0);
	}

	float distance3;
	XMVECTOR inter4;
	bool hit5 = Collision::CheckLay2Triangle(lay, triangle, &distance3, &inter4);
	if (hit5) {
		debugText.Print("LayTri Hit", 50, 370, 1.0f);
	}

	if (input->PushKey(DIK_UP)) {
		n = n + 0.02;
		number = number + 0.05;
		layRot.y -= 2;
		objLay->SetRotation(layRot);
	}
	else if (input->PushKey(DIK_DOWN)) {
		n = n - 0.02;
		number = number - 0.05;
		layRot.y += 2;
		objLay->SetRotation(layRot);
	}

	float distance4;
	XMVECTOR inter5;
	bool hit6 = Collision::CheckLay2Sphere(lay, sphere2, &distance4, &inter5);
	if (hit6)
	{
		debugText.Print("LaySphere Hit", 50, 390, 1.0f);
		hit7 = true;
	}
	if (hit7)
	{
		//float an;
		//an = a*0.05;
		a = -0.05*n;
		p = XMVectorSet(-2*(n*0.05)*n + 0.05,0,0,0);
		XMVector2Normalize(p);
		XMVECTOR moveZ = XMVectorSet(0, 0, a, 0);
		sphere2.center += moveZ;
		position2.z -= a;
		position2.x += p.m128_f32[0];
		//rotation2.x = number;
		//position2.x = number;
		objSphere2->SetPosition(position2);
		//objSphere2->SetRotation(rotation2);
	}
	if (!hit7) {

		XMVECTOR moveZ = XMVectorSet(0, 0, 0.05, 0);
		sphere2.center -= moveZ;
		position2.z -= 0.05f;
		position2.x = 2;
		objSphere2->SetPosition(position2);
	}

	if (position2.z <= -2) {
		position2.z = 20;
		sphere2.center = { 2, 1, 20, 0 };
		objSphere2->SetPosition(position2);
	}

	if (position2.z >= 15&&hit7) {
		hit7 = false;
		position2.z = 20;
		sphere2.center = { 2,1,20,0 };
		objSphere2->SetPosition(position2);
	}

	rotation2.y += 0.5f;
	objSphere2->SetRotation(rotation2);

	{
		static XMVECTOR lightDir = { 0,1,5,0 };
		if (input->PushKey(DIK_W)) { lightDir.m128_f32[1] += 0.5f; }
		else if (input->PushKey(DIK_S)) { lightDir.m128_f32[1] -= 0.5f; }
		if (input->PushKey(DIK_D)) { lightDir.m128_f32[0] += 0.5f; }
		else if (input->PushKey(DIK_A)) { lightDir.m128_f32[0] -= 0.5f; }

		light->SetLightDir(lightDir); 
	}

	objSkydome->Update();
	objGround->Update();
	objFighter->Update();
	objSphere->Update();
	objSphere2->Update();
	objtri->Update();
	objCur->Update();
	objLay->Update();
	light->Update();
}

void GameScene::Draw()
{
	// コマンドリストの取得
	ID3D12GraphicsCommandList* cmdList = dxCommon->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(cmdList);
	// 背景スプライト描画
	//spriteBG->Draw();

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon->ClearDepthBuffer();
#pragma endregion

#pragma region 3D描画
	// 3Dオブジェクトの描画
	Object3d::PreDraw(cmdList);
	objSkydome->Draw();
	objGround->Draw();
	//objFighter->Draw();
	//objSphere->Draw();
	//objtri->Draw();
	//objCur->Draw();
	objSphere2->Draw();
	objLay->Draw();
	Object3d::PostDraw();

	// パーティクルの描画
	//particleMan->Draw(cmdList);
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(cmdList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>


	// デバッグテキストの描画
	debugText.DrawAll(cmdList);

	// スプライト描画後処理
	Sprite::PostDraw();
#pragma endregion
}

void GameScene::CreateParticles()
{
	for (int i = 0; i < 10; i++) {
		// X,Y,Z全て[-5.0f,+5.0f]でランダムに分布
		const float rnd_pos = 10.0f;
		XMFLOAT3 pos{};
		pos.x = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.y = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;
		pos.z = (float)rand() / RAND_MAX * rnd_pos - rnd_pos / 2.0f;

		const float rnd_vel = 0.1f;
		XMFLOAT3 vel{};
		vel.x = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.y = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;
		vel.z = (float)rand() / RAND_MAX * rnd_vel - rnd_vel / 2.0f;

		XMFLOAT3 acc{};
		const float rnd_acc = 0.001f;
		acc.y = -(float)rand() / RAND_MAX * rnd_acc;

		// 追加
		//particleMan->Add(60, pos, vel, acc, 1.0f, 0.0f);
	}
}

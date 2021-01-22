#pragma once

#include "SafeDelete.h"
#include "DirectXCommon.h"
#include <DirectXMath.h>
#include "Input.h"
#include "Sprite.h"
#include "Object3d.h"
#include "ParticleManager.h"
#include "DebugText.h"
#include "Audio.h"
#include "DebugCamera.h"
#include"CollisionPrimitive.h"
#include"Light.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene
{
private: // エイリアス
	// Microsoft::WRL::を省略
	template <class T> using ComPtr = Microsoft::WRL::ComPtr<T>;
	// DirectX::を省略
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMMATRIX = DirectX::XMMATRIX;

private: // 静的メンバ変数
	static const int debugTextTexNumber = 0;

public: // メンバ関数

	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(DirectXCommon* dxCommon, Input* input, Audio* audio);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	/// <summary>
	/// パーティクル生成
	/// </summary>
	void CreateParticles();

private: // メンバ変数
	DirectXCommon* dxCommon = nullptr;
	Input* input = nullptr;
	Audio* audio = nullptr;
	DebugText debugText;

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	DebugCamera* camera = nullptr;
	Sprite* spriteBG = nullptr;
	//sParticleManager* particleMan = nullptr;

	Model* modelSkydome = nullptr;
	Model* modelGround = nullptr;
	Model* modelFighter = nullptr;
	Model* modelSphere = nullptr;
	Model* modelSphere2 = nullptr;
	Model* tri = nullptr;
	Model* modelCur = nullptr;
	Model* modelLay = nullptr;

	Object3d* objSkydome = nullptr;
	Object3d* objGround = nullptr;
	Object3d* objFighter = nullptr;
	Object3d* objSphere = nullptr;
	Object3d* objSphere2 = nullptr;
	Object3d* objtri = nullptr;
	Object3d* objCur = nullptr;
	Object3d* objLay = nullptr;

	Light* light = nullptr;

	Sphere sphere1;
	Sphere sphere2;

	Plane plane;
	Triangle triangle;

	XMMATRIX matWorld;
	XMMATRIX matWorld2;

	bool hit2;

	bool hit3;
	bool hit4;

	bool hit7;

	bool rot1;

	float number;

	Lay lay;

	float n;

};


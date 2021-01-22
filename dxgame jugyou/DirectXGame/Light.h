#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

///ライト
class Light
{
private://エイリアス
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public://サブクラス
	//定数バッファ用データ構造体
	struct ConstBufferData
	{
		XMVECTOR lightv;//ライトへの方向を表すベクトル
		XMFLOAT3 lightcolor;//ライトの色
	};
private://動的メンバ変数
	//デバイス
	static ID3D12Device* device;
public://静的メンバ関数
	//静的初期化
	static void StaticInitialize(ID3D12Device* device);
	//描画
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);
	//インスタンス生成
	static Light* Create();

	//ライト色をセット
	void SetLightColor(const XMFLOAT3& lightcolor);

	//初期化
	void Initialize();
	//定数バッファ転送
	void TransferConstBuffer();
	//ライト方向をセット
	void SetLightDir(const XMVECTOR& lightdir);
	//更新
	void Update();
private://メンバ変数
	//定数バッファ
	ComPtr<ID3D12Resource> constBuff;
	//ライト光線方向(単位ベクトル)
	XMVECTOR lightdir = { 1,0,0,0 };
	//ライト色
	XMFLOAT3 lightcolor = { 1,1,1 };
	//ダーティフラグ
	bool dirty = false;


};

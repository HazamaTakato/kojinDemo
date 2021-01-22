#pragma once
#include <Windows.h>
#include <wrl.h>
#include <d3d12.h>
#include <DirectXMath.h>
#include <d3dx12.h>

///���C�g
class Light
{
private://�G�C���A�X
	template<class T>using ComPtr = Microsoft::WRL::ComPtr<T>;
	using XMFLOAT2 = DirectX::XMFLOAT2;
	using XMFLOAT3 = DirectX::XMFLOAT3;
	using XMFLOAT4 = DirectX::XMFLOAT4;
	using XMVECTOR = DirectX::XMVECTOR;
	using XMMATRIX = DirectX::XMMATRIX;
public://�T�u�N���X
	//�萔�o�b�t�@�p�f�[�^�\����
	struct ConstBufferData
	{
		XMVECTOR lightv;//���C�g�ւ̕�����\���x�N�g��
		XMFLOAT3 lightcolor;//���C�g�̐F
	};
private://���I�����o�ϐ�
	//�f�o�C�X
	static ID3D12Device* device;
public://�ÓI�����o�֐�
	//�ÓI������
	static void StaticInitialize(ID3D12Device* device);
	//�`��
	void Draw(ID3D12GraphicsCommandList* cmdList, UINT rootParameterIndex);
	//�C���X�^���X����
	static Light* Create();

	//���C�g�F���Z�b�g
	void SetLightColor(const XMFLOAT3& lightcolor);

	//������
	void Initialize();
	//�萔�o�b�t�@�]��
	void TransferConstBuffer();
	//���C�g�������Z�b�g
	void SetLightDir(const XMVECTOR& lightdir);
	//�X�V
	void Update();
private://�����o�ϐ�
	//�萔�o�b�t�@
	ComPtr<ID3D12Resource> constBuff;
	//���C�g��������(�P�ʃx�N�g��)
	XMVECTOR lightdir = { 1,0,0,0 };
	//���C�g�F
	XMFLOAT3 lightcolor = { 1,1,1 };
	//�_�[�e�B�t���O
	bool dirty = false;


};

#pragma once

#include "CollisionPrimitive.h"

/// <summary>
/// �����蔻��w���p�[�N���X
/// </summary>
class Collision
{
public:
	/// <summary>
	/// ���ƕ��ʂ̓����蔻��
	/// </summary>
	/// <param name="sphere">��</param>
	/// <param name="plane">����</param>
	/// <param name="inter">��_�i���ʏ�̍Đڋߓ_�j</param>
	/// <returns>�������Ă��邩�ۂ�</returns>
	static bool CheckSphere2Plane(const Sphere& sphere, const Plane& plane, DirectX::XMVECTOR *inter = nullptr);

	///�_�ƎO�p�`�̍ŋߐړ_�����߂�
	static void ClosestPtPoint2Triangle(const DirectX::XMVECTOR& point,
		const Triangle& triangle, DirectX::XMVECTOR* closest);

	///���Ɩ@���t���O�p�`�̓�����`�F�b�N
	static bool CheckSphere2Triangle(const Sphere& sphere, const Triangle& triangle,
		DirectX::XMVECTOR* inter = nullptr);

	///���C�ƕ��ʂ̓����蔻��
	static bool CheckLay2Plane(const Lay& lay, const Plane& plane,
		float* distance = nullptr, DirectX::XMVECTOR* inter = nullptr);

	///���C�Ɩ@���t���O�p�`�̓����蔻��
	static bool CheckLay2Triangle(const Lay& lay, const Triangle& triangle,
		float*distance = nullptr, DirectX::XMVECTOR*inter = nullptr);

	///���C�Ƌ��̓����蔻��
	static bool CheckLay2Sphere(const Lay& lay, const Sphere& sphere,
		float*distance = nullptr, DirectX::XMVECTOR*inter = nullptr);
};


#pragma once

#include "alignment.h"
#include <DirectXMath.h>
#include <DirectXCollision.h>
using namespace DirectX;


class GameObject : public Alignment<16>
{
protected:
	bool        m_Destroy = false;

	XMFLOAT3 m_Position;
	XMFLOAT3 m_Rotation;
	XMFLOAT3 m_Scale;

	XMMATRIX m_WorldMtx;
	XMMATRIX m_ScaleMtx;
	XMMATRIX m_RotMtx;
	XMMATRIX m_TransMtx;
	XMMATRIX m_LookAtMtx;

public:
	GameObject() {}				//�R���X�g���N�^
	virtual ~GameObject() {}	//�f�X�g���N�^

	virtual void Init() = 0;
	virtual void Uninit() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;
	
	void AddWorldOffset(const XMFLOAT3& direction, float speed = 1.0f);
	void AddWorldOffsetFromVector(const XMVECTOR& direction, float speed = 1.0f);
	void AddWorldRotation(const XMFLOAT3& axis, float angle = 1.0f);


	// �L�����N�^�p���s��Z�o�֐� (�C�ӕ����j
	XMMATRIX LookAtMatrix(const XMFLOAT3& Pos, const XMFLOAT3& Look, const XMFLOAT3& Up);

	// �L�����N�^�����p���s��Z�o�֐�
	XMMATRIX LookAtMatrixAxisFix(const XMFLOAT3& Pos, const XMFLOAT3& Look, const XMFLOAT3& Up);


	XMFLOAT2 GetScreenPosition(XMFLOAT3 position);	//3D���W���X�N���[�����W�ɕϊ��@MouseEvent�̂���
	float GetDistance(const XMFLOAT3& pos1, const XMFLOAT3& pos2);
	float GetDistanceFromVector(const XMVECTOR& vec1, const XMVECTOR& vec2);

	XMVECTOR GetForwardVector();	//Z�����x�N�g���擾
	XMVECTOR GetUpVector();			//Y�����x�N�g���擾
	XMVECTOR GetRightVector();		//X�����x�N�g���擾

	const XMFLOAT3& GetPosition() const { return m_Position; }
	const XMFLOAT3& GetRotation() const { return m_Rotation; }
	void SetPosition(XMFLOAT3 Position) { m_Position = Position; }
	void SetRotation(XMFLOAT3 Rotation) { m_Rotation = Rotation; }
	void SetScale(XMFLOAT3 Scale) { m_Scale = Scale; }
	
	void SetDestroy() { m_Destroy = true; }
	bool Destroy()
	{
		if (m_Destroy)
		{
			Uninit();
			delete this;
			return true;
		}
		else
		{
			return false;
		}

	}
};

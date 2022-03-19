

#pragma once
#include "singleton.h"
#include "texture.h"

#include <DirectXMath.h>
using namespace DirectX;

struct Transform2D
{
	XMFLOAT2 Position;
	XMFLOAT2 Rotation;
	XMFLOAT2 Scale;
};

class Sprite2D : public Singleton<Sprite2D>
{
private:
	ID3D11Buffer*		 m_VertexBuffer;
	ID3D11Buffer*		 m_IndexBuffer;

	ID3D11VertexShader*			 m_VertexShader;
	ID3D11PixelShader*			 m_PixelShader;
	ID3D11InputLayout*			 m_VertexLayout;

	XMFLOAT4 m_Color;

public:
	void Init(void);
	void Uninit(void);
	
	//2D�`��
	//
	//�����F
	//			textureId	...�e�N�X�`���[�ԍ�
	//			dx			...�`����W X
	//			xy			...�`����W Y
	//			dw			...�`��T�C�Y�̕� 
	//			dh			...�`��T�C�Y�̍���
	//			tcx			...�e�N�X�`���[�؂�����W X
	//			tcy			...�e�N�X�`���[�؂�����W Y
	//			tcw			...�e�N�X�`���[�؂��蕝
	//			tch			...�e�N�X�`���[�؂��荂��
	//			cx			...��]���S�_���W X
	//			cy			...��]���S�_���W Y
	//			angle		...��]�p�x
	//
	void SpriteDraw(int textureId, float dx, float dy, float dw, float dh, int tcx, int tcy, int tcw, int tch, float cx = 0.0f, float cy = 0.0f, float angle = 0.0f);


	void SetColor(const XMFLOAT4& color) { m_Color = color; }

};
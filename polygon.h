#pragma once


class CPolygon
{
private:

	ID3D11Buffer*				m_VertexBuffer = NULL;
	ID3D11ShaderResourceView*	m_Texture = NULL;

	//������	�V�F�[�_�[�֘A�̕ϐ���ǉ�



public:
	void Init();
	void Uninit();
	void Update();
	void Draw();


};
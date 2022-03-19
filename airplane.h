#pragma once

#include "player.h"
#include "model.h"

class Airplane : public Player
{
private:
	static Model* m_Model;

	static ID3D11VertexShader*		m_VertexShader;
	static ID3D11PixelShader*		m_PixelShader;
	static ID3D11InputLayout*		m_VertexLayout;

	class HP* m_Hp;

public:
	static void Load();
	static void Unload();

	void Init() override;
	void Uninit() override;
	void Update() override;
	void Draw() override;


};

#pragma once

#include"main.h"
#include <DirectXMath.h>
using namespace DirectX;

#define IKD_EPSIRON 0.00001f

// �����\����
struct Line
{
	XMFLOAT2 Start;
	XMFLOAT2 End;
};

// �~�\����
struct Circle
{
	XMFLOAT2 Position;
	float radius;
};

struct Line3D
{
	XMFLOAT3 Start;
	XMFLOAT3 End;
};

struct Tama
{
	XMFLOAT3 Position;
	float Radius;
};

struct Rect
{
	XMFLOAT2 Position;
	XMFLOAT2 Size;
};

class Collision
{

public:

	static bool PointAndRect(const XMFLOAT2& point, const Rect& rect);
	static bool PointAndCircle(const XMFLOAT2& point, const Circle& circle);
};


//���_�Ԃ̒��������߂�
float GetVertexLength(const D3DXVECTOR2& position1, const D3DXVECTOR2& position2);


//�����Ɖ~�̏Փ˔���
bool Collision_LineAndCircle(Line line, Circle circle);



#include"collision.h"

//���_�Ԃ̒��������߂�
float GetVertexLength(const D3DXVECTOR2& position1, const D3DXVECTOR2& position2)
{
	return sqrtf((position1.x - position2.x) * (position1.x - position2.x) + (position1.y - position2.y) * (position1.y - position2.y));
}


////�����Ɖ~�̏Փ˔���
//bool Collision_LineAndCircle(Line line, Circle circle)
//{
//	XMFLOAT2 start_to_center = { circle.Position.x - line.Start.x, circle.Position.y - line.Start.y };
//	XMFLOAT2 end_to_center = { circle.Position.x - line.End.x, circle.Position.y - line.End.y };
//	XMFLOAT2 start_to_end = { line.End.x - line.Start.x, line.End.y - line.Start.y };
//	XMFLOAT2 normal_start_to_end;
//	D3DXVec2Normalize(&normal_start_to_end, &start_to_end);
//
//	//�ˉe���������̒���
//	float distance_projection = start_to_center.x * normal_start_to_end.y - normal_start_to_end.x * start_to_center.y;
//
//	// �ˉe�̒��������a����������
//	if (fabs(distance_projection) < circle.radius)
//	{
//		// �n�_����I�_�Ǝn�_����~�̒��S�̓��ς��v�Z����
//		float dot01 = start_to_center.x * start_to_end.x + start_to_center.y * start_to_end.y;
//		// �n�_����I�_�ƏI�_����~�̒��S�̓��ς��v�Z����
//		float dot02 = end_to_center.x * start_to_end.x + end_to_center.y * start_to_end.y;
//
//		// ��̓��ς̊|���Z���ʂ�0�ȉ��Ȃ瓖����
//		if (dot01 * dot02 <= 0.0f)
//		{
//			return true;
//		}
//		else if (D3DXVec2Length(&start_to_center) < circle.radius ||
//			D3DXVec2Length(&end_to_center) < circle.radius)
//		{
//			return true;
//		}
//	}
//
//	return false;
//
//}

bool Collision::PointAndRect(const XMFLOAT2 & point, const Rect & rect)
{
	if (point.x >= rect.Position.x &&
		point.y >= rect.Position.y &&
		point.x <= (rect.Position.x + rect.Size.x) &&
		point.y <= (rect.Position.y + rect.Size.y))
	{
		return true;
	}
	else
	{
		return false;
	}
}

bool Collision::PointAndCircle(const XMFLOAT2 & point, const Circle & circle)
{
	float a = point.x - circle.Position.x;
	float b = point.y - circle.Position.y;
	float c = a * a + b * b;

	if (c <= circle.radius * circle.radius)
	{
		return true;
	}

	return false;

}


bool CalcSphereRayCollision(
	float r, XMFLOAT3 center, XMFLOAT3 s, XMVECTOR v
) {
	float a = 0.0f;
	float b = 0.0f;
	float c = 0.0f;

	XMVECTOR u = XMVectorSubtract(XMLoadFloat3(&s), XMLoadFloat3(&center));

	XMStoreFloat(&a, XMVector3Dot(v, v));
	XMStoreFloat(&b, XMVector3Dot(v, u));
	XMStoreFloat(&c, XMVector3Dot(u, u));

	float d = c - r * r;

	if (a - IKD_EPSIRON <= 0.0f) 
	{
		// �덷
		return false;
	}

	float isColli = b * b - a * d;
	if (isColli < 0.0f) 
	{
		// �Փ˂��Ȃ�
		return false;
	}


	// �Փ˂��Ă���I
	return true;
}

// lx, ly, lz : ���C�̎n�_
// vx, vy, vz : ���C�̕����x�N�g��
// px, py, pz : ���̒��S�_�̍��W
// r : ���̔��a
// q1x, q1y, q1z: �ՓˊJ�n�_�i�߂�l�j
// q2x, q2y, q2z: �ՓˏI���_�i�߂�l�j

bool calcRaySphere(
	XMFLOAT3 start,
	XMFLOAT3 rayVec,
	XMFLOAT3 sphere,
	float radius
	//float &q1x, float &q1y, float &q1z,
	//float &q2x, float &q2y, float &q2z
) {

	XMStoreFloat3(&sphere,XMVectorSubtract(XMLoadFloat3(&sphere), XMLoadFloat3(&start)));

	float a = rayVec.x * rayVec.x + rayVec.y * rayVec.y + rayVec.z * rayVec.z;
	float b = rayVec.x * sphere.x + rayVec.y * sphere.y + rayVec.z * sphere.z;
	float c = sphere.x * sphere.x + sphere.y * sphere.y + sphere.z * sphere.z - radius * radius;


	if (a == 0.0f)
		return false; // ���C�̒�����0

	float s = b * b - a * c;
	if (s < 0.0f)
		return false; // �Փ˂��Ă��Ȃ�

	s = sqrtf(s);
	float a1 = (b - s) / a;
	float a2 = (b + s) / a;

	if (a1 < 0.0f || a2 < 0.0f)
		return false; // ���C�̔��΂ŏՓ�

	/*q1x = lx + a1 * vx;
	q1y = ly + a1 * vy;
	q1z = lz + a1 * vz;
	q2x = lx + a2 * vx;
	q2y = ly + a2 * vy;
	q2z = lz + a2 * vz;*/

	return true;
}
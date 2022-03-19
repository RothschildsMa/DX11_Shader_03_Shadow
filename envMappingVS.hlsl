
#include "common.hlsl"


void main(in VS_IN In, out PS_IN Out)
{

	matrix wvp;
	wvp = mul(World, View);
	wvp = mul(wvp, Projection);

	//�����v�Z
	float4 worldNormal, normal;
	normal = float4(In.Normal.xyz, 0.0);	//normal.w��0�ɂ���(���s�ړ��͂��Ȃ�)
	worldNormal = mul(normal, World);		//���[���h�ϊ�
	worldNormal = normalize(worldNormal);	//��]��̖@���𐳋K������
	Out.Normal = worldNormal;				//��]��̖@���o�� In.Normal�łȂ���]��̖@�����o��



	Out.Diffuse = In.Diffuse;
	Out.Position = mul(In.Position, wvp);
	Out.TexCoord = In.TexCoord;

}


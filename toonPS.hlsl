

#include "common.hlsl"


Texture2D g_Texture : register(t0);
Texture2D g_TextureToon : register(t1);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{

	float4 normal = normalize(In.Normal);
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);//�e�N�X�`�����擾
	outDiffuse.a *= In.Diffuse.a; //���l�̏���

	float light = -dot(normal.xyz, Light.Direction.xyz);


	/*if (light > 0.6f)
	{
		light = 1.0f;
	}
	else if (light > 0.4f)
	{
		light = 0.8f;
	}
	else
	{
		light = 0.6f;
	}

	outDiffuse.rgb *= saturate(In.Diffuse.rgb * light); //�e�N�X�`�������_�F�����邳
	*/
	
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz; //�����x�N�g�������
	eyev = normalize(eyev); //�����x�N�g���𐳋K������
	float d = dot(eyev, normal.xyz); //�@���Ǝ����x�N�g���̓���

	if (d > -0.3) //d�̒l�𔻒�
	{
		outDiffuse.rgb *= 0.2; //�K����臒l�Ŗ��x�𗎂Ƃ�
	}
	


	//�e�N�X�`���[��
	float2 uv = light;
	float3 col;
	uv = clamp(uv, 0.1f, 0.9);
	col = g_TextureToon.Sample(g_SamplerState, uv).xyz; //���邳���擾
	outDiffuse.rgb *= saturate(In.Diffuse.rgb * col); //�e�N�X�`�������_�F�����邳


}


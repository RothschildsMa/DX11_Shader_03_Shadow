

#include "common.hlsl"


Texture2D g_Texture : register(t0);
Texture2D g_TextureEnv : register(t1);
SamplerState g_SamplerState : register(s0);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	

	//�P �s�N�Z���̖@���𐳋K��
	float4 normal = normalize(In.Normal);

	//float  light = -dot(normal, Light.Direction.xyz); //���邳���v�Z

	//outDiffuse.rgb *= (light * In.Diffuse.rgb);


	//�Q �����x�N�g�����쐬���Đ��K��
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
	eyev = normalize(eyev);
	//�R ���˃x�N�g�����쐬���Đ��K��
	float3 refv = reflect(eyev, normal.xyz);
	refv = normalize(refv);
	//�S ���˃x�N�g��������}�b�s���O�p�̃e�N�X�`�����W���쐬
	float2 envTexCoord;
	envTexCoord.x = -refv.x * 0.3 + 0.5;
	envTexCoord.y = -refv.y * 0.3 + 0.5;
	//�T �e�N�X�`���̃f�[�^���擾��A�X�t�B�A�}�b�v�ƃx�[�X�e�N�X�`�������Z���ďo��
	float4 EnvTex = g_TextureEnv.SampleBias(g_SamplerState, envTexCoord, 0.0f);
	float4 BaseTex = g_Texture.Sample(g_SamplerState, In.TexCoord);
	outDiffuse.rgb = (1.0f * EnvTex.rgb) + (1.0f * BaseTex.rgb);
	//�U ���l�̏��� �x�[�X�̃e�N�X�`���̃��l�ƈ����̃s�N�Z���F�̃��l����Z
	outDiffuse.a = BaseTex.a * In.Diffuse.a;
}


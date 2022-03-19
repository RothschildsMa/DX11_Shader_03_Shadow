

#include "common.hlsl"


Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

Texture2D g_NormalMap : register(t1);


void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{

	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);

	float3 normal = In.Normal.xyz;

	float3 localNormal = g_NormalMap.Sample(g_SamplerState, In.TexCoord).xyz;
	localNormal = (localNormal - 0.5f) * 2.0f;

	normal = In.Tangent * -localNormal.x + In.BiNormal * -localNormal.y + normal * localNormal.z;


	float  light = -dot(normal, Light.Direction.xyz); //���邳���v�Z
	//float  light = 0.5f - 0.5f * dot(normal, Light.Direction.xyz);//�n�[�t�����o�[�g�ɂ�閾�邳�̌v�Z

	outDiffuse.rgb *= (light * In.Diffuse.rgb);
	outDiffuse.a *= In.Diffuse.a; //���ɖ��邳�͊֌W�Ȃ��̂ŕʌv�Z


	//�X�y�L�����[(�t�H�����ʔ���)
	float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;//�����x�N�g��
	eyev = normalize(eyev);
	float3 refv = reflect(Light.Direction.xyz, normal);//���̔��˃x�N�g��
	refv = normalize(refv);
	float specular = -dot(eyev, refv);	//���ʔ��˂̌v�Z
	specular = saturate(specular);		//�l���T�`�����[�g

	specular = pow(specular, 30);		//30��
	outDiffuse.rgb += specular;

	//�X�|�b�g���C�g�̏���
	float3 vp = normalize(In.WorldPosition.xyz - Light.Position.xyz); //���C�g����s�N�Z���̃x�N�g��
	float angle = abs(acos(dot(Light.Direction.xyz, vp))); //�s�N�Z���ւ̃x�N�g���ƌ��x�N�g���̂Ȃ��p�x
	float spot = 1.0f - (1.0f / (Light.Angle + Parameter.x)) * angle; //���C�g�͈͓̔��̏ꍇ�͖��邢�@�͈͊O�͈Â��@��Ԃ����

	spot = saturate(spot);

	outDiffuse.rgb *= spot; //�X�|�b�g���C�g�͈̔͂ł̖��邳�̕␳
}





#include "common.hlsl"

//DirectX�̃e�N�X�`���[�̐ݒ���󂯌p��
Texture2D		g_Texture : register(t0);//�e�N�X�`���[0��
//DirectX�̃T���v���[�X�e�[�g�ݒ���󂯌p��
SamplerState	g_SamplerState : register(s0);//�e�N�X�`���[�T���v���[0��

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
	
	//���̃s�N�Z���Ɏg����e�N�X�`���[�̐F���擾
	outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);

	//���̃s�N�Z���̃f�t���[�Y�F����Z
	outDiffuse *= In.Diffuse;

	if (outDiffuse.a < 0.01)
	{
		discard;
	}

	////�O���[�X�P�[���� Y = 0.299 * R + 0.587 * G + 0.114 * B
	//outDiffuse.rgb = (0.299 * outDiffuse.r) + (0.587 * outDiffuse.g) + (0.114 * outDiffuse.b);

	////�Z�s�A���ϊ�
	//float4 sepia = float4(0.960, 0.784, 0.580, 1.0);
	//outDiffuse *= sepia;

	//�l�K���]
	//outDiffuse.rgb = 1.0f - outDiffuse.rgb;

	//���O�s������
	//outDiffuse.rgb = pow(outDiffuse.rgb, 4);

	//float2 len = float2(0.5, 0.5);	//���S���W
	//len -= In.TexCoord.xy;			//���S�Ǝ��s�N�Z���Ƃ̃x�N�g��
	//len = 1.0 - length(len);		//�x�N�g�����狗�����v�Z

	//outDiffuse.rgb *= pow(len.x, 2);

}

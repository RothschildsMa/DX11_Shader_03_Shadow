#pragma once

#include"main.h"

class Random
{
private:
	static unsigned int d;

public:

	static unsigned int FastNRand(void);		//�����̗����擾
	static float FastFRand(void);				//���������̗����擾
	static int GetRandom(int a, int b);			//�����̗����擾(�͈͎w���a �` b-1)
	static float GetRandom(float a, float b);	//���������̗����擾(�͈͎w���)
	static D3DXVECTOR3& GetRandom(D3DXVECTOR3& out);	//�x�N�g���̗����擾

};
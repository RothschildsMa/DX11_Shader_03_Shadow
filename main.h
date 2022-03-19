#pragma once

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <windows.h>
#include <assert.h>



#pragma warning(push)
#pragma warning(disable:4005)

#include <d3d11.h>
#include <d3dx9.h>
#include <d3dx11.h>

#pragma warning(pop)


#pragma comment (lib, "winmm.lib")
#pragma comment (lib, "d3d11.lib")
#pragma comment (lib, "d3dx9.lib")
#pragma comment (lib, "d3dx11.lib")
#pragma comment(lib, "dinput8.lib")
#pragma comment(lib, "dxguid.lib")

#include <DirectXMath.h>
using namespace DirectX;


#define CLASS_NAME		"GameWindow"			// �E�C���h�E�N���X�̖��O
#define WINDOW_NAME		"AT13A114_35_�n �L��_GG31 �ۑ� 11"        // �E�C���h�E�̖��O
#define SCREEN_WIDTH (1600)
#define SCREEN_HEIGHT (900)

HWND GetWindow();

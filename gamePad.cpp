/*=======================================================================================

	  �R���g���[���[����N���X[gamePad.cpp]
												author:MA
												date:2021/08/13
 -----------------------------------------------------------------------------------------
 ��DirectInput API �̂ݑΉ�����
 =========================================================================================*/
#include"gamePad.h"
#include"singleton.h"

BOOL SetUpGamePadProperty(LPDIRECTINPUTDEVICE8 device);
BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef);

BOOL SetUpGamePadProperty(LPDIRECTINPUTDEVICE8 device)
{
	// �����[�h���Βl���[�h�Ƃ��Đݒ�
	DIPROPDWORD diprop;
	ZeroMemory(&diprop, sizeof(diprop));
	diprop.diph.dwSize = sizeof(diprop);
	diprop.diph.dwHeaderSize = sizeof(diprop.diph);
	diprop.diph.dwHow = DIPH_DEVICE;
	diprop.diph.dwObj = 0;
	diprop.dwData = DIPROPAXISMODE_ABS;
	if (FAILED(device->SetProperty(DIPROP_AXISMODE, &diprop.diph)))
	{
		return false;
	}

	// X���̒l�͈̔͐ݒ�
	DIPROPRANGE diprg;
	ZeroMemory(&diprg, sizeof(diprg));
	diprg.diph.dwSize = sizeof(diprg);
	diprg.diph.dwHeaderSize = sizeof(diprg.diph);
	diprg.diph.dwHow = DIPH_BYOFFSET;
	diprg.lMin = -1000;
	diprg.lMax = 1000;

	diprg.diph.dwObj = DIJOFS_X;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	// Y���̒l�͈̔͐ݒ�
	diprg.diph.dwObj = DIJOFS_Y;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	diprg.diph.dwObj = DIJOFS_Z;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	diprg.diph.dwObj = DIJOFS_RZ;
	if (FAILED(device->SetProperty(DIPROP_RANGE, &diprg.diph)))
	{
		return false;
	}

	return true;
}

BOOL CALLBACK DeviceFindCallBack(LPCDIDEVICEINSTANCE lpddi, LPVOID pvRef)
{
	DeviceEnumParameter* parameter = (DeviceEnumParameter*)pvRef;
	LPDIRECTINPUTDEVICE8 device = nullptr;

	// ���ɔ������Ă���Ȃ�I��
	if (parameter->FindCount >= 1)
	{
		return DIENUM_STOP;
	}

	// �f�o�C�X����
	HRESULT hr = MyDirectInput::GetInstance().GetInterFace()->CreateDevice(
		lpddi->guidInstance,
		parameter->GamePadDevice,
		NULL);

	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	// ���̓t�H�[�}�b�g�̎w��
	device = *parameter->GamePadDevice;
	hr = device->SetDataFormat(&c_dfDIJoystick);

	if (FAILED(hr))
	{
		return DIENUM_STOP;
	}

	// �v���p�e�B�̐ݒ�
	if (SetUpGamePadProperty(device) == false)
	{
		return DIENUM_STOP;
	}

	// �������x���̐ݒ�
	if (SetUpCooperativeLevel(device) == false)
	{
		return DIENUM_STOP;
	}

	// ���������J�E���g
	parameter->FindCount++;

	return DIENUM_CONTINUE;
}

BOOL GamePad::StartGamePadControl()
{
	// �f�o�C�X����������ĂȂ�
	if (this->m_InputDevice == nullptr)
	{
		return false;
	}

	// ����J�n
	if (FAILED(this->m_InputDevice->Acquire()))
	{
		return false;
	}

	DIDEVCAPS cap;
	this->m_InputDevice->GetCapabilities(&cap);
	// �|�[�����O����
	if (cap.dwFlags & DIDC_POLLEDDATAFORMAT)
	{
		DWORD error = GetLastError();
		// �|�[�����O�J�n
		/*
			Poll��Acquire�̑O�ɍs���Ƃ���Ă������A
			Acquire�̑O�Ŏ��s����Ǝ��s�����̂�
			��Ŏ��s����悤�ɂ���
		*/
		if (FAILED(this->m_InputDevice->Poll()))
		{
			return false;
		}
	}

	return true;
}

void GamePad::InitController(void)
{
	// ���͏��̏�����
	for (int i = 0; i < ButtonKindMax; i++)
	{
		m_JoyStates[i] = JoyStateNone;
	}
}

void GamePad::UpdateController(void)
{
	if (this->m_InputDevice == nullptr) return;

	DIJOYSTATE pad_data;

	// �f�o�C�X�擾
	HRESULT hr = this->m_InputDevice->GetDeviceState(sizeof(DIJOYSTATE), &pad_data);
	if (FAILED(hr))
	{
		// �ēx����J�n
		if (FAILED(this->m_InputDevice->Acquire()))
		{
			for (int i = 0; i < ButtonKindMax; i++)
			{
				m_JoyStates[i] = JoyStateNone;
			}
			this->m_InputDevice->Poll();
		}
		return;
	}

	bool is_push[ButtonKindMax];

	//==================================================================
	// ���X�e�B�b�N�̐ݒ�
	//==================================================================
	//�A�i���O�X�e�B�b�N�̍��E�̏�Ԃ� -1000�`+1000

	int unresponsive_range = 200;

	if (pad_data.lX < -unresponsive_range)
	{
		is_push[LStickLeft] = true;
	}
	else if (pad_data.lX > unresponsive_range)
	{
		is_push[LStickRight] = true;
	}

	if (pad_data.lY < -unresponsive_range)
	{
		is_push[LStickUP] = true;
	}
	else if (pad_data.lY > unresponsive_range)
	{
		is_push[LStickDown] = true;
	}

	//==================================================================
	// �E�X�e�B�b�N�̐ݒ�
	//==================================================================
	if (pad_data.lZ < -unresponsive_range)
	{
		is_push[RStickLeft] = true;
	}
	else if (pad_data.lZ > unresponsive_range)
	{
		is_push[RStickRight] = true;
	}

	if (pad_data.lRz < -unresponsive_range)
	{
		is_push[RStickUP] = true;
	}
	else if (pad_data.lRz > unresponsive_range)
	{
		is_push[RStickDown] = true;
	}


	//==================================================================
	// �\���L�[�̐ݒ�
	//==================================================================
	if (pad_data.rgdwPOV[0] != 0xFFFFFFFF)
	{
		float rad = D3DXToRadian((pad_data.rgdwPOV[0] / 100.0f));

		float x = sinf(rad);
		float y = cosf(rad);

		if (x < -0.01f)
		{
			is_push[LeftButton] = true;
		}
		else if (x > 0.01f)
		{
			is_push[RightButton] = true;
		}

		if (y > 0.01f)
		{
			is_push[UpButton] = true;
		}
		else if (y < -0.01f)
		{
			is_push[DownButton] = true;
		}
	}



	//==================================================================
	// �{�^���̐ݒ�
	//==================================================================
	for (int i = 0; i < 32; i++)
	{
		if (!(pad_data.rgbButtons[i] & 0x80))
		{
			continue;
		}

		switch (i)
		{
		case 0:
			is_push[ButtonY] = true;
			break;
		case 1:
			is_push[ButtonB] = true;
			break;
		case 2:
			is_push[ButtonA] = true;
			break;
		case 3:
			is_push[ButtonX] = true;
			break;
		case 4:
			is_push[ButtonLB] = true;
			break;
		case 5:
			is_push[ButtonRB] = true;
			break;
		case 6:
			is_push[ButtonLT] = true;
			break;
		case 7:
			is_push[ButtonRT] = true;
			break;
		case 8:
			is_push[Button_BACK] = true;
			break;
		case 9:
			is_push[Button_START] = true;
			break;
		}
	}


	// ���͏�񂩂�{�^���̏�Ԃ��X�V����
	for (int i = 0; i < ButtonKindMax; i++)
	{
		if (is_push[i] == true)
		{
			if (m_JoyStates[i] == JoyStateNone)
			{
				m_JoyStates[i] = JoyStateDown;
			}
			else
			{
				m_JoyStates[i] = JoyStatePush;
			}
		}
		else
		{
			if (m_JoyStates[i] == JoyStatePush)
			{
				m_JoyStates[i] = JoyStateUp;
			}
			else
			{
				m_JoyStates[i] = JoyStateNone;
			}
		}
	}
}

void GamePad::UninitController()
{
	if (this->m_InputDevice != nullptr)
	{
		// ������~
		this->m_InputDevice->Unacquire();
		this->m_InputDevice->Release();
		this->m_InputDevice = nullptr;
	}

}

bool GamePad::JoystickPress(ButtonKind button)
{
	if (m_JoyStates[button] == JoyStatePush)
	{
		return true;
	}

	return false;
}

bool GamePad::JoystickRelease(ButtonKind button)
{
	if (m_JoyStates[button] == JoyStateUp)
	{
		return true;
	}

	return false;
}

bool GamePad::JoystickTrigger(ButtonKind button)
{
	if (m_JoyStates[button] == JoyStateDown)
	{
		return true;
	}

	return false;
}

void GamePad::CreateGamePadDevice()
{
	DeviceEnumParameter parameter;

	parameter.FindCount = 0;
	parameter.GamePadDevice = &this->m_InputDevice;

	// GAMEPAD�𒲂ׂ�
	MyDirectInput::GetInstance().GetInterFace()->EnumDevices(
		DI8DEVTYPE_GAMEPAD,			// ��������f�o�C�X�̎��
		DeviceFindCallBack,			// �������Ɏ��s����֐�
		&parameter,					// �֐��ɓn���l
		DIEDFL_ATTACHEDONLY			// �������@
	);

	// JOYSTICK�𒲂ׂ�
	MyDirectInput::GetInstance().GetInterFace()->EnumDevices(
		DI8DEVTYPE_JOYSTICK,
		DeviceFindCallBack,
		&parameter,
		DIEDFL_ATTACHEDONLY
	);

	// �ǂ���������邱�Ƃ��o���Ȃ������玸�s
	if (parameter.FindCount == 0) return;

	int count = 0;
	// ����J�n
	while (StartGamePadControl() == false)
	{
		Sleep(100);
		count++;
		if (count >= 5)
		{
			break;
		}
	}
}



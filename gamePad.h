/*=======================================================================================

	 �R���g���[���[����N���X[gamePad.h]
												author:MA
												date:2021/08/13
 -----------------------------------------------------------------------------------------
 ��DirectInput API �̂ݑΉ�����
 =========================================================================================*/
#pragma once
#include "directinput.h"

enum ButtonKind
{
	LStickUP,
	LStickDown,
	LStickLeft,
	LStickRight,

	RStickUP,
	RStickDown,
	RStickLeft,
	RStickRight,

	UpButton,
	DownButton,
	LeftButton,
	RightButton,

	ButtonY,
	ButtonB,
	ButtonA,
	ButtonX,

	ButtonLB,
	ButtonRB,
	ButtonLT,
	ButtonRT,

	Button_BACK,
	Button_START,
	ButtonKindMax,
};


enum ButtonState
{
	JoyStateNone,
	JoyStateDown,
	JoyStatePush,
	JoyStateUp,
	JoyStateMax,
};

//�Q�[���p�b�h�f�o�C�X�̍쐬-�f�o�C�X�񋓂̌��ʂ��󂯎��\����
struct DeviceEnumParameter
{
	LPDIRECTINPUTDEVICE8* GamePadDevice;
	int FindCount;
};

class GamePad : public Singleton<GamePad>
{
private:
	LPDIRECTINPUTDEVICE8 m_InputDevice;
	ButtonState m_JoyStates[ButtonKind::ButtonKindMax];

	BOOL StartGamePadControl();

public:
	void InitController();
	void UpdateController();
	void UninitController();

	bool JoystickPress(ButtonKind button);
	bool JoystickRelease(ButtonKind button);
	bool JoystickTrigger(ButtonKind button);

	// �Q�[���p�b�h�f�o�C�X�̍쐬
	void CreateGamePadDevice();

	const LPDIRECTINPUTDEVICE8& GetDevice(void) { return m_InputDevice; }

};




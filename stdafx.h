// stdafx.h : ���� ��������� ���� ��������� �ʴ�
// ǥ�� �ý��� ���� ���� �Ǵ� ������Ʈ ���� ���� ������
// ��� �ִ� ���� �����Դϴ�.
//

#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN             // ���� ������ �ʴ� ������ Windows ������� �����մϴ�.

// Windows ��� ����:
#include <Windows.h>
#include <mmsystem.h>
#pragma comment(lib, "msimg32.lib") 
// C ��Ÿ�� ��� �����Դϴ�.
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <time.h>
#include <string.h>
void CALLBACK TimerProc(UINT uID, UINT uMsg, DWORD dwUser, DWORD dw1, DWORD dw2);
// TODO: ���α׷��� �ʿ��� �߰� ����� ���⿡�� �����մϴ�.
#include "PlayerData.h"
#include "MessageBox.h"
#include "ClickCheck.h"
#include "Draw.h"
#include "Charock_.h"
#include "TImerFunction.h"

#pragma once
 
#define DEBUG
#define STRING_OBFUSCATOR 
 
#include <Windows.h>
#pragma warning( disable : 4244 )
#pragma warning( disable : 4996 )
#include <iostream>
#include <d3dx9.h>
#include <d3d9.h>
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#include <dwmapi.h>
#pragma comment(lib, "dwmapi.lib")	 
#include <sstream>
#include <iostream>
#include <string> 
#include <vector> 

using namespace std;
using std::stringstream;

#include "obfuscator.h" 
#include "d3d9.h"

#ifdef DEBUG 
#define printfdbg printf
#else
#define printfdbg(...) 
#endif

LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam);
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hSecInstance, LPSTR nCmdLine, INT nCmdShow);
void SetWindowToTarget();
  
int Width = GetSystemMetrics(SM_CXSCREEN);
int Height = GetSystemMetrics(SM_CYSCREEN);
const MARGINS Margin = { 0, 0, Width, Height };
int sdeltaX, sdeltaY, len, aimfov = 30, mineteam = 1, deltax, deltay,  aimsmooth = 1, 
mode = 2, tbdelaymin = 200, tbdelaymax = 300, tbdelaybetween = 20, tbdelaybetween_rand = 20;
char lWindowName[256] = " ";
HWND hWnd;
LPSTR tWindowName;
HWND tWnd;
RECT tSize, ttSize; 
WINDOWINFO winfo;
MSG Message;
RECT rc; 
DWORD scrCenterX, scrCenterY;
HDC hdc;
COLORREF pixel;
bool needaim = false;

void DisExit();
  
#include "cheat.cpp"


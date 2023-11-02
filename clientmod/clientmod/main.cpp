#pragma once
#include "main.h"
 
void DisExit() {
	Sleep(1000);
	p_Object->Release();
	_Exit(1);
}
 
void myInit() 
{
	//timeBeginPeriod(1); 
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)TriggerCheck, 0, 0, 0);
	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)Aim, 0, 0, 0);
	printfdbg("Initiated\n");
}
  
LRESULT CALLBACK WinProc(HWND hWnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_PAINT:
		//RENDER 
		if (tWnd == GetForegroundWindow())
		{
			char * value = tWindowName;

			HWND newhwnd = FindWindow(NULL, value);
			if (newhwnd != NULL) {
				GetWindowRect(newhwnd, &rc);
			}
			else {
				ExitProcess(0);
			}

			p_Device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
			p_Device->BeginScene();

			myDraw();

			p_Device->EndScene();
			p_Device->Present(NULL, NULL, NULL, NULL);
		}
		else
		{
			p_Device->Clear(0, 0, D3DCLEAR_TARGET, 0, 1.0f, 0);
			p_Device->BeginScene();

			p_Device->EndScene();
			p_Device->PresentEx(0, 0, 0, 0, 0);
		}
		
		break;

	case WM_CREATE: 
	{
		DwmExtendFrameIntoClientArea(hWnd, &Margin);
		    
		printf(AY_OBFUSCATE("horizon external cheat   \n")); 
		printf(AY_OBFUSCATE("0.1 update - pixel aimbot\n"));
		printf(AY_OBFUSCATE("================================================================\n"));

		for (HWND hwnd = GetTopWindow(NULL); hwnd != NULL; hwnd = GetNextWindow(hwnd, GW_HWNDNEXT))
		{ 
			if (!IsWindowVisible(hwnd)) continue;
			 
			int length = GetWindowTextLength(hwnd);  
			if (length == 0)
				continue;
			 
			char* title = new char[length + 1];  
			GetWindowText(hwnd, title, length + 1);  

			std::cout << AY_OBFUSCATE("HWND: ") << dec << (int)hwnd << AY_OBFUSCATE(" Title: ") << title << ";" << std::endl;  
		}

		printf(AY_OBFUSCATE("\nPlease type HWND (number) of game window.\n"));  

		int wid;  
		cin >> wid;   
		len = GetWindowTextLength((HWND)wid);  
		hdc = GetDC((HWND)wid);

		char* wname = new char[len + 1];  
		GetWindowText((HWND)wid, wname, len + 1);  
		tWindowName = const_cast<LPSTR>(wname);
		 
		printf(AY_OBFUSCATE("You took HWID %d named \"%s\"\n"), wid, tWindowName);  
		printf(AY_OBFUSCATE("Useful console commands: cl_ragdoll_physics_enable 0; violence_hblood 0\n"));
		 
		myInit();  

	}
		break;

	case WM_DESTROY: 
		PostQuitMessage(1);  
		return 0;

	default:
		return DefWindowProc(hWnd, Message, wParam, lParam);
		break;
	}
	return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hSecInstance, LPSTR nCmdLine, INT nCmdShow)
{
	AllocConsole();
	freopen("conin$", "r", stdin);
	freopen("conout$", "w", stdout);
	freopen("conout$", "w", stderr);

	CreateThread(0, 0, (LPTHREAD_START_ROUTINE)SetWindowToTarget, 0, 0, 0);

	WNDCLASSEX wClass;
	wClass.cbClsExtra = NULL;
	wClass.cbSize = sizeof(WNDCLASSEX);
	wClass.cbWndExtra = NULL;
	wClass.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(0, 0, 0));
	wClass.hCursor = LoadCursor(0, IDC_ARROW);
	wClass.hIcon = LoadIcon(0, IDI_APPLICATION);
	wClass.hIconSm = LoadIcon(0, IDI_APPLICATION);
	wClass.hInstance = hInstance;
	wClass.lpfnWndProc = WinProc;
	wClass.lpszClassName = lWindowName;
	wClass.lpszMenuName = lWindowName;
	wClass.style = CS_VREDRAW | CS_HREDRAW;

	if (!RegisterClassEx(&wClass))
		exit(1);
	 
	hWnd = CreateWindowEx(WS_EX_TOPMOST | WS_EX_TRANSPARENT | WS_EX_NOACTIVATE | WS_EX_LAYERED, lWindowName, lWindowName, WS_POPUP, 1, 1, Width, Height, 0, 0, 0, 0);
	SetLayeredWindowAttributes(hWnd, 0, 1.0f, LWA_ALPHA);
	SetLayeredWindowAttributes(hWnd, 0, RGB(0, 0, 0), LWA_COLORKEY);
	ShowWindow(hWnd, SW_SHOW);
	 
	DirectXInit(hWnd);

	for (;;)
	{
		if (PeekMessage(&Message, hWnd, 0, 0, PM_REMOVE))
		{
			DispatchMessage(&Message);
			TranslateMessage(&Message);
		}
		Sleep(1);
	}
	return 0;
}

void SetWindowToTarget()
{
	while (true)
	{
		tWnd = FindWindow(0, tWindowName);

		if (tWnd)
		{
			GetWindowRect(tWnd, &tSize);   
  
			DWORD dwStyle = GetWindowLong(tWnd, GWL_STYLE);  
			if (dwStyle & WS_BORDER)
			{
				GetClientRect(tWnd, &ttSize);
				GetWindowInfo(tWnd, &winfo);
				
				sdeltaX = ((tSize.right - tSize.left) - ttSize.right) / 2;
				sdeltaY = GetSystemMetrics(SM_CYCAPTION) + winfo.cyWindowBorders;
  
				tSize.top += sdeltaY;
				tSize.left += sdeltaX;

				Height = ttSize.bottom;
				Width = ttSize.right;
			}
			else
			{
				Width = tSize.right - tSize.left;  
				Height = tSize.bottom - tSize.top;  
			}

			scrCenterX = Width / 2;
			scrCenterY = Height / 2;
   
			MoveWindow(hWnd, tSize.left, tSize.top, Width, Height, true);  
		}
		else
		{ 
			exit(1);  
		}
		Sleep(1);  
	}
}

#define WINVER 0x0500
#define ID_TIME 1
#include <windows.h>
#include "sysmets.h"


LRESULT CALLBACK WndProc(HWND,UINT,WPARAM,LPARAM);

int WINAPI WinMain(HINSTANCE hlnstance,HINSTANCE hPrevlnstance,
				   PSTR szCmdLine,int iCmdShow)
{
	static TCHAR AppName[]=TEXT("TextShow");
	HWND hwnd;
	MSG msg;
	WNDCLASS wndclass;
	wndclass.style             =CS_HREDRAW | CS_VREDRAW;
	wndclass.lpfnWndProc       =WndProc;
	wndclass.cbClsExtra        =0;
	wndclass.cbWndExtra        =0;
	wndclass.hInstance         =hlnstance;
	wndclass.hIcon             =LoadIcon(NULL,IDI_APPLICATION);
	wndclass.hCursor           =LoadCursor(NULL,IDC_ARROW);
	wndclass.hbrBackground     =(HBRUSH)GetStockObject(WHITE_BRUSH);
	wndclass.lpszMenuName      =NULL;
	wndclass.lpszClassName     =AppName;

	if(!RegisterClass(&wndclass))
	{
		MessageBox(NULL,TEXT("what a rubbish computer!"),
			AppName,MB_ICONERROR);
		return 0;
	}

	hwnd=CreateWindow(AppName,TEXT("text out"),
		WS_OVERLAPPEDWINDOW ,//| WS_VSCROLL,
		CW_USEDEFAULT,CW_USEDEFAULT,
		CW_USEDEFAULT,CW_USEDEFAULT,
		NULL,NULL,hlnstance,NULL);

	ShowWindow(hwnd,iCmdShow);
	UpdateWindow(hwnd);

	while(GetMessage(&msg,NULL,0,0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd ,UINT message,WPARAM wParam,LPARAM lParam)
{
	static int cxChar,cxCaps,cyChar,cyClient,iVscrollPos,iVscrollMax;
	int i,y;
	HBRUSH hBrush;
	HDC hdc;
	PAINTSTRUCT ps;
	TCHAR  SzBuffer[10];
	TEXTMETRIC tm;
	RECT rc;

	switch(message)
	{
	case WM_CREATE:
		hdc=GetDC(hwnd);
		SetTimer(hwnd,ID_TIME,300,NULL);
		GetTextMetrics(hdc,&tm);
		cxChar=tm.tmAveCharWidth;
		cxCaps=(tm.tmPitchAndFamily&1?3:2)*cxChar/2;
		cyChar=tm.tmHeight+tm.tmExternalLeading;
		iVscrollMax=max(0,NUMLINES-1);
		ReleaseDC(hwnd,hdc);
	//	SetScrollRange(hwnd,SB_VERT,0,iVscrollMax,FALSE);
	//	SetScrollPos(hwnd,SB_VERT,iVscrollPos,TRUE);
		return 0;
	case WM_SIZE:
		cyClient=HIWORD(lParam);
		return 0;
	case WM_TIMER:
		if(iVscrollPos<iVscrollMax)
			iVscrollPos++;
		else
		{
			iVscrollPos=0;
			MessageBeep(-1);
		}
		InvalidateRect(hwnd,NULL,FALSE);
		return 0;
	/*
	case WM_VSCROLL:
		switch(LOWORD(wParam))
		{
		case SB_LINEUP:
			iVscrollPos-=1;
			break;
		case SB_LINEDOWN:
			iVscrollPos+=1;
			break;
		case SB_PAGEUP:
			iVscrollPos-=cyClient/cyChar;
			break;
		case SB_PAGEDOWN:
			iVscrollPos+=cyClient/cyChar;
			break;
		case SB_THUMBPOSITION:
			iVscrollPos=HIWORD(wParam);
			break;
		default:
			break;
		}
		iVscrollPos=max(0,min(iVscrollPos,iVscrollMax));
		if(iVscrollPos!=GetScrollPos(hwnd,SB_VERT))
		{
			SetScrollPos(hwnd,SB_VERT,iVscrollPos,TRUE);
			InvalidateRect(hwnd,NULL,TRUE);
		}
		return 0;
	*/
	case WM_PAINT:
		hdc = BeginPaint(hwnd,&ps);
		GetClientRect (hwnd, &rc);
		hBrush = (HBRUSH)GetStockObject (WHITE_BRUSH) ;
		SelectObject (hdc, hBrush);
		FillRect (hdc, &rc, hBrush);
		for(i=0;i<NUMLINES;i++)
		{
			y=i-iVscrollPos;

			TextOut(hdc,0,cyChar*y,
				sysmetrics[i].szLabel,
				lstrlen(sysmetrics[i].szLabel));
			TextOut(hdc,22*cxCaps,cyChar*y,
				sysmetrics[i].szDesc,
				lstrlen(sysmetrics[i].szDesc));

			SetTextAlign(hdc,TA_RIGHT | TA_TOP);

			TextOut(hdc,20*cxCaps+40*cxChar,cyChar*y,SzBuffer,
				wsprintf(SzBuffer,TEXT("%5d"),
				GetSystemMetrics(sysmetrics[i].ilndex)));
			
			SetTextAlign(hdc,TA_LEFT | TA_TOP);
		}
		EndPaint(hwnd,&ps);
		return 0;
	case WM_DESTROY:
		KillTimer(hwnd,ID_TIME);
		PostQuitMessage(0);
		return 0;
	}
	return DefWindowProc(hwnd,message,wParam,lParam);
}






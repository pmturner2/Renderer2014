/** Main.cpp - Entry point for application. Handles interface with OS
 *    Current Implementation: Windows 32. Handles win messages.
 *    Has a Game object which handles all Game-related logic/processing.
 *  Peter Turner - Summer 2012
 */
#include "Game.h"
#include "stdafx.h"
//#include "Game.h"
#include "resource.h"
#include "gl/renderer_gl.h"
#include "Logger.h"


//#include <GL/glut.h>

#define MAX_LOADSTRING 100

Game game;

#ifdef GL
Renderer_GL renderer;
#else
Renderer_DX11 renderer;
#endif

// Global Variables:
LONG screenHeight = (long)GetSystemMetrics(SM_CYSCREEN);
LONG screenWidth = (long)GetSystemMetrics(SM_CXSCREEN); 

bool fullScreen = true;

HINSTANCE hInst;                        // current instance
HWND hWnd = NULL;
TCHAR szTitle[MAX_LOADSTRING];               // The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];         // the main window class name

// Forward declarations of functions included in this code module:
ATOM            MyRegisterClass(HINSTANCE hInstance);
BOOL            InitInstance(HINSTANCE, int);
LRESULT CALLBACK   WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK   About(HWND, UINT, WPARAM, LPARAM);
bool resizing = false;
Logger logger;

int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
   UNREFERENCED_PARAMETER(hPrevInstance);
   UNREFERENCED_PARAMETER(lpCmdLine);
   logger.Open("output.log");
   renderer.SetLogger(&logger);
   game.logger = &logger;//.SetLogger(&logger);
   game.SetRenderer( &renderer );

   MSG msg = {0};
   HACCEL hAccelTable;

   // Initialize global strings
  // LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
   LoadString(hInstance, IDS_STRING101, szWindowClass, MAX_LOADSTRING);
   if (!MyRegisterClass(hInstance)) {
      return FALSE;
   }

   // Perform application initialization:
   if (!InitInstance (hInstance, nCmdShow))
   {
      DWORD x = GetLastError();
      return FALSE;
   }

  // hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_D3DGAME));
   
  // game.Init(hWnd, screenWidth, screenHeight);

   // Main message loop:   
   while (msg.message != WM_QUIT)
   {
      //if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
      if (PeekMessage(&msg, 0, 0, 0, PM_REMOVE))
      {
         TranslateMessage(&msg);
         DispatchMessage(&msg);
      } else {		
         game.Update();
      }
   }

   return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	/*
   WNDCLASSEX wcex;

   wcex.cbSize = sizeof(WNDCLASSEX);
   wcex.style         = CS_HREDRAW | CS_VREDRAW;
   wcex.lpfnWndProc   = WndProc;
   wcex.cbClsExtra      = 0;
   wcex.cbWndExtra      = 0;
   wcex.hInstance      = hInstance;
   wcex.hIcon         = LoadIcon(0, IDI_APPLICATION);//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_D3DGAME));
   wcex.hCursor      = LoadCursor(0, IDC_ARROW);//LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1)); //LoadCursor(NULL, IDC_CURSOR1); /
   wcex.hbrBackground   = (HBRUSH)(COLOR_WINDOW+1);
   wcex.lpszMenuName   =  NULL;//szWindowClass;// MAKEINTRESOURCE(IDC_D3DGAME);
   wcex.lpszClassName   = L"ClassName";//szWindowClass;
 //  wcex.hIconSm      = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));
 */
	
   WNDCLASS wcex;

 //  wcex.cbSize = sizeof(WNDCLASSEX);
    wcex.style         = CS_HREDRAW | CS_VREDRAW;
#ifdef GL
   // For OpenGL Context, use this style
   wcex.style |= CS_OWNDC;
#endif
   wcex.lpfnWndProc   = WndProc;
   wcex.cbClsExtra      = 0;
   wcex.cbWndExtra      = 0;
   wcex.hInstance      = hInstance;
   wcex.hIcon         = LoadIcon(0, IDI_APPLICATION);//LoadIcon(hInstance, MAKEINTRESOURCE(IDI_D3DGAME));
   wcex.hCursor      = LoadCursor(0, IDC_ARROW);//LoadCursor(hInstance, MAKEINTRESOURCE(IDC_CURSOR1)); //LoadCursor(NULL, IDC_CURSOR1); /
   wcex.hbrBackground   = (HBRUSH)(COLOR_WINDOW+1);
   wcex.lpszMenuName   =  NULL;//szWindowClass;// MAKEINTRESOURCE(IDC_D3DGAME);
   wcex.lpszClassName   = szWindowClass;
   if (! RegisterClass(&wcex))
   {
	   return false;
   }
   
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{  

   hInst = hInstance; // Store instance handle in our global variable

   //(1) hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
   //  CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);
   //(2) hWnd = CreateWindowEx(WS_EX_TOPMOST, szTitle, szTitle, WS_POPUP,
   //   0, 0, screenWidth, screenHeight, NULL, NULL, hInstance, NULL);
   /*
   RECT rc = { 0, 0, screenWidth, screenHeight };
   AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
   hWnd = CreateWindow( L"TutorialWindowClass", L"Direct3D 10 Tutorial 2: Rendering a Triangle", WS_OVERLAPPEDWINDOW,
      0, 0, screenWidth, screenHeight, NULL, NULL, hInstance, NULL );
      */
    //g_hInst = hInstance;
   RECT rc = { 0, 0, screenWidth, screenHeight };

   int bits = 16;
   if (fullScreen)
   {
	   // From NeHe.. Full Screen.
	   DEVMODE dmScreenSettings;                   // Device Mode
	   memset(&dmScreenSettings,0,sizeof(dmScreenSettings));       // Makes Sure Memory's Cleared
	   dmScreenSettings.dmSize=sizeof(dmScreenSettings);       // Size Of The Devmode Structure
	   dmScreenSettings.dmPelsWidth    = screenWidth;            // Selected Screen Width
	   dmScreenSettings.dmPelsHeight   = screenHeight;           // Selected Screen Height
	   dmScreenSettings.dmBitsPerPel   = bits;             // Selected Bits Per Pixel
	   dmScreenSettings.dmFields=DM_BITSPERPEL|DM_PELSWIDTH|DM_PELSHEIGHT;

	   //LONG result = 
	   if (ChangeDisplaySettings(&dmScreenSettings,CDS_FULLSCREEN)!=DISP_CHANGE_SUCCESSFUL)
	   {
			fullScreen = false;
			AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
			hWnd = CreateWindow( szWindowClass, szTitle,
                           WS_OVERLAPPEDWINDOW,
                           CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
                           NULL );

	   }
	   else
	   {
		    DWORD       dwExStyle;                      // Window Extended Style
			DWORD       dwStyle;                        // Window Style
			dwExStyle=WS_EX_APPWINDOW;                  // Window Extended Style
			dwStyle=WS_POPUP;                       // Windows Style
			ShowCursor(FALSE);                      // Hide Mouse Pointer
			AdjustWindowRectEx(&rc, dwStyle, FALSE, dwExStyle);
			hWnd = CreateWindowEx( dwExStyle, szWindowClass, szTitle,
                            WS_CLIPSIBLINGS |           // Required Window Style
							WS_CLIPCHILDREN |           // Required Window Style
							dwStyle, 
                           0, 0, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
                           NULL );
	   }
   }
   else
   {
	   fullScreen = false;
		AdjustWindowRect( &rc, WS_OVERLAPPEDWINDOW, FALSE );
		hWnd = CreateWindow( szWindowClass, szTitle,
						WS_OVERLAPPEDWINDOW,
						CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left, rc.bottom - rc.top, NULL, NULL, hInstance,
						NULL );
   }

    
    
   
   if (!hWnd)
   {
      return FALSE;
   }
   ShowCursor(false);
   SetCursorPos(100, 100);
   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND   - process the application menu
//  WM_PAINT   - Paint the main window
//  WM_DESTROY   - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
   int wmId, wmEvent;
   PAINTSTRUCT ps;
   HDC hdc;
   float xPos, yPos;
   switch (message)
   {
   case WM_CREATE:
	   
        hdc = GetDC(hWnd);

		if (!renderer.Init(hWnd, hdc))
		{
			ShowCursor(true);
			//MessageBoxA(0,(char*)glGetString(GL_VERSION), "OPENGL VERSION",0);
			logger.Write("Unable to create Rendering Context - Error Initializing Renderer\n");
			MessageBoxA(0,"Unable to create Rendering Context", "Error Initializing Renderer",0);
			PostQuitMessage(0);
		}
		ShowCursor(false);
		renderer.SetupScene();
		break;
   case WM_MOUSEMOVE:
      xPos = LOWORD(lParam);
      yPos = HIWORD(lParam);
	  
      if (fabs(xPos - 100.0f) < 0.01f && fabs(yPos - 100.0f) < 0.01f) { // prevent inf loop. probably more efficient way to handle this.
         break;
      }
      game.MouseMove(xPos, yPos);
      
	  SetCursorPos(100, 100); // so we never hit a screen edge.
      break;
   case WM_ENTERSIZEMOVE:
      //game.Pause();
      resizing  = true;
      break;

   // WM_EXITSIZEMOVE is sent when the user releases the resize bars.
   // Here we reset everything based on the new window dimensions.
   case WM_EXITSIZEMOVE:
      //game.Resume();
      resizing  = false;      
     // game.OnResize(screenWidth, screenHeight);
      return 0;
   case WM_ACTIVATE:     
      if (LOWORD(wParam) == WA_INACTIVE) {
        // game.Pause();         
      } else {
        // game.Resume();         
      }
      break;
   case WM_KEYDOWN:
      switch (wParam) {
		  // Short VK_A..VK_Z, etc.
      case VK_ESCAPE:
         ShowCursor(true);
         PostQuitMessage(0);
         break;
      case 'W':
      case 'w':         
			game.UpdateMovement(1.0f, 0.0f);
         break;
      case 'S':
      case 's':
			game.UpdateMovement(-1.0f, 0.0f);
         break;
	  case 'A':
      case 'a':
			game.UpdateMovement(0.0f, 1.0f);
         break;
		  
	  case 'D':
      case 'd':
			game.UpdateMovement(0.0f, -1.0f);
         break;
      case VK_ADD:
        // game.SetSpeed(game.GetSpeed() * 2);
         break;
      case VK_SUBTRACT:
      //   if (game.GetSpeed() > 1) {
      //      game.SetSpeed(game.GetSpeed() / 2);
      //   }
         break;
      }
      
      break;
   case WM_COMMAND:
      wmId    = LOWORD(wParam);
      wmEvent = HIWORD(wParam);
      // Parse the menu selections:
      switch (wmId)
      {
		  /*
      case IDM_ABOUT:
         DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
         break;
      case IDM_EXIT:
         DestroyWindow(hWnd);
         break;*/
      default:
         return DefWindowProc(hWnd, message, wParam, lParam);
      }
      break;
   case WM_PAINT:
      hdc = BeginPaint(hWnd, &ps);
      EndPaint(hWnd, &ps);
      break;
   case WM_DESTROY:
#ifdef GL
	   //wglMakeCurrent (hdc, NULL);
	   //wglDeleteContext(ourOpenGLRenderingContext);
#endif
      ShowCursor(true);
      PostQuitMessage(0);
      break;
   case WM_SIZE:
      // Save the new client area dimensions.
      screenWidth  = LOWORD(lParam);
      screenHeight = HIWORD(lParam);
           
      ShowCursor(true);
	  renderer.ReshapeWindow(screenWidth, screenHeight);

      /*
      if( wParam == SIZE_MINIMIZED )
      {
         game.Pause();
      
      }
      else if( wParam == SIZE_MAXIMIZED )
      {
         game.OnResize(screenWidth, screenHeight);
         game.Resume();
      }
      else if( wParam == SIZE_RESTORED )
      {
         game.OnResize(screenWidth, screenHeight);
         game.Resume();
      }
      else if( resizing )
      {
               // If user is dragging the resize bars, we do not resize 
               // the buffers here because as the user continuously 
               // drags the resize bars, a stream of WM_SIZE messages are
               // sent to the window, and it would be pointless (and slow)
               // to resize for each WM_SIZE message received from dragging
               // the resize bars.  So instead, we reset after the user is 
               // done resizing the window and releases the resize bars, which 
               // sends a WM_EXITSIZEMOVE message.
            }
      else // API call such as SetWindowPos or mSwapChain->SetFullscreenState.
      {
         game.OnResize(screenWidth, screenHeight);
      }*/
      break;
   default:
      return DefWindowProc(hWnd, message, wParam, lParam);
   }
   return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
   UNREFERENCED_PARAMETER(lParam);
   switch (message)
   {
   case WM_INITDIALOG:
      return (INT_PTR)TRUE;

   case WM_COMMAND:
      if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
      {
         EndDialog(hDlg, LOWORD(wParam));
         return (INT_PTR)TRUE;
      }
      break;
   }
   return (INT_PTR)FALSE;
}


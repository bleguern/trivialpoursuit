/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* config.cpp : Contient les méthodes nécessaires à     */
/* la configuration du programme.                       */
/********************************************************/

#include "Config.h"


//Charge les valeurs par défaut
void Config::LoadDefault()
{
	screen_width = 640;
	screen_height = 480;
	screen_bpp = 16;
	fullscreen = FALSE;

	gouraud_shading = TRUE;

	view_depth = 10000.0f;
	
	nb_players = 2;
	sec_to_answer = 30;
}

//Initialise OpenGL
bool Config::Init()
{
	FILE *fd;
	unsigned int i;

	if((fd = fopen(CONFIG_FILE, "r")) == NULL)
	{
		LoadDefault();
	}
	else
	{
		fscanf(fd, "[screen properties]\nscreen_width=%i\nscreen_height=%i\nscreen_bpp=%i\nfullscreen=%i\n\n[graphics option]\ngouraud_shading=%i\nview_depth=%f\n\n[game option]\nnb_players=%i\nsec_to_answer=%i\n",
			&screen_width, &screen_height, &screen_bpp, &fullscreen, &gouraud_shading, &view_depth, &nb_players, &sec_to_answer);

		if(nb_players < MAX_PLAYERS+1)
		{
			for(i = 0; i < nb_players; i++)
			{
				fscanf(fd, "%s\n", players[i].name);
			}
		}
		else
		{
			return FALSE;
		}
		
		fclose(fd);
	}

	hWnd = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_INIT), NULL, (DLGPROC) InitProc);
	
	ShowWindow(hWnd, nCmdShow);

	SetFocus(hWnd);
	
	return TRUE;
}

//Lance le jeu
bool Config::Launch()
{
	coef_x = float(screen_width)/1600;
	coef_y = float(screen_height)/1200;

	hWC.cbSize = sizeof(hWC);
	hWC.style = CS_HREDRAW|CS_VREDRAW|CS_OWNDC;
	hWC.lpfnWndProc = (WNDPROC) WndProc;
	hWC.cbClsExtra = 0;
	hWC.cbWndExtra = 0;
	hWC.hInstance = hInstance;
	hWC.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	hWC.hCursor = LoadCursor(NULL, IDC_CROSS);
	hWC.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	hWC.lpszMenuName = NULL;
	hWC.lpszClassName = "TrivialWndClass";
	hWC.hIconSm = NULL;

	if(!RegisterClassEx(&hWC))
	{
		Warning("RegisterClass error\n", sizeof("RegisterClass error\n"));
		return FALSE;
	}

	if(fullscreen && !dwStyle)
	{
		dwStyle = WS_POPUP|WS_VISIBLE;
		ChangeToFullScreen();
	}
	else if(!dwStyle)
		dwStyle = WS_TILED|WS_SYSMENU|WS_VISIBLE;


	hWnd = CreateWindow("TrivialWndClass",
					    "Trivial Poursuit v1.0a - (C) 2003 GummiTeam!",
					    dwStyle,
					    0, 0,
					    screen_width + WINDOW_WIDTH_DELTA,
						screen_height + WINDOW_HEIGHT_DELTA,
					    HWND_DESKTOP,
					    (HMENU) NULL,
					    hInstance,
					    (LPVOID) NULL);

	if(!hWnd)
	{
		Warning("hWnd error\n", sizeof("hWnd error\n"));
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow); 
    //UpdateWindow(hWnd);

	SetFocus(hWnd);

	hDC = GetDC(hWnd);
	SetupPixelFormat(hDC);
	hRC = wglCreateContext(hDC);
	wglMakeCurrent(hDC, hRC);

	Init_GL();

	return TRUE;
}



//Enregistre la configuration
bool Config::Save()
{
	FILE* fd;
	unsigned int i;

	if((fd = fopen(CONFIG_FILE, "w")) == NULL)
	{
		return FALSE;
	}

	fprintf(fd, "[screen properties]\nscreen_width=%i\nscreen_height=%i\nscreen_bpp=%i\nfullscreen=%i\n\n[graphics option]\ngouraud_shading=%i\nview_depth=%.2f\n\n[game option]\nnb_players=%i\nsec_to_answer=%i\n",
			screen_width, screen_height, screen_bpp, fullscreen, gouraud_shading, view_depth, nb_players, sec_to_answer);

	for(i = 0; i < nb_players; i++)
	{
		fprintf(fd, "%s\n", players[i].name);
	}


	fclose(fd);

	return TRUE;
}



//Quitte le programme
void Config::Quit()
{
	if(hRC)
	{
		wglMakeCurrent(NULL, NULL);
		wglDeleteContext(hRC);	
	}
	
	if(hDC)
		ReleaseDC(hWnd, hDC);
		
	if(fullscreen)
	{
		ChangeDisplaySettings(NULL,0);
		ShowCursor(TRUE);
	}

	DestroyWindow(hWnd);

	UnregisterClass("TrivialWndClass", hInstance);

	PostQuitMessage(0);
}

//Initialise OpenGL
bool Config::Init_GL()
{
	Vector4 lightPosition;
	lightPosition.x = 0.0f;
	lightPosition.y = 0.0f;
	lightPosition.z = 300.0f;
	lightPosition.t = 1.0f;

	SizeOpenGLScreen();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	glLightfv(GL_LIGHT0, GL_POSITION, lightPosition);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glEnable(GL_COLOR_MATERIAL);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	return TRUE;
}

//Redimensionne l'affichage OpenGL
void Config::SizeOpenGLScreen()
{
	if(screen_height == 0)
	{
		screen_height = 1;
	}

	glViewport(0, 0, screen_width, screen_height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	gluPerspective(45.0f, (GLfloat)screen_width/(GLfloat)screen_height, 0.1f, view_depth);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}




//Change pour un mode plein écran
bool Config::ChangeToFullScreen()
{
	DEVMODE dmSettings;

	memset(&dmSettings, 0, sizeof(dmSettings));
	dmSettings.dmSize = sizeof(dmSettings);

	if(!EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dmSettings))
	{
		Warning("Could Not Enum Display Settings\n", sizeof("Could Not Enum Display Settings\n"));
		return FALSE;
	}

	dmSettings.dmPelsWidth	= screen_width;
	dmSettings.dmPelsHeight	= screen_height;
	dmSettings.dmBitsPerPel = screen_bpp;
		

	if(ChangeDisplaySettings(&dmSettings, CDS_FULLSCREEN) != DISP_CHANGE_SUCCESSFUL)
	{
		Warning("Display Mode Not Compatible\n", sizeof("Display Mode Not Compatible\n"));
		ChangeDisplaySettings(NULL,0);
		return FALSE;
	}

	return TRUE;
}
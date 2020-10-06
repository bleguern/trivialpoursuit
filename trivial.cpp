/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* trivial.cpp : Fichier principal du programme.        */
/* Contient la fonction : WinMain()                     */
/********************************************************/

#include "trivial.h"

#include "error.h"

#include "config.h"
#include "scene.h"
#include "mouse.h"



//Objetxs globaux
Config config;  //Configuration
Scene scene;    //Scene
Mouse mouse;    //Souris

//Fonction principale
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	config.hInstance = hInstance;
	config.nCmdShow = nShowCmd;

	srand((unsigned)time(NULL));

	if(!config.Init())
	{
		Warning("Init error\n", sizeof("Init error\n"));
		return FALSE;
	}

	return MainLoop();
}

//Boucle de jeu
WPARAM MainLoop()
{
	while(1)
	{
		if(PeekMessage(&config.uMsg, NULL, 0, 0, PM_REMOVE)) 
        {
			if(config.uMsg.message == WM_QUIT)
				break;

            TranslateMessage(&config.uMsg);
            DispatchMessage(&config.uMsg);
        }
		else
		{
			if(scene.loaded)
			{
				if(mouse.r_click)
				{
					scene.camera.MouseMove(config, mouse);
				}

				scene.Draw(config, mouse);
				SwapBuffers(config.hDC);
			}
        }
	}

	config.Quit();

	return(config.uMsg.wParam);
}

//Procédure de programme
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch(uMsg)
    {
		case WM_DESTROY:
			config.Quit();
			break;
		case WM_CLOSE:
			config.Quit();
			break;
		case WM_KEYDOWN:
			switch(wParam)
			{
				case VK_ESCAPE:
					config.Quit();
					break;
				case VK_PRIOR:
					scene.camera.Move(ZOOM_IN);
					break;
				case VK_NEXT:
					scene.camera.Move(ZOOM_OUT);
					break;
				case VK_UP:
					scene.camera.MoveAround(MOVE_UP);
					break;
				case VK_DOWN:
					scene.camera.MoveAround(MOVE_DOWN);
					break;
				case VK_RIGHT:
					scene.camera.MoveAround(MOVE_RIGHT);
					break;
				case VK_LEFT:
					scene.camera.MoveAround(MOVE_LEFT);
					break;
				default:
					break;
			}
			break;
		case WM_RBUTTONDOWN:
			mouse.r_click = TRUE;
			break;
		case WM_RBUTTONUP:
			mouse.r_click = FALSE;
			break;
		case WM_LBUTTONDOWN:
			mouse.l_click = TRUE;
			if(config.game_status == GAME_STATUS_POSITION)
			{
				scene.board.selected_square = scene.GetSelected(config, mouse);
			}
			break;
		case WM_LBUTTONUP:
			mouse.l_click = FALSE;
			break;
		case WM_MOUSEMOVE:
			if(!mouse.r_click)
			{
				mouse.x = LOWORD(lParam);
				mouse.y = HIWORD(lParam);
			}
			break;
        default:
            return DefWindowProc(hWnd, uMsg, wParam, lParam);
			break;
    }

	return FALSE;
}


//Procédure de la boite de dialogue initiale
LRESULT CALLBACK InitProc(HWND hDlg, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	HWND hInitControl;

	unsigned int res, sec, i, tmp_nb;
	bool bpp;
	char tmp_str[2];

	switch(uMsg) 
    {
	case WM_INITDIALOG:
		{
			SetWindowPos(hDlg, HWND_TOP, 320, 240, 0, 0, SWP_NOSIZE);

			switch(config.screen_width)
			{
			case 640:
				res = 0;
				break;
			case 800:
				res = 1;
				break;
			case 1024:
				res = 2;
				break;
			case 1280:
				res = 3;
				break;
			case 1600:
				res = 4;
				break;
			default:
				res = 1;
				break;
			}

			switch(config.screen_bpp)
			{
			case 16:
				bpp = FALSE;
				break;
			case 32:
				bpp = TRUE;
				break;
			default:
				bpp = FALSE;
				break;
			}

			switch(config.sec_to_answer)
			{
			case 10:
				sec = 0;
				break;
			case 20:
				sec = 1;
				break;
			case 30:
				sec = 2;
				break;
			case 60:
				sec = 3;
				break;
			default:
				sec = 2;
				break;
			}

			hInitControl = GetDlgItem(hDlg, IDC_INIT_RES);
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "640x480");
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "800x600");				
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "1024x768");
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "1280x1024");
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "1600x1200");
			SendMessage(hInitControl, CB_SETCURSEL, res, 0);

			hInitControl = GetDlgItem(hDlg, IDC_INIT_BPP);
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "16 Bpp");
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "32 Bpp");
			SendMessage(hInitControl, CB_SETCURSEL, bpp, 0);

			hInitControl = GetDlgItem(hDlg, IDC_INIT_NB_PLAYERS);
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "2");
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "3");
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "4");
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "5");
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "6");
			SendMessage(hInitControl, CB_SETCURSEL, config.nb_players-2, 0);

			hInitControl = GetDlgItem(hDlg, IDC_INIT_SEC_TO_ANSWER);
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "Warrior : 10");
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "Petit : 20");
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "Moyen : 30");
			SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) "Mode naze : 60");
			SendMessage(hInitControl, CB_SETCURSEL, sec, 0);




			hInitControl = GetDlgItem(hDlg, IDC_INIT_PLAYER_ID);
			for(i = 1; i < config.nb_players+1; i++)
			{
				itoa(i, tmp_str, 10);
				SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) tmp_str);
			}
			SendMessage(hInitControl, CB_SETCURSEL, 0, 0);

			hInitControl = GetDlgItem(hDlg, IDC_INIT_PLAYER_NAME);
			SendMessage(hInitControl, EM_SETLIMITTEXT, MAX_NAME_LENGTH, 0);
			SendMessage(hInitControl, WM_SETTEXT, 0, (LONG) (LPSTR) config.players[config.active_player].name);

			CheckDlgButton(hDlg, IDC_INIT_FULLSCREEN, config.fullscreen);
			CheckDlgButton(hDlg, IDC_INIT_GOURAUD, config.gouraud_shading);

			break;
		}
	case WM_COMMAND:
		{
			switch (LOWORD(wParam)) 
			{
			case ID_INIT_SAVE:
				if(!config.Save())
				{
					Warning("Saving error\n", sizeof("Saving error\n"));
					return FALSE;
				}
				break;
			case ID_INIT_LAUNCH:
				EndDialog(config.hWnd, wParam);
				if(!config.Launch())
				{
					Warning("Launch error\n", sizeof("Launch error\n"));
					return FALSE;
				}
				if(!scene.Load(config))
				{
					Warning("Load error\n", sizeof("Load error\n"));
					return FALSE;
				}
				break;
			case ID_INIT_QUIT:
				config.Quit();
				break;
			case ID_INIT_ABOUT:
				MessageBox(HWND_DESKTOP, "Trivial Poursuit v1.0a - (C) 2003 GummiTeam!\nContact:\nbenoit.leguern@supinfo.com\nyounece.aliouche@supinfo.com\nmarc.ollendorf@supinfo.com", "About", MB_ICONINFORMATION | MB_OK);
				break;
			case IDC_INIT_FULLSCREEN:
				config.fullscreen = !config.fullscreen;
				break;
			case IDC_INIT_GOURAUD:
				config.gouraud_shading = !config.gouraud_shading;
				break;
			case IDC_INIT_RES:
				hInitControl = GetDlgItem(hDlg, IDC_INIT_RES);
				switch(SendMessage(hInitControl, CB_GETCURSEL, 0, 0))
				{
				case 0:
					config.screen_width = 640;
					config.screen_height = 480;
					break;
				case 1:
					config.screen_width = 800;
					config.screen_height = 600;
					break;
				case 2:
					config.screen_width = 1024;
					config.screen_height = 768;
					break;
				case 3:
					config.screen_width = 1280;
					config.screen_height = 1024;
					break;
				case 4:
					config.screen_width = 1600;
					config.screen_height = 1200;
					break;
				default:
					config.screen_width = 640;
					config.screen_height = 480;
					break;
				}
				break;
			case IDC_INIT_BPP:
				hInitControl = GetDlgItem(hDlg, IDC_INIT_BPP);
				switch(SendMessage(hInitControl, CB_GETCURSEL, 0, 0))
				{
				case 0:
					config.screen_bpp = 16;
					break;
				case 1:
					config.screen_bpp = 32;
					break;
				default:
					config.screen_bpp = 16;
					break;
				}
				break;
			case IDC_INIT_NB_PLAYERS:
				hInitControl = GetDlgItem(hDlg, IDC_INIT_NB_PLAYERS);
				
				tmp_nb = SendMessage(hInitControl, CB_GETCURSEL, 0, 0);
				tmp_nb += 2;
				
				hInitControl = GetDlgItem(hDlg, IDC_INIT_PLAYER_ID);
				if(tmp_nb < config.nb_players)
				{
					for(i = config.nb_players-1; i > tmp_nb-1; i--)
					{
						SendMessage(hInitControl, CB_DELETESTRING, i, 0);
					}
				}
				else if(tmp_nb > config.nb_players)
				{
					for(i = config.nb_players+1; i < tmp_nb+1; i++)
					{
						itoa(i, tmp_str, 10);
						SendMessage(hInitControl, CB_ADDSTRING, 0, (LONG) (LPSTR) tmp_str);
					}
				}
				
				config.nb_players = tmp_nb;

				SendMessage(hInitControl, CB_SETCURSEL, 0, 0);
				config.active_player = 0;

				hInitControl = GetDlgItem(hDlg, IDC_INIT_PLAYER_NAME);
				SendMessage(hInitControl, WM_SETTEXT, 0, (LONG) (LPSTR) config.players[config.active_player].name);
				break;
			case IDC_INIT_PLAYER_ID:
				hInitControl = GetDlgItem(hDlg, IDC_INIT_PLAYER_ID);
				config.active_player = SendMessage(hInitControl, CB_GETCURSEL, 0, 0);

				hInitControl = GetDlgItem(hDlg, IDC_INIT_PLAYER_NAME);
				SendMessage(hInitControl, WM_SETTEXT, 0, (LONG) (LPSTR) config.players[config.active_player].name);
				break;
			case IDC_INIT_PLAYER_NAME_OK:
				hInitControl = GetDlgItem(hDlg, IDC_INIT_PLAYER_NAME);
				SendMessage(hInitControl, WM_GETTEXT, MAX_NAME_LENGTH, (LONG) (LPSTR) config.players[config.active_player].name);
				break;
			case IDC_INIT_SEC_TO_ANSWER:
				hInitControl = GetDlgItem(hDlg, IDC_INIT_SEC_TO_ANSWER);
				switch(SendMessage(hInitControl, CB_GETCURSEL, 0, 0))
				{
				case 0:
					config.sec_to_answer = 10;
					break;
				case 1:
					config.sec_to_answer = 20;
					break;
				case 2:
					config.sec_to_answer = 30;
					break;
				case 3:
					config.sec_to_answer = 60;
					break;
				default:
					config.sec_to_answer = 30;
					break;
				}
				break;
			default:
				break;
			}
			break;
		}
	case WM_DESTROY:
		config.Quit();
		break;
	case WM_CLOSE:
		config.Quit();
		break;
	default:
		//return DefDlgProc(hDlg, uMsg, wParam, lParam);
		break;
    }

    return FALSE;
}


//Défini le format de pixel
void SetupPixelFormat(HDC hDC)
{
	int PixelFormat;

	static PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,
		PFD_TYPE_RGBA,
		32,
		0,0,0,0,0,0,
		0,
		0,
		0,
		0,0,0,0,
		16,
		0,
		0,
		PFD_MAIN_PLANE,
		0,
		0,0,0
	};

	PixelFormat = ChoosePixelFormat(hDC, &pfd);

	SetPixelFormat(hDC, PixelFormat, &pfd);
}


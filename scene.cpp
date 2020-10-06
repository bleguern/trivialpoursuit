/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* scene.cpp : Contient les méthodes nécessaires à      */
/* la gestion de l'affichage de la scène.               */
/********************************************************/

#include "scene.h"

//Charge la scene en mémoire
bool Scene::Load(Config& config)
{
	LoadObject(config);             //Charge tous les objets de la scene
	LoadFont(config);               //Charge les polices

	config.active_player = 0;       //Le premier joueur à jouer

	loaded = TRUE;
	return loaded;
}

//Charge les polices de caractère
bool Scene::LoadFont(Config& config)
{
	HFONT hFont;

	if(!AddFontResource("data//_fontz//exmouth_.ttf"))
	{
		return FALSE;
	}

	//Génère une liste d'affichage pour chaque lettre
	font_list = glGenLists(MAX_CHARS);

	//Défini un type de caractère
	hFont = CreateFont(	(int)(FONT_HEIGHT*config.coef_y),
						0,
						0,
						0,
						FW_EXTRABOLD,
						FALSE,
						FALSE,
						FALSE,
						ANSI_CHARSET,
						OUT_TT_PRECIS,
						CLIP_DEFAULT_PRECIS,
						ANTIALIASED_QUALITY,
						FF_DONTCARE|DEFAULT_PITCH,
						"Exmouth");

	hOldFont = (HFONT)SelectObject(config.hDC, hFont);

	wglUseFontBitmaps(config.hDC, 0, MAX_CHARS - 1, font_list);

	return TRUE;
}


//Charge les objets
bool Scene::LoadObject(Config& config)
{
	display_list = glGenLists(5);
	
	board.Load(config, display_list);
	die.Load(config, DIE_DATA_FILE_PATH, DIE_TEXTURE_FILE_PATH, display_list+1);
	ground.Load(config, GROUND_DATA_FILE_PATH, display_list+2);
	pawn.Load(config, PAWN_DATA_FILE_PATH, display_list+3);
	camember.Load(config, CAMEMBER_DATA_FILE_PATH, display_list+4);

	return TRUE;
}

///Dessine la scène
void Scene::Draw(Config& config, Mouse& mouse)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	//Positionne la caméra
	gluLookAt(camera.position.x, camera.position.y, camera.position.z,
		0, 0, 0,
		0, 0, 1);

	glPushMatrix();
		glTranslatef(0.0f, -camera.distance, 0.0f);
		glRotatef(-camera.x_angle, 1.0f, 0.0f, 0.0f);
		glRotatef(camera.z_angle, 0.0f, 0.0f, 1.0f);
		
		if( (!((config.game_status == GAME_STATUS_POSITION) && mouse.l_click)) || (config.game_status == GAME_STATUS_POSITION) && ((mouse.x > ((int)config.screen_width - 98)) && (mouse.y > ((int)config.screen_height - (FONT_HEIGHT+10)))))
		{
			DrawHUD(config, mouse);
		}

		glColor3f(0.0f, 0.23f, 0.23f);
		ground.Draw();

		DrawPawn(config);
		DrawCamember(config);
		DrawDie(config);

		DrawBoard(config);
	glPopMatrix();
}


//Dessine le plateau
void Scene::DrawBoard(Config& config)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	board.Draw();
	

	if(config.game_status == GAME_STATUS_POSITION)
	{
		board.DrawVirtual();
		board.DrawPossibleSquare();
		board.DrawSelectedSquare();
	}
}

//Dessine les pions
void Scene::DrawPawn(Config& config)
{
	unsigned int i, j;

	for(i = 0; i < config.nb_players; i++)
	{
		glPushMatrix();

			for(j = config.nb_players-1; j > i; j--)
			{
				if(config.players[i].square_pos == config.players[j].square_pos)
				{
					glTranslatef(0.0f, 0.0f, 10.0f);
				}
			}

			SetPos(config.players[i].square_pos);
			
			switch(i+1)
			{
			case ORANGE:
				glColor3f(1.0f, 0.66f, 0.0f);
				break;
			case GREEN:
				glColor3f(0.0f, 0.66f, 0.0f);
				break;
			case BROWN:
				glColor3f(0.66f, 0.4f, 0.0f);
				break;
			case PINK:
				glColor3f(1.0f, 0.0f, 1.0f);
				break;
			case YELLOW:
				glColor3f(1.0f, 1.0f, 0.0f);
				break;
			case BLUE:
				glColor3f(0.0f, 1.0f, 1.0f);
				break;
			default:
				glColor3f(1.0f, 1.0f, 1.0f);
				break;
			}

			pawn.Draw();

		glPopMatrix();
	}
}


//Dessine les camembers
void Scene::DrawCamember(Config& config)
{
	unsigned int i, j, k;

	for(i = 0; i < config.nb_players; i++)
	{		
		for(j = 0; j < 6; j++)
		{
			if(config.players[i].camember[j])
			{
				glPushMatrix();
				
					for(k = config.nb_players-1; k > i; k--)
					{
						if(config.players[i].square_pos == config.players[k].square_pos)
						{
							glTranslatef(0.0f, 0.0f, 10.0f);
						}
					}

					SetPos(config.players[i].square_pos);

					glRotatef((GLfloat)60*j, 0.0f, 0.0f, 1.0f);

					switch(j+1)
					{
					case ORANGE:
						glColor3f(1.0f, 0.66f, 0.0f);
						break;
					case GREEN:
						glColor3f(0.0f, 0.66f, 0.0f);
						break;
					case BROWN:
						glColor3f(0.66f, 0.4f, 0.0f);
						break;
					case PINK:
						glColor3f(1.0f, 0.0f, 1.0f);
						break;
					case YELLOW:
						glColor3f(1.0f, 1.0f, 0.0f);
						break;
					case BLUE:
						glColor3f(0.0f, 1.0f, 1.0f);
						break;
					default:
						glColor3f(1.0f, 1.0f, 1.0f);
						break;
					}

					camember.Draw();
					
				glPopMatrix();
			}
		}
	}
}


//Dessine le dé
void Scene::DrawDie(Config& config)
{
	if(die_anim)
	{
		if(delta < 12.0f)
		{
			delta += 0.1f;
		}
		else
		{
			die_anim = FALSE;
			config.game_status = GAME_STATUS_POSITION;
		}
	}

	glColor3f(1.0f, 1.0f, 1.0f);

	glPushMatrix();

		glTranslatef(-60.0f + 10.0f*delta, 0.0f, 2.373f);

		glRotatef(30.0f*delta, 0.0f, 1.0f, 0.0f);

		switch(config.players[config.active_player].hit)
		{
		case 1:
			glRotatef(90.0f, 1.0f, 0.0f, 0.0f);
			break;
		case 2:
			glRotatef(270.0f, 0.0f, 1.0f, 0.0f);
			break;
		case 3:
			glRotatef(180.0f, 0.0f, 1.0f, 0.0f);
			break;
		case 5:
			glRotatef(90.0f, 0.0f, 1.0f, 0.0f);
			break;
		case 6:
			glRotatef(-90.0f, 1.0f, 0.0f, 0.0f);
			break;
		default:
			break;
		}

		die.Draw();

	glPopMatrix();
}


//Dessine le HUD : Affichage du texte
void Scene::DrawHUD(Config& config, Mouse& mouse)
{
	switch(config.active_player+1)
	{
	case ORANGE:
		glColor3f(1.0f, 0.66f, 0.0f);
		break;
	case GREEN:
		glColor3f(0.0f, 0.66f, 0.0f);
		break;
	case BROWN:
		glColor3f(0.66f, 0.4f, 0.0f);
		break;
	case PINK:
		glColor3f(1.0f, 0.0f, 1.0f);
		break;
	case YELLOW:
		glColor3f(1.0f, 1.0f, 0.0f);
		break;
	case BLUE:
		glColor3f(0.0f, 1.0f, 1.0f);
		break;
	default:
		glColor3f(1.0f, 1.0f, 1.0f);
		break;
	}
	glDrawText(config, 10, -5, "Joueur %i : %s", config.active_player+1, config.players[config.active_player].name);

	switch(config.game_status)
	{
	case GAME_STATUS_DIE_THROW:
		{
			DrawHUDDieThrow(config, mouse);
			break;
		}
	case GAME_STATUS_POSITION:
		{
			DrawHUDPosition(config, mouse);
			break;
		}
	case GAME_STATUS_QUESTION:
		{
			DrawHUDQuestion(config, mouse);
			break;
		}
	case GAME_STATUS_ANSWER:
		{
			DrawHUDAnswer(config, mouse);
			break;
		}
	case GAME_STATUS_CHOOSE_QUESTION_COLOR:
		{
			DrawHUDChooseQuestionColor(config, mouse);
			break;
		}
	case GAME_STATUS_END:
		{
			DrawHUDEnd(config, mouse);
			break;
		}
	case GAME_STATUS_DIE_ANIM:
		{
			DrawHUDDieAnim(config, mouse);
			break;
		}
	default:
		break;
	}

	glColor3f(1.0f, 1.0f, 1.0f);
}

//Dessine du texte
void Scene::glDrawText(Config& config, int x, int y, const char *strString, ...)
{
	char strText[MAX_CHARS];
	va_list	argumentPtr;

	if(strString == "")
		return;
	
	va_start(argumentPtr, strString);
	vsprintf(strText, strString, argumentPtr);
	va_end(argumentPtr);

	glPushAttrib(GL_TRANSFORM_BIT | GL_VIEWPORT_BIT);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	y = config.screen_height - (int)(FONT_HEIGHT*config.coef_y) - (int)(y*config.coef_y);

	glViewport((int)(x*config.coef_x) - 1, y - 1, 0, 0);

	glRasterPos4f(0, 0, 0, 1);

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glPopAttrib();

	glPushAttrib(GL_LIST_BIT);

	glListBase(font_list);

	glCallLists(strlen(strText), GL_UNSIGNED_BYTE, strText);

	glPopAttrib();
}



//Retourne l'objet sélectionné
int Scene::GetSelected(Config& config, Mouse& mouse)
{
	int objectsFound = 0;
	int	viewportCoords[4] = {0};
	unsigned int selectBuffer[512];
	int selected;

	glGetIntegerv(GL_VIEWPORT, viewportCoords);
	glSelectBuffer(512, selectBuffer);

	glRenderMode(GL_SELECT);

	glInitNames();
	glPushName(0);

	glMatrixMode(GL_PROJECTION);
	
	glPushMatrix();
		glLoadIdentity();

		gluPickMatrix(mouse.x, viewportCoords[3] - mouse.y, 1.0f, 1.0f, viewportCoords);

		gluPerspective(45.0f,(GLfloat)config.screen_width/(GLfloat)config.screen_height, 0.1f, config.view_depth);
		
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
	
		Draw(config, mouse);

		glMatrixMode(GL_PROJECTION);
	glPopMatrix();

	glMatrixMode(GL_MODELVIEW);

	objectsFound = glRenderMode(GL_RENDER);

	if(objectsFound > 0)
	{
		unsigned int lowestDepth = selectBuffer[1];

		selected = selectBuffer[3];

		for(int i = 1; i < objectsFound; i++)
		{
			if(selectBuffer[(i * 4) + 1] < lowestDepth)
			{
				lowestDepth = selectBuffer[(i * 4) + 1];
				selected = selectBuffer[(i * 4) + 3];
			}
		}
	}
	else
	{
		selected = -1;
	}

	return selected;
}

//Défini la position sur la case
bool Scene::SetPos(unsigned int square)
{
	if((square > 1) && (square < 26))
	{
		glRotatef(((square-2)/4)*60.0f, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, (GLfloat)(23.02485+((square-2)%4)*(11.4053)), 0.0f);
	}
	else if((square > 25) && (square < 32))
	{
		glRotatef((square-26)*60.0f, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, 68.65345f, 0.0f);
	}
	else if((square > 31) && (square < 38))
	{
		glRotatef((square-32)*60.0f, 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, 81.7942f, 0.0f);
	}
	else if((square > 37) && (square < 74))
	{
		glRotatef((GLfloat)(((square-38)%6)*(-7.5)+(((square-38)/6)*8)*(-7.5f)-11.25), 0.0f, 0.0f, 1.0f);
		glTranslatef(0.0f, 81.7942f, 0.0f);
	}

	return TRUE;
}

//Retourne la question et les réponses
bool Scene::GetQuestion(unsigned int color)
{
	FILE* question_fd;
	fpos_t pos;
	
	char c;

	unsigned int i, number, nb_questions = 0, tmp_number = 0;

	switch(color)
	{
	case ORANGE:
		question_fd = fopen(ORANGE_QUESTION_FILE_PATH, "r");
		break;
	case GREEN:
		question_fd = fopen(GREEN_QUESTION_FILE_PATH, "r");
		break;
	case BROWN:
		question_fd = fopen(BROWN_QUESTION_FILE_PATH, "r");
		break;
	case PINK:
		question_fd = fopen(PINK_QUESTION_FILE_PATH, "r");
		break;
	case YELLOW:
		question_fd = fopen(YELLOW_QUESTION_FILE_PATH, "r");
		break;
	case BLUE:
		question_fd = fopen(BLUE_QUESTION_FILE_PATH, "r");
		break;
	default:
		return FALSE;
	}

	if(question_fd == NULL)
		return FALSE;

	

	fscanf(question_fd, "nb_questions=%i\n", &nb_questions);
	
	if(!nb_questions)
	{
		return FALSE;
	}

	do
	{
		number = 1+(rand()%nb_questions);
	}
	while(answered_question[color-1][number-1]);

	answered_question[color-1][number-1] = TRUE;

	if(fgetpos(question_fd, &pos))
	{
		return FALSE;
	}

	while(!feof(question_fd))
	{
		if(fsetpos(question_fd, &pos))
		{
			return FALSE;
		}

		fscanf(question_fd, "[%i]\n", &tmp_number);

		if(tmp_number == number)
		{
			fgets(qcm.question, MAX_CHARS, question_fd);
			qcm.question[strlen(qcm.question)-1] = '\0';

			for(i = 0; i < 4; i++)
			{
				fscanf(question_fd, "%c ", &c);

				if(c == '+')
				{
					qcm.good_answer = i;
				}
				fgets(qcm.answer[i], MAX_CHARS, question_fd);
				qcm.answer[i][strlen(qcm.answer[i])-1] = '\0';
			}



			return TRUE;
		}

		pos++;
	}

	return FALSE;
}


void Scene::DrawHUDAnswer(Config& config, Mouse& mouse)
{
	glColor3f(1.0f, 0.0f, 0.0f);
	if(config.players[config.active_player].answer)
	{
		glDrawText(config, 10, FONT_HEIGHT-10, "Bonne réponse!!");

		if(board.GetSquareType(config.players[config.active_player].square_pos-1) == TYPE_CAMEMBER)
		{
			if(!config.players[config.active_player].camember[board.GetSquareColor(config.players[config.active_player].square_pos-1)-1])
			{
				config.players[config.active_player].camember[board.GetSquareColor(config.players[config.active_player].square_pos-1)-1] = TRUE;
			}
		}
	}
	else
	{
		glDrawText(config, 10, FONT_HEIGHT-10, "Réponse fausse...");
	}

	if((mouse.x > ((int)config.screen_width - 96)) && (mouse.y > ((int)config.screen_height - (FONT_HEIGHT+10))))
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		if(mouse.l_click)
		{
			config.players[config.active_player].hit = 0;
			config.players[config.active_player].choice = 0;
					
			if(!config.players[config.active_player].answer)
			{
				if(config.active_player < (config.nb_players-1))
				{
					config.active_player++;
				}
				else
				{
					config.active_player = 0;
				}
			}

			config.players[config.active_player].answer = 0;
			mouse.l_click = FALSE;
			config.game_status = GAME_STATUS_DIE_THROW;
		}
	}
	else
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	glDrawText(config, 1600 - 96, 1200 - (FONT_HEIGHT+10), "OK");
}


void Scene::DrawHUDChooseQuestionColor(Config& config, Mouse& mouse)
{
	unsigned int i, j;

	for(j = 0, i = 0; j < 6; j++)
	{
		if(config.players[config.active_player].camember[j])
		{
			i++;
		}
	}

	glColor3f(1.0f, 0.0f, 0.0f);

	if(i == 6)
	{
		glDrawText(config, 10, FONT_HEIGHT-10, "Le joueur %i : %s doit choisir la catégorie de votre question...", random_player+1, config.players[random_player].name);

	}
	else
	{
		glDrawText(config, 10, FONT_HEIGHT-10, "Veuillez choisir la catégorie de votre question...");
	}


	glColor3f(1.0f, 0.66f, 0.0f);
	glDrawText(config, 400, FONT_HEIGHT+100, "Question orange : Géographie");
	glColor3f(0.0f, 0.66f, 0.0f);
	glDrawText(config, 400, FONT_HEIGHT+200, "Question verte : Science");
	glColor3f(0.66f, 0.4f, 0.0f);
	glDrawText(config, 400, FONT_HEIGHT+300, "Question marron : Histoire");
	glColor3f(1.0f, 0.0f, 1.0f);
	glDrawText(config, 400, FONT_HEIGHT+400, "Question rose : People");
	glColor3f(1.0f, 1.0f, 0.0f);
	glDrawText(config, 400, FONT_HEIGHT+500, "Question jaune : Art");
	glColor3f(0.0f, 1.0f, 1.0f);
	glDrawText(config, 400, FONT_HEIGHT+600, "Question bleu : Sport");


	glColor3f(1.0f, 1.0f, 1.0f);
	glDrawText(config, 350, FONT_HEIGHT+100+(config.players[config.active_player].choice*100), ">>");


	if(mouse.l_click)
	{
		if(mouse.y < FONT_HEIGHT+200)
		{
			config.players[config.active_player].choice = 0;
		}
		else if((mouse.y > FONT_HEIGHT+200) && (mouse.y < FONT_HEIGHT+300))
		{
			config.players[config.active_player].choice = 1;
		}
		else if((mouse.y > FONT_HEIGHT+300) && (mouse.y < FONT_HEIGHT+400))
		{
			config.players[config.active_player].choice = 2;
		}
		else if((mouse.y > FONT_HEIGHT+400) && (mouse.y < FONT_HEIGHT+500))
		{
			config.players[config.active_player].choice = 3;
		}
		else if((mouse.y > FONT_HEIGHT+500) && (mouse.y < FONT_HEIGHT+600))
		{
			config.players[config.active_player].choice = 4;
		}
		else if((mouse.y > FONT_HEIGHT+600) && (mouse.y < FONT_HEIGHT+700))
		{
			config.players[config.active_player].choice = 5;
		}
	}

	if((mouse.x > ((int)config.screen_width - 96)) && (mouse.y > ((int)config.screen_height - (FONT_HEIGHT+10))))
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		if(mouse.l_click)
		{
			GetQuestion(config.players[config.active_player].choice+1);
			config.players[config.active_player].choice = 0;
			mouse.l_click = FALSE;
			time(&last_time);
			config.game_status = GAME_STATUS_QUESTION;
		}
	}
	else
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	glDrawText(config, 1600 - 96, 1200 - (FONT_HEIGHT+10), "OK");
}

void Scene::DrawHUDDieAnim(Config& config, Mouse& mouse)
{
	if(!die_anim)
	{
		delta = 0.0f;
	}

	die_anim = TRUE;
}


void Scene::DrawHUDDieThrow(Config& config, Mouse& mouse)
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glDrawText(config, 10, FONT_HEIGHT-10, "Veuillez lancer le dé...");
	if((mouse.x > ((int)config.screen_width - 170)) && (mouse.y > ((int)config.screen_height - (FONT_HEIGHT+10))))
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		if(mouse.l_click)
		{
			config.players[config.active_player].LaunchTheDie();
			board.GetPossibleSquare(config);
			config.game_status = GAME_STATUS_DIE_ANIM;
			mouse.l_click = FALSE;
		}
	}
	else
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	glDrawText(config, 1600 - 170, 1200 - (FONT_HEIGHT+10), "Lancer le dé");
}


void Scene::DrawHUDEnd(Config& config, Mouse& mouse)
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glDrawText(config, 10, FONT_HEIGHT-10, "Vous avez gagné!!! Bravo!");

	if((mouse.x > ((int)config.screen_width - 130)) && (mouse.y > ((int)config.screen_height - (FONT_HEIGHT+10))))
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		if(mouse.l_click)
		{
			mouse.l_click = FALSE;
			config.Quit();
		}
	}
	else
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	glDrawText(config, 1600 - 130, 1200 - (FONT_HEIGHT+10), "Quitter");
}

void Scene::DrawHUDPosition(Config& config, Mouse& mouse)
{
	glColor3f(1.0f, 0.0f, 0.0f);
	glDrawText(config, 10, FONT_HEIGHT-10, "Vous avez fait %i, veuillez choisir votre position...", config.players[config.active_player].hit);
	if((mouse.x > ((int)config.screen_width - 96)) && (mouse.y > ((int)config.screen_height - (FONT_HEIGHT+10))))
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		if(mouse.l_click)
		{
			if(board.selected_square > 0)
			{
				config.players[config.active_player].square_pos = board.selected_square;
						
				switch(board.GetSquareType(config.players[config.active_player].square_pos-1))
				{
				case TYPE_REPLAY:
					config.game_status = GAME_STATUS_DIE_THROW;
					break;
				case TYPE_CENTER:
					random_player = rand()%config.nb_players;
					config.game_status = GAME_STATUS_CHOOSE_QUESTION_COLOR;
					break;
				default:
					GetQuestion(board.GetSquareColor(config.players[config.active_player].square_pos-1));
					time(&last_time);
					config.game_status = GAME_STATUS_QUESTION;
					break;
				}
			}
			mouse.l_click = FALSE;
		}
	}
	else
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	glDrawText(config, 1600 - 96, 1200 - (FONT_HEIGHT+10), "OK");
}


void Scene::DrawHUDQuestion(Config& config, Mouse& mouse)
{
	unsigned int i, j;

	time(&elapsed_time);
			
	if(elapsed_time-last_time > (int)config.sec_to_answer-1)
	{
		config.players[config.active_player].answer = FALSE;
		config.game_status = GAME_STATUS_ANSWER;
	}

	glColor3f(1.0f, 0.0f, 0.0f);
	if(elapsed_time-last_time < (int)config.sec_to_answer-1)
	{
		glDrawText(config, 10, FONT_HEIGHT-10, "Il vous reste %i secondes pour répondre", config.sec_to_answer-(int)(elapsed_time-last_time));
	}
	else
	{
		glDrawText(config, 10, FONT_HEIGHT-10, "Il vous reste %i seconde pour répondre", config.sec_to_answer-(int)(elapsed_time-last_time));
	}


	switch(board.GetSquareColor(config.players[config.active_player].square_pos-1))
	{
	case ORANGE:
		glColor3f(1.0f, 0.66f, 0.0f);
		break;
	case GREEN:
		glColor3f(0.0f, 0.66f, 0.0f);
		break;
	case BROWN:
		glColor3f(0.66f, 0.4f, 0.0f);
		break;
	case PINK:
		glColor3f(1.0f, 0.0f, 1.0f);
		break;
	case YELLOW:
		glColor3f(1.0f, 1.0f, 0.0f);
		break;
	case BLUE:
		glColor3f(0.0f, 1.0f, 1.0f);
		break;
	default:
		glColor3f(1.0f, 1.0f, 1.0f);
		break;
	}
	glDrawText(config, 50, FONT_HEIGHT+100, "%s", qcm.question);
			
			
	glColor3f(1.0f, 1.0f, 1.0f);
	glDrawText(config, 100, FONT_HEIGHT+300, "%s", qcm.answer[0]);
	glDrawText(config, 100, FONT_HEIGHT+400, "%s", qcm.answer[1]);
	glDrawText(config, 100, FONT_HEIGHT+500, "%s", qcm.answer[2]);
	glDrawText(config, 100, FONT_HEIGHT+600, "%s", qcm.answer[3]);


	glColor3f(1.0f, 1.0f, 1.0f);
	glDrawText(config, 50, FONT_HEIGHT+300+(config.players[config.active_player].choice*100), ">>");


	if(mouse.l_click)
	{
		if(mouse.y < FONT_HEIGHT+400)
		{
			config.players[config.active_player].choice = 0;
		}
		else if((mouse.y > FONT_HEIGHT+400) && (mouse.y < FONT_HEIGHT+500))
		{
			config.players[config.active_player].choice = 1;
		}
		else if((mouse.y > FONT_HEIGHT+500) && (mouse.y < FONT_HEIGHT+600))
		{
			config.players[config.active_player].choice = 2;
		}
		else if((mouse.y > FONT_HEIGHT+600) && (mouse.y < FONT_HEIGHT+700))
		{
			config.players[config.active_player].choice = 3;
		}
	}


	if((mouse.x > ((int)config.screen_width - 96)) && (mouse.y > ((int)config.screen_height - (FONT_HEIGHT+10))))
	{
		glColor3f(0.0f, 1.0f, 0.0f);
		if(mouse.l_click)
		{
			config.game_status = GAME_STATUS_ANSWER;
					
			if(config.players[config.active_player].choice == qcm.good_answer)
			{
				config.players[config.active_player].answer = TRUE;

				if(board.GetSquareType(config.players[config.active_player].square_pos-1) == TYPE_CENTER)
				{
					for(j = 0, i = 0; j < 6; j++)
					{
						if(config.players[config.active_player].camember[j])
						{
							i++;
						}
					}

					if(i == 6)
					{
						config.game_status = GAME_STATUS_END;
					}
				}
			}

			mouse.l_click = FALSE;
		}
	}
	else
	{
		glColor3f(1.0f, 0.0f, 0.0f);
	}
	glDrawText(config, 1600 - 96, 1200 - (FONT_HEIGHT+10), "OK");
}
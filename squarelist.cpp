/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* squarelist.cpp : Contient les méthodes nécessaires à */
/* la gestion du plateau.                               */
/********************************************************/

#include "squarelist.h"

//Retourne l'ID de tous les liens des cases
SquareResult SquareList::GetLinkId(unsigned int id)
{
	SquareResult link_id;
	unsigned int i, j, tmp;

	if(square[id-1].type == TYPE_CENTER)
	{
		link_id.result = (unsigned int*)malloc(6);
		link_id.nb = 6;
		for(i = 0; i < link_id.nb; i++)
		{
			link_id.result[i] = square[id-1].link[i]->id;
		}
		return link_id;
	}
	else if(square[id-1].type == TYPE_CAMEMBER)
	{
		link_id.result = (unsigned int*)malloc(3);
		link_id.nb = 3;
		for(i = 0; i < link_id.nb; i++)
		{
			link_id.result[i] = square[id-1].link[i]->id;
		}
		return link_id;
	}
	else
	{
		link_id.result = (unsigned int*)malloc(2);
		link_id.nb = 2;
		for(i = 0; i < link_id.nb; i++)
		{
			link_id.result[i] = square[id-1].link[i]->id;
		}
		return link_id;
	}

	for(i = 0; i < link_id.nb-1; i++)
	{
		for(j = i+1; j < link_id.nb; j++)
		{
			if(link_id.result[j] > link_id.result[i])
			{
				tmp = link_id.result[j];
				link_id.result[j] = link_id.result[i];
				link_id.result[i] = tmp;
			}
		}
	}

	return link_id;
}

//Retourne l'ID des cases suivantes
bool SquareList::GetNextLinkId(SquareResult& previous, SquareResult& current)
{
	unsigned int i, j, k, count;
	SquareResult next;
	SquareResult tmp;

	next.result = (unsigned int*)malloc(MAX_POSSIBLE_POSITIONS);
	next.nb = 0;

	for(i = 0; i < current.nb; i++)
	{
		tmp = GetLinkId(current.result[i]);
		for(j = 0; j < tmp.nb; j++)
		{
			for(k = 0, count = 0; k < previous.nb; k++)
			{
				if(tmp.result[j] != previous.result[k])
				{
					count++;
				}
			}
			if(count == previous.nb)
			{
				next.result[next.nb] = tmp.result[j];
				next.nb++;
			}
		}
	}

	previous.nb = current.nb;
	//free(previous.result);
	previous.result = (unsigned int*)malloc(current.nb);

	for(i = 0; i < current.nb; i++)
	{
		previous.result[i] = current.result[i];
	}

	current.nb = next.nb;
	//free(current.result);
	current.result = (unsigned int*)malloc(next.nb);

	for(i = 0; i < next.nb; i++)
	{
		current.result[i] = next.result[i];
	}

	//free(tmp.result);
	//free(next.result);

	return TRUE;
}
		


//Charge le plateau : initialise les cases : numéro, couleur...
bool SquareList::Load()
{
	unsigned int i, j;

	square = new Square[73];

	if(square == NULL)
		return FALSE;

	//center
	square[0].Set(1, &square[1], &square[5], &square[9], &square[13], &square[17], &square[21]);

	for(i = 0; i < 6; i++)
	{
		//near center
		square[1+(4*i)].Set(2+(4*i), &square[0], &square[2+(4*i)]);

		//center square
		square[2+(4*i)].Set(3+(4*i), &square[1+(4*i)], &square[3+(4*i)]);
		square[3+(4*i)].Set(4+(4*i), &square[2+(4*i)], &square[4+(4*i)]);

		//near inter near inter
		square[4+(4*i)].Set(5+(4*i), &square[3+(4*i)], &square[25+i]);

		//near inter
		square[25+i].Set(26+i, &square[4+(4*i)], &square[31+i]);

		for(j = 0; j < 5; j++)
		{
			//ext square
			square[38+j+(i*6)].Set(39+j+(i*6), &square[37+j+(i*6)], &square[39+j+(i*6)]);
		}
	}

	//inter
	square[31].Set(32, &square[25], &square[37], &square[72]);

	//near inter ext
	square[37].Set(38, &square[31], &square[38]);
	square[72].Set(73, &square[31], &square[71]);

	for(i = 0; i < 5; i++)
	{
		//inter
		square[32+i].Set(33+i, &square[26+i], &square[67-(i*6)], &square[66-(i*6)]);

		//near inter ext
		square[67-(i*6)].Set(68-(i*6), &square[32+i], &square[68-(i*6)]);
		square[66-(i*6)].Set(67-(i*6), &square[32+i], &square[65-(i*6)]);
	}



	//TYPE
	square[0].type = TYPE_CENTER;

	for(i = 0; i < 6; i++)
	{
		square[31+i].type = TYPE_CAMEMBER;
		square[38+i*6].type = TYPE_REPLAY;
		square[41+i*6].type = TYPE_REPLAY;
	}

	//COULEUR - ORANGE
	square[2].color = ORANGE;
	square[7].color = ORANGE;
	square[16].color = ORANGE;
	square[17].color = ORANGE;
	square[27].color = ORANGE;
	square[36].color = ORANGE;
	square[52].color = ORANGE;
	square[60].color = ORANGE;
	square[61].color = ORANGE;
	square[69].color = ORANGE;

	//COULEUR - GREEN
	square[4].color = GREEN;
	square[5].color = GREEN;
	square[14].color = GREEN;
	square[19].color = GREEN;
	square[33].color = GREEN;
	square[42].color = GREEN;
	square[43].color = GREEN;
	square[51].color = GREEN;
	square[70].color = GREEN;

	//COULEUR - BROWN
	square[1].color = BROWN;
	square[10].color = BROWN;
	square[15].color = BROWN;
	square[24].color = BROWN;
	square[29].color = BROWN;
	square[32].color = BROWN;
	square[40].color = BROWN;
	square[48].color = BROWN;
	square[49].color = BROWN;
	square[57].color = BROWN;

	//COULEUR - PINK
	square[8].color = PINK;
	square[9].color = PINK;
	square[18].color = PINK;
	square[23].color = PINK;
	square[25].color = PINK;
	square[34].color = PINK;
	square[37].color = PINK;
	square[45].color = PINK;
	square[64].color = PINK;
	square[72].color = PINK;

	//COULEUR - YELLOW
	square[3].color = YELLOW;
	square[12].color = YELLOW;
	square[13].color = YELLOW;
	square[22].color = YELLOW;
	square[26].color = YELLOW;
	square[35].color = YELLOW;
	square[39].color = YELLOW;
	square[58].color = YELLOW;	
	square[66].color = YELLOW;
	square[67].color = YELLOW;

	//COULEUR - BLUE
	square[6].color = BLUE;
	square[11].color = BLUE;
	square[20].color = BLUE;
	square[21].color = BLUE;
	square[28].color = BLUE;
	square[31].color = BLUE;
	square[46].color = BLUE;
	square[54].color = BLUE;
	square[55].color = BLUE;
	square[63].color = BLUE;

	return TRUE;
}

//Retourne les cases possibles
SquareResult SquareList::GetPossibleSquare(Config& config)
{
	unsigned int i;

	SquareResult last, current;

	last.result = (unsigned int*)malloc(MAX_POSSIBLE_POSITIONS);
	last.nb = 1;
	last.result[0] = config.players[config.active_player].square_pos-1;

	current.result = (unsigned int*)malloc(MAX_POSSIBLE_POSITIONS);
	current.nb = 0;
	for(i = 0; i < 6; i++)
	{
		if(square[config.players[config.active_player].square_pos-1].link[i] != NULL)
		{
			current.result[i] = square[config.players[config.active_player].square_pos-1].link[i]->id;
		}
	}

	for(i = 0; i < config.players[config.active_player].hit; i++)
	{
		GetNextLinkId(last, current);
	}

	return current;

}



//Retourne le type de la case
unsigned int SquareList::GetSquareType(unsigned int id)
{
	return square[id].type;
}

//Retourne la couleur de la case
unsigned int SquareList::GetSquareColor(unsigned int id)
{
	return square[id].color;
}
/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* board.cpp : Contient les méthodes nécessaires à      */
/* la gestion du plateau du trivial.                    */
/********************************************************/


#include "board.h"


//Charge le plateau
bool Board::Load(Config& config, unsigned int id)
{
	unsigned int i, j;
	FILE* data_fd;

	display_list_id = id;

	if((data_fd = fopen(BOARD_DATA_FILE_PATH, "r")) == NULL)
		return FALSE;

	fscanf(data_fd, "nb_vertex=%i\n", &nb_vertex);
	fscanf(data_fd, "nb_face=%i\n", &nb_face);
	fscanf(data_fd, "nb_vertex_map_coord=%i\n", &nb_vertex_map_coord);
	fscanf(data_fd, "nb_face_map_coord=%i\n", &nb_face_map_coord);
	
	vertex = new Vector3[nb_vertex];
	for(i = 0; i < nb_vertex; i++)
	{
		fscanf(data_fd, "			*MESH_VERTEX    %*i %f %f %f\n", &vertex[i].x, &vertex[i].y, &vertex[i].z);
	}
	
	face_vertex_id = new Uint3[nb_face];
	for(i = 0; i < nb_face; i++)
	{
		fscanf(data_fd, "			*MESH_FACE %*i:    A: %i B: %i C: %i AB: %*i BC: %*i CA: %*i *MESH_SMOOTHING 	*MESH_MTLID %*i\n", &face_vertex_id[i].Num[0], &face_vertex_id[i].Num[1], &face_vertex_id[i].Num[2]);
	}

	vertex_map_coord = new Vector3[nb_vertex_map_coord];
	for(i = 0; i < nb_vertex_map_coord; i++)
	{
		fscanf(data_fd, "			*MESH_TVERT %*i	%f %f %f\n", &vertex_map_coord[i].x, &vertex_map_coord[i].y, &vertex_map_coord[i].z);
	}

	face_map_coord_id = new Uint3[nb_face_map_coord];
	for(i = 0; i < nb_face_map_coord; i++)
	{
		fscanf(data_fd, "			*MESH_TFACE %*i	%i	%i	%i\n", &face_map_coord_id[i].Num[0], &face_map_coord_id[i].Num[1], &face_map_coord_id[i].Num[2]);
	}

	face_normal = new Vector3[nb_face];
	vertex_normal = new VertexNormal[nb_face];
	for(i = 0; i < nb_face; i++)
	{
		fscanf(data_fd, "			*MESH_FACENORMAL %*i	%f	%f	%f\n				*MESH_VERTEXNORMAL %*i	%f	%f	%f\n				*MESH_VERTEXNORMAL %*i	%f	%f	%f\n				*MESH_VERTEXNORMAL %*i	%f	%f	%f\n",
			&face_normal[i].x, &face_normal[i].y, &face_normal[i].z, 
			&vertex_normal[i].Vertex[0].x, &vertex_normal[i].Vertex[0].y, &vertex_normal[i].Vertex[0].z,
			&vertex_normal[i].Vertex[1].x, &vertex_normal[i].Vertex[1].y, &vertex_normal[i].Vertex[1].z,
			&vertex_normal[i].Vertex[2].x, &vertex_normal[i].Vertex[2].y, &vertex_normal[i].Vertex[2].z);
	}

	fclose(data_fd);

	if(!LoadTexture(id, BOARD_TEXTURE_FILE_PATH))
	{
		return FALSE;
	}
	
	glNewList(display_list_id, GL_COMPILE);

	glDisable(GL_COLOR_MATERIAL);
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, id);

	glBegin(GL_TRIANGLES);

		for(i = 0; i < nb_face; i++)
		{
			if(!config.gouraud_shading)
			{
				glNormal3f(face_normal[i].x, face_normal[i].y, face_normal[i].z);
			}
			
			for(j = 0; j < 3; j++)
			{
				if(config.gouraud_shading)
				{
					glNormal3f(vertex_normal[i].Vertex[j].x, vertex_normal[i].Vertex[j].y, vertex_normal[i].Vertex[j].z);
				}

				glTexCoord3f(vertex_map_coord[face_map_coord_id[i].Num[j]].x, vertex_map_coord[face_map_coord_id[i].Num[j]].y, vertex_map_coord[face_map_coord_id[i].Num[j]].z);
				glVertex3f(vertex[face_vertex_id[i].Num[j]].x, vertex[face_vertex_id[i].Num[j]].y, vertex[face_vertex_id[i].Num[j]].z);
			}
		}

	glEnd();

	glDisable(GL_TEXTURE_2D);
	glEnable(GL_COLOR_MATERIAL);

	glEndList();

	LoadVirtual();


	return TRUE;
}


//Charge le plateau virtuel (utilisé pour la selection)
bool Board::LoadVirtual()
{
	unsigned int i, j;

	virtual_list_id = glGenLists(72);

	//CENTER
	glNewList(virtual_list_id, GL_COMPILE);
		
		glLoadName(1);

		glBegin(GL_TRIANGLES);
			glVertex3f(19.9966f, 0.0017f, 0.2f);
			glVertex3f(9.9966f, -17.3188f, 0.2f);
			glVertex3f(-10.0034f, -17.3188f, 0.2f);

			glVertex3f(-10.0034f, -17.3188f, 0.2f);
			glVertex3f(19.9966f, 0.0017f, 0.2f);
			glVertex3f(-20.0034f, 0.0017f, 0.2f);

			glVertex3f(-20.0034f, 0.0017f, 0.2f);
			glVertex3f(19.9966f, 0.0017f, 0.2f);
			glVertex3f(9.9966f, 17.3222f, 0.2f);

			glVertex3f(9.9966f, 17.3222f, 0.2f);
			glVertex3f(-20.0034f, 0.0017f, 0.2f);
			glVertex3f(-10.0034f, 17.3222f, 0.2f);
		glEnd();

		glEnd();

	glEndList();

	//CENTER_SQUARE
	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 4; j++)
		{
			glNewList(virtual_list_id+1+(i*4)+j, GL_COMPILE);

				glPushMatrix();

					glRotatef(i*60.0f, 0.0f, 0.0f, 1.0f);

					glTranslatef(0.0f, (GLfloat)(11.4053*(GLfloat)j), 0.0f);

					glLoadName(2+(i*4)+j);

					glBegin(GL_TRIANGLES);
						glVertex3f(9.9966f, 17.3222f, 0.2f);
						glVertex3f(-10.0034f, 17.3222f, 0.2f);
						glVertex3f(9.9966f, 28.7275f, 0.2f);
						
						glVertex3f(9.9966f, 28.7275f, 0.2f);
						glVertex3f(-10.0034f, 17.3222f, 0.2f);
						glVertex3f(-10.0034f, 28.7275f, 0.2f);
					glEnd();

					glEnd();

				glPopMatrix();
			
			glEndList();
		}
	}

	//NEAR_INTERSECT
	for(i = 0; i < 6; i++)
	{
		glNewList(virtual_list_id+25+i, GL_COMPILE);

			glPushMatrix();

				glRotatef(i*60.0f, 0.0f, 0.0f, 1.0f);

				glLoadName(26+i);

				glBegin(GL_TRIANGLES);
					glVertex3f(9.9966f, 74.3584f, 0.2f);
					glVertex3f(9.9966f, 62.9485f, 0.2f);
					glVertex3f(-0.0034f, 75.0017f, 0.2f);
						
					glVertex3f(-0.0034f, 75.0017f, 0.2f);
					glVertex3f(9.9966f, 62.9485f, 0.2f);
					glVertex3f(-10.0034f, 62.9485f, 0.2f);

					glVertex3f(-10.0034f, 62.9485f, 0.2f);
					glVertex3f(-0.0034f, 75.0017f, 0.2f);
					glVertex3f(-10.0034f, 74.3584f, 0.2f);
				glEnd();

				glEnd();

			glPopMatrix();

		glEndList();
	}

	//INTERSEC
	for(i = 0; i < 6; i++)
	{
		glNewList(virtual_list_id+31+i, GL_COMPILE);

			glPushMatrix();

				glRotatef(i*60.0f, 0.0f, 0.0f, 1.0f);

				glLoadName(32+i);

				glBegin(GL_TRIANGLES);
					glVertex3f(9.9966f, 74.3584f, 0.2f);
					glVertex3f(-0.0034f, 75.0017f, 0.2f);
					glVertex3f(11.7474f, 89.2300f, 0.2f);
						
					glVertex3f(11.7474f, 89.2300f, 0.2f);
					glVertex3f(-0.0034f, 75.0017f, 0.2f);
					glVertex3f(-0.0034f, 90.0000f, 0.2f);

					glVertex3f(-0.0034f, 90.0000f, 0.2f);
					glVertex3f(-0.0034f, 75.0017f, 0.2f);
					glVertex3f(-11.7474f, 89.2300f, 0.2f);

					glVertex3f(-11.7474f, 89.2300f, 0.2f);
					glVertex3f(-0.0034f, 75.0017f, 0.2f);
					glVertex3f(-10.0034f, 74.3584f, 0.2f);
				glEnd();

				glEnd();

			glPopMatrix();

		glEndList();
	}


	//EXT_SQUARE
	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 6; j++)
		{
			glNewList(virtual_list_id+37+(i*6)+j, GL_COMPILE);

				glPushMatrix();

					glRotatef(i*-60.0f, 0.0f, 0.0f, 1.0f);

					glRotatef(j*-7.5f, 0.0f, 0.0f, 1.0f);

					glLoadName(38+(i*6)+j);

					glBegin(GL_TRIANGLES);
						glVertex3f(9.9966f, 74.3584f, 0.2f);
						glVertex3f(11.7474f, 89.2300f, 0.2f);
						glVertex3f(23.2937f, 86.9333f, 0.2f);
							
						glVertex3f(23.2937f, 86.9333f, 0.2f);
						glVertex3f(9.9966f, 74.3584f, 0.2f);
						glVertex3f(19.4114f, 72.4444f, 0.2f);
					glEnd();

					glEnd();

				glPopMatrix();

			glEndList();
		}
	}


	return TRUE;
}



//Dessine le plateau virtuel
void Board::DrawVirtual()
{
	unsigned int i, j;

	glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);

	glColor3f(0.0f, 0.0f, 0.0f);

	glEnable(GL_BLEND);
	glBlendFunc(GL_ONE, GL_ONE);

	glCallList(virtual_list_id);

	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 4; j++)
		{
			glCallList(virtual_list_id+1+(i*4)+j);
		}
	}

	for(i = 0; i < 6; i++)
	{
		glCallList(virtual_list_id+25+i);
	}

	for(i = 0; i < 6; i++)
	{
		glCallList(virtual_list_id+31+i);
	}

	for(i = 0; i < 6; i++)
	{
		for(j = 0; j < 6; j++)
		{
			glCallList(virtual_list_id+37+(i*6)+j);
		}
	}

	glDisable(GL_BLEND);

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}










//Dessine la case selectionnée
void Board::DrawSelectedSquare()
{
	unsigned int i;

	if(selected_square > 0)
	{
		glEnable(GL_BLEND);

		glBlendFunc(GL_ONE, GL_ONE);

		glColor3f(0.0f, 1.0f, 0.0f);

		if(possible_square.nb)
		{
			for(i = 0; i < possible_square.nb; i++)
			{
				if(possible_square.result[i] == (unsigned int)selected_square)
				{
					glColor3f(1.0f, 0.0f, 0.0f);
				}
			}
		}

		glCallList(virtual_list_id+selected_square-1);

		glColor3f(1.0f, 1.0f, 1.0f);

		glDisable(GL_BLEND);
	}	
}


//Dessine les cases possibles
void Board::DrawPossibleSquare()
{
	unsigned int i;

	glEnable(GL_BLEND);

	glBlendFunc(GL_ONE, GL_ONE);

	glColor3f(0.0f, 1.0f, 0.0f);

	for(i = 0; i < possible_square.nb; i++)
	{
		glCallList(virtual_list_id+possible_square.result[i]-1);
	}

	glColor3f(1.0f, 1.0f, 1.0f);

	glDisable(GL_BLEND);
}





//Retourne les cases possible
bool Board::GetPossibleSquare(Config& config)
{
	possible_square = square_list.GetPossibleSquare(config);
	return TRUE;
}

//Retourne le type de la case
unsigned int Board::GetSquareType(unsigned int id)
{
	return square_list.GetSquareType(id);
}

//Retourne la couleur de la case
unsigned int Board::GetSquareColor(unsigned int id)
{
	return square_list.GetSquareColor(id);
}
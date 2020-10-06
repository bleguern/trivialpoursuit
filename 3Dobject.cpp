/********************************************************/
/* Trivial Poursuit v1.0a By GummiTeam!                 */
/* 3Dobject.cpp : Contient les méthodes nécessaires à   */
/* la gestion des objets 3D.                            */
/********************************************************/


#include "3Dobject.h"


//Charge un objet 3D en mémoire
bool Object::Load(Config& config, const char* data_file_path, unsigned int id)
{
	unsigned int i, j;
	FILE* data_fd;

	display_list_id = id;

	if((data_fd = fopen(data_file_path, "r")) == NULL)
	{
		return FALSE;
	}

	fscanf(data_fd, "nb_vertex=%i\n", &nb_vertex);
	fscanf(data_fd, "nb_face=%i\n", &nb_face);
	
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
	
	glNewList(display_list_id, GL_COMPILE);

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

			glVertex3f(vertex[face_vertex_id[i].Num[j]].x, vertex[face_vertex_id[i].Num[j]].y, vertex[face_vertex_id[i].Num[j]].z);
		}
	}

	glEnd();

	glEndList();


	return TRUE;
}

//Dessine l'objet 3D
void Object::Draw()
{
	glCallList(display_list_id);
}



//Charge un objet 3D texturé en mémoire
bool TexturedObject::Load(Config& config, const char* data_file_path, const char* texture_file_path, unsigned int id)
{
	unsigned int i, j;
	FILE* data_fd;

	display_list_id = id;

	if((data_fd = fopen(data_file_path, "r")) == NULL)
	{
		return FALSE;
	}

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

	if(!LoadTexture(id, texture_file_path))
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

	return TRUE;
}



//Charge la texture d'un objet 3D en mémoire
bool TexturedObject::LoadTexture(unsigned int id, const char* texture_file_path)
{
	AUX_RGBImageRec *image = NULL;
	texture_id = id;

	if((image = auxDIBImageLoad(texture_file_path)) == NULL)
	{
		Warning("LoadTexture error\n", sizeof("LoadTexture error\n"));
		return FALSE;
	}

	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	glBindTexture(GL_TEXTURE_2D, texture_id);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	gluBuild2DMipmaps(GL_TEXTURE_2D, 3, image->sizeX, image->sizeY, GL_RGB, GL_UNSIGNED_BYTE, image->data);

	if(image)
	{
		if(image->data)
		{
			free(image->data);
		}

		free(image);
	}

	return TRUE;
}
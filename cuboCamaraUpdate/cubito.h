#define STB_IMAGE_IMPLEMENTATION

#ifndef CUBITO_H
#define CUBITO_H

#include <utility>

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "stb_image.h"
#include "shader/shader.h"
#include "transform.h"

using namespace std;

Shader shaderCamara;
float colores[] = {
	1,0.3451,0,			//orange
	0.7176,0.0706,0.2039,//red
	1,0.8353,0,			//yellow
	1,1,1,				//white
	0,0.2745,0.6784,	//blue
	0,0.6078,0.2824,	//green
	0.2,0.2,0.2//gris
};

void changeColor(int arr[6], int a, int b, int c, int d) {
	int aux = arr[a];
	arr[a] = arr[b];
	arr[b] = arr[c];
	arr[c] = arr[d];
	arr[d] = aux;
}

struct Cubito {
	unsigned int _id = 0;
	int orientacionCentro = 0;
	float tam = 0.4;
	float min = 0.25;
	float div = 2 / (tam - min);
	float starterPosition[3] = { 0,0,0 };
	int esquinaRefencia = 15;

	pair<int, unsigned int> textures[6];//El primero es en que cara esta la textura, el segundo la textura en si

	int color[6] = { 0,0,0,0,0,0 };
	int colorPos[6] = { 0,1,2,3,4,5 };
	//Este se actualiza y muestra los colores de 
	//back //front //left //derecha //abajo //arriba
	float vertices[120] = {
		//back
		0.5f,-0.5f,-0.5f,0.0f,0.0f,//2
		0.5f,0.5f,-0.5f,0.0f,1.0f,//1
		-0.5f,0.5f,-0.5f,1.0f,1.0f,//0
		-0.5f,-0.5f,-0.5f,1.0f,0.0f,//3
		//front
		-0.5f,-0.5f,0.5f,0.0f,0.0f,//7
		-0.5f,0.5f,0.5f,0.0f,1.0f,//4
		0.5f,0.5f,0.5f,1.0f,1.0f,//5
		0.5f,-0.5f,0.5f,1.0f,0.0f,//6
		//left 
		-0.5f,-0.5f,-0.5f,0.0f,0.0f,//3
		-0.5f,0.5f,-0.5f,0.0f,1.0f,//0
		-0.5f,0.5f,0.5f,1.0f,1.0f,//4
		-0.5f,-0.5f,0.5f,1.0f,0.0f,//7
		//derecha
		0.5f,-0.5f,0.5f,0.0f,0.0f,//6
		0.5f,0.5f,0.5f,0.0f,1.0f,//5
		0.5f,0.5f,-0.5f,1.0f,1.0f,//1
		0.5f,-0.5f,-0.5f,1.0f,0.0f,//2
		//abajo
		-0.5f,-0.5f,-0.5f,0.0f,0.0f,//3
		-0.5f,-0.5f,0.5f,0.0f,1.0f,//7
		0.5f,-0.5f,0.5f,1.0f,1.0f,//6
		0.5f,-0.5f,-0.5f,1.0f,0.0f,//2
		//arriba
		-0.5f,0.5f,0.5f,0.0f,0.0f,//4
		-0.5f,0.5f,-0.5f,0.0f,1.0f,//0
		0.5f,0.5f,-0.5f,1.0f,1.0f,//1
		0.5f,0.5f,0.5f,1.0f,0.0f,//5
	};
	float centro[3] = { 0,0,0 };
	Cubito(unsigned int index = 0) : _id(index) {
		float M[4][4];
		getIdentidad(M);
		M[0][0] = M[1][1] = M[2][2] = 0.4;
		aplicarMatriz(M);
		for (int i = 0; i < 6; i++) {
			textures[i] = pair<int, unsigned int>(-1, 0);
		}
	};
	~Cubito() { };
	void aplicarMatriz(float M[4][4], bool uCentro = true) {
		transformPuntos(M, vertices, 24);//#vertices
		if (uCentro) transformPunto(M, centro);
		loadData();
	}
	void updateColorPos(char rotacion) {
		//back //front //left //derecha //abajo //arriba
		switch (rotacion) {
		case 'u': //antihorario
		case 'd':
			//Version de prueba, falta optimizar
			changeColor(colorPos, 2, 1, 3, 0);
			changeColor(colorPos, 2, 1, 3, 0);
		case 'U': //Se quedan fijos arriba y abajo
		case 'D':
			changeColor(colorPos, 2, 1, 3, 0);
			break;
		case 'f':
		case 'b':
			changeColor(colorPos, 3, 5, 2, 4);
			changeColor(colorPos, 3, 5, 2, 4);
		case 'F': //Se quedan fijos adelante y atras
		case 'B':
			changeColor(colorPos, 3, 5, 2, 4);
			break;
		case 'l': //Queda fijo derecha e izquierda
		case 'r':
			changeColor(colorPos, 5, 1, 4, 0);
			changeColor(colorPos, 5, 1, 4, 0);
		case 'L': //Queda fijo derecha e izquierda
		case 'R':
			changeColor(colorPos, 5, 1, 4, 0);
			break;
		default:
			break;
		}
	}
	void draw() {
		for (unsigned int i = 0, j = 0; i < 36; i += 6, j++) {
			if (color[j] == 6) continue;

			if (textures[j].first != -1) bindTexture(textures[j].second);//Tiene textura asignada
			else bindTexture(0);

			shaderCamara.setVec4("ourColor", colores[color[j] * 3], colores[color[j] * 3 + 1], colores[color[j] * 3 + 2], 0.0f);

			glDrawElementsBaseVertex(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)(i * sizeof(unsigned int)), _id * unsigned int(24));//#vertices
			shaderCamara.setVec4("ourColor", 0.0f, 0.0f, 0.0f, 0.0f);
			glDrawElementsBaseVertex(GL_LINE_STRIP, 3, GL_UNSIGNED_INT, (void*)(i * sizeof(unsigned int)), _id * unsigned int(24));//#vertices
			glDrawElementsBaseVertex(GL_LINE_STRIP, 3, GL_UNSIGNED_INT, (void*)((i + 3) * sizeof(unsigned int)), _id * unsigned int(24));//#vertices

		}
	}
	void loadTexture(int cara, string imageFile) {
		glGenTextures(1, &textures[cara].second);
		glBindTexture(GL_TEXTURE_2D, textures[cara].second);

		// load image, create texture and generate mipmaps
		int width, height, nrChannels;
		stbi_set_flip_vertically_on_load(true); // tell stb_image.h to flip loaded texture's on the y-axis.
		unsigned char* data = stbi_load(imageFile.c_str(), &width, &height, &nrChannels, 0);
		if (data) {
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else cout << "Failed to load texture" << endl;
		stbi_image_free(data);
		bindTexture(textures[cara].second);

		textures[cara].first = cara;
		color[cara] = colorPos[cara];//Solo pinta las caras que tienen textura
	}
	void bindTexture(unsigned int texture) {
		// bind textures on corresponding texture units
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture);
	}
	void loadData() {
		//#Vertices
		glBufferSubData(GL_ARRAY_BUFFER, sizeof(float) * 120 * _id, sizeof(vertices), vertices);
	}
	void pintarAll(int _color) {
		for (int i = 0; i < 6; i++) color[i] = _color;
	}

	void breather() {
		float M[4][4];
		//Mover al centro 
		mTraslacion(M, -centro[0], -centro[1], -centro[2]);
		aplicarMatriz(M,0);

		float deseado = (sin(currentFrame) + 1)/ div + min;
		float x = deseado / tam;// deseado/actual
		tam = deseado;

		mEscala(M, x);
		aplicarMatriz(M,0);

		//Devolver del centro 
		mTraslacion(M, centro[0], centro[1], centro[2]);
		aplicarMatriz(M, 0);
	}

	double pasosAPosInicial = 6;
	bool llegoPosInicial = 0;
	double incrementoEjes[3];
	bool goToStarterPosition() {//Retorna si llego
		float M[4][4];
		if (pasosAPosInicial == 6) {
			pasosAPosInicial--;
			incrementoEjes[0] = (starterPosition[0] - vertices[esquinaRefencia])/ pasosAPosInicial;
			incrementoEjes[1] = (starterPosition[1] - vertices[esquinaRefencia+1])/ pasosAPosInicial;
			incrementoEjes[2] = (starterPosition[2] - vertices[esquinaRefencia+2])/ pasosAPosInicial;
			return 0;
		}
		else if(pasosAPosInicial>0) {
			mTraslacion(M, incrementoEjes[0], incrementoEjes[1], incrementoEjes[2]);
			aplicarMatriz(M);
			pasosAPosInicial--;
			return 0;
		}
		else {
			return 1;
		}
	}
};

#endif
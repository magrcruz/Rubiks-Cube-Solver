//Version con rotaciones
#ifndef CUBO_H
#define CUBO_H

#include <iostream>
#include <vector>
#include <fstream>

#include "cubito.h"
#include "plainCube.h"
#include "animation.h"

#include <glad/glad.h>
#include <glfw/glfw3.h>
#include "shader/shader.h"

#define nCubitos 27

#define strTransform ""
//BRB
GLFWwindow* window;

using namespace std;

unsigned int indices[36] = {
	3,0,1, 1,2,3,//back
	4,7,6, 6,5,4,//front
	10,9,8, 8,11,10,//left
	13,14,15, 15,12,13,//derecha
	16,19,18, 18,17,16,//abajo
	21,22,23, 23,20,21,//arriba
};


struct Cubo {
	unsigned int VAO, VBO, EBO;
	vector<Cubito> cubitos;

	void setBuffers() {
		// BUFFER
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glGenBuffers(1, &EBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);//Tipo de buffer
		//#Vertices
		glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 120 * nCubitos, NULL, GL_STATIC_DRAW);//Copia la data al buffer

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		// position attribute
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		// texture coord attribute
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);
	}
	void intialiceTextures(){
		//Parametros de textura
		glEnable(GL_BLEND);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		//Tipo de textura que queremos *
		shaderCamara.setInt("texture1", 1);
	}
	void setUpTextures() {
		//back //front //left //derecha //abajo //arriba
		Cubito* cara[9];
		char caraName[7] = "BFLRDU";
		for (int i = 0; i < 6; i++) {
			pCube.getCubitosARotar(caraName[i], cara);
			for (int x = 0, j = 0; x < 3; x++)
				for (int y = 0; y < 3; y++, j++) {
					string imageFile = string(1, caraName[i] + 32) + to_string(x + 1) + to_string(y + 1) + ".png";
					//cout << "configure_file(${CMAKE_CURRENT_SOURCE_DIR}/textures/" + imageFile  + " ${CMAKE_CURRENT_BINARY_DIR} COPYONLY)" << endl;;
					cara[j]->loadTexture(i, imageFile);
				}
		}

	}
	void breather() {
		for (int i = 0; i < nCubitos; i++) cubitos[i].breather();
	}
	void cubesCorrectPosition() {
		float M[4][4];
		getIdentidad(M);
		float esquina[3] = { cubitos[0].vertices[3 * 5],cubitos[0].vertices[3 * 5 + 1], cubitos[0].vertices[3 * 5 + 2], };
		int c = 0;
		for (float i = -0.6; i < 0.5; i += 0.4) {//y
			for (float j = -0.6; j < 0.5; j += 0.4) {//z
				for (float k = -0.6; k < 0.5; k += 0.4) {//x
					M[0][3] = k - esquina[0];
					M[1][3] = i - esquina[1];
					M[2][3] = j - esquina[2];
					cubitos[c].aplicarMatriz(M);
					c++;
				}
			}
		}
	}
	void cubesOnTheGround() {
		float M[4][4];
		getIdentidad(M);
		//Esquina de abajo delantera
		float esquina[3] = { cubitos[0].vertices[3 * 5],cubitos[0].vertices[3 * 5 + 1], cubitos[0].vertices[3 * 5 + 2], };
		int c = 0;
		for (float i = -1; i < 0.9; i += 0.4) {
			for (float j = -1; j < 1.3; j += 0.4) {
				M[0][3] = i - esquina[0];
				M[1][3] = -1 - esquina[1];
				M[2][3] = j - esquina[2];
				cubitos[c].aplicarMatriz(M);
				c++;
				if (c > 26) break;
			}
		}

		c = 0;
		for (float i = -0.6; i < 0.5; i += 0.4) {//y
			for (float j = -0.6; j < 0.5; j += 0.4) {//z
				for (float k = -0.6; k < 0.5; k += 0.4) {//x
					cubitos[c].starterPosition[0] = k;
					cubitos[c].starterPosition[1] = i;
					cubitos[c].starterPosition[2] = j;
					c++;
				}
			}
		}
	}

	Cubo() {
		//PARAMS
		glPointSize(4);
		glLineWidth(6);
		
		shaderCamara.set("7.1.camera.vs", "7.1.camera.fs");

		setBuffers();
		intialiceTextures();
		

		for (int i = 0; i < nCubitos; i++) {
			cubitos.push_back(Cubito(i));
			//cubitos[i].loadData();
		}
		pCube.setCubo(cubitos);

		// Colocar cubitos en posicion
		//cubesCorrectPosition();
		cubesOnTheGround();
		
		setUpTextures();
	}

	bool goToStarterPos() {
		for (int i = 26; i >= 0; i--) {
			if (!cubitos[i].goToStarterPosition()) {
				return 0;//Aun no completo todos los cubos
				//break;
			}
		}
		return 1;
	}
	void show() {
		for (int i = 0; i < nCubitos; i++) {
			cubitos[i].draw();
		}
	}

};


#endif
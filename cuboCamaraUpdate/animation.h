#ifndef ANIMATION_H
#define ANIMATION_H

#include <deque>

#include "solver.h"
#include "cubito.h"
#include "plainCube.h"
#include "transform.h"
#include "camaraAnimations.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define PI 3.1416

PlainCubo pCube;
bool solving = false;


struct animate {
	int pendings = 0;
	bool onAnim = false;//Que falta actualizar indices
	const int pasos = 18;
	const float angleAnimation = 5 * PI / 180;

	deque <pair<char, bool>> pendingAnimations;//accion, horario?
	float mTransformacion[4][4];
	int pasosRestantes = 0;
	float rotationAngle;
	int rIndex[5][5][2];//Por ahora copiar matriz
	bool derecha;
	char A;//Accion
	Cubito* cubitosARotar[9];

	//Para actualizar los punteros de pCube
	int rb[5][5][2] = {
		8,3, 5,8, 0,5, 3,0, 8,3,
		8,4, 4,8, 0,4, 4,0, 8,4,
		8,5, 3,8, 0,3, 5,0, 8,5,
		9,3, 9,5, 11,5, 11,3, 9,3,
		9,4, 10,5, 11,4, 10,3, 9,4,
	};
	int rd[5][5][2] = {
		5,3, 5,6, 9,5, 5,0, 5,3,
		5,4, 5,7, 9,4, 5,1, 5,4,
		5,5, 5,8, 9,3, 5,2, 5,5,
		6,3, 6,5, 8,5, 8,3, 6,3,
		6,4, 7,5, 8,4, 7,3, 6,4,
	};
	int ru[5][5][2] = {
		11,3, 3,8, 3,5, 3,2, 11,3,
		11,4, 3,7, 3,4, 3,1, 11,4,
		11,5, 3,6, 3,3, 3,0, 11,5,
		0,3, 0,5, 2,5, 2,3, 0,3,
		0,4, 1,5, 2,4, 1,3, 0,4,
	};
	int rr[5][5][2] = {//blanco
		2,5, 11,5, 8,5, 5,5, 2,5,
		1,5, 10,5, 7,5, 4,5, 1,5,
		0,5, 9,5, 6,5, 3,5, 0,5,
		3,6, 3,8, 5,8, 5,6, 3,6,
		3,7, 4,8, 5,7, 4,6, 3,7,
	};
	int rf[5][5][2] = {//rojo
		2,3, 3,6, 6,5, 5,2, 2,3,
		2,4, 4,6, 6,4, 4,2, 2,4,
		2,5, 5,6, 6,3, 3,2, 2,5,
		3,3, 3,5, 5,5, 5,3, 3,3,
		3,4, 4,5, 5,4, 4,3, 3,4,
	};
	int rl[5][5][2] = {//amarillo
		0,3, 3,3, 6,3, 9,3, 0,3,
		1,3, 4,3, 7,3, 10,3, 1,3,
		2,3, 5,3, 8,3, 11,3, 2,3,
		3,0, 3,2, 5,2, 5,0, 3,0,
		3,1, 4,2, 5,1, 4,0, 3,1,
	};

	void rotarIndicesDer(int rotacion[5][5][2]) {
		for (int i = 0; i < 5; i++) {
			Cubito* aux = pCube.get(rotacion[i][0]);
			for (int j = 0; j < 3; j++)
				pCube.set(rotacion[i][j], pCube.get(rotacion[i][j + 1]));
			pCube.set(rotacion[i][3], aux);
		}
	}
	void rotarIndicesIzq(int rotacion[5][5][2]) {
		for (int i = 0; i < 5; i++) {
			Cubito* aux = pCube.get(rotacion[i][3]);
			for (int j = 3; j > 0; j--)
				pCube.set(rotacion[i][j], pCube.get(rotacion[i][j - 1]));
			pCube.set(rotacion[i][0], aux);
		}
	}

	void aplicarMatrixCara(float M[4][4]) {
		for (int i = 0; i < 9; i++)
			cubitosARotar[i]->aplicarMatriz(M);//Load data automaticamente
	}
	void updateColors(char A) {
		for (int i = 0; i < 9; i++)
			cubitosARotar[i]->updateColorPos(A);
	}

	void copyRIndex(int rIN[5][5][2], int rOUT[5][5][2]) {
		for (int i = 0; i < 5; i++) {
			for (int j = 0; j < 5; j++) {
				rOUT[i][j][0] = rIN[i][j][0];
				rOUT[i][j][1] = rIN[i][j][1];
			}
		}
	}
	void B(bool antihorario = false) {
		if (antihorario) {
			rotationAngle = -1 * rotationAngle;
			derecha = false;
		}
		mRotarZ(mTransformacion, rotationAngle);
		copyRIndex(rb, rIndex);
	}
	void R(bool antihorario = false) {
		if (antihorario) derecha = false;
		else rotationAngle = -1 * rotationAngle;
		mRotarX(mTransformacion, rotationAngle);
		copyRIndex(rr, rIndex);
	}
	void L(bool antihorario = false) {
		if (antihorario) {
			rotationAngle = -1 * rotationAngle;
			derecha = false;
		}
		mRotarX(mTransformacion, rotationAngle);
		copyRIndex(rl, rIndex);
	}
	void U(bool antihorario = false) {
		if (antihorario) derecha = false;
		else rotationAngle = -1 * rotationAngle;
		mRotarY(mTransformacion, rotationAngle);
		copyRIndex(ru, rIndex);
	}
	void D(bool antihorario = false) {
		if (antihorario) {
			rotationAngle = -1 * rotationAngle;
			derecha = false;
		}
		mRotarY(mTransformacion, rotationAngle);
		copyRIndex(rd, rIndex);
	}
	void F(bool antihorario = false) {
		if (antihorario) derecha = false;
		else rotationAngle = -1 * rotationAngle;
		mRotarZ(mTransformacion, rotationAngle);
		copyRIndex(rf, rIndex);
	}

	void setAnim() {
		if (!pendingAnimations.empty()) {
			if (pendingAnimations.front().first == 'S') { //Reinicia los centros
				fixCentros();
				pendingAnimations.pop_front();
				return;
			}

			derecha = true;
			rotationAngle = angleAnimation;//Restart angle

			//Update animation
			A = pendingAnimations.front().first;
			bool horario = pendingAnimations.front().second;
			pCube.getCubitosARotar(A, cubitosARotar);

			//Actualizar orientacion del centro, asume que es horario
			cubitosARotar[4]->orientacionCentro += (horario ? 1 : -1);//Actualiza en el cubito del centro

			if (A == 'F') F(!horario);
			else if (A == 'B') B(!horario);
			else if (A == 'U') U(!horario);
			else if (A == 'D') D(!horario);
			else if (A == 'L') L(!horario);
			else if (A == 'R') R(!horario);

			pendingAnimations.pop_front();
			pasosRestantes = pasos;
			onAnim = true;
		}
	}

	void anim() {
		if (solving) return;
		if (pasosRestantes) {
			aplicarMatrixCara(mTransformacion);
			pasosRestantes--;
		}
		else {
			if (onAnim) {
				//Update colors
				if (rotationAngle < 0) updateColors(char(A + 32));//Pasar a minuscula
				else updateColors(A);
				//Update indexes
				if (derecha) rotarIndicesDer(rIndex);
				else rotarIndicesIzq(rIndex);
				//antihorario izquierda
				onAnim = false;

			}
			else setAnim();
		}
	}

	void addAnim(char A, bool horario = 0) {
		pendingAnimations.push_back(pair<char, bool>(A, horario));
	}

	void solve() {
		solving = true;
		string solution = solver(pCube.stringCubo());
		cout << solution << endl;
		size_t e1 = 0, e2 = solution.find(" ");
		string accion = solution.substr(e1, e2);
		while (e1 != string::npos) {
			//cout << accion << "-";
			if (accion[0] == 'F') {
				addAnim('F', accion[1] == '\'');
				if (accion[1] == '2') addAnim('F');
			}
			else if (accion[0] == 'B') {
				addAnim('B', accion[1] == '\'');
				if (accion[1] == '2') addAnim('B');
			}
			else if (accion[0] == 'U') {
				addAnim('U', accion[1] == '\'');
				if (accion[1] == '2') addAnim('U');
			}
			else if (accion[0] == 'D') {
				addAnim('D', accion[1] == '\'');
				if (accion[1] == '2') addAnim('D');
			}
			else if (accion[0] == 'L') {
				addAnim('L', accion[1] == '\'');
				if (accion[1] == '2') addAnim('L');
			}
			else if (accion[0] == 'R') {
				addAnim('R', accion[1] == '\'');
				if (accion[1] == '2') addAnim('R');
			}

			accion = solution.substr(e1 + 1, e2 - e1 - 1);
			e1 = e2;
			e2 = solution.find(" ", e2 + 1);
		}
		addAnim('S');//Inidica que termino de resolver y debe arreglar los centros
		solving = false;
	}

	void fixCentros() {
		//iterar cada centro, aplicar matriz de transformacion segun su orientacion
		int centrosCoord[][2] = { 4, 5, 10, 4, 4, 1, 4, 7, 7, 4, 1, 4 };//y x z
		Cubito* aux;
		aux = pCube.get(4, 5);
		if (aux->orientacionCentro) {
			mRotarY(mTransformacion, 90 * PI / 180 * aux->orientacionCentro);//Obtiene matriz de rotacion
			aux->aplicarMatriz(mTransformacion);//Modifica el cubito
			aux->orientacionCentro = 0;//Resetea el valor del centro
		}
		aux = pCube.get(10, 4);
		if (aux->orientacionCentro) {
			mRotarY(mTransformacion, 90 * PI / 180 * aux->orientacionCentro);//Obtiene matriz de rotacion
			aux->aplicarMatriz(mTransformacion);//Modifica el cubito
			aux->orientacionCentro = 0;//Resetea el valor del centro
		}
		aux = pCube.get(4, 1);
		if (aux->orientacionCentro) {
			mRotarX(mTransformacion, 90 * PI / 180 * aux->orientacionCentro);//Obtiene matriz de rotacion
			aux->aplicarMatriz(mTransformacion);//Modifica el cubito
			aux->orientacionCentro = 0;//Resetea el valor del centro
		}
		aux = pCube.get(4, 7);
		if (aux->orientacionCentro) {
			mRotarX(mTransformacion, 90 * PI / 180 * aux->orientacionCentro);//Obtiene matriz de rotacion
			aux->aplicarMatriz(mTransformacion);//Modifica el cubito
			aux->orientacionCentro = 0;//Resetea el valor del centro
		}
		aux = pCube.get(7, 4);
		if (aux->orientacionCentro) {
			mRotarZ(mTransformacion, 90 * PI / 180 * aux->orientacionCentro);//Obtiene matriz de rotacion
			aux->aplicarMatriz(mTransformacion);//Modifica el cubito
			aux->orientacionCentro = 0;//Resetea el valor del centro
		}
		aux = pCube.get(1, 4);
		if (aux->orientacionCentro) {
			mRotarZ(mTransformacion, 90 * PI / 180 * aux->orientacionCentro);//Obtiene matriz de rotacion
			aux->aplicarMatriz(mTransformacion);//Modifica el cubito
			aux->orientacionCentro = 0;//Resetea el valor del centro
		}
	}

};
animate animation;

#endif
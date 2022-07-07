#ifndef TRANSFORM_H
#define TRANSFORM_H
#include <math.h>

// timing
float deltaTime = 0.0f;	// time between current frame and last frame
float lastFrame = 0.0f;
float currentFrame;
float startAnimationFrame = 0;
float localFrame = 0;


void getIdentidad(float M[4][4]) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++)
			M[i][j] = 0;
		M[i][i] = 1;
	}
}
void transformPunto(float T[][4], float* _punto) {
	float punto[4] = { _punto[0],_punto[1], _punto[2], 1 };
	float p[4] = { 0, 0, 0, 0 };
	for (int i = 0; i < 4; i++)
		for (int x = 0; x < 4; x++)
			p[i] += T[i][x] * punto[x];
	for (int i = 0; i < 3; i++)
		_punto[i] = p[i];// p[3];
}
void transformPuntos(float T[][4], float* puntos, int n, int ini = 0) {//T * p
	for (int i = 0; i < n * 5; i += 5)
		transformPunto(T, puntos + i);
}
void mRotarX(float M[4][4], float angulo) {
	getIdentidad(M);
	M[1][1] = M[2][2] = cos(angulo);
	M[1][2] = sin(angulo);
	M[2][1] = -sin(angulo);
}
void mRotarY(float M[4][4], float angulo) {
	getIdentidad(M);
	M[0][0] = M[2][2] = cos(angulo);
	M[0][2] = -sin(angulo);
	M[2][0] = sin(angulo);
}
void mRotarZ(float M[4][4], float angulo) {
	getIdentidad(M);
	M[0][0] = M[1][1] = cos(angulo);
	M[0][1] = sin(angulo);
	M[1][0] = -sin(angulo);
}
void mEscala(float M[4][4], float x) {
	getIdentidad(M);
	M[0][0] = M[1][1] = M[2][2] = x;
}
void mTraslacion(float M[4][4], float x, float y, float z ) {
	getIdentidad(M);
	M[0][3] = x;
	M[1][3] = y;
	M[2][3] = z;
}

#endif
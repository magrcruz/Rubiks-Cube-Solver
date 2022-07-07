#ifndef PLAINCUBE_H
#define PLAINCUBE_H

#include <vector>
#include "cubito.h"

struct PlainCubo {
	Cubito* plainCube[12][9];

	Cubito* get(int pos[]) { return plainCube[pos[0]][pos[1]]; }
	Cubito* get(int x, int y) { return plainCube[x][y]; }
	void set(int pos[], Cubito* c) { plainCube[pos[0]][pos[1]] = c; }
	void set(int x, int y, Cubito* c) { plainCube[x][y] = c; }

	PlainCubo() {};
	void setCubo(vector<Cubito>& c) {
		Cubito* pCube[12][9] = {
			0,0,0,&c[18],&c[19],&c[20],0,0,0,
			0,0,0,&c[21],&c[22],&c[23],0,0,0,
			0,0,0,&c[24],&c[25],&c[26],0,0,0,
			&c[18],&c[21],&c[24],&c[24],&c[25],&c[26],&c[26],&c[23],&c[20],
			&c[9],&c[12],&c[15],&c[15],&c[16],&c[17],&c[17],&c[14],&c[11],
			&c[0],&c[3],&c[6],&c[6],&c[7],&c[8],&c[8],&c[5],&c[2],
			0,0,0,&c[6],&c[7],&c[8],0,0,0,
			0,0,0,&c[3],&c[4],&c[5],0,0,0,
			0,0,0,&c[0],&c[1],&c[2],0,0,0,
			0,0,0,&c[0],&c[1],&c[2],0,0,0,
			0,0,0,&c[9],&c[10],&c[11],0,0,0,
			0,0,0,&c[18],&c[19],&c[20],0,0,0,
		};
		for (int i = 0; i < 12; i++)
			for (int j = 0; j < 9; j++)
				plainCube[i][j] = pCube[i][j];
	}
	string stringCubo() {
		//UUUUUUUUURRRRRRRRRFFFFFFFFFDDDDDDDDDLLLLLLLLLBBBBBBBBB
		//Order color pos// back front left derecha abajo arriba
		string output;
		string colorC = "ORYWBG";
		for (int i = 0; i < 3; i++)//U
			for (int j = 3; j < 6; j++)
				output += colorC[plainCube[i][j]->colorPos[5]];
		for (int i = 6; i < 9; i++)//D
			for (int j = 3; j < 6; j++)
				output += colorC[plainCube[i][j]->colorPos[4]];
		for (int i = 3; i < 6; i++)//F
			for (int j = 3; j < 6; j++)
				output += colorC[plainCube[i][j]->colorPos[1]];
		for (int i = 11; i >= 9; i--)//B
			for (int j = 5; j >= 3; j--)
				output += colorC[plainCube[i][j]->colorPos[0]];
		for (int i = 3; i < 6; i++)//L
			for (int j = 0; j < 3; j++)
				output += colorC[plainCube[i][j]->colorPos[2]];
		for (int i = 3; i < 6; i++)//R
			for (int j = 6; j < 9; j++)
				output += colorC[plainCube[i][j]->colorPos[3]];
		return output;
	}
	void getCubitosARotar(char A, Cubito* cubitos[9]) {
		//Obtiene que cubitos se deben rotar segun el mapa en excel
		int a, b;
		switch (A) {
		case 'F'://Front
			a = b = 3; break;
		case 'R'://Right
			a = 3; b = 6; break;
		case 'L':
			a = 3; b = 0; break;
		case 'U':
			a = 0; b = 3; break;
		case 'D'://Down
			a = 6; b = 3; break;
		case 'B'://Back
			a = 9; b = 3; break;
		}
		for (int i = a, k = 0; i < a + 3; i++)
			for (int j = b; j < b + 3; j++, k++)
				cubitos[k] = plainCube[i][j];
	}
};


#endif
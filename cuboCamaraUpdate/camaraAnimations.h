#pragma once
#include <math.h>
#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>


//*/
// camera
glm::vec3 cameraPos = glm::vec3(0.0f, 0.0f, 2.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

struct Animation {
	//virtual void setUpParameters() = 0;
	virtual void updatePos() = 0;
};

class Rebotar : public Animation {
	float r = 2, k = 1, reference = 0, reset = 5;
	void updatePos() {
		cameraPos.x = r * cos(localFrame);
		cameraPos.y = k * (localFrame) * sin(localFrame);
		cameraPos.z = r * sin(localFrame);
	}
};
class Espiral : public Animation {
	float r = 0.5, k = 0.5;
	void updatePos() {
		cameraPos.x = r * localFrame * cos(localFrame);
		cameraPos.y = k * localFrame + 1.5;
		cameraPos.z = r * localFrame * sin(localFrame);
	}
};
class Lissajous : public Animation {
	float amplitud = 2;
	float f1 = 0.5;
	float f2 = 0.5;
	float desfase = 0.5;
	void updatePos() {
		cameraPos.x = amplitud * cos(f1 * localFrame);
		cameraPos.y = 2;
		cameraPos.z = amplitud * sin(f2 * localFrame + desfase);
	}
};
class XFijo : public Animation {
	float rad = 2;
	void updatePos() {
		cameraPos.z = rad * cos(localFrame);
		if (cameraPos.z < 0) cameraUp.y = -1;
		else cameraUp.y = 1;
		cameraPos.y = rad * sin(localFrame);
	}
};
class YFijo : public Animation {
	float rad = 2;
	void updatePos() {
		cameraPos.x = rad * sin(currentFrame);
		cameraPos.z = rad * cos(currentFrame);
	}
};

struct animationCamera{
	// t es localFrame
	glm::vec3 cameraStartPos = glm::vec3(0.0f, 0.0f, 2.0f);
	Animation* anim = 0;

	void move() {
		localFrame = currentFrame - startAnimationFrame ;
		if (anim) anim->updatePos();
	}
	void setUp(char A) {
		//lastFrame = 0;
		cameraUp.y = 1;
		startAnimationFrame = currentFrame;
		if (anim) {
			delete anim;
			anim = 0;
		}
		switch (A) {
		case 'H': anim = new Rebotar; break;
		case 'E': anim = new Espiral; break;
		case 'L': anim = new Lissajous; break;
		case 'X': anim = new XFijo; break;
		case 'Y': anim = new YFijo; break;
		default:
			break;
		}

	}
	~animationCamera() {
		if (anim) delete anim;
	}

	// Pasos para agregar una animacion
	// 1. Buscar la forma parametrica de la ecuacion
	// 2. Crear una clase hija de la clase animation Animation
	// 3. Colocar en la clase hija los parametros necesarios y
	//    en la funcion updatePos actualizar la posicion x y z
	//    de la camara segun la funcion parametrica
	// 4. En la funcion setUp agregar el char en el switch
	// 5. Agregar en key_callback la llamada a Magic.setUp('A')
	// 6. Con todo :3
};

animationCamera Magic;
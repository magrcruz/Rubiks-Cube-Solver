#include <glad/glad.h>
#include <glfw/glfw3.h>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "shader/shader.h"
#include "transform.h"
#include "cubo.h"
#include "camaraAnimations.h"
using namespace std;

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glad_glViewport(0, 0, width, height);
}
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

// settings
const unsigned int SCR_WIDTH = 600;
const unsigned int SCR_HEIGHT = 600;
const char title[] = "LearnOpenGL";



bool horario = true;
int main() {
	//Initialice and Setup
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Creating a window
	window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, title, NULL, NULL);
	//Parameters: width, height, title, monitor for full screen, share resources with window
	if (window == NULL) {
		cout << "Failed to create GLFW window" << endl;
		glfwTerminate();//Destruye ventanas y limpia recursos
		return -1;
	}
	glfwMakeContextCurrent(window);//Hace actual el contexto de la ventana

	//Load glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		cout << "Failed to initialize GLAD" << endl;
		return -1;
	}

	glEnable(GL_DEPTH_TEST);

	glfwSetKeyCallback(window, key_callback);//Eventos de teclado
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);// Identifica cambios de tamanio en la ventana
	glViewport(0, 0, SCR_WIDTH, SCR_HEIGHT);//TRansform coordinates to screen size
	//location of lower left corner, width and height

	Cubo temp;

	shaderCamara.use();
	
	
	// pass projection matrix to shader (as projection matrix rarely changes there's no need to do this per frame)
	// -----------------------------------------------------------------------------------------------------------
	///*
	glm::mat4 projection = glm::perspective(glm::radians(90.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	shaderCamara.setMat4("projection", projection);
	// camera/view transformation
	glm::mat4 view = glm::lookAt(cameraPos, cameraFront, cameraUp);
	shaderCamara.setMat4("view", view);
	shaderCamara.setVec4("ourColor", 0.1f, 0.5f, 0.3f, 0.0f);
	//*/
	
	//glPolygonMode(GL_FRONT_AND_BACK, GL_TRIANGLES);


	shaderCamara.use();
	//shader.setVec4("ourColor", 0.1f, 0.2f, 0.3f, 0.0f);
	//glBindVertexArray(VAO);

	//To keep drawing and not quit inmediately
	// RENDER LOOP
	int goingToStarterPosition = 2;
	

	while (!glfwWindowShouldClose(window)){//Check if GLFW has been instructed to close
		// per-frame time logic
		// --------------------
		///*
		currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;//*/

		//Clear window
		glClearColor(233.0/255.0, 230.0/255.0, 225.0/255.0, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		

		// activate shader
		shaderCamara.use();

		// camera/view transformation
		///*
		glm::mat4 view = glm::lookAt(cameraPos, cameraFront, cameraUp);
		shaderCamara.setMat4("view", view); //*/

		//RENDERING COMANDS HERE
		if (goingToStarterPosition == 2) {
			if(temp.goToStarterPos()) goingToStarterPosition--;
		}
		else if (goingToStarterPosition == 1) {
			temp.cubitos.clear();
			for (int i = 0; i < nCubitos; i++) {
				temp.cubitos.push_back(Cubito(i));
			}
			pCube.setCubo(temp.cubitos);
			temp.setUpTextures();
			temp.cubesCorrectPosition();
			goingToStarterPosition = 0;
		}
		
		temp.show();
		temp.breather();
		animation.anim();
		Magic.move();

		glfwSwapBuffers(window);//swap the color buffer
		glfwPollEvents();//Check events Triggered (keyboard o mouse)
		// calls the corresponding functions registered by callback methods
	}

	glfwTerminate();
	return 0;
}

float rad = 2;
int signo = 1;
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods){
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	// Movimientos de las camadas
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) animation.addAnim('F', horario);
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) animation.addAnim('B', horario);
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) animation.addAnim('R', horario);
	if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) animation.addAnim('L', horario);
	if (glfwGetKey(window, GLFW_KEY_G) == GLFW_PRESS) animation.addAnim('U', horario);
	if (glfwGetKey(window, GLFW_KEY_H) == GLFW_PRESS) animation.addAnim('D', horario);
	if (glfwGetKey(window, GLFW_KEY_J) == GLFW_PRESS) horario = true;
	if (glfwGetKey(window, GLFW_KEY_K) == GLFW_PRESS) horario = false;

	// Movimientos de la camara
	float cameraSpeed = static_cast<float>(20 * deltaTime);
	//float cameraSpeed = 1;
	if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS) cameraPos.x += cameraSpeed * signo;
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) cameraPos.y += cameraSpeed * signo;
	if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS) cameraPos.z += cameraSpeed * signo;

	if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) cameraFront.x += cameraSpeed * signo;
	if (glfwGetKey(window, GLFW_KEY_T) == GLFW_PRESS) cameraFront.y += cameraSpeed * signo;
	if (glfwGetKey(window, GLFW_KEY_Y) == GLFW_PRESS) cameraFront.z += cameraSpeed * signo;

	if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) signo = 1;
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS) signo = -1;

	// Animacion de la camara
	if (glfwGetKey(window, GLFW_KEY_Z) == GLFW_PRESS) Magic.setUp('X');
	if (glfwGetKey(window, GLFW_KEY_X) == GLFW_PRESS) Magic.setUp('Y');
	if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
		//Espiral
		Magic.setUp('E');
	}
	if (glfwGetKey(window, GLFW_KEY_V) == GLFW_PRESS) {
		//Yoyo
		Magic.setUp('H');
	}
	
	if (glfwGetKey(window, GLFW_KEY_B) == GLFW_PRESS) {
		//Lissajous 
		Magic.setUp('L');
	}
	
	if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS) {
		Magic.setUp(' ');
	}

	// Solver
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS) animation.solve();
	
}
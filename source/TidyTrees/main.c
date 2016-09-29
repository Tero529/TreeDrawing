#include "binaryTree.h"
#include "WetherellShannon.c"

//GLEW
#define GLEW_STATIC
#include <GL/glew.h>


// GLFW
#include <GLFW/glfw3.h>


//Window dimensions
int WIDTH=800,HEIGHT=600;

int main(){

	/*Create tree to be drawn and run it through the
		WetherellShannon Algorithm to generate the x and
		y values for each node */

	node *root=createTree();
	enum AlgorithmType secondPass=NORMAL;
	generateWetherellShannon(root,maxHeight,secondPass);
	inorderPrint(root);

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

	//Create the Window object
	GLFWwindow* window = glfwCreateWindow(WIDTH,HEIGHT,"Wetherell Shannon Tree Drawing",NULL,NULL);
	if(window == NULL){
		printf("Window Creation has failed\n");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

  //GLEW is used to manage the function pointers to OpenGL
	glewExperimental= GL_TRUE;
	if(glewInit() != GLEW_OK){
		printf("GLEW Initialization has failed\n");
		glfwTerminate();
		return -1;
	}

	/*Set the viewPort size to display data and coordinates
		with respect to the window
		In effect (-1,-1) is mapped to (0,WIDTH) and (0,HEIGHT)*/
	int width, height;
	glfwGetFramebufferSize(window,&width,&height);
	glViewport(0,0,width,height);

	while (!glfwWindowShouldClose(window)){
		glfwPollEvents();
		glfwSwapBuffers(window);
	}
	glfwTerminate();
	return 0;
}

/**Author's Name:          Ikamjot Hundal
 * Last Modified By:       Ikamjot Hundal
 * Date Last Modified:     August 26, 2026
 * Description:            Main file to display the graphics
 * ------------------------------------------------------------------------
 * Revision History:
 */
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
using namespace std;


// checking glad works or nah basically
static bool checking_glad_initalize_or_not()
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		cout << "Failed to initalize GLAD" << endl;
		return false;
	}

	return true;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}


// get DA BALL ROLLINNNNNN
int main()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // what option to configure
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); // an integer that set the value MWHAHAHAHA

	// get access to a smaller subset of OpenGL features without backwards-compatible features
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// variable for creating da window
	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);



	if (window == NULL)
	{
		cout << "failed to create da glfw window smh smh" << endl;
		glfwTerminate();
		return -1;
	}
	
	// checking if glad works or naj
	glfwMakeContextCurrent(window);

	if (!checking_glad_initalize_or_not())
	{
		glfwTerminate();
		return -1;
	}

	//give the user ability to resize the window 
	framebuffer_size_callback(window, 800, 600);

	// tell the glfw that we wanna call the function
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	// a way to not make window close immediately 
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// clean the allocated glfw resources. 
	glfwTerminate();
	return 0;


}



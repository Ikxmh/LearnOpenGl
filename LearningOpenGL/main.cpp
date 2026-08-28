/**Author's Name:          Ikamjot Hundal
 * Last Modified By:       Ikamjot Hundal
 * Date Last Modified:     August 27, 2026
 * Description:            Main file to display the graphics
 * ------------------------------------------------------------------------
 * Revision History: Changed the colour of Rendering and added variables. (August 27, 2026)
 */
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

using namespace std;


// variables 

const char *vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
" gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";

const char* fragmentShaderSource = R"(
#version 330 core
out vec4 FragColour;
void main()
{
	FragColour = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

unsigned int vertexShader; 
unsigned int fragmentShader;

float verticles[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f,
};

unsigned int VBO; // vertex buffer objects 

int success;

char infoLog[512];

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


// get da window going 
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
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
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);


	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		cout << "error::shader::vertex::compilation_failed\n" << infoLog << endl;
	}

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);

	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	// a way to not make window close immediately 
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		//probably will render here
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		// check and call events and swap the buffers 
		glfwPollEvents();
		glfwSwapBuffers(window);
		
	}

	// clean the allocated glfw resources. 
	glfwTerminate();
	return 0;


}



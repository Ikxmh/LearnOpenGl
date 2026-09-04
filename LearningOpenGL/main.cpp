/**Author's Name:          Ikamjot Hundal
 * Last Modified By:       Ikamjot Hundal
 * Date Last Modified:     September 04, 2026
 * Description:            Main file to display the graphics
 * ------------------------------------------------------------------------
 * Revision History: Changed the colour of Rendering and added variables. (August 27, 2026)
 * Linked the both vertex and fragment shaders (August 31, 2026) 
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

const char *fragmentShaderSource = R"(
#version 330 core
out vec4 FragColour;
void main()
{
	FragColour = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

// Shader- Related Programs 
unsigned int vertexShader; 
unsigned int fragmentShader;
unsigned int shaderProgram;

float verticles[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f,
};

unsigned int VBO; // vertex buffer object 
unsigned int VAO; // vertex array object
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

// respond to input "Escape"
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

	// check if complication is successful with glGetShaderiv. 
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

	shaderProgram = glCreateProgram(); // Create a program and returns the ID reference. 

	// LINKING THEM TOGETHAAAAA
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	
	// thing go brr if no no work
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
	}

	// basically telling OpenGL how to interpret the vertex data per vertex attribute 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	/*
	* First parameter = specifies which vertex attribute we wanna configure.
	* (we already specified the location of the position vertex attribute in the vertex shader with layout (location = 0))
	* Set the location of the vertex attribute to 0, and since we want to pass data to this vertex attribute, we pass in 0
	* Next argument specifies the size of the vertex attribute (vec3 = composed of 3 values)
	* Third argument specifies the type of the data 
	* Fourth argument = asking if we wanted the data to be normalized
	* Fifth argument = the stride, and tell us the space between consecutive vertex attributes.
	* Since next set of position data is located exactly 3 times the size of a float away we specify that value as a stride
	* Last one = type void* = offset of where the position data begins in the buffer. 
	* Since position data is at the start of the data array - value = 0.
	*/

	glGenVertexArrays(1, &VAO);

	// Bind Vertex Array Object 
	glBindVertexArray(VAO);

	// copy the vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(verticles), verticles, GL_STATIC_DRAW);

	// set the vertex attributes pointers 
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	

	// a way to not make window close immediately 
	while (!glfwWindowShouldClose(window))
	{
		// input
		processInput(window);

		// probably will render background colour here
		
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw da triangle 
		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);



		// check and call events and swap the buffers 
		glfwPollEvents();
		glfwSwapBuffers(window);
		
	}


	// clean the allocated glfw resources. 
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	glfwTerminate();
	return 0;


}



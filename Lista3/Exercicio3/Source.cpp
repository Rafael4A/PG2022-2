#include <iostream>
#include <string>
#include <assert.h>

using namespace std;

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <../../glm/glm/glm.hpp>
#include <../../glm/glm/gtc/matrix_transform.hpp>
#include <../../glm/glm/gtc/type_ptr.hpp>

#include <../../shaders/Shader.h>

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

int setupGeometry();

const GLuint WIDTH = 1400, HEIGHT = 800;

enum Movement { Left, Right, Top, Down, Stop };
static Movement movement = Stop;

const float base = 50;

int main()
{
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "Lista 3 - Ex3", nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, key_callback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;

	}

	const GLubyte* renderer = glGetString(GL_RENDERER);
	const GLubyte* version = glGetString(GL_VERSION);
	cout << "Renderer: " << renderer << endl;
	cout << "OpenGL version supported " << version << endl;

	int width, height;
	
	

	Shader shader("../../dependencies/shaders/vertex_lista3.vs", "../../dependencies/shaders/fragment.fs");

	GLuint VAO = setupGeometry();

	GLint colorLoc = glGetUniformLocation(shader.ID, "inputColor");
	assert(colorLoc > -1);

	glUseProgram(shader.ID);

	glm::mat4 projection = glm::mat4(1);
	projection = glm::ortho(0.0f, 800.0f, 0.0f, 600.0f, -1.0f, 1.0f);

	GLint projLoc = glGetUniformLocation(shader.ID, "projection");
	glUniformMatrix4fv(projLoc, 1, false, glm::value_ptr(projection));

	float x = 400;
	float y = 300;

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		glClearColor(0.8f, 0.8f, 0.8f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glLineWidth(3);
		glPointSize(5);

		glBindVertexArray(VAO);

		glfwGetFramebufferSize(window, &width, &height);

		glm::mat4 model = glm::mat4(1);

		switch (movement) {
		case Left:
			if (x > base)
				x -= 5.0f;
			break;
		case Right:
			if (x < width - base)
				x += 5.0f;
			break;
		case Top:
			if (y < height - base)
				y += 5.0f;
			break;
		case Down:
			if (y > base)
				y -= 5.0f;
			break;
		default:
			break;
		}

		model = glm::translate(model, glm::vec3(x, y, 0));
		shader.setMat4("model", glm::value_ptr(model));

		glUniform4f(colorLoc, 0.0f, 0.0f, 1.0f, 1.0f);
		glDrawArrays(GL_TRIANGLES, 0, 3);

		glUniform4f(colorLoc, 1.0f, 0.0f, 1.0f, 1.0f);
		glDrawArrays(GL_POINTS, 0, 3);

		glViewport(0, 0, width, height);

		glBindVertexArray(0);

		glfwSwapBuffers(window);
	}
	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();
	return 0;
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
		movement = Right;
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
		movement = Left;
	}
	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
		movement = Top;
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
		movement = Down;
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		movement = Stop;
	}
}

int setupGeometry()
{
	GLfloat vertices[] = {
		-50, -50, 0.0,
		50, -50, 0.0,
		0.0, 50, 0.0,
	};

	GLuint VBO, VAO;

	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glGenVertexArrays(1, &VAO);

	glBindVertexArray(VAO);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);

	return VAO;
}
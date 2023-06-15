#include "imgui.h"
#include "imgui-SFML.h"
#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <iostream>

const GLint WIDTH = 1000, HEIGHT = 800;

const GLchar* vertexShaderSource = "#version 330 core\n"
"layout ( location = 0 ) in vec3 position;\n"
"void main()\n"
"{\n"
"gl_Position = vec4( position, 1.0f );\n"
"}";

const GLchar *fragmentShaderSource = "#version 330 core\n"
"out vec4 color\n"
"void main()\n"
"{\n"
"color = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
"}";

int main()
{
	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	settings.majorVersion = 3;
	settings.minorVersion = 3;
	settings.attributeFlags = sf::ContextSettings::Core;

	sf::Window window(sf::VideoMode(WIDTH, HEIGHT, 32), "OpenGL", sf::Style::Titlebar | sf::Style::Close, settings);
	

	glewExperimental = GL_TRUE;

	if (GLEW_OK != glewInit())
	{
		std::cout << "Failed to initialaize GLEW" << std::endl;

		return EXIT_FAILURE;
	}


	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);


	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	GLfloat vertices[] =
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.0f, 0.5f, 0.0f
	};

	GLuint VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);




	bool runing = true;

	while (runing)
	{
		sf::Event windowEvent;

		while (window.pollEvent(windowEvent))
		{
			switch (windowEvent.type)
			{
			case sf::Event::Closed:
				runing = false;

				break;
			}
		}


		glClearColor(0.5f, 0.5f, 0.5f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);

		window.display();

	}
	window.close();

	glDeleteVertexArrays(1, & VAO);
	glDeleteBuffers(1, &VBO);

	return EXIT_SUCCESS;
}
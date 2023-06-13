#include <GL/glew.h>
#include <SFML/Graphics.hpp>
#include <iostream>

const GLint WIDTH = 1000, HEIGHT = 800;

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


		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		window.display();

	}
	window.close();

	return EXIT_SUCCESS;
}
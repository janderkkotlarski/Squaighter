#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include <SFML/Graphics.hpp>

class square
{	
	const sf::Vector2f m_wind{800.0f, 400.0f};	
	sf::Vector2f m_posit{0.5f*m_wind};
	
	const float m_divis{10.0f};
	
	const float m_side{m_wind.y/m_divis};	
	const float m_radius{0.5f*m_side};
	
	const float m_speed_mult{0.001f};
		
	const sf::Vector2f m_speed_right{m_speed_mult*m_wind.x, 0.0f};
	const sf::Vector2f m_speed_left{-m_speed_mult*m_wind.y, 0.0f};
	
	const float m_jump_mult{0.001f};
	
	const sf::Vector2f m_jump_up{0.0f, -m_speed_mult*m_wind.y};
	
	sf::Vector2f m_speed{0.0f, 0.0f};
	
	const float m_accel_mult{0.0001f};
	const sf::Vector2f m_accel{0.0f, m_accel_mult*m_wind.y};
		
	const sf::Color m_color{255, 255, 255};
	
	sf::RectangleShape m_square;
	
	
	
	public:
	
	void show_square(sf::RenderWindow window)
	{
		window.draw(m_square);		
	}
	
	square()
	{
		
	}
	
	~square()
	{		
	}
	
	// float m_health{100.0f};	
	
};

class floor
{
	const sf::Vector2f m_wind{800.0f, 400.0f};
	
	const float m_divis{10.0f};
	const float m_side{m_wind.y/m_divis};
	
	const sf::Vector2f m_posit{0.0f, m_wind.y - m_side};
	const sf::Vector2f m_dims{m_wind.x, m_side};
	
	
};

int window_maker(const sf::Vector2f& window_dims, const std::string& program_name)
{
	const sf::Color black{sf::Color(0, 0, 0)};
	
	sf::RenderWindow window(sf::VideoMode(window_dims.x, window_dims.y), program_name, sf::Style::Default);
		
	while (window.isOpen())
	{
		sf::Event event;
		
		window.clear(black);
		// windje.draw(sprait);
		window.display();
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window.close();
			return 0;
		}
		
		while (window.pollEvent(event))
		{			
			if (event.type == sf::Event::Closed)
			{
				window.close();
				return 0;
			}		
		}		
	}
	
	return 1;	
}

int main()
{
	const std::string program_name{"Squaighter"};
	
	std::cout << program_name << '\n';
	
	const sf::Vector2f window_dims{800.0f, 400.0f};
	
	return window_maker(window_dims, program_name);
} 

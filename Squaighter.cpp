#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include <SFML/Graphics.hpp>

class square
{	
	const sf::Vector2f m_windims{800.0f, 400.0f};	
	sf::Vector2f m_posit{0.5f*m_windims};
	
	const float m_divis{10.0f};
	
	const float m_side{m_windims.y/m_divis};	
	const float m_radius{0.5f*m_side};
	
	const sf::Vector2f m_sides{m_side, m_side};
	
	const float m_speed_mult{0.001f};
		
	const sf::Vector2f m_speed_right{m_speed_mult*m_windims.x, 0.0f};
	const sf::Vector2f m_speed_left{-m_speed_mult*m_windims.y, 0.0f};
	
	const float m_jump_mult{0.001f};
	
	const sf::Vector2f m_jump_up{0.0f, -m_speed_mult*m_windims.y};
	
	sf::Vector2f m_speed{0.0f, 0.0f};
	
	const float m_accel_mult{0.0001f};
	const sf::Vector2f m_accel{0.0f, m_accel_mult*m_windims.y};
		
	sf::Color m_color{255, 255, 255};
	
	sf::RectangleShape m_square;
	
	void set_square()
	{
		m_square.setSize(m_sides);
		m_square.setPosition(m_posit.x - m_radius, m_posit.y - m_radius);
		m_square.setFillColor(m_color);
	}
	
	public:
	
	void show_square(sf::RenderWindow& window)
	{
		window.draw(m_square);		
	}
	
	square(const sf::Vector2f& windims, const sf::Vector2f& start_rel, const sf::Color& color)
		: m_windims(windims), m_posit(start_rel.x*m_windims.x, start_rel.y*m_windims.y), m_side(m_windims.y/m_divis),	
		  m_radius(0.5f*m_side), m_sides(m_side, m_side),
		  m_speed_right(m_speed_mult*m_windims.x, 0.0f), m_speed_left(-m_speed_mult*m_windims.y, 0.0f),
		  m_jump_up(0.0f, -m_speed_mult*m_windims.y), m_accel(0.0f, m_accel_mult*m_windims.y),
		  m_color(color), m_square()
	{
		set_square();
	}
	
	~square()
	{		
	}
	
	// float m_health{100.0f};	
	
};

class floor
{
	const sf::Vector2f m_windims{800.0f, 400.0f};
	
	const float m_divis{10.0f};
	const float m_side{m_windims.y/m_divis};
	
	const sf::Vector2f m_posit{0.0f, m_windims.y - m_side};
	const sf::Vector2f m_dims{m_windims.x, m_side};
	
	
};

int window_maker(const sf::Vector2f& windims, const std::string& program_name)
{
	const sf::Color black{sf::Color(0, 0, 0)};
	const sf::Color light_red{sf::Color(191, 63, 63)};
	
	const sf::Vector2f left_start_rel{0.2f, 0.9f};
	
	square tess(windims, left_start_rel, light_red);
	
	sf::RenderWindow window(sf::VideoMode(windims.x, windims.y), program_name, sf::Style::Default);
		
	while (window.isOpen())
	{
		sf::Event event;
		
		window.clear(black);
		
		tess.show_square(window);
		
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
	
	const sf::Vector2f windims{800.0f, 400.0f};
	
	return window_maker(windims, program_name);
} 

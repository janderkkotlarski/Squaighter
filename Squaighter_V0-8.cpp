#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include <SFML/Graphics.hpp>

enum class wing {left, right};

class ground
{
	const sf::Vector2f m_windims{800.0f, 400.0f};
	
	const float m_divis{10.0f};
	const float m_side{m_windims.y/m_divis};
	
	const sf::Vector2f m_posit{0.0f, m_windims.y - m_side};
	const sf::Vector2f m_dims{m_windims.x, m_side};
	
	sf::Color m_color{255, 255, 255};
	
	sf::RectangleShape m_rect;
	
	void set_rect_posit()
	{
		m_rect.setPosition(m_posit);
	}
	
	void set_rect()
	{
		m_rect.setSize(m_dims);
		set_rect_posit();
		m_rect.setFillColor(m_color);
	}
	
	public:
	
	void displaying(sf::RenderWindow& window)
	{
		window.draw(m_rect);
	}
	
	float show_posit_y()
	{
		return m_posit.y;
	}
	
	ground(const sf::Vector2f& windims, const float divis, const sf::Color& color)
		: m_windims(windims), m_divis(divis), m_side(m_windims.y/m_divis),
		  m_posit(0.0f, m_windims.y - m_side), m_dims(m_windims.x, m_side), m_color(color),
		  m_rect()
	{
		  set_rect();
	}
		  
	~ground()
	{
	}
	
};

class shot
{
	const float m_squide{1.0f};
	sf::Vector2f m_posit;
	
	const sf::Vector2f m_speed;
	
	const float m_side{0.25f*m_squide};
	const sf::Vector2f m_sides {m_side, m_side};
	const float m_radius{0.5f*m_side};
	
	
	const sf::Color m_dark{63, 63, 63};
	const sf::Color m_color;
	
	sf::RectangleShape m_square;
	
	void set_square_posit()
	{
		m_square.setPosition(m_posit.x - m_radius, m_posit.y - m_radius);
	}
	
	void set_square()
	{
		m_square.setSize(m_sides);
		set_square_posit();
		m_square.setFillColor(m_color);
	}
	
	public:
	
	float r_pout()
	{
		return m_radius;
	}
	
	float x_pout()
	{
		return m_posit.x;
	}
	
	float y_pout()
	{
		return m_posit.y;
	}
	
	void move_shot()
	{
		m_posit = m_posit + m_speed;
		set_square_posit();
	}
	
	void displaying(sf::RenderWindow& window)
	{
		window.draw(m_square);
	}
	
	shot(const float squide, const sf::Vector2f& posit, const sf::Vector2f& speed, const sf::Color& color)
		: m_squide(squide), m_posit(posit), m_speed(speed), m_side(0.25f*m_squide), m_sides(m_side, m_side),
		  m_radius(0.5f*m_side), m_color(color + m_dark), m_square()
		  {
			  set_square();
		  }
		  
	~shot()
	{
	}
	
	
};

class square
{	
	const sf::Vector2f m_windims{800.0f, 400.0f};
	sf::Vector2f m_posit{0.5f*m_windims};
	
	const wing m_winger{wing::left};
	
	const float m_divis{10.0f};
	
	const float m_side{m_windims.y/m_divis};	
	const float m_radius{0.5f*m_side};
	
	const sf::Vector2f m_sides{m_side, m_side};
	
	const float m_speed_mult{0.005f};
		
	const sf::Vector2f m_speed_right{m_speed_mult*m_windims.x, 0.0f};
	const sf::Vector2f m_speed_left{-m_speed_mult*m_windims.x, 0.0f};
	sf::Vector2f m_speed_vert{0.0f, 0.0f};
	
	const float m_jump_mult{0.019f};
	
	const sf::Vector2f m_jump_up{0.0f, -m_jump_mult*m_windims.y};
	
	const int m_max_jumps = 2;	
	int m_jumps = m_max_jumps;
	
	bool pressing = false;
	
	bool warping = false;
	
	sf::Vector2f m_speed{0.0f, 0.0f};
	
	const float m_accel_mult{0.0005f};
	const sf::Vector2f m_accel{0.0f, m_accel_mult*m_windims.y};
		
	sf::Color m_color{255, 255, 255};
	
	sf::RectangleShape m_square;
	
	const float m_shot_speed_mult{0.007f};
	
	sf::Vector2f m_shot_speed{m_shot_speed_mult*m_windims.x, 0.0f};
	
	std::vector <shot> m_shots;
	
	bool dressing{false};
	
	float r_pout()
	{
		return m_radius;
	}
	
	float x_pout()
	{
		return m_posit.x;
	}
	
	float y_pout()
	{
		return m_posit.y;
	}
	
	void x_pin(const float pin)
	{
		m_posit.x = pin;
	}
	
	void y_pin(const float pin)
	{
		m_posit.y = pin;
	}
	
	void reset_jumps()
	{
		m_jumps = m_max_jumps;
	}
	
	void set_wing()
	{
		if (m_winger == wing::left)
		{
			m_posit = sf::Vector2f(3.0f*m_radius, m_windims.y - 3.0f*m_radius);
		}
		else if (m_winger == wing::right)
		{
			m_posit = sf::Vector2f(m_windims.x - 3.0f*m_radius, m_windims.y - 3.0f*m_radius);
		}
	}
	
	void set_square_posit()
	{
		m_square.setPosition(m_posit.x - m_radius, m_posit.y - m_radius);
	}
	
	void set_square()
	{
		m_square.setSize(m_sides);
		set_square_posit();
		m_square.setFillColor(m_color);
	}
	
	void horizon_check()
	{
		if (m_posit.x < m_radius)
		{
			m_posit.x = m_radius;
		}
		
		if (m_posit.x > m_windims.x - m_radius)
		{
			m_posit.x = m_windims.x - m_radius;
		}
	}
	
	void move_right()
	{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) && (m_winger == wing::left)) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::L) && (m_winger == wing::right)))
		{
			m_posit += m_speed_right;
		}
		
		horizon_check();
	}
	
	void move_left()
	{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) && (m_winger == wing::left)) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::J) && (m_winger == wing::right)))
		{
			m_posit += m_speed_left;			
		}
		
		horizon_check();
	}
	
	void vertigo_check(ground& earth)
	{
		if (m_posit.y > earth.show_posit_y() - m_radius)
		{
			m_posit.y = earth.show_posit_y() - m_radius;
			m_speed_vert.y = 0.0f;
			m_jumps = m_max_jumps;
		}
	}
	
	void jump_up()
	{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) && (m_winger == wing::left)) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::I) && (m_winger == wing::right)))
		{
			if (!pressing && (m_jumps > 0))
			{
				m_speed_vert.y = m_jump_up.y;
				pressing = true;
				--m_jumps;				
			}		
		}
		else if (pressing)
		{
			pressing = false;
		}
	}
	
	void gravity(ground& earth)
	{
		m_speed_vert += m_accel;		
		jump_up();
		
		if (m_speed_vert.y > -m_jump_up.y)
		{
			m_speed_vert.y = -m_jump_up.y;
		}
		
		m_posit += m_speed_vert;
		vertigo_check(earth);
	}
	
	void warp(square& another)
	{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::S) && (m_winger == wing::left)) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::K) && (m_winger == wing::right)))
		{
			if (!warping)
			{
				const float x_pout_ = x_pout();
				const float o_x_pout = another.x_pout();
				
				if (o_x_pout > x_pout_)
				{
					if (o_x_pout <= m_windims.x - 2.5f*m_side)
					{
						m_posit.x = o_x_pout + 2.0f*m_side;
					}
					else if (o_x_pout >= 2.5f*m_side)
					{
						m_posit.x = o_x_pout - 2.0f*m_side;
					}
				}
				
				if (o_x_pout < x_pout_)
				{
					if (o_x_pout >= 2.5f*m_side)
					{
						m_posit.x = o_x_pout - 2.0f*m_side;
					}
					else if (o_x_pout <= m_windims.x - 2.5f*m_side)
					{
						m_posit.x = o_x_pout + 2.0f*m_side;
					}
				}

				warping = true;
			}
		}
		else if (warping)
		{
			warping = false;
		}
	}
	
	void collision_square(square& another)
	{
		const float delta_x{x_pout() - another.x_pout()};		
		const float delta_y{y_pout() - another.y_pout()};
		
		if ((abs(delta_y) >= abs(delta_x)) && (abs(delta_y) <= m_side))
		{
			if (delta_y <= 0)
			{
				y_pin(another.y_pout() - m_side);
				reset_jumps();
			}
		}
		
		if ((abs(delta_x) > abs(delta_y)) && (abs(delta_x) <= m_side))
		{
			if (delta_x <= 0)
			{
				const float x_middle{another.x_pout() + 0.5f*delta_x};
				
				x_pin(x_middle - m_radius);
				another.x_pin(x_middle + m_radius);
			}
		}
		
	}
	
	bool collision_shot(shot& own)
	{
		const float delta_x{x_pout() - own.x_pout()};		
		const float delta_y{y_pout() - own.y_pout()};
		
		const float distance{r_pout() + own.r_pout()};
			
		bool collision{false};
		
		if (((abs(delta_y) >= abs(delta_x)) && (abs(delta_y) <= distance)) ||
			((abs(delta_x) > abs(delta_y)) && (abs(delta_x) <= distance)))
		{
			collision = true;
		}
		
		return collision;		
	}
	
	bool collision_square_shot(square& another, shot& own)
	{
		const float delta_x{another.x_pout() - own.x_pout()};		
		const float delta_y{another.y_pout() - own.y_pout()};
		
		const float distance{another.r_pout() + own.r_pout()};
			
		bool collision{false};
		
		if (((abs(delta_y) >= abs(delta_x)) && (abs(delta_y) <= distance)) ||
			((abs(delta_x) > abs(delta_y)) && (abs(delta_x) <= distance)))
		{
			collision = true;
		}
		
		return collision;		
	}
	
	void move_shots()
	{
		const int shot_number{static_cast<int>(m_shots.size())};
		
		int count{0};
		
		while (count < shot_number)
		{
			m_shots[count].move_shot();
			++count;
		}
	}
	
	void moving(ground& earth, square& another)
	{
		move_left();
		move_right();		
		gravity(earth);
		warp(another);
		collision_square(another);
		set_square_posit();
		move_shots();
	}
	
	void display_square(sf::RenderWindow& window)
	{
		window.draw(m_square);
	}
	
	void display_shots(sf::RenderWindow& window)
	{
		int count = 0;
		
		while (count < static_cast<int>(m_shots.size()))
		{
			m_shots[count].displaying(window);
			++count;
		}
	}
	
	void shooting(square& another)
	{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::R) && (show_wing() == wing::left)) ||
			(sf::Keyboard::isKeyPressed(sf::Keyboard::P) && (show_wing() == wing::right)))
		{
			if (!dressing)
			{
				sf::Vector2f shot_speed{m_shot_speed};
				
				sf::Vector2f shot_posit{show_posit()};
				
				shot example{show_side(), show_posit(), shot_speed, show_color()};	
				
				const sf::Vector2f shot_disp{1.5f*sf::Vector2f(m_radius + example.r_pout(), 0.0f)};
				
				if (another.m_posit.x < m_posit.x)
				{
					shot_speed = -m_shot_speed;
					
					shot_posit -= shot_disp;
				}
				else
				{
					shot_posit += shot_disp;
				}
				
				const shot fired{show_side(), shot_posit, shot_speed, show_color()};	
				m_shots.push_back(fired);
				dressing = true;
			}
		}
		else if (dressing)
		{
			dressing = false;
		}
	}
	
	void shot_expire(square& another)
	{
		int count = 0;
		
		const int size{static_cast<int>(m_shots.size())};
		
		while (count < size)
		{
			if ((m_shots[count].x_pout() + m_shots[count].r_pout() < 0.15f*m_windims.x) ||
				(m_shots[count].x_pout() - m_shots[count].r_pout() > 0.85f*m_windims.x) ||
				collision_shot(m_shots[count]) || collision_square_shot(another, m_shots[count]))
			{
				std::vector <shot> t_shots;
				
				int count_2{0};
				
				while (count_2 < size)
				{
					if (count_2 != count)
					{
						t_shots.push_back(m_shots[count_2]);
					}
					else
					{
						t_shots.push_back(m_shots[size - 1]);
					}
					
					++count_2;
				}				
																
				while (static_cast<int>(m_shots.size()) > 0)
				{
					m_shots.pop_back();					
				}				
								
				count_2 = 0;
				
				while (count_2 < size - 1)
				{
					m_shots.push_back(t_shots[count_2]);
										
					++count_2;
				}
			}
			
			++count;
		}
	}
	
	public:
	
	float show_side()
	{
		return m_side;
	}
	
	sf::Vector2f show_posit()
	{
		return m_posit;
	}
	
	sf::Color show_color()
	{
		return m_color;
	}
	
	wing show_wing()
	{
		return m_winger;
	}
	
	std::vector <shot> show_shots()
	{
		return m_shots;
	}
		
	void displaying(sf::RenderWindow& window)
	{
		display_square(window);
		display_shots(window);	
	}
	
	void acting(ground& earth, square& another)
	{
		moving(earth, another);
		shooting(another);
		shot_expire(another);
	}
	
	square(const sf::Vector2f& windims, const wing& winger, const sf::Color& color)
		: m_windims(windims), m_winger(winger), m_side(m_windims.y/m_divis),	
		  m_radius(0.5f*m_side), m_sides(m_side, m_side),
		  m_speed_right(m_speed_mult*m_windims.x, 0.0f), m_speed_left(-m_speed_mult*m_windims.x, 0.0f),
		  m_jump_up(0.0f, -m_jump_mult*m_windims.y), m_accel(0.0f, m_accel_mult*m_windims.y),
		  m_color(color), m_square(), m_shots()
	{
		set_wing();
		set_square();
	}
	
	~square()
	{		
	}
	
	// float m_health{100.0f};	
	
};

int window_maker(const sf::Vector2f& windims, const std::string& program_name)
{
	const float millis{5.0f/1000.0f};
	
	const sf::Color black{sf::Color(0, 0, 0)};
	const sf::Color light_red{sf::Color(191, 63, 63)};
	const sf::Color light_green{sf::Color(63, 191, 63)};	const sf::Color light_blue{sf::Color(63, 63, 191)};
	
	const float divis{10.0f};
	
	square lefter(windims, wing::left, light_red);
	square righter(windims, wing::right, light_blue);
	
	std::vector <shot> shots;
	
	ground earth(windims, divis, light_green);
	
	sf::RenderWindow window(sf::VideoMode(windims.x, windims.y), program_name, sf::Style::Default);
	
	sf::Clock clock;
	
	sf::Time time;
		
	while (window.isOpen())
	{
		clock.restart();
		
		sf::Event event;
		
		window.clear(black);
		
		earth.displaying(window);
		lefter.displaying(window);
		righter.displaying(window);
		
		time = clock.getElapsedTime();
		
		while(time.asSeconds() < millis)
		{
			time = clock.getElapsedTime();
		}
		
		window.display();
		
		lefter.acting(earth, righter);
		righter.acting(earth, lefter);
		
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
	const std::string program_name{"Squaighter V0.8"};
	
	std::cout << program_name << '\n';
	
	const sf::Vector2f windims{800.0f, 400.0f};
	
	return window_maker(windims, program_name);
} 

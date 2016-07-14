#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include <SFML/Graphics.hpp>

float abs_delta(const float first, const float second)
{
	return std::abs(first - second);
}

sf::Keyboard::Key char_to_key(const char letter)
{
	sf::Keyboard::Key keyn;
	
	if (letter >= 97 && letter <= 122)
	{
		keyn = static_cast<sf::Keyboard::Key>(letter - 97);
	}
	else if (letter == 32)
	{
		keyn = static_cast<sf::Keyboard::Key>(57);
	}
	else if (letter == 27)
	{
		keyn = static_cast<sf::Keyboard::Key>(36);
	}
	
	return keyn;
}

std::string key_naming(const char letter)
{
	std::string setter{letter};
	
	if (letter == 27)
	{
		setter = "esc";
	}
	
	return "Key_" + setter + ".png";
}

enum class wing {left, right};

class botan
{
	const sf::Vector2f m_posit;	
	
	sf::Color m_color;
	const sf::Color m_bright;
	const sf::Color m_dark{63, 63, 63};
	
	const sf::Vector2f m_windims;
	const float m_divis;
	
	float m_mult{1.0f};
	
	const char m_letter;
	const std::string m_filename;	
	sf::Keyboard::Key m_keyn;
	
	bool m_pressed{false};
	
	sf::Texture m_tex;
	sf::Sprite m_sprite;
	
	sf::Vector2f m_sizes{0.0f, 0.0f};
	
	void load_tex()
	{
		if (!m_tex.loadFromFile(m_filename))
		{				
			std::cout << m_filename << " not found!\n";
		}
	}
	
	void set_tex()
	{
		m_sprite.setTexture(m_tex);
	}
	
	void set_color()
	{
		m_sprite.setColor(m_color);
	}
		
	void sprite_sizes()
	{
		const sf::FloatRect rect{m_sprite.getLocalBounds()};
		
		m_sizes = sf::Vector2f(rect.width, rect.height);
	}
		
	void stretch()
	{
		m_mult = m_windims.y/(m_divis*m_sizes.y);
		m_sprite.setScale(sf::Vector2f(m_mult, m_mult));				
	}
	
	void set_posit()
	{
		m_sprite.setPosition(m_posit - 0.5f*m_mult*m_sizes);
	}
	
	public:
	
	void pressing()
	{
		if (sf::Keyboard::isKeyPressed(m_keyn))
		{
			if (!m_pressed)
			{
				m_pressed = true;
				m_color = m_dark;
				set_color();
			}
		}
		else if (m_pressed)
		{
			m_pressed = false;
			m_color = m_bright;
			set_color();
		}
	}
	
	void displaying(sf::RenderWindow& window)
	{
		window.draw(m_sprite);
	}
	
	void set_botan()
	{
		load_tex();
		set_tex();
		set_color();
		sprite_sizes();
		stretch();
		set_posit();
	}
	
	botan(const sf::Vector2f& posit, const sf::Color& color,
		  const sf::Vector2f& windims, const float divis, const char letter)
		: m_posit(posit), m_color(color), m_bright(m_color),
		  m_windims(windims), m_divis(divis), m_letter(letter), m_filename(key_naming(m_letter)),
		  m_keyn(char_to_key(m_letter)), m_tex(), m_sprite()
	{
		set_botan();
	}
	
	~botan()
	{
	}
	
};

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

class health
{
	float m_health{1.0f};
	const float m_shot_health{0.05f};
	
	const float m_squide{1.0f};
	
	sf::Vector2f m_posit;
	
	float m_side_x{m_squide};
	const float m_side_y{0.15f*m_squide};
	
	sf::Vector2f m_sides{m_side_x, m_side_y};
	
	const float m_radius{0.5f*m_side_x};
	
	const sf::Color m_color{191, 191, 63};
	
	sf::RectangleShape m_rect;
	
	void set_rect_posit()
	{
		m_rect.setPosition(m_posit.x - m_radius, m_posit.y - m_radius);
	}
	
	void set_rect()
	{
		m_rect.setSize(m_sides);
		set_rect_posit();
		m_rect.setFillColor(m_color);
	}
	
	void set_side_x()
	{
		m_side_x = m_health*m_squide;
		m_sides = sf::Vector2f(m_side_x, m_side_y);
		m_rect.setSize(m_sides);
	}
	
	public:
	
	void displaying(sf::RenderWindow& window)
	{
		window.draw(m_rect);
	}
	
	void set_posit(const sf::Vector2f& posit)
	{
		m_posit = posit;
		set_rect_posit();
	}
	
	void shot_health()
	{
		m_health -= m_shot_health;
		set_side_x();
	}
	
	float show_health()
	{
		return m_health;
	}
	
	health(const float side, const sf::Vector2f& posit)
	: m_squide(side), m_posit(posit), m_side_x(m_squide), m_side_y(0.15f*m_squide),
	  m_radius(0.5f*m_side_x), m_rect()
	{
		set_rect();
	}
	
	~health()
	{
	}
	
};

class punch
{
	const float m_squide{1.0f};
	sf::Vector2f m_posit;
	
	const float m_steps{10.0f};
	const float m_min_stretch{1.0f};
	const float m_max_stretch{4.0f};
	const float m_delta_stretch{(m_max_stretch - m_min_stretch)/m_steps};
	float m_stretch{m_min_stretch};
	
	const float m_side{0.5f*m_squide};
	sf::Vector2f m_sides{m_side, m_side};
	sf::Vector2f m_radii{0.5f*m_sides.x, 0.5f*m_sides.y};
	
	const sf::Color m_dark{63, 63, 63};
	const sf::Color m_color;	
	
	sf::RectangleShape m_rect;
	
	bool m_stretch_out{false};
	bool m_stretch_in{false};
	
	void set_stretch()
	{
		m_sides = sf::Vector2f(m_stretch*m_side, m_side);
		m_radii = sf::Vector2f(0.5f*m_sides.x, 0.5f*m_sides.y);
	}
	
	void set_rect_posit()
	{
		m_rect.setPosition(m_posit.x - m_radii.x, m_posit.y - m_radii.y);
	}
	
	void set_rect()
	{
		m_rect.setSize(m_sides);
		set_rect_posit();
		m_rect.setFillColor(m_color);
	}
	
	void stretch_out()
	{
		if (m_stretch_out)
		{
			m_stretch += m_delta_stretch;
			
			if (m_stretch > m_max_stretch - 0.5f*m_delta_stretch)
			{
				set_stretch();
				m_stretch_out = false;
				m_stretch_in = true;
			}
		}		
	}
	
	void stretch_in()
	{
		if (m_stretch_in)
		{
			m_stretch -= m_delta_stretch;
			
			if (m_stretch < m_min_stretch + 0.5f*m_delta_stretch)
			{
				set_stretch();
				m_stretch_in = false;
			}
		}		
	}
	
	public:
	
	void stretching()
	{
		stretch_out();
		stretch_in();
	}
	
	void punch_out()
	{
		m_stretch_out = true;
	}
	
	sf::Vector2f r_pout()
	{
		return m_radii;
	}
	
	float x_pout()
	{
		return m_posit.x;
	}
	
	float y_pout()
	{
		return m_posit.y;
	}
	
	void set_posit(const sf::Vector2f& posit)
	{
		m_posit = posit;
		set_rect_posit();
	}
	
	void displaying(sf::RenderWindow& window)
	{
		window.draw(m_rect);
	}
	
	punch(const float squide, const sf::Vector2f& posit, const sf::Color& color)
		: m_squide(squide), m_posit(posit), m_side(0.5f*m_squide), m_sides(m_side, m_side),
		  m_radii(0.5f*m_sides.x, 0.5f*m_sides.y), m_color(color + m_dark), m_rect()
	  {
		  set_rect();
	  }

	~punch()
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
	
	const sf::Color m_shocked{191, 63, 191};
	
	const int m_shock_time{30};
	
	int m_shocks{0};
	
	sf::RectangleShape m_square;
	
	const float m_shot_speed_mult{0.007f};
	
	sf::Vector2f m_shot_speed{m_shot_speed_mult*m_windims.x, 0.0f};
	
	health m_health;
	
	punch m_punch;
	
	std::vector <shot> m_shots;
	
	std::string m_chars;
	const int m_chars_size;
	std::vector <botan> m_botans;
	
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
	
	void set_botans()
	{
		for (int count{0}; count < m_chars_size; ++count)
		{
			sf::Vector2f char_posit{m_posit.x + 1.5f*(static_cast<float>(count - 1))*m_side, m_posit.y + 2.5f*m_side};
			
			if (count > 2)
			{
				char_posit += sf::Vector2f(-6.0f*m_side, 1.5f*m_side);
			}
			
			if (m_winger == wing::left)
			{
				char_posit += sf::Vector2f(3.0f*m_side, 0.0f);
			}
			
			if (m_winger == wing::right)
			{
				char_posit += sf::Vector2f(-1.5f*m_side, 0.0f);
			}
				
				
			botan button(char_posit, m_color, m_windims, m_divis, m_chars[count]);
			
			m_botans.push_back(button);
		}
		
		for (int count{0}; count < m_chars_size; ++count)
		{
			m_botans[count].set_botan();
		}
	}
	
	void pressing_botans()
	{
		if (static_cast<int>(m_botans.size()) == m_chars_size)
		{
			for (int count{0}; count < m_chars_size; ++count)
			{				
				m_botans[count].pressing();
			}
		}		
	}
	
	void display_botans(sf::RenderWindow& window)
	{
		if (static_cast<int>(m_botans.size()) == m_chars_size)
		{
			for (int count{0}; count < m_chars_size; ++count)
			{				
				m_botans[count].displaying(window);
			}
		}		
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
	
	void shocking()
	{	
		if (m_shocks == 0)
		{
			m_shocks = m_shock_time;			
			m_square.setFillColor(m_shocked);
			m_health.shot_health();
		}
	}
	
	void deshocking()
	{
		if (m_shocks > 0)
		{
			--m_shocks;
			
			if (m_shocks == 0)
			{
				m_square.setFillColor(m_color);
			}
		}
	}
	
	bool collision_shot(shot& own)
	{
		const float delta_x{abs_delta(x_pout(), own.x_pout())};		
		const float delta_y{abs_delta(y_pout(), own.y_pout())};
		
		const float distance{r_pout() + own.r_pout()};
			
		bool collision{false};
		
		if (((delta_y >= delta_x) && (delta_y <= distance)) ||
			((delta_x > delta_y) && (delta_x <= distance)))
		{
			shocking();
			collision = true;
		}
		
		return collision;		
	}
	
	bool collision_square_shot(square& another, shot& own)
	{
		const float delta_x{abs_delta(another.x_pout(), own.x_pout())};		
		const float delta_y{abs_delta(another.y_pout(), own.y_pout())};
		
		const float distance{another.r_pout() + own.r_pout()};
			
		bool collision{false};
		
		if (((delta_y >= delta_x) && (delta_y <= distance)) ||
			((delta_x > delta_y) && (delta_x <= distance)))
		{
			another.spooked();
			collision = true;
		}
		
		return collision;		
	}
	
	void move_punch()
	{
		m_punch.set_posit(m_posit);
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
		move_punch();
		move_shots();
		deshocking();
		m_health.set_posit(m_posit);
		pressing_botans();
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
	
	void punching()
	{
		if ((sf::Keyboard::isKeyPressed(sf::Keyboard::E) && (show_wing() == wing::left)) ||
		   (sf::Keyboard::isKeyPressed(sf::Keyboard::O) && (show_wing() == wing::right)))
		{			
			m_punch.punch_out();
		}
		
		m_punch.stretching();
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
	
	bool shot_walled(const int count)
	{
		bool walled{false};
		
		if ((m_shots[count].x_pout() + m_shots[count].r_pout() < 0.0f*m_windims.x) ||
			(m_shots[count].x_pout() - m_shots[count].r_pout() > 1.0f*m_windims.x))
		{
			walled = true;
		}
		
		return walled;
	}
	
	void shot_expire(square& another)
	{
		int count = 0;
		
		const int size{static_cast<int>(m_shots.size())};
		
		while (count < size)
		{
			
			
			if (shot_walled(count) ||
				collision_shot(m_shots[count]) ||
				collision_square_shot(another, m_shots[count]))
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
	
	float show_health()
	{
		return m_health.show_health();
	}
	
	void spooked()
	{
		shocking();
	}
		
	void displaying(sf::RenderWindow& window)
	{
		m_punch.displaying(window);
		display_square(window);
		m_health.displaying(window);
		display_shots(window);
		display_botans(window);
	}
	
	void acting(ground& earth, square& another)
	{
		moving(earth, another);
		punching();
		
		shooting(another);
		shot_expire(another);
	}
	
	square(const sf::Vector2f& windims, const wing& winger, const sf::Color& color,
			const std::string& chars)
		: m_windims(windims), m_winger(winger), m_side(m_windims.y/m_divis),	
		  m_radius(0.5f*m_side), m_sides(m_side, m_side),
		  m_speed_right(m_speed_mult*m_windims.x, 0.0f), m_speed_left(-m_speed_mult*m_windims.x, 0.0f),
		  m_jump_up(0.0f, -m_jump_mult*m_windims.y), m_accel(0.0f, m_accel_mult*m_windims.y),
		  m_color(color), m_square(), m_health(m_side, m_posit),
		  m_punch(m_side, m_posit, m_color), m_shots(), m_chars(chars),
		  m_chars_size(static_cast<int>(m_chars.size())), m_botans()
	{
		set_wing();
		set_square();
		m_health.set_posit(m_posit);
		set_botans();
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
	const sf::Color light_green{sf::Color(63, 191, 63)};
	const sf::Color light_blue{sf::Color(63, 63, 191)};
	const sf::Color light_orange{sf::Color(191, 127, 63)};
	const sf::Color light_purple{sf::Color(191, 63, 191)};
	const sf::Color light{sf::Color(191, 191, 191)};
	
	const std::string lefter_letters{'w', 'e', 'r', 'a', 's', 'd'};
	const std::string righter_letters{'i', 'o', 'p', 'j', 'k', 'l'};
	
	const float divis{10.0f};
	
	const float block{windims.y/divis};
	
	const float h_factor{1.35f};
	
	const std::string space_name{"Key_Space.png"};
	const sf::Vector2f space_posit{10.0f*block, 12.5f*block};
	
	const sf::Vector2f escape_posit{10.0f*block, 11.0f*block};
	
	sf::RenderWindow window(sf::VideoMode(windims.x, h_factor*windims.y), program_name, sf::Style::Default);
			
	while (window.isOpen())
	{
		int loop_mode{0};
		
		square lefter(windims, wing::left, light_red, lefter_letters);
		square righter(windims, wing::right, light_blue, righter_letters);
		ground earth(windims, divis, light_green);
		
		const char letter_space{' '};
		const char letter_escape{27};
		
		botan space_button(space_posit, light, windims, divis, letter_space);
		botan escape_button(escape_posit, light, windims, divis, letter_escape);
		
		sf::Clock clock;
		sf::Time time;
		
		while (loop_mode != 10)
		{		
			clock.restart();
			
			sf::Event event;
			
			if (loop_mode == 0)
			{
				window.clear(black);
						
				earth.displaying(window);
				lefter.displaying(window);
				righter.displaying(window);
			}
			
			if (loop_mode == -1)
			{
				window.clear(light_red);
				space_button.displaying(window);
			}
			
			if (loop_mode == 1)
			{
				window.clear(light_blue);
				space_button.displaying(window);
			}
			
			escape_button.displaying(window);
			
			time = clock.getElapsedTime();
			
			while(time.asSeconds() < millis)
			{
				time = clock.getElapsedTime();
			}
			
			window.display();
			
			if (loop_mode == 0)
			{
				lefter.acting(earth, righter);
				righter.acting(earth, lefter);
				
				if (lefter.show_health() <= 0.0f)
				{
					loop_mode = 1;
				}
				
				if (righter.show_health() <= 0.0f)
				{
					loop_mode = -1;
				}
			}
			
			space_button.pressing();
			escape_button.pressing();
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) &&
				(loop_mode != 0))
			{
				loop_mode = 10;
			}
			
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
	}
	
	return 1;	
}

int main()
{
	const std::string program_name{"Squaighter V0.17"};
	
	std::cout << program_name << '\n';
	
	const sf::Vector2f windims{800.0f, 400.0f};
	
	return window_maker(windims, program_name);
} 

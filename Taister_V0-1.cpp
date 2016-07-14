#include <iostream>
#include <string>
#include <vector>
#include <cassert>

#include <SFML/Graphics.hpp>

int main()
{
	sf::Keyboard::Key keyn{static_cast<sf::Keyboard::Key>(' ')};
	
	if (sf::Keyboard::KeyCount == keyn)
	{
		std::cout << sf::Keyboard::Escape << " == " << keyn << "\n";
	}
	else
	{
		std::cout << sf::Keyboard::Escape << " != " << keyn << "\n";
	}
	
	const char letter{'z'};
	
	const int number{letter};
	
	const int mumber{static_cast<int>(letter)};
	
	std::cout << number << ":" << mumber << "\n";
	
}

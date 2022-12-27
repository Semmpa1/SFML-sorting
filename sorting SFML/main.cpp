#include <iostream>
#include <array>
#include <set>
#include <algorithm>
#include <thread>
#include <random>

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


sf::RenderWindow window(sf::VideoMode(800, 600), "sorting");

const unsigned short Asize = 21;
const unsigned short speed = 50;

std::array<int, Asize> unSort;

sf::RectangleShape LineArr[Asize];

void Sort();
void arrFill();

int main() {
	arrFill();
	std::thread sorting(Sort);
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q)) { window.close(); }
			if (event.type == sf::Event::Closed) { window.close(); }
		}
		window.clear(sf::Color(50, 50, 50, 255));

		for (short i = 0; i < Asize; i++)
		{
			LineArr[i].setRotation(180);
			LineArr[i].setSize(sf::Vector2f(800 / Asize - 5, (580 / Asize) * unSort[i] ));

			LineArr[i].setPosition(sf::Vector2f((800 / Asize ) *(i +1), 580));
		}

		for (short i = 0; i < Asize; i++)
		{
			window.draw(LineArr[i]);
		}
		window.display();
	}
	sorting.detach();
	return 0;
}

// vizualizing with  std::this_thread::sleep_for(std::chrono::milliseconds(speed));

// Change function name to "Sort" and run code
// 
//				||||||||||||||
//				||||||||||||||
//				||||||||||||||
//				VVVVVVVVVVVVVV

void minSwapToRight() {
	for (unsigned short j = Asize; j > 0; j--) {
		short maxElem = std::min_element(unSort.begin(), unSort.end() - (Asize - j)) - unSort.begin();
		for (unsigned short i = maxElem; i < j - 1; i++)
		{
			LineArr[i].setFillColor(sf::Color(255, 0, 0));
			std::this_thread::sleep_for(std::chrono::milliseconds(speed));
			if (unSort[i] < unSort[i + 1])
			{
				std::swap(unSort[i], unSort[i + 1]);
			}
			LineArr[i].setFillColor(sf::Color(255, 255, 255));
		}
		LineArr[j].setFillColor(sf::Color(255, 255, 255));
	}
}

void maxSwapToRight() {
	for (unsigned short j = Asize; j > 0; j--) {
		short maxElem = std::max_element(unSort.begin() , unSort.end() - (Asize - j)) - unSort.begin();
		for (unsigned short i = maxElem; i < j-1; i++)
		{
			LineArr[i].setFillColor(sf::Color(255, 0, 0));
			std::this_thread::sleep_for(std::chrono::milliseconds(speed));
			if (unSort[i] > unSort[i + 1])
			{
				std::swap(unSort[i], unSort[i + 1]);
			}
			LineArr[i].setFillColor(sf::Color(255, 255, 255));
		}
		LineArr[j].setFillColor(sf::Color(255, 255, 255));
	}
}

void maxSwapToLeft() {
	for (unsigned short j = 0; j < Asize; j++) {
		short maxElem = std::max_element(unSort.begin() + j, unSort.end()) - unSort.begin();
		for (unsigned short i = maxElem; i > j; i--)
		{
			LineArr[i].setFillColor(sf::Color(255, 0, 0));
			std::this_thread::sleep_for(std::chrono::milliseconds(speed));
			if (unSort[i] > unSort[i - 1])
			{
				std::swap(unSort[i], unSort[i - 1]);
			}
			LineArr[i].setFillColor(sf::Color(255, 255, 255));
		}
		LineArr[j].setFillColor(sf::Color(255, 255, 255));
	}
}

void minSwapToLeft() {
	for (unsigned short j = 0; j < Asize; j++){
		short minElem = std::min_element(unSort.begin()+j, unSort.end()) - unSort.begin();

		for (unsigned short i = minElem; i > j; i--)
		{
			LineArr[i].setFillColor(sf::Color(255, 0, 0));
			std::this_thread::sleep_for(std::chrono::milliseconds(speed));
			if (unSort[i] < unSort[i - 1])
			{
				std::swap(unSort[i], unSort[i - 1]);
			}
			LineArr[i].setFillColor(sf::Color(255, 255, 255));
		}
		LineArr[j].setFillColor(sf::Color(255, 255, 255));
	}
}

void BubbleSort() {
	//while (std::is_sorted(unSort.begin(), unSort.end()))
	for (unsigned short i = 0; i < Asize; i++)
	{
		for (unsigned short j = 0; j < Asize-1; j++)
		{
			LineArr[j].setFillColor(sf::Color(255, 0, 0));
			std::this_thread::sleep_for(std::chrono::milliseconds(speed));
			if (unSort[j] > unSort[j + 1])
			{
				std::swap(unSort[j], unSort[j + 1]);
			}
			LineArr[j].setFillColor(sf::Color(255, 255, 255));
		}
		LineArr[i].setFillColor(sf::Color(255, 255, 255));
	}
}

void D4() {
	float d = 4;
	const float cd = 4;
	auto start = 0;
	auto end = Asize / d;

	while (true)
	{
		for (unsigned short j = start; j < end; j++) {
			short minElem = std::min_element(unSort.begin() + j, unSort.begin() + end) - unSort.begin();
			for (unsigned short i = minElem; i > j; i--)
			{
				LineArr[i].setFillColor(sf::Color(255, 0, 0));
				std::this_thread::sleep_for(std::chrono::milliseconds(speed));
				if (unSort[i] < unSort[i - 1])
				{
					std::swap(unSort[i], unSort[i - 1]);
				}
				LineArr[i].setFillColor(sf::Color(255, 255, 255));
			}
			LineArr[j].setFillColor(sf::Color(255, 255, 255));
		}

		if (d == 1) {
			break;
		}
		if (end > Asize-1) {
			end = 0;
			d /= 2;
		}
		start = end;
		end += Asize / d;
	}
}

void arrFill() {
	srand(time(NULL));
	int i = 0;
	while (i < Asize)
	{
		short el = (std::rand() % Asize + 1);

		if (std::find(unSort.begin(), unSort.end(), el) == unSort.end())
		{
			unSort[i] = el;
			i++;
		}
	}
}
//include classes and headers
#include "../inc/common.hpp"
#include "TimeUtil.hpp"

int getRandomInt(int x, int y);

int main() {
    sf::RenderWindow window(sf::VideoMode(200, 200), "SFML works!");
    window.setFramerateLimit(60);

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Yellow);

    TimeUtil tu;
    tu.setTime();

    int totalTime = 0;

    while (window.isOpen()) {
        tu.setTime();
        totalTime += tu.getTime();

        totalTime = 0;

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            if(event.type == sf::Event::TextEntered) {
                if(event.text.unicode == 0) {}
            }
        }

        window.clear(sf::Color::Black);
        window.draw(shape);
        window.display();
    }

    // Exit program.
    return 0;
}

int getRandomInt(int x, int y) {
    std::random_device device;
    std::mt19937 generator(device());
    std::uniform_int_distribution<int> distribution(x, y);

    return distribution(generator);
}

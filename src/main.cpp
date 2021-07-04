//include classes and headers
#include "../inc/common.hpp"
#include "TimeUtil.hpp"

int getRandomInt(int x, int y);

int main() {
    sf::RenderWindow window(sf::VideoMode(1000 , 1000), "SFML works!");
    window.setFramerateLimit(60);

    sf::CircleShape shape(10);
    //shape.setFillColor(sf::Color::Blue);
    shape.setPosition(500, 900);

    /*sf::Texture texture;
    if (!texture.loadFromFile("../jojo.png")) {
        std::cout << "Error!" << std::endl;
    }

    shape.setTexture(&texture);*/

    TimeUtil tu;
    tu.setTime();

    int totalTime;
    int speed = 5;
    double turnSpeed = M_PI / 16;

    double direction = (M_PI / 2) * 3;
    int moveX = 0;
    int moveY = 0;

    shape.setOrigin(10, 10);

    std::vector<sf::CircleShape> circles;


    while (window.isOpen()) {
        tu.setTime();
        totalTime += tu.getTime();

        totalTime = 0;

        shape.setRotation(direction);

        //moveX += speed * cos(direction);
        //moveY += speed * sin(direction);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();

            /*if(event.type == sf::Event::TextEntered) {
                if(event.text.unicode == 0) {}
            }*/
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            circles.push_back(shape);
            shape.move(speed * cos(direction), speed * sin(direction));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            shape.move(-speed * cos(direction), -speed * sin(direction));
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            direction += turnSpeed;
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            direction -= turnSpeed;
        }

        if(direction > M_PI * 2)
            direction = 0.f;
        if(direction < 0.f)
            direction = M_PI * 2;

        /*if(direction > 360.f)
            direction = 0.f;
        if(direction < 0.f)
            direction = 360.f;*/

        std::cout << direction << std::endl;

        window.clear(sf::Color::Black);
        window.draw(shape);

        for(int i = 0; i < circles.size(); i++) {
            window.draw(circles[i]);
        }
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

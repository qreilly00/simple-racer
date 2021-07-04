//include classes and headers
#include "../inc/common.hpp"
#include "TimeUtil.hpp"

int getRandomInt(int x, int y);

int main() {
    sf::RenderWindow window(sf::VideoMode(500 , 500), "SFML works!");
    window.setFramerateLimit(60);

    sf::CircleShape snakeHead(10);
    snakeHead.setPosition(500, 900);
    snakeHead.setOrigin(10, 10);

    TimeUtil tu;
    tu.setTime();
    int totalTime = 0;

    // Not sure if PI is needed here, but I'll keep it for now.
    int speed = M_PI;
    double turnSpeed = M_PI / 16;
    double direction = (M_PI / 2) * 3;

    int pauses = 1;
    int pausesLeft = pauses;

    std::vector<sf::CircleShape> snakeBody;
    int snakeLength = 50;

    sf::CircleShape food(10);
    food.setFillColor(sf::Color::Green);
    food.setPosition(-40, -40);
    food.setOrigin(10, 10);

    bool foodExists = 0;

    while (window.isOpen()) {
        tu.setTime();
        totalTime += tu.getTime();

        snakeHead.setRotation(direction);

        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Add a shadow of the snake head to the body.
        snakeBody.push_back(snakeHead);
        snakeHead.move(speed * cos(direction), speed * sin(direction));

        // Controls. Only activated once pauses are depleted to increase turning radius.
        if(pausesLeft == 0) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                direction += turnSpeed;
            }

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                direction -= turnSpeed;
            }

            pausesLeft = pauses;
        } else
            pausesLeft--;

        // Reset rotation when limit is reached.
        if(direction > M_PI * 2)
            direction = 0.f;
        if(direction < 0.f)
            direction = M_PI * 2;

        if(snakeBody.size() == snakeLength) {
            snakeBody.erase(snakeBody.begin());
        }

        // Left screen.
        if(snakeHead.getPosition().x <= 20) {
            snakeHead.setPosition(window.getSize().x - 20, snakeHead.getPosition().y);
        }

        // Right screen.
        if(snakeHead.getPosition().x >= window.getSize().x - 10) {
            snakeHead.setPosition(20, snakeHead.getPosition().y);
        }

        // Top Screen.
        if(snakeHead.getPosition().y <= 20) {
            snakeHead.setPosition(snakeHead.getPosition().x, window.getSize().y - 20);
        }

        // Bottom Screen.
        if(snakeHead.getPosition().y >= window.getSize().y - 10) {
            snakeHead.setPosition(snakeHead.getPosition().x, 20);
        }

        // Food eaten.
        if(snakeHead.getGlobalBounds().intersects(food.getGlobalBounds())) {
            snakeLength += 10;
            foodExists = 0;
            food.setPosition(-20, -20);
        }

        window.clear(sf::Color::Black);
        window.draw(snakeHead);
        window.draw(food);

        int foodCheckCounter = 0;

        sf::CircleShape tmpCircle(10.f);
        tmpCircle.setPosition(getRandomInt(40, window.getSize().x - 40), getRandomInt(40, window.getSize().y - 40));
        tmpCircle.setOrigin(10.f, 10.f);

        // Snake body draw, collision and pellet hybrid.
        for(int i = 0; i < snakeBody.size(); i++) {
            window.draw(snakeBody[i]);

            // Game over.
            if(snakeBody.size() > 10 && i < snakeBody.size() - 10)
                if(snakeHead.getGlobalBounds().intersects(snakeBody[i].getGlobalBounds())) return 0;

            // Add new food.
            if(foodExists == 0 && totalTime > 1000) {// No intersects found.
                if(!snakeBody[i].getGlobalBounds().intersects(tmpCircle.getGlobalBounds())) {
                    foodCheckCounter++;
                }
            }
        }

        if(foodCheckCounter == snakeLength - 1) {
            food.setPosition(tmpCircle.getPosition());
            foodExists = 1;
            foodCheckCounter = 0;
            //totalTime = 0;
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

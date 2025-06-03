#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm> 

const int WIDTH = 800;
const int HEIGHT = 600;

sf::Image framebuffer; //framebuffer
sf::Texture texture;
sf::Sprite sprite;

//limits drawing to the viewport, prevents memory leak/overflow
int clamp(int val, int minVal, int maxVal) {
    return std::max(minVal, std::min(val, maxVal));
}

void drawpix(float x, float y, int R, int G, int B) {
    int ix = clamp(static_cast<int>(x + 0.5f), 0, WIDTH - 1);
    int iy = clamp(static_cast<int>(y + 0.5f), 0, HEIGHT - 1);
    framebuffer.setPixel(ix, iy, sf::Color(R, G, B));
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "test");
    framebuffer.create(WIDTH, HEIGHT, sf::Color::Black);

    int Cx = WIDTH/2; //assumption that origin is at center of the viewport
    int Cy = HEIGHT/2;

    for (int i = 0; i < 100; ++i) {
        drawpix(Cx + i, Cy, 255, 255, 255); 
        drawpix(Cx, Cy - i, 255, 255, 255); 
    } //y-axis is -ve since reversed (cartesian)

    texture.loadFromImage(framebuffer);
    sprite.setTexture(texture);

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }
    return 0;
}


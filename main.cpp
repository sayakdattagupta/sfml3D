#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>
#include <algorithm>

const int WIDTH = 800; //4:3 ASPECT
const int HEIGHT = 600;
const float FOV = 53.0f;
const float NEAR_PLANE = 0.1f;

struct Vec3 {
    float x, y, z;
    Vec3 operator+(const Vec3& other) const {
        return {x + other.x, y + other.y, z + other.z};
    }
    Vec3 operator-(const Vec3& other) const {
        return {x - other.x, y - other.y, z - other.z};
    }
    Vec3 operator*(float s) const {
        return {x * s, y * s, z * s};
    }
};

Vec3 rotateY(const Vec3& p, float angle) {
    float s = std::sin(angle);
    float c = std::cos(angle);
    return { //too much to break down here
        p.x * c - p.z * s,
        p.y,
        p.x * s + p.z * c
    };
} 

Vec3 rotateX(const Vec3& p, float angle) {
    float s = std::sin(angle);
    float c = std::cos(angle);
    return {
        p.x,
        p.y * c - p.z * s,
        p.y * s + p.z * c
    };
}

sf::Vector2f project(const Vec3& p) { //cam faces +X axis
    float scale = (WIDTH / 2.0f) / std::tan(FOV * 0.5f * 3.14159f / 180.0f);
    return {
        (p.x / p.z) * scale + WIDTH / 2.0f, //triangular similarity property
        (p.y / p.z) * scale + HEIGHT / 2.0f //convert normalized coords to screen coords
    };
}

int main() {
    sf::RenderWindow window(sf::VideoMode(WIDTH, HEIGHT), "sfml3D");
    window.setFramerateLimit(60);
    
    //A CUBE
    std::vector<Vec3> verts = {
        {-1,-1,-1}, {1,-1,-1}, {1,1,-1}, {-1,1,-1},
        {-1,-1,1},  {1,-1,1},  {1,1,1},  {-1,1,1}
    };

    std::vector<std::pair<int, int>> edges = { //pair of two vertices
        {0,1}, {1,2}, {2,3}, {3,0},
        {4,5}, {5,6}, {6,7}, {7,4},
        {0,4}, {1,5}, {2,6}, {3,7}
    };

    Vec3 cameraPos = {0, 0, -5};
    float yaw = 0.0f;
    float pitch = 0.0f;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //rotate cam
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) yaw -= 0.03f; //MODIFY AS YOU WISH
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) yaw += 0.03f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) pitch -= 0.03f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) pitch += 0.03f;

        Vec3 forward = { std::sin(yaw), 0, std::cos(yaw) };
        Vec3 right = { forward.z, 0, -forward.x };

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) cameraPos = cameraPos + forward * 0.1f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) cameraPos = cameraPos - forward * 0.1f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) cameraPos = cameraPos - right * 0.1f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) cameraPos = cameraPos + right * 0.1f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) cameraPos.y += 0.1f;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift)) cameraPos.y -= 0.1f;

        window.clear();

        for (auto& edge : edges) { //loops over all edges in the cube
            Vec3 a = verts[edge.first]; //first endp
            Vec3 b = verts[edge.second]; //second endp

            a = rotateX(rotateY(a, yaw), pitch);
            b = rotateX(rotateY(b, yaw), pitch);

            a = a - cameraPos;
            b = b - cameraPos;

            if (a.z <= NEAR_PLANE || b.z <= NEAR_PLANE) continue; //OTHERWISE SKIP

            sf::Vector2f pa = project(a);
            sf::Vector2f pb = project(b);

            sf::Vertex line[] = {
                sf::Vertex(pa, sf::Color::White),
                sf::Vertex(pb, sf::Color::White)
            };
            window.draw(line, 2, sf::Lines); //draws primitive using 2 vertices
        }
        window.display();
    }
    return 0;
}


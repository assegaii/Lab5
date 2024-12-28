#include "World.h"
#include "Painter.h"
#include <fstream>
#include <stdexcept>
#include <iostream>

// Длительность одного тика симуляции.
// Подробнее см. update()
// Изменять не следует
static constexpr double timePerTick = 0.001;

Point World::readPoint(std::istream& stream) {
    Point point;
    stream >> point.x >> point.y;
    return point;
}

Velocity World::readVelocity(std::istream& stream) {
    double vx, vy;
    stream >> vx >> vy;
    return Velocity(Point(vx, vy));
}

Color World::readColor(std::istream& stream) {
    double red, green, blue;
    stream >> red >> green >> blue;
    return Color(red, green, blue);
}

World::World(const std::string& worldFilePath) {

    std::ifstream stream(worldFilePath);
    
    topLeft = readPoint(stream);
    bottomRight = readPoint(stream);
    physics.setWorldBox(topLeft, bottomRight);

    if (!stream) {
        throw std::runtime_error("Unable to open world file: " + worldFilePath);
    }
    while (stream.peek(), stream.good()) {
        Point center = readPoint(stream);
        Velocity velocity = readVelocity(stream);
        Color color = readColor(stream);
        double radius;
        bool isCollidable;
        
        stream >> radius >> std::boolalpha >> isCollidable;

        Ball ball(center, radius, velocity, color, isCollidable);
        std::cout << "Ball created: center=(" << center.x << ", " << center.y 
          << "), radius=" << radius 
          << ", isCollidable=" << (isCollidable ? "true" : "false") << std::endl;
        balls.push_back(ball);
    }
}

/// @brief Отображает состояние мира
void World::show(Painter& painter) const {
    // Рисуем белый прямоугольник, отображающий границу
    // мира
    painter.draw(topLeft, bottomRight, Color(1, 1, 1));

    // Вызываем отрисовку каждого шара
    for (const Ball& ball : balls) {
        ball.draw(painter);
    }

    for (const Dust& particle : particles) {
        particle.draw(painter);
    }

}

/// @brief Обновляет состояние мира
void World::update(double time) {
    

    // учитываем остаток времени, который мы не "доработали" при прошлом update
    time += restTime;
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick));
    restTime = time - double(ticks) * timePerTick;

    physics.update(balls, particles, ticks);
}
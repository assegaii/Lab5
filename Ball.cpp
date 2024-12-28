#include "Ball.hpp"


Ball::Ball(const Point& center, double radius, const Velocity& velocity, const Color& color, bool isCollidable)
    : center(center), radius(radius), velocity(velocity), color(color), collidable(isCollidable) {}

void Ball::setVelocity(const Velocity& velocity) {
    this->velocity = velocity;
}

Velocity Ball::getVelocity() const {
    return velocity;
}

void Ball::draw(Painter& painter) const {
    painter.draw(center, radius, color);
}

void Ball::setCenter(const Point& center) {
    this->center = center;
}

Point Ball::getCenter() const {
    return center;
}

double Ball::getRadius() const {
    return radius;
}

double Ball::getMass() const {
    static constexpr double density = 1.0; // Плотность материала
    return density * (4.0 / 3.0) * M_PI * std::pow(radius, 3);
}

bool Ball::isCollidable() const {
    return collidable;
}
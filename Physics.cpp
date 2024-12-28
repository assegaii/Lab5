#include "Physics.h"
#include <iostream>
#include <algorithm>

double dot(const Point& lhs, const Point& rhs) {
    return lhs.x * rhs.x + lhs.y * rhs.y;
}

Physics::Physics(double timePerTick) : timePerTick{timePerTick} {}

void Physics::setWorldBox(const Point& topLeft, const Point& bottomRight) {
    this->topLeft = topLeft;
    this->bottomRight = bottomRight;
}

void Physics::update(std::vector<Ball>& balls, std::vector<Dust>& particles, const size_t ticks) const {

    for (size_t i = 0; i < ticks; ++i) {
        move(balls, particles);
        collideWithBox(balls);
        collideBalls(balls, particles);
    }
    for (Dust& particle : particles) {
            particle.decrementLifetime();
        }

        particles.erase(
            std::remove_if(
                particles.begin(),
                particles.end(),
                [](const Dust& particle) { return particle.getLifetime() <= 0; } 
            ),
            particles.end()
        );
}

void Physics::collideBalls(std::vector<Ball>& balls, std::vector<Dust>& particles) const {
    for (auto a = balls.begin(); a != balls.end(); ++a) {
        for (auto b = std::next(a); b != balls.end(); ++b) {
            if (!a->isCollidable() || !b->isCollidable()) {
                continue;
            }
            
            const double distanceBetweenCenters2 =
                distance2(a->getCenter(), b->getCenter());
            const double collisionDistance = a->getRadius() + b->getRadius();
            const double collisionDistance2 =
                collisionDistance * collisionDistance;

            if (distanceBetweenCenters2 < collisionDistance2) {
                processCollision(*a, *b, distanceBetweenCenters2, particles);
            }
        }
    }
}

void Physics::collideWithBox(std::vector<Ball>& balls) const {
    for (Ball& ball : balls) {
        if(!ball.isCollidable())
            continue;
        const Point p = ball.getCenter();
        const double r = ball.getRadius();
        // определяет, находится ли v в диапазоне (lo, hi) (не включая границы)
        auto isOutOfRange = [](double v, double lo, double hi) {
            return v < lo || v > hi;
        };

        if (isOutOfRange(p.x, topLeft.x + r, bottomRight.x - r)) {
            Point vector = ball.getVelocity().vector();
            vector.x = -vector.x;
            ball.setVelocity(vector);
        } else if (isOutOfRange(p.y, topLeft.y + r, bottomRight.y - r)) {
            Point vector = ball.getVelocity().vector();
            vector.y = -vector.y;
            ball.setVelocity(vector);
        }
    }
}

void Physics::move(std::vector<Ball>& balls, std::vector<Dust>& particles) const {
    for (Ball& ball : balls) {
        Point newPos =
            ball.getCenter() + ball.getVelocity().vector() * timePerTick;
        ball.setCenter(newPos);
    }
    for (Dust& particle : particles) {
        Point newPos = particle.getCoordinates() + particle.getVelocity().vector() * timePerTick;
        particle.setCoordinates(newPos);
    }
}

void Physics::processCollision(Ball& a, Ball& b,
                               double distanceBetweenCenters2, std::vector<Dust>& particles) const {
    // нормированный вектор столкновения
    const Point normal =
        (b.getCenter() - a.getCenter()) / std::sqrt(distanceBetweenCenters2);

    // получаем скорость в векторном виде
    const Point aV = a.getVelocity().vector();
    const Point bV = b.getVelocity().vector();

    // коэффициент p учитывает скорость обоих мячей
    const double p =
        2 * (dot(aV, normal) - dot(bV, normal)) / (a.getMass() + b.getMass());

    // задаем новые скорости мячей после столкновения
    a.setVelocity(Velocity(aV - normal * p * a.getMass()));
    b.setVelocity(Velocity(bV + normal * p * b.getMass()));

    const Point collisionPoint=(a.getCenter() + b.getCenter()) / 2.0;
    int numParticles = 10; // Количество частиц
    for (int i = 0; i < numParticles; ++i) {
        
        double vx = pow(-1,rand()%2)*500;
        double vy = pow(-1,rand()%2)*500;


        particles.emplace_back(collisionPoint, Velocity(vx, vy), 200); 
    }
}

#pragma once
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"
#include "Color.h"
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif


class Ball {
public:
    Ball(const Point& center, double radius, const Velocity& velocity, const Color& color, bool isCollidable);

    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    double getRadius() const;
    double getMass() const;
    bool isCollidable() const;
private:
    Point center;
    double radius;
    Velocity velocity;
    Color color;
    bool collidable;
};

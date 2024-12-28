#pragma once
#include "Painter.h"
#include "Point.h"
#include "Velocity.h"
#include "Color.h"
class Dust{
public:
    Dust(Point coord, Velocity vel, int lifetime);
    Point getCoordinates();
    Velocity getVelocity() const;
    void setCoordinates(const Point& coord);
    void draw(Painter& painter) const;
    int getLifetime() const;
    void decrementLifetime();
private:
    Point coordinates;
    Velocity velocity;
    int lifetime;
    double radius;
    Color color;
};
#include "Dust.h"

Dust::Dust(Point coord, Velocity vel, int lifetime){
    this->coordinates=coord;
    this->velocity=vel;
    this->lifetime=lifetime;
    this->radius=10.0;
    this->color=Color(0, 0, 0);
}

Point Dust::getCoordinates(){
    return coordinates;
}

Velocity Dust::getVelocity() const {
    
    return velocity;
}

void Dust::setCoordinates(const Point& coord){
    this->coordinates=coord;
}

void Dust::draw(Painter& painter) const {
    painter.draw(coordinates, radius, color);
}

int Dust::getLifetime() const {
    return lifetime;  
}

void Dust::decrementLifetime() {
    --lifetime;  
}
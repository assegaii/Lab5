#pragma once
#include "Ball.hpp"
#include "Physics.h"
#include "Dust.h"
#include <vector>
#include <fstream>

class Painter;

class World {
  public:
    World(const std::string& worldFilePath);
    void show(Painter& painter) const;
    void update(double time);

  private:
    // Границы мира заданы углами прямоугольника
    Point topLeft;
    Point bottomRight;
    // Объект физического движка
    Physics physics;
    // Контейнер с шарами
    std::vector<Ball> balls;
    // Частицы
    std::vector<Dust> particles;
    // Длина отрезка времени, который не был
    // учтен при прошлой симуляции. См. реализацию update
    double restTime = 0.;

    static Point readPoint(std::istream& stream);
    static Velocity readVelocity(std::istream& stream);
    static Color readColor(std::istream& stream);
};

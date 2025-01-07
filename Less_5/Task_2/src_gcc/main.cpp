#include <iostream>

class Figure
{
private:
    std::string title;
    int sides_count;

public:
    Figure(const std::string& name = "Фигура", int count = 0):title{ name }, sides_count{count} {}
    const std::string get_name() const { return title; }
    const int get_sides_count() const { return sides_count; }

};

class Triangle : public Figure
{
private:


public:
    Triangle(const std::string& name = "Треугольник", int count = 3) : Figure(name, count) {}

};

class Quadrangle : public Figure
{
private:


public:
    Quadrangle(const std::string& name = "Четырёхугольник", int count = 4) : Figure(name, count) {}

};

int main()
{
    std::cout << "Количество сторон: " << std::endl;

    Figure figure;
    std::cout << figure.get_name() << ": " << figure.get_sides_count() << "\n";

    Triangle triangle;
    std::cout << triangle.get_name() << ": " << triangle.get_sides_count() << "\n";

    Quadrangle quadrangle;
    std::cout << quadrangle.get_name() << ": " << quadrangle.get_sides_count() << "\n";

    return 0;
}
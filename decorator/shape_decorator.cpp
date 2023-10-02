#include <iostream>
#include <string>

struct Shape{
  virtual std::string str() const = 0;
};

class Circle : public Shape{
  float radius = 10.0f;
  
public:
  std::string str() const override{
    return std::string("A circle of radius ") + std::to_string(radius);
  }
};

class ColoredShape : public Shape{
  std::string color;
  Shape& shape;
public:
  ColoredShape(std::string c, Shape& s): color{c}, shape{s} {}
  std::string str() const override{
    return shape.str() + std::string(" which is coloured ") + color;
  }
};

class FramedShape : public Shape{
  Shape& shape;
public:
  FramedShape(Shape& s): shape{s} {}
  std::string str() const override{
    return shape.str() + std::string(" and has a frame");
  }
};

int main(){

  Circle circle;
  ColoredShape coloredShape("red", circle);    // (1)
  FramedShape framedShape1(circle);            // (2)
  FramedShape framedShape2(coloredShape);      // (3)

  ColoredShape coloredShape2("blue", framedShape2); //(4)

  std::cout << circle.str() << '\n';
  std::cout << coloredShape.str() << '\n';
  std::cout << framedShape1.str() << '\n';
  std::cout << framedShape2.str() << '\n';
  std::cout << coloredShape2.str() << '\n';

}
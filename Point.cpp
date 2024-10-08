#include <iostream>
using namespace std;

class Point
{
public:
double x;
double y;
Point(): x(0), y(0) {}
Point(double x, double y){
    this -> x = x; 
    this -> y = y;
}
Point(Point &p){
    x = p.x;
    y = p.y;
}
~Point(){
    x = 0;
    y = 0;
}
Point& operator = (double d){
    x = d;
    y = d;
    return * this;
}
Point& operator = (Point &p){
    x = p.x;
    y = p.y;
    return * this;
}
};

int main(){
Point p1;
Point p2(3, 7);
Point p3(p2);
Point p4;
p4 = 7.5;
p3 = p4;
cout<<p2<< endl;
}
//ДЛЯ ArrayF оператор равно; оператор +=; перегрузить []
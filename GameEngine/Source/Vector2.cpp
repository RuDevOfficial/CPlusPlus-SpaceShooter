#include "Includes/Vector2.h"

Vector2::Vector2() { X = 0; Y = 0; }
Vector2::Vector2(int x, int y) : X(x),Y(y) { }
Vector2::~Vector2() { }

bool Vector2::operator==(const Vector2& a) { return this->X == a.X && this->Y == a.Y; }
bool Vector2::operator!=(const Vector2& a) { return this->X != a.X || this->Y != a.Y; }
Vector2 Vector2::operator+(const Vector2& a) { return Vector2(this->X + a.X, this->Y + a.Y); }
Vector2 Vector2::operator-(const Vector2& a) { return Vector2(this->X - a.X, this->Y - a.Y); }
Vector2 Vector2::operator*(const Vector2& a) { return Vector2(this->X * a.X , this->Y * a.Y); }
Vector2 Vector2::operator*(const int& a) { return Vector2(this->X * a , this->Y * a); }
Vector2 Vector2::operator*(const float& a) { return Vector2(this->X * a , this->Y * a); }
Vector2 Vector2::operator/(const Vector2& a) { return Vector2(this->X / a.X, this->Y / a.Y); }
Vector2 Vector2::operator/(const int& a) { return Vector2(this->X / a, this->Y / a); }
Vector2 Vector2::operator/(const float& a) { return Vector2(this->X / a, this->Y / a); }

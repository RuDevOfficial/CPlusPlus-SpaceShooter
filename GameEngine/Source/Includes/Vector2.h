#pragma once
struct Vector2
{
	Vector2();
	Vector2(int x, int y);
	~Vector2();

	int X = 0;
	int Y = 0;

	bool operator== (const Vector2& a);
	bool operator!= (const Vector2& a);
	Vector2 operator+ (const Vector2& a);
	Vector2 operator- (const Vector2& a);

	Vector2 operator* (const Vector2& a);
	Vector2 operator* (const int& a);
	Vector2 operator* (const float& a);

	Vector2 operator/ (const Vector2& a);
	Vector2 operator/ (const int& a);
	Vector2 operator/ (const float& a);
};


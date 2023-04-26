#pragma once

#include <iostream>

struct Vector2f
//cấu trúc của 1 vector 2 chiều
{
	Vector2f()//hàm tạo mặc định của cấu trúc Vector2f, khởi tạo giá trị của x và y là 0.0f
	:x(0.0f), y(0.0f)
	{}

	Vector2f(float p_x, float p_y)
	//hàm tạo của cấu trúc Vector2f với tham số truyền vào là giá trị của x và y. Tham số p_x và p_y đại diện cho giá trị của hai thành phần x và y
	:x(p_x), y(p_y)
	{}

	void print()//in ra giá trị của vector 2 chiều
	{
		std::cout << x << ", " << y << std::endl;
	}

	float x, y;
};
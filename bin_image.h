#pragma once 
#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <math.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <iostream>
#include "errors.h"


/*
Сделать тип пикселя шаблонным параметром.Обеспечить работоспособность шаблонного класса как минимум со следующими типами :
bool;
char;
short;
float.
*/

template<typename type>
class bin_image
{
private:
	type** data;
	int length, width;
public:
	int get_length() const;
	int get_width() const;
	bin_image(int length = 10, int width = 10);
	type& operator ()(int str_index, int col_index) const;
	bin_image& operator !();
	double fill_factor() const;
	~bin_image();
	bin_image(const bin_image& a);

	friend std::ostream& operator <<(std::ostream& s, const bin_image<type>& image)
	{
		for (int i = 0; i < image.length; i++) {
			for (int j = 0; j < image.width; j++) {
				if (image.data[i][j] == false) { s << " ."; }
				if (image.data[i][j] == true) { s << " 1"; }
			}
			s << "\n";
		}
		return s;
	};

	friend bin_image<type> operator+(const bin_image<type>& image_1, const bin_image<type>& image_2)//сложение изображений bool
	{
		if (image_1.length != image_2.length || image_1.width != image_2.width) { throw error("Addition error"); }
		bin_image<type> image(image_1.length, image_1.width);
		for (int i = 0; i < image_1.length; i++) {
			for (int j = 0; j < image_1.width; j++) {
				image.data[i][j] = (image_1.data[i][j] || image_2.data[i][j]);
			}
		}
		return image;
	}

	friend bin_image<type> operator*(const bin_image<type>& image_1, const bin_image<type>& image_2)//умножение изображений bool
	{
		if (image_1.length != image_2.length || image_1.width != image_2.width) { throw error("Multiplication error"); }
		bin_image<type> image(image_1.length, image_1.width);
		for (int i = 0; i < image_1.length; i++) {
			for (int j = 0; j < image_1.width; j++) {
				image.data[i][j] = (image_1.data[i][j] && image_2.data[i][j]);
			}
		}
		return image;
	}

	friend bin_image<type> operator*(const bin_image<type>& image, bool a)
	{
		bin_image<type> tmp(image.length, image.width);
		for (int i = 0; i < image.length; i++) {
			for (int j = 0; j < image.width; j++) {
				tmp.data[i][j] = (image.data[i][j] && a);
			}
		}
		return tmp;
	}

	friend bin_image<type> operator+(const bin_image<type>& image, bool a)
	{
		bin_image<type> tmp(image.length, image.width);
		for (int i = 0; i < image.length; i++) {
			for (int j = 0; j < image.width; j++) {
				tmp.data[i][j] = (image.data[i][j] || a);
			}
		}
		return tmp;
	}

	friend bin_image<type> operator*(bool a, const bin_image<type>& image)
	{
		bin_image<type> tmp(image.length, image.width);
		for (int i = 0; i < image.length; i++) {
			for (int j = 0; j < image.width; j++) {
				tmp.data[i][j] = (image.data[i][j] && a);
			}
		}
		return tmp;
	}

	friend bin_image<type> operator+(bool a, const bin_image<type>& image)
	{
		bin_image<type> tmp(image.length, image.width);
		for (int i = 0; i < image.length; i++) {
			for (int j = 0; j < image.width; j++) {
				tmp.data[i][j] = (image.data[i][j] || a);
			}
		}
		return tmp;
	}
};

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
#include <vector>
using namespace std;

template<typename type>
class bin_image
{
private:
	vector<vector<type>> data;

	auto begin() { return data.begin(); }

	auto end() { return data.end(); }

	int length, width;
public:
	int get_length() const;
	int get_width() const;
	bin_image(int length = 10, int width = 10);
	type operator ()(int str_index, int col_index) const;
	void operator ()(int str_index, int col_index, type value);
	bin_image& operator !();
	double fill_factor() const;
	~bin_image();
	bin_image(const bin_image& a);

	friend std::ostream& operator <<(std::ostream& s, const bin_image<type>& image) 
	{
		/*for (int i = 0; i < image.length; i++) {
			for (int j = 0; j < image.width; j++) {
				if (image.data[i][j] == 0) { s << " ."; }
				if (image.data[i][j] == 1) { s << " 1"; }
			}
			s << "\n";
		}*/
		for (auto lines : image.data) {
			for (auto lines_item : lines) {
				if (lines_item == 0) { s << " ."; }
				if (lines_item == 1) { s << " 1"; }
			}
			s << "\n";
		}
		return s;
	};

	friend bin_image<type> operator+(const bin_image<type>& image_1, const bin_image<type>& image_2)//сложение изображений bool
	{
		if (image_1.length != image_2.length || image_1.width != image_2.width) { throw error("Addition error"); }
		bin_image<type> image(image_1.length, image_1.width);
		/*for (int i = 0; i < image_1.length; i++) {
			for (int j = 0; j < image_1.width; j++) {
				image.data[i][j] = (image_1.data[i][j] || image_2.data[i][j]);
			}
		}*/
		int i = 0;
		int j = 0;
		for (auto iterator1 = image.data.begin(); iterator1 != image.data.end(); iterator1++) {
			for (auto iterator2 = (*iterator1).begin(); iterator2 != (*iterator1).end(); iterator2++) {
				(*iterator2) = (image_1.data.at(i).at(j) || image_2.data.at(i).at(j));
				j++;
			}
			j = 0;
			i++;
		}
		return image;
	}

	friend bin_image<type> operator*(const bin_image<type>& image_1, const bin_image<type>& image_2)//умножение изображений bool
	{
		if (image_1.length != image_2.length || image_1.width != image_2.width) { throw error("Multiplication error"); }
		bin_image<type> image(image_1.length, image_1.width);
		/*for (int i = 0; i < image_1.length; i++) {
			for (int j = 0; j < image_1.width; j++) {
				image.data[i][j] = (image_1.data[i][j] && image_2.data[i][j]);
			}
		}*/
		int i = 0;
		int j = 0;
		for (auto iterator1 = image.data.begin(); iterator1 != image.data.end(); iterator1++) {
			for (auto iterator2 = (*iterator1).begin(); iterator2 != (*iterator1).end(); iterator2++) {
				(*iterator2) = (image_1.data.at(i).at(j) && image_2.data.at(i).at(j));
				j++;
			}
			j = 0;
			i++;
		}
		return image;
	}

	friend bin_image<type> operator*(const bin_image<type>& image, bool a)
	{
		bin_image<type> tmp(image.length, image.width);
		/*for (int i = 0; i < image.length; i++) {
			for (int j = 0; j < image.width; j++) {
				tmp.data[i][j] = (image.data[i][j] && a);
			}
		}*/
		int i = 0;
		int j = 0;
		for (auto iterator1 = tmp.data.begin(); iterator1 != tmp.data.end(); iterator1++) {
			for (auto iterator2 = (*iterator1).begin(); iterator2 != (*iterator1).end(); iterator2++) {
				(*iterator2) = (image.data.at(i).at(j) && a);
				j++;
			}
			j = 0;
			i++;
		}
		return tmp;
	}

	friend bin_image<type> operator+(const bin_image<type>& image, bool a)
	{
		bin_image<type> tmp(image.length, image.width);
		/*for (int i = 0; i < image.length; i++) {
			for (int j = 0; j < image.width; j++) {
				tmp.data[i][j] = (image.data[i][j] || a);
			}
		}*/
		int i = 0;
		int j = 0;
		for (auto iterator1 = tmp.data.begin(); iterator1 != tmp.data.end(); iterator1++) {
			for (auto iterator2 = (*iterator1).begin(); iterator2 != (*iterator1).end(); iterator2++) {
				(*iterator2) = (image.data.at(i).at(j) || a);
				j++;
			}
			j = 0;
			i++;
		}
		return tmp;
	}

	friend bin_image<type> operator*(bool a, const bin_image<type>& image)
	{
		bin_image<type> tmp(image.length, image.width);
		/*for (int i = 0; i < image.length; i++) {
			for (int j = 0; j < image.width; j++) {
				tmp.data[i][j] = (image.data[i][j] && a);
			}
		}*/
		int i = 0;
		int j = 0;
		for (auto iterator1 = tmp.data.begin(); iterator1 != tmp.data.end(); iterator1++) {
			for (auto iterator2 = (*iterator1).begin(); iterator2 != (*iterator1).end(); iterator2++) {
				(*iterator2) = (image.data.at(i).at(j) && a);
				j++;
			}
			j = 0;
			i++;
		}
		return tmp;
	}

	friend bin_image<type> operator+(bool a, const bin_image<type>& image)
	{
		bin_image<type> tmp(image.length, image.width);
		int i = 0;
		int j = 0;
		for (auto iterator1 = tmp.data.begin(); iterator1 != tmp.data.end(); iterator1++) {
			for (auto iterator2 = (*iterator1).begin(); iterator2 != (*iterator1).end(); iterator2++) {
				(*iterator2) = (image.data.at(i).at(j) || a);
				j++;
			}
			j = 0;
			i++;
		}
		return tmp;
	}
};

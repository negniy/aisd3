#include "bin_image.h"
#pragma once


template<typename type>
int bin_image<type>::get_length() const
{
	return length;
}

template<typename type>
int bin_image<type>::get_width() const
{
	return width;
}

template<typename type>
bin_image<type>::bin_image(int length, int width) : length(length), width(width)
{
	if (length < 1 || width < 1) { throw error("Incorrect length and width calculations"); }
	data = new type * [length];
	for (int i = 0; i < length; i++) {
		data[i] = new type[width];
	}
}

template<typename type>
type& bin_image<type>::operator ()(int str_index, int col_index) const {
	if (str_index < 0 || str_index >= length) { throw error("Invalid str_index"); }
	if (col_index < 0 || col_index >= width) { throw error("Invalid col_index"); }
	type& a = data[str_index][col_index];
	return a;
}

template<typename type>
bin_image<type>& bin_image<type>:: operator !() {
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			if (data[i][j] == 0) {
				data[i][j] = 1;
			}
			else {
				data[i][j] = 0;
			}
		}
	}
	return *this;
}

template<typename type>
double bin_image<type>::fill_factor() const {
	double count_0 = 0;
	double count_1 = 0;
	for (int i = 0; i < length; i++) {
		for (int j = 0; j < width; j++) {
			if (data[i][j] == false) { count_0 += 1; }
			if (data[i][j] == true) { count_1 += 1; }
		}
	}
	return (double)(count_1) / (count_0 + count_1);
}

template<typename type>
bin_image<type>::~bin_image() {
	for (int i = 0; i < length; i++) {
		delete[]data[i];
	}
	delete[]data;
	length = 0;
	width = 0;
}

template<typename type>
bin_image<type>::bin_image(const bin_image& a) {
	length = a.length;
	width = a.width;
	data = new type * [length];
	for (int i = 0; i < length; i++) {
		data[i] = new type[width];
		for (int j = 0; j < width; j++) {
			data[i][j] = a.data[i][j];
		}
	}
}


template class bin_image<short>;
template class bin_image<float>;
template class bin_image<bool>;
template class bin_image<char>;


#pragma once 
#include "bin_image.h"
#include "stdio.h"
#include <stdlib.h>
#include <string>
#include <ctype.h>
#include <math.h>
#include <locale.h>
#include <windows.h>
#include <conio.h>
#include <time.h>
#include <iostream>
#include "errors.h"
using namespace std;

/*
В данной работе необходимо улучшить свой класс из предыдущей лабораторной работы, полностью делегировав управление памятью стандартному контейнеру.
1. Конструктор копирования, оператор присваивания и деструктор в классе должны неявно генерироваться компилятором (см. ключевое слово default); при этом операции копирования должны выполнять глубокое клонирование объекта (т. е. внешнее поведение класса должно остаться таким же, каким и было).
2. Внутри класса не должно остаться ни указателей, ни ручного управления памятью.
3. В качестве поля класса должен появиться стандартный контейнер std::vector или std::list/std::forward_list (в зависимости от того, использовали вы массив или связный список в предыдущей лабораторной работе).
4. Элементы, хранящиеся в классе, должны быть константно итерируемыми с помощью range-based for loop (for(auto i: v) {}).В частности, это означает, что вы должны определить методы begin() и end() для вашего класса и возвращать соответствующий итератор.
5. Распечатку элементов проводить с помощью range - based for loop(for (auto i : v) { }).

*/

int get_key()
{
	int key = _getch();
	if ((key == 0) || (key == 224)) key = _getch();
	return key;
};

int menu_1()
{
	std::cout << "Выберите, как вы хотите продолжить работу:\n";
	std::cout << "Инвертировать изображение: Enter\nСложить с другим изображением: 1\nУмножить на другое изображение: 2\nСложить с булевским значением: 3\nУмножить на булевское значение: 4\nВычислить коэффициент заполнения изображения: 5\nВыход из прог-мы: Esc\n";
	while (true)
	{
		int key = get_key();
		if ((key == 13) || (key == 49) || (key == 50) || (key == 51) || (key == 52) || (key == 53) || (key == 27)) return key;
	}
}

int menu_2()
{
	std::cout << "Вернуться: Enter\nВыход из прог-мы: Esc\n";
	while (true)
	{
		int key = get_key();
		if ((key == 13) || (key == 27)) return key;
	}
}

int check() {
	int number = -1;
	while (number < 0)
	{
		while (!(std::cin >> number) || (std::cin.peek() != '\n'))
		{
			std::cin.clear();
			while (std::cin.get() != '\n');
			std::cout << "Некорректное значение, повторите ввод\n";
		}
		if (number < 0) std::cout << "Некорректное значение, повторите ввод\n";

	}

	return number;
}

bool check_bool() {
	bool number = FALSE;

	while (!(std::cin >> number) || (std::cin.peek() != '\n'))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "Некорректное значение, повторите ввод\n";
	}

	return number;
}

double check_double() {
	double number = 0;
	while (number <= 0)
	{
		while (!(std::cin >> number) || (std::cin.peek() != '\n'))
		{
			std::cin.clear();
			while (std::cin.get() != '\n');
			std::cout << "Некорректное значение, повторите ввод\n";
		}
		if (number <= 0) std::cout << "Некорректное значение, повторите ввод\n";
	}
	return number;
}

template<typename type>
bin_image<type> create_image() {
	std::cout << "\nВведите размеры изображения(длина, ширина)\n";
	int length, width;
	length = check();
	width = check();
	try {
		bin_image<type> A(length, width);
		return A;
	}
	catch (error programm_error) {
		programm_error.print();
		while (true) {
			std::cout << "\nВведите размеры изображения(длина, ширина)\n";
			length = check();
			width = check();
			try {
				bin_image<type> A(length, width);
				return A;
			}
			catch (error programm_error) {
				programm_error.print();
			}
		}
	}
}

template<typename type>
void create_circle(double radios, int x, int y, bin_image<type>& A) {
	if (radios < 0) { throw error("Invalid radios value\n"); }

	for (int j = 0; j < A.get_width(); j++) { // проверка за выход за границы по вертикали
		int i = -1;
		double a = sqrt((y - i) * (y - i) + (x - j) * (x - j));
		if (a <= radios) { throw error("Going beyond the boundaries of the image\n"); }
		i = A.get_length();
		a = sqrt((x - i) * (x - i) + (y - j) * (y - j));
		if (a <= radios) { throw error("Going beyond the boundaries of the image\n"); }
	}

	for (int i = 0; i < A.get_length(); i++) { // проверка за выход за границы по горизонтали
		int j = -1;
		double a = sqrt((y - i) * (y - i) + (x - j) * (x - j));
		if (a <= radios) { throw error("Going beyond the boundaries of the image\n"); }
		j = A.get_width();
		a = sqrt((x - i) * (x - i) + (y - j) * (y - j));
		if (a <= radios) { throw error("Going beyond the boundaries of the image\n"); }
	}

	for (int i = 0; i < A.get_length(); i++) {
		for (int j = 0; j < A.get_width(); j++) {
			double a = sqrt((y - i) * (y - i) + (x - j) * (x - j));
			if (a <= radios) {
				A(i, j, true);
			}
			else { A(i, j, false); }
		}
	}

	if (A.fill_factor() == 0) throw error("Empty image\n");
}

template<typename type>
int main_type() {

	while (true) {
		system("cls");
		std::cout << "\nЭто программа по работе с бинарными изображениями окружности\n";
		bin_image<type> A = create_image<type>();
		std::cout << "\nВведите радиус и координаты центра(х,у) окружности\n";
		double R = check_double();
		int x = check(); int y = check();
		try {
			create_circle<type>(R, x, y, A);
		}
		catch (error programm_error) {
			programm_error.print();
			while (true) {
				std::cout << "Некорректные координаты центра или радиус введите еще раз: R (х,у)\n";
				R = check_double();
				x = check(); y = check();
				try {
					create_circle<type>(R, x, y, A);
					break;
				}
				catch (error programm_error) {
					programm_error.print();
				}
			}
		}
		while (true) {
			std::cin.clear();
			system("cls");
			std::cout << A;
			std::cout << "\nОкружность радиуса R=" << R << " с центром в точке О" << "(" << x << ";" << y << ")\n";
			int m1 = menu_1();
			//выход из программы
			if (m1 == 27) return 0;
			//интвертировать
			if (m1 == 13) {
				A = !A;
				while (true) {
					system("cls");
					std::cout << "Инвертированное изображение:\n";
					std::cout << A;
					int m2 = menu_2();
					if (m2 == 27) return 0;
					if (m2 == 13) {
						A = !A;
						break;
					}
				}
			}
			// коэф заполнения
			if (m1 == 53) {
				while (true) {
					system("cls");
					std::cout << "Коэффициент заполнения = " << A.fill_factor() << "\n";
					int m2 = menu_2();
					if (m2 == 27) return 0;
					if (m2 == 13) {
						break;
					}
				}
			}
			// сложить с изобр
			if (m1 == 49) {
				bin_image<type> B = create_image<type>();
				std::cout << "\nВведите радиус и координаты центра(х,у) окружности\n";
				double R2 = check_double();
				int x2 = check(); int y2 = check();
				try {
					create_circle<type>(R2, x2, y2, B);
				}
				catch (error programm_error) {
					programm_error.print();
					while (true) {
						std::cout << "Некорректные координаты центра или радиус введите еще раз: R (х,у)\n";
						R2 = check_double();
						x2 = check(); y2 = check();
						try {
							create_circle(R2, x2, y2, B);
							break;
						}
						catch (error programm_error) {
							programm_error.print();
						}
					}
				}
				try {
					bin_image<type> C = A + B;
					while (true) {
						system("cls");
						std::cout << "Полученное изображение\n";
						std::cout << C;
						int m2 = menu_2();
						if (m2 == 27) return 0;
						if (m2 == 13) break;
					}
				}
				catch (error programm_error) {
					programm_error.print();
					while (true) {
						system("cls");
						std::cout << "Невозвожно сложить 2 изображения\n";
						int m3 = menu_2();
						if (m3 == 27) return 0;
						if (m3 == 13) break;
					}
				}
			}
			//умножить на изобр
			if (m1 == 50) {
				bin_image<type> B = create_image<type>();
				std::cout << "\nВведите радиус и координаты центра(х,у) окружности\n";
				double R2 = check_double();
				int x2 = check(); int y2 = check();
				try {
					create_circle(R2, x2, y2, B);
				}
				catch (error programm_error) {
					programm_error.print();
					while (true) {
						std::cout << "Некорректные координаты центра или радиус введите еще раз: R (х,у)\n";
						R2 = check_double();
						x2 = check(); y2 = check();
						try {
							create_circle(R2, x2, y2, B);
							break;
						}
						catch (error programm_error) {
							programm_error.print();
						}
					}
				}
				try {
					bin_image<type> C = A * B;
					while (true) {
						system("cls");
						std::cout << "Полученное изображение\n";
						std::cout << C;
						int m2 = menu_2();
						if (m2 == 27) return 0;
						if (m2 == 13) break;
					}
				}
				catch (error programm_error) {
					programm_error.print();
					while (true) {
						system("cls");
						std::cout << "Невозвожно умножить 2 изображения\n";
						int m3 = menu_2();
						if (m3 == 27) return 0;
						if (m3 == 13) break;
					}
				}
			}
			// сложить с булевским
			if (m1 == 51) {
				system("cls");
				std::cout << "Введите булевское значение:\n";
				bool n = check_bool();
				bin_image<type> tmp = A + n;
				while (true) {
					system("cls");
					std::cout << "Полученное изображение:\n";
					std::cout << tmp;
					int m2 = menu_2();
					if (m2 == 27) return 0;
					if (m2 == 13) break;
				}
			}
			// умножить на булевское
			if (m1 == 52) {
				system("cls");
				std::cout << "Введите булевское значение:\n";
				bool n = check_bool();
				bin_image<type> tmp = n * A;
				while (true) {
					system("cls");
					std::cout << "Полученное изображение:\n";
					std::cout << tmp;
					int m2 = menu_2();
					if (m2 == 27) return 0;
					if (m2 == 13) break;
				}
			}
		}
	}
	return 0;
}

int main() {
	{
		SetConsoleCP(1251);
		SetConsoleOutputCP(1251);
		setlocale(LC_ALL, "RUS");
		while (true) {
			system("cls");
			std::cout << "Выберите тип:\n";
			std::cout << "[1] - short\n";
			std::cout << "[2] - float\n";
			std::cout << "[3] - bool\n";
			std::cout << "[4] - char\n";
			std::cout << "[ESC] - Exit\n";

			int m = get_key();

			switch (m)
			{
			case 49:
				main_type<short>();
				break;
			case 50:
				main_type<float>();
				break;
			case 51:
				main_type<bool>();
				break;
			case 52:
				main_type<char>();
				break;
			case 27:
				return 0;
				break;
			}
		}
	}
}
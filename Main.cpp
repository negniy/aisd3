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
� ������ ������ ���������� �������� ���� ����� �� ���������� ������������ ������, ��������� ����������� ���������� ������� ������������ ����������.
1. ����������� �����������, �������� ������������ � ���������� � ������ ������ ������ �������������� ������������ (��. �������� ����� default); ��� ���� �������� ����������� ������ ��������� �������� ������������ ������� (�. �. ������� ��������� ������ ������ �������� ����� ��, ����� � ����).
2. ������ ������ �� ������ �������� �� ����������, �� ������� ���������� �������.
3. � �������� ���� ������ ������ ��������� ����������� ��������� std::vector ��� std::list/std::forward_list (� ����������� �� ����, ������������ �� ������ ��� ������� ������ � ���������� ������������ ������).
4. ��������, ���������� � ������, ������ ���� ���������� ������������ � ������� range-based for loop (for(auto i: v) {}).� ���������, ��� ��������, ��� �� ������ ���������� ������ begin() � end() ��� ������ ������ � ���������� ��������������� ��������.
5. ���������� ��������� ��������� � ������� range - based for loop(for (auto i : v) { }).

*/

int get_key()
{
	int key = _getch();
	if ((key == 0) || (key == 224)) key = _getch();
	return key;
};

int menu_1()
{
	std::cout << "��������, ��� �� ������ ���������� ������:\n";
	std::cout << "������������� �����������: Enter\n������� � ������ ������������: 1\n�������� �� ������ �����������: 2\n������� � ��������� ���������: 3\n�������� �� ��������� ��������: 4\n��������� ����������� ���������� �����������: 5\n����� �� ����-��: Esc\n";
	while (true)
	{
		int key = get_key();
		if ((key == 13) || (key == 49) || (key == 50) || (key == 51) || (key == 52) || (key == 53) || (key == 27)) return key;
	}
}

int menu_2()
{
	std::cout << "���������: Enter\n����� �� ����-��: Esc\n";
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
			std::cout << "������������ ��������, ��������� ����\n";
		}
		if (number < 0) std::cout << "������������ ��������, ��������� ����\n";

	}

	return number;
}

bool check_bool() {
	bool number = FALSE;

	while (!(std::cin >> number) || (std::cin.peek() != '\n'))
	{
		std::cin.clear();
		while (std::cin.get() != '\n');
		std::cout << "������������ ��������, ��������� ����\n";
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
			std::cout << "������������ ��������, ��������� ����\n";
		}
		if (number <= 0) std::cout << "������������ ��������, ��������� ����\n";
	}
	return number;
}

template<typename type>
bin_image<type> create_image() {
	std::cout << "\n������� ������� �����������(�����, ������)\n";
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
			std::cout << "\n������� ������� �����������(�����, ������)\n";
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

	for (int j = 0; j < A.get_width(); j++) { // �������� �� ����� �� ������� �� ���������
		int i = -1;
		double a = sqrt((y - i) * (y - i) + (x - j) * (x - j));
		if (a <= radios) { throw error("Going beyond the boundaries of the image\n"); }
		i = A.get_length();
		a = sqrt((x - i) * (x - i) + (y - j) * (y - j));
		if (a <= radios) { throw error("Going beyond the boundaries of the image\n"); }
	}

	for (int i = 0; i < A.get_length(); i++) { // �������� �� ����� �� ������� �� �����������
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
		std::cout << "\n��� ��������� �� ������ � ��������� ������������� ����������\n";
		bin_image<type> A = create_image<type>();
		std::cout << "\n������� ������ � ���������� ������(�,�) ����������\n";
		double R = check_double();
		int x = check(); int y = check();
		try {
			create_circle<type>(R, x, y, A);
		}
		catch (error programm_error) {
			programm_error.print();
			while (true) {
				std::cout << "������������ ���������� ������ ��� ������ ������� ��� ���: R (�,�)\n";
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
			std::cout << "\n���������� ������� R=" << R << " � ������� � ����� �" << "(" << x << ";" << y << ")\n";
			int m1 = menu_1();
			//����� �� ���������
			if (m1 == 27) return 0;
			//��������������
			if (m1 == 13) {
				A = !A;
				while (true) {
					system("cls");
					std::cout << "��������������� �����������:\n";
					std::cout << A;
					int m2 = menu_2();
					if (m2 == 27) return 0;
					if (m2 == 13) {
						A = !A;
						break;
					}
				}
			}
			// ���� ����������
			if (m1 == 53) {
				while (true) {
					system("cls");
					std::cout << "����������� ���������� = " << A.fill_factor() << "\n";
					int m2 = menu_2();
					if (m2 == 27) return 0;
					if (m2 == 13) {
						break;
					}
				}
			}
			// ������� � �����
			if (m1 == 49) {
				bin_image<type> B = create_image<type>();
				std::cout << "\n������� ������ � ���������� ������(�,�) ����������\n";
				double R2 = check_double();
				int x2 = check(); int y2 = check();
				try {
					create_circle<type>(R2, x2, y2, B);
				}
				catch (error programm_error) {
					programm_error.print();
					while (true) {
						std::cout << "������������ ���������� ������ ��� ������ ������� ��� ���: R (�,�)\n";
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
						std::cout << "���������� �����������\n";
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
						std::cout << "���������� ������� 2 �����������\n";
						int m3 = menu_2();
						if (m3 == 27) return 0;
						if (m3 == 13) break;
					}
				}
			}
			//�������� �� �����
			if (m1 == 50) {
				bin_image<type> B = create_image<type>();
				std::cout << "\n������� ������ � ���������� ������(�,�) ����������\n";
				double R2 = check_double();
				int x2 = check(); int y2 = check();
				try {
					create_circle(R2, x2, y2, B);
				}
				catch (error programm_error) {
					programm_error.print();
					while (true) {
						std::cout << "������������ ���������� ������ ��� ������ ������� ��� ���: R (�,�)\n";
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
						std::cout << "���������� �����������\n";
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
						std::cout << "���������� �������� 2 �����������\n";
						int m3 = menu_2();
						if (m3 == 27) return 0;
						if (m3 == 13) break;
					}
				}
			}
			// ������� � ���������
			if (m1 == 51) {
				system("cls");
				std::cout << "������� ��������� ��������:\n";
				bool n = check_bool();
				bin_image<type> tmp = A + n;
				while (true) {
					system("cls");
					std::cout << "���������� �����������:\n";
					std::cout << tmp;
					int m2 = menu_2();
					if (m2 == 27) return 0;
					if (m2 == 13) break;
				}
			}
			// �������� �� ���������
			if (m1 == 52) {
				system("cls");
				std::cout << "������� ��������� ��������:\n";
				bool n = check_bool();
				bin_image<type> tmp = n * A;
				while (true) {
					system("cls");
					std::cout << "���������� �����������:\n";
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
			std::cout << "�������� ���:\n";
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
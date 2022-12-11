#pragma once

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

class error
{
private:
	char* message;
public:
	error(const char* message);
	error(const error& e);
	~error();
	const char* get_message();
	void print();
};


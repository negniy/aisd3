#pragma once 
#include "errors.h"

error::error(const char* message)
{
	this->message = _strdup(message);
}

error::error(const error& e)
{
	this->message = _strdup(e.message);
}

error::~error()
{
	free(message);
}

const char* error::get_message() { return message; }

void error::print() { std::cout << message; }
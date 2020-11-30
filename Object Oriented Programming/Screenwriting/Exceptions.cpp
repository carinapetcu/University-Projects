#include "Exceptions.h"

const char* ValidationException::what() const noexcept
{
	return this->message.c_str();
}

const char* RepositoryException::what() const noexcept
{
	return this->message.c_str();
}
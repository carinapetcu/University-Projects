#pragma once
#include <exception>
#include <string>

class ValidationException: public std::exception 
{
private:
	std::string message;

public:
	ValidationException(std::string errors) : message{ errors } {};
	const char* what() const noexcept override;
};

class RepositoryException : public std::exception
{
private:
	std::string message;

public:
	RepositoryException(std::string errors) : message{ errors } {};
	const char* what() const noexcept override;
};
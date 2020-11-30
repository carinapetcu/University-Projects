#include "Validators.h"
#include "Tape.h"

void ValidateTape::validateTape(const Task& tape)
{
	std::string errors;
	int month = tape.getDate().getMonth(), day = tape.getDate().getDay(), year = tape.getDate().getYear();
	if (month <= 0 || month >= 12)
		errors += "Invalid month!\n";
	if (day <= 0)
		errors += "Invalid day!\n";
	if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && day >= 32)
		errors += "Invalid combination day/month for months with 31 days!\n";
	if (month == 2 && year % 4 != 0 && day >= 29)
		errors += "Invalid February combination non-leap year!\n";
	if (month == 2 && year % 4 == 0 && day >= 30)
		errors += "Invalid February combination leap year!\n";
	if ((month == 4 || month == 6 || month == 9 || month == 11) && day >= 31)
		errors += "Invalid combination day/month for months with 30 days!\n";
	if (year <= 0)
		errors += "Invalid year!\n";
	if (errors.size() > 0)
		throw ValidationException(errors);
}
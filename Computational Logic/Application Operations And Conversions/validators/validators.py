from exceptions.exceptions import ValidationError


class ValidateNumber:
    def __init__(self):
        pass

    @staticmethod
    def validate_number(number):
        foundErrors = ""
        base = int(number.get_base())
        value = number.get_number()
        listOfDigits = ['0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '10']
        listOfLetters = [['a'], ['a', 'b'], ['a', 'b', 'c'], ['a', 'b', 'c', 'd'], ['a', 'b', 'c', 'd', 'e'],
                         ['a', 'b', 'c', 'd', 'e', 'f']]
        for digit in value:
            if digit not in listOfDigits:
                if base <= 10:
                    foundErrors += "The base is invalid! "
                elif digit.lower() not in listOfLetters[base % 10 - 1]:
                    foundErrors += "The base is invalid! "
            else:
                if int(digit) >= base:
                    foundErrors += "The base is invalid! "
        if number.get_base() < 0:
            foundErrors += "The base is invalid! "
        if len(foundErrors) > 0:
            raise ValidationError(foundErrors)

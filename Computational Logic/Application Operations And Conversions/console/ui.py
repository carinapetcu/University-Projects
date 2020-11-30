from exceptions.exceptions import ValidationError, RepositoryError
from entities.entities import Number


class ApplicationUI:

    def __add_two_integers(self):
        firstNumber = input("Please enter the first number: ")
        secondNumber = input("Please enter the second number: ")
        base = int(input("Please input the base of the numbers: "))
        result = self.__serviceNumber.add_integers(Number(firstNumber, base), Number(secondNumber, base))
        print("The sum between {} and {} in base {} is {}".format(firstNumber, secondNumber, base, result))

    def __subtract_two_integers(self):
        firstNumber = input("Please enter the first number: ")
        secondNumber = input("Please enter the second number: ")
        base = int(input("Please input the base of the numbers: "))
        result = self.__serviceNumber.subtract_integers(Number(firstNumber, base), Number(secondNumber, base))
        print("The difference between {} and {} in base {} is {}".format(firstNumber, secondNumber, base, result))

    def __multiply_two_integers(self):
        firstNumber = input("Please enter the first number: ")
        secondNumber = input("Please enter the second number: ")
        base = int(input("Please input the base of the numbers: "))
        if len(secondNumber) != 1:
            print("Invalid input. The second number must be a digit.")
        else:
            result = self.__serviceNumber.multiply_integers(Number(firstNumber, base), Number(secondNumber, base))
            print("The product between {} and {} in base {} is {}".format(firstNumber, secondNumber, base, result))

    def __divide_two_integers(self):
        firstNumber = input("Please enter the first number: ")
        secondNumber = input("Please enter the second number: ")
        base = int(input("Please input the base of the numbers: "))
        if len(secondNumber) != 1:
            print("Invalid input. The second number must be a digit.")
        else:
            quotient, remainder = self.__serviceNumber.divide_integers(Number(firstNumber, base),
                                                                       Number(secondNumber, base))
            print("The division between {} and {} in base {} has a quotient of {} and a remainder of {}".format(
                firstNumber, secondNumber, base, quotient, remainder))

    def __converse_from_base_to_another_base(self):
        number = input("Please enter the number: ")
        sourceBase = int(input("Please enter the source base: "))
        destinationBase = int(input("Please enter the destination base: "))
        result = self.__serviceNumber.converse_from_base_to_another_base(Number(number, sourceBase), destinationBase)
        print("The number {} in base {} converted in base {} is {}".format(number, sourceBase, destinationBase, result))

    def __init__(self, serviceNumber):
        self.__serviceNumber = serviceNumber
        self.__commands = {
            '1': self.__add_two_integers,
            '2': self.__subtract_two_integers,
            '3': self.__multiply_two_integers,
            '4': self.__divide_two_integers,
            '5': self.__converse_from_base_to_another_base
        }

    @staticmethod
    def __print_commands():
        print("Choose one of the options:\n"
              "1. Add 2 integer numbers of the same base.\n"
              "2. Subtract 2 integer numbers of the same base.\n"
              "3. Multiply 2 integer numbers of the same base, the second one being of one digit.\n"
              "4. Divide 2 integer numbers of the same base, the second one being of one digit.\n"
              "5. Converse a natural number from a base to another base.\n"
              "x. Exit the application\n")

    def start_application(self):
        while True:
            self.__print_commands()
            command = input("Your choice is:")
            if command == 'x':
                break
            else:
                command.strip()
                if command == "":
                    continue
                else:
                    if command in self.__commands:
                        try:
                            self.__commands[command]()
                        except ValueError as valueError:
                            print("UI error:\n" + str(valueError))
                        except ValidationError as validationError:
                            print("Business error:\n" + str(validationError))
                        except RepositoryError as repositoryError:
                            print("Repository error:\n" + str(repositoryError))
                    else:
                        print("Invalid command!")

from Exceptions.Exceptions import ValidatorError


class Application:
    def __init__(self, service):
        self.__service = service
        self.__commands = {
            'place': self.__place_pattern,
            'tick': self.__tick_generation,
            'save': self.__save_file,
            'load': self.__load_file
        }

    def print_board(self):
        print(self.__service.get_board())

    def __tick_generation(self, userInput):
        if len(userInput) == 0:
            numberOfGenerations = 1
        else:
            numberOfGenerations = int(userInput[0])
        self.__service.tick(numberOfGenerations)

    def __save_file(self, userInput):
        if len(userInput) != 1:
            raise ValueError("The length is invalid!")
        self.__service.save_file(userInput[0])

    def __load_file(self, userInput):
        if len(userInput) != 1:
            raise ValueError("The length is invalid!")
        self.__service.load_file(userInput[0])

    def __place_pattern(self, userInput):
        if len(userInput) != 2:
            raise ValueError("The length is invalid!")
        pattern = userInput[0]
        coordinates = userInput[1]
        coordinates = coordinates.split(",")
        self.__service.place_pattern(pattern, coordinates)

    def start(self):
        self.print_board()
        while True:
            userInput = input('Please enter your command: ')
            userInput.strip()
            if userInput == "":
                continue
            elif userInput == 'exit':
                break
            else:
                userInput = userInput.split(" ")
                command = userInput[0]
                if command in self.__commands:
                    try:
                        userInput = userInput[1:]
                        self.__commands[command](userInput)
                        self.print_board()
                    except ValueError as valueError:
                        print(valueError)
                    except ValidatorError as validatorError:
                        print(validatorError)
                else:
                    print("Invalid command! Try harder!")

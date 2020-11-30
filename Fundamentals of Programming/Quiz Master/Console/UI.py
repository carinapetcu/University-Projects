from Exceptions.Exceptions import ValidationError, RepositoryError, ServiceError


class ApplicationUI:
    def __init__(self, service_game):
        self.__service_game = service_game
        self.__commands = {
            'add': self.__add,
            'create' : self.__create,
            'start': self.__start
        }

    def __add(self, question):
        if len(question) != 7:
            raise ValueError("The command requires more parameters!")
        id = int(question[0])
        text = question[1]
        choice_a = question[2]
        choice_b = question[3]
        choice_c = question[4]
        correct_choice = question[5]
        difficulty = question[6]

        self.__service_game.add_question(id, text, choice_a, choice_b, choice_c, correct_choice, difficulty)

    def __create(self, parameters):
        if len(parameters) != 3:
            raise ValueError("The command requires more parameters!")
        difficulty = parameters[0]
        number_of_questions = int(parameters[1])
        file_name = parameters[2]

        self.__service_game.create_quiz(difficulty, number_of_questions, file_name)

    def __start(self, parameter):
        if len(parameter) != 1:
            raise ValueError("Invalid number of parameters!")
        file_name = parameter[0]
        questions = self.__service_game.start_quiz(file_name)
        user_choices = []
        for question in questions:
            print(question)
            user_choice = input("Please enter the choice: ")
            user_choices.append(user_choice)
        print("The score is :", self.__service_game.calculate_score(file_name, user_choices))

    def start_application(self):
        while True:
            parameters = []
            command = input(">>>")
            command.strip()
            if command == "exit":
                break
            elif command == "":
                continue
            elif command[:3] == "add":
                parameters = command[4:]
                parameters = parameters.split(";")
                command = command[:3]
            elif command[:6] == "create":
                parameters = command[7:]
                parameters = parameters.split(" ")
                command = command[:6]
            elif command[:5] == "start":
                parameters = command[6:]
                parameters = parameters.split(" ")
                command = command[:5]
            if command in self.__commands:
                try:
                    self.__commands[command](parameters)
                except ValueError as ve:
                    print(str(ve))
                except ValidationError as validation_error:
                    print(validation_error)
                except ServiceError as se:
                    print(se)
                except RepositoryError as re:
                    print(re)
            else:
                print("Invalid command!\n")

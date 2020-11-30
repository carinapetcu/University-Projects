class Question:
    def __init__(self, id, text, choice_a, choice_b, choice_c, correct_choice, difficulty):
        self.__id = id
        self.__text = text
        self.__choice_a = choice_a
        self.__choice_b = choice_b
        self.__choice_c = choice_c
        self.__correct_choice = correct_choice
        self.__difficulty = difficulty

    def get_id(self):
        return self.__id

    def get_text(self):
        return self.__text

    def get_choice_a(self):
        return self.__choice_a

    def get_choice_b(self):
        return self.__choice_b

    def get_choice_c(self):
        return self.__choice_c

    def get_correct_choice(self):
        return self.__correct_choice

    def get_difficulty(self):
        return self.__difficulty

    def __eq__(self, another_question):
        return self.__id == another_question.get_id()

    @staticmethod
    def read_mode(line):
        elements = line.split(";")
        return Question(elements[0], str(elements[1]), str(elements[2]), str(elements[3]), str(elements[4]),
                        str(elements[5]), str(elements[6]))

    @staticmethod
    def write_mode(question):
        return str(question.get_id()) + ";" + question.get_text() + ";" + question.get_choice_a() + ";" + \
               question.get_choice_b() + ";" + question.get_choice_c() + ";" + question.get_correct_choice() + ";" + \
               question.get_difficulty()

from Entities.Question import Question
from Exceptions.Exceptions import ServiceError
from Repository.Repositories import Repository, RepositoryFile


class ServiceGame:
    def __init__(self, repository_game, validate_question):
        self.__repository_game = repository_game
        self.__validate_question = validate_question

    def add_question(self, id, text, choice_a, choice_b, choice_c, correct_choice, difficulty):
        question = Question(id, text, choice_a, choice_b, choice_c, correct_choice, difficulty)
        self.__validate_question.validate(question)
        self.__repository_game.add("masterQuestionList.txt", question)

    def create_quiz(self, difficulty, number_of_questions, file_name):
        # now we see if there are enough questions with that difficulty
        questions = self.__repository_game.get_all_elements("masterQuestionList.txt")
        if len(questions) >= number_of_questions:
            number_of_questions_with_difficulty = 0
            questions_with_difficulty = []
            for question in questions:
                if question.get_difficulty()[0] == difficulty[0]:
                    number_of_questions_with_difficulty += 1
                    questions_with_difficulty.append(question)

            if number_of_questions_with_difficulty >= number_of_questions / 2:
                questions_for_quiz = []
                for question_with_difficulty in questions_with_difficulty:
                    if len(questions_for_quiz) < number_of_questions:
                        questions_for_quiz.append(question_with_difficulty)
                for question in questions:
                    if len(questions_for_quiz) < number_of_questions and question not in questions_for_quiz:
                        questions_for_quiz.append(question)
                for question in questions_for_quiz:
                    RepositoryFile(Question.read_mode, Question.write_mode).add(file_name, question)
            else:
                raise ServiceError("There are not enough questions with that difficulty!")
        else:
            raise ServiceError("There are not enough questions!")

    @staticmethod
    def start_quiz(file_name):
        questions = RepositoryFile(Question.read_mode, Question.write_mode).get_all_elements(file_name)
        questions_to_be_printed = []

        for question in questions:
            string_for_question = ""
            string_for_question += str(question.get_text()) + ":" + str(question.get_choice_a()) + "," + \
                                   str(question.get_choice_b()) + "," + str(question.get_choice_c())
            questions_to_be_printed.append(string_for_question)

        return questions_to_be_printed

    def calculate_score(self, file_name, user_choices):
        questions = RepositoryFile(Question.read_mode, Question.write_mode).get_all_elements(file_name)
        user_score = 0
        for index in range(len(user_choices)):
            # print(questions[index].get_correct_choice, user_choices[index])
            if user_choices[index] == questions[index].get_correct_choice():
                if questions[index].get_difficulty() == 'easy':
                    user_score += 1
                elif questions[index].get_difficulty() == 'medium':
                    user_score += 2
                elif questions[index].get_difficulty() == 'hard':
                    user_score += 3

        return user_score

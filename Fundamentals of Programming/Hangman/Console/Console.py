from Exceptions.Exceptions import RepositoryError, ValidateError


class GameUI:
    def __init__(self, serviceGame):
        self.__serviceGame = serviceGame

    def start_game(self, lettersShown):
        sentenceNumber = self.__serviceGame.get_random_sentence()
        self.__serviceGame.get_letters_from_sentence(sentenceNumber, lettersShown)
        print(self.__serviceGame.print_sentence(sentenceNumber, lettersShown))
        return sentenceNumber

    def continue_game(self, sentenceNumber, lettersShown, numberOfWrongLetters):
        letter = input("Please input a letter: ")
        if letter in lettersShown:
            numberOfWrongLetters += 1
        else:
            itExists = self.__serviceGame.add_letter_if_exists(letter, sentenceNumber, lettersShown)
            if not itExists:
                numberOfWrongLetters += 1
        print(self.__serviceGame.print_whole_sentence(sentenceNumber, lettersShown, numberOfWrongLetters))
        return numberOfWrongLetters

    def finish_game(self, sentenceNumber, lettersShown, numberOfWrongLetters):
        if numberOfWrongLetters == 7:
            print("The computer won!")
            return True
        else:
            isWon = self.__serviceGame.is_game_won(sentenceNumber, lettersShown)
            if isWon:
                print("You won! Congratulations!")
                return True
            else:
                return False

    def start_application(self):
        gameStarted = False
        sentenceNumber = 0
        lettersShown = []
        numberOfWrongLetters = 0
        while True:
            if not gameStarted:
                print("Do you want to add a sentence? Yes/ No")
                choice = input("Your choice is: ")
                if choice == 'Yes' or choice == 'yes':
                    try:
                        sentence = input("Please input a sentence: ")
                        self.__serviceGame.add_sentence(sentence)
                    except ValidateError as ve:
                        print(ve)
                    except RepositoryError as re:
                        print(re)
                print("Do you want to start the game? Yes/ No")
                gameChoice = input("Your choice is: ")
                if gameChoice == 'Yes' or gameChoice == 'yes':
                    sentenceNumber = self.start_game(lettersShown)
                    gameStarted = True
            else:
                numberOfWrongLetters = self.continue_game(sentenceNumber, lettersShown, numberOfWrongLetters)
                isGameEnded = self.finish_game(sentenceNumber, lettersShown, numberOfWrongLetters)
                if isGameEnded:
                    print("The game is ended.")
                    break

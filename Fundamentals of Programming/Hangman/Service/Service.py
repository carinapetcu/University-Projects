import random


class ServiceGame:
    def __init__(self, repositoryGame, validator):
        self.__repositoryGame = repositoryGame
        self.__validator = validator

    def add_sentence(self, sentence):
        self.__validator.validate_sentence(sentence)
        self.__repositoryGame.add_entity(sentence)

    def get_random_sentence(self):
        numberOfSentences = self.__repositoryGame.size()
        randomSentenceNumber = random.randrange(1, numberOfSentences, 1)
        return randomSentenceNumber

    def print_sentence(self, sentenceNumber, lettersShown):
        sentence = self.__repositoryGame.get_entity(sentenceNumber)
        sentence = sentence.split(" ")
        sentenceToBePrinted = ""
        for word in sentence:
            for index in range(len(word)):
                if word[index] in lettersShown:
                    sentenceToBePrinted += str(word[index])
                else:
                    sentenceToBePrinted += " _ "
            sentenceToBePrinted += " "
        return sentenceToBePrinted

    def get_letters_from_sentence(self, sentenceNumber, lettersShown):
        sentence = self.__repositoryGame.get_entity(sentenceNumber)
        sentence = sentence.split(" ")

        for word in sentence:
            if word[0] not in lettersShown:
                lettersShown.append(word[0])
            if word[len(word) - 1] not in lettersShown:
                lettersShown.append(word[len(word) - 1])

    def add_letter_if_exists(self, letter, sentenceNumber, lettersShown):
        sentence = self.__repositoryGame.get_entity(sentenceNumber)

        if letter not in sentence:
            return False

        sentence = sentence.split(" ")

        for word in sentence:
            if letter in word:
                lettersShown.append(letter)
        return True

    def print_whole_sentence(self, sentenceNumber, lettersShown, numberOfWrongLetters):
        hangman = "hangman"
        stringToBePrinted = ""
        stringToBePrinted += self.print_sentence(sentenceNumber, lettersShown)
        stringToBePrinted += " - "
        stringToBePrinted += str(hangman[:numberOfWrongLetters])

        return stringToBePrinted

    def is_game_won(self, sentenceNumber, lettersShown):
        sentence = self.__repositoryGame.get_entity(sentenceNumber)
        for letter in sentence:
            if letter not in lettersShown and letter != " ":
                return False

        return True
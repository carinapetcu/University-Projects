class Sentence:
    def __init__(self, sentence):
        self.__sentence = sentence

    def get_sentence(self):
        return self.__sentence

    def set_sentence(self, new_sentence):
        self.__sentence = new_sentence

    def __eq__(self, another_sentence):
        return self.__sentence == another_sentence

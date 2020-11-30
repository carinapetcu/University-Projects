from Exceptions.Exceptions import ValidateError

class ValidateSentence:
    @staticmethod
    def validate_sentence(sentence):
        words = sentence.split(" ")
        for index in range(len(words)):
            if words[index] == ' ':
                del words[index]
            if len(words[index]) < 3:
                raise ValidateError("The sentence is invalid.")

        if len(words) < 3:
            raise ValidateError("The sentence is invalid.")

        return True
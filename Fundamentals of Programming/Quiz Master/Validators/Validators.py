from Exceptions.Exceptions import ValidationError


class ValidateQuestion:
    @staticmethod
    def validate(question):
        if question.get_id() <= 0:
            raise ValidationError("The id is invalid!")
        if question.get_choice_a() != question.get_correct_choice() and \
                question.get_choice_b() != question.get_correct_choice() and \
                question.get_choice_c() != question.get_correct_choice():
            raise ValidationError("The correct choice is not in the list of choices!")
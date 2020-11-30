from errors.exceptions import ValidationError


class ValidateStudent(object):
    def __init__(self):
        pass

    @staticmethod
    def validate_student(student):
        foundErrors = ""
        if student.get_studentID() < 0:
            foundErrors += "The ID is invalid!"
        if student.get_studentName() == "":
            foundErrors += "The name of the student is invalid!"
        if len(foundErrors) > 0:
            raise ValidationError(foundErrors)


class ValidateSubject(object):
    def __init__(self):
        pass

    @staticmethod
    def validate_subject(subject):
        foundErrors = ""
        if subject.get_subjectID() < 0:
            foundErrors += "The ID is invalid!"
        if subject.get_subjectName() == "":
            foundErrors += "The name of the subject is invalid!"
        if len(foundErrors) > 0:
            raise ValidationError(foundErrors)


class ValidateGrade(object):
    def __init__(self):
        pass

    @staticmethod
    def validate_grade(grade):
        foundErrors = ""
        if grade.get_valueOfGrade() < 0 or grade.get_valueOfGrade() > 10:
            foundErrors += "The value of the grade is invalid!"
        if len(foundErrors) > 0:
            raise ValidationError(foundErrors)

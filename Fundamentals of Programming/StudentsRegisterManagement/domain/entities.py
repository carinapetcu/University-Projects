class Student(object):
    def __init__(self, studentID, studentName):
        self.__studentID = studentID
        self.__studentName = studentName

    def get_studentID(self):
        return self.__studentID

    def get_studentName(self):
        return self.__studentName

    def set_studentName(self, newStudentName):
        self.__studentName = newStudentName

    def __eq__(self, anotherStudent):
        return self.__studentID == anotherStudent.__studentID

    def __str__(self):
        return str(self.__studentID) + " " + self.__studentName

    @staticmethod
    def read_student(line):
        parts = line.split(",")
        return Student(int(parts[0]), parts[1])

    @staticmethod
    def write_student(student):
        return str(student.get_studentID()) + "," + student.get_studentName()


class Subject(object):
    def __init__(self, subjectID, subjectName):
        self.__subjectID = subjectID
        self.__subjectName = subjectName

    def get_subjectID(self):
        return self.__subjectID

    def get_subjectName(self):
        return self.__subjectName

    def set_subjectName(self, newSubjectName):
        self.__subjectName = newSubjectName

    def __eq__(self, anotherSubject):
        return self.__subjectID == anotherSubject.__subjectID

    def __str__(self):
        return str(self.__subjectID) + " " + self.__subjectName

    @staticmethod
    def read_subject(line):
        parts = line.split(",")
        return Subject(int(parts[0]), parts[1])

    @staticmethod
    def write_subject(subject):
        return str(subject.get_subjectID()) + "," + subject.get_subjectName()


class Grade(object):
    def __init__(self, student, subject, valueOfGrade):
        self.__student = student
        self.__subject = subject
        self.__valueOfGrade = valueOfGrade

    def get_student(self):
        return self.__student

    def get_subject(self):
        return self.__subject

    def get_valueOfGrade(self):
        return self.__valueOfGrade

    def set_valueOfGrade(self, newValue):
        self.__valueOfGrade = newValue

    def __eq__(self, anotherGrade):
        return self.__student.get_studentID() == anotherGrade.get_student().get_studentID() and \
               self.__subject.get_subjectID() == anotherGrade.get_subject().get_subjectID()

    @staticmethod
    def read_grade(line):
        parts = line.split(",")
        return Grade(Student(int(parts[0]), None), Subject(int(parts[1]), None), float(parts[2]))

    @staticmethod
    def write_grade(grade):
        return str(grade.get_student().get_studentID()) + "," + str(grade.get_subject().get_subjectID()) + "," \
               + str(grade.get_valueOfGrade())


class GradeDTO(object):
    def __init__(self, studentName, subjectName, valueOfGrade):
        self.__studentName = studentName
        self.__subjectName = subjectName
        self.__valueOfGrade = valueOfGrade

    def __str__(self):
        return self.__studentName + " got a " + str(self.__valueOfGrade) + " in the " + self.__subjectName + " exam"


class StudentByDescendingOrderDTO(object):
    def __init__(self, studentID, studentName, aggregatedAverage):
        self.__studentID = studentID
        self.__studentName = studentName
        self.__aggregatedAverage = aggregatedAverage

    def __str__(self):
        return "The student with the ID " + str(self.__studentID) + " and the name " + self.__studentName +\
               " has the aggegrated average of " + str(self.__aggregatedAverage)

    def get_aggregated_average(self):
        return self.__aggregatedAverage


class SubjectByDescendingGradeDTO(object):
    def __init__(self, subjectID, subjectName, aggregatedAverage):
        self.__subjectID = subjectID
        self.__subjectName = subjectName
        self.__aggregatedAverage = aggregatedAverage

    def __str__(self):
        return "The subject with the ID " + str(self.__subjectID) + " and the name " + self.__subjectName + \
               " has the aggregated average of " + str(self.__aggregatedAverage)

    def get_aggregated_average(self):
        return self.__aggregatedAverage

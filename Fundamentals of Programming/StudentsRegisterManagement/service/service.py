from domain.entities import Student, Subject, Grade, GradeDTO, StudentByDescendingOrderDTO, SubjectByDescendingGradeDTO
from Iterable import Iterable


class ServiceStudents(object):
    def __init__(self, repositoryStudents, validateStudent):
        self.__repositoryStudents = repositoryStudents
        self.__validateStudent = validateStudent

    def add_student(self, studentID, studentName):
        student = Student(studentID, studentName)
        self.__validateStudent.validate_student(student)
        self.__repositoryStudents.add(student)

    def get_students(self):
        return self.__repositoryStudents.get_all_elements()

    def remove_student(self, studentIDToRemove):
        keyOfStudent = Student(studentIDToRemove, None)
        # keyOfStudent is a student where only the ID is known, and we are searching for the student which has that ID
        studentToBeRemoved = self.__repositoryStudents.search_element(keyOfStudent)
        self.__repositoryStudents.remove_element(studentToBeRemoved)

    def update_student(self, IDOfStudentToUpdate, newNameOfStudent):
        student = Student(IDOfStudentToUpdate, newNameOfStudent)
        self.__repositoryStudents.update_element(student)

    def search_student_by_ID_complete(self, searchID):
        students = self.__repositoryStudents.get_all_elements()
        for student in students:
            if student.get_studentID() == searchID:
                return student.get_studentName()

    def search_student_by_ID(self, searchID):

        students = self.__repositoryStudents.get_all_elements()

        def compare_ascending(firstStudent, secondStudent):
            if firstStudent in students and secondStudent in students:
                return firstStudent.get_studentID() < secondStudent.get_studentID()

        stringToBePrinted = []
        for student in students:
            currentID = str(student.get_studentID())
            currentID = currentID.casefold()
            searchID = searchID.casefold()
            if searchID in currentID:
                currentID = int(currentID)
                studentName = student.get_studentName()
                studentFound = Student(currentID, studentName)
                stringToBePrinted.append(studentFound)

        iterable = Iterable(stringToBePrinted)
        iterable.shell_sort(compare_ascending)

        return iterable._items

    def search_student_by_name(self, searchName):
        students = self.__repositoryStudents.get_all_elements()

        def compare_ascending(firstStudent, secondStudent):
            if firstStudent in students and secondStudent in students:
                return firstStudent.get_studentID() < secondStudent.get_studentID()

        stringToBePrinted = []
        for student in students:
            currentName = student.get_studentName()
            copyOfCurrentName = currentName.casefold()
            searchName = searchName.casefold()
            if searchName in copyOfCurrentName:
                studentID = student.get_studentID()
                studentFound = Student(studentID, currentName)
                stringToBePrinted.append(studentFound)
        iterable = Iterable(stringToBePrinted)
        iterable.shell_sort(compare_ascending)

        return iterable._items


class ServiceSubjects(object):
    def __init__(self, repositorySubjects, validateSubject):
        self.__repositorySubjects = repositorySubjects
        self.__validateSubject = validateSubject

    def add_subject(self, subjectID, subjectName):
        subject = Subject(subjectID, subjectName)
        self.__validateSubject.validate_subject(subject)
        self.__repositorySubjects.add(subject)

    def get_subjects(self):
        return self.__repositorySubjects.get_all_elements()

    def remove_subject(self, subjectIdToBeRemoved):
        keyOfSubject = Subject(subjectIdToBeRemoved, None)
        # keyOfSubject is a subject where only the ID is known, and we are searching for the subject which has that ID
        subjectToBeRemoved = self.__repositorySubjects.search_element(keyOfSubject)
        self.__repositorySubjects.remove_element(subjectToBeRemoved)

    def update_subject(self, IDOfSubjectToBeUpdated, newNameOfSubject):
        subject = Subject(IDOfSubjectToBeUpdated, newNameOfSubject)
        self.__repositorySubjects.update_element(subject)

    def search_subject_by_ID_complete(self, searchID):
        subjects = self.__repositorySubjects.get_all_elements()
        for subject in subjects:
            if searchID == subject.get_subjectID():
                return subject.get_subjectName()

    def search_subject_by_ID(self, searchID):
        subjects = self.__repositorySubjects.get_all_elements()

        def compare_ascending(firstSubject, secondSubject):
            if firstSubject in subjects and secondSubject in subjects:
                return firstSubject.get_subjectID() < secondSubject.get_subjectID()

        stringToBePrinted = []
        for subject in subjects:
            currentID = str(subject.get_subjectID())
            currentID = currentID.casefold()
            searchID = searchID.casefold()
            if searchID in currentID:
                currentID = int(currentID)
                subjectName = subject.get_subjectName()
                subjectFound = Subject(currentID, subjectName)
                stringToBePrinted.append(subjectFound)

        iterable = Iterable(stringToBePrinted)
        iterable.shell_sort(compare_ascending)

        return iterable._items

    def search_subject_by_name(self, searchName):
        subjects = self.__repositorySubjects.get_all_elements()

        def compare_ascending(firstSubject, secondSubject):
            if firstSubject in subjects and secondSubject in subjects:
                return firstSubject.get_subjectID() < secondSubject.get_subjectID()

        stringToBePrinted = []
        for subject in subjects:
            currentName = subject.get_subjectName()
            copyOfCurrentName = currentName.casefold()
            searchName = searchName.casefold()
            if searchName in copyOfCurrentName:
                subjectID = subject.get_subjectID()
                subjectFound = Subject(subjectID, currentName)
                stringToBePrinted.append(subjectFound)

        iterable = Iterable(stringToBePrinted)
        iterable.shell_sort(compare_ascending)

        return iterable._items


class ServiceGrades(object):
    def __init__(self, repositoryStudents, repositorySubjects, repositoryGrades, validateGrade):
        self.__repositoryStudents = repositoryStudents
        self.__repositorySubjects = repositorySubjects
        self.__repositoryGrades = repositoryGrades
        self.__validateGrade = validateGrade

    def add_grade(self, studentID, subjectID, valueOfGrade):
        grade = Grade(Student(studentID, None), Subject(subjectID, None), valueOfGrade)
        self.__repositoryStudents.search_element(Student(studentID, None))
        self.__repositorySubjects.search_element(Subject(subjectID, None))
        self.__validateGrade.validate_grade(grade)
        self.__repositoryGrades.add(grade)

    def get_grades(self):
        grades = self.__repositoryGrades.get_all_elements()
        stringToBePrinted = []
        for grade in grades:
            studentName = self.__repositoryStudents.search_element(grade.get_student()).get_studentName()
            subjectName = self.__repositorySubjects.search_element(grade.get_subject()).get_subjectName()
            gradeDTO = GradeDTO(studentName, subjectName, grade.get_valueOfGrade())
            stringToBePrinted.append(gradeDTO)
        return stringToBePrinted

    def remove_grades(self, studentID, subjectID):
        grades = self.__repositoryGrades.get_all_elements()
        for grade in grades:
            if grade.get_student().get_studentID() == studentID or grade.get_subject().get_subjectID() == subjectID:
                self.__repositoryGrades.remove_element(grade)

    def get_failing_students(self):
        grades = self.__repositoryGrades.get_all_elements()
        gradeSituation = {}
        for grade in grades:
            if grade.get_student().get_studentID() not in gradeSituation:
                gradeSituation[grade.get_student().get_studentID()] = []
            currentSubjectID = grade.get_subject().get_subjectID()
            gradeSituation[grade.get_student().get_studentID()].append([currentSubjectID, grade.get_valueOfGrade()])
        stringToBePrinted = []
        for studentSituation in gradeSituation.items():
            gradeSituationForStudent = studentSituation[1]
            situationByGradeForStudent = {}
            for grade in gradeSituationForStudent:
                if grade[0] not in situationByGradeForStudent:
                    situationByGradeForStudent[grade[0]] = []
                situationByGradeForStudent[grade[0]].append(grade[1])
            studentFailing = False
            # it will be False if the student is not failing and it will be True if the student is failing
            for gradeSituation in situationByGradeForStudent.items():
                average = sum(gradeSituation[1]) / len(gradeSituation[1])
                if average < 5:
                    studentFailing = True
            if studentFailing:
                studentID = studentSituation[0]
                studentName = self.__repositoryStudents.search_element(Student(studentID, None)).get_studentName()
                failingStudent = Student(studentID, studentName)
                stringToBePrinted.append(failingStudent)
        return stringToBePrinted

    def get_all_students_descending_by_grade(self):
        grades = self.__repositoryGrades.get_all_elements()
        gradeSituation = {}
        for grade in grades:
            if grade.get_student().get_studentID() not in gradeSituation:
                gradeSituation[grade.get_student().get_studentID()] = []
            gradeSituation[grade.get_student().get_studentID()].append(grade.get_valueOfGrade())
        stringToBePrinted = []
        for studentSituation in gradeSituation.items():
            studentID = studentSituation[0]
            studentName = self.__repositoryStudents.search_element(Student(studentID, None)).get_studentName()
            aggregatedAverage = sum(studentSituation[1]) / len(studentSituation[1])
            studentByDescendingGradedto = StudentByDescendingOrderDTO(studentID, studentName, aggregatedAverage)
            stringToBePrinted.append(studentByDescendingGradedto)
        stringToBePrinted.sort(key=lambda x: x.get_aggregated_average(), reverse=True)
        return stringToBePrinted

    def get_all_subjects_descending_by_grade(self):
        grades = self.__repositoryGrades.get_all_elements()
        gradeSituation = {}
        for grade in grades:
            if grade.get_subject().get_subjectID() not in gradeSituation:
                gradeSituation[grade.get_subject().get_subjectID()] = []
            gradeSituation[grade.get_subject().get_subjectID()].append(grade.get_valueOfGrade())
        stringToBePrinted = []
        for subjectSituation in gradeSituation.items():
            if len(subjectSituation[1]) > 0:
                subjectID = subjectSituation[0]
                subjectName = self.__repositorySubjects.search_element(Subject(subjectID, None)).get_subjectName()
                aggregatedAverage = sum(subjectSituation[1]) / len(subjectSituation[1])
                subjectByDescendingGradedto = SubjectByDescendingGradeDTO(subjectID, subjectName, aggregatedAverage)
                stringToBePrinted.append(subjectByDescendingGradedto)
        stringToBePrinted.sort(key=lambda x: x.get_aggregated_average(), reverse=True)
        return stringToBePrinted


class ServiceUndo(object):
    def __init__(self, repositoryStudents, repositorySubjects, repositoryGrades, repositoryUndo):
        self.__repositoryStudents = repositoryStudents
        self.__repositorySubjects = repositorySubjects
        self.__repositoryGrades = repositoryGrades
        self.__repositoryUndo = repositoryUndo

    def add_last_operation(self, operation):
        self.__repositoryUndo.add_element(operation)

    def remove_last_operation(self):
        self.__repositoryUndo.remove_last_element()

    def get_last_operation(self):
        return self.__repositoryUndo.get_last_element()

    def get_all_operations(self):
        return self.__repositoryUndo.get_all_elements()

    def operate_last_operation(self):
        lastOperation = self.__repositoryUndo.get_last_element()
        commandOfLastOperation = lastOperation[0]
        inputOfLastOperation = lastOperation[1]
        if commandOfLastOperation == 'add student':
            keyOfStudent = Student(inputOfLastOperation[0], None)
            nameOfStudent = self.__repositoryStudents.search_element(keyOfStudent)
            studentToRemove = Student(inputOfLastOperation[0], nameOfStudent)
            self.__repositoryStudents.remove_element(studentToRemove)
            grades = self.__repositoryGrades.get_all_elements()
            for grade in grades:
                if grade.get_student().get_studentID() == inputOfLastOperation[0]:
                    self.__repositoryGrades.remove_element(grade)
        elif commandOfLastOperation == 'remove student':
            self.__repositoryStudents.add(Student(inputOfLastOperation[0], inputOfLastOperation[1]))
            # I will now search for all the grades that this student has received
            undoOperations = self.__repositoryUndo.get_all_elements()
            subjects = self.__repositorySubjects.get_all_elements()
            listOfSubjectIDs = []
            for subject in subjects:
                listOfSubjectIDs.append(subject.get_subjectID())
            index = len(undoOperations) - 1
            while index >= 0:
                if undoOperations[index][0] == 'add grade' and undoOperations[index][1][0] == inputOfLastOperation[0] \
                        and undoOperations[index][1][1] in listOfSubjectIDs:
                    self.__repositoryGrades.add(Grade(Student(undoOperations[index][1][0], None),
                                                      Subject(undoOperations[index][1][1], None),
                                                      undoOperations[index][1][2]))
                if undoOperations[index][0] == 'add student' and undoOperations[index][1][0] == inputOfLastOperation[0]:
                    index = 0
                index -= 1
        elif commandOfLastOperation == 'update student':
            self.__repositoryStudents.update_element(Student(inputOfLastOperation[0], inputOfLastOperation[1]))
        elif commandOfLastOperation == 'add subject':
            keyOfSubject = Subject(inputOfLastOperation[0], None)
            nameOfSubject = self.__repositorySubjects.search_element(keyOfSubject)
            self.__repositorySubjects.remove_element(Subject(inputOfLastOperation[0], nameOfSubject))
            grades = self.__repositoryGrades.get_all_elements()
            for grade in grades:
                if grade.get_subject().get_subjectID() == inputOfLastOperation[0]:
                    self.__repositoryGrades.remove_element(grade)
        elif commandOfLastOperation == 'remove subject':
            self.__repositorySubjects.add(Subject(inputOfLastOperation[0], inputOfLastOperation[1]))
            # I will now search for all the grades that this student has received
            undoOperations = self.__repositoryUndo.get_all_elements()
            students = self.__repositoryStudents.get_all_elements()
            listOfStudentIDs = []
            for student in students:
                listOfStudentIDs.append(student.get_studentID())
            index = len(undoOperations) - 1
            while index >= 0:
                if undoOperations[index][0] == 'add grade' and undoOperations[index][1][1] == inputOfLastOperation[0] \
                        and undoOperations[index][1][0] in listOfStudentIDs:
                    self.__repositoryGrades.add(Grade(Student(undoOperations[index][1][0], None),
                                                      Subject(undoOperations[index][1][1], None),
                                                      undoOperations[index][1][2]))
                if undoOperations[index][0] == 'add subject' and undoOperations[index][1][0] == inputOfLastOperation[0]:
                    index = 0
                index -= 1
        elif commandOfLastOperation == 'update subject':
            self.__repositorySubjects.update_element(Subject(inputOfLastOperation[0], inputOfLastOperation[1]))
        elif commandOfLastOperation == 'add grade':
            studentID = inputOfLastOperation[0]
            subjectID = inputOfLastOperation[1]
            grades = self.__repositoryGrades.get_all_elements()
            for grade in grades:
                if grade.get_student().get_studentID() == studentID or grade.get_subject().get_subjectID() == subjectID:
                    self.__repositoryGrades.remove_element(grade)


class ServiceRedo(object):
    def __init__(self, repositoryStudents, repositorySubjects, repositoryGrades, repositoryUndo, repositoryRedo):
        self.__repositoryStudents = repositoryStudents
        self.__repositorySubjects = repositorySubjects
        self.__repositoryGrades = repositoryGrades
        self.__repositoryUndo = repositoryUndo
        self.__repositoryRedo = repositoryRedo

    def add_operation(self, operation):
        self.__repositoryRedo.add_element(operation)

    def remove_last_operation(self):
        self.__repositoryRedo.remove_last_element()

    def get_last_operation(self):
        return self.__repositoryRedo.get_last_element()

    def get_all_operations(self):
        return self.__repositoryRedo.get_all_elements()

    def operate_last_operation(self):
        operation = self.__repositoryRedo.get_last_element()
        command = operation[0]
        inputLastOperation = operation[1]
        if command == 'add student':
            self.__repositoryStudents.add(Student(inputLastOperation[0], inputLastOperation[1]))
        elif command == 'remove student':
            keyOfStudent = Student(inputLastOperation[0], None)
            nameOfStudent = self.__repositoryStudents.search_element(keyOfStudent)
            studentToRemove = Student(inputLastOperation[0], nameOfStudent)
            self.__repositoryStudents.remove_element(studentToRemove)
            grades = self.__repositoryGrades.get_all_elements()
            for grade in grades:
                if grade.get_student().get_studentID() == inputLastOperation[0]:
                    self.__repositoryGrades.remove_element(grade)
        elif command == 'update student':
            self.__repositoryStudents.update_element(Subject(inputLastOperation[0], inputLastOperation[2]))
        elif command == 'add subject':
            self.__repositorySubjects.add(Subject(inputLastOperation[0], inputLastOperation[1]))
        elif command == 'remove subject':
            keyOfSubject = Subject(inputLastOperation[0], None)
            nameOfSubject = self.__repositorySubjects.search_element(keyOfSubject)
            self.__repositorySubjects.remove_element(Subject(inputLastOperation[0], nameOfSubject))
            grades = self.__repositoryGrades.get_all_elements()
            for grade in grades:
                if grade.get_subject().get_subjectID() == inputLastOperation[0]:
                    self.__repositoryGrades.remove_element(grade)
        elif command == 'update subject':
            self.__repositorySubjects.update_element(Subject(inputLastOperation[0], inputLastOperation[2]))
        elif command == 'add grade':
            grades = self.__repositoryGrades.get_all_elements()
            for grade in grades:
                if grade.get_student().get_studentID() == inputLastOperation[0] \
                        or grade.get_subject().get_subjectID() == inputLastOperation[1]:
                    self.__repositoryGrades.remove_element(grade)

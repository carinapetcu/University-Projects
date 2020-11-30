from errors.exceptions import ValidationError, RepositoryError


class Console(object):

    def __ui_add_student(self):
        studentID = int(input("Please enter the student ID:"))
        studentName = input("Please enter the name of the student:")
        self.__serviceStudents.add_student(studentID, studentName)
        self.__serviceUndo.add_last_operation(['add student', [studentID, studentName]])

    def __ui_list_students(self):
        students = self.__serviceStudents.get_students()
        for student in students:
            print(student)

    def __ui_remove_student(self):
        studentIdToBeRemoved = int(input("Please enter the ID of the student to be removed:"))
        nameOfStudentToBeRemoved = self.__serviceStudents.search_student_by_ID_complete(studentIdToBeRemoved)
        self.__serviceGrades.remove_grades(studentIdToBeRemoved, None)
        self.__serviceStudents.remove_student(studentIdToBeRemoved)
        self.__serviceUndo.add_last_operation(['remove student', [studentIdToBeRemoved, nameOfStudentToBeRemoved]])

    def __ui_update_student(self):
        IDOfStudentToUpdate = int(input("Please enter the ID of the student to be updated:"))
        newNameOfStudent = input("Please enter the new name of the student:")
        oldName = self.__serviceStudents.search_student_by_ID_complete(IDOfStudentToUpdate)
        self.__serviceUndo.add_last_operation(['update student', [IDOfStudentToUpdate, oldName, newNameOfStudent]])
        self.__serviceStudents.update_student(IDOfStudentToUpdate, newNameOfStudent)

    def __ui_add_subject(self):
        subjectID = int(input("Please enter the ID of the new subject:"))
        subjectName = input("Please enter the name of the subject:")
        self.__serviceSubjects.add_subject(subjectID, subjectName)
        self.__serviceUndo.add_last_operation(['add subject', [subjectID, subjectName]])

    def __ui_list_subjects(self):
        subjects = self.__serviceSubjects.get_subjects()
        for subject in subjects:
            print(subject)

    def __ui_remove_subject(self):
        subjectIDToBeRemoved = int(input("Please enter the ID of the subject to be removed:"))
        nameOfSubjectToBeRemoved = self.__serviceSubjects.search_subject_by_ID_complete(subjectIDToBeRemoved)
        self.__serviceGrades.remove_grades(None, subjectIDToBeRemoved)
        self.__serviceSubjects.remove_subject(subjectIDToBeRemoved)
        self.__serviceUndo.add_last_operation(['remove subject', [subjectIDToBeRemoved, nameOfSubjectToBeRemoved]])

    def __ui_update_subject(self):
        IDOfSubjectToBeUpdated = int(input("Please enter the ID of the subject to be updated:"))
        newNameOfSubject = input("Please enter the new name of the subject:")
        oldName = self.__serviceSubjects.search_subject_by_ID_complete(IDOfSubjectToBeUpdated)
        self.__serviceUndo.add_last_operation(['update subject', [IDOfSubjectToBeUpdated, oldName, newNameOfSubject]])
        self.__serviceSubjects.update_subject(IDOfSubjectToBeUpdated, newNameOfSubject)

    def __ui_add_grade(self):
        studentID = int(input("Please enter the ID of the student: "))
        subjectID = int(input("Please enter the ID of the subject: "))
        valueOfGrade = int(input("Please enter the grade: "))
        self.__serviceGrades.add_grade(studentID, subjectID, valueOfGrade)
        self.__serviceUndo.add_last_operation(['add grade', [studentID, subjectID, valueOfGrade]])

    def __ui_list_grades(self):
        grades = self.__serviceGrades.get_grades()
        for grade in grades:
            print(grade)

    def __ui_search_student_by_ID(self):
        searchID = input("Please input the ID you are searching for: ")
        students = self.__serviceStudents.search_student_by_ID(searchID)
        for student in students:
            print(student)

    def __ui_search_student_by_name(self):
        searchName = input("Please input the name you are searching for: ")
        students = self.__serviceStudents.search_student_by_name(searchName)
        for student in students:
            print(student)

    def __ui_search_subject_by_ID(self):
        searchID = input("Please input the ID you are searching for: ")
        subjects = self.__serviceSubjects.search_subject_by_ID(searchID)
        for subject in subjects:
            print(subject)

    def __ui_search_subject_by_name(self):
        searchName = input("Please input the name you are searching for: ")
        subjects = self.__serviceSubjects.search_subject_by_name(searchName)
        for subject in subjects:
            print(subject)

    def __ui_print_failing_students(self):
        students = self.__serviceGrades.get_failing_students()
        for student in students:
            print(student)

    def __ui_print_all_students_descending_by_grade(self):
        students = self.__serviceGrades.get_all_students_descending_by_grade()
        for student in students:
            print(student)

    def __ui_print_all_subjects_with_grades_descending_order(self):
        subjects = self.__serviceGrades.get_all_subjects_descending_by_grade()
        for subject in subjects:
            print(subject)

    def __ui_undo(self):
        undoList = self.__serviceUndo.get_all_operations()
        if len(undoList) == 0:
            print("There are no operations to be undone.")
        else:
            lastOperation = self.__serviceUndo.get_last_operation()
            self.__serviceUndo.operate_last_operation()
            self.__serviceRedo.add_operation(lastOperation)
            self.__serviceUndo.remove_last_operation()

    def __ui_redo(self):
        redoList = self.__serviceRedo.get_all_operations()
        if len(redoList) == 0:
            print("There are no operations to be redone.")
        else:
            lastOperation = self.__serviceRedo.get_last_operation()
            self.__serviceRedo.operate_last_operation()
            self.__serviceUndo.add_last_operation(lastOperation)
            self.__serviceRedo.remove_last_operation()

    @staticmethod
    def __print_menu():
        print("The choices are:\n"
              "1. Add a new student\n"
              "2. Print the list of students\n"
              "3. Add a new subject\n"
              "4. Print the list of subjects\n"
              "5. Remove a student\n"
              "6. Remove a subject\n"
              "7. Update a student\n"
              "8. Update a subject\n"
              "9. Add a new grade\n"
              "10. Print the list of grades\n"
              "11. Search a student by ID\n"
              "12. Search a student by name\n"
              "13. Search a subject by ID\n"
              "14. Search a subject a name\n"
              "15. Show all the students failing at one or more disciplines\n"
              "16. Print all the students, sorted in descending order by their aggregated average\n"
              "17. Print all the subjects more than one grade, sorted in descending order by the aggregated average\n"
              "18. Undo the last operation\n"
              "19. Redo the last operation\n"
              "x. Exit the application\n")

    def __init__(self, serviceStudents, serviceSubjects, serviceGrades, serviceUndo, serviceRedo):
        self.__serviceStudents = serviceStudents
        self.__serviceSubjects = serviceSubjects
        self.__serviceGrades = serviceGrades
        self.__serviceUndo = serviceUndo
        self.__serviceRedo = serviceRedo
        self.__commands = {
            "1": self.__ui_add_student,
            "2": self.__ui_list_students,
            "3": self.__ui_add_subject,
            "4": self.__ui_list_subjects,
            "5": self.__ui_remove_student,
            "6": self.__ui_remove_subject,
            "7": self.__ui_update_student,
            "8": self.__ui_update_subject,
            "9": self.__ui_add_grade,
            "10": self.__ui_list_grades,
            "11": self.__ui_search_student_by_ID,
            "12": self.__ui_search_student_by_name,
            "13": self.__ui_search_subject_by_ID,
            "14": self.__ui_search_subject_by_name,
            "15": self.__ui_print_failing_students,
            "16": self.__ui_print_all_students_descending_by_grade,
            "17": self.__ui_print_all_subjects_with_grades_descending_order,
            "18": self.__ui_undo,
            "19": self.__ui_redo
        }

    def start_application(self):
        while True:
            self.__print_menu()
            command = input("Please enter the option:")
            if command == 'x':
                break
            else:
                command.strip()
                if command == "":
                    continue
                else:
                    if command in self.__commands:
                        try:
                            self.__commands[command]()
                        except ValueError as valueError:
                            print("UI error:\n" + str(valueError))
                        except ValidationError as validationError:
                            print("Business error:\n" + str(validationError))
                        except RepositoryError as repositoryError:
                            print("Repository error:\n" + str(repositoryError))
                    else:
                        print("Invalid command!")

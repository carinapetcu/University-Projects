from tkinter import *
from tkinter import messagebox


class ApplicationGUI:

    def __init__(self, serviceStudents, serviceSubjects, serviceGrades, serviceUndo, serviceRedo):
        self.__serviceStudents = serviceStudents
        self.__serviceSubjects = serviceSubjects
        self.__serviceGrades = serviceGrades
        self.__serviceUndo = serviceUndo
        self.__serviceRedo = serviceRedo

    def __gui_add_student(self):
        studentID = self.studentID.get()
        studentName = self.studentName.get()
        try:
            self.__serviceStudents.add_student(int(studentID), studentName)
            self.__serviceUndo.add_last_operation(['add student', [int(studentID), studentName]])
        except Exception as exception:
            messagebox.showinfo("Error", "Error saving student - " + str(exception))

    def __gui_list_students(self):
        students = self.__serviceStudents.get_students()
        windowListStudents = Toplevel()
        listOfStudents = Text(windowListStudents)
        for student in students:
            listOfStudents.insert(INSERT, student)
            listOfStudents.insert(INSERT, '\n')
        listOfStudents.pack()
        windowListStudents.mainloop()

    def __gui_remove_student(self):
        studentIDToRemove = self.studentID.get()
        nameOfStudentToBeRemoved = self.__serviceStudents.search_student_by_ID_complete(int(studentIDToRemove))
        try:
            self.__serviceGrades.remove_grades(int(studentIDToRemove), None)
            self.__serviceStudents.remove_student(int(studentIDToRemove))
            self.__serviceUndo.add_last_operation(['remove student', [int(studentIDToRemove),
                                                                      nameOfStudentToBeRemoved]])
        except Exception as exception:
            messagebox.showinfo("Error", "Error removing student - " + str(exception))

    def __gui_update_student(self):
        studentIDToUpdate = self.studentID.get()
        newNameOfStudent = self.studentName.get()
        try:
            oldName = self.__serviceStudents.search_student_by_ID_complete(int(studentIDToUpdate))
            self.__serviceUndo.add_last_operation(['update student', [int(studentIDToUpdate), oldName,
                                                                      newNameOfStudent]])
            self.__serviceStudents.update_student(int(studentIDToUpdate), newNameOfStudent)
        except Exception as exception:
            messagebox.showinfo("Error", "Error updating the new name of student - " + str(exception))

    def __gui_add_subject(self):
        subjectID = self.subjectID.get()
        subjectName = self.subjectName.get()
        try:
            self.__serviceSubjects.add_subject(int(subjectID), subjectName)
            self.__serviceUndo.add_last_operation(['add subject', [int(subjectID), subjectName]])
        except Exception as exception:
            messagebox.showinfo("Error", "Error adding the subject - " + str(exception))

    def __gui_list_subjects(self):
        subjects = self.__serviceSubjects.get_subjects()
        windowListSubjects = Toplevel()
        listOfSubjects = Text(windowListSubjects)
        for subject in subjects:
            listOfSubjects.insert(INSERT, subject)
            listOfSubjects.insert(INSERT, '\n')
        listOfSubjects.pack()
        windowListSubjects.mainloop()

    def __gui_remove_subject(self):
        subjectIDToRemove = self.subjectID.get()
        try:
            nameOfSubjectToBeRemoved = self.__serviceSubjects.search_subject_by_ID_complete(int(subjectIDToRemove))
            self.__serviceSubjects.remove_subject(int(subjectIDToRemove))
            self.__serviceUndo.add_last_operation(['remove subject', [int(subjectIDToRemove),
                                                                      nameOfSubjectToBeRemoved]])
            self.__serviceGrades.remove_grades(None, int(subjectIDToRemove))
        except Exception as exception:
            messagebox.showinfo("Error", "Error removing subject - " + str(exception))

    def __gui_update_subject(self):
        subjectIDToUpdate = self.subjectID.get()
        newNameOfSubject = self.subjectName.get()
        try:
            oldName = self.__serviceSubjects.search_subject_by_ID_complete(int(subjectIDToUpdate))
            self.__serviceUndo.add_last_operation(['update subject', [int(subjectIDToUpdate),
                                                                      oldName, newNameOfSubject]])
            self.__serviceSubjects.update_subject(int(subjectIDToUpdate), newNameOfSubject)
        except Exception as exception:
            messagebox.showinfo("Error", "Error updating the new name of subject - " + str(exception))

    def __gui_add_grade(self):
        studentID = self.studentID.get()
        subjectID = self.subjectID.get()
        valueOfGrade = self.valueOfGrade.get()
        try:
            self.__serviceGrades.add_grade(int(studentID), int(subjectID), int(valueOfGrade))
            self.__serviceUndo.add_last_operation(['add grade', [int(studentID), int(subjectID), int(valueOfGrade)]])
        except Exception as exception:
            messagebox.showinfo("Error", "Error adding the grade - " + str(exception))

    def __gui_list_grades(self):
        grades = self.__serviceGrades.get_grades()
        windowListGrades = Toplevel()
        listOfGrades = Text(windowListGrades)
        for grade in grades:
            listOfGrades.insert(INSERT, grade)
            listOfGrades.insert(INSERT, '\n')
        listOfGrades.pack()
        windowListGrades.mainloop()

    def __gui_show_failing_students(self):
        failingStudents = self.__serviceGrades.get_failing_students()
        windowListFailingStudents = Toplevel()
        listOfFailingStudents = Text(windowListFailingStudents)
        for failingStudent in failingStudents:
            listOfFailingStudents.insert(INSERT, failingStudent)
            listOfFailingStudents.insert(INSERT, '\n')
        listOfFailingStudents.pack()
        windowListFailingStudents.mainloop()

    def __gui_show_students_descending_order_by_grade(self):
        students = self.__serviceGrades.get_all_students_descending_by_grade()
        windowListStudents = Toplevel()
        listOfStudents = Text(windowListStudents)
        for student in students:
            listOfStudents.insert(INSERT, student)
            listOfStudents.insert(INSERT, '\n')
        listOfStudents.pack()
        windowListStudents.mainloop()

    def __gui_show_subjects_descending_order_by_grade(self):
        subjects = self.__serviceGrades.get_all_subjects_descending_by_grade()
        windowListSubjects = Toplevel()
        listOfSubjects = Text(windowListSubjects)
        for subject in subjects:
            listOfSubjects.insert(INSERT, subject)
            listOfSubjects.insert(INSERT, '\n')
        listOfSubjects.pack()
        windowListSubjects.mainloop()

    def __gui_search_student_by_ID(self):
        IDToSearch = self.IDToSearch.get()
        if IDToSearch != '':
            students = self.__serviceStudents.search_student_by_ID(IDToSearch)
        else:
            students = []
        windowListOfStudents = Toplevel()
        listOfStudents = Text(windowListOfStudents)
        if not students:
            listOfStudents.insert(INSERT, 'There is no student matching that ID.')
        for student in students:
            listOfStudents.insert(INSERT, student)
            listOfStudents.insert(INSERT, '\n')
        listOfStudents.pack()
        windowListOfStudents.mainloop()

    def __gui_search_student_by_name(self):
        nameToSearch = self.nameToSearch.get()
        if nameToSearch != '':
            students = self.__serviceStudents.search_student_by_name(nameToSearch)
        else:
            students = []
        windowListOfStudents = Toplevel()
        listOfStudents = Text(windowListOfStudents)
        if not students:
            listOfStudents.insert(INSERT, 'There is no student matching that name.')
        for student in students:
            listOfStudents.insert(INSERT, student)
            listOfStudents.insert(INSERT, '\n')
        listOfStudents.pack()
        windowListOfStudents.mainloop()

    def __gui_search_subject_by_ID(self):
        IDToSearch = self.IDToSearch.get()
        if IDToSearch != '':
            subjects = self.__serviceSubjects.search_subject_by_ID(IDToSearch)
        else:
            subjects = []
        windowListOfSubjects = Toplevel()
        listOfSubjects = Text(windowListOfSubjects)
        if not subjects:
            listOfSubjects.insert(INSERT, 'There is no subject matching that ID.')
        for subject in subjects:
            listOfSubjects.insert(INSERT, subject)
            listOfSubjects.insert(INSERT, '\n')
        listOfSubjects.pack()
        windowListOfSubjects.mainloop()

    def __gui_search_subject_by_name(self):
        nameToSearch = self.nameToSearch.get()
        if nameToSearch != '':
            subjects = self.__serviceSubjects.search_subject_by_name(nameToSearch)
        else:
            subjects = []
        windowListOfSubjects = Toplevel()
        listOfSubjects = Text(windowListOfSubjects)
        if not subjects:
            listOfSubjects.insert(INSERT, 'There is no subject matching that name.')
        for subject in subjects:
            listOfSubjects.insert(INSERT, subject)
            listOfSubjects.insert(INSERT, '\n')
        listOfSubjects.pack()
        windowListOfSubjects.mainloop()

    def __gui_undo(self):
        undoList = self.__serviceUndo.get_all_operations()
        if len(undoList):
            lastOperation = self.__serviceUndo.get_last_operation()
            self.__serviceUndo.operate_last_operation()
            self.__serviceRedo.add_operation(lastOperation)
            self.__serviceUndo.remove_last_operation()

    def __gui_redo(self):
        redoList = self.__serviceRedo.get_all_operations()
        if len(redoList):
            lastOperation = self.__serviceRedo.get_last_operation()
            self.__serviceRedo.operate_last_operation()
            self.__serviceUndo.add_last_operation(lastOperation)
            self.__serviceRedo.remove_last_operation()


    def __gui_manage_students(self):
        self.studentMenu = Tk()
        self.studentMenu.title("Manage the students")
        frameStudent = Frame(self.studentMenu)
        frameStudent.pack()
        self.frameStudent = frameStudent

        label = Label(frameStudent, text="ID:")
        label.pack(side=LEFT)

        self.studentID = Entry(frameStudent, {})
        self.studentID.pack(side=LEFT)

        label = Label(frameStudent, text="Name:")
        label.pack(side=LEFT)

        self.studentName = Entry(frameStudent, {})
        self.studentName.pack(side=LEFT)

        self.addStudent = Button(frameStudent, text="Add", command=self.__gui_add_student)
        self.addStudent.pack(side=LEFT)

        self.listStudents = Button(frameStudent, text="List", command=self.__gui_list_students)
        self.listStudents.pack(side=LEFT)

        self.removeStudent = Button(frameStudent, text="Remove", command=self.__gui_remove_student)
        self.removeStudent.pack(side=LEFT)

        self.updateStudent = Button(frameStudent, text="Update", command=self.__gui_update_student)
        self.updateStudent.pack(side=LEFT)

        self.undo = Button(frameStudent, text="Undo", command=self.__gui_undo)
        self.undo.pack(side=LEFT)

        self.redo = Button(frameStudent, text="Redo", command=self.__gui_redo)
        self.redo.pack(side=LEFT)

        self.studentMenu.mainloop()

    def __gui_manage_subjects(self):
        self.subjectMenu = Tk()
        self.subjectMenu.title("Manage the subjects")

        frameSubject = Frame(self.subjectMenu)
        frameSubject.pack()
        self.frameSubject = frameSubject

        label = Label(frameSubject, text="ID:")
        label.pack(side=LEFT)

        self.subjectID = Entry(frameSubject, {})
        self.subjectID.pack(side=LEFT)

        label = Label(frameSubject, text="Name:")
        label.pack(side=LEFT)

        self.subjectName = Entry(frameSubject, {})
        self.subjectName.pack(side=LEFT)

        self.addSubject = Button(frameSubject, text="Add", command=self.__gui_add_subject)
        self.addSubject.pack(side=LEFT)

        self.listSubjects = Button(frameSubject, text="List", command=self.__gui_list_subjects)
        self.listSubjects.pack(side=LEFT)

        self.removeSubject = Button(frameSubject, text="Remove", command=self.__gui_remove_subject)
        self.removeSubject.pack(side=LEFT)

        self.updateSubject = Button(frameSubject, text="Update", command=self.__gui_update_subject)
        self.updateSubject.pack(side=LEFT)

        self.undo = Button(frameSubject, text="Undo", command=self.__gui_undo)
        self.undo.pack(side=LEFT)

        self.redo = Button(frameSubject, text="Redo", command=self.__gui_redo)
        self.redo.pack(side=LEFT)

        self.subjectMenu.mainloop()

    def __gui_manage_grades(self):
        self.gradeMenu = Tk()
        self.gradeMenu.title("Manage the grades")

        frameGrade = Frame(self.gradeMenu)
        frameGrade.pack()
        self.frameGrade = frameGrade

        label = Label(frameGrade, text="Student ID:")
        label.pack(side=LEFT)

        self.studentID = Entry(frameGrade, {})
        self.studentID.pack(side=LEFT)

        label = Label(frameGrade, text="Subject ID:")
        label.pack(side=LEFT)

        self.subjectID = Entry(frameGrade, {})
        self.subjectID.pack(side=LEFT)

        label = Label(frameGrade, text="Value of grade:")
        label.pack(side=LEFT)
        self.valueOfGrade = Entry(frameGrade, {})
        self.valueOfGrade.pack(side=LEFT)

        self.addGrade = Button(frameGrade, text="Add", command=self.__gui_add_grade)
        self.addGrade.pack(side=LEFT)

        self.listGrades = Button(frameGrade, text="List", command=self.__gui_list_grades)
        self.listGrades.pack(side=LEFT)

        self.undo = Button(frameGrade, text="Undo", command=self.__gui_undo)
        self.undo.pack(side=LEFT)

        self.redo = Button(frameGrade, text="Redo", command=self.__gui_redo)
        self.redo.pack(side=LEFT)

        self.gradeMenu.mainloop()

    def __gui_statistics(self):
        self.statisticsMenu = Tk()
        self.statisticsMenu.title("Manage the statistics")

        frameStatistics = Frame(self.statisticsMenu)
        frameStatistics.pack()
        self.frameStatistics = frameStatistics

        self.showFailingStudents = Button(frameStatistics, text="Show failing students",
                                          command=self.__gui_show_failing_students)
        self.showFailingStudents.pack(side=LEFT)

        self.showStudentsDescendingOrderByGrade = Button(frameStatistics,
                                                         text="Show students by descending aggregated average",
                                                         command=self.__gui_show_students_descending_order_by_grade)
        self.showStudentsDescendingOrderByGrade.pack(side=LEFT)

        self.showSubjectsDescendingOrderByGrade = Button(frameStatistics,
                                                         text="Show subjects by descending aggregated average",
                                                         command = self.__gui_show_subjects_descending_order_by_grade)
        self.showSubjectsDescendingOrderByGrade.pack(side=LEFT)

        self.statisticsMenu.mainloop()

    def __gui_search(self):
        self.searchMenu = Tk()
        self.searchMenu.title("Search for a student/ subject")

        frameSearch = Frame(self.searchMenu)
        frameSearch.pack()
        self.frameSearch = frameSearch

        label = Label(frameSearch, text="ID:")
        label.pack(side=LEFT)

        self.IDToSearch = Entry(frameSearch, {})
        self.IDToSearch.pack(side=LEFT)

        label = Label(frameSearch, text="Name:")
        label.pack(side=LEFT)

        self.nameToSearch = Entry(frameSearch, {})
        self.nameToSearch.pack(side=LEFT)

        self.searchStudentByID = Button(frameSearch, text="Search for a student by ID",
                                        command=self.__gui_search_student_by_ID)
        self.searchStudentByID.pack(side=LEFT)

        self.searchStudentByName = Button(frameSearch, text="Search for a student by name",
                                          command=self.__gui_search_student_by_name)
        self.searchStudentByName.pack(side=LEFT)

        self.searchSubjectByID = Button(frameSearch, text="Search for a subject by ID",
                                        command=self.__gui_search_subject_by_ID)
        self.searchSubjectByID.pack(side=LEFT)

        self.searchSubjectByName = Button(frameSearch, text="Search for a subject by name",
                                          command=self.__gui_search_subject_by_name)
        self.searchSubjectByName.pack(side=LEFT)

        self.searchMenu.mainloop()

    def start_application(self):
        self.tk = Tk()
        self.tk.title("Students Register Management")

        frame = Frame(self.tk)
        frame.pack()
        self.frame = frame

        self.student = Button(frame, text="Enter the student menu.", command=self.__gui_manage_students)
        self.student.pack(side=LEFT)

        self.subject = Button(frame, text="Enter the subject menu.", command=self.__gui_manage_subjects)
        self.subject.pack(side=LEFT)

        self.grade = Button(frame, text="Enter the grade menu.", command=self.__gui_manage_grades)
        self.grade.pack(side=LEFT)

        self.search = Button(frame, text="Search for a certain student/ subject.", command=self.__gui_search)
        self.search.pack(side=LEFT)

        self.statistics = Button(frame, text="Enter the statistics menu.", command=self.__gui_statistics)
        self.statistics.pack(side=LEFT)
        self.tk.mainloop()
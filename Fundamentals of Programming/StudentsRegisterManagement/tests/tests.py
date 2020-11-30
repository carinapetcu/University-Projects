from business.service import ServiceStudents, ServiceSubjects
from domain.entities import Student, Subject
from infrastructure.repository import Repository
from validation.validators import ValidateSubject, ValidateStudent
import unittest


class Tests(unittest.TestCase):

    # def setUp(self):
    #     unittest.TestCase.setUp(self)
    #
    # def tearDown(self):
    #     unittest.TestCase.tearDown(self)

    def testGetStudentName_validInput_getsStudentName(self):
        studentID = 12
        studentName = 'Michael'
        student = Student(studentID, studentName)
        self.assertEqual(student.get_studentName(), 'Michael')

    def testGetStudentID_validInput_getsStudentID(self):
        studentID = 12
        studentName = 'Michael'
        student = Student(studentID, studentName)
        self.assertEqual(student.get_studentID(), 12)

    def testSetStudentName_validInput_setsStudentName(self):
        studentID = 12
        studentName = 'Michael'
        student = Student(studentID, studentName)
        self.assertEqual(student.get_studentName(), 'Michael')
        student.set_studentName('Lorelei')
        self.assertEqual(student.get_studentName(), 'Lorelei')
        self.assertNotEqual(student.get_studentName(), 'Michael')

    def testGetSubjectName_validInput_getsSubjectName(self):
        subjectID = 3
        subjectName = 'history'
        subject = Subject(subjectID, subjectName)
        self.assertEqual(subject.get_subjectName(), 'history')

    def testGetSubjectID_validInput(self):
        subjectID = 3
        subjectName = 'history'
        subject = Subject(subjectID, subjectName)
        self.assertEqual(subject.get_subjectID(), 3)

    def testSetSubjectName_validInput(self):
        subjectID = 3
        subjectName = 'history'
        subject = Subject(subjectID, subjectName)
        self.assertEqual(subject.get_subjectID(), 3)
        subject.set_subjectName('math')
        self.assertEqual(subject.get_subjectName(), 'math')

    def testServiceAddNewStudent_validStudent_addStudentToTheList(self):
        studentID = 3
        studentName = 'Lili'
        student = Student(studentID, studentName)
        validateStudent = ValidateStudent()
        repositoryStudent = Repository()
        serviceStudents = ServiceStudents(repositoryStudent, validateStudent)
        serviceStudents.add_student(studentID, studentName)
        students = serviceStudents.get_students()
        self.assertEqual(students, [student])

    def testServiceAddNewSubject_validSubject_addSubjectToTheList(self):
        subjectID = 5
        subjectName = 'logic'
        subject = Subject(subjectID, subjectName)
        validateSubject = ValidateSubject()
        repositorySubject = Repository()
        serviceSubjects = ServiceSubjects(repositorySubject, validateSubject)
        serviceSubjects.add_subject(subjectID, subjectName)
        subjects = serviceSubjects.get_subjects()
        self.assertEqual(subjects, [subject])

    def testServiceRemoveStudent_validStudent_removeStudentFromTheList(self):
        validateStudent = ValidateStudent()
        repositoryStudent = Repository()
        serviceStudents = ServiceStudents(repositoryStudent, validateStudent)
        student1 = Student(2, 'Lola')
        serviceStudents.add_student(2, 'Lola')
        serviceStudents.add_student(5, 'Berry')
        serviceStudents.remove_student(5)
        students = serviceStudents.get_students()
        self.assertEqual(students, [student1])

    def testServiceRemoveSubject_validSubject_removeSubjectFromTheList(self):
        validateSubject = ValidateSubject()
        repositorySubject = Repository()
        serviceSubjects = ServiceSubjects(repositorySubject, validateSubject)
        subject2 = Subject(6, 'algebra')
        serviceSubjects.add_subject(2, 'math')
        serviceSubjects.add_subject(6, 'algebra')
        serviceSubjects.remove_subject(2)
        subjects = serviceSubjects.get_subjects()
        self.assertEqual(subjects, [subject2])

    def testServiceUpdateStudent_validStudent_updateNewNameToCertainStudent(self):
        validateStudent = ValidateStudent()
        repositoryStudent = Repository()
        serviceStudents = ServiceStudents(repositoryStudent, validateStudent)
        studentID = 6
        studentName = 'Lola'
        newStudentName = 'Lololol'
        serviceStudents.add_student(studentID, studentName)
        serviceStudents.update_student(studentID, newStudentName)
        keyOfStudent = Student(studentID, None)
        self.assertEqual(repositoryStudent.search_element(keyOfStudent).get_studentName(), 'Lololol')

    def testServiceUpdateSubject_validSubject_updateNewNameToCertainSubject(self):
        validateSubject = ValidateSubject()
        repositorySubject = Repository()
        serviceSubjects = ServiceSubjects(repositorySubject, validateSubject)
        subjectID = 1
        subjectName = 'math'
        newSubjectName = 'algebra'
        serviceSubjects.add_subject(subjectID, subjectName)
        serviceSubjects.update_subject(subjectID, newSubjectName)
        keyOfSubject = Subject(subjectID, None)
        self.assertEqual(repositorySubject.search_element(keyOfSubject).get_subjectName(), 'algebra')

    def testRepositoryAddStudent_validStudent_addNewStudentToTheList(self):
        repositoryStudent = Repository()
        student = Student(1, 'Meli')
        repositoryStudent.add(student)
        self.assertEqual(repositoryStudent.get_all_elements(), [student])

    def testRepositoryAddSubject_validSubject_addNewSubjectToTheList(self):
        repositorySubject = Repository()
        subject = Subject(1, 'history')
        repositorySubject.add(subject)
        self.assertEqual(repositorySubject.get_all_elements(), [subject])

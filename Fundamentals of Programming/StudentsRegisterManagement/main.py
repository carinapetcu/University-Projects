from presentation.console import Console
from validation.validators import ValidateStudent, ValidateSubject, ValidateGrade
from infrastructure.repository import RepositoryUndoAndRedo, FileRepository, FileRepositoryBinary, Repository
from business.service import ServiceStudents, ServiceSubjects, ServiceGrades, ServiceUndo, ServiceRedo
from gui.gui import ApplicationGUI
from domain.entities import Student, Subject, Grade


validateStudent = ValidateStudent()
validateSubject = ValidateSubject()
validateGrade = ValidateGrade()

repositoryUndo = RepositoryUndoAndRedo()
repositoryRedo = RepositoryUndoAndRedo()


with open("settings_file.txt", "r") as file:
    lines = file.readlines()
    for line in lines:
        line = line.strip()
        elementsOfLine = line.split('=')
        if elementsOfLine[0] == 'repository':
            typeOfFile = elementsOfLine[1]
        elif elementsOfLine[0] == 'students':
            studentsFile = elementsOfLine[1][1:len(elementsOfLine[1])-1]
        elif elementsOfLine[0] == 'subjects':
            subjectsFile = elementsOfLine[1][1:len(elementsOfLine[1])-1]
        elif elementsOfLine[0] == 'grades':
            gradesFile = elementsOfLine[1][1:len(elementsOfLine[1])-1]

with open("settings_binary.txt", "r") as file:
    lines = file.readlines()
    for line in lines:
        line = line.strip()
        elementsOfLine = line.split('=')
        if elementsOfLine[0] == 'repository':
            typeOfFileBinary = elementsOfLine[1]
        elif elementsOfLine[0] == 'students':
            studentsFileBinary = elementsOfLine[1][1:len(elementsOfLine[1])-1]
        elif elementsOfLine[0] == 'subjects':
            subjectsFileBinary = elementsOfLine[1][1:len(elementsOfLine[1])-1]
        elif elementsOfLine[0] == 'grades':
            gradesFileBinary = elementsOfLine[1][1:len(elementsOfLine[1])-1]


while True:
    print("Choose one between text/ binary/ inmemory.")
    choice = input("Your choice: ")
    if choice == typeOfFile:
        repositoryStudents = FileRepository(studentsFile, Student.read_student, Student.write_student)
        repositorySubjects = FileRepository(subjectsFile, Subject.read_subject, Subject.write_subject)
        repositoryGrades = FileRepository(gradesFile, Grade.read_grade, Grade.write_grade)
        break
    elif choice == typeOfFileBinary:
        repositoryStudents = FileRepositoryBinary(studentsFileBinary)
        repositorySubjects = FileRepositoryBinary(subjectsFileBinary)
        repositoryGrades = FileRepositoryBinary(gradesFileBinary)
        break
    elif choice == 'inmemory':
        repositoryStudents = Repository()
        repositorySubjects = Repository()
        repositoryGrades = Repository()
        break
    else:
        print("Choose another option.")


repositoryUndo.add_element(['add student', [1, "Michael"]])
repositoryUndo.add_element(['add student', [23, "Lorelei"]])
repositoryUndo.add_element(['add student', [15, "Gicu"]])
repositoryUndo.add_element(['add student', [7, "Mila"]])
repositoryUndo.add_element(['add student', [2, "Viaa"]])
repositoryUndo.add_element(['add student', [19, "Dali"]])
repositoryUndo.add_element(['add student', [11, "Flowy"]])
repositoryUndo.add_element(['add student', [20, "Bratva"]])
repositoryUndo.add_element(['add student', [4, "Geli"]])
repositoryUndo.add_element(['add student', [30, "Fili"]])


repositoryUndo.add_element(['add subject', [1, "history"]])
repositoryUndo.add_element(['add subject', [2, "math"]])
repositoryUndo.add_element(['add subject', [3, "romanian"]])
repositoryUndo.add_element(['add subject', [4, "fundamentals of programming"]])
repositoryUndo.add_element(['add subject', [5, "asc"]])
repositoryUndo.add_element(['add subject', [6, "logic"]])
repositoryUndo.add_element(['add subject', [7, "geogra"]])
repositoryUndo.add_element(['add subject', [8, "philosophy"]])
repositoryUndo.add_element(['add subject', [9, "english"]])
repositoryUndo.add_element(['add subject', [10, "physics"]])


repositoryUndo.add_element(['add grade', [1, 2, 10]])
repositoryUndo.add_element(['add grade', [23, 2, 5]])
repositoryUndo.add_element(['add grade', [19, 3, 7.25]])
repositoryUndo.add_element(['add grade', [23, 2, 4.77]])
repositoryUndo.add_element(['add grade', [19, 7, 9]])
repositoryUndo.add_element(['add grade', [20, 5, 5]])
repositoryUndo.add_element(['add grade', [4, 1, 9.5]])
repositoryUndo.add_element(['add grade', [30, 9, 3.6]])
repositoryUndo.add_element(['add grade', [7, 4, 9.9]])
repositoryUndo.add_element(['add grade', [11, 6, 6]])
repositoryUndo.add_element(['add grade', [23, 6, 10]])

serviceStudents = ServiceStudents(repositoryStudents, validateStudent)
serviceSubjects = ServiceSubjects(repositorySubjects, validateSubject)
serviceGrades = ServiceGrades(repositoryStudents, repositorySubjects, repositoryGrades, validateGrade)
serviceUndo = ServiceUndo(repositoryStudents, repositorySubjects, repositoryGrades, repositoryUndo)
serviceRedo = ServiceRedo(repositoryStudents, repositorySubjects, repositoryGrades, repositoryUndo, repositoryRedo)

if choice == typeOfFile:
    ui = Console(serviceStudents, serviceSubjects, serviceGrades, serviceUndo, serviceRedo)
    ui.start_application()
else:
    gui = ApplicationGUI(serviceStudents, serviceSubjects, serviceGrades, serviceUndo, serviceRedo)
    gui.start_application()

from Console.UI import ApplicationUI
from Service.Service import ServiceGame
from Repository.Repositories import Repository, RepositoryFile
from Validators.Validators import ValidateQuestion
from Entities.Question import Question

repository_game = RepositoryFile(Question.read_mode, Question.write_mode)
# repository_quiz = RepositoryFile(None, )

validate_question = ValidateQuestion()

service_game = ServiceGame(repository_game, validate_question)
# service_quiz = ServiceQuiz

ui = ApplicationUI(service_game)

ui.start_application()

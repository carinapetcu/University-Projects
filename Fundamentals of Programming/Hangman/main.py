from Console.Console import GameUI
from Service.Service import ServiceGame
from Repository.Repository import RepositoryFiles
from Validators.Validate import ValidateSentence

repositoryGame = RepositoryFiles("sentences.txt")
validator = ValidateSentence()

serviceGame = ServiceGame(repositoryGame, validator)

ui = GameUI(serviceGame)

ui.start_application()
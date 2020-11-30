from Repository.Repository import Repository
from Controllers.ComputerController import ComputerController
from Controllers.PlayerController import PlayerController
from Controllers.GameController import GameController
from Console.UI import UI


gameRepository = Repository()

playerController = PlayerController(gameRepository)
computerController = ComputerController(gameRepository)
gameController = GameController(playerController, computerController, gameRepository)

ui = UI(gameController)
ui.start_application()

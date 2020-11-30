from Board.Board import Board
from Console.UI import Application
from Service.ServiceApplication import Service
from Repository.Repository import RepositoryFiles
from Validator.Validate import Validate

board = Board(8, 8)
validator = Validate()
repository = RepositoryFiles("patterns.txt", Board.read_mode, Board.write_mode)
service = Service(repository, board, validator)

application = Application(service)

application.start()
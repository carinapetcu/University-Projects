import unittest


class GameController:
    def __init__(self, playerController, computerController, gameRepository):
        self.__playerController = playerController
        self.__computerController = computerController
        self.__gameRepository = gameRepository
        self.__lastMovePlayerRow = -1
        self.__lastMovePlayerColumn = -1
        self.__lastComputerMoveRow = -1
        self.__lastComputerMoveColumn = -1
        self.__lastPlayer = 0

    def start_new_game(self):
        self.__gameRepository.initialize_new_game()

    def get_grid(self):
        return self.__gameRepository.get_game_grid()

    def check_if_grid_full(self):
        lastRow = self.__gameRepository.get_row(0)
        for index in range(len(lastRow)):
            if lastRow[index] == 0:
                return False
        return True

    def place_player_piece(self, column):
        self.__lastMovePlayerRow, self.__lastMovePlayerColumn = self.__playerController.place_piece(column)
        self.__lastPlayer = 1

    def place_computer_piece(self):
        # self.__lastMovePlayerRow, self.__lastMovePlayerColumn = \
        #     self.__computerController.place_piece(self.__lastMovePlayerRow, self.__lastMovePlayerColumn)
        row, column, typeOfPiece = \
            self.__computerController.place_piece(self.__lastComputerMoveRow, self.__lastComputerMoveColumn)
        if typeOfPiece == 1:
            row, column, typeOfPiece = \
                self.__computerController.place_piece(self.__lastMovePlayerRow, self.__lastMovePlayerColumn)
        self.__gameRepository.add_piece(row, column, 2)
        self.__lastMovePlayerRow, self.__lastMovePlayerColumn = row, column
        self.__lastPlayer = 2
        self.__lastComputerMoveRow, self.__lastComputerMoveColumn = row, column

    def search_identical_elements_main_diagonal(self, rowMainDiagonal, columnMainDiagonal):
        numberOf0 = 0
        numberOf1 = 0
        numberOf2 = 0
        board = self.__gameRepository.get_game_grid()
        while rowMainDiagonal >= 0 and columnMainDiagonal <= 6:
            if rowMainDiagonal - 3 >= 0 and columnMainDiagonal + 3 <= 6:
                for index in range(4):
                    if board[rowMainDiagonal - index][columnMainDiagonal + index] == 0:
                        numberOf0 += 1
                    elif board[rowMainDiagonal - index][columnMainDiagonal + index] == 1:
                        numberOf1 += 1
                    elif board[rowMainDiagonal - index][columnMainDiagonal + index] == 2:
                        numberOf2 += 1
                if numberOf1 == 4:
                    return 1
                if numberOf2 == 4:
                    return 2
                numberOf0 = 0
                numberOf1 = 0
                numberOf2 = 0
            if numberOf1 == 4:
                return 1
            if numberOf2 == 4:
                return 2
            rowMainDiagonal -= 1
            columnMainDiagonal += 1
        return 0

    def get_game_winner(self):
        row = self.__lastMovePlayerRow
        column = self.__lastMovePlayerColumn

        # firstly we check the row
        line = self.__gameRepository.get_row(row)
        numberOfConsecutiveElements = 0
        index = len(line) - 1
        while index >= 0 and line[index] != self.__lastPlayer:
            index -= 1
        while index >= 0 and self.__lastPlayer == line[index]:
            numberOfConsecutiveElements += 1
            index -= 1
            if numberOfConsecutiveElements == 4:
                return self.__lastPlayer
        if numberOfConsecutiveElements == 4:
            return self.__lastPlayer

        # secondly we check the column
        line = self.__gameRepository.get_column(column)
        numberOfConsecutiveElements = 0
        index = len(line) - 1
        while index >= 0 and line[index] != self.__lastPlayer:
            index -= 1
        while index >= 0 and self.__lastPlayer == line[index]:
            numberOfConsecutiveElements += 1
            index -= 1
            if numberOfConsecutiveElements == 4:
                return self.__lastPlayer
        if numberOfConsecutiveElements == 4:
            return self.__lastPlayer

        rowMainDiagonal = row
        columnMainDiagonal = column
        while rowMainDiagonal < 5 and columnMainDiagonal > 0:
            rowMainDiagonal += 1
            columnMainDiagonal -= 1
        if abs(5 - rowMainDiagonal) + abs(6 - columnMainDiagonal) > 2 and \
                abs(0 - rowMainDiagonal) + abs(0 - columnMainDiagonal) > 2:
            winner = self.search_identical_elements_main_diagonal(rowMainDiagonal, columnMainDiagonal)
            if winner != 0:
                return winner

        return 0


class TestGameController(unittest.TestCase):
    def setUp(self):
        from Repository.Repository import Repository
        from Controllers.ComputerController import ComputerController
        from Controllers.PlayerController import PlayerController
        self.repository = Repository()
        computerController = ComputerController(self.repository)
        playerController = PlayerController(self.repository)
        self.computerController = GameController(playerController, computerController, self.repository)

    def testStartNewGame(self):
        matrix = [[0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0]]
        self.repository.add_piece(0, 0, 1)
        self.computerController.start_new_game()
        self.assertEqual(self.repository.get_game_grid(), matrix)

    def testGetGrid(self):
        matrix = [[1, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0]]
        self.repository.add_piece(0, 0, 1)
        self.assertEqual(self.computerController.get_grid(), matrix)

    def testCheckIfGridFull(self):
        self.repository.add_piece(0, 0, 1)
        self.assertEqual(self.computerController.check_if_grid_full(), False)

    def testGetGameWinner(self):
        self.assertEqual(self.computerController.get_game_winner(), 0)


from Utilities.generateMatrix import GenerateMatrix
import unittest


class Repository:
    def __init__(self):
        self.__gameGrid = GenerateMatrix.generate_matrix(6, 7, 0)

    def initialize_new_game(self):
        self.__gameGrid = GenerateMatrix.generate_matrix(6, 7, 0)

    def get_game_grid(self):
        return self.__gameGrid[:]

    def add_piece(self, row, column, value):
        if row == -1 or column == -1:
            raise ValueError("The column is full")
        self.__gameGrid[row][column] = value

    def check_piece_value(self, row, column):
        return self.__gameGrid[row][column]

    def get_row(self, row):
        return self.__gameGrid[row][:]

    def get_column(self, column):
        columnValues = []
        for index in range(6):
            columnValues.append(self.__gameGrid[index][column])
        return columnValues


class TestRepository(unittest.TestCase):
    def setUp(self):
        self.repository = Repository()

    def testInitializeNewGame(self):
        matrix = [[0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0]]
        self.repository.initialize_new_game()
        self.assertEqual(self.repository.get_game_grid(), matrix)

    def testGetGameGrid(self):
        matrix = [[0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0]]
        self.assertEqual(self.repository.get_game_grid(), matrix)

    def testAddPiece(self):
        matrix = [[1, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0]]
        self.repository.add_piece(0, 0, 1)
        self.assertEqual(self.repository.get_game_grid(), matrix)

    def testCheckPieceValue(self):
        self.repository.add_piece(0, 0, 1)
        self.assertEqual(self.repository.check_piece_value(0, 0), 1)

    def testGetRow(self):
        self.repository.add_piece(0, 0, 1)
        self.assertEqual(self.repository.get_row(0), [1, 0, 0, 0, 0, 0, 0])

    def testGetColumn(self):
        self.repository.add_piece(0, 0, 1)
        self.assertEqual(self.repository.get_column(0), [1, 0, 0, 0, 0, 0])


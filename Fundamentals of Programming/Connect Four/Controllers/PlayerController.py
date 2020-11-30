import unittest


class PlayerController:
    def __init__(self, gameRepository):
        self.__gameRepository = gameRepository

    def place_piece(self, column):
        columnValues = self.__gameRepository.get_column(column)
        index = len(columnValues) - 1
        while index >= 0 and columnValues[index] != 0:
            index -= 1
        if index == -1:
            raise ValueError("There is no space left on the column.")
        else:
            self.__gameRepository.add_piece(index, column, 1)
            return index, column


class TestPlayerController(unittest.TestCase):
    def setUp(self):
        from Repository.Repository import Repository
        self.repository = Repository()
        self.computerController = PlayerController(self.repository)

    def testPlacePiece(self):
        row, column = self.computerController.place_piece(1)
        self.assertEqual(row, 5)
        self.assertEqual(column, 1)

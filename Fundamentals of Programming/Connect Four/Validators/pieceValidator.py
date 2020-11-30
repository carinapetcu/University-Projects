import unittest


class PieceValidator:
    @staticmethod
    def check_if_column_full(column):
        index = len(column) - 1
        while index >= 0 and column[index] != 0:
            index -= 1
        return index


class TestPieceValidator(unittest.TestCase):
    def setUp(self):
        self.pieceValidator = PieceValidator()

    def testCheckIfColumnFull(self):
        index = self.pieceValidator.check_if_column_full([1, 1, 1, 1])
        self.assertEqual(index, -1)

import random
from Validators.pieceValidator import PieceValidator
import unittest


class ComputerController:
    def __init__(self, gameRepository):
        self.__gameRepository = gameRepository

    def place_piece_random(self):
        while True:
            columns = [0, 1, 2, 3, 4, 5]
            randomColumn = random.choice(columns)
            column = self.__gameRepository.get_column(randomColumn)
            positionLastZero = PieceValidator.check_if_column_full(column)
            while positionLastZero == -1:
                randomColumn = random.choice(columns)
                column = self.__gameRepository.get_column(randomColumn)
                positionLastZero = PieceValidator.check_if_column_full(column)
            return positionLastZero, randomColumn

    @staticmethod
    def search_identical_elements(line):
        numberOf0 = 0
        numberOf1 = 0
        numberOf2 = 0
        positionOf0 = -1
        for index1 in range(len(line) - 3):
            for index2 in range(4):
                if line[index1 + index2] == 0:
                    numberOf0 += 1
                    positionOf0 = index1 + index2
                elif line[index1 + index2] == 1:
                    numberOf1 += 1
                elif line[index1 + index2] == 2:
                    numberOf2 += 1
            if numberOf1 == 3 and numberOf0 == 1:
                return positionOf0, 1
            if numberOf2 == 3 and numberOf0 == 1:
                return positionOf0, 2
            numberOf0 = 0
            numberOf1 = 0
            numberOf2 = 0
            positionOf0 = -1
        if numberOf1 == 3 and numberOf0 == 1:
            return positionOf0, 1
        if numberOf2 == 3 and numberOf0 == 1:
            return positionOf0, 2
        return -1, -1
    # works fine don't change

    def search_identical_elements_main_diagonal(self, rowMainDiagonal, columnMainDiagonal):
        numberOf0 = 0
        numberOf1 = 0
        numberOf2 = 0
        rowOf0 = -1
        columnOf0 = -1
        board = self.__gameRepository.get_game_grid()
        while rowMainDiagonal >= 0 and columnMainDiagonal <= 6:
            if rowMainDiagonal - 3 >= 0 and columnMainDiagonal + 3 <= 6:
                for index in range(4):
                    if board[rowMainDiagonal - index][columnMainDiagonal + index] == 0:
                        numberOf0 += 1
                        rowOf0 = rowMainDiagonal - index
                        columnOf0 = columnMainDiagonal + index
                    elif board[rowMainDiagonal - index][columnMainDiagonal + index] == 1:
                        numberOf1 += 1
                    elif board[rowMainDiagonal - index][columnMainDiagonal + index] == 2:
                        numberOf2 += 1
                if numberOf1 == 3 and numberOf0 == 1:
                    return rowOf0, columnOf0, 1
                if numberOf2 == 3 and numberOf0 == 1:
                    return rowOf0, columnOf0, 2
                numberOf0 = 0
                numberOf1 = 0
                numberOf2 = 0
                rowOf0 = -1
                columnOf0 = -1
            if numberOf1 == 3 and numberOf0 == 1:
                return rowOf0, columnOf0, 1
            if numberOf2 == 3 and numberOf0 == 1:
                return rowOf0, columnOf0, 2
            rowMainDiagonal -= 1
            columnMainDiagonal += 1
        return -1, -1, -1

    def search_identical_elements_secondary_diagonal(self, rowSecondaryDiagonal, columnSecondaryDiagonal):
        numberOf0 = 0
        numberOf1 = 0
        numberOf2 = 0
        rowOf0 = -1
        columnOf0 = -1
        board = self.__gameRepository.get_game_grid()
        while rowSecondaryDiagonal >= 0 and columnSecondaryDiagonal >= 0:
            if rowSecondaryDiagonal - 3 >= 0 and columnSecondaryDiagonal - 3 >= 0:
                for index in range(4):
                    if board[rowSecondaryDiagonal - index][columnSecondaryDiagonal - index] == 0:
                        numberOf0 += 1
                        rowOf0 = rowSecondaryDiagonal - index
                        columnOf0 = columnSecondaryDiagonal - index
                    elif board[rowSecondaryDiagonal - index][columnSecondaryDiagonal - index] == 1:
                        numberOf1 += 1
                    elif board[rowSecondaryDiagonal - index][columnSecondaryDiagonal - index] == 2:
                        numberOf2 += 1
                if numberOf1 == 3 and numberOf0 == 1:
                    return rowOf0, columnOf0, 1
                if numberOf2 == 3 and numberOf0 == 1:
                    return rowOf0, columnOf0, 2
                numberOf0 = 0
                numberOf1 = 0
                numberOf2 = 0
                rowOf0 = -1
                columnOf0 = -1
            if numberOf1 == 3 and numberOf0 == 1:
                return rowOf0, columnOf0, 1
            if numberOf2 == 3 and numberOf0 == 1:
                return rowOf0, columnOf0, 2
            rowSecondaryDiagonal -= 1
            columnSecondaryDiagonal -= 1
        return -1, -1, -1

    def block_human_or_win(self, row, column):
        columnOfNewPiece = -1
        rowOfNewPiece = -1
        currentRow = self.__gameRepository.get_row(row)
        columnOfZero, typeOfPiece = self.search_identical_elements(currentRow)
        if columnOfZero != -1:
            if row == 5:
                columnOfNewPiece = columnOfZero
                return row, columnOfNewPiece
            elif self.__gameRepository.check_piece_value(row + 1, columnOfZero) != 0:
                columnOfNewPiece = columnOfZero
                return row, columnOfNewPiece

        currentColumn = self.__gameRepository.get_column(column)
        rowOfZero, typeOfPiece = self.search_identical_elements(currentColumn)
        if rowOfZero != -1:
            rowOfNewPiece = rowOfZero
            return rowOfNewPiece, column

        # we need the 2 diagonals that pass through the coordinates row and column
        rowMainDiagonal = row
        columnMainDiagonal = column
        while rowMainDiagonal < 5 and columnMainDiagonal > 0:
            rowMainDiagonal += 1
            columnMainDiagonal -= 1
        if abs(5 - rowMainDiagonal) + abs(6 - columnMainDiagonal) > 2 and \
                abs(0 - rowMainDiagonal) + abs(0 - columnMainDiagonal) > 2:
            rowOfNewPiece, columnOfNewPiece, typeOfPiece = \
                self.search_identical_elements_main_diagonal(rowMainDiagonal, columnMainDiagonal)
            if columnOfZero != -1:
                if rowOfNewPiece == 5:
                    columnOfNewPiece = columnOfZero
                    return rowOfNewPiece, columnOfNewPiece
                elif self.__gameRepository.check_piece_value(rowOfNewPiece + 1, columnOfZero) != 0:
                    columnOfNewPiece = columnOfZero
                    return rowOfNewPiece, columnOfNewPiece

        rowSecondaryDiagonal = row
        columnSecondaryDiagonal = column
        while rowSecondaryDiagonal < 5 and columnSecondaryDiagonal < 6:
            rowSecondaryDiagonal += 1
            columnSecondaryDiagonal += 1
        if abs(5 - rowSecondaryDiagonal) + abs(0 - columnSecondaryDiagonal) > 2 and \
                abs(0 - rowSecondaryDiagonal) + abs(6 - columnSecondaryDiagonal) > 2:
            rowOfNewPiece, columnOfNewPiece, typeOfPiece = \
                self.search_identical_elements_secondary_diagonal(rowSecondaryDiagonal, columnSecondaryDiagonal)
            if columnOfZero != -1:
                if rowOfNewPiece == 5:
                    columnOfNewPiece = columnOfZero
                    return rowOfNewPiece, columnOfNewPiece
                elif self.__gameRepository.check_piece_value(rowOfNewPiece + 1, columnOfZero) != 0:
                    columnOfNewPiece = columnOfZero
                    return rowOfNewPiece, columnOfNewPiece

        return rowOfNewPiece, columnOfNewPiece

    def place_piece(self, lastMoveRow, lastMoveColumn):
        if lastMoveColumn != -1 and lastMoveRow != -1:
            rowOfNewPiece, columnOfNewPiece = self.block_human_or_win(lastMoveRow, lastMoveColumn)
        else:
            rowOfNewPiece = -1
            columnOfNewPiece = -1
        if rowOfNewPiece == -1 or columnOfNewPiece == -1:
            type = 1
            row, column = self.place_piece_random()
            return row, column, type
        else:
            type = 2
            return rowOfNewPiece, columnOfNewPiece, type


class TestsComputerController(unittest.TestCase):
    def setUp(self):
        from Repository.Repository import Repository
        from Utilities.generateMatrix import GenerateMatrix
        self.repository = Repository()
        self.computerController = ComputerController(self.repository)

    def testSearchConsecutiveElements(self):
        place, type = self.computerController.search_identical_elements([0, 0, 2, 2, 2, 0, 0])
        self.assertEqual(place, 1)
        self.assertEqual(type, 2)

    def testBlockHumanOrWin(self):
        row, column = self.computerController.block_human_or_win(0, 0)
        self.assertEqual(row, -1)
        self.assertEqual(column, -1)

    def testPlacePiece(self):
        row, column, player = self.computerController.place_piece(0, 0)
        self.assertEqual(row, 5)
        self.assertEqual(player, 1)

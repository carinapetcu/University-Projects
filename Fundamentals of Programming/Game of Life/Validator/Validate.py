import math

from Exceptions.Exceptions import ValidatorError


class Validate:
    def __init__(self):
        pass

    @staticmethod
    def validateBoards(board, boardWithPattern, row, column):
        dimension = int(len(boardWithPattern))
        for index1 in range(dimension):
            for index2 in range(dimension):
                if board[row+index1][column+index2] == boardWithPattern[index1][index2] == 1:
                    raise ValidatorError("The live cells overlap!")
                if index1 + row > 8 or index2 + column > 8 and boardWithPattern[index1][index2] == 1:
                    raise ValidatorError("The live cell is outside the board!")

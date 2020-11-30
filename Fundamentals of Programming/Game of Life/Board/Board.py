from math import sqrt


class Board:
    def __init__(self, rows, columns):
        self.__rows = rows
        self.__columns = columns
        self.__board = [[0 for j in range(self.__rows)] for i in range(self.__columns)]

    def get_board(self):
        return self.__board

    def update(self, row, column, value):
        self.__board[row][column] = value

    @staticmethod
    def read_mode(line):
        dimension = int(sqrt(len(line)))
        board = Board(dimension, dimension)
        for index1 in range(dimension):
            for index2 in range(dimension):
                element = line[index1 * dimension + index2]
                element = element.split(";")
                board.update(int(element[0]), int(element[1]), int(element[2]))
        return board.get_board()

    @staticmethod
    def write_mode(board):
        dimension = int((len(board)))
        line = ""
        for index1 in range(dimension):
            for index2 in range(dimension):
                line += str(index1) + ";" + str(index2) + ";" + str(board[index1][index2])
                line += ","
        line = line[:len(line) - 1]
        return line

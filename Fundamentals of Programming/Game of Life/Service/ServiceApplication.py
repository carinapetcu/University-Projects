import copy
import math


class Service:
    def __init__(self, repository, board, validator):
        self.__repository = repository
        self.__board = board
        self.__validator = validator

    def get_board(self):
        board = self.__board.get_board()
        line = " - - - - - - - - \n"
        string = ""
        string += line
        for boardLine in board:
            for cell in boardLine:
                if cell == 0:
                    string += " |"
                else:
                    string += "X|"
            string += "\n"
            string += line
        return string

    def save_file(self, fileName):
        with open(fileName, 'w') as file:
            for row in self.__board.get_board():
                line = ""
                for element in row:
                    line += str(element)+","
                line = line[:len(line) - 1]
                file.write(line + "\n")

    def load_file(self, fileName):
        with open(fileName, 'r') as file:
            lines = file.readlines()
            index1 = 0
            for line in lines:
                line = line.split(',')
                for index2 in range(8):
                    self.__board.get_board()[index1][index2] = int(line[index2])
                index1 += 1

    def place_pattern(self, pattern, coordinates):
        '''

        :param pattern: the name of the desired pattern
        :param coordinates: a list containing the row and the column of the starting point
        :return: the board is modified, putting the pattern in our board
        '''
        row = int(coordinates[0])
        column = int(coordinates[1])
        boardWithPattern = self.__repository.search([pattern, []])
        dimension = int(len(boardWithPattern))
        self.__validator.validateBoards(self.__board.get_board(), boardWithPattern, row, column)
        for index1 in range(dimension):
            for index2 in range(dimension):
                if index1 + row < 8 and index2 + column < 8:
                    # self.__board.update(index1+row, index2+column, boardWithPattern[index1][index2])
                    self.__board.get_board()[index1 + row][index2 + column] = boardWithPattern[index1][index2]

    def change_generation(self, copyOfBoard):
        '''

        :param copyOfBoard:
        :return: changes the board depending on the rules of what cells live and what cells die
        '''
        neighbours = [[-1, -1], [-1, 0], [-1, 1], [0, -1], [0, 1], [1, -1], [1, 0], [1, 1]]
        for index1 in range(8):
            for index2 in range(8):
                numberOfLivingNeighbours = 0
                for neighbour in neighbours:
                    if 0 <= neighbour[0] + index1 < 8 and 0 <= neighbour[1] + index2 < 8:
                        if copyOfBoard[neighbour[0] + index1][neighbour[1] + index2] == 1:
                            numberOfLivingNeighbours += 1
                if numberOfLivingNeighbours < 2 or numberOfLivingNeighbours > 3:
                    self.__board.get_board()[index1][index2] = 0
                if numberOfLivingNeighbours == 3 and self.__board.get_board()[index1][index2] == 0:
                    self.__board.get_board()[index1][index2] = 1

    def change_generation_pattern(self, pattern, copyOfPattern):
        '''

        :param pattern:
        :param copyOfPattern:
        :return: changes the board depending on the rules of what cells live and what cells die
        '''
        neighbours = [[-1, -1], [-1, 0], [-1, 1], [0, -1], [0, 1], [1, -1], [1, 0], [1, 1]]
        dimension = int(math.sqrt(len(pattern)))
        for index1 in range(dimension):
            for index2 in range(dimension):
                numberOfLivingNeighbours = 0
                for neighbour in neighbours:
                    if 0 <= neighbour[0] + index1 < dimension and 0 <= neighbour[1] + index2 < dimension:
                        if copyOfPattern[neighbour[0] + index1][neighbour[1] + index2] == 1:
                            numberOfLivingNeighbours += 1
                if numberOfLivingNeighbours < 2 or numberOfLivingNeighbours > 3:
                    pattern[index1][index2] = 0
                if numberOfLivingNeighbours == 3 and pattern[index1][index2] == 0:
                    pattern[index1][index2] = 1
        self.__repository.update(pattern)

    def tick(self, numberOfGenerations):
        '''
        :param numberOfGenerations:
        :return: it does the changes on the board and also on the patterns from the text file considering the 4 rules of
        living/ dying
        '''

        for index in range(numberOfGenerations):
            # initially I will change the board, by using a copy of our initial board
            copyOfBoard = copy.deepcopy(self.__board.get_board())
            self.change_generation(copyOfBoard)
            patterns = self.__repository.get_all()
            for pattern in patterns:
                patternBoard = pattern[1:]
                copyOfPattern = copy.deepcopy(patternBoard)
                self.change_generation_pattern(patternBoard, copyOfPattern)

from copy import deepcopy
import unittest


class GenerateMatrix:
    @staticmethod
    def generate_matrix(numberOfRows, numberOfColumns, emptyElement=0):
        matrix = []
        firstRow = [emptyElement] * numberOfColumns
        for index in range(numberOfRows):
            matrix += [deepcopy(firstRow)]
        return matrix


class TestGenerateMatrix(unittest.TestCase):
    def setUp(self):
        self.generateMatrix = GenerateMatrix()

    def testGenerateMatrix(self):
        matrix = [[0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0],
                  [0, 0, 0, 0, 0, 0, 0]]
        self.assertEqual(self.generateMatrix.generate_matrix(6, 7), matrix)

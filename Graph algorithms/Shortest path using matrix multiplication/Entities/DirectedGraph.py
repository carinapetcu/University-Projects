import math
import copy
from Exceptions.Exceptions import *

class DirectedGraph:
    def __init__(self, numberOfVertices):
        self._dictionaryOut = {}
        self._dictionaryIn = {}
        self._dictionaryCosts = {}
        for index in range(numberOfVertices):
            self._dictionaryOut[index] = []
            self._dictionaryIn[index] = []

    def get_number_vertices(self):
        return len(self._dictionaryOut.keys())

    def get_number_edges(self):
        return len(self._dictionaryCosts)

    def parse_set_of_vertices(self):
        for vertex in self._dictionaryOut.keys():
            yield vertex

    def check_edge(self, firstVertex, secondVertex):
        for vertex in self._dictionaryOut[firstVertex]:
            if vertex == secondVertex:
                return True
        return False

    def is_vertex(self, vertexToBeChecked):
        for vertex in self._dictionaryOut.keys():
            if vertex == vertexToBeChecked:
                return True
        return False

    def in_degree(self, vertex):
        return len(self._dictionaryIn[vertex])

    def out_degree(self, vertex):
        return len(self._dictionaryOut[vertex])

    def inbound_vertices(self, forVertex):
        for vertex in self._dictionaryIn[forVertex]:
            yield vertex

    def outbound_vertices(self, forVertex):
        for vertex in self._dictionaryOut[forVertex]:
            yield vertex

    def get_cost(self, edge):
        return self._dictionaryCosts[edge]

    def modify_cost(self, edge, newCost):
        self._dictionaryCosts[edge] = newCost

    def add_edge(self, source, destination, cost):
        keyOfDictionaryCost = (source, destination)
        self._dictionaryCosts[keyOfDictionaryCost] = cost
        self._dictionaryOut[source].append(destination)
        self._dictionaryIn[destination].append(source)

    def remove_edge(self, firstVertex, secondVertex):
        del self._dictionaryCosts[(firstVertex, secondVertex)]
        for index in range(len(self._dictionaryOut[firstVertex])):
            if self._dictionaryOut[firstVertex][index] == secondVertex:
                del self._dictionaryOut[firstVertex][index]
        for index in range(len(self._dictionaryIn[secondVertex])):
            if self._dictionaryIn[secondVertex][index] == firstVertex:
                del self._dictionaryIn[secondVertex][index]

    def add_vertex(self, newVertex):
        self._dictionaryOut[newVertex] = []
        self._dictionaryIn[newVertex] = []

    def remove_vertex(self, vertexToBeRemoved):
        # we will firstly delete the edges which have the vertex as a source
        for outVertex in self._dictionaryOut[vertexToBeRemoved]:
            del self._dictionaryCosts[(vertexToBeRemoved, outVertex)]
            for index in range(len(self._dictionaryIn[outVertex])):
                if self._dictionaryIn[outVertex][index] == vertexToBeRemoved:
                    del self._dictionaryIn[outVertex][index]
                    break

        # we will secondly delete the edges which have the vertex as a destination
        for inVertex in self._dictionaryIn[vertexToBeRemoved]:
            del self._dictionaryCosts[(inVertex, vertexToBeRemoved)]
            for index in range(len(self._dictionaryOut[inVertex])):
                if self._dictionaryOut[inVertex][index] == vertexToBeRemoved:
                    del self._dictionaryOut[inVertex][index]
                    break
        del self._dictionaryIn[vertexToBeRemoved]
        del self._dictionaryOut[vertexToBeRemoved]

    def get_matrix_of_graph(self):
        infinity = math.inf
        matrix = [[infinity for index1 in self.parse_set_of_vertices()] for index2 in self.parse_set_of_vertices()]
        for index1 in self.parse_set_of_vertices():
            for index2 in self.parse_set_of_vertices():
                if self.check_edge(index1, index2):
                    matrix[index1][index2] = self.get_cost((index1, index2))
        return matrix

    def print_matrix(self, matrix):
        stringToBePrinted = "   "
        for index1 in range(len(matrix)):
            stringToBePrinted += str(index1) + "   "
        stringToBePrinted += "\n"
        line = 0
        for index1 in range(len(matrix)):
            stringToBePrinted += str(line) + " "
            for index2 in range(len(matrix[0])):
                if matrix[index1][index2] == math.inf:
                    stringToBePrinted += str(matrix[index1][index2]) + " "
                else:
                    stringToBePrinted += " " + str(matrix[index1][index2]) + "  "

            stringToBePrinted += "\n"
            line += 1
        print(stringToBePrinted)

    def extend(self, matrix, adjacencyMatrix, prevMatrix, lengthPath, startVertex):
        copyOfMatrix = copy.deepcopy(matrix)
        for index1 in range(len(matrix)):
            for index2 in range(len(matrix)):
                if index1 != index2:
                    matrix[index1][index2] = math.inf
                    for index3 in range(len(matrix)):
                        if startVertex == index1:
                            if prevMatrix[lengthPath][index2] == -1:
                                if matrix[index1][index2] > copyOfMatrix[index1][index3] + adjacencyMatrix[index3][index2]:
                                    prevMatrix[lengthPath][index2] = index3
                                else:
                                    prevMatrix[lengthPath][index2] = prevMatrix[lengthPath-1][index2]
                        matrix[index1][index2] = min(matrix[index1][index2],
                                                     copyOfMatrix[index1][index3] + adjacencyMatrix[index3][index2])
        return matrix, prevMatrix

    def slow_apsp(self, startVertex, endVertex):
        matrix = self.get_matrix_of_graph()
        adjacencyMatrix = self.get_matrix_of_graph()
        prevMatrix = [[-1 for index1 in range(len(matrix))] for index2 in range(len(matrix))]
        for index in range(len(matrix)):
            matrix[index][index] = 0
            if self.check_edge(startVertex, index):
                prevMatrix[1][index] = startVertex

        self.print_matrix(matrix)

        for index in range(2, len(matrix)):
            copyOfMatrix = copy.deepcopy(matrix)
            matrix, prevMatrix = self.extend(copyOfMatrix, adjacencyMatrix, prevMatrix, index, startVertex)
            self.print_matrix(matrix)

        for index1 in range(len(matrix)):
            for index2 in range(len(matrix)):
                if matrix[index1][index2] < 0:
                    raise ServiceException("There are negative cycles in the graph!\n")

        if matrix[startVertex][endVertex] == math.inf:
            raise ServiceException("There is no path between the start and the end vertex!\n")

        reversedPath = []
        currentVertex = endVertex
        for index in range(len(matrix)-1, -1, -1):
            if prevMatrix[index][currentVertex] != -1:
                if prevMatrix[index][currentVertex] not in reversedPath:
                    reversedPath.append(currentVertex)
                currentVertex = prevMatrix[index][currentVertex]

        reversedPath.append(startVertex)
        reversedPath.reverse()
        path = ""
        for vertex in reversedPath:
            path += str(vertex) + " - "

        path = path[:-2]
        print(path)

        return matrix

    def get_shortest_cost(self, vertex1, vertex2):
        matrix = self.slow_apsp(vertex1, vertex2)
        return matrix[vertex1][vertex2]

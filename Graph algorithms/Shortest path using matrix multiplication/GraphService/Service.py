from Entities.DirectedGraph import *
from Exceptions.Exceptions import ServiceException
import random
import time


class Service:
    def __init__(self):
        self.__graph = DirectedGraph(0)

    def get_number_vertices(self):
        return self.__graph.get_number_vertices()

    def get_vertices(self):
        listOfVertices = []
        for vertex in self.__graph.parse_set_of_vertices():
            listOfVertices.append(vertex)
        return listOfVertices

    def check_if_edge_exists(self, firstVertex, secondVertex):
        if not self.__graph.is_vertex(firstVertex) or not self.__graph.is_vertex(secondVertex):
            raise ServiceException("Invalid values of vertices!\n")
        return self.__graph.check_edge(firstVertex, secondVertex)

    def get_in_degree(self, vertex):
        if not self.__graph.is_vertex(vertex):
            raise ServiceException("Invalid value of vertex!\n")
        return self.__graph.in_degree(vertex)

    def get_out_degree(self, vertex):
        if not self.__graph.is_vertex(vertex):
            raise ServiceException("Invalid value of vertex!\n")
        return self.__graph.out_degree(vertex)

    def get_inbound_vertices(self, vertex):
        if not self.__graph.is_vertex(vertex):
            raise ServiceException("Invalid value of vertex!\n")
        listOfVertices = []
        for vertex in self.__graph.inbound_vertices(vertex):
            listOfVertices.append(vertex)
        return listOfVertices

    def get_outbound_vertices(self, vertex):
        if not self.__graph.is_vertex(vertex):
            raise ServiceException("Invalid value of vertex!\n")
        listOfVertices = []
        for vertex in self.__graph.outbound_vertices(vertex):
            listOfVertices.append(vertex)
        return listOfVertices

    def get_cost(self, firstVertex, secondVertex):
        if not self.__graph.is_vertex(firstVertex) or not self.__graph.is_vertex(secondVertex):
            raise ServiceException("Invalid values of vertices!\n")
        if not self.__graph.check_edge(firstVertex, secondVertex):
            raise ServiceException("The edge does not exist!\n")
        edge = (firstVertex, secondVertex)
        return self.__graph.get_cost(edge)

    def modify_cost(self, firstVertex, secondVertex, newCost):
        if not self.__graph.is_vertex(firstVertex) or not self.__graph.is_vertex(secondVertex):
            raise ServiceException("Invalid values of vertices!\n")
        if not self.__graph.check_edge(firstVertex, secondVertex):
            raise ServiceException("The edge does not exist!\n")
        edge = (firstVertex, secondVertex)
        self.__graph.modify_cost(edge, newCost)

    def add_new_edge(self, firstVertex, secondVertex, newCost):
        if not self.__graph.is_vertex(firstVertex) or not self.__graph.is_vertex(secondVertex):
            raise ServiceException("Invalid values of vertices!\n")
        if self.__graph.check_edge(firstVertex, secondVertex):
            raise ServiceException("The edge already exists!\n")
        self.__graph.add_edge(firstVertex, secondVertex, newCost)

    def remove_edge(self, firstVertex, secondVertex):
        if not self.__graph.is_vertex(firstVertex) or not self.__graph.is_vertex(secondVertex):
            raise ServiceException("Invalid values of vertices!\n")
        if not self.__graph.check_edge(firstVertex, secondVertex):
            raise ServiceException("The edge does not exist!\n")
        self.__graph.remove_edge(firstVertex, secondVertex)

    def add_new_vertex(self, newVertex):
        if self.__graph.is_vertex(newVertex):
            raise ServiceException("The vertex already exists!\n")
        self.__graph.add_vertex(newVertex)

    def remove_vertex(self, vertexToDelete):
        if not self.__graph.is_vertex(vertexToDelete):
            raise ServiceException("The vertex does not exist!\n")
        self.__graph.remove_vertex(vertexToDelete)

    def copy_graph(self):
        newGraph = DirectedGraph(0)
        for vertex in self.__graph.parse_set_of_vertices():
            if not newGraph.is_vertex(vertex):
                newGraph.add_vertex(vertex)
            listOfSuccessors = self.get_outbound_vertices(vertex)
            for successor in listOfSuccessors:
                if not newGraph.is_vertex(successor):
                    newGraph.add_vertex(successor)
                cost = self.__graph.get_cost((vertex, listOfSuccessors))
                newGraph.add_edge(vertex, successor, cost)
        return newGraph

    def read_from_file_isolatedVertices(self, fileName):
        with open(fileName, 'r') as file:
            lines = file.readlines()
            lines[0] = lines[0].split()
            lines = lines[1:]
            self.__graph = DirectedGraph(0)
            for line in lines:
                line = line.strip()
                if line != "":
                    line = line.split(" ")
                    if len(line) == 3:
                        source = int(line[0])
                        destination = int(line[1])
                        cost = int(line[2])
                        if not self.__graph.is_vertex(source):
                            self.__graph.add_vertex(source)
                        if not self.__graph.is_vertex(destination):
                            self.__graph.add_vertex(destination)
                        self.__graph.add_edge(source, destination, cost)
                    elif len(line) == 2:
                        source = int(line[0])
                        if not self.__graph.is_vertex(source):
                            self.__graph.add_vertex(source)

    def read_from_file_nVertices(self, fileName):
        with open(fileName, 'r') as file:
            lines = file.readlines()
            lines[0] = lines[0].split()
            numberOfVertices = int(lines[0][0])
            lines = lines[1:]
            self.__graph = DirectedGraph(numberOfVertices)
            for line in lines:
                line = line.strip()
                if line != "":
                    line = line.split(" ")
                    if len(line) == 3:
                        source = int(line[0])
                        destination = int(line[1])
                        cost = int(line[2])
                        self.__graph.add_edge(source, destination, cost)

    def read_from_file(self, fileName):
        whichType = "nVertices"
        with open(fileName, 'r') as file:
            lines = file.readlines()
            lines = lines[1:]
            for line in lines:
                line = line.strip()
                if line != "":
                    line = line.split(" ")
                    if len(line) == 2:
                        whichType = "isolatedVertices"
        if whichType == "nVertices":
            self.read_from_file_nVertices(fileName)
        else:
            self.read_from_file_isolatedVertices(fileName)

    def write_to_file(self, fileName):
        with open(fileName, 'w') as file:
            numberVertices = self.__graph.get_number_vertices()
            numberEdges = self.__graph.get_number_edges()
            file.write(str(numberVertices) + " " + str(numberEdges) + "\n")
            for vertex in self.__graph.parse_set_of_vertices():
                if self.__graph.is_vertex(vertex):
                    if self.__graph.out_degree(vertex) == 0 and self.__graph.in_degree(vertex) == 0:
                        file.write(str(vertex) + " -1\n")
                    else:
                        listOfSuccessors = self.get_outbound_vertices(vertex)
                        for successor in listOfSuccessors:
                            edge = (vertex, successor)
                            cost = self.__graph.get_cost(edge)
                            file.write(str(vertex) + " " + str(successor) + " " + str(cost) + "\n")

    def create_random_graph(self, numberOfVertices, numberOfEdges):
        if numberOfVertices * numberOfVertices < numberOfEdges:
            raise ServiceException("The number of edges is invalid!\n")
        self.__graph = DirectedGraph(numberOfVertices)
        for index in range(numberOfEdges):
            firstVertex = random.randrange(numberOfVertices - 1)
            secondVertex = random.randrange(numberOfVertices - 1)
            while self.__graph.check_edge(firstVertex, secondVertex):
                firstVertex = random.randrange(numberOfVertices - 1)
                secondVertex = random.randrange(numberOfVertices - 1)
            cost = random.randrange(100000)
            self.__graph.add_edge(firstVertex, secondVertex, cost)

    def shortest_path(self, firstVertex, secondVertex):
        return self.__graph.get_shortest_cost(firstVertex, secondVertex)
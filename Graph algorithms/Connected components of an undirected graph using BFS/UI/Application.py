
from Exceptions.Exceptions import ServiceException
import time


class Application:
    def __init__(self, service):
        self.__service = service
        self.__commands = {
            '1': self.__add_new_edge,
            '2': self.__remove_edge,
            '3': self.__add_new_vertex,
            '4': self.__remove_vertex,
            '5': self.__read_from_file,
            '6': self.__write_to_file,
            '7': self.__create_random_graph,
            '8': self.__laboratory2Ex4
        }

    @staticmethod
    def print_options():
        print("The options are:\n"
              "1. Add a new edge\n"
              "2. Remove an edge\n"
              "3. Add a vertex\n"
              "4. Remove a vertex\n"
              "5. Read from a file\n"
              "6. Write to a file\n"
              "7. Create random graph\n"
              "8. Find the connected components of an undirected graph using a breadth-first traversal of the graph\n")

    def __add_new_edge(self):
        firstVertex = int(input("The first vertex is: "))
        secondVertex = int(input("The second vertex is: "))
        cost = int(input("The cost is: "))
        self.__service.add_new_edge(firstVertex, secondVertex, cost)

    def __remove_edge(self):
        firstVertex = int(input("The first vertex is: "))
        secondVertex = int(input("The second vertex is: "))
        self.__service.remove_edge(firstVertex, secondVertex)

    def __add_new_vertex(self):
        newVertex = int(input("The new vertex is: "))
        self.__service.add_new_vertex(newVertex)

    def __remove_vertex(self):
        vertex = int(input("The vertex to be deleted is: "))
        self.__service.remove_vertex(vertex)

    def __read_from_file(self):
        fileName = input("The file name is: ")
        self.__service.read_from_file(fileName)

    def __write_to_file(self):
        fileName = input("The file name is: ")
        self.__service.write_to_file(fileName)

    def __create_random_graph(self):
        numberOfVertices = int(input("The number of vertices is: "))
        numberOfEdges = int(input("The number of edges is: "))
        self.__service.create_random_graph(numberOfVertices, numberOfEdges)

    def __laboratory2Ex4(self):
        numberOfConnectedComponents, stringToBePrinted = self.__service.laboratory2_exercise4()
        print(stringToBePrinted)
        print("The number of connected components is ", numberOfConnectedComponents)

    def start(self):
        while True:
            self.print_options()
            option = input("Your options is: ")
            if option == 'exit':
                print("Goodbye!\n")
                break
            if option in self.__commands:
                try:
                    self.__commands[option]()
                except ValueError as valueError:
                    print("Invalid input!")
                except ServiceException as serviceException:
                    print(serviceException)
            else:
                print("Invalid command!")

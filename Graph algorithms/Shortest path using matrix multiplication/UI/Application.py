from Exceptions.Exceptions import ServiceException
import time


class Application:
    def __init__(self, service):
        self.__service = service
        self.__commands = {
            '1': self.__get_number_vertices,
            '2': self.__parse_set_of_vertices,
            '3': self.__check_if_edge,
            '4': self.__get_in_degree,
            '5': self.__get_out_degree,
            '6': self.__get_inbound_edges,
            '7': self.__get_outbound_edges,
            '8': self.__get_cost_of_edge,
            '9': self.__modify_cost,
            '10': self.__add_new_edge,
            '11': self.__remove_edge,
            '12': self.__add_new_vertex,
            '13': self.__remove_vertex,
            '14': self.__read_from_file,
            '15': self.__write_to_file,
            '16': self.__create_random_graph,
            '17': self.__shortest_path_matrix_multiplication
        }

    @staticmethod
    def print_options():
        print("The options are:\n"
              "1. Get the number of vertices\n"
              "2. Parse the set of vertices\n"
              "3. Find out whether there is an edge from the first vertex to the second one\n"
              "4. Get the in degree of a vertex\n"
              "5. Get the out degree of a vertex\n"
              "6. Get the inbound edges of a vertex\n"
              "7. Get the outbound edges of a vertex\n"
              "8. Get the information attached to an edge\n"
              "9. Modify the information attached to an edge\n"
              "10. Add a new edge\n"
              "11. Remove an edge\n"
              "12. Add a vertex\n"
              "13. Remove a vertex\n"
              "14. Read from a file\n"
              "15. Write to a file\n"
              "16. Create random graph\n"
              "17. Get shortest path\n")

    def __get_number_vertices(self):
        numberOfVertices = self.__service.get_number_vertices()
        print("The number of vertices is: {0}".format(numberOfVertices))

    def __parse_set_of_vertices(self):
        setOfVertices = self.__service.get_vertices()
        stringToBePrinted = "The vertices are: "
        for vertex in setOfVertices:
            stringToBePrinted += str(vertex) + " "
        print(stringToBePrinted)

    def __check_if_edge(self):
        firstVertex = int(input("The first vertex is: "))
        secondVertex = int(input("The second vertex is: "))
        isEdge = self.__service.check_if_edge_exists(firstVertex, secondVertex)
        if isEdge:
            print("The edge ({0},{1}) exists!".format(firstVertex, secondVertex))
        else:
            print("The edge ({0},{1}) does not exist!".format(firstVertex, secondVertex))

    def __get_in_degree(self):
        vertex = int(input("The vertex is: "))
        inDegree = self.__service.get_in_degree(vertex)
        print("The in degree of the vertex {0} is {1}\n".format(vertex, inDegree))

    def __get_out_degree(self):
        vertex = int(input("The vertex is: "))
        outDegree = self.__service.get_out_degree(vertex)
        print("The out degree of the vertex {0} is {1}\n".format(vertex, outDegree))

    def __get_inbound_edges(self):
        vertex = int(input("The vertex is: "))
        listOfVertices = self.__service.get_inbound_vertices(vertex)
        if len(listOfVertices) == 0:
            print("There are no inbound edges!")
        else:
            for inVertex in listOfVertices:
                print("({0},{1})".format(inVertex, vertex))

    def __get_outbound_edges(self):
        vertex = int(input("The vertex is: "))
        listOfVertices = self.__service.get_outbound_vertices(vertex)
        if len(listOfVertices) == 0:
            print("There are no outbound edges!")
        else:
            for outVertex in listOfVertices:
                print("({0},{1})".format(vertex, outVertex))

    def __get_cost_of_edge(self):
        firstVertex = int(input("The first vertex is: "))
        secondVertex = int(input("The second vertex is: "))
        cost = self.__service.get_cost(firstVertex, secondVertex)
        print("The cost of the edge ({0},{1}) is {2}".format(firstVertex, secondVertex, cost))

    def __modify_cost(self):
        firstVertex = int(input("The first vertex is: "))
        secondVertex = int(input("The second vertex is: "))
        newCost = int(input("The new cost is: "))
        self.__service.modify_cost(firstVertex, secondVertex, newCost)

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

    def __shortest_path_matrix_multiplication(self):
        firstVertex = int(input("The first vertex is: "))
        secondVertex = int(input("the second vertex is: "))
        print("The lowest cost walk has the cost: ", self.__service.shortest_path(firstVertex, secondVertex))

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

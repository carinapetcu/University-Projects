class UndirectedGraph:
    def __init__(self, numberOfVertices):
        self._dictionaryOut = {}
        self._dictionaryCosts = {}
        for index in range(numberOfVertices):
            self._dictionaryOut[index] = []

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

    def is_edge(self, firstVertex, secondVertex):
        for vertex in self._dictionaryOut[firstVertex]:
            if vertex == secondVertex:
                return True
        return False

    def out_degree(self, vertex):
        return len(self._dictionaryOut[vertex])

    def outbound_vertices(self, forVertex):
        for vertex in self._dictionaryOut[forVertex]:
            yield vertex

    def get_cost(self, edge):
        return self._dictionaryCosts[edge]

    def add_edge(self, source, destination, cost):
        keyOfDictionaryCost = (source, destination)
        self._dictionaryOut[source].append(destination)
        self._dictionaryOut[destination].append(source)
        self._dictionaryCosts[keyOfDictionaryCost] = cost
        self._dictionaryCosts[(destination, source)] = cost

    def remove_edge(self, firstVertex, secondVertex):
        del self._dictionaryCosts[(firstVertex, secondVertex)]
        self._dictionaryOut[firstVertex].remove(secondVertex)
        self._dictionaryOut[secondVertex].remove(firstVertex)

    def add_vertex(self, newVertex):
        self._dictionaryOut[newVertex] = []

    def remove_vertex(self, vertexToBeRemoved):
        # we will firstly delete the edges which have the vertex as a source
        for outVertex in self._dictionaryOut[vertexToBeRemoved]:
            del self._dictionaryCosts[(vertexToBeRemoved, outVertex)]
            del self._dictionaryCosts[(outVertex, vertexToBeRemoved)]
            self._dictionaryOut[outVertex].remove(vertexToBeRemoved)
        del self._dictionaryOut[vertexToBeRemoved]

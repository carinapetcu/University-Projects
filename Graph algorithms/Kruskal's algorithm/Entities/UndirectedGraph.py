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

    def parse_set_of_edges(self):
        for edge in self._dictionaryCosts.keys():
            yield edge

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

    def find_set(self, vertex, parent):
        if parent[vertex] == vertex:
            return vertex
        return self.find_set(parent[vertex], parent)

    def union_set(self, parent, rank, firstVertex, secondVertex):
        firstVertexRoot = self.find_set(firstVertex, parent)
        secondVertexRoot = self.find_set(secondVertex, parent)

        if rank[firstVertexRoot] < rank[secondVertexRoot]:
            parent[firstVertexRoot] = secondVertexRoot
        elif rank[firstVertexRoot] > rank[secondVertexRoot]:
            parent[secondVertexRoot] = firstVertexRoot
        else:
            parent[secondVertexRoot] = firstVertexRoot
            rank[firstVertexRoot] += 1

    def print_minimumSpanningTree(self, minimumSpanningTree):
        totalCost = 0
        for index in range(len(minimumSpanningTree)):
            print("Edge ({0}, {1}) having the cost {2}".format(minimumSpanningTree[index][0],
                                                               minimumSpanningTree[index][1],
                                                               minimumSpanningTree[index][2]))
            totalCost += minimumSpanningTree[index][2]
        print("Total cost is: {0}\n".format(totalCost))

    def KruskalAlgorithm(self):
        # I will create an array which contains each edge, and the cost of it, also I will create the parent set
        parent = [index for index in range(self.get_number_vertices())]
        rank = [0 for index in range(self.get_number_vertices())]
        edges = []
        minimumSpanningTree = []
        for edge in self.parse_set_of_edges():
            edges.append([edge[0], edge[1], self.get_cost(edge)])

        # I will sort the array of edges
        edges.sort(key=lambda element: element[2])
        index1 = 0
        index2 = 0
        while index2 < self.get_number_vertices() - 1:
            firstVertex, secondVertex, cost = edges[index1]
            index1 += 1
            vertex1 = self.find_set(firstVertex, parent)
            vertex2 = self.find_set(secondVertex, parent)

            if vertex1 != vertex2:
                index2 += 1
                minimumSpanningTree.append([firstVertex, secondVertex, cost])
                self.union_set(parent, rank, vertex1, vertex2)

        self.print_minimumSpanningTree(minimumSpanningTree)
        print(parent)

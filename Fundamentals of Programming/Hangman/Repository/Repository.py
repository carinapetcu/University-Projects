from Exceptions.Exceptions import RepositoryError


class Repository:
    def __init__(self):
        self._entities = []

    def size(self):
        return len(self._entities)

    def get_all(self):
        return self._entities[:]

    def add_entity(self, entity):
        if entity in self._entities:
            raise RepositoryError("Entity already added.")
        self._entities.append(entity)

    def remove_entity(self, keyOfEntity):
        if keyOfEntity not in self._entities:
            raise RepositoryError("Entity not found.")
        for index in range(len(self._entities)):
            if self._entities[index] == keyOfEntity:
                del self._entities[index]
                return

    def get_entity(self, index):
        return self._entities[index]

    def search_entity(self, keyOfEntity):
        if keyOfEntity not in self._entities:
            raise RepositoryError("Entity not found.")
        for entity in self._entities:
            if entity == keyOfEntity:
                return entity


class RepositoryFiles(Repository):
    def __init__(self, file_name):
        Repository.__init__(self)
        self.__file_name = file_name

    def read_all(self):
        self._entities = []
        with open(self.__file_name, "r") as file:
            lines = file.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    self._entities.append(line)

    def write_all(self):
        with open(self.__file_name, "w") as file:
            for entity in self._entities:
                file.write(entity + "\n")

    def size(self):
        self.read_all()
        return Repository.size(self)

    def get_all(self):
        self.read_all()
        return Repository.get_all(self)

    def add_entity(self, entity):
        self.read_all()
        Repository.add_entity(self, entity)
        self.write_all()

    def get_entity(self, index):
        self.read_all()
        return Repository.get_entity(self, index)

    def remove_entity(self, keyOfEntity):
        self.read_all()
        Repository.remove_entity(self, keyOfEntity)
        self.write_all()

    def search_entity(self, keyOfEntity):
        self.read_all()
        return Repository.search_entity(self, keyOfEntity)

from Exceptions.Exceptions import RepositoryError


class Repository:
    def __init__(self):
        self._entities = []

    def add(self, file_name, entity):
        if entity in self._entities:
            raise RepositoryError("The id is already added!")
        self._entities.append(entity)

    def size(self, file_name):
        return len(self._entities)

    def get_all_elements(self, file_name):
        return self._entities[:]


class RepositoryFile(Repository):
    def __init__(self, read_mode, write_mode):
        Repository.__init__(self)
        self.__read_mode = read_mode
        self.__write_mode = write_mode

    def read_all(self, file_name):
        with open(file_name, "r") as file:
            lines = file.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    question = self.__read_mode(line)
                    self._entities.append(question)

    def write_all(self, file_name):
        with open(file_name, "w") as file:
            for entity in self._entities:
                line = self.__write_mode(entity)
                file.write(line + "\n")

    def size(self, file_name):
        self.read_all(file_name)
        return Repository.size(self)

    def add(self, file_name, entity):
        self.read_all(file_name)
        Repository.add(self, file_name, entity)
        self.write_all(file_name)

    def get_all_elements(self, file_name):
        self.read_all(file_name)
        return Repository.get_all_elements(self, file_name)
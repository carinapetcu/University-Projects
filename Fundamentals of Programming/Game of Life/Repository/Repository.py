class Repository:
    def __init__(self):
        self._entities = []

    def get_all(self):
        return self._entities[:]

    def update(self, newEntity):
        for entity in self._entities:
            if entity[0] == newEntity[0]:
                entity[1] = newEntity[1]

    def search(self, keyOfEntity):
        for entity in self._entities:
            if entity[0] == keyOfEntity[0]:
                return entity[1]


class RepositoryFiles(Repository):
    def __init__(self, fileName, readMode, writeMode):
        Repository.__init__(self)
        self._fileName = fileName
        self._readMode = readMode
        self._writeMode = writeMode

    def read_all_from_file(self):
        self._entities = []
        with open(self._fileName, 'r') as file:
            lines = file.readlines()
            for line in lines:
                line.strip()
                if line != "":
                    line = line.split(",")
                    patternName = line[0]
                    line = line[1:]
                    line[len(line) - 1] = line[len(line) - 1][:5]
                    patternBoard = self._readMode(line)
                    entity = [patternName, patternBoard]
                    self._entities.append(entity)

    def write_all_to_file(self):
        with open(self._fileName, 'w') as file:
            for entity in self._entities:
                line = ""
                line += str(entity[0])
                line += ","
                lineBoard = self._writeMode(entity[1])
                line += lineBoard
                file.write(line+"\n")

    def update(self, newEntity):
        self.read_all_from_file()
        Repository.update(self, newEntity)
        self.write_all_to_file()

    def search(self, keyOfEntity):
        self.read_all_from_file()
        return Repository.search(self, keyOfEntity)

    def get_all(self):
        self.read_all_from_file()
        return Repository.get_all(self)
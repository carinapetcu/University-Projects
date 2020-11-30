class Repository:
    def __init__(self):
        self.__entities = []

    def add(self, new_entity):
        self.__entities.append(new_entity)

    def get_last_entity(self):
        return self.__entities[len(self.__entities) - 1]
import pickle
from errors.exceptions import RepositoryError
from Iterable import *


class Repository(object):

    def __init__(self):
        self._entities = []

    def sizeOfRepository(self):
        iterable = Iterable(self._entities)
        return iterable.__len__()

    def add(self, entity):
        if entity in self._entities:
            raise RepositoryError("The entity is already added!\n")
        self._entities.append(entity)

    def get_all_elements(self):
        iterable = Iterable(self._entities)
        return iterable._items

    def search_element(self, keyOfEntity):
        if keyOfEntity not in self._entities:
            raise RepositoryError("The ID does not exist!\n")
        iterable = Iterable(self._entities)
        for index in range(iterable.__len__()):
            if iterable.__getitem__(index) == keyOfEntity:
                return iterable.__getitem__(index)

    def remove_element(self, keyOfEntity):

        def remove_entity(anotherEntity):
            return anotherEntity != keyOfEntity

        foundKey = False
        for i in range(len(self._entities)):
            if self._entities[i] == keyOfEntity:
                foundKey = True
        if not foundKey:
            raise RepositoryError("The ID does not exist!\n")
        else:
            iterable = Iterable(self._entities)
            self._entities = iterable.filter(remove_entity)

    def update_element(self, keyOfEntity):
        if keyOfEntity not in self._entities:
            raise RepositoryError("The ID does not exist!\n")
        iterable = Iterable(self._entities)
        for i in range(iterable.__len__()):
            if iterable.__getitem__(i) == keyOfEntity:
                iterable.__setitem__(i, keyOfEntity)
                self._entities[i] = keyOfEntity
                return


class RepositoryUndoAndRedo(object):

    def __init__(self):
        self._entities = []

    def add_element(self, entity):
        self._entities.append(entity)

    def remove_last_element(self):
        self._entities.pop()

    def get_last_element(self):
        return self._entities[len(self._entities) - 1]

    def get_all_elements(self):
        return self._entities[:]


class FileRepository(Repository):

    def __init__(self, filename, read_entity, write_entity):
        Repository.__init__(self)
        self.__filename = filename
        self.__read_entity = read_entity
        self.__write_entity = write_entity

    def __read_all_from_file(self):
        self._entities = []
        with open(self.__filename, "r") as file:
            lines = file.readlines()
            for line in lines:
                line = line.strip()
                if line != "":
                    entity = self.__read_entity(line)
                    self._entities.append(entity)

    def __write_all_to_file(self):
        with open(self.__filename, "w") as file:
            for entity in self._entities:
                line = self.__write_entity(entity)
                file.write(line + "\n")

    def add(self, entity):
        self.__read_all_from_file()
        Repository.add(self, entity)
        self.__write_all_to_file()

    def search_element(self, keyOfEntity):
        self.__read_all_from_file()
        return Repository.search_element(self, keyOfEntity)

    def update_element(self, keyOfEntity):
        self.__read_all_from_file()
        Repository.update_element(self, keyOfEntity)
        self.__write_all_to_file()

    def remove_element(self, keyOfEntity):
        self.__read_all_from_file()
        Repository.remove_element(self, keyOfEntity)
        self.__write_all_to_file()

    def get_all_elements(self):
        self.__read_all_from_file()
        return Repository.get_all_elements(self)


class FileRepositoryBinary(Repository):

    def __init__(self, fileNamePickle):
        Repository.__init__(self)
        self.__fileNamePickle = fileNamePickle

    def __write_all_to_file(self):
        with open(self.__fileNamePickle, "wb") as filePickle:
            pickle.dump(self._entities, filePickle)

    def __read_all_from_file(self):
        with open(self.__fileNamePickle, "rb") as filePickle:
            self._entities = pickle.load(filePickle)

    def add(self, entity):
        self.__read_all_from_file()
        Repository.add(self, entity)
        self.__write_all_to_file()

    def search_element(self, keyOfEntity):
        self.__read_all_from_file()
        return Repository.search_element(self, keyOfEntity)

    def update_element(self, keyOfEntity):
        self.__read_all_from_file()
        Repository.update_element(self, keyOfEntity)
        self.__write_all_to_file()

    def remove_element(self, keyOfEntity):
        self.__read_all_from_file()
        Repository.remove_element(self, keyOfEntity)
        self.__write_all_to_file()

    def get_all_elements(self):
        self.__read_all_from_file()
        return Repository.get_all_elements(self)

from Entities.Entities import Room
from Exceptions.Exceptions import RepositoryError
import unittest


class Repository:
    def __init__(self):
        self._entities = []

    def size(self):
        '''

        :return: returns the size of the repository
        '''
        return len(self._entities)

    def get_all(self):
        '''
        :return: All the entities of the repository
        '''
        return self._entities[:]

    def add(self, entity):
        '''

        :param entity:
        :return: raises an error if the id of the entity is already in the repository, otherwise
        the entity gets added to the list of entities
        '''
        if entity in self._entities:
            raise RepositoryError("The ID is already added!\n")
        self._entities.append(entity)

    def delete(self, entity):
        '''

        :param entity:
        :return: raises an error if the id does not exist, otherwise it searches for the element and then deletes it
        '''
        if entity not in self._entities:
            raise RepositoryError("The ID does not exist!\n")
        for index in range(len(self._entities)):
            if self._entities[index] == entity:
                del self._entities[index]


class RepositoryFile(Repository):
    def __init__(self, file_name, read_mode, write_mode):
        Repository.__init__(self)
        self.__file_name = file_name
        self.__read_mode = read_mode
        self.__write_mode = write_mode

    def read_all_from_file(self):
        '''

        Specification: it adds all the elements from the file to the entities list
        '''
        self._entities = []
        with open(self.__file_name, "r") as file:
            lines = file.readlines()
            for line in lines:
                line.strip()
                if line != "" and line != "\n":
                    entity = self.__read_mode(line)
                    self._entities.append(entity)

    def write_all_to_file(self):
        '''

        :return: Writes all the elements from the entities list to the file
        '''
        with open(self.__file_name, "w") as file:
            for entity in self._entities:
                line = self.__write_mode(entity)
                file.write(line)


    def get_all(self):
        self.read_all_from_file()
        return Repository.get_all(self)

    def size(self):
        self.read_all_from_file()
        return Repository.size(self)

    def add(self, entity):
        self.read_all_from_file()
        Repository.add(self, entity)
        self.write_all_to_file()

    def delete(self, entity):
        self.read_all_from_file()
        Repository.delete(self, entity)
        self.write_all_to_file()


class Tests(unittest.TestCase):
    def testGetSizeReservation(self):
        self.assertEqual(RepositoryFile("tests.txt", Room.read_mode, None).size(), 2)

    def testAdd_validInput(self):
       repository = Repository()
       self.assertEqual(repository.size(), 0)
       repository.add(Room(1, 'single'))
       self.assertEqual(repository.size(), 1)

    def testGetAll_validInput(self):
        repository = Repository()
        repository.add(Room(1, 'single'))
        repository.add(Room(2, 'double'))
        self.assertEqual(len(repository.get_all()), 2)




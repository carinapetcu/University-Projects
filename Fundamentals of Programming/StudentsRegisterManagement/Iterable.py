import unittest


class Iterable:
    def __init__(self, content):
        self._content = content
        self._index = 0
        self._items = list(content)

    def __iter__(self):
        return self

    def __next__(self):
        self._index += 1
        if self._index >= len(self._items):
            raise StopIteration
        return self._items[self._index]

    def __len__(self):
        return len(self._items)

    def __getitem__(self, key):
        return self._items[key]

    def __setitem__(self, key, item):
        self._items[key] = item

    def __delitem__(self, key):
        del (self._items[key])

    def __eq__(self, anotherItem):
        return self._items == anotherItem

    def __str__(self):
        return str(self._items)

    def shell_sort(self, compare_function):
        gap = int(len(self._items) // 2)
        while gap > 0:
            for index1 in range(gap, len(self._items)):
                element = self._items[index1]
                index2 = index1
                while index2 >= gap and compare_function(self._items[index2 - gap], element) != True:
                    self._items[index2] = self._items[index2 - gap]
                    index2 -= gap
                self._items[index2] = element
            gap = int(gap // 2)

    def filter(self, acceptance_function):
        for index in range(len(self._items) - 1, -1, -1):
            if acceptance_function(self._items[index]) != True:
                self._items.remove(self._items[index])
        return self._items


class Tests(unittest.TestCase):
    def testItem_ValidValue(self):
        items = [5]
        iterable = Iterable(items)
        self.assertEqual(iterable[0], 5)

    def testSetItem_ValidValue_setsTheItem(self):
        items = [0, 1, 2]
        iterable = Iterable(items)
        iterable.__setitem__(2, 5)
        self.assertEqual(iterable[2], 5)

    def testGetNext_getsNextElement(self):
        items = [0, 1]
        iterable = Iterable(items)
        self.assertEqual(iterable.__next__(), 1)

    def testGetItem_ValidValue_getsCertainItem(self):
        items = [0, 1, 2]
        iterable = Iterable(items)
        self.assertEqual(iterable.__getitem__(2), 2)

    def testDeleteItem_ValidValue_deletsItem(self):
        items = [0, 1, 2]
        iterable = Iterable(items)
        iterable.__delitem__(1)
        self.assertEqual(iterable.__getitem__(1), 2)

    def testLen_getsLenOfItems(self):
        items = [0, 1, 2]
        iterable = Iterable(items)
        self.assertEqual(iterable.__len__(), 3)

    def testEq(self):
        items = [0, 1, 2]
        iterable = Iterable(items)
        self.assertEqual(iterable.__eq__([0, 1, 2]), True)

    def testStr(self):
        items = [0, 1, 2]
        iterable = Iterable(items)
        self.assertEqual(iterable.__str__(), "[0, 1, 2]")

    def testShellSort_unsortedList_sortsList(self):
        def compare_ascending(element1, element2):
            return element1 < element2

        items = [0, 2, 1]
        iterable = Iterable(items)
        iterable.shell_sort(compare_ascending)
        self.assertEqual(iterable.__eq__([0, 1, 2]), True)

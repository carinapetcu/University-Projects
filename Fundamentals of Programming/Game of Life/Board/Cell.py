class Cell:
    def __init__(self, row, column, value):
        self.__row = row
        self.__column = column
        self.__value = value

    def get_row(self):
        return self.__row

    def get_column(self):
        return self.__column

    def get_value(self):
        return self.__value
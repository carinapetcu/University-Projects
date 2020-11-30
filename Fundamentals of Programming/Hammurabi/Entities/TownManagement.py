class TownExpenses:
    def __init__(self, acres_of_land, population):
        self.__acres_of_land = acres_of_land
        self.__population = population

    def get_acres_of_land(self):
        return self.__acres_of_land

    def get_population(self):
        return self.__population

    def set_acres_of_land(self, new_quantity):
        self.__acres_of_land = new_quantity

    def set_population(self, new_population):
        self.__population = new_population

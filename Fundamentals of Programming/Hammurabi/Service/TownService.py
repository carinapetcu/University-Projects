from Entities.TownManagement import TownExpenses
import random


class TownService:
    def __init__(self, repository, validator):
        self.__repository = repository
        self.__validator = validator
        self.__starved_people = 0
        self.__new_people = 0
        self.__harvest = 0
        self.__rats = 0
        self.__land_price = 0
        self.__grain_stocks = 0
        self.__acres_to_plant = 0

    def initial_dates(self):
        self.__repository.add(TownExpenses(1000, 100))

    def manage_year_before_input(self):
        self.__harvest = random.randrange(1, 6, 1)
        chance_of_rats = [0, 0, 0, 0, 1]
        are_rats = random.choice(chance_of_rats)
        population = self.__repository.get_last_entity().get_population()
        acres = self.__repository.get_last_entity().get_acres_of_land()

        if population * 10 <= acres:
            self.__grain_stocks = population * 10 * self.__harvest
        else:
            self.__grain_stocks = self.__acres_to_plant * self.__harvest

        if are_rats == 1:
            self.__rats = random.randrange(1, self.__grain_stocks // 10, 1)
            self.__grain_stocks -= self.__rats
        else:
            self.__rats = 0

        self.__land_price = random.randrange(15, 25, 1)

    def make_yearly_changes(self, acres_to_buy_sell, food, acres_to_plant):
        self.__validator.validate_entry(acres_to_buy_sell, food, acres_to_plant,
                                        self.__repository.get_last_entity().get_acres_of_land(),
                                        self.__grain_stocks, self.__land_price)
        total_acres = self.__repository.get_last_entity().get_acres_of_land()
        population = self.__repository.get_last_entity().get_population()
        total_acres += acres_to_buy_sell
        self.__grain_stocks -= acres_to_buy_sell * self.__land_price
        if food // 20 < population // 2:
            return True
        self.__starved_people = population - food // 20
        if self.__starved_people < 0:
            self.__starved_people = 0
        population -= self.__starved_people
        if self.__starved_people == 0:
            self.__new_people = random.randrange(0, 10, 1)
            population += self.__new_people
        else:
            self.__new_people = 0
        self.__acres_to_plant = acres_to_plant
        self.__repository.add(TownExpenses(total_acres, population))
        return False

    def check_won(self):
        if self.__repository.get_last_entity().get_population() >= 100 and self.__repository.get_last_entity().get_acres_of_land() >= 1000:
            return True
        return False

    def print_dates(self, year):
        string_to_be_printed = ""
        string_to_be_printed += "In year " + str(year) + ", " + str(self.__starved_people) + " people starved.\n"
        string_to_be_printed += str(self.__new_people) + " people came to the city.\n"
        string_to_be_printed += "City population is " + str(
            self.__repository.get_last_entity().get_population()) + ".\n"
        string_to_be_printed += "City owns " + str(self.__repository.get_last_entity().get_acres_of_land()) + \
                                " acres of land.\n"
        string_to_be_printed += "Harvest was " + str(self.__harvest) + " units per acre.\n"
        string_to_be_printed += "Rats ate " + str(self.__rats) + " units.\n"
        string_to_be_printed += "Land price is " + str(self.__land_price) + " units per acre.\n"
        string_to_be_printed += "Grain stocks are " + str(self.__grain_stocks) + " units.\n"
        return string_to_be_printed

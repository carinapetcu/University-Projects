from Exceptions.Exceptions import ValidationError


class UI:
    def __init__(self, town_service):
        self.__town_service = town_service

    def __add_first_day(self):
        self.__town_service.initial_dates()

    def __make_yearly_activities(self):
        acres_to_buy_sell = int(input("Acres to buy/ sell (+/-) -> "))
        food = int(input("Units to feed the population -> "))
        acres_to_plant = int(input("Acres to plant -> "))
        print("\n")
        is_lost = self.__town_service.make_yearly_changes(acres_to_buy_sell, food, acres_to_plant)
        return is_lost

    def __print_statistics(self, number_of_year):
        self.__town_service.manage_year_before_input()
        print(self.__town_service.print_dates(number_of_year))

    def __check_if_won(self):
        return self.__town_service.check_won()

    def start_hammurabi(self):
        is_lost = False
        self.__add_first_day()
        number_of_year = 1
        while number_of_year != 5:
            try:
                self.__print_statistics(number_of_year)
                is_lost = self.__make_yearly_activities()
                if is_lost:
                    print("GAME OVER.")
                    break
                number_of_year += 1
            except ValueError as value_error:
                print(value_error)
            except ValidationError as validation_error:
                print(validation_error)
        self.__print_statistics(5)
        if self.__check_if_won() and is_lost != True:
            print("YOU WON!")
        else:
            print("GAME OVER.")

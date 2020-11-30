from Exceptions.Exceptions import RepositoryError, ValidationError, ServiceError


class ApplicationUI:
    def __init__(self, serviceReservation):
        self.__serviceReservation = serviceReservation
        self.__commands = {
            '1': self.__create_reservation,
            '2': self.__delete_reservation,
            '3': self.__available_rooms,
            '4': self.__monthly_report,
            '5': self.__day_of_week_report
        }

    def __create_reservation(self):
        family = input("Please enter the family name: ")
        roomType = input("Please enter the room type: ")
        guests = int(input("Please enter the number of guests: "))
        arrival = input("Please enter the arrival date(dd.mm): ")
        departure = input("Please enter the departure date(dd.mm): ")
        self.__serviceReservation.create_reservation(family, roomType, guests, arrival, departure)

    def __delete_reservation(self):
        reservationNumber = int(input("Please enter the reservation you want to delete: "))
        self.__serviceReservation.delete_reservation(reservationNumber)

    def __available_rooms(self):
        firstDate = input("Please enter the first date(dd.mm): ")
        secondDate = input("Please enter the second date(dd.mm): ")
        rooms = self.__serviceReservation.available_rooms(firstDate, secondDate)
        for room in rooms:
            print(room)

    def __monthly_report(self):
        print(self.__serviceReservation.get_monthly_report())

    def __day_of_week_report(self):
        print(self.__serviceReservation.day_of_week_report())

    def __print_commands(self):
        print("Your choices are:\n"
              "1. Create a reservation\n"
              "2. Delete a reservation\n"
              "3. Show available rooms\n"
              "4. Get monthly report\n"
              "5. Days of week report\n"
              "x. Exit\n")

    def start_application(self):
        while True:
            self.__print_commands()
            choice = input("Your choice is: ")
            if choice == 'x':
                break
            elif choice in self.__commands:
                try:
                    self.__commands[choice]()
                except ValueError as valueError:
                    print(valueError)
                except ValidationError as validationError:
                    print(validationError)
                except ServiceError as serviceError:
                    print(serviceError)
                except RepositoryError as repositoryError:
                    print(repositoryError)
            else:
                print("Try harder.")
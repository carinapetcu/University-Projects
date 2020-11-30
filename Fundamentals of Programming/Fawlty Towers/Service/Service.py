import random
import unittest

from Entities.Entities import Reservation, Room
from Exceptions.Exceptions import ServiceError, ValidationError
from Repository.Repository import RepositoryFile
from Validators.Validators import Validate


class ServiceReservation:
    def __init__(self, repositoryRoom, repositoryReservation, validator):
        self.__repositoryRoom = repositoryRoom
        self.__repositoryReservation = repositoryReservation
        self.__validator = validator
        self.__rooms = self.__repositoryRoom.get_all()

    @staticmethod
    def calculate_what_day_of_year(date):
        '''

        :param date: a string of the format dd.mm
        :return: what day in the year is that date
        the algorithm sums up all the full months until the actual one and then it adds the day of the current month
        '''
        date = date.split(".")
        day = int(date[0])
        month = int(date[1])
        months30Days = [4, 6, 9, 11]
        months31Days = [1, 3, 5, 7, 8, 10, 12]
        numberOfdays = 0
        for index in range(month):
            if index in months30Days:
                numberOfdays += 30
            elif index in months31Days:
                numberOfdays += 31
            elif index == 2:
                numberOfdays += 29
        numberOfdays += day
        return numberOfdays

    def is_available(self, roomNumber, firstDate, secondDate):
        '''
        :param roomNumber: the room we want to check if it is reserved
        :param firstDate: the date of the check in
        :param secondDate: the date of the check out
        :return: True if the room is available during this period of time
                False if it is not available then
        '''
        reservations = self.__repositoryReservation.get_all()
        firstDateNumber = self.calculate_what_day_of_year(firstDate)
        secondDateNumber = self.calculate_what_day_of_year(secondDate)
        for reservation in reservations:
            if reservation.getRoomNumber() == roomNumber:
                arrivalDate = self.calculate_what_day_of_year(reservation.getArrival())
                departureDate = self.calculate_what_day_of_year(reservation.getDeparture())
                if arrivalDate <= firstDateNumber <= departureDate:
                    return False
                if arrivalDate <= secondDateNumber <= departureDate:
                    return False
                if arrivalDate <= firstDateNumber and secondDateNumber <= departureDate:
                    return False
                if arrivalDate >= firstDateNumber and secondDateNumber >= departureDate:
                    return False
        return True

    def create_reservation(self, family, roomType, guests, arrival, departure):
        '''
        :param family: a string containing the name of a family
        :param roomType: a string containing one of the following types: single, double, family
        :param guests: number of guests
        :param arrival: the arrival date in the format dd.mm
        :param departure: the departure date in the format dd.mm
        :return: the function adds successfully a reservation if at least a room is available, otherwise it raises
         an exception
        '''
        self.__validator.validateInput(family, roomType, guests, arrival, departure)
        reservationNumber = random.randrange(1000, 9999, 1)
        for room in self.__rooms:
            isAvailable = self.is_available(room.getRoomNumber(), arrival, departure)
            if isAvailable:
                self.__repositoryReservation.add(Reservation(reservationNumber, room.getRoomNumber(),
                                                             family, guests, arrival, departure))
                return
        raise ServiceError("No room is available!\n")

    def delete_reservation(self, reservationNumber):
        '''
        :param reservationNumber: the number of the reservation we want to delete
        :return: it successfully deletes the reservation if the reservation number exists
        '''
        self.__repositoryReservation.delete(Reservation(reservationNumber, None, None, None, None, None))

    def available_rooms(self, firstDate, secondDate):
        availableRooms = []
        for room in self.__rooms:
            isAvailable = self.is_available(room.getRoomNumber(), firstDate, secondDate)
            if isAvailable:
                availableRooms.append(room)
        return availableRooms

    def get_monthly_report(self):
        reservationsMonth = [['January', 0], ['February', 0], ['March', 0], ['April', 0], ['May', 0], ['June', 0],
                             ['July', 0], ['August', 0],
                             ['September', 0], ['October', 0], ['November', 0], ['December', 0]]
        monthIndeces = ['January', 'February', 'March', 'April', 'May', 'June', 'July', 'August',
                        'September', 'October', 'November', 'December']
        reservations = self.__repositoryReservation.get_all()
        string = ""
        reservationsPerDayOfYear = [0 for index in range(366)]
        for reservation in reservations:
            arrival = self.calculate_what_day_of_year(reservation.getArrival()) - 1
            departure = self.calculate_what_day_of_year(reservation.getDeparture()) - 1
            for index in range(arrival, departure + 1, 1):
                reservationsPerDayOfYear[index] = 1

        for month in reservationsMonth:
            for index in range(12):
                if month[0] == monthIndeces[index]:
                    whichMonth = index + 1
            startDateOfMonth = "01." + str(whichMonth)
            months30Days = [4, 6, 9, 11]
            months31Days = [1, 3, 5, 7, 8, 10, 12]
            endDateOfMonth = ""
            if whichMonth in months30Days:
                endDateOfMonth = "30." + str(whichMonth)
            elif whichMonth in months31Days:
                endDateOfMonth = "31." + str(whichMonth)
            elif whichMonth == 2:
                endDateOfMonth = "29." + str(whichMonth)
            startDay = self.calculate_what_day_of_year(startDateOfMonth) - 1
            endDay = self.calculate_what_day_of_year(endDateOfMonth) - 1
            for index in range(startDay, endDay, 1):
                if reservationsPerDayOfYear[index] == 1:
                    month[1] += 1
        for index1 in range(12):
            for index2 in range(12):
                if reservationsMonth[index1][1] > reservationsMonth[index2][1]:
                    reservationsMonth[index1], reservationsMonth[index2] = reservationsMonth[index2], \
                                                                           reservationsMonth[index1]

        for month in reservationsMonth:
            string += "In "
            string += str(month[0])
            string += " "
            string += str(month[1])
            string += " days were reserved.\n"
        return string

    def day_of_week_report(self):
        reservationsDaysOfWeek = [['Wednesday', 0], ['Thursday', 0], ['Friday', 0],
                                  ['Saturday', 0], ['Sunday', 0], ['Monday', 0], ['Tuesday', 0]]
        # 1st of January was on a Wednesday
        reservations = self.__repositoryReservation.get_all()
        for reservation in reservations:
            arrival = self.calculate_what_day_of_year(reservation.getArrival()) - 1
            departure = self.calculate_what_day_of_year(reservation.getDeparture()) - 1
            for index in range(arrival, departure + 1, 1):
                modulo = index % 7 - 1
                if index % 7 - 1 == -1:
                    modulo = 6
                reservationsDaysOfWeek[modulo][1] += 1

        for index1 in range(7):
            for index2 in range(7):
                if reservationsDaysOfWeek[index1][1] > reservationsDaysOfWeek[index2][1]:
                    reservationsDaysOfWeek[index1], reservationsDaysOfWeek[index2] = reservationsDaysOfWeek[index2], \
                                                                                     reservationsDaysOfWeek[index1]

        string = ""
        for index in range(7):
            string += str(reservationsDaysOfWeek[index][1])
            string += " days reserved on "
            string += str(reservationsDaysOfWeek[index][0])
            string += '\n'

        return string


class Tests(unittest.TestCase):
    def testDayOfYear_validDay_validOutput(self):
        self.assertEqual(ServiceReservation.calculate_what_day_of_year("12.01"), 12)
        self.assertEqual(ServiceReservation.calculate_what_day_of_year("12.02"), 43)

    def testIsReserved_validInput_True(self):
        repositoryRoom = RepositoryFile("rooms1.txt", Room.read_mode, None)
        repositoryReservation = RepositoryFile("reservations1.txt", Reservation.read_mode, Reservation.write_mode)
        validator = Validate()
        service = ServiceReservation(repositoryRoom, repositoryReservation, validator)
        self.assertEqual(service.is_available(1, "15.08", "17.08"), True)

    def testAddReservation(self):
        repositoryRoom = RepositoryFile("rooms1.txt", Room.read_mode, None)
        repositoryReservation = RepositoryFile("reservations1.txt", Reservation.read_mode, Reservation.write_mode)
        validator = Validate()
        service = ServiceReservation(repositoryRoom, repositoryReservation, validator)
        self.assertRaises(ValidationError, lambda : service.create_reservation('Lalal', 'single', 1, '12.7777', '12.999'))
        self.assertEqual(repositoryReservation.size(), 11)
        service.create_reservation('Lalal', 'single', 1, '12.07', '17.07')
        self.assertEqual(repositoryReservation.size(), 12)


    def testDeleteReservation(self):
        repositoryRoom = RepositoryFile("rooms1.txt", Room.read_mode, None)
        repositoryReservation = RepositoryFile("reservations1.txt", Reservation.read_mode, Reservation.write_mode)
        validator = Validate()
        service = ServiceReservation(repositoryRoom, repositoryReservation, validator)
        self.assertEqual(repositoryReservation.size(), 12)
        service.delete_reservation(9948)
        self.assertEqual(repositoryReservation.size(), 11)


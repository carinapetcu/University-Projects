class Room:
    def __init__(self, roomNumber, roomType):
        self.__roomNumber = roomNumber
        self.__roomType = roomType

    def getRoomNumber(self):
        return self.__roomNumber

    def getRoomType(self):
        return self.__roomType

    @staticmethod
    def read_mode(line):
        parts = line.split(",")
        return Room(int(parts[0]), str(parts[1]))

    def __str__(self):
        return str(self.__roomNumber)


class Reservation:
    def __init__(self, ID, roomNumber, name, numberGuests, arrival, departure):
        self.__ID = ID
        self.__roomNumber = roomNumber
        self.__name = name
        self.__numberGuests = numberGuests
        self.__arrival = arrival
        self.__departure = departure

    def getID(self):
        return self.__ID

    def getFamily(self):
        return self.__name

    def getRoomNumber(self):
        return self.__roomNumber

    def getNumberGuests(self):
        return self.__numberGuests

    def getArrival(self):
        return self.__arrival

    def getDeparture(self):
        return self.__departure

    def __eq__(self, anotherEntity):
        return anotherEntity.getID() == self.__ID

    @staticmethod
    def read_mode(line):
        parts = line.split(",")
        return Reservation(int(parts[0]), int(parts[1]), str(parts[2]), int(parts[3]), str(parts[4]), str(parts[5]))

    @staticmethod
    def write_mode(entity):
        return str(entity.getID()) + "," + str(entity.getRoomNumber()) + "," + str(entity.getFamily()) + "," + \
               str(entity.getNumberGuests()) + "," + str(entity.getArrival()) + "," + str(entity.getDeparture()) + "\n"

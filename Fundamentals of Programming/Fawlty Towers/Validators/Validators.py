from Exceptions.Exceptions import ValidationError


class Validate:
    def __init__(self):
        pass

    def validateInput(self, family, roomType, guests, arrival, departure):
        family = family.strip()
        if family == "":
            raise ValidationError("The name is invalid!\n")

        roomTypes = ['single', 'double', 'family']
        if roomType not in roomTypes:
            raise ValidationError("The room type is invalid!\n")

        if guests < 1 or guests > 4:
            raise ValidationError("The number of guests is invalid!\n")

        arrivalDate = arrival.split(".")
        arrivalDay = int(arrivalDate[0])
        arrivalMonth = int(arrivalDate[1])

        months30Days = [4, 6, 9, 11]
        months31Days = [1, 3, 5, 7, 8, 10, 12]

        if arrivalDay < 0 or arrivalDay > 31 or (arrivalDay == 30 and arrivalMonth not in months30Days) or \
                (arrivalDay == 31 and arrivalMonth not in months31Days) or (arrivalMonth == 2 and arrivalDay > 28) \
                or arrivalMonth < 0 or arrivalMonth > 12:
            raise ValidationError("The arrival date is invalid!\n")

        departureDate = departure.split(".")
        departureDay = int(departureDate[0])
        departureMonth = int(departureDate[1])

        if departureDay < 0 or departureDay > 31 or (departureDay == 30 and departureMonth not in months30Days) or \
                (departureDay == 31 and departureMonth not in months31Days) or (arrivalMonth == 2 and departureMonth > 29)\
                or departureMonth < 0 or departureMonth > 12:
            raise ValidationError("The departure date is invalid!\n")

        if departureMonth == arrivalMonth:
            if departureDay < arrivalDay:
                raise ValidationError("The date is invalid!\n")
        elif departureMonth < arrivalMonth:
            raise ValidationError("The date is invalid!\n")

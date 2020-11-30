from Service.Service import ServiceReservation
from Validators.Validators import Validate
from Repository.Repository import RepositoryFile
from Console.UI import ApplicationUI
from Entities.Entities import Room, Reservation

repositoryRoom = RepositoryFile("rooms.txt", Room.read_mode, None)
repositoryReservation = RepositoryFile("reservations.txt", Reservation.read_mode, Reservation.write_mode)

validator = Validate()

serviceReservation = ServiceReservation(repositoryRoom, repositoryReservation, validator)

ui = ApplicationUI(serviceReservation)
ui.start_application()
from Console.Application import UI
from Service.TownService import TownService
from Validations.Validations import ValidateInput
from Repository.Repository import Repository

validator = ValidateInput()
repository = Repository()

town_service = TownService(repository, validator)

ui = UI(town_service)
ui.start_hammurabi()
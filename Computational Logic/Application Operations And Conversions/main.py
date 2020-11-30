'''
Author name: Petcu Carina
Group: 916
'''

from console.ui import ApplicationUI
from service.service import ServiceNumber
from validators.validators import ValidateNumber
from gui.gui import GUI

validateNumber = ValidateNumber()
serviceNumber = ServiceNumber(validateNumber)

gui = GUI(serviceNumber)
gui.start_application()

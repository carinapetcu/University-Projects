from GraphService.Service import Service
from UI.Application import Application

service = Service()
application = Application(service)
application.start()
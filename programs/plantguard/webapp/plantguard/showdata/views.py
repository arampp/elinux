# -*- coding: utf-8 -*-

from django.shortcuts import render_to_response
from django.http import HttpResponse
from django.conf import settings
from plantguard.showdata.models import MoistureData
from datetime import datetime, timedelta
import matplotlib.pyplot as plot
import os.path

#########
# VIEWS #
#########

def home(request):
    data = MoistureData.objects.order_by('-pub_date')[:10]
    sensor = MoistureSensor(data=data, diagramfile=None)
    return render_to_response('home.html', {'sensor' : sensor})

def show_diagrams(request, days):
    """
    Renders the diagrams page
    @param days - The number of days that should be used for the calculation.
    """
    data = MoistureData.objects.filter(pub_date__gte = datetime.now()
                                        - timedelta(int(days))) \
                                        .order_by('-pub_date')
    filename = "diagram_" + days + "_days.png"
    sensor = MoistureSensor(data=data, diagramfile=filename)
    
    draw_diagram(data, filename)
    
    return render_to_response('diagrams.html', {'sensor': sensor,
                                                'days': days})


def storedata(request, data, password):
    """
    Stores new data in the database.

    @param data - The data that should be stored
    @param password - The password that should be used for authentication.
    @return HttpResonse with status 200 if everything was ok, if the password
    was wrong, HttpResonse with status 403.
    """
    # Password
    # I'm aware that this is very insecure, it will be replaced with an
    # authenticatin mechanism in the future
    pw = "Streng5632Geheim"


    if pw == password:
        moisture = MoistureData(value=data)
        moisture.save()
        return HttpResponse(status=200)
    else:
        return HttpResponse(status=403)

##################
# HELPER CLASSES #
##################
    
class MoistureSensor(object):
    """
    Represents the data from one sensor.
    """

    # Strings for the GUI layer to show
    OK = "OK"
    WARNING = "bald gießen"
    CRITICAL = "sofort gießen"
    UNDEFINED = "keine Daten"

    def __init__(self, data=[], diagramfile='diagram.png'):
        self.data = data
        self.diagramfile = diagramfile
        if len(data) < 1:
            self.value = -1
        else:
            self.value = data[0].value

    def get_state(self):
        """
        Tests if the moisture value is ok.
        """
        if self.value == -1:
            return MoistureSensor.UNDEFINED
        elif self.value > 20:
            return MoistureSensor.OK
        elif self.value > 5:
            return MoistureSensor.WARNING
        elif self.value <= 5:
            return MoistureSensor.CRITICAL

    # properties
    state = property(fget=get_state)
    


####################
# HELPER FUNCTIONS #
####################

    
def draw_diagram(data, filename):
    """
    Draws a new diagramm and stores it under the given name. If the name
    already exists, the file will be overwritten.
    """

    x = []
    y = []
    for cur_dataset in data:
        x.append(cur_dataset.pub_date)
        y.append(cur_dataset.value)

    plot.plot(x, y)
    plot.savefig(os.path.join(settings.MEDIA_ROOT, filename))


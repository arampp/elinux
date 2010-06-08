from django.http import HttpResponse
from plantguard.storedata.models import MoistureData

# Password
pw = "Streng5632Geheim"

def storedata(request, data, password):
    if pw == password:
        moisture = MoistureData(value=data)
        moisture.save()
        return HttpResponse(status=200)
    else:
        return HttpResponse(status=403)

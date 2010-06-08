"""
This file demonstrates two different styles of tests (one doctest and one
unittest). These will both pass when you run "manage.py test".

Replace these with more appropriate tests for your application.
"""

from django.test import TestCase
from plantguard.showdata import views
from plantguard.showdata.views import MoistureSensor

class TestMoistureSensor(TestCase):


    def test_moisture_ok_OK(self):
        self.assertEqual(MoistureSensor.OK, MoistureSensor([21,]).state)
        
    def test_moisture_ok_UNDEFINED(self):
        
        self.assertEqual(MoistureSensor.UNDEFINED, MoistureSensor().state)

    def test_moisture_ok_WARNING(self):        
        self.assertEqual(MoistureSensor.WARNING, MoistureSensor([6,]).state)
        
    def test_moisture_ok_CRITICAL(self):
        self.assertEqual(MoistureSensor.CRITICAL, MoistureSensor([5,]).state)


class TestStoreData(TestCase):

    def test_storedata_with_wrong_password(self):
        self.assertEqual(403, views.storedata(None, 5, "wrongPW").status_code)

    def test_storedata_ok(self):
        self.assertEqual(200, views.storedata(None, 5, "Streng5632Geheim").status_code)


#__test__ = {"doctest": """
#Another way to test that 1 + 1 is equal to 2.

#>>> 1 + 1 == 2
#True
#"""}


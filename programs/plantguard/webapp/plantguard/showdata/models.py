from django.db import models
from datetime import datetime

# Create your models here.

class MoistureData(models.Model):
    """
    This table stores moisture data from the plants. The value is a percentage
    value ranging from 0 to 100.
    """
    value = models.IntegerField()
    pub_date = models.DateTimeField(default=datetime.now)

    def __unicode__(self):
        return str(self.value)
    

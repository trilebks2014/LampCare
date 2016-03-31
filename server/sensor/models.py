from __future__ import unicode_literals
from datetime import datetime    
from django.db import models

# Create your models here.
class Sensor(models.Model):
	idLamp = models.CharField(max_length=40,blank=False)
	sound= models.IntegerField()
	passiveInfrared = models.IntegerField()
	time = models.DateTimeField(default=datetime.now, blank=False)
	def __str__(self):
		return unicode(self.idLamp)

# -*- coding: utf-8 -*-
# Generated by Django 1.9.6 on 2016-05-16 17:06
from __future__ import unicode_literals

import datetime
from django.db import migrations, models
import django.db.models.deletion


class Migration(migrations.Migration):

    initial = True

    dependencies = [
        ('lamp', '0001_initial'),
    ]

    operations = [
        migrations.CreateModel(
            name='Sensor',
            fields=[
                ('id', models.AutoField(auto_created=True, primary_key=True, serialize=False, verbose_name='ID')),
                ('sound', models.IntegerField()),
                ('passiveInfrared', models.IntegerField()),
                ('time', models.DateTimeField(default=datetime.datetime.now)),
                ('lamp', models.ForeignKey(on_delete=django.db.models.deletion.CASCADE, to='lamp.Lamp')),
            ],
        ),
    ]

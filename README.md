# UPC PAE project 2023

This is a Spring PAE project in which i had to implement a Accelerometer and Gyroscope sensor MPU6050.
This sensor will be put in a Drone which will be used to scan and detect biodiversity of the jungle.

## MPU6050_Arduino
To work in Arduino ide i used a simple library of this own sensor and after checked the correct woking of the sensor i go with some improvement and personalization.
Basically, the addition was to hibernate the sensor. IF there was no movement or the angle of the movement was not significant enough the sensor won't send any data.


## MPU6050_RaspberryPi Model 3 2015
To work in RaspberryPI Model 3 i used a simple library of this own sensor availabe in python 

First i checked the correct woking of the sensor, to do this i used the code provided in this github profile : https://github.com/Arijit1080/mpu6050-with-Raspberry-Pi/blob/master/mpu_6050.py

After that i  go with some improvement and personalization. (Same idea while using Arduino Ide)
Basically, the addition was to hibernate the sensor. IF there was no movement or the angle of the movement was not significant enough the sensor won't send any data.


## Observation
Please before using these codes, verify that you have the libraries installed in your working enviroment.

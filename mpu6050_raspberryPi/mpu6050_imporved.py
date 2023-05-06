from mpu6050 import mpu6050
import math
import time, datetime

sensor = mpu6050(0x68)

prev_pitch = 0
prev_yaw = 0
prev_roll = 0
threshold = 5.0
current_time=datetime.datetime.now()

while True:
    accel_data = sensor.get_accel_data()
    gyro_data = sensor.get_gyro_data()
    temp = sensor.get_temp()

    if (accel_data['x'] == 0 or accel_data['y'] == 0 or accel_data['z'] == 0 or gyro_data['x'] == 0 or gyro_data['y'] == 0 or gyro_data['z'] == 0 or temp == 0):
        print("One or more sensor values are zero, skipping this reading.")
        continue

    roll = math.atan2(accel_data['y'], accel_data['z'])
    pitch = math.atan2(-accel_data['x'], math.sqrt(accel_data['y'] * accel_data['y'] + accel_data['z'] * accel_data['z']))
    yaw = math.atan2(gyro_data['y'], gyro_data['z'])

    roll = math.degrees(roll)
    pitch = math.degrees(pitch)
    yaw = math.degrees(yaw)

    if ((abs(pitch - prev_pitch) < threshold and abs(yaw - prev_yaw) < threshold) or (abs(roll - prev_roll) < threshold and abs(yaw - prev_yaw) < threshold) or (abs(pitch - prev_pitch) < threshold and abs(roll - prev_roll) < threshold)):
        pass
    else:
        print("******************************************")
        print("Temperature: {:.3f} degC".format(temp))

        # Print out the values
        print("Acceleration X: {:.3f}, Y: {:.3f}, Z: {:.3f} m/s^2".format(accel_data['x'], accel_data['y'], accel_data['z']))

        if abs(roll) > 10 and abs(pitch) > 10 and abs(yaw) > 10:
            print("Movement in en x & y & z")
            print("Roll: {:.3f} deg, Pitch: {:.3f} deg, Yaw: {:.3f} deg".format(roll, pitch, yaw))
        elif abs(roll) > 10 and abs(pitch) > 10:
            print("Movement en X & Y")
            print("Roll: {:.3f} deg, Pitch: {:.3f} deg".format(roll, pitch))
        elif abs(pitch) > 10 and abs(yaw) > 10:
            print("Movement in en Y & Z")
            print("Pitch: {:.3f} deg, Yaw: {:.3f} deg".format(pitch, yaw))
        elif abs(roll) > 10 and abs(yaw) > 10:
            print("Movement in en X & Z")
            print("Roll: {:.3f} deg, Yaw: {:.3f} deg".format(roll, yaw))
        
        print("···········Time:", current_time.strftime("%Y-%m-%d %H:%M:%S"), "··················\n")
        print("******************************************")
        print("\n")
   
        
   
    
    prev_pitch = pitch
    prev_roll = roll
    prev_yaw = yaw
    time.sleep(0.2)

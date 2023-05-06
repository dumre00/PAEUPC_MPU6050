// Basic demo for accelerometer readings from Adafruit MPU6050

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

Adafruit_MPU6050 mpu;
float prev_pitch=0, prev_yaw=0, prev_roll=0;
float threshold = 5.0; // Threshold for variation in degrees

void setup(void) {
  Serial.begin(115200);
  while (!Serial)
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }

  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_16_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
    case MPU6050_RANGE_2_G:
      Serial.println("+-2G");
      break;
    case MPU6050_RANGE_4_G:
      Serial.println("+-4G");
      break;
    case MPU6050_RANGE_8_G:
      Serial.println("+-8G");
      break;
    case MPU6050_RANGE_16_G:
      Serial.println("+-16G");
      break;
  }
  mpu.setGyroRange(MPU6050_RANGE_250_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
    case MPU6050_RANGE_250_DEG:
      Serial.println("+- 250 deg/s");
      break;
    case MPU6050_RANGE_500_DEG:
      Serial.println("+- 500 deg/s");
      break;
    case MPU6050_RANGE_1000_DEG:
      Serial.println("+- 1000 deg/s");
      break;
    case MPU6050_RANGE_2000_DEG:
      Serial.println("+- 2000 deg/s");
      break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_10_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
    case MPU6050_BAND_260_HZ:
      Serial.println("260 Hz");
      break;
    case MPU6050_BAND_184_HZ:
      Serial.println("184 Hz");
      break;
    case MPU6050_BAND_94_HZ:
      Serial.println("94 Hz");
      break;
    case MPU6050_BAND_44_HZ:
      Serial.println("44 Hz");
      break;
    case MPU6050_BAND_21_HZ:
      Serial.println("21 Hz");
      break;
    case MPU6050_BAND_10_HZ:
      Serial.println("10 Hz");
      break;
    case MPU6050_BAND_5_HZ:
      Serial.println("5 Hz");
      break;
  }

  Serial.println("");
  delay(100);
}

void loop() {
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);

  /* Check if any of the sensor values are zero, if yes then skip printing */
  if (a.acceleration.x == 0 || a.acceleration.y == 0 || a.acceleration.z == 0 ||
      g.gyro.x == 0 || g.gyro.y == 0 || g.gyro.z == 0 || temp.temperature == 0) {
    Serial.println("One or more sensor values are zero, skipping this reading.");
    mpu.begin();

  }
  else {


    //
    //    Serial.print("Rotation X: ");
    //    Serial.print(g.gyro.x*(180/PI));
    //    Serial.print(", Y: ");
    //    Serial.print(g.gyro.y*(180/PI));
    //    Serial.print(", Z: ");
    //    Serial.print(g.gyro.z*(180/PI));
    //    Serial.println(" deg/s");

    /* Calculate the angle in each axis using atan2 */
    float roll = atan2(a.acceleration.y, a.acceleration.z);
    float pitch = atan2(-a.acceleration.x, sqrt(a.acceleration.y * a.acceleration.y + a.acceleration.z * a.acceleration.z));
    float yaw = atan2(g.gyro.y, g.gyro.z);

    /* Convert radians to degrees */
    roll = roll * 180 / PI;
    pitch = pitch * 180 / PI;
    yaw = yaw * 180 / PI;

    //    Serial.print("Roll: ");
    //    Serial.print(roll);
    //    Serial.print(", Pitch: ");
    //    Serial.print(pitch);
    //    Serial.print(", Yaw: ");
    //    Serial.print(yaw);
    //    Serial.println(" deg");


    if ((abs(pitch - prev_pitch) < threshold && abs(yaw - prev_yaw) < threshold ) || (abs(roll - prev_roll) < threshold && abs(yaw - prev_yaw) < threshold ) || (abs(pitch - prev_pitch) < threshold && abs(roll - prev_roll) < threshold )) {
     
      //Serial.println("");
    }
    else {
      
      Serial.print("Temperature: ");
      Serial.print(temp.temperature);
      Serial.println(" degC");




      /* Print out the values */
      Serial.print("Acceleration X: ");
      Serial.print(a.acceleration.x);
      Serial.print(", Y: ");
      Serial.print(a.acceleration.y);
      Serial.print(", Z: ");
      Serial.print(a.acceleration.z);
      Serial.println(" m/s^2");

      if (abs(roll) > 10 && abs(pitch) > 10 && abs(yaw) > 10) {
        Serial.println("Movimientos en x & y & z");
        Serial.print("Roll: ");
        Serial.print(roll);
        Serial.print(", Pitch: ");
        Serial.print(pitch);
        Serial.print(", Yaw: ");
        Serial.print(yaw);
        Serial.println(" deg");

      }
      else if (abs(roll) > 10 && abs(pitch) > 10) {
        Serial.println("Movimientos en X & Y");
        Serial.print("Roll: ");
        Serial.print(roll);
        Serial.print(", Pitch: ");
        Serial.print(pitch);
        Serial.println(" deg");

      }
      else if (abs(pitch) > 10 && abs(yaw) > 10) {
        Serial.println("Movimientos en Y & Z");

        Serial.print("Pitch: ");
        Serial.print(pitch);
        Serial.print(", Yaw: ");
        Serial.print(yaw);
        Serial.println(" deg");

      }
      else if (abs(roll) > 10 && abs(yaw) > 10) {
        Serial.println("Movimientos en X & Z");
        Serial.print("Roll: ");
        Serial.print(roll);
        Serial.print(", Yaw: ");
        Serial.print(yaw);
        Serial.println(" deg");

      }
      Serial.println("-----------------------");

      Serial.println("");

      prev_pitch = pitch;
      prev_yaw = yaw;
      prev_roll = roll;

    }

  }

  delay(500);
}

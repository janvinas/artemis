#include <Wire.h>
#include <SPI.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>
#include <ADXL345.h> 
#include <SoftwareSerial.h>

char c = 'x';
Adafruit_BMP280 bme;
ADXL345 adxl;
int slp = 1023;
bool en = true;
int temps = 0;
bool contartemps = false;
SoftwareSerial BT(10,11);

//////////////////////////////////

void setup() {
  Serial.begin(9600);
  BT.begin(9600);
  Serial.println("INICI");
  Serial.println();
  ///PROVA SENSOR PRESSIO///
  if (!bme.begin()) {  
    Serial.println("Error starting pressure sensor!");
    while (1);
  }
  ///SENSOR ACC.///
  adxl.powerOn();
  adxl.setActivityThreshold(75); //62.5mg per increment
  adxl.setInactivityThreshold(75); //62.5mg per increment
  adxl.setTimeInactivity(10); // how many seconds of no activity is inactive?
}

//////////////////////////////////

void loop() {
  pinMode(13,OUTPUT);
  float ax;
  if(en == true){
  //BAROMETRE
  float alt = bme.readAltitude(slp);
  //ACCELEROMETRE
  int x,y,z;  
  adxl.readXYZ(&x, &y, &z); //read the accelerometer values and store them in variables  x,y,z
  double xyz[3];
  double ay,az;
  adxl.getAcceleration(xyz);
  ax = xyz[0];
  ay = xyz[1];
  az = xyz[2];
  
///////////IMPRIMIR VALORS////////

  //BT.print(alt);
  //BT.print(", ");
  BT.print(ax);
  BT.print(", ");
  BT.print(ay);
  BT.print(", ");
  BT.println(az);
  Serial.print(ax);
  Serial.print(", ");
  Serial.print(ay);
  Serial.print(", ");
  Serial.println(az);
  
  }else{}
  
  ///////LLEGIR CARACTERS BT///////
  
  if(!BT.available()){}else{
    c = BT.read();
    switch(c){
      case 's':   BT.println(slp);
                  delay(1000);
                  c = 'x';
                  break;
      case 'e':   en = true;
                  BT.println("data log enabled!");
                  delay(1000);
                  c = 'x';
                  break;
      case 'd':   en = false;
                  BT.println("data log disabled!");
                  delay(1000);
                  c = 'x';
                  break;
      case 'x':   break;
      default:    break;
    }
    }
  delay(200);
}

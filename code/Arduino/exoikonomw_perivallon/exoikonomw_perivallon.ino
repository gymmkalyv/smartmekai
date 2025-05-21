// Αρχικοποίηση pins πρώτου ultrasonic sensor
const int trigPin1 = 22;
const int echoPin1 = 23;
int pos = 5; // Ορισμός μεταβλητής για αρχική θέση κινητήρα Servo
int freetoilet=0; 

// Αρχικοποίηση pins δεύτερου ultrasonic sensor
const int trigPin2 = 24;
const int echoPin2 = 25;
#include <Servo.h>
Servo myservo; 

// Χρήση Οθόνης LCD
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,16,2); 

//RGB
int redPinTo= 3;
int greenPinTo = 4;
int bluePinTo = 5;
int prsensorTo = 6;
int redPin= 9;
int greenPin = 10;
int bluePin = 11;
int prsensor = 8;
int redPin3= 27;
int greenPin3 = 12;
int bluePin3 = 28;
int dis=10;

void setup() 
{
  pinMode(trigPin1, OUTPUT);
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin1, INPUT);  
  pinMode(echoPin2, INPUT);
  myservo.attach(7);  // Θέση 7 για κινητήρα Servo
  myservo.write(5 );  // Αρχικά κλειστή πόρτα
  // Αρχοκοποίηση οθόνης
    lcd.init();                       
  lcd.init();
  // Εμφάνιση μηνύματος στην οθόνη LCD
  lcd.backlight();
  lcd.setCursor(3,0);
  lcd.print("GYMNASIO");
  lcd.setCursor(0,1);
  lcd.print("MEGALWN KALYVIWN");
  delay(2000);
    lcd.clear();
  lcd.setCursor(0, 0); 
  lcd.print("FREE         "); 

  //ΑΡΧΙΚΟΠΟΙΗΣΗ RGB
  pinMode(redPinTo, OUTPUT);
  pinMode(greenPinTo, OUTPUT);
  pinMode(bluePinTo, OUTPUT);
  pinMode(prsensorTo, INPUT);
  pinMode(redPin3, OUTPUT);
  pinMode(greenPin3, OUTPUT);
  pinMode(bluePin3, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(prsensor, INPUT);
  pinMode(2, OUTPUT); // ΟΡΙΣΜΟΣ PIN ΦΩΤΙΣΜΟΥ
  Serial.begin(9600);
}

void loop() 
{
  digitalWrite(trigPin1, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin1, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin1, LOW);
  long duration1 = pulseIn(echoPin1, HIGH);
  int distance1 = duration1 / 58;

  digitalWrite(trigPin2, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin2, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin2, LOW);
  long duration2 = pulseIn(echoPin2, HIGH);
  int distance2 = duration2 / 58;

// RGB ΛΕΙΤΟΥΡΓΙΑ
   int valTo = digitalRead(prsensorTo); //ΤΟΥΑΛΕΤΑ
  if (valTo)
  {
     setColorTo(0, 0, 255); 
  }
  else
  {
    setColorTo(255, 0, 0); 
  }

  int val = digitalRead(prsensor); //ΒΡΥΣΗ
  if (val)
  {
     setColor(0, 0, 255); 
  }
  else
  {
    setColor(255, 0, 0); 
  }
  delay(500);

  if (freetoilet==0)
  {
    if (distance1 <=5)
    {
    for (pos = 5; pos <= 120; pos += 1) 
     { // Ανοίγει την πόρτα
      // in steps of 1 degree
      myservo.write(pos);        // Αλλαγή θέσης κινητήρα
      delay(30);                 // Περιμένει 30msec για να κλείσει σταδιακά η πόρτα
     }
     delay(1000); 
     for (pos = 120; pos >= 5; pos -= 1) 
     { // Κλείνει την πόρτα
      myservo.write(pos);          // Αλλαγή θέσης κινητήρα
      delay(30);                   // Περιμένει 30msec για να κλείσει σταδιακά η πόρτα
     }
   digitalWrite(2, HIGH);   // ΑΝΑΒΕΙ ΤΟ LCD ΦΩΤΙΣΜΟΥ
   lcd.setCursor(0, 0); 
   lcd.print("OCCUPIED!    "); 
   freetoilet=1;  
    }
  }
  //ultrasonic εσωτερικά
  if (freetoilet==1)
  {
    if (distance2 <=5)
    {
     for (pos = 5; pos <= 120; pos += 1) 
     { // Ανοίγει την πόρτα
      // in steps of 1 degree
      myservo.write(pos);        // Αλλαγή θέσης κινητήρα
      delay(30);                 // Περιμένει 30msec για να κλείσει σταδιακά η πόρτα
      }
      delay(1000); 
      for (pos = 120; pos >= 5; pos -= 1) 
      { // Κλείνει την πόρτα
        myservo.write(pos);       // Αλλαγή θέσης κινητήρα
        delay(30);                // Περιμένει 30msec για να κλείσει σταδιακά η πόρτα
      }
      digitalWrite(2, LOW);    // ΣΒΗΝΕΙ ΤΟ LCD ΦΩΤΙΣΜΟΥ
      disinfection();
      lcd.setCursor(0, 0); 
      lcd.print("FREE         ");
      freetoilet=0;  
    }
  }
}

void setColorTo(int redValueTo, int greenValueTo, int blueValueTo) 
{
  analogWrite(redPinTo, redValueTo);
  analogWrite(greenPinTo, greenValueTo);
  analogWrite(bluePinTo, blueValueTo);
}
void setColor(int redValue, int greenValue, int blueValue) 
{
  analogWrite(redPin, redValue);
  analogWrite(greenPin, greenValue);
  analogWrite(bluePin, blueValue);
}
void setColordis(int redValue3, int greenValue3, int blueValue3) 
{
  analogWrite(redPin3, redValue3);
  analogWrite(greenPin3, greenValue3);
  analogWrite(bluePin3, blueValue3);
}
void disinfection()
{
   lcd.setCursor(0, 0); 
   lcd.print("DISINFECTION!!  "); 
  while (dis >= 1)
  {
   lcd.setCursor(0, 0); 
   lcd.print("DISINFECTION!!  "); 
   lcd.setCursor(0, 1); 
   lcd.print("Wait ");
   lcd.print(dis);
   Serial.println(dis);
   lcd.print(" sec "); 
   setColordis(255, 0, 150); 
   delay(250);
   setColordis(255, 0, 255); 
   delay(250);
   setColordis(0, 0, 255); 
   delay(250);
   setColordis(0, 0, 125); 
   delay(250);
   dis--;
   lcd.clear();
   }
   dis=10;
   lcd.setCursor(0, 1); 
   lcd.print("                ");
}

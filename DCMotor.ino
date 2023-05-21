#include <Keypad.h>

#define BRAKE 0
#define CW    1
#define CCW   2
#define CS_THRESHOLD 15   // Definition of safety current (Check: "1.3 Monster Shield Example").

//Define pins
#define MOTOR_A1_PIN 12
#define MOTOR_B1_PIN 13

#define PWM_MOTOR_1 11 // pwm pin

#define CURRENT_SEN_1 A2

#define EN_PIN_1 A0

#define MOTOR_1 0

short usSpeed = 96.63157895;  //default 36rpm motor speed for 95rpm DC Motor, 0-255 Duty Cycle
unsigned short usMotor_Status = BRAKE;


// define keypad pins
const byte ROWS = 4; 
const byte COLS = 4; 

char hexaKeys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

byte rowPins[ROWS] = {9, 8, 7, 6}; 
byte colPins[COLS] = {5, 4, 3, 2}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);
 
void setup()                         
{
  pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);

  pinMode(PWM_MOTOR_1, OUTPUT);
  
  pinMode(CURRENT_SEN_1, OUTPUT);
 
  pinMode(EN_PIN_1, OUTPUT);

  Serial.begin(9600);              // Initiates the serial to do the monitoring 
  Serial.println("Begin motor control");
  Serial.println(); //Print function list for user selection
  Serial.println("Press numpad for control option:");
  Serial.println("1. STOP");
  Serial.println("2. 36 RPM");
  Serial.println("3. 42 RPM");
  Serial.println("4. 48 RPM");
  Serial.println("5. 95 RPM (Max RPM)");
  Serial.println();
}

void loop() 
{
  char customKey = customKeypad.getKey();  


 digitalWrite(EN_PIN_1, HIGH);
  
 if (customKey =='1')
    {
       Stop();
       Serial.println("1");
    }
    else if(customKey =='2')
    {
      RPM36();
      Serial.println("36 RPM");
    }
    else if(customKey =='3')
    {
      RPM42();
      Serial.println("42 RPM");
    }
    else if(customKey =='4')
    {
      RPM48();
      Serial.println("48 RPM");
    }
     else if(customKey =='5')
    {
      RPMMAX();
      Serial.println("95 RPM");
    }
}

void Stop()
{
  Serial.println("Stop");
  usMotor_Status = BRAKE;
  motorGo(MOTOR_1, usMotor_Status, 0);
}

void RPM36()
{
  Serial.println("36 RPM");
  usMotor_Status = CW;
  motorGo(MOTOR_1, usMotor_Status, 96.63157895);
}

void RPM42()
{
  Serial.println("42RPM");
  usMotor_Status = CW;
  motorGo(MOTOR_1, usMotor_Status, 112.7368421);
}

void RPM48()
{
  Serial.println("48RPM");
  usMotor_Status = CW;
  motorGo(MOTOR_1, usMotor_Status, 128.8421053);
}

void RPMMAX()
{
  Serial.println("Max Rpm (95rpm)");
  usMotor_Status = CW;
  motorGo(MOTOR_1, usMotor_Status, 255);
}


void motorGo(uint8_t motor, uint8_t direct, uint8_t pwm)         //Function that controls the variables: motor(0 ou 1), direction (cw ou ccw) e pwm (entra 0 e 255);
{
  if(motor == MOTOR_1)
  {
    if(direct == CW)
    {
      digitalWrite(MOTOR_A1_PIN, LOW); 
      digitalWrite(MOTOR_B1_PIN, HIGH);
    }
    else if(direct == CCW)
    {
      digitalWrite(MOTOR_A1_PIN, HIGH);
      digitalWrite(MOTOR_B1_PIN, LOW);      
    }
    else
    {
      digitalWrite(MOTOR_A1_PIN, LOW);
      digitalWrite(MOTOR_B1_PIN, LOW);            
    }
    
    analogWrite(PWM_MOTOR_1, pwm); 
  }
}



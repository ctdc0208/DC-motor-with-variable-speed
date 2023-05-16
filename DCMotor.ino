#define CS_THRESHOLD 15   // Definition of safety current
// Define values for:
#define BRAKE 0
#define CW 1 // clockwise
#define MOTOR_1 0

//Assign Pins
#define EN_PIN_1 A0
#define CURRENT_SEN_1 A2 // CS > A2
#define MOTOR_B1_PIN 8 // INB > D8
#define MOTOR_A1_PIN 7 // INA > D7
#define PWM_MOTOR_1 5 // PWM > D5

// default RPM
short usSpeed = 36;
unsigned short usMotor_Status = BRAKE;

void setup ()
{
	pinMode(MOTOR_A1_PIN, OUTPUT);
  pinMode(MOTOR_B1_PIN, OUTPUT);

  pinMode(PWM_MOTOR_1, OUTPUT);
  
  pinMode(CURRENT_SEN_1, OUTPUT);
 
  pinMode(EN_PIN_1, OUTPUT);

	Serial.begin(9600);              // Initiates the serial to do the monitoring 
  Serial.println("Begin motor control");
  Serial.println(); //Print function list for user selection
  Serial.println("Enter number for control option:");
  Serial.println("1. STOP");
  Serial.println("2. 36 RPM");
  Serial.println("3. 42 RPM");
	Serial.println("4. 46 RPM");
  Serial.println();
}

void loop()
{
	user_input = Serial.read(); //Read user input and trigger appropriate function
    digitalWrite(EN_PIN_1, HIGH);

     
    if (user_input =='1')
    {
       Stop();
    }
    else if(user_input =='2')
    {
      FirstRPM();
    }
    else if(user_input =='3')
    {
      SecondRPM() () ;
    }
    else if(user_input =='4')
    {
      ThirdRPM();
    }
    else
    {
      Serial.println("Invalid option entered.");
    }   
  }
}

void Stop()
{
	Serial.println("Stop");
  usMotor_Status = BRAKE;
  motorGo(MOTOR_1, usMotor_Status, 0);
}

void FirstRPM() 
{
	usSpeed = usSpeed;
	Serial.print("Speed = 36 rpm");
  Serial.println(usSpeed);

  motorGo(MOTOR_1, usMotor_Status, usSpeed);
}

void SecondRPM() 
{
	usSpeed = 42;
	Serial.print("Speed = 36 rpm");
  Serial.println(usSpeed);

  motorGo(MOTOR_1, usMotor_Status, usSpeed);
}

void ThirdRPM() 
{
	usSpeed = 46;
	Serial.print("Speed = 36 rpm");
  Serial.println(usSpeed);

  motorGo(MOTOR_1, usMotor_Status, usSpeed);
}
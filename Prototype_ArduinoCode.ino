// VARIABLES
// motor A
int enA = 11; //PB5
int in1 = 12; //PB6
int in2 = 13; //PB7
// motor B
int enB = 5; //PE3 
int in3 = 6; //PH3
int in4 = 7; //PH4
// sensors
int SENSOR1 = 0; // PF0 (ADC0)
int SENSOR2 = 1; // PF1 (ADC1)
int SENSOR3 = 2; // PF2 (ADC2)
int SENSOR4 = 3; // PF3 (ADC3)
int SENSOR5 = 4; // PF4 (ADC4)
int SENSOR6 = 5; // PF5 (ADC5)
int SENSOR7 = 6; // PF6 (ADC6)
int s1, s2, s3, s4, s5, s6, s7;

int speed_motors = 150; //max 255;

float corrA = 0.9; // correction factor for A motor
float corrB = 1; // correction factor for B motor

int turn_speed_stop = 0;
int turn_speed_move = 100; 

/*  STATES
 *  1. line following
 *  2. stop
 *  3. turn
 *  4. end_stop
 *  5. out_room
 */
int  state = 1;

// conditions to finish turning
int cond_1 = 0;
int cond_2 = 0;
int cond_3 = 0;

int turn_count = 0;

void setup() {
  // UART
  Serial.begin(9600);
  
  // Set all the motor control pins to outputs
  // motor A
  pinMode(enA, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  // motor B
  pinMode(enB, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);
  
  stopMotors();
  speedMotors(speed_motors);
}

void loop() {  
  s1 = (analogRead(SENSOR1)>40) ? 1 : 0;
  s2 = (analogRead(SENSOR2)>200) ? 1 : 0;
  s3 = (analogRead(SENSOR3)>150) ? 1 : 0;
  s4 = (analogRead(SENSOR4)>100) ? 1 : 0;
  s5 = (analogRead(SENSOR5)>70) ? 1 : 0;
  s6 = (analogRead(SENSOR6)>100) ? 1 : 0;
  s7 = (analogRead(SENSOR7)>100) ? 1 : 0;

  /* LINE FOLLOWING */
  if (state == 1) {
    if (s1  &&  s2) {
      moveForward();
    }
    if (s1  && !s2) {
      turnRight();
    }
    if (!s1 &&  s2) {
      turnLeft();
    }

    // STOP
    if (s3 && !s4  && s7) {
      state = 2;
      Serial.println("stop");
    }

    // TURN
    if (s3  &&  s4  && s7) {
      if (turn_count == 1) {
        corrA = 0.7;
      } 
      stopMotors();
      state = 3;
      cond_1 = 0;
      cond_2 = 0;
      cond_3 = 0;
      Serial.println("Turn");
    }
    /* STOP */
  } else if (state == 2) {
      stopMotors();
      delay(1000);
      Serial.println("End stop");
      moveForward();a
      speedMotors(speed_motors);
      state = 4; /* END STOP */
  } else if (state == 4) {
    if(!s3) {
      state = 1; /* LINE FOLLOWING */
      Serial.println("Line following");
    }
    /* TURN */
  }  else if (state == 3) {
    if (cond_2 == 0) {
      turnClockwise();
    }
    if (!s4 && !s3) {
      cond_1 = 1;
    }
    if (cond_1 == 1 &&  s5 && !s6) {
      cond_2 = 1;
    }
    
    if (cond_2 == 1 &&  s6) {
      moveForward();
      speedMotors(speed_motors); 
      cond_3 = 1;
    }
    // END OF TURN
    if (cond_3 == 1 && !s3) {
      Serial.println("Line following");
      if (turn_count < 2) {
        turn_count++;
        Serial.print("turn_count: ");
        Serial.println(turn_count);
      }
      if (turn_count == 2) {
        corrA = 0.9;
        state = 5; /* OUT ROOM */
        turn_count = 0;
        Serial.println("Out of room");
      } else {
        state = 1; /* LINE FOLLOWING */
        Serial.println("Line following");
      }
    }
    /* OUT ROOM */
  } else if ( state == 5 ) {
    if (s1  &&  s2) {
      moveForward();
    }
    if (s1  && !s2) {
      turnRight();
    }
    if (!s1 &&  s2) {
      turnLeft();
    }
    if (!s1 && !s2 && s7) {
      special_count++;
      moveForward();
      Serial.println("Exiting room");
    }
    if ( s3 || s4) {
      Serial.println("Turn");
      state = 3; /* TURN */
      turn_count = 0;
    }
  }
}

// =====================================================================
// FUNCTIONS

// Set speed for both motors
void speedMotors(int speed_val){
  // Set motors to speed_val
  // For PWM maximum possible values are 0 to 255
  // motor A
  analogWrite(enA, speed_val*corrA);
  // motor B
  analogWrite(enB, speed_val*corrB);
}

// Move both motors at same speed, forward
void moveForward() {
   // Forward motor A 
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // Forward motor B 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Set turning speeds and turn right 
void turnRight() {  
  // motor A
  analogWrite(enA, turn_speed_move);
  // motor B
  analogWrite(enB, turn_speed_stop);
  // Forward motor A 
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // Forward motor B 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Set turning speeds and turn left 
void turnLeft() {  
  // motor A
  analogWrite(enA, turn_speed_stop);
  // motor B
  analogWrite(enB, turn_speed_move);
  // Forward motor A 
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // Forward motor B 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Move both motors at same speed, backwards
void moveBackward() {
  // Backward motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // Backward motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

// Set clockwise turning speed and turn
void turnClockwise() {
  speedMotors(speed_motors);
   // Forward motor A 
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // Backward motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

// Set anti-clockwise turning speed and turn
void turnAntiClockwise() {
  // Backward motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // Forward motor B 
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

// Stop both motors
void stopMotors(){
  // Turn off motor A
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  // Turn off motor B
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

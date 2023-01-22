/*
  The connectors are pin numbers on the arduino board which can be changed
  according to circuit connections. The mentioned ones are placeholders.
*/

int trigger_connector = 4; // connects to the HCSR04 trig pin and generates an ultrasonic pulse.
int echo_connector = 5; // connects to the HCSR04 echo pin and recieves the ultrasonic pulse reflected from the obstacle.
int buzzer_connector = 10; // buzzer control pin
int time; // variable declaration
int distance; // variable declaration

void setup() //This function sets up the data once.
{
  Serial.begin(9600);
  /*
    Serial establishes a connection for data transfer between the arduino and PC using the cable.
    9600 is the baud rate (bits per second) which can go upto 115200 bits per second.
    Since we are not emphasising on high speed functionality, a minimum of 9600 bits per second
    ensures loss less transmission at workable speeds.
  */
  pinMode (trigger_connector, OUTPUT); // We are using the trig pin to send a pulse, hence pin mode is set as output
  pinMode (echo_connector, INPUT); // Echo pin recieves the reflected wave, hence, input mode.
  pinMode (buzzer_connector, OUTPUT); // Buzzer provides output into the real world.
}

void loop() //This function keeps running as long as the arduino is powered up.
{
  digitalWrite (trigger_connector, HIGH);
  delayMicroseconds (10);
  digitalWrite (trigger_connector, LOW);
  /*
    The three lines above generate an ultrasonic pulse with a period of 10 microseconds (default).
  */
  time = pulseIn (echo_connector, HIGH); // PulseIn function returns the time period of the reflected wave (See explanations and Illustrations folder for details).
  /*
    Distance = Speed x Time
    Speed = approx 340 m/s = 0.034 cm/us
    Time = From pulseIn function
  */
  distance = (0.034 * time) / 2; //in centimeters
  /*
    We remove half the time because
    we only require the time that it takes the wave to reach the object
    and not the time it takes to come back as well.
  */

  // Now we are concerned with the buzzer
  if (distance <= 30) // Change the distance limit (centimeters) as per requirement
  {
    digitalWrite (buzzer_connector, HIGH); // The alarm goes off.
    Serial.println ("Obstacle close enough, Distance = ");
    Serial.println (distance); // Printing the distance of the obstacle on the serial monitor.
    delay (500); //delay before continuing to the next iteration
  }
  else
  {
    digitalWrite (buzzer_connector, LOW);
    Serial.println ("Obstacle far away, Distance = ");
    Serial.println (distance); // Printing the distance of the obstacle on the serial monitor.
    delay (500); //delay before continuing to the next iteration
  }
}

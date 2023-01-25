
/*
January 2023
@author: madshv

NB: When loading a program to the arduino, remove the capacitor between reset and ground.
When running the program, ensure to put a capacitor between reset and ground. Otherwise, problems
will occur when opening and closing the serial connection while the Arduino program is running!

This program is used to control the temperature of two piezo stages, each with three voltage inputs.
The piezo stage temperatures are controlled by a voltage, which is supplied from PWM Arduino output.
The Arduino has 6 PWM outputs, 3 for each piezo stage.
The program takes USB serial commands from the arduino_comm.py script, and sets the PWM outputs
hereafter.

The stages must be connected to the following PWM pins:
# stage 1, X = pin D6
# stage 1, Y = pin D5
# stage 1, Z = pin D9
# stage 2, X = pin D10
# stage 2, Y = pin D11
# stage 2, Z = pin D3
*/

// Define global variables
uint8_t input_byte=10;
String str,str_dir,str_num;

// The setup() function is run once when the arduino is powered.
// In this function, the three timers of the atmega328p are set to 64 kHz PWM mode.
// For each timer, two PWM outputs are available.
// The meaning of the registers can be found in the datasheet of the atmega328p.
void setup() {
  Serial.begin(115200);   // Must match with the python program serial baudrate.
  
  // Set timer0 registers
  // OC0A=D6, OC0B=D5
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  OCR0A = 50;   // Set output register A to 50/255 PWM duty cycle
  OCR0B = 150;  // Set output register B to 150/255 PWM duty cycle
  TCCR0A = (1<<COM0A1);   //Set OC1A on compare match, clear OC1A at BOTTOM, (non-inverting mode).
  TCCR0A |= (1<<COM0B1); //Set OC1B on compare match, clear OC1B at BOTTOM, (non-inverting mode).
  TCCR0A |= (1<<WGM01)|(1<<WGM00); //Fast PWM
  TCCR0B = (1<<CS00);  // Prescaler=1

  // Set timer1 registers
  // OC1A=D9, OC1B=D10
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  OCR1A = 50;   // Set output register A to 50/255 PWM duty cycle
  OCR1B = 150;  // Set output register B to 150/255 PWM duty cycle
  TCCR1A = (1<<COM1A1); //Set OC1A on compare match, clear OC1A at BOTTOM, (non-inverting mode).
  TCCR1A |= (1<<COM1B1); //Set OC1B on compare match, clear OC1B at BOTTOM, (non-inverting mode).
  TCCR1A |= (1<<WGM10); //Fast PWM, 8-bit
  TCCR1B = (1<<WGM12)|(1<<CS10);  //Fast PWM, 8-bit and prescaler=1

  // Set timer2 registers
  // OC2A=D11, OC2B=D3
  pinMode(11,OUTPUT);
  pinMode(3,OUTPUT);
  OCR2A = 50;   // Set output register A to 50/255 PWM duty cycle
  OCR2B = 150;  // Set output register B to 150/255 PWM duty cycle
  TCCR2A = (1<<COM2A1); //Set OC2A on compare match, clear OC2A at BOTTOM, (non-inverting mode).
  TCCR2A |= (1<<COM2B1); //Set OC2B on compare match, clear OC2B at BOTTOM, (non-inverting mode).
  TCCR2A |= (1<<WGM21)|(1<<WGM20); //Fast PWM
  TCCR2B = (1<<CS20);   // Prescaler = 1
  
}

// The loop() function runs continiously in loop once after the setup() function has been run.
// In this function the incoming serial messages are read, and based on the incoming string,
// the PWM duty cycle of one of the PWM pins is set.
void loop() {
  while(Serial.available()>0){  // read while there are messages available in the serial buffer.
    // Read and split the incoming string.
    str = Serial.readString();
    str_dir = str.substring(0,2);
    str_num = str.substring(2);
    
    // convert to an unsigned byte.
    input_byte = uint8_t(str_num.toInt());

    // Set one of the PWM duty cycles.
    if(str_dir=="X1"){
      OCR0A = input_byte; //OC0A=D6
    }
    else if(str_dir=="Y1"){
      OCR0B = input_byte; //OC0B=D5
    }
    else if(str_dir=="Z1"){
      OCR1A = input_byte; //OC1A=D9
    }
    else if(str_dir=="X2"){
      OCR1B = input_byte; //OC1B=D10
    }
    else if(str_dir=="Y2"){
      OCR2A = input_byte; //OC2A=D11
    }
    else if(str_dir=="Z2"){
      OCR2B = input_byte; //OC2B=D3
    }
    // Send the read string components back (used for debugging)
    Serial.println(str_dir);
    Serial.println(str_num);
  }
}

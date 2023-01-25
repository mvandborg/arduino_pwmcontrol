

int pwmPin = 5;
uint8_t input_byte=10;
String str,str_dir,str_num;

// When loading a program to the arduino, remove the capacitor between reset and ground.

void setup() {
  Serial.begin(115200);
  
  // Set timer0 registers
  // OC0A=D6, OC0B=D5
  pinMode(6,OUTPUT);
  pinMode(5,OUTPUT);
  OCR0A = 50;
  OCR0B = 150;
  TCCR0A = (1<<COM0A1); //Set OC1A on compare match, clear OC1A at BOTTOM, (non-inverting mode).
  TCCR0A |= (1<<COM0B1); //Set OC1B on compare match, clear OC1B at BOTTOM, (non-inverting mode).
  TCCR0A |= (1<<WGM01)|(1<<WGM00); //Fast PWM
  TCCR0B = (1<<CS00);  // Prescaler=1

  // Set timer1 registers
  // OC1A=D9, OC1B=D10
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  OCR1A = 50;
  OCR1B = 150;
  TCCR1A = (1<<COM1A1); //Set OC1A on compare match, clear OC1A at BOTTOM, (non-inverting mode).
  TCCR1A |= (1<<COM1B1); //Set OC1B on compare match, clear OC1B at BOTTOM, (non-inverting mode).
  TCCR1A |= (1<<WGM10); //Fast PWM, 8-bit
  TCCR1B = (1<<WGM12)|(1<<CS10);  //Fast PWM, 8-bit and prescaler=1

  // Set timer2 registers
  // OC2A=D11, OC2B=D3
  pinMode(11,OUTPUT);
  pinMode(3,OUTPUT);
  OCR2A = 50;
  OCR2B = 150;
  TCCR2A = (1<<COM2A1); //Set OC2A on compare match, clear OC2A at BOTTOM, (non-inverting mode).
  TCCR2A |= (1<<COM2B1); //Set OC2B on compare match, clear OC2B at BOTTOM, (non-inverting mode).
  TCCR2A |= (1<<WGM21)|(1<<WGM20); //Fast PWM
  TCCR2B = (1<<CS20);   // Prescaler = 1
  
}

void loop() {
  while(Serial.available()>0){
    str = Serial.readString();
    str_dir = str.substring(0,2);
    str_num = str.substring(2);
    input_byte = uint8_t(str_num.toInt());
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
    Serial.println(str_dir);
    Serial.println(str_num);
  }
}

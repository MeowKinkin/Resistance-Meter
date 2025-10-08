// Digital pins Initialization 
int D8 = 8;
int D9 = 9;
int D10 = 10;
int D11 = 11;
// Analog pins Initialization 
int TP1 = A0;
int TP2 = A1;

int ADC_1 = 0;
int ADC_2 = 0;

double R1 = 680+29;
double R2 = 470000+10.9;
double R3 = 680+24.8;
double R4 = 470000+5.46;
double Rx = 0;

double a = 0;
double b = 0;

double V1 = 0;
double V2 = 0;
double Vx = 0;


void setup() {
  Serial.begin(9600);
}

// To get stable ADC values
int stableAnalogRead(uint8_t pin, unsigned int settle_us = 2000, int samples = 3) {
  analogRead(pin);
  delayMicroseconds(settle_us);      
  int sum = 0;
  for(int i=0;i<samples;i++){
    sum += analogRead(pin);           // Averaging the ADC values to reduce error
    delayMicroseconds(50);           
  }
  return sum / samples;
}

void loop() {
  int flag = 0;
  double voltage = checker_1();         // For resistance value between 1 to 13K ohm
 
  if(voltage>=4.8)                    
 {
   voltage =  checker_2();              // For resistance value between 1 to 13K ohm
  }

  else if(voltage>=4.7)               
  {
    voltage = checker_3();             // For resistance value between 10M to 50M ohm
  }

  if(voltage > 4.8){                  // For when no resistor is connected
    Serial.println("Open Circuit");
    Serial.println();
    flag = 1;
    delay(1000);
  }

  Rx = (Vx*(a + b)) / (5 - Vx);         // Formula to measure resistance
  if(flag == 0){
  Serial.print("Voltage Drop: ");
  Serial.println(voltage,4);
  Serial.print("Resistance Value: ");
  Serial.println((double)Rx, 3);
  Serial.println();
  delay(1000);
  }
}

double checker_1(){                   // For resistance value between 1 to 13K ohm (only R1 and R3 combunations)
  a=R1; //680 Ohm
  b=R3; //680 Ohm
  analogReference(DEFAULT);
  pinMode(D8, OUTPUT);
  pinMode(D9, INPUT);
  pinMode(D10, OUTPUT);
  pinMode(D11, INPUT);

  digitalWrite(D8, HIGH);
  digitalWrite(D10, LOW);


ADC_1 = stableAnalogRead(TP1, 2000, 4); // 2 ms settle, average 4 samples
ADC_2 = stableAnalogRead(TP2, 2000, 4);
V1 = (ADC_1 * (5.0 / 1023.0));
V2 = (ADC_2 * (5.0 / 1023.0));
Vx = V1 - V2;
return Vx;
}

double checker_2(){             // For resistance value between 13K to 10M ohm (only R2 and R3 combunations)
  a=R2; //470k Ohm
  b=R3; //680 Ohm
  pinMode(D9, OUTPUT);
  pinMode(D10, OUTPUT);
  pinMode(D8, INPUT);
  pinMode(D11, INPUT);
  digitalWrite(D9, HIGH);
  digitalWrite(D10, LOW);

  ADC_1 = stableAnalogRead(TP1, 2000, 4); // 2 ms settle, average 4 samples
  ADC_2 = stableAnalogRead(TP2, 2000, 4);
  V1 = (ADC_1 * (5.0 / 1023.0));
  V2 = (ADC_2 * (5.0 / 1023.0));
  Vx = V1 - V2;
  return Vx;
}

double checker_3(){             // For resistance value between 10M to 50M ohm (only R2 and R4 combunations)
  a=R2; //470k
  b=R4; //470k
  pinMode(D10, INPUT);
  pinMode(D11, OUTPUT);
  pinMode(D8, INPUT);
  pinMode(D9, OUTPUT);

  digitalWrite(D9, HIGH);
  digitalWrite(D11, LOW);
  delayMicroseconds(200);    

  ADC_1 = stableAnalogRead(TP1, 2000, 4);
  ADC_2 = stableAnalogRead(TP2, 2000, 4);
  V1 = (ADC_1 * (5.0 / 1023.0));
  V2 = (ADC_2 * (5.0 / 1023.0));
  Vx = V1 - V2;

  return Vx;
}

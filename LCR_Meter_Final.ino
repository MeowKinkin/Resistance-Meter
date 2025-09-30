int D8 = 8;
int D9 = 9;
int D10 = 10;
int D11 = 11;
int vref=5;


int TP1 = A0;
int TP2 = A1;
int ADC_1 = 0;
int ADC_2 = 0;

double Rx = 0;

double R1 = 680+29;
double R2 = 470000+10.9;
double R3 = 680+24.8;
double R4 = 470000+5.46;
double a = 0;
double b = 0;
double V1 = 0;
double V2 = 0;

double Vx = 0;

void setup() {
  Serial.begin(9600);

}

int stableAnalogRead(uint8_t pin, unsigned int settle_us = 2000, int samples = 3) {
  analogRead(pin);
  delayMicroseconds(settle_us);      
  int sum = 0;
  for(int i=0;i<samples;i++){
    sum += analogRead(pin);
    delayMicroseconds(50);           
  }
  return sum / samples;
}

void loop() {
  //vref=5;
  int flag = 0;
  double voltage = checker_1();
 
  if(voltage>=4.8){
   voltage =  checker_2();
   
  }
  else if(voltage>=4.7){
    voltage = checker_3();
  }
  if(voltage > 4.8){
    Serial.println("Open Circuit");
    //Serial.println(voltage,4);
    Serial.println();
    flag = 1;
    delay(1000);
  }

  //Rx = (b*(5-voltage)-(voltage*a))/(voltage-5);
  Rx = (Vx*(a + b)) / (5 - Vx);
  //Serial.println(ADC_1);
  if(flag == 0){
  Serial.print("Voltage Drop: ");
  Serial.println(voltage,4);
  Serial.print("Resistance Value: ");
  Serial.println((double)Rx, 3);
  Serial.println();
  delay(1000);
  }

}

double checker_1(){
  a=R1; //680
  b=R3; //680
  analogReference(DEFAULT);
  pinMode(D8, OUTPUT);
  pinMode(D9, INPUT);
  pinMode(D10, OUTPUT);
  pinMode(D11, INPUT);

  digitalWrite(D8, HIGH);
  digitalWrite(D10, LOW);
  //analogRead(TP1);
  //delayMicroseconds(200);      // small settle time

ADC_1 = stableAnalogRead(TP1, 2000, 4); // 2 ms settle, average 4 samples
ADC_2 = stableAnalogRead(TP2, 2000, 4);
V1 = (ADC_1 * (5.0 / 1023.0));
V2 = (ADC_2 * (5.0 / 1023.0));
Vx = V1 - V2;

  //Serial.println("1st");
      //Serial.println(V1);
      //Serial.println(V2);
  return Vx;
}

double checker_2(){
  a=R2; //470k
  b=R3; //680
  pinMode(D9, OUTPUT);
  pinMode(D10, OUTPUT);
  pinMode(D8, INPUT);
  pinMode(D11, INPUT);
  //analogReference(DEFAULT);
  digitalWrite(D9, HIGH);
  digitalWrite(D10, LOW);
  //delayMicroseconds(200);  

  ADC_1 = stableAnalogRead(TP1, 2000, 4); // 2 ms settle, average 4 samples
  ADC_2 = stableAnalogRead(TP2, 2000, 4);
  V1 = (ADC_1 * (5.0 / 1023.0));
  V2 = (ADC_2 * (5.0 / 1023.0));
  Vx = V1 - V2;

  /*if (Vx<=1.1){
    vref=1.1;
    analogReference(INTERNAL);
    delay(500);
    analogReference(INTERNAL);
    ADC_1 = analogRead(TP1);
    ADC_1 = ADC_1 + 1;
    Vx = (ADC_1 * 0.001074);
  }*/
  
  //analogReference(DEFAULT);
  //delay(500);
  //Serial.println("2nd");
  //Serial.println(V1);
  //Serial.println(V2);
  return Vx;

}

double checker_3(){
  a=R2; //470k
  b=R4; //470k
  //analogReference(DEFAULT);
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


  //Serial.println("3rd");
  //Serial.println(V1);
  //Serial.println(V2);
  return Vx;
 
 
}

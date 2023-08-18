double flow; //Water flow L/Min
int flowsensor = 2;
unsigned long currentTime;
unsigned long lastTime;
unsigned long pulse_freq;
double flow_2; //Water flow L/Min
int flowsensor_2 = 4;
unsigned long currentTime_2;
//const int AnalogPin=A0;
unsigned long lastTime_2;
unsigned long pulse_freq_2;
int diff=0;
const int analogInPin = A0;
int sensorValue = 0;
int outputValue = 0;
void pulse () // Interrupt function
{
   pulse_freq++;
   pulse_freq_2++;
}
   void setup()
 {
  pinMode(8,OUTPUT);
   pinMode(flowsensor, INPUT);
   Serial.begin(9600);
   attachInterrupt(0, pulse, RISING); // Setup Interrupt
   currentTime = millis();
   lastTime = currentTime;
   pinMode(flowsensor_2, INPUT);
   Serial.begin(9600);
   attachInterrupt(0, pulse, RISING); // Setup Interrupt
   currentTime_2 = millis();
   lastTime_2 = currentTime_2;
}
   void loop ()
{
   currentTime = millis();
   // Every second, calculate and print L/Min
   if(currentTime >= (lastTime + 1000))
   {
      lastTime = currentTime;
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      flow = (pulse_freq * 60 / 7.5);
      pulse_freq = 0; // Reset Counter
      Serial.print(flow, DEC);
      Serial.println(" L/Hr s1");
      currentTime_2 = millis();
      delay(1000);
   }
   // Every second, calculate and print L/Min
   if(currentTime_2 >= (lastTime_2 + 1000))
   {
      lastTime_2 = currentTime_2;
      // Pulse frequency (Hz) = 7.5Q, Q is flow rate in L/min.
      flow_2 = (pulse_freq_2 * 60 / 7.5);
      pulse_freq_2 = 0; // Reset Counter
      Serial.print(flow_2 , DEC);
      Serial.println(" L/Hr s2\n");
      delay(1000);
 
    }
    sensorValue = analogRead(analogInPin);
    outputValue=map(sensorValue,0,1053,0,255);
    Serial.print("Output = ");
    Serial.print(outputValue);
    Serial.print("\n");
    delay(1000);
    if(outputValue>50){
      digitalWrite(8,HIGH);
      delay(1000);
    }
    else{
      digitalWrite(8,LOW);
      delay(1000);
    }
   diff=flow-flow_2;
   if(diff!=0){
      Serial.println("\ndifference = ");
      Serial.print(diff ,DEC);
      digitalWrite(7,HIGH);
      if(8==HIGH){
        digitalWrite(8,LOW);
      }
   }
   else{
    digitalWrite(7,LOW);
   }
   delay(1000);

}

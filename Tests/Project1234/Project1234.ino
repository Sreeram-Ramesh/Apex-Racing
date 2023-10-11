const int Relay1_line1 = 35;
const int Relay1_line2 = 39;
const int Relay2_line1 = 45;
const int Relay2_line2 = 49;
const int D_to_T = 44; // 44 pin subject to checking.

void setup() {
  // put your setup code here, to run once:
  pinMode(Relay1_line1, OUTPUT);
  pinMode(Relay1_line2, OUTPUT);
  pinMode(Relay2_line1, OUTPUT);
  pinMode(Relay2_line2, OUTPUT);
  pinMode(D_to_T, INPUT);

  Serial.begin(9600);

  Serial.println("1 - DtoT switch");
  Serial.println("2 - TtoD relay");
  Serial.println("3 - Ignition relay");
  Serial.println("4 - Kill switch relay");
  Serial.println("5 - Extra relay");
}

void loop() {
  // put your main code here, to run repeatedly:

  int selection = 0;
  selection = Serial.read();

  switch(selection){

    case 1:
      
      int D_to_T_status;

      D_to_T_status = digitalRead(D_to_T);

      Serial.print("D_to_T switch status: ");
      
      if(D_to_T_status == HIGH){
        Serial.println("ON");
      }else{
        Serial.println("OFF");
      }

      break;

    case 2:

      digitalWrite(Relay1_line1, HIGH);
      delay(500);
      digitalWrite(Relay1_line1, LOW);
      delay(500);
      break;

    case 3:

      digitalWrite(Relay1_line2, HIGH);
      delay(500);
      digitalWrite(Relay1_line2, LOW);
      delay(500);
      break;

    case 4:

      digitalWrite(Relay2_line1, HIGH);
      delay(500);
      digitalWrite(Relay2_line1, LOW);
      delay(500);
      break;

    case 5:

      digitalWrite(Relay2_line2, HIGH);
      delay(500);
      digitalWrite(Relay2_line2, LOW);
      delay(500);
      break;

  }

}

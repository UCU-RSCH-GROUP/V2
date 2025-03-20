
int digit[7] = {13,12,11,10,9,8,7};
int in;

void setup(){
  Serial.begin(9600);
  pinMode(digit[7],OUTPUT);
  Serial.println("Board is Ready ");
    
}
/*
void ledCheck(int arr, int time){

  for(int i=0; i<=sizeof(digit[3]);i++){

    digitalWrite(digit[i],HIGH);
    digitalWrite(digit[i-1],LOW);
    delay(time)
  }

}*/

void loop(){
  

      for(int i=0; i<8;i++){

        digitalWrite(digit[i],HIGH);
        Serial.print("LED ");
        Serial.print(i);
        Serial.print(" is Working");
        Serial.print("\n");
        delay(1000);
        digitalWrite(digit[i],LOW);
        


      }/*

  }

  else if (in == 0){

    Serial.println(in);
    
    for(int i=0; i<=sizeof(digit[3]);i++){

      digitalWrite(digit[i],LOW);
    }

  }

  }*/
      }



/*
 * Code by Liam Kluempke
 * 
 * Emulation of the game Simon
 * 
 * All code is public domain
 */

//define button pins
#define butRed  8
#define butYel  9
#define butBlu  10
#define butGre  11

//define LED pins
#define ledRed  2
#define ledYel  3
#define ledBlu  4
#define ledGre  5

boolean state[4]; //last state of all 4 buttons

unsigned long lastMil = 0; //timer to prevent button bouncing

int order[20]; //keeps track of order of lights
int turn = 1; //turn number
int part = 0; //progress of current turn

boolean playing = true; //set to false when game has been lost/won

void setup() {
  pinMode(butRed, INPUT_PULLUP); //setup pins
  pinMode(butYel, INPUT_PULLUP);
  pinMode(butBlu, INPUT_PULLUP);
  pinMode(butGre, INPUT_PULLUP);

  pinMode(ledRed, OUTPUT);
  pinMode(ledYel, OUTPUT);
  pinMode(ledBlu, OUTPUT);
  pinMode(ledGre, OUTPUT);

  randomSeed(analogRead(0)); //get noise to set random seed

  for(int i=0; i<4; i++){ //set all states as false
    state[i] = false;
  }
  
  for(int i=0; i<=20; i++){ //set light order before game
    order[i] = random(2,6); // 2-6 set as pin numbers of LEDs
  }
}

void lightsOn(){ //turn all lights on
  for(int i = 2; i<=5; i++){
    digitalWrite(i, HIGH);
  }
}

void lightsOff(){ //turn all lights off
  for(int i = 2; i<=5; i++){
    digitalWrite(i, LOW);
  }
}

void loop() {
  if(playing && turn <=20){ //if the player has NOT won/lost yet
    for(int i=0; i<turn; i++){ //read colors at begining of turn
      digitalWrite(order[i], HIGH);
      delay(750);
      digitalWrite(order[i], LOW);
      delay(200);
    }

    while(part<turn){ //while current turn has not finished
      if(!digitalRead(butRed)!=state[0] && lastMil+50<millis()){ //if the button state has changed and it has been >50 ms since the last push (debounce)
        if(order[part]==ledRed && !state[0]){ //if correct button was pressed and the button was pushed down
          part++;
          digitalWrite(ledRed, HIGH); //turn light on while button is down
        }else if(!state[0]){ //if wrong button was pushed and the button was pushed down
          //failure (wrong button pressed)
          part=22; //end loop (doesn't matter what number is used as long as it's above 21)
          lightsOn();
          playing = false;
        } else { //if button was released turn off light
          digitalWrite(ledRed, LOW);
        }
        state[0] = !state[0]; //invert state
        lastMil = millis(); //reset lastMil for debounce
      } else if(!digitalRead(butYel)!=state[1] && lastMil+50<millis()){ //if the button state has changed and it has been >50 ms since the last push (debounce)
        if(order[part]==ledYel && !state[1]){ //if correct button was pressed and the button was pushed down
          part++;
          digitalWrite(ledYel, HIGH); //turn light on while button is down
        }else if(!state[1]){ //if wrong button was pushed and the button was pushed down
          //failure (wrong button pressed)
          part=22; //end loop (doesn't matter what number is used as long as it's above 21)
          lightsOn();
          playing = false;
        } else { //if button was released turn off light
          digitalWrite(ledYel, LOW);
        }
        state[1] = !state[1]; //invert state
        lastMil = millis(); //reset lastMil for debounce
      } else if(!digitalRead(butBlu)!=state[2] && lastMil+50<millis()){ //if the button state has changed and it has been >50 ms since the last push (debounce)
        if(order[part]==ledBlu && !state[2]){ //if correct button was pressed and the button was pushed down
          part++;
          digitalWrite(ledBlu, HIGH); //turn light on while button is down
        }else if(!state[2]){ //if wrong button was pushed and the button was pushed down
          //failure (wrong button pressed)
          part=22; //end loop (doesn't matter what number is used as long as it's above 21)
          lightsOn();
          playing = false;
        } else { //if button was released turn off light
          digitalWrite(ledBlu, LOW);
        }
        state[2] = !state[2]; //invert state
        lastMil = millis(); //reset lastMil for debounce
      } else if(!digitalRead(butGre)!=state[3] && lastMil+50<millis()){ //if the button state has changed and it has been >50 ms since the last push (debounce)
        if(order[part]==ledGre && !state[3]){ //if correct button was pressed and the button was pushed down
          part++;
          digitalWrite(ledGre, HIGH); //turn light on while button is down
        }else if(!state[3]){ //if wrong button was pushed and the button was pushed down
          //failure (wrong button pressed)
          part=22; //end loop (doesn't matter what number is used as long as it's above 21)
          lightsOn();
          playing = false;
        } else { //if button was released turn off light
          digitalWrite(ledGre, LOW);
        }
        state[3] = !state[3]; //invert state
        lastMil = millis(); //reset lastMil for debounce
      }
    }
    if(playing){ //delay lights for next turn so it looks prettier
      part = 0;
      turn++;
      delay(500);
      lightsOff();
      delay(500);
    }
  }else if(playing==21){ //game won, flash random lights
    part = random(2,6);
    digitalWrite(part, HIGH);
    delay(250);
    digitalWrite(part, LOW);
  }
}

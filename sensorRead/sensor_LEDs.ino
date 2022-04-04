//#include "state.h"
#define SOUND_SENSOR_PIN  5
#define SOUND_TRESHOLD    242
#define R1                12
#define R2                11
#define J1                10
#define J2                9
#define V1                8
#define V2                7

enum E_STATE {DFT, WSOUND, WPRESENCE};

//declaration variables globales
int broche = 7;
E_STATE state;

//declaration fonctions
void initLEDs();
void initSTATE();
int worm(int broche);
void sound();
int is_present();
void presence();
void message(E_STATE state, unsigned long wtime);
void flashR();
void flashJ();
void flashV();
void timer(int how_long, void( (*flash)() ) );

/*-----------main-------------*/

// the setup function runs once when you press reset or power the board
void setup() {
  initLEDs(); //initialisation des pins des leds
  initSTATE();  //init de la machine a etat
  Serial.begin(9600); //init serial connexion
  pinMode(5, INPUT);  //init pin capteur de son
}

// the loop function runs over and over again forever
void loop() {
  switch(state){
  case WPRESENCE :
  {
    unsigned long starttime = millis(); //heure de debut
    presence();
    while( is_present() ){ 
      presence();  
    }
    unsigned long endtime = millis(); //heure de fin
    unsigned long warningtime = endtime - starttime;  //calcul du temps en alerte
    message(state, warningtime);                      //envoie message
    if(analogRead(SOUND_SENSOR_PIN) > SOUND_TRESHOLD){ 
      state = WSOUND;  
    }
    else{
      state = DFT;
    }
  }
    break;
    
  case WSOUND :
  {
    unsigned long starttime = millis();
    sound();
    while(analogRead(SOUND_SENSOR_PIN) > SOUND_TRESHOLD &&  !is_present()){ // a modifier lorsqu'on aura les données du capteur de presence
      sound(); 
    }
    unsigned long endtime = millis();
    unsigned long warningtime = endtime - starttime;
    message(state, warningtime);
    if( is_present() ){
      state = WPRESENCE;
    }
    else{
      state = DFT;
    }
  }
    break;
    
  case DFT :
    broche = worm(broche);
    if( is_present() ){
      state = WPRESENCE;
      break;
    }
    else if((analogRead(SOUND_SENSOR_PIN) > SOUND_TRESHOLD) ){
      state = WSOUND; 
      break;
    }
    break;
  }
}

/*-----------init functions-------------*/
void initLEDs(){
  for(int i=7; i<=12; i++){
    pinMode(i, OUTPUT);
  }
}

void initSTATE(){
  if( is_present() ){
    state = WPRESENCE;
    }
  else if( (analogRead(SOUND_SENSOR_PIN) > SOUND_TRESHOLD) ) {
    state = WSOUND;
    }
  else{
    state = DFT;
    }
}

/*------------functions------------*/

//verification pour passage en mode presence
int is_present(){
  if( Serial.available() ){
    String data = "0";
    data = Serial.readStringUntil('\n');
    while(Serial.available()){Serial.read();} //flush serial buffer
    if(data.equals("1\n") || data.equals("1") || data == 1){ return 1; }
    else{ return 0; }
  }
}

//envoi des données d'alerte de son pour les logs
void message(E_STATE state, unsigned long wtime){
  Serial.print("Warning type: ");
  Serial.print(state);
  Serial.print(" ; Warning time: ");
  Serial.print(wtime);
  Serial.print(" ms\n");
}

//pilotage des LEDs en mode attente
int worm(int broche){
  digitalWrite(broche, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(250);                       // wait for a second
  digitalWrite(broche, LOW);    // turn the LED off by making the voltage LOW
  delay(250);                       // wait for a second
  
  if(broche<=7){
    return 12;
    }else return broche-1;
}

//pilotage des LEDs en mode alerte son
void sound(){
  flashR();
  flashV();
  
}

//pilotage des LEDs en mode alerte presence
void presence(){
  timer(5000, &flashJ);
  timer(2000, &flashR);
  timer(2000, &flashV);
  timer(1000, &flashR);

  flashJ();
 }

//flash LEDs rouges
void flashR(){
  digitalWrite(R1, HIGH);
  digitalWrite(R2, HIGH);
  delay(200);
  digitalWrite(R1, LOW);
  digitalWrite(R2, LOW);
  delay(200);
}

//flash LEDs jaunes
void flashJ(){
  digitalWrite(J1, HIGH);
  digitalWrite(J2, HIGH);
  delay(200);
  digitalWrite(J1, LOW);
  digitalWrite(J2, LOW);
  delay(200);
}

//flash LEDs vertes
void flashV(){
  digitalWrite(V1, HIGH);
  digitalWrite(V2, HIGH);
  delay(200);
  digitalWrite(V1, LOW);
  digitalWrite(V2, LOW);
  delay(200);
}

//mesure du temps d'alerte et pilotage des leds
void timer(int how_long, void( (*flash)() ) ){
  unsigned long starttime = millis();
  unsigned long endtime = starttime;
  while((endtime - starttime) < how_long){ // do loop for how_long second
    flash();
  endtime = millis();
  }
}

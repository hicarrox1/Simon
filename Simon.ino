//pin Definitions
int Redled=11;
int Yellowled=12;
int Greenled=13;
int Blueled=10;
int Errorled=9; 
int Key1=5; //Green button
int Key2=4; //Yellow button
int Key3=3; //Red button
int Key4=2; //Blue button

//variable to state of button
int key4State;
int key3State; 
int key2State;
int key1State;

//variable to avoids persistence
bool TouchRed;
bool TouchYellow;
bool TouchGreen;
bool TouchBlue;

//variable to color serie
int serie[50];
int index_serie = 0;
int index_dispo = 0;

//variable that acts as a return
bool test;
int led;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600);

  //set pin
  pinMode(Redled,OUTPUT);
  pinMode(Yellowled,OUTPUT);
  pinMode(Greenled,OUTPUT);
  pinMode(Blueled,OUTPUT);
  pinMode(Errorled,OUTPUT);
  pinMode(Key1,INPUT);
  pinMode(Key2,INPUT);
  pinMode(Key3,INPUT);
  pinMode(Key4,INPUT);

  //random first color in the serie
  randomSeed(analogRead(0));

  serie[0] = random(1,5);

  Serial.println(serie[0]);

  //display serie
  info_lumineuse();

}

void loop() {
  // put your main code here, to run repeatedly:

  //detect state of button
  key3State = digitalRead(Key3);
  key1State = digitalRead(Key1);
  key2State = digitalRead(Key2);
  key4State = digitalRead(Key4);

  //avoids persistence
  if (TouchRed == false && key3State == HIGH)
  {
    joue_couleur(1); //1 = red
    TouchRed = true;
  }
  else if(key3State == LOW)
  {
    TouchRed = false;
  }

if (TouchYellow == false && key2State == HIGH)
  {
     joue_couleur(2); //2 = yellow
    TouchYellow = true;
  }
  else if(key2State == LOW)
  {
    TouchYellow = false;
  }


if (TouchGreen == false && key1State == HIGH)
  {
    joue_couleur(3); //3 = green
    TouchGreen = true;
  }
  else if(key1State == LOW)
  {
    TouchGreen = false;
  }

if (TouchBlue == false && key4State == HIGH)
  {
    joue_couleur(4); //4 = blue
    TouchBlue = true;
  }
  else if(key4State == LOW)
  {
    TouchBlue = false;
  }

}

void joue_couleur(int color)
{

  test_couleur(color);

  if (test == true)
  {
    
    Serial.println("good color");
  
    // allume la lumière joue
    get_light_led(color);
    light_blink(led,300);

    index_serie ++;

    if (index_serie > index_dispo) // vérifie si on a atteint la fin de la série
    {
      
      if (index_serie <= 12)
      {
      
      //génère une nouvelle couleur dans la serie et l'affiche
      serie[index_serie] = random(1,5);

      Serial.println(serie[index_serie]);
      Serial.println("nouvelle");

      index_serie = 0;
      index_dispo ++; 
      info_lumineuse();
      }
    }
    
  }
  else{
    Serial.println("wrong color");
    error_light();
    index_serie = 0;
  }
}

void test_couleur(int color) // change test à true si la couleur en paramètre est la bonne 
{
  if (serie[index_serie] == color)
  {
    test = true;
  } else {
    test = false;
  }
}

void info_lumineuse() //affiche la série avec les lumières
{
  for (int i = 0; i <= index_dispo; i++)
  {
    get_light_led(serie[i]);
    light_blink(led,300);
  }
}

void error_light() // active la lumière d'erreur
{ 
  for (int i = 0; i < 4; i++)
  {
    light_blink(Errorled,200);
  }
}

void light_blink(int led,int time) //fait clignoter la lumière voulue le temps voulu
{
  digitalWrite(led,HIGH);
  delay(time);
  digitalWrite(led,LOW);
  delay(time);
}

void get_light_led(int number) // change led en fonction de la couleur en paramètre (1:red,2:yellox,3:green,4:blue) au pin de sa led
{
  if (number == 1) led = Redled;
  else if (number == 2) led = Yellowled;
  else if (number == 3) led = Greenled;
  else if (number == 4) led = Blueled;
}

void clear_led() // all LED off
{
digitalWrite(Redled,LOW);
digitalWrite(Greenled,LOW);
digitalWrite(Yellowled,LOW);
}
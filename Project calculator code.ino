/*
 * Arduino Keypad calculator Program
 */

#include <LiquidCrystal.h> //Header file for LCD from https://www.arduino.cc/en/Reference/LiquidCrystal
#include <Keypad.h> //Header file for Keypad from https://github.com/Chris--A/Keypad
#include <math.h>
#define pi 3.141592
int tempo = 100;
char notes[] = "eeeeeeegcde fffffeeeeddedg";
int duration[] = {1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2};
unsigned int buzzle = 14;



const byte ROWS = 4; // Four rows
const byte COLS = 4; // Three columns

// Define the Keymap
char keys[ROWS][COLS] = {

  {'7','8','9','D'},

  {'4','5','6','C'},

  {'1','2','3','B'},

  {'*','0','#','A'}

};

byte rowPins[ROWS] = { 0, 1, 2, 3 };// Connect keypad ROW0, ROW1, ROW2 and ROW3 to these Arduino pins.
byte colPins[COLS] = { 4, 5, 6, 7 }; // Connect keypad COL0, COL1 and COL2 to these Arduino pins.

Keypad kpd = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS ); //  Create the Keypad

const int rs = 8, en = 9, d4 = 10, d5 = 11, d6 = 12, d7 = 13; //Pins to which LCD is connected
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

 double Num1,Number,Test1=0; // for muti calculated
 long Num2;
 char key,action;
 unsigned int state=0;
  unsigned int state_a=0;
 char a[1]={'x'};
 unsigned int count=1;
 unsigned int Test2=0;
 unsigned int Test3=0;
 
 unsigned int gamemode=0;
 unsigned int stategame=0;
 unsigned int opG;
 long NumG1=0;
 long NumG2=0;
 long check=-1;
 unsigned int turn=0;
 unsigned int score=0;
 unsigned int statescore=0;
 
 boolean result = false;
 
void setup() {
  pinMode(buzzle,OUTPUT);
  lcd.begin(16, 2); //We are using a 16*2 LCD display
  lcd.print("DIY Calculator"); //Display a intro message
  lcd.setCursor(0, 1);   // set the cursor to column 0, line 1
  lcd.print("by Bas_3p"); //Display a intro message 
  action='*';
  // Scan each char from "notes"

  for (unsigned int i = 0; i<sizeof(notes)-20; i++) {
    if (notes[i] == ' ') {
      // If find a space it rests
      delay(duration[i] * tempo);
    } else {
      playTheShit(notes[i], duration[i] * tempo);
    }

    // Pauses between notes
    delay((tempo*2)*duration[i]);
  }
    randomSeed(analogRead(0));
    lcd.clear(); //Then clean it
  
}

void loop() {
  
key = kpd.getKey(); //storing pres  sed key value in a char

gameturn();

if (key!=NO_KEY)
{ tone(buzzle,700,100);
  if (state_a>0)
  {key='*';}
  if (statescore>0)
  {key='*';}
  DetectButtons();
  a[0]=key;
  }

if (result==true)
CalculateResult();

DisplayResult();   
}

void DetectButtons()
{   
     
     lcd.clear(); //Then clean it
     
    
 
    if (key=='*') //If cancel Button is pressed
    {Serial.println ("Button Cancel"); 
    if ((Number==0&&Num1==0&&Num2==0)&&(stategame==0))
    { if (Test3==0&&Test2==0)
      {Test3=1; Test2=0;}
      else if (Test3==1&&Test2==0)
      {Test3=0; Test2=1;}
      else if (Test3==0&&Test2==1)
      {Test3=0; Test2=0;}   
      }
    state_a=statescore=Number=Num1=Num2=0;
     check=-1;
    result=false;
    }
      
     if (key == '1') //If Button 1 is pressed
    {Serial.println ("Button 1"); 
    if (Number==0)
    Number=1;
    else
    Number = (Number*10) + 1; //Pressed twice
    if (Test3==1)
    {Number=Test3=Num1=Num2=0; state=1;}
    if (gamemode==1)
    {Number=gamemode=Num1=Num2=0; check=-1; stategame=turn=1;}
    }
    
     if (key == '4') //If Button 4 is pressed
    {Serial.println ("Button 4"); 
    if (Number==0)
    Number=4;
    else
    Number = (Number*10) + 4; //Pressed twice
    if (Test3==1)
    {Number=Test3=Num1=Num2=0; state=4;}
    }
    
     if (key == '7') //If Button 7 is pressed
    {Serial.println ("Button 7");
    if (Number==0)
    Number=7;
    else
    Number = (Number*10) + 7; //Pressed twice
    if (Test2==1)
    {Number=Test2=Num1=Num2=0; state=7;}
    } 
  

    if (key == '0')
    {Serial.println ("Button 0"); //Button 0 is Pressed
    if (Number==0)
    Number=0;
    else
    Number = (Number*10) + 0; //Pressed twice
    }
    
     if (key == '2') //Button 2 is Pressed
    {Serial.println ("Button 2");  
     if (Number==0)
    Number=2;
    else
    Number = (Number*10) + 2; //Pressed twice
     if (Test3==1)
    {Number=Test3=Num1=Num2=0; state=2;}
    if (gamemode==1)
    {Number=gamemode=Num1=Num2=0; check=-1; stategame=0;}
    }
    
     if (key == '5')
    {Serial.println ("Button 5"); 
     if (Number==0)
    Number=5;
    else
    Number = (Number*10) + 5; //Pressed twice
    if (Test2==1)
    {Number=Test2=Num1=Num2=0; state=5;}
    }
    
     if (key == '8')
    {Serial.println ("Button 8"); 
     if (Number==0)
    Number=8;
    else
    Number = (Number*10) + 8; //Pressed twice
    if (Test2==1)
    {Number=Test2=Num1=Num2=0; state=8;}
    }   
  

    if (key == '#')
    {Serial.println ("Button Equal"); 
    if (Num1==0&&Num2==0&&Number==0&&stategame==0)  //game mode
     {gamemode=1;score=0;}
     if (stategame==1)
     {turn=1;}
    if (state==0&&stategame==0)
    {if ((Num1==Test1)&&Num2!=0)
    Num1=Number;
    else
    Num2=Number;} 
    if (gamemode==0)
    result = true;
    if (state==1&&result==true)
     {if (Num1==0)
      {result=false;
      Num1=Number; 
      Number=0; 
      Num2=0;}
      else
      Num2=Number; 
      }
      if ((Number>0)&&(state==2)&&(result==true))
     {
      Num1=Number; 
      Number=0; 
      }
      if ((Number>0)&&(state==3)&&(result==true))
     {
      Num1=Number; 
      Number=0; 
      }
      if ((Number>0)&&(state==4)&&(result==true))
     {
      Num1=Number; 
      Number=0; 
      }
      if ((Number>0)&&(state==5)&&(result==true))
     {
      Num1=Number; 
      Number=0; 
      }
      if ((Number>0)&&(state==6)&&(result==true))
     {
      Num1=Number; 
      Number=0; 
      }
      if ((Number>0)&&(state==7)&&(result==true))
     {
      Num1=Number; 
      Number=0; 
      }
      if ((Number>0)&&(state==8)&&(result==true))
     {
      Num1=Number; 
      Number=0; 
      }               
    }
    
    
     if (key == '3')
    {Serial.println ("Button 3"); 
     if (Number==0)
    Number=3;
    else
    Number = (Number*10) + 3; //Pressed twice
    if (Test3==1)
    {Number=Test3=Num1=Num2=0; state=3;}
    }
    
     if (key == '6')
    {Serial.println ("Button 6"); 
    if (Number==0)
    Number=6;
    else
    Number = (Number*10) + 6; //Pressed twice
    if (Test2==1)
    {Number=Test2=Num1=Num2=0; state=6;}
    }
    
     if (key == '9')
    {Serial.println ("Button 9");
    if (Number==0)
    Number=9;
    else
    Number = (Number*10) + 9; //Pressed twice
    }  

      if ((key == 'A' || key == 'B' || key == 'C' || key == 'D')&&stategame==0) //Detecting Buttons on Column 4
  {
    
   
      
    
    if (key == 'A')
    {Serial.println ("Addition"); action = '+';}
     if (key == 'B')
    {Serial.println ("Subtraction"); action = '-'; }
     if (key == 'C')
    {Serial.println ("Multiplication"); action = '*';}
     if (key == 'D')
    {Serial.println ("Devesion"); action = '/';}  
   
     
     if ((a[0] == 'A' || a[0] == 'B' || a[0] == 'C' || a[0] == 'D')&&(Num1!=0))
      {Num1=Num1;  result=false;}
      if (a[0]== '#'||(Num1==0&&Num2==0)) 
    {Num1=Number; Num2=0;  Test2=0; result=false;}
    
    
    Number=0;
    delay(100);

}
}

void CalculateResult()
{
  
  Test1 = Num1; // save previous data for determine process
  
  
  if (state==0&&state_a==0)
  {
  if (action=='+')
    { if (stategame==1)
      {check=NumG1+NumG2;
       if (check==Number)
       score++;
      }
      else
      Number = Num1+Num2;
    }

  if (action=='-')
    {if (stategame==1)
      {check=NumG1-NumG2;
       if (check==Number)
       score++;
      }
      else
      Number = Num1-Num2;
    }

  if (action=='*')
    {if (stategame==1)
      {check=NumG1*NumG2;
       if (check==Number)
       score++;
      }
      else
      Number = Num1*Num2;
    }

  if (action=='/')
    {if (stategame==1)
      {check=NumG1/NumG2;
       if (check==Number)
       score++;
      }
      else
      Number = Num1/Num2;
    }        
    }
  else if (state==1)
  {Number=pow(Num1,Num2);
   state=0;state_a=1;} 
  else if (state==2)
  {Number=sqrt(Num1);
   state=0;state_a=2;} 
  else if (state==3)
  { Number=exp(Num1);
   state=0;state_a=3;} 
  else if (state==4)
  {Number=log(Num1);
   state=0; state_a=4;}
   else if (state==5)
  { Num1=(pi/180.0)*Num1;
    Number=sin(Num1);
   state=0;state_a=5;} 
  else if (state==6)
  {Num1=(pi/180.0)*Num1;
    Number=cos(Num1);
   state=0;state_a=6;} 
  else if (state==7)
  { Num1=(pi/180.0)*Num1;
    Number=tan(Num1);
   state=0;state_a=7;} 
  else if (state==8)
  {Number=log10(Num1);
   state=0; state_a=8;}

   if (stategame==1)
   {result=false; count++;}
   
    
}

void DisplayResult()
{ if (Test3==1)
  statedisplay();
  else if (Test2==1)
  statedisplay2();
  else if (gamemode==1)
  gamedisplay();
  else if (statescore==1)
  scoredisplay();
  else
  {lcd.setCursor(0, 0);   // set the cursor to column 0, line 0
  if (state==1||state_a==1)
  {lcd.print(Num1); 
  lcd.print("^"); 
  lcd.print(Num2);} 
  else if (state==2||state_a==2)
  {lcd.print(Num1); 
  lcd.print("^1/2"); 
   } 
  else if (state==3||state_a==3)
  { lcd.print("exp");
    lcd.print(Num1); 
   } 
  else if (state==4||state_a==4)
  {lcd.print("ln");
   lcd.print(Num1);  
   }  
  else if (state==5||state_a==5)
  {lcd.print("sin");
   lcd.print(Num1);  
   }
   else if (state==6||state_a==6)
  {lcd.print("cos");
   lcd.print(Num1);  
   } 
   else if (state==7||state_a==7)
  {lcd.print("tan");
   lcd.print(Num1);  
   } 
   else if (state==8||state_a==8)
  {lcd.print("log10(");
   lcd.print(Num1);  
   lcd.print(")");
   }
   else if (stategame==1)
   {
    lcd.print(NumG1); 
     lcd.print(action); 
      lcd.print(NumG2);
    }   
  else
  {lcd.print(Num1); 
  lcd.print(action); 
  lcd.print(Num2);}

   if (stategame==1)
  {lcd.setCursor(13,0);
    lcd.print(count); lcd.print("/5");
    }
    
  if (result==true)
   {lcd.setCursor(0, 1); lcd.print(" ="); lcd.print(Number);} //Display the result

  else
  {lcd.setCursor(0, 1);   // set the cursor to column 0, line 1
  lcd.print(Number);}
  } //Display the result
}
void playTheShit(char note, int duration) 
{
  char notesName[] = { 'c', 'd', 'e', 'f', 'g' };
  int tones[] = { 261, 293, 329, 349, 392 };
  for (int i = 0; i<= sizeof(tones); i++) {
    // Bind the note took from the char array to the array notesName
    if (note == notesName[i]) {
      // Bind the notesName to tones
      tone(buzzle, tones[i], duration);}}}

void statedisplay()
{
  
  
  lcd.setCursor(0, 0);
  lcd.print("1.Pow()"); lcd.print(" 2.Sqrt()"); 
  lcd.setCursor(0, 1);
  lcd.print("3.exp()"); lcd.print(" 4.ln()"); 

  
  
  }
 void statedisplay2()
{
  
  
  lcd.setCursor(0, 0);
  lcd.print("5.sin()"); lcd.print(" 6.cos()"); 
  lcd.setCursor(0, 1);
  lcd.print("7.tan()"); lcd.print("8.log10()"); 

  
  
  }
  void gamedisplay()
  {
    lcd.setCursor(0, 0);
    lcd.print("Continued ?");
    lcd.setCursor(0, 1);
    lcd.print("1.Yes"); lcd.print(" 2.No"); 
    
    }
    void gameturn()
    {   if (count==6)
        {stategame=0; turn=0; count=1; statescore=1;lcd.clear();}
      if (stategame==1&&turn==1)
    {  opG=random(1,5); // random operator
          
          
          if (opG<3)
        {  NumG1=random(1111,9999);
           NumG2=random(105,999);
           if (opG==1)
           action = '+';
           else
           action = '-';
        }
          else if (opG==3)
        {NumG1=random(25,50);
          NumG2=random(1,20);
          action = '*';
            }
          else if (opG==4)
       { NumG1=random(11,45);
        NumG2=random(51,312);
        NumG1=NumG1*NumG2;
        action = '/';
       }
    turn=0; Number=0; lcd.clear();
  }
  
      }
  void scoredisplay()
      {
        if (statescore==1)
      { lcd.setCursor(0,0);
         lcd.print("Your score "); lcd.print(score);
     if (score==0)
     {lcd.setCursor(0, 1); lcd.print("Chicken !!");}
     else if (score==1)
     {lcd.setCursor(0, 1); lcd.print("Cheer up !!");}
     else if (score==2)
     {lcd.setCursor(0, 1); lcd.print("Just so so");}
     else if (score==3)
     {lcd.setCursor(0, 1); lcd.print("OK, Fine");}
     else if (score==4)
     {lcd.setCursor(0, 1); lcd.print("A little bit *w*");}
     else if (score==5)
     {lcd.setCursor(0, 1); lcd.print("U are Insane");}
     
      }
        } 

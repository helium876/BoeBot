#include <Servo.h>

Servo right;
Servo left;


//**************************************//
//      Declaration of the IRF PINs     //
//**************************************//
#define IRL_PIN_s0  4//22
#define IRL_PIN_s1  5//23
#define IRL_PIN_s2  6//24
#define IRL_PIN_s3  7//25
#define IRL_PIN_s4  8//26
#define IRL_PIN_s5  9//27
#define IRL_PIN_s6  10//28
#define IRL_PIN_s7  11//29


void setup(){
    Serial.begin(9600); //Opens serial connection at 9600 baud rate
    right.attach(2);
    left.attach(3);
    
    left.write(90);
    right.write(90);
}

int IRL_in; 
// declaration of the buffer to store the output of all  s0- s7 pins of the KRF


void loop()
{
  IRL_Read();
  switch(IRL_in)
  {
    case 0b11111111: //off the line
    break;
    
    case 0b00000000: /// in a box
    break;
    
    case 0b11000011: 
    //case 0b11000111: 
    //case 0b11100011: 
    //case 0b10000001: //forward
        forward();
        break;

    case 0b11110001: 
    case 0b11100001: 
    case 0b11110000: 
    case 0b11111000: 
    case 0b11111100: 
    case 0b11111110: //right curve
        rightcurve();
        break;

    case 0b10000000:
    case 0b11000000:
    case 0b11100000:
        //do{
            rightturn();
            delay(200);
            IRL_Read();
        //}while(IRL_in != 0b11110000);
        
        break;

    case 0b00000001:
    case 0b00000011:
    case 0b00000111:
    case 0b00001111:
        //do{
            leftturn();
            delay(200);
            IRL_Read();
        //}while(IRL_in != 0b00001111);

        break;
   
 
    case 0b10000111:
    case 0b00011111: 
    case 0b00111111:
    case 0b01111111: //right curve
        leftcurve();
        break;

    //default:
        //forward();
       // break;
    
  }
    
}

void stop(){
    right.write(90);
    left.write(90);
}

void forward(){
    right.write(0);//Move forward
    left.write(180);//Move forward
}

void rightcurve(){
    Serial.println("Right Curve");
        right.write(130);//180
        left.write(180);//90
    
}

void rightturn(){
    Serial.println("Right Turn");
    //right.write(90);
    //left.write(90);
    right.write(180);
    left.write(180);
    }

void leftcurve(){
    Serial.println("Left Curve");
    right.write(0);
    left.write(45);
}

void leftturn(){
    Serial.println("Left Turn");
    //right.write(90);
    //left.write(90);
    right.write(0);
    left.write(0);
}

void IRL_Read()
{
    IRL_in = 0;
    
    for(int i = 0; i <= 7; i++){
        IRL_in = (IRL_in << 1) + digitalRead(IRL_PIN_s7 - i);
    }
    Serial.println(IRL_in, BIN);
}

#include <Wire.h> 
 
#define address 0x1E 
byte stun_gun[10][10]=
{
  {2,3,4,5,6,8},
  {3,4},
  {2,3,5,6,7},
  {2,3,4,5,7},
  {3,4,7,8},
  {2,4,5,7,8},
  {2,4,5,6,7,8},
  {2,3,4,8},
  {2,3,4,5,6,7,8},
  {2,3,4,7,8}
}; 
byte stun_gun2[10][10]=
{
  {9,11,12,13,20,21},
  {13,20},
  {10,11,12,20,21},
  {10,12,13,20,21},
  {9,10,13,20},
  {9,10,12,13,21},
  {9,10,11,12,13,21},
  {9,13,20,21},
  {9,10,11,12,13,20,21},
  {9,10,13,20,21}
};

int i,j,l,m;
void setup(){
  int k;
  Serial.begin(9600);
  Wire.begin();
 
  Wire.beginTransmission(address); 
  Wire.write(0x02); 
  Wire.write(0x00); 
  Wire.endTransmission();
  for(i=2;i<=13;i++)
  {
    pinMode(i,OUTPUT);
  }
  pinMode(A0,OUTPUT);
  pinMode(A1,OUTPUT);
}
void turn_off()
{
  int k;
  for(k=2;k<=8;k++) digitalWrite(k,HIGH);
}
void turn_off2()
{
  int k;
  for(k=9;k<=13;k++) digitalWrite(k,HIGH);
  digitalWrite(A0,HIGH);
  digitalWrite(A1,HIGH);
}

void loop(){
 
  int x,y,z;
  int xx,yy,zz;
  byte tmp;
  Wire.beginTransmission(address);
  Wire.write(0x03);
  Wire.endTransmission();

  Wire.requestFrom(address, 6);

  if(6<=Wire.available()){
    x = Wire.read()<<8;
    x |= Wire.read();
    z = Wire.read()<<8;
    z |= Wire.read();
    y = Wire.read()<<8;
    y |= Wire.read();
  }
  if(abs(xx-x)>=180 && abs(yy-y)>=180 && abs(zz-z)>=180)
  {
    turn_off();
    ++i;
    i%=10;
    if(i==0)
    {
        ++m;
        m%=10;
        turn_off2();
        while(stun_gun2[m][l]!=0) 
        {
          if(stun_gun2[m][l]==20) digitalWrite(A0,LOW);
          else if(stun_gun2[m][l]==21) digitalWrite(A1,LOW);
          else digitalWrite(stun_gun2[m][l],LOW);
          ++l;
        }
        l=0;
    }
    while(stun_gun[i][j]!=0) digitalWrite(stun_gun[i][j++],LOW);
    j=0;
    Serial.print("      ");
  } 
  xx=x;
  yy=y;
  zz=z;
  Serial.print("x: ");
  Serial.print(x);
  Serial.print("  y: ");
  Serial.print(y);
  Serial.print("  z: ");
  Serial.println(z);
 
  delay(250);
}


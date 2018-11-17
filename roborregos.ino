#include <Ultrasonic.h>

  int fase2[5][2];
  int fase2x=1;
  int fase2y=0;
  boolean positivox=false;
  boolean positivoy=true;
  boolean negativox=false;
  boolean negativoy=false;
int derecha1= 23; 
int derecha2= 22;
const int S0 = 12;  
const int S1 = 13;  
const int S2 = 11;  
const int S3 = 10;  
const int out = 9;  
int frecuenciaRoja = 0;
int frecuenciaVerde = 0;
int frecuenciaAzul = 0;
int rojo = 0;
int azul = 0;
int verde = 0;
int LEDA=7;
int LEDV=6;
int LEDR=5;
int LEDAM = 4;
char color = '0';
const int fotoResistor1 = A2;
const int fotoResistor2 = A3; //Pin del LDR
int V1;
int V2;
int izquierda1= 24; 
int izquierda2= 25;
//FRENTE
const int Trigger1 = 44;  
const int Echo1 = 45;
//DERECHA   
const int Trigger3 = 46;  
const int Echo3 = 48;   //Pin digital 3 para el echo del sensor
//IZQUIERDA   
const int Trigger2 = 50;   //Pin digital 2 para el Trigger del sensor
const int Echo2 = 52;   //Pin digital 3 para el echo del sensor

int potenciamotor1=3;
int potenciamotor=2;
int fase=1;
int rampa=0;
bool derecha=false;
int count=0;
int primerCuenta = 0;
int segundaCuenta = 0;

boolean anteriorI = 0;    
boolean actualI = 0; 
int contadorI = 0; 
int sensorEncoderI = 19;
boolean anteriorD = 0;    
boolean actualD = 0; 
int contadorD = 0; 
int sensorEncoderD =18 ;
int countbola=0;
boolean atrasAlgo = false;



void setup()
{
  Serial.begin(9600);
  pinMode (derecha1, OUTPUT);   
  pinMode (derecha2, OUTPUT);   
  pinMode (izquierda1, OUTPUT);   
  pinMode (izquierda2, OUTPUT);  
  pinMode(potenciamotor,OUTPUT);
    pinMode(potenciamotor1,OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
   pinMode(out, INPUT);
   digitalWrite(S0,HIGH);
  digitalWrite(S1,LOW);
   pinMode(LEDR, OUTPUT);
  pinMode(LEDV, OUTPUT);
  pinMode(LEDA, OUTPUT);
 
  for(int i=0;i<5;i++)
    for(int j=0;j<2;j++)
    fase2[i][j]=0;
    
  pinMode(Trigger1, OUTPUT); //pin como salida
  pinMode(Echo1, INPUT);  //pin como entrada
  pinMode(Trigger2, OUTPUT); //pin como salida
  pinMode(Echo2, INPUT);  //pin como entrada
  pinMode(Trigger3, OUTPUT); //pin como salida
  pinMode(Echo3, INPUT);  //pin como entrada
  
  
  pinMode(sensorEncoderI,INPUT_PULLUP);
   pinMode(sensorEncoderD,INPUT_PULLUP);
   attachInterrupt(digitalPinToInterrupt(sensorEncoderI),cambioEncoderI, CHANGE);
   attachInterrupt(digitalPinToInterrupt(sensorEncoderD),cambioEncoderD, CHANGE);        

}

void cambiarpotenciamotores(int x,int dif){

    analogWrite(potenciamotor,x);
    
    analogWrite(potenciamotor1,x-dif);
  
}
void avanzar(){

  cambiarpotenciamotores(130,40);
  while(contadorI<30 && contadorD<25){
   digitalWrite(derecha1, HIGH);
   digitalWrite(derecha2, LOW);
   digitalWrite(izquierda2, LOW);
   digitalWrite(izquierda1, HIGH);
  }
  contadorI = 0;
  contadorD = 0;
  
}


void avanzarFase2(){

  cambiarpotenciamotores(90,18);
   digitalWrite(derecha2, LOW);
   digitalWrite(derecha1, HIGH);
   digitalWrite(izquierda1, HIGH);
   digitalWrite(izquierda2, LOW);
}
void atras(){
  
   cambiarpotenciamotores(180,50);
  
   digitalWrite(derecha1, LOW);
   digitalWrite(derecha2, HIGH);
   digitalWrite(izquierda2, HIGH);
   digitalWrite(izquierda1, LOW);
  delay(1000);
  contadorI = 0;
  contadorD = 0;
}
void avanzarPoquito(){

cambiarpotenciamotores(90,23);
while(contadorI<7 && contadorD<5){
   digitalWrite(derecha2, LOW);
   digitalWrite(derecha1, HIGH);
   digitalWrite(izquierda1, HIGH);
   digitalWrite(izquierda2, LOW);
}
contadorI = 0;
contadorD = 0;
 
}

void atrasPoquito(){
cambiarpotenciamotores(90,18);

while(contadorI<7 && contadorD<5){
 digitalWrite(derecha1, LOW);
   digitalWrite(derecha2, HIGH);
   digitalWrite(izquierda2, HIGH);
   digitalWrite(izquierda1, LOW);
   }
  contadorI = 0;
  contadorD = 0;

}

void giroejeL(){
 
  if(getDistanceR()<15){
        atrasAlgo = true;
     }
 
    cambiarpotenciamotores(250,80);
  while(contadorI<=20 && contadorD<23){
   digitalWrite(derecha2, HIGH);
   digitalWrite(derecha1, LOW);
   digitalWrite(izquierda1, HIGH);
   digitalWrite(izquierda2, LOW);
  }
    contadorI = 0;
  contadorD = 0;
  
  if (atrasAlgo){
    
      Detener();
      atras();
      Detener();
      avanzarPoquito();
      Detener();
  }
  

   atrasAlgo= false;
   
}
void giroejeR(){

     if(getDistanceL()<15){
        atrasAlgo = true;
      
     }
    
   cambiarpotenciamotores(170,-80) ;
   while(contadorI<=23 && contadorD<20){
   digitalWrite(derecha2, LOW);
   digitalWrite(derecha1, HIGH);
   digitalWrite(izquierda1, LOW);
   digitalWrite(izquierda2, HIGH);
   }
   Detener();
   contadorI = 0;
  contadorD = 0;
  
   if (atrasAlgo){
      
      atras();
      Detener();
      avanzarPoquito();
      Detener();
  }
  atrasAlgo = false;

}

int Detener(){
  cambiarpotenciamotores(0,0);
   delay(600);
  contadorI = 0;
  contadorD = 0;
}



boolean encoderI(boolean anteriorI) {
  delay(1);

   actualI = digitalRead(sensorEncoderI);
      if (anteriorI != actualI){
            delay(6);
            actualI = digitalRead(sensorEncoderI);
      }
   return actualI;
 }
   
boolean encoderD(boolean anteriorD) {
  delay(1);
 actualD = digitalRead(sensorEncoderD);
   if (anteriorD != actualD) {
      delay(6);
      actualD = digitalRead(sensorEncoderD);
   }
   return actualD;
} 
 
void cambioEncoderI(){
  
  actualI = encoderI(anteriorI); 
  

  if ( anteriorI == 0 && actualI == 1) {
         contadorI++;              
        
         Serial.println("Izquierda");          
         Serial.println(contadorI);
  }
  
    anteriorI = actualI;  
}

void cambioEncoderD(){
  
  actualD = encoderD(anteriorD); 
  

  if ( anteriorD == 0 && actualD == 1) {
         contadorD++;              
      
         Serial.println("Derecha");  
         Serial.println(contadorD);
  }
  
    anteriorD = actualD; 
}

boolean atras1=false;

void MovimientoUnidadDelayFASE1(){

   if(getDistanceF()>12){
   avanzar();
    Detener(); 
  
   
 }
 
 
    if(getDistanceF()<=12){
      Detener();
      
      if((getDistanceL()<15) && (getDistanceR()<15)){
        giroejeR();
        Detener();
     
        }
        
        else if(getDistanceL()<25){
          
          giroejeR();
          Detener();

          
          }
          
          else{
            giroejeL();
            Detener(); 
          
          }
    }

}

void MovimientoUnidadDelayFASE2(){
  Serial.print("Posx:");
  Serial.println(fase2x);
  Serial.print("Posy:");
  Serial.println(fase2y);
  
  if(fase2[fase2x][fase2y]!=1 && !(fase2x==0 && positivoy) ){
        giroejeLFASE2(); 
        Detener();
    }
    
    if(fase2x==0 && fase2y==4 && positivoy){
           giroejeLFASE2(); 
            Detener();
            avanzar();
            Detener();
            fase++;
            return;
         }
   if(getDistanceF()>15){
  
  while(contadorI<30 && contadorD<25 && !sensorLinea()){
   
   cambiarpotenciamotores(130,40);
   digitalWrite(derecha1, HIGH);
   digitalWrite(derecha2, LOW);
   digitalWrite(izquierda2, LOW);
   digitalWrite(izquierda1, HIGH);
    }
    Detener();
    if(contadorD>21 || contadorI>=25){
        if(positivox){
          fase2x++;      
          }else if(negativox){
            fase2x--;  
            }else if(negativoy){
              fase2y--;
              }else{
                fase2y++;
                } 
      }
     contadorI = 0;
    contadorD = 0;
      if(sensorLinea()){
        
                 avanzarPoquito();
                 Detener();
                 if(!sensorLinea()){
                 fase2[fase2x][fase2y]=1;
                 atrasPoquito();
                 Detener();
                 giroejeRFASE2();   
                    Detener();
                    }
        }else{
           giroejeRFASE2();  
           Detener(); 
          }
  
      
}else {
  fase2[fase2x][fase2y]=1;
   giroejeRFASE2(); 
   Detener();
  }

}
void giroejeLFASE2(){
  giroejeL();
         if(positivox){
          positivoy=true;
          positivox=false;
          }else if(negativox){
            negativoy=true;
            negativox=false;
            }else if(negativoy){
              positivox=true;
              negativoy=false;
              }else{
                negativox=true;
                positivoy=false;
                }
  }
void   giroejeRFASE2(){
      giroejeR();
         
         if(positivox){
          negativoy=true;
          positivox=false;
          }else if(negativox){
            positivoy=true;
            negativox=false;
            }else if(negativoy){
              negativox=true;
              negativoy=false;
              }else{
                positivox=true;
                positivoy=false;
                }
  }
  int direcciony=0;
  int direccionx=0;

  

int getDistance(int t1,int ec1){
     long t; //timepo que demora en llegar el eco
      long d; //distancia en centimetros
      //Enviamos un pulso de 10us
      digitalWrite(t1, LOW);
       delayMicroseconds(2);  
      digitalWrite(t1, HIGH);
      delayMicroseconds(10);     //Enviamos un pulso de 10us
      digitalWrite(t1, LOW);
      
      t = pulseIn(ec1, HIGH); //obtenemos el ancho del pulso
       d = t/59; 
       return d;
  }
int getDistanceF(){
     return getDistance(Trigger1,Echo1);
    }
    
int getDistanceR(){
     return getDistance(Trigger2,Echo2);
    }
    
int getDistanceL(){
     return getDistance(Trigger3,Echo3);
    }
    
void MovimientoLaberinto(){
    
   if(getDistanceR() <15){
      if (getDistanceF() >25){
        avanzar();
        Detener();
        
      }else{
        
        giroejeL();
        Detener();

      }
   }else{
    
    if (getDistanceL()<15){
    giroejeR();
    Detener();
   
    avanzar();
    Detener();
    }
    
    else{
      giroejeR();
      Detener();
      avanzar();
      Detener();
    }
   }
   
}


void calibrarcolor(){
     //CALIBRACION
        
         //COLOR ROJO 
         
           digitalWrite(S2,LOW);
           digitalWrite(S3,LOW);
         
           frecuenciaRoja = pulseIn(out, LOW);
         
           Serial.print(" R = ");
           Serial.print(frecuenciaRoja);
           delay(500);
        
          //VERDE
          
           digitalWrite(S2,HIGH);
           digitalWrite(S3,HIGH);
        
           frecuenciaVerde = pulseIn(out, LOW);
           
           Serial.print(" V = ");
           Serial.print(frecuenciaVerde);
           delay(500);
        
          //AZUL
           digitalWrite(S2,LOW);
           digitalWrite(S3,HIGH);
          
           frecuenciaAzul = pulseIn(out, LOW);
           
           Serial.print(" A = ");
           Serial.println(frecuenciaAzul);
           delay(500);
        
          // Constrains??
            }
char getColor(){
          digitalWrite(S2,LOW);
          digitalWrite(S3,LOW);
           digitalWrite(LEDR,LOW);
           digitalWrite(LEDA,LOW);
            digitalWrite(LEDV,LOW);
               digitalWrite(LEDAM,LOW);
          // Se lee el valor de la frecuencia 
          frecuenciaRoja = pulseIn(out, LOW);
          
         // Filtro para que no tome valores más grandes que los máx y mínimos
        if(frecuenciaRoja>80 || frecuenciaRoja<35){
          rojo = 0;
         }
         
         // Si el valor entra en el rango, hace un map de los valores
         if (frecuenciaRoja>=35 && frecuenciaRoja<=80){
          rojo  = map(frecuenciaRoja,35,80,255,0);
         }
        
          // Ajustando los filtros verdes de los fotodiodos para que sean leídos 
          digitalWrite(S2,HIGH);
          digitalWrite(S3,HIGH);
         
          // Se lee el valor de la frecuencia 
        frecuenciaVerde = pulseIn(out, LOW);
        
         // Filtro para que no tome valores más grandes que los máx y mínimos
          if(frecuenciaVerde>106 || frecuenciaVerde<42){
          verde = 0;
         }
         
         // Si el valor entra en el rango, hace un map de los valores
         if (frecuenciaVerde>=42 && frecuenciaVerde<=106){
          verde = map(frecuenciaVerde,42,106,255,0);
         }
         
          // Ajustando los filtros azules de los fotodiodos para que sean leídos 
          digitalWrite(S2,LOW);
          digitalWrite(S3,HIGH);
          
          // Se lee el valor de la frecuencia
          frecuenciaAzul = pulseIn(out, LOW);
        
        // Filtro para que no tome valores más grandes que los máx y mínimos
        if(frecuenciaAzul>140 || frecuenciaAzul<50){
          azul = 0;
         }
         
         // Si el valor entra en el rango, hace un map de los valores
         if (frecuenciaAzul>=50 && frecuenciaAzul<=140){
          azul = map(frecuenciaAzul,50,140,255,0);
         }

      if (frecuenciaAzul>=52 && frecuenciaAzul<=105 && frecuenciaVerde>=27 && frecuenciaVerde<=72 && frecuenciaRoja>=19 && frecuenciaRoja<=50){
         Serial.println("¡Color Amarillo!");
            color = 'y';
            
              digitalWrite(LEDAM,HIGH);
            
            return color;
         }
       
        Serial.print(" R = ");
         Serial.print(rojo);
          Serial.print("  ");
         
         Serial.print(" A = ");
         Serial.print(azul);
          Serial.print("  ");
         
         Serial.print(" V = ");
         Serial.print(verde);
        
        //Impresion de los valores de cada color
       

               if (rojo>azul && rojo>verde){
                digitalWrite(LEDR,HIGH);
          Serial.println("¡Color Rojo!");
          color = 'r';
           return color;
          delay(200);
          }
          
          if (azul>rojo && azul>verde){
            digitalWrite(LEDA,HIGH);
            Serial.println("¡Color Azul!");
            color = 'a';
             return color;
              delay(200);
              
          }
          
          if (verde>rojo && verde>azul){
            digitalWrite(LEDV,HIGH);
            Serial.println("¡Color Verde!");
            color = 'v';
             return color;
             
              delay(200);
          }
          
         

          
            return color;
    }
 void rampa1(){
  cambiarpotenciamotores(200,50);
   digitalWrite(derecha2, LOW);
   digitalWrite(derecha1, HIGH);
   digitalWrite(izquierda1, HIGH);
   digitalWrite(izquierda2, LOW);
   delay(12000);
 }
bool sensorLinea(){

 V2 = analogRead(A0);
  Serial.print("2-->");
  Serial.println(V2);
  
  if((V2 > 415)){
    return true;
  }
  else{
    return false;
  }
}     
bool sensorbola(){
   
  int value = 0;  
  int time = pulseIn(37,LOW);  
  if(time>2000) // Checking if the Start Bit has been received. Start Bit Duration is 2.4ms  
  {  
   for(int counter1=0;counter1<12;counter1++) // A loop to receive the next 12 bits  
   {  
    if(pulseIn(37,LOW)>1000) // checking the duration of each pulse, if it is a '1' then we use it in our binary to decimal conversion, '0's can be ignored.  
    {  
     value = value + (1<< counter1);// binary to decimail conversion. 1<< i is nothing but 2 raised to the power of i  
    }  
   }  
  }
  //Serial.println(time);
  if(time!=0)
    return true;

          return false;
}


void loop()
{   
  
 delay(2000);

  if(getColor()=='a'){
    fase=2;
    }else if(getColor()=='y'){
     fase=1;
      }else if (getColor() == 'r'){
        fase = 4
      }
      else{
        fase=3;
        }

 Serial.println("Fase: ");
 Serial.print(fase);
 
  if(fase==1){
      avanzar();
      Detener();

      boolean sensorbola1=false;
      while(countbola<5){
        if(sensorbola()){
          sensorbola1=true;
          }
        delay(100);
        countbola++;
        }
        if(sensorbola1){
            giroejeR();
        }
        else{
          giroejeL();
        }
          
      while(getColor()!='v') {
        MovimientoUnidadDelayFASE1();
     //   Detener();  
            
      }
           fase++;
  }
  Serial.println("Fase: ");
 Serial.print(fase);
 while(fase==2){      
       
             MovimientoUnidadDelayFASE2();
 }
 Serial.println("Fase: ");
 Serial.print(fase);
    while(fase==3){
      MovimientoLaberinto();

      if(getColor()=='r'){
          giroejeR();
          Detener();
          break;
      }
   }
   if (fase == 4){
      rampa1();
   }
}

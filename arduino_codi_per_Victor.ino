/*Per VICTOR MARIN
victorjajalolxd@gmail.com
Pots utilitzar i modificar aquest codi
sempre i quan es respecti el nom de l'autor original*/


//Assignació de pins

//Motor 1

int motor1pin1 = 8; //asignem el pin 8 digital a al motor 1 cap endavant
int motor1pin2 = 3; // asignem el pin 3 digital a al motor 1 cap enrere

//Motor 2

int motor2pin1 = 4; //asignem el pin 4 digital a al motor 2 cap endavant
int motor2pin2 = 5; //asignem el pin 8 digital a al motor 2 cap enrere

//Llibreries

#include <MPU6050_light.h> // afegim la llibreria MPU6050_light.h que ens permet obtenir les variables del acceleròmetre

// Accelerometre i giroscopi (MPU6050)

MPU6050 mpu(Wire);// obté un corrent per a saber on esta cada entrada del MPU6050 i a quin pin correspon cada sortida del MPU6050

unsigned long timer = 0; // ens permet fer un comptador d'una variable, en aquest cas "timer" i podem emmagatzemar 32 bits, de 0 fins a [(2^32) -1] 

void setup() { // part del codi que solament s'executa una vegada
  Serial.begin(9600); //  Funció utilitzada per a l'inicialització de la comunicació serial. Amb aquesta podem configurar el nombre de bauds que es transfereigen, en aquest cas 9600
  Wire.begin(); //inicialitza la llibreria Wire y conecta arduino al bus com a mestre 
  byte status = mpu.begin();// permet a la variable status emmagatzemar un numero entre 0 i 225 es de 8 bits
  
  Serial.print(F("Estat del MPU6050: ")); //imprimeix el text entre parentesis 
  Serial.println(status); //imprimeix l'estat de l'accelerometre (si s'ha conectat un 0 o no)
  while(status!=0){ } // mentre la funció anterior no dongui 0 no continuara el programa, inclús es pararà
  
  Serial.println(F("Calculant els valors inicials del MPU6050"));
  delay(1000); //retras d'un segon
  mpu.calcOffsets(); // comença a calcular tots els valors
  
  //Motor 1

  pinMode(motor1pin1, OUTPUT); // asignem el pin motor1pin1 com a sortida cap endavant
  pinMode(motor1pin2, OUTPUT); // asignem el pin motor1pin1 com a sortida cap enrere

  //Motor 2
  
  pinMode(motor2pin1, OUTPUT); // asignem el pin motor2pin1 com a sortida cap endavant
  pinMode(motor2pin2, OUTPUT); // asignem el pin motor2pin2 com a sortida cap enrere

  pinMode(9, OUTPUT); //asignem el pin 9 digital a al motor 1, que ens permetrà variar la velocitat
  pinMode(10, OUTPUT); //asignem el pin 10 digital a al motor 2, que ens permetrà variar la velocitat

  //FINALITZACIÓ

  
  Serial.println("FET!\n"); //Quan tot s'hagi configurat i pugui arrancar rebrem un missatge per el monitor de serie
}
 //Codi que es repeteix indefinidament (en bucle)

void loop() { 

  //Obtenció de dades
  
  mpu.update(); //refresca les dades que obté l'accelerometre
  
  if((millis()-timer)>10){ // mostra per el monitor de serie els valors que obté el MPU 6050
  
  Serial.print("X : ");
  Serial.print(mpu.getAngleX()); // mostra l'angle creat en l'eix X
  
  Serial.print("\tY : ");
  Serial.print(mpu.getAngleY()); // mostra l'angle creat en l'eix Y
  
  Serial.print("\tZ : ");
  Serial.println(mpu.getAngleZ()); // mostra l'angle creat en l'eix Z
  timer = millis();  
  }

  //Condicionals segons les variables

  //En l'eix X
   if (mpu.getAngleX() >= 20)//si l'angles en X es igual o més gran que 30º
{    
    Serial.print("Dreta"); //mostra que va cap a la dreta
    Serial.println(); //fa una separació un "enter" en anglés
   
    analogWrite(9, 100); //Valor variable del motor 1, a la esquerra el pin de l'Arduino, a la dreta la velocitat en rpm
    analogWrite(10, 0); //Valor variable del motor 2
    
    digitalWrite(motor1pin1, HIGH); //dona corrent al motor 1 cap endavant
    digitalWrite(motor1pin2, LOW); //no dona corrent al motor 1 cap enrere

    digitalWrite(motor2pin1, LOW); //dona corrent al motor 1 cap endavant
    digitalWrite(motor2pin2, LOW); //no dona corrent al motor 1 cap enrere

}
   if (mpu.getAngleX() <= -20) //si l'angles en X es igual o més petit que 30º
{    
    Serial.print("Esquerra");//mostra que va cap a la esquerra
    Serial.println();//escriu una separació en el monitor 
    
    analogWrite(9, 0); //ENA pin motor 1 (ENA es la surtida del Pont en H L298N que permet controlar la velocitat)
    analogWrite(10, 100); //ENA pin motor 2
    
    digitalWrite(motor2pin1, HIGH); //dona corrent al motor 2 cap endavant
    digitalWrite(motor2pin2, LOW); //no dona corrent al motor 2 cap enrere
    
    digitalWrite(motor1pin1, LOW); //dona corrent al motor 2 cap endavant
    digitalWrite(motor1pin2, LOW); //no dona corrent al motor 2 cap enrere
}

    //En l'eix Y
   
   if (mpu.getAngleY() >= 20)//si l'angles en Y es igual o més gran que 30º
{    
    Serial.print("Endavant");//mostra que va endavant
    Serial.println();//escriu una separació en el monitor 
    
    analogWrite(9, 75); //ENA pin motor 1
    analogWrite(10, 75); //ENA pin motor 2
    
    digitalWrite(motor1pin1, HIGH);//dona corrent al motor 1 cap endavant
    digitalWrite(motor1pin2, LOW);//no dona corrent al motor 1 cap enrere

    digitalWrite(motor2pin1, HIGH);//dona corrent al motor 2 cap endavant
    digitalWrite(motor2pin2, LOW);//no dona corrent al motor 2 cap enrere
    
}
   if (mpu.getAngleY() <= -20) //si l'angles en Y es igual o més petit que 30º
{    
    Serial.print("Enrere");//mostra que va enrere
    Serial.println();//escriu una separació en el monitor 
    
    analogWrite(9, 75); //ENA pin motor 1
    analogWrite(10, 75); //ENA pin motor 2
    
    digitalWrite(motor1pin1, LOW);//no dona corrent al motor 1 cap endavant
    digitalWrite(motor1pin2, HIGH);//dona corrent al motor 1 cap enrere
    
    digitalWrite(motor2pin1, LOW); //no dona corrent al motor 2 cap endavant
    digitalWrite(motor2pin2, HIGH);//dona corrent al motor 2 cap enrere
}

    //En cas de que no pasi res

   if ((mpu.getAngleY() < 20 && mpu.getAngleY() > -20) && (mpu.getAngleX() > -20 && mpu.getAngleX() < 20))//si l'angle en X o Y no es troba en els paràmetres anteriors
{
    
    Serial.print("Res");//mostra que no va enlloc
    Serial.println();//escriu una separació en el monitor 
    
    digitalWrite(motor1pin1, LOW);//dona corrent al motor 1 cap endavant
    digitalWrite(motor1pin2, LOW);//no dona corrent al motor 1 cap enrere
    
    digitalWrite(motor2pin1, LOW);//dona corrent al motor 2 cap endavant
    digitalWrite(motor2pin2, LOW);//no dona corrent al motor 2 cap enrere
      
  }
}

//FINALITZACIÓ DEL CODI

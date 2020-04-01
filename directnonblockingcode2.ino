  int AV=2;    //AV es la bombilla verde del semáforo de automóviles
  int AN=6;    //AN es la bombilla naranja del semáforo de automóviles
  int AR=7;    //AR es la bombilla roja del semáforo de automóviles
  int PV=4;    //PV es la bombilla verde del semáforo de peatonales
  int PR=3;    //PR es la bombilla roja del semáforo de peatonales
  int pres= 5; //pres es la variable de botón 
  float t; //contador del tiempo
  float k; //Variable de conteo
  float c; //Variable de conteo
  float p; //Variable de conteo
  float z; //Variable para crear intervalo 1
  float w; //otra variable de tiempo
  float m; //variable de adelanto
  float q; //Variable de conteo
  float f; //Variable para crear intervalo 2
  boolean BAV; //Estado booleano de la bombilla verde del semáforo de automóviles
  boolean BPV; //Estado booleano de la bombilla verde del semáforo de peatones



void setup() {
   Serial.begin(9000);
    
   pinMode(AV,OUTPUT);  //Se configuran todos los bombillos como output y el botón como input
   pinMode(AN,OUTPUT);
   pinMode(AR,OUTPUT);
   pinMode(PV,OUTPUT);
   pinMode(PR,OUTPUT);
   pinMode(pres,INPUT);
     
   digitalWrite(AV,1); //El semáforo de automóviles empieza en verde, mientras que el de peatones empieza en rojo.
   digitalWrite(AN,0);
   digitalWrite(AR,0);
   digitalWrite(PV,0);
   digitalWrite(PR,1);

  
   BAV=1; //Inicializamos los valores del resto de variables
   k=0.0;
   c=0.0;
   p=0.0;
   z=0.08;
   w=0.0;
   m=0;
   q=1;
   f=0.025;
   
}



void loop() {
  
t=w+float(millis()/1000.0)+m; //Definimos el contador. Este está en segundos
  


if ((t>85.0-z+c*0.5)&&(t<85.0+z+c*0.5) && (c<=10.0)){   //El semáforo está en verde hasta el segundo 85, cuando empieza a alternar entre estar apagado y prendido.
                                                        //La luz verde titila 5 veces hasta que t llega al segundo 90, ahí se apaga del todo.
                                                        //Debido a que el contador de millis() tiene una resolución finita a veces es dificíl que t adquiera un valor exacto de tiempo, por lo que es usar mejor un intervalo pequeño. Para eso es z.
   BAV=!BAV;
   digitalWrite(AV,BAV);
   c=c+1;

   if( (t>90.0-z)&&(t<90.0+z) ){digitalWrite(AN,1);}   //En el segundo 90 se prende la luz naranja.
    

   
}else if((t>95.0-z)&&(t<95.0+z)){
    digitalWrite(AN,0);             //Al segundo 95 el semáforo de autos pasa de naranja a rojo y el de peatones, de rojo a verde.
    digitalWrite(AR,1);
    digitalWrite(PR,0);
    digitalWrite(PV,1);
    BPV=1;
    

}else if((t>110.0-z+k*0.5)&&(t<110.0+z+k*0.5) && (k<=10)){
   BPV=!BPV;                                                // Al segundo 110 el la luz roja del semáforo peatonal empieza a titilar. Titila 5 veces hasta llegar al segundo 115.               
   digitalWrite(PV,BPV);
   k=k+1;

   if((t>115.0-z)&&(t<115.0+z)){digitalWrite(PR,1);}  //En el segundo 115 el semáforo peatonal cambia a rojo.

}else if((t>117.0-z)&&(t<117.0+z)){  //En el segundo 117 el semáforo de autos cambia a verde.
  c=0;
  k=0;                              //Se reinician todas las variables, incluyendo el tiempo.
  m=0;
  p=0;
  q=1;
  w=-float((millis()/1000.0));
  BAV=1;
  digitalWrite(AV,1);
  digitalWrite(AR,0);
  
}
  if((t>0.18*q-f)&&(t<0.18*q+f)&& (t<84.9)){  //Se verifica cada cierto periodo de tiempo (también dentro de un intervalo) si se ha presionado el botón.
  if(digitalRead(pres)==1){p=p+1;}
  q=q+1;}
  if((p==5.0) && (t<84.9)){p=0; m=84.9-t;} //Si el botón se presionó 5 veces mientras que el semáforo estaba de automóviles estaba en verde (sin titilar), se adelanta el tiempo hasta llegar a 85. Acelerando efectivamente el cambio.
    
  
}

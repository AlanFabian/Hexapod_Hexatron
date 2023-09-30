//Alan de Jesus Fabian Garcia Cinematica inversa analitica Hexapodo
#include <Servo.h>  
#include<math.h>

// Declaración de variables globales
float q[6] = {0, 0, 0, 0, 0, 0};  // Vector q
float T[5001];  // Vector T debe ser suficiente para la cantidad de datos que este manejando 
int phi[6] ={0, 1, 0, 1, 0, 1};  // Vector phi
Servo servos[18];  // Declaración de servos 

void setup() {
  // Inicializacion de los servos en los pines  2 y un espacio
  servos[0].attach(9);  
  servos[1].attach(10); 
  servos[2].attach(12); 
  servos[3].attach(13); 
  servos[4].attach(14); 
  servos[5].attach(16); 
  servos[6].attach(17);
  servos[7].attach(19);
  servos[8].attach(20);
  servos[9].attach(21);
  servos[10].attach(23);
  servos[11].attach(24);
  servos[12].attach(26);
  servos[13].attach(27);
  servos[14].attach(29);
  servos[15].attach(30);
  servos[16].attach(32);
  servos[17].attach(28);

  // Inicializa el vector T
  float dt = 0.0001;
  for (int i = 0; i <= 5000; i++) {
    T[i] = i * dt;
  }
}

void loop() {
  for (int i = 0; i <= 5000; i++) {
    float t = T[i];
    for (int l = 0; l < 6; l++) {
      float p = Trajectory(t, phi[l]);
      deltaQ(p, l,q);
      // Actualiza los servos con los valores de q
      servos[l].write(q[l]);
      delay(10);  // Añade un pequeño retardo si es necesario
    }
    
  }
}

float Trajectory(float t, int phi) {
  float xc    = 0.0; //Coordenada x del origen 
  float zc    = 0.0; //Coordenada z del origen 
  float a     = 80.0/2.0; //Desplazamiento horizontal maximo 8 centimetros como maximo 
  float b     = 70/2.0; //Desplazamiento vertical maximo 7 centimetros  sobre 2
  float omega = 20.0; //Velocidad angular 
  float phi = 2.0 * tf1(b,omega,zc)/4.0;

  if(T==1){
    t+t+phi;
  }
  if(t>tf2(b,omega,zc)){
    t=t-int(t/tf2(b,omega,zc))*tf2(b,omega,zc);
  }
  if (t<=tf1(b,omega,zc)){
    float x = xc+a*cos(omega*t);
    float z = zc+b*sin(omega*t);
    return x;//regreso el valor de la coordenada x en caso de que la necesite 
    return z;//Valor de la coordenada z
    
  }else if(t<= tf2(b,omega,zc)){
     float x = xc - a * sqrt(-1.0 / (b * b) * (zc * zc) + 1.0) +
              (omega * (a + a * sqrt(-1.0 / (b * b) * (zc * zc) + 1.0)) *
               (t - (PI + asin(zc / b)) / omega)) /
                  (PI + asin(zc / b));
     float z = 0.0; //Definir la coordenada z
     return x; //valor de la coordenada x
     return z; //valor de la coordenada z
  }
  return 0.0;//asignar un valor predeterminado por si algo sale mal que es lo comun 

  float tf1(float b,float omega, float zc){
    return(PI+asin(zc/b))/omega;
  }
  float tf2(float b,float omega,float zc){
    return 2.0 * (PI+asin(zc/b))/omega;
  }
}

float delta_q(float p, int l, float px, float py, float pz, float x1, float x2, float x3, float x4, float x5, float z2, float z3, float z4, float z5) {
  float q1 = p[0];
  float q2 = p[1];
  float q3 = p[2];
  float q4 = p[3];
  float q5 = p[4];

  float d1 = sign((py * cos(q1 + q4 - q5) - px * sin(q1 + q4 - q5) + x1 * sin(q1) - x5 * sin(q1)) * 
                   (x2 + x4 * cos(q2 + q3) + z4 * sin(q2 + q3) + x3 * cos(q2) + z3 * sin(q2)));
  
  float delta_q1 = d1 * abs(acos((px * cos(q1 + q4 - q5) + py * sin(q1 + q4 - q5) - x1 * cos(q1) + x5 * cos(q1)) * 
                                (x2 + x4 * cos(q2 + q3) + z4 * sin(q2 + q3) + x3 * cos(q2) + z3 * sin(q2)) /
                                (abs(x2 + x4 * cos(q2 + q3) + z4 * sin(q2 + q3) + x3 * cos(q2) + z3 * sin(q2)) *
                                 sqrt(px * px - 2 * cos(q4 - q5) * px * x1 + 2 * cos(q4 - q5) * px * x5 + 
                                      py * py - 2 * sin(q4 - q5) * py * x1 + 2 * sin(q4 - q5) * py * x5 + 
                                      x1 * x1 - 2 * x1 * x5 + x5 * x5))));
  
  float d3 = -1;
  
  float num = x3 * x3 - (x5 - x1 - x2 * cos(q1) + px * cos(q4 - q5) + pz * sin(q4 - q5)) * 
              (x5 - x1 - x2 * cos(q1) + px * cos(q4 - q5) + pz * sin(q4 - q5)) - 
              (z2 - zc + z5) * (z2 - zc + z5) - 
              (x2 * sin(q1) - py * cos(q4 - q5) + px * sin(q4 - q5)) * 
              (x2 * sin(q1) - py * cos(q4 - q5) + px * sin(q4 - q5)) + 
              x4 * x4 + z3 * z3 + z4 * z4;
  
  float den = 2.0 * sqrt(x3 * x3 + z3 * z3) * sqrt(x4 * x4 + z4 * z4);
  
  float delta_q3 = d3 * (acos((num / den) - PI + acos((x3 * x4 * cos(q3) + z3 * z4 * cos(q3) + x3 * z4 * sin(q3) - x4 * z3 * sin(q3)) /
                                                     (sqrt(x3 * x3 + z3 * z3) * sqrt(x4 * x4 + z4 * z4)))));

  float z4 = -97.49;
  float z3 = 52.15;

  float d2 = sign((z4 * cos(q2 + q3) - x4 * sin(q2 + q3) + z3 * cos(q2) - x3 * sin(q2)) * 
                   (x5 - x1 - x2 * cos(q1) + px * cos(q4 - q5) + pz * sin(q4 - q5)) - 
                   cos(q1) * (z2 - zc + z5) * 
                   (x4 * cos(q2 + q3) + z4 * sin(q2 + q3) + x3 * cos(q2) + z3 * sin(q2)));
  
  float delta_q2 = d2 * abs(acos((num / den) - PI + acos((x3 * x4 * cos(q3) + z3 * z4 * cos(q3) + x3 * z4 * sin(q3) - x4 * z3 * sin(q3)) /
                                                     (sqrt(x3 * x3 + z3 * z3) * sqrt(x4 * x4 + z4 * z4)))));

  // Devuelve un arreglo o una estructura con los valores de delta_q1, delta_q2 y delta_q3.
  // definir una estructura llamada ResultadoDeltaQ y devolverla.
  ResultadoDeltaQ resultado;
  resultado.delta_q1 = delta_q1;
  resultado.delta_q2 = delta_q2;
  resultado.delta_q3 = delta_q3;
  return resultado;
}

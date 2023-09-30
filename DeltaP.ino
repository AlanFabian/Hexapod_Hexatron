float delta_q(float p, int l, float px, float py, float pz, float x1, float x2, float x3, float x4, float x5, float z2, float z3, float z4, float z5) {
  float q1 = p[0];
  float q2 = p[1];
  float q3 = p[2];
  float q4 = p[3];
  float q5 = p[4];

  float d1 = sign((py * cos(q1 + q4 - q5) - px * sin(q1 + q4 - q5) + x1 * sin(q1) - x5 * sin(q1)) * 
                   (x2 + x4 * cos(q2 + q3) + z4 * sin(q2 + q3) + x3 * cos(q2) + z3 * sin(q2)));
  
  float num = (px * cos(q1 + q4 - q5) + py * sin(q1 + q4 - q5) - x1 * cos(q1) + x5 * cos(q1)) * 
              (x2 + x4 * cos(q2 + q3) + z4 * sin(q2 + q3) + x3 * cos(q2) + z3 * sin(q2));
  
  float den = abs(x2 + x4 * cos(q2 + q3) + z4 * sin(q2 + q3) + x3 * cos(q2) + z3 * sin(q2)) * 
              sqrt(px * px - 2 * cos(q4 - q5) * px * x1 + 2 * cos(q4 - q5) * px * x5 + 
                   py * py - 2 * sin(q4 - q5) * py * x1 + 2 * sin(q4 - q5) * py * x5 + 
                   x1 * x1 - 2 * x1 * x5 + x5 * x5)^(1/2);
  
  float delta_q1 = d1 * acos_deg(num / den);

  // Calcula delta_q2 y delta_q3 aquí...

  // Devuelve un arreglo o una estructura con los valores de delta_q1, delta_q2 y delta_q3.
  // Por ejemplo, puedes definir una estructura llamada ResultadoDeltaQ y devolverla.
  ResultadoDeltaQ resultado;
  resultado.delta_q1 = delta_q1;
  resultado.delta_q2 = delta_q2;
  resultado.delta_q3 = delta_q3;
  return resultado;
  
}
void deltaQ(float p, int l) {
  // Definir los valores de px, py, pz, x1, x2, x3, x4, x5, z2, z3, z4 y z5

  ResultadoDeltaQ resultado = delta_q(p, l, px, py, pz, x1, x2, x3, x4, x5, z2, z3, z4, z5);

  // Usar resultado.delta_q1, resultado.delta_q2 y resultado.delta_q3 
}

// Inclusao de Bibliotecas
#include <sensorNivel.h>

// Configuração do Sensor de Nível
int TRIG = 12;
int ECHO = 13;
sensorNivel sensorNivel(TRIG, ECHO);

// Variaveis de média móvel
float level = 0;
float level_m1 = 0;
float level_m2 = 0;
float level_m3 = 0;
float level_m4 = 0;

//Variáveis auxiliares
float tempo = 0;
float dt = 0.5;
float aux = 0;
float sp = 5.1;
float e = sp;

//Variáveis dos ganhos
float u  = 0;
float e0 = 0;
float u0 = 0;

void setup() {
  /* Habilita Comunicação Serial a uma taxa de 9600 bauds.*/
  Serial.begin(9600);
}

void loop() {

  while (Serial.available()) {

    int aux = Serial.parseInt();

    if (aux == 0) {
      analogWrite (10, 0);

    }
    if (aux == 1) {
      while (tempo <= 60)
      {
        // Leitura do Nível
        if (tempo < 2) {
          level = 0;
        } else {
          level = 17 - sensorNivel.calcSensor();
          level = (level + level_m1 + level_m2 + level_m3 + level_m4) / 5.0;

          level_m4 = level_m3;
          level_m3 = level_m2;
          level_m2 = level_m1;
          level_m1 = level;

        }

        // calculo do erro
        e = sp - level;
        
        // calculo da ação do ctrl
        //u = 43.96 * e - 41.86 * e0 + u0; // Dt = 1
        //u = 43.43 * e - 42.38 * e0 + u0; // Dt = 0.5
        //u = 43.01 * e - 42.8 * e0 + u0;    // Dt = 0.1 
       //u = 42.91 * e - 41.86 * e0 + u0;    // Dt = 0.5  Forward euler
        u = 43.96 * e - 42.91 * e0 + u0;    // Dt = 0.5  Backward euler

        if (u > 255) {u = 255;}        
        if (u <-255) {u = -255;}        
        u0 = u;       
        e0 = e;
        analogWrite (10, u);

        // Impressao do valor na porta serial
        Serial.print(tempo);
        Serial.print(" ");
        Serial.print(e);        //Erro do sistema
        Serial.print(" ");
        Serial.print(u);        //Ação de controle
        Serial.print(" ");
        Serial.println(level);  //Resposta do sistema


        // calculo do tempo
        tempo = tempo + dt;

        delay(1000 * dt);

      }
      Serial.println("-------");
      analogWrite (10, 0);
      tempo = 0;
    }
  }
}



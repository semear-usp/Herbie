//Pinos sensores óticos
#define S1 2
#define S2 3
#define S3 4
#define S4 5
#define S5 6

//Pinos motores CC
  //Esquerda
  #define leftmot1  7  //IN1
  #define leftmot2  8  //IN2

  //Direita
  #define rightmot1 9  //IN3
  #define rightmot2 10 //IN4

//Pinos energia (baixa corrente => não usar para os motores)
#define VCC 11

//Strings de movimento
#define MOV_AVANCAR         0
#define MOV_RECUAR          1
#define MOV_FREAR           2
#define MOV_PARAR           3
#define MOV_ESQUERDA_PARADO 4
#define MOV_DIREITA_PARADO  5
#define MOV_ESQUERDA_VOLTA  6
#define MOV_DIREITA_VOLTA   7
#define ESQUERDA            8
#define DIREITA             9

//Definição do modo de giro
//#define MOV_PARADO
#define MOV_VOLTA

//Identificação da linha
#define BRANCO HIGH
#define PRETO LOW

/*
 * Motor da esquerda:
 * out1 fio preto
 * out2 fio vermelho
 * 
 * Motor da direita:
 * out4 fio preto
 * out3 fio vermelho
 */
void virar(int direcao){
  if(direcao == ESQUERDA){
    #ifdef MOV_PARADO
      sentido(MOV_ESQUERDA_PARADO);
    #endif

    #ifdef MOV_VOLTA
      sentido(MOV_ESQUERDA_VOLTA);
    #endif
  }
  else if(direcao == DIREITA){
    #ifdef MOV_PARADO
      sentido(MOV_DIREITA_PARADO);
    #endif

    #ifdef MOV_VOLTA
      sentido(MOV_DIREITA_VOLTA);
    #endif
  }
}
 
void sentido(int comando){
  if(comando == MOV_RECUAR){
    digitalWrite(leftmot1, LOW);
    digitalWrite(leftmot2, HIGH);

    digitalWrite(rightmot1, LOW);
    digitalWrite(rightmot2, HIGH);
  }
  else if(comando == MOV_AVANCAR){
    digitalWrite(leftmot1, HIGH);
    digitalWrite(leftmot2, LOW);
    
    digitalWrite(rightmot1, HIGH);
    digitalWrite(rightmot2, LOW);
  }
  else if(comando == MOV_FREAR){
    digitalWrite(leftmot1, HIGH);
    digitalWrite(leftmot2, HIGH);
    
    digitalWrite(rightmot1, HIGH);
    digitalWrite(rightmot2, HIGH);
  }
  else if(comando == MOV_PARAR){
    digitalWrite(leftmot1, LOW);
    digitalWrite(leftmot2, LOW);
    
    digitalWrite(rightmot1, LOW);
    digitalWrite(rightmot2, LOW);
  }
  else if(comando == MOV_ESQUERDA_PARADO){
    digitalWrite(leftmot1, LOW);
    digitalWrite(leftmot2, LOW);
    
    digitalWrite(rightmot1, HIGH);
    digitalWrite(rightmot2, LOW);
  }
  else if(comando == MOV_DIREITA_PARADO){
    digitalWrite(leftmot1, HIGH);
    digitalWrite(leftmot2, LOW);
    
    digitalWrite(rightmot1, LOW);
    digitalWrite(rightmot2, LOW);
  }
  else if(comando == MOV_ESQUERDA_VOLTA){
    digitalWrite(leftmot1, LOW);
    digitalWrite(leftmot2, HIGH);
    
    digitalWrite(rightmot1, HIGH);
    digitalWrite(rightmot2, LOW);
  }
  else if(comando == MOV_DIREITA_VOLTA){
    digitalWrite(leftmot1, HIGH);
    digitalWrite(leftmot2, LOW);
    
    digitalWrite(rightmot1, LOW);
    digitalWrite(rightmot2, HIGH);
  }
}

void configuraPinosSensores(){
  //Sensores óticos
  pinMode(S1, INPUT);
  pinMode(S2, INPUT);
  pinMode(S3, INPUT);
  pinMode(S4, INPUT);
  pinMode(S5, INPUT);
}

void configuraPinosMotores(){
  //Motores
  pinMode(leftmot1, OUTPUT);
  pinMode(leftmot2, OUTPUT);
  pinMode(rightmot1, OUTPUT);
  pinMode(rightmot2, OUTPUT);
}

void setup(){
  //Definir se os pinos serão de entrada ou de saída
  configuraPinosSensores();
  configuraPinosMotores();
  //VCC
  pinMode(VCC, OUTPUT);
  digitalWrite(VCC, HIGH);

  Serial.begin(115200);
}

void loop()
{
  //Ler os 5 sensores do sensor ótico: HIGH = branco    LOW = preto
  int v1 = digitalRead(S1);
  int v2 = digitalRead(S2);
  int v3 = digitalRead(S3);
  int v4 = digitalRead(S4);
  int v5 = digitalRead(S5);

  //MOV_AVANCAR ; MOV_RECUAR ; MOV_PARAR

  /*
   * Casos possíveis que não foram tratados:
   * - Início de uma curva, mas v2, v3 e v4 detectam branco no começo dela (o carrinho parará)
   * - 
   */
  if(v3 == BRANCO && v2 == BRANCO && v4 == BRANCO){
    sentido(MOV_PARAR);
  }
  else if(v3 == BRANCO && v2 == PRETO){
    while(v3 != PRETO){
      virar(ESQUERDA);
    }
  }
  else if(v3 == BRANCO && v4 == PRETO){
    while(v3 != PRETO){
      virar(DIREITA);
    }
  }
  else{
    sentido(MOV_AVANCAR);
  }

  delay(500);
}

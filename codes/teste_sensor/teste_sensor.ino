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
#define MOV_AVANCAR 0
#define MOV_RECUAR  1
#define MOV_FREAR   2
#define MOV_PARAR   3

/*
 * Motor da esquerda:
 * out1 fio preto
 * out2 fio vermelho
 * 
 * Motor da direita:
 * out4 fio preto
 * out3 fio vermelho
 */
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

void setup()
{
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

  if (v1 == HIGH){
    Serial.println("Sensor 1 ativado! => AVANÇAR");
    sentido(MOV_AVANCAR);
  }
  if (v2 == HIGH){
    Serial.println("Sensor 2 ativado! => RECUAR");
    sentido(MOV_RECUAR);
  }
  if (v3 == HIGH){
    Serial.println("Sensor 3 ativado! => PARAR");
    sentido(MOV_PARAR);
  }
  if (v4 == HIGH){
    Serial.println("Sensor 4 ativado! => FREAR");
    sentido(MOV_FREAR);
  }
  if (v5 == HIGH){
    Serial.println("Sensor 5 ativado! => FEIJOADA");
  }

  Serial.println("\n");

  delay(500);
}

// Pedro Almeida 333696 15/03/2022

/* Faça um algoritmo para ler a distância de um sonar em centímetros. No algoritmo deverá ser definido
duas constantes chamadas distância mínima e distância máxima. Agora com 5led’s, execute um contador binário 
representando 5 bits, 2^5 = 32. O vetor de Led’s deverá acender de modo a representar os valores em 
centímetros do sonar de 2cm a 31cm (precisão mínima do Sonar de 2 a 3cm). Caso o valor lido do sonar 
seja maior que 31cm, o vetor de Led’s deverá ser ligado em ordem crescente e apagado em ordem decrescente, 
utilizando os pinos pwm (modulação por Largura de Pulso) do arduino, oscilando a luminosidade de 0 a 255. */

// declara leds como uma array dos pins onde estao os leds, echo pin, trigger pin, disttancia minima e maxima
#define STDELAY 1000
int ledList[5] = {11, 10, 9, 6, 5}, echoPin = 3, trigPin = 4, minDist = 2, maxDist = 31;
unsigned long preMillis = 0;

void turnOff(){ // funcao para desligar todos os leds
    for (int i = 0; i < 5; i++){
        digitalWrite(ledList[i], LOW);
    }
}

void distPulse(){ // funcao para ligar e desligar os leds em ordem crescente
    for (int i = 0; i < 5; i++){
        for (int j = 0; j < 256; j++){
            analogWrite(ledList[i], j);
            }
        }
    for (int i = 4; i >= 0; i--){
        for (int j = 255; j >= 0; j--){
            analogWrite(ledList[i], j);
        }
    }
}

int distValue(){
    int distance = 0, duration = 0;

    digitalWrite(trigPin, 0); 
    delayMicroseconds(2);
    digitalWrite(trigPin, 1);
    delayMicroseconds(10);
    digitalWrite(trigPin, 0);
    duration = pulseIn(echoPin, 1);
    distance = (duration / 2.0) * 0.034;

    return distance;
}
}

void setup(){
    Serial.begin(9600);
    for (int i = 0; i < 5; i++){ // define todos os leds como saida
        pinMode(ledList[i], OUTPUT);
    }
    pinMode(echoPin , INPUT); // define eco como entrada
    pinMode(trigPin , OUTPUT ); // define trigger como saida
}

int x = 1;

void loop(){
    unsigned long curMillis = millis();
   
    Serial.println("Hello");
   
    while(millis() < curMillis + STDELAY){
        distPulse()
    }
}
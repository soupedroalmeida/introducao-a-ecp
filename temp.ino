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

int distValue(){
    int result = 0, duration = 0;

    digitalWrite(trigPin, 0); 
    delayMicroseconds(2);
    digitalWrite(trigPin, 1);
    delayMicroseconds(10);
    digitalWrite(trigPin, 0);
    duration = pulseIn(echoPin, 1);
    result = (duration / 2.0) * 0.034;

    return result;
}

void setup(){
    Serial.begin(9600);
    for (int i = 0; i < 5; i++){ // define todos os leds como saida
        pinMode(ledList[i], OUTPUT);
    }
    pinMode(echoPin , INPUT); // define eco como entrada
    pinMode(trigPin , OUTPUT ); // define trigger como saida
}

void loop(){
    if (distValue() > 2 && distValue() <= 31){
        int temp = distValue(), bin[5], index = 4;

        while (temp != 0){
            bin[index] = temp % 2;
            temp /= 2;
            index--;
        }

        for (int i = 0; i < 5; i++){
            if (distValue() < 2 || distValue() > 31){
                turnOff();
                break;
            }
            if (bin[i] == 1){
                digitalWrite(ledList[i], HIGH);
            }
            else{
                digitalWrite(ledList[i], LOW);
            }
        }
    }
    else{
        for (int i = 0; i < 5; i++){
            if (distValue() > 2 && distValue() <= 31){
                turnOff();
                break;
            }
            for (float j = 0; j < 256; j += 0.2){
                analogWrite(ledList[i], j);
            }   
        }
        for (int i = 4; i >= 0; i--){
            if (distValue() > 2 && distValue() <= 31){
                turnOff();
                break;
            }
            for (float j = 255; j >= 0; j -= 0.2){
                analogWrite(ledList[i], j);
            }
        }
    }
}
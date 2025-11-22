#include <Arduino_FreeRTOS.h>
#include <queue.h>

int duration, distance, echoPin=5, trigPin=6, alerta;

bool Functional=true;
bool armat=false;

int button_pin = 8, yAxis = A0;
int CPass[4] = {0, 0, 1, 0};
bool msgAlarma=true;


QueueHandle_t Detect;
QueueHandle_t Pass;



void DistanceDetection(void *pvParametres){
  for(;;){

    if(armat==false){    
        if(msgAlarma==true){
          Serial.println("Alarma este armata");
          msgAlarma=false;
          }

        if(Functional){

          digitalWrite(trigPin, LOW);
          vTaskDelay(2 / portTICK_PERIOD_MS);
          digitalWrite(trigPin, HIGH);
          vTaskDelay(10 / portTICK_PERIOD_MS);
          digitalWrite(trigPin, LOW);

          duration = pulseIn(echoPin, HIGH, 30000);
          distance = (duration * 0.0343) / 2;

          if(distance <= 10 && distance > 0){
          alerta = 1;
          xQueueSend(Detect, &alerta, 0);
          Functional = false;
        }

        vTaskDelay(1000 / portTICK_PERIOD_MS);
      }
    else {
        vTaskDelay(200 / portTICK_PERIOD_MS);
      }

    } 
  }
}



void Buzz(void *pvParametres){
  int rec;
  for(;;){
    if(xQueueReceive(Detect, &rec, portMAX_DELAY)){
      Functional = true;
      analogWrite(10, HIGH);
      vTaskDelay(4000/portTICK_PERIOD_MS);
      analogWrite(10, LOW);
    }
  }
}



void EnterPass(void *pvParametres) {
  int n = 0;
  bool asteptButon = true;
  Serial.println("Astept dezarmare alarma");
  for(;;) {
    if(asteptButon) {
      if(digitalRead(button_pin) == HIGH) {
        
        asteptButon = false;
        n=0;
        Serial.println("Start introducere parola...");
        armat=false;
        vTaskDelay(200 / portTICK_PERIOD_MS);
      }
    } else {
      int valoare = analogRead(yAxis);
      
      if(valoare > 600) { 
        int valueToSend = 1;
        xQueueSend(Pass, &valueToSend, 0);
        Serial.println("1 trimis");
        n++;
        vTaskDelay(500 / portTICK_PERIOD_MS);
      } 
      else if(valoare < 400) {
        int valueToSend = 0;
        xQueueSend(Pass, &valueToSend, 0);
        Serial.println("0 trimis");
        n++;
        vTaskDelay(500 / portTICK_PERIOD_MS);
      }
      if(n >= 4) {
        asteptButon = true;
        Serial.println(" apasa buton pt reset");
      }
    }
    
    vTaskDelay(50 / portTICK_PERIOD_MS);
  }
}



void CheckPass(void *pvParametres) {
  int i = 0, P[4], recieved;
  
  for(;;) {
    if(xQueueReceive(Pass, &recieved, portMAX_DELAY)) {
      P[i] = recieved;
      Serial.print("Am primit: ");
      Serial.println(P[i]);
      
      i++;
      
      if(i >= 4) {
        bool corect = true;
        Serial.print("Parola introdusa: ");
        for(int j = 0; j < 4; j++) {
          Serial.print(P[j]);
          if(P[j] != CPass[j]) {
            corect = false;
          }
        }
        Serial.println();
        
        if(corect) {
          Serial.println("PArola corecta");
          armat=true;
        } else {
          Serial.println("Parola invalida");
          armat=false;
        }
        
        i = 0;
      }
    }
  }
}



void setup() {
  Serial.begin(9600);
  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(10,OUTPUT);


  Detect = xQueueCreate(1, sizeof(int));
  Pass = xQueueCreate(3, sizeof(int));

  xTaskCreate(Buzz, "armed", 128, NULL, 1, NULL);
  xTaskCreate(DistanceDetection, "SensorActivation", 128, NULL, 1, NULL);
  xTaskCreate(EnterPass, "Write",128, NULL, 2, NULL);
  xTaskCreate(CheckPass, "Check", 128, NULL, 2, NULL);

  vTaskStartScheduler();
}

void loop() {
  // put your main code here, to run repeatedly:

}

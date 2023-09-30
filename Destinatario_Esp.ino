#include<WiFi.h>
#include<esp_now.h>

//Estructura de los datos de velocidad grados 
//Es necesarios que el cliente pueda guardar los datos de manera directa 
typedef struct grados_velocidad{
  float grados;
  float velocidad;
}

//Crear una estructura de mensaje llamada myData
grados_velocidad dhtData;

//Callback a la funcion ejecutada cuando los datos son recibidos 
void OnRecv(const uint8_t * mac, const uint8_t * incomingData, int len){
  memcpy(&dhtData,incomingData,sizeof(dhtData));
  Serial.print("Bytes recibidos");
  Serial.println(len);
  Serial-print("Grados");
  Serial.println(dhtData.grados);
  Serial.print("Velocidad");
  Serial.println(dhtData.velocidad);
  
}

void setup(){
  //Inicializar el monitor serial 
  Serial.begin(115200);
  //Configurar la estacion de wifi
  WiFi.mode(WIFI_STA);
  //Inicializar ESP_NOW
  if(esp_now_init() !=ESP_OK){
    Serial.println("Hubo un error a la hora de inicializar ESP_NOW");
    return;

    //Una ves que el protocolo esp_now fue inicializado registramos la funcion callback
    //para ser capaz de reaccionar cuando un paquete llega en tiempo real sin tenter que entrar al loop
    esp_now_register_recv_cb(OnRecv);
  }
  
}
void loop(){
  
}

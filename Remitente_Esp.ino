#include<esp_now.h>
#include<WiFi.h>

//Configurar la Mac del esclavo
uint8_t slaveAddress[] ={0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

//Estructura para mantener los grados y velocidades de movimiento en datos
typedef struct grados_Velocidad{
  float grados;
  float velocidad;
};

//Estructura del mensaje  llamado myData
grados_Velocidad dhtData;

//Callback para mantener un control de los mensajes
void OnSent(const uint8_t * mac_addr,esp_now_send_status_t status){
  Serial.print("\r\nMandar mensaje de estatus:\t");
  Serial.println(status == ESP_NOW_SEND_SUCCESS ? "Enviado de manera exitosa":"Fallo el envio");
}

void setup(){
  //Inicio del monitor serial
  Serial.begin(115200);
  //Configuracion del dispositivo para que sea una estacion de wifi
  WiFi.mode(WIFI_STA);

  //Inicio de ESP_NOW
  if(esp_now_init()!=ESP_OK ){
    Serial.println("Hubo un error inicializando el ESP-NOW");
    return;
  }

  //Registramos la funcion de callback para responder al evento 
  esp_now_register_send_cb(OnSent);

  //Registrar al esclavo 
  esp_now_peer_info_t slaveInfo;
  memopy(slaveInfo.peer_addr.slaveAddress,6);
  slaveInfo.channel = 0;
  salveInfo.encrypt = false;

  //Añadir esclavos 
  if(esp_now_add_peer(&slaveInfo)!=ESP_OK){
    Serial.println("Hubo un error al registrar el esclavo");
    return;
  }
  }

  void loop(){
    //Configurar los valores para mandarlos 
    dhtData.grados=90;
    dhtData.Velocidad=10;
    //Mandar mensaje a traves de ESP-NOW
    esp_err_t result=esp_now_send(salveAddress,(uint8_t*) &dhtData,sizeof(dhtData));

      if(result == ESP_OK){
        Serial.println("El mensaje fue enviado de manera exitosa");
      }
      else{
        Serial.println("Hubo un error a la hora de mandar un mensaje");
      }
      delay(2000);
  }

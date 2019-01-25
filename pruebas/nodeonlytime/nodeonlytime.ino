#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>


// datos para conectarnos a nuestra red wifi
const char *ssid     = "dlink-iotmeg";
const char *password = "iotmich123";

//iniciamos el cliente udp para su uso con el server NTP
WiFiUDP ntpUDP;

// cuando creamos el cliente NTP podemos especificar el servidor al // que nos vamos a conectar en este caso
// 0.south-america.pool.ntp.org SudAmerica
// también podemos especificar el offset en segundos para que nos 
// muestre la hora según nuestra zona horaria en este caso
// restamos -10800 segundos ya que estoy en argentina. 
// y por ultimo especificamos el intervalo de actualización en
// mili segundos en este caso 6000

NTPClient timeClient(ntpUDP, "0.south-america.pool.ntp.org",-21600,6000);

void setup(){
  Serial.begin(115200); // activamos la conexión serial

  WiFi.begin(ssid, password); // nos conectamos al wifi

// Esperamos hasta que se establezca la conexión wifi
 while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }

  timeClient.begin(); 
}

void loop() {
  timeClient.update(); //sincronizamos con el server NTP

  Serial.println(timeClient.getFormattedTime());
//Imprimimos por puerto serie la hora actual

  delay(1000);
}

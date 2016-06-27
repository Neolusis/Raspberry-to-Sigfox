#include "cookingClasses.h"
#include "cookingSigfox.h"
#include "cookingUART.h"
#include "cookingUtils.h"
#include "arduPi.h"
#include "SeeedDHT.h"

//////////////////////////////////////////////
//Asign to UART0
//////////////////////////////////////////////
uint8_t sock = SOCKET0;

#define DHT_PIN 2
#define DHT_TYPE 22
#define DHT_COUNT 16
DHT dht(DHT_PIN, DHT_TYPE, DHT_COUNT);

// Sigfox
uint8_t dataSigfox[12];
uint8_t size;
union
{
  uint8_t  value1[4];
  float    value2;
}t_union;
uint8_t status;

void setup() {
    pinMode(DHT_PIN, INPUT);
    status = Sigfox.ON(sock);
    // Check status
    if (status == 0)
    {
    printf("***  Switch Sigfox ON *** \n");
    }
    else
    {
    printf("Switch Sigfox ON : ERROR\n");
    }
}

void loop()
{
    uint8_t dataSigfox[12];
uint8_t size;
union
{
  uint8_t  value1[4];
  float    value2;
}t_union;
union
{
  uint8_t  value1[2];
  uint16_t value2;
}l_union;
uint8_t status;
    float h = dht.TemperatureHumidityRead(DHT_PIN, 'H');
    float t = dht.TemperatureHumidityRead(DHT_PIN, 'T');

    printf("***  Measures   ***\n");
    printf("Humidity : %f %\n", h);
    printf("Temperature : %f°C\n", t);
    printf("*** Sending data to Sigfox ***\n");
    
    // fill data array
    t_union.value2 = t;
    dataSigfox[0] = t_union.value1[3];
    dataSigfox[1] = t_union.value1[2];
    dataSigfox[2] = t_union.value1[1];
    dataSigfox[3] = t_union.value1[0];

    dataSigfox[4] = (uint8_t) h;
    size = 5;

    // Final Frame to send in "data"
    printf("Final Frame to send: 0x%X\n", dataSigfox);

    // Sending packet to Sigfox
    status = Sigfox.send(dataSigfox,size);

    // Check sending status
    if( status == 0 )
    {
      printf("*** Sigfox packet sent ***\n");
    }
    else
    {
      printf("*** Sigfox packet sent ERROR ***\n");
    }
}

int main (){
	setup();
	while(1){
		loop();
	}
	return (0);
}

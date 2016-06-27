#include "cookingClasses.h"
#include "cookingUtils.h"
#include "arduPi.h"
#include "SeeedDHT.h"

//////////////////////////////////////////////
#define DHT_PIN 8
#define DHT_TYPE 22
#define DHT_COUNT 16
DHT dht(DHT_PIN, DHT_TYPE, DHT_COUNT);


float read_V_out(uint8_t apin) {
  float MeasuredVout = analogRead(0) * (3.0 / 1023.0);
  return MeasuredVout ;
}

float FmultiMap(float val, float * _in, float * _out, uint8_t size) {
  if (val <= _in[0]) return _out[0];
  if (val >= _in[size-1]) return _out[size-1];
  uint8_t pos = 1;
  while (val > _in[pos]) pos++;
  if (val == _in[pos]) return _out[pos];
  return (val - _in[pos-1]) * (_out[pos] - _out[pos-1]) / (_in[pos] - _in[pos-1]) + _out[pos-1];
}


void loop() {
  	float h = dht.TemperatureHumidityRead(DHT_PIN, 'H');
  	float t = dht.TemperatureHumidityRead(DHT_PIN, 'T');

	printf("***  Measures   ***\n");
    printf("Humidity : %f %\n", h);
    printf("Temperature : %f°C\n", t);

    delay(5000);
}

int main (){
   while(1){
      loop();
   }
   return (0);
}

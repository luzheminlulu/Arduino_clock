#define digital_a 2
#define digital_b 4
#define digital_c 7
#define digital_d 8
#define digital_e 11
#define digital_f 12
#define digital_g 13

#define num_1 3
#define num_2 5
#define num_3 6
#define num_4 9

#define lr A0

#define dp 10

#define INTERVAL_TIME 1000000;


#include "Wire.h"
#include "RTClib.h"


RTC_DS3231 rtc;  //默认地址为0x57
unsigned char secondOfRtc;
unsigned char minuteOfRtc;
unsigned char hourOfRtc;
unsigned char dayOfRtc;
unsigned char monthOfRtc;
unsigned int yearOfRtc;
unsigned char weekOfRtc;
float temperatureOfRtc = 0;
unsigned long updateDayInterval = 0;
unsigned char updateMinuteInterval = 0;
String dateStr;
String temperatureStr;
unsigned long prevTime = 0;
unsigned long intervalTime = 1000000; //1000ms

void digital_show(int num)
{

	switch(num){
		case 0:
			digitalWrite(digital_a,HIGH);
			digitalWrite(digital_b,HIGH);
			digitalWrite(digital_c,HIGH);
			digitalWrite(digital_d,HIGH);
			digitalWrite(digital_e,HIGH);
			digitalWrite(digital_f,HIGH);
			digitalWrite(digital_g,LOW );
			break;
		case 1:
			digitalWrite(digital_a,LOW);
			digitalWrite(digital_b,HIGH);
			digitalWrite(digital_c,HIGH);
			digitalWrite(digital_d,LOW);
			digitalWrite(digital_e,LOW);
			digitalWrite(digital_f,LOW);
			digitalWrite(digital_g,LOW );
			break;
		case 2:
			digitalWrite(digital_a,HIGH);
			digitalWrite(digital_b,HIGH);
			digitalWrite(digital_c,LOW);
			digitalWrite(digital_d,HIGH);
			digitalWrite(digital_e,HIGH);
			digitalWrite(digital_f,LOW);
			digitalWrite(digital_g,HIGH);
			break;
		case 3:
			digitalWrite(digital_a,HIGH);
			digitalWrite(digital_b,HIGH);
			digitalWrite(digital_c,HIGH);
			digitalWrite(digital_d,HIGH);
			digitalWrite(digital_e,LOW);
			digitalWrite(digital_f,LOW);
			digitalWrite(digital_g,HIGH);
			break;
		case 4:
			digitalWrite(digital_a,LOW);
			digitalWrite(digital_b,HIGH);
			digitalWrite(digital_c,HIGH);
			digitalWrite(digital_d,LOW);
			digitalWrite(digital_e,LOW);
			digitalWrite(digital_f,HIGH);
			digitalWrite(digital_g,HIGH);
			break;
		case 5:
			digitalWrite(digital_a,HIGH);
			digitalWrite(digital_b,LOW);
			digitalWrite(digital_c,HIGH);
			digitalWrite(digital_d,HIGH);
			digitalWrite(digital_e,LOW);
			digitalWrite(digital_f,HIGH);
			digitalWrite(digital_g,HIGH);
			break;
		case 6:
			digitalWrite(digital_a,HIGH);
			digitalWrite(digital_b,LOW);
			digitalWrite(digital_c,HIGH);
			digitalWrite(digital_d,HIGH);
			digitalWrite(digital_e,HIGH);
			digitalWrite(digital_f,HIGH);
			digitalWrite(digital_g,HIGH);
			break;
		case 7:
			digitalWrite(digital_a,HIGH);
			digitalWrite(digital_b,HIGH);
			digitalWrite(digital_c,HIGH);
			digitalWrite(digital_d,LOW);
			digitalWrite(digital_e,LOW);
			digitalWrite(digital_f,LOW);
			digitalWrite(digital_g,LOW);
			break;
		case 8:
			digitalWrite(digital_a,HIGH);
			digitalWrite(digital_b,HIGH);
			digitalWrite(digital_c,HIGH);
			digitalWrite(digital_d,HIGH);
			digitalWrite(digital_e,HIGH);
			digitalWrite(digital_f,HIGH);
			digitalWrite(digital_g,HIGH);
			break;
		case 9:
			digitalWrite(digital_a,HIGH);
			digitalWrite(digital_b,HIGH);
			digitalWrite(digital_c,HIGH);
			digitalWrite(digital_d,HIGH);
			digitalWrite(digital_e,LOW);
			digitalWrite(digital_f,HIGH);
			digitalWrite(digital_g,HIGH);
			break;
    case -1:
      digitalWrite(digital_a,LOW);
      digitalWrite(digital_b,LOW);
      digitalWrite(digital_c,LOW);
      digitalWrite(digital_d,LOW);
      digitalWrite(digital_e,LOW);
      digitalWrite(digital_f,LOW);
      digitalWrite(digital_g,LOW);
    default:
      digitalWrite(digital_a,HIGH);
      digitalWrite(digital_b,LOW);
      digitalWrite(digital_c,LOW);
      digitalWrite(digital_d,HIGH);
      digitalWrite(digital_e,HIGH);
      digitalWrite(digital_f,HIGH);
      digitalWrite(digital_g,HIGH);
      break;
	}
}

void clock_show(unsigned char time_hour, unsigned char time_min,int brightness)
{
  int time_hour_1 = ((int)time_hour/10);
  int time_hour_2 = ((int)time_hour%10);
  int time_min_1  = ((int)time_min /10);
  int time_min_2  = ((int)time_min %10);

  for(int i=0;i<300;i++)
  {
    digital_show(time_hour_1);
    digitalWrite(num_1,brightness);
    delayMicroseconds(60);
    digitalWrite(num_1,LOW);

    delayMicroseconds(20);

    digital_show(time_hour_2); 
    digitalWrite(num_2,brightness);
    delayMicroseconds(60);
    digitalWrite(num_2,LOW);

    delayMicroseconds(20);
    
    digital_show(time_min_1);
    digitalWrite(num_3,brightness);
    delayMicroseconds(60);
    digitalWrite(num_3,LOW);

    delayMicroseconds(20);

    digital_show(time_min_2);
    digitalWrite(num_4,brightness);
    delayMicroseconds(59);
    analogWrite(dp,brightness);
    digitalWrite(num_4,LOW);

    delayMicroseconds(20);
  }
}
void updateDateTime() {
  DateTime now = rtc.now();
  yearOfRtc = now.year();
  monthOfRtc = now.month();
  dayOfRtc = now.day();
  hourOfRtc = now.hour();
  minuteOfRtc = now.minute();
  secondOfRtc = now.second();
  temperatureOfRtc = rtc.getTemperature();
  weekOfRtc = now.dayOfTheWeek();
}


void setup() {
  // put your setup code here, to run once:
	pinMode(digital_a,OUTPUT);
	pinMode(digital_b,OUTPUT);
	pinMode(digital_c,OUTPUT);
	pinMode(digital_d,OUTPUT);
	pinMode(digital_e,OUTPUT);
	pinMode(digital_f,OUTPUT);
	pinMode(digital_g,OUTPUT);
	
	pinMode(num_1,OUTPUT);
	pinMode(num_2,OUTPUT);
	pinMode(num_3,OUTPUT);
	pinMode(num_4,OUTPUT);

  pinMode(dp,OUTPUT);

  pinMode(lr,INPUT);
	
	Serial.begin(115200);

  if (!rtc.begin()) {
    Serial.println("Couldn't find RTC");
    while (1);
  }

  //if (rtc.lostPower()) {
  //  rtc.adjust(DateTime(F(__DATE__), F(__TIME__)) + TimeSpan(0, 0, 0, 10));
  //}

  prevTime = micros();
}

void loop() {
  // put your main code here, to run repeatedly:
  if (micros() - prevTime >= intervalTime*10) {
    updateDayInterval++;
    updateMinuteInterval++;
    prevTime = micros();
    updateDateTime();
    if (updateDayInterval > 86400) {   //一天86400秒
      updateDayInterval = 1;
    }
    if (updateMinuteInterval > 60) {
      updateMinuteInterval = 1;
    }

  }

  if(analogRead(lr)<800)
	  clock_show(hourOfRtc,minuteOfRtc,3);
  else
    clock_show(hourOfRtc,minuteOfRtc,0);
  
}

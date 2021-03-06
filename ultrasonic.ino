#include "temp_class.h"
#include "ultrasonic_class.h"
//DQ在14号pin D5，echo在5号pin D1，tring在4号pin D2
void setup()
{
    Serial.begin(9600);
    pinMode(LED_BUILTIN, OUTPUT);
    Serial.println("Linking.................");
}

void loop()
{
    auto ultrasoniccm = new ultrasonic(5, 4);
    auto temp = new TempData(14);
    ultrasoniccm->begin();
    temp->begin();
        if ((ultrasoniccm->showcm_temp(temp->ReturnTemp())) < 10)
    {
        digitalWrite(LED_BUILTIN, LOW);
    }
    else
    {
        digitalWrite(LED_BUILTIN, HIGH); 
    }
    Serial.print(ultrasoniccm->showcm_temp(temp->ReturnTemp()));
    Serial.println("CM");
    Serial.print(temp->ReturnTemp());
    Serial.println("摄氏度");
    Serial.println(" ");
    delay(1000);
    delete ultrasoniccm;
    delete temp;
}

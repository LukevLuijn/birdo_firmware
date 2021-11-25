#include <Arduino.h>
#include "App.h"

Application::App app;

void setup()
{
  Serial.begin(9600);
  delay(1000);
  app.Start();
}

void loop()
{
  app.Loop();
}

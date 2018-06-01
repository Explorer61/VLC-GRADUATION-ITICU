/* [0] = start
   [1] = text için 0 resim için değişiyor
   [2 - 8] = textin tamamı resim için 7 biti
   [10] = 1 müzik
   [9] = 0 text [9] = 1 resim
   [11-12-13]= stop
*/
#define wait 30
extern uint8_t bitmap2[];
int x[14];
int imageState = 0;
int resimbilgisi;
int transmitterBusy = 0;
int transmitState = 0;
int first = 0;
int second = 0;
void setup() {
  Serial.begin(115200);
  pinMode(7, OUTPUT);
  pinMode(A0, INPUT);
  x[0] = {1};
  x[1] = { 0 };
  x[10] = { 0 };
  x[11] = { 0 };
  x[12] = { 0 };
  x[13] = {0 };
}


void loop() {
  int v , a ;
  second=millis();
  if (analogRead(A0) > 300)
  {
    transmitterBusy = 0;
    if (transmitterBusy == 0)
    {
      x[10] = 1;
    }

    if ( Serial.available() > 0 )
    {
      if (transmitState == 0 && transmitterBusy == 0)
      {
        second = millis();

        a = Serial.read();
        binaryConverter(a);
        x[9] = 0;
        for (v = 0; v <= 13; v++)
        {
          if (x[v] == 1)
          {
            digitalWrite(7, HIGH);
            Serial.print(x[v]);
            delay(wait);
          }
          else if (x[v] == 0) {
            digitalWrite(7, LOW);
            Serial.print(x[v]);
            delay(wait);
          }
        }
        Serial.println();
       first=second;
      }
    if(second-first > 3000)
    {x[9]=1;
      if (bitmap2[0] != '\0')
      {x[9]=1;
        if (transmitterBusy == 1)
        {
          resimbilgisi = (bitmap2[imageState], DEC);
          binaryConverter2(resimbilgisi);
          for (v = 0; v <= 13; v++)
          {

            if (x[v] == 1)
            {
              digitalWrite(7, HIGH);
              Serial.print(x[v]);
              delay(wait);
            }
            else if (x[v] == 0) {
              digitalWrite(7, LOW);
              Serial.print(x[v]);
              delay(wait);
            }
            transmitState++;
          }
          transmitState = 0;
          Serial.print("Resimin  ");
          Serial.print(imageState);
          Serial.print(". biti");

          Serial.println();
          imageState++;
          if (imageState == 20)
          {
            imageState = 0;
            bitmap2[0] = '\0';
            Serial.print("Resim alındı");
          }
        }

      }
    }
    }
  }
  if ( Serial.available() > 0 )
  {
    if (transmitState == 0 && transmitterBusy == 0)
    {
      second=millis();
      x[10] = 1;
      a = Serial.read();
      binaryConverter(a);
      x[9] = 0;
      for (v = 0; v <= 13; v++)
      {
        if (x[v] == 1)
        {
          digitalWrite(7, HIGH);
          Serial.print(x[v]);
          delay(wait);
        }
        else if (x[v] == 0) {
          digitalWrite(7, LOW);
          Serial.print(x[v]);
          delay(wait);
        }
      }
      Serial.println();
      transmitterBusy = 0;
      first=second;
    }
  }

  if (second - first > 3000)
  {x[9]=1;
    if (bitmap2[0] != '\0')
    {
      x[9]=1;
      if (transmitterBusy == 0)
      {
        x[10] = 1;
        x[9]=1;
        resimbilgisi = bitmap2[imageState];
        binaryConverter2(resimbilgisi);
        for (v = 0; v <= 13; v++)
        {

          if (x[v] == 1)
          {
            digitalWrite(7, HIGH);
            Serial.print(x[v]);
            delay(wait);
          }
          else if (x[v] == 0) {
            digitalWrite(7, LOW);
            Serial.print(x[v]);
            delay(wait);
          }
          transmitState++;
        }
        transmitState = 0;
        Serial.print("Resimin  ");
        Serial.print(imageState);
        Serial.print(". biti");

        Serial.println();
        imageState++;
        if (imageState == 504)
        {
          imageState = 0;
          bitmap2[0] = '\0';
          Serial.print("Resim alındı");
        }
      }
    }
  }
}

void binaryConverter(int a2)
{
  int i;
  for (i = 8; i >= 2; i--)
  {
    x[i] = a2 % 2;
    a2 = a2 / 2;

  }
}



void binaryConverter2(int a) {
  int d = 2;
  if (a == 0) {
    while (d < 9) {
      x[d] = 0;
      d = d + 1;
    }
  }
  else if (a != 0) {
    while (a != 1) {
      x[d] = a % 2;
      d = d + 1;
      a = a / 2;
      if (a == 1) {
        x[d] = 1;
      }
    }
  }
}
  /*for(int j=8;j>=1;j--){
    Serial.print(x[j]);
    }
    Serial.println();*/





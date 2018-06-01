/*
    
    c = start
    [0-7] = text ve resim
    {8] = 0 text 1 resim
    [9] = 1 müzik
    [8] = 0 text
    [8] = 1 resim
    [10]= stop
    [11]= stop
    [12]= stop

*/

#define AREAD 600
#define WAIT 30
int x[13];
char c1[256];
int p = 0;
char c2 = '\0';
int imageState = 0;
unsigned int image[20];

void setup() {
  Serial.begin(115200);
  pinMode(A0, INPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  char f;
  int b, d, i, j, y;
  int c = 0;
  int output = 0;
  int power = 1;
  b = analogRead(A0);
  
  if (b < AREAD) 
   {
    c = 1;
   }
  delay(WAIT);
  if (c == 1) {
    for (i = 0; i < 13; i++) {
      d = analogRead(A0);
      if (d < AREAD) {
        x[i] = 1;

      }
      //delay(100);
      if (d > AREAD) {
        x[i] = 0;

      }
      delay(WAIT);
    }
    if (x[10] == 0 && x[11] == 0)
    {
      if (x[12] == 0)
      {
        if (x[9] == 1)
        {

          //digitalWrite(6, HIGH);
        }
        if (x[9] == 0)
        {
          // digitalWrite(6, LOW);
        }

        if (x[8] == 0)
        {
          for (j = 0; j < 8; j++)
          {
            output += x[7 - j] * power;
            power *= 2;

          }
          f = output;
          Serial.print(f);
          c = 0;
          //Print(f);

        }
        if (x[8] == 1)
        {
          for (j = 0; j < 8; j++)
          {
            output += x[7 - j] * power;
            power *= 2;
          }


          image[imageState] = output;

          c = 0;
          imageState++;
          //Serial.println("resim bilgisi alındı");
          //Serial.println(imageState);
          if (imageState == 19)
          {
            imageState = 0;
            
              Serial.println();
              for(int r=0;r<5;r++)
              {
                Serial.print(image[r],BIN);
              }
              Serial.println();
              for(int r1=0;r1<5;r1++)
              {
                Serial.print(image[r1],BIN);
              }
              Serial.println();
              for(int r2=0;r2<5;r2++)
              {
                Serial.print(image[r2],BIN);
              }
              Serial.println();
              for(int r3=0;r3<5;r3++)
              {
                Serial.print(image[r3],BIN);
              }
              Serial.println();
              
             } 
          }
        }

      }
    }

  }

void Print(char q) {
  
  c1[p] = {q};
  p = p + 1;
  if (q == '.') {
    for (int i1 = 0; i1 < 255; i1++) {
      if (c1[i1] != '\0' )
      {
        Serial.print(c1[i1]);
        p = 0;
        c1[i1] = c2;
      }

    }
  }

}


long cstate = 0;
int cdelta = -1;

/* Configure digital pins 9 and 10 as 16-bit PWM outputs. */
void setupPWM16() {
  DDRB |= _BV(PB1) | _BV(PB2);       /* set pins as outputs */
  TCCR1A = _BV(COM1A1) | _BV(COM1B1) /* non-inverting PWM */
           | _BV(WGM11);             /* mode 14: fast PWM, TOP=ICR1 */
  TCCR1B = _BV(WGM13) | _BV(WGM12)
           | _BV(CS10); /* no prescaling */
  ICR1 = 0xffff;        /* TOP counter value */
}

/* 16-bit version of analogWrite(). Works only on pins 9 and 10. */
void analogWrite16(uint8_t pin, uint16_t val) {
  switch (pin) {
    case 9: OCR1A = val; break;
    case 10: OCR1B = val; break;
  }
}

void blink() {
  cdelta = -cdelta;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(A4, OUTPUT);

  // all 8 pins
  pinMode(7, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A0, OUTPUT);

  // Do NOT use serial in a loop. Will be slow
  Serial.begin(230400);
  Serial.println("OK");

  pinMode(2, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(2), blink, FALLING);
  setupPWM16();
}

void writeled(int led0, int led1, int led2, int led3, int led4, int led5, int led6, int led7, int status) {
  led0 = min(max(0, led0), 255);
  led1 = min(max(0, led1), 255);
  led2 = min(max(0, led2), 255);
  led3 = min(max(0, led3), 255);
  led4 = min(max(0, led4), 255);
  led5 = min(max(0, led5), 255);
  led6 = min(max(0, led6), 255);
  led7 = min(max(0, led7), 255);
  digitalWrite(7, led0 > status);
  digitalWrite(5, led1 > status);
  digitalWrite(A5, led2 > status);
  digitalWrite(A4, led3 > status);
  digitalWrite(A3, led4 > status);
  digitalWrite(A2, led5 > status);
  digitalWrite(A1, led6 > status);
  digitalWrite(A0, led7 > status);
}

#define constant_delay 1
void loop() {
  // Send wave of light
  for (int i = 1; i <= 255 * constant_delay; i++) {
    cstate += cdelta;
    cstate = min(max(0, cstate), 65535);
    analogWrite16(9, cstate);
    writeled(255, 0, 0, 0, 0, 0, 0, 0, i % 256);
  }
  for (int i = 1; i <= 255 * constant_delay; i++) {
    cstate += cdelta;
    cstate = min(max(0, cstate), 65535);
    analogWrite16(9, cstate);
    writeled(128, 255, 0, 0, 0, 0, 0, 0, i % 256);
  }
  for (int i = 1; i <= 255 * constant_delay; i++) {
    cstate += cdelta;
    cstate = min(max(0, cstate), 65535);
    analogWrite16(9, cstate);
    writeled(64, 128, 255, 0, 0, 0, 0, 0, i % 256);
  }
  for (int i = 1; i <= 255 * constant_delay; i++) {
    cstate += cdelta;
    cstate = min(max(0, cstate), 65535);
    analogWrite16(9, cstate);
    writeled(32, 64, 128, 255, 0, 0, 0, 0, i % 256);
  }
  for (int i = 1; i <= 255 * constant_delay; i++) {
    cstate += cdelta;
    cstate = min(max(0, cstate), 65535);
    analogWrite16(9, cstate);
    writeled(16, 32, 64, 128, 255, 0, 0, 0, i % 256);
  }
  for (int i = 1; i <= 255 * constant_delay; i++) {
    cstate += cdelta;
    cstate = min(max(0, cstate), 65535);
    analogWrite16(9, cstate);
    writeled(8, 16, 32, 64, 128, 255, 0, 0, i % 256);
  }
  for (int i = 1; i <= 255 * constant_delay; i++) {
    cstate += cdelta;
    cstate = min(max(0, cstate), 65535);
    analogWrite16(9, cstate);
    writeled(4, 8, 16, 32, 64, 128, 255, 0, i % 256);
  }
  for (int i = 1; i <= 255 * constant_delay; i++) {
    cstate += cdelta;
    cstate = min(max(0, cstate), 65535);
    analogWrite16(9, cstate);
    writeled(2, 4, 8, 16, 32, 64, 128, 255, i % 256);
  }
  int led0 = 2;
  int led1 = 4;
  int led2 = 8;
  int led3 = 16;
  int led4 = 32;
  int led5 = 64;
  int led6 = 128;
  int led7 = 255;
  // fade out the trail
  while (led7) {
    led0 /= 2;
    led1 /= 2;
    led2 /= 2;
    led3 /= 2;
    led4 /= 2;
    led5 /= 2;
    led6 /= 2;
    led7 /= 2;
    for (int i = 1; i <= 255 * constant_delay; i++) {
      cstate += cdelta;
      cstate = min(max(0, cstate), 65535);
      analogWrite16(9, cstate);
      writeled(led0, led1, led2, led3, led4, led5, led6, led7, i % 256);
    }
  }
}

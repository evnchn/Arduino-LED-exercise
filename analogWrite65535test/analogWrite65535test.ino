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

void setup() {
  // put your setup code here, to run once:
  pinMode(A4, OUTPUT);
  Serial.begin(230400);
  Serial.println("OK");
  setupPWM16();
}

void loop() {
  // put your main code here, to run repeatedly:
  for (long i = 0; i <= 65535; i++) {
    analogWrite16(9, i);
    delayMicroseconds(20);
  }
  for (long i = 65535; i >= 0; i--) {
    analogWrite16(9, i);
    delayMicroseconds(20);
  }
}
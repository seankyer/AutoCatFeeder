#include <Stepper.h>

// Pin Setup
int COCO_LED = 5;
int CATIX_LED = 4;
int CAT_SELECTOR_BUTTON = 7;
int DISPENSOR_BUTTON = 6;

// Global Variables
int COCO_MULT = 4;
int CATIX_MULT = 7;
int SELECTOR = 0;

// Stepper Motor Variables
int STEPS_PER_REV = 2048;
int REVERSE_STEPS = 312;
int MOT_SPEED = 10;

Stepper STEP(STEPS_PER_REV, 8, 10, 9, 11);

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  STEP.setSpeed(MOT_SPEED);  
  pinMode(COCO_LED, OUTPUT);
  pinMode(CATIX_LED, OUTPUT);
  pinMode(CAT_SELECTOR_BUTTON, INPUT);
  pinMode(DISPENSOR_BUTTON, INPUT);

  startup_led();

  digitalWrite(COCO_LED, LOW); // Coco is 1
  digitalWrite(CATIX_LED, HIGH); // Catix is 0

  delay(250);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(CAT_SELECTOR_BUTTON) == HIGH) {
    Serial.print("Selecting!\n");
    toggle_protocol();
  };

  if(digitalRead(DISPENSOR_BUTTON) == HIGH) {
    Serial.print("Dispensing!\n");
    feed();
  };
}

void feed() {
  if (SELECTOR == 1) {
    // Coco feeding protocol
    Serial.print("Feeding Coco!\n");
    for (int i = 0; i < COCO_MULT; i++) {  
      STEP.step(-STEPS_PER_REV);
      STEP.step(REVERSE_STEPS);
    }
  } else {
    Serial.print("Feeding Catix!\n");
    for (int i = 0; i < CATIX_MULT; i++) {  
      STEP.step(-STEPS_PER_REV);
      STEP.step(REVERSE_STEPS);
    }
  } 
}

void toggle_protocol() {
  if(SELECTOR == 0) {
    // Coco mode
    Serial.print("Coco Mode!\n");
    digitalWrite(COCO_LED, HIGH);
    digitalWrite(CATIX_LED, LOW);
    SELECTOR = 1;
    delay(200);
  } else {
    // Catix mode
    Serial.print("Catix Mode!\n");
    digitalWrite(COCO_LED, LOW);
    digitalWrite(CATIX_LED, HIGH);
    SELECTOR = 0;
    delay(200);
  }
}

void startup_led() {
  for (int i = 0; i < 3; i++) {
    digitalWrite(COCO_LED, LOW);
    digitalWrite(CATIX_LED, HIGH);
    delay(200);
    digitalWrite(COCO_LED, HIGH);
    digitalWrite(CATIX_LED, LOW);
    delay(200);
  }
    digitalWrite(COCO_LED, LOW);
    digitalWrite(CATIX_LED, LOW);
    delay(500);
}

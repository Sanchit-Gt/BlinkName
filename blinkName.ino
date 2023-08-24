const int button = 2;
int buttonState = 0;
int lastButtonState = HIGH;
bool nameBlinking = false;
int charIndex = 0;

char inputName[100];
int inputIndex = 0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  pinMode(button, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Enter the name you want to blink in Morse code (a-z, space):");
}

void dot() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(250);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

void dash() {
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1500);
  digitalWrite(LED_BUILTIN, LOW);
  delay(250);
}

void morse_encryption(char name) {
  switch (name) {
    case 'a':
      dot();
      dash();
      break;
    case 'b':
      dash();
      dot();
      dot();
      dot();
      break;
    case 'c':
      dash();
      dot();
      dash();
      dot();
      break;
    case 'd':
      dash();
      dot();
      dot();
      break;
    case 'e':
      dot();
      break;
    case 'f':
      dot();
      dot();
      dash();
      dot();
      break;
    case 'g':
      dash();
      dash();
      dot();
      break;
    case 'h':
      dot();
      dot();
      dot();
      dot();
      break;
    case 'i':
      dot();
      dot();
      break;
    case 'j':
      dot();
      dash();
      dash();
      dash();
      break;
    case 'k':
      dash();
      dot();
      dash();
      break;
    case 'l':
      dot();
      dash();
      dot();
      dot();
      break;
    case 'm':
      dash();
      dash();
      break;
    case 'n':
      dash();
      dot();
      break;
    case 'o':
      dash();
      dash();
      dash();
      break;
    case 'p':
      dot();
      dash();
      dash();
      dot();
      break;
    case 'q':
      dash();
      dash();
      dot();
      dash();
      break;
    case 'r':
      dot();
      dash();
      dot();
      break;
    case 's':
      dot();
      dot();
      dot();
      break;
    case 't':
      dash();
      break;
    case 'u':
      dot();
      dot();
      dash();
      break;
    case 'v':
      dot();
      dot();
      dot();
      dash();
      break;
    case 'w':
      dot();
      dash();
      dash();
      break;
    case 'x':
      dash();
      dot();
      dot();
      dash();
      break;
    case 'y':
      dash();
      dot();
      dash();
      dash();
      break;
    case 'z':
      dash();
      dash();
      dot();
      dot();
      break;
    case ' ':
      // Space
      delay(3500); // 3.5 seconds for word spacing
      break;
    default:
      // Ignore unknown characters
      break;
  }
}

void loop() {
  buttonState = digitalRead(button);

  if (buttonState == LOW && lastButtonState == HIGH) {
    nameBlinking = !nameBlinking;
    charIndex = 0;
  }

  lastButtonState = buttonState;

  if (nameBlinking) {
    if (inputName[charIndex] != '\0') {
      char name = inputName[charIndex];
      morse_encryption(name);
      delay(1000);

      charIndex++;
    } else {
      nameBlinking = false;
    }
  } else {
    digitalWrite(LED_BUILTIN, LOW);
  }

  while (Serial.available() > 0) {
    char incoming = Serial.read();
    if (incoming == '\n' || inputIndex >= sizeof(inputName) - 1) {
      inputName[inputIndex] = '\0';
      inputIndex = 0;
      nameBlinking = true;
    } else {
      inputName[inputIndex] = incoming;
      inputIndex++;
    }
  }
}
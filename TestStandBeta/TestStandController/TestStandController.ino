//Example By ArduinoAll

int led = 13;
int relay = 2; // กำหนดขาควบคุม Relay
int button = 3;
int buzzer = 9; //buzzer to arduino pin 9
void setup()
{
  pinMode(button, INPUT);
  pinMode(relay, OUTPUT); // กำหนดขาทำหน้าที่ให้ขา 2 เป็น OUTPUT
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output
}
void loop()
{

  if(digitalRead(button) == LOW){
    Serial.println("button pressed");
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(100);        // ...for 1 sec
    noTone(buzzer);     // Stop sound...
    delay(100);
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(100);
    noTone(buzzer);     // Stop sound...
    
    delay(3000); // ดีเลย์ 1000ms
    
    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(100); // ดีเลย์ 1000ms
    noTone(buzzer);     // Stop sound...
    delay(1000); // ดีเลย์ 1000ms

    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(100); // ดีเลย์ 1000ms
    noTone(buzzer);     // Stop sound...
    delay(1000); // ดีเลย์ 1000ms

    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(100); // ดีเลย์ 1000ms
    noTone(buzzer);     // Stop sound...
    delay(1000); // ดีเลย์ 1000ms

    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(100); // ดีเลย์ 1000ms
    noTone(buzzer);     // Stop sound...
    delay(1000); // ดีเลย์ 1000ms

    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(100); // ดีเลย์ 1000ms
    noTone(buzzer);     // Stop sound...
    delay(1000); // ดีเลย์ 1000ms

    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(100); // ดีเลย์ 1000ms
    noTone(buzzer);     // Stop sound...
    delay(1000); // ดีเลย์ 1000ms

    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(100); // ดีเลย์ 1000ms
    noTone(buzzer);     // Stop sound...
    delay(1000); // ดีเลย์ 1000ms

    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(100); // ดีเลย์ 1000ms
    noTone(buzzer);     // Stop sound...
    delay(1000); // ดีเลย์ 1000ms

    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(100); // ดีเลย์ 1000ms
    noTone(buzzer);     // Stop sound...
    delay(1000); // ดีเลย์ 1000ms

    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(100); // ดีเลย์ 1000ms
    noTone(buzzer);     // Stop sound...
    delay(1000); // ดีเลย์ 1000ms

    tone(buzzer, 1000); // Send 1KHz sound signal...
    delay(2000); // ดีเลย์ 1000ms
    noTone(buzzer);     // Stop sound...
    digitalWrite(led, 1);
    digitalWrite(relay, 1); // สั่งให้ relay ทำงาน
    
    delay(10000); // ดีเลย์ 1000ms
    digitalWrite(led, 0);
    digitalWrite(relay, 0); // ปิดไฟ relay
  }
}

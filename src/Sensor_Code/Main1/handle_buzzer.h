void Buzzer()
{  
 for (int i = 0; i<10; i++)
 {
  digitalWrite(buzzerPin, HIGH);
  delay(100);
  digitalWrite(buzzerPin, LOW);
 }
}
  

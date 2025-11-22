# Sistem-Alarm-Securitate-cu-RTOS
Sistem embedded de securitate implementat cu FreeRTOS, featuring detectare intruși, interfață parolă și alarmă sonoră.
Proiectul este realizat pentru studiul conceptelor de bază a RTOS.


## Caracteristici
- **Sistem de autentificare** cu parolă de 4 biți
- **Detectare intruși** cu senzor ultrasonic HC-SR04
- **Alarmă sonoră** cu buzzer
- **Arhitectură real-time** cu FreeRTOS
- **Management resurse** cu cozi de mesaje


##  Tehnologii Utilizate
- **Platformă:** Arduino Uno
- **RTOS:** FreeRTOS
- **Limbaj:** C/C++
- **Senzori:** HC-SR04 (ultrasonic), Joystick (input parolă)
- **Actuatori:** Buzzer

## Explicatii arhitectura task-uri
- Task1: DistanceDetection - "Paznicul"(verifica când distanța devine mai mică sau egală cu 10-adaugă valori in queue).
- Task2: Buzz - "Alarma"(citește queue-ul - dacă depistează valori aprinde alarma).
- Task3: EnterPass - "Interfața Utilizator"(permite introducerea parolei, parola se stochează în alt queue).
- Task4: CheckPass - "Verificatorul"(verifică corectitudinea parolei, adică citește queue-ul și compară rezultatele, respectiv lasă alarma armată, sau o dezarmează).


## Observații
- Parola este deja inclusă în program din cauză că acest program este făcut cu scopul de a experimenta cu RTOS, și nu este un sistem gândit pentru funcționalitate
- Pentru reactivare a alarmei după dezarmare apasă butonul de reset al plăcii Arduino.


## Cum arată sistemul
![WhatsApp Image 2025-11-22 at 09 52 06](https://github.com/user-attachments/assets/ca36b57b-5bd9-4136-8f2c-925a3ec5c046)

# Bilancia Gravitazionale

Questo progetto è una bilancia basata su un ESP8266 e su un integrato HX711.

Il programma caricato sull'ESP8266 è scritto in C appoggiandosi all'IDE di Arduino, è basato su Blynk, che è anche l'unica dipendenza richiesta per la compilazione del codice (oltre al core Arduino del modulo ESP8266).

Andando avanti con lo sviluppo del progetto abbiamo incontrato vari ostacoli, il più arduo è stato il continuo reset del modulo ESP8266 a causa del watchdog interno non disattivabile del modulo, che ha impiegato un intero weekend per una sostanziale modifica della libreria HX711 di Bodge inserendo delle istruzioni per il reset del watchdog.

BOM (Bill of materials):
- NodeMCU v3
- HX711 Breakout
- Display I2C
- Cella di carico

Collegamenti necessari:
- NodeMCU D1 -> Display I2C SCL
- NodeMCU D2 -> Display I2C SDA
- NodeMCU D3 -> HX711 DT
- NodeMCU D4 -> HX711 SCK

Un ringraziamento speciale ai docenti Luigi Gentile, Ugo Riso, Giorgio Tombola per il grande aiuto che ci hanno dato, nonchè a tutto il corpo docente dell'Istituto.

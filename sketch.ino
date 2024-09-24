#include <DHT.h>

#define DHTPIN 2        // DHT22 terhubung ke pin digital 2
#define DHTTYPE DHT22   // DHT22 (AM2302)
DHT dht(DHTPIN, DHTTYPE);

const int buzzerPin = 8;  // Buzzer terhubung ke pin 8
const int ledPin = 7;     // LED terhubung ke pin 7

float temperatureThreshold = 50.0;  // Suhu ambang batas dalam Celsius

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(buzzerPin, OUTPUT);
  pinMode(ledPin, OUTPUT);
  Serial.println("Sistem Alarm Kebakaran Siap!");
}

void loop() {
  delay(2000);  // Tunggu 2 detik antara pengukuran

  float temperature = dht.readTemperature();  // Baca suhu

  // Periksa apakah pembacaan berhasil
  if (isnan(temperature)) {
    Serial.println("Gagal membaca dari sensor DHT!");
    return;
  }

  // Tampilkan suhu di Serial Monitor
  Serial.print("Suhu: ");
  Serial.print(temperature);
  Serial.println(" °C");

  // Periksa apakah suhu melebihi ambang batas
  if (temperature > temperatureThreshold) {
    // Aktifkan alarm
    digitalWrite(ledPin, HIGH);
    tone(buzzerPin, 1000);  // Bunyikan buzzer pada frekuensi 1000 Hz
    Serial.println("PERINGATAN: SUHU TINGGI!");
  } else {
    // Nonaktifkan alarm
    digitalWrite(ledPin, LOW);
    noTone(buzzerPin);
  }
}
#include <DHT.h>

// Define the pin for the DHT sensor
#define DHTPIN 2

// Define the type of DHT sensor (DHT11 in this case)
#define DHTTYPE DHT11

// Define the pin for the smoke sensor
#define SMOKE_SENSOR_PIN A0

// Define the pin for the buzzer
#define BUZZER_PIN 8

// Create a DHT object
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  // Start serial communication
  Serial.begin(9600);

  // Set the buzzer pin as an output
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize the DHT sensor
  dht.begin();
}

void loop() {
  // Delay for 2 seconds
  delay(2000);

  // Read temperature from the DHT sensor
  float temperature = dht.readTemperature();

  // Read humidity from the DHT sensor
  float humidity = dht.readHumidity();

  // Read analog value from the smoke sensor
  int smokeLevel = analogRead(SMOKE_SENSOR_PIN);

  // Check if the temperature and humidity readings are valid
  if (!isnan(temperature) && !isnan(humidity)) {
    // Print temperature and humidity to the serial monitor
    Serial.print("Temperature: ");
    Serial.print(temperature);
    Serial.println(" °C");
    Serial.print("Humidity: ");
    Serial.print(humidity);
    Serial.println(" %");

    // Print smoke level to the serial monitor
    Serial.print("Smoke Level: ");
    Serial.println(smokeLevel);

    // Check if temperature is above 28.90 degrees Celsius or smoke level is above 500
    if (temperature > 28.90 || smokeLevel > 500) {
      // Activate the buzzer with a tone for 1 second
      tone(BUZZER_PIN, 1000, 1000);
      delay(1000);
      // Turn off the buzzer
      noTone(BUZZER_PIN);
    }
  } else {
    // Print an error message if there is an issue with data transmission from the DHT sensor
    Serial.println("Error in data transmission");
  }
}

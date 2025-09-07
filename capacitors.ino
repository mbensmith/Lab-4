
// Simulated Capacitor Timer on ESP32

const float Vmax = 3.3;      // Max simulated capacitor voltage (scaled to ESP32 ADC range)
const float R = 10000.0;     // 10k ohms
const float C = 0.0001;      // 100 µF = 0.0001 F
const float RC = R * C;      // Time constant ~1 second

bool charging = false;       // Simulated button state
float capVoltage = 0.0;      // Current simulated capacitor voltage
unsigned long lastUpdate = 0;

void setup() {
  Serial.begin(115200);
  Serial.println("=== Simulated Capacitor Timer Starting ===");
  lastUpdate = millis();
}

void loop() {
  unsigned long now = millis();
  float dt = (now - lastUpdate) / 1000.0; // seconds since last update
  lastUpdate = now;

  // Simulated button behavior
  // (Charges for 2 seconds every 5 seconds)
  
  if ((now / 5000) % 2 == 0 && (now % 5000) < 2000) {
    charging = true;
  } else {
    charging = false;
  }

  // Update capacitor voltage

  if (charging) {
    // Charging: V = Vmax * (1 - e^(-t/RC))
    capVoltage += (Vmax - capVoltage) * (1 - exp(-dt / RC));
  } else {
    // Discharging: V = V0 * e^(-t/RC)
    capVoltage *= exp(-dt / RC);
  }

  // Convert simulated voltage to ADC scale (0–4095)
  int capADC = (int)((capVoltage / Vmax) * 4095);

  // Print results
  Serial.print("Capacitor Voltage: ");
  Serial.print(capVoltage, 2);
  Serial.print(" V | ADC Value: ");
  Serial.println(capADC);

  delay(200); // Slow down output
}


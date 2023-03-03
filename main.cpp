// Controll system code for Boost converter LM5170EVM-BIDIR between PV and Bus
// GridVIlle
// 2017-05-01


// Microgrid control system

/*
Detect V_pv and I_pv from the solar panel as input to the function
Detect V_bus and I_bus from the grid as input to the function
Returns Duty cycle as output for the switching device in the boost converter
*/

// Wiring:
// A0 - Voltage divider (solar)
// A1 - Voltage divider (battery)
// D3 - 2104 MOSFET driver IN    (needs to be 3 or 11 with safe timer) (PWM)
// D5 - 2104 MOSFET driver SD    (needs to be a PWM pin)

#define panelMeter A0         // Analog input pin for PV voltmeter
#define batteryMeter A1       // Analog input pin for battery voltmeter
#define driver 3              // PWM output pin to mosfet driver (needs to be 3 or 11 with safe timer)
#define Vbulk 48              // Bulk voltage set-point (Volts)
#define lowBatt 44            // Low battery voltage set-point (Volts)
#define Vmax 52               // Maximum voltage the batteries should hit before throwing an error (Volts)
#define check 15000           // 15 seconds in milliseconds
#define Vfloat 48             // Float voltage set-point (Volts)

// Variables
int V_pv;                    // PV voltage
int I_pv;                    // PV current
int V_bus;                   // Bus voltage
int I_bus;                   // Bus current

// Functions
int dutyCycle(int V_pv, int I_pv, int V_bus, int I_bus); // Calculates duty cycle for the boost converter

void setup() {
  // put your setup code here, to run once:
  pinMode(driver, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  V_pv = analogRead(panelMeter);
  V_bus = analogRead(batteryMeter);
  I_pv = 0;
  I_bus = 0;
  analogWrite(driver, dutyCycle(V_pv, I_pv, V_bus, I_bus));
  delay(check);
}

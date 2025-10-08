## 🧪 Measuring GPIO/Internal Resistance

Sometimes, the Arduino GPIO pin cannot provide the full 5 V when driving a load.  
To improve **low-resistance measurements**, we need to account for the **internal resistance of the GPIO pin** (or wiring).

### Circuit

GPIO (5V)
│
│
[Rload] ← known resistor (e.g., 100 Ω)
│
│
True GND


- **Rload**: precision resistor (e.g., 100 Ω)  
- **GND**: true ground  

---

### Steps

1. Connect **Rload** between GPIO pin and GND.  
2. Measure voltage across Rload with a multimeter → `V_actual`.  

---

### Formula

1. Calculate current through the resistor:

\[
I = \frac{V_\text{actual}}{R_\text{load}}
\]

2. Calculate internal resistance of the GPIO pin:

\[
R_\text{internal} = \frac{V_\text{ref} - V_\text{actual}}{I}
\]

Where:  
- **V_ref** = nominal GPIO voltage (5 V)  
- **V_actual** = measured voltage across Rload  

---

### Notes

- GPIO pins cannot provide exactly 5 V under load; the difference is due to **internal resistance**.  
- Lower Rload → higher current → more accurate measurement of R_internal.  
- Apply `R_internal` as a correction factor in your LCR meter code to improve **low-resistance readings**:

```cpp
double Rx_corrected = Rx_measured - R_internal;



## 🧪 ADC Offset / Zero Error Calibration

Arduino ADCs sometimes do **not read exactly 0 V** when the input is connected to GND.  
This is called **offset error** and can affect all measurements if not corrected.

### Circuit

A0 (Analog Pin)
│
│
GND



- Connect the analog input pin to **true ground**.  
- This ensures the ADC reads **0 V** as a baseline.

---

### Steps to Calibrate

1. Set the analog pin to INPUT mode:

pinMode(A0, INPUT);
Read the ADC value when connected to GND:

Copy code
int ADC_read = analogRead(A0);
If the ADC reading is not zero, record it as ADC_offset.

Subtract ADC_offset from all future ADC readings:

Copy code
int ADC_corrected = analogRead(A0) - ADC_offset;

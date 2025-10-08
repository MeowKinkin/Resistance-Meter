# ⚡ Arduino LCR Meter – Resistance Measurement Mode

## 📘 Overview  
This project is a part of the **Arduino LCR Meter**, designed to measure **unknown resistances (Rx)** using the **voltage divider principle**.  
By combining the unknown resistor with known resistors and reading voltage differences via Arduino ADC pins, the system calculates the resistance across a wide range (from a few ohms to tens of megaohms).

---

## ⚙️ Principle  

The circuit forms a **voltage divider** with the unknown resistor (Rx) and selected known resistors (R1–R4).  
The voltage across Rx is measured using two ADC pins:

\[
V_x = V_1 - V_2
\]

Then, the resistance is calculated using:

\[
R_x = \frac{V_x \cdot (a + b)}{V_{cc} - V_x}
\]

Where:  
- **Vx** = voltage drop across Rx  
- **a, b** = values of the known resistors used for the selected range  
- **Vcc** = supply voltage (5V)  

---

## ⚡ Circuit Diagram (ASCII Representation)

        D8 ── R1 ──┐
        (5V)       │
                   ├── A0 (TP1)
        D9 ── Rx ──┘
                   │
        D10 ── R3 ──┐
        (GND)       │
                   ├── A1 (TP2)
        D11 ────────┘





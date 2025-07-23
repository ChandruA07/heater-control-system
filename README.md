
---

## 🧠 System Overview

- **Input**: Potentiometer (simulates a temperature sensor in Wokwi)
- **Microcontroller**: ESP32 (Arduino + FreeRTOS)
- **FSM States**:
  - `Idle`
  - `Heating`
  - `Stabilizing`
  - `Target Reached`
  - `Overheat`
- **Output**:
  - LED simulates heater relay
  - Buzzer/LED for visual or audible feedback
  - Serial output for logging

---

## 🚀 Features Implemented

✅ Real-time heater state control via FSM  
✅ Temperature band-based stabilization  
✅ Overheat detection and safe shutdown  
✅ Modular code with state-specific logic  
✅ Wokwi simulation for testing and demonstration  

---

## 🌐 Simulation Link

🔗 [Click here to open in Wokwi](https://wokwi.com/projects/437167659432091649)

---

## 🎯 Basic Project (Entry-Level Logic)

- Implements simple threshold logic:
  - Heater turns ON below target
  - Heater turns OFF above target
- Best for understanding initial sensor-actuator control

📂 Code: `basic-project/main.ino`

---

## 🚀 Advanced Project (FSM & Control Logic)

- Full FSM-based heater state machine
- Includes logic for:
  - Target temperature band
  - Time-based stabilization
  - Overheating detection and reset
- Designed for future integration with BLE and profiles

📂 Code: `advanced-project/heater_control_with_profiles.ino`

---

## 📡 Communication Protocol (Recommended)

**I2C** selected for real-world design due to:
- Low pin usage
- Multi-device support
- Strong Arduino/ESP32 integration

---

## 🔮 Future Roadmap

| Feature                     | Description                                                                 |
|-----------------------------|-----------------------------------------------------------------------------|
| 🚨 Overheating Protection   | Buzzer alert + auto shutdown on over-temp                                   |
| 🌡️ Multiple Heating Modes   | User-selectable modes (Eco, Rapid, Standard) via BLE                        |
| 📲 Mobile App Integration   | BLE control and status feedback                                             |
| 🧠 PID Control (Optional)   | For precise temperature stabilization                                       |
| 📊 Data Logging             | Using SD card or internal flash for temp history                           |

---

## 🛠️ Tech Stack

- **Board**: ESP32 (Wokwi simulator)
- **Language**: C++ (Arduino IDE)
- **Environment**: FreeRTOS (Simulated in Wokwi)
- **Simulation Tool**: [Wokwi](https://wokwi.com/)
- **Tools**: Serial Monitor, State Diagrams, FSM Model

---

## 📸 Screenshots

![Simulation Screenshot](wokwi-screenshots/basic_run.png)

---

## 👨‍💻 Author

**Chandrashekhar R Angadi**  
Electrical & Electronics Engineer | Embedded Systems Enthusiast  
[LinkedIn](https://linkedin.com/in/your-profile) *(Optional)*

---

## 📄 License

This project is created as part of an intern assignment and is open for educational and demonstrative purposes.

---


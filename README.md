
---

##  System Overview

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
- [**System Design :**](https://github.com/ChandruA07/heater-control-system/blob/main/Wokwi_Results/System_design.png)
- [**Documents :**](https://github.com/ChandruA07/heater-control-system/tree/main/Documents)
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

## 🎯 Heat Controler (Entry-Level Logic)

- Implements simple threshold logic:
  - Heater turns ON below target
  - Heater turns OFF above target
- Best for understanding initial sensor-actuator control

📂 [Code:](https://github.com/ChandruA07/heater-control-system/tree/main/HeatControler)

---

## 🚀 Heater Controler Advertising

- Full FSM-based heater state machine
- Includes logic for:
  - Target temperature band
  - Time-based stabilization
  - Overheating detection and reset
- Designed for future integration with BLE and profiles

📂 [Code:](https://github.com/ChandruA07/heater-control-system/tree/main/Heater_Controler_Advertising)

---

## 📡 Communication Protocol 

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
| 🧠 PID Control              | For precise temperature stabilization                                       |
| 📊 Data Logging             | Using SD card or internal flash for temp history                           |

---

## 🛠️ Tech Stack

- **Board**: ESP32 (Wokwi simulator)
- **Language**: C++ (Arduino IDE)
- **Environment**: FreeRTOS (Simulated in Wokwi)
- **Simulation Tool**: [Wokwi](https://wokwi.com/)


---

## 📸 Screenshots

![Simulation Screenshot](https://github.com/ChandruA07/heater-control-system/tree/main/Wokwi_Results)

---

## 👨‍💻 Author

**Chandrashekhar R Angadi**  
Electrical & Electronics Engineer | Embedded Systems Enthusiast  
[LinkedIn](https://www.linkedin.com/in/chandrashekhar-r-angadi-6028b2229/)

---

## 📄 License

This project is created as part of an intern assignment and is open for educational and demonstrative purposes.

---


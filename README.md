# Team-68 – Visionary ADAS

Visionary ADAS (Advanced Driver Assistance System) is a comprehensive project that integrates both hardware and software to deliver real-time vehicle safety, object detection, navigation, and driver assistance features. The system leverages embedded hardware (Arduino, ESP32) and a modern Swift-based macOS/iOS application with machine learning for object detection.

---

## Table of Contents

- [Project Overview](#project-overview)
- [Features](#features)
- [Architecture](#architecture)
- [Hardware](#hardware)
  - [Arduino Uno](#arduino-uno)
  - [ESP32](#esp32)
- [Software](#software)
  - [ADAS macOS/iOS App](#adas-macosiOS-app)
  - [Machine Learning Model](#machine-learning-model)
- [Getting Started](#getting-started)
  - [Hardware Setup](#hardware-setup)
  - [Software Setup](#software-setup)
- [Contributing](#contributing)
- [License](#license)

---

## Project Overview

Visionary ADAS is designed to enhance vehicle safety and driver awareness by combining real-time object detection, navigation, and vehicle status monitoring. The system consists of:

- Embedded hardware for sensor data acquisition and basic vehicle control.
- A Swift-based application for advanced driver assistance, object detection, and user interface.
- Integration of a CoreML model for real-time object recognition (vehicles, pedestrians, etc.).

---

## Features

- **Real-Time Object Detection:** Detects vehicles, pedestrians, buses, and trucks using a CoreML model.
- **Camera Integration:** Supports both built-in and iPhone (Continuity) cameras for video input.
- **Navigation & Mapping:** Displays current location, navigation routes, and next-turn information.
- **Vehicle Status Monitoring:** Shows speed, direction, and other vehicle metrics.
- **Music Player Integration:** In-app music player for driver convenience.
- **Safety Alerts:** Provides warnings for obstacles, line tracking, and potential collisions.
- **Remote Control & Line Tracking (Hardware):** Arduino-based vehicle control with IR remote and line sensors.

---

## Architecture

```
HARDWARE (Arduino, ESP32, Sensors)
    |
    |  (Serial/Bluetooth/WiFi)
    v
SOFTWARE (Swift macOS/iOS App)
    |
    |-- Camera Input & Object Detection (CoreML)
    |-- Navigation & Mapping (MapKit)
    |-- Vehicle Status & Safety Alerts
    |-- User Interface (SwiftUI)
```

---

## Hardware

### Arduino Uno

- **Functions:** Obstacle detection (ultrasonic), line tracking, motor control, IR remote control.
- **Key Components:** L298N motor driver, ultrasonic sensor, IR receiver, servo motor, line sensors.
- **Features:** Stops or maneuvers vehicle on obstacle detection, deploys "airbag" (alert), follows lines, responds to remote commands.

**File:** `HARDWARE/Arduino_Uno_code.ino`

### ESP32

- **Functions:** Motor control testing and demonstration.
- **Key Components:** Motor driver pins.
- **Features:** Tests forward/backward movement of left/right motors.

**File:** `HARDWARE/ESP_32_code/ESP_32_code.ino`

---

## Software

### ADAS macOS/iOS App

- **Language:** Swift (SwiftUI)
- **Main Features:**
  - **CameraManager:** Handles camera input, switching between built-in and iPhone cameras.
  - **ObjectDetector:** Uses CoreML and Vision to detect objects in real-time.
  - **MapView:** Displays navigation, route, and vehicle location.
  - **ContentView:** Main UI, integrates all panels (vehicle status, navigation, camera, music, safety).
  - **MetricsPanel, SafetyFeaturesView, ControlPanelView:** Modular UI components for status and controls.

**Key Files:**
- `SOFTWARE/ADASSystem/ADASSystem/ContentView.swift`
- `SOFTWARE/ADASSystem/ADASSystem/CameraManager.swift`
- `SOFTWARE/ADASSystem/ADASSystem/ObjectDetector.swift`
- `SOFTWARE/ADASSystem/ADASSystem/MapView.swift`
- `SOFTWARE/ADASSystem/ADASSystem/ADAS_Safety_System1.mlmodel` (CoreML model)

### Machine Learning Model

- **Model:** `ADAS_Safety_System1.mlmodel`
- **Purpose:** Detects objects (bus, truck, pedestrian, car) in camera frames.
- **Integration:** Used via Vision/CoreML in the Swift app.

---

## Getting Started

### Hardware Setup

1. **Arduino:**
   - Upload `Arduino_Uno_code.ino` to your Arduino Uno.
   - Connect sensors and motor driver as per pin definitions in the code.
   - Power the Arduino and test obstacle avoidance, line tracking, and remote control.

2. **ESP32:**
   - Upload `ESP_32_code.ino` to your ESP32.
   - Connect motor driver as per pin definitions.
   - Use Serial Monitor to observe motor test outputs.

### Software Setup

1. **Requirements:**
   - macOS with Xcode installed (for SwiftUI app).
   - iOS device (optional, for Continuity Camera).
   - Swift 5.x, CoreML, Vision, MapKit.

2. **Running the App:**
   - Open `SOFTWARE/ADASSystem/ADASSystem.xcodeproj` in Xcode.
   - Build and run the app on your Mac (or iOS device if supported).
   - Grant camera permissions when prompted.
   - Select camera source, view detections, navigation, and vehicle status.

---

## Contributing

Contributions are welcome! Please fork the repository and submit a pull request. For major changes, open an issue first to discuss your ideas.

---

## License

This project is licensed under the MIT License.

---

**Note:** For detailed pin connections, hardware schematics, and further documentation, please refer to comments in the `.ino` files and the Swift source code.
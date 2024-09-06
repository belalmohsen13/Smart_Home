# 🚀 Smart Home Control System

## 📝 Description

The **Smart Home Control System** is an embedded application developed using an AVR microcontroller. The system allows users to control various components of a smart home, such as LEDs, fans, and a fire detection system, via a keypad and LCD interface. Additionally, the system communicates with the user through a terminal using **USART**, where users can log in using predefined credentials and navigate through the control options.

---

## 🌟 Features

- **User Authentication**: Two users with distinct ID and password combinations.
- **Room Control**: Control LEDs and fans in different rooms through the keypad interface.
- **Fire Detection**: Continuously monitors the temperature and triggers a fire alarm if the temperature exceeds a set threshold.
- **USART Communication**: Provides a welcome message and feedback through the serial terminal.
- **LCD Interface**: Displays system messages and options for easy navigation.

---

## ⚙️ Components

- **AVR Microcontroller**: Central unit controlling the entire system.
- **LCD Display**: Provides a user interface for interaction.
- **Keypad**: Used for entering user credentials and controlling devices.
- **LEDs and Fans**: Represent the devices in rooms that can be controlled by the user.
- **Temperature Sensor**: Monitors temperature to trigger fire alerts.
- **USART**: Used to communicate with a terminal for status messages and user interaction.

---

## 🛠 Prerequisites

To run this project, you'll need:

- **AVR Studio / Atmel Studio** for development.
- **AVR-GCC** compiler for building the project.
- An **AVR microcontroller** (e.g., ATmega32).
- **Keypad**, **LCD display**, **LEDs**, **temperature sensor**, and other peripheral hardware.

---

## 🚀 How to Use

1. **Power on the system**: The terminal will display a welcome message.
2. **User Authentication**: Enter your user ID and password via the keypad.
3. **Control Devices**: Once logged in, navigate through the menu to control LEDs, fans, and other devices in rooms.
4. **Fire Detection**: The system will monitor the temperature continuously. If it exceeds **55°C**, a fire alert will be triggered.
5. **Logging out**: The system allows users to log out and resets to the login screen.

---

## 🗂 Code Structure

- **main.c**: Contains the main logic for controlling rooms and the authentication process.
- **DIO_interface.c**: Handles input/output pin control for AVR ports.
- **CLCD_interface.c**: Manages LCD screen operations.
- **Keypad_interface.c**: Manages keypad input.
- **USART_interface.c**: Handles serial communication with the terminal.
- **ADC_interface.c**: Handles the temperature sensor readings via ADC.

---

## 🔮 Future Enhancements

- Adding more rooms and devices for control.
- Integrating a mobile app for remote control.
- Implementing a more secure login system with dynamic user creation.

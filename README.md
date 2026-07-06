<div align="center">

# Kintsugi Style Digital Clock & Alarm

*A minimalist Kintsugi-inspired digital alarm clock built for Hack Club's **BLARE** YSWS.*

<!-- Hero Image -->
<img width="1920" height="812" alt="Digital Alarm Clock by Nemo" src="https://github.com/user-attachments/assets/b7802b09-2d5b-4347-b7f0-a6f7fb421afc" />

</div>

---

## About

This is a custom designed digital alarm clock inspired by the Japanese art of Kintsugi the philosophy of embracing imperfections by repairing them with gold.
Instead of hiding cracks, the front of the enclosure celebrates them, turning a simple bedside clock into a small desk piece.
The project is being built for Hack Club BLARE using an ESP32 C3, a TFT display, mechanical switches, and a custom 3D printed enclosure.

## Features

- Digital clock with automatic Wi-Fi time synchronization.
- Alarm that can be set using 5 buttons.
- Custom 3D printed enclosure.
- Kintsugi inspired front panel for the enclosure.
- Piezo buzzer beep alarm.
- Alarm settings saved to memory.

---

## Exploded View

<img width="1920" height="812" alt="Digital Alarm Clock by Nemo6" src="https://github.com/user-attachments/assets/b97d8ea3-52b4-4e12-a94c-b8d400c6c437" />
<img width="1920" height="812" alt="Digital Alarm Clock by Nemo5" src="https://github.com/user-attachments/assets/b149e75b-3fd1-4d61-8d61-f57e537facfd" />

The enclosure consists of two main printed components:

- Front shell
- Removable back plate secured using M3×8 mm screws

The removable back plate makes assembly, wiring, and future maintenance much easier while keeping the outside clean.

---

## BOM (Bill of Materials)

| Component | Purpose |
|-----------|---------|
| ESP32-C3 Mini | Main controller |
| TFT Display | Clock display |
| 5 MX Key/Switches | Alarm controls |
| Piezo Buzzer | Alarm output |
| Jumper Wires | Hand-wired connections |

---

## Circuit Diagram

<img width="1645" height="806" alt="circuitv3" src="https://github.com/user-attachments/assets/b4fd38fa-f262-438a-8dc9-300a8453056e" />

---

## Firmware

The firmware is written using the Arduino IDE and is designed around the following libraries:

- Adafruit GFX
- Adafruit ST7789
- WiFi
- Preferences
- SPI

Current firmware features include:

- Automatic NTP time synchronization.
- Alarm storage in memory.
- Alarm controls.
- Wi-Fi reconnect support.

---

## Gallery

<table>
<tr>
<td width="50%">
<img width="100%" alt="Screenshot (96)" src="https://github.com/user-attachments/assets/2699964e-956b-4430-b104-35fb85a8dc7f" />
</td>
<td width="50%">
<img width="100%" alt="Screenshot (97)" src="https://github.com/user-attachments/assets/ff8592b6-2ccb-40ec-a24a-2c3034fa9cd9" />
</td>
</tr>

<tr>
<td width="50%">
<img width="100%" alt="Screenshot (98)" src="https://github.com/user-attachments/assets/d53408c4-b8d6-4ce7-ad4b-56d43ee947f3" />
</td>
<td width="50%">
<img width="100%" alt="Screenshot (99)" src="https://github.com/user-attachments/assets/ff23283a-6d91-472f-88e8-755ad8089629" />
</td>
</tr>

<tr>
<td width="50%">
<img width="100%" alt="Screenshot (101)" src="https://github.com/user-attachments/assets/4a2b8933-b26a-4e34-8a9f-2f10bd86d73c" />
</td>
<td width="50%">
<img width="100%" alt="Screenshot (100)" src="https://github.com/user-attachments/assets/41ed30f7-b4f0-40e3-a860-a1cb78f2af0b" />
</td>
</tr>

<tr>
<td width="50%">
<img width="1920" height="812" alt="Digital Alarm Clock by Nemo4" src="https://github.com/user-attachments/assets/8cf8ff09-1706-48a0-a006-994db2621339" />
</td>
<td width="50%">
<img width="1920" height="812" alt="Digital Alarm Clock by Nemo5" src="https://github.com/user-attachments/assets/8194add8-cf10-4dcc-ba36-2dcbc9ed5a76" />
</td>
</tr>

<tr>
<td width="50%">
<img width="1920" height="812" alt="Digital Alarm Clock by Nemo3" src="https://github.com/user-attachments/assets/bd260514-c78a-43fc-a41e-eb73c3469e3f" />
</td>
<td width="50%">
<img width="1920" height="812" alt="Digital Alarm Clock by Nemo" src="https://github.com/user-attachments/assets/593648d6-539c-4395-9a22-56ef74e29eb5" />
</td>
</tr>
</table>

---

# JARViE I2C/SPI/GPIO Extender 
The Extender is JARViE's solution to sending up to 1 MHz data rates over cables up to 150 ft long. It uses the Texas Instrument's P82B715 buffer to send I2C, SPI and or digital I/O communications over long cables. 

Sending signals over long cables is a challenge!  One has to account for the cable transmission properties and how it relates to electrical properties of the device sending the signals down the cable (Device A) and the device receiving it on the other end (Device B). The capacitive, inductive and resistive properties of the cable between the devices has an affect on the signal sent from Device A to B.  The cable capacitance will affect max bus speed because bus capacitance is inversely proportional to the max data transmission rate. The cable resistance will cause the signal to attenuate or decrease in amplitude. The cable inductance will choke/reduce the max current the cable can carry as the frequency of the signal increases. 

I2C and SPI were designed to be used in-PCB, so the total bus length shouldn't exceed about 50cm using standard bus speeds. Though reducing the bus speed can enable successful bus communications over longer cables, it is recommended to 
keep bus lengths at 1-2m maximum for I2C and SPI. 
 

![Board](https://raw.githubusercontent.com/DudeYarvie/JARViE_Bus_Extender/main/Reference%20Docs/Pics/DIO_Redriver_Resized_GitHub.jpg "Board")

## Product Features
- Can transmit I2C/SPI/GPIO signals over 150 ft of twisted pair cable
- Two user defined LEDs (yellow, green) on RJ45 connector
- Supports bidirectional data transfer (required for I2C SDA data signal)
- Allows bus capacitance of 400 pF on device/host side of I2C Bus and 3000 pF on the cable side
- Dual bidirectional unity-voltage-gain buffer with no external directional control required
- Drives 10× lower impedance bus wiring/cabling for improved noise immunity
- Supports multi-drop distribution using low cost twisted-pair cables
- Latch-up performance exceeds 100 mA per JESD 78, Class II

## How to Order
[Purchase Boards](https://www.tindie.com/products/jarvie/jarvie-extender-send-i2cspidio-up-to-150ft/)

<a href="https://www.tindie.com/stores/jarvie/?ref=offsite_badges&utm_source=sellers_JARViE&utm_medium=badges&utm_campaign=badge_large"><img src="https://d2ss6ovg47m0r5.cloudfront.net/badges/tindie-larges.png" alt="I sell on Tindie" width="200" height="104"></a>

## DEVICE Pin Descriptions
| **Pin #** | **Signal Name** | **I/O** | **Description** |
| :--------: | :--------: | :--------: | :---------------- |
| 1 | GREEN LED| I | Green LED on RJ45 connector for indication. **Only drive LED from DEVICE HDR pins.**|
| 2 | HOST CLK | I/O | Unbuffered data bus. Connect to I2C/SPI/DIO. Signal has a 4.7k pull-up. HOST CLK and SDA circuitry are the same so pins are interchangeable. |
| 3 | HOST SDA| I/O | Unbuffered data bus. Connect to I2C/SPI/DIO. Signal has a 4.7k pull-up. HOST CLK and SDA circuitry are the same so pins are interchangeable. |
| 4 | GND | — | Ground |
| 5 | VCC | — | Buffer power supply input, sets I2C bus voltage level, rated for 3V min 12V max. **If constructing a buffered cable, connect a power supply to VCC on one side of the cable only!** |
| 6 | YELLOW LED | I | Yellow LED on RJ45 connector for indication. **Only drive LED from DEVICE HDR pins.** |

## J1 Pin Descriptions 
| **Pin #** | **Signal Name** | **I/O** | **Description** |
| :--------: | :--------: | :--------: | :---------------- |
| 1 | VCC | — | Buffer power supply input, sets I2C bus voltage level, rated for 3V min 12V max, Buffer supply current = 22 mA @ VCC = 12 V.  **If constructing a buffered cable, connect a power supply to VCC on one side of the cable only!** |
| 2/3/5/7/8/A1/A3 | GND | — | Ground |
| 4 |CABLE SDA| I/O | Buffered data bus. Route this pin to long cable. Signal has a 300 Ohm pull-up to drive signal down long wires. CABLE CLK and SDA circuitry are the same so pins are interchangeable. |
| 6 | CABLE SCL | I/0 | Buffered data bus. Route this pin to long cable. Signal has a 300 Ohm pull-up to drive signal down long wires. CABLE CLK and SDA circuitry are the same so pins are interchangeable. |
| A2 | YELLOW LED | I | Yellow LED on RJ45 connector for indication. **Only drive LED from DEVICE HDR pins.** |
| A4 | GREEN LED | I | Green LED on RJ45 connector for indication. **Only drive LED from DEVICE HDR pins.** |

# **How It Works**
Place the JARVIE Extender on each side of a cable terminated with an RJ45 connector plug.  Connect the I2C/SPI/DIO signals of each device directly to the HOST pins of the extender(s).  The circuitry on the extender automatically detects the hardware flow (e.g. device A is sending data to device B or vice-versa).  To overcome the large capacitance of the long cable, the extender draws 10x more current on the long cable side when a logic LOW or 0 bit is transmitted between devices A and B.  Drawing 10x more current on the cable side quickly discharges the cable capacitance allowing for fast and clean high-to-low signal transitions.  The pull-ups on the cable-side of the buffer will quickly source current/charge to the cable capacitance.  This allows for fast and clean low-to-high signal transitions.  Clean signal transitions are required for successful bus communications, especially over long cables. 

![Using buffer with long cables](https://raw.githubusercontent.com/DudeYarvie/JARViE_I2C_Bus_Extender/main/Reference%20Docs/Pics/Application%20Diagram.JPG "Cable Application Diagram")

# **Specifications**

## Mechanical 
Dimensions are in inches.
![Board Dimensions](https://raw.githubusercontent.com/DudeYarvie/JARViE_I2C_Bus_Extender/main/Reference%20Docs/Pics/Board_Dimensions.JPG "Mechanical Dimensions")

## Electrical 
| **Parameter** | **Value** |
| :-------- | :------------- |
| VCC supply voltage | 4.5 - 12 V |
| Buffer supply current | 22 mA @ VCC = 12 V |
| User defined LED forward current | 2 mA nominal, 10 mA max |
| User defined LED forward voltage | 1.6 V @ 2 mA |
| Host SDA/SPI/DIO source/sink current | -3 mA max/+3 mA min | 
| Host CLK/SPI/DIO source/sink current | -3 mA max/+3 mA min |
| Cable SDA/SPI/DIO source/sink current | -3 mA max/+30 mA min | 
| Cable CLK/SPI/DIO source/sink current | -3 mA max/+30 mA min |

## Data Transmission
For this section, device A = Master and device B = Slave.

+5V I2C transactions were monitored between master (Arduino MEGA 2560) and slave (Arduino UNO) devices connected together with a 100ft twisted-pair cable.  The following oscilloscope (scope) captures provide insight on signal amplitude, offset and rise/fall times. 

### Voltage High & Low
![Voltage high and low measurements](https://raw.githubusercontent.com/DudeYarvie/JARViE_I2C_Bus_Extender/main/Reference%20Docs/Pics/Vhigh_Vlow_Measurements.jpg "Voltage high and low measurements")


### Rise-Time (10-90%)
![Rise Time](https://raw.githubusercontent.com/DudeYarvie/JARViE_I2C_Bus_Extender/main/Reference%20Docs/Pics/10_90_Rise_Time.jpg "Rise Time")

### Fall-Time (10-90%)
![Fall Time](https://raw.githubusercontent.com/DudeYarvie/JARViE_I2C_Bus_Extender/main/Reference%20Docs/Pics/10_90_Fall_Time.jpg "Fall Time")

## Cable Pulse Response  
Two buffered cables were constructed using a 10ft and 100ft cat6e cable terminated with the JARViE Extender on both ends (see image in product listing). A 0 to +5V square pulse was generated and sent down each cable using an Arduino Mega 2560 development board.  The other end of the cable was loaded with an Arduino Uno development board.  An oscilloscope was placed at both ends of the cable to capture what the pulse looked like after traveling from the start/generator side of the cable to the end/load side of the cable. Ideally, the square pulse sent is identical to the pulse received at the other end of the cable. Due to the capacitive, resistive and inductive properties of the cable and development board I/O ports, this was not the case. The signal was distorted, delayed and or smaller in amplitude.  

The figures below show,

- Cable length and pulse speed affected the pulse captured at the load side of the cable. 
- Signal overshoot increased as cable length and or pulse frequency increased.  Overshoot voltages can exceed bus overvoltage limits on the devices connected to the cable.  This can damage devices or cause communication buses to latch-up.** Device hardware should provide overshoot protection and a way to reset/unlatch the bus. **
- A time delay developed between the sent and received pulse as cable length increased.  Users have to know that when the source sends a data bit, its going to appear at the load side device "t" seconds later in time. These delays may need to be accounted for in device firmware or hardware to ensure successful communications between devices.

### 1 kHz
![10ft Cable Pulse Response](https://raw.githubusercontent.com/DudeYarvie/JARViE_I2C_Bus_Extender/main/Reference%20Docs/Pics/Square_Wave_1kHz_10ft_cable_annotated.jpg "10ft Cable Pulse Response")

![100ft Cable Pulse Response](https://raw.githubusercontent.com/DudeYarvie/JARViE_I2C_Bus_Extender/main/Reference%20Docs/Pics/Square_Wave_1kHz_100ft_cable_annotated.jpg "100ft Cable Pulse Response")

### 100 kHz
![10ft Cable Pulse Response](https://raw.githubusercontent.com/DudeYarvie/JARViE_I2C_Bus_Extender/main/Reference%20Docs/Pics/Square_Wave_100kHz_10ft_cable_annotated.jpg "10ft Cable Pulse Response")

![100ft Cable Pulse Response](https://raw.githubusercontent.com/DudeYarvie/JARViE_I2C_Bus_Extender/main/Reference%20Docs/Pics/Square_Wave_100kHz_100ft_cable_annotated.jpg "100ft Cable Pulse Response")

### 500 kHz
![10ft Cable Pulse Response](https://raw.githubusercontent.com/DudeYarvie/JARViE_I2C_Bus_Extender/main/Reference%20Docs/Pics/Square_Wave_500kHz_10ft_cable_annotated.jpg "10ft Cable Pulse Response")

![100ft Cable Pulse Response](https://raw.githubusercontent.com/DudeYarvie/JARViE_I2C_Bus_Extender/main/Reference%20Docs/Pics/Square_Wave_500kHz_100ft_cable_annotated.jpg "100ft Cable Pulse Response")

## Eye Diagram
A 1 MHz square wave was driven down a 100ft cat6e cable buffered with a JARViE I2C/SPI/GPIO Extender on both ends. No devices were connected to the load side of the cable, so this is an open load measurement.  Here's a scope capture of the square wave received at the load/slave device side of the cable,
![1MHz_Square_Wave](https://raw.githubusercontent.com/DudeYarvie/JARViE_I2C_Bus_Extender/main/Reference%20Docs/Pics/Square_Wave_1MHz_100ft_Cable.JPG "1MHz_Square_Wave")

An eye diagram was generated by placing the oscilloscope in *persistence* mode, configuring the scope to trigger on either falling or rising edges and acquiring 12,614 samples. The diagram shows that a 1MHz signal and or communications bus could send data over a 100ft twisted pair cable with minimal noise or high signal-to-noise ratio (SNR) which means less bits being corrupted or dropped, implying good communications.
![Eye_Diagram](https://raw.githubusercontent.com/DudeYarvie/JARViE_I2C_Bus_Extender/main/Reference%20Docs/Pics/Eye_Diagram_Square_Wave_100ft_Cable.JPG "Eye_Diagram")

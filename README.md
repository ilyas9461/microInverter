
## **Grid Connected Micro Inverter 17-06-2016**

### Introduction :
Renewable resources such as wind power generation and Photovoltaic (PV) systems have gained great visibility as viable and promising renewable energy sources in the last few years.

The recent increase in demand for solar energy systems is due to advances in the production of crystalline panels, which reduce the overall costs of production and increase the efficiency of PV panels. Additional reasons for the demand for solar energy are PV technology, proven and reliable, PV modules with warranties exceeding 30 years, and government incentives.

There are two basic requirements for solar inverter systems: collecting available energy from the PV panel and injecting a sinusoidal current into the grid in phase with the grid voltage. A Maximum Power Point Tracking (MPPT) algorithm is required to harvest energy from the PV panel. This algorithm determines the maximum amount of power available from the PV module at any given time. Interfacing to the grid requires solar inverter systems to comply with certain standards issued by utility companies.

The Solar Micro Inverter Reference Design is a single-stage, grid-connected, solar PV micro inverter. This means that the DC power from the solar panel is directly converted into an AC signal. This conversion is done by an interleaved flyback converter. A Full Bridge (drop-down) converter switched at 2x line frequency controls the direction of power flow to the grid. This microinverter is designed to connect to any PV module with a power rating of approximately 250 watts with an input voltage range of 25 VDC to 45 VDC and a maximum open circuit voltage of ~55V.


### **The Subject of The Project :** 
- Micro Inverter
- PIC33F mikrocontroller
- XC16 PIC C Compiler 
- PCB ddesign 
- Fixed Point numbers and arithmetic.
- Power Electronics (Buck-Boost Converter structures)
- Control systems (PID structures)
- Matlab models

### **Note :**

The hardware tests have been completed on the PCB prepared in this form of the project. Simply, the incandescent lamp was turned on by software setting the output voltage to 100V with the adjusted DC voltage supplied externally. 100W output was available.

Project work was terminated due to unobtainable reasons before the process of creating control structures could be achieved. Therefore, control structures are missing in the software developed in this repository.

Using the source codes in the application note. Appropriate structures can be created.






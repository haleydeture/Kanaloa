## Notes:

**Cold grnd to DACs**
- Remove black wire on low current box between _LC-TB-5-8_ to _LC-TB-1-9_

**No Connection L4-H4**
- ~~Arduino Pins 22,24,26,28,30 on _LC-TB-4_~~
- **_For the following note above, those pins are for the reverse contactors_** -Daniel
  - Pin 22 -> Q1RevContactors
  - Pin 24 -> Q2RevContactors
  - Pin 26 -> Q3RevContactors
  - Pin 28 -> Q4RevContactors
  - Pin 30 -> RevContactors Kill Signal
  
**Does Terminal Block HC-TB-3 have a ground? (3 connections to kill switch)**
- Move to pins on main Arduino in low current box.
- ~~Requires 3 optical filters for digital signal if kill switch does not move~~
- Update on above: Kai did move the kill switch -Daniel


## Grounds from Low Current: ##
Grounds follows the following path (read list from top to bottom, it goes from high current box to low current) Nested lists indicate junctions unless noted otherwise. See diagrams for bus bar notation.

###### Kill Arduino ######
- Vin from HC-TB-1-1 
- LC-TB-3-9
  - LC-TB-1-9
  - Black wire on bread board low pass filter

###### Motor Controller Signals ######
- HC-TB-1-9
- LC-TB-3-9
  -LC-TB-1-9
  -Black wire on breadboard low pass filter
  
###### General Large Wire For Common Ground from Main Power Supply to High Current Box ######
- 10 AWG Black/Red pair from XL Black Terminal Block.
  - **Black Wire Path**
  - HC-TB-1-9
  - LC-TB-3-9
    - LC-TB-1-9
    - Black wire on bread board low pass filter
 - Testing
 
 **_Lisa, I do not know how to represent your notes about the red 10 AWG_**
 
## Signals for filter between boxes ##
**_Total Filters Required: 12_**
- 1.) Voltage divider
  - move as above (low current box (?))
  - LC-TB-5-5 will get new small 22 AWG to a NEW digital pin on Arduino (not analog A0)
  - HC-TB-2-13 to digital output of voltage divider Arduino (new)
- 2.) Q1-Q4 input signal
  - HC-TB-2-(Terminals 9-12) will have 4 optical filters
  - PWM to Motor Controllers (From NO INPUT?) LC-TB-5-(Terminals 1-4) 
  - Note of above Terminals 1-4 on TB-5 are motor controls PWM outputs to HC box. -Daniel
- 3.) Kill Arduino
  - 2 signals on HC-TB-1-(Terminals 10-11) from LC-TB-3-(Terminals 10-11)
- 4.) Forward/Rev Contactors
  - 5 signals
 
 
 
 
 

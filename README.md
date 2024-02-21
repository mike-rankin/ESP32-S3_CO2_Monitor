# ESP32-S3-CO2-Monitor
This is the wall charger mount version of the co2 monitor has been slowly evolving for a while.
It started out as a sensor on qwiic connector but was too messy with the two cables <br/>

![Qwiic](https://github.com/mike-rankin/ESP32-S3_CO2_Monitor/assets/4991664/ac4c1a78-1831-40d3-baf4-e664a4b44238)
The next version elinated the cable. Because of the height of the sensor this version puts it on a seperate board and rear mounts it. From the front side all you see is the tiny hole. It requires a usb-c cable that is on the side and can sit on your desk <br/>
![stanoff_back](https://github.com/mike-rankin/ESP32-S3_CO2_Monitor/assets/4991664/0bdfd69c-7b6b-4fe7-88b5-77e3180044b4) <br/>
![stanoff_front](https://github.com/mike-rankin/ESP32-S3_CO2_Monitor/assets/4991664/cd7bcd85-266e-4c43-81ae-c1c19627d5df) <br/>
![stanoff_data](https://github.com/mike-rankin/ESP32-S3_CO2_Monitor/assets/4991664/30d217f4-5b9d-41f9-9dec-f5e328f74bad) <br/>
This version uses a make usb-c connector and is design to push onto a wall charger. No cord or cables of any kind required and to upload a new sketch you can plug it into the side of your laptop. <br/>

![Plugged_In](https://github.com/mike-rankin/ESP32-S3_CO2_Monitor/assets/4991664/4f69014d-7daf-44b5-adf0-17ec1c5ef7a7) <br/>
![Top](https://github.com/mike-rankin/ESP32-S3_CO2_Monitor/assets/4991664/fb37e600-4b05-4a9b-b6c2-cb791e634421) <br/>
![W_Charger](https://github.com/mike-rankin/ESP32-S3_CO2_Monitor/assets/4991664/53e4341c-1f8c-437a-b2ac-1d98a05d0ea0) <br/>
Revision 4 has been ordered with a few small changes. Two pushbutton on the lower right for setting the com port are now much smaller. These are only used the once and can be super small. The two pushbutton foorprints for the top buttons are hopefully corrected. A new pushbutton on the bottom will act as a power switch to test out a power switch LTC2954ITS8 that I hope to use in other projects. The device can be turned on and off with a momentaty button instead of a sliding switch and possibly turned off by a gpio pin of the micro. <br/>

The final version, Rev 5 strips away the unnecessary components like the power switch and Qwiic connector for easier assembly and lower cost




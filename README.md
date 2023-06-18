# esp32-sensor-fw

Setup esp-idf according to https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/linux-macos-setup.html

### Configure the project 

```
idf.py menuconfig
```

#### Specify the partition table
Navigate to Partition Table -> Partition Table and select "Custom partition table CSV"
![Alt text](./assets/Custom%20partition%20table%20CSV.png?raw=true "Custom partition table CSV")

Set "Custom partition CSV file" to "partitions.csv"
![Alt text](./assets/Custom%20partition%20CSV%20file.png?raw=true "Custom partition CSV file")

#### Configure WiFi

Project Configuration -> WiFi SSID
![Alt text](./assets/WiFi%20SSID.png?raw=true "WiFi SSID")
Project Configuration -> WiFi Password
![Alt text](./assets/WiFi%20Password.png?raw=true "WiFi Pasword")

### Build

```
# Set the correct target for your board
idf.py set-target esp32c3
idf.py build
```

### Run


```
# Use the correct USB device for your setup
idf.py -p /dev/ttyUSB0 flash monitor
```

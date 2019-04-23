# EdgeX J1939 Device Service User Guide

## About

The EdgeX J1939 Device Service is used to monitor/record J1939 messages in an EdgeX deployment.  This user guide is intended to supplement existing EdgeX documentation regarding device service usage.

## Supported EdgeX Version

- 0.7.1

## Supported Hardware

- Dell 3002 gateway

## Supported Operating Systems

- Ubuntu Core 16
- Ubuntu Server 18.04

## Configuration

### Driver Section

The parameters in the "Driver" section of the configuration.toml file need to be adapted to the end application.

#### ReceivePGNs

The ReceivePGNS value is the list of PGNs that will be received by the application.  Only the PGNs included in the ReceivePGNs value will be accessible from within EdgeX.

The format for the ReceivePGNs entry is: `ReceivePGNs = "PGN1, PGN2, ..., PGNX"` Where the PGN is entered in decimal format.  Up to 250 PGNs can be included in the ReceivePGNs list.

#### ApplControlInterface

The J1939 device service uses SocketCAN to interface with the CAN hardware built into the Dell 3002 gateway.  Configuration of SocketCAN interfaces (using ip link) requires root privileges, therefor the device service allows for two different methods of configuring the CAN interface.

##### ApplControlInterface = true

In this case the application has control of bringing the interface up, setting the interface type, setting the bitrate, and bringing the interface down.  In this case the application must be run with root privileges.

##### ApplControlInterface = false

In this case the user is required to setup the SocketCAN interface and the application does not require elevated privileges to run.  In this case the following commands could be issued to start, configure, and stop the interface.

``` console
$ sudo ip link set can0 type can bitrate 250000
$ sudo ip link set can0 up
--Start the application--
--Application runs--
--Stop the application--
$ sudo ip link set can0 down
```

## Example ECU Simulator Profile

The included example profile is for use with the ÖZEN Elektronik J1939 ECU simulator.  Documentation and purchase information for the ÖZEN ECU simulator is available here https://www.ozenelektronik.com/j1939-obd-ecu-simulator-p.html.

### PGNs

The ECU simulator board generates the live simulated ecu parameters below.

| PGN | PGN Name | Parameter Name | Start Position (byte) | Length (bytes) | Value |
|-----|----------------|----------------|--------|-------|-------|
|65262|Engine Temperature 1 - ET1|Engine Coolant Temperature|1|1|-40 to 215 grad variable with pot|
|65262|Engine Temperature 1 - ET1|Engine Fuel Temperature 1 |2|1|80 Fixed|
|65269|Ambient Conditions – AMB|Ambient Air Temperature|4|2|25 grad celsius|
|65269|Ambient Conditions – AMB|Engine Air Inlet Temperature|6|1|35 grad celsius|
|61444|Electronic Engine Controller 1 - EEC1|Engine Speed|4|2|0..64255 ( variable with pot )|
|61443|Electronic Engine Controller 2 - EEC2|Accelerator pedal position 1|2|1|0..250 ( variable with pot )|
|65270|Inlet/Exhaust Conditions 1 - IC1|Engine Intake Manifold #1 Pressure|2|1|0..250 ( variable with pot )|
|65132|Tachograph - TCO1|Vehicle Speed|7|2|0..64255 ( variable with pot )|

Note: For the ÖZEN Elektronik J1939 ECU simulator most non simulated values are set to 0xFF.  Please see the ÖZEN Elektronik manual for more details.

### PGN URLs

Each PGN is accessible by the URL specified in the profile file.

| PGN | URL |
|-----|-----|
|65262|{ip_address}:{service_port}/api/v1/device/{deviceId}/ET1|
|65269|{ip_address}:{service_port}/api/v1/device/{deviceId}/AMB|
|61444|{ip_address}:{service_port}/api/v1/device/{deviceId}/EEC1|
|61443|{ip_address}:{service_port}/api/v1/device/{deviceId}/EEC1|
|65270|{ip_address}:{service_port}/api/v1/device/{deviceId}/IC1|
|65132|{ip_address}:{service_port}/api/v1/device/{deviceId}/TCO1|

### PGN Data Format

The PGN data is sent to EdgeX as a hexadecimal string.

Ex: Reading EEC2 could yield "FFFAFFFFFFFFFFFF" meaning an accelerator pedal position 1 value of 250.

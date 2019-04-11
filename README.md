# EdgeX-Dell-J1939

## About

The EdgeX J1939 Device Service is developed to monitor/record J1939 messages in an EdgeX deployment

## Supported EdgeX Version

- 0.7.1

## Supported Hardware

- Dell 3002 gateway

## Supported Operating Systems

- Ubuntu Core 16
- Ubuntu Server 18.04

## Building

### Dependencies

Ubuntu/Debian:

``` console
$ sudo apt install build-essential can-utils libsocketcan-dev cmake libmicrohttpd-dev libcurl4-openssl-dev libyaml-dev
```

### Submodules

Initialize submodules: ```$ git submodule update --init --recursive```

### Make

To build the project run

``` console
$ cmake
$ make
```

## User Facing Documentation

[User facing readme](USER_README.md)
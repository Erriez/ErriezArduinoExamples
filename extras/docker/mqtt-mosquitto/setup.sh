#!/bin/bash

# Exit bash script on error
set -e

# Create volumes when not exist
mkdir -p volumes

# Copy config files to volumes
cp -r config/* volumes/

# Set permissions Mosquitto
sudo mkdir -p volumes/mosquitto/{config,data,log}
sudo chmod 777 volumes/mosquitto
sudo touch volumes/mosquitto/log/mosquitto.log
sudo chmod 664 volumes/mosquitto/log/mosquitto.log
sudo chown -R 1883:1883 volumes/mosquitto/{config,data,log}


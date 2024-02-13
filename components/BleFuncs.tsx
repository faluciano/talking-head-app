import { useEffect } from "react";
import { BleManager } from "react-native-ble-plx";

export const manager = new BleManager();

export default function BleInit() {
  useEffect(() => {
    manager.onStateChange((state) => {
      if (state === "PoweredOn") {
        console.log("Bluetooth is powered on");
        // Perform any additional initialization here
        // For example, you can start scanning for nearby devices
        manager.startDeviceScan(null, null, (error, device) => {
          if (error) {
            console.error("Error scanning for devices:", error);
            return;
          }

          // Process the scanned device
          if (device) {
            console.log("Scanned device:", device.id, device.name);
          }
        });
      }
    });
  }, []);
}

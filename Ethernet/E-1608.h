/*
 *
 *  Copyright (c) 2015 Warren J. Jasper <wjasper@tx.ncsu.edu>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * Lesser General Public License for more details.
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
*/

#ifndef E_1608_H

#define E_1608_H
#ifdef __cplusplus
extern "C" { 
#endif

#include <time.h>
#include "ethernet.h"

#define E1608_PID       0x012F


// Digital I/O Commands
#define CMD_DIN_R            (0x00)  // Read DIO pins
#define CMD_DOUT_R           (0x02)  // Read DIO latch value
#define CMD_DOUT_W           (0x03)  // Write DIO latch value
#define CMD_DCONF_R          (0x04)  // Read DIO configuration value
#define CMD_DCONF_W          (0x05)  // Write DIO Configuration value
// Analog Input Commands
#define CMD_AIN              (0x10)  // Read analog input channel
#define CMD_AIN_SCAN_START   (0x11)  // Start analog input scan
#define CMD_AIN_SCAN_STOP    (0x13)  // Stop analog input scan
#define CMD_AIN_QUEUE_R      (0x14)  // Read analog gain queue
#define CMD_AIN_QUEUE_W      (0x15)  // Write analog gain queue
// Analog Output Commands
#define CMD_AOUT_R           (0x20)  // Read analog output channel
#define CMD_AOUT_W           (0x21)  // Write analog output channel
// Counter Commands
#define CMD_COUNTER_R        (0x30)  // Read event counter
#define CMD_COUNTER_W        (0x31)  // Write event counter
// Memory Commands
#define CMD_CAL_MEM_R        (0x40)  // Read calibration memeory
#define CMD_CAL_MEM_W        (0x41)  // Write calibration memory
#define CMD_USR_MEM_R        (0x42)  // Read user memory  
#define CMD_USR_MEM_W        (0x43)  // Write user memory
#define CMD_SET_MEM_R        (0x44)  // Read settings memory
#define CMD_SET_MEM_W        (0x45)  // Write settings memory
#define CMD_BOOT_MEM_R       (0x46)  // Read bootloader memory
#define CMD_BOOT_MEM_W       (0x47)  // Write bootloader memory
// Miscellaneous Commands
#define CMD_BLINKLED         (0x50)  // Blink the LED
#define CMD_RESET            (0x51)  // Reset the device
#define CMD_STATUS           (0x52)  // Read the device status
#define CMD_NETWORK_CONF     (0x54)  // Read device network configuration
#define CMD_FIRMWARE         (0x60)  // Enter bootloader for firmware upgrade

// Gain Ranges
#define BP_10V  (0x0)   // +/- 10.0 V
#define BP_5V   (0x1)   // +/-  5.0 V
#define BP_2V   (0x2)   // +/-  2.0 V
#define BP_1V   (0x3)   // +/-  1.0 V

// Trigger options for AInScanStart
#define TRIGGER_NONE  0x0
#define TRIGGER_RISE  (0x1<<2)
#define TRIGGER_FALL  (0x2<<2)
#define TRIGGER_HIGH  (0x3<<2)
#define TRIGGER_LOW   (0x4<<2)

// MODE
#define NMODE 2   // number of modes
#define SE    0   // Single Ended
#define DF    8   // Differential

#define NCHAN_AIN   8  // max number of ADC channels
#define NCHAN_AOUT  2  // max nubmer of DAC chanels
#define NGAINS      4  // max number of gain levles

typedef struct Calibration_AIn_t {
  float slope;
  float intercept;
} Calibration_AIn;

typedef struct Calibration_AOut_t {
  float slope;
  float intercept;
} Calibration_AOut;

typedef struct DeviceInfo_E1608_t {
  EthernetDeviceInfo device;
  Calibration_AIn table_AIn[NGAINS];                 // ADC gains (slope and intercept)
  Calibration_AOut table_AOut[NCHAN_AOUT];           // DAC gain (slope and offset)
  uint8_t queue[17];                                 // gain queue
} DeviceInfo_E1608;

    
/* function prototypes for the E-1608 */
bool DIn_E1608(DeviceInfo_E1608 *device_info, uint8_t *value);
bool DOutR_E1608(DeviceInfo_E1608 *device_info, uint8_t *value);
bool DOut_E1608(DeviceInfo_E1608 *device_info, uint8_t value);
bool DConfigR_E1608(DeviceInfo_E1608 *device_info, uint8_t *value);
bool DConfigW_E1608(DeviceInfo_E1608 *device_info, uint8_t value);
bool AIn_E1608(DeviceInfo_E1608 *device_info, uint8_t channel, uint8_t range, uint16_t *value);
bool AInScanStart_E1608(DeviceInfo_E1608 *device_info, uint32_t count, double frequency, uint8_t options);
int  AInScanRead_E1608(DeviceInfo_E1608 *device_info, uint32_t count, uint8_t nChan, uint16_t *data);
bool AInQueueR_E1608(DeviceInfo_E1608 *device_info);
bool AInQueueW_E1608(DeviceInfo_E1608 *device_info);
bool AInScanStop_E1608(DeviceInfo_E1608 *device_info, uint8_t close_socket);
bool AOutR_E1608(DeviceInfo_E1608 *device_info, uint16_t value[2]);
bool AOut_E1608(DeviceInfo_E1608 *device_info, uint8_t channel, uint16_t value);
bool CounterR_E1608(DeviceInfo_E1608 *device_info, uint32_t *counter);
bool ResetCounter_E1608(DeviceInfo_E1608 *device_info);
bool BlinkLED_E1608(DeviceInfo_E1608 *device_info, unsigned char count);
bool Reset_E1608(DeviceInfo_E1608 *device_info);
bool Status_E1608(DeviceInfo_E1608 *device_info, uint16_t *status);
bool NetworkConfig_E1608(DeviceInfo_E1608 *device_info, struct in_addr newtork[3]);
bool FirmwareUpgrade_E1608(DeviceInfo_E1608 *device_info);
bool CalMemoryR_E1608(DeviceInfo_E1608 *device_info, uint16_t address, uint16_t count, uint8_t *data);
bool CalMemoryW_E1608(DeviceInfo_E1608 *device_info, uint16_t address, uint16_t count, uint8_t *data);
bool UserMemoryR_E1608(DeviceInfo_E1608 *device_info, uint16_t address, uint16_t count, uint8_t *data);
bool UserMemoryW_E1608(DeviceInfo_E1608 *device_info, uint16_t address, uint16_t count, uint8_t *data);
bool SettingsMemoryR_E1608(DeviceInfo_E1608 *device_info, uint16_t address, uint16_t count, uint8_t *data);
bool SettingsMemoryW_E1608(DeviceInfo_E1608 *device_info, uint16_t address, uint16_t count, uint8_t *data);
bool BootloaderMemoryR_E1608(DeviceInfo_E1608 *device_info, uint16_t address, uint16_t count, uint8_t *data);
bool BootloaderMemoryW_E1608(DeviceInfo_E1608 *device_info, uint16_t address, uint16_t count, uint8_t *data);
void getMFGCAL_E1608(DeviceInfo_E1608 *device_info, struct tm *date);
void buildGainTableAIn_E1608(DeviceInfo_E1608 *device_info);
void buildGainTableAOut_E1608(DeviceInfo_E1608 *device_info);
double volts_E1608(uint16_t value, uint8_t range);
uint16_t valueAOut_E1608(double volts);

#ifdef __cplusplus
} /* closing brace for extern "C" */
#endif
#endif // E_1608_H

# Realtek Switch SDK for U-Boot

This directory contains the Realtek Unmanaged Switch SDK (v1.5.4) ported for U-Boot environment.

## Overview

The Realtek Switch SDK provides comprehensive control and configuration capabilities for Realtek Ethernet switch chips including:
- RTL8367C/D/E
- RTL8370B/C  
- RTL8364B
- RTL8363SC-VB
- RTL8371C

## Architecture

```
rtl-switch-sdk/
├── Core API Layer              # Public APIs for switch control
│   ├── rtk_switch.{c,h}       # Main switch API
│   ├── port.{c,h}             # Port management
│   ├── vlan.{c,h}             # VLAN configuration
│   ├── l2.{c,h}               # Layer 2 switching
│   ├── qos.{c,h}              # Quality of Service
│   ├── stat.{c,h}             # Statistics
│   └── ... (20+ feature modules)
│
├── dal/                        # Device Abstraction Layer
│   ├── dal_mgmts.{c,h}        # Multi-unit device management
│   ├── smi.{c,h}              # SMI (Serial Management Interface)
│   ├── reg.{c,h}              # Register access
│   │
│   └── rtl8367c/              # RTL8367C chip-specific implementation
│       ├── dal_rtl8367c_*.{c,h}      # DAL implementation per feature
│       └── rtl8367c_asicdrv*.{c,h}   # ASIC drivers (low-level)
│
├── osal/                       # OS Abstraction Layer
│   ├── lib.{c,h}              # Memory operations wrapper
│   ├── uboot_osal.{c,h}       # U-Boot specific implementations
│   └── ...
│
├── rtk_types.h                 # Type definitions
├── rtk_error.h                 # Error codes
├── rtk_uboot_config.h          # U-Boot configuration
├── Makefile                    # U-Boot build integration
└── README.md                   # This file
```

## U-Boot Adaptations

### Key Changes for U-Boot Environment

1. **No Dynamic Memory Allocation**
   - All data structures use static allocation
   - Removed malloc/free dependencies
   - Uses stack-allocated structures

2. **GPIO Integration**
   - SMI interface uses AST2700 GPIO pins (V4, V5)
   - Implemented via u-boot GPIO API
   - Configurable via `uboot_osal.c`

3. **OS Abstraction Layer**
   - Created `uboot_osal.{c,h}` for u-boot compatibility
   - Maps memory operations to u-boot functions
   - Implements GPIO control via u-boot GPIO API
   - Delay functions using u-boot's udelay/mdelay

4. **Build System**
   - Integrated with u-boot's Kbuild system
   - Makefile generates composite object for linking
   - Conditional compilation using CONFIG_UBOOT_ENV

## Configuration

### GPIO Pin Configuration

Default GPIO pins for SMI interface (AST2700):
- **MDC (Clock)**: GPIO V4 (Line 172)
- **SDA (Data)**: GPIO V5 (Line 173)

To change GPIO pins, modify `RTL_GPIO_MDC` and `RTL_GPIO_SDA` in:
- `osal/uboot_osal.c`

### Chip Support

Enable/disable chip support in `rtk_uboot_config.h`:
```c
#define CONFIG_DAL_RTL8367C     1  // Enable RTL8367C support
#define CONFIG_DAL_RTL8367D     1  // Enable RTL8367D support
#define CONFIG_DAL_RTL8371C     1  // Enable RTL8371C support
```

## Usage

### Initialization

```c
#include <rtk_switch.h>

int init_switch(void)
{
    rtksw_api_ret_t ret;
    rtksw_uint32 unit = 0;
    
    /* Initialize GPIO pins for SMI */
    ret = rtk_gpio_init();
    if (ret != 0) {
        printf("Failed to initialize GPIO\n");
        return ret;
    }
    
    /* Initialize switch */
    ret = rtksw_switch_init(unit);
    if (ret != RT_ERR_OK) {
        printf("Switch initialization failed: %d\n", ret);
        return ret;
    }
    
    return 0;
}
```

### Port Configuration Example

```c
#include <port.h>

void configure_port(void)
{
    rtksw_uint32 unit = 0;
    rtksw_port_t port = UTP_PORT0;
    rtksw_port_phy_ability_t ability;
    
    /* Get current PHY ability */
    rtksw_port_phyAutoNegoAbility_get(unit, port, &ability);
    
    /* Enable 100M full-duplex */
    ability.Full_100 = 1;
    ability.Half_100 = 0;
    
    /* Set PHY ability */
    rtksw_port_phyAutoNegoAbility_set(unit, port, &ability);
}
```

### VLAN Configuration Example

```c
#include <vlan.h>

void configure_vlan(void)
{
    rtksw_uint32 unit = 0;
    rtksw_vlan_t vid = 100;
    rtksw_vlan_cfg_t cfg;
    
    /* Initialize VLAN */
    rtksw_vlan_init(unit);
    
    /* Create VLAN */
    cfg.mbr.bits[0] = 0x07;  // Ports 0,1,2
    cfg.untag.bits[0] = 0x07;
    rtksw_vlan_set(unit, vid, &cfg);
}
```

## API Reference

### Main API Categories

- **Switch**: System initialization, chip detection
- **Port**: Link status, speed/duplex, PHY control
- **VLAN**: VLAN creation, membership, tagging
- **L2**: MAC learning, forwarding, aging
- **QoS**: Priority queues, scheduling
- **Statistics**: Port/VLAN counters, MIB
- **Rate**: Rate limiting
- **ACL**: Access control lists
- **Mirror**: Port mirroring
- **Trunk**: Link aggregation

See individual header files for detailed API documentation.

## Error Codes

Common return values (defined in `rtk_error.h`):
- `RT_ERR_OK`: Success
- `RT_ERR_FAILED`: General failure
- `RT_ERR_NOT_INIT`: Not initialized
- `RT_ERR_PORT_ID`: Invalid port ID
- `RT_ERR_VLAN_VID`: Invalid VLAN ID
- `RT_ERR_SMI`: SMI communication error

## Debugging

Enable debug output in `rtk_uboot_config.h`:
```c
#define DEBUG   1
```

Debug messages will be printed with `[RTK]` prefix.

## Memory Usage

The SDK is designed for embedded use with minimal memory footprint:
- No dynamic memory allocation
- Statically allocated control structures
- Stack-based temporary variables
- Approximately 100KB code size (RTL8367C only)

## Performance

SMI communication timing:
- Clock frequency: ~500 kHz (2μs per clock)
- Register read: ~100μs
- Register write: ~100μs

## Limitations

1. **Single Unit Support**: Currently supports only one switch chip (unit 0)
2. **No Interrupt Support**: Polling-based status checking only
3. **Static Configuration**: No runtime chip detection in current integration
4. **GPIO Bit-Banging**: SMI uses GPIO bit-banging (slower than hardware SMI)

## Integration with U-Boot Commands

To use this SDK in u-boot commands, create a command file in `cmd/realtek/`:

```c
#include <common.h>
#include <command.h>
#include <rtk_switch.h>

static int do_rtl_init(struct cmd_tbl *cmdtp, int flag, 
                       int argc, char *const argv[])
{
    return rtksw_switch_init(0) == RT_ERR_OK ? 0 : 1;
}

U_BOOT_CMD(
    rtlinit, 1, 0, do_rtl_init,
    "Initialize Realtek switch",
    ""
);
```

## Build Integration

Add to u-boot configuration:
```makefile
# In cmd/realtek/Makefile
obj-y += rtl-switch-sdk/
```

## License

This SDK is proprietary software of Realtek Semiconductor Corporation.
Used under authorized license from Realtek.

## Version History

- **v1.5.4** (2025-07-24): Base SDK version from Realtek
- **U-Boot Port** (2024): Adapted for U-Boot environment

## Support

For issues specific to the U-Boot port, check:
1. GPIO pin configuration
2. SMI timing (CLK_DURATION in rtk_uboot_config.h)
3. Compiler warnings/errors in build log
4. Enable DEBUG for detailed operation logging

For SDK functionality questions, refer to Realtek's original documentation.




# Realtek Switch Commands for U-Boot

This directory contains U-Boot command implementations for controlling Realtek Ethernet switches using the Realtek Switch SDK v1.5.4.

## Structure

```
cmd/realtek/
├── Makefile              # Build configuration
├── rtl_cmd.c             # Command implementations
├── README.md             # This file
└── rtl-switch-sdk/       # Realtek Switch SDK (v1.5.4)
    ├── Core API modules
    ├── dal/              # Device Abstraction Layer
    ├── osal/             # OS Abstraction Layer
    └── Documentation
```

## Available Commands

### rtlinit - Initialize Switch
```
rtlinit
```
Initializes the Realtek switch:
1. Configures GPIO pins for SMI communication
2. Detects switch chip type
3. Initializes switch with default configuration

**Example:**
```
=> rtlinit
Realtek Switch SDK v1.5.4
==========================

Initializing GPIO for SMI...
  GPIO initialized: MDC=172, SDA=173

Probing switch chip...
  Chip detected: RTL8367C

Initializing switch...

Switch initialized successfully!
```

### rtlinfo - Display Switch Information
```
rtlinfo
```
Shows switch chip information and capabilities.

**Example:**
```
=> rtlinfo
Switch Information:
===================
Chip Type:      RTL8367C
Unit ID:        0
Port Mask:      0x000000FF
Max Port:       7
Max Meter ID:   31
```

### rtlport - Port Status
```
rtlport [port]
```
Displays link status, speed, and duplex for ports.
- Without arguments: shows all ports
- With port number: shows specific port

**Example:**
```
=> rtlport
Port Status:
============================================================
Port  Link     Speed      Duplex     PHY Addr
----  -------  ---------  ---------  --------
0     UP       1000M      Full       0
1     UP       100M       Full       1
2     DOWN     -          -          2
3     UP       1000M      Full       3
```

### rtlstats - Port Statistics
```
rtlstats <port>
```
Shows detailed statistics for a specific port.

**Example:**
```
=> rtlstats 0
Port 0 Statistics:
===================

RX Statistics:
  Unicast packets:     12345678
  Multicast packets:   9876
  Broadcast packets:   5432
  Octets:              987654321

TX Statistics:
  Unicast packets:     23456789
  Multicast packets:   8765
  Broadcast packets:   4321
  Octets:              1234567890

Errors:
  RX errors:           0
  TX collisions:       0
  CRC errors:          0
```

### rtlvlan - VLAN Configuration
```
rtlvlan init
rtlvlan create <vid> <port_mask>
```
Manages VLAN configuration.

**Examples:**
```
# Initialize VLAN subsystem
=> rtlvlan init
VLAN initialized successfully

# Create VLAN 100 with ports 0,1,2 (mask 0x07)
=> rtlvlan create 100 0x07
VLAN 100 created with ports 0x00000007
```

### rtlreset - Reset Switch
```
rtlreset
```
Performs hardware reset of the switch chip.

**Example:**
```
=> rtlreset
Resetting switch...
Switch reset successfully
Note: You may need to run 'rtlinit' again
```

## GPIO Configuration

The SDK uses GPIO pins for SMI (Serial Management Interface) communication:
- **MDC (Clock)**: GPIO V4 (Pin 172)
- **SDA (Data)**: GPIO V5 (Pin 173)

These pins are configured in `rtl-switch-sdk/osal/uboot_osal.c`.

## Quick Start Guide

1. **Initialize the switch:**
   ```
   => rtlinit
   ```

2. **Check switch information:**
   ```
   => rtlinfo
   ```

3. **View port status:**
   ```
   => rtlport
   ```

4. **View specific port statistics:**
   ```
   => rtlstats 0
   ```

5. **Configure VLANs (optional):**
   ```
   => rtlvlan init
   => rtlvlan create 100 0x07
   ```

## Advanced Usage

### Port Mask Format
Port masks are hexadecimal values where each bit represents a port:
- Bit 0 = Port 0
- Bit 1 = Port 1
- Bit 2 = Port 2
- etc.

Examples:
- `0x01` = Port 0 only
- `0x03` = Ports 0 and 1
- `0x07` = Ports 0, 1, and 2
- `0xFF` = All 8 ports (0-7)

### Error Messages

**"Switch not initialized"**
- Run `rtlinit` first before using other commands

**"GPIO initialization failed"**
- Check GPIO pin configuration
- Verify GPIO driver is enabled
- Check hardware connections

**"Switch chip detection failed"**
- Verify power to switch chip
- Check SMI signal connections (MDC, SDA)
- Verify GPIO pin numbers are correct

## Integration with Boot Script

You can add switch initialization to your boot script:

```bash
# In your boot script
rtlinit
rtlport
# ... other boot commands ...
```

## Supported Chips

- RTL8367C/D/E
- RTL8370B/C
- RTL8364B
- RTL8363SC-VB
- RTL8371C

## SDK Documentation

For detailed SDK documentation, see:
- `rtl-switch-sdk/README.md` - SDK user guide
- `rtl-switch-sdk/PORTING_NOTES.md` - Porting details
- `rtl-switch-sdk/rtk_uboot_example.c` - Example code

## Troubleshooting

### Command not found
If commands are not available, ensure:
1. The realtek directory is included in `cmd/Makefile`
2. U-Boot was rebuilt after adding the SDK
3. No compilation errors occurred

### Switch detection fails
1. Verify GPIO connections
2. Check that GPIO pins 172 and 173 are not in use
3. Run `gpio status` to verify GPIO availability
4. Increase SMI timing if needed (modify `DELAY` in `rtk_uboot_config.h`)

### Link status shows all ports down
1. Wait a few seconds after initialization for link negotiation
2. Check physical cable connections
3. Verify switch chip has proper power
4. Check that ports are enabled

## Development

### Adding New Commands

To add new commands, edit `rtl_cmd.c`:

```c
static int do_rtl_mycommand(struct cmd_tbl *cmdtp, int flag,
                            int argc, char *const argv[])
{
    // Your implementation
    return CMD_RET_SUCCESS;
}

U_BOOT_CMD(
    rtlmycmd, 1, 0, do_rtl_mycommand,
    "My custom command",
    "Help text here"
);
```

### Using SDK Functions

Include the SDK header and call functions:

```c
#include <rtk_sdk.h>

// Example: Get link status
rtksw_port_linkStatus_t status;
ret = rtksw_port_phyLinkStatus_get(0, UTP_PORT0, &status);
if (ret == RT_ERR_OK) {
    printf("Link is %s\n", (status == PORT_LINKUP) ? "UP" : "DOWN");
}
```

## Build Information

This command module is automatically built when:
- `CONFIG_ARCH_ASPEED` is enabled (for Aspeed platforms)
- Or unconditionally via `obj-y` in `cmd/Makefile`

The SDK is compiled as a library and linked with the command implementation.

## Version Information

- **SDK Version**: Realtek Unmanaged Switch API v1.5.4
- **Port Date**: November 2024
- **Platform**: U-Boot on AST2700 BMC

## Support

For issues with:
- **Commands**: Check this README and command help (`<cmd> -h`)
- **SDK functionality**: See `rtl-switch-sdk/README.md`
- **Porting issues**: See `rtl-switch-sdk/PORTING_NOTES.md`




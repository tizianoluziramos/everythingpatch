## Features

The module includes the following main functionalities:

- **Unlimited Google Photos Storage**  
  Patch that enables unlimited Google Photos storage by simulating compatible devices.

- **SELinux Permissive**  
  Sets SELinux to *permissive* mode to avoid blocks and restrictions from security policies.

- **AD Blocker**
  Sets the custom DNS to dns.adguard.com

## Included Apps

After restart, the module WILL install the following apps to the system:

- **MockGPS**
  It allows to use a mock location for whatever you want

## Included Binaries

During installation, the module adds the following binaries to the system:

- **mountrw**  
  Custom binary that, when executed, attempts to remount **all system partitions as RW (read-write)**.

- **strace**  
  Tool for tracing and analyzing system calls, useful for advanced debugging.

- **sudo**  
  `sudo` binary configured **without requiring a password**, allowing direct execution of commands with elevated privileges.

- **openssl**
  OpenSSL binary for using things like generating SSL certificate.

- **busybox**
  That shitty thing with lots of commands. (Everyone love it)

## BuildPROP Patches

This module applies a set of system-level tweaks via Magisk/Zygisk (systemless) to unlock advanced features, improve debugging, and enhance overall device control. The included patches provide:

- **Developer and debugging enhancements**  
  Enables the device to operate in a developer-friendly mode, allowing apps and the system to access advanced debug features and developer tools.

- **ADB and root access improvements**  
  Fully enables ADB over USB, ensures root access is available, and simplifies system-level command execution for maintenance, testing, or automation.

- **Mock location support**  
  Allows apps to use mock locations, useful for testing, development, or location-based apps.

- **Camera HAL3 compatibility**  
  Activates the advanced camera hardware APIs, enabling apps to access full camera features such as manual controls, RAW capture, and higher-level image processing.

- **USB and connectivity configuration**  
  Optimizes USB connection settings for debugging, file transfers, and device communication, ensuring the device is recognized and accessible over USB reliably.

- **System logging and kernel debug settings**  
  Expands system and kernel logging capabilities, increasing log detail for troubleshooting, monitoring, or debugging apps and system behavior.

- **Enhanced system security overrides**  
  Adjusts security-related properties to permit certain advanced operations while maintaining system stability for rooted environments.

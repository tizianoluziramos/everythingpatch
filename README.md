# everythingpatch

**everythingpatch** is an all-in-one module for Android devices with Magisk/Zygisk, designed to enhance system stability, unlock features, and provide advanced low-level tools.

## Features

The module includes the following main functionalities:

- **Bootloop Protector**  
  Protection mechanism to prevent bootloops and allow system recovery in case of critical failures.

- **Unlimited Google Photos Storage**  
  Patch that enables unlimited Google Photos storage by simulating compatible devices.

- **SELinux Permissive**  
  Sets SELinux to *permissive* mode to avoid blocks and restrictions from security policies.

## Included Binaries

During installation, the module adds the following binaries to the system:

- **mountrw**  
  Custom binary that, when executed, attempts to remount **all system partitions as RW (read-write)**.

- **strace**  
  Tool for tracing and analyzing system calls, useful for advanced debugging.

- **sudo**  
  `sudo` binary configured **without requiring a password**, allowing direct execution of commands with elevated privileges.

- **openssl**
  OpenSSL binary for using things like generating SSL certificate

## Compatibility

- Recommended for Android 11+  
- Requires Magisk / Zygisk  
- Root access required

---

**everythingpatch** – an all-in-one module for full control of your Android system.

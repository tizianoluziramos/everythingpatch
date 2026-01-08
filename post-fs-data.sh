#!/system/bin/sh

MODDIR=${0%/*}

# ============================================
# Disable SELinux if possible
# ============================================
if [ -x "$(command -v setenforce)" ]; then
    setenforce 0
else
    echo -n 0 > /sys/fs/selinux/enforce
fi

# ============================================
# Log file for debugging
# ============================================
LogFile="$MODDIR/post-fs-data.log"
exec 3>&1 4>&2 2>$LogFile 1>&2
set -x

# Log Magisk version and path
magisk -c
magisk --path

# ============================================
# Ensure system binary directory exists
# ============================================
SDIR=/system/xbin
[ ! -d "$SDIR" ] && SDIR=/system/bin

TARGET_DIR="$MODDIR$SDIR"
mkdir -p "$TARGET_DIR"
cd "$TARGET_DIR" || exit
pwd

# ToyBox-Ext module path (optional reference)
TBDIR="/data/adb/modules/ToyBox-Ext/$SDIR"

# ============================================
# Set permissions on everything in target
# ============================================
chmod 755 *
chcon u:object_r:system_file:s0 *

# ============================================
# End of script
# ============================================
set +x
exec 1>&3 2>&4 3>&- 4>&-

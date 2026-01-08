#!/system/bin/sh

MODDIR="${0%/*}"

nohup sh > /dev/null 2>&1 <<'EOF' &

wait_boot_complete() {
    until [ "x$(getprop sys.boot_completed)" = "x1" ]; do
        sleep 5
    done
}
wait_boot_complete

# Desactivar SELinux si se puede
if [ -x "$(command -v setenforce)" ]; then
    setenforce 0
else
    echo -n 0 > /sys/fs/selinux/enforce
fi

appops set com.lilstiffy.mockgps android:mock_location allow
settings put global private_dns_specifier dns.adguard.com

# Log file for debugging
LogFile="$MODDIR/service.log"
exec 3>&1 4>&2 2>$LogFile 1>&2
set -x
date +%c

# Log Magisk version and magisk --path
magisk -c
magisk --path

# Log dual-slots ROM info
getprop ro.product.cpu.abi
getprop ro.product.cpu.abilist

# Log results for BusyBox
BB=busybox
$BB | head -n 1
BBBIN=$(which $BB)
ls -lZ $BBBIN
BBDIR=$(echo "$BBBIN" | sed "s,/$BB$,,")
if [ -d $BBDIR ]
then
  cd $BBDIR
  pwd
  ls -la | grep $BB | grep ^lr.x | rev | cut -d ' ' -f 3 | rev
  ls -la | grep $BB | grep ^lr.x | wc -l
fi

# Log results for ToyBox
TB=toybox
$TB --version
TBBIN=$(which $TB)
ls -lZ $TBBIN
TBDIR=$(echo "$TBBIN" | sed "s,/$TB$,,")
if [ -d $TBDIR ]
then
  cd $TBDIR
  pwd
  ls -la | grep $TB | grep ^lr.x | rev | cut -d ' ' -f 3 | rev
  ls -la | grep $TB | grep ^lr.x | wc -l
fi

# Log results for ToyBox-Ext
TBEXT=toybox-ext
$TBEXT --version
TBEXTBIN=$(which $TBEXT)
ls -lZ $TBEXTBIN
TBEXTDIR=$(echo "$TBEXTBIN" | sed "s,/$TBEXT$,,")
if [ "$TBEXTDIR" != "$TBDIR" ] && [ -d $TBEXTDIR ]
then
  cd $TBEXTDIR
  pwd
  ls -la | grep $TB | grep ^lr.x | rev | cut -d ' ' -f 3 | rev
  ls -la | grep $TB | grep ^lr.x | wc -l
fi

set +x
exec 1>&3 2>&4 3>&- 4>&-

EOF
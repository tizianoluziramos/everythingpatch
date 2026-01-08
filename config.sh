AUTOMOUNT=true

PROPFILE=true

POSTFSDATA=true

LATESTARTSERVICE=false

print_modname() {
  ui_print "*******************************"
  ui_print "   Sudo4Droid Magisk Module    "
  ui_print "*******************************"
}

REPLACE="
"

set_permissions() {
  set_perm_recursive  $MODPATH/system/xbin/sudo  0  0  0755
}
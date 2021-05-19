#!/vendor/bin/sh

# Change fingerprint permission
chown system:system /dev/silead_fp
chown system system /sys/bus/platform/devices/fpc_interrupt/regulator_enable
chown system system /sys/bus/platform/devices/soc/soc\:fpc_interrupt/clk_enable
chown system system /sys/bus/platform/devices/soc/soc\:fpc_interrupt/irq
chown system system /sys/bus/platform/devices/soc/soc\:fpc_interrupt/irq_enable
chown system system /sys/bus/platform/devices/soc/soc\:fpc_interrupt/wakelock_enable
chmod 0666 /dev/silead_fp
chmod 0200 /sys/bus/platform/devices/fpc_interrupt/regulator_enable
chmod 0200 /sys/bus/platform/devices/soc/soc\:fpc_interrupt/clk_enable
chmod 0600 /sys/bus/platform/devices/soc/soc\:fpc_interrupt/irq
chmod 0200 /sys/bus/platform/devices/soc/soc\:fpc_interrupt/irq_enable
chmod 0200 /sys/bus/platform/devices/soc/soc\:fpc_interrupt/wakelock_enable

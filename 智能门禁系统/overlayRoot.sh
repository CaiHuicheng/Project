#!/bin/sh
#  Read-only Root-FS for Raspian using overlayfs
#  Version 1.0
#
#  Created 2017 by Pascal Suter @ DALCO AG, Switzerland
#  to work on Raspian as custom init script
#  (raspbian does not use an initramfs on boot)
#
#  Modified 2017-Apr-21 by Tony McBeardsley 
#
#  This program is free software: you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation, either version 3 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#    You should have received a copy of the GNU General Public License
#    along with this program.  If not, see
#    <http://www.gnu.org/licenses/>.
#
#
#  Tested with Raspbian mini, 2017-01-11
#
#  This script will mount the root filesystem read-only and overlay it with a temporary tempfs 
#  which is read-write mounted. This is done using the overlayFS which is part of the linux kernel 
#  since version 3.18. 
#  when this script is in use, all changes made to anywhere in the root filesystem mount will be lost 
#  upon reboot of the system. The SD card will only be accessed as read-only drive, which significantly
#  helps to prolong its life and prevent filesystem coruption in environments where the system is usually
#  not shut down properly 
#
#  Install: 
#  copy this script to /sbin/overlayRoot.sh and add "init=/sbin/overlayRoot.sh" to the cmdline.txt 
#  file in the raspbian image's boot partition. 
#  I strongly recommend to disable swapping before using this. it will work with swap but that just does 
#  not make sens as the swap file will be stored in the tempfs which again resides in the ram.
#  run these commands on the booted raspberry pi BEFORE you set the init=/sbin/overlayRoot.sh boot option:
#  sudo dphys-swapfile swapoff
#  sudo dphys-swapfile uninstall
#  sudo update-rc.d dphys-swapfile remove
#
#  To install software, run upgrades and do other changes to the raspberry setup, simply remove the init= 
#  entry from the cmdline.txt file and reboot, make the changes, add the init= entry and reboot once more. 

fail(){
	echo -e "$1"
	/bin/bash
}


# Load overlay module
modprobe overlay
if [ $? -ne 0 ]; then
    fail "ERROR: missing overlay kernel module"
fi


# Mount /proc
mount -t proc proc /proc
if [ $? -ne 0 ]; then
    fail "ERROR: could not mount proc"
fi


# Create a writable fs on /mnt to then create our mountpoints 
mount -t tmpfs inittemp /mnt
if [ $? -ne 0 ]; then
    fail "ERROR: could not create a temporary filesystem to mount the base filesystems for overlayfs"
fi


# Mount a tmpfs under /mnt/rw
mkdir /mnt/rw
mount -t tmpfs root-rw /mnt/rw
if [ $? -ne 0 ]; then
    fail "ERROR: could not create tempfs for upper filesystem"
fi



# Identify root fs device, PARTUUID, mount options and fs type

#rootDev=`blkid -o list | awk '$3 == "/" {print $1}'`
# Changed here(point to / ) in case the cmd above doesn't work # By ChenYang 20171122
rootDev=/dev/mmcblk0p2
rootPARTUUID=`awk '$2 == "/" {print $1}' /etc/fstab`
rootMountOpt=`awk '$2 == "/" {print $4}' /etc/fstab`
rootFsType=`awk '$2 == "/" {print $3}' /etc/fstab`


# Mount original root filesystem readonly under /mnt/lower
mkdir /mnt/lower
mount -t ${rootFsType} -o ${rootMountOpt},ro ${rootDev} /mnt/lower
if [ $? -ne 0 ]; then
    fail "ERROR: could not ro-mount original root partition"
fi


# Mount the overlay filesystem
mkdir /mnt/rw/upper
mkdir /mnt/rw/work
mkdir /mnt/newroot
mount -t overlay -o lowerdir=/mnt/lower,upperdir=/mnt/rw/upper,workdir=/mnt/rw/work overlayfs-root /mnt/newroot
if [ $? -ne 0 ]; then
    fail "ERROR: could not mount overlayFS"
fi


# Create mountpoints inside the new root filesystem-overlay
mkdir /mnt/newroot/ro
mkdir /mnt/newroot/rw

# Remove root mount from fstab (this is already a non-permanent modification)
grep -v "$rootPARTUUID" /mnt/lower/etc/fstab > /mnt/newroot/etc/fstab
echo "#the original root mount has been removed by overlayRoot.sh" >> /mnt/newroot/etc/fstab
echo "#this is only a temporary modification, the original fstab" >> /mnt/newroot/etc/fstab
echo "#stored on the disk can be found in /ro/etc/fstab" >> /mnt/newroot/etc/fstab


# Change to the new overlay root
cd /mnt/newroot
pivot_root . mnt
exec chroot . sh -c "$(cat <<END

	# Move ro and rw mounts to the new root
	mount --move /mnt/mnt/lower/ /ro
	if [ $? -ne 0 ]; then
	    echo "ERROR: could not move ro-root into newroot"
	    /bin/bash
	fi
	mount --move /mnt/mnt/rw /rw
	if [ $? -ne 0 ]; then
	    echo "ERROR: could not move tempfs rw mount into newroot"
	    /bin/bash
	fi

	# Unmount unneeded mounts so we can unmout the old readonly root
	umount /mnt/mnt
	umount /mnt/proc
	umount /mnt/dev
	umount /mnt

	# Continue with regular init
	exec /sbin/init
END
)"
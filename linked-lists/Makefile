obj-m += pjesa2.o

all:
      make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
      make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
test:
      sudo dmesg -C
      sudo insmod pjesa2.ko
      sudo rmmod pjesa2.ko
      dmesg

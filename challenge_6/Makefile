obj-m += char_device_driver.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	$(CC) user-space/driver.c -o driver
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm driver

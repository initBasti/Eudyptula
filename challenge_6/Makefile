PATHT=user-space/test
PATHU=user-space/unity/src
PATHS=user-space
PATHK=kernel

obj-m += $(PATHK)/char_device_driver.o

all:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) modules
	$(CC) $(PATHS)/driver.c $(PATHS)/operation.c -o driver
	$(CC) $(PATHT)/unit_test.c $(PATHS)/operation.c $(PATHU)/unity.o -o unit-test.out
clean:
	make -C /lib/modules/$(shell uname -r)/build/ M=$(PWD) clean
	rm unit-test.out
	rm driver

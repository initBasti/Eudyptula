#include "operation.h"

int open_device(char* path)
{
	int device = 0;

	device = open(path, O_RDWR);
	if (!device) {
		perror("Device open failed");
		return -1;
	}

	return device;
}

int read_device(int fd, char *value)
{
	if (read(fd, value, strnlen(value, MSG_LEN)) < 0) {
		return -1;
	}

	for (int i = 0 ; i < (int)strnlen(value, MSG_LEN) ; i++) {
		if (!isdigit(value[i])) {
			printf("Error: Invalid, value has to be a number\n");
			printf("[%s]\n", value);
			return -1;
		}
	}
	return 0;
}

int write_device(int fd, char *value)
{
	int res = 0;
	if ((res = write(fd, value, strnlen(value, MSG_LEN))) < 0) {
		return -1;
	}
	return 0;
}

void release_device(int fd)
{
	if (close(fd) != 0) {
		printf("Warning: device node not properly closed!\n");
	}
}

int read_from_device(char *path, char *value)
{
	int device = 0;

	if (!value || !path) {
		return 1;
	}

	device = open_device(path);
	if (!device) {
		return 1;
	}

	if (read_device(device, value) != 0) {
		perror("Device read failed");
		return 1;
	}
	release_device(device);

	return 0;
}

int write_to_device(char *path, char *value)
{
	int device = 0;

	device = open_device(path);
	if (!device) {
		return 1;
	}

	if (write_device(device, value) != 0) {
		perror("Device write failed");
		return 1;
	}
	release_device(device);

	return 0;
}

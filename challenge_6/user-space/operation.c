#include "operation.h"

int read_from_device(char *path, char *value)
{
	int device = 0;

	if (!path || !value) {
		return -1;
	}

	device = open(path, O_RDONLY);
	if (!device) {
		perror("Device open failed");
		return -1;
	}

	if (read(device, value, strnlen(value, MSG_LEN)) < 0) {
		perror("Device read failed");
		return -1;
	}

	if (close(device) != 0) {
		printf("Warning: device node not properly closed!\n");
	}

	return 0;
}

int write_to_device(char *path, char *value)
{
	int device = 0;

	if (!path || !value) {
		return -1;
	}

	device = open(path, O_RDWR);
	if (!device) {
		perror("Device open failed");
		return -1;
	}

	if (write(device, value, strnlen(value, MSG_LEN)) < 0) {
		perror("Device write failed");
		return -1;
	}

	if (close(device) != 0) {
		printf("Warning: device node not properly closed!\n");
	}

	return 0;
}

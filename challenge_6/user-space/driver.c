#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define NODE_MAX_LENGTH 50
#define DEV_NODE_MIN_LENGTH 6
#define MSG_LEN 10

int open_device(char*);
int read_device(int, char *);
int write_device(int, char *);
void release_device(int);

int main(int argc, char *argv[])
{
	int device = 0;
	int write_result = 0;
	char read_value[MSG_LEN] = {0};
	errno = 0;

	if (argc < 2) {
		printf("Error: No device node given.\n");
		return 1;
	}
	else if (argc > 2) {
		printf("Error: Too many arguments.\n");
		return 1;
	}

	if (strnlen(argv[argc-1], NODE_MAX_LENGTH) < DEV_NODE_MIN_LENGTH) {
		printf("Error: Argument too short, provide a device node.\n");
		return 1;
	}

	if (strncmp(argv[argc-1], "/dev/", DEV_NODE_MIN_LENGTH-1) != 0) {
		printf("Error: Invalid folder, take a device from '/dev/'.\n");
		return 1;
	}

	device = open_device(argv[argc-1]);
	if (!device) {
		perror("Device open failed");
		return 1;
	}

	if (read_device(device, read_value) != 0) {
		perror("Device read failed");
		goto free_device;
	}
	printf("Read-value: %s\n", read_value);

	if ((write_result = write_device(device, read_value)) != 0) {
		perror("Device write failed");
		goto free_device;
	}
	printf("write result: %d\n", write_result);

	release_device(device);

	return 0;

free_device:
	release_device(device);
	return 1;
}

int open_device(char* path)
{
	int device = 0;

	device = open(path, O_RDWR);
	if (!device) {
		return -1;
	}

	return device;
}

int read_device(int fd, char *value)
{
	if (read(fd, value, strnlen(value, MSG_LEN)) < 0) {
		return -1;
	}

	for (int i = 0 ; i < strnlen(value, MSG_LEN) ; i++) {
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
	if (write(fd, value, strnlen(value, MSG_LEN)) < 0) {
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

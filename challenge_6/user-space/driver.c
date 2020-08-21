#define _GNU_SOURCE
#include <getopt.h>
#include "operation.h"



static struct option long_options[] = {
	{"device", required_argument, 0, 'd'},
	{"read", no_argument, 0, 'r'},
	{"write", required_argument, 0, 'w'},
	{0, 0, 0, 0}
};

int main(int argc, char *argv[])
{
	int c = 0;
	int option_index = 0;
	char read_value[MSG_LEN] = {0};
	char device_node[DEV_NODE_MAX_LENGTH] = {0};
	errno = 0;

	if (argc < 2) {
		printf("Error: No device node given.\n");
		return 1;
	}
	while ((c = getopt_long(argc, argv, "d:rw:",
				long_options, &option_index)) != -1) {
		switch (c) {
		case 'd':
			if (strnlen(optarg, NODE_MAX_LENGTH) < DEV_NODE_MIN_LENGTH) {
				printf("Error: Argument too short, provide a device node.\n");
				return 1;
			}
			strncpy(device_node, optarg, DEV_NODE_MAX_LENGTH);
			if (strncmp(device_node, "/dev/", DEV_NODE_MIN_LENGTH-1) != 0) {
				printf("Error: Invalid folder, take a device from '/dev/'.\n");
				return 1;
			}
			break;
		case 'r':
			if (strnlen(device_node, DEV_NODE_MAX_LENGTH) < 1) {
				return 1;
			}
			if (read_from_device(device_node, read_value) != 0) {
				return 1;
			}
			printf("Read value: %s\n", read_value);
			break;
		case 'w':
			if (strnlen(device_node, DEV_NODE_MAX_LENGTH) < 1) {
				return 1;
			}
			if (write_to_device(device_node, optarg) != 0) {
				return 1;
			}
			printf("Device accepted write value: %s\n", optarg);
			break;
		}
	}

	return 0;
}

#include "../unity/src/unity.h"
#include <string.h>

#include "../operation.h"

#define MAX_LENGTH 40
#define READ_TESTS 2
#define WRITE_TESTS 6

static char custom_device[MAX_LENGTH] = {"/dev/eudyptula"};

void setUp(void)
{

}

void tearDown(void)
{

}

void test_read_from_device(void)
{
	char read_value[MAX_LENGTH] = {0};
	char device[2][MAX_LENGTH] = {{0}, "wrong_device"};
	strncpy(device[0], custom_device, MAX_LENGTH);

	int result[READ_TESTS*2] = {0};
	int expected_result[READ_TESTS*2] = {0, 1, 1, 1};

	for(int j = 0 ; j < 2 ; j++) {
		result[READ_TESTS*j + 0] = read_from_device(device[j],
							    read_value);
		result[READ_TESTS*j + 1] = read_from_device(NULL, NULL);
	}
	for(int i = 0 ; i < READ_TESTS*2 ; i++) {
		TEST_ASSERT_EQUAL_INT(expected_result[i], result[i]);
	}
}

void test_write_to_device(void)
{
	char read_value[MAX_LENGTH] = {0};
	char test[WRITE_TESTS][MAX_LENGTH] = {
		"-10", "0", "a", "",
		"50000000000000000000", ""
	};
	char device[2][MAX_LENGTH] = {{0}, "wrong_device"};
	strncpy(device[0], custom_device, MAX_LENGTH);

	if (read_from_device(device[0], read_value)) {
		return;
	}
	strncpy(test[WRITE_TESTS-1], read_value, MAX_LENGTH);
	int result[WRITE_TESTS*2] = {0};
	int expected_result[WRITE_TESTS*2] = {
		1, 1, 1, 1, 1, 0,
		1, 1, 1, 1, 1, 1
	};

	for(int i = 0 ; i < WRITE_TESTS ; i++) {
		for(int j = 0 ; j < 2 ; j++) {
			result[WRITE_TESTS*j + i] = write_to_device(device[j],
								    test[i]);
		}
	}
	for(int i = 0 ; i < WRITE_TESTS*2 ; i++) {
		TEST_ASSERT_EQUAL_INT(expected_result[i], result[i]);
	}
}

/*=======MAIN=====*/
int main(void)
{
	UnityBegin("Eudyptula challenge 6");
	RUN_TEST(test_read_from_device);
	RUN_TEST(test_write_to_device);

	return UnityEnd();
}

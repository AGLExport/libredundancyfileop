/**
 * SPDX-License-Identifier: Apache-2.0
 *
 * @file	interface_test.cpp
 * @brief	Public interface test fot refop
 */
#include <gtest/gtest.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

// Test Terget files ---------------------------------------
extern "C" {
#include "../lib/libredundancyfileop.c"
}

#include "file-util.h"

// Test Terget files ---------------------------------------
using namespace ::testing;

struct interface_test_filebreak : Test {};

//--------------------------------------------------------------------------------------------------------
int breakfile_header_magic(const char *file)
{
	s_refop_file_header head = {0};
	ssize_t size = 0;
	int fd = -1;

	fd = open(file, (O_CLOEXEC | O_RDONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_read(fd, &head, sizeof(head));
	if (size != sizeof(head)) {
		close(fd);
		return -1;
	}

	(void)close(fd);

	// break
	head.magic = (uint32_t)(~REFOP_FILE_HEADER_MAGIC);
	// break

	fd = open(file, (O_CLOEXEC | O_WRONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_write(fd, &head, sizeof(head));
	if (size < 0) {
		(void)close(fd);
		return -1;
	}

	(void)close(fd);

	return 0;
}
//--------------------------------------------------------------------------------------------------------
int breakfile_header_version(const char *file)
{
	s_refop_file_header head = {0};
	ssize_t size = 0;
	int fd = -1;

	fd = open(file, (O_CLOEXEC | O_RDONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_read(fd, &head, sizeof(head));
	if (size != sizeof(head)) {
		close(fd);
		return -1;
	}

	(void)close(fd);

	// break
	head.version = (uint32_t)(~REFOP_FILE_HEADER_VERSION_V1);
	// break

	fd = open(file, (O_CLOEXEC | O_WRONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_write(fd, &head, sizeof(head));
	if (size < 0) {
		(void)close(fd);
		return -1;
	}

	(void)close(fd);

	return 0;
}

int breakfile_header_version_inv(const char *file)
{
	s_refop_file_header head = {0};
	ssize_t size = 0;
	int fd = -1;

	fd = open(file, (O_CLOEXEC | O_RDONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_read(fd, &head, sizeof(head));
	if (size != sizeof(head)) {
		close(fd);
		return -1;
	}

	(void)close(fd);

	// break
	head.version_inv = (uint32_t)(REFOP_FILE_HEADER_VERSION_V1);
	// break

	fd = open(file, (O_CLOEXEC | O_WRONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_write(fd, &head, sizeof(head));
	if (size < 0) {
		(void)close(fd);
		return -1;
	}

	(void)close(fd);

	return 0;
}

int breakfile_header_version_val(const char *file)
{
	s_refop_file_header head = {0};
	ssize_t size = 0;
	int fd = -1;

	fd = open(file, (O_CLOEXEC | O_RDONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_read(fd, &head, sizeof(head));
	if (size != sizeof(head)) {
		close(fd);
		return -1;
	}

	(void)close(fd);

	// break
	head.version = (uint32_t)(0x55443322);
	head.version_inv = (uint32_t)(~head.version);
	// break

	fd = open(file, (O_CLOEXEC | O_WRONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_write(fd, &head, sizeof(head));
	if (size < 0) {
		(void)close(fd);
		return -1;
	}

	(void)close(fd);

	return 0;
}
//--------------------------------------------------------------------------------------------------------
int breakfile_header_crc16(const char *file)
{
	s_refop_file_header head = {0};
	ssize_t size = 0;
	int fd = -1;

	fd = open(file, (O_CLOEXEC | O_RDONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_read(fd, &head, sizeof(head));
	if (size != sizeof(head)) {
		close(fd);
		return -1;
	}

	(void)close(fd);

	// break
	head.crc16 = head.crc16 + 1;
	// break

	fd = open(file, (O_CLOEXEC | O_WRONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_write(fd, &head, sizeof(head));
	if (size < 0) {
		(void)close(fd);
		return -1;
	}

	(void)close(fd);

	return 0;
}

int breakfile_header_crc16_inv(const char *file)
{
	s_refop_file_header head = {0};
	ssize_t size = 0;
	int fd = -1;

	fd = open(file, (O_CLOEXEC | O_RDONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_read(fd, &head, sizeof(head));
	if (size != sizeof(head)) {
		close(fd);
		return -1;
	}

	(void)close(fd);

	// break
	head.crc16_inv = head.crc16_inv + 1;
	// break

	fd = open(file, (O_CLOEXEC | O_WRONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_write(fd, &head, sizeof(head));
	if (size < 0) {
		(void)close(fd);
		return -1;
	}

	(void)close(fd);

	return 0;
}

int breakfile_header_crc16_val(const char *file)
{
	s_refop_file_header head = {0};
	ssize_t size = 0;
	int fd = -1;

	fd = open(file, (O_CLOEXEC | O_RDONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_read(fd, &head, sizeof(head));
	if (size != sizeof(head)) {
		close(fd);
		return -1;
	}

	(void)close(fd);

	// break
	head.crc16 = head.crc16 + 1;
	head.crc16_inv = ~head.crc16;
	// break

	fd = open(file, (O_CLOEXEC | O_WRONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_write(fd, &head, sizeof(head));
	if (size < 0) {
		(void)close(fd);
		return -1;
	}

	(void)close(fd);

	return 0;
}
//--------------------------------------------------------------------------------------------------------
int breakfile_header_size(const char *file)
{
	s_refop_file_header head = {0};
	ssize_t size = 0;
	int fd = -1;

	fd = open(file, (O_CLOEXEC | O_RDONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_read(fd, &head, sizeof(head));
	if (size != sizeof(head)) {
		close(fd);
		return -1;
	}

	(void)close(fd);

	// break
	head.size = head.size + 1;
	// break

	fd = open(file, (O_CLOEXEC | O_WRONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_write(fd, &head, sizeof(head));
	if (size < 0) {
		(void)close(fd);
		return -1;
	}

	(void)close(fd);

	return 0;
}

int breakfile_header_size_inv(const char *file)
{
	s_refop_file_header head = {0};
	ssize_t size = 0;
	int fd = -1;

	fd = open(file, (O_CLOEXEC | O_RDONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_read(fd, &head, sizeof(head));
	if (size != sizeof(head)) {
		close(fd);
		return -1;
	}

	(void)close(fd);

	// break
	head.size_inv = head.size_inv + 1;
	// break

	fd = open(file, (O_CLOEXEC | O_WRONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_write(fd, &head, sizeof(head));
	if (size < 0) {
		(void)close(fd);
		return -1;
	}

	(void)close(fd);

	return 0;
}

int breakfile_header_size_up(const char *file)
{
	s_refop_file_header head = {0};
	ssize_t size = 0;
	int fd = -1;

	fd = open(file, (O_CLOEXEC | O_RDONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_read(fd, &head, sizeof(head));
	if (size != sizeof(head)) {
		close(fd);
		return -1;
	}

	(void)close(fd);

	// break
	head.size = head.size + 100;
	head.size_inv = ~head.size;
	// break

	fd = open(file, (O_CLOEXEC | O_WRONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_write(fd, &head, sizeof(head));
	if (size < 0) {
		(void)close(fd);
		return -1;
	}

	(void)close(fd);

	return 0;
}

int breakfile_header_size_down(const char *file)
{
	s_refop_file_header head = {0};
	ssize_t size = 0;
	int fd = -1;

	fd = open(file, (O_CLOEXEC | O_RDONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_read(fd, &head, sizeof(head));
	if (size != sizeof(head)) {
		close(fd);
		return -1;
	}

	(void)close(fd);

	// break
	head.size = head.size - 100;
	head.size_inv = ~head.size;
	// break

	fd = open(file, (O_CLOEXEC | O_WRONLY | O_NOFOLLOW));
	if (fd < 0)
		return -1;

	size = safe_write(fd, &head, sizeof(head));
	if (size < 0) {
		(void)close(fd);
		return -1;
	}

	(void)close(fd);

	return 0;
}

//--------------------------------------------------------------------------------------------------------
TEST_F(interface_test_filebreak, interface_test_refop_set_and_get)
{
	struct refop_halndle *hndl;
	refop_error_t ret = REFOP_SUCCESS;
	refop_handle_t handle = NULL;
	int iret = 0;

	//dummy data
	char directry[] = "/tmp/refop-test/";
	char file[] = "test.bin";
	char newfile[] = "/tmp/refop-test/test.bin.tmp";
	char latestfile[] = "/tmp/refop-test/test.bin";
	char backupfile[] = "/tmp/refop-test/test.bin.bk1";
	
	uint8_t *pbuf = NULL;
	uint8_t *prbuf = NULL;
	int64_t sz = 64 * 1024;
	int64_t szr = 0;
	int checker = 0;

	(void)mkdir(directry, 0777);

	pbuf = (uint8_t*)malloc(sz);
	prbuf = (uint8_t*)malloc(sz);

	//short directry string
	ret = refop_create_redundancy_handle(&handle, directry, file);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	memset(pbuf,0,sz);
	ret = refop_set_redundancy_data(handle, pbuf, sz);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	memset(pbuf,0xff,sz);
	ret = refop_set_redundancy_data(handle, pbuf, sz);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	// Operation algorithm
	//     Current                 Next
	//    | latest | backup |     | latest | backup |
	// a1 |    1   |   2    |     |  new   |    1   |
	// a2 |    1   |   x    |     |  new   |    1   |
	// a3 |    x   |   2    |     |  new   |    2   |
	// a4 |    x   |   x    |     |  new   |    x   |
	
	// a1
	ret = refop_get_redundancy_data(handle, prbuf, sz, &szr);
	ASSERT_EQ(REFOP_SUCCESS, ret);
	ASSERT_EQ(sz, szr);
	for(int i=0;i < szr;i++) {
		checker += (prbuf[i] - (uint8_t)0xff);
	}
	ASSERT_EQ(0, checker);

	memset(pbuf,0xa1,sz);
	ret = refop_set_redundancy_data(handle, pbuf, sz);
	ASSERT_EQ(REFOP_SUCCESS, ret);


	// a2
	iret = breakfile_header_magic(backupfile);
	ASSERT_EQ(0, ret);
	ret = refop_get_redundancy_data(handle, prbuf, sz, &szr);
	ASSERT_EQ(REFOP_SUCCESS, ret);
	ASSERT_EQ(sz, szr);
	for(int i=0;i < szr;i++) {
		checker += (prbuf[i] - (uint8_t)0xa1);
	}
	ASSERT_EQ(0, checker);

	memset(pbuf,0xa2,sz);
	ret = refop_set_redundancy_data(handle, pbuf, sz);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	// a3
	iret = breakfile_header_magic(latestfile);
	ASSERT_EQ(0, ret);
	ret = refop_get_redundancy_data(handle, prbuf, sz, &szr);
	ASSERT_EQ(REFOP_RECOVER, ret);
	ASSERT_EQ(sz, szr);
	for(int i=0;i < szr;i++) {
		checker += (prbuf[i] - (uint8_t)0xa1);
	}
	ASSERT_EQ(0, checker);

	memset(pbuf,0xa3,sz);
	ret = refop_set_redundancy_data(handle, pbuf, sz);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	// a4
	iret = breakfile_header_magic(backupfile);
	ASSERT_EQ(0, ret);
	iret = breakfile_header_magic(latestfile);
	ASSERT_EQ(0, ret);
	ret = refop_get_redundancy_data(handle, prbuf, sz, &szr);
	ASSERT_EQ(REFOP_BROAKEN, ret);

	memset(pbuf,0xa4,sz);
	ret = refop_set_redundancy_data(handle, pbuf, sz);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	ret = refop_remove_redundancy_data(handle);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	ret = refop_release_redundancy_handle(handle);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	free(pbuf);
	free(prbuf);
}
#if 0
//--------------------------------------------------------------------------------------------------------
TEST_F(interface_test, interface_test_refop_set_and_get_smallread)
{
	struct refop_halndle *hndl;
	refop_error_t ret = REFOP_SUCCESS;
	refop_handle_t handle = NULL;

	//dummy data
	char directry[] = "/tmp/refop-test/";
	char file[] = "test.bin";
	char newfile[] = "/tmp/refop-test/test.bin.tmp";
	char latestfile[] = "/tmp/refop-test/test.bin";
	char backupfile[] = "/tmp/refop-test/test.bin.bk1";
	
	uint8_t *pbuf = NULL;
	uint8_t *prbuf = NULL;
	int64_t sz = 4 * 1024;
	int64_t szr = 0;
	int checker = 0;

	(void)mkdir(directry, 0777);

	pbuf = (uint8_t*)malloc(sz);
	prbuf = (uint8_t*)malloc(sz);

	//short directry string
	ret = refop_create_redundancy_handle(&handle, directry, file);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	memset(pbuf,0,sz);
	ret = refop_set_redundancy_data(handle, pbuf, sz);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	memset(pbuf,0xff,sz);
	ret = refop_set_redundancy_data(handle, pbuf, sz);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	// Operation algorithm
	//     Current                 Next
	//    | latest | backup |     | latest | backup |
	// a1 |    1   |   2    |     |  new   |    1   |
	// a2 |    1   |   x    |     |  new   |    1   |
	// a3 |    x   |   2    |     |  new   |    2   |
	// a4 |    x   |   x    |     |  new   |    x   |
	
	// a1
	ret = refop_get_redundancy_data(handle, prbuf, sz/2, &szr);
	ASSERT_EQ(REFOP_SUCCESS, ret);
	ASSERT_EQ(sz/2, szr);
	for(int i=0;i < szr;i++) {
		checker += (prbuf[i] - (uint8_t)0xff);
	}
	ASSERT_EQ(0, checker);

	memset(pbuf,0xa1,sz);
	ret = refop_set_redundancy_data(handle, pbuf, sz);
	ASSERT_EQ(REFOP_SUCCESS, ret);


	// a2
	unlink(backupfile);
	ret = refop_get_redundancy_data(handle, prbuf, sz/2, &szr);
	ASSERT_EQ(REFOP_SUCCESS, ret);
	ASSERT_EQ(sz/2, szr);
	for(int i=0;i < szr;i++) {
		checker += (prbuf[i] - (uint8_t)0xa1);
	}
	ASSERT_EQ(0, checker);

	memset(pbuf,0xa2,sz);
	ret = refop_set_redundancy_data(handle, pbuf, sz);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	// a3
	unlink(latestfile);
	ret = refop_get_redundancy_data(handle, prbuf, sz/2, &szr);
	ASSERT_EQ(REFOP_RECOVER, ret);
	ASSERT_EQ(sz/2, szr);
	for(int i=0;i < szr;i++) {
		checker += (prbuf[i] - (uint8_t)0xa1);
	}
	ASSERT_EQ(0, checker);

	memset(pbuf,0xa3,sz);
	ret = refop_set_redundancy_data(handle, pbuf, sz);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	// a4
	unlink(backupfile);
	unlink(latestfile);
	ret = refop_get_redundancy_data(handle, prbuf, sz/2, &szr);
	ASSERT_EQ(REFOP_NOENT, ret);

	memset(pbuf,0xa4,sz);
	ret = refop_set_redundancy_data(handle, pbuf, sz);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	ret = refop_remove_redundancy_data(handle);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	ret = refop_release_redundancy_handle(handle);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	free(pbuf);
	free(prbuf);
}
//--------------------------------------------------------------------------------------------------------
TEST_F(interface_test, interface_test_refop_set_and_get_largeread)
{
	struct refop_halndle *hndl;
	refop_error_t ret = REFOP_SUCCESS;
	refop_handle_t handle = NULL;

	//dummy data
	char directry[] = "/tmp/refop-test/";
	char file[] = "test.bin";
	char newfile[] = "/tmp/refop-test/test.bin.tmp";
	char latestfile[] = "/tmp/refop-test/test.bin";
	char backupfile[] = "/tmp/refop-test/test.bin.bk1";
	
	uint8_t *pbuf = NULL;
	uint8_t *prbuf = NULL;
	int64_t sz = 256 * 1024;
	int64_t szr = 0;
	int checker = 0;

	(void)mkdir(directry, 0777);

	pbuf = (uint8_t*)malloc(sz);
	prbuf = (uint8_t*)malloc(sz);

	//short directry string
	ret = refop_create_redundancy_handle(&handle, directry, file);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	memset(pbuf,0,sz);
	ret = refop_set_redundancy_data(handle, pbuf, sz);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	memset(pbuf,0xff,sz);
	ret = refop_set_redundancy_data(handle, pbuf, sz);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	// Operation algorithm
	//     Current                 Next
	//    | latest | backup |     | latest | backup |
	// a1 |    1   |   2    |     |  new   |    1   |
	// a2 |    1   |   x    |     |  new   |    1   |
	// a3 |    x   |   2    |     |  new   |    2   |
	// a4 |    x   |   x    |     |  new   |    x   |
	
	// a1
	ret = refop_get_redundancy_data(handle, prbuf, sz*2, &szr);
	ASSERT_EQ(REFOP_SUCCESS, ret);
	ASSERT_EQ(sz, szr);
	for(int i=0;i < szr;i++) {
		checker += (prbuf[i] - (uint8_t)0xff);
	}
	ASSERT_EQ(0, checker);

	memset(pbuf,0xa1,sz);
	ret = refop_set_redundancy_data(handle, pbuf, sz);
	ASSERT_EQ(REFOP_SUCCESS, ret);


	// a2
	unlink(backupfile);
	ret = refop_get_redundancy_data(handle, prbuf, sz*2, &szr);
	ASSERT_EQ(REFOP_SUCCESS, ret);
	ASSERT_EQ(sz, szr);
	for(int i=0;i < szr;i++) {
		checker += (prbuf[i] - (uint8_t)0xa1);
	}
	ASSERT_EQ(0, checker);

	memset(pbuf,0xa2,sz);
	ret = refop_set_redundancy_data(handle, pbuf, sz);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	// a3
	unlink(latestfile);
	ret = refop_get_redundancy_data(handle, prbuf, sz*2, &szr);
	ASSERT_EQ(REFOP_RECOVER, ret);
	ASSERT_EQ(sz, szr);
	for(int i=0;i < szr;i++) {
		checker += (prbuf[i] - (uint8_t)0xa1);
	}
	ASSERT_EQ(0, checker);

	memset(pbuf,0xa3,sz);
	ret = refop_set_redundancy_data(handle, pbuf, sz);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	// a4
	unlink(backupfile);
	unlink(latestfile);
	ret = refop_get_redundancy_data(handle, prbuf, sz*2, &szr);
	ASSERT_EQ(REFOP_NOENT, ret);

	memset(pbuf,0xa4,sz);
	ret = refop_set_redundancy_data(handle, pbuf, sz);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	ret = refop_remove_redundancy_data(handle);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	ret = refop_release_redundancy_handle(handle);
	ASSERT_EQ(REFOP_SUCCESS, ret);

	free(pbuf);
	free(prbuf);
}
//--------------------------------------------------------------------------------------------------------
#endif

#!/bin/sh -e

./test/fileop_test_utils
./test/file_util_test
./test/interface_test
./test/fileop_test_set_get_remove
./test/fileop_test_unit

./test/interface_test_unit
./test/interface_test_filebreak


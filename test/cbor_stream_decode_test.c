#include <stdarg.h>
#include <stddef.h>
#include <setjmp.h>
#include <cmocka.h>
#include "cbor.h"
#include <inttypes.h>
#include "stream_expectations.h"
#include "assertions.h"

unsigned char embedded_uint8_data[] = { 0x00, 0x01, 0x05, 0x17 };
static void test_uint8_embedded_decoding(void **state)
{
	assert_uint8_eq(0);
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(embedded_uint8_data, 1)
	);

	assert_uint8_eq(1);
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(embedded_uint8_data + 1, 1)
	);

	assert_uint8_eq(5);
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(embedded_uint8_data + 2, 1)
	);

	assert_uint8_eq(23);
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(embedded_uint8_data + 3, 1)
	);
}


unsigned char uint8_data[] = { 0x18, 0x83, 0x18, 0xFF };
static void test_uint8_decoding(void **state)
{
	assert_uint8_eq(0x83);
	assert_decoder_result(2, CBOR_DECODER_FINISHED,
		decode(uint8_data, 2)
	);

	assert_uint8_eq(0xFF);
	assert_decoder_result(2, CBOR_DECODER_FINISHED,
		decode(uint8_data + 2, 2)
	);
}

unsigned char uint16_data[] = { 0x19, 0x01, 0xf4 };
static void test_uint16_decoding(void **state)
{

	assert_uint16_eq(500);
	assert_decoder_result(3, CBOR_DECODER_FINISHED,
		decode(uint16_data, 3)
	);
}

unsigned char uint32_data[] = { 0x1a, 0xa5, 0xf7, 0x02, 0xb3 };
static void test_uint32_decoding(void **state)
{
	assert_uint32_eq((uint32_t) 2784428723UL);
	assert_decoder_result(5, CBOR_DECODER_FINISHED,
		decode(uint32_data, 5)
	);
}

unsigned char uint64_data[] = { 0x1b, 0xa5, 0xf7, 0x02, 0xb3, 0xa5, 0xf7, 0x02, 0xb3 };
static void test_uint64_decoding(void **state)
{
	assert_uint64_eq(11959030306112471731ULL);
	assert_decoder_result(9, CBOR_DECODER_FINISHED,
		decode(uint64_data, 9)
	);
}

unsigned char embedded_negint8_data[] = { 0x20, 0x21, 0x25, 0x37 };
static void test_negint8_embedded_decoding(void **state)
{
	assert_negint8_eq(0);
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(embedded_negint8_data, 1)
	);

	assert_negint8_eq(1);
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(embedded_negint8_data + 1, 1)
	);

	assert_negint8_eq(5);
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(embedded_negint8_data + 2, 1)
	);

	assert_negint8_eq(23);
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(embedded_negint8_data + 3, 1)
	);
}


unsigned char negint8_data[] = { 0x38, 0x83, 0x38, 0xFF };
static void test_negint8_decoding(void **state)
{
	assert_negint8_eq(0x83);
	assert_decoder_result(2, CBOR_DECODER_FINISHED,
		decode(negint8_data, 2)
	);

	assert_negint8_eq(0xFF);
	assert_decoder_result(2, CBOR_DECODER_FINISHED,
		decode(negint8_data + 2, 2)
	);
}

unsigned char negint16_data[] = { 0x39, 0x01, 0xf4 };
static void test_negint16_decoding(void **state)
{

	assert_negint16_eq(500);
	assert_decoder_result(3, CBOR_DECODER_FINISHED,
		decode(negint16_data, 3)
	);
}

unsigned char negint32_data[] = { 0x3a, 0xa5, 0xf7, 0x02, 0xb3 };
static void test_negint32_decoding(void **state)
{
	assert_negint32_eq((uint32_t) 2784428723UL);
	assert_decoder_result(5, CBOR_DECODER_FINISHED,
		decode(negint32_data, 5)
	);
}

unsigned char negint64_data[] = { 0x3b, 0xa5, 0xf7, 0x02, 0xb3, 0xa5, 0xf7, 0x02, 0xb3 };
static void test_negint64_decoding(void **state)
{
	assert_negint64_eq(11959030306112471731ULL);
	assert_decoder_result(9, CBOR_DECODER_FINISHED,
		decode(negint64_data, 9)
	);
}

unsigned char bstring_embedded_int8_data[] = { 0x41, 0xFF };
static void test_bstring_embedded_int8_decoding(void **state)
{
	assert_bstring_mem_eq(bstring_embedded_int8_data + 1, 1);
	assert_decoder_result(2, CBOR_DECODER_FINISHED,
		decode(bstring_embedded_int8_data, 2)
	);
}

unsigned char bstring_int8_data[] = { 0x58, 0x00 };
static void test_bstring_int8_decoding(void **state)
{
	assert_bstring_mem_eq(bstring_int8_data + 2, 0);
	assert_decoder_result(2, CBOR_DECODER_FINISHED,
		decode(bstring_int8_data, 2)
	);
}

unsigned char bstring_int16_data[] = { 0x59, 0x01, 0x5C /*, [348 bytes] */ };
static void test_bstring_int16_decoding(void **state)
{
	assert_bstring_mem_eq(bstring_int16_data + 3, 348);
	assert_decoder_result(3 + 348, CBOR_DECODER_FINISHED,
		decode(bstring_int16_data, 3 + 348)
	);
}

unsigned char bstring_int32_data[] = { 0x5A, 0x00, 0x10, 0x10, 0x10 /*, [1052688 bytes] */ };
static void test_bstring_int32_decoding(void **state)
{
	assert_bstring_mem_eq(bstring_int32_data + 5, 1052688);
	assert_decoder_result(5 + 1052688, CBOR_DECODER_FINISHED,
		decode(bstring_int32_data, 5 + 1052688)
	);
}

unsigned char bstring_int64_data[] = { 0x5B, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00 /*, [4294967296 bytes] */ };
static void test_bstring_int64_decoding(void **state)
{
	assert_bstring_mem_eq(bstring_int64_data + 9, 4294967296);
	assert_decoder_result(9 + 4294967296, CBOR_DECODER_FINISHED,
		decode(bstring_int64_data, 9 + 4294967296)
	);
}


unsigned char bstring_indef_1_data[] = { 0x5F, 0x40 /* Empty byte string */, 0xFF };
static void test_bstring_indef_decoding_1(void **state)
{
	assert_bstring_indef_start();
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(bstring_indef_1_data, 3)
	);

	assert_bstring_mem_eq(bstring_indef_1_data + 2, 0);
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(bstring_indef_1_data + 1, 2)
	);

	assert_indef_break();
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(bstring_indef_1_data + 2, 1)
	);
}

unsigned char bstring_indef_2_data[] = { 0x5F, 0xFF };
static void test_bstring_indef_decoding_2(void **state)
{
	assert_bstring_indef_start();
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(bstring_indef_2_data, 2)
	);

	assert_indef_break();
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(bstring_indef_2_data + 1, 1)
	);
}

unsigned char bstring_indef_3_data[] = { 0x5F, 0x40 /* Empty byte string */, 0x58, 0x01, 0xFF /* 1B 1 char bytes string */, 0xFF };
static void test_bstring_indef_decoding_3(void **state)
{
	assert_bstring_indef_start();
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(bstring_indef_3_data, 6)
	);

	assert_bstring_mem_eq(bstring_indef_3_data + 2, 0);
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(bstring_indef_3_data + 1, 5)
	);

	assert_bstring_mem_eq(bstring_indef_3_data + 4, 1);
	assert_decoder_result(3, CBOR_DECODER_FINISHED,
		decode(bstring_indef_3_data + 2, 4)
	);

	assert_indef_break();
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(bstring_indef_3_data + 5, 1)
	);
}

unsigned char array_embedded_int8_data[] = { 0x80 };
static void test_array_embedded_int8(void **state)
{
	assert_array_start(0);
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(array_embedded_int8_data, 1)
	);
}

unsigned char array_int8_data[] = { 0x98, 0x02, 0x00, 0x01 };
static void test_array_int8(void **state)
{
	assert_array_start(2);
	assert_decoder_result(2, CBOR_DECODER_FINISHED,
		decode(array_int8_data, 4)
	);

	assert_uint8_eq(0);
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(array_int8_data + 2, 2)
	);

	assert_uint8_eq(1);
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(array_int8_data + 3, 1)
	);
}

unsigned char array_int16_data[] = { 0x99, 0x00, 0x02, 0x00, 0x01 };
static void test_array_int16(void **state)
{
	assert_array_start(2);
	assert_decoder_result(3, CBOR_DECODER_FINISHED,
		decode(array_int16_data, 5)
	);

	assert_uint8_eq(0);
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(array_int16_data + 3, 2)
	);

	assert_uint8_eq(1);
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(array_int16_data + 4, 1)
	);
}

unsigned char array_int32_data[] = { 0x9A, 0x00, 0x00, 0x00, 0x02, 0x00, 0x01 };
static void test_array_int32(void **state)
{
	assert_array_start(2);
	assert_decoder_result(5, CBOR_DECODER_FINISHED,
		decode(array_int32_data, 7)
	);

	assert_uint8_eq(0);
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(array_int32_data + 5, 2)
	);

	assert_uint8_eq(1);
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(array_int32_data + 6, 1)
	);
}

unsigned char array_int64_data[] = { 0x9B, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02, 0x00, 0x01 };
static void test_array_int64(void **state)
{
	assert_array_start(2);
	assert_decoder_result(9, CBOR_DECODER_FINISHED,
		decode(array_int64_data, 11)
	);

	assert_uint8_eq(0);
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(array_int64_data + 9, 2)
	);

	assert_uint8_eq(1);
	assert_decoder_result(1, CBOR_DECODER_FINISHED,
		decode(array_int64_data + 10, 1)
	);
}

unsigned char array_of_arrays_data[] = { 0x82, 0x80, 0x80 };
static void test_array_of_arrays(void **state)
{
	assert_array_start(2);
	assert_decoder_result(2, CBOR_DECODER_FINISHED,
		decode(array_of_arrays_data, 4)
	);

}

int main(void)
{
	set_decoder(&cbor_stream_decode);
	const UnitTest tests[] = {
		unit_test(test_uint8_embedded_decoding),
		unit_test(test_uint8_decoding),
		unit_test(test_uint16_decoding),
		unit_test(test_uint32_decoding),
		unit_test(test_uint64_decoding),

		unit_test(test_negint8_embedded_decoding),
		unit_test(test_negint8_decoding),
		unit_test(test_negint16_decoding),
		unit_test(test_negint32_decoding),
		unit_test(test_negint64_decoding),

		unit_test(test_bstring_embedded_int8_decoding),
		unit_test(test_bstring_int8_decoding),
		unit_test(test_bstring_int16_decoding),
		unit_test(test_bstring_int32_decoding),
		unit_test(test_bstring_int64_decoding),
		unit_test(test_bstring_indef_decoding_1),
		unit_test(test_bstring_indef_decoding_2),
		unit_test(test_bstring_indef_decoding_3),

		unit_test(test_array_embedded_int8),
		unit_test(test_array_int8),
		unit_test(test_array_int16),
		unit_test(test_array_int32),
		unit_test(test_array_int64)
	};
	return run_tests(tests);
}
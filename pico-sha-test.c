/* Copyright 2023, Darran A Lofthouse
 *
 * This file is part of pico-sha-test.
 *
 * pico-sha-test is free software: you can redistribute it and/or modify it under the terms 
 * of the GNU General Public License as published by the Free Software Foundation, either 
 * version 3 of the License, or (at your option) any later version.
 *
 * pico-sha-test is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 
 * without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 
 * See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with pico-sha-test.
 * If  not, see <https://www.gnu.org/licenses/>. 
 */

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "pico/stdlib.h"

#include "util/binaryutil.h"
#include "util/hexutil.h"
#include "util/systick.h"
#include "security/sha.h"

#include "pico-sha-data.h"

int main()
{
    stdio_init_all();

    printf("\n\n\nBegin SHA-1 Testing\n\n");

    printf("+-------+--------+-------------+-----------------+\n");
    printf("| Test  | Length | Pass / Fail | Syst Tick Count |\n");
    printf("+-------+--------+-------------+-----------------+\n");
    uint32_t digest[5]; // Placeholder for 160 bit digest.
    uint32_t expected_digest[5];
    
    for (short test = 0; test < 67 ; test++ ) {
        struct data_element current_element = sha_tests[test];
        short bytes = current_element.length / 8;
        char *current_data = current_element.test_data;
        char raw_test_bytes[bytes];
        for (short byte = 0 ; byte < bytes ; byte++) {
            raw_test_bytes[byte] = hex_to_char(&current_data[byte * 2]);
        }

        start_syst_counter();
        sha1_digest(raw_test_bytes, bytes, digest);
        uint32_t ticks = stop_syst_counter();

        char *expected_digest_hex = current_element.expected_hash;
        for (short pos = 0 ; pos < 5 ; pos ++) {
            char current_int[9];
            strncpy(current_int, &expected_digest_hex[pos * 8], 8);
            current_int[8] = 0;
            for (short charPos = 0; charPos < 8 ; charPos++) {
                current_int[charPos] = toupper(current_int[charPos]);
            }

            expected_digest[pos] = hex_string_to_uint32(current_int);
        }

        bool passed = true;
        for (int testIntPos = 0 ; testIntPos < 5 && passed ; testIntPos++) {
            passed = digest[testIntPos] == expected_digest[testIntPos];
        }

        printf("| %*d | %*d | %*s | %*d |\n", 5, test, 6, current_element.length, 11, passed ? "Pass" : "Fail", 15, ticks);
    }

    printf("+-------+--------+-------------+-----------------+\n");
}

#ifdef LOG_ARRAY
void log_words(uint32_t * words) {
    char binary_result[32];    
    short this_row_count = 0;

    printf("\n\nBinary Output\n\n");
    for (uint32_t word_pos = 0 ; word_pos <= 79 ; word_pos++) {
        int_to_binary(words[word_pos], binary_result);

        for (short pos = 0 ; pos < 32 ; pos++) {
            putchar(binary_result[pos]);
            if ((pos + 1) % 8 == 0) {
                putchar(' ');
            }
        }

        this_row_count = (this_row_count + 1) % 4;
        if (this_row_count == 0) {
            printf("\n");
        }
    }
}
#endif

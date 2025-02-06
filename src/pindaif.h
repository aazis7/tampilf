#ifndef PINDAI_F
#define PINDAI_F

/**
 * @file pindaif.h
 * @brief Header file for the custom `scamf` function that supports various
 * format specifiers,
 *
 * This header file declares functions and constants for scanning formatted
 *
 * @author [aazis7]
 * @version 0.0.1
 * @date [2025-02-06]
 */

/**
 * @brief Scan formatted output with variable arguments.
 *
 * This function is similar to `scanf` and supports various format specifiers,
 * including standard specifiers
 * (e.g., %d, %s, %f).
 *
 * @param format The format string.
 * @param ... The variable arguments to be formatted and scanned.
 */

int pindaif(const char *format, ...);

#endif // PINDAI_F

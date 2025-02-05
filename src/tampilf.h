#ifndef TAMPILF_H
#define TAMPILF_H

/**
 * @file tampilf.h
 * @brief Header file for the custom `tampilf` function that supports colored
 * and formatted output.
 *
 * This header file declares functions and constants for printing formatted
 * output to the console, including support for color formatting (e.g., {red},
 * {blue}) and variable argument types (e.g., integers, strings, floats).
 *
 * @author [aazis7]
 * @version 0.0.1
 * @date [2025-02-05]
 */

#define STDOUT 1 /**< STDOUT file descriptor used in the write system call */

/**
 * @brief Writes a string to the standard output using the `write` syscall.
 *
 * This function is a wrapper for the low-level `write` syscall that writes the
 * given string to the standard output (stdout).
 *
 * @param str The string to be written.
 * @param len The length of the string.
 */
static void sys_write(const char *str, int len);

/**
 * @brief Converts a number to a string representation.
 *
 * This function converts a given number into a string based on the provided
 * base (e.g., decimal, hexadecimal). It supports both signed and unsigned
 * numbers.
 *
 * @param num The number to convert.
 * @param buf The buffer to store the resulting string.
 * @param base The base for the number conversion (e.g., 10 for decimal, 16 for
 * hexadecimal).
 * @param is_unsigned Flag to indicate if the number is unsigned.
 * @param is_upper Flag to determine whether the hexadecimal digits should be
 * uppercase.
 */
static void int_to_str(long long num, char *buf, int base, int is_unsigned,
                       int is_upper);

/**
 * @brief Converts a floating-point number to a string representation.
 *
 * This function converts a floating-point number into a string with the
 * specified precision after the decimal point.
 *
 * @param num The floating-point number to convert.
 * @param buf The buffer to store the resulting string.
 * @param precision The number of digits to display after the decimal point.
 */
static void float_to_str(double num, char *buf, int precision);

/**
 * @brief Retrieves the ANSI color code corresponding to a given color name.
 *
 * This function returns the appropriate color code for supported colors (e.g.,
 * red, blue, green) to be used in terminal output formatting.
 *
 * @param color The name of the color (e.g., "red", "blue", "green").
 * @return A string representing the corresponding ANSI color code.
 */
static const char *get_color_code(const char *color);

/**
 * @brief Processes color formatting in the format string.
 *
 * This function processes the format string to identify color formatting (e.g.,
 * {red}, {blue}), replacing it with the appropriate ANSI color codes. It
 * updates the output buffer and its length.
 *
 * @param format A pointer to the format string.
 * @param output The output buffer that will contain the formatted string.
 * @param output_len A pointer to the length of the formatted output string.
 */
void process_color(const char **format, char *output, int *output_len);

/**
 * @brief Prints formatted output with variable arguments.
 *
 * This function is similar to `printf` and supports various format specifiers,
 * including color formatting (e.g., {red}, {blue}) and standard specifiers
 * (e.g., %d, %s, %f).
 *
 * @param str The format string.
 * @param ... The variable arguments to be formatted and printed.
 */
void tampilf(const char *str, ...);

#endif // TAMPILF_H

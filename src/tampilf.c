#include "tampilf.h"
#include <stdarg.h>
#include <string.h>
#include <unistd.h>

/**
 * @file tampilf.c
 * @brief Source file for the custom `tampilf` function and related helper
 * functions.
 *
 * This file contains the implementation of the `tampilf` function, which mimics
 * the behavior of the standard `printf` function with support for custom
 * formatting including color output using ANSI escape sequences.
 *
 * @author [aazis7]
 * @version 0.0.1
 * @date [2025-02-05]
 */

/**
 * @brief Writes a string to the standard output (stdout).
 *
 * This function uses the `write` system call to print the provided string to
 * standard output. It is a low-level function that directly interacts with the
 * operating system to output text.
 *
 * @param str Pointer to the string to be written.
 * @param len The length of the string to be written.
 */
static void sys_write(const char *str, int len) {
  write(STDOUT_FILENO, str, len);
}

/**
 * @brief Converts an integer (signed or unsigned) to a string.
 *
 * This function handles the conversion of both signed and unsigned integers to
 * string representations.
 *
 * @param num The number to convert.
 * @param buf The buffer to store the resulting string.
 * @param base The base for the conversion (e.g., 10 for decimal, 16 for
 * hexadecimal).
 * @param is_unsigned Flag indicating whether the number is unsigned.
 * @param is_upper Flag indicating whether the hexadecimal should be uppercase.
 */
static void int_to_str(long long num, char *buf, int base, int is_unsigned,
                       int is_upper) {
  const char *digits = is_upper ? "0123456789ABCDEF" : "0123456789abcdef";
  int i = 0, is_neg = 0;

  if (!is_unsigned && num < 0) {
    is_neg = 1;
    num = -num;
  }

  if (num == 0) { // Special case for zero
    buf[i++] = '0';
  } else {
    do {
      buf[i++] = digits[num % base];
      num /= base;
    } while (num);
  }

  if (is_neg)
    buf[i++] = '-';

  buf[i] = '\0';

  // Reverse the string to get the correct order
  for (int j = 0; j < i / 2; j++) {
    char temp = buf[j];
    buf[j] = buf[i - j - 1];
    buf[i - j - 1] = temp;
  }
}

/**
 * @brief Converts a float or double number to a string.
 *
 * This function handles the conversion of floating-point numbers (either float
 * or double) to string.
 *
 * @param num The floating-point number to convert.
 * @param buf The buffer to store the resulting string.
 * @param precision The number of decimal places to include.
 */
static void float_to_str(double num, char *buf, int precision) {
  int whole = (int)num;
  double fraction = num - whole;

  // Convert integer part to string
  char int_part[32];
  int_to_str(whole, int_part, 10, 0, 0);

  // Convert fractional part to string
  char frac_part[32];
  for (int i = 0; i < precision; i++) {
    fraction *= 10;
    frac_part[i] = ((int)fraction % 10) + '0';
    fraction -= (int)fraction;
  }
  frac_part[precision] = '\0';

  // Join integer part and fractional part
  int i = 0;
  while (int_part[i]) {
    buf[i] = int_part[i];
    i++;
  }
  buf[i++] = '.';
  int j = 0;
  while (frac_part[j]) {
    buf[i++] = frac_part[j++];
  }
  buf[i] = '\0';
}

/**
 * @brief Returns the ANSI color code for the specified color name.
 *
 * This function maps a color name (e.g., "red", "green", "blue") to its
 * corresponding ANSI escape sequence for terminal text coloring.
 *
 * @param color The color name.
 * @return The ANSI escape sequence for the color, or an empty string if the
 * color is unknown.
 */
static const char *get_color_code(const char *color) {
  if (strcmp(color, "red") == 0)
    return "\033[31m"; // Red
  if (strcmp(color, "green") == 0)
    return "\033[32m"; // Green
  if (strcmp(color, "blue") == 0)
    return "\033[34m"; // Blue
  return "";           // No color
}

/**
 * @brief Processes color codes in the format {color} and appends the
 * corresponding ANSI code.
 *
 * This function checks if the current format string contains a color directive,
 * such as {red}, and adds the appropriate color escape code to the output
 * buffer. It updates the output length accordingly and skips over the color
 * directive in the format string.
 *
 * @param format The format string (input, updated as we process it).
 * @param output The output buffer where the formatted string is stored.
 * @param output_len The current length of the output buffer.
 */
void process_color(const char **format, char *output, int *output_len) {
  if (**format == '{') {
    (*format)++; // Skip '{'
    char color[16];
    int i = 0;

    // Read color name until '}' character
    while (**format && **format != '}') {
      if (i < sizeof(color) - 1) {
        color[i++] = **format;
      }
      (*format)++;
    }
    color[i] = '\0';

    if (**format == '}') {
      (*format)++; // Skip '}'
      const char *color_code = get_color_code(color);
      if (color_code[0] != '\0') {
        // Apply color
        int color_len = strlen(color_code);
        if (*output_len + color_len < 1024) { // Ensure buffer doesn't overflow
          memcpy(output + (*output_len), color_code, color_len);
          *output_len += color_len;
        }
      }
    }
  }
}

/**
 * @brief Custom `tampilf` function that supports formatted output and color.
 *
 * This function mimics the behavior of `printf` by parsing format specifiers
 * and printing output to the standard output. It supports custom formatting,
 * including text coloring.
 *
 * @param format The format string that specifies how to print the following
 * arguments.
 * @param ... The variable arguments that correspond to the format specifiers.
 */
void tampilf(const char *format, ...) {
  char output[1024]; // Ensure buffer size is sufficient
  int output_len = 0;
  va_list args;
  va_start(args, format);

  while (*format) {
    // Check for color formatting like {red}, {blue}, etc.
    if (*format == '{') {
      process_color(&format, output, &output_len);
    } else if (*format == '%' && *(format + 1)) {
      format++; // Skip '%'

      switch (*format) {
      case 'c': { // Character
        char c = (char)va_arg(args, int);
        output[output_len++] = c;
        break;
      }

      case 's': { // String
        char *str = va_arg(args, char *);
        while (*str) {
          output[output_len++] = *str++;
        }
        break;
      }

      case 'd':
      case 'i': { // Integer
        int num = va_arg(args, int);
        char buf[32];
        int_to_str(num, buf, 10, 0, 0);
        for (int i = 0; buf[i]; i++) {
          output[output_len++] = buf[i];
        }
        break;
      }

      case 'u': { // Unsigned integer
        unsigned int num = va_arg(args, unsigned int);
        char buf[32];
        int_to_str(num, buf, 10, 1, 0);
        for (int i = 0; buf[i]; i++) {
          output[output_len++] = buf[i];
        }
        break;
      }

      case 'f':   // Float
      case 'l': { // Double
        double num = va_arg(args, double);
        char buf[64];
        float_to_str(num, buf, 6);
        for (int i = 0; buf[i]; i++) {
          output[output_len++] = buf[i];
        }
        break;
      }

      case 'x':
      case 'X': { // Hexadecimal
        unsigned int num = va_arg(args, unsigned int);
        char buf[32];
        int_to_str(num, buf, 16, 1, (*format == 'X'));
        for (int i = 0; buf[i]; i++) {
          output[output_len++] = buf[i];
        }
        break;
      }

      case 'o': { // Octal
        unsigned int num = va_arg(args, unsigned int);
        char buf[32];
        int_to_str(num, buf, 8, 1, 0);
        for (int i = 0; buf[i]; i++) {
          output[output_len++] = buf[i];
        }
        break;
      }

      case 'b': { // Binary (special additional)
        unsigned int num = va_arg(args, unsigned int);
        char buf[32];
        int_to_str(num, buf, 2, 1, 0);
        for (int i = 0; buf[i]; i++) {
          output[output_len++] = buf[i];
        }
        break;
      }

      case 'p': { // Pointer
        void *ptr = va_arg(args, void *);
        unsigned long addr = (unsigned long)ptr;
        char buf[32];
        buf[0] = '0';
        buf[1] = 'x';
        int_to_str(addr, buf + 2, 16, 1, 0);
        for (int i = 0; buf[i]; i++) {
          output[output_len++] = buf[i];
        }
        break;
      }

      case 'z': { // size_t (also can %zu)
        size_t num = va_arg(args, size_t);
        char buf[32];
        int_to_str(num, buf, 10, 1, 0);
        for (int i = 0; buf[i]; i++) {
          output[output_len++] = buf[i];
        }
        break;
      }

      default: { // If not recognized, print as is
        output[output_len++] = '%';
        output[output_len++] = *format;
      }
      }
    } else {
      output[output_len++] = *format;
    }

    format++;
  }

  // End the string and reset color
  output[output_len] = '\0';
  sys_write(output, output_len);

  // Reset to default color after printing
  sys_write("\033[0m", 4);

  va_end(args);
}

int main(void) { tampilf("hello, world!\n"); }

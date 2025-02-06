#include "pindaif.h"
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>

/**
 * @file pindaif.c
 * @brief Source file for the custom `pindaif` function and related helper
 * functions.
 *
 * This file contains the implementation of the `pindaif` function, which mimics
 * the behavior of the standard `scanf` function with support for custom
 * formatting including various format specifiers and escape sequences.
 *
 * @author [aazis7]
 * @version 0.0.1
 * @date [2025-02-06]
 */

/**
 * @brief Custom `scanf` function that supports formatted output.
 *
 * This function mimics the behavior of `scanf` by parsing format specifiers
 * and scanned output to the standard output.
 *
 * @param format The format string that specifies how to print the following
 * arguments.
 * @param ... The variable arguments that correspond to the format specifiers.
 */

int pindaif(const char *format, ...)
{
  va_list args;
  va_start(args, format);

  char buf[255];
  fgets(buf, sizeof(buf), stdin); // Read input from user

  while (*format)
  {
    if (*format == '%')
    {
      format++; // Skip '%' character

      int precision = -1; // Default without precision

      // Check if there's precision like ".2f"
      if (*format == '.')
      {
        format++;
        precision = *format - '0'; // Take num precision
        format++;                  // Skip num precision
      }

      switch (*format)
      {
        case 'd':
        { // Integer
          int *num = va_arg(args, int *);
          *num     = atoi(buf);
          break;
        }

        case 'f':
        { // Float with precision
          float *num = va_arg(args, float *);
          *num       = strtof(buf, NULL);
          break;
        }

        case 'l':
        {           // Double with precision (%.1lf - %.6lf)
          format++; // Skip 'l'
          if (*format == 'f')
          {
            double *num = va_arg(args, double *);
            *num        = strtod(buf, NULL);
          }
          break;
        }

        case 'c':
        {
          char *ch = va_arg(args, char *);
          *ch      = buf[0]; // Take first character
          break;
        }

        case 's':
        {
          char *str = va_arg(args, char *);
          sscanf(buf, "%s", str); // Read args and buf
          break;
        }

        default:
        {
          printf("Unknown format: %%%c\n", *format);
          break;
        }
      }
    }
    format++;
  }

  va_end(args);
  return 1; // Return 1 for success indication
}

int main(void)
{
  int x;

  printf("x: ");
  pindaif("%d\n", &x);

  printf("x: %d\n", x);
}

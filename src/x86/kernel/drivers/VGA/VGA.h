#ifndef VGA_H
#define VGA_H

#include "../../util/strings/strings.h"
#include "../IO/IO.h"
#include <stdint.h>
#include <stddef.h>

void clearScreen(char** vga, unsigned char bg, unsigned char fg);
void kputs(const char* string, char** vga, unsigned short nlDepth);
void kputs_dec(int number, char** vga, unsigned short nlDepth);
void kputs_hex(int hex_num, char** vga, unsigned short nlDepth);
void update_cursor(int x, int y); 

#endif

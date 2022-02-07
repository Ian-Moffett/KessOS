#include "../interrupts/IDT.h"
#include "../drivers/IO/IO.h"


static char* get_key(int scancode) {
    switch (scancode) {
		case 1:
			return "ESC";
		case 2:
	        	return "1";
		case 3:
			return "2";
		case 4:
			return "3";
		case 5:
			return "4";
		case 6:
			return "5";
		case 7:
			return "6";
		case 8:
			return "7";
		case 9:
			return "8";
		case 10:
			return "9";
		case 11:
			return "0";
		case 12:
			return "-";
		case 53:
			return "/";
		case 55:
			return "*";
		case 13:
			return "+";
		case 28:
			return "Enter";
		case  30:
			return "A";
		case 48:
			return "B";
		case 46:
			return "C";
		case 32:
			return "D";
		case 18:
			return "E";
		case 33:
			return "F";
		case 34:
			return "G";
		case 35:
			return "H";
		case 23:
			return "I";
		case 36:
			return "J";
		case 37:
			return "K";
		case 38:
			return "L";
		case 50:
			return "M";
		case 49:
			return "N";
		case 24:
			return "O";
		case 25:
			return "P";
		case 16:
			return "Q";
		case 19:
			return "R";
		case 31:
			return "S";
		case 20:
			return "T";
		case 22:
			return "U";
		case 47:
			return "V";
		case 17:
			return "W";
		case 45:
			return "X";
		case 21:
			return "Y";
		case 44:
			return "Z";
        	case 0x84:
        	case 0x88:
        	case 0x8C:
        	case 0x90:
        	case 0x94:
        	case 0x98:
        	case 0x9C:
        	case 0xA0:
        	case 0xA4:
        	case 0xA8:
        	case 0xAC:
        	case 0xB0:
            		return 0x0;
	}

    return 0x0;
}

static unsigned int x = 17;
static unsigned int y = 0;


__attribute__((interrupt)) void irq1_isr(int_frame32_t*) {
    extern char* vga;

    const uint8_t* const SC_ASCII = "\x00\x1B" "1234567890-=" "\x08"
    "\x00" "qwertyuiop[]" "\x0D\x1D" "asdfghjkl;'`" "\x00" "\\"
    "zxcvbnm,./" "\x00\x00\x00" " ";

    unsigned int scancode = inportb(0x60);
    unsigned int status = inportb(0x64);

    if (get_key(scancode) != 0x0 && scancode != 57 && scancode != 1 && SC_ASCII[scancode] != '\x08' && x < 40) {
        *(vga + 2) = ' ';
        *vga = get_key(scancode)[0];
        vga += 2;
        *(vga + 2) = '|';
        ++x;
    } else if (scancode == 57 && x < 40) {   // 23 chars max.
        *(vga + 2) = ' ';
        *vga = ' ';
        vga += 2;
        *(vga + 2) = '|';
        ++x;
    } else if (SC_ASCII[scancode] == '\x08' && x > 17) {
        *(vga + 2) = ' ';
        vga -= 2;
        *vga = ' ';
        *(vga + 2) = '|';
        --x;
    }

    outportb(0x64, 0xFF);
    outportb(0x20, 0x20);
}



int _main() {

}

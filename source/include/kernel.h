/* required libraries */
#include "keymap.h"

/* VGA buffer values */
#ifndef KERNEL_H
#define KERNEL_H

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned int uint32;

#define VGA_ADDRESS 0xB8000
#define BUFSIZE 2200

uint16* vga_buffer;

#define NULL 0

/* VGA color table */

enum vga_color {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    GREY,
    DARK_GREY,
    BRIGHT_BLUE,
    BRIGHT_GREEN,
    BRIGHT_CYAN,
    BRIGHT_RED,
    BRIGHT_MAGENTA,
    YELLOW,
    WHITE,
};

#endif


/* index for video buffer array */
uint32 vga_index;
/* counter to store new lines  */
static uint32 next_line_index = 1;
/* fore & back color values  */
uint8 g_fore_color = WHITE, g_back_color = BLUE;
/* digit ascii code for printing integers  */
int digit_ascii_codes[10] = {0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};


//index for video buffer array
/*
16 bit video buffer elements(register ax)
8 bits(ah) higher : 
  lower 4 bits - fore color
  higher 4 bits - back color

8 bits(al) lower :
  8 bits : ASCII character to print
*/

/* VGA entry colors */
uint16 vga_entry(unsigned char ch, uint8 fore_color, uint8 back_color) 
{
  uint16 ax = 0;
  uint8 ah = 0, al = 0;

  ah = back_color;
  ah <<= 4;
  ah |= fore_color;
  ax = ah;
  ax <<= 8;
  al = ch;
  ax |= al;

  return ax;
}


/* clear video buffer array */
void clear_vga_buffer(uint16 **buffer, uint8 fore_color, uint8 back_color)
{
  uint32 i;
  for(i = 0; i < BUFSIZE; i++){
    (*buffer)[i] = vga_entry(NULL, fore_color, back_color);
  }
  next_line_index = 1;
  vga_index = 0;
}

/* initialize vga buffer */ 
void init_vga(uint8 fore_color, uint8 back_color)
{
  vga_buffer = (uint16*)VGA_ADDRESS;
  clear_vga_buffer(&vga_buffer, fore_color, back_color);
  g_fore_color = fore_color;
  g_back_color = back_color;
}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Assembly Input/Output */

/* input port control */
uint8 inb(uint16 port) {
  uint8 ret;
  asm volatile("inb %1, %0" : "=a"(ret) : "d"(port));
  return ret;
}

/* output port control */
void outb(uint16 port, uint8 data) {
  asm volatile("outb %0, %1" : "=a"(data) : "d"(port));
}

/* digit counter function */
uint32 digit_count(int num)
{
  uint32 count = 0;
  if(num == 0)
    return 1;
  while(num > 0){
    count++;
    num = num/10;
  }
  return count;
}


/* convert data type (int to string) */
void itoa(int num, char *number)
{
  int dgcount = digit_count(num);
  int index = dgcount - 1;
  char x;
  if(num == 0 && dgcount == 1){
    number[0] = '0';
    number[1] = '\0';
  }else{
    while(num != 0){
      x = num % 10;
      number[index] = x + '0';
      index--;
      num = num / 10;
    }
    number[dgcount] = '\0';
  }
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* keep the cpu busy for doing nothing (NOP) Assembly function */
void nop(uint32 timer_count) {
  while(1){
    asm volatile("nop");
    timer_count--;
    if(timer_count <= 0)
      break;
    }
}

/* conventional sleep function */
void sleep(uint32 timer_count) {
  nop(timer_count);
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* print new line */
void crlf() {
  if (next_line_index >= 55) {
    next_line_index = 0;
    clear_vga_buffer(&vga_buffer, g_fore_color, g_back_color);
  }
  vga_index = 80*next_line_index;
  next_line_index++;
}


/* single char output */
void print_char(char ch) {
  vga_buffer[vga_index] = vga_entry(ch, g_fore_color, g_back_color);
  vga_index++;
}

/* print int variable value */
void print_int(int num) {
  char str_num[digit_count(num)+1];
  itoa(num, str_num);
  print_string(str_num);
}

/* return string length */
uint32 strlen(const char* str) {
  uint32 length = 0;
  while(str[length])
    length++;
  return length;
}

/* print string */
void print_string(char *str) {
  uint32 index = 0;
  while(str[index]) {
    print_char(str[index]);
    index++;
  }
}

/* get input keyboard ascii code */
char get_input_keycode() {
  char ch = 0;
  while((ch = inb(KEYBOARD_PORT)) != 0){
    if(ch > 0)
      return ch;
  }
  return ch;
}


/* keyboard input function */
void kinput() {
  char ch = 0;
  char keycode = 0;
  do {
    keycode = get_input_keycode();
    if (keycode == KEY_ENTER) {
      crlf();
      print_string("root@miletus# ");
      sleep(0x06FFFFFF);
    }
    else {uint32 digit_count(int num)
{
  uint32 count = 0;
  if(num == 0)
    return 1;
  while(num > 0){
    count++;
    num = num/10;
  }
  return count;
}
      ch = get_input_keycode(keycode);
      if (ch == KEY_A) {
        print_char(97);
        sleep(0x05FFFFFF);
      }
      else if (ch == KEY_B) {
        print_char(98);
        sleep(0x05FFFFFF);
      }
      else if (ch == KEY_C) {
        print_char(99);
        sleep(0x05FFFFFF);
      }
      /* verificar na função backspace o controle do vga_index (para não apagar o menu do terminal) */
      /* carregar informacoes do hardware durante inicialização do kernel */
      /* após o carregamento do hardware, chamar a funcao konsole() que irá exercer a função de terminal */
      /* atualizar estrutura de pastas e substituir na pasta MTOS (Mytheril OS)*/
      else if (ch = KEY_BACKSPACE) {
        vga_index--;
        print_string(" ");
        sleep(0x06FFFFFF);
        vga_index--;
      }    
    }
    sleep(0x02FFFFFF);
  }
  while(ch > 0);
}

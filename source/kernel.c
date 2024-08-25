/* required libraries */
#include "include/kernel.h"


void kernel_entry()
{
  //first init vga with fore & back colors
  init_vga(GREY, BLACK);

  /*call above function to print something
    here to change the fore & back color
    assign g_fore_color & g_back_color to color values
    g_fore_color = BRIGHT_RED;
  */

  print_string("root~0.0.7# ");
  sleep(0x20FFFFFF);
  print_string("helo, kernel world!");
  crlf();
  print_string("Hello");
  kinput();

}
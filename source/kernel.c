/* required libraries */
#include "include/kernel.h"

/* Konsole */
void konsole() {
  print_string("root~# ");
  //print_int(vga_index_buffer);
  //print_int(vga_index_buffer);
  kinput();
  //crlf();
  //print_string("root~# ");
  //print_int(vga_index_buffer);
}

void kernel_entry() {
  //first init vga with fore & back colors
  init_vga(GREY, BLACK);

  /*call above function to print something
    here to change the fore & back color
    assign g_fore_color & g_back_color to color values
    g_fore_color = BRIGHT_RED;
  */
  //sleep(0x20FFFFFF);
  print_string("Mytheril (Developer Edition)");
  crlf();
  print_string("Kernel 0.0.0-22");
  crlf();
  konsole();

}
/**************************************************************************************************

MIT License

Copyright (c) RISC-V Steel

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

**************************************************************************************************/

/**************************************************************************************************

Project Name:  RISC-V Steel SoC
Project Repo:  github.com/riscv-steel/riscv-steel
Author:        Rafael Calcada 
E-mail:        rafaelcalcada@gmail.com

Top Module:    rvsteel_soc
 
**************************************************************************************************/

/**************************************************************************************************

Remarks:

  - 'clock' is connected to Cmod's 12MHz board clock.
  - 'reset' is connected to BTN1 on the board
  - UART signals are connect to Cmod's UART-USB bridge

**************************************************************************************************/
module hello_world_cmod_a7 (

  input   wire clock,
  input   wire reset,
  input   wire uart_rx,
  output  wire uart_tx

  );

  rvsteel_soc #(

    .CLOCK_FREQUENCY          (12000000           ),
    .UART_BAUD_RATE           (9600               ),
    .MEMORY_SIZE              (8192               ),
    .MEMORY_INIT_FILE         ("hello-world.mem"  ),
    .FILL_UNUSED_MEMORY_WITH  (32'hdeadbeef       ),
    .BOOT_ADDRESS             (32'h00000000       )

  ) rvsteel_soc_instance (
    
    .clock                    (clock              ),
    .reset                    (reset              ),
    .uart_rx                  (uart_rx            ),
    .uart_tx                  (uart_tx            )

  );

endmodule
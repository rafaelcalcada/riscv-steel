cd [file normalize [file dirname [info script]]]
create_project freertos_arty_a7_100t ./freertos_arty_a7_100t -part xc7a100ticsg324-1L -force
set_msg_config -suppress -id {Synth 8-7080}
set_msg_config -suppress -id {Power 33-332}
set_msg_config -suppress -id {Pwropt 34-321}
set_msg_config -suppress -id {Synth 8-6841}
set_msg_config -suppress -id {Netlist 29-101}
set_msg_config -suppress -id {Device 21-9320} 
set_msg_config -suppress -id {Device 21-2174}
set_property simulator_language Verilog [current_project]
add_files -fileset constrs_1 -norecurse { ./freertos_arty_a7_constraints.xdc }
add_files -norecurse .
add_files -norecurse { ../../../../hardware/rvsteel.v }
add_files -norecurse { ../../../../hardware/rvsteel_core.v }
add_files -norecurse { ../../../../hardware/rvsteel_bus.v }
add_files -norecurse { ../../../../hardware/rvsteel_uart.v }
add_files -norecurse { ../../../../hardware/rvsteel_mtimer.v }
add_files -norecurse { ../../../../hardware/rvsteel_gpio.v }
add_files -norecurse { ../../../../hardware/rvsteel_spi.v }
add_files -norecurse { ../../../../hardware/rvsteel_ram.v }
add_files -norecurse { ../../software/build/freertos.hex }
set_property file_type {Memory Initialization Files} [get_files ../../software/build/freertos.hex]
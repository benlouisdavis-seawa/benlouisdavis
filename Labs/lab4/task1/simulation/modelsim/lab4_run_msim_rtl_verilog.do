transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -sv -work work +incdir+C:/Users/bdavi/OneDrive/Desktop/EE\ 371/Labs/lab4/task1 {C:/Users/bdavi/OneDrive/Desktop/EE 371/Labs/lab4/task1/lab4task1_ASM.sv}
vlog -sv -work work +incdir+C:/Users/bdavi/OneDrive/Desktop/EE\ 371/Labs/lab4/task1 {C:/Users/bdavi/OneDrive/Desktop/EE 371/Labs/lab4/task1/lab4task1_FSM.sv}
vlog -sv -work work +incdir+C:/Users/bdavi/OneDrive/Desktop/EE\ 371/Labs/lab4/task1 {C:/Users/bdavi/OneDrive/Desktop/EE 371/Labs/lab4/task1/hexadecimal.sv}
vlog -sv -work work +incdir+C:/Users/bdavi/OneDrive/Desktop/EE\ 371/Labs/lab4/task1 {C:/Users/bdavi/OneDrive/Desktop/EE 371/Labs/lab4/task1/lab4task1_fpga.sv}


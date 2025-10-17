transcript on
if {[file exists rtl_work]} {
	vdel -lib rtl_work -all
}
vlib rtl_work
vmap work rtl_work

vlog -sv -work work +incdir+C:/Users/bdavi/OneDrive/Desktop/EE\ 371/Labs/lab2/task3/Lab2_Task3_skeleton/Lab2_Task3_skeleton {C:/Users/bdavi/OneDrive/Desktop/EE 371/Labs/lab2/task3/Lab2_Task3_skeleton/Lab2_Task3_skeleton/FIFO_Control.sv}
vlog -sv -work work +incdir+C:/Users/bdavi/OneDrive/Desktop/EE\ 371/Labs/lab2/task3/Lab2_Task3_skeleton/Lab2_Task3_skeleton {C:/Users/bdavi/OneDrive/Desktop/EE 371/Labs/lab2/task3/Lab2_Task3_skeleton/Lab2_Task3_skeleton/DE1_SoC_fifo.sv}
vlog -sv -work work +incdir+C:/Users/bdavi/OneDrive/Desktop/EE\ 371/Labs/lab2/task3/Lab2_Task3_skeleton/Lab2_Task3_skeleton {C:/Users/bdavi/OneDrive/Desktop/EE 371/Labs/lab2/task3/Lab2_Task3_skeleton/Lab2_Task3_skeleton/hexadecimal.sv}
vlog -sv -work work +incdir+C:/Users/bdavi/OneDrive/Desktop/EE\ 371/Labs/lab2/task3/Lab2_Task3_skeleton/Lab2_Task3_skeleton {C:/Users/bdavi/OneDrive/Desktop/EE 371/Labs/lab2/task3/Lab2_Task3_skeleton/Lab2_Task3_skeleton/RAM_16x8.sv}
vlog -sv -work work +incdir+C:/Users/bdavi/OneDrive/Desktop/EE\ 371/Labs/lab2/task3/Lab2_Task3_skeleton/Lab2_Task3_skeleton {C:/Users/bdavi/OneDrive/Desktop/EE 371/Labs/lab2/task3/Lab2_Task3_skeleton/Lab2_Task3_skeleton/FIFO.sv}


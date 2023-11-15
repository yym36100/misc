# Copyright (C) 1991-2013 Altera Corporation
# Your use of Altera Corporation's design tools, logic functions 
# and other software and tools, and its AMPP partner logic 
# functions, and any output files from any of the foregoing 
# (including device programming or simulation files), and any 
# associated documentation or information are expressly subject 
# to the terms and conditions of the Altera Program License 
# Subscription Agreement, Altera MegaCore Function License 
# Agreement, or other applicable license agreement, including, 
# without limitation, that your use is for the sole purpose of 
# programming logic devices manufactured by Altera and sold by 
# Altera or its authorized distributors.  Please refer to the 
# applicable agreement for further details.

# Quartus II: Generate Tcl File for Project
# File: staticramtest.tcl
# Generated on: Fri Nov 06 09:01:03 2015

# Load Quartus II Tcl Project package
package require ::quartus::project

set need_to_close_project 0
set make_assignments 1

# Check that the right project is open
if {[is_project_open]} {
	if {[string compare $quartus(project) "staticramtest"]} {
		puts "Project staticramtest is not open"
		set make_assignments 0
	}
} else {
	# Only open if not already open
	if {[project_exists staticramtest]} {
		project_open -revision staticramtest staticramtest
	} else {
		project_new -revision staticramtest staticramtest
	}
	set need_to_close_project 1
}

# Make assignments
if {$make_assignments} {
	set_global_assignment -name FAMILY "Cyclone IV E"
	set_global_assignment -name DEVICE EP4CE22F17C6
	set_global_assignment -name ORIGINAL_QUARTUS_VERSION 12.0
	set_global_assignment -name LAST_QUARTUS_VERSION "13.0 SP1"
	set_global_assignment -name PROJECT_CREATION_TIME_DATE "10:12:30 NOVEMBER 05,2015"
	set_global_assignment -name DEVICE_FILTER_PACKAGE FBGA
	set_global_assignment -name DEVICE_FILTER_PIN_COUNT 256
	set_global_assignment -name DEVICE_FILTER_SPEED_GRADE 6
	set_global_assignment -name PARTITION_NETLIST_TYPE SOURCE -section_id Top
	set_global_assignment -name PARTITION_FITTER_PRESERVATION_LEVEL PLACEMENT_AND_ROUTING -section_id Top
	set_global_assignment -name PARTITION_COLOR 16764057 -section_id Top
	set_global_assignment -name PHYSICAL_SYNTHESIS_EFFORT FAST
	set_global_assignment -name SYNTH_TIMING_DRIVEN_SYNTHESIS ON
	set_global_assignment -name VERILOG_FILE ../hw/sram.v
	set_global_assignment -name VERILOG_FILE ../hw/staticramtest.v
	set_global_assignment -name SDC_FILE ../hw/staticramtest.sdc
	set_global_assignment -name VECTOR_WAVEFORM_FILE ../hw/Waveform.vwf
	set_global_assignment -name SIMULATION_MODE FUNCTIONAL
	set_global_assignment -name EDA_SIMULATION_TOOL "ModelSim-Altera (Verilog)"
	set_global_assignment -name EDA_OUTPUT_DATA_FORMAT "VERILOG HDL" -section_id eda_simulation
	set_global_assignment -name EDA_GENERATE_FUNCTIONAL_NETLIST ON -section_id eda_simulation
	set_global_assignment -name INCREMENTAL_VECTOR_INPUT_SOURCE "E:/fpgaproj/de0_nano/myproj/staticramtest/hw/Waveform.vwf"
	set_location_assignment PIN_R8 -to CLOCK_50
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to CLOCK_50
	set_location_assignment PIN_A15 -to LED[0]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to LED[0]
	set_location_assignment PIN_A13 -to LED[1]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to LED[1]
	set_location_assignment PIN_B13 -to LED[2]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to LED[2]
	set_location_assignment PIN_A11 -to LED[3]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to LED[3]
	set_location_assignment PIN_D1 -to LED[4]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to LED[4]
	set_location_assignment PIN_F3 -to LED[5]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to LED[5]
	set_location_assignment PIN_B1 -to LED[6]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to LED[6]
	set_location_assignment PIN_L3 -to LED[7]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to LED[7]
	set_location_assignment PIN_A8 -to top_IN[0]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top_IN[0]
	set_location_assignment PIN_D3 -to top[0]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[0]
	set_location_assignment PIN_B8 -to top_IN[1]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top_IN[1]
	set_location_assignment PIN_C3 -to top[1]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[1]
	set_location_assignment PIN_A2 -to top[2]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[2]
	set_location_assignment PIN_A3 -to top[3]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[3]
	set_location_assignment PIN_B3 -to top[4]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[4]
	set_location_assignment PIN_B4 -to top[5]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[5]
	set_location_assignment PIN_A4 -to top[6]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[6]
	set_location_assignment PIN_B5 -to top[7]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[7]
	set_location_assignment PIN_A5 -to top[8]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[8]
	set_location_assignment PIN_D5 -to top[9]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[9]
	set_location_assignment PIN_B6 -to top[10]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[10]
	set_location_assignment PIN_A6 -to top[11]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[11]
	set_location_assignment PIN_B7 -to top[12]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[12]
	set_location_assignment PIN_D6 -to top[13]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[13]
	set_location_assignment PIN_A7 -to top[14]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[14]
	set_location_assignment PIN_C6 -to top[15]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[15]
	set_location_assignment PIN_C8 -to top[16]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[16]
	set_location_assignment PIN_E6 -to top[17]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[17]
	set_location_assignment PIN_E7 -to top[18]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[18]
	set_location_assignment PIN_D8 -to top[19]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[19]
	set_location_assignment PIN_E8 -to top[20]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[20]
	set_location_assignment PIN_F8 -to top[21]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[21]
	set_location_assignment PIN_F9 -to top[22]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[22]
	set_location_assignment PIN_E9 -to top[23]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[23]
	set_location_assignment PIN_C9 -to top[24]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[24]
	set_location_assignment PIN_D9 -to top[25]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[25]
	set_location_assignment PIN_E11 -to top[26]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[26]
	set_location_assignment PIN_E10 -to top[27]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[27]
	set_location_assignment PIN_C11 -to top[28]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[28]
	set_location_assignment PIN_B11 -to top[29]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[29]
	set_location_assignment PIN_A12 -to top[30]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[30]
	set_location_assignment PIN_D11 -to top[31]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[31]
	set_location_assignment PIN_D12 -to top[32]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[32]
	set_location_assignment PIN_B12 -to top[33]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to top[33]
	set_location_assignment PIN_T9 -to bottom_IN[0]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom_IN[0]
	set_location_assignment PIN_F13 -to bottom[0]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[0]
	set_location_assignment PIN_R9 -to bottom_IN[1]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom_IN[1]
	set_location_assignment PIN_T15 -to bottom[1]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[1]
	set_location_assignment PIN_T14 -to bottom[2]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[2]
	set_location_assignment PIN_T13 -to bottom[3]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[3]
	set_location_assignment PIN_R13 -to bottom[4]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[4]
	set_location_assignment PIN_T12 -to bottom[5]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[5]
	set_location_assignment PIN_R12 -to bottom[6]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[6]
	set_location_assignment PIN_T11 -to bottom[7]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[7]
	set_location_assignment PIN_T10 -to bottom[8]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[8]
	set_location_assignment PIN_R11 -to bottom[9]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[9]
	set_location_assignment PIN_P11 -to bottom[10]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[10]
	set_location_assignment PIN_R10 -to bottom[11]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[11]
	set_location_assignment PIN_N12 -to bottom[12]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[12]
	set_location_assignment PIN_P9 -to bottom[13]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[13]
	set_location_assignment PIN_N9 -to bottom[14]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[14]
	set_location_assignment PIN_N11 -to bottom[15]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[15]
	set_location_assignment PIN_L16 -to bottom[16]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[16]
	set_location_assignment PIN_K16 -to bottom[17]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[17]
	set_location_assignment PIN_R16 -to bottom[18]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[18]
	set_location_assignment PIN_L15 -to bottom[19]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[19]
	set_location_assignment PIN_P15 -to bottom[20]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[20]
	set_location_assignment PIN_P16 -to bottom[21]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[21]
	set_location_assignment PIN_R14 -to bottom[22]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[22]
	set_location_assignment PIN_N16 -to bottom[23]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[23]
	set_location_assignment PIN_N15 -to bottom[24]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[24]
	set_location_assignment PIN_P14 -to bottom[25]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[25]
	set_location_assignment PIN_L14 -to bottom[26]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[26]
	set_location_assignment PIN_N14 -to bottom[27]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[27]
	set_location_assignment PIN_M10 -to bottom[28]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[28]
	set_location_assignment PIN_L13 -to bottom[29]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[29]
	set_location_assignment PIN_J16 -to bottom[30]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[30]
	set_location_assignment PIN_K15 -to bottom[31]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[31]
	set_location_assignment PIN_J13 -to bottom[32]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[32]
	set_location_assignment PIN_J14 -to bottom[33]
	set_instance_assignment -name IO_STANDARD "3.3-V LVTTL" -to bottom[33]
	set_instance_assignment -name PARTITION_HIERARCHY root_partition -to | -section_id Top

	# Commit assignments
	export_assignments

	# Close project
	if {$need_to_close_project} {
		project_close
	}
}

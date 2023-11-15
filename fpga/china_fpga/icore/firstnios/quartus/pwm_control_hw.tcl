# TCL File Generated by Component Editor 13.0sp1
# Fri Nov 13 10:18:23 EET 2015
# DO NOT MODIFY


# 
# pwm_control "pwm_control" v1.0
#  2015.11.13.10:18:23
# 
# 

# 
# request TCL package from ACDS 13.1
# 
package require -exact qsys 13.1


# 
# module pwm_control
# 
set_module_property DESCRIPTION ""
set_module_property NAME pwm_control
set_module_property VERSION 1.0
set_module_property INTERNAL false
set_module_property OPAQUE_ADDRESS_MAP true
set_module_property AUTHOR ""
set_module_property DISPLAY_NAME pwm_control
set_module_property INSTANTIATE_IN_SYSTEM_MODULE true
set_module_property EDITABLE true
set_module_property ANALYZE_HDL AUTO
set_module_property REPORT_TO_TALKBACK false
set_module_property ALLOW_GREYBOX_GENERATION false


# 
# file sets
# 
add_fileset QUARTUS_SYNTH QUARTUS_SYNTH "" ""
set_fileset_property QUARTUS_SYNTH TOP_LEVEL pwm_control
set_fileset_property QUARTUS_SYNTH ENABLE_RELATIVE_INCLUDE_PATHS false
add_fileset_file pwm_control.v VERILOG PATH ../hw/pwm_control.v TOP_LEVEL_FILE


# 
# parameters
# 
add_parameter S_idle INTEGER 0
set_parameter_property S_idle DEFAULT_VALUE 0
set_parameter_property S_idle DISPLAY_NAME S_idle
set_parameter_property S_idle TYPE INTEGER
set_parameter_property S_idle UNITS None
set_parameter_property S_idle HDL_PARAMETER true
add_parameter S_pwm INTEGER 1
set_parameter_property S_pwm DEFAULT_VALUE 1
set_parameter_property S_pwm DISPLAY_NAME S_pwm
set_parameter_property S_pwm TYPE INTEGER
set_parameter_property S_pwm UNITS None
set_parameter_property S_pwm HDL_PARAMETER true
add_parameter S_waiting INTEGER 2
set_parameter_property S_waiting DEFAULT_VALUE 2
set_parameter_property S_waiting DISPLAY_NAME S_waiting
set_parameter_property S_waiting TYPE INTEGER
set_parameter_property S_waiting UNITS None
set_parameter_property S_waiting HDL_PARAMETER true


# 
# display items
# 


# 
# connection point reset
# 
add_interface reset reset end
set_interface_property reset associatedClock clock_sink
set_interface_property reset synchronousEdges DEASSERT
set_interface_property reset ENABLED true
set_interface_property reset EXPORT_OF ""
set_interface_property reset PORT_NAME_MAP ""
set_interface_property reset SVD_ADDRESS_GROUP ""

add_interface_port reset reset_n reset_n Input 1


# 
# connection point avalon_slave
# 
add_interface avalon_slave avalon end
set_interface_property avalon_slave addressUnits WORDS
set_interface_property avalon_slave associatedClock clock_sink
set_interface_property avalon_slave associatedReset reset
set_interface_property avalon_slave bitsPerSymbol 8
set_interface_property avalon_slave burstOnBurstBoundariesOnly false
set_interface_property avalon_slave burstcountUnits WORDS
set_interface_property avalon_slave explicitAddressSpan 0
set_interface_property avalon_slave holdTime 0
set_interface_property avalon_slave linewrapBursts false
set_interface_property avalon_slave maximumPendingReadTransactions 0
set_interface_property avalon_slave readLatency 0
set_interface_property avalon_slave readWaitTime 1
set_interface_property avalon_slave setupTime 0
set_interface_property avalon_slave timingUnits Cycles
set_interface_property avalon_slave writeWaitTime 0
set_interface_property avalon_slave ENABLED true
set_interface_property avalon_slave EXPORT_OF ""
set_interface_property avalon_slave PORT_NAME_MAP ""
set_interface_property avalon_slave SVD_ADDRESS_GROUP ""

add_interface_port avalon_slave address address Input 2
add_interface_port avalon_slave chipselect chipselect Input 1
add_interface_port avalon_slave write_n write_n Input 1
add_interface_port avalon_slave writedata writedata Input 32
add_interface_port avalon_slave readdata readdata Output 32
set_interface_assignment avalon_slave embeddedsw.configuration.isFlash 0
set_interface_assignment avalon_slave embeddedsw.configuration.isMemoryDevice 0
set_interface_assignment avalon_slave embeddedsw.configuration.isNonVolatileStorage 0
set_interface_assignment avalon_slave embeddedsw.configuration.isPrintableDevice 0


# 
# connection point clock_sink
# 
add_interface clock_sink clock end
set_interface_property clock_sink clockRate 0
set_interface_property clock_sink ENABLED true
set_interface_property clock_sink EXPORT_OF ""
set_interface_property clock_sink PORT_NAME_MAP ""
set_interface_property clock_sink SVD_ADDRESS_GROUP ""

add_interface_port clock_sink a_50_MHZ_CLK clk Input 1


# 
# connection point conduit_end
# 
add_interface conduit_end conduit end
set_interface_property conduit_end associatedClock ""
set_interface_property conduit_end associatedReset ""
set_interface_property conduit_end ENABLED true
set_interface_property conduit_end EXPORT_OF ""
set_interface_property conduit_end PORT_NAME_MAP ""
set_interface_property conduit_end SVD_ADDRESS_GROUP ""

add_interface_port conduit_end pwmDrive export Output 2
add_interface_port conduit_end done export Output 1

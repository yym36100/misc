//megafunction wizard: %Altera SOPC Builder%
//GENERATION: STANDARD
//VERSION: WM1.0


//Legal Notice: (C)2013 Altera Corporation. All rights reserved.  Your
//use of Altera Corporation's design tools, logic functions and other
//software and tools, and its AMPP partner logic functions, and any
//output files any of the foregoing (including device programming or
//simulation files), and any associated documentation or information are
//expressly subject to the terms and conditions of the Altera Program
//License Subscription Agreement or other applicable license agreement,
//including, without limitation, that your use is for the sole purpose
//of programming logic devices manufactured by Altera and sold by Altera
//or its authorized distributors.  Please refer to the applicable
//agreement for further details.

// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module ADC_DATA_s1_arbitrator (
                                // inputs:
                                 ADC_DATA_s1_readdata,
                                 clk,
                                 cpu_0_data_master_address_to_slave,
                                 cpu_0_data_master_latency_counter,
                                 cpu_0_data_master_read,
                                 cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                 cpu_0_data_master_write,
                                 cpu_0_data_master_writedata,
                                 reset_n,

                                // outputs:
                                 ADC_DATA_s1_address,
                                 ADC_DATA_s1_chipselect,
                                 ADC_DATA_s1_readdata_from_sa,
                                 ADC_DATA_s1_reset_n,
                                 ADC_DATA_s1_write_n,
                                 ADC_DATA_s1_writedata,
                                 cpu_0_data_master_granted_ADC_DATA_s1,
                                 cpu_0_data_master_qualified_request_ADC_DATA_s1,
                                 cpu_0_data_master_read_data_valid_ADC_DATA_s1,
                                 cpu_0_data_master_requests_ADC_DATA_s1,
                                 d1_ADC_DATA_s1_end_xfer
                              )
;

  output  [  1: 0] ADC_DATA_s1_address;
  output           ADC_DATA_s1_chipselect;
  output  [ 31: 0] ADC_DATA_s1_readdata_from_sa;
  output           ADC_DATA_s1_reset_n;
  output           ADC_DATA_s1_write_n;
  output  [ 31: 0] ADC_DATA_s1_writedata;
  output           cpu_0_data_master_granted_ADC_DATA_s1;
  output           cpu_0_data_master_qualified_request_ADC_DATA_s1;
  output           cpu_0_data_master_read_data_valid_ADC_DATA_s1;
  output           cpu_0_data_master_requests_ADC_DATA_s1;
  output           d1_ADC_DATA_s1_end_xfer;
  input   [ 31: 0] ADC_DATA_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] ADC_DATA_s1_address;
  wire             ADC_DATA_s1_allgrants;
  wire             ADC_DATA_s1_allow_new_arb_cycle;
  wire             ADC_DATA_s1_any_bursting_master_saved_grant;
  wire             ADC_DATA_s1_any_continuerequest;
  wire             ADC_DATA_s1_arb_counter_enable;
  reg     [  1: 0] ADC_DATA_s1_arb_share_counter;
  wire    [  1: 0] ADC_DATA_s1_arb_share_counter_next_value;
  wire    [  1: 0] ADC_DATA_s1_arb_share_set_values;
  wire             ADC_DATA_s1_beginbursttransfer_internal;
  wire             ADC_DATA_s1_begins_xfer;
  wire             ADC_DATA_s1_chipselect;
  wire             ADC_DATA_s1_end_xfer;
  wire             ADC_DATA_s1_firsttransfer;
  wire             ADC_DATA_s1_grant_vector;
  wire             ADC_DATA_s1_in_a_read_cycle;
  wire             ADC_DATA_s1_in_a_write_cycle;
  wire             ADC_DATA_s1_master_qreq_vector;
  wire             ADC_DATA_s1_non_bursting_master_requests;
  wire    [ 31: 0] ADC_DATA_s1_readdata_from_sa;
  reg              ADC_DATA_s1_reg_firsttransfer;
  wire             ADC_DATA_s1_reset_n;
  reg              ADC_DATA_s1_slavearbiterlockenable;
  wire             ADC_DATA_s1_slavearbiterlockenable2;
  wire             ADC_DATA_s1_unreg_firsttransfer;
  wire             ADC_DATA_s1_waits_for_read;
  wire             ADC_DATA_s1_waits_for_write;
  wire             ADC_DATA_s1_write_n;
  wire    [ 31: 0] ADC_DATA_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_ADC_DATA_s1;
  wire             cpu_0_data_master_qualified_request_ADC_DATA_s1;
  wire             cpu_0_data_master_read_data_valid_ADC_DATA_s1;
  wire             cpu_0_data_master_requests_ADC_DATA_s1;
  wire             cpu_0_data_master_saved_grant_ADC_DATA_s1;
  reg              d1_ADC_DATA_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_ADC_DATA_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_ADC_DATA_s1_from_cpu_0_data_master;
  wire             wait_for_ADC_DATA_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~ADC_DATA_s1_end_xfer;
    end


  assign ADC_DATA_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_ADC_DATA_s1));
  //assign ADC_DATA_s1_readdata_from_sa = ADC_DATA_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign ADC_DATA_s1_readdata_from_sa = ADC_DATA_s1_readdata;

  assign cpu_0_data_master_requests_ADC_DATA_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002150) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //ADC_DATA_s1_arb_share_counter set values, which is an e_mux
  assign ADC_DATA_s1_arb_share_set_values = 1;

  //ADC_DATA_s1_non_bursting_master_requests mux, which is an e_mux
  assign ADC_DATA_s1_non_bursting_master_requests = cpu_0_data_master_requests_ADC_DATA_s1;

  //ADC_DATA_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign ADC_DATA_s1_any_bursting_master_saved_grant = 0;

  //ADC_DATA_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign ADC_DATA_s1_arb_share_counter_next_value = ADC_DATA_s1_firsttransfer ? (ADC_DATA_s1_arb_share_set_values - 1) : |ADC_DATA_s1_arb_share_counter ? (ADC_DATA_s1_arb_share_counter - 1) : 0;

  //ADC_DATA_s1_allgrants all slave grants, which is an e_mux
  assign ADC_DATA_s1_allgrants = |ADC_DATA_s1_grant_vector;

  //ADC_DATA_s1_end_xfer assignment, which is an e_assign
  assign ADC_DATA_s1_end_xfer = ~(ADC_DATA_s1_waits_for_read | ADC_DATA_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_ADC_DATA_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_ADC_DATA_s1 = ADC_DATA_s1_end_xfer & (~ADC_DATA_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //ADC_DATA_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign ADC_DATA_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_ADC_DATA_s1 & ADC_DATA_s1_allgrants) | (end_xfer_arb_share_counter_term_ADC_DATA_s1 & ~ADC_DATA_s1_non_bursting_master_requests);

  //ADC_DATA_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ADC_DATA_s1_arb_share_counter <= 0;
      else if (ADC_DATA_s1_arb_counter_enable)
          ADC_DATA_s1_arb_share_counter <= ADC_DATA_s1_arb_share_counter_next_value;
    end


  //ADC_DATA_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ADC_DATA_s1_slavearbiterlockenable <= 0;
      else if ((|ADC_DATA_s1_master_qreq_vector & end_xfer_arb_share_counter_term_ADC_DATA_s1) | (end_xfer_arb_share_counter_term_ADC_DATA_s1 & ~ADC_DATA_s1_non_bursting_master_requests))
          ADC_DATA_s1_slavearbiterlockenable <= |ADC_DATA_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master ADC_DATA/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = ADC_DATA_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //ADC_DATA_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign ADC_DATA_s1_slavearbiterlockenable2 = |ADC_DATA_s1_arb_share_counter_next_value;

  //cpu_0/data_master ADC_DATA/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = ADC_DATA_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //ADC_DATA_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign ADC_DATA_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_ADC_DATA_s1 = cpu_0_data_master_requests_ADC_DATA_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_ADC_DATA_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_ADC_DATA_s1 = cpu_0_data_master_granted_ADC_DATA_s1 & cpu_0_data_master_read & ~ADC_DATA_s1_waits_for_read;

  //ADC_DATA_s1_writedata mux, which is an e_mux
  assign ADC_DATA_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_ADC_DATA_s1 = cpu_0_data_master_qualified_request_ADC_DATA_s1;

  //cpu_0/data_master saved-grant ADC_DATA/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_ADC_DATA_s1 = cpu_0_data_master_requests_ADC_DATA_s1;

  //allow new arb cycle for ADC_DATA/s1, which is an e_assign
  assign ADC_DATA_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign ADC_DATA_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign ADC_DATA_s1_master_qreq_vector = 1;

  //ADC_DATA_s1_reset_n assignment, which is an e_assign
  assign ADC_DATA_s1_reset_n = reset_n;

  assign ADC_DATA_s1_chipselect = cpu_0_data_master_granted_ADC_DATA_s1;
  //ADC_DATA_s1_firsttransfer first transaction, which is an e_assign
  assign ADC_DATA_s1_firsttransfer = ADC_DATA_s1_begins_xfer ? ADC_DATA_s1_unreg_firsttransfer : ADC_DATA_s1_reg_firsttransfer;

  //ADC_DATA_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign ADC_DATA_s1_unreg_firsttransfer = ~(ADC_DATA_s1_slavearbiterlockenable & ADC_DATA_s1_any_continuerequest);

  //ADC_DATA_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ADC_DATA_s1_reg_firsttransfer <= 1'b1;
      else if (ADC_DATA_s1_begins_xfer)
          ADC_DATA_s1_reg_firsttransfer <= ADC_DATA_s1_unreg_firsttransfer;
    end


  //ADC_DATA_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign ADC_DATA_s1_beginbursttransfer_internal = ADC_DATA_s1_begins_xfer;

  //~ADC_DATA_s1_write_n assignment, which is an e_mux
  assign ADC_DATA_s1_write_n = ~(cpu_0_data_master_granted_ADC_DATA_s1 & cpu_0_data_master_write);

  assign shifted_address_to_ADC_DATA_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //ADC_DATA_s1_address mux, which is an e_mux
  assign ADC_DATA_s1_address = shifted_address_to_ADC_DATA_s1_from_cpu_0_data_master >> 2;

  //d1_ADC_DATA_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_ADC_DATA_s1_end_xfer <= 1;
      else 
        d1_ADC_DATA_s1_end_xfer <= ADC_DATA_s1_end_xfer;
    end


  //ADC_DATA_s1_waits_for_read in a cycle, which is an e_mux
  assign ADC_DATA_s1_waits_for_read = ADC_DATA_s1_in_a_read_cycle & ADC_DATA_s1_begins_xfer;

  //ADC_DATA_s1_in_a_read_cycle assignment, which is an e_assign
  assign ADC_DATA_s1_in_a_read_cycle = cpu_0_data_master_granted_ADC_DATA_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = ADC_DATA_s1_in_a_read_cycle;

  //ADC_DATA_s1_waits_for_write in a cycle, which is an e_mux
  assign ADC_DATA_s1_waits_for_write = ADC_DATA_s1_in_a_write_cycle & 0;

  //ADC_DATA_s1_in_a_write_cycle assignment, which is an e_assign
  assign ADC_DATA_s1_in_a_write_cycle = cpu_0_data_master_granted_ADC_DATA_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = ADC_DATA_s1_in_a_write_cycle;

  assign wait_for_ADC_DATA_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //ADC_DATA/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module BUZZER_DATA_s1_arbitrator (
                                   // inputs:
                                    BUZZER_DATA_s1_readdata,
                                    clk,
                                    cpu_0_data_master_address_to_slave,
                                    cpu_0_data_master_latency_counter,
                                    cpu_0_data_master_read,
                                    cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                    cpu_0_data_master_write,
                                    cpu_0_data_master_writedata,
                                    reset_n,

                                   // outputs:
                                    BUZZER_DATA_s1_address,
                                    BUZZER_DATA_s1_chipselect,
                                    BUZZER_DATA_s1_readdata_from_sa,
                                    BUZZER_DATA_s1_reset_n,
                                    BUZZER_DATA_s1_write_n,
                                    BUZZER_DATA_s1_writedata,
                                    cpu_0_data_master_granted_BUZZER_DATA_s1,
                                    cpu_0_data_master_qualified_request_BUZZER_DATA_s1,
                                    cpu_0_data_master_read_data_valid_BUZZER_DATA_s1,
                                    cpu_0_data_master_requests_BUZZER_DATA_s1,
                                    d1_BUZZER_DATA_s1_end_xfer
                                 )
;

  output  [  1: 0] BUZZER_DATA_s1_address;
  output           BUZZER_DATA_s1_chipselect;
  output  [ 31: 0] BUZZER_DATA_s1_readdata_from_sa;
  output           BUZZER_DATA_s1_reset_n;
  output           BUZZER_DATA_s1_write_n;
  output  [ 31: 0] BUZZER_DATA_s1_writedata;
  output           cpu_0_data_master_granted_BUZZER_DATA_s1;
  output           cpu_0_data_master_qualified_request_BUZZER_DATA_s1;
  output           cpu_0_data_master_read_data_valid_BUZZER_DATA_s1;
  output           cpu_0_data_master_requests_BUZZER_DATA_s1;
  output           d1_BUZZER_DATA_s1_end_xfer;
  input   [ 31: 0] BUZZER_DATA_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] BUZZER_DATA_s1_address;
  wire             BUZZER_DATA_s1_allgrants;
  wire             BUZZER_DATA_s1_allow_new_arb_cycle;
  wire             BUZZER_DATA_s1_any_bursting_master_saved_grant;
  wire             BUZZER_DATA_s1_any_continuerequest;
  wire             BUZZER_DATA_s1_arb_counter_enable;
  reg     [  1: 0] BUZZER_DATA_s1_arb_share_counter;
  wire    [  1: 0] BUZZER_DATA_s1_arb_share_counter_next_value;
  wire    [  1: 0] BUZZER_DATA_s1_arb_share_set_values;
  wire             BUZZER_DATA_s1_beginbursttransfer_internal;
  wire             BUZZER_DATA_s1_begins_xfer;
  wire             BUZZER_DATA_s1_chipselect;
  wire             BUZZER_DATA_s1_end_xfer;
  wire             BUZZER_DATA_s1_firsttransfer;
  wire             BUZZER_DATA_s1_grant_vector;
  wire             BUZZER_DATA_s1_in_a_read_cycle;
  wire             BUZZER_DATA_s1_in_a_write_cycle;
  wire             BUZZER_DATA_s1_master_qreq_vector;
  wire             BUZZER_DATA_s1_non_bursting_master_requests;
  wire    [ 31: 0] BUZZER_DATA_s1_readdata_from_sa;
  reg              BUZZER_DATA_s1_reg_firsttransfer;
  wire             BUZZER_DATA_s1_reset_n;
  reg              BUZZER_DATA_s1_slavearbiterlockenable;
  wire             BUZZER_DATA_s1_slavearbiterlockenable2;
  wire             BUZZER_DATA_s1_unreg_firsttransfer;
  wire             BUZZER_DATA_s1_waits_for_read;
  wire             BUZZER_DATA_s1_waits_for_write;
  wire             BUZZER_DATA_s1_write_n;
  wire    [ 31: 0] BUZZER_DATA_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_BUZZER_DATA_s1;
  wire             cpu_0_data_master_qualified_request_BUZZER_DATA_s1;
  wire             cpu_0_data_master_read_data_valid_BUZZER_DATA_s1;
  wire             cpu_0_data_master_requests_BUZZER_DATA_s1;
  wire             cpu_0_data_master_saved_grant_BUZZER_DATA_s1;
  reg              d1_BUZZER_DATA_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_BUZZER_DATA_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_BUZZER_DATA_s1_from_cpu_0_data_master;
  wire             wait_for_BUZZER_DATA_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~BUZZER_DATA_s1_end_xfer;
    end


  assign BUZZER_DATA_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_BUZZER_DATA_s1));
  //assign BUZZER_DATA_s1_readdata_from_sa = BUZZER_DATA_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign BUZZER_DATA_s1_readdata_from_sa = BUZZER_DATA_s1_readdata;

  assign cpu_0_data_master_requests_BUZZER_DATA_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002130) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //BUZZER_DATA_s1_arb_share_counter set values, which is an e_mux
  assign BUZZER_DATA_s1_arb_share_set_values = 1;

  //BUZZER_DATA_s1_non_bursting_master_requests mux, which is an e_mux
  assign BUZZER_DATA_s1_non_bursting_master_requests = cpu_0_data_master_requests_BUZZER_DATA_s1;

  //BUZZER_DATA_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign BUZZER_DATA_s1_any_bursting_master_saved_grant = 0;

  //BUZZER_DATA_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign BUZZER_DATA_s1_arb_share_counter_next_value = BUZZER_DATA_s1_firsttransfer ? (BUZZER_DATA_s1_arb_share_set_values - 1) : |BUZZER_DATA_s1_arb_share_counter ? (BUZZER_DATA_s1_arb_share_counter - 1) : 0;

  //BUZZER_DATA_s1_allgrants all slave grants, which is an e_mux
  assign BUZZER_DATA_s1_allgrants = |BUZZER_DATA_s1_grant_vector;

  //BUZZER_DATA_s1_end_xfer assignment, which is an e_assign
  assign BUZZER_DATA_s1_end_xfer = ~(BUZZER_DATA_s1_waits_for_read | BUZZER_DATA_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_BUZZER_DATA_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_BUZZER_DATA_s1 = BUZZER_DATA_s1_end_xfer & (~BUZZER_DATA_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //BUZZER_DATA_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign BUZZER_DATA_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_BUZZER_DATA_s1 & BUZZER_DATA_s1_allgrants) | (end_xfer_arb_share_counter_term_BUZZER_DATA_s1 & ~BUZZER_DATA_s1_non_bursting_master_requests);

  //BUZZER_DATA_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          BUZZER_DATA_s1_arb_share_counter <= 0;
      else if (BUZZER_DATA_s1_arb_counter_enable)
          BUZZER_DATA_s1_arb_share_counter <= BUZZER_DATA_s1_arb_share_counter_next_value;
    end


  //BUZZER_DATA_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          BUZZER_DATA_s1_slavearbiterlockenable <= 0;
      else if ((|BUZZER_DATA_s1_master_qreq_vector & end_xfer_arb_share_counter_term_BUZZER_DATA_s1) | (end_xfer_arb_share_counter_term_BUZZER_DATA_s1 & ~BUZZER_DATA_s1_non_bursting_master_requests))
          BUZZER_DATA_s1_slavearbiterlockenable <= |BUZZER_DATA_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master BUZZER_DATA/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = BUZZER_DATA_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //BUZZER_DATA_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign BUZZER_DATA_s1_slavearbiterlockenable2 = |BUZZER_DATA_s1_arb_share_counter_next_value;

  //cpu_0/data_master BUZZER_DATA/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = BUZZER_DATA_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //BUZZER_DATA_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign BUZZER_DATA_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_BUZZER_DATA_s1 = cpu_0_data_master_requests_BUZZER_DATA_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_BUZZER_DATA_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_BUZZER_DATA_s1 = cpu_0_data_master_granted_BUZZER_DATA_s1 & cpu_0_data_master_read & ~BUZZER_DATA_s1_waits_for_read;

  //BUZZER_DATA_s1_writedata mux, which is an e_mux
  assign BUZZER_DATA_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_BUZZER_DATA_s1 = cpu_0_data_master_qualified_request_BUZZER_DATA_s1;

  //cpu_0/data_master saved-grant BUZZER_DATA/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_BUZZER_DATA_s1 = cpu_0_data_master_requests_BUZZER_DATA_s1;

  //allow new arb cycle for BUZZER_DATA/s1, which is an e_assign
  assign BUZZER_DATA_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign BUZZER_DATA_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign BUZZER_DATA_s1_master_qreq_vector = 1;

  //BUZZER_DATA_s1_reset_n assignment, which is an e_assign
  assign BUZZER_DATA_s1_reset_n = reset_n;

  assign BUZZER_DATA_s1_chipselect = cpu_0_data_master_granted_BUZZER_DATA_s1;
  //BUZZER_DATA_s1_firsttransfer first transaction, which is an e_assign
  assign BUZZER_DATA_s1_firsttransfer = BUZZER_DATA_s1_begins_xfer ? BUZZER_DATA_s1_unreg_firsttransfer : BUZZER_DATA_s1_reg_firsttransfer;

  //BUZZER_DATA_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign BUZZER_DATA_s1_unreg_firsttransfer = ~(BUZZER_DATA_s1_slavearbiterlockenable & BUZZER_DATA_s1_any_continuerequest);

  //BUZZER_DATA_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          BUZZER_DATA_s1_reg_firsttransfer <= 1'b1;
      else if (BUZZER_DATA_s1_begins_xfer)
          BUZZER_DATA_s1_reg_firsttransfer <= BUZZER_DATA_s1_unreg_firsttransfer;
    end


  //BUZZER_DATA_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign BUZZER_DATA_s1_beginbursttransfer_internal = BUZZER_DATA_s1_begins_xfer;

  //~BUZZER_DATA_s1_write_n assignment, which is an e_mux
  assign BUZZER_DATA_s1_write_n = ~(cpu_0_data_master_granted_BUZZER_DATA_s1 & cpu_0_data_master_write);

  assign shifted_address_to_BUZZER_DATA_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //BUZZER_DATA_s1_address mux, which is an e_mux
  assign BUZZER_DATA_s1_address = shifted_address_to_BUZZER_DATA_s1_from_cpu_0_data_master >> 2;

  //d1_BUZZER_DATA_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_BUZZER_DATA_s1_end_xfer <= 1;
      else 
        d1_BUZZER_DATA_s1_end_xfer <= BUZZER_DATA_s1_end_xfer;
    end


  //BUZZER_DATA_s1_waits_for_read in a cycle, which is an e_mux
  assign BUZZER_DATA_s1_waits_for_read = BUZZER_DATA_s1_in_a_read_cycle & BUZZER_DATA_s1_begins_xfer;

  //BUZZER_DATA_s1_in_a_read_cycle assignment, which is an e_assign
  assign BUZZER_DATA_s1_in_a_read_cycle = cpu_0_data_master_granted_BUZZER_DATA_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = BUZZER_DATA_s1_in_a_read_cycle;

  //BUZZER_DATA_s1_waits_for_write in a cycle, which is an e_mux
  assign BUZZER_DATA_s1_waits_for_write = BUZZER_DATA_s1_in_a_write_cycle & 0;

  //BUZZER_DATA_s1_in_a_write_cycle assignment, which is an e_assign
  assign BUZZER_DATA_s1_in_a_write_cycle = cpu_0_data_master_granted_BUZZER_DATA_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = BUZZER_DATA_s1_in_a_write_cycle;

  assign wait_for_BUZZER_DATA_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //BUZZER_DATA/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module DAC_DATA_s1_arbitrator (
                                // inputs:
                                 DAC_DATA_s1_readdata,
                                 clk,
                                 cpu_0_data_master_address_to_slave,
                                 cpu_0_data_master_latency_counter,
                                 cpu_0_data_master_read,
                                 cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                 cpu_0_data_master_write,
                                 cpu_0_data_master_writedata,
                                 reset_n,

                                // outputs:
                                 DAC_DATA_s1_address,
                                 DAC_DATA_s1_chipselect,
                                 DAC_DATA_s1_readdata_from_sa,
                                 DAC_DATA_s1_reset_n,
                                 DAC_DATA_s1_write_n,
                                 DAC_DATA_s1_writedata,
                                 cpu_0_data_master_granted_DAC_DATA_s1,
                                 cpu_0_data_master_qualified_request_DAC_DATA_s1,
                                 cpu_0_data_master_read_data_valid_DAC_DATA_s1,
                                 cpu_0_data_master_requests_DAC_DATA_s1,
                                 d1_DAC_DATA_s1_end_xfer
                              )
;

  output  [  1: 0] DAC_DATA_s1_address;
  output           DAC_DATA_s1_chipselect;
  output  [ 31: 0] DAC_DATA_s1_readdata_from_sa;
  output           DAC_DATA_s1_reset_n;
  output           DAC_DATA_s1_write_n;
  output  [ 31: 0] DAC_DATA_s1_writedata;
  output           cpu_0_data_master_granted_DAC_DATA_s1;
  output           cpu_0_data_master_qualified_request_DAC_DATA_s1;
  output           cpu_0_data_master_read_data_valid_DAC_DATA_s1;
  output           cpu_0_data_master_requests_DAC_DATA_s1;
  output           d1_DAC_DATA_s1_end_xfer;
  input   [ 31: 0] DAC_DATA_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] DAC_DATA_s1_address;
  wire             DAC_DATA_s1_allgrants;
  wire             DAC_DATA_s1_allow_new_arb_cycle;
  wire             DAC_DATA_s1_any_bursting_master_saved_grant;
  wire             DAC_DATA_s1_any_continuerequest;
  wire             DAC_DATA_s1_arb_counter_enable;
  reg     [  1: 0] DAC_DATA_s1_arb_share_counter;
  wire    [  1: 0] DAC_DATA_s1_arb_share_counter_next_value;
  wire    [  1: 0] DAC_DATA_s1_arb_share_set_values;
  wire             DAC_DATA_s1_beginbursttransfer_internal;
  wire             DAC_DATA_s1_begins_xfer;
  wire             DAC_DATA_s1_chipselect;
  wire             DAC_DATA_s1_end_xfer;
  wire             DAC_DATA_s1_firsttransfer;
  wire             DAC_DATA_s1_grant_vector;
  wire             DAC_DATA_s1_in_a_read_cycle;
  wire             DAC_DATA_s1_in_a_write_cycle;
  wire             DAC_DATA_s1_master_qreq_vector;
  wire             DAC_DATA_s1_non_bursting_master_requests;
  wire    [ 31: 0] DAC_DATA_s1_readdata_from_sa;
  reg              DAC_DATA_s1_reg_firsttransfer;
  wire             DAC_DATA_s1_reset_n;
  reg              DAC_DATA_s1_slavearbiterlockenable;
  wire             DAC_DATA_s1_slavearbiterlockenable2;
  wire             DAC_DATA_s1_unreg_firsttransfer;
  wire             DAC_DATA_s1_waits_for_read;
  wire             DAC_DATA_s1_waits_for_write;
  wire             DAC_DATA_s1_write_n;
  wire    [ 31: 0] DAC_DATA_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_DAC_DATA_s1;
  wire             cpu_0_data_master_qualified_request_DAC_DATA_s1;
  wire             cpu_0_data_master_read_data_valid_DAC_DATA_s1;
  wire             cpu_0_data_master_requests_DAC_DATA_s1;
  wire             cpu_0_data_master_saved_grant_DAC_DATA_s1;
  reg              d1_DAC_DATA_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_DAC_DATA_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_DAC_DATA_s1_from_cpu_0_data_master;
  wire             wait_for_DAC_DATA_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~DAC_DATA_s1_end_xfer;
    end


  assign DAC_DATA_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_DAC_DATA_s1));
  //assign DAC_DATA_s1_readdata_from_sa = DAC_DATA_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign DAC_DATA_s1_readdata_from_sa = DAC_DATA_s1_readdata;

  assign cpu_0_data_master_requests_DAC_DATA_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002140) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //DAC_DATA_s1_arb_share_counter set values, which is an e_mux
  assign DAC_DATA_s1_arb_share_set_values = 1;

  //DAC_DATA_s1_non_bursting_master_requests mux, which is an e_mux
  assign DAC_DATA_s1_non_bursting_master_requests = cpu_0_data_master_requests_DAC_DATA_s1;

  //DAC_DATA_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign DAC_DATA_s1_any_bursting_master_saved_grant = 0;

  //DAC_DATA_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign DAC_DATA_s1_arb_share_counter_next_value = DAC_DATA_s1_firsttransfer ? (DAC_DATA_s1_arb_share_set_values - 1) : |DAC_DATA_s1_arb_share_counter ? (DAC_DATA_s1_arb_share_counter - 1) : 0;

  //DAC_DATA_s1_allgrants all slave grants, which is an e_mux
  assign DAC_DATA_s1_allgrants = |DAC_DATA_s1_grant_vector;

  //DAC_DATA_s1_end_xfer assignment, which is an e_assign
  assign DAC_DATA_s1_end_xfer = ~(DAC_DATA_s1_waits_for_read | DAC_DATA_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_DAC_DATA_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_DAC_DATA_s1 = DAC_DATA_s1_end_xfer & (~DAC_DATA_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //DAC_DATA_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign DAC_DATA_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_DAC_DATA_s1 & DAC_DATA_s1_allgrants) | (end_xfer_arb_share_counter_term_DAC_DATA_s1 & ~DAC_DATA_s1_non_bursting_master_requests);

  //DAC_DATA_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          DAC_DATA_s1_arb_share_counter <= 0;
      else if (DAC_DATA_s1_arb_counter_enable)
          DAC_DATA_s1_arb_share_counter <= DAC_DATA_s1_arb_share_counter_next_value;
    end


  //DAC_DATA_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          DAC_DATA_s1_slavearbiterlockenable <= 0;
      else if ((|DAC_DATA_s1_master_qreq_vector & end_xfer_arb_share_counter_term_DAC_DATA_s1) | (end_xfer_arb_share_counter_term_DAC_DATA_s1 & ~DAC_DATA_s1_non_bursting_master_requests))
          DAC_DATA_s1_slavearbiterlockenable <= |DAC_DATA_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master DAC_DATA/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = DAC_DATA_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //DAC_DATA_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign DAC_DATA_s1_slavearbiterlockenable2 = |DAC_DATA_s1_arb_share_counter_next_value;

  //cpu_0/data_master DAC_DATA/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = DAC_DATA_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //DAC_DATA_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign DAC_DATA_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_DAC_DATA_s1 = cpu_0_data_master_requests_DAC_DATA_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_DAC_DATA_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_DAC_DATA_s1 = cpu_0_data_master_granted_DAC_DATA_s1 & cpu_0_data_master_read & ~DAC_DATA_s1_waits_for_read;

  //DAC_DATA_s1_writedata mux, which is an e_mux
  assign DAC_DATA_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_DAC_DATA_s1 = cpu_0_data_master_qualified_request_DAC_DATA_s1;

  //cpu_0/data_master saved-grant DAC_DATA/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_DAC_DATA_s1 = cpu_0_data_master_requests_DAC_DATA_s1;

  //allow new arb cycle for DAC_DATA/s1, which is an e_assign
  assign DAC_DATA_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign DAC_DATA_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign DAC_DATA_s1_master_qreq_vector = 1;

  //DAC_DATA_s1_reset_n assignment, which is an e_assign
  assign DAC_DATA_s1_reset_n = reset_n;

  assign DAC_DATA_s1_chipselect = cpu_0_data_master_granted_DAC_DATA_s1;
  //DAC_DATA_s1_firsttransfer first transaction, which is an e_assign
  assign DAC_DATA_s1_firsttransfer = DAC_DATA_s1_begins_xfer ? DAC_DATA_s1_unreg_firsttransfer : DAC_DATA_s1_reg_firsttransfer;

  //DAC_DATA_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign DAC_DATA_s1_unreg_firsttransfer = ~(DAC_DATA_s1_slavearbiterlockenable & DAC_DATA_s1_any_continuerequest);

  //DAC_DATA_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          DAC_DATA_s1_reg_firsttransfer <= 1'b1;
      else if (DAC_DATA_s1_begins_xfer)
          DAC_DATA_s1_reg_firsttransfer <= DAC_DATA_s1_unreg_firsttransfer;
    end


  //DAC_DATA_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign DAC_DATA_s1_beginbursttransfer_internal = DAC_DATA_s1_begins_xfer;

  //~DAC_DATA_s1_write_n assignment, which is an e_mux
  assign DAC_DATA_s1_write_n = ~(cpu_0_data_master_granted_DAC_DATA_s1 & cpu_0_data_master_write);

  assign shifted_address_to_DAC_DATA_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //DAC_DATA_s1_address mux, which is an e_mux
  assign DAC_DATA_s1_address = shifted_address_to_DAC_DATA_s1_from_cpu_0_data_master >> 2;

  //d1_DAC_DATA_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_DAC_DATA_s1_end_xfer <= 1;
      else 
        d1_DAC_DATA_s1_end_xfer <= DAC_DATA_s1_end_xfer;
    end


  //DAC_DATA_s1_waits_for_read in a cycle, which is an e_mux
  assign DAC_DATA_s1_waits_for_read = DAC_DATA_s1_in_a_read_cycle & DAC_DATA_s1_begins_xfer;

  //DAC_DATA_s1_in_a_read_cycle assignment, which is an e_assign
  assign DAC_DATA_s1_in_a_read_cycle = cpu_0_data_master_granted_DAC_DATA_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = DAC_DATA_s1_in_a_read_cycle;

  //DAC_DATA_s1_waits_for_write in a cycle, which is an e_mux
  assign DAC_DATA_s1_waits_for_write = DAC_DATA_s1_in_a_write_cycle & 0;

  //DAC_DATA_s1_in_a_write_cycle assignment, which is an e_assign
  assign DAC_DATA_s1_in_a_write_cycle = cpu_0_data_master_granted_DAC_DATA_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = DAC_DATA_s1_in_a_write_cycle;

  assign wait_for_DAC_DATA_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //DAC_DATA/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module ETH_CLKOUT_I_s1_arbitrator (
                                    // inputs:
                                     ETH_CLKOUT_I_s1_readdata,
                                     clk,
                                     cpu_0_data_master_address_to_slave,
                                     cpu_0_data_master_latency_counter,
                                     cpu_0_data_master_read,
                                     cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                     cpu_0_data_master_write,
                                     cpu_0_data_master_writedata,
                                     reset_n,

                                    // outputs:
                                     ETH_CLKOUT_I_s1_address,
                                     ETH_CLKOUT_I_s1_chipselect,
                                     ETH_CLKOUT_I_s1_readdata_from_sa,
                                     ETH_CLKOUT_I_s1_reset_n,
                                     ETH_CLKOUT_I_s1_write_n,
                                     ETH_CLKOUT_I_s1_writedata,
                                     cpu_0_data_master_granted_ETH_CLKOUT_I_s1,
                                     cpu_0_data_master_qualified_request_ETH_CLKOUT_I_s1,
                                     cpu_0_data_master_read_data_valid_ETH_CLKOUT_I_s1,
                                     cpu_0_data_master_requests_ETH_CLKOUT_I_s1,
                                     d1_ETH_CLKOUT_I_s1_end_xfer
                                  )
;

  output  [  1: 0] ETH_CLKOUT_I_s1_address;
  output           ETH_CLKOUT_I_s1_chipselect;
  output  [ 31: 0] ETH_CLKOUT_I_s1_readdata_from_sa;
  output           ETH_CLKOUT_I_s1_reset_n;
  output           ETH_CLKOUT_I_s1_write_n;
  output  [ 31: 0] ETH_CLKOUT_I_s1_writedata;
  output           cpu_0_data_master_granted_ETH_CLKOUT_I_s1;
  output           cpu_0_data_master_qualified_request_ETH_CLKOUT_I_s1;
  output           cpu_0_data_master_read_data_valid_ETH_CLKOUT_I_s1;
  output           cpu_0_data_master_requests_ETH_CLKOUT_I_s1;
  output           d1_ETH_CLKOUT_I_s1_end_xfer;
  input   [ 31: 0] ETH_CLKOUT_I_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] ETH_CLKOUT_I_s1_address;
  wire             ETH_CLKOUT_I_s1_allgrants;
  wire             ETH_CLKOUT_I_s1_allow_new_arb_cycle;
  wire             ETH_CLKOUT_I_s1_any_bursting_master_saved_grant;
  wire             ETH_CLKOUT_I_s1_any_continuerequest;
  wire             ETH_CLKOUT_I_s1_arb_counter_enable;
  reg     [  1: 0] ETH_CLKOUT_I_s1_arb_share_counter;
  wire    [  1: 0] ETH_CLKOUT_I_s1_arb_share_counter_next_value;
  wire    [  1: 0] ETH_CLKOUT_I_s1_arb_share_set_values;
  wire             ETH_CLKOUT_I_s1_beginbursttransfer_internal;
  wire             ETH_CLKOUT_I_s1_begins_xfer;
  wire             ETH_CLKOUT_I_s1_chipselect;
  wire             ETH_CLKOUT_I_s1_end_xfer;
  wire             ETH_CLKOUT_I_s1_firsttransfer;
  wire             ETH_CLKOUT_I_s1_grant_vector;
  wire             ETH_CLKOUT_I_s1_in_a_read_cycle;
  wire             ETH_CLKOUT_I_s1_in_a_write_cycle;
  wire             ETH_CLKOUT_I_s1_master_qreq_vector;
  wire             ETH_CLKOUT_I_s1_non_bursting_master_requests;
  wire    [ 31: 0] ETH_CLKOUT_I_s1_readdata_from_sa;
  reg              ETH_CLKOUT_I_s1_reg_firsttransfer;
  wire             ETH_CLKOUT_I_s1_reset_n;
  reg              ETH_CLKOUT_I_s1_slavearbiterlockenable;
  wire             ETH_CLKOUT_I_s1_slavearbiterlockenable2;
  wire             ETH_CLKOUT_I_s1_unreg_firsttransfer;
  wire             ETH_CLKOUT_I_s1_waits_for_read;
  wire             ETH_CLKOUT_I_s1_waits_for_write;
  wire             ETH_CLKOUT_I_s1_write_n;
  wire    [ 31: 0] ETH_CLKOUT_I_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_ETH_CLKOUT_I_s1;
  wire             cpu_0_data_master_qualified_request_ETH_CLKOUT_I_s1;
  wire             cpu_0_data_master_read_data_valid_ETH_CLKOUT_I_s1;
  wire             cpu_0_data_master_requests_ETH_CLKOUT_I_s1;
  wire             cpu_0_data_master_saved_grant_ETH_CLKOUT_I_s1;
  reg              d1_ETH_CLKOUT_I_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_ETH_CLKOUT_I_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_ETH_CLKOUT_I_s1_from_cpu_0_data_master;
  wire             wait_for_ETH_CLKOUT_I_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~ETH_CLKOUT_I_s1_end_xfer;
    end


  assign ETH_CLKOUT_I_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_ETH_CLKOUT_I_s1));
  //assign ETH_CLKOUT_I_s1_readdata_from_sa = ETH_CLKOUT_I_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign ETH_CLKOUT_I_s1_readdata_from_sa = ETH_CLKOUT_I_s1_readdata;

  assign cpu_0_data_master_requests_ETH_CLKOUT_I_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002250) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //ETH_CLKOUT_I_s1_arb_share_counter set values, which is an e_mux
  assign ETH_CLKOUT_I_s1_arb_share_set_values = 1;

  //ETH_CLKOUT_I_s1_non_bursting_master_requests mux, which is an e_mux
  assign ETH_CLKOUT_I_s1_non_bursting_master_requests = cpu_0_data_master_requests_ETH_CLKOUT_I_s1;

  //ETH_CLKOUT_I_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign ETH_CLKOUT_I_s1_any_bursting_master_saved_grant = 0;

  //ETH_CLKOUT_I_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign ETH_CLKOUT_I_s1_arb_share_counter_next_value = ETH_CLKOUT_I_s1_firsttransfer ? (ETH_CLKOUT_I_s1_arb_share_set_values - 1) : |ETH_CLKOUT_I_s1_arb_share_counter ? (ETH_CLKOUT_I_s1_arb_share_counter - 1) : 0;

  //ETH_CLKOUT_I_s1_allgrants all slave grants, which is an e_mux
  assign ETH_CLKOUT_I_s1_allgrants = |ETH_CLKOUT_I_s1_grant_vector;

  //ETH_CLKOUT_I_s1_end_xfer assignment, which is an e_assign
  assign ETH_CLKOUT_I_s1_end_xfer = ~(ETH_CLKOUT_I_s1_waits_for_read | ETH_CLKOUT_I_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_ETH_CLKOUT_I_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_ETH_CLKOUT_I_s1 = ETH_CLKOUT_I_s1_end_xfer & (~ETH_CLKOUT_I_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //ETH_CLKOUT_I_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign ETH_CLKOUT_I_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_ETH_CLKOUT_I_s1 & ETH_CLKOUT_I_s1_allgrants) | (end_xfer_arb_share_counter_term_ETH_CLKOUT_I_s1 & ~ETH_CLKOUT_I_s1_non_bursting_master_requests);

  //ETH_CLKOUT_I_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_CLKOUT_I_s1_arb_share_counter <= 0;
      else if (ETH_CLKOUT_I_s1_arb_counter_enable)
          ETH_CLKOUT_I_s1_arb_share_counter <= ETH_CLKOUT_I_s1_arb_share_counter_next_value;
    end


  //ETH_CLKOUT_I_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_CLKOUT_I_s1_slavearbiterlockenable <= 0;
      else if ((|ETH_CLKOUT_I_s1_master_qreq_vector & end_xfer_arb_share_counter_term_ETH_CLKOUT_I_s1) | (end_xfer_arb_share_counter_term_ETH_CLKOUT_I_s1 & ~ETH_CLKOUT_I_s1_non_bursting_master_requests))
          ETH_CLKOUT_I_s1_slavearbiterlockenable <= |ETH_CLKOUT_I_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master ETH_CLKOUT_I/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = ETH_CLKOUT_I_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //ETH_CLKOUT_I_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign ETH_CLKOUT_I_s1_slavearbiterlockenable2 = |ETH_CLKOUT_I_s1_arb_share_counter_next_value;

  //cpu_0/data_master ETH_CLKOUT_I/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = ETH_CLKOUT_I_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //ETH_CLKOUT_I_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign ETH_CLKOUT_I_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_ETH_CLKOUT_I_s1 = cpu_0_data_master_requests_ETH_CLKOUT_I_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_ETH_CLKOUT_I_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_ETH_CLKOUT_I_s1 = cpu_0_data_master_granted_ETH_CLKOUT_I_s1 & cpu_0_data_master_read & ~ETH_CLKOUT_I_s1_waits_for_read;

  //ETH_CLKOUT_I_s1_writedata mux, which is an e_mux
  assign ETH_CLKOUT_I_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_ETH_CLKOUT_I_s1 = cpu_0_data_master_qualified_request_ETH_CLKOUT_I_s1;

  //cpu_0/data_master saved-grant ETH_CLKOUT_I/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_ETH_CLKOUT_I_s1 = cpu_0_data_master_requests_ETH_CLKOUT_I_s1;

  //allow new arb cycle for ETH_CLKOUT_I/s1, which is an e_assign
  assign ETH_CLKOUT_I_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign ETH_CLKOUT_I_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign ETH_CLKOUT_I_s1_master_qreq_vector = 1;

  //ETH_CLKOUT_I_s1_reset_n assignment, which is an e_assign
  assign ETH_CLKOUT_I_s1_reset_n = reset_n;

  assign ETH_CLKOUT_I_s1_chipselect = cpu_0_data_master_granted_ETH_CLKOUT_I_s1;
  //ETH_CLKOUT_I_s1_firsttransfer first transaction, which is an e_assign
  assign ETH_CLKOUT_I_s1_firsttransfer = ETH_CLKOUT_I_s1_begins_xfer ? ETH_CLKOUT_I_s1_unreg_firsttransfer : ETH_CLKOUT_I_s1_reg_firsttransfer;

  //ETH_CLKOUT_I_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign ETH_CLKOUT_I_s1_unreg_firsttransfer = ~(ETH_CLKOUT_I_s1_slavearbiterlockenable & ETH_CLKOUT_I_s1_any_continuerequest);

  //ETH_CLKOUT_I_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_CLKOUT_I_s1_reg_firsttransfer <= 1'b1;
      else if (ETH_CLKOUT_I_s1_begins_xfer)
          ETH_CLKOUT_I_s1_reg_firsttransfer <= ETH_CLKOUT_I_s1_unreg_firsttransfer;
    end


  //ETH_CLKOUT_I_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign ETH_CLKOUT_I_s1_beginbursttransfer_internal = ETH_CLKOUT_I_s1_begins_xfer;

  //~ETH_CLKOUT_I_s1_write_n assignment, which is an e_mux
  assign ETH_CLKOUT_I_s1_write_n = ~(cpu_0_data_master_granted_ETH_CLKOUT_I_s1 & cpu_0_data_master_write);

  assign shifted_address_to_ETH_CLKOUT_I_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //ETH_CLKOUT_I_s1_address mux, which is an e_mux
  assign ETH_CLKOUT_I_s1_address = shifted_address_to_ETH_CLKOUT_I_s1_from_cpu_0_data_master >> 2;

  //d1_ETH_CLKOUT_I_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_ETH_CLKOUT_I_s1_end_xfer <= 1;
      else 
        d1_ETH_CLKOUT_I_s1_end_xfer <= ETH_CLKOUT_I_s1_end_xfer;
    end


  //ETH_CLKOUT_I_s1_waits_for_read in a cycle, which is an e_mux
  assign ETH_CLKOUT_I_s1_waits_for_read = ETH_CLKOUT_I_s1_in_a_read_cycle & ETH_CLKOUT_I_s1_begins_xfer;

  //ETH_CLKOUT_I_s1_in_a_read_cycle assignment, which is an e_assign
  assign ETH_CLKOUT_I_s1_in_a_read_cycle = cpu_0_data_master_granted_ETH_CLKOUT_I_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = ETH_CLKOUT_I_s1_in_a_read_cycle;

  //ETH_CLKOUT_I_s1_waits_for_write in a cycle, which is an e_mux
  assign ETH_CLKOUT_I_s1_waits_for_write = ETH_CLKOUT_I_s1_in_a_write_cycle & 0;

  //ETH_CLKOUT_I_s1_in_a_write_cycle assignment, which is an e_assign
  assign ETH_CLKOUT_I_s1_in_a_write_cycle = cpu_0_data_master_granted_ETH_CLKOUT_I_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = ETH_CLKOUT_I_s1_in_a_write_cycle;

  assign wait_for_ETH_CLKOUT_I_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //ETH_CLKOUT_I/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module ETH_CS_O_s1_arbitrator (
                                // inputs:
                                 ETH_CS_O_s1_readdata,
                                 clk,
                                 cpu_0_data_master_address_to_slave,
                                 cpu_0_data_master_latency_counter,
                                 cpu_0_data_master_read,
                                 cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                 cpu_0_data_master_write,
                                 cpu_0_data_master_writedata,
                                 reset_n,

                                // outputs:
                                 ETH_CS_O_s1_address,
                                 ETH_CS_O_s1_chipselect,
                                 ETH_CS_O_s1_readdata_from_sa,
                                 ETH_CS_O_s1_reset_n,
                                 ETH_CS_O_s1_write_n,
                                 ETH_CS_O_s1_writedata,
                                 cpu_0_data_master_granted_ETH_CS_O_s1,
                                 cpu_0_data_master_qualified_request_ETH_CS_O_s1,
                                 cpu_0_data_master_read_data_valid_ETH_CS_O_s1,
                                 cpu_0_data_master_requests_ETH_CS_O_s1,
                                 d1_ETH_CS_O_s1_end_xfer
                              )
;

  output  [  1: 0] ETH_CS_O_s1_address;
  output           ETH_CS_O_s1_chipselect;
  output  [ 31: 0] ETH_CS_O_s1_readdata_from_sa;
  output           ETH_CS_O_s1_reset_n;
  output           ETH_CS_O_s1_write_n;
  output  [ 31: 0] ETH_CS_O_s1_writedata;
  output           cpu_0_data_master_granted_ETH_CS_O_s1;
  output           cpu_0_data_master_qualified_request_ETH_CS_O_s1;
  output           cpu_0_data_master_read_data_valid_ETH_CS_O_s1;
  output           cpu_0_data_master_requests_ETH_CS_O_s1;
  output           d1_ETH_CS_O_s1_end_xfer;
  input   [ 31: 0] ETH_CS_O_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] ETH_CS_O_s1_address;
  wire             ETH_CS_O_s1_allgrants;
  wire             ETH_CS_O_s1_allow_new_arb_cycle;
  wire             ETH_CS_O_s1_any_bursting_master_saved_grant;
  wire             ETH_CS_O_s1_any_continuerequest;
  wire             ETH_CS_O_s1_arb_counter_enable;
  reg     [  1: 0] ETH_CS_O_s1_arb_share_counter;
  wire    [  1: 0] ETH_CS_O_s1_arb_share_counter_next_value;
  wire    [  1: 0] ETH_CS_O_s1_arb_share_set_values;
  wire             ETH_CS_O_s1_beginbursttransfer_internal;
  wire             ETH_CS_O_s1_begins_xfer;
  wire             ETH_CS_O_s1_chipselect;
  wire             ETH_CS_O_s1_end_xfer;
  wire             ETH_CS_O_s1_firsttransfer;
  wire             ETH_CS_O_s1_grant_vector;
  wire             ETH_CS_O_s1_in_a_read_cycle;
  wire             ETH_CS_O_s1_in_a_write_cycle;
  wire             ETH_CS_O_s1_master_qreq_vector;
  wire             ETH_CS_O_s1_non_bursting_master_requests;
  wire    [ 31: 0] ETH_CS_O_s1_readdata_from_sa;
  reg              ETH_CS_O_s1_reg_firsttransfer;
  wire             ETH_CS_O_s1_reset_n;
  reg              ETH_CS_O_s1_slavearbiterlockenable;
  wire             ETH_CS_O_s1_slavearbiterlockenable2;
  wire             ETH_CS_O_s1_unreg_firsttransfer;
  wire             ETH_CS_O_s1_waits_for_read;
  wire             ETH_CS_O_s1_waits_for_write;
  wire             ETH_CS_O_s1_write_n;
  wire    [ 31: 0] ETH_CS_O_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_ETH_CS_O_s1;
  wire             cpu_0_data_master_qualified_request_ETH_CS_O_s1;
  wire             cpu_0_data_master_read_data_valid_ETH_CS_O_s1;
  wire             cpu_0_data_master_requests_ETH_CS_O_s1;
  wire             cpu_0_data_master_saved_grant_ETH_CS_O_s1;
  reg              d1_ETH_CS_O_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_ETH_CS_O_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_ETH_CS_O_s1_from_cpu_0_data_master;
  wire             wait_for_ETH_CS_O_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~ETH_CS_O_s1_end_xfer;
    end


  assign ETH_CS_O_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_ETH_CS_O_s1));
  //assign ETH_CS_O_s1_readdata_from_sa = ETH_CS_O_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign ETH_CS_O_s1_readdata_from_sa = ETH_CS_O_s1_readdata;

  assign cpu_0_data_master_requests_ETH_CS_O_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002270) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //ETH_CS_O_s1_arb_share_counter set values, which is an e_mux
  assign ETH_CS_O_s1_arb_share_set_values = 1;

  //ETH_CS_O_s1_non_bursting_master_requests mux, which is an e_mux
  assign ETH_CS_O_s1_non_bursting_master_requests = cpu_0_data_master_requests_ETH_CS_O_s1;

  //ETH_CS_O_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign ETH_CS_O_s1_any_bursting_master_saved_grant = 0;

  //ETH_CS_O_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign ETH_CS_O_s1_arb_share_counter_next_value = ETH_CS_O_s1_firsttransfer ? (ETH_CS_O_s1_arb_share_set_values - 1) : |ETH_CS_O_s1_arb_share_counter ? (ETH_CS_O_s1_arb_share_counter - 1) : 0;

  //ETH_CS_O_s1_allgrants all slave grants, which is an e_mux
  assign ETH_CS_O_s1_allgrants = |ETH_CS_O_s1_grant_vector;

  //ETH_CS_O_s1_end_xfer assignment, which is an e_assign
  assign ETH_CS_O_s1_end_xfer = ~(ETH_CS_O_s1_waits_for_read | ETH_CS_O_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_ETH_CS_O_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_ETH_CS_O_s1 = ETH_CS_O_s1_end_xfer & (~ETH_CS_O_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //ETH_CS_O_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign ETH_CS_O_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_ETH_CS_O_s1 & ETH_CS_O_s1_allgrants) | (end_xfer_arb_share_counter_term_ETH_CS_O_s1 & ~ETH_CS_O_s1_non_bursting_master_requests);

  //ETH_CS_O_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_CS_O_s1_arb_share_counter <= 0;
      else if (ETH_CS_O_s1_arb_counter_enable)
          ETH_CS_O_s1_arb_share_counter <= ETH_CS_O_s1_arb_share_counter_next_value;
    end


  //ETH_CS_O_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_CS_O_s1_slavearbiterlockenable <= 0;
      else if ((|ETH_CS_O_s1_master_qreq_vector & end_xfer_arb_share_counter_term_ETH_CS_O_s1) | (end_xfer_arb_share_counter_term_ETH_CS_O_s1 & ~ETH_CS_O_s1_non_bursting_master_requests))
          ETH_CS_O_s1_slavearbiterlockenable <= |ETH_CS_O_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master ETH_CS_O/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = ETH_CS_O_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //ETH_CS_O_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign ETH_CS_O_s1_slavearbiterlockenable2 = |ETH_CS_O_s1_arb_share_counter_next_value;

  //cpu_0/data_master ETH_CS_O/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = ETH_CS_O_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //ETH_CS_O_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign ETH_CS_O_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_ETH_CS_O_s1 = cpu_0_data_master_requests_ETH_CS_O_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_ETH_CS_O_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_ETH_CS_O_s1 = cpu_0_data_master_granted_ETH_CS_O_s1 & cpu_0_data_master_read & ~ETH_CS_O_s1_waits_for_read;

  //ETH_CS_O_s1_writedata mux, which is an e_mux
  assign ETH_CS_O_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_ETH_CS_O_s1 = cpu_0_data_master_qualified_request_ETH_CS_O_s1;

  //cpu_0/data_master saved-grant ETH_CS_O/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_ETH_CS_O_s1 = cpu_0_data_master_requests_ETH_CS_O_s1;

  //allow new arb cycle for ETH_CS_O/s1, which is an e_assign
  assign ETH_CS_O_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign ETH_CS_O_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign ETH_CS_O_s1_master_qreq_vector = 1;

  //ETH_CS_O_s1_reset_n assignment, which is an e_assign
  assign ETH_CS_O_s1_reset_n = reset_n;

  assign ETH_CS_O_s1_chipselect = cpu_0_data_master_granted_ETH_CS_O_s1;
  //ETH_CS_O_s1_firsttransfer first transaction, which is an e_assign
  assign ETH_CS_O_s1_firsttransfer = ETH_CS_O_s1_begins_xfer ? ETH_CS_O_s1_unreg_firsttransfer : ETH_CS_O_s1_reg_firsttransfer;

  //ETH_CS_O_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign ETH_CS_O_s1_unreg_firsttransfer = ~(ETH_CS_O_s1_slavearbiterlockenable & ETH_CS_O_s1_any_continuerequest);

  //ETH_CS_O_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_CS_O_s1_reg_firsttransfer <= 1'b1;
      else if (ETH_CS_O_s1_begins_xfer)
          ETH_CS_O_s1_reg_firsttransfer <= ETH_CS_O_s1_unreg_firsttransfer;
    end


  //ETH_CS_O_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign ETH_CS_O_s1_beginbursttransfer_internal = ETH_CS_O_s1_begins_xfer;

  //~ETH_CS_O_s1_write_n assignment, which is an e_mux
  assign ETH_CS_O_s1_write_n = ~(cpu_0_data_master_granted_ETH_CS_O_s1 & cpu_0_data_master_write);

  assign shifted_address_to_ETH_CS_O_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //ETH_CS_O_s1_address mux, which is an e_mux
  assign ETH_CS_O_s1_address = shifted_address_to_ETH_CS_O_s1_from_cpu_0_data_master >> 2;

  //d1_ETH_CS_O_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_ETH_CS_O_s1_end_xfer <= 1;
      else 
        d1_ETH_CS_O_s1_end_xfer <= ETH_CS_O_s1_end_xfer;
    end


  //ETH_CS_O_s1_waits_for_read in a cycle, which is an e_mux
  assign ETH_CS_O_s1_waits_for_read = ETH_CS_O_s1_in_a_read_cycle & ETH_CS_O_s1_begins_xfer;

  //ETH_CS_O_s1_in_a_read_cycle assignment, which is an e_assign
  assign ETH_CS_O_s1_in_a_read_cycle = cpu_0_data_master_granted_ETH_CS_O_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = ETH_CS_O_s1_in_a_read_cycle;

  //ETH_CS_O_s1_waits_for_write in a cycle, which is an e_mux
  assign ETH_CS_O_s1_waits_for_write = ETH_CS_O_s1_in_a_write_cycle & 0;

  //ETH_CS_O_s1_in_a_write_cycle assignment, which is an e_assign
  assign ETH_CS_O_s1_in_a_write_cycle = cpu_0_data_master_granted_ETH_CS_O_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = ETH_CS_O_s1_in_a_write_cycle;

  assign wait_for_ETH_CS_O_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //ETH_CS_O/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module ETH_INT_I_s1_arbitrator (
                                 // inputs:
                                  ETH_INT_I_s1_readdata,
                                  clk,
                                  cpu_0_data_master_address_to_slave,
                                  cpu_0_data_master_latency_counter,
                                  cpu_0_data_master_read,
                                  cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                  cpu_0_data_master_write,
                                  cpu_0_data_master_writedata,
                                  reset_n,

                                 // outputs:
                                  ETH_INT_I_s1_address,
                                  ETH_INT_I_s1_chipselect,
                                  ETH_INT_I_s1_readdata_from_sa,
                                  ETH_INT_I_s1_reset_n,
                                  ETH_INT_I_s1_write_n,
                                  ETH_INT_I_s1_writedata,
                                  cpu_0_data_master_granted_ETH_INT_I_s1,
                                  cpu_0_data_master_qualified_request_ETH_INT_I_s1,
                                  cpu_0_data_master_read_data_valid_ETH_INT_I_s1,
                                  cpu_0_data_master_requests_ETH_INT_I_s1,
                                  d1_ETH_INT_I_s1_end_xfer
                               )
;

  output  [  1: 0] ETH_INT_I_s1_address;
  output           ETH_INT_I_s1_chipselect;
  output  [ 31: 0] ETH_INT_I_s1_readdata_from_sa;
  output           ETH_INT_I_s1_reset_n;
  output           ETH_INT_I_s1_write_n;
  output  [ 31: 0] ETH_INT_I_s1_writedata;
  output           cpu_0_data_master_granted_ETH_INT_I_s1;
  output           cpu_0_data_master_qualified_request_ETH_INT_I_s1;
  output           cpu_0_data_master_read_data_valid_ETH_INT_I_s1;
  output           cpu_0_data_master_requests_ETH_INT_I_s1;
  output           d1_ETH_INT_I_s1_end_xfer;
  input   [ 31: 0] ETH_INT_I_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] ETH_INT_I_s1_address;
  wire             ETH_INT_I_s1_allgrants;
  wire             ETH_INT_I_s1_allow_new_arb_cycle;
  wire             ETH_INT_I_s1_any_bursting_master_saved_grant;
  wire             ETH_INT_I_s1_any_continuerequest;
  wire             ETH_INT_I_s1_arb_counter_enable;
  reg     [  1: 0] ETH_INT_I_s1_arb_share_counter;
  wire    [  1: 0] ETH_INT_I_s1_arb_share_counter_next_value;
  wire    [  1: 0] ETH_INT_I_s1_arb_share_set_values;
  wire             ETH_INT_I_s1_beginbursttransfer_internal;
  wire             ETH_INT_I_s1_begins_xfer;
  wire             ETH_INT_I_s1_chipselect;
  wire             ETH_INT_I_s1_end_xfer;
  wire             ETH_INT_I_s1_firsttransfer;
  wire             ETH_INT_I_s1_grant_vector;
  wire             ETH_INT_I_s1_in_a_read_cycle;
  wire             ETH_INT_I_s1_in_a_write_cycle;
  wire             ETH_INT_I_s1_master_qreq_vector;
  wire             ETH_INT_I_s1_non_bursting_master_requests;
  wire    [ 31: 0] ETH_INT_I_s1_readdata_from_sa;
  reg              ETH_INT_I_s1_reg_firsttransfer;
  wire             ETH_INT_I_s1_reset_n;
  reg              ETH_INT_I_s1_slavearbiterlockenable;
  wire             ETH_INT_I_s1_slavearbiterlockenable2;
  wire             ETH_INT_I_s1_unreg_firsttransfer;
  wire             ETH_INT_I_s1_waits_for_read;
  wire             ETH_INT_I_s1_waits_for_write;
  wire             ETH_INT_I_s1_write_n;
  wire    [ 31: 0] ETH_INT_I_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_ETH_INT_I_s1;
  wire             cpu_0_data_master_qualified_request_ETH_INT_I_s1;
  wire             cpu_0_data_master_read_data_valid_ETH_INT_I_s1;
  wire             cpu_0_data_master_requests_ETH_INT_I_s1;
  wire             cpu_0_data_master_saved_grant_ETH_INT_I_s1;
  reg              d1_ETH_INT_I_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_ETH_INT_I_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_ETH_INT_I_s1_from_cpu_0_data_master;
  wire             wait_for_ETH_INT_I_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~ETH_INT_I_s1_end_xfer;
    end


  assign ETH_INT_I_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_ETH_INT_I_s1));
  //assign ETH_INT_I_s1_readdata_from_sa = ETH_INT_I_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign ETH_INT_I_s1_readdata_from_sa = ETH_INT_I_s1_readdata;

  assign cpu_0_data_master_requests_ETH_INT_I_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002260) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //ETH_INT_I_s1_arb_share_counter set values, which is an e_mux
  assign ETH_INT_I_s1_arb_share_set_values = 1;

  //ETH_INT_I_s1_non_bursting_master_requests mux, which is an e_mux
  assign ETH_INT_I_s1_non_bursting_master_requests = cpu_0_data_master_requests_ETH_INT_I_s1;

  //ETH_INT_I_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign ETH_INT_I_s1_any_bursting_master_saved_grant = 0;

  //ETH_INT_I_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign ETH_INT_I_s1_arb_share_counter_next_value = ETH_INT_I_s1_firsttransfer ? (ETH_INT_I_s1_arb_share_set_values - 1) : |ETH_INT_I_s1_arb_share_counter ? (ETH_INT_I_s1_arb_share_counter - 1) : 0;

  //ETH_INT_I_s1_allgrants all slave grants, which is an e_mux
  assign ETH_INT_I_s1_allgrants = |ETH_INT_I_s1_grant_vector;

  //ETH_INT_I_s1_end_xfer assignment, which is an e_assign
  assign ETH_INT_I_s1_end_xfer = ~(ETH_INT_I_s1_waits_for_read | ETH_INT_I_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_ETH_INT_I_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_ETH_INT_I_s1 = ETH_INT_I_s1_end_xfer & (~ETH_INT_I_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //ETH_INT_I_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign ETH_INT_I_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_ETH_INT_I_s1 & ETH_INT_I_s1_allgrants) | (end_xfer_arb_share_counter_term_ETH_INT_I_s1 & ~ETH_INT_I_s1_non_bursting_master_requests);

  //ETH_INT_I_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_INT_I_s1_arb_share_counter <= 0;
      else if (ETH_INT_I_s1_arb_counter_enable)
          ETH_INT_I_s1_arb_share_counter <= ETH_INT_I_s1_arb_share_counter_next_value;
    end


  //ETH_INT_I_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_INT_I_s1_slavearbiterlockenable <= 0;
      else if ((|ETH_INT_I_s1_master_qreq_vector & end_xfer_arb_share_counter_term_ETH_INT_I_s1) | (end_xfer_arb_share_counter_term_ETH_INT_I_s1 & ~ETH_INT_I_s1_non_bursting_master_requests))
          ETH_INT_I_s1_slavearbiterlockenable <= |ETH_INT_I_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master ETH_INT_I/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = ETH_INT_I_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //ETH_INT_I_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign ETH_INT_I_s1_slavearbiterlockenable2 = |ETH_INT_I_s1_arb_share_counter_next_value;

  //cpu_0/data_master ETH_INT_I/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = ETH_INT_I_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //ETH_INT_I_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign ETH_INT_I_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_ETH_INT_I_s1 = cpu_0_data_master_requests_ETH_INT_I_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_ETH_INT_I_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_ETH_INT_I_s1 = cpu_0_data_master_granted_ETH_INT_I_s1 & cpu_0_data_master_read & ~ETH_INT_I_s1_waits_for_read;

  //ETH_INT_I_s1_writedata mux, which is an e_mux
  assign ETH_INT_I_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_ETH_INT_I_s1 = cpu_0_data_master_qualified_request_ETH_INT_I_s1;

  //cpu_0/data_master saved-grant ETH_INT_I/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_ETH_INT_I_s1 = cpu_0_data_master_requests_ETH_INT_I_s1;

  //allow new arb cycle for ETH_INT_I/s1, which is an e_assign
  assign ETH_INT_I_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign ETH_INT_I_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign ETH_INT_I_s1_master_qreq_vector = 1;

  //ETH_INT_I_s1_reset_n assignment, which is an e_assign
  assign ETH_INT_I_s1_reset_n = reset_n;

  assign ETH_INT_I_s1_chipselect = cpu_0_data_master_granted_ETH_INT_I_s1;
  //ETH_INT_I_s1_firsttransfer first transaction, which is an e_assign
  assign ETH_INT_I_s1_firsttransfer = ETH_INT_I_s1_begins_xfer ? ETH_INT_I_s1_unreg_firsttransfer : ETH_INT_I_s1_reg_firsttransfer;

  //ETH_INT_I_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign ETH_INT_I_s1_unreg_firsttransfer = ~(ETH_INT_I_s1_slavearbiterlockenable & ETH_INT_I_s1_any_continuerequest);

  //ETH_INT_I_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_INT_I_s1_reg_firsttransfer <= 1'b1;
      else if (ETH_INT_I_s1_begins_xfer)
          ETH_INT_I_s1_reg_firsttransfer <= ETH_INT_I_s1_unreg_firsttransfer;
    end


  //ETH_INT_I_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign ETH_INT_I_s1_beginbursttransfer_internal = ETH_INT_I_s1_begins_xfer;

  //~ETH_INT_I_s1_write_n assignment, which is an e_mux
  assign ETH_INT_I_s1_write_n = ~(cpu_0_data_master_granted_ETH_INT_I_s1 & cpu_0_data_master_write);

  assign shifted_address_to_ETH_INT_I_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //ETH_INT_I_s1_address mux, which is an e_mux
  assign ETH_INT_I_s1_address = shifted_address_to_ETH_INT_I_s1_from_cpu_0_data_master >> 2;

  //d1_ETH_INT_I_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_ETH_INT_I_s1_end_xfer <= 1;
      else 
        d1_ETH_INT_I_s1_end_xfer <= ETH_INT_I_s1_end_xfer;
    end


  //ETH_INT_I_s1_waits_for_read in a cycle, which is an e_mux
  assign ETH_INT_I_s1_waits_for_read = ETH_INT_I_s1_in_a_read_cycle & ETH_INT_I_s1_begins_xfer;

  //ETH_INT_I_s1_in_a_read_cycle assignment, which is an e_assign
  assign ETH_INT_I_s1_in_a_read_cycle = cpu_0_data_master_granted_ETH_INT_I_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = ETH_INT_I_s1_in_a_read_cycle;

  //ETH_INT_I_s1_waits_for_write in a cycle, which is an e_mux
  assign ETH_INT_I_s1_waits_for_write = ETH_INT_I_s1_in_a_write_cycle & 0;

  //ETH_INT_I_s1_in_a_write_cycle assignment, which is an e_assign
  assign ETH_INT_I_s1_in_a_write_cycle = cpu_0_data_master_granted_ETH_INT_I_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = ETH_INT_I_s1_in_a_write_cycle;

  assign wait_for_ETH_INT_I_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //ETH_INT_I/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module ETH_RESET_O_s1_arbitrator (
                                   // inputs:
                                    ETH_RESET_O_s1_readdata,
                                    clk,
                                    cpu_0_data_master_address_to_slave,
                                    cpu_0_data_master_latency_counter,
                                    cpu_0_data_master_read,
                                    cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                    cpu_0_data_master_write,
                                    cpu_0_data_master_writedata,
                                    reset_n,

                                   // outputs:
                                    ETH_RESET_O_s1_address,
                                    ETH_RESET_O_s1_chipselect,
                                    ETH_RESET_O_s1_readdata_from_sa,
                                    ETH_RESET_O_s1_reset_n,
                                    ETH_RESET_O_s1_write_n,
                                    ETH_RESET_O_s1_writedata,
                                    cpu_0_data_master_granted_ETH_RESET_O_s1,
                                    cpu_0_data_master_qualified_request_ETH_RESET_O_s1,
                                    cpu_0_data_master_read_data_valid_ETH_RESET_O_s1,
                                    cpu_0_data_master_requests_ETH_RESET_O_s1,
                                    d1_ETH_RESET_O_s1_end_xfer
                                 )
;

  output  [  1: 0] ETH_RESET_O_s1_address;
  output           ETH_RESET_O_s1_chipselect;
  output  [ 31: 0] ETH_RESET_O_s1_readdata_from_sa;
  output           ETH_RESET_O_s1_reset_n;
  output           ETH_RESET_O_s1_write_n;
  output  [ 31: 0] ETH_RESET_O_s1_writedata;
  output           cpu_0_data_master_granted_ETH_RESET_O_s1;
  output           cpu_0_data_master_qualified_request_ETH_RESET_O_s1;
  output           cpu_0_data_master_read_data_valid_ETH_RESET_O_s1;
  output           cpu_0_data_master_requests_ETH_RESET_O_s1;
  output           d1_ETH_RESET_O_s1_end_xfer;
  input   [ 31: 0] ETH_RESET_O_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] ETH_RESET_O_s1_address;
  wire             ETH_RESET_O_s1_allgrants;
  wire             ETH_RESET_O_s1_allow_new_arb_cycle;
  wire             ETH_RESET_O_s1_any_bursting_master_saved_grant;
  wire             ETH_RESET_O_s1_any_continuerequest;
  wire             ETH_RESET_O_s1_arb_counter_enable;
  reg     [  1: 0] ETH_RESET_O_s1_arb_share_counter;
  wire    [  1: 0] ETH_RESET_O_s1_arb_share_counter_next_value;
  wire    [  1: 0] ETH_RESET_O_s1_arb_share_set_values;
  wire             ETH_RESET_O_s1_beginbursttransfer_internal;
  wire             ETH_RESET_O_s1_begins_xfer;
  wire             ETH_RESET_O_s1_chipselect;
  wire             ETH_RESET_O_s1_end_xfer;
  wire             ETH_RESET_O_s1_firsttransfer;
  wire             ETH_RESET_O_s1_grant_vector;
  wire             ETH_RESET_O_s1_in_a_read_cycle;
  wire             ETH_RESET_O_s1_in_a_write_cycle;
  wire             ETH_RESET_O_s1_master_qreq_vector;
  wire             ETH_RESET_O_s1_non_bursting_master_requests;
  wire    [ 31: 0] ETH_RESET_O_s1_readdata_from_sa;
  reg              ETH_RESET_O_s1_reg_firsttransfer;
  wire             ETH_RESET_O_s1_reset_n;
  reg              ETH_RESET_O_s1_slavearbiterlockenable;
  wire             ETH_RESET_O_s1_slavearbiterlockenable2;
  wire             ETH_RESET_O_s1_unreg_firsttransfer;
  wire             ETH_RESET_O_s1_waits_for_read;
  wire             ETH_RESET_O_s1_waits_for_write;
  wire             ETH_RESET_O_s1_write_n;
  wire    [ 31: 0] ETH_RESET_O_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_ETH_RESET_O_s1;
  wire             cpu_0_data_master_qualified_request_ETH_RESET_O_s1;
  wire             cpu_0_data_master_read_data_valid_ETH_RESET_O_s1;
  wire             cpu_0_data_master_requests_ETH_RESET_O_s1;
  wire             cpu_0_data_master_saved_grant_ETH_RESET_O_s1;
  reg              d1_ETH_RESET_O_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_ETH_RESET_O_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_ETH_RESET_O_s1_from_cpu_0_data_master;
  wire             wait_for_ETH_RESET_O_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~ETH_RESET_O_s1_end_xfer;
    end


  assign ETH_RESET_O_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_ETH_RESET_O_s1));
  //assign ETH_RESET_O_s1_readdata_from_sa = ETH_RESET_O_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign ETH_RESET_O_s1_readdata_from_sa = ETH_RESET_O_s1_readdata;

  assign cpu_0_data_master_requests_ETH_RESET_O_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002210) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //ETH_RESET_O_s1_arb_share_counter set values, which is an e_mux
  assign ETH_RESET_O_s1_arb_share_set_values = 1;

  //ETH_RESET_O_s1_non_bursting_master_requests mux, which is an e_mux
  assign ETH_RESET_O_s1_non_bursting_master_requests = cpu_0_data_master_requests_ETH_RESET_O_s1;

  //ETH_RESET_O_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign ETH_RESET_O_s1_any_bursting_master_saved_grant = 0;

  //ETH_RESET_O_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign ETH_RESET_O_s1_arb_share_counter_next_value = ETH_RESET_O_s1_firsttransfer ? (ETH_RESET_O_s1_arb_share_set_values - 1) : |ETH_RESET_O_s1_arb_share_counter ? (ETH_RESET_O_s1_arb_share_counter - 1) : 0;

  //ETH_RESET_O_s1_allgrants all slave grants, which is an e_mux
  assign ETH_RESET_O_s1_allgrants = |ETH_RESET_O_s1_grant_vector;

  //ETH_RESET_O_s1_end_xfer assignment, which is an e_assign
  assign ETH_RESET_O_s1_end_xfer = ~(ETH_RESET_O_s1_waits_for_read | ETH_RESET_O_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_ETH_RESET_O_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_ETH_RESET_O_s1 = ETH_RESET_O_s1_end_xfer & (~ETH_RESET_O_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //ETH_RESET_O_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign ETH_RESET_O_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_ETH_RESET_O_s1 & ETH_RESET_O_s1_allgrants) | (end_xfer_arb_share_counter_term_ETH_RESET_O_s1 & ~ETH_RESET_O_s1_non_bursting_master_requests);

  //ETH_RESET_O_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_RESET_O_s1_arb_share_counter <= 0;
      else if (ETH_RESET_O_s1_arb_counter_enable)
          ETH_RESET_O_s1_arb_share_counter <= ETH_RESET_O_s1_arb_share_counter_next_value;
    end


  //ETH_RESET_O_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_RESET_O_s1_slavearbiterlockenable <= 0;
      else if ((|ETH_RESET_O_s1_master_qreq_vector & end_xfer_arb_share_counter_term_ETH_RESET_O_s1) | (end_xfer_arb_share_counter_term_ETH_RESET_O_s1 & ~ETH_RESET_O_s1_non_bursting_master_requests))
          ETH_RESET_O_s1_slavearbiterlockenable <= |ETH_RESET_O_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master ETH_RESET_O/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = ETH_RESET_O_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //ETH_RESET_O_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign ETH_RESET_O_s1_slavearbiterlockenable2 = |ETH_RESET_O_s1_arb_share_counter_next_value;

  //cpu_0/data_master ETH_RESET_O/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = ETH_RESET_O_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //ETH_RESET_O_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign ETH_RESET_O_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_ETH_RESET_O_s1 = cpu_0_data_master_requests_ETH_RESET_O_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_ETH_RESET_O_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_ETH_RESET_O_s1 = cpu_0_data_master_granted_ETH_RESET_O_s1 & cpu_0_data_master_read & ~ETH_RESET_O_s1_waits_for_read;

  //ETH_RESET_O_s1_writedata mux, which is an e_mux
  assign ETH_RESET_O_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_ETH_RESET_O_s1 = cpu_0_data_master_qualified_request_ETH_RESET_O_s1;

  //cpu_0/data_master saved-grant ETH_RESET_O/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_ETH_RESET_O_s1 = cpu_0_data_master_requests_ETH_RESET_O_s1;

  //allow new arb cycle for ETH_RESET_O/s1, which is an e_assign
  assign ETH_RESET_O_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign ETH_RESET_O_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign ETH_RESET_O_s1_master_qreq_vector = 1;

  //ETH_RESET_O_s1_reset_n assignment, which is an e_assign
  assign ETH_RESET_O_s1_reset_n = reset_n;

  assign ETH_RESET_O_s1_chipselect = cpu_0_data_master_granted_ETH_RESET_O_s1;
  //ETH_RESET_O_s1_firsttransfer first transaction, which is an e_assign
  assign ETH_RESET_O_s1_firsttransfer = ETH_RESET_O_s1_begins_xfer ? ETH_RESET_O_s1_unreg_firsttransfer : ETH_RESET_O_s1_reg_firsttransfer;

  //ETH_RESET_O_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign ETH_RESET_O_s1_unreg_firsttransfer = ~(ETH_RESET_O_s1_slavearbiterlockenable & ETH_RESET_O_s1_any_continuerequest);

  //ETH_RESET_O_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_RESET_O_s1_reg_firsttransfer <= 1'b1;
      else if (ETH_RESET_O_s1_begins_xfer)
          ETH_RESET_O_s1_reg_firsttransfer <= ETH_RESET_O_s1_unreg_firsttransfer;
    end


  //ETH_RESET_O_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign ETH_RESET_O_s1_beginbursttransfer_internal = ETH_RESET_O_s1_begins_xfer;

  //~ETH_RESET_O_s1_write_n assignment, which is an e_mux
  assign ETH_RESET_O_s1_write_n = ~(cpu_0_data_master_granted_ETH_RESET_O_s1 & cpu_0_data_master_write);

  assign shifted_address_to_ETH_RESET_O_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //ETH_RESET_O_s1_address mux, which is an e_mux
  assign ETH_RESET_O_s1_address = shifted_address_to_ETH_RESET_O_s1_from_cpu_0_data_master >> 2;

  //d1_ETH_RESET_O_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_ETH_RESET_O_s1_end_xfer <= 1;
      else 
        d1_ETH_RESET_O_s1_end_xfer <= ETH_RESET_O_s1_end_xfer;
    end


  //ETH_RESET_O_s1_waits_for_read in a cycle, which is an e_mux
  assign ETH_RESET_O_s1_waits_for_read = ETH_RESET_O_s1_in_a_read_cycle & ETH_RESET_O_s1_begins_xfer;

  //ETH_RESET_O_s1_in_a_read_cycle assignment, which is an e_assign
  assign ETH_RESET_O_s1_in_a_read_cycle = cpu_0_data_master_granted_ETH_RESET_O_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = ETH_RESET_O_s1_in_a_read_cycle;

  //ETH_RESET_O_s1_waits_for_write in a cycle, which is an e_mux
  assign ETH_RESET_O_s1_waits_for_write = ETH_RESET_O_s1_in_a_write_cycle & 0;

  //ETH_RESET_O_s1_in_a_write_cycle assignment, which is an e_assign
  assign ETH_RESET_O_s1_in_a_write_cycle = cpu_0_data_master_granted_ETH_RESET_O_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = ETH_RESET_O_s1_in_a_write_cycle;

  assign wait_for_ETH_RESET_O_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //ETH_RESET_O/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module ETH_SCK_O_s1_arbitrator (
                                 // inputs:
                                  ETH_SCK_O_s1_readdata,
                                  clk,
                                  cpu_0_data_master_address_to_slave,
                                  cpu_0_data_master_latency_counter,
                                  cpu_0_data_master_read,
                                  cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                  cpu_0_data_master_write,
                                  cpu_0_data_master_writedata,
                                  reset_n,

                                 // outputs:
                                  ETH_SCK_O_s1_address,
                                  ETH_SCK_O_s1_chipselect,
                                  ETH_SCK_O_s1_readdata_from_sa,
                                  ETH_SCK_O_s1_reset_n,
                                  ETH_SCK_O_s1_write_n,
                                  ETH_SCK_O_s1_writedata,
                                  cpu_0_data_master_granted_ETH_SCK_O_s1,
                                  cpu_0_data_master_qualified_request_ETH_SCK_O_s1,
                                  cpu_0_data_master_read_data_valid_ETH_SCK_O_s1,
                                  cpu_0_data_master_requests_ETH_SCK_O_s1,
                                  d1_ETH_SCK_O_s1_end_xfer
                               )
;

  output  [  1: 0] ETH_SCK_O_s1_address;
  output           ETH_SCK_O_s1_chipselect;
  output  [ 31: 0] ETH_SCK_O_s1_readdata_from_sa;
  output           ETH_SCK_O_s1_reset_n;
  output           ETH_SCK_O_s1_write_n;
  output  [ 31: 0] ETH_SCK_O_s1_writedata;
  output           cpu_0_data_master_granted_ETH_SCK_O_s1;
  output           cpu_0_data_master_qualified_request_ETH_SCK_O_s1;
  output           cpu_0_data_master_read_data_valid_ETH_SCK_O_s1;
  output           cpu_0_data_master_requests_ETH_SCK_O_s1;
  output           d1_ETH_SCK_O_s1_end_xfer;
  input   [ 31: 0] ETH_SCK_O_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] ETH_SCK_O_s1_address;
  wire             ETH_SCK_O_s1_allgrants;
  wire             ETH_SCK_O_s1_allow_new_arb_cycle;
  wire             ETH_SCK_O_s1_any_bursting_master_saved_grant;
  wire             ETH_SCK_O_s1_any_continuerequest;
  wire             ETH_SCK_O_s1_arb_counter_enable;
  reg     [  1: 0] ETH_SCK_O_s1_arb_share_counter;
  wire    [  1: 0] ETH_SCK_O_s1_arb_share_counter_next_value;
  wire    [  1: 0] ETH_SCK_O_s1_arb_share_set_values;
  wire             ETH_SCK_O_s1_beginbursttransfer_internal;
  wire             ETH_SCK_O_s1_begins_xfer;
  wire             ETH_SCK_O_s1_chipselect;
  wire             ETH_SCK_O_s1_end_xfer;
  wire             ETH_SCK_O_s1_firsttransfer;
  wire             ETH_SCK_O_s1_grant_vector;
  wire             ETH_SCK_O_s1_in_a_read_cycle;
  wire             ETH_SCK_O_s1_in_a_write_cycle;
  wire             ETH_SCK_O_s1_master_qreq_vector;
  wire             ETH_SCK_O_s1_non_bursting_master_requests;
  wire    [ 31: 0] ETH_SCK_O_s1_readdata_from_sa;
  reg              ETH_SCK_O_s1_reg_firsttransfer;
  wire             ETH_SCK_O_s1_reset_n;
  reg              ETH_SCK_O_s1_slavearbiterlockenable;
  wire             ETH_SCK_O_s1_slavearbiterlockenable2;
  wire             ETH_SCK_O_s1_unreg_firsttransfer;
  wire             ETH_SCK_O_s1_waits_for_read;
  wire             ETH_SCK_O_s1_waits_for_write;
  wire             ETH_SCK_O_s1_write_n;
  wire    [ 31: 0] ETH_SCK_O_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_ETH_SCK_O_s1;
  wire             cpu_0_data_master_qualified_request_ETH_SCK_O_s1;
  wire             cpu_0_data_master_read_data_valid_ETH_SCK_O_s1;
  wire             cpu_0_data_master_requests_ETH_SCK_O_s1;
  wire             cpu_0_data_master_saved_grant_ETH_SCK_O_s1;
  reg              d1_ETH_SCK_O_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_ETH_SCK_O_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_ETH_SCK_O_s1_from_cpu_0_data_master;
  wire             wait_for_ETH_SCK_O_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~ETH_SCK_O_s1_end_xfer;
    end


  assign ETH_SCK_O_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_ETH_SCK_O_s1));
  //assign ETH_SCK_O_s1_readdata_from_sa = ETH_SCK_O_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign ETH_SCK_O_s1_readdata_from_sa = ETH_SCK_O_s1_readdata;

  assign cpu_0_data_master_requests_ETH_SCK_O_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002220) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //ETH_SCK_O_s1_arb_share_counter set values, which is an e_mux
  assign ETH_SCK_O_s1_arb_share_set_values = 1;

  //ETH_SCK_O_s1_non_bursting_master_requests mux, which is an e_mux
  assign ETH_SCK_O_s1_non_bursting_master_requests = cpu_0_data_master_requests_ETH_SCK_O_s1;

  //ETH_SCK_O_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign ETH_SCK_O_s1_any_bursting_master_saved_grant = 0;

  //ETH_SCK_O_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign ETH_SCK_O_s1_arb_share_counter_next_value = ETH_SCK_O_s1_firsttransfer ? (ETH_SCK_O_s1_arb_share_set_values - 1) : |ETH_SCK_O_s1_arb_share_counter ? (ETH_SCK_O_s1_arb_share_counter - 1) : 0;

  //ETH_SCK_O_s1_allgrants all slave grants, which is an e_mux
  assign ETH_SCK_O_s1_allgrants = |ETH_SCK_O_s1_grant_vector;

  //ETH_SCK_O_s1_end_xfer assignment, which is an e_assign
  assign ETH_SCK_O_s1_end_xfer = ~(ETH_SCK_O_s1_waits_for_read | ETH_SCK_O_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_ETH_SCK_O_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_ETH_SCK_O_s1 = ETH_SCK_O_s1_end_xfer & (~ETH_SCK_O_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //ETH_SCK_O_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign ETH_SCK_O_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_ETH_SCK_O_s1 & ETH_SCK_O_s1_allgrants) | (end_xfer_arb_share_counter_term_ETH_SCK_O_s1 & ~ETH_SCK_O_s1_non_bursting_master_requests);

  //ETH_SCK_O_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_SCK_O_s1_arb_share_counter <= 0;
      else if (ETH_SCK_O_s1_arb_counter_enable)
          ETH_SCK_O_s1_arb_share_counter <= ETH_SCK_O_s1_arb_share_counter_next_value;
    end


  //ETH_SCK_O_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_SCK_O_s1_slavearbiterlockenable <= 0;
      else if ((|ETH_SCK_O_s1_master_qreq_vector & end_xfer_arb_share_counter_term_ETH_SCK_O_s1) | (end_xfer_arb_share_counter_term_ETH_SCK_O_s1 & ~ETH_SCK_O_s1_non_bursting_master_requests))
          ETH_SCK_O_s1_slavearbiterlockenable <= |ETH_SCK_O_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master ETH_SCK_O/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = ETH_SCK_O_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //ETH_SCK_O_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign ETH_SCK_O_s1_slavearbiterlockenable2 = |ETH_SCK_O_s1_arb_share_counter_next_value;

  //cpu_0/data_master ETH_SCK_O/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = ETH_SCK_O_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //ETH_SCK_O_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign ETH_SCK_O_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_ETH_SCK_O_s1 = cpu_0_data_master_requests_ETH_SCK_O_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_ETH_SCK_O_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_ETH_SCK_O_s1 = cpu_0_data_master_granted_ETH_SCK_O_s1 & cpu_0_data_master_read & ~ETH_SCK_O_s1_waits_for_read;

  //ETH_SCK_O_s1_writedata mux, which is an e_mux
  assign ETH_SCK_O_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_ETH_SCK_O_s1 = cpu_0_data_master_qualified_request_ETH_SCK_O_s1;

  //cpu_0/data_master saved-grant ETH_SCK_O/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_ETH_SCK_O_s1 = cpu_0_data_master_requests_ETH_SCK_O_s1;

  //allow new arb cycle for ETH_SCK_O/s1, which is an e_assign
  assign ETH_SCK_O_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign ETH_SCK_O_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign ETH_SCK_O_s1_master_qreq_vector = 1;

  //ETH_SCK_O_s1_reset_n assignment, which is an e_assign
  assign ETH_SCK_O_s1_reset_n = reset_n;

  assign ETH_SCK_O_s1_chipselect = cpu_0_data_master_granted_ETH_SCK_O_s1;
  //ETH_SCK_O_s1_firsttransfer first transaction, which is an e_assign
  assign ETH_SCK_O_s1_firsttransfer = ETH_SCK_O_s1_begins_xfer ? ETH_SCK_O_s1_unreg_firsttransfer : ETH_SCK_O_s1_reg_firsttransfer;

  //ETH_SCK_O_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign ETH_SCK_O_s1_unreg_firsttransfer = ~(ETH_SCK_O_s1_slavearbiterlockenable & ETH_SCK_O_s1_any_continuerequest);

  //ETH_SCK_O_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_SCK_O_s1_reg_firsttransfer <= 1'b1;
      else if (ETH_SCK_O_s1_begins_xfer)
          ETH_SCK_O_s1_reg_firsttransfer <= ETH_SCK_O_s1_unreg_firsttransfer;
    end


  //ETH_SCK_O_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign ETH_SCK_O_s1_beginbursttransfer_internal = ETH_SCK_O_s1_begins_xfer;

  //~ETH_SCK_O_s1_write_n assignment, which is an e_mux
  assign ETH_SCK_O_s1_write_n = ~(cpu_0_data_master_granted_ETH_SCK_O_s1 & cpu_0_data_master_write);

  assign shifted_address_to_ETH_SCK_O_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //ETH_SCK_O_s1_address mux, which is an e_mux
  assign ETH_SCK_O_s1_address = shifted_address_to_ETH_SCK_O_s1_from_cpu_0_data_master >> 2;

  //d1_ETH_SCK_O_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_ETH_SCK_O_s1_end_xfer <= 1;
      else 
        d1_ETH_SCK_O_s1_end_xfer <= ETH_SCK_O_s1_end_xfer;
    end


  //ETH_SCK_O_s1_waits_for_read in a cycle, which is an e_mux
  assign ETH_SCK_O_s1_waits_for_read = ETH_SCK_O_s1_in_a_read_cycle & ETH_SCK_O_s1_begins_xfer;

  //ETH_SCK_O_s1_in_a_read_cycle assignment, which is an e_assign
  assign ETH_SCK_O_s1_in_a_read_cycle = cpu_0_data_master_granted_ETH_SCK_O_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = ETH_SCK_O_s1_in_a_read_cycle;

  //ETH_SCK_O_s1_waits_for_write in a cycle, which is an e_mux
  assign ETH_SCK_O_s1_waits_for_write = ETH_SCK_O_s1_in_a_write_cycle & 0;

  //ETH_SCK_O_s1_in_a_write_cycle assignment, which is an e_assign
  assign ETH_SCK_O_s1_in_a_write_cycle = cpu_0_data_master_granted_ETH_SCK_O_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = ETH_SCK_O_s1_in_a_write_cycle;

  assign wait_for_ETH_SCK_O_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //ETH_SCK_O/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module ETH_SI_O_s1_arbitrator (
                                // inputs:
                                 ETH_SI_O_s1_readdata,
                                 clk,
                                 cpu_0_data_master_address_to_slave,
                                 cpu_0_data_master_latency_counter,
                                 cpu_0_data_master_read,
                                 cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                 cpu_0_data_master_write,
                                 cpu_0_data_master_writedata,
                                 reset_n,

                                // outputs:
                                 ETH_SI_O_s1_address,
                                 ETH_SI_O_s1_chipselect,
                                 ETH_SI_O_s1_readdata_from_sa,
                                 ETH_SI_O_s1_reset_n,
                                 ETH_SI_O_s1_write_n,
                                 ETH_SI_O_s1_writedata,
                                 cpu_0_data_master_granted_ETH_SI_O_s1,
                                 cpu_0_data_master_qualified_request_ETH_SI_O_s1,
                                 cpu_0_data_master_read_data_valid_ETH_SI_O_s1,
                                 cpu_0_data_master_requests_ETH_SI_O_s1,
                                 d1_ETH_SI_O_s1_end_xfer
                              )
;

  output  [  1: 0] ETH_SI_O_s1_address;
  output           ETH_SI_O_s1_chipselect;
  output  [ 31: 0] ETH_SI_O_s1_readdata_from_sa;
  output           ETH_SI_O_s1_reset_n;
  output           ETH_SI_O_s1_write_n;
  output  [ 31: 0] ETH_SI_O_s1_writedata;
  output           cpu_0_data_master_granted_ETH_SI_O_s1;
  output           cpu_0_data_master_qualified_request_ETH_SI_O_s1;
  output           cpu_0_data_master_read_data_valid_ETH_SI_O_s1;
  output           cpu_0_data_master_requests_ETH_SI_O_s1;
  output           d1_ETH_SI_O_s1_end_xfer;
  input   [ 31: 0] ETH_SI_O_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] ETH_SI_O_s1_address;
  wire             ETH_SI_O_s1_allgrants;
  wire             ETH_SI_O_s1_allow_new_arb_cycle;
  wire             ETH_SI_O_s1_any_bursting_master_saved_grant;
  wire             ETH_SI_O_s1_any_continuerequest;
  wire             ETH_SI_O_s1_arb_counter_enable;
  reg     [  1: 0] ETH_SI_O_s1_arb_share_counter;
  wire    [  1: 0] ETH_SI_O_s1_arb_share_counter_next_value;
  wire    [  1: 0] ETH_SI_O_s1_arb_share_set_values;
  wire             ETH_SI_O_s1_beginbursttransfer_internal;
  wire             ETH_SI_O_s1_begins_xfer;
  wire             ETH_SI_O_s1_chipselect;
  wire             ETH_SI_O_s1_end_xfer;
  wire             ETH_SI_O_s1_firsttransfer;
  wire             ETH_SI_O_s1_grant_vector;
  wire             ETH_SI_O_s1_in_a_read_cycle;
  wire             ETH_SI_O_s1_in_a_write_cycle;
  wire             ETH_SI_O_s1_master_qreq_vector;
  wire             ETH_SI_O_s1_non_bursting_master_requests;
  wire    [ 31: 0] ETH_SI_O_s1_readdata_from_sa;
  reg              ETH_SI_O_s1_reg_firsttransfer;
  wire             ETH_SI_O_s1_reset_n;
  reg              ETH_SI_O_s1_slavearbiterlockenable;
  wire             ETH_SI_O_s1_slavearbiterlockenable2;
  wire             ETH_SI_O_s1_unreg_firsttransfer;
  wire             ETH_SI_O_s1_waits_for_read;
  wire             ETH_SI_O_s1_waits_for_write;
  wire             ETH_SI_O_s1_write_n;
  wire    [ 31: 0] ETH_SI_O_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_ETH_SI_O_s1;
  wire             cpu_0_data_master_qualified_request_ETH_SI_O_s1;
  wire             cpu_0_data_master_read_data_valid_ETH_SI_O_s1;
  wire             cpu_0_data_master_requests_ETH_SI_O_s1;
  wire             cpu_0_data_master_saved_grant_ETH_SI_O_s1;
  reg              d1_ETH_SI_O_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_ETH_SI_O_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_ETH_SI_O_s1_from_cpu_0_data_master;
  wire             wait_for_ETH_SI_O_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~ETH_SI_O_s1_end_xfer;
    end


  assign ETH_SI_O_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_ETH_SI_O_s1));
  //assign ETH_SI_O_s1_readdata_from_sa = ETH_SI_O_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign ETH_SI_O_s1_readdata_from_sa = ETH_SI_O_s1_readdata;

  assign cpu_0_data_master_requests_ETH_SI_O_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002230) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //ETH_SI_O_s1_arb_share_counter set values, which is an e_mux
  assign ETH_SI_O_s1_arb_share_set_values = 1;

  //ETH_SI_O_s1_non_bursting_master_requests mux, which is an e_mux
  assign ETH_SI_O_s1_non_bursting_master_requests = cpu_0_data_master_requests_ETH_SI_O_s1;

  //ETH_SI_O_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign ETH_SI_O_s1_any_bursting_master_saved_grant = 0;

  //ETH_SI_O_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign ETH_SI_O_s1_arb_share_counter_next_value = ETH_SI_O_s1_firsttransfer ? (ETH_SI_O_s1_arb_share_set_values - 1) : |ETH_SI_O_s1_arb_share_counter ? (ETH_SI_O_s1_arb_share_counter - 1) : 0;

  //ETH_SI_O_s1_allgrants all slave grants, which is an e_mux
  assign ETH_SI_O_s1_allgrants = |ETH_SI_O_s1_grant_vector;

  //ETH_SI_O_s1_end_xfer assignment, which is an e_assign
  assign ETH_SI_O_s1_end_xfer = ~(ETH_SI_O_s1_waits_for_read | ETH_SI_O_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_ETH_SI_O_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_ETH_SI_O_s1 = ETH_SI_O_s1_end_xfer & (~ETH_SI_O_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //ETH_SI_O_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign ETH_SI_O_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_ETH_SI_O_s1 & ETH_SI_O_s1_allgrants) | (end_xfer_arb_share_counter_term_ETH_SI_O_s1 & ~ETH_SI_O_s1_non_bursting_master_requests);

  //ETH_SI_O_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_SI_O_s1_arb_share_counter <= 0;
      else if (ETH_SI_O_s1_arb_counter_enable)
          ETH_SI_O_s1_arb_share_counter <= ETH_SI_O_s1_arb_share_counter_next_value;
    end


  //ETH_SI_O_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_SI_O_s1_slavearbiterlockenable <= 0;
      else if ((|ETH_SI_O_s1_master_qreq_vector & end_xfer_arb_share_counter_term_ETH_SI_O_s1) | (end_xfer_arb_share_counter_term_ETH_SI_O_s1 & ~ETH_SI_O_s1_non_bursting_master_requests))
          ETH_SI_O_s1_slavearbiterlockenable <= |ETH_SI_O_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master ETH_SI_O/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = ETH_SI_O_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //ETH_SI_O_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign ETH_SI_O_s1_slavearbiterlockenable2 = |ETH_SI_O_s1_arb_share_counter_next_value;

  //cpu_0/data_master ETH_SI_O/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = ETH_SI_O_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //ETH_SI_O_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign ETH_SI_O_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_ETH_SI_O_s1 = cpu_0_data_master_requests_ETH_SI_O_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_ETH_SI_O_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_ETH_SI_O_s1 = cpu_0_data_master_granted_ETH_SI_O_s1 & cpu_0_data_master_read & ~ETH_SI_O_s1_waits_for_read;

  //ETH_SI_O_s1_writedata mux, which is an e_mux
  assign ETH_SI_O_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_ETH_SI_O_s1 = cpu_0_data_master_qualified_request_ETH_SI_O_s1;

  //cpu_0/data_master saved-grant ETH_SI_O/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_ETH_SI_O_s1 = cpu_0_data_master_requests_ETH_SI_O_s1;

  //allow new arb cycle for ETH_SI_O/s1, which is an e_assign
  assign ETH_SI_O_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign ETH_SI_O_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign ETH_SI_O_s1_master_qreq_vector = 1;

  //ETH_SI_O_s1_reset_n assignment, which is an e_assign
  assign ETH_SI_O_s1_reset_n = reset_n;

  assign ETH_SI_O_s1_chipselect = cpu_0_data_master_granted_ETH_SI_O_s1;
  //ETH_SI_O_s1_firsttransfer first transaction, which is an e_assign
  assign ETH_SI_O_s1_firsttransfer = ETH_SI_O_s1_begins_xfer ? ETH_SI_O_s1_unreg_firsttransfer : ETH_SI_O_s1_reg_firsttransfer;

  //ETH_SI_O_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign ETH_SI_O_s1_unreg_firsttransfer = ~(ETH_SI_O_s1_slavearbiterlockenable & ETH_SI_O_s1_any_continuerequest);

  //ETH_SI_O_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_SI_O_s1_reg_firsttransfer <= 1'b1;
      else if (ETH_SI_O_s1_begins_xfer)
          ETH_SI_O_s1_reg_firsttransfer <= ETH_SI_O_s1_unreg_firsttransfer;
    end


  //ETH_SI_O_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign ETH_SI_O_s1_beginbursttransfer_internal = ETH_SI_O_s1_begins_xfer;

  //~ETH_SI_O_s1_write_n assignment, which is an e_mux
  assign ETH_SI_O_s1_write_n = ~(cpu_0_data_master_granted_ETH_SI_O_s1 & cpu_0_data_master_write);

  assign shifted_address_to_ETH_SI_O_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //ETH_SI_O_s1_address mux, which is an e_mux
  assign ETH_SI_O_s1_address = shifted_address_to_ETH_SI_O_s1_from_cpu_0_data_master >> 2;

  //d1_ETH_SI_O_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_ETH_SI_O_s1_end_xfer <= 1;
      else 
        d1_ETH_SI_O_s1_end_xfer <= ETH_SI_O_s1_end_xfer;
    end


  //ETH_SI_O_s1_waits_for_read in a cycle, which is an e_mux
  assign ETH_SI_O_s1_waits_for_read = ETH_SI_O_s1_in_a_read_cycle & ETH_SI_O_s1_begins_xfer;

  //ETH_SI_O_s1_in_a_read_cycle assignment, which is an e_assign
  assign ETH_SI_O_s1_in_a_read_cycle = cpu_0_data_master_granted_ETH_SI_O_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = ETH_SI_O_s1_in_a_read_cycle;

  //ETH_SI_O_s1_waits_for_write in a cycle, which is an e_mux
  assign ETH_SI_O_s1_waits_for_write = ETH_SI_O_s1_in_a_write_cycle & 0;

  //ETH_SI_O_s1_in_a_write_cycle assignment, which is an e_assign
  assign ETH_SI_O_s1_in_a_write_cycle = cpu_0_data_master_granted_ETH_SI_O_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = ETH_SI_O_s1_in_a_write_cycle;

  assign wait_for_ETH_SI_O_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //ETH_SI_O/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module ETH_SO_I_s1_arbitrator (
                                // inputs:
                                 ETH_SO_I_s1_readdata,
                                 clk,
                                 cpu_0_data_master_address_to_slave,
                                 cpu_0_data_master_latency_counter,
                                 cpu_0_data_master_read,
                                 cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                 cpu_0_data_master_write,
                                 cpu_0_data_master_writedata,
                                 reset_n,

                                // outputs:
                                 ETH_SO_I_s1_address,
                                 ETH_SO_I_s1_chipselect,
                                 ETH_SO_I_s1_readdata_from_sa,
                                 ETH_SO_I_s1_reset_n,
                                 ETH_SO_I_s1_write_n,
                                 ETH_SO_I_s1_writedata,
                                 cpu_0_data_master_granted_ETH_SO_I_s1,
                                 cpu_0_data_master_qualified_request_ETH_SO_I_s1,
                                 cpu_0_data_master_read_data_valid_ETH_SO_I_s1,
                                 cpu_0_data_master_requests_ETH_SO_I_s1,
                                 d1_ETH_SO_I_s1_end_xfer
                              )
;

  output  [  1: 0] ETH_SO_I_s1_address;
  output           ETH_SO_I_s1_chipselect;
  output  [ 31: 0] ETH_SO_I_s1_readdata_from_sa;
  output           ETH_SO_I_s1_reset_n;
  output           ETH_SO_I_s1_write_n;
  output  [ 31: 0] ETH_SO_I_s1_writedata;
  output           cpu_0_data_master_granted_ETH_SO_I_s1;
  output           cpu_0_data_master_qualified_request_ETH_SO_I_s1;
  output           cpu_0_data_master_read_data_valid_ETH_SO_I_s1;
  output           cpu_0_data_master_requests_ETH_SO_I_s1;
  output           d1_ETH_SO_I_s1_end_xfer;
  input   [ 31: 0] ETH_SO_I_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] ETH_SO_I_s1_address;
  wire             ETH_SO_I_s1_allgrants;
  wire             ETH_SO_I_s1_allow_new_arb_cycle;
  wire             ETH_SO_I_s1_any_bursting_master_saved_grant;
  wire             ETH_SO_I_s1_any_continuerequest;
  wire             ETH_SO_I_s1_arb_counter_enable;
  reg     [  1: 0] ETH_SO_I_s1_arb_share_counter;
  wire    [  1: 0] ETH_SO_I_s1_arb_share_counter_next_value;
  wire    [  1: 0] ETH_SO_I_s1_arb_share_set_values;
  wire             ETH_SO_I_s1_beginbursttransfer_internal;
  wire             ETH_SO_I_s1_begins_xfer;
  wire             ETH_SO_I_s1_chipselect;
  wire             ETH_SO_I_s1_end_xfer;
  wire             ETH_SO_I_s1_firsttransfer;
  wire             ETH_SO_I_s1_grant_vector;
  wire             ETH_SO_I_s1_in_a_read_cycle;
  wire             ETH_SO_I_s1_in_a_write_cycle;
  wire             ETH_SO_I_s1_master_qreq_vector;
  wire             ETH_SO_I_s1_non_bursting_master_requests;
  wire    [ 31: 0] ETH_SO_I_s1_readdata_from_sa;
  reg              ETH_SO_I_s1_reg_firsttransfer;
  wire             ETH_SO_I_s1_reset_n;
  reg              ETH_SO_I_s1_slavearbiterlockenable;
  wire             ETH_SO_I_s1_slavearbiterlockenable2;
  wire             ETH_SO_I_s1_unreg_firsttransfer;
  wire             ETH_SO_I_s1_waits_for_read;
  wire             ETH_SO_I_s1_waits_for_write;
  wire             ETH_SO_I_s1_write_n;
  wire    [ 31: 0] ETH_SO_I_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_ETH_SO_I_s1;
  wire             cpu_0_data_master_qualified_request_ETH_SO_I_s1;
  wire             cpu_0_data_master_read_data_valid_ETH_SO_I_s1;
  wire             cpu_0_data_master_requests_ETH_SO_I_s1;
  wire             cpu_0_data_master_saved_grant_ETH_SO_I_s1;
  reg              d1_ETH_SO_I_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_ETH_SO_I_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_ETH_SO_I_s1_from_cpu_0_data_master;
  wire             wait_for_ETH_SO_I_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~ETH_SO_I_s1_end_xfer;
    end


  assign ETH_SO_I_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_ETH_SO_I_s1));
  //assign ETH_SO_I_s1_readdata_from_sa = ETH_SO_I_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign ETH_SO_I_s1_readdata_from_sa = ETH_SO_I_s1_readdata;

  assign cpu_0_data_master_requests_ETH_SO_I_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002240) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //ETH_SO_I_s1_arb_share_counter set values, which is an e_mux
  assign ETH_SO_I_s1_arb_share_set_values = 1;

  //ETH_SO_I_s1_non_bursting_master_requests mux, which is an e_mux
  assign ETH_SO_I_s1_non_bursting_master_requests = cpu_0_data_master_requests_ETH_SO_I_s1;

  //ETH_SO_I_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign ETH_SO_I_s1_any_bursting_master_saved_grant = 0;

  //ETH_SO_I_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign ETH_SO_I_s1_arb_share_counter_next_value = ETH_SO_I_s1_firsttransfer ? (ETH_SO_I_s1_arb_share_set_values - 1) : |ETH_SO_I_s1_arb_share_counter ? (ETH_SO_I_s1_arb_share_counter - 1) : 0;

  //ETH_SO_I_s1_allgrants all slave grants, which is an e_mux
  assign ETH_SO_I_s1_allgrants = |ETH_SO_I_s1_grant_vector;

  //ETH_SO_I_s1_end_xfer assignment, which is an e_assign
  assign ETH_SO_I_s1_end_xfer = ~(ETH_SO_I_s1_waits_for_read | ETH_SO_I_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_ETH_SO_I_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_ETH_SO_I_s1 = ETH_SO_I_s1_end_xfer & (~ETH_SO_I_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //ETH_SO_I_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign ETH_SO_I_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_ETH_SO_I_s1 & ETH_SO_I_s1_allgrants) | (end_xfer_arb_share_counter_term_ETH_SO_I_s1 & ~ETH_SO_I_s1_non_bursting_master_requests);

  //ETH_SO_I_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_SO_I_s1_arb_share_counter <= 0;
      else if (ETH_SO_I_s1_arb_counter_enable)
          ETH_SO_I_s1_arb_share_counter <= ETH_SO_I_s1_arb_share_counter_next_value;
    end


  //ETH_SO_I_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_SO_I_s1_slavearbiterlockenable <= 0;
      else if ((|ETH_SO_I_s1_master_qreq_vector & end_xfer_arb_share_counter_term_ETH_SO_I_s1) | (end_xfer_arb_share_counter_term_ETH_SO_I_s1 & ~ETH_SO_I_s1_non_bursting_master_requests))
          ETH_SO_I_s1_slavearbiterlockenable <= |ETH_SO_I_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master ETH_SO_I/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = ETH_SO_I_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //ETH_SO_I_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign ETH_SO_I_s1_slavearbiterlockenable2 = |ETH_SO_I_s1_arb_share_counter_next_value;

  //cpu_0/data_master ETH_SO_I/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = ETH_SO_I_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //ETH_SO_I_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign ETH_SO_I_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_ETH_SO_I_s1 = cpu_0_data_master_requests_ETH_SO_I_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_ETH_SO_I_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_ETH_SO_I_s1 = cpu_0_data_master_granted_ETH_SO_I_s1 & cpu_0_data_master_read & ~ETH_SO_I_s1_waits_for_read;

  //ETH_SO_I_s1_writedata mux, which is an e_mux
  assign ETH_SO_I_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_ETH_SO_I_s1 = cpu_0_data_master_qualified_request_ETH_SO_I_s1;

  //cpu_0/data_master saved-grant ETH_SO_I/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_ETH_SO_I_s1 = cpu_0_data_master_requests_ETH_SO_I_s1;

  //allow new arb cycle for ETH_SO_I/s1, which is an e_assign
  assign ETH_SO_I_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign ETH_SO_I_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign ETH_SO_I_s1_master_qreq_vector = 1;

  //ETH_SO_I_s1_reset_n assignment, which is an e_assign
  assign ETH_SO_I_s1_reset_n = reset_n;

  assign ETH_SO_I_s1_chipselect = cpu_0_data_master_granted_ETH_SO_I_s1;
  //ETH_SO_I_s1_firsttransfer first transaction, which is an e_assign
  assign ETH_SO_I_s1_firsttransfer = ETH_SO_I_s1_begins_xfer ? ETH_SO_I_s1_unreg_firsttransfer : ETH_SO_I_s1_reg_firsttransfer;

  //ETH_SO_I_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign ETH_SO_I_s1_unreg_firsttransfer = ~(ETH_SO_I_s1_slavearbiterlockenable & ETH_SO_I_s1_any_continuerequest);

  //ETH_SO_I_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_SO_I_s1_reg_firsttransfer <= 1'b1;
      else if (ETH_SO_I_s1_begins_xfer)
          ETH_SO_I_s1_reg_firsttransfer <= ETH_SO_I_s1_unreg_firsttransfer;
    end


  //ETH_SO_I_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign ETH_SO_I_s1_beginbursttransfer_internal = ETH_SO_I_s1_begins_xfer;

  //~ETH_SO_I_s1_write_n assignment, which is an e_mux
  assign ETH_SO_I_s1_write_n = ~(cpu_0_data_master_granted_ETH_SO_I_s1 & cpu_0_data_master_write);

  assign shifted_address_to_ETH_SO_I_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //ETH_SO_I_s1_address mux, which is an e_mux
  assign ETH_SO_I_s1_address = shifted_address_to_ETH_SO_I_s1_from_cpu_0_data_master >> 2;

  //d1_ETH_SO_I_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_ETH_SO_I_s1_end_xfer <= 1;
      else 
        d1_ETH_SO_I_s1_end_xfer <= ETH_SO_I_s1_end_xfer;
    end


  //ETH_SO_I_s1_waits_for_read in a cycle, which is an e_mux
  assign ETH_SO_I_s1_waits_for_read = ETH_SO_I_s1_in_a_read_cycle & ETH_SO_I_s1_begins_xfer;

  //ETH_SO_I_s1_in_a_read_cycle assignment, which is an e_assign
  assign ETH_SO_I_s1_in_a_read_cycle = cpu_0_data_master_granted_ETH_SO_I_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = ETH_SO_I_s1_in_a_read_cycle;

  //ETH_SO_I_s1_waits_for_write in a cycle, which is an e_mux
  assign ETH_SO_I_s1_waits_for_write = ETH_SO_I_s1_in_a_write_cycle & 0;

  //ETH_SO_I_s1_in_a_write_cycle assignment, which is an e_assign
  assign ETH_SO_I_s1_in_a_write_cycle = cpu_0_data_master_granted_ETH_SO_I_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = ETH_SO_I_s1_in_a_write_cycle;

  assign wait_for_ETH_SO_I_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //ETH_SO_I/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module ETH_WOL_I_s1_arbitrator (
                                 // inputs:
                                  ETH_WOL_I_s1_readdata,
                                  clk,
                                  cpu_0_data_master_address_to_slave,
                                  cpu_0_data_master_latency_counter,
                                  cpu_0_data_master_read,
                                  cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                  cpu_0_data_master_write,
                                  cpu_0_data_master_writedata,
                                  reset_n,

                                 // outputs:
                                  ETH_WOL_I_s1_address,
                                  ETH_WOL_I_s1_chipselect,
                                  ETH_WOL_I_s1_readdata_from_sa,
                                  ETH_WOL_I_s1_reset_n,
                                  ETH_WOL_I_s1_write_n,
                                  ETH_WOL_I_s1_writedata,
                                  cpu_0_data_master_granted_ETH_WOL_I_s1,
                                  cpu_0_data_master_qualified_request_ETH_WOL_I_s1,
                                  cpu_0_data_master_read_data_valid_ETH_WOL_I_s1,
                                  cpu_0_data_master_requests_ETH_WOL_I_s1,
                                  d1_ETH_WOL_I_s1_end_xfer
                               )
;

  output  [  1: 0] ETH_WOL_I_s1_address;
  output           ETH_WOL_I_s1_chipselect;
  output  [ 31: 0] ETH_WOL_I_s1_readdata_from_sa;
  output           ETH_WOL_I_s1_reset_n;
  output           ETH_WOL_I_s1_write_n;
  output  [ 31: 0] ETH_WOL_I_s1_writedata;
  output           cpu_0_data_master_granted_ETH_WOL_I_s1;
  output           cpu_0_data_master_qualified_request_ETH_WOL_I_s1;
  output           cpu_0_data_master_read_data_valid_ETH_WOL_I_s1;
  output           cpu_0_data_master_requests_ETH_WOL_I_s1;
  output           d1_ETH_WOL_I_s1_end_xfer;
  input   [ 31: 0] ETH_WOL_I_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] ETH_WOL_I_s1_address;
  wire             ETH_WOL_I_s1_allgrants;
  wire             ETH_WOL_I_s1_allow_new_arb_cycle;
  wire             ETH_WOL_I_s1_any_bursting_master_saved_grant;
  wire             ETH_WOL_I_s1_any_continuerequest;
  wire             ETH_WOL_I_s1_arb_counter_enable;
  reg     [  1: 0] ETH_WOL_I_s1_arb_share_counter;
  wire    [  1: 0] ETH_WOL_I_s1_arb_share_counter_next_value;
  wire    [  1: 0] ETH_WOL_I_s1_arb_share_set_values;
  wire             ETH_WOL_I_s1_beginbursttransfer_internal;
  wire             ETH_WOL_I_s1_begins_xfer;
  wire             ETH_WOL_I_s1_chipselect;
  wire             ETH_WOL_I_s1_end_xfer;
  wire             ETH_WOL_I_s1_firsttransfer;
  wire             ETH_WOL_I_s1_grant_vector;
  wire             ETH_WOL_I_s1_in_a_read_cycle;
  wire             ETH_WOL_I_s1_in_a_write_cycle;
  wire             ETH_WOL_I_s1_master_qreq_vector;
  wire             ETH_WOL_I_s1_non_bursting_master_requests;
  wire    [ 31: 0] ETH_WOL_I_s1_readdata_from_sa;
  reg              ETH_WOL_I_s1_reg_firsttransfer;
  wire             ETH_WOL_I_s1_reset_n;
  reg              ETH_WOL_I_s1_slavearbiterlockenable;
  wire             ETH_WOL_I_s1_slavearbiterlockenable2;
  wire             ETH_WOL_I_s1_unreg_firsttransfer;
  wire             ETH_WOL_I_s1_waits_for_read;
  wire             ETH_WOL_I_s1_waits_for_write;
  wire             ETH_WOL_I_s1_write_n;
  wire    [ 31: 0] ETH_WOL_I_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_ETH_WOL_I_s1;
  wire             cpu_0_data_master_qualified_request_ETH_WOL_I_s1;
  wire             cpu_0_data_master_read_data_valid_ETH_WOL_I_s1;
  wire             cpu_0_data_master_requests_ETH_WOL_I_s1;
  wire             cpu_0_data_master_saved_grant_ETH_WOL_I_s1;
  reg              d1_ETH_WOL_I_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_ETH_WOL_I_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_ETH_WOL_I_s1_from_cpu_0_data_master;
  wire             wait_for_ETH_WOL_I_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~ETH_WOL_I_s1_end_xfer;
    end


  assign ETH_WOL_I_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_ETH_WOL_I_s1));
  //assign ETH_WOL_I_s1_readdata_from_sa = ETH_WOL_I_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign ETH_WOL_I_s1_readdata_from_sa = ETH_WOL_I_s1_readdata;

  assign cpu_0_data_master_requests_ETH_WOL_I_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002280) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //ETH_WOL_I_s1_arb_share_counter set values, which is an e_mux
  assign ETH_WOL_I_s1_arb_share_set_values = 1;

  //ETH_WOL_I_s1_non_bursting_master_requests mux, which is an e_mux
  assign ETH_WOL_I_s1_non_bursting_master_requests = cpu_0_data_master_requests_ETH_WOL_I_s1;

  //ETH_WOL_I_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign ETH_WOL_I_s1_any_bursting_master_saved_grant = 0;

  //ETH_WOL_I_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign ETH_WOL_I_s1_arb_share_counter_next_value = ETH_WOL_I_s1_firsttransfer ? (ETH_WOL_I_s1_arb_share_set_values - 1) : |ETH_WOL_I_s1_arb_share_counter ? (ETH_WOL_I_s1_arb_share_counter - 1) : 0;

  //ETH_WOL_I_s1_allgrants all slave grants, which is an e_mux
  assign ETH_WOL_I_s1_allgrants = |ETH_WOL_I_s1_grant_vector;

  //ETH_WOL_I_s1_end_xfer assignment, which is an e_assign
  assign ETH_WOL_I_s1_end_xfer = ~(ETH_WOL_I_s1_waits_for_read | ETH_WOL_I_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_ETH_WOL_I_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_ETH_WOL_I_s1 = ETH_WOL_I_s1_end_xfer & (~ETH_WOL_I_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //ETH_WOL_I_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign ETH_WOL_I_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_ETH_WOL_I_s1 & ETH_WOL_I_s1_allgrants) | (end_xfer_arb_share_counter_term_ETH_WOL_I_s1 & ~ETH_WOL_I_s1_non_bursting_master_requests);

  //ETH_WOL_I_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_WOL_I_s1_arb_share_counter <= 0;
      else if (ETH_WOL_I_s1_arb_counter_enable)
          ETH_WOL_I_s1_arb_share_counter <= ETH_WOL_I_s1_arb_share_counter_next_value;
    end


  //ETH_WOL_I_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_WOL_I_s1_slavearbiterlockenable <= 0;
      else if ((|ETH_WOL_I_s1_master_qreq_vector & end_xfer_arb_share_counter_term_ETH_WOL_I_s1) | (end_xfer_arb_share_counter_term_ETH_WOL_I_s1 & ~ETH_WOL_I_s1_non_bursting_master_requests))
          ETH_WOL_I_s1_slavearbiterlockenable <= |ETH_WOL_I_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master ETH_WOL_I/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = ETH_WOL_I_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //ETH_WOL_I_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign ETH_WOL_I_s1_slavearbiterlockenable2 = |ETH_WOL_I_s1_arb_share_counter_next_value;

  //cpu_0/data_master ETH_WOL_I/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = ETH_WOL_I_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //ETH_WOL_I_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign ETH_WOL_I_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_ETH_WOL_I_s1 = cpu_0_data_master_requests_ETH_WOL_I_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_ETH_WOL_I_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_ETH_WOL_I_s1 = cpu_0_data_master_granted_ETH_WOL_I_s1 & cpu_0_data_master_read & ~ETH_WOL_I_s1_waits_for_read;

  //ETH_WOL_I_s1_writedata mux, which is an e_mux
  assign ETH_WOL_I_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_ETH_WOL_I_s1 = cpu_0_data_master_qualified_request_ETH_WOL_I_s1;

  //cpu_0/data_master saved-grant ETH_WOL_I/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_ETH_WOL_I_s1 = cpu_0_data_master_requests_ETH_WOL_I_s1;

  //allow new arb cycle for ETH_WOL_I/s1, which is an e_assign
  assign ETH_WOL_I_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign ETH_WOL_I_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign ETH_WOL_I_s1_master_qreq_vector = 1;

  //ETH_WOL_I_s1_reset_n assignment, which is an e_assign
  assign ETH_WOL_I_s1_reset_n = reset_n;

  assign ETH_WOL_I_s1_chipselect = cpu_0_data_master_granted_ETH_WOL_I_s1;
  //ETH_WOL_I_s1_firsttransfer first transaction, which is an e_assign
  assign ETH_WOL_I_s1_firsttransfer = ETH_WOL_I_s1_begins_xfer ? ETH_WOL_I_s1_unreg_firsttransfer : ETH_WOL_I_s1_reg_firsttransfer;

  //ETH_WOL_I_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign ETH_WOL_I_s1_unreg_firsttransfer = ~(ETH_WOL_I_s1_slavearbiterlockenable & ETH_WOL_I_s1_any_continuerequest);

  //ETH_WOL_I_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          ETH_WOL_I_s1_reg_firsttransfer <= 1'b1;
      else if (ETH_WOL_I_s1_begins_xfer)
          ETH_WOL_I_s1_reg_firsttransfer <= ETH_WOL_I_s1_unreg_firsttransfer;
    end


  //ETH_WOL_I_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign ETH_WOL_I_s1_beginbursttransfer_internal = ETH_WOL_I_s1_begins_xfer;

  //~ETH_WOL_I_s1_write_n assignment, which is an e_mux
  assign ETH_WOL_I_s1_write_n = ~(cpu_0_data_master_granted_ETH_WOL_I_s1 & cpu_0_data_master_write);

  assign shifted_address_to_ETH_WOL_I_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //ETH_WOL_I_s1_address mux, which is an e_mux
  assign ETH_WOL_I_s1_address = shifted_address_to_ETH_WOL_I_s1_from_cpu_0_data_master >> 2;

  //d1_ETH_WOL_I_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_ETH_WOL_I_s1_end_xfer <= 1;
      else 
        d1_ETH_WOL_I_s1_end_xfer <= ETH_WOL_I_s1_end_xfer;
    end


  //ETH_WOL_I_s1_waits_for_read in a cycle, which is an e_mux
  assign ETH_WOL_I_s1_waits_for_read = ETH_WOL_I_s1_in_a_read_cycle & ETH_WOL_I_s1_begins_xfer;

  //ETH_WOL_I_s1_in_a_read_cycle assignment, which is an e_assign
  assign ETH_WOL_I_s1_in_a_read_cycle = cpu_0_data_master_granted_ETH_WOL_I_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = ETH_WOL_I_s1_in_a_read_cycle;

  //ETH_WOL_I_s1_waits_for_write in a cycle, which is an e_mux
  assign ETH_WOL_I_s1_waits_for_write = ETH_WOL_I_s1_in_a_write_cycle & 0;

  //ETH_WOL_I_s1_in_a_write_cycle assignment, which is an e_assign
  assign ETH_WOL_I_s1_in_a_write_cycle = cpu_0_data_master_granted_ETH_WOL_I_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = ETH_WOL_I_s1_in_a_write_cycle;

  assign wait_for_ETH_WOL_I_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //ETH_WOL_I/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module IR_DATA_s1_arbitrator (
                               // inputs:
                                IR_DATA_s1_readdata,
                                clk,
                                cpu_0_data_master_address_to_slave,
                                cpu_0_data_master_latency_counter,
                                cpu_0_data_master_read,
                                cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                cpu_0_data_master_write,
                                cpu_0_data_master_writedata,
                                reset_n,

                               // outputs:
                                IR_DATA_s1_address,
                                IR_DATA_s1_chipselect,
                                IR_DATA_s1_readdata_from_sa,
                                IR_DATA_s1_reset_n,
                                IR_DATA_s1_write_n,
                                IR_DATA_s1_writedata,
                                cpu_0_data_master_granted_IR_DATA_s1,
                                cpu_0_data_master_qualified_request_IR_DATA_s1,
                                cpu_0_data_master_read_data_valid_IR_DATA_s1,
                                cpu_0_data_master_requests_IR_DATA_s1,
                                d1_IR_DATA_s1_end_xfer
                             )
;

  output  [  1: 0] IR_DATA_s1_address;
  output           IR_DATA_s1_chipselect;
  output  [ 31: 0] IR_DATA_s1_readdata_from_sa;
  output           IR_DATA_s1_reset_n;
  output           IR_DATA_s1_write_n;
  output  [ 31: 0] IR_DATA_s1_writedata;
  output           cpu_0_data_master_granted_IR_DATA_s1;
  output           cpu_0_data_master_qualified_request_IR_DATA_s1;
  output           cpu_0_data_master_read_data_valid_IR_DATA_s1;
  output           cpu_0_data_master_requests_IR_DATA_s1;
  output           d1_IR_DATA_s1_end_xfer;
  input   [ 31: 0] IR_DATA_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] IR_DATA_s1_address;
  wire             IR_DATA_s1_allgrants;
  wire             IR_DATA_s1_allow_new_arb_cycle;
  wire             IR_DATA_s1_any_bursting_master_saved_grant;
  wire             IR_DATA_s1_any_continuerequest;
  wire             IR_DATA_s1_arb_counter_enable;
  reg     [  1: 0] IR_DATA_s1_arb_share_counter;
  wire    [  1: 0] IR_DATA_s1_arb_share_counter_next_value;
  wire    [  1: 0] IR_DATA_s1_arb_share_set_values;
  wire             IR_DATA_s1_beginbursttransfer_internal;
  wire             IR_DATA_s1_begins_xfer;
  wire             IR_DATA_s1_chipselect;
  wire             IR_DATA_s1_end_xfer;
  wire             IR_DATA_s1_firsttransfer;
  wire             IR_DATA_s1_grant_vector;
  wire             IR_DATA_s1_in_a_read_cycle;
  wire             IR_DATA_s1_in_a_write_cycle;
  wire             IR_DATA_s1_master_qreq_vector;
  wire             IR_DATA_s1_non_bursting_master_requests;
  wire    [ 31: 0] IR_DATA_s1_readdata_from_sa;
  reg              IR_DATA_s1_reg_firsttransfer;
  wire             IR_DATA_s1_reset_n;
  reg              IR_DATA_s1_slavearbiterlockenable;
  wire             IR_DATA_s1_slavearbiterlockenable2;
  wire             IR_DATA_s1_unreg_firsttransfer;
  wire             IR_DATA_s1_waits_for_read;
  wire             IR_DATA_s1_waits_for_write;
  wire             IR_DATA_s1_write_n;
  wire    [ 31: 0] IR_DATA_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_IR_DATA_s1;
  wire             cpu_0_data_master_qualified_request_IR_DATA_s1;
  wire             cpu_0_data_master_read_data_valid_IR_DATA_s1;
  wire             cpu_0_data_master_requests_IR_DATA_s1;
  wire             cpu_0_data_master_saved_grant_IR_DATA_s1;
  reg              d1_IR_DATA_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_IR_DATA_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_IR_DATA_s1_from_cpu_0_data_master;
  wire             wait_for_IR_DATA_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~IR_DATA_s1_end_xfer;
    end


  assign IR_DATA_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_IR_DATA_s1));
  //assign IR_DATA_s1_readdata_from_sa = IR_DATA_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign IR_DATA_s1_readdata_from_sa = IR_DATA_s1_readdata;

  assign cpu_0_data_master_requests_IR_DATA_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002100) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //IR_DATA_s1_arb_share_counter set values, which is an e_mux
  assign IR_DATA_s1_arb_share_set_values = 1;

  //IR_DATA_s1_non_bursting_master_requests mux, which is an e_mux
  assign IR_DATA_s1_non_bursting_master_requests = cpu_0_data_master_requests_IR_DATA_s1;

  //IR_DATA_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign IR_DATA_s1_any_bursting_master_saved_grant = 0;

  //IR_DATA_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign IR_DATA_s1_arb_share_counter_next_value = IR_DATA_s1_firsttransfer ? (IR_DATA_s1_arb_share_set_values - 1) : |IR_DATA_s1_arb_share_counter ? (IR_DATA_s1_arb_share_counter - 1) : 0;

  //IR_DATA_s1_allgrants all slave grants, which is an e_mux
  assign IR_DATA_s1_allgrants = |IR_DATA_s1_grant_vector;

  //IR_DATA_s1_end_xfer assignment, which is an e_assign
  assign IR_DATA_s1_end_xfer = ~(IR_DATA_s1_waits_for_read | IR_DATA_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_IR_DATA_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_IR_DATA_s1 = IR_DATA_s1_end_xfer & (~IR_DATA_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //IR_DATA_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign IR_DATA_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_IR_DATA_s1 & IR_DATA_s1_allgrants) | (end_xfer_arb_share_counter_term_IR_DATA_s1 & ~IR_DATA_s1_non_bursting_master_requests);

  //IR_DATA_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          IR_DATA_s1_arb_share_counter <= 0;
      else if (IR_DATA_s1_arb_counter_enable)
          IR_DATA_s1_arb_share_counter <= IR_DATA_s1_arb_share_counter_next_value;
    end


  //IR_DATA_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          IR_DATA_s1_slavearbiterlockenable <= 0;
      else if ((|IR_DATA_s1_master_qreq_vector & end_xfer_arb_share_counter_term_IR_DATA_s1) | (end_xfer_arb_share_counter_term_IR_DATA_s1 & ~IR_DATA_s1_non_bursting_master_requests))
          IR_DATA_s1_slavearbiterlockenable <= |IR_DATA_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master IR_DATA/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = IR_DATA_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //IR_DATA_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign IR_DATA_s1_slavearbiterlockenable2 = |IR_DATA_s1_arb_share_counter_next_value;

  //cpu_0/data_master IR_DATA/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = IR_DATA_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //IR_DATA_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign IR_DATA_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_IR_DATA_s1 = cpu_0_data_master_requests_IR_DATA_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_IR_DATA_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_IR_DATA_s1 = cpu_0_data_master_granted_IR_DATA_s1 & cpu_0_data_master_read & ~IR_DATA_s1_waits_for_read;

  //IR_DATA_s1_writedata mux, which is an e_mux
  assign IR_DATA_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_IR_DATA_s1 = cpu_0_data_master_qualified_request_IR_DATA_s1;

  //cpu_0/data_master saved-grant IR_DATA/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_IR_DATA_s1 = cpu_0_data_master_requests_IR_DATA_s1;

  //allow new arb cycle for IR_DATA/s1, which is an e_assign
  assign IR_DATA_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign IR_DATA_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign IR_DATA_s1_master_qreq_vector = 1;

  //IR_DATA_s1_reset_n assignment, which is an e_assign
  assign IR_DATA_s1_reset_n = reset_n;

  assign IR_DATA_s1_chipselect = cpu_0_data_master_granted_IR_DATA_s1;
  //IR_DATA_s1_firsttransfer first transaction, which is an e_assign
  assign IR_DATA_s1_firsttransfer = IR_DATA_s1_begins_xfer ? IR_DATA_s1_unreg_firsttransfer : IR_DATA_s1_reg_firsttransfer;

  //IR_DATA_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign IR_DATA_s1_unreg_firsttransfer = ~(IR_DATA_s1_slavearbiterlockenable & IR_DATA_s1_any_continuerequest);

  //IR_DATA_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          IR_DATA_s1_reg_firsttransfer <= 1'b1;
      else if (IR_DATA_s1_begins_xfer)
          IR_DATA_s1_reg_firsttransfer <= IR_DATA_s1_unreg_firsttransfer;
    end


  //IR_DATA_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign IR_DATA_s1_beginbursttransfer_internal = IR_DATA_s1_begins_xfer;

  //~IR_DATA_s1_write_n assignment, which is an e_mux
  assign IR_DATA_s1_write_n = ~(cpu_0_data_master_granted_IR_DATA_s1 & cpu_0_data_master_write);

  assign shifted_address_to_IR_DATA_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //IR_DATA_s1_address mux, which is an e_mux
  assign IR_DATA_s1_address = shifted_address_to_IR_DATA_s1_from_cpu_0_data_master >> 2;

  //d1_IR_DATA_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_IR_DATA_s1_end_xfer <= 1;
      else 
        d1_IR_DATA_s1_end_xfer <= IR_DATA_s1_end_xfer;
    end


  //IR_DATA_s1_waits_for_read in a cycle, which is an e_mux
  assign IR_DATA_s1_waits_for_read = IR_DATA_s1_in_a_read_cycle & IR_DATA_s1_begins_xfer;

  //IR_DATA_s1_in_a_read_cycle assignment, which is an e_assign
  assign IR_DATA_s1_in_a_read_cycle = cpu_0_data_master_granted_IR_DATA_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = IR_DATA_s1_in_a_read_cycle;

  //IR_DATA_s1_waits_for_write in a cycle, which is an e_mux
  assign IR_DATA_s1_waits_for_write = IR_DATA_s1_in_a_write_cycle & 0;

  //IR_DATA_s1_in_a_write_cycle assignment, which is an e_assign
  assign IR_DATA_s1_in_a_write_cycle = cpu_0_data_master_granted_IR_DATA_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = IR_DATA_s1_in_a_write_cycle;

  assign wait_for_IR_DATA_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //IR_DATA/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module KEY_FOCUS_s1_arbitrator (
                                 // inputs:
                                  KEY_FOCUS_s1_readdata,
                                  clk,
                                  cpu_0_data_master_address_to_slave,
                                  cpu_0_data_master_latency_counter,
                                  cpu_0_data_master_read,
                                  cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                  cpu_0_data_master_write,
                                  cpu_0_data_master_writedata,
                                  reset_n,

                                 // outputs:
                                  KEY_FOCUS_s1_address,
                                  KEY_FOCUS_s1_chipselect,
                                  KEY_FOCUS_s1_readdata_from_sa,
                                  KEY_FOCUS_s1_reset_n,
                                  KEY_FOCUS_s1_write_n,
                                  KEY_FOCUS_s1_writedata,
                                  cpu_0_data_master_granted_KEY_FOCUS_s1,
                                  cpu_0_data_master_qualified_request_KEY_FOCUS_s1,
                                  cpu_0_data_master_read_data_valid_KEY_FOCUS_s1,
                                  cpu_0_data_master_requests_KEY_FOCUS_s1,
                                  d1_KEY_FOCUS_s1_end_xfer
                               )
;

  output  [  1: 0] KEY_FOCUS_s1_address;
  output           KEY_FOCUS_s1_chipselect;
  output  [ 31: 0] KEY_FOCUS_s1_readdata_from_sa;
  output           KEY_FOCUS_s1_reset_n;
  output           KEY_FOCUS_s1_write_n;
  output  [ 31: 0] KEY_FOCUS_s1_writedata;
  output           cpu_0_data_master_granted_KEY_FOCUS_s1;
  output           cpu_0_data_master_qualified_request_KEY_FOCUS_s1;
  output           cpu_0_data_master_read_data_valid_KEY_FOCUS_s1;
  output           cpu_0_data_master_requests_KEY_FOCUS_s1;
  output           d1_KEY_FOCUS_s1_end_xfer;
  input   [ 31: 0] KEY_FOCUS_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] KEY_FOCUS_s1_address;
  wire             KEY_FOCUS_s1_allgrants;
  wire             KEY_FOCUS_s1_allow_new_arb_cycle;
  wire             KEY_FOCUS_s1_any_bursting_master_saved_grant;
  wire             KEY_FOCUS_s1_any_continuerequest;
  wire             KEY_FOCUS_s1_arb_counter_enable;
  reg     [  1: 0] KEY_FOCUS_s1_arb_share_counter;
  wire    [  1: 0] KEY_FOCUS_s1_arb_share_counter_next_value;
  wire    [  1: 0] KEY_FOCUS_s1_arb_share_set_values;
  wire             KEY_FOCUS_s1_beginbursttransfer_internal;
  wire             KEY_FOCUS_s1_begins_xfer;
  wire             KEY_FOCUS_s1_chipselect;
  wire             KEY_FOCUS_s1_end_xfer;
  wire             KEY_FOCUS_s1_firsttransfer;
  wire             KEY_FOCUS_s1_grant_vector;
  wire             KEY_FOCUS_s1_in_a_read_cycle;
  wire             KEY_FOCUS_s1_in_a_write_cycle;
  wire             KEY_FOCUS_s1_master_qreq_vector;
  wire             KEY_FOCUS_s1_non_bursting_master_requests;
  wire    [ 31: 0] KEY_FOCUS_s1_readdata_from_sa;
  reg              KEY_FOCUS_s1_reg_firsttransfer;
  wire             KEY_FOCUS_s1_reset_n;
  reg              KEY_FOCUS_s1_slavearbiterlockenable;
  wire             KEY_FOCUS_s1_slavearbiterlockenable2;
  wire             KEY_FOCUS_s1_unreg_firsttransfer;
  wire             KEY_FOCUS_s1_waits_for_read;
  wire             KEY_FOCUS_s1_waits_for_write;
  wire             KEY_FOCUS_s1_write_n;
  wire    [ 31: 0] KEY_FOCUS_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_KEY_FOCUS_s1;
  wire             cpu_0_data_master_qualified_request_KEY_FOCUS_s1;
  wire             cpu_0_data_master_read_data_valid_KEY_FOCUS_s1;
  wire             cpu_0_data_master_requests_KEY_FOCUS_s1;
  wire             cpu_0_data_master_saved_grant_KEY_FOCUS_s1;
  reg              d1_KEY_FOCUS_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_KEY_FOCUS_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_KEY_FOCUS_s1_from_cpu_0_data_master;
  wire             wait_for_KEY_FOCUS_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~KEY_FOCUS_s1_end_xfer;
    end


  assign KEY_FOCUS_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_KEY_FOCUS_s1));
  //assign KEY_FOCUS_s1_readdata_from_sa = KEY_FOCUS_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign KEY_FOCUS_s1_readdata_from_sa = KEY_FOCUS_s1_readdata;

  assign cpu_0_data_master_requests_KEY_FOCUS_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002110) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //KEY_FOCUS_s1_arb_share_counter set values, which is an e_mux
  assign KEY_FOCUS_s1_arb_share_set_values = 1;

  //KEY_FOCUS_s1_non_bursting_master_requests mux, which is an e_mux
  assign KEY_FOCUS_s1_non_bursting_master_requests = cpu_0_data_master_requests_KEY_FOCUS_s1;

  //KEY_FOCUS_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign KEY_FOCUS_s1_any_bursting_master_saved_grant = 0;

  //KEY_FOCUS_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign KEY_FOCUS_s1_arb_share_counter_next_value = KEY_FOCUS_s1_firsttransfer ? (KEY_FOCUS_s1_arb_share_set_values - 1) : |KEY_FOCUS_s1_arb_share_counter ? (KEY_FOCUS_s1_arb_share_counter - 1) : 0;

  //KEY_FOCUS_s1_allgrants all slave grants, which is an e_mux
  assign KEY_FOCUS_s1_allgrants = |KEY_FOCUS_s1_grant_vector;

  //KEY_FOCUS_s1_end_xfer assignment, which is an e_assign
  assign KEY_FOCUS_s1_end_xfer = ~(KEY_FOCUS_s1_waits_for_read | KEY_FOCUS_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_KEY_FOCUS_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_KEY_FOCUS_s1 = KEY_FOCUS_s1_end_xfer & (~KEY_FOCUS_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //KEY_FOCUS_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign KEY_FOCUS_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_KEY_FOCUS_s1 & KEY_FOCUS_s1_allgrants) | (end_xfer_arb_share_counter_term_KEY_FOCUS_s1 & ~KEY_FOCUS_s1_non_bursting_master_requests);

  //KEY_FOCUS_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          KEY_FOCUS_s1_arb_share_counter <= 0;
      else if (KEY_FOCUS_s1_arb_counter_enable)
          KEY_FOCUS_s1_arb_share_counter <= KEY_FOCUS_s1_arb_share_counter_next_value;
    end


  //KEY_FOCUS_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          KEY_FOCUS_s1_slavearbiterlockenable <= 0;
      else if ((|KEY_FOCUS_s1_master_qreq_vector & end_xfer_arb_share_counter_term_KEY_FOCUS_s1) | (end_xfer_arb_share_counter_term_KEY_FOCUS_s1 & ~KEY_FOCUS_s1_non_bursting_master_requests))
          KEY_FOCUS_s1_slavearbiterlockenable <= |KEY_FOCUS_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master KEY_FOCUS/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = KEY_FOCUS_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //KEY_FOCUS_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign KEY_FOCUS_s1_slavearbiterlockenable2 = |KEY_FOCUS_s1_arb_share_counter_next_value;

  //cpu_0/data_master KEY_FOCUS/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = KEY_FOCUS_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //KEY_FOCUS_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign KEY_FOCUS_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_KEY_FOCUS_s1 = cpu_0_data_master_requests_KEY_FOCUS_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_KEY_FOCUS_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_KEY_FOCUS_s1 = cpu_0_data_master_granted_KEY_FOCUS_s1 & cpu_0_data_master_read & ~KEY_FOCUS_s1_waits_for_read;

  //KEY_FOCUS_s1_writedata mux, which is an e_mux
  assign KEY_FOCUS_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_KEY_FOCUS_s1 = cpu_0_data_master_qualified_request_KEY_FOCUS_s1;

  //cpu_0/data_master saved-grant KEY_FOCUS/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_KEY_FOCUS_s1 = cpu_0_data_master_requests_KEY_FOCUS_s1;

  //allow new arb cycle for KEY_FOCUS/s1, which is an e_assign
  assign KEY_FOCUS_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign KEY_FOCUS_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign KEY_FOCUS_s1_master_qreq_vector = 1;

  //KEY_FOCUS_s1_reset_n assignment, which is an e_assign
  assign KEY_FOCUS_s1_reset_n = reset_n;

  assign KEY_FOCUS_s1_chipselect = cpu_0_data_master_granted_KEY_FOCUS_s1;
  //KEY_FOCUS_s1_firsttransfer first transaction, which is an e_assign
  assign KEY_FOCUS_s1_firsttransfer = KEY_FOCUS_s1_begins_xfer ? KEY_FOCUS_s1_unreg_firsttransfer : KEY_FOCUS_s1_reg_firsttransfer;

  //KEY_FOCUS_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign KEY_FOCUS_s1_unreg_firsttransfer = ~(KEY_FOCUS_s1_slavearbiterlockenable & KEY_FOCUS_s1_any_continuerequest);

  //KEY_FOCUS_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          KEY_FOCUS_s1_reg_firsttransfer <= 1'b1;
      else if (KEY_FOCUS_s1_begins_xfer)
          KEY_FOCUS_s1_reg_firsttransfer <= KEY_FOCUS_s1_unreg_firsttransfer;
    end


  //KEY_FOCUS_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign KEY_FOCUS_s1_beginbursttransfer_internal = KEY_FOCUS_s1_begins_xfer;

  //~KEY_FOCUS_s1_write_n assignment, which is an e_mux
  assign KEY_FOCUS_s1_write_n = ~(cpu_0_data_master_granted_KEY_FOCUS_s1 & cpu_0_data_master_write);

  assign shifted_address_to_KEY_FOCUS_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //KEY_FOCUS_s1_address mux, which is an e_mux
  assign KEY_FOCUS_s1_address = shifted_address_to_KEY_FOCUS_s1_from_cpu_0_data_master >> 2;

  //d1_KEY_FOCUS_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_KEY_FOCUS_s1_end_xfer <= 1;
      else 
        d1_KEY_FOCUS_s1_end_xfer <= KEY_FOCUS_s1_end_xfer;
    end


  //KEY_FOCUS_s1_waits_for_read in a cycle, which is an e_mux
  assign KEY_FOCUS_s1_waits_for_read = KEY_FOCUS_s1_in_a_read_cycle & KEY_FOCUS_s1_begins_xfer;

  //KEY_FOCUS_s1_in_a_read_cycle assignment, which is an e_assign
  assign KEY_FOCUS_s1_in_a_read_cycle = cpu_0_data_master_granted_KEY_FOCUS_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = KEY_FOCUS_s1_in_a_read_cycle;

  //KEY_FOCUS_s1_waits_for_write in a cycle, which is an e_mux
  assign KEY_FOCUS_s1_waits_for_write = KEY_FOCUS_s1_in_a_write_cycle & 0;

  //KEY_FOCUS_s1_in_a_write_cycle assignment, which is an e_assign
  assign KEY_FOCUS_s1_in_a_write_cycle = cpu_0_data_master_granted_KEY_FOCUS_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = KEY_FOCUS_s1_in_a_write_cycle;

  assign wait_for_KEY_FOCUS_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //KEY_FOCUS/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module LCD_CS_s1_arbitrator (
                              // inputs:
                               LCD_CS_s1_readdata,
                               clk,
                               cpu_0_data_master_address_to_slave,
                               cpu_0_data_master_latency_counter,
                               cpu_0_data_master_read,
                               cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                               cpu_0_data_master_write,
                               cpu_0_data_master_writedata,
                               reset_n,

                              // outputs:
                               LCD_CS_s1_address,
                               LCD_CS_s1_chipselect,
                               LCD_CS_s1_readdata_from_sa,
                               LCD_CS_s1_reset_n,
                               LCD_CS_s1_write_n,
                               LCD_CS_s1_writedata,
                               cpu_0_data_master_granted_LCD_CS_s1,
                               cpu_0_data_master_qualified_request_LCD_CS_s1,
                               cpu_0_data_master_read_data_valid_LCD_CS_s1,
                               cpu_0_data_master_requests_LCD_CS_s1,
                               d1_LCD_CS_s1_end_xfer
                            )
;

  output  [  1: 0] LCD_CS_s1_address;
  output           LCD_CS_s1_chipselect;
  output  [ 31: 0] LCD_CS_s1_readdata_from_sa;
  output           LCD_CS_s1_reset_n;
  output           LCD_CS_s1_write_n;
  output  [ 31: 0] LCD_CS_s1_writedata;
  output           cpu_0_data_master_granted_LCD_CS_s1;
  output           cpu_0_data_master_qualified_request_LCD_CS_s1;
  output           cpu_0_data_master_read_data_valid_LCD_CS_s1;
  output           cpu_0_data_master_requests_LCD_CS_s1;
  output           d1_LCD_CS_s1_end_xfer;
  input   [ 31: 0] LCD_CS_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] LCD_CS_s1_address;
  wire             LCD_CS_s1_allgrants;
  wire             LCD_CS_s1_allow_new_arb_cycle;
  wire             LCD_CS_s1_any_bursting_master_saved_grant;
  wire             LCD_CS_s1_any_continuerequest;
  wire             LCD_CS_s1_arb_counter_enable;
  reg     [  1: 0] LCD_CS_s1_arb_share_counter;
  wire    [  1: 0] LCD_CS_s1_arb_share_counter_next_value;
  wire    [  1: 0] LCD_CS_s1_arb_share_set_values;
  wire             LCD_CS_s1_beginbursttransfer_internal;
  wire             LCD_CS_s1_begins_xfer;
  wire             LCD_CS_s1_chipselect;
  wire             LCD_CS_s1_end_xfer;
  wire             LCD_CS_s1_firsttransfer;
  wire             LCD_CS_s1_grant_vector;
  wire             LCD_CS_s1_in_a_read_cycle;
  wire             LCD_CS_s1_in_a_write_cycle;
  wire             LCD_CS_s1_master_qreq_vector;
  wire             LCD_CS_s1_non_bursting_master_requests;
  wire    [ 31: 0] LCD_CS_s1_readdata_from_sa;
  reg              LCD_CS_s1_reg_firsttransfer;
  wire             LCD_CS_s1_reset_n;
  reg              LCD_CS_s1_slavearbiterlockenable;
  wire             LCD_CS_s1_slavearbiterlockenable2;
  wire             LCD_CS_s1_unreg_firsttransfer;
  wire             LCD_CS_s1_waits_for_read;
  wire             LCD_CS_s1_waits_for_write;
  wire             LCD_CS_s1_write_n;
  wire    [ 31: 0] LCD_CS_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_LCD_CS_s1;
  wire             cpu_0_data_master_qualified_request_LCD_CS_s1;
  wire             cpu_0_data_master_read_data_valid_LCD_CS_s1;
  wire             cpu_0_data_master_requests_LCD_CS_s1;
  wire             cpu_0_data_master_saved_grant_LCD_CS_s1;
  reg              d1_LCD_CS_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_LCD_CS_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_LCD_CS_s1_from_cpu_0_data_master;
  wire             wait_for_LCD_CS_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~LCD_CS_s1_end_xfer;
    end


  assign LCD_CS_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_LCD_CS_s1));
  //assign LCD_CS_s1_readdata_from_sa = LCD_CS_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign LCD_CS_s1_readdata_from_sa = LCD_CS_s1_readdata;

  assign cpu_0_data_master_requests_LCD_CS_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002070) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //LCD_CS_s1_arb_share_counter set values, which is an e_mux
  assign LCD_CS_s1_arb_share_set_values = 1;

  //LCD_CS_s1_non_bursting_master_requests mux, which is an e_mux
  assign LCD_CS_s1_non_bursting_master_requests = cpu_0_data_master_requests_LCD_CS_s1;

  //LCD_CS_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign LCD_CS_s1_any_bursting_master_saved_grant = 0;

  //LCD_CS_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign LCD_CS_s1_arb_share_counter_next_value = LCD_CS_s1_firsttransfer ? (LCD_CS_s1_arb_share_set_values - 1) : |LCD_CS_s1_arb_share_counter ? (LCD_CS_s1_arb_share_counter - 1) : 0;

  //LCD_CS_s1_allgrants all slave grants, which is an e_mux
  assign LCD_CS_s1_allgrants = |LCD_CS_s1_grant_vector;

  //LCD_CS_s1_end_xfer assignment, which is an e_assign
  assign LCD_CS_s1_end_xfer = ~(LCD_CS_s1_waits_for_read | LCD_CS_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_LCD_CS_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_LCD_CS_s1 = LCD_CS_s1_end_xfer & (~LCD_CS_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //LCD_CS_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign LCD_CS_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_LCD_CS_s1 & LCD_CS_s1_allgrants) | (end_xfer_arb_share_counter_term_LCD_CS_s1 & ~LCD_CS_s1_non_bursting_master_requests);

  //LCD_CS_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          LCD_CS_s1_arb_share_counter <= 0;
      else if (LCD_CS_s1_arb_counter_enable)
          LCD_CS_s1_arb_share_counter <= LCD_CS_s1_arb_share_counter_next_value;
    end


  //LCD_CS_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          LCD_CS_s1_slavearbiterlockenable <= 0;
      else if ((|LCD_CS_s1_master_qreq_vector & end_xfer_arb_share_counter_term_LCD_CS_s1) | (end_xfer_arb_share_counter_term_LCD_CS_s1 & ~LCD_CS_s1_non_bursting_master_requests))
          LCD_CS_s1_slavearbiterlockenable <= |LCD_CS_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master LCD_CS/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = LCD_CS_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //LCD_CS_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign LCD_CS_s1_slavearbiterlockenable2 = |LCD_CS_s1_arb_share_counter_next_value;

  //cpu_0/data_master LCD_CS/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = LCD_CS_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //LCD_CS_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign LCD_CS_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_LCD_CS_s1 = cpu_0_data_master_requests_LCD_CS_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_LCD_CS_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_LCD_CS_s1 = cpu_0_data_master_granted_LCD_CS_s1 & cpu_0_data_master_read & ~LCD_CS_s1_waits_for_read;

  //LCD_CS_s1_writedata mux, which is an e_mux
  assign LCD_CS_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_LCD_CS_s1 = cpu_0_data_master_qualified_request_LCD_CS_s1;

  //cpu_0/data_master saved-grant LCD_CS/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_LCD_CS_s1 = cpu_0_data_master_requests_LCD_CS_s1;

  //allow new arb cycle for LCD_CS/s1, which is an e_assign
  assign LCD_CS_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign LCD_CS_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign LCD_CS_s1_master_qreq_vector = 1;

  //LCD_CS_s1_reset_n assignment, which is an e_assign
  assign LCD_CS_s1_reset_n = reset_n;

  assign LCD_CS_s1_chipselect = cpu_0_data_master_granted_LCD_CS_s1;
  //LCD_CS_s1_firsttransfer first transaction, which is an e_assign
  assign LCD_CS_s1_firsttransfer = LCD_CS_s1_begins_xfer ? LCD_CS_s1_unreg_firsttransfer : LCD_CS_s1_reg_firsttransfer;

  //LCD_CS_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign LCD_CS_s1_unreg_firsttransfer = ~(LCD_CS_s1_slavearbiterlockenable & LCD_CS_s1_any_continuerequest);

  //LCD_CS_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          LCD_CS_s1_reg_firsttransfer <= 1'b1;
      else if (LCD_CS_s1_begins_xfer)
          LCD_CS_s1_reg_firsttransfer <= LCD_CS_s1_unreg_firsttransfer;
    end


  //LCD_CS_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign LCD_CS_s1_beginbursttransfer_internal = LCD_CS_s1_begins_xfer;

  //~LCD_CS_s1_write_n assignment, which is an e_mux
  assign LCD_CS_s1_write_n = ~(cpu_0_data_master_granted_LCD_CS_s1 & cpu_0_data_master_write);

  assign shifted_address_to_LCD_CS_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //LCD_CS_s1_address mux, which is an e_mux
  assign LCD_CS_s1_address = shifted_address_to_LCD_CS_s1_from_cpu_0_data_master >> 2;

  //d1_LCD_CS_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_LCD_CS_s1_end_xfer <= 1;
      else 
        d1_LCD_CS_s1_end_xfer <= LCD_CS_s1_end_xfer;
    end


  //LCD_CS_s1_waits_for_read in a cycle, which is an e_mux
  assign LCD_CS_s1_waits_for_read = LCD_CS_s1_in_a_read_cycle & LCD_CS_s1_begins_xfer;

  //LCD_CS_s1_in_a_read_cycle assignment, which is an e_assign
  assign LCD_CS_s1_in_a_read_cycle = cpu_0_data_master_granted_LCD_CS_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = LCD_CS_s1_in_a_read_cycle;

  //LCD_CS_s1_waits_for_write in a cycle, which is an e_mux
  assign LCD_CS_s1_waits_for_write = LCD_CS_s1_in_a_write_cycle & 0;

  //LCD_CS_s1_in_a_write_cycle assignment, which is an e_assign
  assign LCD_CS_s1_in_a_write_cycle = cpu_0_data_master_granted_LCD_CS_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = LCD_CS_s1_in_a_write_cycle;

  assign wait_for_LCD_CS_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //LCD_CS/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module LCD_DATA_s1_arbitrator (
                                // inputs:
                                 LCD_DATA_s1_readdata,
                                 clk,
                                 cpu_0_data_master_address_to_slave,
                                 cpu_0_data_master_latency_counter,
                                 cpu_0_data_master_read,
                                 cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                 cpu_0_data_master_write,
                                 cpu_0_data_master_writedata,
                                 reset_n,

                                // outputs:
                                 LCD_DATA_s1_address,
                                 LCD_DATA_s1_chipselect,
                                 LCD_DATA_s1_readdata_from_sa,
                                 LCD_DATA_s1_reset_n,
                                 LCD_DATA_s1_write_n,
                                 LCD_DATA_s1_writedata,
                                 cpu_0_data_master_granted_LCD_DATA_s1,
                                 cpu_0_data_master_qualified_request_LCD_DATA_s1,
                                 cpu_0_data_master_read_data_valid_LCD_DATA_s1,
                                 cpu_0_data_master_requests_LCD_DATA_s1,
                                 d1_LCD_DATA_s1_end_xfer
                              )
;

  output  [  1: 0] LCD_DATA_s1_address;
  output           LCD_DATA_s1_chipselect;
  output  [ 31: 0] LCD_DATA_s1_readdata_from_sa;
  output           LCD_DATA_s1_reset_n;
  output           LCD_DATA_s1_write_n;
  output  [ 31: 0] LCD_DATA_s1_writedata;
  output           cpu_0_data_master_granted_LCD_DATA_s1;
  output           cpu_0_data_master_qualified_request_LCD_DATA_s1;
  output           cpu_0_data_master_read_data_valid_LCD_DATA_s1;
  output           cpu_0_data_master_requests_LCD_DATA_s1;
  output           d1_LCD_DATA_s1_end_xfer;
  input   [ 31: 0] LCD_DATA_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] LCD_DATA_s1_address;
  wire             LCD_DATA_s1_allgrants;
  wire             LCD_DATA_s1_allow_new_arb_cycle;
  wire             LCD_DATA_s1_any_bursting_master_saved_grant;
  wire             LCD_DATA_s1_any_continuerequest;
  wire             LCD_DATA_s1_arb_counter_enable;
  reg     [  1: 0] LCD_DATA_s1_arb_share_counter;
  wire    [  1: 0] LCD_DATA_s1_arb_share_counter_next_value;
  wire    [  1: 0] LCD_DATA_s1_arb_share_set_values;
  wire             LCD_DATA_s1_beginbursttransfer_internal;
  wire             LCD_DATA_s1_begins_xfer;
  wire             LCD_DATA_s1_chipselect;
  wire             LCD_DATA_s1_end_xfer;
  wire             LCD_DATA_s1_firsttransfer;
  wire             LCD_DATA_s1_grant_vector;
  wire             LCD_DATA_s1_in_a_read_cycle;
  wire             LCD_DATA_s1_in_a_write_cycle;
  wire             LCD_DATA_s1_master_qreq_vector;
  wire             LCD_DATA_s1_non_bursting_master_requests;
  wire    [ 31: 0] LCD_DATA_s1_readdata_from_sa;
  reg              LCD_DATA_s1_reg_firsttransfer;
  wire             LCD_DATA_s1_reset_n;
  reg              LCD_DATA_s1_slavearbiterlockenable;
  wire             LCD_DATA_s1_slavearbiterlockenable2;
  wire             LCD_DATA_s1_unreg_firsttransfer;
  wire             LCD_DATA_s1_waits_for_read;
  wire             LCD_DATA_s1_waits_for_write;
  wire             LCD_DATA_s1_write_n;
  wire    [ 31: 0] LCD_DATA_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_LCD_DATA_s1;
  wire             cpu_0_data_master_qualified_request_LCD_DATA_s1;
  wire             cpu_0_data_master_read_data_valid_LCD_DATA_s1;
  wire             cpu_0_data_master_requests_LCD_DATA_s1;
  wire             cpu_0_data_master_saved_grant_LCD_DATA_s1;
  reg              d1_LCD_DATA_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_LCD_DATA_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_LCD_DATA_s1_from_cpu_0_data_master;
  wire             wait_for_LCD_DATA_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~LCD_DATA_s1_end_xfer;
    end


  assign LCD_DATA_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_LCD_DATA_s1));
  //assign LCD_DATA_s1_readdata_from_sa = LCD_DATA_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign LCD_DATA_s1_readdata_from_sa = LCD_DATA_s1_readdata;

  assign cpu_0_data_master_requests_LCD_DATA_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002060) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //LCD_DATA_s1_arb_share_counter set values, which is an e_mux
  assign LCD_DATA_s1_arb_share_set_values = 1;

  //LCD_DATA_s1_non_bursting_master_requests mux, which is an e_mux
  assign LCD_DATA_s1_non_bursting_master_requests = cpu_0_data_master_requests_LCD_DATA_s1;

  //LCD_DATA_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign LCD_DATA_s1_any_bursting_master_saved_grant = 0;

  //LCD_DATA_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign LCD_DATA_s1_arb_share_counter_next_value = LCD_DATA_s1_firsttransfer ? (LCD_DATA_s1_arb_share_set_values - 1) : |LCD_DATA_s1_arb_share_counter ? (LCD_DATA_s1_arb_share_counter - 1) : 0;

  //LCD_DATA_s1_allgrants all slave grants, which is an e_mux
  assign LCD_DATA_s1_allgrants = |LCD_DATA_s1_grant_vector;

  //LCD_DATA_s1_end_xfer assignment, which is an e_assign
  assign LCD_DATA_s1_end_xfer = ~(LCD_DATA_s1_waits_for_read | LCD_DATA_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_LCD_DATA_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_LCD_DATA_s1 = LCD_DATA_s1_end_xfer & (~LCD_DATA_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //LCD_DATA_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign LCD_DATA_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_LCD_DATA_s1 & LCD_DATA_s1_allgrants) | (end_xfer_arb_share_counter_term_LCD_DATA_s1 & ~LCD_DATA_s1_non_bursting_master_requests);

  //LCD_DATA_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          LCD_DATA_s1_arb_share_counter <= 0;
      else if (LCD_DATA_s1_arb_counter_enable)
          LCD_DATA_s1_arb_share_counter <= LCD_DATA_s1_arb_share_counter_next_value;
    end


  //LCD_DATA_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          LCD_DATA_s1_slavearbiterlockenable <= 0;
      else if ((|LCD_DATA_s1_master_qreq_vector & end_xfer_arb_share_counter_term_LCD_DATA_s1) | (end_xfer_arb_share_counter_term_LCD_DATA_s1 & ~LCD_DATA_s1_non_bursting_master_requests))
          LCD_DATA_s1_slavearbiterlockenable <= |LCD_DATA_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master LCD_DATA/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = LCD_DATA_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //LCD_DATA_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign LCD_DATA_s1_slavearbiterlockenable2 = |LCD_DATA_s1_arb_share_counter_next_value;

  //cpu_0/data_master LCD_DATA/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = LCD_DATA_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //LCD_DATA_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign LCD_DATA_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_LCD_DATA_s1 = cpu_0_data_master_requests_LCD_DATA_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_LCD_DATA_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_LCD_DATA_s1 = cpu_0_data_master_granted_LCD_DATA_s1 & cpu_0_data_master_read & ~LCD_DATA_s1_waits_for_read;

  //LCD_DATA_s1_writedata mux, which is an e_mux
  assign LCD_DATA_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_LCD_DATA_s1 = cpu_0_data_master_qualified_request_LCD_DATA_s1;

  //cpu_0/data_master saved-grant LCD_DATA/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_LCD_DATA_s1 = cpu_0_data_master_requests_LCD_DATA_s1;

  //allow new arb cycle for LCD_DATA/s1, which is an e_assign
  assign LCD_DATA_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign LCD_DATA_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign LCD_DATA_s1_master_qreq_vector = 1;

  //LCD_DATA_s1_reset_n assignment, which is an e_assign
  assign LCD_DATA_s1_reset_n = reset_n;

  assign LCD_DATA_s1_chipselect = cpu_0_data_master_granted_LCD_DATA_s1;
  //LCD_DATA_s1_firsttransfer first transaction, which is an e_assign
  assign LCD_DATA_s1_firsttransfer = LCD_DATA_s1_begins_xfer ? LCD_DATA_s1_unreg_firsttransfer : LCD_DATA_s1_reg_firsttransfer;

  //LCD_DATA_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign LCD_DATA_s1_unreg_firsttransfer = ~(LCD_DATA_s1_slavearbiterlockenable & LCD_DATA_s1_any_continuerequest);

  //LCD_DATA_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          LCD_DATA_s1_reg_firsttransfer <= 1'b1;
      else if (LCD_DATA_s1_begins_xfer)
          LCD_DATA_s1_reg_firsttransfer <= LCD_DATA_s1_unreg_firsttransfer;
    end


  //LCD_DATA_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign LCD_DATA_s1_beginbursttransfer_internal = LCD_DATA_s1_begins_xfer;

  //~LCD_DATA_s1_write_n assignment, which is an e_mux
  assign LCD_DATA_s1_write_n = ~(cpu_0_data_master_granted_LCD_DATA_s1 & cpu_0_data_master_write);

  assign shifted_address_to_LCD_DATA_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //LCD_DATA_s1_address mux, which is an e_mux
  assign LCD_DATA_s1_address = shifted_address_to_LCD_DATA_s1_from_cpu_0_data_master >> 2;

  //d1_LCD_DATA_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_LCD_DATA_s1_end_xfer <= 1;
      else 
        d1_LCD_DATA_s1_end_xfer <= LCD_DATA_s1_end_xfer;
    end


  //LCD_DATA_s1_waits_for_read in a cycle, which is an e_mux
  assign LCD_DATA_s1_waits_for_read = LCD_DATA_s1_in_a_read_cycle & LCD_DATA_s1_begins_xfer;

  //LCD_DATA_s1_in_a_read_cycle assignment, which is an e_assign
  assign LCD_DATA_s1_in_a_read_cycle = cpu_0_data_master_granted_LCD_DATA_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = LCD_DATA_s1_in_a_read_cycle;

  //LCD_DATA_s1_waits_for_write in a cycle, which is an e_mux
  assign LCD_DATA_s1_waits_for_write = LCD_DATA_s1_in_a_write_cycle & 0;

  //LCD_DATA_s1_in_a_write_cycle assignment, which is an e_assign
  assign LCD_DATA_s1_in_a_write_cycle = cpu_0_data_master_granted_LCD_DATA_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = LCD_DATA_s1_in_a_write_cycle;

  assign wait_for_LCD_DATA_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //LCD_DATA/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module LCD_RD_s1_arbitrator (
                              // inputs:
                               LCD_RD_s1_readdata,
                               clk,
                               cpu_0_data_master_address_to_slave,
                               cpu_0_data_master_latency_counter,
                               cpu_0_data_master_read,
                               cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                               cpu_0_data_master_write,
                               cpu_0_data_master_writedata,
                               reset_n,

                              // outputs:
                               LCD_RD_s1_address,
                               LCD_RD_s1_chipselect,
                               LCD_RD_s1_readdata_from_sa,
                               LCD_RD_s1_reset_n,
                               LCD_RD_s1_write_n,
                               LCD_RD_s1_writedata,
                               cpu_0_data_master_granted_LCD_RD_s1,
                               cpu_0_data_master_qualified_request_LCD_RD_s1,
                               cpu_0_data_master_read_data_valid_LCD_RD_s1,
                               cpu_0_data_master_requests_LCD_RD_s1,
                               d1_LCD_RD_s1_end_xfer
                            )
;

  output  [  1: 0] LCD_RD_s1_address;
  output           LCD_RD_s1_chipselect;
  output  [ 31: 0] LCD_RD_s1_readdata_from_sa;
  output           LCD_RD_s1_reset_n;
  output           LCD_RD_s1_write_n;
  output  [ 31: 0] LCD_RD_s1_writedata;
  output           cpu_0_data_master_granted_LCD_RD_s1;
  output           cpu_0_data_master_qualified_request_LCD_RD_s1;
  output           cpu_0_data_master_read_data_valid_LCD_RD_s1;
  output           cpu_0_data_master_requests_LCD_RD_s1;
  output           d1_LCD_RD_s1_end_xfer;
  input   [ 31: 0] LCD_RD_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] LCD_RD_s1_address;
  wire             LCD_RD_s1_allgrants;
  wire             LCD_RD_s1_allow_new_arb_cycle;
  wire             LCD_RD_s1_any_bursting_master_saved_grant;
  wire             LCD_RD_s1_any_continuerequest;
  wire             LCD_RD_s1_arb_counter_enable;
  reg     [  1: 0] LCD_RD_s1_arb_share_counter;
  wire    [  1: 0] LCD_RD_s1_arb_share_counter_next_value;
  wire    [  1: 0] LCD_RD_s1_arb_share_set_values;
  wire             LCD_RD_s1_beginbursttransfer_internal;
  wire             LCD_RD_s1_begins_xfer;
  wire             LCD_RD_s1_chipselect;
  wire             LCD_RD_s1_end_xfer;
  wire             LCD_RD_s1_firsttransfer;
  wire             LCD_RD_s1_grant_vector;
  wire             LCD_RD_s1_in_a_read_cycle;
  wire             LCD_RD_s1_in_a_write_cycle;
  wire             LCD_RD_s1_master_qreq_vector;
  wire             LCD_RD_s1_non_bursting_master_requests;
  wire    [ 31: 0] LCD_RD_s1_readdata_from_sa;
  reg              LCD_RD_s1_reg_firsttransfer;
  wire             LCD_RD_s1_reset_n;
  reg              LCD_RD_s1_slavearbiterlockenable;
  wire             LCD_RD_s1_slavearbiterlockenable2;
  wire             LCD_RD_s1_unreg_firsttransfer;
  wire             LCD_RD_s1_waits_for_read;
  wire             LCD_RD_s1_waits_for_write;
  wire             LCD_RD_s1_write_n;
  wire    [ 31: 0] LCD_RD_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_LCD_RD_s1;
  wire             cpu_0_data_master_qualified_request_LCD_RD_s1;
  wire             cpu_0_data_master_read_data_valid_LCD_RD_s1;
  wire             cpu_0_data_master_requests_LCD_RD_s1;
  wire             cpu_0_data_master_saved_grant_LCD_RD_s1;
  reg              d1_LCD_RD_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_LCD_RD_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_LCD_RD_s1_from_cpu_0_data_master;
  wire             wait_for_LCD_RD_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~LCD_RD_s1_end_xfer;
    end


  assign LCD_RD_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_LCD_RD_s1));
  //assign LCD_RD_s1_readdata_from_sa = LCD_RD_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign LCD_RD_s1_readdata_from_sa = LCD_RD_s1_readdata;

  assign cpu_0_data_master_requests_LCD_RD_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002090) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //LCD_RD_s1_arb_share_counter set values, which is an e_mux
  assign LCD_RD_s1_arb_share_set_values = 1;

  //LCD_RD_s1_non_bursting_master_requests mux, which is an e_mux
  assign LCD_RD_s1_non_bursting_master_requests = cpu_0_data_master_requests_LCD_RD_s1;

  //LCD_RD_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign LCD_RD_s1_any_bursting_master_saved_grant = 0;

  //LCD_RD_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign LCD_RD_s1_arb_share_counter_next_value = LCD_RD_s1_firsttransfer ? (LCD_RD_s1_arb_share_set_values - 1) : |LCD_RD_s1_arb_share_counter ? (LCD_RD_s1_arb_share_counter - 1) : 0;

  //LCD_RD_s1_allgrants all slave grants, which is an e_mux
  assign LCD_RD_s1_allgrants = |LCD_RD_s1_grant_vector;

  //LCD_RD_s1_end_xfer assignment, which is an e_assign
  assign LCD_RD_s1_end_xfer = ~(LCD_RD_s1_waits_for_read | LCD_RD_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_LCD_RD_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_LCD_RD_s1 = LCD_RD_s1_end_xfer & (~LCD_RD_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //LCD_RD_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign LCD_RD_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_LCD_RD_s1 & LCD_RD_s1_allgrants) | (end_xfer_arb_share_counter_term_LCD_RD_s1 & ~LCD_RD_s1_non_bursting_master_requests);

  //LCD_RD_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          LCD_RD_s1_arb_share_counter <= 0;
      else if (LCD_RD_s1_arb_counter_enable)
          LCD_RD_s1_arb_share_counter <= LCD_RD_s1_arb_share_counter_next_value;
    end


  //LCD_RD_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          LCD_RD_s1_slavearbiterlockenable <= 0;
      else if ((|LCD_RD_s1_master_qreq_vector & end_xfer_arb_share_counter_term_LCD_RD_s1) | (end_xfer_arb_share_counter_term_LCD_RD_s1 & ~LCD_RD_s1_non_bursting_master_requests))
          LCD_RD_s1_slavearbiterlockenable <= |LCD_RD_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master LCD_RD/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = LCD_RD_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //LCD_RD_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign LCD_RD_s1_slavearbiterlockenable2 = |LCD_RD_s1_arb_share_counter_next_value;

  //cpu_0/data_master LCD_RD/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = LCD_RD_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //LCD_RD_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign LCD_RD_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_LCD_RD_s1 = cpu_0_data_master_requests_LCD_RD_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_LCD_RD_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_LCD_RD_s1 = cpu_0_data_master_granted_LCD_RD_s1 & cpu_0_data_master_read & ~LCD_RD_s1_waits_for_read;

  //LCD_RD_s1_writedata mux, which is an e_mux
  assign LCD_RD_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_LCD_RD_s1 = cpu_0_data_master_qualified_request_LCD_RD_s1;

  //cpu_0/data_master saved-grant LCD_RD/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_LCD_RD_s1 = cpu_0_data_master_requests_LCD_RD_s1;

  //allow new arb cycle for LCD_RD/s1, which is an e_assign
  assign LCD_RD_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign LCD_RD_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign LCD_RD_s1_master_qreq_vector = 1;

  //LCD_RD_s1_reset_n assignment, which is an e_assign
  assign LCD_RD_s1_reset_n = reset_n;

  assign LCD_RD_s1_chipselect = cpu_0_data_master_granted_LCD_RD_s1;
  //LCD_RD_s1_firsttransfer first transaction, which is an e_assign
  assign LCD_RD_s1_firsttransfer = LCD_RD_s1_begins_xfer ? LCD_RD_s1_unreg_firsttransfer : LCD_RD_s1_reg_firsttransfer;

  //LCD_RD_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign LCD_RD_s1_unreg_firsttransfer = ~(LCD_RD_s1_slavearbiterlockenable & LCD_RD_s1_any_continuerequest);

  //LCD_RD_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          LCD_RD_s1_reg_firsttransfer <= 1'b1;
      else if (LCD_RD_s1_begins_xfer)
          LCD_RD_s1_reg_firsttransfer <= LCD_RD_s1_unreg_firsttransfer;
    end


  //LCD_RD_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign LCD_RD_s1_beginbursttransfer_internal = LCD_RD_s1_begins_xfer;

  //~LCD_RD_s1_write_n assignment, which is an e_mux
  assign LCD_RD_s1_write_n = ~(cpu_0_data_master_granted_LCD_RD_s1 & cpu_0_data_master_write);

  assign shifted_address_to_LCD_RD_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //LCD_RD_s1_address mux, which is an e_mux
  assign LCD_RD_s1_address = shifted_address_to_LCD_RD_s1_from_cpu_0_data_master >> 2;

  //d1_LCD_RD_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_LCD_RD_s1_end_xfer <= 1;
      else 
        d1_LCD_RD_s1_end_xfer <= LCD_RD_s1_end_xfer;
    end


  //LCD_RD_s1_waits_for_read in a cycle, which is an e_mux
  assign LCD_RD_s1_waits_for_read = LCD_RD_s1_in_a_read_cycle & LCD_RD_s1_begins_xfer;

  //LCD_RD_s1_in_a_read_cycle assignment, which is an e_assign
  assign LCD_RD_s1_in_a_read_cycle = cpu_0_data_master_granted_LCD_RD_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = LCD_RD_s1_in_a_read_cycle;

  //LCD_RD_s1_waits_for_write in a cycle, which is an e_mux
  assign LCD_RD_s1_waits_for_write = LCD_RD_s1_in_a_write_cycle & 0;

  //LCD_RD_s1_in_a_write_cycle assignment, which is an e_assign
  assign LCD_RD_s1_in_a_write_cycle = cpu_0_data_master_granted_LCD_RD_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = LCD_RD_s1_in_a_write_cycle;

  assign wait_for_LCD_RD_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //LCD_RD/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module LCD_RS_s1_arbitrator (
                              // inputs:
                               LCD_RS_s1_readdata,
                               clk,
                               cpu_0_data_master_address_to_slave,
                               cpu_0_data_master_latency_counter,
                               cpu_0_data_master_read,
                               cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                               cpu_0_data_master_write,
                               cpu_0_data_master_writedata,
                               reset_n,

                              // outputs:
                               LCD_RS_s1_address,
                               LCD_RS_s1_chipselect,
                               LCD_RS_s1_readdata_from_sa,
                               LCD_RS_s1_reset_n,
                               LCD_RS_s1_write_n,
                               LCD_RS_s1_writedata,
                               cpu_0_data_master_granted_LCD_RS_s1,
                               cpu_0_data_master_qualified_request_LCD_RS_s1,
                               cpu_0_data_master_read_data_valid_LCD_RS_s1,
                               cpu_0_data_master_requests_LCD_RS_s1,
                               d1_LCD_RS_s1_end_xfer
                            )
;

  output  [  1: 0] LCD_RS_s1_address;
  output           LCD_RS_s1_chipselect;
  output  [ 31: 0] LCD_RS_s1_readdata_from_sa;
  output           LCD_RS_s1_reset_n;
  output           LCD_RS_s1_write_n;
  output  [ 31: 0] LCD_RS_s1_writedata;
  output           cpu_0_data_master_granted_LCD_RS_s1;
  output           cpu_0_data_master_qualified_request_LCD_RS_s1;
  output           cpu_0_data_master_read_data_valid_LCD_RS_s1;
  output           cpu_0_data_master_requests_LCD_RS_s1;
  output           d1_LCD_RS_s1_end_xfer;
  input   [ 31: 0] LCD_RS_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] LCD_RS_s1_address;
  wire             LCD_RS_s1_allgrants;
  wire             LCD_RS_s1_allow_new_arb_cycle;
  wire             LCD_RS_s1_any_bursting_master_saved_grant;
  wire             LCD_RS_s1_any_continuerequest;
  wire             LCD_RS_s1_arb_counter_enable;
  reg     [  1: 0] LCD_RS_s1_arb_share_counter;
  wire    [  1: 0] LCD_RS_s1_arb_share_counter_next_value;
  wire    [  1: 0] LCD_RS_s1_arb_share_set_values;
  wire             LCD_RS_s1_beginbursttransfer_internal;
  wire             LCD_RS_s1_begins_xfer;
  wire             LCD_RS_s1_chipselect;
  wire             LCD_RS_s1_end_xfer;
  wire             LCD_RS_s1_firsttransfer;
  wire             LCD_RS_s1_grant_vector;
  wire             LCD_RS_s1_in_a_read_cycle;
  wire             LCD_RS_s1_in_a_write_cycle;
  wire             LCD_RS_s1_master_qreq_vector;
  wire             LCD_RS_s1_non_bursting_master_requests;
  wire    [ 31: 0] LCD_RS_s1_readdata_from_sa;
  reg              LCD_RS_s1_reg_firsttransfer;
  wire             LCD_RS_s1_reset_n;
  reg              LCD_RS_s1_slavearbiterlockenable;
  wire             LCD_RS_s1_slavearbiterlockenable2;
  wire             LCD_RS_s1_unreg_firsttransfer;
  wire             LCD_RS_s1_waits_for_read;
  wire             LCD_RS_s1_waits_for_write;
  wire             LCD_RS_s1_write_n;
  wire    [ 31: 0] LCD_RS_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_LCD_RS_s1;
  wire             cpu_0_data_master_qualified_request_LCD_RS_s1;
  wire             cpu_0_data_master_read_data_valid_LCD_RS_s1;
  wire             cpu_0_data_master_requests_LCD_RS_s1;
  wire             cpu_0_data_master_saved_grant_LCD_RS_s1;
  reg              d1_LCD_RS_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_LCD_RS_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_LCD_RS_s1_from_cpu_0_data_master;
  wire             wait_for_LCD_RS_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~LCD_RS_s1_end_xfer;
    end


  assign LCD_RS_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_LCD_RS_s1));
  //assign LCD_RS_s1_readdata_from_sa = LCD_RS_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign LCD_RS_s1_readdata_from_sa = LCD_RS_s1_readdata;

  assign cpu_0_data_master_requests_LCD_RS_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002080) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //LCD_RS_s1_arb_share_counter set values, which is an e_mux
  assign LCD_RS_s1_arb_share_set_values = 1;

  //LCD_RS_s1_non_bursting_master_requests mux, which is an e_mux
  assign LCD_RS_s1_non_bursting_master_requests = cpu_0_data_master_requests_LCD_RS_s1;

  //LCD_RS_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign LCD_RS_s1_any_bursting_master_saved_grant = 0;

  //LCD_RS_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign LCD_RS_s1_arb_share_counter_next_value = LCD_RS_s1_firsttransfer ? (LCD_RS_s1_arb_share_set_values - 1) : |LCD_RS_s1_arb_share_counter ? (LCD_RS_s1_arb_share_counter - 1) : 0;

  //LCD_RS_s1_allgrants all slave grants, which is an e_mux
  assign LCD_RS_s1_allgrants = |LCD_RS_s1_grant_vector;

  //LCD_RS_s1_end_xfer assignment, which is an e_assign
  assign LCD_RS_s1_end_xfer = ~(LCD_RS_s1_waits_for_read | LCD_RS_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_LCD_RS_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_LCD_RS_s1 = LCD_RS_s1_end_xfer & (~LCD_RS_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //LCD_RS_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign LCD_RS_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_LCD_RS_s1 & LCD_RS_s1_allgrants) | (end_xfer_arb_share_counter_term_LCD_RS_s1 & ~LCD_RS_s1_non_bursting_master_requests);

  //LCD_RS_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          LCD_RS_s1_arb_share_counter <= 0;
      else if (LCD_RS_s1_arb_counter_enable)
          LCD_RS_s1_arb_share_counter <= LCD_RS_s1_arb_share_counter_next_value;
    end


  //LCD_RS_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          LCD_RS_s1_slavearbiterlockenable <= 0;
      else if ((|LCD_RS_s1_master_qreq_vector & end_xfer_arb_share_counter_term_LCD_RS_s1) | (end_xfer_arb_share_counter_term_LCD_RS_s1 & ~LCD_RS_s1_non_bursting_master_requests))
          LCD_RS_s1_slavearbiterlockenable <= |LCD_RS_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master LCD_RS/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = LCD_RS_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //LCD_RS_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign LCD_RS_s1_slavearbiterlockenable2 = |LCD_RS_s1_arb_share_counter_next_value;

  //cpu_0/data_master LCD_RS/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = LCD_RS_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //LCD_RS_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign LCD_RS_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_LCD_RS_s1 = cpu_0_data_master_requests_LCD_RS_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_LCD_RS_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_LCD_RS_s1 = cpu_0_data_master_granted_LCD_RS_s1 & cpu_0_data_master_read & ~LCD_RS_s1_waits_for_read;

  //LCD_RS_s1_writedata mux, which is an e_mux
  assign LCD_RS_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_LCD_RS_s1 = cpu_0_data_master_qualified_request_LCD_RS_s1;

  //cpu_0/data_master saved-grant LCD_RS/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_LCD_RS_s1 = cpu_0_data_master_requests_LCD_RS_s1;

  //allow new arb cycle for LCD_RS/s1, which is an e_assign
  assign LCD_RS_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign LCD_RS_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign LCD_RS_s1_master_qreq_vector = 1;

  //LCD_RS_s1_reset_n assignment, which is an e_assign
  assign LCD_RS_s1_reset_n = reset_n;

  assign LCD_RS_s1_chipselect = cpu_0_data_master_granted_LCD_RS_s1;
  //LCD_RS_s1_firsttransfer first transaction, which is an e_assign
  assign LCD_RS_s1_firsttransfer = LCD_RS_s1_begins_xfer ? LCD_RS_s1_unreg_firsttransfer : LCD_RS_s1_reg_firsttransfer;

  //LCD_RS_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign LCD_RS_s1_unreg_firsttransfer = ~(LCD_RS_s1_slavearbiterlockenable & LCD_RS_s1_any_continuerequest);

  //LCD_RS_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          LCD_RS_s1_reg_firsttransfer <= 1'b1;
      else if (LCD_RS_s1_begins_xfer)
          LCD_RS_s1_reg_firsttransfer <= LCD_RS_s1_unreg_firsttransfer;
    end


  //LCD_RS_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign LCD_RS_s1_beginbursttransfer_internal = LCD_RS_s1_begins_xfer;

  //~LCD_RS_s1_write_n assignment, which is an e_mux
  assign LCD_RS_s1_write_n = ~(cpu_0_data_master_granted_LCD_RS_s1 & cpu_0_data_master_write);

  assign shifted_address_to_LCD_RS_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //LCD_RS_s1_address mux, which is an e_mux
  assign LCD_RS_s1_address = shifted_address_to_LCD_RS_s1_from_cpu_0_data_master >> 2;

  //d1_LCD_RS_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_LCD_RS_s1_end_xfer <= 1;
      else 
        d1_LCD_RS_s1_end_xfer <= LCD_RS_s1_end_xfer;
    end


  //LCD_RS_s1_waits_for_read in a cycle, which is an e_mux
  assign LCD_RS_s1_waits_for_read = LCD_RS_s1_in_a_read_cycle & LCD_RS_s1_begins_xfer;

  //LCD_RS_s1_in_a_read_cycle assignment, which is an e_assign
  assign LCD_RS_s1_in_a_read_cycle = cpu_0_data_master_granted_LCD_RS_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = LCD_RS_s1_in_a_read_cycle;

  //LCD_RS_s1_waits_for_write in a cycle, which is an e_mux
  assign LCD_RS_s1_waits_for_write = LCD_RS_s1_in_a_write_cycle & 0;

  //LCD_RS_s1_in_a_write_cycle assignment, which is an e_assign
  assign LCD_RS_s1_in_a_write_cycle = cpu_0_data_master_granted_LCD_RS_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = LCD_RS_s1_in_a_write_cycle;

  assign wait_for_LCD_RS_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //LCD_RS/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module LCD_RST_s1_arbitrator (
                               // inputs:
                                LCD_RST_s1_readdata,
                                clk,
                                cpu_0_data_master_address_to_slave,
                                cpu_0_data_master_latency_counter,
                                cpu_0_data_master_read,
                                cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                cpu_0_data_master_write,
                                cpu_0_data_master_writedata,
                                reset_n,

                               // outputs:
                                LCD_RST_s1_address,
                                LCD_RST_s1_chipselect,
                                LCD_RST_s1_readdata_from_sa,
                                LCD_RST_s1_reset_n,
                                LCD_RST_s1_write_n,
                                LCD_RST_s1_writedata,
                                cpu_0_data_master_granted_LCD_RST_s1,
                                cpu_0_data_master_qualified_request_LCD_RST_s1,
                                cpu_0_data_master_read_data_valid_LCD_RST_s1,
                                cpu_0_data_master_requests_LCD_RST_s1,
                                d1_LCD_RST_s1_end_xfer
                             )
;

  output  [  1: 0] LCD_RST_s1_address;
  output           LCD_RST_s1_chipselect;
  output  [ 31: 0] LCD_RST_s1_readdata_from_sa;
  output           LCD_RST_s1_reset_n;
  output           LCD_RST_s1_write_n;
  output  [ 31: 0] LCD_RST_s1_writedata;
  output           cpu_0_data_master_granted_LCD_RST_s1;
  output           cpu_0_data_master_qualified_request_LCD_RST_s1;
  output           cpu_0_data_master_read_data_valid_LCD_RST_s1;
  output           cpu_0_data_master_requests_LCD_RST_s1;
  output           d1_LCD_RST_s1_end_xfer;
  input   [ 31: 0] LCD_RST_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] LCD_RST_s1_address;
  wire             LCD_RST_s1_allgrants;
  wire             LCD_RST_s1_allow_new_arb_cycle;
  wire             LCD_RST_s1_any_bursting_master_saved_grant;
  wire             LCD_RST_s1_any_continuerequest;
  wire             LCD_RST_s1_arb_counter_enable;
  reg     [  1: 0] LCD_RST_s1_arb_share_counter;
  wire    [  1: 0] LCD_RST_s1_arb_share_counter_next_value;
  wire    [  1: 0] LCD_RST_s1_arb_share_set_values;
  wire             LCD_RST_s1_beginbursttransfer_internal;
  wire             LCD_RST_s1_begins_xfer;
  wire             LCD_RST_s1_chipselect;
  wire             LCD_RST_s1_end_xfer;
  wire             LCD_RST_s1_firsttransfer;
  wire             LCD_RST_s1_grant_vector;
  wire             LCD_RST_s1_in_a_read_cycle;
  wire             LCD_RST_s1_in_a_write_cycle;
  wire             LCD_RST_s1_master_qreq_vector;
  wire             LCD_RST_s1_non_bursting_master_requests;
  wire    [ 31: 0] LCD_RST_s1_readdata_from_sa;
  reg              LCD_RST_s1_reg_firsttransfer;
  wire             LCD_RST_s1_reset_n;
  reg              LCD_RST_s1_slavearbiterlockenable;
  wire             LCD_RST_s1_slavearbiterlockenable2;
  wire             LCD_RST_s1_unreg_firsttransfer;
  wire             LCD_RST_s1_waits_for_read;
  wire             LCD_RST_s1_waits_for_write;
  wire             LCD_RST_s1_write_n;
  wire    [ 31: 0] LCD_RST_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_LCD_RST_s1;
  wire             cpu_0_data_master_qualified_request_LCD_RST_s1;
  wire             cpu_0_data_master_read_data_valid_LCD_RST_s1;
  wire             cpu_0_data_master_requests_LCD_RST_s1;
  wire             cpu_0_data_master_saved_grant_LCD_RST_s1;
  reg              d1_LCD_RST_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_LCD_RST_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_LCD_RST_s1_from_cpu_0_data_master;
  wire             wait_for_LCD_RST_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~LCD_RST_s1_end_xfer;
    end


  assign LCD_RST_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_LCD_RST_s1));
  //assign LCD_RST_s1_readdata_from_sa = LCD_RST_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign LCD_RST_s1_readdata_from_sa = LCD_RST_s1_readdata;

  assign cpu_0_data_master_requests_LCD_RST_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h40020a0) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //LCD_RST_s1_arb_share_counter set values, which is an e_mux
  assign LCD_RST_s1_arb_share_set_values = 1;

  //LCD_RST_s1_non_bursting_master_requests mux, which is an e_mux
  assign LCD_RST_s1_non_bursting_master_requests = cpu_0_data_master_requests_LCD_RST_s1;

  //LCD_RST_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign LCD_RST_s1_any_bursting_master_saved_grant = 0;

  //LCD_RST_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign LCD_RST_s1_arb_share_counter_next_value = LCD_RST_s1_firsttransfer ? (LCD_RST_s1_arb_share_set_values - 1) : |LCD_RST_s1_arb_share_counter ? (LCD_RST_s1_arb_share_counter - 1) : 0;

  //LCD_RST_s1_allgrants all slave grants, which is an e_mux
  assign LCD_RST_s1_allgrants = |LCD_RST_s1_grant_vector;

  //LCD_RST_s1_end_xfer assignment, which is an e_assign
  assign LCD_RST_s1_end_xfer = ~(LCD_RST_s1_waits_for_read | LCD_RST_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_LCD_RST_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_LCD_RST_s1 = LCD_RST_s1_end_xfer & (~LCD_RST_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //LCD_RST_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign LCD_RST_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_LCD_RST_s1 & LCD_RST_s1_allgrants) | (end_xfer_arb_share_counter_term_LCD_RST_s1 & ~LCD_RST_s1_non_bursting_master_requests);

  //LCD_RST_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          LCD_RST_s1_arb_share_counter <= 0;
      else if (LCD_RST_s1_arb_counter_enable)
          LCD_RST_s1_arb_share_counter <= LCD_RST_s1_arb_share_counter_next_value;
    end


  //LCD_RST_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          LCD_RST_s1_slavearbiterlockenable <= 0;
      else if ((|LCD_RST_s1_master_qreq_vector & end_xfer_arb_share_counter_term_LCD_RST_s1) | (end_xfer_arb_share_counter_term_LCD_RST_s1 & ~LCD_RST_s1_non_bursting_master_requests))
          LCD_RST_s1_slavearbiterlockenable <= |LCD_RST_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master LCD_RST/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = LCD_RST_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //LCD_RST_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign LCD_RST_s1_slavearbiterlockenable2 = |LCD_RST_s1_arb_share_counter_next_value;

  //cpu_0/data_master LCD_RST/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = LCD_RST_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //LCD_RST_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign LCD_RST_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_LCD_RST_s1 = cpu_0_data_master_requests_LCD_RST_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_LCD_RST_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_LCD_RST_s1 = cpu_0_data_master_granted_LCD_RST_s1 & cpu_0_data_master_read & ~LCD_RST_s1_waits_for_read;

  //LCD_RST_s1_writedata mux, which is an e_mux
  assign LCD_RST_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_LCD_RST_s1 = cpu_0_data_master_qualified_request_LCD_RST_s1;

  //cpu_0/data_master saved-grant LCD_RST/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_LCD_RST_s1 = cpu_0_data_master_requests_LCD_RST_s1;

  //allow new arb cycle for LCD_RST/s1, which is an e_assign
  assign LCD_RST_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign LCD_RST_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign LCD_RST_s1_master_qreq_vector = 1;

  //LCD_RST_s1_reset_n assignment, which is an e_assign
  assign LCD_RST_s1_reset_n = reset_n;

  assign LCD_RST_s1_chipselect = cpu_0_data_master_granted_LCD_RST_s1;
  //LCD_RST_s1_firsttransfer first transaction, which is an e_assign
  assign LCD_RST_s1_firsttransfer = LCD_RST_s1_begins_xfer ? LCD_RST_s1_unreg_firsttransfer : LCD_RST_s1_reg_firsttransfer;

  //LCD_RST_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign LCD_RST_s1_unreg_firsttransfer = ~(LCD_RST_s1_slavearbiterlockenable & LCD_RST_s1_any_continuerequest);

  //LCD_RST_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          LCD_RST_s1_reg_firsttransfer <= 1'b1;
      else if (LCD_RST_s1_begins_xfer)
          LCD_RST_s1_reg_firsttransfer <= LCD_RST_s1_unreg_firsttransfer;
    end


  //LCD_RST_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign LCD_RST_s1_beginbursttransfer_internal = LCD_RST_s1_begins_xfer;

  //~LCD_RST_s1_write_n assignment, which is an e_mux
  assign LCD_RST_s1_write_n = ~(cpu_0_data_master_granted_LCD_RST_s1 & cpu_0_data_master_write);

  assign shifted_address_to_LCD_RST_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //LCD_RST_s1_address mux, which is an e_mux
  assign LCD_RST_s1_address = shifted_address_to_LCD_RST_s1_from_cpu_0_data_master >> 2;

  //d1_LCD_RST_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_LCD_RST_s1_end_xfer <= 1;
      else 
        d1_LCD_RST_s1_end_xfer <= LCD_RST_s1_end_xfer;
    end


  //LCD_RST_s1_waits_for_read in a cycle, which is an e_mux
  assign LCD_RST_s1_waits_for_read = LCD_RST_s1_in_a_read_cycle & LCD_RST_s1_begins_xfer;

  //LCD_RST_s1_in_a_read_cycle assignment, which is an e_assign
  assign LCD_RST_s1_in_a_read_cycle = cpu_0_data_master_granted_LCD_RST_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = LCD_RST_s1_in_a_read_cycle;

  //LCD_RST_s1_waits_for_write in a cycle, which is an e_mux
  assign LCD_RST_s1_waits_for_write = LCD_RST_s1_in_a_write_cycle & 0;

  //LCD_RST_s1_in_a_write_cycle assignment, which is an e_assign
  assign LCD_RST_s1_in_a_write_cycle = cpu_0_data_master_granted_LCD_RST_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = LCD_RST_s1_in_a_write_cycle;

  assign wait_for_LCD_RST_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //LCD_RST/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module LCD_WR_s1_arbitrator (
                              // inputs:
                               LCD_WR_s1_readdata,
                               clk,
                               cpu_0_data_master_address_to_slave,
                               cpu_0_data_master_latency_counter,
                               cpu_0_data_master_read,
                               cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                               cpu_0_data_master_write,
                               cpu_0_data_master_writedata,
                               reset_n,

                              // outputs:
                               LCD_WR_s1_address,
                               LCD_WR_s1_chipselect,
                               LCD_WR_s1_readdata_from_sa,
                               LCD_WR_s1_reset_n,
                               LCD_WR_s1_write_n,
                               LCD_WR_s1_writedata,
                               cpu_0_data_master_granted_LCD_WR_s1,
                               cpu_0_data_master_qualified_request_LCD_WR_s1,
                               cpu_0_data_master_read_data_valid_LCD_WR_s1,
                               cpu_0_data_master_requests_LCD_WR_s1,
                               d1_LCD_WR_s1_end_xfer
                            )
;

  output  [  1: 0] LCD_WR_s1_address;
  output           LCD_WR_s1_chipselect;
  output  [ 31: 0] LCD_WR_s1_readdata_from_sa;
  output           LCD_WR_s1_reset_n;
  output           LCD_WR_s1_write_n;
  output  [ 31: 0] LCD_WR_s1_writedata;
  output           cpu_0_data_master_granted_LCD_WR_s1;
  output           cpu_0_data_master_qualified_request_LCD_WR_s1;
  output           cpu_0_data_master_read_data_valid_LCD_WR_s1;
  output           cpu_0_data_master_requests_LCD_WR_s1;
  output           d1_LCD_WR_s1_end_xfer;
  input   [ 31: 0] LCD_WR_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] LCD_WR_s1_address;
  wire             LCD_WR_s1_allgrants;
  wire             LCD_WR_s1_allow_new_arb_cycle;
  wire             LCD_WR_s1_any_bursting_master_saved_grant;
  wire             LCD_WR_s1_any_continuerequest;
  wire             LCD_WR_s1_arb_counter_enable;
  reg     [  1: 0] LCD_WR_s1_arb_share_counter;
  wire    [  1: 0] LCD_WR_s1_arb_share_counter_next_value;
  wire    [  1: 0] LCD_WR_s1_arb_share_set_values;
  wire             LCD_WR_s1_beginbursttransfer_internal;
  wire             LCD_WR_s1_begins_xfer;
  wire             LCD_WR_s1_chipselect;
  wire             LCD_WR_s1_end_xfer;
  wire             LCD_WR_s1_firsttransfer;
  wire             LCD_WR_s1_grant_vector;
  wire             LCD_WR_s1_in_a_read_cycle;
  wire             LCD_WR_s1_in_a_write_cycle;
  wire             LCD_WR_s1_master_qreq_vector;
  wire             LCD_WR_s1_non_bursting_master_requests;
  wire    [ 31: 0] LCD_WR_s1_readdata_from_sa;
  reg              LCD_WR_s1_reg_firsttransfer;
  wire             LCD_WR_s1_reset_n;
  reg              LCD_WR_s1_slavearbiterlockenable;
  wire             LCD_WR_s1_slavearbiterlockenable2;
  wire             LCD_WR_s1_unreg_firsttransfer;
  wire             LCD_WR_s1_waits_for_read;
  wire             LCD_WR_s1_waits_for_write;
  wire             LCD_WR_s1_write_n;
  wire    [ 31: 0] LCD_WR_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_LCD_WR_s1;
  wire             cpu_0_data_master_qualified_request_LCD_WR_s1;
  wire             cpu_0_data_master_read_data_valid_LCD_WR_s1;
  wire             cpu_0_data_master_requests_LCD_WR_s1;
  wire             cpu_0_data_master_saved_grant_LCD_WR_s1;
  reg              d1_LCD_WR_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_LCD_WR_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_LCD_WR_s1_from_cpu_0_data_master;
  wire             wait_for_LCD_WR_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~LCD_WR_s1_end_xfer;
    end


  assign LCD_WR_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_LCD_WR_s1));
  //assign LCD_WR_s1_readdata_from_sa = LCD_WR_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign LCD_WR_s1_readdata_from_sa = LCD_WR_s1_readdata;

  assign cpu_0_data_master_requests_LCD_WR_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h40020b0) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //LCD_WR_s1_arb_share_counter set values, which is an e_mux
  assign LCD_WR_s1_arb_share_set_values = 1;

  //LCD_WR_s1_non_bursting_master_requests mux, which is an e_mux
  assign LCD_WR_s1_non_bursting_master_requests = cpu_0_data_master_requests_LCD_WR_s1;

  //LCD_WR_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign LCD_WR_s1_any_bursting_master_saved_grant = 0;

  //LCD_WR_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign LCD_WR_s1_arb_share_counter_next_value = LCD_WR_s1_firsttransfer ? (LCD_WR_s1_arb_share_set_values - 1) : |LCD_WR_s1_arb_share_counter ? (LCD_WR_s1_arb_share_counter - 1) : 0;

  //LCD_WR_s1_allgrants all slave grants, which is an e_mux
  assign LCD_WR_s1_allgrants = |LCD_WR_s1_grant_vector;

  //LCD_WR_s1_end_xfer assignment, which is an e_assign
  assign LCD_WR_s1_end_xfer = ~(LCD_WR_s1_waits_for_read | LCD_WR_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_LCD_WR_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_LCD_WR_s1 = LCD_WR_s1_end_xfer & (~LCD_WR_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //LCD_WR_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign LCD_WR_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_LCD_WR_s1 & LCD_WR_s1_allgrants) | (end_xfer_arb_share_counter_term_LCD_WR_s1 & ~LCD_WR_s1_non_bursting_master_requests);

  //LCD_WR_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          LCD_WR_s1_arb_share_counter <= 0;
      else if (LCD_WR_s1_arb_counter_enable)
          LCD_WR_s1_arb_share_counter <= LCD_WR_s1_arb_share_counter_next_value;
    end


  //LCD_WR_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          LCD_WR_s1_slavearbiterlockenable <= 0;
      else if ((|LCD_WR_s1_master_qreq_vector & end_xfer_arb_share_counter_term_LCD_WR_s1) | (end_xfer_arb_share_counter_term_LCD_WR_s1 & ~LCD_WR_s1_non_bursting_master_requests))
          LCD_WR_s1_slavearbiterlockenable <= |LCD_WR_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master LCD_WR/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = LCD_WR_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //LCD_WR_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign LCD_WR_s1_slavearbiterlockenable2 = |LCD_WR_s1_arb_share_counter_next_value;

  //cpu_0/data_master LCD_WR/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = LCD_WR_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //LCD_WR_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign LCD_WR_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_LCD_WR_s1 = cpu_0_data_master_requests_LCD_WR_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_LCD_WR_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_LCD_WR_s1 = cpu_0_data_master_granted_LCD_WR_s1 & cpu_0_data_master_read & ~LCD_WR_s1_waits_for_read;

  //LCD_WR_s1_writedata mux, which is an e_mux
  assign LCD_WR_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_LCD_WR_s1 = cpu_0_data_master_qualified_request_LCD_WR_s1;

  //cpu_0/data_master saved-grant LCD_WR/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_LCD_WR_s1 = cpu_0_data_master_requests_LCD_WR_s1;

  //allow new arb cycle for LCD_WR/s1, which is an e_assign
  assign LCD_WR_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign LCD_WR_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign LCD_WR_s1_master_qreq_vector = 1;

  //LCD_WR_s1_reset_n assignment, which is an e_assign
  assign LCD_WR_s1_reset_n = reset_n;

  assign LCD_WR_s1_chipselect = cpu_0_data_master_granted_LCD_WR_s1;
  //LCD_WR_s1_firsttransfer first transaction, which is an e_assign
  assign LCD_WR_s1_firsttransfer = LCD_WR_s1_begins_xfer ? LCD_WR_s1_unreg_firsttransfer : LCD_WR_s1_reg_firsttransfer;

  //LCD_WR_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign LCD_WR_s1_unreg_firsttransfer = ~(LCD_WR_s1_slavearbiterlockenable & LCD_WR_s1_any_continuerequest);

  //LCD_WR_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          LCD_WR_s1_reg_firsttransfer <= 1'b1;
      else if (LCD_WR_s1_begins_xfer)
          LCD_WR_s1_reg_firsttransfer <= LCD_WR_s1_unreg_firsttransfer;
    end


  //LCD_WR_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign LCD_WR_s1_beginbursttransfer_internal = LCD_WR_s1_begins_xfer;

  //~LCD_WR_s1_write_n assignment, which is an e_mux
  assign LCD_WR_s1_write_n = ~(cpu_0_data_master_granted_LCD_WR_s1 & cpu_0_data_master_write);

  assign shifted_address_to_LCD_WR_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //LCD_WR_s1_address mux, which is an e_mux
  assign LCD_WR_s1_address = shifted_address_to_LCD_WR_s1_from_cpu_0_data_master >> 2;

  //d1_LCD_WR_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_LCD_WR_s1_end_xfer <= 1;
      else 
        d1_LCD_WR_s1_end_xfer <= LCD_WR_s1_end_xfer;
    end


  //LCD_WR_s1_waits_for_read in a cycle, which is an e_mux
  assign LCD_WR_s1_waits_for_read = LCD_WR_s1_in_a_read_cycle & LCD_WR_s1_begins_xfer;

  //LCD_WR_s1_in_a_read_cycle assignment, which is an e_assign
  assign LCD_WR_s1_in_a_read_cycle = cpu_0_data_master_granted_LCD_WR_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = LCD_WR_s1_in_a_read_cycle;

  //LCD_WR_s1_waits_for_write in a cycle, which is an e_mux
  assign LCD_WR_s1_waits_for_write = LCD_WR_s1_in_a_write_cycle & 0;

  //LCD_WR_s1_in_a_write_cycle assignment, which is an e_assign
  assign LCD_WR_s1_in_a_write_cycle = cpu_0_data_master_granted_LCD_WR_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = LCD_WR_s1_in_a_write_cycle;

  assign wait_for_LCD_WR_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //LCD_WR/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module LED_DATA_s1_arbitrator (
                                // inputs:
                                 LED_DATA_s1_readdata,
                                 clk,
                                 cpu_0_data_master_address_to_slave,
                                 cpu_0_data_master_latency_counter,
                                 cpu_0_data_master_read,
                                 cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                 cpu_0_data_master_write,
                                 cpu_0_data_master_writedata,
                                 reset_n,

                                // outputs:
                                 LED_DATA_s1_address,
                                 LED_DATA_s1_chipselect,
                                 LED_DATA_s1_readdata_from_sa,
                                 LED_DATA_s1_reset_n,
                                 LED_DATA_s1_write_n,
                                 LED_DATA_s1_writedata,
                                 cpu_0_data_master_granted_LED_DATA_s1,
                                 cpu_0_data_master_qualified_request_LED_DATA_s1,
                                 cpu_0_data_master_read_data_valid_LED_DATA_s1,
                                 cpu_0_data_master_requests_LED_DATA_s1,
                                 d1_LED_DATA_s1_end_xfer
                              )
;

  output  [  1: 0] LED_DATA_s1_address;
  output           LED_DATA_s1_chipselect;
  output  [ 31: 0] LED_DATA_s1_readdata_from_sa;
  output           LED_DATA_s1_reset_n;
  output           LED_DATA_s1_write_n;
  output  [ 31: 0] LED_DATA_s1_writedata;
  output           cpu_0_data_master_granted_LED_DATA_s1;
  output           cpu_0_data_master_qualified_request_LED_DATA_s1;
  output           cpu_0_data_master_read_data_valid_LED_DATA_s1;
  output           cpu_0_data_master_requests_LED_DATA_s1;
  output           d1_LED_DATA_s1_end_xfer;
  input   [ 31: 0] LED_DATA_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] LED_DATA_s1_address;
  wire             LED_DATA_s1_allgrants;
  wire             LED_DATA_s1_allow_new_arb_cycle;
  wire             LED_DATA_s1_any_bursting_master_saved_grant;
  wire             LED_DATA_s1_any_continuerequest;
  wire             LED_DATA_s1_arb_counter_enable;
  reg     [  1: 0] LED_DATA_s1_arb_share_counter;
  wire    [  1: 0] LED_DATA_s1_arb_share_counter_next_value;
  wire    [  1: 0] LED_DATA_s1_arb_share_set_values;
  wire             LED_DATA_s1_beginbursttransfer_internal;
  wire             LED_DATA_s1_begins_xfer;
  wire             LED_DATA_s1_chipselect;
  wire             LED_DATA_s1_end_xfer;
  wire             LED_DATA_s1_firsttransfer;
  wire             LED_DATA_s1_grant_vector;
  wire             LED_DATA_s1_in_a_read_cycle;
  wire             LED_DATA_s1_in_a_write_cycle;
  wire             LED_DATA_s1_master_qreq_vector;
  wire             LED_DATA_s1_non_bursting_master_requests;
  wire    [ 31: 0] LED_DATA_s1_readdata_from_sa;
  reg              LED_DATA_s1_reg_firsttransfer;
  wire             LED_DATA_s1_reset_n;
  reg              LED_DATA_s1_slavearbiterlockenable;
  wire             LED_DATA_s1_slavearbiterlockenable2;
  wire             LED_DATA_s1_unreg_firsttransfer;
  wire             LED_DATA_s1_waits_for_read;
  wire             LED_DATA_s1_waits_for_write;
  wire             LED_DATA_s1_write_n;
  wire    [ 31: 0] LED_DATA_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_LED_DATA_s1;
  wire             cpu_0_data_master_qualified_request_LED_DATA_s1;
  wire             cpu_0_data_master_read_data_valid_LED_DATA_s1;
  wire             cpu_0_data_master_requests_LED_DATA_s1;
  wire             cpu_0_data_master_saved_grant_LED_DATA_s1;
  reg              d1_LED_DATA_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_LED_DATA_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_LED_DATA_s1_from_cpu_0_data_master;
  wire             wait_for_LED_DATA_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~LED_DATA_s1_end_xfer;
    end


  assign LED_DATA_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_LED_DATA_s1));
  //assign LED_DATA_s1_readdata_from_sa = LED_DATA_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign LED_DATA_s1_readdata_from_sa = LED_DATA_s1_readdata;

  assign cpu_0_data_master_requests_LED_DATA_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002120) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //LED_DATA_s1_arb_share_counter set values, which is an e_mux
  assign LED_DATA_s1_arb_share_set_values = 1;

  //LED_DATA_s1_non_bursting_master_requests mux, which is an e_mux
  assign LED_DATA_s1_non_bursting_master_requests = cpu_0_data_master_requests_LED_DATA_s1;

  //LED_DATA_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign LED_DATA_s1_any_bursting_master_saved_grant = 0;

  //LED_DATA_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign LED_DATA_s1_arb_share_counter_next_value = LED_DATA_s1_firsttransfer ? (LED_DATA_s1_arb_share_set_values - 1) : |LED_DATA_s1_arb_share_counter ? (LED_DATA_s1_arb_share_counter - 1) : 0;

  //LED_DATA_s1_allgrants all slave grants, which is an e_mux
  assign LED_DATA_s1_allgrants = |LED_DATA_s1_grant_vector;

  //LED_DATA_s1_end_xfer assignment, which is an e_assign
  assign LED_DATA_s1_end_xfer = ~(LED_DATA_s1_waits_for_read | LED_DATA_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_LED_DATA_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_LED_DATA_s1 = LED_DATA_s1_end_xfer & (~LED_DATA_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //LED_DATA_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign LED_DATA_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_LED_DATA_s1 & LED_DATA_s1_allgrants) | (end_xfer_arb_share_counter_term_LED_DATA_s1 & ~LED_DATA_s1_non_bursting_master_requests);

  //LED_DATA_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          LED_DATA_s1_arb_share_counter <= 0;
      else if (LED_DATA_s1_arb_counter_enable)
          LED_DATA_s1_arb_share_counter <= LED_DATA_s1_arb_share_counter_next_value;
    end


  //LED_DATA_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          LED_DATA_s1_slavearbiterlockenable <= 0;
      else if ((|LED_DATA_s1_master_qreq_vector & end_xfer_arb_share_counter_term_LED_DATA_s1) | (end_xfer_arb_share_counter_term_LED_DATA_s1 & ~LED_DATA_s1_non_bursting_master_requests))
          LED_DATA_s1_slavearbiterlockenable <= |LED_DATA_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master LED_DATA/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = LED_DATA_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //LED_DATA_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign LED_DATA_s1_slavearbiterlockenable2 = |LED_DATA_s1_arb_share_counter_next_value;

  //cpu_0/data_master LED_DATA/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = LED_DATA_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //LED_DATA_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign LED_DATA_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_LED_DATA_s1 = cpu_0_data_master_requests_LED_DATA_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_LED_DATA_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_LED_DATA_s1 = cpu_0_data_master_granted_LED_DATA_s1 & cpu_0_data_master_read & ~LED_DATA_s1_waits_for_read;

  //LED_DATA_s1_writedata mux, which is an e_mux
  assign LED_DATA_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_LED_DATA_s1 = cpu_0_data_master_qualified_request_LED_DATA_s1;

  //cpu_0/data_master saved-grant LED_DATA/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_LED_DATA_s1 = cpu_0_data_master_requests_LED_DATA_s1;

  //allow new arb cycle for LED_DATA/s1, which is an e_assign
  assign LED_DATA_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign LED_DATA_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign LED_DATA_s1_master_qreq_vector = 1;

  //LED_DATA_s1_reset_n assignment, which is an e_assign
  assign LED_DATA_s1_reset_n = reset_n;

  assign LED_DATA_s1_chipselect = cpu_0_data_master_granted_LED_DATA_s1;
  //LED_DATA_s1_firsttransfer first transaction, which is an e_assign
  assign LED_DATA_s1_firsttransfer = LED_DATA_s1_begins_xfer ? LED_DATA_s1_unreg_firsttransfer : LED_DATA_s1_reg_firsttransfer;

  //LED_DATA_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign LED_DATA_s1_unreg_firsttransfer = ~(LED_DATA_s1_slavearbiterlockenable & LED_DATA_s1_any_continuerequest);

  //LED_DATA_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          LED_DATA_s1_reg_firsttransfer <= 1'b1;
      else if (LED_DATA_s1_begins_xfer)
          LED_DATA_s1_reg_firsttransfer <= LED_DATA_s1_unreg_firsttransfer;
    end


  //LED_DATA_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign LED_DATA_s1_beginbursttransfer_internal = LED_DATA_s1_begins_xfer;

  //~LED_DATA_s1_write_n assignment, which is an e_mux
  assign LED_DATA_s1_write_n = ~(cpu_0_data_master_granted_LED_DATA_s1 & cpu_0_data_master_write);

  assign shifted_address_to_LED_DATA_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //LED_DATA_s1_address mux, which is an e_mux
  assign LED_DATA_s1_address = shifted_address_to_LED_DATA_s1_from_cpu_0_data_master >> 2;

  //d1_LED_DATA_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_LED_DATA_s1_end_xfer <= 1;
      else 
        d1_LED_DATA_s1_end_xfer <= LED_DATA_s1_end_xfer;
    end


  //LED_DATA_s1_waits_for_read in a cycle, which is an e_mux
  assign LED_DATA_s1_waits_for_read = LED_DATA_s1_in_a_read_cycle & LED_DATA_s1_begins_xfer;

  //LED_DATA_s1_in_a_read_cycle assignment, which is an e_assign
  assign LED_DATA_s1_in_a_read_cycle = cpu_0_data_master_granted_LED_DATA_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = LED_DATA_s1_in_a_read_cycle;

  //LED_DATA_s1_waits_for_write in a cycle, which is an e_mux
  assign LED_DATA_s1_waits_for_write = LED_DATA_s1_in_a_write_cycle & 0;

  //LED_DATA_s1_in_a_write_cycle assignment, which is an e_assign
  assign LED_DATA_s1_in_a_write_cycle = cpu_0_data_master_granted_LED_DATA_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = LED_DATA_s1_in_a_write_cycle;

  assign wait_for_LED_DATA_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //LED_DATA/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module PS2_DATA_REC_s1_arbitrator (
                                    // inputs:
                                     PS2_DATA_REC_s1_readdata,
                                     clk,
                                     cpu_0_data_master_address_to_slave,
                                     cpu_0_data_master_latency_counter,
                                     cpu_0_data_master_read,
                                     cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                     cpu_0_data_master_write,
                                     cpu_0_data_master_writedata,
                                     reset_n,

                                    // outputs:
                                     PS2_DATA_REC_s1_address,
                                     PS2_DATA_REC_s1_chipselect,
                                     PS2_DATA_REC_s1_readdata_from_sa,
                                     PS2_DATA_REC_s1_reset_n,
                                     PS2_DATA_REC_s1_write_n,
                                     PS2_DATA_REC_s1_writedata,
                                     cpu_0_data_master_granted_PS2_DATA_REC_s1,
                                     cpu_0_data_master_qualified_request_PS2_DATA_REC_s1,
                                     cpu_0_data_master_read_data_valid_PS2_DATA_REC_s1,
                                     cpu_0_data_master_requests_PS2_DATA_REC_s1,
                                     d1_PS2_DATA_REC_s1_end_xfer
                                  )
;

  output  [  1: 0] PS2_DATA_REC_s1_address;
  output           PS2_DATA_REC_s1_chipselect;
  output  [ 31: 0] PS2_DATA_REC_s1_readdata_from_sa;
  output           PS2_DATA_REC_s1_reset_n;
  output           PS2_DATA_REC_s1_write_n;
  output  [ 31: 0] PS2_DATA_REC_s1_writedata;
  output           cpu_0_data_master_granted_PS2_DATA_REC_s1;
  output           cpu_0_data_master_qualified_request_PS2_DATA_REC_s1;
  output           cpu_0_data_master_read_data_valid_PS2_DATA_REC_s1;
  output           cpu_0_data_master_requests_PS2_DATA_REC_s1;
  output           d1_PS2_DATA_REC_s1_end_xfer;
  input   [ 31: 0] PS2_DATA_REC_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] PS2_DATA_REC_s1_address;
  wire             PS2_DATA_REC_s1_allgrants;
  wire             PS2_DATA_REC_s1_allow_new_arb_cycle;
  wire             PS2_DATA_REC_s1_any_bursting_master_saved_grant;
  wire             PS2_DATA_REC_s1_any_continuerequest;
  wire             PS2_DATA_REC_s1_arb_counter_enable;
  reg     [  1: 0] PS2_DATA_REC_s1_arb_share_counter;
  wire    [  1: 0] PS2_DATA_REC_s1_arb_share_counter_next_value;
  wire    [  1: 0] PS2_DATA_REC_s1_arb_share_set_values;
  wire             PS2_DATA_REC_s1_beginbursttransfer_internal;
  wire             PS2_DATA_REC_s1_begins_xfer;
  wire             PS2_DATA_REC_s1_chipselect;
  wire             PS2_DATA_REC_s1_end_xfer;
  wire             PS2_DATA_REC_s1_firsttransfer;
  wire             PS2_DATA_REC_s1_grant_vector;
  wire             PS2_DATA_REC_s1_in_a_read_cycle;
  wire             PS2_DATA_REC_s1_in_a_write_cycle;
  wire             PS2_DATA_REC_s1_master_qreq_vector;
  wire             PS2_DATA_REC_s1_non_bursting_master_requests;
  wire    [ 31: 0] PS2_DATA_REC_s1_readdata_from_sa;
  reg              PS2_DATA_REC_s1_reg_firsttransfer;
  wire             PS2_DATA_REC_s1_reset_n;
  reg              PS2_DATA_REC_s1_slavearbiterlockenable;
  wire             PS2_DATA_REC_s1_slavearbiterlockenable2;
  wire             PS2_DATA_REC_s1_unreg_firsttransfer;
  wire             PS2_DATA_REC_s1_waits_for_read;
  wire             PS2_DATA_REC_s1_waits_for_write;
  wire             PS2_DATA_REC_s1_write_n;
  wire    [ 31: 0] PS2_DATA_REC_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_PS2_DATA_REC_s1;
  wire             cpu_0_data_master_qualified_request_PS2_DATA_REC_s1;
  wire             cpu_0_data_master_read_data_valid_PS2_DATA_REC_s1;
  wire             cpu_0_data_master_requests_PS2_DATA_REC_s1;
  wire             cpu_0_data_master_saved_grant_PS2_DATA_REC_s1;
  reg              d1_PS2_DATA_REC_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_PS2_DATA_REC_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_PS2_DATA_REC_s1_from_cpu_0_data_master;
  wire             wait_for_PS2_DATA_REC_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~PS2_DATA_REC_s1_end_xfer;
    end


  assign PS2_DATA_REC_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_PS2_DATA_REC_s1));
  //assign PS2_DATA_REC_s1_readdata_from_sa = PS2_DATA_REC_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign PS2_DATA_REC_s1_readdata_from_sa = PS2_DATA_REC_s1_readdata;

  assign cpu_0_data_master_requests_PS2_DATA_REC_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h40020d0) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //PS2_DATA_REC_s1_arb_share_counter set values, which is an e_mux
  assign PS2_DATA_REC_s1_arb_share_set_values = 1;

  //PS2_DATA_REC_s1_non_bursting_master_requests mux, which is an e_mux
  assign PS2_DATA_REC_s1_non_bursting_master_requests = cpu_0_data_master_requests_PS2_DATA_REC_s1;

  //PS2_DATA_REC_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign PS2_DATA_REC_s1_any_bursting_master_saved_grant = 0;

  //PS2_DATA_REC_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign PS2_DATA_REC_s1_arb_share_counter_next_value = PS2_DATA_REC_s1_firsttransfer ? (PS2_DATA_REC_s1_arb_share_set_values - 1) : |PS2_DATA_REC_s1_arb_share_counter ? (PS2_DATA_REC_s1_arb_share_counter - 1) : 0;

  //PS2_DATA_REC_s1_allgrants all slave grants, which is an e_mux
  assign PS2_DATA_REC_s1_allgrants = |PS2_DATA_REC_s1_grant_vector;

  //PS2_DATA_REC_s1_end_xfer assignment, which is an e_assign
  assign PS2_DATA_REC_s1_end_xfer = ~(PS2_DATA_REC_s1_waits_for_read | PS2_DATA_REC_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_PS2_DATA_REC_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_PS2_DATA_REC_s1 = PS2_DATA_REC_s1_end_xfer & (~PS2_DATA_REC_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //PS2_DATA_REC_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign PS2_DATA_REC_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_PS2_DATA_REC_s1 & PS2_DATA_REC_s1_allgrants) | (end_xfer_arb_share_counter_term_PS2_DATA_REC_s1 & ~PS2_DATA_REC_s1_non_bursting_master_requests);

  //PS2_DATA_REC_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          PS2_DATA_REC_s1_arb_share_counter <= 0;
      else if (PS2_DATA_REC_s1_arb_counter_enable)
          PS2_DATA_REC_s1_arb_share_counter <= PS2_DATA_REC_s1_arb_share_counter_next_value;
    end


  //PS2_DATA_REC_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          PS2_DATA_REC_s1_slavearbiterlockenable <= 0;
      else if ((|PS2_DATA_REC_s1_master_qreq_vector & end_xfer_arb_share_counter_term_PS2_DATA_REC_s1) | (end_xfer_arb_share_counter_term_PS2_DATA_REC_s1 & ~PS2_DATA_REC_s1_non_bursting_master_requests))
          PS2_DATA_REC_s1_slavearbiterlockenable <= |PS2_DATA_REC_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master PS2_DATA_REC/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = PS2_DATA_REC_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //PS2_DATA_REC_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign PS2_DATA_REC_s1_slavearbiterlockenable2 = |PS2_DATA_REC_s1_arb_share_counter_next_value;

  //cpu_0/data_master PS2_DATA_REC/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = PS2_DATA_REC_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //PS2_DATA_REC_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign PS2_DATA_REC_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_PS2_DATA_REC_s1 = cpu_0_data_master_requests_PS2_DATA_REC_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_PS2_DATA_REC_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_PS2_DATA_REC_s1 = cpu_0_data_master_granted_PS2_DATA_REC_s1 & cpu_0_data_master_read & ~PS2_DATA_REC_s1_waits_for_read;

  //PS2_DATA_REC_s1_writedata mux, which is an e_mux
  assign PS2_DATA_REC_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_PS2_DATA_REC_s1 = cpu_0_data_master_qualified_request_PS2_DATA_REC_s1;

  //cpu_0/data_master saved-grant PS2_DATA_REC/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_PS2_DATA_REC_s1 = cpu_0_data_master_requests_PS2_DATA_REC_s1;

  //allow new arb cycle for PS2_DATA_REC/s1, which is an e_assign
  assign PS2_DATA_REC_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign PS2_DATA_REC_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign PS2_DATA_REC_s1_master_qreq_vector = 1;

  //PS2_DATA_REC_s1_reset_n assignment, which is an e_assign
  assign PS2_DATA_REC_s1_reset_n = reset_n;

  assign PS2_DATA_REC_s1_chipselect = cpu_0_data_master_granted_PS2_DATA_REC_s1;
  //PS2_DATA_REC_s1_firsttransfer first transaction, which is an e_assign
  assign PS2_DATA_REC_s1_firsttransfer = PS2_DATA_REC_s1_begins_xfer ? PS2_DATA_REC_s1_unreg_firsttransfer : PS2_DATA_REC_s1_reg_firsttransfer;

  //PS2_DATA_REC_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign PS2_DATA_REC_s1_unreg_firsttransfer = ~(PS2_DATA_REC_s1_slavearbiterlockenable & PS2_DATA_REC_s1_any_continuerequest);

  //PS2_DATA_REC_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          PS2_DATA_REC_s1_reg_firsttransfer <= 1'b1;
      else if (PS2_DATA_REC_s1_begins_xfer)
          PS2_DATA_REC_s1_reg_firsttransfer <= PS2_DATA_REC_s1_unreg_firsttransfer;
    end


  //PS2_DATA_REC_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign PS2_DATA_REC_s1_beginbursttransfer_internal = PS2_DATA_REC_s1_begins_xfer;

  //~PS2_DATA_REC_s1_write_n assignment, which is an e_mux
  assign PS2_DATA_REC_s1_write_n = ~(cpu_0_data_master_granted_PS2_DATA_REC_s1 & cpu_0_data_master_write);

  assign shifted_address_to_PS2_DATA_REC_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //PS2_DATA_REC_s1_address mux, which is an e_mux
  assign PS2_DATA_REC_s1_address = shifted_address_to_PS2_DATA_REC_s1_from_cpu_0_data_master >> 2;

  //d1_PS2_DATA_REC_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_PS2_DATA_REC_s1_end_xfer <= 1;
      else 
        d1_PS2_DATA_REC_s1_end_xfer <= PS2_DATA_REC_s1_end_xfer;
    end


  //PS2_DATA_REC_s1_waits_for_read in a cycle, which is an e_mux
  assign PS2_DATA_REC_s1_waits_for_read = PS2_DATA_REC_s1_in_a_read_cycle & PS2_DATA_REC_s1_begins_xfer;

  //PS2_DATA_REC_s1_in_a_read_cycle assignment, which is an e_assign
  assign PS2_DATA_REC_s1_in_a_read_cycle = cpu_0_data_master_granted_PS2_DATA_REC_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = PS2_DATA_REC_s1_in_a_read_cycle;

  //PS2_DATA_REC_s1_waits_for_write in a cycle, which is an e_mux
  assign PS2_DATA_REC_s1_waits_for_write = PS2_DATA_REC_s1_in_a_write_cycle & 0;

  //PS2_DATA_REC_s1_in_a_write_cycle assignment, which is an e_assign
  assign PS2_DATA_REC_s1_in_a_write_cycle = cpu_0_data_master_granted_PS2_DATA_REC_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = PS2_DATA_REC_s1_in_a_write_cycle;

  assign wait_for_PS2_DATA_REC_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //PS2_DATA_REC/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module RTC_DATA_s1_arbitrator (
                                // inputs:
                                 RTC_DATA_s1_readdata,
                                 clk,
                                 cpu_0_data_master_address_to_slave,
                                 cpu_0_data_master_latency_counter,
                                 cpu_0_data_master_read,
                                 cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                 cpu_0_data_master_write,
                                 cpu_0_data_master_writedata,
                                 reset_n,

                                // outputs:
                                 RTC_DATA_s1_address,
                                 RTC_DATA_s1_chipselect,
                                 RTC_DATA_s1_readdata_from_sa,
                                 RTC_DATA_s1_reset_n,
                                 RTC_DATA_s1_write_n,
                                 RTC_DATA_s1_writedata,
                                 cpu_0_data_master_granted_RTC_DATA_s1,
                                 cpu_0_data_master_qualified_request_RTC_DATA_s1,
                                 cpu_0_data_master_read_data_valid_RTC_DATA_s1,
                                 cpu_0_data_master_requests_RTC_DATA_s1,
                                 d1_RTC_DATA_s1_end_xfer
                              )
;

  output  [  1: 0] RTC_DATA_s1_address;
  output           RTC_DATA_s1_chipselect;
  output  [ 31: 0] RTC_DATA_s1_readdata_from_sa;
  output           RTC_DATA_s1_reset_n;
  output           RTC_DATA_s1_write_n;
  output  [ 31: 0] RTC_DATA_s1_writedata;
  output           cpu_0_data_master_granted_RTC_DATA_s1;
  output           cpu_0_data_master_qualified_request_RTC_DATA_s1;
  output           cpu_0_data_master_read_data_valid_RTC_DATA_s1;
  output           cpu_0_data_master_requests_RTC_DATA_s1;
  output           d1_RTC_DATA_s1_end_xfer;
  input   [ 31: 0] RTC_DATA_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] RTC_DATA_s1_address;
  wire             RTC_DATA_s1_allgrants;
  wire             RTC_DATA_s1_allow_new_arb_cycle;
  wire             RTC_DATA_s1_any_bursting_master_saved_grant;
  wire             RTC_DATA_s1_any_continuerequest;
  wire             RTC_DATA_s1_arb_counter_enable;
  reg     [  1: 0] RTC_DATA_s1_arb_share_counter;
  wire    [  1: 0] RTC_DATA_s1_arb_share_counter_next_value;
  wire    [  1: 0] RTC_DATA_s1_arb_share_set_values;
  wire             RTC_DATA_s1_beginbursttransfer_internal;
  wire             RTC_DATA_s1_begins_xfer;
  wire             RTC_DATA_s1_chipselect;
  wire             RTC_DATA_s1_end_xfer;
  wire             RTC_DATA_s1_firsttransfer;
  wire             RTC_DATA_s1_grant_vector;
  wire             RTC_DATA_s1_in_a_read_cycle;
  wire             RTC_DATA_s1_in_a_write_cycle;
  wire             RTC_DATA_s1_master_qreq_vector;
  wire             RTC_DATA_s1_non_bursting_master_requests;
  wire    [ 31: 0] RTC_DATA_s1_readdata_from_sa;
  reg              RTC_DATA_s1_reg_firsttransfer;
  wire             RTC_DATA_s1_reset_n;
  reg              RTC_DATA_s1_slavearbiterlockenable;
  wire             RTC_DATA_s1_slavearbiterlockenable2;
  wire             RTC_DATA_s1_unreg_firsttransfer;
  wire             RTC_DATA_s1_waits_for_read;
  wire             RTC_DATA_s1_waits_for_write;
  wire             RTC_DATA_s1_write_n;
  wire    [ 31: 0] RTC_DATA_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_RTC_DATA_s1;
  wire             cpu_0_data_master_qualified_request_RTC_DATA_s1;
  wire             cpu_0_data_master_read_data_valid_RTC_DATA_s1;
  wire             cpu_0_data_master_requests_RTC_DATA_s1;
  wire             cpu_0_data_master_saved_grant_RTC_DATA_s1;
  reg              d1_RTC_DATA_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_RTC_DATA_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_RTC_DATA_s1_from_cpu_0_data_master;
  wire             wait_for_RTC_DATA_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~RTC_DATA_s1_end_xfer;
    end


  assign RTC_DATA_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_RTC_DATA_s1));
  //assign RTC_DATA_s1_readdata_from_sa = RTC_DATA_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign RTC_DATA_s1_readdata_from_sa = RTC_DATA_s1_readdata;

  assign cpu_0_data_master_requests_RTC_DATA_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h40020f0) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //RTC_DATA_s1_arb_share_counter set values, which is an e_mux
  assign RTC_DATA_s1_arb_share_set_values = 1;

  //RTC_DATA_s1_non_bursting_master_requests mux, which is an e_mux
  assign RTC_DATA_s1_non_bursting_master_requests = cpu_0_data_master_requests_RTC_DATA_s1;

  //RTC_DATA_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign RTC_DATA_s1_any_bursting_master_saved_grant = 0;

  //RTC_DATA_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign RTC_DATA_s1_arb_share_counter_next_value = RTC_DATA_s1_firsttransfer ? (RTC_DATA_s1_arb_share_set_values - 1) : |RTC_DATA_s1_arb_share_counter ? (RTC_DATA_s1_arb_share_counter - 1) : 0;

  //RTC_DATA_s1_allgrants all slave grants, which is an e_mux
  assign RTC_DATA_s1_allgrants = |RTC_DATA_s1_grant_vector;

  //RTC_DATA_s1_end_xfer assignment, which is an e_assign
  assign RTC_DATA_s1_end_xfer = ~(RTC_DATA_s1_waits_for_read | RTC_DATA_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_RTC_DATA_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_RTC_DATA_s1 = RTC_DATA_s1_end_xfer & (~RTC_DATA_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //RTC_DATA_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign RTC_DATA_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_RTC_DATA_s1 & RTC_DATA_s1_allgrants) | (end_xfer_arb_share_counter_term_RTC_DATA_s1 & ~RTC_DATA_s1_non_bursting_master_requests);

  //RTC_DATA_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          RTC_DATA_s1_arb_share_counter <= 0;
      else if (RTC_DATA_s1_arb_counter_enable)
          RTC_DATA_s1_arb_share_counter <= RTC_DATA_s1_arb_share_counter_next_value;
    end


  //RTC_DATA_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          RTC_DATA_s1_slavearbiterlockenable <= 0;
      else if ((|RTC_DATA_s1_master_qreq_vector & end_xfer_arb_share_counter_term_RTC_DATA_s1) | (end_xfer_arb_share_counter_term_RTC_DATA_s1 & ~RTC_DATA_s1_non_bursting_master_requests))
          RTC_DATA_s1_slavearbiterlockenable <= |RTC_DATA_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master RTC_DATA/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = RTC_DATA_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //RTC_DATA_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign RTC_DATA_s1_slavearbiterlockenable2 = |RTC_DATA_s1_arb_share_counter_next_value;

  //cpu_0/data_master RTC_DATA/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = RTC_DATA_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //RTC_DATA_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign RTC_DATA_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_RTC_DATA_s1 = cpu_0_data_master_requests_RTC_DATA_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_RTC_DATA_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_RTC_DATA_s1 = cpu_0_data_master_granted_RTC_DATA_s1 & cpu_0_data_master_read & ~RTC_DATA_s1_waits_for_read;

  //RTC_DATA_s1_writedata mux, which is an e_mux
  assign RTC_DATA_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_RTC_DATA_s1 = cpu_0_data_master_qualified_request_RTC_DATA_s1;

  //cpu_0/data_master saved-grant RTC_DATA/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_RTC_DATA_s1 = cpu_0_data_master_requests_RTC_DATA_s1;

  //allow new arb cycle for RTC_DATA/s1, which is an e_assign
  assign RTC_DATA_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign RTC_DATA_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign RTC_DATA_s1_master_qreq_vector = 1;

  //RTC_DATA_s1_reset_n assignment, which is an e_assign
  assign RTC_DATA_s1_reset_n = reset_n;

  assign RTC_DATA_s1_chipselect = cpu_0_data_master_granted_RTC_DATA_s1;
  //RTC_DATA_s1_firsttransfer first transaction, which is an e_assign
  assign RTC_DATA_s1_firsttransfer = RTC_DATA_s1_begins_xfer ? RTC_DATA_s1_unreg_firsttransfer : RTC_DATA_s1_reg_firsttransfer;

  //RTC_DATA_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign RTC_DATA_s1_unreg_firsttransfer = ~(RTC_DATA_s1_slavearbiterlockenable & RTC_DATA_s1_any_continuerequest);

  //RTC_DATA_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          RTC_DATA_s1_reg_firsttransfer <= 1'b1;
      else if (RTC_DATA_s1_begins_xfer)
          RTC_DATA_s1_reg_firsttransfer <= RTC_DATA_s1_unreg_firsttransfer;
    end


  //RTC_DATA_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign RTC_DATA_s1_beginbursttransfer_internal = RTC_DATA_s1_begins_xfer;

  //~RTC_DATA_s1_write_n assignment, which is an e_mux
  assign RTC_DATA_s1_write_n = ~(cpu_0_data_master_granted_RTC_DATA_s1 & cpu_0_data_master_write);

  assign shifted_address_to_RTC_DATA_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //RTC_DATA_s1_address mux, which is an e_mux
  assign RTC_DATA_s1_address = shifted_address_to_RTC_DATA_s1_from_cpu_0_data_master >> 2;

  //d1_RTC_DATA_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_RTC_DATA_s1_end_xfer <= 1;
      else 
        d1_RTC_DATA_s1_end_xfer <= RTC_DATA_s1_end_xfer;
    end


  //RTC_DATA_s1_waits_for_read in a cycle, which is an e_mux
  assign RTC_DATA_s1_waits_for_read = RTC_DATA_s1_in_a_read_cycle & RTC_DATA_s1_begins_xfer;

  //RTC_DATA_s1_in_a_read_cycle assignment, which is an e_assign
  assign RTC_DATA_s1_in_a_read_cycle = cpu_0_data_master_granted_RTC_DATA_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = RTC_DATA_s1_in_a_read_cycle;

  //RTC_DATA_s1_waits_for_write in a cycle, which is an e_mux
  assign RTC_DATA_s1_waits_for_write = RTC_DATA_s1_in_a_write_cycle & 0;

  //RTC_DATA_s1_in_a_write_cycle assignment, which is an e_assign
  assign RTC_DATA_s1_in_a_write_cycle = cpu_0_data_master_granted_RTC_DATA_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = RTC_DATA_s1_in_a_write_cycle;

  assign wait_for_RTC_DATA_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //RTC_DATA/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module SCL_s1_arbitrator (
                           // inputs:
                            SCL_s1_readdata,
                            clk,
                            cpu_0_data_master_address_to_slave,
                            cpu_0_data_master_latency_counter,
                            cpu_0_data_master_read,
                            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                            cpu_0_data_master_write,
                            cpu_0_data_master_writedata,
                            reset_n,

                           // outputs:
                            SCL_s1_address,
                            SCL_s1_chipselect,
                            SCL_s1_readdata_from_sa,
                            SCL_s1_reset_n,
                            SCL_s1_write_n,
                            SCL_s1_writedata,
                            cpu_0_data_master_granted_SCL_s1,
                            cpu_0_data_master_qualified_request_SCL_s1,
                            cpu_0_data_master_read_data_valid_SCL_s1,
                            cpu_0_data_master_requests_SCL_s1,
                            d1_SCL_s1_end_xfer
                         )
;

  output  [  1: 0] SCL_s1_address;
  output           SCL_s1_chipselect;
  output  [ 31: 0] SCL_s1_readdata_from_sa;
  output           SCL_s1_reset_n;
  output           SCL_s1_write_n;
  output  [ 31: 0] SCL_s1_writedata;
  output           cpu_0_data_master_granted_SCL_s1;
  output           cpu_0_data_master_qualified_request_SCL_s1;
  output           cpu_0_data_master_read_data_valid_SCL_s1;
  output           cpu_0_data_master_requests_SCL_s1;
  output           d1_SCL_s1_end_xfer;
  input   [ 31: 0] SCL_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] SCL_s1_address;
  wire             SCL_s1_allgrants;
  wire             SCL_s1_allow_new_arb_cycle;
  wire             SCL_s1_any_bursting_master_saved_grant;
  wire             SCL_s1_any_continuerequest;
  wire             SCL_s1_arb_counter_enable;
  reg     [  1: 0] SCL_s1_arb_share_counter;
  wire    [  1: 0] SCL_s1_arb_share_counter_next_value;
  wire    [  1: 0] SCL_s1_arb_share_set_values;
  wire             SCL_s1_beginbursttransfer_internal;
  wire             SCL_s1_begins_xfer;
  wire             SCL_s1_chipselect;
  wire             SCL_s1_end_xfer;
  wire             SCL_s1_firsttransfer;
  wire             SCL_s1_grant_vector;
  wire             SCL_s1_in_a_read_cycle;
  wire             SCL_s1_in_a_write_cycle;
  wire             SCL_s1_master_qreq_vector;
  wire             SCL_s1_non_bursting_master_requests;
  wire    [ 31: 0] SCL_s1_readdata_from_sa;
  reg              SCL_s1_reg_firsttransfer;
  wire             SCL_s1_reset_n;
  reg              SCL_s1_slavearbiterlockenable;
  wire             SCL_s1_slavearbiterlockenable2;
  wire             SCL_s1_unreg_firsttransfer;
  wire             SCL_s1_waits_for_read;
  wire             SCL_s1_waits_for_write;
  wire             SCL_s1_write_n;
  wire    [ 31: 0] SCL_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_SCL_s1;
  wire             cpu_0_data_master_qualified_request_SCL_s1;
  wire             cpu_0_data_master_read_data_valid_SCL_s1;
  wire             cpu_0_data_master_requests_SCL_s1;
  wire             cpu_0_data_master_saved_grant_SCL_s1;
  reg              d1_SCL_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_SCL_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_SCL_s1_from_cpu_0_data_master;
  wire             wait_for_SCL_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~SCL_s1_end_xfer;
    end


  assign SCL_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_SCL_s1));
  //assign SCL_s1_readdata_from_sa = SCL_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign SCL_s1_readdata_from_sa = SCL_s1_readdata;

  assign cpu_0_data_master_requests_SCL_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002290) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //SCL_s1_arb_share_counter set values, which is an e_mux
  assign SCL_s1_arb_share_set_values = 1;

  //SCL_s1_non_bursting_master_requests mux, which is an e_mux
  assign SCL_s1_non_bursting_master_requests = cpu_0_data_master_requests_SCL_s1;

  //SCL_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign SCL_s1_any_bursting_master_saved_grant = 0;

  //SCL_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign SCL_s1_arb_share_counter_next_value = SCL_s1_firsttransfer ? (SCL_s1_arb_share_set_values - 1) : |SCL_s1_arb_share_counter ? (SCL_s1_arb_share_counter - 1) : 0;

  //SCL_s1_allgrants all slave grants, which is an e_mux
  assign SCL_s1_allgrants = |SCL_s1_grant_vector;

  //SCL_s1_end_xfer assignment, which is an e_assign
  assign SCL_s1_end_xfer = ~(SCL_s1_waits_for_read | SCL_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_SCL_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_SCL_s1 = SCL_s1_end_xfer & (~SCL_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //SCL_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign SCL_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_SCL_s1 & SCL_s1_allgrants) | (end_xfer_arb_share_counter_term_SCL_s1 & ~SCL_s1_non_bursting_master_requests);

  //SCL_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          SCL_s1_arb_share_counter <= 0;
      else if (SCL_s1_arb_counter_enable)
          SCL_s1_arb_share_counter <= SCL_s1_arb_share_counter_next_value;
    end


  //SCL_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          SCL_s1_slavearbiterlockenable <= 0;
      else if ((|SCL_s1_master_qreq_vector & end_xfer_arb_share_counter_term_SCL_s1) | (end_xfer_arb_share_counter_term_SCL_s1 & ~SCL_s1_non_bursting_master_requests))
          SCL_s1_slavearbiterlockenable <= |SCL_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master SCL/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = SCL_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //SCL_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign SCL_s1_slavearbiterlockenable2 = |SCL_s1_arb_share_counter_next_value;

  //cpu_0/data_master SCL/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = SCL_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //SCL_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign SCL_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_SCL_s1 = cpu_0_data_master_requests_SCL_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_SCL_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_SCL_s1 = cpu_0_data_master_granted_SCL_s1 & cpu_0_data_master_read & ~SCL_s1_waits_for_read;

  //SCL_s1_writedata mux, which is an e_mux
  assign SCL_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_SCL_s1 = cpu_0_data_master_qualified_request_SCL_s1;

  //cpu_0/data_master saved-grant SCL/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_SCL_s1 = cpu_0_data_master_requests_SCL_s1;

  //allow new arb cycle for SCL/s1, which is an e_assign
  assign SCL_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign SCL_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign SCL_s1_master_qreq_vector = 1;

  //SCL_s1_reset_n assignment, which is an e_assign
  assign SCL_s1_reset_n = reset_n;

  assign SCL_s1_chipselect = cpu_0_data_master_granted_SCL_s1;
  //SCL_s1_firsttransfer first transaction, which is an e_assign
  assign SCL_s1_firsttransfer = SCL_s1_begins_xfer ? SCL_s1_unreg_firsttransfer : SCL_s1_reg_firsttransfer;

  //SCL_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign SCL_s1_unreg_firsttransfer = ~(SCL_s1_slavearbiterlockenable & SCL_s1_any_continuerequest);

  //SCL_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          SCL_s1_reg_firsttransfer <= 1'b1;
      else if (SCL_s1_begins_xfer)
          SCL_s1_reg_firsttransfer <= SCL_s1_unreg_firsttransfer;
    end


  //SCL_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign SCL_s1_beginbursttransfer_internal = SCL_s1_begins_xfer;

  //~SCL_s1_write_n assignment, which is an e_mux
  assign SCL_s1_write_n = ~(cpu_0_data_master_granted_SCL_s1 & cpu_0_data_master_write);

  assign shifted_address_to_SCL_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //SCL_s1_address mux, which is an e_mux
  assign SCL_s1_address = shifted_address_to_SCL_s1_from_cpu_0_data_master >> 2;

  //d1_SCL_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_SCL_s1_end_xfer <= 1;
      else 
        d1_SCL_s1_end_xfer <= SCL_s1_end_xfer;
    end


  //SCL_s1_waits_for_read in a cycle, which is an e_mux
  assign SCL_s1_waits_for_read = SCL_s1_in_a_read_cycle & SCL_s1_begins_xfer;

  //SCL_s1_in_a_read_cycle assignment, which is an e_assign
  assign SCL_s1_in_a_read_cycle = cpu_0_data_master_granted_SCL_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = SCL_s1_in_a_read_cycle;

  //SCL_s1_waits_for_write in a cycle, which is an e_mux
  assign SCL_s1_waits_for_write = SCL_s1_in_a_write_cycle & 0;

  //SCL_s1_in_a_write_cycle assignment, which is an e_assign
  assign SCL_s1_in_a_write_cycle = cpu_0_data_master_granted_SCL_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = SCL_s1_in_a_write_cycle;

  assign wait_for_SCL_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //SCL/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module SDA_s1_arbitrator (
                           // inputs:
                            SDA_s1_readdata,
                            clk,
                            cpu_0_data_master_address_to_slave,
                            cpu_0_data_master_latency_counter,
                            cpu_0_data_master_read,
                            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                            cpu_0_data_master_write,
                            cpu_0_data_master_writedata,
                            reset_n,

                           // outputs:
                            SDA_s1_address,
                            SDA_s1_chipselect,
                            SDA_s1_readdata_from_sa,
                            SDA_s1_reset_n,
                            SDA_s1_write_n,
                            SDA_s1_writedata,
                            cpu_0_data_master_granted_SDA_s1,
                            cpu_0_data_master_qualified_request_SDA_s1,
                            cpu_0_data_master_read_data_valid_SDA_s1,
                            cpu_0_data_master_requests_SDA_s1,
                            d1_SDA_s1_end_xfer
                         )
;

  output  [  1: 0] SDA_s1_address;
  output           SDA_s1_chipselect;
  output  [ 31: 0] SDA_s1_readdata_from_sa;
  output           SDA_s1_reset_n;
  output           SDA_s1_write_n;
  output  [ 31: 0] SDA_s1_writedata;
  output           cpu_0_data_master_granted_SDA_s1;
  output           cpu_0_data_master_qualified_request_SDA_s1;
  output           cpu_0_data_master_read_data_valid_SDA_s1;
  output           cpu_0_data_master_requests_SDA_s1;
  output           d1_SDA_s1_end_xfer;
  input   [ 31: 0] SDA_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] SDA_s1_address;
  wire             SDA_s1_allgrants;
  wire             SDA_s1_allow_new_arb_cycle;
  wire             SDA_s1_any_bursting_master_saved_grant;
  wire             SDA_s1_any_continuerequest;
  wire             SDA_s1_arb_counter_enable;
  reg     [  1: 0] SDA_s1_arb_share_counter;
  wire    [  1: 0] SDA_s1_arb_share_counter_next_value;
  wire    [  1: 0] SDA_s1_arb_share_set_values;
  wire             SDA_s1_beginbursttransfer_internal;
  wire             SDA_s1_begins_xfer;
  wire             SDA_s1_chipselect;
  wire             SDA_s1_end_xfer;
  wire             SDA_s1_firsttransfer;
  wire             SDA_s1_grant_vector;
  wire             SDA_s1_in_a_read_cycle;
  wire             SDA_s1_in_a_write_cycle;
  wire             SDA_s1_master_qreq_vector;
  wire             SDA_s1_non_bursting_master_requests;
  wire    [ 31: 0] SDA_s1_readdata_from_sa;
  reg              SDA_s1_reg_firsttransfer;
  wire             SDA_s1_reset_n;
  reg              SDA_s1_slavearbiterlockenable;
  wire             SDA_s1_slavearbiterlockenable2;
  wire             SDA_s1_unreg_firsttransfer;
  wire             SDA_s1_waits_for_read;
  wire             SDA_s1_waits_for_write;
  wire             SDA_s1_write_n;
  wire    [ 31: 0] SDA_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_SDA_s1;
  wire             cpu_0_data_master_qualified_request_SDA_s1;
  wire             cpu_0_data_master_read_data_valid_SDA_s1;
  wire             cpu_0_data_master_requests_SDA_s1;
  wire             cpu_0_data_master_saved_grant_SDA_s1;
  reg              d1_SDA_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_SDA_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_SDA_s1_from_cpu_0_data_master;
  wire             wait_for_SDA_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~SDA_s1_end_xfer;
    end


  assign SDA_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_SDA_s1));
  //assign SDA_s1_readdata_from_sa = SDA_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign SDA_s1_readdata_from_sa = SDA_s1_readdata;

  assign cpu_0_data_master_requests_SDA_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h40022a0) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //SDA_s1_arb_share_counter set values, which is an e_mux
  assign SDA_s1_arb_share_set_values = 1;

  //SDA_s1_non_bursting_master_requests mux, which is an e_mux
  assign SDA_s1_non_bursting_master_requests = cpu_0_data_master_requests_SDA_s1;

  //SDA_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign SDA_s1_any_bursting_master_saved_grant = 0;

  //SDA_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign SDA_s1_arb_share_counter_next_value = SDA_s1_firsttransfer ? (SDA_s1_arb_share_set_values - 1) : |SDA_s1_arb_share_counter ? (SDA_s1_arb_share_counter - 1) : 0;

  //SDA_s1_allgrants all slave grants, which is an e_mux
  assign SDA_s1_allgrants = |SDA_s1_grant_vector;

  //SDA_s1_end_xfer assignment, which is an e_assign
  assign SDA_s1_end_xfer = ~(SDA_s1_waits_for_read | SDA_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_SDA_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_SDA_s1 = SDA_s1_end_xfer & (~SDA_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //SDA_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign SDA_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_SDA_s1 & SDA_s1_allgrants) | (end_xfer_arb_share_counter_term_SDA_s1 & ~SDA_s1_non_bursting_master_requests);

  //SDA_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          SDA_s1_arb_share_counter <= 0;
      else if (SDA_s1_arb_counter_enable)
          SDA_s1_arb_share_counter <= SDA_s1_arb_share_counter_next_value;
    end


  //SDA_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          SDA_s1_slavearbiterlockenable <= 0;
      else if ((|SDA_s1_master_qreq_vector & end_xfer_arb_share_counter_term_SDA_s1) | (end_xfer_arb_share_counter_term_SDA_s1 & ~SDA_s1_non_bursting_master_requests))
          SDA_s1_slavearbiterlockenable <= |SDA_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master SDA/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = SDA_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //SDA_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign SDA_s1_slavearbiterlockenable2 = |SDA_s1_arb_share_counter_next_value;

  //cpu_0/data_master SDA/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = SDA_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //SDA_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign SDA_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_SDA_s1 = cpu_0_data_master_requests_SDA_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_SDA_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_SDA_s1 = cpu_0_data_master_granted_SDA_s1 & cpu_0_data_master_read & ~SDA_s1_waits_for_read;

  //SDA_s1_writedata mux, which is an e_mux
  assign SDA_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_SDA_s1 = cpu_0_data_master_qualified_request_SDA_s1;

  //cpu_0/data_master saved-grant SDA/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_SDA_s1 = cpu_0_data_master_requests_SDA_s1;

  //allow new arb cycle for SDA/s1, which is an e_assign
  assign SDA_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign SDA_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign SDA_s1_master_qreq_vector = 1;

  //SDA_s1_reset_n assignment, which is an e_assign
  assign SDA_s1_reset_n = reset_n;

  assign SDA_s1_chipselect = cpu_0_data_master_granted_SDA_s1;
  //SDA_s1_firsttransfer first transaction, which is an e_assign
  assign SDA_s1_firsttransfer = SDA_s1_begins_xfer ? SDA_s1_unreg_firsttransfer : SDA_s1_reg_firsttransfer;

  //SDA_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign SDA_s1_unreg_firsttransfer = ~(SDA_s1_slavearbiterlockenable & SDA_s1_any_continuerequest);

  //SDA_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          SDA_s1_reg_firsttransfer <= 1'b1;
      else if (SDA_s1_begins_xfer)
          SDA_s1_reg_firsttransfer <= SDA_s1_unreg_firsttransfer;
    end


  //SDA_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign SDA_s1_beginbursttransfer_internal = SDA_s1_begins_xfer;

  //~SDA_s1_write_n assignment, which is an e_mux
  assign SDA_s1_write_n = ~(cpu_0_data_master_granted_SDA_s1 & cpu_0_data_master_write);

  assign shifted_address_to_SDA_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //SDA_s1_address mux, which is an e_mux
  assign SDA_s1_address = shifted_address_to_SDA_s1_from_cpu_0_data_master >> 2;

  //d1_SDA_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_SDA_s1_end_xfer <= 1;
      else 
        d1_SDA_s1_end_xfer <= SDA_s1_end_xfer;
    end


  //SDA_s1_waits_for_read in a cycle, which is an e_mux
  assign SDA_s1_waits_for_read = SDA_s1_in_a_read_cycle & SDA_s1_begins_xfer;

  //SDA_s1_in_a_read_cycle assignment, which is an e_assign
  assign SDA_s1_in_a_read_cycle = cpu_0_data_master_granted_SDA_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = SDA_s1_in_a_read_cycle;

  //SDA_s1_waits_for_write in a cycle, which is an e_mux
  assign SDA_s1_waits_for_write = SDA_s1_in_a_write_cycle & 0;

  //SDA_s1_in_a_write_cycle assignment, which is an e_assign
  assign SDA_s1_in_a_write_cycle = cpu_0_data_master_granted_SDA_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = SDA_s1_in_a_write_cycle;

  assign wait_for_SDA_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //SDA/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module SD_CLK_s1_arbitrator (
                              // inputs:
                               SD_CLK_s1_readdata,
                               clk,
                               cpu_0_data_master_address_to_slave,
                               cpu_0_data_master_latency_counter,
                               cpu_0_data_master_read,
                               cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                               cpu_0_data_master_write,
                               cpu_0_data_master_writedata,
                               reset_n,

                              // outputs:
                               SD_CLK_s1_address,
                               SD_CLK_s1_chipselect,
                               SD_CLK_s1_readdata_from_sa,
                               SD_CLK_s1_reset_n,
                               SD_CLK_s1_write_n,
                               SD_CLK_s1_writedata,
                               cpu_0_data_master_granted_SD_CLK_s1,
                               cpu_0_data_master_qualified_request_SD_CLK_s1,
                               cpu_0_data_master_read_data_valid_SD_CLK_s1,
                               cpu_0_data_master_requests_SD_CLK_s1,
                               d1_SD_CLK_s1_end_xfer
                            )
;

  output  [  1: 0] SD_CLK_s1_address;
  output           SD_CLK_s1_chipselect;
  output  [ 31: 0] SD_CLK_s1_readdata_from_sa;
  output           SD_CLK_s1_reset_n;
  output           SD_CLK_s1_write_n;
  output  [ 31: 0] SD_CLK_s1_writedata;
  output           cpu_0_data_master_granted_SD_CLK_s1;
  output           cpu_0_data_master_qualified_request_SD_CLK_s1;
  output           cpu_0_data_master_read_data_valid_SD_CLK_s1;
  output           cpu_0_data_master_requests_SD_CLK_s1;
  output           d1_SD_CLK_s1_end_xfer;
  input   [ 31: 0] SD_CLK_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] SD_CLK_s1_address;
  wire             SD_CLK_s1_allgrants;
  wire             SD_CLK_s1_allow_new_arb_cycle;
  wire             SD_CLK_s1_any_bursting_master_saved_grant;
  wire             SD_CLK_s1_any_continuerequest;
  wire             SD_CLK_s1_arb_counter_enable;
  reg     [  1: 0] SD_CLK_s1_arb_share_counter;
  wire    [  1: 0] SD_CLK_s1_arb_share_counter_next_value;
  wire    [  1: 0] SD_CLK_s1_arb_share_set_values;
  wire             SD_CLK_s1_beginbursttransfer_internal;
  wire             SD_CLK_s1_begins_xfer;
  wire             SD_CLK_s1_chipselect;
  wire             SD_CLK_s1_end_xfer;
  wire             SD_CLK_s1_firsttransfer;
  wire             SD_CLK_s1_grant_vector;
  wire             SD_CLK_s1_in_a_read_cycle;
  wire             SD_CLK_s1_in_a_write_cycle;
  wire             SD_CLK_s1_master_qreq_vector;
  wire             SD_CLK_s1_non_bursting_master_requests;
  wire    [ 31: 0] SD_CLK_s1_readdata_from_sa;
  reg              SD_CLK_s1_reg_firsttransfer;
  wire             SD_CLK_s1_reset_n;
  reg              SD_CLK_s1_slavearbiterlockenable;
  wire             SD_CLK_s1_slavearbiterlockenable2;
  wire             SD_CLK_s1_unreg_firsttransfer;
  wire             SD_CLK_s1_waits_for_read;
  wire             SD_CLK_s1_waits_for_write;
  wire             SD_CLK_s1_write_n;
  wire    [ 31: 0] SD_CLK_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_SD_CLK_s1;
  wire             cpu_0_data_master_qualified_request_SD_CLK_s1;
  wire             cpu_0_data_master_read_data_valid_SD_CLK_s1;
  wire             cpu_0_data_master_requests_SD_CLK_s1;
  wire             cpu_0_data_master_saved_grant_SD_CLK_s1;
  reg              d1_SD_CLK_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_SD_CLK_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_SD_CLK_s1_from_cpu_0_data_master;
  wire             wait_for_SD_CLK_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~SD_CLK_s1_end_xfer;
    end


  assign SD_CLK_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_SD_CLK_s1));
  //assign SD_CLK_s1_readdata_from_sa = SD_CLK_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign SD_CLK_s1_readdata_from_sa = SD_CLK_s1_readdata;

  assign cpu_0_data_master_requests_SD_CLK_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002180) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //SD_CLK_s1_arb_share_counter set values, which is an e_mux
  assign SD_CLK_s1_arb_share_set_values = 1;

  //SD_CLK_s1_non_bursting_master_requests mux, which is an e_mux
  assign SD_CLK_s1_non_bursting_master_requests = cpu_0_data_master_requests_SD_CLK_s1;

  //SD_CLK_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign SD_CLK_s1_any_bursting_master_saved_grant = 0;

  //SD_CLK_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign SD_CLK_s1_arb_share_counter_next_value = SD_CLK_s1_firsttransfer ? (SD_CLK_s1_arb_share_set_values - 1) : |SD_CLK_s1_arb_share_counter ? (SD_CLK_s1_arb_share_counter - 1) : 0;

  //SD_CLK_s1_allgrants all slave grants, which is an e_mux
  assign SD_CLK_s1_allgrants = |SD_CLK_s1_grant_vector;

  //SD_CLK_s1_end_xfer assignment, which is an e_assign
  assign SD_CLK_s1_end_xfer = ~(SD_CLK_s1_waits_for_read | SD_CLK_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_SD_CLK_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_SD_CLK_s1 = SD_CLK_s1_end_xfer & (~SD_CLK_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //SD_CLK_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign SD_CLK_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_SD_CLK_s1 & SD_CLK_s1_allgrants) | (end_xfer_arb_share_counter_term_SD_CLK_s1 & ~SD_CLK_s1_non_bursting_master_requests);

  //SD_CLK_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          SD_CLK_s1_arb_share_counter <= 0;
      else if (SD_CLK_s1_arb_counter_enable)
          SD_CLK_s1_arb_share_counter <= SD_CLK_s1_arb_share_counter_next_value;
    end


  //SD_CLK_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          SD_CLK_s1_slavearbiterlockenable <= 0;
      else if ((|SD_CLK_s1_master_qreq_vector & end_xfer_arb_share_counter_term_SD_CLK_s1) | (end_xfer_arb_share_counter_term_SD_CLK_s1 & ~SD_CLK_s1_non_bursting_master_requests))
          SD_CLK_s1_slavearbiterlockenable <= |SD_CLK_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master SD_CLK/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = SD_CLK_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //SD_CLK_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign SD_CLK_s1_slavearbiterlockenable2 = |SD_CLK_s1_arb_share_counter_next_value;

  //cpu_0/data_master SD_CLK/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = SD_CLK_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //SD_CLK_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign SD_CLK_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_SD_CLK_s1 = cpu_0_data_master_requests_SD_CLK_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_SD_CLK_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_SD_CLK_s1 = cpu_0_data_master_granted_SD_CLK_s1 & cpu_0_data_master_read & ~SD_CLK_s1_waits_for_read;

  //SD_CLK_s1_writedata mux, which is an e_mux
  assign SD_CLK_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_SD_CLK_s1 = cpu_0_data_master_qualified_request_SD_CLK_s1;

  //cpu_0/data_master saved-grant SD_CLK/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_SD_CLK_s1 = cpu_0_data_master_requests_SD_CLK_s1;

  //allow new arb cycle for SD_CLK/s1, which is an e_assign
  assign SD_CLK_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign SD_CLK_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign SD_CLK_s1_master_qreq_vector = 1;

  //SD_CLK_s1_reset_n assignment, which is an e_assign
  assign SD_CLK_s1_reset_n = reset_n;

  assign SD_CLK_s1_chipselect = cpu_0_data_master_granted_SD_CLK_s1;
  //SD_CLK_s1_firsttransfer first transaction, which is an e_assign
  assign SD_CLK_s1_firsttransfer = SD_CLK_s1_begins_xfer ? SD_CLK_s1_unreg_firsttransfer : SD_CLK_s1_reg_firsttransfer;

  //SD_CLK_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign SD_CLK_s1_unreg_firsttransfer = ~(SD_CLK_s1_slavearbiterlockenable & SD_CLK_s1_any_continuerequest);

  //SD_CLK_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          SD_CLK_s1_reg_firsttransfer <= 1'b1;
      else if (SD_CLK_s1_begins_xfer)
          SD_CLK_s1_reg_firsttransfer <= SD_CLK_s1_unreg_firsttransfer;
    end


  //SD_CLK_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign SD_CLK_s1_beginbursttransfer_internal = SD_CLK_s1_begins_xfer;

  //~SD_CLK_s1_write_n assignment, which is an e_mux
  assign SD_CLK_s1_write_n = ~(cpu_0_data_master_granted_SD_CLK_s1 & cpu_0_data_master_write);

  assign shifted_address_to_SD_CLK_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //SD_CLK_s1_address mux, which is an e_mux
  assign SD_CLK_s1_address = shifted_address_to_SD_CLK_s1_from_cpu_0_data_master >> 2;

  //d1_SD_CLK_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_SD_CLK_s1_end_xfer <= 1;
      else 
        d1_SD_CLK_s1_end_xfer <= SD_CLK_s1_end_xfer;
    end


  //SD_CLK_s1_waits_for_read in a cycle, which is an e_mux
  assign SD_CLK_s1_waits_for_read = SD_CLK_s1_in_a_read_cycle & SD_CLK_s1_begins_xfer;

  //SD_CLK_s1_in_a_read_cycle assignment, which is an e_assign
  assign SD_CLK_s1_in_a_read_cycle = cpu_0_data_master_granted_SD_CLK_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = SD_CLK_s1_in_a_read_cycle;

  //SD_CLK_s1_waits_for_write in a cycle, which is an e_mux
  assign SD_CLK_s1_waits_for_write = SD_CLK_s1_in_a_write_cycle & 0;

  //SD_CLK_s1_in_a_write_cycle assignment, which is an e_assign
  assign SD_CLK_s1_in_a_write_cycle = cpu_0_data_master_granted_SD_CLK_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = SD_CLK_s1_in_a_write_cycle;

  assign wait_for_SD_CLK_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //SD_CLK/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module SD_CS_s1_arbitrator (
                             // inputs:
                              SD_CS_s1_readdata,
                              clk,
                              cpu_0_data_master_address_to_slave,
                              cpu_0_data_master_latency_counter,
                              cpu_0_data_master_read,
                              cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                              cpu_0_data_master_write,
                              cpu_0_data_master_writedata,
                              reset_n,

                             // outputs:
                              SD_CS_s1_address,
                              SD_CS_s1_chipselect,
                              SD_CS_s1_readdata_from_sa,
                              SD_CS_s1_reset_n,
                              SD_CS_s1_write_n,
                              SD_CS_s1_writedata,
                              cpu_0_data_master_granted_SD_CS_s1,
                              cpu_0_data_master_qualified_request_SD_CS_s1,
                              cpu_0_data_master_read_data_valid_SD_CS_s1,
                              cpu_0_data_master_requests_SD_CS_s1,
                              d1_SD_CS_s1_end_xfer
                           )
;

  output  [  1: 0] SD_CS_s1_address;
  output           SD_CS_s1_chipselect;
  output  [ 31: 0] SD_CS_s1_readdata_from_sa;
  output           SD_CS_s1_reset_n;
  output           SD_CS_s1_write_n;
  output  [ 31: 0] SD_CS_s1_writedata;
  output           cpu_0_data_master_granted_SD_CS_s1;
  output           cpu_0_data_master_qualified_request_SD_CS_s1;
  output           cpu_0_data_master_read_data_valid_SD_CS_s1;
  output           cpu_0_data_master_requests_SD_CS_s1;
  output           d1_SD_CS_s1_end_xfer;
  input   [ 31: 0] SD_CS_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] SD_CS_s1_address;
  wire             SD_CS_s1_allgrants;
  wire             SD_CS_s1_allow_new_arb_cycle;
  wire             SD_CS_s1_any_bursting_master_saved_grant;
  wire             SD_CS_s1_any_continuerequest;
  wire             SD_CS_s1_arb_counter_enable;
  reg     [  1: 0] SD_CS_s1_arb_share_counter;
  wire    [  1: 0] SD_CS_s1_arb_share_counter_next_value;
  wire    [  1: 0] SD_CS_s1_arb_share_set_values;
  wire             SD_CS_s1_beginbursttransfer_internal;
  wire             SD_CS_s1_begins_xfer;
  wire             SD_CS_s1_chipselect;
  wire             SD_CS_s1_end_xfer;
  wire             SD_CS_s1_firsttransfer;
  wire             SD_CS_s1_grant_vector;
  wire             SD_CS_s1_in_a_read_cycle;
  wire             SD_CS_s1_in_a_write_cycle;
  wire             SD_CS_s1_master_qreq_vector;
  wire             SD_CS_s1_non_bursting_master_requests;
  wire    [ 31: 0] SD_CS_s1_readdata_from_sa;
  reg              SD_CS_s1_reg_firsttransfer;
  wire             SD_CS_s1_reset_n;
  reg              SD_CS_s1_slavearbiterlockenable;
  wire             SD_CS_s1_slavearbiterlockenable2;
  wire             SD_CS_s1_unreg_firsttransfer;
  wire             SD_CS_s1_waits_for_read;
  wire             SD_CS_s1_waits_for_write;
  wire             SD_CS_s1_write_n;
  wire    [ 31: 0] SD_CS_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_SD_CS_s1;
  wire             cpu_0_data_master_qualified_request_SD_CS_s1;
  wire             cpu_0_data_master_read_data_valid_SD_CS_s1;
  wire             cpu_0_data_master_requests_SD_CS_s1;
  wire             cpu_0_data_master_saved_grant_SD_CS_s1;
  reg              d1_SD_CS_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_SD_CS_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_SD_CS_s1_from_cpu_0_data_master;
  wire             wait_for_SD_CS_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~SD_CS_s1_end_xfer;
    end


  assign SD_CS_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_SD_CS_s1));
  //assign SD_CS_s1_readdata_from_sa = SD_CS_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign SD_CS_s1_readdata_from_sa = SD_CS_s1_readdata;

  assign cpu_0_data_master_requests_SD_CS_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002160) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //SD_CS_s1_arb_share_counter set values, which is an e_mux
  assign SD_CS_s1_arb_share_set_values = 1;

  //SD_CS_s1_non_bursting_master_requests mux, which is an e_mux
  assign SD_CS_s1_non_bursting_master_requests = cpu_0_data_master_requests_SD_CS_s1;

  //SD_CS_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign SD_CS_s1_any_bursting_master_saved_grant = 0;

  //SD_CS_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign SD_CS_s1_arb_share_counter_next_value = SD_CS_s1_firsttransfer ? (SD_CS_s1_arb_share_set_values - 1) : |SD_CS_s1_arb_share_counter ? (SD_CS_s1_arb_share_counter - 1) : 0;

  //SD_CS_s1_allgrants all slave grants, which is an e_mux
  assign SD_CS_s1_allgrants = |SD_CS_s1_grant_vector;

  //SD_CS_s1_end_xfer assignment, which is an e_assign
  assign SD_CS_s1_end_xfer = ~(SD_CS_s1_waits_for_read | SD_CS_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_SD_CS_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_SD_CS_s1 = SD_CS_s1_end_xfer & (~SD_CS_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //SD_CS_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign SD_CS_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_SD_CS_s1 & SD_CS_s1_allgrants) | (end_xfer_arb_share_counter_term_SD_CS_s1 & ~SD_CS_s1_non_bursting_master_requests);

  //SD_CS_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          SD_CS_s1_arb_share_counter <= 0;
      else if (SD_CS_s1_arb_counter_enable)
          SD_CS_s1_arb_share_counter <= SD_CS_s1_arb_share_counter_next_value;
    end


  //SD_CS_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          SD_CS_s1_slavearbiterlockenable <= 0;
      else if ((|SD_CS_s1_master_qreq_vector & end_xfer_arb_share_counter_term_SD_CS_s1) | (end_xfer_arb_share_counter_term_SD_CS_s1 & ~SD_CS_s1_non_bursting_master_requests))
          SD_CS_s1_slavearbiterlockenable <= |SD_CS_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master SD_CS/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = SD_CS_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //SD_CS_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign SD_CS_s1_slavearbiterlockenable2 = |SD_CS_s1_arb_share_counter_next_value;

  //cpu_0/data_master SD_CS/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = SD_CS_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //SD_CS_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign SD_CS_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_SD_CS_s1 = cpu_0_data_master_requests_SD_CS_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_SD_CS_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_SD_CS_s1 = cpu_0_data_master_granted_SD_CS_s1 & cpu_0_data_master_read & ~SD_CS_s1_waits_for_read;

  //SD_CS_s1_writedata mux, which is an e_mux
  assign SD_CS_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_SD_CS_s1 = cpu_0_data_master_qualified_request_SD_CS_s1;

  //cpu_0/data_master saved-grant SD_CS/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_SD_CS_s1 = cpu_0_data_master_requests_SD_CS_s1;

  //allow new arb cycle for SD_CS/s1, which is an e_assign
  assign SD_CS_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign SD_CS_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign SD_CS_s1_master_qreq_vector = 1;

  //SD_CS_s1_reset_n assignment, which is an e_assign
  assign SD_CS_s1_reset_n = reset_n;

  assign SD_CS_s1_chipselect = cpu_0_data_master_granted_SD_CS_s1;
  //SD_CS_s1_firsttransfer first transaction, which is an e_assign
  assign SD_CS_s1_firsttransfer = SD_CS_s1_begins_xfer ? SD_CS_s1_unreg_firsttransfer : SD_CS_s1_reg_firsttransfer;

  //SD_CS_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign SD_CS_s1_unreg_firsttransfer = ~(SD_CS_s1_slavearbiterlockenable & SD_CS_s1_any_continuerequest);

  //SD_CS_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          SD_CS_s1_reg_firsttransfer <= 1'b1;
      else if (SD_CS_s1_begins_xfer)
          SD_CS_s1_reg_firsttransfer <= SD_CS_s1_unreg_firsttransfer;
    end


  //SD_CS_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign SD_CS_s1_beginbursttransfer_internal = SD_CS_s1_begins_xfer;

  //~SD_CS_s1_write_n assignment, which is an e_mux
  assign SD_CS_s1_write_n = ~(cpu_0_data_master_granted_SD_CS_s1 & cpu_0_data_master_write);

  assign shifted_address_to_SD_CS_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //SD_CS_s1_address mux, which is an e_mux
  assign SD_CS_s1_address = shifted_address_to_SD_CS_s1_from_cpu_0_data_master >> 2;

  //d1_SD_CS_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_SD_CS_s1_end_xfer <= 1;
      else 
        d1_SD_CS_s1_end_xfer <= SD_CS_s1_end_xfer;
    end


  //SD_CS_s1_waits_for_read in a cycle, which is an e_mux
  assign SD_CS_s1_waits_for_read = SD_CS_s1_in_a_read_cycle & SD_CS_s1_begins_xfer;

  //SD_CS_s1_in_a_read_cycle assignment, which is an e_assign
  assign SD_CS_s1_in_a_read_cycle = cpu_0_data_master_granted_SD_CS_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = SD_CS_s1_in_a_read_cycle;

  //SD_CS_s1_waits_for_write in a cycle, which is an e_mux
  assign SD_CS_s1_waits_for_write = SD_CS_s1_in_a_write_cycle & 0;

  //SD_CS_s1_in_a_write_cycle assignment, which is an e_assign
  assign SD_CS_s1_in_a_write_cycle = cpu_0_data_master_granted_SD_CS_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = SD_CS_s1_in_a_write_cycle;

  assign wait_for_SD_CS_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //SD_CS/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module SD_DI_s1_arbitrator (
                             // inputs:
                              SD_DI_s1_readdata,
                              clk,
                              cpu_0_data_master_address_to_slave,
                              cpu_0_data_master_latency_counter,
                              cpu_0_data_master_read,
                              cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                              cpu_0_data_master_write,
                              cpu_0_data_master_writedata,
                              reset_n,

                             // outputs:
                              SD_DI_s1_address,
                              SD_DI_s1_chipselect,
                              SD_DI_s1_readdata_from_sa,
                              SD_DI_s1_reset_n,
                              SD_DI_s1_write_n,
                              SD_DI_s1_writedata,
                              cpu_0_data_master_granted_SD_DI_s1,
                              cpu_0_data_master_qualified_request_SD_DI_s1,
                              cpu_0_data_master_read_data_valid_SD_DI_s1,
                              cpu_0_data_master_requests_SD_DI_s1,
                              d1_SD_DI_s1_end_xfer
                           )
;

  output  [  1: 0] SD_DI_s1_address;
  output           SD_DI_s1_chipselect;
  output  [ 31: 0] SD_DI_s1_readdata_from_sa;
  output           SD_DI_s1_reset_n;
  output           SD_DI_s1_write_n;
  output  [ 31: 0] SD_DI_s1_writedata;
  output           cpu_0_data_master_granted_SD_DI_s1;
  output           cpu_0_data_master_qualified_request_SD_DI_s1;
  output           cpu_0_data_master_read_data_valid_SD_DI_s1;
  output           cpu_0_data_master_requests_SD_DI_s1;
  output           d1_SD_DI_s1_end_xfer;
  input   [ 31: 0] SD_DI_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] SD_DI_s1_address;
  wire             SD_DI_s1_allgrants;
  wire             SD_DI_s1_allow_new_arb_cycle;
  wire             SD_DI_s1_any_bursting_master_saved_grant;
  wire             SD_DI_s1_any_continuerequest;
  wire             SD_DI_s1_arb_counter_enable;
  reg     [  1: 0] SD_DI_s1_arb_share_counter;
  wire    [  1: 0] SD_DI_s1_arb_share_counter_next_value;
  wire    [  1: 0] SD_DI_s1_arb_share_set_values;
  wire             SD_DI_s1_beginbursttransfer_internal;
  wire             SD_DI_s1_begins_xfer;
  wire             SD_DI_s1_chipselect;
  wire             SD_DI_s1_end_xfer;
  wire             SD_DI_s1_firsttransfer;
  wire             SD_DI_s1_grant_vector;
  wire             SD_DI_s1_in_a_read_cycle;
  wire             SD_DI_s1_in_a_write_cycle;
  wire             SD_DI_s1_master_qreq_vector;
  wire             SD_DI_s1_non_bursting_master_requests;
  wire    [ 31: 0] SD_DI_s1_readdata_from_sa;
  reg              SD_DI_s1_reg_firsttransfer;
  wire             SD_DI_s1_reset_n;
  reg              SD_DI_s1_slavearbiterlockenable;
  wire             SD_DI_s1_slavearbiterlockenable2;
  wire             SD_DI_s1_unreg_firsttransfer;
  wire             SD_DI_s1_waits_for_read;
  wire             SD_DI_s1_waits_for_write;
  wire             SD_DI_s1_write_n;
  wire    [ 31: 0] SD_DI_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_SD_DI_s1;
  wire             cpu_0_data_master_qualified_request_SD_DI_s1;
  wire             cpu_0_data_master_read_data_valid_SD_DI_s1;
  wire             cpu_0_data_master_requests_SD_DI_s1;
  wire             cpu_0_data_master_saved_grant_SD_DI_s1;
  reg              d1_SD_DI_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_SD_DI_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_SD_DI_s1_from_cpu_0_data_master;
  wire             wait_for_SD_DI_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~SD_DI_s1_end_xfer;
    end


  assign SD_DI_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_SD_DI_s1));
  //assign SD_DI_s1_readdata_from_sa = SD_DI_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign SD_DI_s1_readdata_from_sa = SD_DI_s1_readdata;

  assign cpu_0_data_master_requests_SD_DI_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002170) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //SD_DI_s1_arb_share_counter set values, which is an e_mux
  assign SD_DI_s1_arb_share_set_values = 1;

  //SD_DI_s1_non_bursting_master_requests mux, which is an e_mux
  assign SD_DI_s1_non_bursting_master_requests = cpu_0_data_master_requests_SD_DI_s1;

  //SD_DI_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign SD_DI_s1_any_bursting_master_saved_grant = 0;

  //SD_DI_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign SD_DI_s1_arb_share_counter_next_value = SD_DI_s1_firsttransfer ? (SD_DI_s1_arb_share_set_values - 1) : |SD_DI_s1_arb_share_counter ? (SD_DI_s1_arb_share_counter - 1) : 0;

  //SD_DI_s1_allgrants all slave grants, which is an e_mux
  assign SD_DI_s1_allgrants = |SD_DI_s1_grant_vector;

  //SD_DI_s1_end_xfer assignment, which is an e_assign
  assign SD_DI_s1_end_xfer = ~(SD_DI_s1_waits_for_read | SD_DI_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_SD_DI_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_SD_DI_s1 = SD_DI_s1_end_xfer & (~SD_DI_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //SD_DI_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign SD_DI_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_SD_DI_s1 & SD_DI_s1_allgrants) | (end_xfer_arb_share_counter_term_SD_DI_s1 & ~SD_DI_s1_non_bursting_master_requests);

  //SD_DI_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          SD_DI_s1_arb_share_counter <= 0;
      else if (SD_DI_s1_arb_counter_enable)
          SD_DI_s1_arb_share_counter <= SD_DI_s1_arb_share_counter_next_value;
    end


  //SD_DI_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          SD_DI_s1_slavearbiterlockenable <= 0;
      else if ((|SD_DI_s1_master_qreq_vector & end_xfer_arb_share_counter_term_SD_DI_s1) | (end_xfer_arb_share_counter_term_SD_DI_s1 & ~SD_DI_s1_non_bursting_master_requests))
          SD_DI_s1_slavearbiterlockenable <= |SD_DI_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master SD_DI/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = SD_DI_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //SD_DI_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign SD_DI_s1_slavearbiterlockenable2 = |SD_DI_s1_arb_share_counter_next_value;

  //cpu_0/data_master SD_DI/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = SD_DI_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //SD_DI_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign SD_DI_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_SD_DI_s1 = cpu_0_data_master_requests_SD_DI_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_SD_DI_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_SD_DI_s1 = cpu_0_data_master_granted_SD_DI_s1 & cpu_0_data_master_read & ~SD_DI_s1_waits_for_read;

  //SD_DI_s1_writedata mux, which is an e_mux
  assign SD_DI_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_SD_DI_s1 = cpu_0_data_master_qualified_request_SD_DI_s1;

  //cpu_0/data_master saved-grant SD_DI/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_SD_DI_s1 = cpu_0_data_master_requests_SD_DI_s1;

  //allow new arb cycle for SD_DI/s1, which is an e_assign
  assign SD_DI_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign SD_DI_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign SD_DI_s1_master_qreq_vector = 1;

  //SD_DI_s1_reset_n assignment, which is an e_assign
  assign SD_DI_s1_reset_n = reset_n;

  assign SD_DI_s1_chipselect = cpu_0_data_master_granted_SD_DI_s1;
  //SD_DI_s1_firsttransfer first transaction, which is an e_assign
  assign SD_DI_s1_firsttransfer = SD_DI_s1_begins_xfer ? SD_DI_s1_unreg_firsttransfer : SD_DI_s1_reg_firsttransfer;

  //SD_DI_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign SD_DI_s1_unreg_firsttransfer = ~(SD_DI_s1_slavearbiterlockenable & SD_DI_s1_any_continuerequest);

  //SD_DI_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          SD_DI_s1_reg_firsttransfer <= 1'b1;
      else if (SD_DI_s1_begins_xfer)
          SD_DI_s1_reg_firsttransfer <= SD_DI_s1_unreg_firsttransfer;
    end


  //SD_DI_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign SD_DI_s1_beginbursttransfer_internal = SD_DI_s1_begins_xfer;

  //~SD_DI_s1_write_n assignment, which is an e_mux
  assign SD_DI_s1_write_n = ~(cpu_0_data_master_granted_SD_DI_s1 & cpu_0_data_master_write);

  assign shifted_address_to_SD_DI_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //SD_DI_s1_address mux, which is an e_mux
  assign SD_DI_s1_address = shifted_address_to_SD_DI_s1_from_cpu_0_data_master >> 2;

  //d1_SD_DI_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_SD_DI_s1_end_xfer <= 1;
      else 
        d1_SD_DI_s1_end_xfer <= SD_DI_s1_end_xfer;
    end


  //SD_DI_s1_waits_for_read in a cycle, which is an e_mux
  assign SD_DI_s1_waits_for_read = SD_DI_s1_in_a_read_cycle & SD_DI_s1_begins_xfer;

  //SD_DI_s1_in_a_read_cycle assignment, which is an e_assign
  assign SD_DI_s1_in_a_read_cycle = cpu_0_data_master_granted_SD_DI_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = SD_DI_s1_in_a_read_cycle;

  //SD_DI_s1_waits_for_write in a cycle, which is an e_mux
  assign SD_DI_s1_waits_for_write = SD_DI_s1_in_a_write_cycle & 0;

  //SD_DI_s1_in_a_write_cycle assignment, which is an e_assign
  assign SD_DI_s1_in_a_write_cycle = cpu_0_data_master_granted_SD_DI_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = SD_DI_s1_in_a_write_cycle;

  assign wait_for_SD_DI_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //SD_DI/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module SD_DO_s1_arbitrator (
                             // inputs:
                              SD_DO_s1_readdata,
                              clk,
                              cpu_0_data_master_address_to_slave,
                              cpu_0_data_master_latency_counter,
                              cpu_0_data_master_read,
                              cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                              cpu_0_data_master_write,
                              cpu_0_data_master_writedata,
                              reset_n,

                             // outputs:
                              SD_DO_s1_address,
                              SD_DO_s1_chipselect,
                              SD_DO_s1_readdata_from_sa,
                              SD_DO_s1_reset_n,
                              SD_DO_s1_write_n,
                              SD_DO_s1_writedata,
                              cpu_0_data_master_granted_SD_DO_s1,
                              cpu_0_data_master_qualified_request_SD_DO_s1,
                              cpu_0_data_master_read_data_valid_SD_DO_s1,
                              cpu_0_data_master_requests_SD_DO_s1,
                              d1_SD_DO_s1_end_xfer
                           )
;

  output  [  1: 0] SD_DO_s1_address;
  output           SD_DO_s1_chipselect;
  output  [ 31: 0] SD_DO_s1_readdata_from_sa;
  output           SD_DO_s1_reset_n;
  output           SD_DO_s1_write_n;
  output  [ 31: 0] SD_DO_s1_writedata;
  output           cpu_0_data_master_granted_SD_DO_s1;
  output           cpu_0_data_master_qualified_request_SD_DO_s1;
  output           cpu_0_data_master_read_data_valid_SD_DO_s1;
  output           cpu_0_data_master_requests_SD_DO_s1;
  output           d1_SD_DO_s1_end_xfer;
  input   [ 31: 0] SD_DO_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] SD_DO_s1_address;
  wire             SD_DO_s1_allgrants;
  wire             SD_DO_s1_allow_new_arb_cycle;
  wire             SD_DO_s1_any_bursting_master_saved_grant;
  wire             SD_DO_s1_any_continuerequest;
  wire             SD_DO_s1_arb_counter_enable;
  reg     [  1: 0] SD_DO_s1_arb_share_counter;
  wire    [  1: 0] SD_DO_s1_arb_share_counter_next_value;
  wire    [  1: 0] SD_DO_s1_arb_share_set_values;
  wire             SD_DO_s1_beginbursttransfer_internal;
  wire             SD_DO_s1_begins_xfer;
  wire             SD_DO_s1_chipselect;
  wire             SD_DO_s1_end_xfer;
  wire             SD_DO_s1_firsttransfer;
  wire             SD_DO_s1_grant_vector;
  wire             SD_DO_s1_in_a_read_cycle;
  wire             SD_DO_s1_in_a_write_cycle;
  wire             SD_DO_s1_master_qreq_vector;
  wire             SD_DO_s1_non_bursting_master_requests;
  wire    [ 31: 0] SD_DO_s1_readdata_from_sa;
  reg              SD_DO_s1_reg_firsttransfer;
  wire             SD_DO_s1_reset_n;
  reg              SD_DO_s1_slavearbiterlockenable;
  wire             SD_DO_s1_slavearbiterlockenable2;
  wire             SD_DO_s1_unreg_firsttransfer;
  wire             SD_DO_s1_waits_for_read;
  wire             SD_DO_s1_waits_for_write;
  wire             SD_DO_s1_write_n;
  wire    [ 31: 0] SD_DO_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_SD_DO_s1;
  wire             cpu_0_data_master_qualified_request_SD_DO_s1;
  wire             cpu_0_data_master_read_data_valid_SD_DO_s1;
  wire             cpu_0_data_master_requests_SD_DO_s1;
  wire             cpu_0_data_master_saved_grant_SD_DO_s1;
  reg              d1_SD_DO_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_SD_DO_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_SD_DO_s1_from_cpu_0_data_master;
  wire             wait_for_SD_DO_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~SD_DO_s1_end_xfer;
    end


  assign SD_DO_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_SD_DO_s1));
  //assign SD_DO_s1_readdata_from_sa = SD_DO_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign SD_DO_s1_readdata_from_sa = SD_DO_s1_readdata;

  assign cpu_0_data_master_requests_SD_DO_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002190) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //SD_DO_s1_arb_share_counter set values, which is an e_mux
  assign SD_DO_s1_arb_share_set_values = 1;

  //SD_DO_s1_non_bursting_master_requests mux, which is an e_mux
  assign SD_DO_s1_non_bursting_master_requests = cpu_0_data_master_requests_SD_DO_s1;

  //SD_DO_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign SD_DO_s1_any_bursting_master_saved_grant = 0;

  //SD_DO_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign SD_DO_s1_arb_share_counter_next_value = SD_DO_s1_firsttransfer ? (SD_DO_s1_arb_share_set_values - 1) : |SD_DO_s1_arb_share_counter ? (SD_DO_s1_arb_share_counter - 1) : 0;

  //SD_DO_s1_allgrants all slave grants, which is an e_mux
  assign SD_DO_s1_allgrants = |SD_DO_s1_grant_vector;

  //SD_DO_s1_end_xfer assignment, which is an e_assign
  assign SD_DO_s1_end_xfer = ~(SD_DO_s1_waits_for_read | SD_DO_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_SD_DO_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_SD_DO_s1 = SD_DO_s1_end_xfer & (~SD_DO_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //SD_DO_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign SD_DO_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_SD_DO_s1 & SD_DO_s1_allgrants) | (end_xfer_arb_share_counter_term_SD_DO_s1 & ~SD_DO_s1_non_bursting_master_requests);

  //SD_DO_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          SD_DO_s1_arb_share_counter <= 0;
      else if (SD_DO_s1_arb_counter_enable)
          SD_DO_s1_arb_share_counter <= SD_DO_s1_arb_share_counter_next_value;
    end


  //SD_DO_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          SD_DO_s1_slavearbiterlockenable <= 0;
      else if ((|SD_DO_s1_master_qreq_vector & end_xfer_arb_share_counter_term_SD_DO_s1) | (end_xfer_arb_share_counter_term_SD_DO_s1 & ~SD_DO_s1_non_bursting_master_requests))
          SD_DO_s1_slavearbiterlockenable <= |SD_DO_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master SD_DO/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = SD_DO_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //SD_DO_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign SD_DO_s1_slavearbiterlockenable2 = |SD_DO_s1_arb_share_counter_next_value;

  //cpu_0/data_master SD_DO/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = SD_DO_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //SD_DO_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign SD_DO_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_SD_DO_s1 = cpu_0_data_master_requests_SD_DO_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_SD_DO_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_SD_DO_s1 = cpu_0_data_master_granted_SD_DO_s1 & cpu_0_data_master_read & ~SD_DO_s1_waits_for_read;

  //SD_DO_s1_writedata mux, which is an e_mux
  assign SD_DO_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_SD_DO_s1 = cpu_0_data_master_qualified_request_SD_DO_s1;

  //cpu_0/data_master saved-grant SD_DO/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_SD_DO_s1 = cpu_0_data_master_requests_SD_DO_s1;

  //allow new arb cycle for SD_DO/s1, which is an e_assign
  assign SD_DO_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign SD_DO_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign SD_DO_s1_master_qreq_vector = 1;

  //SD_DO_s1_reset_n assignment, which is an e_assign
  assign SD_DO_s1_reset_n = reset_n;

  assign SD_DO_s1_chipselect = cpu_0_data_master_granted_SD_DO_s1;
  //SD_DO_s1_firsttransfer first transaction, which is an e_assign
  assign SD_DO_s1_firsttransfer = SD_DO_s1_begins_xfer ? SD_DO_s1_unreg_firsttransfer : SD_DO_s1_reg_firsttransfer;

  //SD_DO_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign SD_DO_s1_unreg_firsttransfer = ~(SD_DO_s1_slavearbiterlockenable & SD_DO_s1_any_continuerequest);

  //SD_DO_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          SD_DO_s1_reg_firsttransfer <= 1'b1;
      else if (SD_DO_s1_begins_xfer)
          SD_DO_s1_reg_firsttransfer <= SD_DO_s1_unreg_firsttransfer;
    end


  //SD_DO_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign SD_DO_s1_beginbursttransfer_internal = SD_DO_s1_begins_xfer;

  //~SD_DO_s1_write_n assignment, which is an e_mux
  assign SD_DO_s1_write_n = ~(cpu_0_data_master_granted_SD_DO_s1 & cpu_0_data_master_write);

  assign shifted_address_to_SD_DO_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //SD_DO_s1_address mux, which is an e_mux
  assign SD_DO_s1_address = shifted_address_to_SD_DO_s1_from_cpu_0_data_master >> 2;

  //d1_SD_DO_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_SD_DO_s1_end_xfer <= 1;
      else 
        d1_SD_DO_s1_end_xfer <= SD_DO_s1_end_xfer;
    end


  //SD_DO_s1_waits_for_read in a cycle, which is an e_mux
  assign SD_DO_s1_waits_for_read = SD_DO_s1_in_a_read_cycle & SD_DO_s1_begins_xfer;

  //SD_DO_s1_in_a_read_cycle assignment, which is an e_assign
  assign SD_DO_s1_in_a_read_cycle = cpu_0_data_master_granted_SD_DO_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = SD_DO_s1_in_a_read_cycle;

  //SD_DO_s1_waits_for_write in a cycle, which is an e_mux
  assign SD_DO_s1_waits_for_write = SD_DO_s1_in_a_write_cycle & 0;

  //SD_DO_s1_in_a_write_cycle assignment, which is an e_assign
  assign SD_DO_s1_in_a_write_cycle = cpu_0_data_master_granted_SD_DO_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = SD_DO_s1_in_a_write_cycle;

  assign wait_for_SD_DO_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //SD_DO/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module TEMP_DATA_s1_arbitrator (
                                 // inputs:
                                  TEMP_DATA_s1_readdata,
                                  clk,
                                  cpu_0_data_master_address_to_slave,
                                  cpu_0_data_master_latency_counter,
                                  cpu_0_data_master_read,
                                  cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                  cpu_0_data_master_write,
                                  cpu_0_data_master_writedata,
                                  reset_n,

                                 // outputs:
                                  TEMP_DATA_s1_address,
                                  TEMP_DATA_s1_chipselect,
                                  TEMP_DATA_s1_readdata_from_sa,
                                  TEMP_DATA_s1_reset_n,
                                  TEMP_DATA_s1_write_n,
                                  TEMP_DATA_s1_writedata,
                                  cpu_0_data_master_granted_TEMP_DATA_s1,
                                  cpu_0_data_master_qualified_request_TEMP_DATA_s1,
                                  cpu_0_data_master_read_data_valid_TEMP_DATA_s1,
                                  cpu_0_data_master_requests_TEMP_DATA_s1,
                                  d1_TEMP_DATA_s1_end_xfer
                               )
;

  output  [  1: 0] TEMP_DATA_s1_address;
  output           TEMP_DATA_s1_chipselect;
  output  [ 31: 0] TEMP_DATA_s1_readdata_from_sa;
  output           TEMP_DATA_s1_reset_n;
  output           TEMP_DATA_s1_write_n;
  output  [ 31: 0] TEMP_DATA_s1_writedata;
  output           cpu_0_data_master_granted_TEMP_DATA_s1;
  output           cpu_0_data_master_qualified_request_TEMP_DATA_s1;
  output           cpu_0_data_master_read_data_valid_TEMP_DATA_s1;
  output           cpu_0_data_master_requests_TEMP_DATA_s1;
  output           d1_TEMP_DATA_s1_end_xfer;
  input   [ 31: 0] TEMP_DATA_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] TEMP_DATA_s1_address;
  wire             TEMP_DATA_s1_allgrants;
  wire             TEMP_DATA_s1_allow_new_arb_cycle;
  wire             TEMP_DATA_s1_any_bursting_master_saved_grant;
  wire             TEMP_DATA_s1_any_continuerequest;
  wire             TEMP_DATA_s1_arb_counter_enable;
  reg     [  1: 0] TEMP_DATA_s1_arb_share_counter;
  wire    [  1: 0] TEMP_DATA_s1_arb_share_counter_next_value;
  wire    [  1: 0] TEMP_DATA_s1_arb_share_set_values;
  wire             TEMP_DATA_s1_beginbursttransfer_internal;
  wire             TEMP_DATA_s1_begins_xfer;
  wire             TEMP_DATA_s1_chipselect;
  wire             TEMP_DATA_s1_end_xfer;
  wire             TEMP_DATA_s1_firsttransfer;
  wire             TEMP_DATA_s1_grant_vector;
  wire             TEMP_DATA_s1_in_a_read_cycle;
  wire             TEMP_DATA_s1_in_a_write_cycle;
  wire             TEMP_DATA_s1_master_qreq_vector;
  wire             TEMP_DATA_s1_non_bursting_master_requests;
  wire    [ 31: 0] TEMP_DATA_s1_readdata_from_sa;
  reg              TEMP_DATA_s1_reg_firsttransfer;
  wire             TEMP_DATA_s1_reset_n;
  reg              TEMP_DATA_s1_slavearbiterlockenable;
  wire             TEMP_DATA_s1_slavearbiterlockenable2;
  wire             TEMP_DATA_s1_unreg_firsttransfer;
  wire             TEMP_DATA_s1_waits_for_read;
  wire             TEMP_DATA_s1_waits_for_write;
  wire             TEMP_DATA_s1_write_n;
  wire    [ 31: 0] TEMP_DATA_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_TEMP_DATA_s1;
  wire             cpu_0_data_master_qualified_request_TEMP_DATA_s1;
  wire             cpu_0_data_master_read_data_valid_TEMP_DATA_s1;
  wire             cpu_0_data_master_requests_TEMP_DATA_s1;
  wire             cpu_0_data_master_saved_grant_TEMP_DATA_s1;
  reg              d1_TEMP_DATA_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_TEMP_DATA_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_TEMP_DATA_s1_from_cpu_0_data_master;
  wire             wait_for_TEMP_DATA_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~TEMP_DATA_s1_end_xfer;
    end


  assign TEMP_DATA_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_TEMP_DATA_s1));
  //assign TEMP_DATA_s1_readdata_from_sa = TEMP_DATA_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign TEMP_DATA_s1_readdata_from_sa = TEMP_DATA_s1_readdata;

  assign cpu_0_data_master_requests_TEMP_DATA_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h40020c0) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //TEMP_DATA_s1_arb_share_counter set values, which is an e_mux
  assign TEMP_DATA_s1_arb_share_set_values = 1;

  //TEMP_DATA_s1_non_bursting_master_requests mux, which is an e_mux
  assign TEMP_DATA_s1_non_bursting_master_requests = cpu_0_data_master_requests_TEMP_DATA_s1;

  //TEMP_DATA_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign TEMP_DATA_s1_any_bursting_master_saved_grant = 0;

  //TEMP_DATA_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign TEMP_DATA_s1_arb_share_counter_next_value = TEMP_DATA_s1_firsttransfer ? (TEMP_DATA_s1_arb_share_set_values - 1) : |TEMP_DATA_s1_arb_share_counter ? (TEMP_DATA_s1_arb_share_counter - 1) : 0;

  //TEMP_DATA_s1_allgrants all slave grants, which is an e_mux
  assign TEMP_DATA_s1_allgrants = |TEMP_DATA_s1_grant_vector;

  //TEMP_DATA_s1_end_xfer assignment, which is an e_assign
  assign TEMP_DATA_s1_end_xfer = ~(TEMP_DATA_s1_waits_for_read | TEMP_DATA_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_TEMP_DATA_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_TEMP_DATA_s1 = TEMP_DATA_s1_end_xfer & (~TEMP_DATA_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //TEMP_DATA_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign TEMP_DATA_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_TEMP_DATA_s1 & TEMP_DATA_s1_allgrants) | (end_xfer_arb_share_counter_term_TEMP_DATA_s1 & ~TEMP_DATA_s1_non_bursting_master_requests);

  //TEMP_DATA_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          TEMP_DATA_s1_arb_share_counter <= 0;
      else if (TEMP_DATA_s1_arb_counter_enable)
          TEMP_DATA_s1_arb_share_counter <= TEMP_DATA_s1_arb_share_counter_next_value;
    end


  //TEMP_DATA_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          TEMP_DATA_s1_slavearbiterlockenable <= 0;
      else if ((|TEMP_DATA_s1_master_qreq_vector & end_xfer_arb_share_counter_term_TEMP_DATA_s1) | (end_xfer_arb_share_counter_term_TEMP_DATA_s1 & ~TEMP_DATA_s1_non_bursting_master_requests))
          TEMP_DATA_s1_slavearbiterlockenable <= |TEMP_DATA_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master TEMP_DATA/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = TEMP_DATA_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //TEMP_DATA_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign TEMP_DATA_s1_slavearbiterlockenable2 = |TEMP_DATA_s1_arb_share_counter_next_value;

  //cpu_0/data_master TEMP_DATA/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = TEMP_DATA_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //TEMP_DATA_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign TEMP_DATA_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_TEMP_DATA_s1 = cpu_0_data_master_requests_TEMP_DATA_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_TEMP_DATA_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_TEMP_DATA_s1 = cpu_0_data_master_granted_TEMP_DATA_s1 & cpu_0_data_master_read & ~TEMP_DATA_s1_waits_for_read;

  //TEMP_DATA_s1_writedata mux, which is an e_mux
  assign TEMP_DATA_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_TEMP_DATA_s1 = cpu_0_data_master_qualified_request_TEMP_DATA_s1;

  //cpu_0/data_master saved-grant TEMP_DATA/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_TEMP_DATA_s1 = cpu_0_data_master_requests_TEMP_DATA_s1;

  //allow new arb cycle for TEMP_DATA/s1, which is an e_assign
  assign TEMP_DATA_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign TEMP_DATA_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign TEMP_DATA_s1_master_qreq_vector = 1;

  //TEMP_DATA_s1_reset_n assignment, which is an e_assign
  assign TEMP_DATA_s1_reset_n = reset_n;

  assign TEMP_DATA_s1_chipselect = cpu_0_data_master_granted_TEMP_DATA_s1;
  //TEMP_DATA_s1_firsttransfer first transaction, which is an e_assign
  assign TEMP_DATA_s1_firsttransfer = TEMP_DATA_s1_begins_xfer ? TEMP_DATA_s1_unreg_firsttransfer : TEMP_DATA_s1_reg_firsttransfer;

  //TEMP_DATA_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign TEMP_DATA_s1_unreg_firsttransfer = ~(TEMP_DATA_s1_slavearbiterlockenable & TEMP_DATA_s1_any_continuerequest);

  //TEMP_DATA_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          TEMP_DATA_s1_reg_firsttransfer <= 1'b1;
      else if (TEMP_DATA_s1_begins_xfer)
          TEMP_DATA_s1_reg_firsttransfer <= TEMP_DATA_s1_unreg_firsttransfer;
    end


  //TEMP_DATA_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign TEMP_DATA_s1_beginbursttransfer_internal = TEMP_DATA_s1_begins_xfer;

  //~TEMP_DATA_s1_write_n assignment, which is an e_mux
  assign TEMP_DATA_s1_write_n = ~(cpu_0_data_master_granted_TEMP_DATA_s1 & cpu_0_data_master_write);

  assign shifted_address_to_TEMP_DATA_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //TEMP_DATA_s1_address mux, which is an e_mux
  assign TEMP_DATA_s1_address = shifted_address_to_TEMP_DATA_s1_from_cpu_0_data_master >> 2;

  //d1_TEMP_DATA_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_TEMP_DATA_s1_end_xfer <= 1;
      else 
        d1_TEMP_DATA_s1_end_xfer <= TEMP_DATA_s1_end_xfer;
    end


  //TEMP_DATA_s1_waits_for_read in a cycle, which is an e_mux
  assign TEMP_DATA_s1_waits_for_read = TEMP_DATA_s1_in_a_read_cycle & TEMP_DATA_s1_begins_xfer;

  //TEMP_DATA_s1_in_a_read_cycle assignment, which is an e_assign
  assign TEMP_DATA_s1_in_a_read_cycle = cpu_0_data_master_granted_TEMP_DATA_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = TEMP_DATA_s1_in_a_read_cycle;

  //TEMP_DATA_s1_waits_for_write in a cycle, which is an e_mux
  assign TEMP_DATA_s1_waits_for_write = TEMP_DATA_s1_in_a_write_cycle & 0;

  //TEMP_DATA_s1_in_a_write_cycle assignment, which is an e_assign
  assign TEMP_DATA_s1_in_a_write_cycle = cpu_0_data_master_granted_TEMP_DATA_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = TEMP_DATA_s1_in_a_write_cycle;

  assign wait_for_TEMP_DATA_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //TEMP_DATA/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module TUBE_EN_s1_arbitrator (
                               // inputs:
                                TUBE_EN_s1_readdata,
                                clk,
                                cpu_0_data_master_address_to_slave,
                                cpu_0_data_master_latency_counter,
                                cpu_0_data_master_read,
                                cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                cpu_0_data_master_write,
                                cpu_0_data_master_writedata,
                                reset_n,

                               // outputs:
                                TUBE_EN_s1_address,
                                TUBE_EN_s1_chipselect,
                                TUBE_EN_s1_readdata_from_sa,
                                TUBE_EN_s1_reset_n,
                                TUBE_EN_s1_write_n,
                                TUBE_EN_s1_writedata,
                                cpu_0_data_master_granted_TUBE_EN_s1,
                                cpu_0_data_master_qualified_request_TUBE_EN_s1,
                                cpu_0_data_master_read_data_valid_TUBE_EN_s1,
                                cpu_0_data_master_requests_TUBE_EN_s1,
                                d1_TUBE_EN_s1_end_xfer
                             )
;

  output  [  1: 0] TUBE_EN_s1_address;
  output           TUBE_EN_s1_chipselect;
  output  [ 31: 0] TUBE_EN_s1_readdata_from_sa;
  output           TUBE_EN_s1_reset_n;
  output           TUBE_EN_s1_write_n;
  output  [ 31: 0] TUBE_EN_s1_writedata;
  output           cpu_0_data_master_granted_TUBE_EN_s1;
  output           cpu_0_data_master_qualified_request_TUBE_EN_s1;
  output           cpu_0_data_master_read_data_valid_TUBE_EN_s1;
  output           cpu_0_data_master_requests_TUBE_EN_s1;
  output           d1_TUBE_EN_s1_end_xfer;
  input   [ 31: 0] TUBE_EN_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] TUBE_EN_s1_address;
  wire             TUBE_EN_s1_allgrants;
  wire             TUBE_EN_s1_allow_new_arb_cycle;
  wire             TUBE_EN_s1_any_bursting_master_saved_grant;
  wire             TUBE_EN_s1_any_continuerequest;
  wire             TUBE_EN_s1_arb_counter_enable;
  reg     [  1: 0] TUBE_EN_s1_arb_share_counter;
  wire    [  1: 0] TUBE_EN_s1_arb_share_counter_next_value;
  wire    [  1: 0] TUBE_EN_s1_arb_share_set_values;
  wire             TUBE_EN_s1_beginbursttransfer_internal;
  wire             TUBE_EN_s1_begins_xfer;
  wire             TUBE_EN_s1_chipselect;
  wire             TUBE_EN_s1_end_xfer;
  wire             TUBE_EN_s1_firsttransfer;
  wire             TUBE_EN_s1_grant_vector;
  wire             TUBE_EN_s1_in_a_read_cycle;
  wire             TUBE_EN_s1_in_a_write_cycle;
  wire             TUBE_EN_s1_master_qreq_vector;
  wire             TUBE_EN_s1_non_bursting_master_requests;
  wire    [ 31: 0] TUBE_EN_s1_readdata_from_sa;
  reg              TUBE_EN_s1_reg_firsttransfer;
  wire             TUBE_EN_s1_reset_n;
  reg              TUBE_EN_s1_slavearbiterlockenable;
  wire             TUBE_EN_s1_slavearbiterlockenable2;
  wire             TUBE_EN_s1_unreg_firsttransfer;
  wire             TUBE_EN_s1_waits_for_read;
  wire             TUBE_EN_s1_waits_for_write;
  wire             TUBE_EN_s1_write_n;
  wire    [ 31: 0] TUBE_EN_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_TUBE_EN_s1;
  wire             cpu_0_data_master_qualified_request_TUBE_EN_s1;
  wire             cpu_0_data_master_read_data_valid_TUBE_EN_s1;
  wire             cpu_0_data_master_requests_TUBE_EN_s1;
  wire             cpu_0_data_master_saved_grant_TUBE_EN_s1;
  reg              d1_TUBE_EN_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_TUBE_EN_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_TUBE_EN_s1_from_cpu_0_data_master;
  wire             wait_for_TUBE_EN_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~TUBE_EN_s1_end_xfer;
    end


  assign TUBE_EN_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_TUBE_EN_s1));
  //assign TUBE_EN_s1_readdata_from_sa = TUBE_EN_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign TUBE_EN_s1_readdata_from_sa = TUBE_EN_s1_readdata;

  assign cpu_0_data_master_requests_TUBE_EN_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h40022b0) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //TUBE_EN_s1_arb_share_counter set values, which is an e_mux
  assign TUBE_EN_s1_arb_share_set_values = 1;

  //TUBE_EN_s1_non_bursting_master_requests mux, which is an e_mux
  assign TUBE_EN_s1_non_bursting_master_requests = cpu_0_data_master_requests_TUBE_EN_s1;

  //TUBE_EN_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign TUBE_EN_s1_any_bursting_master_saved_grant = 0;

  //TUBE_EN_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign TUBE_EN_s1_arb_share_counter_next_value = TUBE_EN_s1_firsttransfer ? (TUBE_EN_s1_arb_share_set_values - 1) : |TUBE_EN_s1_arb_share_counter ? (TUBE_EN_s1_arb_share_counter - 1) : 0;

  //TUBE_EN_s1_allgrants all slave grants, which is an e_mux
  assign TUBE_EN_s1_allgrants = |TUBE_EN_s1_grant_vector;

  //TUBE_EN_s1_end_xfer assignment, which is an e_assign
  assign TUBE_EN_s1_end_xfer = ~(TUBE_EN_s1_waits_for_read | TUBE_EN_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_TUBE_EN_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_TUBE_EN_s1 = TUBE_EN_s1_end_xfer & (~TUBE_EN_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //TUBE_EN_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign TUBE_EN_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_TUBE_EN_s1 & TUBE_EN_s1_allgrants) | (end_xfer_arb_share_counter_term_TUBE_EN_s1 & ~TUBE_EN_s1_non_bursting_master_requests);

  //TUBE_EN_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          TUBE_EN_s1_arb_share_counter <= 0;
      else if (TUBE_EN_s1_arb_counter_enable)
          TUBE_EN_s1_arb_share_counter <= TUBE_EN_s1_arb_share_counter_next_value;
    end


  //TUBE_EN_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          TUBE_EN_s1_slavearbiterlockenable <= 0;
      else if ((|TUBE_EN_s1_master_qreq_vector & end_xfer_arb_share_counter_term_TUBE_EN_s1) | (end_xfer_arb_share_counter_term_TUBE_EN_s1 & ~TUBE_EN_s1_non_bursting_master_requests))
          TUBE_EN_s1_slavearbiterlockenable <= |TUBE_EN_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master TUBE_EN/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = TUBE_EN_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //TUBE_EN_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign TUBE_EN_s1_slavearbiterlockenable2 = |TUBE_EN_s1_arb_share_counter_next_value;

  //cpu_0/data_master TUBE_EN/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = TUBE_EN_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //TUBE_EN_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign TUBE_EN_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_TUBE_EN_s1 = cpu_0_data_master_requests_TUBE_EN_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_TUBE_EN_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_TUBE_EN_s1 = cpu_0_data_master_granted_TUBE_EN_s1 & cpu_0_data_master_read & ~TUBE_EN_s1_waits_for_read;

  //TUBE_EN_s1_writedata mux, which is an e_mux
  assign TUBE_EN_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_TUBE_EN_s1 = cpu_0_data_master_qualified_request_TUBE_EN_s1;

  //cpu_0/data_master saved-grant TUBE_EN/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_TUBE_EN_s1 = cpu_0_data_master_requests_TUBE_EN_s1;

  //allow new arb cycle for TUBE_EN/s1, which is an e_assign
  assign TUBE_EN_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign TUBE_EN_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign TUBE_EN_s1_master_qreq_vector = 1;

  //TUBE_EN_s1_reset_n assignment, which is an e_assign
  assign TUBE_EN_s1_reset_n = reset_n;

  assign TUBE_EN_s1_chipselect = cpu_0_data_master_granted_TUBE_EN_s1;
  //TUBE_EN_s1_firsttransfer first transaction, which is an e_assign
  assign TUBE_EN_s1_firsttransfer = TUBE_EN_s1_begins_xfer ? TUBE_EN_s1_unreg_firsttransfer : TUBE_EN_s1_reg_firsttransfer;

  //TUBE_EN_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign TUBE_EN_s1_unreg_firsttransfer = ~(TUBE_EN_s1_slavearbiterlockenable & TUBE_EN_s1_any_continuerequest);

  //TUBE_EN_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          TUBE_EN_s1_reg_firsttransfer <= 1'b1;
      else if (TUBE_EN_s1_begins_xfer)
          TUBE_EN_s1_reg_firsttransfer <= TUBE_EN_s1_unreg_firsttransfer;
    end


  //TUBE_EN_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign TUBE_EN_s1_beginbursttransfer_internal = TUBE_EN_s1_begins_xfer;

  //~TUBE_EN_s1_write_n assignment, which is an e_mux
  assign TUBE_EN_s1_write_n = ~(cpu_0_data_master_granted_TUBE_EN_s1 & cpu_0_data_master_write);

  assign shifted_address_to_TUBE_EN_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //TUBE_EN_s1_address mux, which is an e_mux
  assign TUBE_EN_s1_address = shifted_address_to_TUBE_EN_s1_from_cpu_0_data_master >> 2;

  //d1_TUBE_EN_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_TUBE_EN_s1_end_xfer <= 1;
      else 
        d1_TUBE_EN_s1_end_xfer <= TUBE_EN_s1_end_xfer;
    end


  //TUBE_EN_s1_waits_for_read in a cycle, which is an e_mux
  assign TUBE_EN_s1_waits_for_read = TUBE_EN_s1_in_a_read_cycle & TUBE_EN_s1_begins_xfer;

  //TUBE_EN_s1_in_a_read_cycle assignment, which is an e_assign
  assign TUBE_EN_s1_in_a_read_cycle = cpu_0_data_master_granted_TUBE_EN_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = TUBE_EN_s1_in_a_read_cycle;

  //TUBE_EN_s1_waits_for_write in a cycle, which is an e_mux
  assign TUBE_EN_s1_waits_for_write = TUBE_EN_s1_in_a_write_cycle & 0;

  //TUBE_EN_s1_in_a_write_cycle assignment, which is an e_assign
  assign TUBE_EN_s1_in_a_write_cycle = cpu_0_data_master_granted_TUBE_EN_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = TUBE_EN_s1_in_a_write_cycle;

  assign wait_for_TUBE_EN_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //TUBE_EN/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module UART_RX_DATA_s1_arbitrator (
                                    // inputs:
                                     UART_RX_DATA_s1_readdata,
                                     clk,
                                     cpu_0_data_master_address_to_slave,
                                     cpu_0_data_master_latency_counter,
                                     cpu_0_data_master_read,
                                     cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                     cpu_0_data_master_write,
                                     cpu_0_data_master_writedata,
                                     reset_n,

                                    // outputs:
                                     UART_RX_DATA_s1_address,
                                     UART_RX_DATA_s1_chipselect,
                                     UART_RX_DATA_s1_readdata_from_sa,
                                     UART_RX_DATA_s1_reset_n,
                                     UART_RX_DATA_s1_write_n,
                                     UART_RX_DATA_s1_writedata,
                                     cpu_0_data_master_granted_UART_RX_DATA_s1,
                                     cpu_0_data_master_qualified_request_UART_RX_DATA_s1,
                                     cpu_0_data_master_read_data_valid_UART_RX_DATA_s1,
                                     cpu_0_data_master_requests_UART_RX_DATA_s1,
                                     d1_UART_RX_DATA_s1_end_xfer
                                  )
;

  output  [  1: 0] UART_RX_DATA_s1_address;
  output           UART_RX_DATA_s1_chipselect;
  output  [ 31: 0] UART_RX_DATA_s1_readdata_from_sa;
  output           UART_RX_DATA_s1_reset_n;
  output           UART_RX_DATA_s1_write_n;
  output  [ 31: 0] UART_RX_DATA_s1_writedata;
  output           cpu_0_data_master_granted_UART_RX_DATA_s1;
  output           cpu_0_data_master_qualified_request_UART_RX_DATA_s1;
  output           cpu_0_data_master_read_data_valid_UART_RX_DATA_s1;
  output           cpu_0_data_master_requests_UART_RX_DATA_s1;
  output           d1_UART_RX_DATA_s1_end_xfer;
  input   [ 31: 0] UART_RX_DATA_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] UART_RX_DATA_s1_address;
  wire             UART_RX_DATA_s1_allgrants;
  wire             UART_RX_DATA_s1_allow_new_arb_cycle;
  wire             UART_RX_DATA_s1_any_bursting_master_saved_grant;
  wire             UART_RX_DATA_s1_any_continuerequest;
  wire             UART_RX_DATA_s1_arb_counter_enable;
  reg     [  1: 0] UART_RX_DATA_s1_arb_share_counter;
  wire    [  1: 0] UART_RX_DATA_s1_arb_share_counter_next_value;
  wire    [  1: 0] UART_RX_DATA_s1_arb_share_set_values;
  wire             UART_RX_DATA_s1_beginbursttransfer_internal;
  wire             UART_RX_DATA_s1_begins_xfer;
  wire             UART_RX_DATA_s1_chipselect;
  wire             UART_RX_DATA_s1_end_xfer;
  wire             UART_RX_DATA_s1_firsttransfer;
  wire             UART_RX_DATA_s1_grant_vector;
  wire             UART_RX_DATA_s1_in_a_read_cycle;
  wire             UART_RX_DATA_s1_in_a_write_cycle;
  wire             UART_RX_DATA_s1_master_qreq_vector;
  wire             UART_RX_DATA_s1_non_bursting_master_requests;
  wire    [ 31: 0] UART_RX_DATA_s1_readdata_from_sa;
  reg              UART_RX_DATA_s1_reg_firsttransfer;
  wire             UART_RX_DATA_s1_reset_n;
  reg              UART_RX_DATA_s1_slavearbiterlockenable;
  wire             UART_RX_DATA_s1_slavearbiterlockenable2;
  wire             UART_RX_DATA_s1_unreg_firsttransfer;
  wire             UART_RX_DATA_s1_waits_for_read;
  wire             UART_RX_DATA_s1_waits_for_write;
  wire             UART_RX_DATA_s1_write_n;
  wire    [ 31: 0] UART_RX_DATA_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_UART_RX_DATA_s1;
  wire             cpu_0_data_master_qualified_request_UART_RX_DATA_s1;
  wire             cpu_0_data_master_read_data_valid_UART_RX_DATA_s1;
  wire             cpu_0_data_master_requests_UART_RX_DATA_s1;
  wire             cpu_0_data_master_saved_grant_UART_RX_DATA_s1;
  reg              d1_UART_RX_DATA_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_UART_RX_DATA_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_UART_RX_DATA_s1_from_cpu_0_data_master;
  wire             wait_for_UART_RX_DATA_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~UART_RX_DATA_s1_end_xfer;
    end


  assign UART_RX_DATA_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_UART_RX_DATA_s1));
  //assign UART_RX_DATA_s1_readdata_from_sa = UART_RX_DATA_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign UART_RX_DATA_s1_readdata_from_sa = UART_RX_DATA_s1_readdata;

  assign cpu_0_data_master_requests_UART_RX_DATA_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h40020e0) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //UART_RX_DATA_s1_arb_share_counter set values, which is an e_mux
  assign UART_RX_DATA_s1_arb_share_set_values = 1;

  //UART_RX_DATA_s1_non_bursting_master_requests mux, which is an e_mux
  assign UART_RX_DATA_s1_non_bursting_master_requests = cpu_0_data_master_requests_UART_RX_DATA_s1;

  //UART_RX_DATA_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign UART_RX_DATA_s1_any_bursting_master_saved_grant = 0;

  //UART_RX_DATA_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign UART_RX_DATA_s1_arb_share_counter_next_value = UART_RX_DATA_s1_firsttransfer ? (UART_RX_DATA_s1_arb_share_set_values - 1) : |UART_RX_DATA_s1_arb_share_counter ? (UART_RX_DATA_s1_arb_share_counter - 1) : 0;

  //UART_RX_DATA_s1_allgrants all slave grants, which is an e_mux
  assign UART_RX_DATA_s1_allgrants = |UART_RX_DATA_s1_grant_vector;

  //UART_RX_DATA_s1_end_xfer assignment, which is an e_assign
  assign UART_RX_DATA_s1_end_xfer = ~(UART_RX_DATA_s1_waits_for_read | UART_RX_DATA_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_UART_RX_DATA_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_UART_RX_DATA_s1 = UART_RX_DATA_s1_end_xfer & (~UART_RX_DATA_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //UART_RX_DATA_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign UART_RX_DATA_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_UART_RX_DATA_s1 & UART_RX_DATA_s1_allgrants) | (end_xfer_arb_share_counter_term_UART_RX_DATA_s1 & ~UART_RX_DATA_s1_non_bursting_master_requests);

  //UART_RX_DATA_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          UART_RX_DATA_s1_arb_share_counter <= 0;
      else if (UART_RX_DATA_s1_arb_counter_enable)
          UART_RX_DATA_s1_arb_share_counter <= UART_RX_DATA_s1_arb_share_counter_next_value;
    end


  //UART_RX_DATA_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          UART_RX_DATA_s1_slavearbiterlockenable <= 0;
      else if ((|UART_RX_DATA_s1_master_qreq_vector & end_xfer_arb_share_counter_term_UART_RX_DATA_s1) | (end_xfer_arb_share_counter_term_UART_RX_DATA_s1 & ~UART_RX_DATA_s1_non_bursting_master_requests))
          UART_RX_DATA_s1_slavearbiterlockenable <= |UART_RX_DATA_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master UART_RX_DATA/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = UART_RX_DATA_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //UART_RX_DATA_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign UART_RX_DATA_s1_slavearbiterlockenable2 = |UART_RX_DATA_s1_arb_share_counter_next_value;

  //cpu_0/data_master UART_RX_DATA/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = UART_RX_DATA_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //UART_RX_DATA_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign UART_RX_DATA_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_UART_RX_DATA_s1 = cpu_0_data_master_requests_UART_RX_DATA_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_UART_RX_DATA_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_UART_RX_DATA_s1 = cpu_0_data_master_granted_UART_RX_DATA_s1 & cpu_0_data_master_read & ~UART_RX_DATA_s1_waits_for_read;

  //UART_RX_DATA_s1_writedata mux, which is an e_mux
  assign UART_RX_DATA_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_UART_RX_DATA_s1 = cpu_0_data_master_qualified_request_UART_RX_DATA_s1;

  //cpu_0/data_master saved-grant UART_RX_DATA/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_UART_RX_DATA_s1 = cpu_0_data_master_requests_UART_RX_DATA_s1;

  //allow new arb cycle for UART_RX_DATA/s1, which is an e_assign
  assign UART_RX_DATA_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign UART_RX_DATA_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign UART_RX_DATA_s1_master_qreq_vector = 1;

  //UART_RX_DATA_s1_reset_n assignment, which is an e_assign
  assign UART_RX_DATA_s1_reset_n = reset_n;

  assign UART_RX_DATA_s1_chipselect = cpu_0_data_master_granted_UART_RX_DATA_s1;
  //UART_RX_DATA_s1_firsttransfer first transaction, which is an e_assign
  assign UART_RX_DATA_s1_firsttransfer = UART_RX_DATA_s1_begins_xfer ? UART_RX_DATA_s1_unreg_firsttransfer : UART_RX_DATA_s1_reg_firsttransfer;

  //UART_RX_DATA_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign UART_RX_DATA_s1_unreg_firsttransfer = ~(UART_RX_DATA_s1_slavearbiterlockenable & UART_RX_DATA_s1_any_continuerequest);

  //UART_RX_DATA_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          UART_RX_DATA_s1_reg_firsttransfer <= 1'b1;
      else if (UART_RX_DATA_s1_begins_xfer)
          UART_RX_DATA_s1_reg_firsttransfer <= UART_RX_DATA_s1_unreg_firsttransfer;
    end


  //UART_RX_DATA_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign UART_RX_DATA_s1_beginbursttransfer_internal = UART_RX_DATA_s1_begins_xfer;

  //~UART_RX_DATA_s1_write_n assignment, which is an e_mux
  assign UART_RX_DATA_s1_write_n = ~(cpu_0_data_master_granted_UART_RX_DATA_s1 & cpu_0_data_master_write);

  assign shifted_address_to_UART_RX_DATA_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //UART_RX_DATA_s1_address mux, which is an e_mux
  assign UART_RX_DATA_s1_address = shifted_address_to_UART_RX_DATA_s1_from_cpu_0_data_master >> 2;

  //d1_UART_RX_DATA_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_UART_RX_DATA_s1_end_xfer <= 1;
      else 
        d1_UART_RX_DATA_s1_end_xfer <= UART_RX_DATA_s1_end_xfer;
    end


  //UART_RX_DATA_s1_waits_for_read in a cycle, which is an e_mux
  assign UART_RX_DATA_s1_waits_for_read = UART_RX_DATA_s1_in_a_read_cycle & UART_RX_DATA_s1_begins_xfer;

  //UART_RX_DATA_s1_in_a_read_cycle assignment, which is an e_assign
  assign UART_RX_DATA_s1_in_a_read_cycle = cpu_0_data_master_granted_UART_RX_DATA_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = UART_RX_DATA_s1_in_a_read_cycle;

  //UART_RX_DATA_s1_waits_for_write in a cycle, which is an e_mux
  assign UART_RX_DATA_s1_waits_for_write = UART_RX_DATA_s1_in_a_write_cycle & 0;

  //UART_RX_DATA_s1_in_a_write_cycle assignment, which is an e_assign
  assign UART_RX_DATA_s1_in_a_write_cycle = cpu_0_data_master_granted_UART_RX_DATA_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = UART_RX_DATA_s1_in_a_write_cycle;

  assign wait_for_UART_RX_DATA_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //UART_RX_DATA/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module USB_INT_I_s1_arbitrator (
                                 // inputs:
                                  USB_INT_I_s1_readdata,
                                  clk,
                                  cpu_0_data_master_address_to_slave,
                                  cpu_0_data_master_latency_counter,
                                  cpu_0_data_master_read,
                                  cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                  cpu_0_data_master_write,
                                  reset_n,

                                 // outputs:
                                  USB_INT_I_s1_address,
                                  USB_INT_I_s1_readdata_from_sa,
                                  USB_INT_I_s1_reset_n,
                                  cpu_0_data_master_granted_USB_INT_I_s1,
                                  cpu_0_data_master_qualified_request_USB_INT_I_s1,
                                  cpu_0_data_master_read_data_valid_USB_INT_I_s1,
                                  cpu_0_data_master_requests_USB_INT_I_s1,
                                  d1_USB_INT_I_s1_end_xfer
                               )
;

  output  [  1: 0] USB_INT_I_s1_address;
  output  [ 31: 0] USB_INT_I_s1_readdata_from_sa;
  output           USB_INT_I_s1_reset_n;
  output           cpu_0_data_master_granted_USB_INT_I_s1;
  output           cpu_0_data_master_qualified_request_USB_INT_I_s1;
  output           cpu_0_data_master_read_data_valid_USB_INT_I_s1;
  output           cpu_0_data_master_requests_USB_INT_I_s1;
  output           d1_USB_INT_I_s1_end_xfer;
  input   [ 31: 0] USB_INT_I_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input            reset_n;

  wire    [  1: 0] USB_INT_I_s1_address;
  wire             USB_INT_I_s1_allgrants;
  wire             USB_INT_I_s1_allow_new_arb_cycle;
  wire             USB_INT_I_s1_any_bursting_master_saved_grant;
  wire             USB_INT_I_s1_any_continuerequest;
  wire             USB_INT_I_s1_arb_counter_enable;
  reg     [  1: 0] USB_INT_I_s1_arb_share_counter;
  wire    [  1: 0] USB_INT_I_s1_arb_share_counter_next_value;
  wire    [  1: 0] USB_INT_I_s1_arb_share_set_values;
  wire             USB_INT_I_s1_beginbursttransfer_internal;
  wire             USB_INT_I_s1_begins_xfer;
  wire             USB_INT_I_s1_end_xfer;
  wire             USB_INT_I_s1_firsttransfer;
  wire             USB_INT_I_s1_grant_vector;
  wire             USB_INT_I_s1_in_a_read_cycle;
  wire             USB_INT_I_s1_in_a_write_cycle;
  wire             USB_INT_I_s1_master_qreq_vector;
  wire             USB_INT_I_s1_non_bursting_master_requests;
  wire    [ 31: 0] USB_INT_I_s1_readdata_from_sa;
  reg              USB_INT_I_s1_reg_firsttransfer;
  wire             USB_INT_I_s1_reset_n;
  reg              USB_INT_I_s1_slavearbiterlockenable;
  wire             USB_INT_I_s1_slavearbiterlockenable2;
  wire             USB_INT_I_s1_unreg_firsttransfer;
  wire             USB_INT_I_s1_waits_for_read;
  wire             USB_INT_I_s1_waits_for_write;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_USB_INT_I_s1;
  wire             cpu_0_data_master_qualified_request_USB_INT_I_s1;
  wire             cpu_0_data_master_read_data_valid_USB_INT_I_s1;
  wire             cpu_0_data_master_requests_USB_INT_I_s1;
  wire             cpu_0_data_master_saved_grant_USB_INT_I_s1;
  reg              d1_USB_INT_I_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_USB_INT_I_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_USB_INT_I_s1_from_cpu_0_data_master;
  wire             wait_for_USB_INT_I_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~USB_INT_I_s1_end_xfer;
    end


  assign USB_INT_I_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_USB_INT_I_s1));
  //assign USB_INT_I_s1_readdata_from_sa = USB_INT_I_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign USB_INT_I_s1_readdata_from_sa = USB_INT_I_s1_readdata;

  assign cpu_0_data_master_requests_USB_INT_I_s1 = (({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h40021e0) & (cpu_0_data_master_read | cpu_0_data_master_write)) & cpu_0_data_master_read;
  //USB_INT_I_s1_arb_share_counter set values, which is an e_mux
  assign USB_INT_I_s1_arb_share_set_values = 1;

  //USB_INT_I_s1_non_bursting_master_requests mux, which is an e_mux
  assign USB_INT_I_s1_non_bursting_master_requests = cpu_0_data_master_requests_USB_INT_I_s1;

  //USB_INT_I_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign USB_INT_I_s1_any_bursting_master_saved_grant = 0;

  //USB_INT_I_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign USB_INT_I_s1_arb_share_counter_next_value = USB_INT_I_s1_firsttransfer ? (USB_INT_I_s1_arb_share_set_values - 1) : |USB_INT_I_s1_arb_share_counter ? (USB_INT_I_s1_arb_share_counter - 1) : 0;

  //USB_INT_I_s1_allgrants all slave grants, which is an e_mux
  assign USB_INT_I_s1_allgrants = |USB_INT_I_s1_grant_vector;

  //USB_INT_I_s1_end_xfer assignment, which is an e_assign
  assign USB_INT_I_s1_end_xfer = ~(USB_INT_I_s1_waits_for_read | USB_INT_I_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_USB_INT_I_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_USB_INT_I_s1 = USB_INT_I_s1_end_xfer & (~USB_INT_I_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //USB_INT_I_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign USB_INT_I_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_USB_INT_I_s1 & USB_INT_I_s1_allgrants) | (end_xfer_arb_share_counter_term_USB_INT_I_s1 & ~USB_INT_I_s1_non_bursting_master_requests);

  //USB_INT_I_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          USB_INT_I_s1_arb_share_counter <= 0;
      else if (USB_INT_I_s1_arb_counter_enable)
          USB_INT_I_s1_arb_share_counter <= USB_INT_I_s1_arb_share_counter_next_value;
    end


  //USB_INT_I_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          USB_INT_I_s1_slavearbiterlockenable <= 0;
      else if ((|USB_INT_I_s1_master_qreq_vector & end_xfer_arb_share_counter_term_USB_INT_I_s1) | (end_xfer_arb_share_counter_term_USB_INT_I_s1 & ~USB_INT_I_s1_non_bursting_master_requests))
          USB_INT_I_s1_slavearbiterlockenable <= |USB_INT_I_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master USB_INT_I/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = USB_INT_I_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //USB_INT_I_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign USB_INT_I_s1_slavearbiterlockenable2 = |USB_INT_I_s1_arb_share_counter_next_value;

  //cpu_0/data_master USB_INT_I/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = USB_INT_I_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //USB_INT_I_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign USB_INT_I_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_USB_INT_I_s1 = cpu_0_data_master_requests_USB_INT_I_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_USB_INT_I_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_USB_INT_I_s1 = cpu_0_data_master_granted_USB_INT_I_s1 & cpu_0_data_master_read & ~USB_INT_I_s1_waits_for_read;

  //master is always granted when requested
  assign cpu_0_data_master_granted_USB_INT_I_s1 = cpu_0_data_master_qualified_request_USB_INT_I_s1;

  //cpu_0/data_master saved-grant USB_INT_I/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_USB_INT_I_s1 = cpu_0_data_master_requests_USB_INT_I_s1;

  //allow new arb cycle for USB_INT_I/s1, which is an e_assign
  assign USB_INT_I_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign USB_INT_I_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign USB_INT_I_s1_master_qreq_vector = 1;

  //USB_INT_I_s1_reset_n assignment, which is an e_assign
  assign USB_INT_I_s1_reset_n = reset_n;

  //USB_INT_I_s1_firsttransfer first transaction, which is an e_assign
  assign USB_INT_I_s1_firsttransfer = USB_INT_I_s1_begins_xfer ? USB_INT_I_s1_unreg_firsttransfer : USB_INT_I_s1_reg_firsttransfer;

  //USB_INT_I_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign USB_INT_I_s1_unreg_firsttransfer = ~(USB_INT_I_s1_slavearbiterlockenable & USB_INT_I_s1_any_continuerequest);

  //USB_INT_I_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          USB_INT_I_s1_reg_firsttransfer <= 1'b1;
      else if (USB_INT_I_s1_begins_xfer)
          USB_INT_I_s1_reg_firsttransfer <= USB_INT_I_s1_unreg_firsttransfer;
    end


  //USB_INT_I_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign USB_INT_I_s1_beginbursttransfer_internal = USB_INT_I_s1_begins_xfer;

  assign shifted_address_to_USB_INT_I_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //USB_INT_I_s1_address mux, which is an e_mux
  assign USB_INT_I_s1_address = shifted_address_to_USB_INT_I_s1_from_cpu_0_data_master >> 2;

  //d1_USB_INT_I_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_USB_INT_I_s1_end_xfer <= 1;
      else 
        d1_USB_INT_I_s1_end_xfer <= USB_INT_I_s1_end_xfer;
    end


  //USB_INT_I_s1_waits_for_read in a cycle, which is an e_mux
  assign USB_INT_I_s1_waits_for_read = USB_INT_I_s1_in_a_read_cycle & USB_INT_I_s1_begins_xfer;

  //USB_INT_I_s1_in_a_read_cycle assignment, which is an e_assign
  assign USB_INT_I_s1_in_a_read_cycle = cpu_0_data_master_granted_USB_INT_I_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = USB_INT_I_s1_in_a_read_cycle;

  //USB_INT_I_s1_waits_for_write in a cycle, which is an e_mux
  assign USB_INT_I_s1_waits_for_write = USB_INT_I_s1_in_a_write_cycle & 0;

  //USB_INT_I_s1_in_a_write_cycle assignment, which is an e_assign
  assign USB_INT_I_s1_in_a_write_cycle = cpu_0_data_master_granted_USB_INT_I_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = USB_INT_I_s1_in_a_write_cycle;

  assign wait_for_USB_INT_I_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //USB_INT_I/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module USB_PC_I_s1_arbitrator (
                                // inputs:
                                 USB_PC_I_s1_readdata,
                                 clk,
                                 cpu_0_data_master_address_to_slave,
                                 cpu_0_data_master_latency_counter,
                                 cpu_0_data_master_read,
                                 cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                 cpu_0_data_master_write,
                                 cpu_0_data_master_writedata,
                                 reset_n,

                                // outputs:
                                 USB_PC_I_s1_address,
                                 USB_PC_I_s1_chipselect,
                                 USB_PC_I_s1_readdata_from_sa,
                                 USB_PC_I_s1_reset_n,
                                 USB_PC_I_s1_write_n,
                                 USB_PC_I_s1_writedata,
                                 cpu_0_data_master_granted_USB_PC_I_s1,
                                 cpu_0_data_master_qualified_request_USB_PC_I_s1,
                                 cpu_0_data_master_read_data_valid_USB_PC_I_s1,
                                 cpu_0_data_master_requests_USB_PC_I_s1,
                                 d1_USB_PC_I_s1_end_xfer
                              )
;

  output  [  1: 0] USB_PC_I_s1_address;
  output           USB_PC_I_s1_chipselect;
  output  [ 31: 0] USB_PC_I_s1_readdata_from_sa;
  output           USB_PC_I_s1_reset_n;
  output           USB_PC_I_s1_write_n;
  output  [ 31: 0] USB_PC_I_s1_writedata;
  output           cpu_0_data_master_granted_USB_PC_I_s1;
  output           cpu_0_data_master_qualified_request_USB_PC_I_s1;
  output           cpu_0_data_master_read_data_valid_USB_PC_I_s1;
  output           cpu_0_data_master_requests_USB_PC_I_s1;
  output           d1_USB_PC_I_s1_end_xfer;
  input   [ 31: 0] USB_PC_I_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] USB_PC_I_s1_address;
  wire             USB_PC_I_s1_allgrants;
  wire             USB_PC_I_s1_allow_new_arb_cycle;
  wire             USB_PC_I_s1_any_bursting_master_saved_grant;
  wire             USB_PC_I_s1_any_continuerequest;
  wire             USB_PC_I_s1_arb_counter_enable;
  reg     [  1: 0] USB_PC_I_s1_arb_share_counter;
  wire    [  1: 0] USB_PC_I_s1_arb_share_counter_next_value;
  wire    [  1: 0] USB_PC_I_s1_arb_share_set_values;
  wire             USB_PC_I_s1_beginbursttransfer_internal;
  wire             USB_PC_I_s1_begins_xfer;
  wire             USB_PC_I_s1_chipselect;
  wire             USB_PC_I_s1_end_xfer;
  wire             USB_PC_I_s1_firsttransfer;
  wire             USB_PC_I_s1_grant_vector;
  wire             USB_PC_I_s1_in_a_read_cycle;
  wire             USB_PC_I_s1_in_a_write_cycle;
  wire             USB_PC_I_s1_master_qreq_vector;
  wire             USB_PC_I_s1_non_bursting_master_requests;
  wire    [ 31: 0] USB_PC_I_s1_readdata_from_sa;
  reg              USB_PC_I_s1_reg_firsttransfer;
  wire             USB_PC_I_s1_reset_n;
  reg              USB_PC_I_s1_slavearbiterlockenable;
  wire             USB_PC_I_s1_slavearbiterlockenable2;
  wire             USB_PC_I_s1_unreg_firsttransfer;
  wire             USB_PC_I_s1_waits_for_read;
  wire             USB_PC_I_s1_waits_for_write;
  wire             USB_PC_I_s1_write_n;
  wire    [ 31: 0] USB_PC_I_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_USB_PC_I_s1;
  wire             cpu_0_data_master_qualified_request_USB_PC_I_s1;
  wire             cpu_0_data_master_read_data_valid_USB_PC_I_s1;
  wire             cpu_0_data_master_requests_USB_PC_I_s1;
  wire             cpu_0_data_master_saved_grant_USB_PC_I_s1;
  reg              d1_USB_PC_I_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_USB_PC_I_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_USB_PC_I_s1_from_cpu_0_data_master;
  wire             wait_for_USB_PC_I_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~USB_PC_I_s1_end_xfer;
    end


  assign USB_PC_I_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_USB_PC_I_s1));
  //assign USB_PC_I_s1_readdata_from_sa = USB_PC_I_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign USB_PC_I_s1_readdata_from_sa = USB_PC_I_s1_readdata;

  assign cpu_0_data_master_requests_USB_PC_I_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h4002200) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //USB_PC_I_s1_arb_share_counter set values, which is an e_mux
  assign USB_PC_I_s1_arb_share_set_values = 1;

  //USB_PC_I_s1_non_bursting_master_requests mux, which is an e_mux
  assign USB_PC_I_s1_non_bursting_master_requests = cpu_0_data_master_requests_USB_PC_I_s1;

  //USB_PC_I_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign USB_PC_I_s1_any_bursting_master_saved_grant = 0;

  //USB_PC_I_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign USB_PC_I_s1_arb_share_counter_next_value = USB_PC_I_s1_firsttransfer ? (USB_PC_I_s1_arb_share_set_values - 1) : |USB_PC_I_s1_arb_share_counter ? (USB_PC_I_s1_arb_share_counter - 1) : 0;

  //USB_PC_I_s1_allgrants all slave grants, which is an e_mux
  assign USB_PC_I_s1_allgrants = |USB_PC_I_s1_grant_vector;

  //USB_PC_I_s1_end_xfer assignment, which is an e_assign
  assign USB_PC_I_s1_end_xfer = ~(USB_PC_I_s1_waits_for_read | USB_PC_I_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_USB_PC_I_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_USB_PC_I_s1 = USB_PC_I_s1_end_xfer & (~USB_PC_I_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //USB_PC_I_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign USB_PC_I_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_USB_PC_I_s1 & USB_PC_I_s1_allgrants) | (end_xfer_arb_share_counter_term_USB_PC_I_s1 & ~USB_PC_I_s1_non_bursting_master_requests);

  //USB_PC_I_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          USB_PC_I_s1_arb_share_counter <= 0;
      else if (USB_PC_I_s1_arb_counter_enable)
          USB_PC_I_s1_arb_share_counter <= USB_PC_I_s1_arb_share_counter_next_value;
    end


  //USB_PC_I_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          USB_PC_I_s1_slavearbiterlockenable <= 0;
      else if ((|USB_PC_I_s1_master_qreq_vector & end_xfer_arb_share_counter_term_USB_PC_I_s1) | (end_xfer_arb_share_counter_term_USB_PC_I_s1 & ~USB_PC_I_s1_non_bursting_master_requests))
          USB_PC_I_s1_slavearbiterlockenable <= |USB_PC_I_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master USB_PC_I/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = USB_PC_I_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //USB_PC_I_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign USB_PC_I_s1_slavearbiterlockenable2 = |USB_PC_I_s1_arb_share_counter_next_value;

  //cpu_0/data_master USB_PC_I/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = USB_PC_I_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //USB_PC_I_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign USB_PC_I_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_USB_PC_I_s1 = cpu_0_data_master_requests_USB_PC_I_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_USB_PC_I_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_USB_PC_I_s1 = cpu_0_data_master_granted_USB_PC_I_s1 & cpu_0_data_master_read & ~USB_PC_I_s1_waits_for_read;

  //USB_PC_I_s1_writedata mux, which is an e_mux
  assign USB_PC_I_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_USB_PC_I_s1 = cpu_0_data_master_qualified_request_USB_PC_I_s1;

  //cpu_0/data_master saved-grant USB_PC_I/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_USB_PC_I_s1 = cpu_0_data_master_requests_USB_PC_I_s1;

  //allow new arb cycle for USB_PC_I/s1, which is an e_assign
  assign USB_PC_I_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign USB_PC_I_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign USB_PC_I_s1_master_qreq_vector = 1;

  //USB_PC_I_s1_reset_n assignment, which is an e_assign
  assign USB_PC_I_s1_reset_n = reset_n;

  assign USB_PC_I_s1_chipselect = cpu_0_data_master_granted_USB_PC_I_s1;
  //USB_PC_I_s1_firsttransfer first transaction, which is an e_assign
  assign USB_PC_I_s1_firsttransfer = USB_PC_I_s1_begins_xfer ? USB_PC_I_s1_unreg_firsttransfer : USB_PC_I_s1_reg_firsttransfer;

  //USB_PC_I_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign USB_PC_I_s1_unreg_firsttransfer = ~(USB_PC_I_s1_slavearbiterlockenable & USB_PC_I_s1_any_continuerequest);

  //USB_PC_I_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          USB_PC_I_s1_reg_firsttransfer <= 1'b1;
      else if (USB_PC_I_s1_begins_xfer)
          USB_PC_I_s1_reg_firsttransfer <= USB_PC_I_s1_unreg_firsttransfer;
    end


  //USB_PC_I_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign USB_PC_I_s1_beginbursttransfer_internal = USB_PC_I_s1_begins_xfer;

  //~USB_PC_I_s1_write_n assignment, which is an e_mux
  assign USB_PC_I_s1_write_n = ~(cpu_0_data_master_granted_USB_PC_I_s1 & cpu_0_data_master_write);

  assign shifted_address_to_USB_PC_I_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //USB_PC_I_s1_address mux, which is an e_mux
  assign USB_PC_I_s1_address = shifted_address_to_USB_PC_I_s1_from_cpu_0_data_master >> 2;

  //d1_USB_PC_I_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_USB_PC_I_s1_end_xfer <= 1;
      else 
        d1_USB_PC_I_s1_end_xfer <= USB_PC_I_s1_end_xfer;
    end


  //USB_PC_I_s1_waits_for_read in a cycle, which is an e_mux
  assign USB_PC_I_s1_waits_for_read = USB_PC_I_s1_in_a_read_cycle & USB_PC_I_s1_begins_xfer;

  //USB_PC_I_s1_in_a_read_cycle assignment, which is an e_assign
  assign USB_PC_I_s1_in_a_read_cycle = cpu_0_data_master_granted_USB_PC_I_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = USB_PC_I_s1_in_a_read_cycle;

  //USB_PC_I_s1_waits_for_write in a cycle, which is an e_mux
  assign USB_PC_I_s1_waits_for_write = USB_PC_I_s1_in_a_write_cycle & 0;

  //USB_PC_I_s1_in_a_write_cycle assignment, which is an e_assign
  assign USB_PC_I_s1_in_a_write_cycle = cpu_0_data_master_granted_USB_PC_I_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = USB_PC_I_s1_in_a_write_cycle;

  assign wait_for_USB_PC_I_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //USB_PC_I/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module USB_RST_O_s1_arbitrator (
                                 // inputs:
                                  USB_RST_O_s1_readdata,
                                  clk,
                                  cpu_0_data_master_address_to_slave,
                                  cpu_0_data_master_latency_counter,
                                  cpu_0_data_master_read,
                                  cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                  cpu_0_data_master_write,
                                  cpu_0_data_master_writedata,
                                  reset_n,

                                 // outputs:
                                  USB_RST_O_s1_address,
                                  USB_RST_O_s1_chipselect,
                                  USB_RST_O_s1_readdata_from_sa,
                                  USB_RST_O_s1_reset_n,
                                  USB_RST_O_s1_write_n,
                                  USB_RST_O_s1_writedata,
                                  cpu_0_data_master_granted_USB_RST_O_s1,
                                  cpu_0_data_master_qualified_request_USB_RST_O_s1,
                                  cpu_0_data_master_read_data_valid_USB_RST_O_s1,
                                  cpu_0_data_master_requests_USB_RST_O_s1,
                                  d1_USB_RST_O_s1_end_xfer
                               )
;

  output  [  1: 0] USB_RST_O_s1_address;
  output           USB_RST_O_s1_chipselect;
  output  [ 31: 0] USB_RST_O_s1_readdata_from_sa;
  output           USB_RST_O_s1_reset_n;
  output           USB_RST_O_s1_write_n;
  output  [ 31: 0] USB_RST_O_s1_writedata;
  output           cpu_0_data_master_granted_USB_RST_O_s1;
  output           cpu_0_data_master_qualified_request_USB_RST_O_s1;
  output           cpu_0_data_master_read_data_valid_USB_RST_O_s1;
  output           cpu_0_data_master_requests_USB_RST_O_s1;
  output           d1_USB_RST_O_s1_end_xfer;
  input   [ 31: 0] USB_RST_O_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] USB_RST_O_s1_address;
  wire             USB_RST_O_s1_allgrants;
  wire             USB_RST_O_s1_allow_new_arb_cycle;
  wire             USB_RST_O_s1_any_bursting_master_saved_grant;
  wire             USB_RST_O_s1_any_continuerequest;
  wire             USB_RST_O_s1_arb_counter_enable;
  reg     [  1: 0] USB_RST_O_s1_arb_share_counter;
  wire    [  1: 0] USB_RST_O_s1_arb_share_counter_next_value;
  wire    [  1: 0] USB_RST_O_s1_arb_share_set_values;
  wire             USB_RST_O_s1_beginbursttransfer_internal;
  wire             USB_RST_O_s1_begins_xfer;
  wire             USB_RST_O_s1_chipselect;
  wire             USB_RST_O_s1_end_xfer;
  wire             USB_RST_O_s1_firsttransfer;
  wire             USB_RST_O_s1_grant_vector;
  wire             USB_RST_O_s1_in_a_read_cycle;
  wire             USB_RST_O_s1_in_a_write_cycle;
  wire             USB_RST_O_s1_master_qreq_vector;
  wire             USB_RST_O_s1_non_bursting_master_requests;
  wire    [ 31: 0] USB_RST_O_s1_readdata_from_sa;
  reg              USB_RST_O_s1_reg_firsttransfer;
  wire             USB_RST_O_s1_reset_n;
  reg              USB_RST_O_s1_slavearbiterlockenable;
  wire             USB_RST_O_s1_slavearbiterlockenable2;
  wire             USB_RST_O_s1_unreg_firsttransfer;
  wire             USB_RST_O_s1_waits_for_read;
  wire             USB_RST_O_s1_waits_for_write;
  wire             USB_RST_O_s1_write_n;
  wire    [ 31: 0] USB_RST_O_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_USB_RST_O_s1;
  wire             cpu_0_data_master_qualified_request_USB_RST_O_s1;
  wire             cpu_0_data_master_read_data_valid_USB_RST_O_s1;
  wire             cpu_0_data_master_requests_USB_RST_O_s1;
  wire             cpu_0_data_master_saved_grant_USB_RST_O_s1;
  reg              d1_USB_RST_O_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_USB_RST_O_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_USB_RST_O_s1_from_cpu_0_data_master;
  wire             wait_for_USB_RST_O_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~USB_RST_O_s1_end_xfer;
    end


  assign USB_RST_O_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_USB_RST_O_s1));
  //assign USB_RST_O_s1_readdata_from_sa = USB_RST_O_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign USB_RST_O_s1_readdata_from_sa = USB_RST_O_s1_readdata;

  assign cpu_0_data_master_requests_USB_RST_O_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h40021f0) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //USB_RST_O_s1_arb_share_counter set values, which is an e_mux
  assign USB_RST_O_s1_arb_share_set_values = 1;

  //USB_RST_O_s1_non_bursting_master_requests mux, which is an e_mux
  assign USB_RST_O_s1_non_bursting_master_requests = cpu_0_data_master_requests_USB_RST_O_s1;

  //USB_RST_O_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign USB_RST_O_s1_any_bursting_master_saved_grant = 0;

  //USB_RST_O_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign USB_RST_O_s1_arb_share_counter_next_value = USB_RST_O_s1_firsttransfer ? (USB_RST_O_s1_arb_share_set_values - 1) : |USB_RST_O_s1_arb_share_counter ? (USB_RST_O_s1_arb_share_counter - 1) : 0;

  //USB_RST_O_s1_allgrants all slave grants, which is an e_mux
  assign USB_RST_O_s1_allgrants = |USB_RST_O_s1_grant_vector;

  //USB_RST_O_s1_end_xfer assignment, which is an e_assign
  assign USB_RST_O_s1_end_xfer = ~(USB_RST_O_s1_waits_for_read | USB_RST_O_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_USB_RST_O_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_USB_RST_O_s1 = USB_RST_O_s1_end_xfer & (~USB_RST_O_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //USB_RST_O_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign USB_RST_O_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_USB_RST_O_s1 & USB_RST_O_s1_allgrants) | (end_xfer_arb_share_counter_term_USB_RST_O_s1 & ~USB_RST_O_s1_non_bursting_master_requests);

  //USB_RST_O_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          USB_RST_O_s1_arb_share_counter <= 0;
      else if (USB_RST_O_s1_arb_counter_enable)
          USB_RST_O_s1_arb_share_counter <= USB_RST_O_s1_arb_share_counter_next_value;
    end


  //USB_RST_O_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          USB_RST_O_s1_slavearbiterlockenable <= 0;
      else if ((|USB_RST_O_s1_master_qreq_vector & end_xfer_arb_share_counter_term_USB_RST_O_s1) | (end_xfer_arb_share_counter_term_USB_RST_O_s1 & ~USB_RST_O_s1_non_bursting_master_requests))
          USB_RST_O_s1_slavearbiterlockenable <= |USB_RST_O_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master USB_RST_O/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = USB_RST_O_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //USB_RST_O_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign USB_RST_O_s1_slavearbiterlockenable2 = |USB_RST_O_s1_arb_share_counter_next_value;

  //cpu_0/data_master USB_RST_O/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = USB_RST_O_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //USB_RST_O_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign USB_RST_O_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_USB_RST_O_s1 = cpu_0_data_master_requests_USB_RST_O_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_USB_RST_O_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_USB_RST_O_s1 = cpu_0_data_master_granted_USB_RST_O_s1 & cpu_0_data_master_read & ~USB_RST_O_s1_waits_for_read;

  //USB_RST_O_s1_writedata mux, which is an e_mux
  assign USB_RST_O_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_USB_RST_O_s1 = cpu_0_data_master_qualified_request_USB_RST_O_s1;

  //cpu_0/data_master saved-grant USB_RST_O/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_USB_RST_O_s1 = cpu_0_data_master_requests_USB_RST_O_s1;

  //allow new arb cycle for USB_RST_O/s1, which is an e_assign
  assign USB_RST_O_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign USB_RST_O_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign USB_RST_O_s1_master_qreq_vector = 1;

  //USB_RST_O_s1_reset_n assignment, which is an e_assign
  assign USB_RST_O_s1_reset_n = reset_n;

  assign USB_RST_O_s1_chipselect = cpu_0_data_master_granted_USB_RST_O_s1;
  //USB_RST_O_s1_firsttransfer first transaction, which is an e_assign
  assign USB_RST_O_s1_firsttransfer = USB_RST_O_s1_begins_xfer ? USB_RST_O_s1_unreg_firsttransfer : USB_RST_O_s1_reg_firsttransfer;

  //USB_RST_O_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign USB_RST_O_s1_unreg_firsttransfer = ~(USB_RST_O_s1_slavearbiterlockenable & USB_RST_O_s1_any_continuerequest);

  //USB_RST_O_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          USB_RST_O_s1_reg_firsttransfer <= 1'b1;
      else if (USB_RST_O_s1_begins_xfer)
          USB_RST_O_s1_reg_firsttransfer <= USB_RST_O_s1_unreg_firsttransfer;
    end


  //USB_RST_O_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign USB_RST_O_s1_beginbursttransfer_internal = USB_RST_O_s1_begins_xfer;

  //~USB_RST_O_s1_write_n assignment, which is an e_mux
  assign USB_RST_O_s1_write_n = ~(cpu_0_data_master_granted_USB_RST_O_s1 & cpu_0_data_master_write);

  assign shifted_address_to_USB_RST_O_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //USB_RST_O_s1_address mux, which is an e_mux
  assign USB_RST_O_s1_address = shifted_address_to_USB_RST_O_s1_from_cpu_0_data_master >> 2;

  //d1_USB_RST_O_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_USB_RST_O_s1_end_xfer <= 1;
      else 
        d1_USB_RST_O_s1_end_xfer <= USB_RST_O_s1_end_xfer;
    end


  //USB_RST_O_s1_waits_for_read in a cycle, which is an e_mux
  assign USB_RST_O_s1_waits_for_read = USB_RST_O_s1_in_a_read_cycle & USB_RST_O_s1_begins_xfer;

  //USB_RST_O_s1_in_a_read_cycle assignment, which is an e_assign
  assign USB_RST_O_s1_in_a_read_cycle = cpu_0_data_master_granted_USB_RST_O_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = USB_RST_O_s1_in_a_read_cycle;

  //USB_RST_O_s1_waits_for_write in a cycle, which is an e_mux
  assign USB_RST_O_s1_waits_for_write = USB_RST_O_s1_in_a_write_cycle & 0;

  //USB_RST_O_s1_in_a_write_cycle assignment, which is an e_assign
  assign USB_RST_O_s1_in_a_write_cycle = cpu_0_data_master_granted_USB_RST_O_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = USB_RST_O_s1_in_a_write_cycle;

  assign wait_for_USB_RST_O_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //USB_RST_O/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module USB_SCK_O_s1_arbitrator (
                                 // inputs:
                                  USB_SCK_O_s1_readdata,
                                  clk,
                                  cpu_0_data_master_address_to_slave,
                                  cpu_0_data_master_latency_counter,
                                  cpu_0_data_master_read,
                                  cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                  cpu_0_data_master_write,
                                  cpu_0_data_master_writedata,
                                  reset_n,

                                 // outputs:
                                  USB_SCK_O_s1_address,
                                  USB_SCK_O_s1_chipselect,
                                  USB_SCK_O_s1_readdata_from_sa,
                                  USB_SCK_O_s1_reset_n,
                                  USB_SCK_O_s1_write_n,
                                  USB_SCK_O_s1_writedata,
                                  cpu_0_data_master_granted_USB_SCK_O_s1,
                                  cpu_0_data_master_qualified_request_USB_SCK_O_s1,
                                  cpu_0_data_master_read_data_valid_USB_SCK_O_s1,
                                  cpu_0_data_master_requests_USB_SCK_O_s1,
                                  d1_USB_SCK_O_s1_end_xfer
                               )
;

  output  [  1: 0] USB_SCK_O_s1_address;
  output           USB_SCK_O_s1_chipselect;
  output  [ 31: 0] USB_SCK_O_s1_readdata_from_sa;
  output           USB_SCK_O_s1_reset_n;
  output           USB_SCK_O_s1_write_n;
  output  [ 31: 0] USB_SCK_O_s1_writedata;
  output           cpu_0_data_master_granted_USB_SCK_O_s1;
  output           cpu_0_data_master_qualified_request_USB_SCK_O_s1;
  output           cpu_0_data_master_read_data_valid_USB_SCK_O_s1;
  output           cpu_0_data_master_requests_USB_SCK_O_s1;
  output           d1_USB_SCK_O_s1_end_xfer;
  input   [ 31: 0] USB_SCK_O_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] USB_SCK_O_s1_address;
  wire             USB_SCK_O_s1_allgrants;
  wire             USB_SCK_O_s1_allow_new_arb_cycle;
  wire             USB_SCK_O_s1_any_bursting_master_saved_grant;
  wire             USB_SCK_O_s1_any_continuerequest;
  wire             USB_SCK_O_s1_arb_counter_enable;
  reg     [  1: 0] USB_SCK_O_s1_arb_share_counter;
  wire    [  1: 0] USB_SCK_O_s1_arb_share_counter_next_value;
  wire    [  1: 0] USB_SCK_O_s1_arb_share_set_values;
  wire             USB_SCK_O_s1_beginbursttransfer_internal;
  wire             USB_SCK_O_s1_begins_xfer;
  wire             USB_SCK_O_s1_chipselect;
  wire             USB_SCK_O_s1_end_xfer;
  wire             USB_SCK_O_s1_firsttransfer;
  wire             USB_SCK_O_s1_grant_vector;
  wire             USB_SCK_O_s1_in_a_read_cycle;
  wire             USB_SCK_O_s1_in_a_write_cycle;
  wire             USB_SCK_O_s1_master_qreq_vector;
  wire             USB_SCK_O_s1_non_bursting_master_requests;
  wire    [ 31: 0] USB_SCK_O_s1_readdata_from_sa;
  reg              USB_SCK_O_s1_reg_firsttransfer;
  wire             USB_SCK_O_s1_reset_n;
  reg              USB_SCK_O_s1_slavearbiterlockenable;
  wire             USB_SCK_O_s1_slavearbiterlockenable2;
  wire             USB_SCK_O_s1_unreg_firsttransfer;
  wire             USB_SCK_O_s1_waits_for_read;
  wire             USB_SCK_O_s1_waits_for_write;
  wire             USB_SCK_O_s1_write_n;
  wire    [ 31: 0] USB_SCK_O_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_USB_SCK_O_s1;
  wire             cpu_0_data_master_qualified_request_USB_SCK_O_s1;
  wire             cpu_0_data_master_read_data_valid_USB_SCK_O_s1;
  wire             cpu_0_data_master_requests_USB_SCK_O_s1;
  wire             cpu_0_data_master_saved_grant_USB_SCK_O_s1;
  reg              d1_USB_SCK_O_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_USB_SCK_O_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_USB_SCK_O_s1_from_cpu_0_data_master;
  wire             wait_for_USB_SCK_O_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~USB_SCK_O_s1_end_xfer;
    end


  assign USB_SCK_O_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_USB_SCK_O_s1));
  //assign USB_SCK_O_s1_readdata_from_sa = USB_SCK_O_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign USB_SCK_O_s1_readdata_from_sa = USB_SCK_O_s1_readdata;

  assign cpu_0_data_master_requests_USB_SCK_O_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h40021d0) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //USB_SCK_O_s1_arb_share_counter set values, which is an e_mux
  assign USB_SCK_O_s1_arb_share_set_values = 1;

  //USB_SCK_O_s1_non_bursting_master_requests mux, which is an e_mux
  assign USB_SCK_O_s1_non_bursting_master_requests = cpu_0_data_master_requests_USB_SCK_O_s1;

  //USB_SCK_O_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign USB_SCK_O_s1_any_bursting_master_saved_grant = 0;

  //USB_SCK_O_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign USB_SCK_O_s1_arb_share_counter_next_value = USB_SCK_O_s1_firsttransfer ? (USB_SCK_O_s1_arb_share_set_values - 1) : |USB_SCK_O_s1_arb_share_counter ? (USB_SCK_O_s1_arb_share_counter - 1) : 0;

  //USB_SCK_O_s1_allgrants all slave grants, which is an e_mux
  assign USB_SCK_O_s1_allgrants = |USB_SCK_O_s1_grant_vector;

  //USB_SCK_O_s1_end_xfer assignment, which is an e_assign
  assign USB_SCK_O_s1_end_xfer = ~(USB_SCK_O_s1_waits_for_read | USB_SCK_O_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_USB_SCK_O_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_USB_SCK_O_s1 = USB_SCK_O_s1_end_xfer & (~USB_SCK_O_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //USB_SCK_O_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign USB_SCK_O_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_USB_SCK_O_s1 & USB_SCK_O_s1_allgrants) | (end_xfer_arb_share_counter_term_USB_SCK_O_s1 & ~USB_SCK_O_s1_non_bursting_master_requests);

  //USB_SCK_O_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          USB_SCK_O_s1_arb_share_counter <= 0;
      else if (USB_SCK_O_s1_arb_counter_enable)
          USB_SCK_O_s1_arb_share_counter <= USB_SCK_O_s1_arb_share_counter_next_value;
    end


  //USB_SCK_O_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          USB_SCK_O_s1_slavearbiterlockenable <= 0;
      else if ((|USB_SCK_O_s1_master_qreq_vector & end_xfer_arb_share_counter_term_USB_SCK_O_s1) | (end_xfer_arb_share_counter_term_USB_SCK_O_s1 & ~USB_SCK_O_s1_non_bursting_master_requests))
          USB_SCK_O_s1_slavearbiterlockenable <= |USB_SCK_O_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master USB_SCK_O/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = USB_SCK_O_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //USB_SCK_O_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign USB_SCK_O_s1_slavearbiterlockenable2 = |USB_SCK_O_s1_arb_share_counter_next_value;

  //cpu_0/data_master USB_SCK_O/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = USB_SCK_O_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //USB_SCK_O_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign USB_SCK_O_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_USB_SCK_O_s1 = cpu_0_data_master_requests_USB_SCK_O_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_USB_SCK_O_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_USB_SCK_O_s1 = cpu_0_data_master_granted_USB_SCK_O_s1 & cpu_0_data_master_read & ~USB_SCK_O_s1_waits_for_read;

  //USB_SCK_O_s1_writedata mux, which is an e_mux
  assign USB_SCK_O_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_USB_SCK_O_s1 = cpu_0_data_master_qualified_request_USB_SCK_O_s1;

  //cpu_0/data_master saved-grant USB_SCK_O/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_USB_SCK_O_s1 = cpu_0_data_master_requests_USB_SCK_O_s1;

  //allow new arb cycle for USB_SCK_O/s1, which is an e_assign
  assign USB_SCK_O_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign USB_SCK_O_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign USB_SCK_O_s1_master_qreq_vector = 1;

  //USB_SCK_O_s1_reset_n assignment, which is an e_assign
  assign USB_SCK_O_s1_reset_n = reset_n;

  assign USB_SCK_O_s1_chipselect = cpu_0_data_master_granted_USB_SCK_O_s1;
  //USB_SCK_O_s1_firsttransfer first transaction, which is an e_assign
  assign USB_SCK_O_s1_firsttransfer = USB_SCK_O_s1_begins_xfer ? USB_SCK_O_s1_unreg_firsttransfer : USB_SCK_O_s1_reg_firsttransfer;

  //USB_SCK_O_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign USB_SCK_O_s1_unreg_firsttransfer = ~(USB_SCK_O_s1_slavearbiterlockenable & USB_SCK_O_s1_any_continuerequest);

  //USB_SCK_O_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          USB_SCK_O_s1_reg_firsttransfer <= 1'b1;
      else if (USB_SCK_O_s1_begins_xfer)
          USB_SCK_O_s1_reg_firsttransfer <= USB_SCK_O_s1_unreg_firsttransfer;
    end


  //USB_SCK_O_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign USB_SCK_O_s1_beginbursttransfer_internal = USB_SCK_O_s1_begins_xfer;

  //~USB_SCK_O_s1_write_n assignment, which is an e_mux
  assign USB_SCK_O_s1_write_n = ~(cpu_0_data_master_granted_USB_SCK_O_s1 & cpu_0_data_master_write);

  assign shifted_address_to_USB_SCK_O_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //USB_SCK_O_s1_address mux, which is an e_mux
  assign USB_SCK_O_s1_address = shifted_address_to_USB_SCK_O_s1_from_cpu_0_data_master >> 2;

  //d1_USB_SCK_O_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_USB_SCK_O_s1_end_xfer <= 1;
      else 
        d1_USB_SCK_O_s1_end_xfer <= USB_SCK_O_s1_end_xfer;
    end


  //USB_SCK_O_s1_waits_for_read in a cycle, which is an e_mux
  assign USB_SCK_O_s1_waits_for_read = USB_SCK_O_s1_in_a_read_cycle & USB_SCK_O_s1_begins_xfer;

  //USB_SCK_O_s1_in_a_read_cycle assignment, which is an e_assign
  assign USB_SCK_O_s1_in_a_read_cycle = cpu_0_data_master_granted_USB_SCK_O_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = USB_SCK_O_s1_in_a_read_cycle;

  //USB_SCK_O_s1_waits_for_write in a cycle, which is an e_mux
  assign USB_SCK_O_s1_waits_for_write = USB_SCK_O_s1_in_a_write_cycle & 0;

  //USB_SCK_O_s1_in_a_write_cycle assignment, which is an e_assign
  assign USB_SCK_O_s1_in_a_write_cycle = cpu_0_data_master_granted_USB_SCK_O_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = USB_SCK_O_s1_in_a_write_cycle;

  assign wait_for_USB_SCK_O_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //USB_SCK_O/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module USB_SCS_O_s1_arbitrator (
                                 // inputs:
                                  USB_SCS_O_s1_readdata,
                                  clk,
                                  cpu_0_data_master_address_to_slave,
                                  cpu_0_data_master_latency_counter,
                                  cpu_0_data_master_read,
                                  cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                  cpu_0_data_master_write,
                                  cpu_0_data_master_writedata,
                                  reset_n,

                                 // outputs:
                                  USB_SCS_O_s1_address,
                                  USB_SCS_O_s1_chipselect,
                                  USB_SCS_O_s1_readdata_from_sa,
                                  USB_SCS_O_s1_reset_n,
                                  USB_SCS_O_s1_write_n,
                                  USB_SCS_O_s1_writedata,
                                  cpu_0_data_master_granted_USB_SCS_O_s1,
                                  cpu_0_data_master_qualified_request_USB_SCS_O_s1,
                                  cpu_0_data_master_read_data_valid_USB_SCS_O_s1,
                                  cpu_0_data_master_requests_USB_SCS_O_s1,
                                  d1_USB_SCS_O_s1_end_xfer
                               )
;

  output  [  1: 0] USB_SCS_O_s1_address;
  output           USB_SCS_O_s1_chipselect;
  output  [ 31: 0] USB_SCS_O_s1_readdata_from_sa;
  output           USB_SCS_O_s1_reset_n;
  output           USB_SCS_O_s1_write_n;
  output  [ 31: 0] USB_SCS_O_s1_writedata;
  output           cpu_0_data_master_granted_USB_SCS_O_s1;
  output           cpu_0_data_master_qualified_request_USB_SCS_O_s1;
  output           cpu_0_data_master_read_data_valid_USB_SCS_O_s1;
  output           cpu_0_data_master_requests_USB_SCS_O_s1;
  output           d1_USB_SCS_O_s1_end_xfer;
  input   [ 31: 0] USB_SCS_O_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] USB_SCS_O_s1_address;
  wire             USB_SCS_O_s1_allgrants;
  wire             USB_SCS_O_s1_allow_new_arb_cycle;
  wire             USB_SCS_O_s1_any_bursting_master_saved_grant;
  wire             USB_SCS_O_s1_any_continuerequest;
  wire             USB_SCS_O_s1_arb_counter_enable;
  reg     [  1: 0] USB_SCS_O_s1_arb_share_counter;
  wire    [  1: 0] USB_SCS_O_s1_arb_share_counter_next_value;
  wire    [  1: 0] USB_SCS_O_s1_arb_share_set_values;
  wire             USB_SCS_O_s1_beginbursttransfer_internal;
  wire             USB_SCS_O_s1_begins_xfer;
  wire             USB_SCS_O_s1_chipselect;
  wire             USB_SCS_O_s1_end_xfer;
  wire             USB_SCS_O_s1_firsttransfer;
  wire             USB_SCS_O_s1_grant_vector;
  wire             USB_SCS_O_s1_in_a_read_cycle;
  wire             USB_SCS_O_s1_in_a_write_cycle;
  wire             USB_SCS_O_s1_master_qreq_vector;
  wire             USB_SCS_O_s1_non_bursting_master_requests;
  wire    [ 31: 0] USB_SCS_O_s1_readdata_from_sa;
  reg              USB_SCS_O_s1_reg_firsttransfer;
  wire             USB_SCS_O_s1_reset_n;
  reg              USB_SCS_O_s1_slavearbiterlockenable;
  wire             USB_SCS_O_s1_slavearbiterlockenable2;
  wire             USB_SCS_O_s1_unreg_firsttransfer;
  wire             USB_SCS_O_s1_waits_for_read;
  wire             USB_SCS_O_s1_waits_for_write;
  wire             USB_SCS_O_s1_write_n;
  wire    [ 31: 0] USB_SCS_O_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_USB_SCS_O_s1;
  wire             cpu_0_data_master_qualified_request_USB_SCS_O_s1;
  wire             cpu_0_data_master_read_data_valid_USB_SCS_O_s1;
  wire             cpu_0_data_master_requests_USB_SCS_O_s1;
  wire             cpu_0_data_master_saved_grant_USB_SCS_O_s1;
  reg              d1_USB_SCS_O_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_USB_SCS_O_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_USB_SCS_O_s1_from_cpu_0_data_master;
  wire             wait_for_USB_SCS_O_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~USB_SCS_O_s1_end_xfer;
    end


  assign USB_SCS_O_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_USB_SCS_O_s1));
  //assign USB_SCS_O_s1_readdata_from_sa = USB_SCS_O_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign USB_SCS_O_s1_readdata_from_sa = USB_SCS_O_s1_readdata;

  assign cpu_0_data_master_requests_USB_SCS_O_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h40021a0) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //USB_SCS_O_s1_arb_share_counter set values, which is an e_mux
  assign USB_SCS_O_s1_arb_share_set_values = 1;

  //USB_SCS_O_s1_non_bursting_master_requests mux, which is an e_mux
  assign USB_SCS_O_s1_non_bursting_master_requests = cpu_0_data_master_requests_USB_SCS_O_s1;

  //USB_SCS_O_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign USB_SCS_O_s1_any_bursting_master_saved_grant = 0;

  //USB_SCS_O_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign USB_SCS_O_s1_arb_share_counter_next_value = USB_SCS_O_s1_firsttransfer ? (USB_SCS_O_s1_arb_share_set_values - 1) : |USB_SCS_O_s1_arb_share_counter ? (USB_SCS_O_s1_arb_share_counter - 1) : 0;

  //USB_SCS_O_s1_allgrants all slave grants, which is an e_mux
  assign USB_SCS_O_s1_allgrants = |USB_SCS_O_s1_grant_vector;

  //USB_SCS_O_s1_end_xfer assignment, which is an e_assign
  assign USB_SCS_O_s1_end_xfer = ~(USB_SCS_O_s1_waits_for_read | USB_SCS_O_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_USB_SCS_O_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_USB_SCS_O_s1 = USB_SCS_O_s1_end_xfer & (~USB_SCS_O_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //USB_SCS_O_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign USB_SCS_O_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_USB_SCS_O_s1 & USB_SCS_O_s1_allgrants) | (end_xfer_arb_share_counter_term_USB_SCS_O_s1 & ~USB_SCS_O_s1_non_bursting_master_requests);

  //USB_SCS_O_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          USB_SCS_O_s1_arb_share_counter <= 0;
      else if (USB_SCS_O_s1_arb_counter_enable)
          USB_SCS_O_s1_arb_share_counter <= USB_SCS_O_s1_arb_share_counter_next_value;
    end


  //USB_SCS_O_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          USB_SCS_O_s1_slavearbiterlockenable <= 0;
      else if ((|USB_SCS_O_s1_master_qreq_vector & end_xfer_arb_share_counter_term_USB_SCS_O_s1) | (end_xfer_arb_share_counter_term_USB_SCS_O_s1 & ~USB_SCS_O_s1_non_bursting_master_requests))
          USB_SCS_O_s1_slavearbiterlockenable <= |USB_SCS_O_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master USB_SCS_O/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = USB_SCS_O_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //USB_SCS_O_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign USB_SCS_O_s1_slavearbiterlockenable2 = |USB_SCS_O_s1_arb_share_counter_next_value;

  //cpu_0/data_master USB_SCS_O/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = USB_SCS_O_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //USB_SCS_O_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign USB_SCS_O_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_USB_SCS_O_s1 = cpu_0_data_master_requests_USB_SCS_O_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_USB_SCS_O_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_USB_SCS_O_s1 = cpu_0_data_master_granted_USB_SCS_O_s1 & cpu_0_data_master_read & ~USB_SCS_O_s1_waits_for_read;

  //USB_SCS_O_s1_writedata mux, which is an e_mux
  assign USB_SCS_O_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_USB_SCS_O_s1 = cpu_0_data_master_qualified_request_USB_SCS_O_s1;

  //cpu_0/data_master saved-grant USB_SCS_O/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_USB_SCS_O_s1 = cpu_0_data_master_requests_USB_SCS_O_s1;

  //allow new arb cycle for USB_SCS_O/s1, which is an e_assign
  assign USB_SCS_O_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign USB_SCS_O_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign USB_SCS_O_s1_master_qreq_vector = 1;

  //USB_SCS_O_s1_reset_n assignment, which is an e_assign
  assign USB_SCS_O_s1_reset_n = reset_n;

  assign USB_SCS_O_s1_chipselect = cpu_0_data_master_granted_USB_SCS_O_s1;
  //USB_SCS_O_s1_firsttransfer first transaction, which is an e_assign
  assign USB_SCS_O_s1_firsttransfer = USB_SCS_O_s1_begins_xfer ? USB_SCS_O_s1_unreg_firsttransfer : USB_SCS_O_s1_reg_firsttransfer;

  //USB_SCS_O_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign USB_SCS_O_s1_unreg_firsttransfer = ~(USB_SCS_O_s1_slavearbiterlockenable & USB_SCS_O_s1_any_continuerequest);

  //USB_SCS_O_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          USB_SCS_O_s1_reg_firsttransfer <= 1'b1;
      else if (USB_SCS_O_s1_begins_xfer)
          USB_SCS_O_s1_reg_firsttransfer <= USB_SCS_O_s1_unreg_firsttransfer;
    end


  //USB_SCS_O_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign USB_SCS_O_s1_beginbursttransfer_internal = USB_SCS_O_s1_begins_xfer;

  //~USB_SCS_O_s1_write_n assignment, which is an e_mux
  assign USB_SCS_O_s1_write_n = ~(cpu_0_data_master_granted_USB_SCS_O_s1 & cpu_0_data_master_write);

  assign shifted_address_to_USB_SCS_O_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //USB_SCS_O_s1_address mux, which is an e_mux
  assign USB_SCS_O_s1_address = shifted_address_to_USB_SCS_O_s1_from_cpu_0_data_master >> 2;

  //d1_USB_SCS_O_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_USB_SCS_O_s1_end_xfer <= 1;
      else 
        d1_USB_SCS_O_s1_end_xfer <= USB_SCS_O_s1_end_xfer;
    end


  //USB_SCS_O_s1_waits_for_read in a cycle, which is an e_mux
  assign USB_SCS_O_s1_waits_for_read = USB_SCS_O_s1_in_a_read_cycle & USB_SCS_O_s1_begins_xfer;

  //USB_SCS_O_s1_in_a_read_cycle assignment, which is an e_assign
  assign USB_SCS_O_s1_in_a_read_cycle = cpu_0_data_master_granted_USB_SCS_O_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = USB_SCS_O_s1_in_a_read_cycle;

  //USB_SCS_O_s1_waits_for_write in a cycle, which is an e_mux
  assign USB_SCS_O_s1_waits_for_write = USB_SCS_O_s1_in_a_write_cycle & 0;

  //USB_SCS_O_s1_in_a_write_cycle assignment, which is an e_assign
  assign USB_SCS_O_s1_in_a_write_cycle = cpu_0_data_master_granted_USB_SCS_O_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = USB_SCS_O_s1_in_a_write_cycle;

  assign wait_for_USB_SCS_O_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //USB_SCS_O/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module USB_SDI_O_s1_arbitrator (
                                 // inputs:
                                  USB_SDI_O_s1_readdata,
                                  clk,
                                  cpu_0_data_master_address_to_slave,
                                  cpu_0_data_master_latency_counter,
                                  cpu_0_data_master_read,
                                  cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                  cpu_0_data_master_write,
                                  cpu_0_data_master_writedata,
                                  reset_n,

                                 // outputs:
                                  USB_SDI_O_s1_address,
                                  USB_SDI_O_s1_chipselect,
                                  USB_SDI_O_s1_readdata_from_sa,
                                  USB_SDI_O_s1_reset_n,
                                  USB_SDI_O_s1_write_n,
                                  USB_SDI_O_s1_writedata,
                                  cpu_0_data_master_granted_USB_SDI_O_s1,
                                  cpu_0_data_master_qualified_request_USB_SDI_O_s1,
                                  cpu_0_data_master_read_data_valid_USB_SDI_O_s1,
                                  cpu_0_data_master_requests_USB_SDI_O_s1,
                                  d1_USB_SDI_O_s1_end_xfer
                               )
;

  output  [  1: 0] USB_SDI_O_s1_address;
  output           USB_SDI_O_s1_chipselect;
  output  [ 31: 0] USB_SDI_O_s1_readdata_from_sa;
  output           USB_SDI_O_s1_reset_n;
  output           USB_SDI_O_s1_write_n;
  output  [ 31: 0] USB_SDI_O_s1_writedata;
  output           cpu_0_data_master_granted_USB_SDI_O_s1;
  output           cpu_0_data_master_qualified_request_USB_SDI_O_s1;
  output           cpu_0_data_master_read_data_valid_USB_SDI_O_s1;
  output           cpu_0_data_master_requests_USB_SDI_O_s1;
  output           d1_USB_SDI_O_s1_end_xfer;
  input   [ 31: 0] USB_SDI_O_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] USB_SDI_O_s1_address;
  wire             USB_SDI_O_s1_allgrants;
  wire             USB_SDI_O_s1_allow_new_arb_cycle;
  wire             USB_SDI_O_s1_any_bursting_master_saved_grant;
  wire             USB_SDI_O_s1_any_continuerequest;
  wire             USB_SDI_O_s1_arb_counter_enable;
  reg     [  1: 0] USB_SDI_O_s1_arb_share_counter;
  wire    [  1: 0] USB_SDI_O_s1_arb_share_counter_next_value;
  wire    [  1: 0] USB_SDI_O_s1_arb_share_set_values;
  wire             USB_SDI_O_s1_beginbursttransfer_internal;
  wire             USB_SDI_O_s1_begins_xfer;
  wire             USB_SDI_O_s1_chipselect;
  wire             USB_SDI_O_s1_end_xfer;
  wire             USB_SDI_O_s1_firsttransfer;
  wire             USB_SDI_O_s1_grant_vector;
  wire             USB_SDI_O_s1_in_a_read_cycle;
  wire             USB_SDI_O_s1_in_a_write_cycle;
  wire             USB_SDI_O_s1_master_qreq_vector;
  wire             USB_SDI_O_s1_non_bursting_master_requests;
  wire    [ 31: 0] USB_SDI_O_s1_readdata_from_sa;
  reg              USB_SDI_O_s1_reg_firsttransfer;
  wire             USB_SDI_O_s1_reset_n;
  reg              USB_SDI_O_s1_slavearbiterlockenable;
  wire             USB_SDI_O_s1_slavearbiterlockenable2;
  wire             USB_SDI_O_s1_unreg_firsttransfer;
  wire             USB_SDI_O_s1_waits_for_read;
  wire             USB_SDI_O_s1_waits_for_write;
  wire             USB_SDI_O_s1_write_n;
  wire    [ 31: 0] USB_SDI_O_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_USB_SDI_O_s1;
  wire             cpu_0_data_master_qualified_request_USB_SDI_O_s1;
  wire             cpu_0_data_master_read_data_valid_USB_SDI_O_s1;
  wire             cpu_0_data_master_requests_USB_SDI_O_s1;
  wire             cpu_0_data_master_saved_grant_USB_SDI_O_s1;
  reg              d1_USB_SDI_O_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_USB_SDI_O_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_USB_SDI_O_s1_from_cpu_0_data_master;
  wire             wait_for_USB_SDI_O_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~USB_SDI_O_s1_end_xfer;
    end


  assign USB_SDI_O_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_USB_SDI_O_s1));
  //assign USB_SDI_O_s1_readdata_from_sa = USB_SDI_O_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign USB_SDI_O_s1_readdata_from_sa = USB_SDI_O_s1_readdata;

  assign cpu_0_data_master_requests_USB_SDI_O_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h40021c0) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //USB_SDI_O_s1_arb_share_counter set values, which is an e_mux
  assign USB_SDI_O_s1_arb_share_set_values = 1;

  //USB_SDI_O_s1_non_bursting_master_requests mux, which is an e_mux
  assign USB_SDI_O_s1_non_bursting_master_requests = cpu_0_data_master_requests_USB_SDI_O_s1;

  //USB_SDI_O_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign USB_SDI_O_s1_any_bursting_master_saved_grant = 0;

  //USB_SDI_O_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign USB_SDI_O_s1_arb_share_counter_next_value = USB_SDI_O_s1_firsttransfer ? (USB_SDI_O_s1_arb_share_set_values - 1) : |USB_SDI_O_s1_arb_share_counter ? (USB_SDI_O_s1_arb_share_counter - 1) : 0;

  //USB_SDI_O_s1_allgrants all slave grants, which is an e_mux
  assign USB_SDI_O_s1_allgrants = |USB_SDI_O_s1_grant_vector;

  //USB_SDI_O_s1_end_xfer assignment, which is an e_assign
  assign USB_SDI_O_s1_end_xfer = ~(USB_SDI_O_s1_waits_for_read | USB_SDI_O_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_USB_SDI_O_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_USB_SDI_O_s1 = USB_SDI_O_s1_end_xfer & (~USB_SDI_O_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //USB_SDI_O_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign USB_SDI_O_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_USB_SDI_O_s1 & USB_SDI_O_s1_allgrants) | (end_xfer_arb_share_counter_term_USB_SDI_O_s1 & ~USB_SDI_O_s1_non_bursting_master_requests);

  //USB_SDI_O_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          USB_SDI_O_s1_arb_share_counter <= 0;
      else if (USB_SDI_O_s1_arb_counter_enable)
          USB_SDI_O_s1_arb_share_counter <= USB_SDI_O_s1_arb_share_counter_next_value;
    end


  //USB_SDI_O_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          USB_SDI_O_s1_slavearbiterlockenable <= 0;
      else if ((|USB_SDI_O_s1_master_qreq_vector & end_xfer_arb_share_counter_term_USB_SDI_O_s1) | (end_xfer_arb_share_counter_term_USB_SDI_O_s1 & ~USB_SDI_O_s1_non_bursting_master_requests))
          USB_SDI_O_s1_slavearbiterlockenable <= |USB_SDI_O_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master USB_SDI_O/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = USB_SDI_O_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //USB_SDI_O_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign USB_SDI_O_s1_slavearbiterlockenable2 = |USB_SDI_O_s1_arb_share_counter_next_value;

  //cpu_0/data_master USB_SDI_O/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = USB_SDI_O_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //USB_SDI_O_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign USB_SDI_O_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_USB_SDI_O_s1 = cpu_0_data_master_requests_USB_SDI_O_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_USB_SDI_O_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_USB_SDI_O_s1 = cpu_0_data_master_granted_USB_SDI_O_s1 & cpu_0_data_master_read & ~USB_SDI_O_s1_waits_for_read;

  //USB_SDI_O_s1_writedata mux, which is an e_mux
  assign USB_SDI_O_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_USB_SDI_O_s1 = cpu_0_data_master_qualified_request_USB_SDI_O_s1;

  //cpu_0/data_master saved-grant USB_SDI_O/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_USB_SDI_O_s1 = cpu_0_data_master_requests_USB_SDI_O_s1;

  //allow new arb cycle for USB_SDI_O/s1, which is an e_assign
  assign USB_SDI_O_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign USB_SDI_O_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign USB_SDI_O_s1_master_qreq_vector = 1;

  //USB_SDI_O_s1_reset_n assignment, which is an e_assign
  assign USB_SDI_O_s1_reset_n = reset_n;

  assign USB_SDI_O_s1_chipselect = cpu_0_data_master_granted_USB_SDI_O_s1;
  //USB_SDI_O_s1_firsttransfer first transaction, which is an e_assign
  assign USB_SDI_O_s1_firsttransfer = USB_SDI_O_s1_begins_xfer ? USB_SDI_O_s1_unreg_firsttransfer : USB_SDI_O_s1_reg_firsttransfer;

  //USB_SDI_O_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign USB_SDI_O_s1_unreg_firsttransfer = ~(USB_SDI_O_s1_slavearbiterlockenable & USB_SDI_O_s1_any_continuerequest);

  //USB_SDI_O_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          USB_SDI_O_s1_reg_firsttransfer <= 1'b1;
      else if (USB_SDI_O_s1_begins_xfer)
          USB_SDI_O_s1_reg_firsttransfer <= USB_SDI_O_s1_unreg_firsttransfer;
    end


  //USB_SDI_O_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign USB_SDI_O_s1_beginbursttransfer_internal = USB_SDI_O_s1_begins_xfer;

  //~USB_SDI_O_s1_write_n assignment, which is an e_mux
  assign USB_SDI_O_s1_write_n = ~(cpu_0_data_master_granted_USB_SDI_O_s1 & cpu_0_data_master_write);

  assign shifted_address_to_USB_SDI_O_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //USB_SDI_O_s1_address mux, which is an e_mux
  assign USB_SDI_O_s1_address = shifted_address_to_USB_SDI_O_s1_from_cpu_0_data_master >> 2;

  //d1_USB_SDI_O_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_USB_SDI_O_s1_end_xfer <= 1;
      else 
        d1_USB_SDI_O_s1_end_xfer <= USB_SDI_O_s1_end_xfer;
    end


  //USB_SDI_O_s1_waits_for_read in a cycle, which is an e_mux
  assign USB_SDI_O_s1_waits_for_read = USB_SDI_O_s1_in_a_read_cycle & USB_SDI_O_s1_begins_xfer;

  //USB_SDI_O_s1_in_a_read_cycle assignment, which is an e_assign
  assign USB_SDI_O_s1_in_a_read_cycle = cpu_0_data_master_granted_USB_SDI_O_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = USB_SDI_O_s1_in_a_read_cycle;

  //USB_SDI_O_s1_waits_for_write in a cycle, which is an e_mux
  assign USB_SDI_O_s1_waits_for_write = USB_SDI_O_s1_in_a_write_cycle & 0;

  //USB_SDI_O_s1_in_a_write_cycle assignment, which is an e_assign
  assign USB_SDI_O_s1_in_a_write_cycle = cpu_0_data_master_granted_USB_SDI_O_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = USB_SDI_O_s1_in_a_write_cycle;

  assign wait_for_USB_SDI_O_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //USB_SDI_O/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module USB_SDO_I_s1_arbitrator (
                                 // inputs:
                                  USB_SDO_I_s1_readdata,
                                  clk,
                                  cpu_0_data_master_address_to_slave,
                                  cpu_0_data_master_latency_counter,
                                  cpu_0_data_master_read,
                                  cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                  cpu_0_data_master_write,
                                  cpu_0_data_master_writedata,
                                  reset_n,

                                 // outputs:
                                  USB_SDO_I_s1_address,
                                  USB_SDO_I_s1_chipselect,
                                  USB_SDO_I_s1_readdata_from_sa,
                                  USB_SDO_I_s1_reset_n,
                                  USB_SDO_I_s1_write_n,
                                  USB_SDO_I_s1_writedata,
                                  cpu_0_data_master_granted_USB_SDO_I_s1,
                                  cpu_0_data_master_qualified_request_USB_SDO_I_s1,
                                  cpu_0_data_master_read_data_valid_USB_SDO_I_s1,
                                  cpu_0_data_master_requests_USB_SDO_I_s1,
                                  d1_USB_SDO_I_s1_end_xfer
                               )
;

  output  [  1: 0] USB_SDO_I_s1_address;
  output           USB_SDO_I_s1_chipselect;
  output  [ 31: 0] USB_SDO_I_s1_readdata_from_sa;
  output           USB_SDO_I_s1_reset_n;
  output           USB_SDO_I_s1_write_n;
  output  [ 31: 0] USB_SDO_I_s1_writedata;
  output           cpu_0_data_master_granted_USB_SDO_I_s1;
  output           cpu_0_data_master_qualified_request_USB_SDO_I_s1;
  output           cpu_0_data_master_read_data_valid_USB_SDO_I_s1;
  output           cpu_0_data_master_requests_USB_SDO_I_s1;
  output           d1_USB_SDO_I_s1_end_xfer;
  input   [ 31: 0] USB_SDO_I_s1_readdata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;

  wire    [  1: 0] USB_SDO_I_s1_address;
  wire             USB_SDO_I_s1_allgrants;
  wire             USB_SDO_I_s1_allow_new_arb_cycle;
  wire             USB_SDO_I_s1_any_bursting_master_saved_grant;
  wire             USB_SDO_I_s1_any_continuerequest;
  wire             USB_SDO_I_s1_arb_counter_enable;
  reg     [  1: 0] USB_SDO_I_s1_arb_share_counter;
  wire    [  1: 0] USB_SDO_I_s1_arb_share_counter_next_value;
  wire    [  1: 0] USB_SDO_I_s1_arb_share_set_values;
  wire             USB_SDO_I_s1_beginbursttransfer_internal;
  wire             USB_SDO_I_s1_begins_xfer;
  wire             USB_SDO_I_s1_chipselect;
  wire             USB_SDO_I_s1_end_xfer;
  wire             USB_SDO_I_s1_firsttransfer;
  wire             USB_SDO_I_s1_grant_vector;
  wire             USB_SDO_I_s1_in_a_read_cycle;
  wire             USB_SDO_I_s1_in_a_write_cycle;
  wire             USB_SDO_I_s1_master_qreq_vector;
  wire             USB_SDO_I_s1_non_bursting_master_requests;
  wire    [ 31: 0] USB_SDO_I_s1_readdata_from_sa;
  reg              USB_SDO_I_s1_reg_firsttransfer;
  wire             USB_SDO_I_s1_reset_n;
  reg              USB_SDO_I_s1_slavearbiterlockenable;
  wire             USB_SDO_I_s1_slavearbiterlockenable2;
  wire             USB_SDO_I_s1_unreg_firsttransfer;
  wire             USB_SDO_I_s1_waits_for_read;
  wire             USB_SDO_I_s1_waits_for_write;
  wire             USB_SDO_I_s1_write_n;
  wire    [ 31: 0] USB_SDO_I_s1_writedata;
  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_USB_SDO_I_s1;
  wire             cpu_0_data_master_qualified_request_USB_SDO_I_s1;
  wire             cpu_0_data_master_read_data_valid_USB_SDO_I_s1;
  wire             cpu_0_data_master_requests_USB_SDO_I_s1;
  wire             cpu_0_data_master_saved_grant_USB_SDO_I_s1;
  reg              d1_USB_SDO_I_s1_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_USB_SDO_I_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_USB_SDO_I_s1_from_cpu_0_data_master;
  wire             wait_for_USB_SDO_I_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~USB_SDO_I_s1_end_xfer;
    end


  assign USB_SDO_I_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_USB_SDO_I_s1));
  //assign USB_SDO_I_s1_readdata_from_sa = USB_SDO_I_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign USB_SDO_I_s1_readdata_from_sa = USB_SDO_I_s1_readdata;

  assign cpu_0_data_master_requests_USB_SDO_I_s1 = ({cpu_0_data_master_address_to_slave[26 : 4] , 4'b0} == 27'h40021b0) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //USB_SDO_I_s1_arb_share_counter set values, which is an e_mux
  assign USB_SDO_I_s1_arb_share_set_values = 1;

  //USB_SDO_I_s1_non_bursting_master_requests mux, which is an e_mux
  assign USB_SDO_I_s1_non_bursting_master_requests = cpu_0_data_master_requests_USB_SDO_I_s1;

  //USB_SDO_I_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign USB_SDO_I_s1_any_bursting_master_saved_grant = 0;

  //USB_SDO_I_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign USB_SDO_I_s1_arb_share_counter_next_value = USB_SDO_I_s1_firsttransfer ? (USB_SDO_I_s1_arb_share_set_values - 1) : |USB_SDO_I_s1_arb_share_counter ? (USB_SDO_I_s1_arb_share_counter - 1) : 0;

  //USB_SDO_I_s1_allgrants all slave grants, which is an e_mux
  assign USB_SDO_I_s1_allgrants = |USB_SDO_I_s1_grant_vector;

  //USB_SDO_I_s1_end_xfer assignment, which is an e_assign
  assign USB_SDO_I_s1_end_xfer = ~(USB_SDO_I_s1_waits_for_read | USB_SDO_I_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_USB_SDO_I_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_USB_SDO_I_s1 = USB_SDO_I_s1_end_xfer & (~USB_SDO_I_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //USB_SDO_I_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign USB_SDO_I_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_USB_SDO_I_s1 & USB_SDO_I_s1_allgrants) | (end_xfer_arb_share_counter_term_USB_SDO_I_s1 & ~USB_SDO_I_s1_non_bursting_master_requests);

  //USB_SDO_I_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          USB_SDO_I_s1_arb_share_counter <= 0;
      else if (USB_SDO_I_s1_arb_counter_enable)
          USB_SDO_I_s1_arb_share_counter <= USB_SDO_I_s1_arb_share_counter_next_value;
    end


  //USB_SDO_I_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          USB_SDO_I_s1_slavearbiterlockenable <= 0;
      else if ((|USB_SDO_I_s1_master_qreq_vector & end_xfer_arb_share_counter_term_USB_SDO_I_s1) | (end_xfer_arb_share_counter_term_USB_SDO_I_s1 & ~USB_SDO_I_s1_non_bursting_master_requests))
          USB_SDO_I_s1_slavearbiterlockenable <= |USB_SDO_I_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master USB_SDO_I/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = USB_SDO_I_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //USB_SDO_I_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign USB_SDO_I_s1_slavearbiterlockenable2 = |USB_SDO_I_s1_arb_share_counter_next_value;

  //cpu_0/data_master USB_SDO_I/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = USB_SDO_I_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //USB_SDO_I_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign USB_SDO_I_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_USB_SDO_I_s1 = cpu_0_data_master_requests_USB_SDO_I_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_USB_SDO_I_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_USB_SDO_I_s1 = cpu_0_data_master_granted_USB_SDO_I_s1 & cpu_0_data_master_read & ~USB_SDO_I_s1_waits_for_read;

  //USB_SDO_I_s1_writedata mux, which is an e_mux
  assign USB_SDO_I_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_USB_SDO_I_s1 = cpu_0_data_master_qualified_request_USB_SDO_I_s1;

  //cpu_0/data_master saved-grant USB_SDO_I/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_USB_SDO_I_s1 = cpu_0_data_master_requests_USB_SDO_I_s1;

  //allow new arb cycle for USB_SDO_I/s1, which is an e_assign
  assign USB_SDO_I_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign USB_SDO_I_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign USB_SDO_I_s1_master_qreq_vector = 1;

  //USB_SDO_I_s1_reset_n assignment, which is an e_assign
  assign USB_SDO_I_s1_reset_n = reset_n;

  assign USB_SDO_I_s1_chipselect = cpu_0_data_master_granted_USB_SDO_I_s1;
  //USB_SDO_I_s1_firsttransfer first transaction, which is an e_assign
  assign USB_SDO_I_s1_firsttransfer = USB_SDO_I_s1_begins_xfer ? USB_SDO_I_s1_unreg_firsttransfer : USB_SDO_I_s1_reg_firsttransfer;

  //USB_SDO_I_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign USB_SDO_I_s1_unreg_firsttransfer = ~(USB_SDO_I_s1_slavearbiterlockenable & USB_SDO_I_s1_any_continuerequest);

  //USB_SDO_I_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          USB_SDO_I_s1_reg_firsttransfer <= 1'b1;
      else if (USB_SDO_I_s1_begins_xfer)
          USB_SDO_I_s1_reg_firsttransfer <= USB_SDO_I_s1_unreg_firsttransfer;
    end


  //USB_SDO_I_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign USB_SDO_I_s1_beginbursttransfer_internal = USB_SDO_I_s1_begins_xfer;

  //~USB_SDO_I_s1_write_n assignment, which is an e_mux
  assign USB_SDO_I_s1_write_n = ~(cpu_0_data_master_granted_USB_SDO_I_s1 & cpu_0_data_master_write);

  assign shifted_address_to_USB_SDO_I_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //USB_SDO_I_s1_address mux, which is an e_mux
  assign USB_SDO_I_s1_address = shifted_address_to_USB_SDO_I_s1_from_cpu_0_data_master >> 2;

  //d1_USB_SDO_I_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_USB_SDO_I_s1_end_xfer <= 1;
      else 
        d1_USB_SDO_I_s1_end_xfer <= USB_SDO_I_s1_end_xfer;
    end


  //USB_SDO_I_s1_waits_for_read in a cycle, which is an e_mux
  assign USB_SDO_I_s1_waits_for_read = USB_SDO_I_s1_in_a_read_cycle & USB_SDO_I_s1_begins_xfer;

  //USB_SDO_I_s1_in_a_read_cycle assignment, which is an e_assign
  assign USB_SDO_I_s1_in_a_read_cycle = cpu_0_data_master_granted_USB_SDO_I_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = USB_SDO_I_s1_in_a_read_cycle;

  //USB_SDO_I_s1_waits_for_write in a cycle, which is an e_mux
  assign USB_SDO_I_s1_waits_for_write = USB_SDO_I_s1_in_a_write_cycle & 0;

  //USB_SDO_I_s1_in_a_write_cycle assignment, which is an e_assign
  assign USB_SDO_I_s1_in_a_write_cycle = cpu_0_data_master_granted_USB_SDO_I_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = USB_SDO_I_s1_in_a_write_cycle;

  assign wait_for_USB_SDO_I_s1_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //USB_SDO_I/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module cpu_0_jtag_debug_module_arbitrator (
                                            // inputs:
                                             clk,
                                             cpu_0_data_master_address_to_slave,
                                             cpu_0_data_master_byteenable,
                                             cpu_0_data_master_debugaccess,
                                             cpu_0_data_master_latency_counter,
                                             cpu_0_data_master_read,
                                             cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                             cpu_0_data_master_write,
                                             cpu_0_data_master_writedata,
                                             cpu_0_instruction_master_address_to_slave,
                                             cpu_0_instruction_master_latency_counter,
                                             cpu_0_instruction_master_read,
                                             cpu_0_instruction_master_read_data_valid_sdram_0_s1_shift_register,
                                             cpu_0_jtag_debug_module_readdata,
                                             cpu_0_jtag_debug_module_resetrequest,
                                             reset_n,

                                            // outputs:
                                             cpu_0_data_master_granted_cpu_0_jtag_debug_module,
                                             cpu_0_data_master_qualified_request_cpu_0_jtag_debug_module,
                                             cpu_0_data_master_read_data_valid_cpu_0_jtag_debug_module,
                                             cpu_0_data_master_requests_cpu_0_jtag_debug_module,
                                             cpu_0_instruction_master_granted_cpu_0_jtag_debug_module,
                                             cpu_0_instruction_master_qualified_request_cpu_0_jtag_debug_module,
                                             cpu_0_instruction_master_read_data_valid_cpu_0_jtag_debug_module,
                                             cpu_0_instruction_master_requests_cpu_0_jtag_debug_module,
                                             cpu_0_jtag_debug_module_address,
                                             cpu_0_jtag_debug_module_begintransfer,
                                             cpu_0_jtag_debug_module_byteenable,
                                             cpu_0_jtag_debug_module_chipselect,
                                             cpu_0_jtag_debug_module_debugaccess,
                                             cpu_0_jtag_debug_module_readdata_from_sa,
                                             cpu_0_jtag_debug_module_reset_n,
                                             cpu_0_jtag_debug_module_resetrequest_from_sa,
                                             cpu_0_jtag_debug_module_write,
                                             cpu_0_jtag_debug_module_writedata,
                                             d1_cpu_0_jtag_debug_module_end_xfer
                                          )
;

  output           cpu_0_data_master_granted_cpu_0_jtag_debug_module;
  output           cpu_0_data_master_qualified_request_cpu_0_jtag_debug_module;
  output           cpu_0_data_master_read_data_valid_cpu_0_jtag_debug_module;
  output           cpu_0_data_master_requests_cpu_0_jtag_debug_module;
  output           cpu_0_instruction_master_granted_cpu_0_jtag_debug_module;
  output           cpu_0_instruction_master_qualified_request_cpu_0_jtag_debug_module;
  output           cpu_0_instruction_master_read_data_valid_cpu_0_jtag_debug_module;
  output           cpu_0_instruction_master_requests_cpu_0_jtag_debug_module;
  output  [  8: 0] cpu_0_jtag_debug_module_address;
  output           cpu_0_jtag_debug_module_begintransfer;
  output  [  3: 0] cpu_0_jtag_debug_module_byteenable;
  output           cpu_0_jtag_debug_module_chipselect;
  output           cpu_0_jtag_debug_module_debugaccess;
  output  [ 31: 0] cpu_0_jtag_debug_module_readdata_from_sa;
  output           cpu_0_jtag_debug_module_reset_n;
  output           cpu_0_jtag_debug_module_resetrequest_from_sa;
  output           cpu_0_jtag_debug_module_write;
  output  [ 31: 0] cpu_0_jtag_debug_module_writedata;
  output           d1_cpu_0_jtag_debug_module_end_xfer;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input   [  3: 0] cpu_0_data_master_byteenable;
  input            cpu_0_data_master_debugaccess;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input   [ 26: 0] cpu_0_instruction_master_address_to_slave;
  input            cpu_0_instruction_master_latency_counter;
  input            cpu_0_instruction_master_read;
  input            cpu_0_instruction_master_read_data_valid_sdram_0_s1_shift_register;
  input   [ 31: 0] cpu_0_jtag_debug_module_readdata;
  input            cpu_0_jtag_debug_module_resetrequest;
  input            reset_n;

  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_cpu_0_jtag_debug_module;
  wire             cpu_0_data_master_qualified_request_cpu_0_jtag_debug_module;
  wire             cpu_0_data_master_read_data_valid_cpu_0_jtag_debug_module;
  wire             cpu_0_data_master_requests_cpu_0_jtag_debug_module;
  wire             cpu_0_data_master_saved_grant_cpu_0_jtag_debug_module;
  wire             cpu_0_instruction_master_arbiterlock;
  wire             cpu_0_instruction_master_arbiterlock2;
  wire             cpu_0_instruction_master_continuerequest;
  wire             cpu_0_instruction_master_granted_cpu_0_jtag_debug_module;
  wire             cpu_0_instruction_master_qualified_request_cpu_0_jtag_debug_module;
  wire             cpu_0_instruction_master_read_data_valid_cpu_0_jtag_debug_module;
  wire             cpu_0_instruction_master_requests_cpu_0_jtag_debug_module;
  wire             cpu_0_instruction_master_saved_grant_cpu_0_jtag_debug_module;
  wire    [  8: 0] cpu_0_jtag_debug_module_address;
  wire             cpu_0_jtag_debug_module_allgrants;
  wire             cpu_0_jtag_debug_module_allow_new_arb_cycle;
  wire             cpu_0_jtag_debug_module_any_bursting_master_saved_grant;
  wire             cpu_0_jtag_debug_module_any_continuerequest;
  reg     [  1: 0] cpu_0_jtag_debug_module_arb_addend;
  wire             cpu_0_jtag_debug_module_arb_counter_enable;
  reg     [  1: 0] cpu_0_jtag_debug_module_arb_share_counter;
  wire    [  1: 0] cpu_0_jtag_debug_module_arb_share_counter_next_value;
  wire    [  1: 0] cpu_0_jtag_debug_module_arb_share_set_values;
  wire    [  1: 0] cpu_0_jtag_debug_module_arb_winner;
  wire             cpu_0_jtag_debug_module_arbitration_holdoff_internal;
  wire             cpu_0_jtag_debug_module_beginbursttransfer_internal;
  wire             cpu_0_jtag_debug_module_begins_xfer;
  wire             cpu_0_jtag_debug_module_begintransfer;
  wire    [  3: 0] cpu_0_jtag_debug_module_byteenable;
  wire             cpu_0_jtag_debug_module_chipselect;
  wire    [  3: 0] cpu_0_jtag_debug_module_chosen_master_double_vector;
  wire    [  1: 0] cpu_0_jtag_debug_module_chosen_master_rot_left;
  wire             cpu_0_jtag_debug_module_debugaccess;
  wire             cpu_0_jtag_debug_module_end_xfer;
  wire             cpu_0_jtag_debug_module_firsttransfer;
  wire    [  1: 0] cpu_0_jtag_debug_module_grant_vector;
  wire             cpu_0_jtag_debug_module_in_a_read_cycle;
  wire             cpu_0_jtag_debug_module_in_a_write_cycle;
  wire    [  1: 0] cpu_0_jtag_debug_module_master_qreq_vector;
  wire             cpu_0_jtag_debug_module_non_bursting_master_requests;
  wire    [ 31: 0] cpu_0_jtag_debug_module_readdata_from_sa;
  reg              cpu_0_jtag_debug_module_reg_firsttransfer;
  wire             cpu_0_jtag_debug_module_reset_n;
  wire             cpu_0_jtag_debug_module_resetrequest_from_sa;
  reg     [  1: 0] cpu_0_jtag_debug_module_saved_chosen_master_vector;
  reg              cpu_0_jtag_debug_module_slavearbiterlockenable;
  wire             cpu_0_jtag_debug_module_slavearbiterlockenable2;
  wire             cpu_0_jtag_debug_module_unreg_firsttransfer;
  wire             cpu_0_jtag_debug_module_waits_for_read;
  wire             cpu_0_jtag_debug_module_waits_for_write;
  wire             cpu_0_jtag_debug_module_write;
  wire    [ 31: 0] cpu_0_jtag_debug_module_writedata;
  reg              d1_cpu_0_jtag_debug_module_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_cpu_0_jtag_debug_module;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  reg              last_cycle_cpu_0_data_master_granted_slave_cpu_0_jtag_debug_module;
  reg              last_cycle_cpu_0_instruction_master_granted_slave_cpu_0_jtag_debug_module;
  wire    [ 26: 0] shifted_address_to_cpu_0_jtag_debug_module_from_cpu_0_data_master;
  wire    [ 26: 0] shifted_address_to_cpu_0_jtag_debug_module_from_cpu_0_instruction_master;
  wire             wait_for_cpu_0_jtag_debug_module_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~cpu_0_jtag_debug_module_end_xfer;
    end


  assign cpu_0_jtag_debug_module_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_cpu_0_jtag_debug_module | cpu_0_instruction_master_qualified_request_cpu_0_jtag_debug_module));
  //assign cpu_0_jtag_debug_module_readdata_from_sa = cpu_0_jtag_debug_module_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign cpu_0_jtag_debug_module_readdata_from_sa = cpu_0_jtag_debug_module_readdata;

  assign cpu_0_data_master_requests_cpu_0_jtag_debug_module = ({cpu_0_data_master_address_to_slave[26 : 11] , 11'b0} == 27'h4001000) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //cpu_0_jtag_debug_module_arb_share_counter set values, which is an e_mux
  assign cpu_0_jtag_debug_module_arb_share_set_values = 1;

  //cpu_0_jtag_debug_module_non_bursting_master_requests mux, which is an e_mux
  assign cpu_0_jtag_debug_module_non_bursting_master_requests = cpu_0_data_master_requests_cpu_0_jtag_debug_module |
    cpu_0_instruction_master_requests_cpu_0_jtag_debug_module |
    cpu_0_data_master_requests_cpu_0_jtag_debug_module |
    cpu_0_instruction_master_requests_cpu_0_jtag_debug_module;

  //cpu_0_jtag_debug_module_any_bursting_master_saved_grant mux, which is an e_mux
  assign cpu_0_jtag_debug_module_any_bursting_master_saved_grant = 0;

  //cpu_0_jtag_debug_module_arb_share_counter_next_value assignment, which is an e_assign
  assign cpu_0_jtag_debug_module_arb_share_counter_next_value = cpu_0_jtag_debug_module_firsttransfer ? (cpu_0_jtag_debug_module_arb_share_set_values - 1) : |cpu_0_jtag_debug_module_arb_share_counter ? (cpu_0_jtag_debug_module_arb_share_counter - 1) : 0;

  //cpu_0_jtag_debug_module_allgrants all slave grants, which is an e_mux
  assign cpu_0_jtag_debug_module_allgrants = (|cpu_0_jtag_debug_module_grant_vector) |
    (|cpu_0_jtag_debug_module_grant_vector) |
    (|cpu_0_jtag_debug_module_grant_vector) |
    (|cpu_0_jtag_debug_module_grant_vector);

  //cpu_0_jtag_debug_module_end_xfer assignment, which is an e_assign
  assign cpu_0_jtag_debug_module_end_xfer = ~(cpu_0_jtag_debug_module_waits_for_read | cpu_0_jtag_debug_module_waits_for_write);

  //end_xfer_arb_share_counter_term_cpu_0_jtag_debug_module arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_cpu_0_jtag_debug_module = cpu_0_jtag_debug_module_end_xfer & (~cpu_0_jtag_debug_module_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //cpu_0_jtag_debug_module_arb_share_counter arbitration counter enable, which is an e_assign
  assign cpu_0_jtag_debug_module_arb_counter_enable = (end_xfer_arb_share_counter_term_cpu_0_jtag_debug_module & cpu_0_jtag_debug_module_allgrants) | (end_xfer_arb_share_counter_term_cpu_0_jtag_debug_module & ~cpu_0_jtag_debug_module_non_bursting_master_requests);

  //cpu_0_jtag_debug_module_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          cpu_0_jtag_debug_module_arb_share_counter <= 0;
      else if (cpu_0_jtag_debug_module_arb_counter_enable)
          cpu_0_jtag_debug_module_arb_share_counter <= cpu_0_jtag_debug_module_arb_share_counter_next_value;
    end


  //cpu_0_jtag_debug_module_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          cpu_0_jtag_debug_module_slavearbiterlockenable <= 0;
      else if ((|cpu_0_jtag_debug_module_master_qreq_vector & end_xfer_arb_share_counter_term_cpu_0_jtag_debug_module) | (end_xfer_arb_share_counter_term_cpu_0_jtag_debug_module & ~cpu_0_jtag_debug_module_non_bursting_master_requests))
          cpu_0_jtag_debug_module_slavearbiterlockenable <= |cpu_0_jtag_debug_module_arb_share_counter_next_value;
    end


  //cpu_0/data_master cpu_0/jtag_debug_module arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = cpu_0_jtag_debug_module_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //cpu_0_jtag_debug_module_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign cpu_0_jtag_debug_module_slavearbiterlockenable2 = |cpu_0_jtag_debug_module_arb_share_counter_next_value;

  //cpu_0/data_master cpu_0/jtag_debug_module arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = cpu_0_jtag_debug_module_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //cpu_0/instruction_master cpu_0/jtag_debug_module arbiterlock, which is an e_assign
  assign cpu_0_instruction_master_arbiterlock = cpu_0_jtag_debug_module_slavearbiterlockenable & cpu_0_instruction_master_continuerequest;

  //cpu_0/instruction_master cpu_0/jtag_debug_module arbiterlock2, which is an e_assign
  assign cpu_0_instruction_master_arbiterlock2 = cpu_0_jtag_debug_module_slavearbiterlockenable2 & cpu_0_instruction_master_continuerequest;

  //cpu_0/instruction_master granted cpu_0/jtag_debug_module last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_cpu_0_instruction_master_granted_slave_cpu_0_jtag_debug_module <= 0;
      else 
        last_cycle_cpu_0_instruction_master_granted_slave_cpu_0_jtag_debug_module <= cpu_0_instruction_master_saved_grant_cpu_0_jtag_debug_module ? 1 : (cpu_0_jtag_debug_module_arbitration_holdoff_internal | ~cpu_0_instruction_master_requests_cpu_0_jtag_debug_module) ? 0 : last_cycle_cpu_0_instruction_master_granted_slave_cpu_0_jtag_debug_module;
    end


  //cpu_0_instruction_master_continuerequest continued request, which is an e_mux
  assign cpu_0_instruction_master_continuerequest = last_cycle_cpu_0_instruction_master_granted_slave_cpu_0_jtag_debug_module & cpu_0_instruction_master_requests_cpu_0_jtag_debug_module;

  //cpu_0_jtag_debug_module_any_continuerequest at least one master continues requesting, which is an e_mux
  assign cpu_0_jtag_debug_module_any_continuerequest = cpu_0_instruction_master_continuerequest |
    cpu_0_data_master_continuerequest;

  assign cpu_0_data_master_qualified_request_cpu_0_jtag_debug_module = cpu_0_data_master_requests_cpu_0_jtag_debug_module & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))) | cpu_0_instruction_master_arbiterlock);
  //local readdatavalid cpu_0_data_master_read_data_valid_cpu_0_jtag_debug_module, which is an e_mux
  assign cpu_0_data_master_read_data_valid_cpu_0_jtag_debug_module = cpu_0_data_master_granted_cpu_0_jtag_debug_module & cpu_0_data_master_read & ~cpu_0_jtag_debug_module_waits_for_read;

  //cpu_0_jtag_debug_module_writedata mux, which is an e_mux
  assign cpu_0_jtag_debug_module_writedata = cpu_0_data_master_writedata;

  assign cpu_0_instruction_master_requests_cpu_0_jtag_debug_module = (({cpu_0_instruction_master_address_to_slave[26 : 11] , 11'b0} == 27'h4001000) & (cpu_0_instruction_master_read)) & cpu_0_instruction_master_read;
  //cpu_0/data_master granted cpu_0/jtag_debug_module last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_cpu_0_data_master_granted_slave_cpu_0_jtag_debug_module <= 0;
      else 
        last_cycle_cpu_0_data_master_granted_slave_cpu_0_jtag_debug_module <= cpu_0_data_master_saved_grant_cpu_0_jtag_debug_module ? 1 : (cpu_0_jtag_debug_module_arbitration_holdoff_internal | ~cpu_0_data_master_requests_cpu_0_jtag_debug_module) ? 0 : last_cycle_cpu_0_data_master_granted_slave_cpu_0_jtag_debug_module;
    end


  //cpu_0_data_master_continuerequest continued request, which is an e_mux
  assign cpu_0_data_master_continuerequest = last_cycle_cpu_0_data_master_granted_slave_cpu_0_jtag_debug_module & cpu_0_data_master_requests_cpu_0_jtag_debug_module;

  assign cpu_0_instruction_master_qualified_request_cpu_0_jtag_debug_module = cpu_0_instruction_master_requests_cpu_0_jtag_debug_module & ~((cpu_0_instruction_master_read & ((cpu_0_instruction_master_latency_counter != 0) | (|cpu_0_instruction_master_read_data_valid_sdram_0_s1_shift_register))) | cpu_0_data_master_arbiterlock);
  //local readdatavalid cpu_0_instruction_master_read_data_valid_cpu_0_jtag_debug_module, which is an e_mux
  assign cpu_0_instruction_master_read_data_valid_cpu_0_jtag_debug_module = cpu_0_instruction_master_granted_cpu_0_jtag_debug_module & cpu_0_instruction_master_read & ~cpu_0_jtag_debug_module_waits_for_read;

  //allow new arb cycle for cpu_0/jtag_debug_module, which is an e_assign
  assign cpu_0_jtag_debug_module_allow_new_arb_cycle = ~cpu_0_data_master_arbiterlock & ~cpu_0_instruction_master_arbiterlock;

  //cpu_0/instruction_master assignment into master qualified-requests vector for cpu_0/jtag_debug_module, which is an e_assign
  assign cpu_0_jtag_debug_module_master_qreq_vector[0] = cpu_0_instruction_master_qualified_request_cpu_0_jtag_debug_module;

  //cpu_0/instruction_master grant cpu_0/jtag_debug_module, which is an e_assign
  assign cpu_0_instruction_master_granted_cpu_0_jtag_debug_module = cpu_0_jtag_debug_module_grant_vector[0];

  //cpu_0/instruction_master saved-grant cpu_0/jtag_debug_module, which is an e_assign
  assign cpu_0_instruction_master_saved_grant_cpu_0_jtag_debug_module = cpu_0_jtag_debug_module_arb_winner[0] && cpu_0_instruction_master_requests_cpu_0_jtag_debug_module;

  //cpu_0/data_master assignment into master qualified-requests vector for cpu_0/jtag_debug_module, which is an e_assign
  assign cpu_0_jtag_debug_module_master_qreq_vector[1] = cpu_0_data_master_qualified_request_cpu_0_jtag_debug_module;

  //cpu_0/data_master grant cpu_0/jtag_debug_module, which is an e_assign
  assign cpu_0_data_master_granted_cpu_0_jtag_debug_module = cpu_0_jtag_debug_module_grant_vector[1];

  //cpu_0/data_master saved-grant cpu_0/jtag_debug_module, which is an e_assign
  assign cpu_0_data_master_saved_grant_cpu_0_jtag_debug_module = cpu_0_jtag_debug_module_arb_winner[1] && cpu_0_data_master_requests_cpu_0_jtag_debug_module;

  //cpu_0/jtag_debug_module chosen-master double-vector, which is an e_assign
  assign cpu_0_jtag_debug_module_chosen_master_double_vector = {cpu_0_jtag_debug_module_master_qreq_vector, cpu_0_jtag_debug_module_master_qreq_vector} & ({~cpu_0_jtag_debug_module_master_qreq_vector, ~cpu_0_jtag_debug_module_master_qreq_vector} + cpu_0_jtag_debug_module_arb_addend);

  //stable onehot encoding of arb winner
  assign cpu_0_jtag_debug_module_arb_winner = (cpu_0_jtag_debug_module_allow_new_arb_cycle & | cpu_0_jtag_debug_module_grant_vector) ? cpu_0_jtag_debug_module_grant_vector : cpu_0_jtag_debug_module_saved_chosen_master_vector;

  //saved cpu_0_jtag_debug_module_grant_vector, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          cpu_0_jtag_debug_module_saved_chosen_master_vector <= 0;
      else if (cpu_0_jtag_debug_module_allow_new_arb_cycle)
          cpu_0_jtag_debug_module_saved_chosen_master_vector <= |cpu_0_jtag_debug_module_grant_vector ? cpu_0_jtag_debug_module_grant_vector : cpu_0_jtag_debug_module_saved_chosen_master_vector;
    end


  //onehot encoding of chosen master
  assign cpu_0_jtag_debug_module_grant_vector = {(cpu_0_jtag_debug_module_chosen_master_double_vector[1] | cpu_0_jtag_debug_module_chosen_master_double_vector[3]),
    (cpu_0_jtag_debug_module_chosen_master_double_vector[0] | cpu_0_jtag_debug_module_chosen_master_double_vector[2])};

  //cpu_0/jtag_debug_module chosen master rotated left, which is an e_assign
  assign cpu_0_jtag_debug_module_chosen_master_rot_left = (cpu_0_jtag_debug_module_arb_winner << 1) ? (cpu_0_jtag_debug_module_arb_winner << 1) : 1;

  //cpu_0/jtag_debug_module's addend for next-master-grant
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          cpu_0_jtag_debug_module_arb_addend <= 1;
      else if (|cpu_0_jtag_debug_module_grant_vector)
          cpu_0_jtag_debug_module_arb_addend <= cpu_0_jtag_debug_module_end_xfer? cpu_0_jtag_debug_module_chosen_master_rot_left : cpu_0_jtag_debug_module_grant_vector;
    end


  assign cpu_0_jtag_debug_module_begintransfer = cpu_0_jtag_debug_module_begins_xfer;
  //cpu_0_jtag_debug_module_reset_n assignment, which is an e_assign
  assign cpu_0_jtag_debug_module_reset_n = reset_n;

  //assign cpu_0_jtag_debug_module_resetrequest_from_sa = cpu_0_jtag_debug_module_resetrequest so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign cpu_0_jtag_debug_module_resetrequest_from_sa = cpu_0_jtag_debug_module_resetrequest;

  assign cpu_0_jtag_debug_module_chipselect = cpu_0_data_master_granted_cpu_0_jtag_debug_module | cpu_0_instruction_master_granted_cpu_0_jtag_debug_module;
  //cpu_0_jtag_debug_module_firsttransfer first transaction, which is an e_assign
  assign cpu_0_jtag_debug_module_firsttransfer = cpu_0_jtag_debug_module_begins_xfer ? cpu_0_jtag_debug_module_unreg_firsttransfer : cpu_0_jtag_debug_module_reg_firsttransfer;

  //cpu_0_jtag_debug_module_unreg_firsttransfer first transaction, which is an e_assign
  assign cpu_0_jtag_debug_module_unreg_firsttransfer = ~(cpu_0_jtag_debug_module_slavearbiterlockenable & cpu_0_jtag_debug_module_any_continuerequest);

  //cpu_0_jtag_debug_module_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          cpu_0_jtag_debug_module_reg_firsttransfer <= 1'b1;
      else if (cpu_0_jtag_debug_module_begins_xfer)
          cpu_0_jtag_debug_module_reg_firsttransfer <= cpu_0_jtag_debug_module_unreg_firsttransfer;
    end


  //cpu_0_jtag_debug_module_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign cpu_0_jtag_debug_module_beginbursttransfer_internal = cpu_0_jtag_debug_module_begins_xfer;

  //cpu_0_jtag_debug_module_arbitration_holdoff_internal arbitration_holdoff, which is an e_assign
  assign cpu_0_jtag_debug_module_arbitration_holdoff_internal = cpu_0_jtag_debug_module_begins_xfer & cpu_0_jtag_debug_module_firsttransfer;

  //cpu_0_jtag_debug_module_write assignment, which is an e_mux
  assign cpu_0_jtag_debug_module_write = cpu_0_data_master_granted_cpu_0_jtag_debug_module & cpu_0_data_master_write;

  assign shifted_address_to_cpu_0_jtag_debug_module_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //cpu_0_jtag_debug_module_address mux, which is an e_mux
  assign cpu_0_jtag_debug_module_address = (cpu_0_data_master_granted_cpu_0_jtag_debug_module)? (shifted_address_to_cpu_0_jtag_debug_module_from_cpu_0_data_master >> 2) :
    (shifted_address_to_cpu_0_jtag_debug_module_from_cpu_0_instruction_master >> 2);

  assign shifted_address_to_cpu_0_jtag_debug_module_from_cpu_0_instruction_master = cpu_0_instruction_master_address_to_slave;
  //d1_cpu_0_jtag_debug_module_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_cpu_0_jtag_debug_module_end_xfer <= 1;
      else 
        d1_cpu_0_jtag_debug_module_end_xfer <= cpu_0_jtag_debug_module_end_xfer;
    end


  //cpu_0_jtag_debug_module_waits_for_read in a cycle, which is an e_mux
  assign cpu_0_jtag_debug_module_waits_for_read = cpu_0_jtag_debug_module_in_a_read_cycle & cpu_0_jtag_debug_module_begins_xfer;

  //cpu_0_jtag_debug_module_in_a_read_cycle assignment, which is an e_assign
  assign cpu_0_jtag_debug_module_in_a_read_cycle = (cpu_0_data_master_granted_cpu_0_jtag_debug_module & cpu_0_data_master_read) | (cpu_0_instruction_master_granted_cpu_0_jtag_debug_module & cpu_0_instruction_master_read);

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = cpu_0_jtag_debug_module_in_a_read_cycle;

  //cpu_0_jtag_debug_module_waits_for_write in a cycle, which is an e_mux
  assign cpu_0_jtag_debug_module_waits_for_write = cpu_0_jtag_debug_module_in_a_write_cycle & 0;

  //cpu_0_jtag_debug_module_in_a_write_cycle assignment, which is an e_assign
  assign cpu_0_jtag_debug_module_in_a_write_cycle = cpu_0_data_master_granted_cpu_0_jtag_debug_module & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = cpu_0_jtag_debug_module_in_a_write_cycle;

  assign wait_for_cpu_0_jtag_debug_module_counter = 0;
  //cpu_0_jtag_debug_module_byteenable byte enable port mux, which is an e_mux
  assign cpu_0_jtag_debug_module_byteenable = (cpu_0_data_master_granted_cpu_0_jtag_debug_module)? cpu_0_data_master_byteenable :
    -1;

  //debugaccess mux, which is an e_mux
  assign cpu_0_jtag_debug_module_debugaccess = (cpu_0_data_master_granted_cpu_0_jtag_debug_module)? cpu_0_data_master_debugaccess :
    0;


//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //cpu_0/jtag_debug_module enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end


  //grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (cpu_0_data_master_granted_cpu_0_jtag_debug_module + cpu_0_instruction_master_granted_cpu_0_jtag_debug_module > 1)
        begin
          $write("%0d ns: > 1 of grant signals are active simultaneously", $time);
          $stop;
        end
    end


  //saved_grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (cpu_0_data_master_saved_grant_cpu_0_jtag_debug_module + cpu_0_instruction_master_saved_grant_cpu_0_jtag_debug_module > 1)
        begin
          $write("%0d ns: > 1 of saved_grant signals are active simultaneously", $time);
          $stop;
        end
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module cpu_0_data_master_arbitrator (
                                      // inputs:
                                       ADC_DATA_s1_readdata_from_sa,
                                       BUZZER_DATA_s1_readdata_from_sa,
                                       DAC_DATA_s1_readdata_from_sa,
                                       ETH_CLKOUT_I_s1_readdata_from_sa,
                                       ETH_CS_O_s1_readdata_from_sa,
                                       ETH_INT_I_s1_readdata_from_sa,
                                       ETH_RESET_O_s1_readdata_from_sa,
                                       ETH_SCK_O_s1_readdata_from_sa,
                                       ETH_SI_O_s1_readdata_from_sa,
                                       ETH_SO_I_s1_readdata_from_sa,
                                       ETH_WOL_I_s1_readdata_from_sa,
                                       IR_DATA_s1_readdata_from_sa,
                                       KEY_FOCUS_s1_readdata_from_sa,
                                       LCD_CS_s1_readdata_from_sa,
                                       LCD_DATA_s1_readdata_from_sa,
                                       LCD_RD_s1_readdata_from_sa,
                                       LCD_RST_s1_readdata_from_sa,
                                       LCD_RS_s1_readdata_from_sa,
                                       LCD_WR_s1_readdata_from_sa,
                                       LED_DATA_s1_readdata_from_sa,
                                       PS2_DATA_REC_s1_readdata_from_sa,
                                       RTC_DATA_s1_readdata_from_sa,
                                       SCL_s1_readdata_from_sa,
                                       SDA_s1_readdata_from_sa,
                                       SD_CLK_s1_readdata_from_sa,
                                       SD_CS_s1_readdata_from_sa,
                                       SD_DI_s1_readdata_from_sa,
                                       SD_DO_s1_readdata_from_sa,
                                       TEMP_DATA_s1_readdata_from_sa,
                                       TUBE_EN_s1_readdata_from_sa,
                                       UART_RX_DATA_s1_readdata_from_sa,
                                       USB_INT_I_s1_readdata_from_sa,
                                       USB_PC_I_s1_readdata_from_sa,
                                       USB_RST_O_s1_readdata_from_sa,
                                       USB_SCK_O_s1_readdata_from_sa,
                                       USB_SCS_O_s1_readdata_from_sa,
                                       USB_SDI_O_s1_readdata_from_sa,
                                       USB_SDO_I_s1_readdata_from_sa,
                                       clk,
                                       cpu_0_data_master_address,
                                       cpu_0_data_master_byteenable,
                                       cpu_0_data_master_byteenable_sdram_0_s1,
                                       cpu_0_data_master_granted_ADC_DATA_s1,
                                       cpu_0_data_master_granted_BUZZER_DATA_s1,
                                       cpu_0_data_master_granted_DAC_DATA_s1,
                                       cpu_0_data_master_granted_ETH_CLKOUT_I_s1,
                                       cpu_0_data_master_granted_ETH_CS_O_s1,
                                       cpu_0_data_master_granted_ETH_INT_I_s1,
                                       cpu_0_data_master_granted_ETH_RESET_O_s1,
                                       cpu_0_data_master_granted_ETH_SCK_O_s1,
                                       cpu_0_data_master_granted_ETH_SI_O_s1,
                                       cpu_0_data_master_granted_ETH_SO_I_s1,
                                       cpu_0_data_master_granted_ETH_WOL_I_s1,
                                       cpu_0_data_master_granted_IR_DATA_s1,
                                       cpu_0_data_master_granted_KEY_FOCUS_s1,
                                       cpu_0_data_master_granted_LCD_CS_s1,
                                       cpu_0_data_master_granted_LCD_DATA_s1,
                                       cpu_0_data_master_granted_LCD_RD_s1,
                                       cpu_0_data_master_granted_LCD_RST_s1,
                                       cpu_0_data_master_granted_LCD_RS_s1,
                                       cpu_0_data_master_granted_LCD_WR_s1,
                                       cpu_0_data_master_granted_LED_DATA_s1,
                                       cpu_0_data_master_granted_PS2_DATA_REC_s1,
                                       cpu_0_data_master_granted_RTC_DATA_s1,
                                       cpu_0_data_master_granted_SCL_s1,
                                       cpu_0_data_master_granted_SDA_s1,
                                       cpu_0_data_master_granted_SD_CLK_s1,
                                       cpu_0_data_master_granted_SD_CS_s1,
                                       cpu_0_data_master_granted_SD_DI_s1,
                                       cpu_0_data_master_granted_SD_DO_s1,
                                       cpu_0_data_master_granted_TEMP_DATA_s1,
                                       cpu_0_data_master_granted_TUBE_EN_s1,
                                       cpu_0_data_master_granted_UART_RX_DATA_s1,
                                       cpu_0_data_master_granted_USB_INT_I_s1,
                                       cpu_0_data_master_granted_USB_PC_I_s1,
                                       cpu_0_data_master_granted_USB_RST_O_s1,
                                       cpu_0_data_master_granted_USB_SCK_O_s1,
                                       cpu_0_data_master_granted_USB_SCS_O_s1,
                                       cpu_0_data_master_granted_USB_SDI_O_s1,
                                       cpu_0_data_master_granted_USB_SDO_I_s1,
                                       cpu_0_data_master_granted_cpu_0_jtag_debug_module,
                                       cpu_0_data_master_granted_epcs_flash_controller_0_epcs_control_port,
                                       cpu_0_data_master_granted_sdram_0_s1,
                                       cpu_0_data_master_granted_sysid_0_control_slave,
                                       cpu_0_data_master_granted_timer_0_s1,
                                       cpu_0_data_master_granted_timer_1_s1,
                                       cpu_0_data_master_granted_uart_0_s1,
                                       cpu_0_data_master_qualified_request_ADC_DATA_s1,
                                       cpu_0_data_master_qualified_request_BUZZER_DATA_s1,
                                       cpu_0_data_master_qualified_request_DAC_DATA_s1,
                                       cpu_0_data_master_qualified_request_ETH_CLKOUT_I_s1,
                                       cpu_0_data_master_qualified_request_ETH_CS_O_s1,
                                       cpu_0_data_master_qualified_request_ETH_INT_I_s1,
                                       cpu_0_data_master_qualified_request_ETH_RESET_O_s1,
                                       cpu_0_data_master_qualified_request_ETH_SCK_O_s1,
                                       cpu_0_data_master_qualified_request_ETH_SI_O_s1,
                                       cpu_0_data_master_qualified_request_ETH_SO_I_s1,
                                       cpu_0_data_master_qualified_request_ETH_WOL_I_s1,
                                       cpu_0_data_master_qualified_request_IR_DATA_s1,
                                       cpu_0_data_master_qualified_request_KEY_FOCUS_s1,
                                       cpu_0_data_master_qualified_request_LCD_CS_s1,
                                       cpu_0_data_master_qualified_request_LCD_DATA_s1,
                                       cpu_0_data_master_qualified_request_LCD_RD_s1,
                                       cpu_0_data_master_qualified_request_LCD_RST_s1,
                                       cpu_0_data_master_qualified_request_LCD_RS_s1,
                                       cpu_0_data_master_qualified_request_LCD_WR_s1,
                                       cpu_0_data_master_qualified_request_LED_DATA_s1,
                                       cpu_0_data_master_qualified_request_PS2_DATA_REC_s1,
                                       cpu_0_data_master_qualified_request_RTC_DATA_s1,
                                       cpu_0_data_master_qualified_request_SCL_s1,
                                       cpu_0_data_master_qualified_request_SDA_s1,
                                       cpu_0_data_master_qualified_request_SD_CLK_s1,
                                       cpu_0_data_master_qualified_request_SD_CS_s1,
                                       cpu_0_data_master_qualified_request_SD_DI_s1,
                                       cpu_0_data_master_qualified_request_SD_DO_s1,
                                       cpu_0_data_master_qualified_request_TEMP_DATA_s1,
                                       cpu_0_data_master_qualified_request_TUBE_EN_s1,
                                       cpu_0_data_master_qualified_request_UART_RX_DATA_s1,
                                       cpu_0_data_master_qualified_request_USB_INT_I_s1,
                                       cpu_0_data_master_qualified_request_USB_PC_I_s1,
                                       cpu_0_data_master_qualified_request_USB_RST_O_s1,
                                       cpu_0_data_master_qualified_request_USB_SCK_O_s1,
                                       cpu_0_data_master_qualified_request_USB_SCS_O_s1,
                                       cpu_0_data_master_qualified_request_USB_SDI_O_s1,
                                       cpu_0_data_master_qualified_request_USB_SDO_I_s1,
                                       cpu_0_data_master_qualified_request_cpu_0_jtag_debug_module,
                                       cpu_0_data_master_qualified_request_epcs_flash_controller_0_epcs_control_port,
                                       cpu_0_data_master_qualified_request_sdram_0_s1,
                                       cpu_0_data_master_qualified_request_sysid_0_control_slave,
                                       cpu_0_data_master_qualified_request_timer_0_s1,
                                       cpu_0_data_master_qualified_request_timer_1_s1,
                                       cpu_0_data_master_qualified_request_uart_0_s1,
                                       cpu_0_data_master_read,
                                       cpu_0_data_master_read_data_valid_ADC_DATA_s1,
                                       cpu_0_data_master_read_data_valid_BUZZER_DATA_s1,
                                       cpu_0_data_master_read_data_valid_DAC_DATA_s1,
                                       cpu_0_data_master_read_data_valid_ETH_CLKOUT_I_s1,
                                       cpu_0_data_master_read_data_valid_ETH_CS_O_s1,
                                       cpu_0_data_master_read_data_valid_ETH_INT_I_s1,
                                       cpu_0_data_master_read_data_valid_ETH_RESET_O_s1,
                                       cpu_0_data_master_read_data_valid_ETH_SCK_O_s1,
                                       cpu_0_data_master_read_data_valid_ETH_SI_O_s1,
                                       cpu_0_data_master_read_data_valid_ETH_SO_I_s1,
                                       cpu_0_data_master_read_data_valid_ETH_WOL_I_s1,
                                       cpu_0_data_master_read_data_valid_IR_DATA_s1,
                                       cpu_0_data_master_read_data_valid_KEY_FOCUS_s1,
                                       cpu_0_data_master_read_data_valid_LCD_CS_s1,
                                       cpu_0_data_master_read_data_valid_LCD_DATA_s1,
                                       cpu_0_data_master_read_data_valid_LCD_RD_s1,
                                       cpu_0_data_master_read_data_valid_LCD_RST_s1,
                                       cpu_0_data_master_read_data_valid_LCD_RS_s1,
                                       cpu_0_data_master_read_data_valid_LCD_WR_s1,
                                       cpu_0_data_master_read_data_valid_LED_DATA_s1,
                                       cpu_0_data_master_read_data_valid_PS2_DATA_REC_s1,
                                       cpu_0_data_master_read_data_valid_RTC_DATA_s1,
                                       cpu_0_data_master_read_data_valid_SCL_s1,
                                       cpu_0_data_master_read_data_valid_SDA_s1,
                                       cpu_0_data_master_read_data_valid_SD_CLK_s1,
                                       cpu_0_data_master_read_data_valid_SD_CS_s1,
                                       cpu_0_data_master_read_data_valid_SD_DI_s1,
                                       cpu_0_data_master_read_data_valid_SD_DO_s1,
                                       cpu_0_data_master_read_data_valid_TEMP_DATA_s1,
                                       cpu_0_data_master_read_data_valid_TUBE_EN_s1,
                                       cpu_0_data_master_read_data_valid_UART_RX_DATA_s1,
                                       cpu_0_data_master_read_data_valid_USB_INT_I_s1,
                                       cpu_0_data_master_read_data_valid_USB_PC_I_s1,
                                       cpu_0_data_master_read_data_valid_USB_RST_O_s1,
                                       cpu_0_data_master_read_data_valid_USB_SCK_O_s1,
                                       cpu_0_data_master_read_data_valid_USB_SCS_O_s1,
                                       cpu_0_data_master_read_data_valid_USB_SDI_O_s1,
                                       cpu_0_data_master_read_data_valid_USB_SDO_I_s1,
                                       cpu_0_data_master_read_data_valid_cpu_0_jtag_debug_module,
                                       cpu_0_data_master_read_data_valid_epcs_flash_controller_0_epcs_control_port,
                                       cpu_0_data_master_read_data_valid_sdram_0_s1,
                                       cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                       cpu_0_data_master_read_data_valid_sysid_0_control_slave,
                                       cpu_0_data_master_read_data_valid_timer_0_s1,
                                       cpu_0_data_master_read_data_valid_timer_1_s1,
                                       cpu_0_data_master_read_data_valid_uart_0_s1,
                                       cpu_0_data_master_requests_ADC_DATA_s1,
                                       cpu_0_data_master_requests_BUZZER_DATA_s1,
                                       cpu_0_data_master_requests_DAC_DATA_s1,
                                       cpu_0_data_master_requests_ETH_CLKOUT_I_s1,
                                       cpu_0_data_master_requests_ETH_CS_O_s1,
                                       cpu_0_data_master_requests_ETH_INT_I_s1,
                                       cpu_0_data_master_requests_ETH_RESET_O_s1,
                                       cpu_0_data_master_requests_ETH_SCK_O_s1,
                                       cpu_0_data_master_requests_ETH_SI_O_s1,
                                       cpu_0_data_master_requests_ETH_SO_I_s1,
                                       cpu_0_data_master_requests_ETH_WOL_I_s1,
                                       cpu_0_data_master_requests_IR_DATA_s1,
                                       cpu_0_data_master_requests_KEY_FOCUS_s1,
                                       cpu_0_data_master_requests_LCD_CS_s1,
                                       cpu_0_data_master_requests_LCD_DATA_s1,
                                       cpu_0_data_master_requests_LCD_RD_s1,
                                       cpu_0_data_master_requests_LCD_RST_s1,
                                       cpu_0_data_master_requests_LCD_RS_s1,
                                       cpu_0_data_master_requests_LCD_WR_s1,
                                       cpu_0_data_master_requests_LED_DATA_s1,
                                       cpu_0_data_master_requests_PS2_DATA_REC_s1,
                                       cpu_0_data_master_requests_RTC_DATA_s1,
                                       cpu_0_data_master_requests_SCL_s1,
                                       cpu_0_data_master_requests_SDA_s1,
                                       cpu_0_data_master_requests_SD_CLK_s1,
                                       cpu_0_data_master_requests_SD_CS_s1,
                                       cpu_0_data_master_requests_SD_DI_s1,
                                       cpu_0_data_master_requests_SD_DO_s1,
                                       cpu_0_data_master_requests_TEMP_DATA_s1,
                                       cpu_0_data_master_requests_TUBE_EN_s1,
                                       cpu_0_data_master_requests_UART_RX_DATA_s1,
                                       cpu_0_data_master_requests_USB_INT_I_s1,
                                       cpu_0_data_master_requests_USB_PC_I_s1,
                                       cpu_0_data_master_requests_USB_RST_O_s1,
                                       cpu_0_data_master_requests_USB_SCK_O_s1,
                                       cpu_0_data_master_requests_USB_SCS_O_s1,
                                       cpu_0_data_master_requests_USB_SDI_O_s1,
                                       cpu_0_data_master_requests_USB_SDO_I_s1,
                                       cpu_0_data_master_requests_cpu_0_jtag_debug_module,
                                       cpu_0_data_master_requests_epcs_flash_controller_0_epcs_control_port,
                                       cpu_0_data_master_requests_sdram_0_s1,
                                       cpu_0_data_master_requests_sysid_0_control_slave,
                                       cpu_0_data_master_requests_timer_0_s1,
                                       cpu_0_data_master_requests_timer_1_s1,
                                       cpu_0_data_master_requests_uart_0_s1,
                                       cpu_0_data_master_write,
                                       cpu_0_data_master_writedata,
                                       cpu_0_jtag_debug_module_readdata_from_sa,
                                       d1_ADC_DATA_s1_end_xfer,
                                       d1_BUZZER_DATA_s1_end_xfer,
                                       d1_DAC_DATA_s1_end_xfer,
                                       d1_ETH_CLKOUT_I_s1_end_xfer,
                                       d1_ETH_CS_O_s1_end_xfer,
                                       d1_ETH_INT_I_s1_end_xfer,
                                       d1_ETH_RESET_O_s1_end_xfer,
                                       d1_ETH_SCK_O_s1_end_xfer,
                                       d1_ETH_SI_O_s1_end_xfer,
                                       d1_ETH_SO_I_s1_end_xfer,
                                       d1_ETH_WOL_I_s1_end_xfer,
                                       d1_IR_DATA_s1_end_xfer,
                                       d1_KEY_FOCUS_s1_end_xfer,
                                       d1_LCD_CS_s1_end_xfer,
                                       d1_LCD_DATA_s1_end_xfer,
                                       d1_LCD_RD_s1_end_xfer,
                                       d1_LCD_RST_s1_end_xfer,
                                       d1_LCD_RS_s1_end_xfer,
                                       d1_LCD_WR_s1_end_xfer,
                                       d1_LED_DATA_s1_end_xfer,
                                       d1_PS2_DATA_REC_s1_end_xfer,
                                       d1_RTC_DATA_s1_end_xfer,
                                       d1_SCL_s1_end_xfer,
                                       d1_SDA_s1_end_xfer,
                                       d1_SD_CLK_s1_end_xfer,
                                       d1_SD_CS_s1_end_xfer,
                                       d1_SD_DI_s1_end_xfer,
                                       d1_SD_DO_s1_end_xfer,
                                       d1_TEMP_DATA_s1_end_xfer,
                                       d1_TUBE_EN_s1_end_xfer,
                                       d1_UART_RX_DATA_s1_end_xfer,
                                       d1_USB_INT_I_s1_end_xfer,
                                       d1_USB_PC_I_s1_end_xfer,
                                       d1_USB_RST_O_s1_end_xfer,
                                       d1_USB_SCK_O_s1_end_xfer,
                                       d1_USB_SCS_O_s1_end_xfer,
                                       d1_USB_SDI_O_s1_end_xfer,
                                       d1_USB_SDO_I_s1_end_xfer,
                                       d1_cpu_0_jtag_debug_module_end_xfer,
                                       d1_epcs_flash_controller_0_epcs_control_port_end_xfer,
                                       d1_sdram_0_s1_end_xfer,
                                       d1_sysid_0_control_slave_end_xfer,
                                       d1_timer_0_s1_end_xfer,
                                       d1_timer_1_s1_end_xfer,
                                       d1_uart_0_s1_end_xfer,
                                       epcs_flash_controller_0_epcs_control_port_irq_from_sa,
                                       epcs_flash_controller_0_epcs_control_port_readdata_from_sa,
                                       reset_n,
                                       sdram_0_s1_readdata_from_sa,
                                       sdram_0_s1_waitrequest_from_sa,
                                       sysid_0_control_slave_readdata_from_sa,
                                       timer_0_s1_irq_from_sa,
                                       timer_0_s1_readdata_from_sa,
                                       timer_1_s1_irq_from_sa,
                                       timer_1_s1_readdata_from_sa,
                                       uart_0_s1_irq_from_sa,
                                       uart_0_s1_readdata_from_sa,

                                      // outputs:
                                       cpu_0_data_master_address_to_slave,
                                       cpu_0_data_master_dbs_address,
                                       cpu_0_data_master_dbs_write_16,
                                       cpu_0_data_master_irq,
                                       cpu_0_data_master_latency_counter,
                                       cpu_0_data_master_readdata,
                                       cpu_0_data_master_readdatavalid,
                                       cpu_0_data_master_waitrequest
                                    )
;

  output  [ 26: 0] cpu_0_data_master_address_to_slave;
  output  [  1: 0] cpu_0_data_master_dbs_address;
  output  [ 15: 0] cpu_0_data_master_dbs_write_16;
  output  [ 31: 0] cpu_0_data_master_irq;
  output           cpu_0_data_master_latency_counter;
  output  [ 31: 0] cpu_0_data_master_readdata;
  output           cpu_0_data_master_readdatavalid;
  output           cpu_0_data_master_waitrequest;
  input   [ 31: 0] ADC_DATA_s1_readdata_from_sa;
  input   [ 31: 0] BUZZER_DATA_s1_readdata_from_sa;
  input   [ 31: 0] DAC_DATA_s1_readdata_from_sa;
  input   [ 31: 0] ETH_CLKOUT_I_s1_readdata_from_sa;
  input   [ 31: 0] ETH_CS_O_s1_readdata_from_sa;
  input   [ 31: 0] ETH_INT_I_s1_readdata_from_sa;
  input   [ 31: 0] ETH_RESET_O_s1_readdata_from_sa;
  input   [ 31: 0] ETH_SCK_O_s1_readdata_from_sa;
  input   [ 31: 0] ETH_SI_O_s1_readdata_from_sa;
  input   [ 31: 0] ETH_SO_I_s1_readdata_from_sa;
  input   [ 31: 0] ETH_WOL_I_s1_readdata_from_sa;
  input   [ 31: 0] IR_DATA_s1_readdata_from_sa;
  input   [ 31: 0] KEY_FOCUS_s1_readdata_from_sa;
  input   [ 31: 0] LCD_CS_s1_readdata_from_sa;
  input   [ 31: 0] LCD_DATA_s1_readdata_from_sa;
  input   [ 31: 0] LCD_RD_s1_readdata_from_sa;
  input   [ 31: 0] LCD_RST_s1_readdata_from_sa;
  input   [ 31: 0] LCD_RS_s1_readdata_from_sa;
  input   [ 31: 0] LCD_WR_s1_readdata_from_sa;
  input   [ 31: 0] LED_DATA_s1_readdata_from_sa;
  input   [ 31: 0] PS2_DATA_REC_s1_readdata_from_sa;
  input   [ 31: 0] RTC_DATA_s1_readdata_from_sa;
  input   [ 31: 0] SCL_s1_readdata_from_sa;
  input   [ 31: 0] SDA_s1_readdata_from_sa;
  input   [ 31: 0] SD_CLK_s1_readdata_from_sa;
  input   [ 31: 0] SD_CS_s1_readdata_from_sa;
  input   [ 31: 0] SD_DI_s1_readdata_from_sa;
  input   [ 31: 0] SD_DO_s1_readdata_from_sa;
  input   [ 31: 0] TEMP_DATA_s1_readdata_from_sa;
  input   [ 31: 0] TUBE_EN_s1_readdata_from_sa;
  input   [ 31: 0] UART_RX_DATA_s1_readdata_from_sa;
  input   [ 31: 0] USB_INT_I_s1_readdata_from_sa;
  input   [ 31: 0] USB_PC_I_s1_readdata_from_sa;
  input   [ 31: 0] USB_RST_O_s1_readdata_from_sa;
  input   [ 31: 0] USB_SCK_O_s1_readdata_from_sa;
  input   [ 31: 0] USB_SCS_O_s1_readdata_from_sa;
  input   [ 31: 0] USB_SDI_O_s1_readdata_from_sa;
  input   [ 31: 0] USB_SDO_I_s1_readdata_from_sa;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address;
  input   [  3: 0] cpu_0_data_master_byteenable;
  input   [  1: 0] cpu_0_data_master_byteenable_sdram_0_s1;
  input            cpu_0_data_master_granted_ADC_DATA_s1;
  input            cpu_0_data_master_granted_BUZZER_DATA_s1;
  input            cpu_0_data_master_granted_DAC_DATA_s1;
  input            cpu_0_data_master_granted_ETH_CLKOUT_I_s1;
  input            cpu_0_data_master_granted_ETH_CS_O_s1;
  input            cpu_0_data_master_granted_ETH_INT_I_s1;
  input            cpu_0_data_master_granted_ETH_RESET_O_s1;
  input            cpu_0_data_master_granted_ETH_SCK_O_s1;
  input            cpu_0_data_master_granted_ETH_SI_O_s1;
  input            cpu_0_data_master_granted_ETH_SO_I_s1;
  input            cpu_0_data_master_granted_ETH_WOL_I_s1;
  input            cpu_0_data_master_granted_IR_DATA_s1;
  input            cpu_0_data_master_granted_KEY_FOCUS_s1;
  input            cpu_0_data_master_granted_LCD_CS_s1;
  input            cpu_0_data_master_granted_LCD_DATA_s1;
  input            cpu_0_data_master_granted_LCD_RD_s1;
  input            cpu_0_data_master_granted_LCD_RST_s1;
  input            cpu_0_data_master_granted_LCD_RS_s1;
  input            cpu_0_data_master_granted_LCD_WR_s1;
  input            cpu_0_data_master_granted_LED_DATA_s1;
  input            cpu_0_data_master_granted_PS2_DATA_REC_s1;
  input            cpu_0_data_master_granted_RTC_DATA_s1;
  input            cpu_0_data_master_granted_SCL_s1;
  input            cpu_0_data_master_granted_SDA_s1;
  input            cpu_0_data_master_granted_SD_CLK_s1;
  input            cpu_0_data_master_granted_SD_CS_s1;
  input            cpu_0_data_master_granted_SD_DI_s1;
  input            cpu_0_data_master_granted_SD_DO_s1;
  input            cpu_0_data_master_granted_TEMP_DATA_s1;
  input            cpu_0_data_master_granted_TUBE_EN_s1;
  input            cpu_0_data_master_granted_UART_RX_DATA_s1;
  input            cpu_0_data_master_granted_USB_INT_I_s1;
  input            cpu_0_data_master_granted_USB_PC_I_s1;
  input            cpu_0_data_master_granted_USB_RST_O_s1;
  input            cpu_0_data_master_granted_USB_SCK_O_s1;
  input            cpu_0_data_master_granted_USB_SCS_O_s1;
  input            cpu_0_data_master_granted_USB_SDI_O_s1;
  input            cpu_0_data_master_granted_USB_SDO_I_s1;
  input            cpu_0_data_master_granted_cpu_0_jtag_debug_module;
  input            cpu_0_data_master_granted_epcs_flash_controller_0_epcs_control_port;
  input            cpu_0_data_master_granted_sdram_0_s1;
  input            cpu_0_data_master_granted_sysid_0_control_slave;
  input            cpu_0_data_master_granted_timer_0_s1;
  input            cpu_0_data_master_granted_timer_1_s1;
  input            cpu_0_data_master_granted_uart_0_s1;
  input            cpu_0_data_master_qualified_request_ADC_DATA_s1;
  input            cpu_0_data_master_qualified_request_BUZZER_DATA_s1;
  input            cpu_0_data_master_qualified_request_DAC_DATA_s1;
  input            cpu_0_data_master_qualified_request_ETH_CLKOUT_I_s1;
  input            cpu_0_data_master_qualified_request_ETH_CS_O_s1;
  input            cpu_0_data_master_qualified_request_ETH_INT_I_s1;
  input            cpu_0_data_master_qualified_request_ETH_RESET_O_s1;
  input            cpu_0_data_master_qualified_request_ETH_SCK_O_s1;
  input            cpu_0_data_master_qualified_request_ETH_SI_O_s1;
  input            cpu_0_data_master_qualified_request_ETH_SO_I_s1;
  input            cpu_0_data_master_qualified_request_ETH_WOL_I_s1;
  input            cpu_0_data_master_qualified_request_IR_DATA_s1;
  input            cpu_0_data_master_qualified_request_KEY_FOCUS_s1;
  input            cpu_0_data_master_qualified_request_LCD_CS_s1;
  input            cpu_0_data_master_qualified_request_LCD_DATA_s1;
  input            cpu_0_data_master_qualified_request_LCD_RD_s1;
  input            cpu_0_data_master_qualified_request_LCD_RST_s1;
  input            cpu_0_data_master_qualified_request_LCD_RS_s1;
  input            cpu_0_data_master_qualified_request_LCD_WR_s1;
  input            cpu_0_data_master_qualified_request_LED_DATA_s1;
  input            cpu_0_data_master_qualified_request_PS2_DATA_REC_s1;
  input            cpu_0_data_master_qualified_request_RTC_DATA_s1;
  input            cpu_0_data_master_qualified_request_SCL_s1;
  input            cpu_0_data_master_qualified_request_SDA_s1;
  input            cpu_0_data_master_qualified_request_SD_CLK_s1;
  input            cpu_0_data_master_qualified_request_SD_CS_s1;
  input            cpu_0_data_master_qualified_request_SD_DI_s1;
  input            cpu_0_data_master_qualified_request_SD_DO_s1;
  input            cpu_0_data_master_qualified_request_TEMP_DATA_s1;
  input            cpu_0_data_master_qualified_request_TUBE_EN_s1;
  input            cpu_0_data_master_qualified_request_UART_RX_DATA_s1;
  input            cpu_0_data_master_qualified_request_USB_INT_I_s1;
  input            cpu_0_data_master_qualified_request_USB_PC_I_s1;
  input            cpu_0_data_master_qualified_request_USB_RST_O_s1;
  input            cpu_0_data_master_qualified_request_USB_SCK_O_s1;
  input            cpu_0_data_master_qualified_request_USB_SCS_O_s1;
  input            cpu_0_data_master_qualified_request_USB_SDI_O_s1;
  input            cpu_0_data_master_qualified_request_USB_SDO_I_s1;
  input            cpu_0_data_master_qualified_request_cpu_0_jtag_debug_module;
  input            cpu_0_data_master_qualified_request_epcs_flash_controller_0_epcs_control_port;
  input            cpu_0_data_master_qualified_request_sdram_0_s1;
  input            cpu_0_data_master_qualified_request_sysid_0_control_slave;
  input            cpu_0_data_master_qualified_request_timer_0_s1;
  input            cpu_0_data_master_qualified_request_timer_1_s1;
  input            cpu_0_data_master_qualified_request_uart_0_s1;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_ADC_DATA_s1;
  input            cpu_0_data_master_read_data_valid_BUZZER_DATA_s1;
  input            cpu_0_data_master_read_data_valid_DAC_DATA_s1;
  input            cpu_0_data_master_read_data_valid_ETH_CLKOUT_I_s1;
  input            cpu_0_data_master_read_data_valid_ETH_CS_O_s1;
  input            cpu_0_data_master_read_data_valid_ETH_INT_I_s1;
  input            cpu_0_data_master_read_data_valid_ETH_RESET_O_s1;
  input            cpu_0_data_master_read_data_valid_ETH_SCK_O_s1;
  input            cpu_0_data_master_read_data_valid_ETH_SI_O_s1;
  input            cpu_0_data_master_read_data_valid_ETH_SO_I_s1;
  input            cpu_0_data_master_read_data_valid_ETH_WOL_I_s1;
  input            cpu_0_data_master_read_data_valid_IR_DATA_s1;
  input            cpu_0_data_master_read_data_valid_KEY_FOCUS_s1;
  input            cpu_0_data_master_read_data_valid_LCD_CS_s1;
  input            cpu_0_data_master_read_data_valid_LCD_DATA_s1;
  input            cpu_0_data_master_read_data_valid_LCD_RD_s1;
  input            cpu_0_data_master_read_data_valid_LCD_RST_s1;
  input            cpu_0_data_master_read_data_valid_LCD_RS_s1;
  input            cpu_0_data_master_read_data_valid_LCD_WR_s1;
  input            cpu_0_data_master_read_data_valid_LED_DATA_s1;
  input            cpu_0_data_master_read_data_valid_PS2_DATA_REC_s1;
  input            cpu_0_data_master_read_data_valid_RTC_DATA_s1;
  input            cpu_0_data_master_read_data_valid_SCL_s1;
  input            cpu_0_data_master_read_data_valid_SDA_s1;
  input            cpu_0_data_master_read_data_valid_SD_CLK_s1;
  input            cpu_0_data_master_read_data_valid_SD_CS_s1;
  input            cpu_0_data_master_read_data_valid_SD_DI_s1;
  input            cpu_0_data_master_read_data_valid_SD_DO_s1;
  input            cpu_0_data_master_read_data_valid_TEMP_DATA_s1;
  input            cpu_0_data_master_read_data_valid_TUBE_EN_s1;
  input            cpu_0_data_master_read_data_valid_UART_RX_DATA_s1;
  input            cpu_0_data_master_read_data_valid_USB_INT_I_s1;
  input            cpu_0_data_master_read_data_valid_USB_PC_I_s1;
  input            cpu_0_data_master_read_data_valid_USB_RST_O_s1;
  input            cpu_0_data_master_read_data_valid_USB_SCK_O_s1;
  input            cpu_0_data_master_read_data_valid_USB_SCS_O_s1;
  input            cpu_0_data_master_read_data_valid_USB_SDI_O_s1;
  input            cpu_0_data_master_read_data_valid_USB_SDO_I_s1;
  input            cpu_0_data_master_read_data_valid_cpu_0_jtag_debug_module;
  input            cpu_0_data_master_read_data_valid_epcs_flash_controller_0_epcs_control_port;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_read_data_valid_sysid_0_control_slave;
  input            cpu_0_data_master_read_data_valid_timer_0_s1;
  input            cpu_0_data_master_read_data_valid_timer_1_s1;
  input            cpu_0_data_master_read_data_valid_uart_0_s1;
  input            cpu_0_data_master_requests_ADC_DATA_s1;
  input            cpu_0_data_master_requests_BUZZER_DATA_s1;
  input            cpu_0_data_master_requests_DAC_DATA_s1;
  input            cpu_0_data_master_requests_ETH_CLKOUT_I_s1;
  input            cpu_0_data_master_requests_ETH_CS_O_s1;
  input            cpu_0_data_master_requests_ETH_INT_I_s1;
  input            cpu_0_data_master_requests_ETH_RESET_O_s1;
  input            cpu_0_data_master_requests_ETH_SCK_O_s1;
  input            cpu_0_data_master_requests_ETH_SI_O_s1;
  input            cpu_0_data_master_requests_ETH_SO_I_s1;
  input            cpu_0_data_master_requests_ETH_WOL_I_s1;
  input            cpu_0_data_master_requests_IR_DATA_s1;
  input            cpu_0_data_master_requests_KEY_FOCUS_s1;
  input            cpu_0_data_master_requests_LCD_CS_s1;
  input            cpu_0_data_master_requests_LCD_DATA_s1;
  input            cpu_0_data_master_requests_LCD_RD_s1;
  input            cpu_0_data_master_requests_LCD_RST_s1;
  input            cpu_0_data_master_requests_LCD_RS_s1;
  input            cpu_0_data_master_requests_LCD_WR_s1;
  input            cpu_0_data_master_requests_LED_DATA_s1;
  input            cpu_0_data_master_requests_PS2_DATA_REC_s1;
  input            cpu_0_data_master_requests_RTC_DATA_s1;
  input            cpu_0_data_master_requests_SCL_s1;
  input            cpu_0_data_master_requests_SDA_s1;
  input            cpu_0_data_master_requests_SD_CLK_s1;
  input            cpu_0_data_master_requests_SD_CS_s1;
  input            cpu_0_data_master_requests_SD_DI_s1;
  input            cpu_0_data_master_requests_SD_DO_s1;
  input            cpu_0_data_master_requests_TEMP_DATA_s1;
  input            cpu_0_data_master_requests_TUBE_EN_s1;
  input            cpu_0_data_master_requests_UART_RX_DATA_s1;
  input            cpu_0_data_master_requests_USB_INT_I_s1;
  input            cpu_0_data_master_requests_USB_PC_I_s1;
  input            cpu_0_data_master_requests_USB_RST_O_s1;
  input            cpu_0_data_master_requests_USB_SCK_O_s1;
  input            cpu_0_data_master_requests_USB_SCS_O_s1;
  input            cpu_0_data_master_requests_USB_SDI_O_s1;
  input            cpu_0_data_master_requests_USB_SDO_I_s1;
  input            cpu_0_data_master_requests_cpu_0_jtag_debug_module;
  input            cpu_0_data_master_requests_epcs_flash_controller_0_epcs_control_port;
  input            cpu_0_data_master_requests_sdram_0_s1;
  input            cpu_0_data_master_requests_sysid_0_control_slave;
  input            cpu_0_data_master_requests_timer_0_s1;
  input            cpu_0_data_master_requests_timer_1_s1;
  input            cpu_0_data_master_requests_uart_0_s1;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input   [ 31: 0] cpu_0_jtag_debug_module_readdata_from_sa;
  input            d1_ADC_DATA_s1_end_xfer;
  input            d1_BUZZER_DATA_s1_end_xfer;
  input            d1_DAC_DATA_s1_end_xfer;
  input            d1_ETH_CLKOUT_I_s1_end_xfer;
  input            d1_ETH_CS_O_s1_end_xfer;
  input            d1_ETH_INT_I_s1_end_xfer;
  input            d1_ETH_RESET_O_s1_end_xfer;
  input            d1_ETH_SCK_O_s1_end_xfer;
  input            d1_ETH_SI_O_s1_end_xfer;
  input            d1_ETH_SO_I_s1_end_xfer;
  input            d1_ETH_WOL_I_s1_end_xfer;
  input            d1_IR_DATA_s1_end_xfer;
  input            d1_KEY_FOCUS_s1_end_xfer;
  input            d1_LCD_CS_s1_end_xfer;
  input            d1_LCD_DATA_s1_end_xfer;
  input            d1_LCD_RD_s1_end_xfer;
  input            d1_LCD_RST_s1_end_xfer;
  input            d1_LCD_RS_s1_end_xfer;
  input            d1_LCD_WR_s1_end_xfer;
  input            d1_LED_DATA_s1_end_xfer;
  input            d1_PS2_DATA_REC_s1_end_xfer;
  input            d1_RTC_DATA_s1_end_xfer;
  input            d1_SCL_s1_end_xfer;
  input            d1_SDA_s1_end_xfer;
  input            d1_SD_CLK_s1_end_xfer;
  input            d1_SD_CS_s1_end_xfer;
  input            d1_SD_DI_s1_end_xfer;
  input            d1_SD_DO_s1_end_xfer;
  input            d1_TEMP_DATA_s1_end_xfer;
  input            d1_TUBE_EN_s1_end_xfer;
  input            d1_UART_RX_DATA_s1_end_xfer;
  input            d1_USB_INT_I_s1_end_xfer;
  input            d1_USB_PC_I_s1_end_xfer;
  input            d1_USB_RST_O_s1_end_xfer;
  input            d1_USB_SCK_O_s1_end_xfer;
  input            d1_USB_SCS_O_s1_end_xfer;
  input            d1_USB_SDI_O_s1_end_xfer;
  input            d1_USB_SDO_I_s1_end_xfer;
  input            d1_cpu_0_jtag_debug_module_end_xfer;
  input            d1_epcs_flash_controller_0_epcs_control_port_end_xfer;
  input            d1_sdram_0_s1_end_xfer;
  input            d1_sysid_0_control_slave_end_xfer;
  input            d1_timer_0_s1_end_xfer;
  input            d1_timer_1_s1_end_xfer;
  input            d1_uart_0_s1_end_xfer;
  input            epcs_flash_controller_0_epcs_control_port_irq_from_sa;
  input   [ 31: 0] epcs_flash_controller_0_epcs_control_port_readdata_from_sa;
  input            reset_n;
  input   [ 15: 0] sdram_0_s1_readdata_from_sa;
  input            sdram_0_s1_waitrequest_from_sa;
  input   [ 31: 0] sysid_0_control_slave_readdata_from_sa;
  input            timer_0_s1_irq_from_sa;
  input   [ 15: 0] timer_0_s1_readdata_from_sa;
  input            timer_1_s1_irq_from_sa;
  input   [ 15: 0] timer_1_s1_readdata_from_sa;
  input            uart_0_s1_irq_from_sa;
  input   [ 15: 0] uart_0_s1_readdata_from_sa;

  reg              active_and_waiting_last_time;
  reg     [ 26: 0] cpu_0_data_master_address_last_time;
  wire    [ 26: 0] cpu_0_data_master_address_to_slave;
  reg     [  3: 0] cpu_0_data_master_byteenable_last_time;
  reg     [  1: 0] cpu_0_data_master_dbs_address;
  wire    [  1: 0] cpu_0_data_master_dbs_increment;
  reg     [  1: 0] cpu_0_data_master_dbs_rdv_counter;
  wire    [  1: 0] cpu_0_data_master_dbs_rdv_counter_inc;
  wire    [ 15: 0] cpu_0_data_master_dbs_write_16;
  wire    [ 31: 0] cpu_0_data_master_irq;
  wire             cpu_0_data_master_is_granted_some_slave;
  reg              cpu_0_data_master_latency_counter;
  wire    [  1: 0] cpu_0_data_master_next_dbs_rdv_counter;
  reg              cpu_0_data_master_read_but_no_slave_selected;
  reg              cpu_0_data_master_read_last_time;
  wire    [ 31: 0] cpu_0_data_master_readdata;
  wire             cpu_0_data_master_readdatavalid;
  wire             cpu_0_data_master_run;
  wire             cpu_0_data_master_waitrequest;
  reg              cpu_0_data_master_write_last_time;
  reg     [ 31: 0] cpu_0_data_master_writedata_last_time;
  wire             dbs_count_enable;
  wire             dbs_counter_overflow;
  reg     [ 15: 0] dbs_latent_16_reg_segment_0;
  wire             dbs_rdv_count_enable;
  wire             dbs_rdv_counter_overflow;
  wire             latency_load_value;
  wire    [  1: 0] next_dbs_address;
  wire             p1_cpu_0_data_master_latency_counter;
  wire    [ 15: 0] p1_dbs_latent_16_reg_segment_0;
  wire             pre_dbs_count_enable;
  wire             pre_flush_cpu_0_data_master_readdatavalid;
  wire             r_0;
  wire             r_1;
  wire             r_2;
  wire             r_3;
  wire             r_4;
  wire             r_5;
  wire             r_6;
  wire             r_7;
  wire             r_8;
  wire             r_9;
  //r_0 master_run cascaded wait assignment, which is an e_assign
  assign r_0 = 1 & (cpu_0_data_master_qualified_request_ADC_DATA_s1 | ~cpu_0_data_master_requests_ADC_DATA_s1) & ((~cpu_0_data_master_qualified_request_ADC_DATA_s1 | ~cpu_0_data_master_read | (1 & ~d1_ADC_DATA_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_ADC_DATA_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_BUZZER_DATA_s1 | ~cpu_0_data_master_requests_BUZZER_DATA_s1) & ((~cpu_0_data_master_qualified_request_BUZZER_DATA_s1 | ~cpu_0_data_master_read | (1 & ~d1_BUZZER_DATA_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_BUZZER_DATA_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_DAC_DATA_s1 | ~cpu_0_data_master_requests_DAC_DATA_s1) & ((~cpu_0_data_master_qualified_request_DAC_DATA_s1 | ~cpu_0_data_master_read | (1 & ~d1_DAC_DATA_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_DAC_DATA_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_ETH_CLKOUT_I_s1 | ~cpu_0_data_master_requests_ETH_CLKOUT_I_s1) & ((~cpu_0_data_master_qualified_request_ETH_CLKOUT_I_s1 | ~cpu_0_data_master_read | (1 & ~d1_ETH_CLKOUT_I_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_ETH_CLKOUT_I_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_ETH_CS_O_s1 | ~cpu_0_data_master_requests_ETH_CS_O_s1) & ((~cpu_0_data_master_qualified_request_ETH_CS_O_s1 | ~cpu_0_data_master_read | (1 & ~d1_ETH_CS_O_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_ETH_CS_O_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write)));

  //cascaded wait assignment, which is an e_assign
  assign cpu_0_data_master_run = r_0 & r_1 & r_2 & r_3 & r_4 & r_5 & r_6 & r_7 & r_8 & r_9;

  //r_1 master_run cascaded wait assignment, which is an e_assign
  assign r_1 = 1 & (cpu_0_data_master_qualified_request_ETH_INT_I_s1 | ~cpu_0_data_master_requests_ETH_INT_I_s1) & ((~cpu_0_data_master_qualified_request_ETH_INT_I_s1 | ~cpu_0_data_master_read | (1 & ~d1_ETH_INT_I_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_ETH_INT_I_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_ETH_RESET_O_s1 | ~cpu_0_data_master_requests_ETH_RESET_O_s1) & ((~cpu_0_data_master_qualified_request_ETH_RESET_O_s1 | ~cpu_0_data_master_read | (1 & ~d1_ETH_RESET_O_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_ETH_RESET_O_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_ETH_SCK_O_s1 | ~cpu_0_data_master_requests_ETH_SCK_O_s1) & ((~cpu_0_data_master_qualified_request_ETH_SCK_O_s1 | ~cpu_0_data_master_read | (1 & ~d1_ETH_SCK_O_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_ETH_SCK_O_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_ETH_SI_O_s1 | ~cpu_0_data_master_requests_ETH_SI_O_s1) & ((~cpu_0_data_master_qualified_request_ETH_SI_O_s1 | ~cpu_0_data_master_read | (1 & ~d1_ETH_SI_O_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_ETH_SI_O_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_ETH_SO_I_s1 | ~cpu_0_data_master_requests_ETH_SO_I_s1) & ((~cpu_0_data_master_qualified_request_ETH_SO_I_s1 | ~cpu_0_data_master_read | (1 & ~d1_ETH_SO_I_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_ETH_SO_I_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write)));

  //r_2 master_run cascaded wait assignment, which is an e_assign
  assign r_2 = 1 & (cpu_0_data_master_qualified_request_ETH_WOL_I_s1 | ~cpu_0_data_master_requests_ETH_WOL_I_s1) & ((~cpu_0_data_master_qualified_request_ETH_WOL_I_s1 | ~cpu_0_data_master_read | (1 & ~d1_ETH_WOL_I_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_ETH_WOL_I_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_IR_DATA_s1 | ~cpu_0_data_master_requests_IR_DATA_s1) & ((~cpu_0_data_master_qualified_request_IR_DATA_s1 | ~cpu_0_data_master_read | (1 & ~d1_IR_DATA_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_IR_DATA_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_KEY_FOCUS_s1 | ~cpu_0_data_master_requests_KEY_FOCUS_s1) & ((~cpu_0_data_master_qualified_request_KEY_FOCUS_s1 | ~cpu_0_data_master_read | (1 & ~d1_KEY_FOCUS_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_KEY_FOCUS_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_LCD_CS_s1 | ~cpu_0_data_master_requests_LCD_CS_s1) & ((~cpu_0_data_master_qualified_request_LCD_CS_s1 | ~cpu_0_data_master_read | (1 & ~d1_LCD_CS_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_LCD_CS_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_LCD_DATA_s1 | ~cpu_0_data_master_requests_LCD_DATA_s1) & ((~cpu_0_data_master_qualified_request_LCD_DATA_s1 | ~cpu_0_data_master_read | (1 & ~d1_LCD_DATA_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_LCD_DATA_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write)));

  //r_3 master_run cascaded wait assignment, which is an e_assign
  assign r_3 = 1 & (cpu_0_data_master_qualified_request_LCD_RD_s1 | ~cpu_0_data_master_requests_LCD_RD_s1) & ((~cpu_0_data_master_qualified_request_LCD_RD_s1 | ~cpu_0_data_master_read | (1 & ~d1_LCD_RD_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_LCD_RD_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_LCD_RS_s1 | ~cpu_0_data_master_requests_LCD_RS_s1) & ((~cpu_0_data_master_qualified_request_LCD_RS_s1 | ~cpu_0_data_master_read | (1 & ~d1_LCD_RS_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_LCD_RS_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_LCD_RST_s1 | ~cpu_0_data_master_requests_LCD_RST_s1) & ((~cpu_0_data_master_qualified_request_LCD_RST_s1 | ~cpu_0_data_master_read | (1 & ~d1_LCD_RST_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_LCD_RST_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_LCD_WR_s1 | ~cpu_0_data_master_requests_LCD_WR_s1) & ((~cpu_0_data_master_qualified_request_LCD_WR_s1 | ~cpu_0_data_master_read | (1 & ~d1_LCD_WR_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_LCD_WR_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_LED_DATA_s1 | ~cpu_0_data_master_requests_LED_DATA_s1) & ((~cpu_0_data_master_qualified_request_LED_DATA_s1 | ~cpu_0_data_master_read | (1 & ~d1_LED_DATA_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_LED_DATA_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write)));

  //r_4 master_run cascaded wait assignment, which is an e_assign
  assign r_4 = 1 & (cpu_0_data_master_qualified_request_PS2_DATA_REC_s1 | ~cpu_0_data_master_requests_PS2_DATA_REC_s1) & ((~cpu_0_data_master_qualified_request_PS2_DATA_REC_s1 | ~cpu_0_data_master_read | (1 & ~d1_PS2_DATA_REC_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_PS2_DATA_REC_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_RTC_DATA_s1 | ~cpu_0_data_master_requests_RTC_DATA_s1) & ((~cpu_0_data_master_qualified_request_RTC_DATA_s1 | ~cpu_0_data_master_read | (1 & ~d1_RTC_DATA_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_RTC_DATA_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_SCL_s1 | ~cpu_0_data_master_requests_SCL_s1) & ((~cpu_0_data_master_qualified_request_SCL_s1 | ~cpu_0_data_master_read | (1 & ~d1_SCL_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_SCL_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_SDA_s1 | ~cpu_0_data_master_requests_SDA_s1) & ((~cpu_0_data_master_qualified_request_SDA_s1 | ~cpu_0_data_master_read | (1 & ~d1_SDA_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_SDA_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_SD_CLK_s1 | ~cpu_0_data_master_requests_SD_CLK_s1) & ((~cpu_0_data_master_qualified_request_SD_CLK_s1 | ~cpu_0_data_master_read | (1 & ~d1_SD_CLK_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_SD_CLK_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write)));

  //r_5 master_run cascaded wait assignment, which is an e_assign
  assign r_5 = 1 & (cpu_0_data_master_qualified_request_SD_CS_s1 | ~cpu_0_data_master_requests_SD_CS_s1) & ((~cpu_0_data_master_qualified_request_SD_CS_s1 | ~cpu_0_data_master_read | (1 & ~d1_SD_CS_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_SD_CS_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_SD_DI_s1 | ~cpu_0_data_master_requests_SD_DI_s1) & ((~cpu_0_data_master_qualified_request_SD_DI_s1 | ~cpu_0_data_master_read | (1 & ~d1_SD_DI_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_SD_DI_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_SD_DO_s1 | ~cpu_0_data_master_requests_SD_DO_s1) & ((~cpu_0_data_master_qualified_request_SD_DO_s1 | ~cpu_0_data_master_read | (1 & ~d1_SD_DO_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_SD_DO_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_TEMP_DATA_s1 | ~cpu_0_data_master_requests_TEMP_DATA_s1) & ((~cpu_0_data_master_qualified_request_TEMP_DATA_s1 | ~cpu_0_data_master_read | (1 & ~d1_TEMP_DATA_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_TEMP_DATA_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_TUBE_EN_s1 | ~cpu_0_data_master_requests_TUBE_EN_s1) & ((~cpu_0_data_master_qualified_request_TUBE_EN_s1 | ~cpu_0_data_master_read | (1 & ~d1_TUBE_EN_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_TUBE_EN_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write)));

  //r_6 master_run cascaded wait assignment, which is an e_assign
  assign r_6 = 1 & (cpu_0_data_master_qualified_request_UART_RX_DATA_s1 | ~cpu_0_data_master_requests_UART_RX_DATA_s1) & ((~cpu_0_data_master_qualified_request_UART_RX_DATA_s1 | ~cpu_0_data_master_read | (1 & ~d1_UART_RX_DATA_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_UART_RX_DATA_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_USB_INT_I_s1 | ~cpu_0_data_master_requests_USB_INT_I_s1) & ((~cpu_0_data_master_qualified_request_USB_INT_I_s1 | ~cpu_0_data_master_read | (1 & ~d1_USB_INT_I_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_USB_INT_I_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_USB_PC_I_s1 | ~cpu_0_data_master_requests_USB_PC_I_s1) & ((~cpu_0_data_master_qualified_request_USB_PC_I_s1 | ~cpu_0_data_master_read | (1 & ~d1_USB_PC_I_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_USB_PC_I_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_USB_RST_O_s1 | ~cpu_0_data_master_requests_USB_RST_O_s1) & ((~cpu_0_data_master_qualified_request_USB_RST_O_s1 | ~cpu_0_data_master_read | (1 & ~d1_USB_RST_O_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_USB_RST_O_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_USB_SCK_O_s1 | ~cpu_0_data_master_requests_USB_SCK_O_s1) & ((~cpu_0_data_master_qualified_request_USB_SCK_O_s1 | ~cpu_0_data_master_read | (1 & ~d1_USB_SCK_O_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_USB_SCK_O_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write)));

  //r_7 master_run cascaded wait assignment, which is an e_assign
  assign r_7 = 1 & (cpu_0_data_master_qualified_request_USB_SCS_O_s1 | ~cpu_0_data_master_requests_USB_SCS_O_s1) & ((~cpu_0_data_master_qualified_request_USB_SCS_O_s1 | ~cpu_0_data_master_read | (1 & ~d1_USB_SCS_O_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_USB_SCS_O_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_USB_SDI_O_s1 | ~cpu_0_data_master_requests_USB_SDI_O_s1) & ((~cpu_0_data_master_qualified_request_USB_SDI_O_s1 | ~cpu_0_data_master_read | (1 & ~d1_USB_SDI_O_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_USB_SDI_O_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_USB_SDO_I_s1 | ~cpu_0_data_master_requests_USB_SDO_I_s1) & ((~cpu_0_data_master_qualified_request_USB_SDO_I_s1 | ~cpu_0_data_master_read | (1 & ~d1_USB_SDO_I_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_USB_SDO_I_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_cpu_0_jtag_debug_module | ~cpu_0_data_master_requests_cpu_0_jtag_debug_module) & (cpu_0_data_master_granted_cpu_0_jtag_debug_module | ~cpu_0_data_master_qualified_request_cpu_0_jtag_debug_module) & ((~cpu_0_data_master_qualified_request_cpu_0_jtag_debug_module | ~cpu_0_data_master_read | (1 & ~d1_cpu_0_jtag_debug_module_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_cpu_0_jtag_debug_module | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_epcs_flash_controller_0_epcs_control_port | ~cpu_0_data_master_requests_epcs_flash_controller_0_epcs_control_port) & (cpu_0_data_master_granted_epcs_flash_controller_0_epcs_control_port | ~cpu_0_data_master_qualified_request_epcs_flash_controller_0_epcs_control_port);

  //r_8 master_run cascaded wait assignment, which is an e_assign
  assign r_8 = ((~cpu_0_data_master_qualified_request_epcs_flash_controller_0_epcs_control_port | ~(cpu_0_data_master_read | cpu_0_data_master_write) | (1 & ~d1_epcs_flash_controller_0_epcs_control_port_end_xfer & (cpu_0_data_master_read | cpu_0_data_master_write)))) & ((~cpu_0_data_master_qualified_request_epcs_flash_controller_0_epcs_control_port | ~(cpu_0_data_master_read | cpu_0_data_master_write) | (1 & ~d1_epcs_flash_controller_0_epcs_control_port_end_xfer & (cpu_0_data_master_read | cpu_0_data_master_write)))) & 1 & (cpu_0_data_master_qualified_request_sdram_0_s1 | (cpu_0_data_master_write & !cpu_0_data_master_byteenable_sdram_0_s1 & cpu_0_data_master_dbs_address[1]) | ~cpu_0_data_master_requests_sdram_0_s1) & (cpu_0_data_master_granted_sdram_0_s1 | ~cpu_0_data_master_qualified_request_sdram_0_s1) & ((~cpu_0_data_master_qualified_request_sdram_0_s1 | ~cpu_0_data_master_read | (1 & ~sdram_0_s1_waitrequest_from_sa & (cpu_0_data_master_dbs_address[1]) & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_sdram_0_s1 | ~cpu_0_data_master_write | (1 & ~sdram_0_s1_waitrequest_from_sa & (cpu_0_data_master_dbs_address[1]) & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_sysid_0_control_slave | ~cpu_0_data_master_requests_sysid_0_control_slave) & ((~cpu_0_data_master_qualified_request_sysid_0_control_slave | ~cpu_0_data_master_read | (1 & ~d1_sysid_0_control_slave_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_sysid_0_control_slave | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_timer_0_s1 | ~cpu_0_data_master_requests_timer_0_s1) & ((~cpu_0_data_master_qualified_request_timer_0_s1 | ~cpu_0_data_master_read | (1 & ~d1_timer_0_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_timer_0_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1 & (cpu_0_data_master_qualified_request_timer_1_s1 | ~cpu_0_data_master_requests_timer_1_s1) & ((~cpu_0_data_master_qualified_request_timer_1_s1 | ~cpu_0_data_master_read | (1 & ~d1_timer_1_s1_end_xfer & cpu_0_data_master_read))) & ((~cpu_0_data_master_qualified_request_timer_1_s1 | ~cpu_0_data_master_write | (1 & cpu_0_data_master_write))) & 1;

  //r_9 master_run cascaded wait assignment, which is an e_assign
  assign r_9 = (cpu_0_data_master_qualified_request_uart_0_s1 | ~cpu_0_data_master_requests_uart_0_s1) & ((~cpu_0_data_master_qualified_request_uart_0_s1 | ~(cpu_0_data_master_read | cpu_0_data_master_write) | (1 & ~d1_uart_0_s1_end_xfer & (cpu_0_data_master_read | cpu_0_data_master_write)))) & ((~cpu_0_data_master_qualified_request_uart_0_s1 | ~(cpu_0_data_master_read | cpu_0_data_master_write) | (1 & ~d1_uart_0_s1_end_xfer & (cpu_0_data_master_read | cpu_0_data_master_write))));

  //optimize select-logic by passing only those address bits which matter.
  assign cpu_0_data_master_address_to_slave = cpu_0_data_master_address[26 : 0];

  //cpu_0_data_master_read_but_no_slave_selected assignment, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          cpu_0_data_master_read_but_no_slave_selected <= 0;
      else 
        cpu_0_data_master_read_but_no_slave_selected <= cpu_0_data_master_read & cpu_0_data_master_run & ~cpu_0_data_master_is_granted_some_slave;
    end


  //some slave is getting selected, which is an e_mux
  assign cpu_0_data_master_is_granted_some_slave = cpu_0_data_master_granted_ADC_DATA_s1 |
    cpu_0_data_master_granted_BUZZER_DATA_s1 |
    cpu_0_data_master_granted_DAC_DATA_s1 |
    cpu_0_data_master_granted_ETH_CLKOUT_I_s1 |
    cpu_0_data_master_granted_ETH_CS_O_s1 |
    cpu_0_data_master_granted_ETH_INT_I_s1 |
    cpu_0_data_master_granted_ETH_RESET_O_s1 |
    cpu_0_data_master_granted_ETH_SCK_O_s1 |
    cpu_0_data_master_granted_ETH_SI_O_s1 |
    cpu_0_data_master_granted_ETH_SO_I_s1 |
    cpu_0_data_master_granted_ETH_WOL_I_s1 |
    cpu_0_data_master_granted_IR_DATA_s1 |
    cpu_0_data_master_granted_KEY_FOCUS_s1 |
    cpu_0_data_master_granted_LCD_CS_s1 |
    cpu_0_data_master_granted_LCD_DATA_s1 |
    cpu_0_data_master_granted_LCD_RD_s1 |
    cpu_0_data_master_granted_LCD_RS_s1 |
    cpu_0_data_master_granted_LCD_RST_s1 |
    cpu_0_data_master_granted_LCD_WR_s1 |
    cpu_0_data_master_granted_LED_DATA_s1 |
    cpu_0_data_master_granted_PS2_DATA_REC_s1 |
    cpu_0_data_master_granted_RTC_DATA_s1 |
    cpu_0_data_master_granted_SCL_s1 |
    cpu_0_data_master_granted_SDA_s1 |
    cpu_0_data_master_granted_SD_CLK_s1 |
    cpu_0_data_master_granted_SD_CS_s1 |
    cpu_0_data_master_granted_SD_DI_s1 |
    cpu_0_data_master_granted_SD_DO_s1 |
    cpu_0_data_master_granted_TEMP_DATA_s1 |
    cpu_0_data_master_granted_TUBE_EN_s1 |
    cpu_0_data_master_granted_UART_RX_DATA_s1 |
    cpu_0_data_master_granted_USB_INT_I_s1 |
    cpu_0_data_master_granted_USB_PC_I_s1 |
    cpu_0_data_master_granted_USB_RST_O_s1 |
    cpu_0_data_master_granted_USB_SCK_O_s1 |
    cpu_0_data_master_granted_USB_SCS_O_s1 |
    cpu_0_data_master_granted_USB_SDI_O_s1 |
    cpu_0_data_master_granted_USB_SDO_I_s1 |
    cpu_0_data_master_granted_cpu_0_jtag_debug_module |
    cpu_0_data_master_granted_epcs_flash_controller_0_epcs_control_port |
    cpu_0_data_master_granted_sdram_0_s1 |
    cpu_0_data_master_granted_sysid_0_control_slave |
    cpu_0_data_master_granted_timer_0_s1 |
    cpu_0_data_master_granted_timer_1_s1 |
    cpu_0_data_master_granted_uart_0_s1;

  //latent slave read data valids which may be flushed, which is an e_mux
  assign pre_flush_cpu_0_data_master_readdatavalid = cpu_0_data_master_read_data_valid_sdram_0_s1 & dbs_rdv_counter_overflow;

  //latent slave read data valid which is not flushed, which is an e_mux
  assign cpu_0_data_master_readdatavalid = cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_ADC_DATA_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_BUZZER_DATA_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_DAC_DATA_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_ETH_CLKOUT_I_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_ETH_CS_O_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_ETH_INT_I_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_ETH_RESET_O_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_ETH_SCK_O_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_ETH_SI_O_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_ETH_SO_I_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_ETH_WOL_I_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_IR_DATA_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_KEY_FOCUS_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_LCD_CS_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_LCD_DATA_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_LCD_RD_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_LCD_RS_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_LCD_RST_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_LCD_WR_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_LED_DATA_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_PS2_DATA_REC_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_RTC_DATA_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_SCL_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_SDA_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_SD_CLK_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_SD_CS_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_SD_DI_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_SD_DO_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_TEMP_DATA_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_TUBE_EN_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_UART_RX_DATA_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_USB_INT_I_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_USB_PC_I_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_USB_RST_O_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_USB_SCK_O_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_USB_SCS_O_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_USB_SDI_O_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_USB_SDO_I_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_cpu_0_jtag_debug_module |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_epcs_flash_controller_0_epcs_control_port |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_sysid_0_control_slave |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_timer_0_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_timer_1_s1 |
    cpu_0_data_master_read_but_no_slave_selected |
    pre_flush_cpu_0_data_master_readdatavalid |
    cpu_0_data_master_read_data_valid_uart_0_s1;

  //cpu_0/data_master readdata mux, which is an e_mux
  assign cpu_0_data_master_readdata = ({32 {~(cpu_0_data_master_qualified_request_ADC_DATA_s1 & cpu_0_data_master_read)}} | ADC_DATA_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_BUZZER_DATA_s1 & cpu_0_data_master_read)}} | BUZZER_DATA_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_DAC_DATA_s1 & cpu_0_data_master_read)}} | DAC_DATA_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_ETH_CLKOUT_I_s1 & cpu_0_data_master_read)}} | ETH_CLKOUT_I_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_ETH_CS_O_s1 & cpu_0_data_master_read)}} | ETH_CS_O_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_ETH_INT_I_s1 & cpu_0_data_master_read)}} | ETH_INT_I_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_ETH_RESET_O_s1 & cpu_0_data_master_read)}} | ETH_RESET_O_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_ETH_SCK_O_s1 & cpu_0_data_master_read)}} | ETH_SCK_O_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_ETH_SI_O_s1 & cpu_0_data_master_read)}} | ETH_SI_O_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_ETH_SO_I_s1 & cpu_0_data_master_read)}} | ETH_SO_I_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_ETH_WOL_I_s1 & cpu_0_data_master_read)}} | ETH_WOL_I_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_IR_DATA_s1 & cpu_0_data_master_read)}} | IR_DATA_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_KEY_FOCUS_s1 & cpu_0_data_master_read)}} | KEY_FOCUS_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_LCD_CS_s1 & cpu_0_data_master_read)}} | LCD_CS_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_LCD_DATA_s1 & cpu_0_data_master_read)}} | LCD_DATA_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_LCD_RD_s1 & cpu_0_data_master_read)}} | LCD_RD_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_LCD_RS_s1 & cpu_0_data_master_read)}} | LCD_RS_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_LCD_RST_s1 & cpu_0_data_master_read)}} | LCD_RST_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_LCD_WR_s1 & cpu_0_data_master_read)}} | LCD_WR_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_LED_DATA_s1 & cpu_0_data_master_read)}} | LED_DATA_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_PS2_DATA_REC_s1 & cpu_0_data_master_read)}} | PS2_DATA_REC_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_RTC_DATA_s1 & cpu_0_data_master_read)}} | RTC_DATA_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_SCL_s1 & cpu_0_data_master_read)}} | SCL_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_SDA_s1 & cpu_0_data_master_read)}} | SDA_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_SD_CLK_s1 & cpu_0_data_master_read)}} | SD_CLK_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_SD_CS_s1 & cpu_0_data_master_read)}} | SD_CS_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_SD_DI_s1 & cpu_0_data_master_read)}} | SD_DI_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_SD_DO_s1 & cpu_0_data_master_read)}} | SD_DO_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_TEMP_DATA_s1 & cpu_0_data_master_read)}} | TEMP_DATA_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_TUBE_EN_s1 & cpu_0_data_master_read)}} | TUBE_EN_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_UART_RX_DATA_s1 & cpu_0_data_master_read)}} | UART_RX_DATA_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_USB_INT_I_s1 & cpu_0_data_master_read)}} | USB_INT_I_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_USB_PC_I_s1 & cpu_0_data_master_read)}} | USB_PC_I_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_USB_RST_O_s1 & cpu_0_data_master_read)}} | USB_RST_O_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_USB_SCK_O_s1 & cpu_0_data_master_read)}} | USB_SCK_O_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_USB_SCS_O_s1 & cpu_0_data_master_read)}} | USB_SCS_O_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_USB_SDI_O_s1 & cpu_0_data_master_read)}} | USB_SDI_O_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_USB_SDO_I_s1 & cpu_0_data_master_read)}} | USB_SDO_I_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_cpu_0_jtag_debug_module & cpu_0_data_master_read)}} | cpu_0_jtag_debug_module_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_epcs_flash_controller_0_epcs_control_port & cpu_0_data_master_read)}} | epcs_flash_controller_0_epcs_control_port_readdata_from_sa) &
    ({32 {~cpu_0_data_master_read_data_valid_sdram_0_s1}} | {sdram_0_s1_readdata_from_sa[15 : 0],
    dbs_latent_16_reg_segment_0}) &
    ({32 {~(cpu_0_data_master_qualified_request_sysid_0_control_slave & cpu_0_data_master_read)}} | sysid_0_control_slave_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_timer_0_s1 & cpu_0_data_master_read)}} | timer_0_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_timer_1_s1 & cpu_0_data_master_read)}} | timer_1_s1_readdata_from_sa) &
    ({32 {~(cpu_0_data_master_qualified_request_uart_0_s1 & cpu_0_data_master_read)}} | uart_0_s1_readdata_from_sa);

  //actual waitrequest port, which is an e_assign
  assign cpu_0_data_master_waitrequest = ~cpu_0_data_master_run;

  //latent max counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          cpu_0_data_master_latency_counter <= 0;
      else 
        cpu_0_data_master_latency_counter <= p1_cpu_0_data_master_latency_counter;
    end


  //latency counter load mux, which is an e_mux
  assign p1_cpu_0_data_master_latency_counter = ((cpu_0_data_master_run & cpu_0_data_master_read))? latency_load_value :
    (cpu_0_data_master_latency_counter)? cpu_0_data_master_latency_counter - 1 :
    0;

  //read latency load values, which is an e_mux
  assign latency_load_value = 0;

  //irq assign, which is an e_assign
  assign cpu_0_data_master_irq = {1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    1'b0,
    timer_1_s1_irq_from_sa,
    timer_0_s1_irq_from_sa,
    uart_0_s1_irq_from_sa,
    epcs_flash_controller_0_epcs_control_port_irq_from_sa};

  //pre dbs count enable, which is an e_mux
  assign pre_dbs_count_enable = (((~0) & cpu_0_data_master_requests_sdram_0_s1 & cpu_0_data_master_write & !cpu_0_data_master_byteenable_sdram_0_s1)) |
    (cpu_0_data_master_granted_sdram_0_s1 & cpu_0_data_master_read & 1 & 1 & ~sdram_0_s1_waitrequest_from_sa) |
    (cpu_0_data_master_granted_sdram_0_s1 & cpu_0_data_master_write & 1 & 1 & ~sdram_0_s1_waitrequest_from_sa);

  //input to latent dbs-16 stored 0, which is an e_mux
  assign p1_dbs_latent_16_reg_segment_0 = sdram_0_s1_readdata_from_sa;

  //dbs register for latent dbs-16 segment 0, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          dbs_latent_16_reg_segment_0 <= 0;
      else if (dbs_rdv_count_enable & ((cpu_0_data_master_dbs_rdv_counter[1]) == 0))
          dbs_latent_16_reg_segment_0 <= p1_dbs_latent_16_reg_segment_0;
    end


  //mux write dbs 1, which is an e_mux
  assign cpu_0_data_master_dbs_write_16 = (cpu_0_data_master_dbs_address[1])? cpu_0_data_master_writedata[31 : 16] :
    cpu_0_data_master_writedata[15 : 0];

  //dbs count increment, which is an e_mux
  assign cpu_0_data_master_dbs_increment = (cpu_0_data_master_requests_sdram_0_s1)? 2 :
    0;

  //dbs counter overflow, which is an e_assign
  assign dbs_counter_overflow = cpu_0_data_master_dbs_address[1] & !(next_dbs_address[1]);

  //next master address, which is an e_assign
  assign next_dbs_address = cpu_0_data_master_dbs_address + cpu_0_data_master_dbs_increment;

  //dbs count enable, which is an e_mux
  assign dbs_count_enable = pre_dbs_count_enable;

  //dbs counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          cpu_0_data_master_dbs_address <= 0;
      else if (dbs_count_enable)
          cpu_0_data_master_dbs_address <= next_dbs_address;
    end


  //p1 dbs rdv counter, which is an e_assign
  assign cpu_0_data_master_next_dbs_rdv_counter = cpu_0_data_master_dbs_rdv_counter + cpu_0_data_master_dbs_rdv_counter_inc;

  //cpu_0_data_master_rdv_inc_mux, which is an e_mux
  assign cpu_0_data_master_dbs_rdv_counter_inc = 2;

  //master any slave rdv, which is an e_mux
  assign dbs_rdv_count_enable = cpu_0_data_master_read_data_valid_sdram_0_s1;

  //dbs rdv counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          cpu_0_data_master_dbs_rdv_counter <= 0;
      else if (dbs_rdv_count_enable)
          cpu_0_data_master_dbs_rdv_counter <= cpu_0_data_master_next_dbs_rdv_counter;
    end


  //dbs rdv counter overflow, which is an e_assign
  assign dbs_rdv_counter_overflow = cpu_0_data_master_dbs_rdv_counter[1] & ~cpu_0_data_master_next_dbs_rdv_counter[1];


//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //cpu_0_data_master_address check against wait, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          cpu_0_data_master_address_last_time <= 0;
      else 
        cpu_0_data_master_address_last_time <= cpu_0_data_master_address;
    end


  //cpu_0/data_master waited last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          active_and_waiting_last_time <= 0;
      else 
        active_and_waiting_last_time <= cpu_0_data_master_waitrequest & (cpu_0_data_master_read | cpu_0_data_master_write);
    end


  //cpu_0_data_master_address matches last port_name, which is an e_process
  always @(posedge clk)
    begin
      if (active_and_waiting_last_time & (cpu_0_data_master_address != cpu_0_data_master_address_last_time))
        begin
          $write("%0d ns: cpu_0_data_master_address did not heed wait!!!", $time);
          $stop;
        end
    end


  //cpu_0_data_master_byteenable check against wait, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          cpu_0_data_master_byteenable_last_time <= 0;
      else 
        cpu_0_data_master_byteenable_last_time <= cpu_0_data_master_byteenable;
    end


  //cpu_0_data_master_byteenable matches last port_name, which is an e_process
  always @(posedge clk)
    begin
      if (active_and_waiting_last_time & (cpu_0_data_master_byteenable != cpu_0_data_master_byteenable_last_time))
        begin
          $write("%0d ns: cpu_0_data_master_byteenable did not heed wait!!!", $time);
          $stop;
        end
    end


  //cpu_0_data_master_read check against wait, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          cpu_0_data_master_read_last_time <= 0;
      else 
        cpu_0_data_master_read_last_time <= cpu_0_data_master_read;
    end


  //cpu_0_data_master_read matches last port_name, which is an e_process
  always @(posedge clk)
    begin
      if (active_and_waiting_last_time & (cpu_0_data_master_read != cpu_0_data_master_read_last_time))
        begin
          $write("%0d ns: cpu_0_data_master_read did not heed wait!!!", $time);
          $stop;
        end
    end


  //cpu_0_data_master_write check against wait, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          cpu_0_data_master_write_last_time <= 0;
      else 
        cpu_0_data_master_write_last_time <= cpu_0_data_master_write;
    end


  //cpu_0_data_master_write matches last port_name, which is an e_process
  always @(posedge clk)
    begin
      if (active_and_waiting_last_time & (cpu_0_data_master_write != cpu_0_data_master_write_last_time))
        begin
          $write("%0d ns: cpu_0_data_master_write did not heed wait!!!", $time);
          $stop;
        end
    end


  //cpu_0_data_master_writedata check against wait, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          cpu_0_data_master_writedata_last_time <= 0;
      else 
        cpu_0_data_master_writedata_last_time <= cpu_0_data_master_writedata;
    end


  //cpu_0_data_master_writedata matches last port_name, which is an e_process
  always @(posedge clk)
    begin
      if (active_and_waiting_last_time & (cpu_0_data_master_writedata != cpu_0_data_master_writedata_last_time) & cpu_0_data_master_write)
        begin
          $write("%0d ns: cpu_0_data_master_writedata did not heed wait!!!", $time);
          $stop;
        end
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module cpu_0_instruction_master_arbitrator (
                                             // inputs:
                                              clk,
                                              cpu_0_instruction_master_address,
                                              cpu_0_instruction_master_granted_cpu_0_jtag_debug_module,
                                              cpu_0_instruction_master_granted_epcs_flash_controller_0_epcs_control_port,
                                              cpu_0_instruction_master_granted_sdram_0_s1,
                                              cpu_0_instruction_master_qualified_request_cpu_0_jtag_debug_module,
                                              cpu_0_instruction_master_qualified_request_epcs_flash_controller_0_epcs_control_port,
                                              cpu_0_instruction_master_qualified_request_sdram_0_s1,
                                              cpu_0_instruction_master_read,
                                              cpu_0_instruction_master_read_data_valid_cpu_0_jtag_debug_module,
                                              cpu_0_instruction_master_read_data_valid_epcs_flash_controller_0_epcs_control_port,
                                              cpu_0_instruction_master_read_data_valid_sdram_0_s1,
                                              cpu_0_instruction_master_read_data_valid_sdram_0_s1_shift_register,
                                              cpu_0_instruction_master_requests_cpu_0_jtag_debug_module,
                                              cpu_0_instruction_master_requests_epcs_flash_controller_0_epcs_control_port,
                                              cpu_0_instruction_master_requests_sdram_0_s1,
                                              cpu_0_jtag_debug_module_readdata_from_sa,
                                              d1_cpu_0_jtag_debug_module_end_xfer,
                                              d1_epcs_flash_controller_0_epcs_control_port_end_xfer,
                                              d1_sdram_0_s1_end_xfer,
                                              epcs_flash_controller_0_epcs_control_port_readdata_from_sa,
                                              reset_n,
                                              sdram_0_s1_readdata_from_sa,
                                              sdram_0_s1_waitrequest_from_sa,

                                             // outputs:
                                              cpu_0_instruction_master_address_to_slave,
                                              cpu_0_instruction_master_dbs_address,
                                              cpu_0_instruction_master_latency_counter,
                                              cpu_0_instruction_master_readdata,
                                              cpu_0_instruction_master_readdatavalid,
                                              cpu_0_instruction_master_waitrequest
                                           )
;

  output  [ 26: 0] cpu_0_instruction_master_address_to_slave;
  output  [  1: 0] cpu_0_instruction_master_dbs_address;
  output           cpu_0_instruction_master_latency_counter;
  output  [ 31: 0] cpu_0_instruction_master_readdata;
  output           cpu_0_instruction_master_readdatavalid;
  output           cpu_0_instruction_master_waitrequest;
  input            clk;
  input   [ 26: 0] cpu_0_instruction_master_address;
  input            cpu_0_instruction_master_granted_cpu_0_jtag_debug_module;
  input            cpu_0_instruction_master_granted_epcs_flash_controller_0_epcs_control_port;
  input            cpu_0_instruction_master_granted_sdram_0_s1;
  input            cpu_0_instruction_master_qualified_request_cpu_0_jtag_debug_module;
  input            cpu_0_instruction_master_qualified_request_epcs_flash_controller_0_epcs_control_port;
  input            cpu_0_instruction_master_qualified_request_sdram_0_s1;
  input            cpu_0_instruction_master_read;
  input            cpu_0_instruction_master_read_data_valid_cpu_0_jtag_debug_module;
  input            cpu_0_instruction_master_read_data_valid_epcs_flash_controller_0_epcs_control_port;
  input            cpu_0_instruction_master_read_data_valid_sdram_0_s1;
  input            cpu_0_instruction_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_instruction_master_requests_cpu_0_jtag_debug_module;
  input            cpu_0_instruction_master_requests_epcs_flash_controller_0_epcs_control_port;
  input            cpu_0_instruction_master_requests_sdram_0_s1;
  input   [ 31: 0] cpu_0_jtag_debug_module_readdata_from_sa;
  input            d1_cpu_0_jtag_debug_module_end_xfer;
  input            d1_epcs_flash_controller_0_epcs_control_port_end_xfer;
  input            d1_sdram_0_s1_end_xfer;
  input   [ 31: 0] epcs_flash_controller_0_epcs_control_port_readdata_from_sa;
  input            reset_n;
  input   [ 15: 0] sdram_0_s1_readdata_from_sa;
  input            sdram_0_s1_waitrequest_from_sa;

  reg              active_and_waiting_last_time;
  reg     [ 26: 0] cpu_0_instruction_master_address_last_time;
  wire    [ 26: 0] cpu_0_instruction_master_address_to_slave;
  reg     [  1: 0] cpu_0_instruction_master_dbs_address;
  wire    [  1: 0] cpu_0_instruction_master_dbs_increment;
  reg     [  1: 0] cpu_0_instruction_master_dbs_rdv_counter;
  wire    [  1: 0] cpu_0_instruction_master_dbs_rdv_counter_inc;
  wire             cpu_0_instruction_master_is_granted_some_slave;
  reg              cpu_0_instruction_master_latency_counter;
  wire    [  1: 0] cpu_0_instruction_master_next_dbs_rdv_counter;
  reg              cpu_0_instruction_master_read_but_no_slave_selected;
  reg              cpu_0_instruction_master_read_last_time;
  wire    [ 31: 0] cpu_0_instruction_master_readdata;
  wire             cpu_0_instruction_master_readdatavalid;
  wire             cpu_0_instruction_master_run;
  wire             cpu_0_instruction_master_waitrequest;
  wire             dbs_count_enable;
  wire             dbs_counter_overflow;
  reg     [ 15: 0] dbs_latent_16_reg_segment_0;
  wire             dbs_rdv_count_enable;
  wire             dbs_rdv_counter_overflow;
  wire             latency_load_value;
  wire    [  1: 0] next_dbs_address;
  wire             p1_cpu_0_instruction_master_latency_counter;
  wire    [ 15: 0] p1_dbs_latent_16_reg_segment_0;
  wire             pre_dbs_count_enable;
  wire             pre_flush_cpu_0_instruction_master_readdatavalid;
  wire             r_7;
  wire             r_8;
  //r_7 master_run cascaded wait assignment, which is an e_assign
  assign r_7 = 1 & (cpu_0_instruction_master_qualified_request_cpu_0_jtag_debug_module | ~cpu_0_instruction_master_requests_cpu_0_jtag_debug_module) & (cpu_0_instruction_master_granted_cpu_0_jtag_debug_module | ~cpu_0_instruction_master_qualified_request_cpu_0_jtag_debug_module) & ((~cpu_0_instruction_master_qualified_request_cpu_0_jtag_debug_module | ~cpu_0_instruction_master_read | (1 & ~d1_cpu_0_jtag_debug_module_end_xfer & cpu_0_instruction_master_read))) & 1 & (cpu_0_instruction_master_qualified_request_epcs_flash_controller_0_epcs_control_port | ~cpu_0_instruction_master_requests_epcs_flash_controller_0_epcs_control_port);

  //cascaded wait assignment, which is an e_assign
  assign cpu_0_instruction_master_run = r_7 & r_8;

  //r_8 master_run cascaded wait assignment, which is an e_assign
  assign r_8 = (cpu_0_instruction_master_granted_epcs_flash_controller_0_epcs_control_port | ~cpu_0_instruction_master_qualified_request_epcs_flash_controller_0_epcs_control_port) & ((~cpu_0_instruction_master_qualified_request_epcs_flash_controller_0_epcs_control_port | ~(cpu_0_instruction_master_read) | (1 & ~d1_epcs_flash_controller_0_epcs_control_port_end_xfer & (cpu_0_instruction_master_read)))) & 1 & (cpu_0_instruction_master_qualified_request_sdram_0_s1 | ~cpu_0_instruction_master_requests_sdram_0_s1) & (cpu_0_instruction_master_granted_sdram_0_s1 | ~cpu_0_instruction_master_qualified_request_sdram_0_s1) & ((~cpu_0_instruction_master_qualified_request_sdram_0_s1 | ~cpu_0_instruction_master_read | (1 & ~sdram_0_s1_waitrequest_from_sa & (cpu_0_instruction_master_dbs_address[1]) & cpu_0_instruction_master_read)));

  //optimize select-logic by passing only those address bits which matter.
  assign cpu_0_instruction_master_address_to_slave = cpu_0_instruction_master_address[26 : 0];

  //cpu_0_instruction_master_read_but_no_slave_selected assignment, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          cpu_0_instruction_master_read_but_no_slave_selected <= 0;
      else 
        cpu_0_instruction_master_read_but_no_slave_selected <= cpu_0_instruction_master_read & cpu_0_instruction_master_run & ~cpu_0_instruction_master_is_granted_some_slave;
    end


  //some slave is getting selected, which is an e_mux
  assign cpu_0_instruction_master_is_granted_some_slave = cpu_0_instruction_master_granted_cpu_0_jtag_debug_module |
    cpu_0_instruction_master_granted_epcs_flash_controller_0_epcs_control_port |
    cpu_0_instruction_master_granted_sdram_0_s1;

  //latent slave read data valids which may be flushed, which is an e_mux
  assign pre_flush_cpu_0_instruction_master_readdatavalid = cpu_0_instruction_master_read_data_valid_sdram_0_s1 & dbs_rdv_counter_overflow;

  //latent slave read data valid which is not flushed, which is an e_mux
  assign cpu_0_instruction_master_readdatavalid = cpu_0_instruction_master_read_but_no_slave_selected |
    pre_flush_cpu_0_instruction_master_readdatavalid |
    cpu_0_instruction_master_read_data_valid_cpu_0_jtag_debug_module |
    cpu_0_instruction_master_read_but_no_slave_selected |
    pre_flush_cpu_0_instruction_master_readdatavalid |
    cpu_0_instruction_master_read_data_valid_epcs_flash_controller_0_epcs_control_port |
    cpu_0_instruction_master_read_but_no_slave_selected |
    pre_flush_cpu_0_instruction_master_readdatavalid;

  //cpu_0/instruction_master readdata mux, which is an e_mux
  assign cpu_0_instruction_master_readdata = ({32 {~(cpu_0_instruction_master_qualified_request_cpu_0_jtag_debug_module & cpu_0_instruction_master_read)}} | cpu_0_jtag_debug_module_readdata_from_sa) &
    ({32 {~(cpu_0_instruction_master_qualified_request_epcs_flash_controller_0_epcs_control_port & cpu_0_instruction_master_read)}} | epcs_flash_controller_0_epcs_control_port_readdata_from_sa) &
    ({32 {~cpu_0_instruction_master_read_data_valid_sdram_0_s1}} | {sdram_0_s1_readdata_from_sa[15 : 0],
    dbs_latent_16_reg_segment_0});

  //actual waitrequest port, which is an e_assign
  assign cpu_0_instruction_master_waitrequest = ~cpu_0_instruction_master_run;

  //latent max counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          cpu_0_instruction_master_latency_counter <= 0;
      else 
        cpu_0_instruction_master_latency_counter <= p1_cpu_0_instruction_master_latency_counter;
    end


  //latency counter load mux, which is an e_mux
  assign p1_cpu_0_instruction_master_latency_counter = ((cpu_0_instruction_master_run & cpu_0_instruction_master_read))? latency_load_value :
    (cpu_0_instruction_master_latency_counter)? cpu_0_instruction_master_latency_counter - 1 :
    0;

  //read latency load values, which is an e_mux
  assign latency_load_value = 0;

  //input to latent dbs-16 stored 0, which is an e_mux
  assign p1_dbs_latent_16_reg_segment_0 = sdram_0_s1_readdata_from_sa;

  //dbs register for latent dbs-16 segment 0, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          dbs_latent_16_reg_segment_0 <= 0;
      else if (dbs_rdv_count_enable & ((cpu_0_instruction_master_dbs_rdv_counter[1]) == 0))
          dbs_latent_16_reg_segment_0 <= p1_dbs_latent_16_reg_segment_0;
    end


  //dbs count increment, which is an e_mux
  assign cpu_0_instruction_master_dbs_increment = (cpu_0_instruction_master_requests_sdram_0_s1)? 2 :
    0;

  //dbs counter overflow, which is an e_assign
  assign dbs_counter_overflow = cpu_0_instruction_master_dbs_address[1] & !(next_dbs_address[1]);

  //next master address, which is an e_assign
  assign next_dbs_address = cpu_0_instruction_master_dbs_address + cpu_0_instruction_master_dbs_increment;

  //dbs count enable, which is an e_mux
  assign dbs_count_enable = pre_dbs_count_enable;

  //dbs counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          cpu_0_instruction_master_dbs_address <= 0;
      else if (dbs_count_enable)
          cpu_0_instruction_master_dbs_address <= next_dbs_address;
    end


  //p1 dbs rdv counter, which is an e_assign
  assign cpu_0_instruction_master_next_dbs_rdv_counter = cpu_0_instruction_master_dbs_rdv_counter + cpu_0_instruction_master_dbs_rdv_counter_inc;

  //cpu_0_instruction_master_rdv_inc_mux, which is an e_mux
  assign cpu_0_instruction_master_dbs_rdv_counter_inc = 2;

  //master any slave rdv, which is an e_mux
  assign dbs_rdv_count_enable = cpu_0_instruction_master_read_data_valid_sdram_0_s1;

  //dbs rdv counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          cpu_0_instruction_master_dbs_rdv_counter <= 0;
      else if (dbs_rdv_count_enable)
          cpu_0_instruction_master_dbs_rdv_counter <= cpu_0_instruction_master_next_dbs_rdv_counter;
    end


  //dbs rdv counter overflow, which is an e_assign
  assign dbs_rdv_counter_overflow = cpu_0_instruction_master_dbs_rdv_counter[1] & ~cpu_0_instruction_master_next_dbs_rdv_counter[1];

  //pre dbs count enable, which is an e_mux
  assign pre_dbs_count_enable = cpu_0_instruction_master_granted_sdram_0_s1 & cpu_0_instruction_master_read & 1 & 1 & ~sdram_0_s1_waitrequest_from_sa;


//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //cpu_0_instruction_master_address check against wait, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          cpu_0_instruction_master_address_last_time <= 0;
      else 
        cpu_0_instruction_master_address_last_time <= cpu_0_instruction_master_address;
    end


  //cpu_0/instruction_master waited last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          active_and_waiting_last_time <= 0;
      else 
        active_and_waiting_last_time <= cpu_0_instruction_master_waitrequest & (cpu_0_instruction_master_read);
    end


  //cpu_0_instruction_master_address matches last port_name, which is an e_process
  always @(posedge clk)
    begin
      if (active_and_waiting_last_time & (cpu_0_instruction_master_address != cpu_0_instruction_master_address_last_time))
        begin
          $write("%0d ns: cpu_0_instruction_master_address did not heed wait!!!", $time);
          $stop;
        end
    end


  //cpu_0_instruction_master_read check against wait, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          cpu_0_instruction_master_read_last_time <= 0;
      else 
        cpu_0_instruction_master_read_last_time <= cpu_0_instruction_master_read;
    end


  //cpu_0_instruction_master_read matches last port_name, which is an e_process
  always @(posedge clk)
    begin
      if (active_and_waiting_last_time & (cpu_0_instruction_master_read != cpu_0_instruction_master_read_last_time))
        begin
          $write("%0d ns: cpu_0_instruction_master_read did not heed wait!!!", $time);
          $stop;
        end
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module epcs_flash_controller_0_epcs_control_port_arbitrator (
                                                              // inputs:
                                                               clk,
                                                               cpu_0_data_master_address_to_slave,
                                                               cpu_0_data_master_latency_counter,
                                                               cpu_0_data_master_read,
                                                               cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                                               cpu_0_data_master_write,
                                                               cpu_0_data_master_writedata,
                                                               cpu_0_instruction_master_address_to_slave,
                                                               cpu_0_instruction_master_latency_counter,
                                                               cpu_0_instruction_master_read,
                                                               cpu_0_instruction_master_read_data_valid_sdram_0_s1_shift_register,
                                                               epcs_flash_controller_0_epcs_control_port_dataavailable,
                                                               epcs_flash_controller_0_epcs_control_port_endofpacket,
                                                               epcs_flash_controller_0_epcs_control_port_irq,
                                                               epcs_flash_controller_0_epcs_control_port_readdata,
                                                               epcs_flash_controller_0_epcs_control_port_readyfordata,
                                                               reset_n,

                                                              // outputs:
                                                               cpu_0_data_master_granted_epcs_flash_controller_0_epcs_control_port,
                                                               cpu_0_data_master_qualified_request_epcs_flash_controller_0_epcs_control_port,
                                                               cpu_0_data_master_read_data_valid_epcs_flash_controller_0_epcs_control_port,
                                                               cpu_0_data_master_requests_epcs_flash_controller_0_epcs_control_port,
                                                               cpu_0_instruction_master_granted_epcs_flash_controller_0_epcs_control_port,
                                                               cpu_0_instruction_master_qualified_request_epcs_flash_controller_0_epcs_control_port,
                                                               cpu_0_instruction_master_read_data_valid_epcs_flash_controller_0_epcs_control_port,
                                                               cpu_0_instruction_master_requests_epcs_flash_controller_0_epcs_control_port,
                                                               d1_epcs_flash_controller_0_epcs_control_port_end_xfer,
                                                               epcs_flash_controller_0_epcs_control_port_address,
                                                               epcs_flash_controller_0_epcs_control_port_chipselect,
                                                               epcs_flash_controller_0_epcs_control_port_dataavailable_from_sa,
                                                               epcs_flash_controller_0_epcs_control_port_endofpacket_from_sa,
                                                               epcs_flash_controller_0_epcs_control_port_irq_from_sa,
                                                               epcs_flash_controller_0_epcs_control_port_read_n,
                                                               epcs_flash_controller_0_epcs_control_port_readdata_from_sa,
                                                               epcs_flash_controller_0_epcs_control_port_readyfordata_from_sa,
                                                               epcs_flash_controller_0_epcs_control_port_reset_n,
                                                               epcs_flash_controller_0_epcs_control_port_write_n,
                                                               epcs_flash_controller_0_epcs_control_port_writedata
                                                            )
;

  output           cpu_0_data_master_granted_epcs_flash_controller_0_epcs_control_port;
  output           cpu_0_data_master_qualified_request_epcs_flash_controller_0_epcs_control_port;
  output           cpu_0_data_master_read_data_valid_epcs_flash_controller_0_epcs_control_port;
  output           cpu_0_data_master_requests_epcs_flash_controller_0_epcs_control_port;
  output           cpu_0_instruction_master_granted_epcs_flash_controller_0_epcs_control_port;
  output           cpu_0_instruction_master_qualified_request_epcs_flash_controller_0_epcs_control_port;
  output           cpu_0_instruction_master_read_data_valid_epcs_flash_controller_0_epcs_control_port;
  output           cpu_0_instruction_master_requests_epcs_flash_controller_0_epcs_control_port;
  output           d1_epcs_flash_controller_0_epcs_control_port_end_xfer;
  output  [  8: 0] epcs_flash_controller_0_epcs_control_port_address;
  output           epcs_flash_controller_0_epcs_control_port_chipselect;
  output           epcs_flash_controller_0_epcs_control_port_dataavailable_from_sa;
  output           epcs_flash_controller_0_epcs_control_port_endofpacket_from_sa;
  output           epcs_flash_controller_0_epcs_control_port_irq_from_sa;
  output           epcs_flash_controller_0_epcs_control_port_read_n;
  output  [ 31: 0] epcs_flash_controller_0_epcs_control_port_readdata_from_sa;
  output           epcs_flash_controller_0_epcs_control_port_readyfordata_from_sa;
  output           epcs_flash_controller_0_epcs_control_port_reset_n;
  output           epcs_flash_controller_0_epcs_control_port_write_n;
  output  [ 31: 0] epcs_flash_controller_0_epcs_control_port_writedata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input   [ 26: 0] cpu_0_instruction_master_address_to_slave;
  input            cpu_0_instruction_master_latency_counter;
  input            cpu_0_instruction_master_read;
  input            cpu_0_instruction_master_read_data_valid_sdram_0_s1_shift_register;
  input            epcs_flash_controller_0_epcs_control_port_dataavailable;
  input            epcs_flash_controller_0_epcs_control_port_endofpacket;
  input            epcs_flash_controller_0_epcs_control_port_irq;
  input   [ 31: 0] epcs_flash_controller_0_epcs_control_port_readdata;
  input            epcs_flash_controller_0_epcs_control_port_readyfordata;
  input            reset_n;

  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_epcs_flash_controller_0_epcs_control_port;
  wire             cpu_0_data_master_qualified_request_epcs_flash_controller_0_epcs_control_port;
  wire             cpu_0_data_master_read_data_valid_epcs_flash_controller_0_epcs_control_port;
  wire             cpu_0_data_master_requests_epcs_flash_controller_0_epcs_control_port;
  wire             cpu_0_data_master_saved_grant_epcs_flash_controller_0_epcs_control_port;
  wire             cpu_0_instruction_master_arbiterlock;
  wire             cpu_0_instruction_master_arbiterlock2;
  wire             cpu_0_instruction_master_continuerequest;
  wire             cpu_0_instruction_master_granted_epcs_flash_controller_0_epcs_control_port;
  wire             cpu_0_instruction_master_qualified_request_epcs_flash_controller_0_epcs_control_port;
  wire             cpu_0_instruction_master_read_data_valid_epcs_flash_controller_0_epcs_control_port;
  wire             cpu_0_instruction_master_requests_epcs_flash_controller_0_epcs_control_port;
  wire             cpu_0_instruction_master_saved_grant_epcs_flash_controller_0_epcs_control_port;
  reg              d1_epcs_flash_controller_0_epcs_control_port_end_xfer;
  reg              d1_reasons_to_wait;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_epcs_flash_controller_0_epcs_control_port;
  wire    [  8: 0] epcs_flash_controller_0_epcs_control_port_address;
  wire             epcs_flash_controller_0_epcs_control_port_allgrants;
  wire             epcs_flash_controller_0_epcs_control_port_allow_new_arb_cycle;
  wire             epcs_flash_controller_0_epcs_control_port_any_bursting_master_saved_grant;
  wire             epcs_flash_controller_0_epcs_control_port_any_continuerequest;
  reg     [  1: 0] epcs_flash_controller_0_epcs_control_port_arb_addend;
  wire             epcs_flash_controller_0_epcs_control_port_arb_counter_enable;
  reg     [  1: 0] epcs_flash_controller_0_epcs_control_port_arb_share_counter;
  wire    [  1: 0] epcs_flash_controller_0_epcs_control_port_arb_share_counter_next_value;
  wire    [  1: 0] epcs_flash_controller_0_epcs_control_port_arb_share_set_values;
  wire    [  1: 0] epcs_flash_controller_0_epcs_control_port_arb_winner;
  wire             epcs_flash_controller_0_epcs_control_port_arbitration_holdoff_internal;
  wire             epcs_flash_controller_0_epcs_control_port_beginbursttransfer_internal;
  wire             epcs_flash_controller_0_epcs_control_port_begins_xfer;
  wire             epcs_flash_controller_0_epcs_control_port_chipselect;
  wire    [  3: 0] epcs_flash_controller_0_epcs_control_port_chosen_master_double_vector;
  wire    [  1: 0] epcs_flash_controller_0_epcs_control_port_chosen_master_rot_left;
  wire             epcs_flash_controller_0_epcs_control_port_dataavailable_from_sa;
  wire             epcs_flash_controller_0_epcs_control_port_end_xfer;
  wire             epcs_flash_controller_0_epcs_control_port_endofpacket_from_sa;
  wire             epcs_flash_controller_0_epcs_control_port_firsttransfer;
  wire    [  1: 0] epcs_flash_controller_0_epcs_control_port_grant_vector;
  wire             epcs_flash_controller_0_epcs_control_port_in_a_read_cycle;
  wire             epcs_flash_controller_0_epcs_control_port_in_a_write_cycle;
  wire             epcs_flash_controller_0_epcs_control_port_irq_from_sa;
  wire    [  1: 0] epcs_flash_controller_0_epcs_control_port_master_qreq_vector;
  wire             epcs_flash_controller_0_epcs_control_port_non_bursting_master_requests;
  wire             epcs_flash_controller_0_epcs_control_port_read_n;
  wire    [ 31: 0] epcs_flash_controller_0_epcs_control_port_readdata_from_sa;
  wire             epcs_flash_controller_0_epcs_control_port_readyfordata_from_sa;
  reg              epcs_flash_controller_0_epcs_control_port_reg_firsttransfer;
  wire             epcs_flash_controller_0_epcs_control_port_reset_n;
  reg     [  1: 0] epcs_flash_controller_0_epcs_control_port_saved_chosen_master_vector;
  reg              epcs_flash_controller_0_epcs_control_port_slavearbiterlockenable;
  wire             epcs_flash_controller_0_epcs_control_port_slavearbiterlockenable2;
  wire             epcs_flash_controller_0_epcs_control_port_unreg_firsttransfer;
  wire             epcs_flash_controller_0_epcs_control_port_waits_for_read;
  wire             epcs_flash_controller_0_epcs_control_port_waits_for_write;
  wire             epcs_flash_controller_0_epcs_control_port_write_n;
  wire    [ 31: 0] epcs_flash_controller_0_epcs_control_port_writedata;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  reg              last_cycle_cpu_0_data_master_granted_slave_epcs_flash_controller_0_epcs_control_port;
  reg              last_cycle_cpu_0_instruction_master_granted_slave_epcs_flash_controller_0_epcs_control_port;
  wire    [ 26: 0] shifted_address_to_epcs_flash_controller_0_epcs_control_port_from_cpu_0_data_master;
  wire    [ 26: 0] shifted_address_to_epcs_flash_controller_0_epcs_control_port_from_cpu_0_instruction_master;
  wire             wait_for_epcs_flash_controller_0_epcs_control_port_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~epcs_flash_controller_0_epcs_control_port_end_xfer;
    end


  assign epcs_flash_controller_0_epcs_control_port_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_epcs_flash_controller_0_epcs_control_port | cpu_0_instruction_master_qualified_request_epcs_flash_controller_0_epcs_control_port));
  //assign epcs_flash_controller_0_epcs_control_port_readdata_from_sa = epcs_flash_controller_0_epcs_control_port_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign epcs_flash_controller_0_epcs_control_port_readdata_from_sa = epcs_flash_controller_0_epcs_control_port_readdata;

  assign cpu_0_data_master_requests_epcs_flash_controller_0_epcs_control_port = ({cpu_0_data_master_address_to_slave[26 : 11] , 11'b0} == 27'h4001800) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //assign epcs_flash_controller_0_epcs_control_port_dataavailable_from_sa = epcs_flash_controller_0_epcs_control_port_dataavailable so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign epcs_flash_controller_0_epcs_control_port_dataavailable_from_sa = epcs_flash_controller_0_epcs_control_port_dataavailable;

  //assign epcs_flash_controller_0_epcs_control_port_readyfordata_from_sa = epcs_flash_controller_0_epcs_control_port_readyfordata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign epcs_flash_controller_0_epcs_control_port_readyfordata_from_sa = epcs_flash_controller_0_epcs_control_port_readyfordata;

  //epcs_flash_controller_0_epcs_control_port_arb_share_counter set values, which is an e_mux
  assign epcs_flash_controller_0_epcs_control_port_arb_share_set_values = 1;

  //epcs_flash_controller_0_epcs_control_port_non_bursting_master_requests mux, which is an e_mux
  assign epcs_flash_controller_0_epcs_control_port_non_bursting_master_requests = cpu_0_data_master_requests_epcs_flash_controller_0_epcs_control_port |
    cpu_0_instruction_master_requests_epcs_flash_controller_0_epcs_control_port |
    cpu_0_data_master_requests_epcs_flash_controller_0_epcs_control_port |
    cpu_0_instruction_master_requests_epcs_flash_controller_0_epcs_control_port;

  //epcs_flash_controller_0_epcs_control_port_any_bursting_master_saved_grant mux, which is an e_mux
  assign epcs_flash_controller_0_epcs_control_port_any_bursting_master_saved_grant = 0;

  //epcs_flash_controller_0_epcs_control_port_arb_share_counter_next_value assignment, which is an e_assign
  assign epcs_flash_controller_0_epcs_control_port_arb_share_counter_next_value = epcs_flash_controller_0_epcs_control_port_firsttransfer ? (epcs_flash_controller_0_epcs_control_port_arb_share_set_values - 1) : |epcs_flash_controller_0_epcs_control_port_arb_share_counter ? (epcs_flash_controller_0_epcs_control_port_arb_share_counter - 1) : 0;

  //epcs_flash_controller_0_epcs_control_port_allgrants all slave grants, which is an e_mux
  assign epcs_flash_controller_0_epcs_control_port_allgrants = (|epcs_flash_controller_0_epcs_control_port_grant_vector) |
    (|epcs_flash_controller_0_epcs_control_port_grant_vector) |
    (|epcs_flash_controller_0_epcs_control_port_grant_vector) |
    (|epcs_flash_controller_0_epcs_control_port_grant_vector);

  //epcs_flash_controller_0_epcs_control_port_end_xfer assignment, which is an e_assign
  assign epcs_flash_controller_0_epcs_control_port_end_xfer = ~(epcs_flash_controller_0_epcs_control_port_waits_for_read | epcs_flash_controller_0_epcs_control_port_waits_for_write);

  //end_xfer_arb_share_counter_term_epcs_flash_controller_0_epcs_control_port arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_epcs_flash_controller_0_epcs_control_port = epcs_flash_controller_0_epcs_control_port_end_xfer & (~epcs_flash_controller_0_epcs_control_port_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //epcs_flash_controller_0_epcs_control_port_arb_share_counter arbitration counter enable, which is an e_assign
  assign epcs_flash_controller_0_epcs_control_port_arb_counter_enable = (end_xfer_arb_share_counter_term_epcs_flash_controller_0_epcs_control_port & epcs_flash_controller_0_epcs_control_port_allgrants) | (end_xfer_arb_share_counter_term_epcs_flash_controller_0_epcs_control_port & ~epcs_flash_controller_0_epcs_control_port_non_bursting_master_requests);

  //epcs_flash_controller_0_epcs_control_port_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          epcs_flash_controller_0_epcs_control_port_arb_share_counter <= 0;
      else if (epcs_flash_controller_0_epcs_control_port_arb_counter_enable)
          epcs_flash_controller_0_epcs_control_port_arb_share_counter <= epcs_flash_controller_0_epcs_control_port_arb_share_counter_next_value;
    end


  //epcs_flash_controller_0_epcs_control_port_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          epcs_flash_controller_0_epcs_control_port_slavearbiterlockenable <= 0;
      else if ((|epcs_flash_controller_0_epcs_control_port_master_qreq_vector & end_xfer_arb_share_counter_term_epcs_flash_controller_0_epcs_control_port) | (end_xfer_arb_share_counter_term_epcs_flash_controller_0_epcs_control_port & ~epcs_flash_controller_0_epcs_control_port_non_bursting_master_requests))
          epcs_flash_controller_0_epcs_control_port_slavearbiterlockenable <= |epcs_flash_controller_0_epcs_control_port_arb_share_counter_next_value;
    end


  //cpu_0/data_master epcs_flash_controller_0/epcs_control_port arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = epcs_flash_controller_0_epcs_control_port_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //epcs_flash_controller_0_epcs_control_port_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign epcs_flash_controller_0_epcs_control_port_slavearbiterlockenable2 = |epcs_flash_controller_0_epcs_control_port_arb_share_counter_next_value;

  //cpu_0/data_master epcs_flash_controller_0/epcs_control_port arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = epcs_flash_controller_0_epcs_control_port_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //cpu_0/instruction_master epcs_flash_controller_0/epcs_control_port arbiterlock, which is an e_assign
  assign cpu_0_instruction_master_arbiterlock = epcs_flash_controller_0_epcs_control_port_slavearbiterlockenable & cpu_0_instruction_master_continuerequest;

  //cpu_0/instruction_master epcs_flash_controller_0/epcs_control_port arbiterlock2, which is an e_assign
  assign cpu_0_instruction_master_arbiterlock2 = epcs_flash_controller_0_epcs_control_port_slavearbiterlockenable2 & cpu_0_instruction_master_continuerequest;

  //cpu_0/instruction_master granted epcs_flash_controller_0/epcs_control_port last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_cpu_0_instruction_master_granted_slave_epcs_flash_controller_0_epcs_control_port <= 0;
      else 
        last_cycle_cpu_0_instruction_master_granted_slave_epcs_flash_controller_0_epcs_control_port <= cpu_0_instruction_master_saved_grant_epcs_flash_controller_0_epcs_control_port ? 1 : (epcs_flash_controller_0_epcs_control_port_arbitration_holdoff_internal | ~cpu_0_instruction_master_requests_epcs_flash_controller_0_epcs_control_port) ? 0 : last_cycle_cpu_0_instruction_master_granted_slave_epcs_flash_controller_0_epcs_control_port;
    end


  //cpu_0_instruction_master_continuerequest continued request, which is an e_mux
  assign cpu_0_instruction_master_continuerequest = last_cycle_cpu_0_instruction_master_granted_slave_epcs_flash_controller_0_epcs_control_port & cpu_0_instruction_master_requests_epcs_flash_controller_0_epcs_control_port;

  //epcs_flash_controller_0_epcs_control_port_any_continuerequest at least one master continues requesting, which is an e_mux
  assign epcs_flash_controller_0_epcs_control_port_any_continuerequest = cpu_0_instruction_master_continuerequest |
    cpu_0_data_master_continuerequest;

  assign cpu_0_data_master_qualified_request_epcs_flash_controller_0_epcs_control_port = cpu_0_data_master_requests_epcs_flash_controller_0_epcs_control_port & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))) | cpu_0_instruction_master_arbiterlock);
  //local readdatavalid cpu_0_data_master_read_data_valid_epcs_flash_controller_0_epcs_control_port, which is an e_mux
  assign cpu_0_data_master_read_data_valid_epcs_flash_controller_0_epcs_control_port = cpu_0_data_master_granted_epcs_flash_controller_0_epcs_control_port & cpu_0_data_master_read & ~epcs_flash_controller_0_epcs_control_port_waits_for_read;

  //epcs_flash_controller_0_epcs_control_port_writedata mux, which is an e_mux
  assign epcs_flash_controller_0_epcs_control_port_writedata = cpu_0_data_master_writedata;

  //assign epcs_flash_controller_0_epcs_control_port_endofpacket_from_sa = epcs_flash_controller_0_epcs_control_port_endofpacket so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign epcs_flash_controller_0_epcs_control_port_endofpacket_from_sa = epcs_flash_controller_0_epcs_control_port_endofpacket;

  assign cpu_0_instruction_master_requests_epcs_flash_controller_0_epcs_control_port = (({cpu_0_instruction_master_address_to_slave[26 : 11] , 11'b0} == 27'h4001800) & (cpu_0_instruction_master_read)) & cpu_0_instruction_master_read;
  //cpu_0/data_master granted epcs_flash_controller_0/epcs_control_port last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_cpu_0_data_master_granted_slave_epcs_flash_controller_0_epcs_control_port <= 0;
      else 
        last_cycle_cpu_0_data_master_granted_slave_epcs_flash_controller_0_epcs_control_port <= cpu_0_data_master_saved_grant_epcs_flash_controller_0_epcs_control_port ? 1 : (epcs_flash_controller_0_epcs_control_port_arbitration_holdoff_internal | ~cpu_0_data_master_requests_epcs_flash_controller_0_epcs_control_port) ? 0 : last_cycle_cpu_0_data_master_granted_slave_epcs_flash_controller_0_epcs_control_port;
    end


  //cpu_0_data_master_continuerequest continued request, which is an e_mux
  assign cpu_0_data_master_continuerequest = last_cycle_cpu_0_data_master_granted_slave_epcs_flash_controller_0_epcs_control_port & cpu_0_data_master_requests_epcs_flash_controller_0_epcs_control_port;

  assign cpu_0_instruction_master_qualified_request_epcs_flash_controller_0_epcs_control_port = cpu_0_instruction_master_requests_epcs_flash_controller_0_epcs_control_port & ~((cpu_0_instruction_master_read & ((cpu_0_instruction_master_latency_counter != 0) | (|cpu_0_instruction_master_read_data_valid_sdram_0_s1_shift_register))) | cpu_0_data_master_arbiterlock);
  //local readdatavalid cpu_0_instruction_master_read_data_valid_epcs_flash_controller_0_epcs_control_port, which is an e_mux
  assign cpu_0_instruction_master_read_data_valid_epcs_flash_controller_0_epcs_control_port = cpu_0_instruction_master_granted_epcs_flash_controller_0_epcs_control_port & cpu_0_instruction_master_read & ~epcs_flash_controller_0_epcs_control_port_waits_for_read;

  //allow new arb cycle for epcs_flash_controller_0/epcs_control_port, which is an e_assign
  assign epcs_flash_controller_0_epcs_control_port_allow_new_arb_cycle = ~cpu_0_data_master_arbiterlock & ~cpu_0_instruction_master_arbiterlock;

  //cpu_0/instruction_master assignment into master qualified-requests vector for epcs_flash_controller_0/epcs_control_port, which is an e_assign
  assign epcs_flash_controller_0_epcs_control_port_master_qreq_vector[0] = cpu_0_instruction_master_qualified_request_epcs_flash_controller_0_epcs_control_port;

  //cpu_0/instruction_master grant epcs_flash_controller_0/epcs_control_port, which is an e_assign
  assign cpu_0_instruction_master_granted_epcs_flash_controller_0_epcs_control_port = epcs_flash_controller_0_epcs_control_port_grant_vector[0];

  //cpu_0/instruction_master saved-grant epcs_flash_controller_0/epcs_control_port, which is an e_assign
  assign cpu_0_instruction_master_saved_grant_epcs_flash_controller_0_epcs_control_port = epcs_flash_controller_0_epcs_control_port_arb_winner[0] && cpu_0_instruction_master_requests_epcs_flash_controller_0_epcs_control_port;

  //cpu_0/data_master assignment into master qualified-requests vector for epcs_flash_controller_0/epcs_control_port, which is an e_assign
  assign epcs_flash_controller_0_epcs_control_port_master_qreq_vector[1] = cpu_0_data_master_qualified_request_epcs_flash_controller_0_epcs_control_port;

  //cpu_0/data_master grant epcs_flash_controller_0/epcs_control_port, which is an e_assign
  assign cpu_0_data_master_granted_epcs_flash_controller_0_epcs_control_port = epcs_flash_controller_0_epcs_control_port_grant_vector[1];

  //cpu_0/data_master saved-grant epcs_flash_controller_0/epcs_control_port, which is an e_assign
  assign cpu_0_data_master_saved_grant_epcs_flash_controller_0_epcs_control_port = epcs_flash_controller_0_epcs_control_port_arb_winner[1] && cpu_0_data_master_requests_epcs_flash_controller_0_epcs_control_port;

  //epcs_flash_controller_0/epcs_control_port chosen-master double-vector, which is an e_assign
  assign epcs_flash_controller_0_epcs_control_port_chosen_master_double_vector = {epcs_flash_controller_0_epcs_control_port_master_qreq_vector, epcs_flash_controller_0_epcs_control_port_master_qreq_vector} & ({~epcs_flash_controller_0_epcs_control_port_master_qreq_vector, ~epcs_flash_controller_0_epcs_control_port_master_qreq_vector} + epcs_flash_controller_0_epcs_control_port_arb_addend);

  //stable onehot encoding of arb winner
  assign epcs_flash_controller_0_epcs_control_port_arb_winner = (epcs_flash_controller_0_epcs_control_port_allow_new_arb_cycle & | epcs_flash_controller_0_epcs_control_port_grant_vector) ? epcs_flash_controller_0_epcs_control_port_grant_vector : epcs_flash_controller_0_epcs_control_port_saved_chosen_master_vector;

  //saved epcs_flash_controller_0_epcs_control_port_grant_vector, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          epcs_flash_controller_0_epcs_control_port_saved_chosen_master_vector <= 0;
      else if (epcs_flash_controller_0_epcs_control_port_allow_new_arb_cycle)
          epcs_flash_controller_0_epcs_control_port_saved_chosen_master_vector <= |epcs_flash_controller_0_epcs_control_port_grant_vector ? epcs_flash_controller_0_epcs_control_port_grant_vector : epcs_flash_controller_0_epcs_control_port_saved_chosen_master_vector;
    end


  //onehot encoding of chosen master
  assign epcs_flash_controller_0_epcs_control_port_grant_vector = {(epcs_flash_controller_0_epcs_control_port_chosen_master_double_vector[1] | epcs_flash_controller_0_epcs_control_port_chosen_master_double_vector[3]),
    (epcs_flash_controller_0_epcs_control_port_chosen_master_double_vector[0] | epcs_flash_controller_0_epcs_control_port_chosen_master_double_vector[2])};

  //epcs_flash_controller_0/epcs_control_port chosen master rotated left, which is an e_assign
  assign epcs_flash_controller_0_epcs_control_port_chosen_master_rot_left = (epcs_flash_controller_0_epcs_control_port_arb_winner << 1) ? (epcs_flash_controller_0_epcs_control_port_arb_winner << 1) : 1;

  //epcs_flash_controller_0/epcs_control_port's addend for next-master-grant
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          epcs_flash_controller_0_epcs_control_port_arb_addend <= 1;
      else if (|epcs_flash_controller_0_epcs_control_port_grant_vector)
          epcs_flash_controller_0_epcs_control_port_arb_addend <= epcs_flash_controller_0_epcs_control_port_end_xfer? epcs_flash_controller_0_epcs_control_port_chosen_master_rot_left : epcs_flash_controller_0_epcs_control_port_grant_vector;
    end


  //epcs_flash_controller_0_epcs_control_port_reset_n assignment, which is an e_assign
  assign epcs_flash_controller_0_epcs_control_port_reset_n = reset_n;

  assign epcs_flash_controller_0_epcs_control_port_chipselect = cpu_0_data_master_granted_epcs_flash_controller_0_epcs_control_port | cpu_0_instruction_master_granted_epcs_flash_controller_0_epcs_control_port;
  //epcs_flash_controller_0_epcs_control_port_firsttransfer first transaction, which is an e_assign
  assign epcs_flash_controller_0_epcs_control_port_firsttransfer = epcs_flash_controller_0_epcs_control_port_begins_xfer ? epcs_flash_controller_0_epcs_control_port_unreg_firsttransfer : epcs_flash_controller_0_epcs_control_port_reg_firsttransfer;

  //epcs_flash_controller_0_epcs_control_port_unreg_firsttransfer first transaction, which is an e_assign
  assign epcs_flash_controller_0_epcs_control_port_unreg_firsttransfer = ~(epcs_flash_controller_0_epcs_control_port_slavearbiterlockenable & epcs_flash_controller_0_epcs_control_port_any_continuerequest);

  //epcs_flash_controller_0_epcs_control_port_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          epcs_flash_controller_0_epcs_control_port_reg_firsttransfer <= 1'b1;
      else if (epcs_flash_controller_0_epcs_control_port_begins_xfer)
          epcs_flash_controller_0_epcs_control_port_reg_firsttransfer <= epcs_flash_controller_0_epcs_control_port_unreg_firsttransfer;
    end


  //epcs_flash_controller_0_epcs_control_port_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign epcs_flash_controller_0_epcs_control_port_beginbursttransfer_internal = epcs_flash_controller_0_epcs_control_port_begins_xfer;

  //epcs_flash_controller_0_epcs_control_port_arbitration_holdoff_internal arbitration_holdoff, which is an e_assign
  assign epcs_flash_controller_0_epcs_control_port_arbitration_holdoff_internal = epcs_flash_controller_0_epcs_control_port_begins_xfer & epcs_flash_controller_0_epcs_control_port_firsttransfer;

  //~epcs_flash_controller_0_epcs_control_port_read_n assignment, which is an e_mux
  assign epcs_flash_controller_0_epcs_control_port_read_n = ~((cpu_0_data_master_granted_epcs_flash_controller_0_epcs_control_port & cpu_0_data_master_read) | (cpu_0_instruction_master_granted_epcs_flash_controller_0_epcs_control_port & cpu_0_instruction_master_read));

  //~epcs_flash_controller_0_epcs_control_port_write_n assignment, which is an e_mux
  assign epcs_flash_controller_0_epcs_control_port_write_n = ~(cpu_0_data_master_granted_epcs_flash_controller_0_epcs_control_port & cpu_0_data_master_write);

  assign shifted_address_to_epcs_flash_controller_0_epcs_control_port_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //epcs_flash_controller_0_epcs_control_port_address mux, which is an e_mux
  assign epcs_flash_controller_0_epcs_control_port_address = (cpu_0_data_master_granted_epcs_flash_controller_0_epcs_control_port)? (shifted_address_to_epcs_flash_controller_0_epcs_control_port_from_cpu_0_data_master >> 2) :
    (shifted_address_to_epcs_flash_controller_0_epcs_control_port_from_cpu_0_instruction_master >> 2);

  assign shifted_address_to_epcs_flash_controller_0_epcs_control_port_from_cpu_0_instruction_master = cpu_0_instruction_master_address_to_slave;
  //d1_epcs_flash_controller_0_epcs_control_port_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_epcs_flash_controller_0_epcs_control_port_end_xfer <= 1;
      else 
        d1_epcs_flash_controller_0_epcs_control_port_end_xfer <= epcs_flash_controller_0_epcs_control_port_end_xfer;
    end


  //epcs_flash_controller_0_epcs_control_port_waits_for_read in a cycle, which is an e_mux
  assign epcs_flash_controller_0_epcs_control_port_waits_for_read = epcs_flash_controller_0_epcs_control_port_in_a_read_cycle & epcs_flash_controller_0_epcs_control_port_begins_xfer;

  //epcs_flash_controller_0_epcs_control_port_in_a_read_cycle assignment, which is an e_assign
  assign epcs_flash_controller_0_epcs_control_port_in_a_read_cycle = (cpu_0_data_master_granted_epcs_flash_controller_0_epcs_control_port & cpu_0_data_master_read) | (cpu_0_instruction_master_granted_epcs_flash_controller_0_epcs_control_port & cpu_0_instruction_master_read);

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = epcs_flash_controller_0_epcs_control_port_in_a_read_cycle;

  //epcs_flash_controller_0_epcs_control_port_waits_for_write in a cycle, which is an e_mux
  assign epcs_flash_controller_0_epcs_control_port_waits_for_write = epcs_flash_controller_0_epcs_control_port_in_a_write_cycle & epcs_flash_controller_0_epcs_control_port_begins_xfer;

  //epcs_flash_controller_0_epcs_control_port_in_a_write_cycle assignment, which is an e_assign
  assign epcs_flash_controller_0_epcs_control_port_in_a_write_cycle = cpu_0_data_master_granted_epcs_flash_controller_0_epcs_control_port & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = epcs_flash_controller_0_epcs_control_port_in_a_write_cycle;

  assign wait_for_epcs_flash_controller_0_epcs_control_port_counter = 0;
  //assign epcs_flash_controller_0_epcs_control_port_irq_from_sa = epcs_flash_controller_0_epcs_control_port_irq so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign epcs_flash_controller_0_epcs_control_port_irq_from_sa = epcs_flash_controller_0_epcs_control_port_irq;


//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //epcs_flash_controller_0/epcs_control_port enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end


  //grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (cpu_0_data_master_granted_epcs_flash_controller_0_epcs_control_port + cpu_0_instruction_master_granted_epcs_flash_controller_0_epcs_control_port > 1)
        begin
          $write("%0d ns: > 1 of grant signals are active simultaneously", $time);
          $stop;
        end
    end


  //saved_grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (cpu_0_data_master_saved_grant_epcs_flash_controller_0_epcs_control_port + cpu_0_instruction_master_saved_grant_epcs_flash_controller_0_epcs_control_port > 1)
        begin
          $write("%0d ns: > 1 of saved_grant signals are active simultaneously", $time);
          $stop;
        end
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module rdv_fifo_for_cpu_0_data_master_to_sdram_0_s1_module (
                                                             // inputs:
                                                              clear_fifo,
                                                              clk,
                                                              data_in,
                                                              read,
                                                              reset_n,
                                                              sync_reset,
                                                              write,

                                                             // outputs:
                                                              data_out,
                                                              empty,
                                                              fifo_contains_ones_n,
                                                              full
                                                           )
;

  output           data_out;
  output           empty;
  output           fifo_contains_ones_n;
  output           full;
  input            clear_fifo;
  input            clk;
  input            data_in;
  input            read;
  input            reset_n;
  input            sync_reset;
  input            write;

  wire             data_out;
  wire             empty;
  reg              fifo_contains_ones_n;
  wire             full;
  reg              full_0;
  reg              full_1;
  reg              full_2;
  reg              full_3;
  reg              full_4;
  reg              full_5;
  reg              full_6;
  wire             full_7;
  reg     [  3: 0] how_many_ones;
  wire    [  3: 0] one_count_minus_one;
  wire    [  3: 0] one_count_plus_one;
  wire             p0_full_0;
  wire             p0_stage_0;
  wire             p1_full_1;
  wire             p1_stage_1;
  wire             p2_full_2;
  wire             p2_stage_2;
  wire             p3_full_3;
  wire             p3_stage_3;
  wire             p4_full_4;
  wire             p4_stage_4;
  wire             p5_full_5;
  wire             p5_stage_5;
  wire             p6_full_6;
  wire             p6_stage_6;
  reg              stage_0;
  reg              stage_1;
  reg              stage_2;
  reg              stage_3;
  reg              stage_4;
  reg              stage_5;
  reg              stage_6;
  wire    [  3: 0] updated_one_count;
  assign data_out = stage_0;
  assign full = full_6;
  assign empty = !full_0;
  assign full_7 = 0;
  //data_6, which is an e_mux
  assign p6_stage_6 = ((full_7 & ~clear_fifo) == 0)? data_in :
    data_in;

  //data_reg_6, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          stage_6 <= 0;
      else if (clear_fifo | sync_reset | read | (write & !full_6))
          if (sync_reset & full_6 & !((full_7 == 0) & read & write))
              stage_6 <= 0;
          else 
            stage_6 <= p6_stage_6;
    end


  //control_6, which is an e_mux
  assign p6_full_6 = ((read & !write) == 0)? full_5 :
    0;

  //control_reg_6, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          full_6 <= 0;
      else if (clear_fifo | (read ^ write) | (write & !full_0))
          if (clear_fifo)
              full_6 <= 0;
          else 
            full_6 <= p6_full_6;
    end


  //data_5, which is an e_mux
  assign p5_stage_5 = ((full_6 & ~clear_fifo) == 0)? data_in :
    stage_6;

  //data_reg_5, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          stage_5 <= 0;
      else if (clear_fifo | sync_reset | read | (write & !full_5))
          if (sync_reset & full_5 & !((full_6 == 0) & read & write))
              stage_5 <= 0;
          else 
            stage_5 <= p5_stage_5;
    end


  //control_5, which is an e_mux
  assign p5_full_5 = ((read & !write) == 0)? full_4 :
    full_6;

  //control_reg_5, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          full_5 <= 0;
      else if (clear_fifo | (read ^ write) | (write & !full_0))
          if (clear_fifo)
              full_5 <= 0;
          else 
            full_5 <= p5_full_5;
    end


  //data_4, which is an e_mux
  assign p4_stage_4 = ((full_5 & ~clear_fifo) == 0)? data_in :
    stage_5;

  //data_reg_4, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          stage_4 <= 0;
      else if (clear_fifo | sync_reset | read | (write & !full_4))
          if (sync_reset & full_4 & !((full_5 == 0) & read & write))
              stage_4 <= 0;
          else 
            stage_4 <= p4_stage_4;
    end


  //control_4, which is an e_mux
  assign p4_full_4 = ((read & !write) == 0)? full_3 :
    full_5;

  //control_reg_4, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          full_4 <= 0;
      else if (clear_fifo | (read ^ write) | (write & !full_0))
          if (clear_fifo)
              full_4 <= 0;
          else 
            full_4 <= p4_full_4;
    end


  //data_3, which is an e_mux
  assign p3_stage_3 = ((full_4 & ~clear_fifo) == 0)? data_in :
    stage_4;

  //data_reg_3, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          stage_3 <= 0;
      else if (clear_fifo | sync_reset | read | (write & !full_3))
          if (sync_reset & full_3 & !((full_4 == 0) & read & write))
              stage_3 <= 0;
          else 
            stage_3 <= p3_stage_3;
    end


  //control_3, which is an e_mux
  assign p3_full_3 = ((read & !write) == 0)? full_2 :
    full_4;

  //control_reg_3, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          full_3 <= 0;
      else if (clear_fifo | (read ^ write) | (write & !full_0))
          if (clear_fifo)
              full_3 <= 0;
          else 
            full_3 <= p3_full_3;
    end


  //data_2, which is an e_mux
  assign p2_stage_2 = ((full_3 & ~clear_fifo) == 0)? data_in :
    stage_3;

  //data_reg_2, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          stage_2 <= 0;
      else if (clear_fifo | sync_reset | read | (write & !full_2))
          if (sync_reset & full_2 & !((full_3 == 0) & read & write))
              stage_2 <= 0;
          else 
            stage_2 <= p2_stage_2;
    end


  //control_2, which is an e_mux
  assign p2_full_2 = ((read & !write) == 0)? full_1 :
    full_3;

  //control_reg_2, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          full_2 <= 0;
      else if (clear_fifo | (read ^ write) | (write & !full_0))
          if (clear_fifo)
              full_2 <= 0;
          else 
            full_2 <= p2_full_2;
    end


  //data_1, which is an e_mux
  assign p1_stage_1 = ((full_2 & ~clear_fifo) == 0)? data_in :
    stage_2;

  //data_reg_1, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          stage_1 <= 0;
      else if (clear_fifo | sync_reset | read | (write & !full_1))
          if (sync_reset & full_1 & !((full_2 == 0) & read & write))
              stage_1 <= 0;
          else 
            stage_1 <= p1_stage_1;
    end


  //control_1, which is an e_mux
  assign p1_full_1 = ((read & !write) == 0)? full_0 :
    full_2;

  //control_reg_1, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          full_1 <= 0;
      else if (clear_fifo | (read ^ write) | (write & !full_0))
          if (clear_fifo)
              full_1 <= 0;
          else 
            full_1 <= p1_full_1;
    end


  //data_0, which is an e_mux
  assign p0_stage_0 = ((full_1 & ~clear_fifo) == 0)? data_in :
    stage_1;

  //data_reg_0, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          stage_0 <= 0;
      else if (clear_fifo | sync_reset | read | (write & !full_0))
          if (sync_reset & full_0 & !((full_1 == 0) & read & write))
              stage_0 <= 0;
          else 
            stage_0 <= p0_stage_0;
    end


  //control_0, which is an e_mux
  assign p0_full_0 = ((read & !write) == 0)? 1 :
    full_1;

  //control_reg_0, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          full_0 <= 0;
      else if (clear_fifo | (read ^ write) | (write & !full_0))
          if (clear_fifo & ~write)
              full_0 <= 0;
          else 
            full_0 <= p0_full_0;
    end


  assign one_count_plus_one = how_many_ones + 1;
  assign one_count_minus_one = how_many_ones - 1;
  //updated_one_count, which is an e_mux
  assign updated_one_count = ((((clear_fifo | sync_reset) & !write)))? 0 :
    ((((clear_fifo | sync_reset) & write)))? |data_in :
    ((read & (|data_in) & write & (|stage_0)))? how_many_ones :
    ((write & (|data_in)))? one_count_plus_one :
    ((read & (|stage_0)))? one_count_minus_one :
    how_many_ones;

  //counts how many ones in the data pipeline, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          how_many_ones <= 0;
      else if (clear_fifo | sync_reset | read | write)
          how_many_ones <= updated_one_count;
    end


  //this fifo contains ones in the data pipeline, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          fifo_contains_ones_n <= 1;
      else if (clear_fifo | sync_reset | read | write)
          fifo_contains_ones_n <= ~(|updated_one_count);
    end



endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module rdv_fifo_for_cpu_0_instruction_master_to_sdram_0_s1_module (
                                                                    // inputs:
                                                                     clear_fifo,
                                                                     clk,
                                                                     data_in,
                                                                     read,
                                                                     reset_n,
                                                                     sync_reset,
                                                                     write,

                                                                    // outputs:
                                                                     data_out,
                                                                     empty,
                                                                     fifo_contains_ones_n,
                                                                     full
                                                                  )
;

  output           data_out;
  output           empty;
  output           fifo_contains_ones_n;
  output           full;
  input            clear_fifo;
  input            clk;
  input            data_in;
  input            read;
  input            reset_n;
  input            sync_reset;
  input            write;

  wire             data_out;
  wire             empty;
  reg              fifo_contains_ones_n;
  wire             full;
  reg              full_0;
  reg              full_1;
  reg              full_2;
  reg              full_3;
  reg              full_4;
  reg              full_5;
  reg              full_6;
  wire             full_7;
  reg     [  3: 0] how_many_ones;
  wire    [  3: 0] one_count_minus_one;
  wire    [  3: 0] one_count_plus_one;
  wire             p0_full_0;
  wire             p0_stage_0;
  wire             p1_full_1;
  wire             p1_stage_1;
  wire             p2_full_2;
  wire             p2_stage_2;
  wire             p3_full_3;
  wire             p3_stage_3;
  wire             p4_full_4;
  wire             p4_stage_4;
  wire             p5_full_5;
  wire             p5_stage_5;
  wire             p6_full_6;
  wire             p6_stage_6;
  reg              stage_0;
  reg              stage_1;
  reg              stage_2;
  reg              stage_3;
  reg              stage_4;
  reg              stage_5;
  reg              stage_6;
  wire    [  3: 0] updated_one_count;
  assign data_out = stage_0;
  assign full = full_6;
  assign empty = !full_0;
  assign full_7 = 0;
  //data_6, which is an e_mux
  assign p6_stage_6 = ((full_7 & ~clear_fifo) == 0)? data_in :
    data_in;

  //data_reg_6, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          stage_6 <= 0;
      else if (clear_fifo | sync_reset | read | (write & !full_6))
          if (sync_reset & full_6 & !((full_7 == 0) & read & write))
              stage_6 <= 0;
          else 
            stage_6 <= p6_stage_6;
    end


  //control_6, which is an e_mux
  assign p6_full_6 = ((read & !write) == 0)? full_5 :
    0;

  //control_reg_6, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          full_6 <= 0;
      else if (clear_fifo | (read ^ write) | (write & !full_0))
          if (clear_fifo)
              full_6 <= 0;
          else 
            full_6 <= p6_full_6;
    end


  //data_5, which is an e_mux
  assign p5_stage_5 = ((full_6 & ~clear_fifo) == 0)? data_in :
    stage_6;

  //data_reg_5, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          stage_5 <= 0;
      else if (clear_fifo | sync_reset | read | (write & !full_5))
          if (sync_reset & full_5 & !((full_6 == 0) & read & write))
              stage_5 <= 0;
          else 
            stage_5 <= p5_stage_5;
    end


  //control_5, which is an e_mux
  assign p5_full_5 = ((read & !write) == 0)? full_4 :
    full_6;

  //control_reg_5, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          full_5 <= 0;
      else if (clear_fifo | (read ^ write) | (write & !full_0))
          if (clear_fifo)
              full_5 <= 0;
          else 
            full_5 <= p5_full_5;
    end


  //data_4, which is an e_mux
  assign p4_stage_4 = ((full_5 & ~clear_fifo) == 0)? data_in :
    stage_5;

  //data_reg_4, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          stage_4 <= 0;
      else if (clear_fifo | sync_reset | read | (write & !full_4))
          if (sync_reset & full_4 & !((full_5 == 0) & read & write))
              stage_4 <= 0;
          else 
            stage_4 <= p4_stage_4;
    end


  //control_4, which is an e_mux
  assign p4_full_4 = ((read & !write) == 0)? full_3 :
    full_5;

  //control_reg_4, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          full_4 <= 0;
      else if (clear_fifo | (read ^ write) | (write & !full_0))
          if (clear_fifo)
              full_4 <= 0;
          else 
            full_4 <= p4_full_4;
    end


  //data_3, which is an e_mux
  assign p3_stage_3 = ((full_4 & ~clear_fifo) == 0)? data_in :
    stage_4;

  //data_reg_3, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          stage_3 <= 0;
      else if (clear_fifo | sync_reset | read | (write & !full_3))
          if (sync_reset & full_3 & !((full_4 == 0) & read & write))
              stage_3 <= 0;
          else 
            stage_3 <= p3_stage_3;
    end


  //control_3, which is an e_mux
  assign p3_full_3 = ((read & !write) == 0)? full_2 :
    full_4;

  //control_reg_3, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          full_3 <= 0;
      else if (clear_fifo | (read ^ write) | (write & !full_0))
          if (clear_fifo)
              full_3 <= 0;
          else 
            full_3 <= p3_full_3;
    end


  //data_2, which is an e_mux
  assign p2_stage_2 = ((full_3 & ~clear_fifo) == 0)? data_in :
    stage_3;

  //data_reg_2, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          stage_2 <= 0;
      else if (clear_fifo | sync_reset | read | (write & !full_2))
          if (sync_reset & full_2 & !((full_3 == 0) & read & write))
              stage_2 <= 0;
          else 
            stage_2 <= p2_stage_2;
    end


  //control_2, which is an e_mux
  assign p2_full_2 = ((read & !write) == 0)? full_1 :
    full_3;

  //control_reg_2, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          full_2 <= 0;
      else if (clear_fifo | (read ^ write) | (write & !full_0))
          if (clear_fifo)
              full_2 <= 0;
          else 
            full_2 <= p2_full_2;
    end


  //data_1, which is an e_mux
  assign p1_stage_1 = ((full_2 & ~clear_fifo) == 0)? data_in :
    stage_2;

  //data_reg_1, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          stage_1 <= 0;
      else if (clear_fifo | sync_reset | read | (write & !full_1))
          if (sync_reset & full_1 & !((full_2 == 0) & read & write))
              stage_1 <= 0;
          else 
            stage_1 <= p1_stage_1;
    end


  //control_1, which is an e_mux
  assign p1_full_1 = ((read & !write) == 0)? full_0 :
    full_2;

  //control_reg_1, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          full_1 <= 0;
      else if (clear_fifo | (read ^ write) | (write & !full_0))
          if (clear_fifo)
              full_1 <= 0;
          else 
            full_1 <= p1_full_1;
    end


  //data_0, which is an e_mux
  assign p0_stage_0 = ((full_1 & ~clear_fifo) == 0)? data_in :
    stage_1;

  //data_reg_0, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          stage_0 <= 0;
      else if (clear_fifo | sync_reset | read | (write & !full_0))
          if (sync_reset & full_0 & !((full_1 == 0) & read & write))
              stage_0 <= 0;
          else 
            stage_0 <= p0_stage_0;
    end


  //control_0, which is an e_mux
  assign p0_full_0 = ((read & !write) == 0)? 1 :
    full_1;

  //control_reg_0, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          full_0 <= 0;
      else if (clear_fifo | (read ^ write) | (write & !full_0))
          if (clear_fifo & ~write)
              full_0 <= 0;
          else 
            full_0 <= p0_full_0;
    end


  assign one_count_plus_one = how_many_ones + 1;
  assign one_count_minus_one = how_many_ones - 1;
  //updated_one_count, which is an e_mux
  assign updated_one_count = ((((clear_fifo | sync_reset) & !write)))? 0 :
    ((((clear_fifo | sync_reset) & write)))? |data_in :
    ((read & (|data_in) & write & (|stage_0)))? how_many_ones :
    ((write & (|data_in)))? one_count_plus_one :
    ((read & (|stage_0)))? one_count_minus_one :
    how_many_ones;

  //counts how many ones in the data pipeline, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          how_many_ones <= 0;
      else if (clear_fifo | sync_reset | read | write)
          how_many_ones <= updated_one_count;
    end


  //this fifo contains ones in the data pipeline, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          fifo_contains_ones_n <= 1;
      else if (clear_fifo | sync_reset | read | write)
          fifo_contains_ones_n <= ~(|updated_one_count);
    end



endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module sdram_0_s1_arbitrator (
                               // inputs:
                                clk,
                                cpu_0_data_master_address_to_slave,
                                cpu_0_data_master_byteenable,
                                cpu_0_data_master_dbs_address,
                                cpu_0_data_master_dbs_write_16,
                                cpu_0_data_master_latency_counter,
                                cpu_0_data_master_read,
                                cpu_0_data_master_write,
                                cpu_0_instruction_master_address_to_slave,
                                cpu_0_instruction_master_dbs_address,
                                cpu_0_instruction_master_latency_counter,
                                cpu_0_instruction_master_read,
                                reset_n,
                                sdram_0_s1_readdata,
                                sdram_0_s1_readdatavalid,
                                sdram_0_s1_waitrequest,

                               // outputs:
                                cpu_0_data_master_byteenable_sdram_0_s1,
                                cpu_0_data_master_granted_sdram_0_s1,
                                cpu_0_data_master_qualified_request_sdram_0_s1,
                                cpu_0_data_master_read_data_valid_sdram_0_s1,
                                cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                cpu_0_data_master_requests_sdram_0_s1,
                                cpu_0_instruction_master_granted_sdram_0_s1,
                                cpu_0_instruction_master_qualified_request_sdram_0_s1,
                                cpu_0_instruction_master_read_data_valid_sdram_0_s1,
                                cpu_0_instruction_master_read_data_valid_sdram_0_s1_shift_register,
                                cpu_0_instruction_master_requests_sdram_0_s1,
                                d1_sdram_0_s1_end_xfer,
                                sdram_0_s1_address,
                                sdram_0_s1_byteenable_n,
                                sdram_0_s1_chipselect,
                                sdram_0_s1_read_n,
                                sdram_0_s1_readdata_from_sa,
                                sdram_0_s1_reset_n,
                                sdram_0_s1_waitrequest_from_sa,
                                sdram_0_s1_write_n,
                                sdram_0_s1_writedata
                             )
;

  output  [  1: 0] cpu_0_data_master_byteenable_sdram_0_s1;
  output           cpu_0_data_master_granted_sdram_0_s1;
  output           cpu_0_data_master_qualified_request_sdram_0_s1;
  output           cpu_0_data_master_read_data_valid_sdram_0_s1;
  output           cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  output           cpu_0_data_master_requests_sdram_0_s1;
  output           cpu_0_instruction_master_granted_sdram_0_s1;
  output           cpu_0_instruction_master_qualified_request_sdram_0_s1;
  output           cpu_0_instruction_master_read_data_valid_sdram_0_s1;
  output           cpu_0_instruction_master_read_data_valid_sdram_0_s1_shift_register;
  output           cpu_0_instruction_master_requests_sdram_0_s1;
  output           d1_sdram_0_s1_end_xfer;
  output  [ 23: 0] sdram_0_s1_address;
  output  [  1: 0] sdram_0_s1_byteenable_n;
  output           sdram_0_s1_chipselect;
  output           sdram_0_s1_read_n;
  output  [ 15: 0] sdram_0_s1_readdata_from_sa;
  output           sdram_0_s1_reset_n;
  output           sdram_0_s1_waitrequest_from_sa;
  output           sdram_0_s1_write_n;
  output  [ 15: 0] sdram_0_s1_writedata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input   [  3: 0] cpu_0_data_master_byteenable;
  input   [  1: 0] cpu_0_data_master_dbs_address;
  input   [ 15: 0] cpu_0_data_master_dbs_write_16;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_write;
  input   [ 26: 0] cpu_0_instruction_master_address_to_slave;
  input   [  1: 0] cpu_0_instruction_master_dbs_address;
  input            cpu_0_instruction_master_latency_counter;
  input            cpu_0_instruction_master_read;
  input            reset_n;
  input   [ 15: 0] sdram_0_s1_readdata;
  input            sdram_0_s1_readdatavalid;
  input            sdram_0_s1_waitrequest;

  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire    [  1: 0] cpu_0_data_master_byteenable_sdram_0_s1;
  wire    [  1: 0] cpu_0_data_master_byteenable_sdram_0_s1_segment_0;
  wire    [  1: 0] cpu_0_data_master_byteenable_sdram_0_s1_segment_1;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_sdram_0_s1;
  wire             cpu_0_data_master_qualified_request_sdram_0_s1;
  wire             cpu_0_data_master_rdv_fifo_empty_sdram_0_s1;
  wire             cpu_0_data_master_rdv_fifo_output_from_sdram_0_s1;
  wire             cpu_0_data_master_read_data_valid_sdram_0_s1;
  wire             cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  wire             cpu_0_data_master_requests_sdram_0_s1;
  wire             cpu_0_data_master_saved_grant_sdram_0_s1;
  wire             cpu_0_instruction_master_arbiterlock;
  wire             cpu_0_instruction_master_arbiterlock2;
  wire             cpu_0_instruction_master_continuerequest;
  wire             cpu_0_instruction_master_granted_sdram_0_s1;
  wire             cpu_0_instruction_master_qualified_request_sdram_0_s1;
  wire             cpu_0_instruction_master_rdv_fifo_empty_sdram_0_s1;
  wire             cpu_0_instruction_master_rdv_fifo_output_from_sdram_0_s1;
  wire             cpu_0_instruction_master_read_data_valid_sdram_0_s1;
  wire             cpu_0_instruction_master_read_data_valid_sdram_0_s1_shift_register;
  wire             cpu_0_instruction_master_requests_sdram_0_s1;
  wire             cpu_0_instruction_master_saved_grant_sdram_0_s1;
  reg              d1_reasons_to_wait;
  reg              d1_sdram_0_s1_end_xfer;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_sdram_0_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  reg              last_cycle_cpu_0_data_master_granted_slave_sdram_0_s1;
  reg              last_cycle_cpu_0_instruction_master_granted_slave_sdram_0_s1;
  wire    [ 23: 0] sdram_0_s1_address;
  wire             sdram_0_s1_allgrants;
  wire             sdram_0_s1_allow_new_arb_cycle;
  wire             sdram_0_s1_any_bursting_master_saved_grant;
  wire             sdram_0_s1_any_continuerequest;
  reg     [  1: 0] sdram_0_s1_arb_addend;
  wire             sdram_0_s1_arb_counter_enable;
  reg     [  1: 0] sdram_0_s1_arb_share_counter;
  wire    [  1: 0] sdram_0_s1_arb_share_counter_next_value;
  wire    [  1: 0] sdram_0_s1_arb_share_set_values;
  wire    [  1: 0] sdram_0_s1_arb_winner;
  wire             sdram_0_s1_arbitration_holdoff_internal;
  wire             sdram_0_s1_beginbursttransfer_internal;
  wire             sdram_0_s1_begins_xfer;
  wire    [  1: 0] sdram_0_s1_byteenable_n;
  wire             sdram_0_s1_chipselect;
  wire    [  3: 0] sdram_0_s1_chosen_master_double_vector;
  wire    [  1: 0] sdram_0_s1_chosen_master_rot_left;
  wire             sdram_0_s1_end_xfer;
  wire             sdram_0_s1_firsttransfer;
  wire    [  1: 0] sdram_0_s1_grant_vector;
  wire             sdram_0_s1_in_a_read_cycle;
  wire             sdram_0_s1_in_a_write_cycle;
  wire    [  1: 0] sdram_0_s1_master_qreq_vector;
  wire             sdram_0_s1_move_on_to_next_transaction;
  wire             sdram_0_s1_non_bursting_master_requests;
  wire             sdram_0_s1_read_n;
  wire    [ 15: 0] sdram_0_s1_readdata_from_sa;
  wire             sdram_0_s1_readdatavalid_from_sa;
  reg              sdram_0_s1_reg_firsttransfer;
  wire             sdram_0_s1_reset_n;
  reg     [  1: 0] sdram_0_s1_saved_chosen_master_vector;
  reg              sdram_0_s1_slavearbiterlockenable;
  wire             sdram_0_s1_slavearbiterlockenable2;
  wire             sdram_0_s1_unreg_firsttransfer;
  wire             sdram_0_s1_waitrequest_from_sa;
  wire             sdram_0_s1_waits_for_read;
  wire             sdram_0_s1_waits_for_write;
  wire             sdram_0_s1_write_n;
  wire    [ 15: 0] sdram_0_s1_writedata;
  wire    [ 26: 0] shifted_address_to_sdram_0_s1_from_cpu_0_data_master;
  wire    [ 26: 0] shifted_address_to_sdram_0_s1_from_cpu_0_instruction_master;
  wire             wait_for_sdram_0_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~sdram_0_s1_end_xfer;
    end


  assign sdram_0_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_sdram_0_s1 | cpu_0_instruction_master_qualified_request_sdram_0_s1));
  //assign sdram_0_s1_readdatavalid_from_sa = sdram_0_s1_readdatavalid so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign sdram_0_s1_readdatavalid_from_sa = sdram_0_s1_readdatavalid;

  //assign sdram_0_s1_readdata_from_sa = sdram_0_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign sdram_0_s1_readdata_from_sa = sdram_0_s1_readdata;

  assign cpu_0_data_master_requests_sdram_0_s1 = ({cpu_0_data_master_address_to_slave[26 : 25] , 25'b0} == 27'h2000000) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //assign sdram_0_s1_waitrequest_from_sa = sdram_0_s1_waitrequest so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign sdram_0_s1_waitrequest_from_sa = sdram_0_s1_waitrequest;

  //sdram_0_s1_arb_share_counter set values, which is an e_mux
  assign sdram_0_s1_arb_share_set_values = (cpu_0_data_master_granted_sdram_0_s1)? 2 :
    (cpu_0_instruction_master_granted_sdram_0_s1)? 2 :
    (cpu_0_data_master_granted_sdram_0_s1)? 2 :
    (cpu_0_instruction_master_granted_sdram_0_s1)? 2 :
    1;

  //sdram_0_s1_non_bursting_master_requests mux, which is an e_mux
  assign sdram_0_s1_non_bursting_master_requests = cpu_0_data_master_requests_sdram_0_s1 |
    cpu_0_instruction_master_requests_sdram_0_s1 |
    cpu_0_data_master_requests_sdram_0_s1 |
    cpu_0_instruction_master_requests_sdram_0_s1;

  //sdram_0_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign sdram_0_s1_any_bursting_master_saved_grant = 0;

  //sdram_0_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign sdram_0_s1_arb_share_counter_next_value = sdram_0_s1_firsttransfer ? (sdram_0_s1_arb_share_set_values - 1) : |sdram_0_s1_arb_share_counter ? (sdram_0_s1_arb_share_counter - 1) : 0;

  //sdram_0_s1_allgrants all slave grants, which is an e_mux
  assign sdram_0_s1_allgrants = (|sdram_0_s1_grant_vector) |
    (|sdram_0_s1_grant_vector) |
    (|sdram_0_s1_grant_vector) |
    (|sdram_0_s1_grant_vector);

  //sdram_0_s1_end_xfer assignment, which is an e_assign
  assign sdram_0_s1_end_xfer = ~(sdram_0_s1_waits_for_read | sdram_0_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_sdram_0_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_sdram_0_s1 = sdram_0_s1_end_xfer & (~sdram_0_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //sdram_0_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign sdram_0_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_sdram_0_s1 & sdram_0_s1_allgrants) | (end_xfer_arb_share_counter_term_sdram_0_s1 & ~sdram_0_s1_non_bursting_master_requests);

  //sdram_0_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          sdram_0_s1_arb_share_counter <= 0;
      else if (sdram_0_s1_arb_counter_enable)
          sdram_0_s1_arb_share_counter <= sdram_0_s1_arb_share_counter_next_value;
    end


  //sdram_0_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          sdram_0_s1_slavearbiterlockenable <= 0;
      else if ((|sdram_0_s1_master_qreq_vector & end_xfer_arb_share_counter_term_sdram_0_s1) | (end_xfer_arb_share_counter_term_sdram_0_s1 & ~sdram_0_s1_non_bursting_master_requests))
          sdram_0_s1_slavearbiterlockenable <= |sdram_0_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master sdram_0/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = sdram_0_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //sdram_0_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign sdram_0_s1_slavearbiterlockenable2 = |sdram_0_s1_arb_share_counter_next_value;

  //cpu_0/data_master sdram_0/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = sdram_0_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //cpu_0/instruction_master sdram_0/s1 arbiterlock, which is an e_assign
  assign cpu_0_instruction_master_arbiterlock = sdram_0_s1_slavearbiterlockenable & cpu_0_instruction_master_continuerequest;

  //cpu_0/instruction_master sdram_0/s1 arbiterlock2, which is an e_assign
  assign cpu_0_instruction_master_arbiterlock2 = sdram_0_s1_slavearbiterlockenable2 & cpu_0_instruction_master_continuerequest;

  //cpu_0/instruction_master granted sdram_0/s1 last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_cpu_0_instruction_master_granted_slave_sdram_0_s1 <= 0;
      else 
        last_cycle_cpu_0_instruction_master_granted_slave_sdram_0_s1 <= cpu_0_instruction_master_saved_grant_sdram_0_s1 ? 1 : (sdram_0_s1_arbitration_holdoff_internal | ~cpu_0_instruction_master_requests_sdram_0_s1) ? 0 : last_cycle_cpu_0_instruction_master_granted_slave_sdram_0_s1;
    end


  //cpu_0_instruction_master_continuerequest continued request, which is an e_mux
  assign cpu_0_instruction_master_continuerequest = last_cycle_cpu_0_instruction_master_granted_slave_sdram_0_s1 & cpu_0_instruction_master_requests_sdram_0_s1;

  //sdram_0_s1_any_continuerequest at least one master continues requesting, which is an e_mux
  assign sdram_0_s1_any_continuerequest = cpu_0_instruction_master_continuerequest |
    cpu_0_data_master_continuerequest;

  assign cpu_0_data_master_qualified_request_sdram_0_s1 = cpu_0_data_master_requests_sdram_0_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (1 < cpu_0_data_master_latency_counter))) | ((!cpu_0_data_master_byteenable_sdram_0_s1) & cpu_0_data_master_write) | cpu_0_instruction_master_arbiterlock);
  //unique name for sdram_0_s1_move_on_to_next_transaction, which is an e_assign
  assign sdram_0_s1_move_on_to_next_transaction = sdram_0_s1_readdatavalid_from_sa;

  //rdv_fifo_for_cpu_0_data_master_to_sdram_0_s1, which is an e_fifo_with_registered_outputs
  rdv_fifo_for_cpu_0_data_master_to_sdram_0_s1_module rdv_fifo_for_cpu_0_data_master_to_sdram_0_s1
    (
      .clear_fifo           (1'b0),
      .clk                  (clk),
      .data_in              (cpu_0_data_master_granted_sdram_0_s1),
      .data_out             (cpu_0_data_master_rdv_fifo_output_from_sdram_0_s1),
      .empty                (),
      .fifo_contains_ones_n (cpu_0_data_master_rdv_fifo_empty_sdram_0_s1),
      .full                 (),
      .read                 (sdram_0_s1_move_on_to_next_transaction),
      .reset_n              (reset_n),
      .sync_reset           (1'b0),
      .write                (in_a_read_cycle & ~sdram_0_s1_waits_for_read)
    );

  assign cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register = ~cpu_0_data_master_rdv_fifo_empty_sdram_0_s1;
  //local readdatavalid cpu_0_data_master_read_data_valid_sdram_0_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_sdram_0_s1 = (sdram_0_s1_readdatavalid_from_sa & cpu_0_data_master_rdv_fifo_output_from_sdram_0_s1) & ~ cpu_0_data_master_rdv_fifo_empty_sdram_0_s1;

  //sdram_0_s1_writedata mux, which is an e_mux
  assign sdram_0_s1_writedata = cpu_0_data_master_dbs_write_16;

  assign cpu_0_instruction_master_requests_sdram_0_s1 = (({cpu_0_instruction_master_address_to_slave[26 : 25] , 25'b0} == 27'h2000000) & (cpu_0_instruction_master_read)) & cpu_0_instruction_master_read;
  //cpu_0/data_master granted sdram_0/s1 last time, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          last_cycle_cpu_0_data_master_granted_slave_sdram_0_s1 <= 0;
      else 
        last_cycle_cpu_0_data_master_granted_slave_sdram_0_s1 <= cpu_0_data_master_saved_grant_sdram_0_s1 ? 1 : (sdram_0_s1_arbitration_holdoff_internal | ~cpu_0_data_master_requests_sdram_0_s1) ? 0 : last_cycle_cpu_0_data_master_granted_slave_sdram_0_s1;
    end


  //cpu_0_data_master_continuerequest continued request, which is an e_mux
  assign cpu_0_data_master_continuerequest = last_cycle_cpu_0_data_master_granted_slave_sdram_0_s1 & cpu_0_data_master_requests_sdram_0_s1;

  assign cpu_0_instruction_master_qualified_request_sdram_0_s1 = cpu_0_instruction_master_requests_sdram_0_s1 & ~((cpu_0_instruction_master_read & ((cpu_0_instruction_master_latency_counter != 0) | (1 < cpu_0_instruction_master_latency_counter))) | cpu_0_data_master_arbiterlock);
  //rdv_fifo_for_cpu_0_instruction_master_to_sdram_0_s1, which is an e_fifo_with_registered_outputs
  rdv_fifo_for_cpu_0_instruction_master_to_sdram_0_s1_module rdv_fifo_for_cpu_0_instruction_master_to_sdram_0_s1
    (
      .clear_fifo           (1'b0),
      .clk                  (clk),
      .data_in              (cpu_0_instruction_master_granted_sdram_0_s1),
      .data_out             (cpu_0_instruction_master_rdv_fifo_output_from_sdram_0_s1),
      .empty                (),
      .fifo_contains_ones_n (cpu_0_instruction_master_rdv_fifo_empty_sdram_0_s1),
      .full                 (),
      .read                 (sdram_0_s1_move_on_to_next_transaction),
      .reset_n              (reset_n),
      .sync_reset           (1'b0),
      .write                (in_a_read_cycle & ~sdram_0_s1_waits_for_read)
    );

  assign cpu_0_instruction_master_read_data_valid_sdram_0_s1_shift_register = ~cpu_0_instruction_master_rdv_fifo_empty_sdram_0_s1;
  //local readdatavalid cpu_0_instruction_master_read_data_valid_sdram_0_s1, which is an e_mux
  assign cpu_0_instruction_master_read_data_valid_sdram_0_s1 = (sdram_0_s1_readdatavalid_from_sa & cpu_0_instruction_master_rdv_fifo_output_from_sdram_0_s1) & ~ cpu_0_instruction_master_rdv_fifo_empty_sdram_0_s1;

  //allow new arb cycle for sdram_0/s1, which is an e_assign
  assign sdram_0_s1_allow_new_arb_cycle = ~cpu_0_data_master_arbiterlock & ~cpu_0_instruction_master_arbiterlock;

  //cpu_0/instruction_master assignment into master qualified-requests vector for sdram_0/s1, which is an e_assign
  assign sdram_0_s1_master_qreq_vector[0] = cpu_0_instruction_master_qualified_request_sdram_0_s1;

  //cpu_0/instruction_master grant sdram_0/s1, which is an e_assign
  assign cpu_0_instruction_master_granted_sdram_0_s1 = sdram_0_s1_grant_vector[0];

  //cpu_0/instruction_master saved-grant sdram_0/s1, which is an e_assign
  assign cpu_0_instruction_master_saved_grant_sdram_0_s1 = sdram_0_s1_arb_winner[0] && cpu_0_instruction_master_requests_sdram_0_s1;

  //cpu_0/data_master assignment into master qualified-requests vector for sdram_0/s1, which is an e_assign
  assign sdram_0_s1_master_qreq_vector[1] = cpu_0_data_master_qualified_request_sdram_0_s1;

  //cpu_0/data_master grant sdram_0/s1, which is an e_assign
  assign cpu_0_data_master_granted_sdram_0_s1 = sdram_0_s1_grant_vector[1];

  //cpu_0/data_master saved-grant sdram_0/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_sdram_0_s1 = sdram_0_s1_arb_winner[1] && cpu_0_data_master_requests_sdram_0_s1;

  //sdram_0/s1 chosen-master double-vector, which is an e_assign
  assign sdram_0_s1_chosen_master_double_vector = {sdram_0_s1_master_qreq_vector, sdram_0_s1_master_qreq_vector} & ({~sdram_0_s1_master_qreq_vector, ~sdram_0_s1_master_qreq_vector} + sdram_0_s1_arb_addend);

  //stable onehot encoding of arb winner
  assign sdram_0_s1_arb_winner = (sdram_0_s1_allow_new_arb_cycle & | sdram_0_s1_grant_vector) ? sdram_0_s1_grant_vector : sdram_0_s1_saved_chosen_master_vector;

  //saved sdram_0_s1_grant_vector, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          sdram_0_s1_saved_chosen_master_vector <= 0;
      else if (sdram_0_s1_allow_new_arb_cycle)
          sdram_0_s1_saved_chosen_master_vector <= |sdram_0_s1_grant_vector ? sdram_0_s1_grant_vector : sdram_0_s1_saved_chosen_master_vector;
    end


  //onehot encoding of chosen master
  assign sdram_0_s1_grant_vector = {(sdram_0_s1_chosen_master_double_vector[1] | sdram_0_s1_chosen_master_double_vector[3]),
    (sdram_0_s1_chosen_master_double_vector[0] | sdram_0_s1_chosen_master_double_vector[2])};

  //sdram_0/s1 chosen master rotated left, which is an e_assign
  assign sdram_0_s1_chosen_master_rot_left = (sdram_0_s1_arb_winner << 1) ? (sdram_0_s1_arb_winner << 1) : 1;

  //sdram_0/s1's addend for next-master-grant
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          sdram_0_s1_arb_addend <= 1;
      else if (|sdram_0_s1_grant_vector)
          sdram_0_s1_arb_addend <= sdram_0_s1_end_xfer? sdram_0_s1_chosen_master_rot_left : sdram_0_s1_grant_vector;
    end


  //sdram_0_s1_reset_n assignment, which is an e_assign
  assign sdram_0_s1_reset_n = reset_n;

  assign sdram_0_s1_chipselect = cpu_0_data_master_granted_sdram_0_s1 | cpu_0_instruction_master_granted_sdram_0_s1;
  //sdram_0_s1_firsttransfer first transaction, which is an e_assign
  assign sdram_0_s1_firsttransfer = sdram_0_s1_begins_xfer ? sdram_0_s1_unreg_firsttransfer : sdram_0_s1_reg_firsttransfer;

  //sdram_0_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign sdram_0_s1_unreg_firsttransfer = ~(sdram_0_s1_slavearbiterlockenable & sdram_0_s1_any_continuerequest);

  //sdram_0_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          sdram_0_s1_reg_firsttransfer <= 1'b1;
      else if (sdram_0_s1_begins_xfer)
          sdram_0_s1_reg_firsttransfer <= sdram_0_s1_unreg_firsttransfer;
    end


  //sdram_0_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign sdram_0_s1_beginbursttransfer_internal = sdram_0_s1_begins_xfer;

  //sdram_0_s1_arbitration_holdoff_internal arbitration_holdoff, which is an e_assign
  assign sdram_0_s1_arbitration_holdoff_internal = sdram_0_s1_begins_xfer & sdram_0_s1_firsttransfer;

  //~sdram_0_s1_read_n assignment, which is an e_mux
  assign sdram_0_s1_read_n = ~((cpu_0_data_master_granted_sdram_0_s1 & cpu_0_data_master_read) | (cpu_0_instruction_master_granted_sdram_0_s1 & cpu_0_instruction_master_read));

  //~sdram_0_s1_write_n assignment, which is an e_mux
  assign sdram_0_s1_write_n = ~(cpu_0_data_master_granted_sdram_0_s1 & cpu_0_data_master_write);

  assign shifted_address_to_sdram_0_s1_from_cpu_0_data_master = {cpu_0_data_master_address_to_slave >> 2,
    cpu_0_data_master_dbs_address[1],
    {1 {1'b0}}};

  //sdram_0_s1_address mux, which is an e_mux
  assign sdram_0_s1_address = (cpu_0_data_master_granted_sdram_0_s1)? (shifted_address_to_sdram_0_s1_from_cpu_0_data_master >> 1) :
    (shifted_address_to_sdram_0_s1_from_cpu_0_instruction_master >> 1);

  assign shifted_address_to_sdram_0_s1_from_cpu_0_instruction_master = {cpu_0_instruction_master_address_to_slave >> 2,
    cpu_0_instruction_master_dbs_address[1],
    {1 {1'b0}}};

  //d1_sdram_0_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_sdram_0_s1_end_xfer <= 1;
      else 
        d1_sdram_0_s1_end_xfer <= sdram_0_s1_end_xfer;
    end


  //sdram_0_s1_waits_for_read in a cycle, which is an e_mux
  assign sdram_0_s1_waits_for_read = sdram_0_s1_in_a_read_cycle & sdram_0_s1_waitrequest_from_sa;

  //sdram_0_s1_in_a_read_cycle assignment, which is an e_assign
  assign sdram_0_s1_in_a_read_cycle = (cpu_0_data_master_granted_sdram_0_s1 & cpu_0_data_master_read) | (cpu_0_instruction_master_granted_sdram_0_s1 & cpu_0_instruction_master_read);

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = sdram_0_s1_in_a_read_cycle;

  //sdram_0_s1_waits_for_write in a cycle, which is an e_mux
  assign sdram_0_s1_waits_for_write = sdram_0_s1_in_a_write_cycle & sdram_0_s1_waitrequest_from_sa;

  //sdram_0_s1_in_a_write_cycle assignment, which is an e_assign
  assign sdram_0_s1_in_a_write_cycle = cpu_0_data_master_granted_sdram_0_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = sdram_0_s1_in_a_write_cycle;

  assign wait_for_sdram_0_s1_counter = 0;
  //~sdram_0_s1_byteenable_n byte enable port mux, which is an e_mux
  assign sdram_0_s1_byteenable_n = ~((cpu_0_data_master_granted_sdram_0_s1)? cpu_0_data_master_byteenable_sdram_0_s1 :
    -1);

  assign {cpu_0_data_master_byteenable_sdram_0_s1_segment_1,
cpu_0_data_master_byteenable_sdram_0_s1_segment_0} = cpu_0_data_master_byteenable;
  assign cpu_0_data_master_byteenable_sdram_0_s1 = ((cpu_0_data_master_dbs_address[1] == 0))? cpu_0_data_master_byteenable_sdram_0_s1_segment_0 :
    cpu_0_data_master_byteenable_sdram_0_s1_segment_1;


//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //sdram_0/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end


  //grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (cpu_0_data_master_granted_sdram_0_s1 + cpu_0_instruction_master_granted_sdram_0_s1 > 1)
        begin
          $write("%0d ns: > 1 of grant signals are active simultaneously", $time);
          $stop;
        end
    end


  //saved_grant signals are active simultaneously, which is an e_process
  always @(posedge clk)
    begin
      if (cpu_0_data_master_saved_grant_sdram_0_s1 + cpu_0_instruction_master_saved_grant_sdram_0_s1 > 1)
        begin
          $write("%0d ns: > 1 of saved_grant signals are active simultaneously", $time);
          $stop;
        end
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module sysid_0_control_slave_arbitrator (
                                          // inputs:
                                           clk,
                                           cpu_0_data_master_address_to_slave,
                                           cpu_0_data_master_latency_counter,
                                           cpu_0_data_master_read,
                                           cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                           cpu_0_data_master_write,
                                           reset_n,
                                           sysid_0_control_slave_readdata,

                                          // outputs:
                                           cpu_0_data_master_granted_sysid_0_control_slave,
                                           cpu_0_data_master_qualified_request_sysid_0_control_slave,
                                           cpu_0_data_master_read_data_valid_sysid_0_control_slave,
                                           cpu_0_data_master_requests_sysid_0_control_slave,
                                           d1_sysid_0_control_slave_end_xfer,
                                           sysid_0_control_slave_address,
                                           sysid_0_control_slave_readdata_from_sa,
                                           sysid_0_control_slave_reset_n
                                        )
;

  output           cpu_0_data_master_granted_sysid_0_control_slave;
  output           cpu_0_data_master_qualified_request_sysid_0_control_slave;
  output           cpu_0_data_master_read_data_valid_sysid_0_control_slave;
  output           cpu_0_data_master_requests_sysid_0_control_slave;
  output           d1_sysid_0_control_slave_end_xfer;
  output           sysid_0_control_slave_address;
  output  [ 31: 0] sysid_0_control_slave_readdata_from_sa;
  output           sysid_0_control_slave_reset_n;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input            reset_n;
  input   [ 31: 0] sysid_0_control_slave_readdata;

  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_sysid_0_control_slave;
  wire             cpu_0_data_master_qualified_request_sysid_0_control_slave;
  wire             cpu_0_data_master_read_data_valid_sysid_0_control_slave;
  wire             cpu_0_data_master_requests_sysid_0_control_slave;
  wire             cpu_0_data_master_saved_grant_sysid_0_control_slave;
  reg              d1_reasons_to_wait;
  reg              d1_sysid_0_control_slave_end_xfer;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_sysid_0_control_slave;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_sysid_0_control_slave_from_cpu_0_data_master;
  wire             sysid_0_control_slave_address;
  wire             sysid_0_control_slave_allgrants;
  wire             sysid_0_control_slave_allow_new_arb_cycle;
  wire             sysid_0_control_slave_any_bursting_master_saved_grant;
  wire             sysid_0_control_slave_any_continuerequest;
  wire             sysid_0_control_slave_arb_counter_enable;
  reg     [  1: 0] sysid_0_control_slave_arb_share_counter;
  wire    [  1: 0] sysid_0_control_slave_arb_share_counter_next_value;
  wire    [  1: 0] sysid_0_control_slave_arb_share_set_values;
  wire             sysid_0_control_slave_beginbursttransfer_internal;
  wire             sysid_0_control_slave_begins_xfer;
  wire             sysid_0_control_slave_end_xfer;
  wire             sysid_0_control_slave_firsttransfer;
  wire             sysid_0_control_slave_grant_vector;
  wire             sysid_0_control_slave_in_a_read_cycle;
  wire             sysid_0_control_slave_in_a_write_cycle;
  wire             sysid_0_control_slave_master_qreq_vector;
  wire             sysid_0_control_slave_non_bursting_master_requests;
  wire    [ 31: 0] sysid_0_control_slave_readdata_from_sa;
  reg              sysid_0_control_slave_reg_firsttransfer;
  wire             sysid_0_control_slave_reset_n;
  reg              sysid_0_control_slave_slavearbiterlockenable;
  wire             sysid_0_control_slave_slavearbiterlockenable2;
  wire             sysid_0_control_slave_unreg_firsttransfer;
  wire             sysid_0_control_slave_waits_for_read;
  wire             sysid_0_control_slave_waits_for_write;
  wire             wait_for_sysid_0_control_slave_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~sysid_0_control_slave_end_xfer;
    end


  assign sysid_0_control_slave_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_sysid_0_control_slave));
  //assign sysid_0_control_slave_readdata_from_sa = sysid_0_control_slave_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign sysid_0_control_slave_readdata_from_sa = sysid_0_control_slave_readdata;

  assign cpu_0_data_master_requests_sysid_0_control_slave = (({cpu_0_data_master_address_to_slave[26 : 3] , 3'b0} == 27'h40022c0) & (cpu_0_data_master_read | cpu_0_data_master_write)) & cpu_0_data_master_read;
  //sysid_0_control_slave_arb_share_counter set values, which is an e_mux
  assign sysid_0_control_slave_arb_share_set_values = 1;

  //sysid_0_control_slave_non_bursting_master_requests mux, which is an e_mux
  assign sysid_0_control_slave_non_bursting_master_requests = cpu_0_data_master_requests_sysid_0_control_slave;

  //sysid_0_control_slave_any_bursting_master_saved_grant mux, which is an e_mux
  assign sysid_0_control_slave_any_bursting_master_saved_grant = 0;

  //sysid_0_control_slave_arb_share_counter_next_value assignment, which is an e_assign
  assign sysid_0_control_slave_arb_share_counter_next_value = sysid_0_control_slave_firsttransfer ? (sysid_0_control_slave_arb_share_set_values - 1) : |sysid_0_control_slave_arb_share_counter ? (sysid_0_control_slave_arb_share_counter - 1) : 0;

  //sysid_0_control_slave_allgrants all slave grants, which is an e_mux
  assign sysid_0_control_slave_allgrants = |sysid_0_control_slave_grant_vector;

  //sysid_0_control_slave_end_xfer assignment, which is an e_assign
  assign sysid_0_control_slave_end_xfer = ~(sysid_0_control_slave_waits_for_read | sysid_0_control_slave_waits_for_write);

  //end_xfer_arb_share_counter_term_sysid_0_control_slave arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_sysid_0_control_slave = sysid_0_control_slave_end_xfer & (~sysid_0_control_slave_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //sysid_0_control_slave_arb_share_counter arbitration counter enable, which is an e_assign
  assign sysid_0_control_slave_arb_counter_enable = (end_xfer_arb_share_counter_term_sysid_0_control_slave & sysid_0_control_slave_allgrants) | (end_xfer_arb_share_counter_term_sysid_0_control_slave & ~sysid_0_control_slave_non_bursting_master_requests);

  //sysid_0_control_slave_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          sysid_0_control_slave_arb_share_counter <= 0;
      else if (sysid_0_control_slave_arb_counter_enable)
          sysid_0_control_slave_arb_share_counter <= sysid_0_control_slave_arb_share_counter_next_value;
    end


  //sysid_0_control_slave_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          sysid_0_control_slave_slavearbiterlockenable <= 0;
      else if ((|sysid_0_control_slave_master_qreq_vector & end_xfer_arb_share_counter_term_sysid_0_control_slave) | (end_xfer_arb_share_counter_term_sysid_0_control_slave & ~sysid_0_control_slave_non_bursting_master_requests))
          sysid_0_control_slave_slavearbiterlockenable <= |sysid_0_control_slave_arb_share_counter_next_value;
    end


  //cpu_0/data_master sysid_0/control_slave arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = sysid_0_control_slave_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //sysid_0_control_slave_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign sysid_0_control_slave_slavearbiterlockenable2 = |sysid_0_control_slave_arb_share_counter_next_value;

  //cpu_0/data_master sysid_0/control_slave arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = sysid_0_control_slave_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //sysid_0_control_slave_any_continuerequest at least one master continues requesting, which is an e_assign
  assign sysid_0_control_slave_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_sysid_0_control_slave = cpu_0_data_master_requests_sysid_0_control_slave & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_sysid_0_control_slave, which is an e_mux
  assign cpu_0_data_master_read_data_valid_sysid_0_control_slave = cpu_0_data_master_granted_sysid_0_control_slave & cpu_0_data_master_read & ~sysid_0_control_slave_waits_for_read;

  //master is always granted when requested
  assign cpu_0_data_master_granted_sysid_0_control_slave = cpu_0_data_master_qualified_request_sysid_0_control_slave;

  //cpu_0/data_master saved-grant sysid_0/control_slave, which is an e_assign
  assign cpu_0_data_master_saved_grant_sysid_0_control_slave = cpu_0_data_master_requests_sysid_0_control_slave;

  //allow new arb cycle for sysid_0/control_slave, which is an e_assign
  assign sysid_0_control_slave_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign sysid_0_control_slave_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign sysid_0_control_slave_master_qreq_vector = 1;

  //sysid_0_control_slave_reset_n assignment, which is an e_assign
  assign sysid_0_control_slave_reset_n = reset_n;

  //sysid_0_control_slave_firsttransfer first transaction, which is an e_assign
  assign sysid_0_control_slave_firsttransfer = sysid_0_control_slave_begins_xfer ? sysid_0_control_slave_unreg_firsttransfer : sysid_0_control_slave_reg_firsttransfer;

  //sysid_0_control_slave_unreg_firsttransfer first transaction, which is an e_assign
  assign sysid_0_control_slave_unreg_firsttransfer = ~(sysid_0_control_slave_slavearbiterlockenable & sysid_0_control_slave_any_continuerequest);

  //sysid_0_control_slave_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          sysid_0_control_slave_reg_firsttransfer <= 1'b1;
      else if (sysid_0_control_slave_begins_xfer)
          sysid_0_control_slave_reg_firsttransfer <= sysid_0_control_slave_unreg_firsttransfer;
    end


  //sysid_0_control_slave_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign sysid_0_control_slave_beginbursttransfer_internal = sysid_0_control_slave_begins_xfer;

  assign shifted_address_to_sysid_0_control_slave_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //sysid_0_control_slave_address mux, which is an e_mux
  assign sysid_0_control_slave_address = shifted_address_to_sysid_0_control_slave_from_cpu_0_data_master >> 2;

  //d1_sysid_0_control_slave_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_sysid_0_control_slave_end_xfer <= 1;
      else 
        d1_sysid_0_control_slave_end_xfer <= sysid_0_control_slave_end_xfer;
    end


  //sysid_0_control_slave_waits_for_read in a cycle, which is an e_mux
  assign sysid_0_control_slave_waits_for_read = sysid_0_control_slave_in_a_read_cycle & sysid_0_control_slave_begins_xfer;

  //sysid_0_control_slave_in_a_read_cycle assignment, which is an e_assign
  assign sysid_0_control_slave_in_a_read_cycle = cpu_0_data_master_granted_sysid_0_control_slave & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = sysid_0_control_slave_in_a_read_cycle;

  //sysid_0_control_slave_waits_for_write in a cycle, which is an e_mux
  assign sysid_0_control_slave_waits_for_write = sysid_0_control_slave_in_a_write_cycle & 0;

  //sysid_0_control_slave_in_a_write_cycle assignment, which is an e_assign
  assign sysid_0_control_slave_in_a_write_cycle = cpu_0_data_master_granted_sysid_0_control_slave & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = sysid_0_control_slave_in_a_write_cycle;

  assign wait_for_sysid_0_control_slave_counter = 0;

//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //sysid_0/control_slave enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module timer_0_s1_arbitrator (
                               // inputs:
                                clk,
                                cpu_0_data_master_address_to_slave,
                                cpu_0_data_master_latency_counter,
                                cpu_0_data_master_read,
                                cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                cpu_0_data_master_write,
                                cpu_0_data_master_writedata,
                                reset_n,
                                timer_0_s1_irq,
                                timer_0_s1_readdata,

                               // outputs:
                                cpu_0_data_master_granted_timer_0_s1,
                                cpu_0_data_master_qualified_request_timer_0_s1,
                                cpu_0_data_master_read_data_valid_timer_0_s1,
                                cpu_0_data_master_requests_timer_0_s1,
                                d1_timer_0_s1_end_xfer,
                                timer_0_s1_address,
                                timer_0_s1_chipselect,
                                timer_0_s1_irq_from_sa,
                                timer_0_s1_readdata_from_sa,
                                timer_0_s1_reset_n,
                                timer_0_s1_write_n,
                                timer_0_s1_writedata
                             )
;

  output           cpu_0_data_master_granted_timer_0_s1;
  output           cpu_0_data_master_qualified_request_timer_0_s1;
  output           cpu_0_data_master_read_data_valid_timer_0_s1;
  output           cpu_0_data_master_requests_timer_0_s1;
  output           d1_timer_0_s1_end_xfer;
  output  [  2: 0] timer_0_s1_address;
  output           timer_0_s1_chipselect;
  output           timer_0_s1_irq_from_sa;
  output  [ 15: 0] timer_0_s1_readdata_from_sa;
  output           timer_0_s1_reset_n;
  output           timer_0_s1_write_n;
  output  [ 15: 0] timer_0_s1_writedata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;
  input            timer_0_s1_irq;
  input   [ 15: 0] timer_0_s1_readdata;

  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_timer_0_s1;
  wire             cpu_0_data_master_qualified_request_timer_0_s1;
  wire             cpu_0_data_master_read_data_valid_timer_0_s1;
  wire             cpu_0_data_master_requests_timer_0_s1;
  wire             cpu_0_data_master_saved_grant_timer_0_s1;
  reg              d1_reasons_to_wait;
  reg              d1_timer_0_s1_end_xfer;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_timer_0_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_timer_0_s1_from_cpu_0_data_master;
  wire    [  2: 0] timer_0_s1_address;
  wire             timer_0_s1_allgrants;
  wire             timer_0_s1_allow_new_arb_cycle;
  wire             timer_0_s1_any_bursting_master_saved_grant;
  wire             timer_0_s1_any_continuerequest;
  wire             timer_0_s1_arb_counter_enable;
  reg     [  1: 0] timer_0_s1_arb_share_counter;
  wire    [  1: 0] timer_0_s1_arb_share_counter_next_value;
  wire    [  1: 0] timer_0_s1_arb_share_set_values;
  wire             timer_0_s1_beginbursttransfer_internal;
  wire             timer_0_s1_begins_xfer;
  wire             timer_0_s1_chipselect;
  wire             timer_0_s1_end_xfer;
  wire             timer_0_s1_firsttransfer;
  wire             timer_0_s1_grant_vector;
  wire             timer_0_s1_in_a_read_cycle;
  wire             timer_0_s1_in_a_write_cycle;
  wire             timer_0_s1_irq_from_sa;
  wire             timer_0_s1_master_qreq_vector;
  wire             timer_0_s1_non_bursting_master_requests;
  wire    [ 15: 0] timer_0_s1_readdata_from_sa;
  reg              timer_0_s1_reg_firsttransfer;
  wire             timer_0_s1_reset_n;
  reg              timer_0_s1_slavearbiterlockenable;
  wire             timer_0_s1_slavearbiterlockenable2;
  wire             timer_0_s1_unreg_firsttransfer;
  wire             timer_0_s1_waits_for_read;
  wire             timer_0_s1_waits_for_write;
  wire             timer_0_s1_write_n;
  wire    [ 15: 0] timer_0_s1_writedata;
  wire             wait_for_timer_0_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~timer_0_s1_end_xfer;
    end


  assign timer_0_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_timer_0_s1));
  //assign timer_0_s1_readdata_from_sa = timer_0_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign timer_0_s1_readdata_from_sa = timer_0_s1_readdata;

  assign cpu_0_data_master_requests_timer_0_s1 = ({cpu_0_data_master_address_to_slave[26 : 5] , 5'b0} == 27'h4002020) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //timer_0_s1_arb_share_counter set values, which is an e_mux
  assign timer_0_s1_arb_share_set_values = 1;

  //timer_0_s1_non_bursting_master_requests mux, which is an e_mux
  assign timer_0_s1_non_bursting_master_requests = cpu_0_data_master_requests_timer_0_s1;

  //timer_0_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign timer_0_s1_any_bursting_master_saved_grant = 0;

  //timer_0_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign timer_0_s1_arb_share_counter_next_value = timer_0_s1_firsttransfer ? (timer_0_s1_arb_share_set_values - 1) : |timer_0_s1_arb_share_counter ? (timer_0_s1_arb_share_counter - 1) : 0;

  //timer_0_s1_allgrants all slave grants, which is an e_mux
  assign timer_0_s1_allgrants = |timer_0_s1_grant_vector;

  //timer_0_s1_end_xfer assignment, which is an e_assign
  assign timer_0_s1_end_xfer = ~(timer_0_s1_waits_for_read | timer_0_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_timer_0_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_timer_0_s1 = timer_0_s1_end_xfer & (~timer_0_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //timer_0_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign timer_0_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_timer_0_s1 & timer_0_s1_allgrants) | (end_xfer_arb_share_counter_term_timer_0_s1 & ~timer_0_s1_non_bursting_master_requests);

  //timer_0_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          timer_0_s1_arb_share_counter <= 0;
      else if (timer_0_s1_arb_counter_enable)
          timer_0_s1_arb_share_counter <= timer_0_s1_arb_share_counter_next_value;
    end


  //timer_0_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          timer_0_s1_slavearbiterlockenable <= 0;
      else if ((|timer_0_s1_master_qreq_vector & end_xfer_arb_share_counter_term_timer_0_s1) | (end_xfer_arb_share_counter_term_timer_0_s1 & ~timer_0_s1_non_bursting_master_requests))
          timer_0_s1_slavearbiterlockenable <= |timer_0_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master timer_0/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = timer_0_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //timer_0_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign timer_0_s1_slavearbiterlockenable2 = |timer_0_s1_arb_share_counter_next_value;

  //cpu_0/data_master timer_0/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = timer_0_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //timer_0_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign timer_0_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_timer_0_s1 = cpu_0_data_master_requests_timer_0_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_timer_0_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_timer_0_s1 = cpu_0_data_master_granted_timer_0_s1 & cpu_0_data_master_read & ~timer_0_s1_waits_for_read;

  //timer_0_s1_writedata mux, which is an e_mux
  assign timer_0_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_timer_0_s1 = cpu_0_data_master_qualified_request_timer_0_s1;

  //cpu_0/data_master saved-grant timer_0/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_timer_0_s1 = cpu_0_data_master_requests_timer_0_s1;

  //allow new arb cycle for timer_0/s1, which is an e_assign
  assign timer_0_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign timer_0_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign timer_0_s1_master_qreq_vector = 1;

  //timer_0_s1_reset_n assignment, which is an e_assign
  assign timer_0_s1_reset_n = reset_n;

  assign timer_0_s1_chipselect = cpu_0_data_master_granted_timer_0_s1;
  //timer_0_s1_firsttransfer first transaction, which is an e_assign
  assign timer_0_s1_firsttransfer = timer_0_s1_begins_xfer ? timer_0_s1_unreg_firsttransfer : timer_0_s1_reg_firsttransfer;

  //timer_0_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign timer_0_s1_unreg_firsttransfer = ~(timer_0_s1_slavearbiterlockenable & timer_0_s1_any_continuerequest);

  //timer_0_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          timer_0_s1_reg_firsttransfer <= 1'b1;
      else if (timer_0_s1_begins_xfer)
          timer_0_s1_reg_firsttransfer <= timer_0_s1_unreg_firsttransfer;
    end


  //timer_0_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign timer_0_s1_beginbursttransfer_internal = timer_0_s1_begins_xfer;

  //~timer_0_s1_write_n assignment, which is an e_mux
  assign timer_0_s1_write_n = ~(cpu_0_data_master_granted_timer_0_s1 & cpu_0_data_master_write);

  assign shifted_address_to_timer_0_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //timer_0_s1_address mux, which is an e_mux
  assign timer_0_s1_address = shifted_address_to_timer_0_s1_from_cpu_0_data_master >> 2;

  //d1_timer_0_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_timer_0_s1_end_xfer <= 1;
      else 
        d1_timer_0_s1_end_xfer <= timer_0_s1_end_xfer;
    end


  //timer_0_s1_waits_for_read in a cycle, which is an e_mux
  assign timer_0_s1_waits_for_read = timer_0_s1_in_a_read_cycle & timer_0_s1_begins_xfer;

  //timer_0_s1_in_a_read_cycle assignment, which is an e_assign
  assign timer_0_s1_in_a_read_cycle = cpu_0_data_master_granted_timer_0_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = timer_0_s1_in_a_read_cycle;

  //timer_0_s1_waits_for_write in a cycle, which is an e_mux
  assign timer_0_s1_waits_for_write = timer_0_s1_in_a_write_cycle & 0;

  //timer_0_s1_in_a_write_cycle assignment, which is an e_assign
  assign timer_0_s1_in_a_write_cycle = cpu_0_data_master_granted_timer_0_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = timer_0_s1_in_a_write_cycle;

  assign wait_for_timer_0_s1_counter = 0;
  //assign timer_0_s1_irq_from_sa = timer_0_s1_irq so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign timer_0_s1_irq_from_sa = timer_0_s1_irq;


//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //timer_0/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module timer_1_s1_arbitrator (
                               // inputs:
                                clk,
                                cpu_0_data_master_address_to_slave,
                                cpu_0_data_master_latency_counter,
                                cpu_0_data_master_read,
                                cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                                cpu_0_data_master_write,
                                cpu_0_data_master_writedata,
                                reset_n,
                                timer_1_s1_irq,
                                timer_1_s1_readdata,

                               // outputs:
                                cpu_0_data_master_granted_timer_1_s1,
                                cpu_0_data_master_qualified_request_timer_1_s1,
                                cpu_0_data_master_read_data_valid_timer_1_s1,
                                cpu_0_data_master_requests_timer_1_s1,
                                d1_timer_1_s1_end_xfer,
                                timer_1_s1_address,
                                timer_1_s1_chipselect,
                                timer_1_s1_irq_from_sa,
                                timer_1_s1_readdata_from_sa,
                                timer_1_s1_reset_n,
                                timer_1_s1_write_n,
                                timer_1_s1_writedata
                             )
;

  output           cpu_0_data_master_granted_timer_1_s1;
  output           cpu_0_data_master_qualified_request_timer_1_s1;
  output           cpu_0_data_master_read_data_valid_timer_1_s1;
  output           cpu_0_data_master_requests_timer_1_s1;
  output           d1_timer_1_s1_end_xfer;
  output  [  2: 0] timer_1_s1_address;
  output           timer_1_s1_chipselect;
  output           timer_1_s1_irq_from_sa;
  output  [ 15: 0] timer_1_s1_readdata_from_sa;
  output           timer_1_s1_reset_n;
  output           timer_1_s1_write_n;
  output  [ 15: 0] timer_1_s1_writedata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;
  input            timer_1_s1_irq;
  input   [ 15: 0] timer_1_s1_readdata;

  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_timer_1_s1;
  wire             cpu_0_data_master_qualified_request_timer_1_s1;
  wire             cpu_0_data_master_read_data_valid_timer_1_s1;
  wire             cpu_0_data_master_requests_timer_1_s1;
  wire             cpu_0_data_master_saved_grant_timer_1_s1;
  reg              d1_reasons_to_wait;
  reg              d1_timer_1_s1_end_xfer;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_timer_1_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_timer_1_s1_from_cpu_0_data_master;
  wire    [  2: 0] timer_1_s1_address;
  wire             timer_1_s1_allgrants;
  wire             timer_1_s1_allow_new_arb_cycle;
  wire             timer_1_s1_any_bursting_master_saved_grant;
  wire             timer_1_s1_any_continuerequest;
  wire             timer_1_s1_arb_counter_enable;
  reg     [  1: 0] timer_1_s1_arb_share_counter;
  wire    [  1: 0] timer_1_s1_arb_share_counter_next_value;
  wire    [  1: 0] timer_1_s1_arb_share_set_values;
  wire             timer_1_s1_beginbursttransfer_internal;
  wire             timer_1_s1_begins_xfer;
  wire             timer_1_s1_chipselect;
  wire             timer_1_s1_end_xfer;
  wire             timer_1_s1_firsttransfer;
  wire             timer_1_s1_grant_vector;
  wire             timer_1_s1_in_a_read_cycle;
  wire             timer_1_s1_in_a_write_cycle;
  wire             timer_1_s1_irq_from_sa;
  wire             timer_1_s1_master_qreq_vector;
  wire             timer_1_s1_non_bursting_master_requests;
  wire    [ 15: 0] timer_1_s1_readdata_from_sa;
  reg              timer_1_s1_reg_firsttransfer;
  wire             timer_1_s1_reset_n;
  reg              timer_1_s1_slavearbiterlockenable;
  wire             timer_1_s1_slavearbiterlockenable2;
  wire             timer_1_s1_unreg_firsttransfer;
  wire             timer_1_s1_waits_for_read;
  wire             timer_1_s1_waits_for_write;
  wire             timer_1_s1_write_n;
  wire    [ 15: 0] timer_1_s1_writedata;
  wire             wait_for_timer_1_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~timer_1_s1_end_xfer;
    end


  assign timer_1_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_timer_1_s1));
  //assign timer_1_s1_readdata_from_sa = timer_1_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign timer_1_s1_readdata_from_sa = timer_1_s1_readdata;

  assign cpu_0_data_master_requests_timer_1_s1 = ({cpu_0_data_master_address_to_slave[26 : 5] , 5'b0} == 27'h4002040) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //timer_1_s1_arb_share_counter set values, which is an e_mux
  assign timer_1_s1_arb_share_set_values = 1;

  //timer_1_s1_non_bursting_master_requests mux, which is an e_mux
  assign timer_1_s1_non_bursting_master_requests = cpu_0_data_master_requests_timer_1_s1;

  //timer_1_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign timer_1_s1_any_bursting_master_saved_grant = 0;

  //timer_1_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign timer_1_s1_arb_share_counter_next_value = timer_1_s1_firsttransfer ? (timer_1_s1_arb_share_set_values - 1) : |timer_1_s1_arb_share_counter ? (timer_1_s1_arb_share_counter - 1) : 0;

  //timer_1_s1_allgrants all slave grants, which is an e_mux
  assign timer_1_s1_allgrants = |timer_1_s1_grant_vector;

  //timer_1_s1_end_xfer assignment, which is an e_assign
  assign timer_1_s1_end_xfer = ~(timer_1_s1_waits_for_read | timer_1_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_timer_1_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_timer_1_s1 = timer_1_s1_end_xfer & (~timer_1_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //timer_1_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign timer_1_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_timer_1_s1 & timer_1_s1_allgrants) | (end_xfer_arb_share_counter_term_timer_1_s1 & ~timer_1_s1_non_bursting_master_requests);

  //timer_1_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          timer_1_s1_arb_share_counter <= 0;
      else if (timer_1_s1_arb_counter_enable)
          timer_1_s1_arb_share_counter <= timer_1_s1_arb_share_counter_next_value;
    end


  //timer_1_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          timer_1_s1_slavearbiterlockenable <= 0;
      else if ((|timer_1_s1_master_qreq_vector & end_xfer_arb_share_counter_term_timer_1_s1) | (end_xfer_arb_share_counter_term_timer_1_s1 & ~timer_1_s1_non_bursting_master_requests))
          timer_1_s1_slavearbiterlockenable <= |timer_1_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master timer_1/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = timer_1_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //timer_1_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign timer_1_s1_slavearbiterlockenable2 = |timer_1_s1_arb_share_counter_next_value;

  //cpu_0/data_master timer_1/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = timer_1_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //timer_1_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign timer_1_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_timer_1_s1 = cpu_0_data_master_requests_timer_1_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_timer_1_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_timer_1_s1 = cpu_0_data_master_granted_timer_1_s1 & cpu_0_data_master_read & ~timer_1_s1_waits_for_read;

  //timer_1_s1_writedata mux, which is an e_mux
  assign timer_1_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_timer_1_s1 = cpu_0_data_master_qualified_request_timer_1_s1;

  //cpu_0/data_master saved-grant timer_1/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_timer_1_s1 = cpu_0_data_master_requests_timer_1_s1;

  //allow new arb cycle for timer_1/s1, which is an e_assign
  assign timer_1_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign timer_1_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign timer_1_s1_master_qreq_vector = 1;

  //timer_1_s1_reset_n assignment, which is an e_assign
  assign timer_1_s1_reset_n = reset_n;

  assign timer_1_s1_chipselect = cpu_0_data_master_granted_timer_1_s1;
  //timer_1_s1_firsttransfer first transaction, which is an e_assign
  assign timer_1_s1_firsttransfer = timer_1_s1_begins_xfer ? timer_1_s1_unreg_firsttransfer : timer_1_s1_reg_firsttransfer;

  //timer_1_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign timer_1_s1_unreg_firsttransfer = ~(timer_1_s1_slavearbiterlockenable & timer_1_s1_any_continuerequest);

  //timer_1_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          timer_1_s1_reg_firsttransfer <= 1'b1;
      else if (timer_1_s1_begins_xfer)
          timer_1_s1_reg_firsttransfer <= timer_1_s1_unreg_firsttransfer;
    end


  //timer_1_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign timer_1_s1_beginbursttransfer_internal = timer_1_s1_begins_xfer;

  //~timer_1_s1_write_n assignment, which is an e_mux
  assign timer_1_s1_write_n = ~(cpu_0_data_master_granted_timer_1_s1 & cpu_0_data_master_write);

  assign shifted_address_to_timer_1_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //timer_1_s1_address mux, which is an e_mux
  assign timer_1_s1_address = shifted_address_to_timer_1_s1_from_cpu_0_data_master >> 2;

  //d1_timer_1_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_timer_1_s1_end_xfer <= 1;
      else 
        d1_timer_1_s1_end_xfer <= timer_1_s1_end_xfer;
    end


  //timer_1_s1_waits_for_read in a cycle, which is an e_mux
  assign timer_1_s1_waits_for_read = timer_1_s1_in_a_read_cycle & timer_1_s1_begins_xfer;

  //timer_1_s1_in_a_read_cycle assignment, which is an e_assign
  assign timer_1_s1_in_a_read_cycle = cpu_0_data_master_granted_timer_1_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = timer_1_s1_in_a_read_cycle;

  //timer_1_s1_waits_for_write in a cycle, which is an e_mux
  assign timer_1_s1_waits_for_write = timer_1_s1_in_a_write_cycle & 0;

  //timer_1_s1_in_a_write_cycle assignment, which is an e_assign
  assign timer_1_s1_in_a_write_cycle = cpu_0_data_master_granted_timer_1_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = timer_1_s1_in_a_write_cycle;

  assign wait_for_timer_1_s1_counter = 0;
  //assign timer_1_s1_irq_from_sa = timer_1_s1_irq so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign timer_1_s1_irq_from_sa = timer_1_s1_irq;


//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //timer_1/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module uart_0_s1_arbitrator (
                              // inputs:
                               clk,
                               cpu_0_data_master_address_to_slave,
                               cpu_0_data_master_latency_counter,
                               cpu_0_data_master_read,
                               cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register,
                               cpu_0_data_master_write,
                               cpu_0_data_master_writedata,
                               reset_n,
                               uart_0_s1_dataavailable,
                               uart_0_s1_irq,
                               uart_0_s1_readdata,
                               uart_0_s1_readyfordata,

                              // outputs:
                               cpu_0_data_master_granted_uart_0_s1,
                               cpu_0_data_master_qualified_request_uart_0_s1,
                               cpu_0_data_master_read_data_valid_uart_0_s1,
                               cpu_0_data_master_requests_uart_0_s1,
                               d1_uart_0_s1_end_xfer,
                               uart_0_s1_address,
                               uart_0_s1_begintransfer,
                               uart_0_s1_chipselect,
                               uart_0_s1_dataavailable_from_sa,
                               uart_0_s1_irq_from_sa,
                               uart_0_s1_read_n,
                               uart_0_s1_readdata_from_sa,
                               uart_0_s1_readyfordata_from_sa,
                               uart_0_s1_reset_n,
                               uart_0_s1_write_n,
                               uart_0_s1_writedata
                            )
;

  output           cpu_0_data_master_granted_uart_0_s1;
  output           cpu_0_data_master_qualified_request_uart_0_s1;
  output           cpu_0_data_master_read_data_valid_uart_0_s1;
  output           cpu_0_data_master_requests_uart_0_s1;
  output           d1_uart_0_s1_end_xfer;
  output  [  2: 0] uart_0_s1_address;
  output           uart_0_s1_begintransfer;
  output           uart_0_s1_chipselect;
  output           uart_0_s1_dataavailable_from_sa;
  output           uart_0_s1_irq_from_sa;
  output           uart_0_s1_read_n;
  output  [ 15: 0] uart_0_s1_readdata_from_sa;
  output           uart_0_s1_readyfordata_from_sa;
  output           uart_0_s1_reset_n;
  output           uart_0_s1_write_n;
  output  [ 15: 0] uart_0_s1_writedata;
  input            clk;
  input   [ 26: 0] cpu_0_data_master_address_to_slave;
  input            cpu_0_data_master_latency_counter;
  input            cpu_0_data_master_read;
  input            cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  input            cpu_0_data_master_write;
  input   [ 31: 0] cpu_0_data_master_writedata;
  input            reset_n;
  input            uart_0_s1_dataavailable;
  input            uart_0_s1_irq;
  input   [ 15: 0] uart_0_s1_readdata;
  input            uart_0_s1_readyfordata;

  wire             cpu_0_data_master_arbiterlock;
  wire             cpu_0_data_master_arbiterlock2;
  wire             cpu_0_data_master_continuerequest;
  wire             cpu_0_data_master_granted_uart_0_s1;
  wire             cpu_0_data_master_qualified_request_uart_0_s1;
  wire             cpu_0_data_master_read_data_valid_uart_0_s1;
  wire             cpu_0_data_master_requests_uart_0_s1;
  wire             cpu_0_data_master_saved_grant_uart_0_s1;
  reg              d1_reasons_to_wait;
  reg              d1_uart_0_s1_end_xfer;
  reg              enable_nonzero_assertions;
  wire             end_xfer_arb_share_counter_term_uart_0_s1;
  wire             in_a_read_cycle;
  wire             in_a_write_cycle;
  wire    [ 26: 0] shifted_address_to_uart_0_s1_from_cpu_0_data_master;
  wire    [  2: 0] uart_0_s1_address;
  wire             uart_0_s1_allgrants;
  wire             uart_0_s1_allow_new_arb_cycle;
  wire             uart_0_s1_any_bursting_master_saved_grant;
  wire             uart_0_s1_any_continuerequest;
  wire             uart_0_s1_arb_counter_enable;
  reg     [  1: 0] uart_0_s1_arb_share_counter;
  wire    [  1: 0] uart_0_s1_arb_share_counter_next_value;
  wire    [  1: 0] uart_0_s1_arb_share_set_values;
  wire             uart_0_s1_beginbursttransfer_internal;
  wire             uart_0_s1_begins_xfer;
  wire             uart_0_s1_begintransfer;
  wire             uart_0_s1_chipselect;
  wire             uart_0_s1_dataavailable_from_sa;
  wire             uart_0_s1_end_xfer;
  wire             uart_0_s1_firsttransfer;
  wire             uart_0_s1_grant_vector;
  wire             uart_0_s1_in_a_read_cycle;
  wire             uart_0_s1_in_a_write_cycle;
  wire             uart_0_s1_irq_from_sa;
  wire             uart_0_s1_master_qreq_vector;
  wire             uart_0_s1_non_bursting_master_requests;
  wire             uart_0_s1_read_n;
  wire    [ 15: 0] uart_0_s1_readdata_from_sa;
  wire             uart_0_s1_readyfordata_from_sa;
  reg              uart_0_s1_reg_firsttransfer;
  wire             uart_0_s1_reset_n;
  reg              uart_0_s1_slavearbiterlockenable;
  wire             uart_0_s1_slavearbiterlockenable2;
  wire             uart_0_s1_unreg_firsttransfer;
  wire             uart_0_s1_waits_for_read;
  wire             uart_0_s1_waits_for_write;
  wire             uart_0_s1_write_n;
  wire    [ 15: 0] uart_0_s1_writedata;
  wire             wait_for_uart_0_s1_counter;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_reasons_to_wait <= 0;
      else 
        d1_reasons_to_wait <= ~uart_0_s1_end_xfer;
    end


  assign uart_0_s1_begins_xfer = ~d1_reasons_to_wait & ((cpu_0_data_master_qualified_request_uart_0_s1));
  //assign uart_0_s1_readdata_from_sa = uart_0_s1_readdata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign uart_0_s1_readdata_from_sa = uart_0_s1_readdata;

  assign cpu_0_data_master_requests_uart_0_s1 = ({cpu_0_data_master_address_to_slave[26 : 5] , 5'b0} == 27'h4002000) & (cpu_0_data_master_read | cpu_0_data_master_write);
  //assign uart_0_s1_dataavailable_from_sa = uart_0_s1_dataavailable so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign uart_0_s1_dataavailable_from_sa = uart_0_s1_dataavailable;

  //assign uart_0_s1_readyfordata_from_sa = uart_0_s1_readyfordata so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign uart_0_s1_readyfordata_from_sa = uart_0_s1_readyfordata;

  //uart_0_s1_arb_share_counter set values, which is an e_mux
  assign uart_0_s1_arb_share_set_values = 1;

  //uart_0_s1_non_bursting_master_requests mux, which is an e_mux
  assign uart_0_s1_non_bursting_master_requests = cpu_0_data_master_requests_uart_0_s1;

  //uart_0_s1_any_bursting_master_saved_grant mux, which is an e_mux
  assign uart_0_s1_any_bursting_master_saved_grant = 0;

  //uart_0_s1_arb_share_counter_next_value assignment, which is an e_assign
  assign uart_0_s1_arb_share_counter_next_value = uart_0_s1_firsttransfer ? (uart_0_s1_arb_share_set_values - 1) : |uart_0_s1_arb_share_counter ? (uart_0_s1_arb_share_counter - 1) : 0;

  //uart_0_s1_allgrants all slave grants, which is an e_mux
  assign uart_0_s1_allgrants = |uart_0_s1_grant_vector;

  //uart_0_s1_end_xfer assignment, which is an e_assign
  assign uart_0_s1_end_xfer = ~(uart_0_s1_waits_for_read | uart_0_s1_waits_for_write);

  //end_xfer_arb_share_counter_term_uart_0_s1 arb share counter enable term, which is an e_assign
  assign end_xfer_arb_share_counter_term_uart_0_s1 = uart_0_s1_end_xfer & (~uart_0_s1_any_bursting_master_saved_grant | in_a_read_cycle | in_a_write_cycle);

  //uart_0_s1_arb_share_counter arbitration counter enable, which is an e_assign
  assign uart_0_s1_arb_counter_enable = (end_xfer_arb_share_counter_term_uart_0_s1 & uart_0_s1_allgrants) | (end_xfer_arb_share_counter_term_uart_0_s1 & ~uart_0_s1_non_bursting_master_requests);

  //uart_0_s1_arb_share_counter counter, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          uart_0_s1_arb_share_counter <= 0;
      else if (uart_0_s1_arb_counter_enable)
          uart_0_s1_arb_share_counter <= uart_0_s1_arb_share_counter_next_value;
    end


  //uart_0_s1_slavearbiterlockenable slave enables arbiterlock, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          uart_0_s1_slavearbiterlockenable <= 0;
      else if ((|uart_0_s1_master_qreq_vector & end_xfer_arb_share_counter_term_uart_0_s1) | (end_xfer_arb_share_counter_term_uart_0_s1 & ~uart_0_s1_non_bursting_master_requests))
          uart_0_s1_slavearbiterlockenable <= |uart_0_s1_arb_share_counter_next_value;
    end


  //cpu_0/data_master uart_0/s1 arbiterlock, which is an e_assign
  assign cpu_0_data_master_arbiterlock = uart_0_s1_slavearbiterlockenable & cpu_0_data_master_continuerequest;

  //uart_0_s1_slavearbiterlockenable2 slave enables arbiterlock2, which is an e_assign
  assign uart_0_s1_slavearbiterlockenable2 = |uart_0_s1_arb_share_counter_next_value;

  //cpu_0/data_master uart_0/s1 arbiterlock2, which is an e_assign
  assign cpu_0_data_master_arbiterlock2 = uart_0_s1_slavearbiterlockenable2 & cpu_0_data_master_continuerequest;

  //uart_0_s1_any_continuerequest at least one master continues requesting, which is an e_assign
  assign uart_0_s1_any_continuerequest = 1;

  //cpu_0_data_master_continuerequest continued request, which is an e_assign
  assign cpu_0_data_master_continuerequest = 1;

  assign cpu_0_data_master_qualified_request_uart_0_s1 = cpu_0_data_master_requests_uart_0_s1 & ~((cpu_0_data_master_read & ((cpu_0_data_master_latency_counter != 0) | (|cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register))));
  //local readdatavalid cpu_0_data_master_read_data_valid_uart_0_s1, which is an e_mux
  assign cpu_0_data_master_read_data_valid_uart_0_s1 = cpu_0_data_master_granted_uart_0_s1 & cpu_0_data_master_read & ~uart_0_s1_waits_for_read;

  //uart_0_s1_writedata mux, which is an e_mux
  assign uart_0_s1_writedata = cpu_0_data_master_writedata;

  //master is always granted when requested
  assign cpu_0_data_master_granted_uart_0_s1 = cpu_0_data_master_qualified_request_uart_0_s1;

  //cpu_0/data_master saved-grant uart_0/s1, which is an e_assign
  assign cpu_0_data_master_saved_grant_uart_0_s1 = cpu_0_data_master_requests_uart_0_s1;

  //allow new arb cycle for uart_0/s1, which is an e_assign
  assign uart_0_s1_allow_new_arb_cycle = 1;

  //placeholder chosen master
  assign uart_0_s1_grant_vector = 1;

  //placeholder vector of master qualified-requests
  assign uart_0_s1_master_qreq_vector = 1;

  assign uart_0_s1_begintransfer = uart_0_s1_begins_xfer;
  //uart_0_s1_reset_n assignment, which is an e_assign
  assign uart_0_s1_reset_n = reset_n;

  assign uart_0_s1_chipselect = cpu_0_data_master_granted_uart_0_s1;
  //uart_0_s1_firsttransfer first transaction, which is an e_assign
  assign uart_0_s1_firsttransfer = uart_0_s1_begins_xfer ? uart_0_s1_unreg_firsttransfer : uart_0_s1_reg_firsttransfer;

  //uart_0_s1_unreg_firsttransfer first transaction, which is an e_assign
  assign uart_0_s1_unreg_firsttransfer = ~(uart_0_s1_slavearbiterlockenable & uart_0_s1_any_continuerequest);

  //uart_0_s1_reg_firsttransfer first transaction, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          uart_0_s1_reg_firsttransfer <= 1'b1;
      else if (uart_0_s1_begins_xfer)
          uart_0_s1_reg_firsttransfer <= uart_0_s1_unreg_firsttransfer;
    end


  //uart_0_s1_beginbursttransfer_internal begin burst transfer, which is an e_assign
  assign uart_0_s1_beginbursttransfer_internal = uart_0_s1_begins_xfer;

  //~uart_0_s1_read_n assignment, which is an e_mux
  assign uart_0_s1_read_n = ~(cpu_0_data_master_granted_uart_0_s1 & cpu_0_data_master_read);

  //~uart_0_s1_write_n assignment, which is an e_mux
  assign uart_0_s1_write_n = ~(cpu_0_data_master_granted_uart_0_s1 & cpu_0_data_master_write);

  assign shifted_address_to_uart_0_s1_from_cpu_0_data_master = cpu_0_data_master_address_to_slave;
  //uart_0_s1_address mux, which is an e_mux
  assign uart_0_s1_address = shifted_address_to_uart_0_s1_from_cpu_0_data_master >> 2;

  //d1_uart_0_s1_end_xfer register, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          d1_uart_0_s1_end_xfer <= 1;
      else 
        d1_uart_0_s1_end_xfer <= uart_0_s1_end_xfer;
    end


  //uart_0_s1_waits_for_read in a cycle, which is an e_mux
  assign uart_0_s1_waits_for_read = uart_0_s1_in_a_read_cycle & uart_0_s1_begins_xfer;

  //uart_0_s1_in_a_read_cycle assignment, which is an e_assign
  assign uart_0_s1_in_a_read_cycle = cpu_0_data_master_granted_uart_0_s1 & cpu_0_data_master_read;

  //in_a_read_cycle assignment, which is an e_mux
  assign in_a_read_cycle = uart_0_s1_in_a_read_cycle;

  //uart_0_s1_waits_for_write in a cycle, which is an e_mux
  assign uart_0_s1_waits_for_write = uart_0_s1_in_a_write_cycle & uart_0_s1_begins_xfer;

  //uart_0_s1_in_a_write_cycle assignment, which is an e_assign
  assign uart_0_s1_in_a_write_cycle = cpu_0_data_master_granted_uart_0_s1 & cpu_0_data_master_write;

  //in_a_write_cycle assignment, which is an e_mux
  assign in_a_write_cycle = uart_0_s1_in_a_write_cycle;

  assign wait_for_uart_0_s1_counter = 0;
  //assign uart_0_s1_irq_from_sa = uart_0_s1_irq so that symbol knows where to group signals which may go to master only, which is an e_assign
  assign uart_0_s1_irq_from_sa = uart_0_s1_irq;


//synthesis translate_off
//////////////// SIMULATION-ONLY CONTENTS
  //uart_0/s1 enable non-zero assertions, which is an e_register
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          enable_nonzero_assertions <= 0;
      else 
        enable_nonzero_assertions <= 1'b1;
    end



//////////////// END SIMULATION-ONLY CONTENTS

//synthesis translate_on

endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module RC_2C8V3_Nios_CPU_reset_clk_0_domain_synch_module (
                                                           // inputs:
                                                            clk,
                                                            data_in,
                                                            reset_n,

                                                           // outputs:
                                                            data_out
                                                         )
;

  output           data_out;
  input            clk;
  input            data_in;
  input            reset_n;

  reg              data_in_d1 /* synthesis ALTERA_ATTRIBUTE = "{-from \"*\"} CUT=ON ; PRESERVE_REGISTER=ON ; SUPPRESS_DA_RULE_INTERNAL=R101"  */;
  reg              data_out /* synthesis ALTERA_ATTRIBUTE = "PRESERVE_REGISTER=ON ; SUPPRESS_DA_RULE_INTERNAL=R101"  */;
  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          data_in_d1 <= 0;
      else 
        data_in_d1 <= data_in;
    end


  always @(posedge clk or negedge reset_n)
    begin
      if (reset_n == 0)
          data_out <= 0;
      else 
        data_out <= data_in_d1;
    end



endmodule


// synthesis translate_off
`timescale 1ns / 1ps
// synthesis translate_on

// turn off superfluous verilog processor warnings 
// altera message_level Level1 
// altera message_off 10034 10035 10036 10037 10230 10240 10030 

module RC_2C8V3_Nios_CPU (
                           // 1) global signals:
                            clk_0,
                            reset_n,

                           // the_ADC_DATA
                            in_port_to_the_ADC_DATA,

                           // the_BUZZER_DATA
                            in_port_to_the_BUZZER_DATA,

                           // the_DAC_DATA
                            in_port_to_the_DAC_DATA,

                           // the_ETH_CLKOUT_I
                            in_port_to_the_ETH_CLKOUT_I,

                           // the_ETH_CS_O
                            out_port_from_the_ETH_CS_O,

                           // the_ETH_INT_I
                            in_port_to_the_ETH_INT_I,

                           // the_ETH_RESET_O
                            out_port_from_the_ETH_RESET_O,

                           // the_ETH_SCK_O
                            out_port_from_the_ETH_SCK_O,

                           // the_ETH_SI_O
                            out_port_from_the_ETH_SI_O,

                           // the_ETH_SO_I
                            in_port_to_the_ETH_SO_I,

                           // the_ETH_WOL_I
                            in_port_to_the_ETH_WOL_I,

                           // the_IR_DATA
                            in_port_to_the_IR_DATA,

                           // the_KEY_FOCUS
                            in_port_to_the_KEY_FOCUS,

                           // the_LCD_CS
                            out_port_from_the_LCD_CS,

                           // the_LCD_DATA
                            out_port_from_the_LCD_DATA,

                           // the_LCD_RD
                            out_port_from_the_LCD_RD,

                           // the_LCD_RS
                            out_port_from_the_LCD_RS,

                           // the_LCD_RST
                            out_port_from_the_LCD_RST,

                           // the_LCD_WR
                            out_port_from_the_LCD_WR,

                           // the_LED_DATA
                            in_port_to_the_LED_DATA,

                           // the_PS2_DATA_REC
                            in_port_to_the_PS2_DATA_REC,

                           // the_RTC_DATA
                            in_port_to_the_RTC_DATA,

                           // the_SCL
                            out_port_from_the_SCL,

                           // the_SDA
                            bidir_port_to_and_from_the_SDA,

                           // the_SD_CLK
                            out_port_from_the_SD_CLK,

                           // the_SD_CS
                            out_port_from_the_SD_CS,

                           // the_SD_DI
                            out_port_from_the_SD_DI,

                           // the_SD_DO
                            in_port_to_the_SD_DO,

                           // the_TEMP_DATA
                            in_port_to_the_TEMP_DATA,

                           // the_TUBE_EN
                            out_port_from_the_TUBE_EN,

                           // the_UART_RX_DATA
                            in_port_to_the_UART_RX_DATA,

                           // the_USB_INT_I
                            in_port_to_the_USB_INT_I,

                           // the_USB_PC_I
                            in_port_to_the_USB_PC_I,

                           // the_USB_RST_O
                            out_port_from_the_USB_RST_O,

                           // the_USB_SCK_O
                            out_port_from_the_USB_SCK_O,

                           // the_USB_SCS_O
                            out_port_from_the_USB_SCS_O,

                           // the_USB_SDI_O
                            out_port_from_the_USB_SDI_O,

                           // the_USB_SDO_I
                            in_port_to_the_USB_SDO_I,

                           // the_sdram_0
                            zs_addr_from_the_sdram_0,
                            zs_ba_from_the_sdram_0,
                            zs_cas_n_from_the_sdram_0,
                            zs_cke_from_the_sdram_0,
                            zs_cs_n_from_the_sdram_0,
                            zs_dq_to_and_from_the_sdram_0,
                            zs_dqm_from_the_sdram_0,
                            zs_ras_n_from_the_sdram_0,
                            zs_we_n_from_the_sdram_0,

                           // the_uart_0
                            rxd_to_the_uart_0,
                            txd_from_the_uart_0
                         )
;

  inout            bidir_port_to_and_from_the_SDA;
  output           out_port_from_the_ETH_CS_O;
  output           out_port_from_the_ETH_RESET_O;
  output           out_port_from_the_ETH_SCK_O;
  output           out_port_from_the_ETH_SI_O;
  output           out_port_from_the_LCD_CS;
  output  [ 15: 0] out_port_from_the_LCD_DATA;
  output           out_port_from_the_LCD_RD;
  output           out_port_from_the_LCD_RS;
  output           out_port_from_the_LCD_RST;
  output           out_port_from_the_LCD_WR;
  output           out_port_from_the_SCL;
  output           out_port_from_the_SD_CLK;
  output           out_port_from_the_SD_CS;
  output           out_port_from_the_SD_DI;
  output  [  3: 0] out_port_from_the_TUBE_EN;
  output           out_port_from_the_USB_RST_O;
  output           out_port_from_the_USB_SCK_O;
  output           out_port_from_the_USB_SCS_O;
  output           out_port_from_the_USB_SDI_O;
  output           txd_from_the_uart_0;
  output  [ 12: 0] zs_addr_from_the_sdram_0;
  output  [  1: 0] zs_ba_from_the_sdram_0;
  output           zs_cas_n_from_the_sdram_0;
  output           zs_cke_from_the_sdram_0;
  output           zs_cs_n_from_the_sdram_0;
  inout   [ 15: 0] zs_dq_to_and_from_the_sdram_0;
  output  [  1: 0] zs_dqm_from_the_sdram_0;
  output           zs_ras_n_from_the_sdram_0;
  output           zs_we_n_from_the_sdram_0;
  input            clk_0;
  input   [  7: 0] in_port_to_the_ADC_DATA;
  input            in_port_to_the_BUZZER_DATA;
  input   [  7: 0] in_port_to_the_DAC_DATA;
  input            in_port_to_the_ETH_CLKOUT_I;
  input   [  7: 0] in_port_to_the_ETH_INT_I;
  input            in_port_to_the_ETH_SO_I;
  input            in_port_to_the_ETH_WOL_I;
  input   [ 31: 0] in_port_to_the_IR_DATA;
  input   [  3: 0] in_port_to_the_KEY_FOCUS;
  input   [  5: 0] in_port_to_the_LED_DATA;
  input   [ 15: 0] in_port_to_the_PS2_DATA_REC;
  input   [ 23: 0] in_port_to_the_RTC_DATA;
  input            in_port_to_the_SD_DO;
  input   [ 15: 0] in_port_to_the_TEMP_DATA;
  input   [  7: 0] in_port_to_the_UART_RX_DATA;
  input            in_port_to_the_USB_INT_I;
  input            in_port_to_the_USB_PC_I;
  input            in_port_to_the_USB_SDO_I;
  input            reset_n;
  input            rxd_to_the_uart_0;

  wire    [  1: 0] ADC_DATA_s1_address;
  wire             ADC_DATA_s1_chipselect;
  wire    [ 31: 0] ADC_DATA_s1_readdata;
  wire    [ 31: 0] ADC_DATA_s1_readdata_from_sa;
  wire             ADC_DATA_s1_reset_n;
  wire             ADC_DATA_s1_write_n;
  wire    [ 31: 0] ADC_DATA_s1_writedata;
  wire    [  1: 0] BUZZER_DATA_s1_address;
  wire             BUZZER_DATA_s1_chipselect;
  wire    [ 31: 0] BUZZER_DATA_s1_readdata;
  wire    [ 31: 0] BUZZER_DATA_s1_readdata_from_sa;
  wire             BUZZER_DATA_s1_reset_n;
  wire             BUZZER_DATA_s1_write_n;
  wire    [ 31: 0] BUZZER_DATA_s1_writedata;
  wire    [  1: 0] DAC_DATA_s1_address;
  wire             DAC_DATA_s1_chipselect;
  wire    [ 31: 0] DAC_DATA_s1_readdata;
  wire    [ 31: 0] DAC_DATA_s1_readdata_from_sa;
  wire             DAC_DATA_s1_reset_n;
  wire             DAC_DATA_s1_write_n;
  wire    [ 31: 0] DAC_DATA_s1_writedata;
  wire    [  1: 0] ETH_CLKOUT_I_s1_address;
  wire             ETH_CLKOUT_I_s1_chipselect;
  wire    [ 31: 0] ETH_CLKOUT_I_s1_readdata;
  wire    [ 31: 0] ETH_CLKOUT_I_s1_readdata_from_sa;
  wire             ETH_CLKOUT_I_s1_reset_n;
  wire             ETH_CLKOUT_I_s1_write_n;
  wire    [ 31: 0] ETH_CLKOUT_I_s1_writedata;
  wire    [  1: 0] ETH_CS_O_s1_address;
  wire             ETH_CS_O_s1_chipselect;
  wire    [ 31: 0] ETH_CS_O_s1_readdata;
  wire    [ 31: 0] ETH_CS_O_s1_readdata_from_sa;
  wire             ETH_CS_O_s1_reset_n;
  wire             ETH_CS_O_s1_write_n;
  wire    [ 31: 0] ETH_CS_O_s1_writedata;
  wire    [  1: 0] ETH_INT_I_s1_address;
  wire             ETH_INT_I_s1_chipselect;
  wire    [ 31: 0] ETH_INT_I_s1_readdata;
  wire    [ 31: 0] ETH_INT_I_s1_readdata_from_sa;
  wire             ETH_INT_I_s1_reset_n;
  wire             ETH_INT_I_s1_write_n;
  wire    [ 31: 0] ETH_INT_I_s1_writedata;
  wire    [  1: 0] ETH_RESET_O_s1_address;
  wire             ETH_RESET_O_s1_chipselect;
  wire    [ 31: 0] ETH_RESET_O_s1_readdata;
  wire    [ 31: 0] ETH_RESET_O_s1_readdata_from_sa;
  wire             ETH_RESET_O_s1_reset_n;
  wire             ETH_RESET_O_s1_write_n;
  wire    [ 31: 0] ETH_RESET_O_s1_writedata;
  wire    [  1: 0] ETH_SCK_O_s1_address;
  wire             ETH_SCK_O_s1_chipselect;
  wire    [ 31: 0] ETH_SCK_O_s1_readdata;
  wire    [ 31: 0] ETH_SCK_O_s1_readdata_from_sa;
  wire             ETH_SCK_O_s1_reset_n;
  wire             ETH_SCK_O_s1_write_n;
  wire    [ 31: 0] ETH_SCK_O_s1_writedata;
  wire    [  1: 0] ETH_SI_O_s1_address;
  wire             ETH_SI_O_s1_chipselect;
  wire    [ 31: 0] ETH_SI_O_s1_readdata;
  wire    [ 31: 0] ETH_SI_O_s1_readdata_from_sa;
  wire             ETH_SI_O_s1_reset_n;
  wire             ETH_SI_O_s1_write_n;
  wire    [ 31: 0] ETH_SI_O_s1_writedata;
  wire    [  1: 0] ETH_SO_I_s1_address;
  wire             ETH_SO_I_s1_chipselect;
  wire    [ 31: 0] ETH_SO_I_s1_readdata;
  wire    [ 31: 0] ETH_SO_I_s1_readdata_from_sa;
  wire             ETH_SO_I_s1_reset_n;
  wire             ETH_SO_I_s1_write_n;
  wire    [ 31: 0] ETH_SO_I_s1_writedata;
  wire    [  1: 0] ETH_WOL_I_s1_address;
  wire             ETH_WOL_I_s1_chipselect;
  wire    [ 31: 0] ETH_WOL_I_s1_readdata;
  wire    [ 31: 0] ETH_WOL_I_s1_readdata_from_sa;
  wire             ETH_WOL_I_s1_reset_n;
  wire             ETH_WOL_I_s1_write_n;
  wire    [ 31: 0] ETH_WOL_I_s1_writedata;
  wire    [  1: 0] IR_DATA_s1_address;
  wire             IR_DATA_s1_chipselect;
  wire    [ 31: 0] IR_DATA_s1_readdata;
  wire    [ 31: 0] IR_DATA_s1_readdata_from_sa;
  wire             IR_DATA_s1_reset_n;
  wire             IR_DATA_s1_write_n;
  wire    [ 31: 0] IR_DATA_s1_writedata;
  wire    [  1: 0] KEY_FOCUS_s1_address;
  wire             KEY_FOCUS_s1_chipselect;
  wire    [ 31: 0] KEY_FOCUS_s1_readdata;
  wire    [ 31: 0] KEY_FOCUS_s1_readdata_from_sa;
  wire             KEY_FOCUS_s1_reset_n;
  wire             KEY_FOCUS_s1_write_n;
  wire    [ 31: 0] KEY_FOCUS_s1_writedata;
  wire    [  1: 0] LCD_CS_s1_address;
  wire             LCD_CS_s1_chipselect;
  wire    [ 31: 0] LCD_CS_s1_readdata;
  wire    [ 31: 0] LCD_CS_s1_readdata_from_sa;
  wire             LCD_CS_s1_reset_n;
  wire             LCD_CS_s1_write_n;
  wire    [ 31: 0] LCD_CS_s1_writedata;
  wire    [  1: 0] LCD_DATA_s1_address;
  wire             LCD_DATA_s1_chipselect;
  wire    [ 31: 0] LCD_DATA_s1_readdata;
  wire    [ 31: 0] LCD_DATA_s1_readdata_from_sa;
  wire             LCD_DATA_s1_reset_n;
  wire             LCD_DATA_s1_write_n;
  wire    [ 31: 0] LCD_DATA_s1_writedata;
  wire    [  1: 0] LCD_RD_s1_address;
  wire             LCD_RD_s1_chipselect;
  wire    [ 31: 0] LCD_RD_s1_readdata;
  wire    [ 31: 0] LCD_RD_s1_readdata_from_sa;
  wire             LCD_RD_s1_reset_n;
  wire             LCD_RD_s1_write_n;
  wire    [ 31: 0] LCD_RD_s1_writedata;
  wire    [  1: 0] LCD_RST_s1_address;
  wire             LCD_RST_s1_chipselect;
  wire    [ 31: 0] LCD_RST_s1_readdata;
  wire    [ 31: 0] LCD_RST_s1_readdata_from_sa;
  wire             LCD_RST_s1_reset_n;
  wire             LCD_RST_s1_write_n;
  wire    [ 31: 0] LCD_RST_s1_writedata;
  wire    [  1: 0] LCD_RS_s1_address;
  wire             LCD_RS_s1_chipselect;
  wire    [ 31: 0] LCD_RS_s1_readdata;
  wire    [ 31: 0] LCD_RS_s1_readdata_from_sa;
  wire             LCD_RS_s1_reset_n;
  wire             LCD_RS_s1_write_n;
  wire    [ 31: 0] LCD_RS_s1_writedata;
  wire    [  1: 0] LCD_WR_s1_address;
  wire             LCD_WR_s1_chipselect;
  wire    [ 31: 0] LCD_WR_s1_readdata;
  wire    [ 31: 0] LCD_WR_s1_readdata_from_sa;
  wire             LCD_WR_s1_reset_n;
  wire             LCD_WR_s1_write_n;
  wire    [ 31: 0] LCD_WR_s1_writedata;
  wire    [  1: 0] LED_DATA_s1_address;
  wire             LED_DATA_s1_chipselect;
  wire    [ 31: 0] LED_DATA_s1_readdata;
  wire    [ 31: 0] LED_DATA_s1_readdata_from_sa;
  wire             LED_DATA_s1_reset_n;
  wire             LED_DATA_s1_write_n;
  wire    [ 31: 0] LED_DATA_s1_writedata;
  wire    [  1: 0] PS2_DATA_REC_s1_address;
  wire             PS2_DATA_REC_s1_chipselect;
  wire    [ 31: 0] PS2_DATA_REC_s1_readdata;
  wire    [ 31: 0] PS2_DATA_REC_s1_readdata_from_sa;
  wire             PS2_DATA_REC_s1_reset_n;
  wire             PS2_DATA_REC_s1_write_n;
  wire    [ 31: 0] PS2_DATA_REC_s1_writedata;
  wire    [  1: 0] RTC_DATA_s1_address;
  wire             RTC_DATA_s1_chipselect;
  wire    [ 31: 0] RTC_DATA_s1_readdata;
  wire    [ 31: 0] RTC_DATA_s1_readdata_from_sa;
  wire             RTC_DATA_s1_reset_n;
  wire             RTC_DATA_s1_write_n;
  wire    [ 31: 0] RTC_DATA_s1_writedata;
  wire    [  1: 0] SCL_s1_address;
  wire             SCL_s1_chipselect;
  wire    [ 31: 0] SCL_s1_readdata;
  wire    [ 31: 0] SCL_s1_readdata_from_sa;
  wire             SCL_s1_reset_n;
  wire             SCL_s1_write_n;
  wire    [ 31: 0] SCL_s1_writedata;
  wire    [  1: 0] SDA_s1_address;
  wire             SDA_s1_chipselect;
  wire    [ 31: 0] SDA_s1_readdata;
  wire    [ 31: 0] SDA_s1_readdata_from_sa;
  wire             SDA_s1_reset_n;
  wire             SDA_s1_write_n;
  wire    [ 31: 0] SDA_s1_writedata;
  wire    [  1: 0] SD_CLK_s1_address;
  wire             SD_CLK_s1_chipselect;
  wire    [ 31: 0] SD_CLK_s1_readdata;
  wire    [ 31: 0] SD_CLK_s1_readdata_from_sa;
  wire             SD_CLK_s1_reset_n;
  wire             SD_CLK_s1_write_n;
  wire    [ 31: 0] SD_CLK_s1_writedata;
  wire    [  1: 0] SD_CS_s1_address;
  wire             SD_CS_s1_chipselect;
  wire    [ 31: 0] SD_CS_s1_readdata;
  wire    [ 31: 0] SD_CS_s1_readdata_from_sa;
  wire             SD_CS_s1_reset_n;
  wire             SD_CS_s1_write_n;
  wire    [ 31: 0] SD_CS_s1_writedata;
  wire    [  1: 0] SD_DI_s1_address;
  wire             SD_DI_s1_chipselect;
  wire    [ 31: 0] SD_DI_s1_readdata;
  wire    [ 31: 0] SD_DI_s1_readdata_from_sa;
  wire             SD_DI_s1_reset_n;
  wire             SD_DI_s1_write_n;
  wire    [ 31: 0] SD_DI_s1_writedata;
  wire    [  1: 0] SD_DO_s1_address;
  wire             SD_DO_s1_chipselect;
  wire    [ 31: 0] SD_DO_s1_readdata;
  wire    [ 31: 0] SD_DO_s1_readdata_from_sa;
  wire             SD_DO_s1_reset_n;
  wire             SD_DO_s1_write_n;
  wire    [ 31: 0] SD_DO_s1_writedata;
  wire    [  1: 0] TEMP_DATA_s1_address;
  wire             TEMP_DATA_s1_chipselect;
  wire    [ 31: 0] TEMP_DATA_s1_readdata;
  wire    [ 31: 0] TEMP_DATA_s1_readdata_from_sa;
  wire             TEMP_DATA_s1_reset_n;
  wire             TEMP_DATA_s1_write_n;
  wire    [ 31: 0] TEMP_DATA_s1_writedata;
  wire    [  1: 0] TUBE_EN_s1_address;
  wire             TUBE_EN_s1_chipselect;
  wire    [ 31: 0] TUBE_EN_s1_readdata;
  wire    [ 31: 0] TUBE_EN_s1_readdata_from_sa;
  wire             TUBE_EN_s1_reset_n;
  wire             TUBE_EN_s1_write_n;
  wire    [ 31: 0] TUBE_EN_s1_writedata;
  wire    [  1: 0] UART_RX_DATA_s1_address;
  wire             UART_RX_DATA_s1_chipselect;
  wire    [ 31: 0] UART_RX_DATA_s1_readdata;
  wire    [ 31: 0] UART_RX_DATA_s1_readdata_from_sa;
  wire             UART_RX_DATA_s1_reset_n;
  wire             UART_RX_DATA_s1_write_n;
  wire    [ 31: 0] UART_RX_DATA_s1_writedata;
  wire    [  1: 0] USB_INT_I_s1_address;
  wire    [ 31: 0] USB_INT_I_s1_readdata;
  wire    [ 31: 0] USB_INT_I_s1_readdata_from_sa;
  wire             USB_INT_I_s1_reset_n;
  wire    [  1: 0] USB_PC_I_s1_address;
  wire             USB_PC_I_s1_chipselect;
  wire    [ 31: 0] USB_PC_I_s1_readdata;
  wire    [ 31: 0] USB_PC_I_s1_readdata_from_sa;
  wire             USB_PC_I_s1_reset_n;
  wire             USB_PC_I_s1_write_n;
  wire    [ 31: 0] USB_PC_I_s1_writedata;
  wire    [  1: 0] USB_RST_O_s1_address;
  wire             USB_RST_O_s1_chipselect;
  wire    [ 31: 0] USB_RST_O_s1_readdata;
  wire    [ 31: 0] USB_RST_O_s1_readdata_from_sa;
  wire             USB_RST_O_s1_reset_n;
  wire             USB_RST_O_s1_write_n;
  wire    [ 31: 0] USB_RST_O_s1_writedata;
  wire    [  1: 0] USB_SCK_O_s1_address;
  wire             USB_SCK_O_s1_chipselect;
  wire    [ 31: 0] USB_SCK_O_s1_readdata;
  wire    [ 31: 0] USB_SCK_O_s1_readdata_from_sa;
  wire             USB_SCK_O_s1_reset_n;
  wire             USB_SCK_O_s1_write_n;
  wire    [ 31: 0] USB_SCK_O_s1_writedata;
  wire    [  1: 0] USB_SCS_O_s1_address;
  wire             USB_SCS_O_s1_chipselect;
  wire    [ 31: 0] USB_SCS_O_s1_readdata;
  wire    [ 31: 0] USB_SCS_O_s1_readdata_from_sa;
  wire             USB_SCS_O_s1_reset_n;
  wire             USB_SCS_O_s1_write_n;
  wire    [ 31: 0] USB_SCS_O_s1_writedata;
  wire    [  1: 0] USB_SDI_O_s1_address;
  wire             USB_SDI_O_s1_chipselect;
  wire    [ 31: 0] USB_SDI_O_s1_readdata;
  wire    [ 31: 0] USB_SDI_O_s1_readdata_from_sa;
  wire             USB_SDI_O_s1_reset_n;
  wire             USB_SDI_O_s1_write_n;
  wire    [ 31: 0] USB_SDI_O_s1_writedata;
  wire    [  1: 0] USB_SDO_I_s1_address;
  wire             USB_SDO_I_s1_chipselect;
  wire    [ 31: 0] USB_SDO_I_s1_readdata;
  wire    [ 31: 0] USB_SDO_I_s1_readdata_from_sa;
  wire             USB_SDO_I_s1_reset_n;
  wire             USB_SDO_I_s1_write_n;
  wire    [ 31: 0] USB_SDO_I_s1_writedata;
  wire             bidir_port_to_and_from_the_SDA;
  wire             clk_0_reset_n;
  wire    [ 26: 0] cpu_0_data_master_address;
  wire    [ 26: 0] cpu_0_data_master_address_to_slave;
  wire    [  3: 0] cpu_0_data_master_byteenable;
  wire    [  1: 0] cpu_0_data_master_byteenable_sdram_0_s1;
  wire    [  1: 0] cpu_0_data_master_dbs_address;
  wire    [ 15: 0] cpu_0_data_master_dbs_write_16;
  wire             cpu_0_data_master_debugaccess;
  wire             cpu_0_data_master_granted_ADC_DATA_s1;
  wire             cpu_0_data_master_granted_BUZZER_DATA_s1;
  wire             cpu_0_data_master_granted_DAC_DATA_s1;
  wire             cpu_0_data_master_granted_ETH_CLKOUT_I_s1;
  wire             cpu_0_data_master_granted_ETH_CS_O_s1;
  wire             cpu_0_data_master_granted_ETH_INT_I_s1;
  wire             cpu_0_data_master_granted_ETH_RESET_O_s1;
  wire             cpu_0_data_master_granted_ETH_SCK_O_s1;
  wire             cpu_0_data_master_granted_ETH_SI_O_s1;
  wire             cpu_0_data_master_granted_ETH_SO_I_s1;
  wire             cpu_0_data_master_granted_ETH_WOL_I_s1;
  wire             cpu_0_data_master_granted_IR_DATA_s1;
  wire             cpu_0_data_master_granted_KEY_FOCUS_s1;
  wire             cpu_0_data_master_granted_LCD_CS_s1;
  wire             cpu_0_data_master_granted_LCD_DATA_s1;
  wire             cpu_0_data_master_granted_LCD_RD_s1;
  wire             cpu_0_data_master_granted_LCD_RST_s1;
  wire             cpu_0_data_master_granted_LCD_RS_s1;
  wire             cpu_0_data_master_granted_LCD_WR_s1;
  wire             cpu_0_data_master_granted_LED_DATA_s1;
  wire             cpu_0_data_master_granted_PS2_DATA_REC_s1;
  wire             cpu_0_data_master_granted_RTC_DATA_s1;
  wire             cpu_0_data_master_granted_SCL_s1;
  wire             cpu_0_data_master_granted_SDA_s1;
  wire             cpu_0_data_master_granted_SD_CLK_s1;
  wire             cpu_0_data_master_granted_SD_CS_s1;
  wire             cpu_0_data_master_granted_SD_DI_s1;
  wire             cpu_0_data_master_granted_SD_DO_s1;
  wire             cpu_0_data_master_granted_TEMP_DATA_s1;
  wire             cpu_0_data_master_granted_TUBE_EN_s1;
  wire             cpu_0_data_master_granted_UART_RX_DATA_s1;
  wire             cpu_0_data_master_granted_USB_INT_I_s1;
  wire             cpu_0_data_master_granted_USB_PC_I_s1;
  wire             cpu_0_data_master_granted_USB_RST_O_s1;
  wire             cpu_0_data_master_granted_USB_SCK_O_s1;
  wire             cpu_0_data_master_granted_USB_SCS_O_s1;
  wire             cpu_0_data_master_granted_USB_SDI_O_s1;
  wire             cpu_0_data_master_granted_USB_SDO_I_s1;
  wire             cpu_0_data_master_granted_cpu_0_jtag_debug_module;
  wire             cpu_0_data_master_granted_epcs_flash_controller_0_epcs_control_port;
  wire             cpu_0_data_master_granted_sdram_0_s1;
  wire             cpu_0_data_master_granted_sysid_0_control_slave;
  wire             cpu_0_data_master_granted_timer_0_s1;
  wire             cpu_0_data_master_granted_timer_1_s1;
  wire             cpu_0_data_master_granted_uart_0_s1;
  wire    [ 31: 0] cpu_0_data_master_irq;
  wire             cpu_0_data_master_latency_counter;
  wire             cpu_0_data_master_qualified_request_ADC_DATA_s1;
  wire             cpu_0_data_master_qualified_request_BUZZER_DATA_s1;
  wire             cpu_0_data_master_qualified_request_DAC_DATA_s1;
  wire             cpu_0_data_master_qualified_request_ETH_CLKOUT_I_s1;
  wire             cpu_0_data_master_qualified_request_ETH_CS_O_s1;
  wire             cpu_0_data_master_qualified_request_ETH_INT_I_s1;
  wire             cpu_0_data_master_qualified_request_ETH_RESET_O_s1;
  wire             cpu_0_data_master_qualified_request_ETH_SCK_O_s1;
  wire             cpu_0_data_master_qualified_request_ETH_SI_O_s1;
  wire             cpu_0_data_master_qualified_request_ETH_SO_I_s1;
  wire             cpu_0_data_master_qualified_request_ETH_WOL_I_s1;
  wire             cpu_0_data_master_qualified_request_IR_DATA_s1;
  wire             cpu_0_data_master_qualified_request_KEY_FOCUS_s1;
  wire             cpu_0_data_master_qualified_request_LCD_CS_s1;
  wire             cpu_0_data_master_qualified_request_LCD_DATA_s1;
  wire             cpu_0_data_master_qualified_request_LCD_RD_s1;
  wire             cpu_0_data_master_qualified_request_LCD_RST_s1;
  wire             cpu_0_data_master_qualified_request_LCD_RS_s1;
  wire             cpu_0_data_master_qualified_request_LCD_WR_s1;
  wire             cpu_0_data_master_qualified_request_LED_DATA_s1;
  wire             cpu_0_data_master_qualified_request_PS2_DATA_REC_s1;
  wire             cpu_0_data_master_qualified_request_RTC_DATA_s1;
  wire             cpu_0_data_master_qualified_request_SCL_s1;
  wire             cpu_0_data_master_qualified_request_SDA_s1;
  wire             cpu_0_data_master_qualified_request_SD_CLK_s1;
  wire             cpu_0_data_master_qualified_request_SD_CS_s1;
  wire             cpu_0_data_master_qualified_request_SD_DI_s1;
  wire             cpu_0_data_master_qualified_request_SD_DO_s1;
  wire             cpu_0_data_master_qualified_request_TEMP_DATA_s1;
  wire             cpu_0_data_master_qualified_request_TUBE_EN_s1;
  wire             cpu_0_data_master_qualified_request_UART_RX_DATA_s1;
  wire             cpu_0_data_master_qualified_request_USB_INT_I_s1;
  wire             cpu_0_data_master_qualified_request_USB_PC_I_s1;
  wire             cpu_0_data_master_qualified_request_USB_RST_O_s1;
  wire             cpu_0_data_master_qualified_request_USB_SCK_O_s1;
  wire             cpu_0_data_master_qualified_request_USB_SCS_O_s1;
  wire             cpu_0_data_master_qualified_request_USB_SDI_O_s1;
  wire             cpu_0_data_master_qualified_request_USB_SDO_I_s1;
  wire             cpu_0_data_master_qualified_request_cpu_0_jtag_debug_module;
  wire             cpu_0_data_master_qualified_request_epcs_flash_controller_0_epcs_control_port;
  wire             cpu_0_data_master_qualified_request_sdram_0_s1;
  wire             cpu_0_data_master_qualified_request_sysid_0_control_slave;
  wire             cpu_0_data_master_qualified_request_timer_0_s1;
  wire             cpu_0_data_master_qualified_request_timer_1_s1;
  wire             cpu_0_data_master_qualified_request_uart_0_s1;
  wire             cpu_0_data_master_read;
  wire             cpu_0_data_master_read_data_valid_ADC_DATA_s1;
  wire             cpu_0_data_master_read_data_valid_BUZZER_DATA_s1;
  wire             cpu_0_data_master_read_data_valid_DAC_DATA_s1;
  wire             cpu_0_data_master_read_data_valid_ETH_CLKOUT_I_s1;
  wire             cpu_0_data_master_read_data_valid_ETH_CS_O_s1;
  wire             cpu_0_data_master_read_data_valid_ETH_INT_I_s1;
  wire             cpu_0_data_master_read_data_valid_ETH_RESET_O_s1;
  wire             cpu_0_data_master_read_data_valid_ETH_SCK_O_s1;
  wire             cpu_0_data_master_read_data_valid_ETH_SI_O_s1;
  wire             cpu_0_data_master_read_data_valid_ETH_SO_I_s1;
  wire             cpu_0_data_master_read_data_valid_ETH_WOL_I_s1;
  wire             cpu_0_data_master_read_data_valid_IR_DATA_s1;
  wire             cpu_0_data_master_read_data_valid_KEY_FOCUS_s1;
  wire             cpu_0_data_master_read_data_valid_LCD_CS_s1;
  wire             cpu_0_data_master_read_data_valid_LCD_DATA_s1;
  wire             cpu_0_data_master_read_data_valid_LCD_RD_s1;
  wire             cpu_0_data_master_read_data_valid_LCD_RST_s1;
  wire             cpu_0_data_master_read_data_valid_LCD_RS_s1;
  wire             cpu_0_data_master_read_data_valid_LCD_WR_s1;
  wire             cpu_0_data_master_read_data_valid_LED_DATA_s1;
  wire             cpu_0_data_master_read_data_valid_PS2_DATA_REC_s1;
  wire             cpu_0_data_master_read_data_valid_RTC_DATA_s1;
  wire             cpu_0_data_master_read_data_valid_SCL_s1;
  wire             cpu_0_data_master_read_data_valid_SDA_s1;
  wire             cpu_0_data_master_read_data_valid_SD_CLK_s1;
  wire             cpu_0_data_master_read_data_valid_SD_CS_s1;
  wire             cpu_0_data_master_read_data_valid_SD_DI_s1;
  wire             cpu_0_data_master_read_data_valid_SD_DO_s1;
  wire             cpu_0_data_master_read_data_valid_TEMP_DATA_s1;
  wire             cpu_0_data_master_read_data_valid_TUBE_EN_s1;
  wire             cpu_0_data_master_read_data_valid_UART_RX_DATA_s1;
  wire             cpu_0_data_master_read_data_valid_USB_INT_I_s1;
  wire             cpu_0_data_master_read_data_valid_USB_PC_I_s1;
  wire             cpu_0_data_master_read_data_valid_USB_RST_O_s1;
  wire             cpu_0_data_master_read_data_valid_USB_SCK_O_s1;
  wire             cpu_0_data_master_read_data_valid_USB_SCS_O_s1;
  wire             cpu_0_data_master_read_data_valid_USB_SDI_O_s1;
  wire             cpu_0_data_master_read_data_valid_USB_SDO_I_s1;
  wire             cpu_0_data_master_read_data_valid_cpu_0_jtag_debug_module;
  wire             cpu_0_data_master_read_data_valid_epcs_flash_controller_0_epcs_control_port;
  wire             cpu_0_data_master_read_data_valid_sdram_0_s1;
  wire             cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register;
  wire             cpu_0_data_master_read_data_valid_sysid_0_control_slave;
  wire             cpu_0_data_master_read_data_valid_timer_0_s1;
  wire             cpu_0_data_master_read_data_valid_timer_1_s1;
  wire             cpu_0_data_master_read_data_valid_uart_0_s1;
  wire    [ 31: 0] cpu_0_data_master_readdata;
  wire             cpu_0_data_master_readdatavalid;
  wire             cpu_0_data_master_requests_ADC_DATA_s1;
  wire             cpu_0_data_master_requests_BUZZER_DATA_s1;
  wire             cpu_0_data_master_requests_DAC_DATA_s1;
  wire             cpu_0_data_master_requests_ETH_CLKOUT_I_s1;
  wire             cpu_0_data_master_requests_ETH_CS_O_s1;
  wire             cpu_0_data_master_requests_ETH_INT_I_s1;
  wire             cpu_0_data_master_requests_ETH_RESET_O_s1;
  wire             cpu_0_data_master_requests_ETH_SCK_O_s1;
  wire             cpu_0_data_master_requests_ETH_SI_O_s1;
  wire             cpu_0_data_master_requests_ETH_SO_I_s1;
  wire             cpu_0_data_master_requests_ETH_WOL_I_s1;
  wire             cpu_0_data_master_requests_IR_DATA_s1;
  wire             cpu_0_data_master_requests_KEY_FOCUS_s1;
  wire             cpu_0_data_master_requests_LCD_CS_s1;
  wire             cpu_0_data_master_requests_LCD_DATA_s1;
  wire             cpu_0_data_master_requests_LCD_RD_s1;
  wire             cpu_0_data_master_requests_LCD_RST_s1;
  wire             cpu_0_data_master_requests_LCD_RS_s1;
  wire             cpu_0_data_master_requests_LCD_WR_s1;
  wire             cpu_0_data_master_requests_LED_DATA_s1;
  wire             cpu_0_data_master_requests_PS2_DATA_REC_s1;
  wire             cpu_0_data_master_requests_RTC_DATA_s1;
  wire             cpu_0_data_master_requests_SCL_s1;
  wire             cpu_0_data_master_requests_SDA_s1;
  wire             cpu_0_data_master_requests_SD_CLK_s1;
  wire             cpu_0_data_master_requests_SD_CS_s1;
  wire             cpu_0_data_master_requests_SD_DI_s1;
  wire             cpu_0_data_master_requests_SD_DO_s1;
  wire             cpu_0_data_master_requests_TEMP_DATA_s1;
  wire             cpu_0_data_master_requests_TUBE_EN_s1;
  wire             cpu_0_data_master_requests_UART_RX_DATA_s1;
  wire             cpu_0_data_master_requests_USB_INT_I_s1;
  wire             cpu_0_data_master_requests_USB_PC_I_s1;
  wire             cpu_0_data_master_requests_USB_RST_O_s1;
  wire             cpu_0_data_master_requests_USB_SCK_O_s1;
  wire             cpu_0_data_master_requests_USB_SCS_O_s1;
  wire             cpu_0_data_master_requests_USB_SDI_O_s1;
  wire             cpu_0_data_master_requests_USB_SDO_I_s1;
  wire             cpu_0_data_master_requests_cpu_0_jtag_debug_module;
  wire             cpu_0_data_master_requests_epcs_flash_controller_0_epcs_control_port;
  wire             cpu_0_data_master_requests_sdram_0_s1;
  wire             cpu_0_data_master_requests_sysid_0_control_slave;
  wire             cpu_0_data_master_requests_timer_0_s1;
  wire             cpu_0_data_master_requests_timer_1_s1;
  wire             cpu_0_data_master_requests_uart_0_s1;
  wire             cpu_0_data_master_waitrequest;
  wire             cpu_0_data_master_write;
  wire    [ 31: 0] cpu_0_data_master_writedata;
  wire    [ 26: 0] cpu_0_instruction_master_address;
  wire    [ 26: 0] cpu_0_instruction_master_address_to_slave;
  wire    [  1: 0] cpu_0_instruction_master_dbs_address;
  wire             cpu_0_instruction_master_granted_cpu_0_jtag_debug_module;
  wire             cpu_0_instruction_master_granted_epcs_flash_controller_0_epcs_control_port;
  wire             cpu_0_instruction_master_granted_sdram_0_s1;
  wire             cpu_0_instruction_master_latency_counter;
  wire             cpu_0_instruction_master_qualified_request_cpu_0_jtag_debug_module;
  wire             cpu_0_instruction_master_qualified_request_epcs_flash_controller_0_epcs_control_port;
  wire             cpu_0_instruction_master_qualified_request_sdram_0_s1;
  wire             cpu_0_instruction_master_read;
  wire             cpu_0_instruction_master_read_data_valid_cpu_0_jtag_debug_module;
  wire             cpu_0_instruction_master_read_data_valid_epcs_flash_controller_0_epcs_control_port;
  wire             cpu_0_instruction_master_read_data_valid_sdram_0_s1;
  wire             cpu_0_instruction_master_read_data_valid_sdram_0_s1_shift_register;
  wire    [ 31: 0] cpu_0_instruction_master_readdata;
  wire             cpu_0_instruction_master_readdatavalid;
  wire             cpu_0_instruction_master_requests_cpu_0_jtag_debug_module;
  wire             cpu_0_instruction_master_requests_epcs_flash_controller_0_epcs_control_port;
  wire             cpu_0_instruction_master_requests_sdram_0_s1;
  wire             cpu_0_instruction_master_waitrequest;
  wire    [  8: 0] cpu_0_jtag_debug_module_address;
  wire             cpu_0_jtag_debug_module_begintransfer;
  wire    [  3: 0] cpu_0_jtag_debug_module_byteenable;
  wire             cpu_0_jtag_debug_module_chipselect;
  wire             cpu_0_jtag_debug_module_debugaccess;
  wire    [ 31: 0] cpu_0_jtag_debug_module_readdata;
  wire    [ 31: 0] cpu_0_jtag_debug_module_readdata_from_sa;
  wire             cpu_0_jtag_debug_module_reset_n;
  wire             cpu_0_jtag_debug_module_resetrequest;
  wire             cpu_0_jtag_debug_module_resetrequest_from_sa;
  wire             cpu_0_jtag_debug_module_write;
  wire    [ 31: 0] cpu_0_jtag_debug_module_writedata;
  wire             d1_ADC_DATA_s1_end_xfer;
  wire             d1_BUZZER_DATA_s1_end_xfer;
  wire             d1_DAC_DATA_s1_end_xfer;
  wire             d1_ETH_CLKOUT_I_s1_end_xfer;
  wire             d1_ETH_CS_O_s1_end_xfer;
  wire             d1_ETH_INT_I_s1_end_xfer;
  wire             d1_ETH_RESET_O_s1_end_xfer;
  wire             d1_ETH_SCK_O_s1_end_xfer;
  wire             d1_ETH_SI_O_s1_end_xfer;
  wire             d1_ETH_SO_I_s1_end_xfer;
  wire             d1_ETH_WOL_I_s1_end_xfer;
  wire             d1_IR_DATA_s1_end_xfer;
  wire             d1_KEY_FOCUS_s1_end_xfer;
  wire             d1_LCD_CS_s1_end_xfer;
  wire             d1_LCD_DATA_s1_end_xfer;
  wire             d1_LCD_RD_s1_end_xfer;
  wire             d1_LCD_RST_s1_end_xfer;
  wire             d1_LCD_RS_s1_end_xfer;
  wire             d1_LCD_WR_s1_end_xfer;
  wire             d1_LED_DATA_s1_end_xfer;
  wire             d1_PS2_DATA_REC_s1_end_xfer;
  wire             d1_RTC_DATA_s1_end_xfer;
  wire             d1_SCL_s1_end_xfer;
  wire             d1_SDA_s1_end_xfer;
  wire             d1_SD_CLK_s1_end_xfer;
  wire             d1_SD_CS_s1_end_xfer;
  wire             d1_SD_DI_s1_end_xfer;
  wire             d1_SD_DO_s1_end_xfer;
  wire             d1_TEMP_DATA_s1_end_xfer;
  wire             d1_TUBE_EN_s1_end_xfer;
  wire             d1_UART_RX_DATA_s1_end_xfer;
  wire             d1_USB_INT_I_s1_end_xfer;
  wire             d1_USB_PC_I_s1_end_xfer;
  wire             d1_USB_RST_O_s1_end_xfer;
  wire             d1_USB_SCK_O_s1_end_xfer;
  wire             d1_USB_SCS_O_s1_end_xfer;
  wire             d1_USB_SDI_O_s1_end_xfer;
  wire             d1_USB_SDO_I_s1_end_xfer;
  wire             d1_cpu_0_jtag_debug_module_end_xfer;
  wire             d1_epcs_flash_controller_0_epcs_control_port_end_xfer;
  wire             d1_sdram_0_s1_end_xfer;
  wire             d1_sysid_0_control_slave_end_xfer;
  wire             d1_timer_0_s1_end_xfer;
  wire             d1_timer_1_s1_end_xfer;
  wire             d1_uart_0_s1_end_xfer;
  wire    [  8: 0] epcs_flash_controller_0_epcs_control_port_address;
  wire             epcs_flash_controller_0_epcs_control_port_chipselect;
  wire             epcs_flash_controller_0_epcs_control_port_dataavailable;
  wire             epcs_flash_controller_0_epcs_control_port_dataavailable_from_sa;
  wire             epcs_flash_controller_0_epcs_control_port_endofpacket;
  wire             epcs_flash_controller_0_epcs_control_port_endofpacket_from_sa;
  wire             epcs_flash_controller_0_epcs_control_port_irq;
  wire             epcs_flash_controller_0_epcs_control_port_irq_from_sa;
  wire             epcs_flash_controller_0_epcs_control_port_read_n;
  wire    [ 31: 0] epcs_flash_controller_0_epcs_control_port_readdata;
  wire    [ 31: 0] epcs_flash_controller_0_epcs_control_port_readdata_from_sa;
  wire             epcs_flash_controller_0_epcs_control_port_readyfordata;
  wire             epcs_flash_controller_0_epcs_control_port_readyfordata_from_sa;
  wire             epcs_flash_controller_0_epcs_control_port_reset_n;
  wire             epcs_flash_controller_0_epcs_control_port_write_n;
  wire    [ 31: 0] epcs_flash_controller_0_epcs_control_port_writedata;
  wire             out_port_from_the_ETH_CS_O;
  wire             out_port_from_the_ETH_RESET_O;
  wire             out_port_from_the_ETH_SCK_O;
  wire             out_port_from_the_ETH_SI_O;
  wire             out_port_from_the_LCD_CS;
  wire    [ 15: 0] out_port_from_the_LCD_DATA;
  wire             out_port_from_the_LCD_RD;
  wire             out_port_from_the_LCD_RS;
  wire             out_port_from_the_LCD_RST;
  wire             out_port_from_the_LCD_WR;
  wire             out_port_from_the_SCL;
  wire             out_port_from_the_SD_CLK;
  wire             out_port_from_the_SD_CS;
  wire             out_port_from_the_SD_DI;
  wire    [  3: 0] out_port_from_the_TUBE_EN;
  wire             out_port_from_the_USB_RST_O;
  wire             out_port_from_the_USB_SCK_O;
  wire             out_port_from_the_USB_SCS_O;
  wire             out_port_from_the_USB_SDI_O;
  wire             reset_n_sources;
  wire    [ 23: 0] sdram_0_s1_address;
  wire    [  1: 0] sdram_0_s1_byteenable_n;
  wire             sdram_0_s1_chipselect;
  wire             sdram_0_s1_read_n;
  wire    [ 15: 0] sdram_0_s1_readdata;
  wire    [ 15: 0] sdram_0_s1_readdata_from_sa;
  wire             sdram_0_s1_readdatavalid;
  wire             sdram_0_s1_reset_n;
  wire             sdram_0_s1_waitrequest;
  wire             sdram_0_s1_waitrequest_from_sa;
  wire             sdram_0_s1_write_n;
  wire    [ 15: 0] sdram_0_s1_writedata;
  wire             sysid_0_control_slave_address;
  wire             sysid_0_control_slave_clock;
  wire    [ 31: 0] sysid_0_control_slave_readdata;
  wire    [ 31: 0] sysid_0_control_slave_readdata_from_sa;
  wire             sysid_0_control_slave_reset_n;
  wire    [  2: 0] timer_0_s1_address;
  wire             timer_0_s1_chipselect;
  wire             timer_0_s1_irq;
  wire             timer_0_s1_irq_from_sa;
  wire    [ 15: 0] timer_0_s1_readdata;
  wire    [ 15: 0] timer_0_s1_readdata_from_sa;
  wire             timer_0_s1_reset_n;
  wire             timer_0_s1_write_n;
  wire    [ 15: 0] timer_0_s1_writedata;
  wire    [  2: 0] timer_1_s1_address;
  wire             timer_1_s1_chipselect;
  wire             timer_1_s1_irq;
  wire             timer_1_s1_irq_from_sa;
  wire    [ 15: 0] timer_1_s1_readdata;
  wire    [ 15: 0] timer_1_s1_readdata_from_sa;
  wire             timer_1_s1_reset_n;
  wire             timer_1_s1_write_n;
  wire    [ 15: 0] timer_1_s1_writedata;
  wire             txd_from_the_uart_0;
  wire    [  2: 0] uart_0_s1_address;
  wire             uart_0_s1_begintransfer;
  wire             uart_0_s1_chipselect;
  wire             uart_0_s1_dataavailable;
  wire             uart_0_s1_dataavailable_from_sa;
  wire             uart_0_s1_irq;
  wire             uart_0_s1_irq_from_sa;
  wire             uart_0_s1_read_n;
  wire    [ 15: 0] uart_0_s1_readdata;
  wire    [ 15: 0] uart_0_s1_readdata_from_sa;
  wire             uart_0_s1_readyfordata;
  wire             uart_0_s1_readyfordata_from_sa;
  wire             uart_0_s1_reset_n;
  wire             uart_0_s1_write_n;
  wire    [ 15: 0] uart_0_s1_writedata;
  wire    [ 12: 0] zs_addr_from_the_sdram_0;
  wire    [  1: 0] zs_ba_from_the_sdram_0;
  wire             zs_cas_n_from_the_sdram_0;
  wire             zs_cke_from_the_sdram_0;
  wire             zs_cs_n_from_the_sdram_0;
  wire    [ 15: 0] zs_dq_to_and_from_the_sdram_0;
  wire    [  1: 0] zs_dqm_from_the_sdram_0;
  wire             zs_ras_n_from_the_sdram_0;
  wire             zs_we_n_from_the_sdram_0;
  ADC_DATA_s1_arbitrator the_ADC_DATA_s1
    (
      .ADC_DATA_s1_address                                         (ADC_DATA_s1_address),
      .ADC_DATA_s1_chipselect                                      (ADC_DATA_s1_chipselect),
      .ADC_DATA_s1_readdata                                        (ADC_DATA_s1_readdata),
      .ADC_DATA_s1_readdata_from_sa                                (ADC_DATA_s1_readdata_from_sa),
      .ADC_DATA_s1_reset_n                                         (ADC_DATA_s1_reset_n),
      .ADC_DATA_s1_write_n                                         (ADC_DATA_s1_write_n),
      .ADC_DATA_s1_writedata                                       (ADC_DATA_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_ADC_DATA_s1                       (cpu_0_data_master_granted_ADC_DATA_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_ADC_DATA_s1             (cpu_0_data_master_qualified_request_ADC_DATA_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_ADC_DATA_s1               (cpu_0_data_master_read_data_valid_ADC_DATA_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_ADC_DATA_s1                      (cpu_0_data_master_requests_ADC_DATA_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_ADC_DATA_s1_end_xfer                                     (d1_ADC_DATA_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  ADC_DATA the_ADC_DATA
    (
      .address    (ADC_DATA_s1_address),
      .chipselect (ADC_DATA_s1_chipselect),
      .clk        (clk_0),
      .in_port    (in_port_to_the_ADC_DATA),
      .readdata   (ADC_DATA_s1_readdata),
      .reset_n    (ADC_DATA_s1_reset_n),
      .write_n    (ADC_DATA_s1_write_n),
      .writedata  (ADC_DATA_s1_writedata)
    );

  BUZZER_DATA_s1_arbitrator the_BUZZER_DATA_s1
    (
      .BUZZER_DATA_s1_address                                      (BUZZER_DATA_s1_address),
      .BUZZER_DATA_s1_chipselect                                   (BUZZER_DATA_s1_chipselect),
      .BUZZER_DATA_s1_readdata                                     (BUZZER_DATA_s1_readdata),
      .BUZZER_DATA_s1_readdata_from_sa                             (BUZZER_DATA_s1_readdata_from_sa),
      .BUZZER_DATA_s1_reset_n                                      (BUZZER_DATA_s1_reset_n),
      .BUZZER_DATA_s1_write_n                                      (BUZZER_DATA_s1_write_n),
      .BUZZER_DATA_s1_writedata                                    (BUZZER_DATA_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_BUZZER_DATA_s1                    (cpu_0_data_master_granted_BUZZER_DATA_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_BUZZER_DATA_s1          (cpu_0_data_master_qualified_request_BUZZER_DATA_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_BUZZER_DATA_s1            (cpu_0_data_master_read_data_valid_BUZZER_DATA_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_BUZZER_DATA_s1                   (cpu_0_data_master_requests_BUZZER_DATA_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_BUZZER_DATA_s1_end_xfer                                  (d1_BUZZER_DATA_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  BUZZER_DATA the_BUZZER_DATA
    (
      .address    (BUZZER_DATA_s1_address),
      .chipselect (BUZZER_DATA_s1_chipselect),
      .clk        (clk_0),
      .in_port    (in_port_to_the_BUZZER_DATA),
      .readdata   (BUZZER_DATA_s1_readdata),
      .reset_n    (BUZZER_DATA_s1_reset_n),
      .write_n    (BUZZER_DATA_s1_write_n),
      .writedata  (BUZZER_DATA_s1_writedata)
    );

  DAC_DATA_s1_arbitrator the_DAC_DATA_s1
    (
      .DAC_DATA_s1_address                                         (DAC_DATA_s1_address),
      .DAC_DATA_s1_chipselect                                      (DAC_DATA_s1_chipselect),
      .DAC_DATA_s1_readdata                                        (DAC_DATA_s1_readdata),
      .DAC_DATA_s1_readdata_from_sa                                (DAC_DATA_s1_readdata_from_sa),
      .DAC_DATA_s1_reset_n                                         (DAC_DATA_s1_reset_n),
      .DAC_DATA_s1_write_n                                         (DAC_DATA_s1_write_n),
      .DAC_DATA_s1_writedata                                       (DAC_DATA_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_DAC_DATA_s1                       (cpu_0_data_master_granted_DAC_DATA_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_DAC_DATA_s1             (cpu_0_data_master_qualified_request_DAC_DATA_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_DAC_DATA_s1               (cpu_0_data_master_read_data_valid_DAC_DATA_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_DAC_DATA_s1                      (cpu_0_data_master_requests_DAC_DATA_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_DAC_DATA_s1_end_xfer                                     (d1_DAC_DATA_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  DAC_DATA the_DAC_DATA
    (
      .address    (DAC_DATA_s1_address),
      .chipselect (DAC_DATA_s1_chipselect),
      .clk        (clk_0),
      .in_port    (in_port_to_the_DAC_DATA),
      .readdata   (DAC_DATA_s1_readdata),
      .reset_n    (DAC_DATA_s1_reset_n),
      .write_n    (DAC_DATA_s1_write_n),
      .writedata  (DAC_DATA_s1_writedata)
    );

  ETH_CLKOUT_I_s1_arbitrator the_ETH_CLKOUT_I_s1
    (
      .ETH_CLKOUT_I_s1_address                                     (ETH_CLKOUT_I_s1_address),
      .ETH_CLKOUT_I_s1_chipselect                                  (ETH_CLKOUT_I_s1_chipselect),
      .ETH_CLKOUT_I_s1_readdata                                    (ETH_CLKOUT_I_s1_readdata),
      .ETH_CLKOUT_I_s1_readdata_from_sa                            (ETH_CLKOUT_I_s1_readdata_from_sa),
      .ETH_CLKOUT_I_s1_reset_n                                     (ETH_CLKOUT_I_s1_reset_n),
      .ETH_CLKOUT_I_s1_write_n                                     (ETH_CLKOUT_I_s1_write_n),
      .ETH_CLKOUT_I_s1_writedata                                   (ETH_CLKOUT_I_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_ETH_CLKOUT_I_s1                   (cpu_0_data_master_granted_ETH_CLKOUT_I_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_ETH_CLKOUT_I_s1         (cpu_0_data_master_qualified_request_ETH_CLKOUT_I_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_ETH_CLKOUT_I_s1           (cpu_0_data_master_read_data_valid_ETH_CLKOUT_I_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_ETH_CLKOUT_I_s1                  (cpu_0_data_master_requests_ETH_CLKOUT_I_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_ETH_CLKOUT_I_s1_end_xfer                                 (d1_ETH_CLKOUT_I_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  ETH_CLKOUT_I the_ETH_CLKOUT_I
    (
      .address    (ETH_CLKOUT_I_s1_address),
      .chipselect (ETH_CLKOUT_I_s1_chipselect),
      .clk        (clk_0),
      .in_port    (in_port_to_the_ETH_CLKOUT_I),
      .readdata   (ETH_CLKOUT_I_s1_readdata),
      .reset_n    (ETH_CLKOUT_I_s1_reset_n),
      .write_n    (ETH_CLKOUT_I_s1_write_n),
      .writedata  (ETH_CLKOUT_I_s1_writedata)
    );

  ETH_CS_O_s1_arbitrator the_ETH_CS_O_s1
    (
      .ETH_CS_O_s1_address                                         (ETH_CS_O_s1_address),
      .ETH_CS_O_s1_chipselect                                      (ETH_CS_O_s1_chipselect),
      .ETH_CS_O_s1_readdata                                        (ETH_CS_O_s1_readdata),
      .ETH_CS_O_s1_readdata_from_sa                                (ETH_CS_O_s1_readdata_from_sa),
      .ETH_CS_O_s1_reset_n                                         (ETH_CS_O_s1_reset_n),
      .ETH_CS_O_s1_write_n                                         (ETH_CS_O_s1_write_n),
      .ETH_CS_O_s1_writedata                                       (ETH_CS_O_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_ETH_CS_O_s1                       (cpu_0_data_master_granted_ETH_CS_O_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_ETH_CS_O_s1             (cpu_0_data_master_qualified_request_ETH_CS_O_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_ETH_CS_O_s1               (cpu_0_data_master_read_data_valid_ETH_CS_O_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_ETH_CS_O_s1                      (cpu_0_data_master_requests_ETH_CS_O_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_ETH_CS_O_s1_end_xfer                                     (d1_ETH_CS_O_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  ETH_CS_O the_ETH_CS_O
    (
      .address    (ETH_CS_O_s1_address),
      .chipselect (ETH_CS_O_s1_chipselect),
      .clk        (clk_0),
      .out_port   (out_port_from_the_ETH_CS_O),
      .readdata   (ETH_CS_O_s1_readdata),
      .reset_n    (ETH_CS_O_s1_reset_n),
      .write_n    (ETH_CS_O_s1_write_n),
      .writedata  (ETH_CS_O_s1_writedata)
    );

  ETH_INT_I_s1_arbitrator the_ETH_INT_I_s1
    (
      .ETH_INT_I_s1_address                                        (ETH_INT_I_s1_address),
      .ETH_INT_I_s1_chipselect                                     (ETH_INT_I_s1_chipselect),
      .ETH_INT_I_s1_readdata                                       (ETH_INT_I_s1_readdata),
      .ETH_INT_I_s1_readdata_from_sa                               (ETH_INT_I_s1_readdata_from_sa),
      .ETH_INT_I_s1_reset_n                                        (ETH_INT_I_s1_reset_n),
      .ETH_INT_I_s1_write_n                                        (ETH_INT_I_s1_write_n),
      .ETH_INT_I_s1_writedata                                      (ETH_INT_I_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_ETH_INT_I_s1                      (cpu_0_data_master_granted_ETH_INT_I_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_ETH_INT_I_s1            (cpu_0_data_master_qualified_request_ETH_INT_I_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_ETH_INT_I_s1              (cpu_0_data_master_read_data_valid_ETH_INT_I_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_ETH_INT_I_s1                     (cpu_0_data_master_requests_ETH_INT_I_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_ETH_INT_I_s1_end_xfer                                    (d1_ETH_INT_I_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  ETH_INT_I the_ETH_INT_I
    (
      .address    (ETH_INT_I_s1_address),
      .chipselect (ETH_INT_I_s1_chipselect),
      .clk        (clk_0),
      .in_port    (in_port_to_the_ETH_INT_I),
      .readdata   (ETH_INT_I_s1_readdata),
      .reset_n    (ETH_INT_I_s1_reset_n),
      .write_n    (ETH_INT_I_s1_write_n),
      .writedata  (ETH_INT_I_s1_writedata)
    );

  ETH_RESET_O_s1_arbitrator the_ETH_RESET_O_s1
    (
      .ETH_RESET_O_s1_address                                      (ETH_RESET_O_s1_address),
      .ETH_RESET_O_s1_chipselect                                   (ETH_RESET_O_s1_chipselect),
      .ETH_RESET_O_s1_readdata                                     (ETH_RESET_O_s1_readdata),
      .ETH_RESET_O_s1_readdata_from_sa                             (ETH_RESET_O_s1_readdata_from_sa),
      .ETH_RESET_O_s1_reset_n                                      (ETH_RESET_O_s1_reset_n),
      .ETH_RESET_O_s1_write_n                                      (ETH_RESET_O_s1_write_n),
      .ETH_RESET_O_s1_writedata                                    (ETH_RESET_O_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_ETH_RESET_O_s1                    (cpu_0_data_master_granted_ETH_RESET_O_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_ETH_RESET_O_s1          (cpu_0_data_master_qualified_request_ETH_RESET_O_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_ETH_RESET_O_s1            (cpu_0_data_master_read_data_valid_ETH_RESET_O_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_ETH_RESET_O_s1                   (cpu_0_data_master_requests_ETH_RESET_O_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_ETH_RESET_O_s1_end_xfer                                  (d1_ETH_RESET_O_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  ETH_RESET_O the_ETH_RESET_O
    (
      .address    (ETH_RESET_O_s1_address),
      .chipselect (ETH_RESET_O_s1_chipselect),
      .clk        (clk_0),
      .out_port   (out_port_from_the_ETH_RESET_O),
      .readdata   (ETH_RESET_O_s1_readdata),
      .reset_n    (ETH_RESET_O_s1_reset_n),
      .write_n    (ETH_RESET_O_s1_write_n),
      .writedata  (ETH_RESET_O_s1_writedata)
    );

  ETH_SCK_O_s1_arbitrator the_ETH_SCK_O_s1
    (
      .ETH_SCK_O_s1_address                                        (ETH_SCK_O_s1_address),
      .ETH_SCK_O_s1_chipselect                                     (ETH_SCK_O_s1_chipselect),
      .ETH_SCK_O_s1_readdata                                       (ETH_SCK_O_s1_readdata),
      .ETH_SCK_O_s1_readdata_from_sa                               (ETH_SCK_O_s1_readdata_from_sa),
      .ETH_SCK_O_s1_reset_n                                        (ETH_SCK_O_s1_reset_n),
      .ETH_SCK_O_s1_write_n                                        (ETH_SCK_O_s1_write_n),
      .ETH_SCK_O_s1_writedata                                      (ETH_SCK_O_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_ETH_SCK_O_s1                      (cpu_0_data_master_granted_ETH_SCK_O_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_ETH_SCK_O_s1            (cpu_0_data_master_qualified_request_ETH_SCK_O_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_ETH_SCK_O_s1              (cpu_0_data_master_read_data_valid_ETH_SCK_O_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_ETH_SCK_O_s1                     (cpu_0_data_master_requests_ETH_SCK_O_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_ETH_SCK_O_s1_end_xfer                                    (d1_ETH_SCK_O_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  ETH_SCK_O the_ETH_SCK_O
    (
      .address    (ETH_SCK_O_s1_address),
      .chipselect (ETH_SCK_O_s1_chipselect),
      .clk        (clk_0),
      .out_port   (out_port_from_the_ETH_SCK_O),
      .readdata   (ETH_SCK_O_s1_readdata),
      .reset_n    (ETH_SCK_O_s1_reset_n),
      .write_n    (ETH_SCK_O_s1_write_n),
      .writedata  (ETH_SCK_O_s1_writedata)
    );

  ETH_SI_O_s1_arbitrator the_ETH_SI_O_s1
    (
      .ETH_SI_O_s1_address                                         (ETH_SI_O_s1_address),
      .ETH_SI_O_s1_chipselect                                      (ETH_SI_O_s1_chipselect),
      .ETH_SI_O_s1_readdata                                        (ETH_SI_O_s1_readdata),
      .ETH_SI_O_s1_readdata_from_sa                                (ETH_SI_O_s1_readdata_from_sa),
      .ETH_SI_O_s1_reset_n                                         (ETH_SI_O_s1_reset_n),
      .ETH_SI_O_s1_write_n                                         (ETH_SI_O_s1_write_n),
      .ETH_SI_O_s1_writedata                                       (ETH_SI_O_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_ETH_SI_O_s1                       (cpu_0_data_master_granted_ETH_SI_O_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_ETH_SI_O_s1             (cpu_0_data_master_qualified_request_ETH_SI_O_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_ETH_SI_O_s1               (cpu_0_data_master_read_data_valid_ETH_SI_O_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_ETH_SI_O_s1                      (cpu_0_data_master_requests_ETH_SI_O_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_ETH_SI_O_s1_end_xfer                                     (d1_ETH_SI_O_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  ETH_SI_O the_ETH_SI_O
    (
      .address    (ETH_SI_O_s1_address),
      .chipselect (ETH_SI_O_s1_chipselect),
      .clk        (clk_0),
      .out_port   (out_port_from_the_ETH_SI_O),
      .readdata   (ETH_SI_O_s1_readdata),
      .reset_n    (ETH_SI_O_s1_reset_n),
      .write_n    (ETH_SI_O_s1_write_n),
      .writedata  (ETH_SI_O_s1_writedata)
    );

  ETH_SO_I_s1_arbitrator the_ETH_SO_I_s1
    (
      .ETH_SO_I_s1_address                                         (ETH_SO_I_s1_address),
      .ETH_SO_I_s1_chipselect                                      (ETH_SO_I_s1_chipselect),
      .ETH_SO_I_s1_readdata                                        (ETH_SO_I_s1_readdata),
      .ETH_SO_I_s1_readdata_from_sa                                (ETH_SO_I_s1_readdata_from_sa),
      .ETH_SO_I_s1_reset_n                                         (ETH_SO_I_s1_reset_n),
      .ETH_SO_I_s1_write_n                                         (ETH_SO_I_s1_write_n),
      .ETH_SO_I_s1_writedata                                       (ETH_SO_I_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_ETH_SO_I_s1                       (cpu_0_data_master_granted_ETH_SO_I_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_ETH_SO_I_s1             (cpu_0_data_master_qualified_request_ETH_SO_I_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_ETH_SO_I_s1               (cpu_0_data_master_read_data_valid_ETH_SO_I_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_ETH_SO_I_s1                      (cpu_0_data_master_requests_ETH_SO_I_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_ETH_SO_I_s1_end_xfer                                     (d1_ETH_SO_I_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  ETH_SO_I the_ETH_SO_I
    (
      .address    (ETH_SO_I_s1_address),
      .chipselect (ETH_SO_I_s1_chipselect),
      .clk        (clk_0),
      .in_port    (in_port_to_the_ETH_SO_I),
      .readdata   (ETH_SO_I_s1_readdata),
      .reset_n    (ETH_SO_I_s1_reset_n),
      .write_n    (ETH_SO_I_s1_write_n),
      .writedata  (ETH_SO_I_s1_writedata)
    );

  ETH_WOL_I_s1_arbitrator the_ETH_WOL_I_s1
    (
      .ETH_WOL_I_s1_address                                        (ETH_WOL_I_s1_address),
      .ETH_WOL_I_s1_chipselect                                     (ETH_WOL_I_s1_chipselect),
      .ETH_WOL_I_s1_readdata                                       (ETH_WOL_I_s1_readdata),
      .ETH_WOL_I_s1_readdata_from_sa                               (ETH_WOL_I_s1_readdata_from_sa),
      .ETH_WOL_I_s1_reset_n                                        (ETH_WOL_I_s1_reset_n),
      .ETH_WOL_I_s1_write_n                                        (ETH_WOL_I_s1_write_n),
      .ETH_WOL_I_s1_writedata                                      (ETH_WOL_I_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_ETH_WOL_I_s1                      (cpu_0_data_master_granted_ETH_WOL_I_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_ETH_WOL_I_s1            (cpu_0_data_master_qualified_request_ETH_WOL_I_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_ETH_WOL_I_s1              (cpu_0_data_master_read_data_valid_ETH_WOL_I_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_ETH_WOL_I_s1                     (cpu_0_data_master_requests_ETH_WOL_I_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_ETH_WOL_I_s1_end_xfer                                    (d1_ETH_WOL_I_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  ETH_WOL_I the_ETH_WOL_I
    (
      .address    (ETH_WOL_I_s1_address),
      .chipselect (ETH_WOL_I_s1_chipselect),
      .clk        (clk_0),
      .in_port    (in_port_to_the_ETH_WOL_I),
      .readdata   (ETH_WOL_I_s1_readdata),
      .reset_n    (ETH_WOL_I_s1_reset_n),
      .write_n    (ETH_WOL_I_s1_write_n),
      .writedata  (ETH_WOL_I_s1_writedata)
    );

  IR_DATA_s1_arbitrator the_IR_DATA_s1
    (
      .IR_DATA_s1_address                                          (IR_DATA_s1_address),
      .IR_DATA_s1_chipselect                                       (IR_DATA_s1_chipselect),
      .IR_DATA_s1_readdata                                         (IR_DATA_s1_readdata),
      .IR_DATA_s1_readdata_from_sa                                 (IR_DATA_s1_readdata_from_sa),
      .IR_DATA_s1_reset_n                                          (IR_DATA_s1_reset_n),
      .IR_DATA_s1_write_n                                          (IR_DATA_s1_write_n),
      .IR_DATA_s1_writedata                                        (IR_DATA_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_IR_DATA_s1                        (cpu_0_data_master_granted_IR_DATA_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_IR_DATA_s1              (cpu_0_data_master_qualified_request_IR_DATA_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_IR_DATA_s1                (cpu_0_data_master_read_data_valid_IR_DATA_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_IR_DATA_s1                       (cpu_0_data_master_requests_IR_DATA_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_IR_DATA_s1_end_xfer                                      (d1_IR_DATA_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  IR_DATA the_IR_DATA
    (
      .address    (IR_DATA_s1_address),
      .chipselect (IR_DATA_s1_chipselect),
      .clk        (clk_0),
      .in_port    (in_port_to_the_IR_DATA),
      .readdata   (IR_DATA_s1_readdata),
      .reset_n    (IR_DATA_s1_reset_n),
      .write_n    (IR_DATA_s1_write_n),
      .writedata  (IR_DATA_s1_writedata)
    );

  KEY_FOCUS_s1_arbitrator the_KEY_FOCUS_s1
    (
      .KEY_FOCUS_s1_address                                        (KEY_FOCUS_s1_address),
      .KEY_FOCUS_s1_chipselect                                     (KEY_FOCUS_s1_chipselect),
      .KEY_FOCUS_s1_readdata                                       (KEY_FOCUS_s1_readdata),
      .KEY_FOCUS_s1_readdata_from_sa                               (KEY_FOCUS_s1_readdata_from_sa),
      .KEY_FOCUS_s1_reset_n                                        (KEY_FOCUS_s1_reset_n),
      .KEY_FOCUS_s1_write_n                                        (KEY_FOCUS_s1_write_n),
      .KEY_FOCUS_s1_writedata                                      (KEY_FOCUS_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_KEY_FOCUS_s1                      (cpu_0_data_master_granted_KEY_FOCUS_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_KEY_FOCUS_s1            (cpu_0_data_master_qualified_request_KEY_FOCUS_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_KEY_FOCUS_s1              (cpu_0_data_master_read_data_valid_KEY_FOCUS_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_KEY_FOCUS_s1                     (cpu_0_data_master_requests_KEY_FOCUS_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_KEY_FOCUS_s1_end_xfer                                    (d1_KEY_FOCUS_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  KEY_FOCUS the_KEY_FOCUS
    (
      .address    (KEY_FOCUS_s1_address),
      .chipselect (KEY_FOCUS_s1_chipselect),
      .clk        (clk_0),
      .in_port    (in_port_to_the_KEY_FOCUS),
      .readdata   (KEY_FOCUS_s1_readdata),
      .reset_n    (KEY_FOCUS_s1_reset_n),
      .write_n    (KEY_FOCUS_s1_write_n),
      .writedata  (KEY_FOCUS_s1_writedata)
    );

  LCD_CS_s1_arbitrator the_LCD_CS_s1
    (
      .LCD_CS_s1_address                                           (LCD_CS_s1_address),
      .LCD_CS_s1_chipselect                                        (LCD_CS_s1_chipselect),
      .LCD_CS_s1_readdata                                          (LCD_CS_s1_readdata),
      .LCD_CS_s1_readdata_from_sa                                  (LCD_CS_s1_readdata_from_sa),
      .LCD_CS_s1_reset_n                                           (LCD_CS_s1_reset_n),
      .LCD_CS_s1_write_n                                           (LCD_CS_s1_write_n),
      .LCD_CS_s1_writedata                                         (LCD_CS_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_LCD_CS_s1                         (cpu_0_data_master_granted_LCD_CS_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_LCD_CS_s1               (cpu_0_data_master_qualified_request_LCD_CS_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_LCD_CS_s1                 (cpu_0_data_master_read_data_valid_LCD_CS_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_LCD_CS_s1                        (cpu_0_data_master_requests_LCD_CS_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_LCD_CS_s1_end_xfer                                       (d1_LCD_CS_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  LCD_CS the_LCD_CS
    (
      .address    (LCD_CS_s1_address),
      .chipselect (LCD_CS_s1_chipselect),
      .clk        (clk_0),
      .out_port   (out_port_from_the_LCD_CS),
      .readdata   (LCD_CS_s1_readdata),
      .reset_n    (LCD_CS_s1_reset_n),
      .write_n    (LCD_CS_s1_write_n),
      .writedata  (LCD_CS_s1_writedata)
    );

  LCD_DATA_s1_arbitrator the_LCD_DATA_s1
    (
      .LCD_DATA_s1_address                                         (LCD_DATA_s1_address),
      .LCD_DATA_s1_chipselect                                      (LCD_DATA_s1_chipselect),
      .LCD_DATA_s1_readdata                                        (LCD_DATA_s1_readdata),
      .LCD_DATA_s1_readdata_from_sa                                (LCD_DATA_s1_readdata_from_sa),
      .LCD_DATA_s1_reset_n                                         (LCD_DATA_s1_reset_n),
      .LCD_DATA_s1_write_n                                         (LCD_DATA_s1_write_n),
      .LCD_DATA_s1_writedata                                       (LCD_DATA_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_LCD_DATA_s1                       (cpu_0_data_master_granted_LCD_DATA_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_LCD_DATA_s1             (cpu_0_data_master_qualified_request_LCD_DATA_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_LCD_DATA_s1               (cpu_0_data_master_read_data_valid_LCD_DATA_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_LCD_DATA_s1                      (cpu_0_data_master_requests_LCD_DATA_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_LCD_DATA_s1_end_xfer                                     (d1_LCD_DATA_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  LCD_DATA the_LCD_DATA
    (
      .address    (LCD_DATA_s1_address),
      .chipselect (LCD_DATA_s1_chipselect),
      .clk        (clk_0),
      .out_port   (out_port_from_the_LCD_DATA),
      .readdata   (LCD_DATA_s1_readdata),
      .reset_n    (LCD_DATA_s1_reset_n),
      .write_n    (LCD_DATA_s1_write_n),
      .writedata  (LCD_DATA_s1_writedata)
    );

  LCD_RD_s1_arbitrator the_LCD_RD_s1
    (
      .LCD_RD_s1_address                                           (LCD_RD_s1_address),
      .LCD_RD_s1_chipselect                                        (LCD_RD_s1_chipselect),
      .LCD_RD_s1_readdata                                          (LCD_RD_s1_readdata),
      .LCD_RD_s1_readdata_from_sa                                  (LCD_RD_s1_readdata_from_sa),
      .LCD_RD_s1_reset_n                                           (LCD_RD_s1_reset_n),
      .LCD_RD_s1_write_n                                           (LCD_RD_s1_write_n),
      .LCD_RD_s1_writedata                                         (LCD_RD_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_LCD_RD_s1                         (cpu_0_data_master_granted_LCD_RD_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_LCD_RD_s1               (cpu_0_data_master_qualified_request_LCD_RD_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_LCD_RD_s1                 (cpu_0_data_master_read_data_valid_LCD_RD_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_LCD_RD_s1                        (cpu_0_data_master_requests_LCD_RD_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_LCD_RD_s1_end_xfer                                       (d1_LCD_RD_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  LCD_RD the_LCD_RD
    (
      .address    (LCD_RD_s1_address),
      .chipselect (LCD_RD_s1_chipselect),
      .clk        (clk_0),
      .out_port   (out_port_from_the_LCD_RD),
      .readdata   (LCD_RD_s1_readdata),
      .reset_n    (LCD_RD_s1_reset_n),
      .write_n    (LCD_RD_s1_write_n),
      .writedata  (LCD_RD_s1_writedata)
    );

  LCD_RS_s1_arbitrator the_LCD_RS_s1
    (
      .LCD_RS_s1_address                                           (LCD_RS_s1_address),
      .LCD_RS_s1_chipselect                                        (LCD_RS_s1_chipselect),
      .LCD_RS_s1_readdata                                          (LCD_RS_s1_readdata),
      .LCD_RS_s1_readdata_from_sa                                  (LCD_RS_s1_readdata_from_sa),
      .LCD_RS_s1_reset_n                                           (LCD_RS_s1_reset_n),
      .LCD_RS_s1_write_n                                           (LCD_RS_s1_write_n),
      .LCD_RS_s1_writedata                                         (LCD_RS_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_LCD_RS_s1                         (cpu_0_data_master_granted_LCD_RS_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_LCD_RS_s1               (cpu_0_data_master_qualified_request_LCD_RS_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_LCD_RS_s1                 (cpu_0_data_master_read_data_valid_LCD_RS_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_LCD_RS_s1                        (cpu_0_data_master_requests_LCD_RS_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_LCD_RS_s1_end_xfer                                       (d1_LCD_RS_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  LCD_RS the_LCD_RS
    (
      .address    (LCD_RS_s1_address),
      .chipselect (LCD_RS_s1_chipselect),
      .clk        (clk_0),
      .out_port   (out_port_from_the_LCD_RS),
      .readdata   (LCD_RS_s1_readdata),
      .reset_n    (LCD_RS_s1_reset_n),
      .write_n    (LCD_RS_s1_write_n),
      .writedata  (LCD_RS_s1_writedata)
    );

  LCD_RST_s1_arbitrator the_LCD_RST_s1
    (
      .LCD_RST_s1_address                                          (LCD_RST_s1_address),
      .LCD_RST_s1_chipselect                                       (LCD_RST_s1_chipselect),
      .LCD_RST_s1_readdata                                         (LCD_RST_s1_readdata),
      .LCD_RST_s1_readdata_from_sa                                 (LCD_RST_s1_readdata_from_sa),
      .LCD_RST_s1_reset_n                                          (LCD_RST_s1_reset_n),
      .LCD_RST_s1_write_n                                          (LCD_RST_s1_write_n),
      .LCD_RST_s1_writedata                                        (LCD_RST_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_LCD_RST_s1                        (cpu_0_data_master_granted_LCD_RST_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_LCD_RST_s1              (cpu_0_data_master_qualified_request_LCD_RST_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_LCD_RST_s1                (cpu_0_data_master_read_data_valid_LCD_RST_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_LCD_RST_s1                       (cpu_0_data_master_requests_LCD_RST_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_LCD_RST_s1_end_xfer                                      (d1_LCD_RST_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  LCD_RST the_LCD_RST
    (
      .address    (LCD_RST_s1_address),
      .chipselect (LCD_RST_s1_chipselect),
      .clk        (clk_0),
      .out_port   (out_port_from_the_LCD_RST),
      .readdata   (LCD_RST_s1_readdata),
      .reset_n    (LCD_RST_s1_reset_n),
      .write_n    (LCD_RST_s1_write_n),
      .writedata  (LCD_RST_s1_writedata)
    );

  LCD_WR_s1_arbitrator the_LCD_WR_s1
    (
      .LCD_WR_s1_address                                           (LCD_WR_s1_address),
      .LCD_WR_s1_chipselect                                        (LCD_WR_s1_chipselect),
      .LCD_WR_s1_readdata                                          (LCD_WR_s1_readdata),
      .LCD_WR_s1_readdata_from_sa                                  (LCD_WR_s1_readdata_from_sa),
      .LCD_WR_s1_reset_n                                           (LCD_WR_s1_reset_n),
      .LCD_WR_s1_write_n                                           (LCD_WR_s1_write_n),
      .LCD_WR_s1_writedata                                         (LCD_WR_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_LCD_WR_s1                         (cpu_0_data_master_granted_LCD_WR_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_LCD_WR_s1               (cpu_0_data_master_qualified_request_LCD_WR_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_LCD_WR_s1                 (cpu_0_data_master_read_data_valid_LCD_WR_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_LCD_WR_s1                        (cpu_0_data_master_requests_LCD_WR_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_LCD_WR_s1_end_xfer                                       (d1_LCD_WR_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  LCD_WR the_LCD_WR
    (
      .address    (LCD_WR_s1_address),
      .chipselect (LCD_WR_s1_chipselect),
      .clk        (clk_0),
      .out_port   (out_port_from_the_LCD_WR),
      .readdata   (LCD_WR_s1_readdata),
      .reset_n    (LCD_WR_s1_reset_n),
      .write_n    (LCD_WR_s1_write_n),
      .writedata  (LCD_WR_s1_writedata)
    );

  LED_DATA_s1_arbitrator the_LED_DATA_s1
    (
      .LED_DATA_s1_address                                         (LED_DATA_s1_address),
      .LED_DATA_s1_chipselect                                      (LED_DATA_s1_chipselect),
      .LED_DATA_s1_readdata                                        (LED_DATA_s1_readdata),
      .LED_DATA_s1_readdata_from_sa                                (LED_DATA_s1_readdata_from_sa),
      .LED_DATA_s1_reset_n                                         (LED_DATA_s1_reset_n),
      .LED_DATA_s1_write_n                                         (LED_DATA_s1_write_n),
      .LED_DATA_s1_writedata                                       (LED_DATA_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_LED_DATA_s1                       (cpu_0_data_master_granted_LED_DATA_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_LED_DATA_s1             (cpu_0_data_master_qualified_request_LED_DATA_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_LED_DATA_s1               (cpu_0_data_master_read_data_valid_LED_DATA_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_LED_DATA_s1                      (cpu_0_data_master_requests_LED_DATA_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_LED_DATA_s1_end_xfer                                     (d1_LED_DATA_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  LED_DATA the_LED_DATA
    (
      .address    (LED_DATA_s1_address),
      .chipselect (LED_DATA_s1_chipselect),
      .clk        (clk_0),
      .in_port    (in_port_to_the_LED_DATA),
      .readdata   (LED_DATA_s1_readdata),
      .reset_n    (LED_DATA_s1_reset_n),
      .write_n    (LED_DATA_s1_write_n),
      .writedata  (LED_DATA_s1_writedata)
    );

  PS2_DATA_REC_s1_arbitrator the_PS2_DATA_REC_s1
    (
      .PS2_DATA_REC_s1_address                                     (PS2_DATA_REC_s1_address),
      .PS2_DATA_REC_s1_chipselect                                  (PS2_DATA_REC_s1_chipselect),
      .PS2_DATA_REC_s1_readdata                                    (PS2_DATA_REC_s1_readdata),
      .PS2_DATA_REC_s1_readdata_from_sa                            (PS2_DATA_REC_s1_readdata_from_sa),
      .PS2_DATA_REC_s1_reset_n                                     (PS2_DATA_REC_s1_reset_n),
      .PS2_DATA_REC_s1_write_n                                     (PS2_DATA_REC_s1_write_n),
      .PS2_DATA_REC_s1_writedata                                   (PS2_DATA_REC_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_PS2_DATA_REC_s1                   (cpu_0_data_master_granted_PS2_DATA_REC_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_PS2_DATA_REC_s1         (cpu_0_data_master_qualified_request_PS2_DATA_REC_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_PS2_DATA_REC_s1           (cpu_0_data_master_read_data_valid_PS2_DATA_REC_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_PS2_DATA_REC_s1                  (cpu_0_data_master_requests_PS2_DATA_REC_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_PS2_DATA_REC_s1_end_xfer                                 (d1_PS2_DATA_REC_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  PS2_DATA_REC the_PS2_DATA_REC
    (
      .address    (PS2_DATA_REC_s1_address),
      .chipselect (PS2_DATA_REC_s1_chipselect),
      .clk        (clk_0),
      .in_port    (in_port_to_the_PS2_DATA_REC),
      .readdata   (PS2_DATA_REC_s1_readdata),
      .reset_n    (PS2_DATA_REC_s1_reset_n),
      .write_n    (PS2_DATA_REC_s1_write_n),
      .writedata  (PS2_DATA_REC_s1_writedata)
    );

  RTC_DATA_s1_arbitrator the_RTC_DATA_s1
    (
      .RTC_DATA_s1_address                                         (RTC_DATA_s1_address),
      .RTC_DATA_s1_chipselect                                      (RTC_DATA_s1_chipselect),
      .RTC_DATA_s1_readdata                                        (RTC_DATA_s1_readdata),
      .RTC_DATA_s1_readdata_from_sa                                (RTC_DATA_s1_readdata_from_sa),
      .RTC_DATA_s1_reset_n                                         (RTC_DATA_s1_reset_n),
      .RTC_DATA_s1_write_n                                         (RTC_DATA_s1_write_n),
      .RTC_DATA_s1_writedata                                       (RTC_DATA_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_RTC_DATA_s1                       (cpu_0_data_master_granted_RTC_DATA_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_RTC_DATA_s1             (cpu_0_data_master_qualified_request_RTC_DATA_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_RTC_DATA_s1               (cpu_0_data_master_read_data_valid_RTC_DATA_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_RTC_DATA_s1                      (cpu_0_data_master_requests_RTC_DATA_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_RTC_DATA_s1_end_xfer                                     (d1_RTC_DATA_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  RTC_DATA the_RTC_DATA
    (
      .address    (RTC_DATA_s1_address),
      .chipselect (RTC_DATA_s1_chipselect),
      .clk        (clk_0),
      .in_port    (in_port_to_the_RTC_DATA),
      .readdata   (RTC_DATA_s1_readdata),
      .reset_n    (RTC_DATA_s1_reset_n),
      .write_n    (RTC_DATA_s1_write_n),
      .writedata  (RTC_DATA_s1_writedata)
    );

  SCL_s1_arbitrator the_SCL_s1
    (
      .SCL_s1_address                                              (SCL_s1_address),
      .SCL_s1_chipselect                                           (SCL_s1_chipselect),
      .SCL_s1_readdata                                             (SCL_s1_readdata),
      .SCL_s1_readdata_from_sa                                     (SCL_s1_readdata_from_sa),
      .SCL_s1_reset_n                                              (SCL_s1_reset_n),
      .SCL_s1_write_n                                              (SCL_s1_write_n),
      .SCL_s1_writedata                                            (SCL_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_SCL_s1                            (cpu_0_data_master_granted_SCL_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_SCL_s1                  (cpu_0_data_master_qualified_request_SCL_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_SCL_s1                    (cpu_0_data_master_read_data_valid_SCL_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_SCL_s1                           (cpu_0_data_master_requests_SCL_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_SCL_s1_end_xfer                                          (d1_SCL_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  SCL the_SCL
    (
      .address    (SCL_s1_address),
      .chipselect (SCL_s1_chipselect),
      .clk        (clk_0),
      .out_port   (out_port_from_the_SCL),
      .readdata   (SCL_s1_readdata),
      .reset_n    (SCL_s1_reset_n),
      .write_n    (SCL_s1_write_n),
      .writedata  (SCL_s1_writedata)
    );

  SDA_s1_arbitrator the_SDA_s1
    (
      .SDA_s1_address                                              (SDA_s1_address),
      .SDA_s1_chipselect                                           (SDA_s1_chipselect),
      .SDA_s1_readdata                                             (SDA_s1_readdata),
      .SDA_s1_readdata_from_sa                                     (SDA_s1_readdata_from_sa),
      .SDA_s1_reset_n                                              (SDA_s1_reset_n),
      .SDA_s1_write_n                                              (SDA_s1_write_n),
      .SDA_s1_writedata                                            (SDA_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_SDA_s1                            (cpu_0_data_master_granted_SDA_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_SDA_s1                  (cpu_0_data_master_qualified_request_SDA_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_SDA_s1                    (cpu_0_data_master_read_data_valid_SDA_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_SDA_s1                           (cpu_0_data_master_requests_SDA_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_SDA_s1_end_xfer                                          (d1_SDA_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  SDA the_SDA
    (
      .address    (SDA_s1_address),
      .bidir_port (bidir_port_to_and_from_the_SDA),
      .chipselect (SDA_s1_chipselect),
      .clk        (clk_0),
      .readdata   (SDA_s1_readdata),
      .reset_n    (SDA_s1_reset_n),
      .write_n    (SDA_s1_write_n),
      .writedata  (SDA_s1_writedata)
    );

  SD_CLK_s1_arbitrator the_SD_CLK_s1
    (
      .SD_CLK_s1_address                                           (SD_CLK_s1_address),
      .SD_CLK_s1_chipselect                                        (SD_CLK_s1_chipselect),
      .SD_CLK_s1_readdata                                          (SD_CLK_s1_readdata),
      .SD_CLK_s1_readdata_from_sa                                  (SD_CLK_s1_readdata_from_sa),
      .SD_CLK_s1_reset_n                                           (SD_CLK_s1_reset_n),
      .SD_CLK_s1_write_n                                           (SD_CLK_s1_write_n),
      .SD_CLK_s1_writedata                                         (SD_CLK_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_SD_CLK_s1                         (cpu_0_data_master_granted_SD_CLK_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_SD_CLK_s1               (cpu_0_data_master_qualified_request_SD_CLK_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_SD_CLK_s1                 (cpu_0_data_master_read_data_valid_SD_CLK_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_SD_CLK_s1                        (cpu_0_data_master_requests_SD_CLK_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_SD_CLK_s1_end_xfer                                       (d1_SD_CLK_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  SD_CLK the_SD_CLK
    (
      .address    (SD_CLK_s1_address),
      .chipselect (SD_CLK_s1_chipselect),
      .clk        (clk_0),
      .out_port   (out_port_from_the_SD_CLK),
      .readdata   (SD_CLK_s1_readdata),
      .reset_n    (SD_CLK_s1_reset_n),
      .write_n    (SD_CLK_s1_write_n),
      .writedata  (SD_CLK_s1_writedata)
    );

  SD_CS_s1_arbitrator the_SD_CS_s1
    (
      .SD_CS_s1_address                                            (SD_CS_s1_address),
      .SD_CS_s1_chipselect                                         (SD_CS_s1_chipselect),
      .SD_CS_s1_readdata                                           (SD_CS_s1_readdata),
      .SD_CS_s1_readdata_from_sa                                   (SD_CS_s1_readdata_from_sa),
      .SD_CS_s1_reset_n                                            (SD_CS_s1_reset_n),
      .SD_CS_s1_write_n                                            (SD_CS_s1_write_n),
      .SD_CS_s1_writedata                                          (SD_CS_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_SD_CS_s1                          (cpu_0_data_master_granted_SD_CS_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_SD_CS_s1                (cpu_0_data_master_qualified_request_SD_CS_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_SD_CS_s1                  (cpu_0_data_master_read_data_valid_SD_CS_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_SD_CS_s1                         (cpu_0_data_master_requests_SD_CS_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_SD_CS_s1_end_xfer                                        (d1_SD_CS_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  SD_CS the_SD_CS
    (
      .address    (SD_CS_s1_address),
      .chipselect (SD_CS_s1_chipselect),
      .clk        (clk_0),
      .out_port   (out_port_from_the_SD_CS),
      .readdata   (SD_CS_s1_readdata),
      .reset_n    (SD_CS_s1_reset_n),
      .write_n    (SD_CS_s1_write_n),
      .writedata  (SD_CS_s1_writedata)
    );

  SD_DI_s1_arbitrator the_SD_DI_s1
    (
      .SD_DI_s1_address                                            (SD_DI_s1_address),
      .SD_DI_s1_chipselect                                         (SD_DI_s1_chipselect),
      .SD_DI_s1_readdata                                           (SD_DI_s1_readdata),
      .SD_DI_s1_readdata_from_sa                                   (SD_DI_s1_readdata_from_sa),
      .SD_DI_s1_reset_n                                            (SD_DI_s1_reset_n),
      .SD_DI_s1_write_n                                            (SD_DI_s1_write_n),
      .SD_DI_s1_writedata                                          (SD_DI_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_SD_DI_s1                          (cpu_0_data_master_granted_SD_DI_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_SD_DI_s1                (cpu_0_data_master_qualified_request_SD_DI_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_SD_DI_s1                  (cpu_0_data_master_read_data_valid_SD_DI_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_SD_DI_s1                         (cpu_0_data_master_requests_SD_DI_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_SD_DI_s1_end_xfer                                        (d1_SD_DI_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  SD_DI the_SD_DI
    (
      .address    (SD_DI_s1_address),
      .chipselect (SD_DI_s1_chipselect),
      .clk        (clk_0),
      .out_port   (out_port_from_the_SD_DI),
      .readdata   (SD_DI_s1_readdata),
      .reset_n    (SD_DI_s1_reset_n),
      .write_n    (SD_DI_s1_write_n),
      .writedata  (SD_DI_s1_writedata)
    );

  SD_DO_s1_arbitrator the_SD_DO_s1
    (
      .SD_DO_s1_address                                            (SD_DO_s1_address),
      .SD_DO_s1_chipselect                                         (SD_DO_s1_chipselect),
      .SD_DO_s1_readdata                                           (SD_DO_s1_readdata),
      .SD_DO_s1_readdata_from_sa                                   (SD_DO_s1_readdata_from_sa),
      .SD_DO_s1_reset_n                                            (SD_DO_s1_reset_n),
      .SD_DO_s1_write_n                                            (SD_DO_s1_write_n),
      .SD_DO_s1_writedata                                          (SD_DO_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_SD_DO_s1                          (cpu_0_data_master_granted_SD_DO_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_SD_DO_s1                (cpu_0_data_master_qualified_request_SD_DO_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_SD_DO_s1                  (cpu_0_data_master_read_data_valid_SD_DO_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_SD_DO_s1                         (cpu_0_data_master_requests_SD_DO_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_SD_DO_s1_end_xfer                                        (d1_SD_DO_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  SD_DO the_SD_DO
    (
      .address    (SD_DO_s1_address),
      .chipselect (SD_DO_s1_chipselect),
      .clk        (clk_0),
      .in_port    (in_port_to_the_SD_DO),
      .readdata   (SD_DO_s1_readdata),
      .reset_n    (SD_DO_s1_reset_n),
      .write_n    (SD_DO_s1_write_n),
      .writedata  (SD_DO_s1_writedata)
    );

  TEMP_DATA_s1_arbitrator the_TEMP_DATA_s1
    (
      .TEMP_DATA_s1_address                                        (TEMP_DATA_s1_address),
      .TEMP_DATA_s1_chipselect                                     (TEMP_DATA_s1_chipselect),
      .TEMP_DATA_s1_readdata                                       (TEMP_DATA_s1_readdata),
      .TEMP_DATA_s1_readdata_from_sa                               (TEMP_DATA_s1_readdata_from_sa),
      .TEMP_DATA_s1_reset_n                                        (TEMP_DATA_s1_reset_n),
      .TEMP_DATA_s1_write_n                                        (TEMP_DATA_s1_write_n),
      .TEMP_DATA_s1_writedata                                      (TEMP_DATA_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_TEMP_DATA_s1                      (cpu_0_data_master_granted_TEMP_DATA_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_TEMP_DATA_s1            (cpu_0_data_master_qualified_request_TEMP_DATA_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_TEMP_DATA_s1              (cpu_0_data_master_read_data_valid_TEMP_DATA_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_TEMP_DATA_s1                     (cpu_0_data_master_requests_TEMP_DATA_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_TEMP_DATA_s1_end_xfer                                    (d1_TEMP_DATA_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  TEMP_DATA the_TEMP_DATA
    (
      .address    (TEMP_DATA_s1_address),
      .chipselect (TEMP_DATA_s1_chipselect),
      .clk        (clk_0),
      .in_port    (in_port_to_the_TEMP_DATA),
      .readdata   (TEMP_DATA_s1_readdata),
      .reset_n    (TEMP_DATA_s1_reset_n),
      .write_n    (TEMP_DATA_s1_write_n),
      .writedata  (TEMP_DATA_s1_writedata)
    );

  TUBE_EN_s1_arbitrator the_TUBE_EN_s1
    (
      .TUBE_EN_s1_address                                          (TUBE_EN_s1_address),
      .TUBE_EN_s1_chipselect                                       (TUBE_EN_s1_chipselect),
      .TUBE_EN_s1_readdata                                         (TUBE_EN_s1_readdata),
      .TUBE_EN_s1_readdata_from_sa                                 (TUBE_EN_s1_readdata_from_sa),
      .TUBE_EN_s1_reset_n                                          (TUBE_EN_s1_reset_n),
      .TUBE_EN_s1_write_n                                          (TUBE_EN_s1_write_n),
      .TUBE_EN_s1_writedata                                        (TUBE_EN_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_TUBE_EN_s1                        (cpu_0_data_master_granted_TUBE_EN_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_TUBE_EN_s1              (cpu_0_data_master_qualified_request_TUBE_EN_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_TUBE_EN_s1                (cpu_0_data_master_read_data_valid_TUBE_EN_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_TUBE_EN_s1                       (cpu_0_data_master_requests_TUBE_EN_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_TUBE_EN_s1_end_xfer                                      (d1_TUBE_EN_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  TUBE_EN the_TUBE_EN
    (
      .address    (TUBE_EN_s1_address),
      .chipselect (TUBE_EN_s1_chipselect),
      .clk        (clk_0),
      .out_port   (out_port_from_the_TUBE_EN),
      .readdata   (TUBE_EN_s1_readdata),
      .reset_n    (TUBE_EN_s1_reset_n),
      .write_n    (TUBE_EN_s1_write_n),
      .writedata  (TUBE_EN_s1_writedata)
    );

  UART_RX_DATA_s1_arbitrator the_UART_RX_DATA_s1
    (
      .UART_RX_DATA_s1_address                                     (UART_RX_DATA_s1_address),
      .UART_RX_DATA_s1_chipselect                                  (UART_RX_DATA_s1_chipselect),
      .UART_RX_DATA_s1_readdata                                    (UART_RX_DATA_s1_readdata),
      .UART_RX_DATA_s1_readdata_from_sa                            (UART_RX_DATA_s1_readdata_from_sa),
      .UART_RX_DATA_s1_reset_n                                     (UART_RX_DATA_s1_reset_n),
      .UART_RX_DATA_s1_write_n                                     (UART_RX_DATA_s1_write_n),
      .UART_RX_DATA_s1_writedata                                   (UART_RX_DATA_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_UART_RX_DATA_s1                   (cpu_0_data_master_granted_UART_RX_DATA_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_UART_RX_DATA_s1         (cpu_0_data_master_qualified_request_UART_RX_DATA_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_UART_RX_DATA_s1           (cpu_0_data_master_read_data_valid_UART_RX_DATA_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_UART_RX_DATA_s1                  (cpu_0_data_master_requests_UART_RX_DATA_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_UART_RX_DATA_s1_end_xfer                                 (d1_UART_RX_DATA_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  UART_RX_DATA the_UART_RX_DATA
    (
      .address    (UART_RX_DATA_s1_address),
      .chipselect (UART_RX_DATA_s1_chipselect),
      .clk        (clk_0),
      .in_port    (in_port_to_the_UART_RX_DATA),
      .readdata   (UART_RX_DATA_s1_readdata),
      .reset_n    (UART_RX_DATA_s1_reset_n),
      .write_n    (UART_RX_DATA_s1_write_n),
      .writedata  (UART_RX_DATA_s1_writedata)
    );

  USB_INT_I_s1_arbitrator the_USB_INT_I_s1
    (
      .USB_INT_I_s1_address                                        (USB_INT_I_s1_address),
      .USB_INT_I_s1_readdata                                       (USB_INT_I_s1_readdata),
      .USB_INT_I_s1_readdata_from_sa                               (USB_INT_I_s1_readdata_from_sa),
      .USB_INT_I_s1_reset_n                                        (USB_INT_I_s1_reset_n),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_USB_INT_I_s1                      (cpu_0_data_master_granted_USB_INT_I_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_USB_INT_I_s1            (cpu_0_data_master_qualified_request_USB_INT_I_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_USB_INT_I_s1              (cpu_0_data_master_read_data_valid_USB_INT_I_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_USB_INT_I_s1                     (cpu_0_data_master_requests_USB_INT_I_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .d1_USB_INT_I_s1_end_xfer                                    (d1_USB_INT_I_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  USB_INT_I the_USB_INT_I
    (
      .address  (USB_INT_I_s1_address),
      .clk      (clk_0),
      .in_port  (in_port_to_the_USB_INT_I),
      .readdata (USB_INT_I_s1_readdata),
      .reset_n  (USB_INT_I_s1_reset_n)
    );

  USB_PC_I_s1_arbitrator the_USB_PC_I_s1
    (
      .USB_PC_I_s1_address                                         (USB_PC_I_s1_address),
      .USB_PC_I_s1_chipselect                                      (USB_PC_I_s1_chipselect),
      .USB_PC_I_s1_readdata                                        (USB_PC_I_s1_readdata),
      .USB_PC_I_s1_readdata_from_sa                                (USB_PC_I_s1_readdata_from_sa),
      .USB_PC_I_s1_reset_n                                         (USB_PC_I_s1_reset_n),
      .USB_PC_I_s1_write_n                                         (USB_PC_I_s1_write_n),
      .USB_PC_I_s1_writedata                                       (USB_PC_I_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_USB_PC_I_s1                       (cpu_0_data_master_granted_USB_PC_I_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_USB_PC_I_s1             (cpu_0_data_master_qualified_request_USB_PC_I_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_USB_PC_I_s1               (cpu_0_data_master_read_data_valid_USB_PC_I_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_USB_PC_I_s1                      (cpu_0_data_master_requests_USB_PC_I_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_USB_PC_I_s1_end_xfer                                     (d1_USB_PC_I_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  USB_PC_I the_USB_PC_I
    (
      .address    (USB_PC_I_s1_address),
      .chipselect (USB_PC_I_s1_chipselect),
      .clk        (clk_0),
      .in_port    (in_port_to_the_USB_PC_I),
      .readdata   (USB_PC_I_s1_readdata),
      .reset_n    (USB_PC_I_s1_reset_n),
      .write_n    (USB_PC_I_s1_write_n),
      .writedata  (USB_PC_I_s1_writedata)
    );

  USB_RST_O_s1_arbitrator the_USB_RST_O_s1
    (
      .USB_RST_O_s1_address                                        (USB_RST_O_s1_address),
      .USB_RST_O_s1_chipselect                                     (USB_RST_O_s1_chipselect),
      .USB_RST_O_s1_readdata                                       (USB_RST_O_s1_readdata),
      .USB_RST_O_s1_readdata_from_sa                               (USB_RST_O_s1_readdata_from_sa),
      .USB_RST_O_s1_reset_n                                        (USB_RST_O_s1_reset_n),
      .USB_RST_O_s1_write_n                                        (USB_RST_O_s1_write_n),
      .USB_RST_O_s1_writedata                                      (USB_RST_O_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_USB_RST_O_s1                      (cpu_0_data_master_granted_USB_RST_O_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_USB_RST_O_s1            (cpu_0_data_master_qualified_request_USB_RST_O_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_USB_RST_O_s1              (cpu_0_data_master_read_data_valid_USB_RST_O_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_USB_RST_O_s1                     (cpu_0_data_master_requests_USB_RST_O_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_USB_RST_O_s1_end_xfer                                    (d1_USB_RST_O_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  USB_RST_O the_USB_RST_O
    (
      .address    (USB_RST_O_s1_address),
      .chipselect (USB_RST_O_s1_chipselect),
      .clk        (clk_0),
      .out_port   (out_port_from_the_USB_RST_O),
      .readdata   (USB_RST_O_s1_readdata),
      .reset_n    (USB_RST_O_s1_reset_n),
      .write_n    (USB_RST_O_s1_write_n),
      .writedata  (USB_RST_O_s1_writedata)
    );

  USB_SCK_O_s1_arbitrator the_USB_SCK_O_s1
    (
      .USB_SCK_O_s1_address                                        (USB_SCK_O_s1_address),
      .USB_SCK_O_s1_chipselect                                     (USB_SCK_O_s1_chipselect),
      .USB_SCK_O_s1_readdata                                       (USB_SCK_O_s1_readdata),
      .USB_SCK_O_s1_readdata_from_sa                               (USB_SCK_O_s1_readdata_from_sa),
      .USB_SCK_O_s1_reset_n                                        (USB_SCK_O_s1_reset_n),
      .USB_SCK_O_s1_write_n                                        (USB_SCK_O_s1_write_n),
      .USB_SCK_O_s1_writedata                                      (USB_SCK_O_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_USB_SCK_O_s1                      (cpu_0_data_master_granted_USB_SCK_O_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_USB_SCK_O_s1            (cpu_0_data_master_qualified_request_USB_SCK_O_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_USB_SCK_O_s1              (cpu_0_data_master_read_data_valid_USB_SCK_O_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_USB_SCK_O_s1                     (cpu_0_data_master_requests_USB_SCK_O_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_USB_SCK_O_s1_end_xfer                                    (d1_USB_SCK_O_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  USB_SCK_O the_USB_SCK_O
    (
      .address    (USB_SCK_O_s1_address),
      .chipselect (USB_SCK_O_s1_chipselect),
      .clk        (clk_0),
      .out_port   (out_port_from_the_USB_SCK_O),
      .readdata   (USB_SCK_O_s1_readdata),
      .reset_n    (USB_SCK_O_s1_reset_n),
      .write_n    (USB_SCK_O_s1_write_n),
      .writedata  (USB_SCK_O_s1_writedata)
    );

  USB_SCS_O_s1_arbitrator the_USB_SCS_O_s1
    (
      .USB_SCS_O_s1_address                                        (USB_SCS_O_s1_address),
      .USB_SCS_O_s1_chipselect                                     (USB_SCS_O_s1_chipselect),
      .USB_SCS_O_s1_readdata                                       (USB_SCS_O_s1_readdata),
      .USB_SCS_O_s1_readdata_from_sa                               (USB_SCS_O_s1_readdata_from_sa),
      .USB_SCS_O_s1_reset_n                                        (USB_SCS_O_s1_reset_n),
      .USB_SCS_O_s1_write_n                                        (USB_SCS_O_s1_write_n),
      .USB_SCS_O_s1_writedata                                      (USB_SCS_O_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_USB_SCS_O_s1                      (cpu_0_data_master_granted_USB_SCS_O_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_USB_SCS_O_s1            (cpu_0_data_master_qualified_request_USB_SCS_O_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_USB_SCS_O_s1              (cpu_0_data_master_read_data_valid_USB_SCS_O_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_USB_SCS_O_s1                     (cpu_0_data_master_requests_USB_SCS_O_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_USB_SCS_O_s1_end_xfer                                    (d1_USB_SCS_O_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  USB_SCS_O the_USB_SCS_O
    (
      .address    (USB_SCS_O_s1_address),
      .chipselect (USB_SCS_O_s1_chipselect),
      .clk        (clk_0),
      .out_port   (out_port_from_the_USB_SCS_O),
      .readdata   (USB_SCS_O_s1_readdata),
      .reset_n    (USB_SCS_O_s1_reset_n),
      .write_n    (USB_SCS_O_s1_write_n),
      .writedata  (USB_SCS_O_s1_writedata)
    );

  USB_SDI_O_s1_arbitrator the_USB_SDI_O_s1
    (
      .USB_SDI_O_s1_address                                        (USB_SDI_O_s1_address),
      .USB_SDI_O_s1_chipselect                                     (USB_SDI_O_s1_chipselect),
      .USB_SDI_O_s1_readdata                                       (USB_SDI_O_s1_readdata),
      .USB_SDI_O_s1_readdata_from_sa                               (USB_SDI_O_s1_readdata_from_sa),
      .USB_SDI_O_s1_reset_n                                        (USB_SDI_O_s1_reset_n),
      .USB_SDI_O_s1_write_n                                        (USB_SDI_O_s1_write_n),
      .USB_SDI_O_s1_writedata                                      (USB_SDI_O_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_USB_SDI_O_s1                      (cpu_0_data_master_granted_USB_SDI_O_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_USB_SDI_O_s1            (cpu_0_data_master_qualified_request_USB_SDI_O_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_USB_SDI_O_s1              (cpu_0_data_master_read_data_valid_USB_SDI_O_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_USB_SDI_O_s1                     (cpu_0_data_master_requests_USB_SDI_O_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_USB_SDI_O_s1_end_xfer                                    (d1_USB_SDI_O_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  USB_SDI_O the_USB_SDI_O
    (
      .address    (USB_SDI_O_s1_address),
      .chipselect (USB_SDI_O_s1_chipselect),
      .clk        (clk_0),
      .out_port   (out_port_from_the_USB_SDI_O),
      .readdata   (USB_SDI_O_s1_readdata),
      .reset_n    (USB_SDI_O_s1_reset_n),
      .write_n    (USB_SDI_O_s1_write_n),
      .writedata  (USB_SDI_O_s1_writedata)
    );

  USB_SDO_I_s1_arbitrator the_USB_SDO_I_s1
    (
      .USB_SDO_I_s1_address                                        (USB_SDO_I_s1_address),
      .USB_SDO_I_s1_chipselect                                     (USB_SDO_I_s1_chipselect),
      .USB_SDO_I_s1_readdata                                       (USB_SDO_I_s1_readdata),
      .USB_SDO_I_s1_readdata_from_sa                               (USB_SDO_I_s1_readdata_from_sa),
      .USB_SDO_I_s1_reset_n                                        (USB_SDO_I_s1_reset_n),
      .USB_SDO_I_s1_write_n                                        (USB_SDO_I_s1_write_n),
      .USB_SDO_I_s1_writedata                                      (USB_SDO_I_s1_writedata),
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_USB_SDO_I_s1                      (cpu_0_data_master_granted_USB_SDO_I_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_USB_SDO_I_s1            (cpu_0_data_master_qualified_request_USB_SDO_I_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_USB_SDO_I_s1              (cpu_0_data_master_read_data_valid_USB_SDO_I_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_USB_SDO_I_s1                     (cpu_0_data_master_requests_USB_SDO_I_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_USB_SDO_I_s1_end_xfer                                    (d1_USB_SDO_I_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n)
    );

  USB_SDO_I the_USB_SDO_I
    (
      .address    (USB_SDO_I_s1_address),
      .chipselect (USB_SDO_I_s1_chipselect),
      .clk        (clk_0),
      .in_port    (in_port_to_the_USB_SDO_I),
      .readdata   (USB_SDO_I_s1_readdata),
      .reset_n    (USB_SDO_I_s1_reset_n),
      .write_n    (USB_SDO_I_s1_write_n),
      .writedata  (USB_SDO_I_s1_writedata)
    );

  cpu_0_jtag_debug_module_arbitrator the_cpu_0_jtag_debug_module
    (
      .clk                                                                (clk_0),
      .cpu_0_data_master_address_to_slave                                 (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_byteenable                                       (cpu_0_data_master_byteenable),
      .cpu_0_data_master_debugaccess                                      (cpu_0_data_master_debugaccess),
      .cpu_0_data_master_granted_cpu_0_jtag_debug_module                  (cpu_0_data_master_granted_cpu_0_jtag_debug_module),
      .cpu_0_data_master_latency_counter                                  (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_cpu_0_jtag_debug_module        (cpu_0_data_master_qualified_request_cpu_0_jtag_debug_module),
      .cpu_0_data_master_read                                             (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_cpu_0_jtag_debug_module          (cpu_0_data_master_read_data_valid_cpu_0_jtag_debug_module),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register        (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_cpu_0_jtag_debug_module                 (cpu_0_data_master_requests_cpu_0_jtag_debug_module),
      .cpu_0_data_master_write                                            (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                        (cpu_0_data_master_writedata),
      .cpu_0_instruction_master_address_to_slave                          (cpu_0_instruction_master_address_to_slave),
      .cpu_0_instruction_master_granted_cpu_0_jtag_debug_module           (cpu_0_instruction_master_granted_cpu_0_jtag_debug_module),
      .cpu_0_instruction_master_latency_counter                           (cpu_0_instruction_master_latency_counter),
      .cpu_0_instruction_master_qualified_request_cpu_0_jtag_debug_module (cpu_0_instruction_master_qualified_request_cpu_0_jtag_debug_module),
      .cpu_0_instruction_master_read                                      (cpu_0_instruction_master_read),
      .cpu_0_instruction_master_read_data_valid_cpu_0_jtag_debug_module   (cpu_0_instruction_master_read_data_valid_cpu_0_jtag_debug_module),
      .cpu_0_instruction_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_instruction_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_instruction_master_requests_cpu_0_jtag_debug_module          (cpu_0_instruction_master_requests_cpu_0_jtag_debug_module),
      .cpu_0_jtag_debug_module_address                                    (cpu_0_jtag_debug_module_address),
      .cpu_0_jtag_debug_module_begintransfer                              (cpu_0_jtag_debug_module_begintransfer),
      .cpu_0_jtag_debug_module_byteenable                                 (cpu_0_jtag_debug_module_byteenable),
      .cpu_0_jtag_debug_module_chipselect                                 (cpu_0_jtag_debug_module_chipselect),
      .cpu_0_jtag_debug_module_debugaccess                                (cpu_0_jtag_debug_module_debugaccess),
      .cpu_0_jtag_debug_module_readdata                                   (cpu_0_jtag_debug_module_readdata),
      .cpu_0_jtag_debug_module_readdata_from_sa                           (cpu_0_jtag_debug_module_readdata_from_sa),
      .cpu_0_jtag_debug_module_reset_n                                    (cpu_0_jtag_debug_module_reset_n),
      .cpu_0_jtag_debug_module_resetrequest                               (cpu_0_jtag_debug_module_resetrequest),
      .cpu_0_jtag_debug_module_resetrequest_from_sa                       (cpu_0_jtag_debug_module_resetrequest_from_sa),
      .cpu_0_jtag_debug_module_write                                      (cpu_0_jtag_debug_module_write),
      .cpu_0_jtag_debug_module_writedata                                  (cpu_0_jtag_debug_module_writedata),
      .d1_cpu_0_jtag_debug_module_end_xfer                                (d1_cpu_0_jtag_debug_module_end_xfer),
      .reset_n                                                            (clk_0_reset_n)
    );

  cpu_0_data_master_arbitrator the_cpu_0_data_master
    (
      .ADC_DATA_s1_readdata_from_sa                                                  (ADC_DATA_s1_readdata_from_sa),
      .BUZZER_DATA_s1_readdata_from_sa                                               (BUZZER_DATA_s1_readdata_from_sa),
      .DAC_DATA_s1_readdata_from_sa                                                  (DAC_DATA_s1_readdata_from_sa),
      .ETH_CLKOUT_I_s1_readdata_from_sa                                              (ETH_CLKOUT_I_s1_readdata_from_sa),
      .ETH_CS_O_s1_readdata_from_sa                                                  (ETH_CS_O_s1_readdata_from_sa),
      .ETH_INT_I_s1_readdata_from_sa                                                 (ETH_INT_I_s1_readdata_from_sa),
      .ETH_RESET_O_s1_readdata_from_sa                                               (ETH_RESET_O_s1_readdata_from_sa),
      .ETH_SCK_O_s1_readdata_from_sa                                                 (ETH_SCK_O_s1_readdata_from_sa),
      .ETH_SI_O_s1_readdata_from_sa                                                  (ETH_SI_O_s1_readdata_from_sa),
      .ETH_SO_I_s1_readdata_from_sa                                                  (ETH_SO_I_s1_readdata_from_sa),
      .ETH_WOL_I_s1_readdata_from_sa                                                 (ETH_WOL_I_s1_readdata_from_sa),
      .IR_DATA_s1_readdata_from_sa                                                   (IR_DATA_s1_readdata_from_sa),
      .KEY_FOCUS_s1_readdata_from_sa                                                 (KEY_FOCUS_s1_readdata_from_sa),
      .LCD_CS_s1_readdata_from_sa                                                    (LCD_CS_s1_readdata_from_sa),
      .LCD_DATA_s1_readdata_from_sa                                                  (LCD_DATA_s1_readdata_from_sa),
      .LCD_RD_s1_readdata_from_sa                                                    (LCD_RD_s1_readdata_from_sa),
      .LCD_RST_s1_readdata_from_sa                                                   (LCD_RST_s1_readdata_from_sa),
      .LCD_RS_s1_readdata_from_sa                                                    (LCD_RS_s1_readdata_from_sa),
      .LCD_WR_s1_readdata_from_sa                                                    (LCD_WR_s1_readdata_from_sa),
      .LED_DATA_s1_readdata_from_sa                                                  (LED_DATA_s1_readdata_from_sa),
      .PS2_DATA_REC_s1_readdata_from_sa                                              (PS2_DATA_REC_s1_readdata_from_sa),
      .RTC_DATA_s1_readdata_from_sa                                                  (RTC_DATA_s1_readdata_from_sa),
      .SCL_s1_readdata_from_sa                                                       (SCL_s1_readdata_from_sa),
      .SDA_s1_readdata_from_sa                                                       (SDA_s1_readdata_from_sa),
      .SD_CLK_s1_readdata_from_sa                                                    (SD_CLK_s1_readdata_from_sa),
      .SD_CS_s1_readdata_from_sa                                                     (SD_CS_s1_readdata_from_sa),
      .SD_DI_s1_readdata_from_sa                                                     (SD_DI_s1_readdata_from_sa),
      .SD_DO_s1_readdata_from_sa                                                     (SD_DO_s1_readdata_from_sa),
      .TEMP_DATA_s1_readdata_from_sa                                                 (TEMP_DATA_s1_readdata_from_sa),
      .TUBE_EN_s1_readdata_from_sa                                                   (TUBE_EN_s1_readdata_from_sa),
      .UART_RX_DATA_s1_readdata_from_sa                                              (UART_RX_DATA_s1_readdata_from_sa),
      .USB_INT_I_s1_readdata_from_sa                                                 (USB_INT_I_s1_readdata_from_sa),
      .USB_PC_I_s1_readdata_from_sa                                                  (USB_PC_I_s1_readdata_from_sa),
      .USB_RST_O_s1_readdata_from_sa                                                 (USB_RST_O_s1_readdata_from_sa),
      .USB_SCK_O_s1_readdata_from_sa                                                 (USB_SCK_O_s1_readdata_from_sa),
      .USB_SCS_O_s1_readdata_from_sa                                                 (USB_SCS_O_s1_readdata_from_sa),
      .USB_SDI_O_s1_readdata_from_sa                                                 (USB_SDI_O_s1_readdata_from_sa),
      .USB_SDO_I_s1_readdata_from_sa                                                 (USB_SDO_I_s1_readdata_from_sa),
      .clk                                                                           (clk_0),
      .cpu_0_data_master_address                                                     (cpu_0_data_master_address),
      .cpu_0_data_master_address_to_slave                                            (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_byteenable                                                  (cpu_0_data_master_byteenable),
      .cpu_0_data_master_byteenable_sdram_0_s1                                       (cpu_0_data_master_byteenable_sdram_0_s1),
      .cpu_0_data_master_dbs_address                                                 (cpu_0_data_master_dbs_address),
      .cpu_0_data_master_dbs_write_16                                                (cpu_0_data_master_dbs_write_16),
      .cpu_0_data_master_granted_ADC_DATA_s1                                         (cpu_0_data_master_granted_ADC_DATA_s1),
      .cpu_0_data_master_granted_BUZZER_DATA_s1                                      (cpu_0_data_master_granted_BUZZER_DATA_s1),
      .cpu_0_data_master_granted_DAC_DATA_s1                                         (cpu_0_data_master_granted_DAC_DATA_s1),
      .cpu_0_data_master_granted_ETH_CLKOUT_I_s1                                     (cpu_0_data_master_granted_ETH_CLKOUT_I_s1),
      .cpu_0_data_master_granted_ETH_CS_O_s1                                         (cpu_0_data_master_granted_ETH_CS_O_s1),
      .cpu_0_data_master_granted_ETH_INT_I_s1                                        (cpu_0_data_master_granted_ETH_INT_I_s1),
      .cpu_0_data_master_granted_ETH_RESET_O_s1                                      (cpu_0_data_master_granted_ETH_RESET_O_s1),
      .cpu_0_data_master_granted_ETH_SCK_O_s1                                        (cpu_0_data_master_granted_ETH_SCK_O_s1),
      .cpu_0_data_master_granted_ETH_SI_O_s1                                         (cpu_0_data_master_granted_ETH_SI_O_s1),
      .cpu_0_data_master_granted_ETH_SO_I_s1                                         (cpu_0_data_master_granted_ETH_SO_I_s1),
      .cpu_0_data_master_granted_ETH_WOL_I_s1                                        (cpu_0_data_master_granted_ETH_WOL_I_s1),
      .cpu_0_data_master_granted_IR_DATA_s1                                          (cpu_0_data_master_granted_IR_DATA_s1),
      .cpu_0_data_master_granted_KEY_FOCUS_s1                                        (cpu_0_data_master_granted_KEY_FOCUS_s1),
      .cpu_0_data_master_granted_LCD_CS_s1                                           (cpu_0_data_master_granted_LCD_CS_s1),
      .cpu_0_data_master_granted_LCD_DATA_s1                                         (cpu_0_data_master_granted_LCD_DATA_s1),
      .cpu_0_data_master_granted_LCD_RD_s1                                           (cpu_0_data_master_granted_LCD_RD_s1),
      .cpu_0_data_master_granted_LCD_RST_s1                                          (cpu_0_data_master_granted_LCD_RST_s1),
      .cpu_0_data_master_granted_LCD_RS_s1                                           (cpu_0_data_master_granted_LCD_RS_s1),
      .cpu_0_data_master_granted_LCD_WR_s1                                           (cpu_0_data_master_granted_LCD_WR_s1),
      .cpu_0_data_master_granted_LED_DATA_s1                                         (cpu_0_data_master_granted_LED_DATA_s1),
      .cpu_0_data_master_granted_PS2_DATA_REC_s1                                     (cpu_0_data_master_granted_PS2_DATA_REC_s1),
      .cpu_0_data_master_granted_RTC_DATA_s1                                         (cpu_0_data_master_granted_RTC_DATA_s1),
      .cpu_0_data_master_granted_SCL_s1                                              (cpu_0_data_master_granted_SCL_s1),
      .cpu_0_data_master_granted_SDA_s1                                              (cpu_0_data_master_granted_SDA_s1),
      .cpu_0_data_master_granted_SD_CLK_s1                                           (cpu_0_data_master_granted_SD_CLK_s1),
      .cpu_0_data_master_granted_SD_CS_s1                                            (cpu_0_data_master_granted_SD_CS_s1),
      .cpu_0_data_master_granted_SD_DI_s1                                            (cpu_0_data_master_granted_SD_DI_s1),
      .cpu_0_data_master_granted_SD_DO_s1                                            (cpu_0_data_master_granted_SD_DO_s1),
      .cpu_0_data_master_granted_TEMP_DATA_s1                                        (cpu_0_data_master_granted_TEMP_DATA_s1),
      .cpu_0_data_master_granted_TUBE_EN_s1                                          (cpu_0_data_master_granted_TUBE_EN_s1),
      .cpu_0_data_master_granted_UART_RX_DATA_s1                                     (cpu_0_data_master_granted_UART_RX_DATA_s1),
      .cpu_0_data_master_granted_USB_INT_I_s1                                        (cpu_0_data_master_granted_USB_INT_I_s1),
      .cpu_0_data_master_granted_USB_PC_I_s1                                         (cpu_0_data_master_granted_USB_PC_I_s1),
      .cpu_0_data_master_granted_USB_RST_O_s1                                        (cpu_0_data_master_granted_USB_RST_O_s1),
      .cpu_0_data_master_granted_USB_SCK_O_s1                                        (cpu_0_data_master_granted_USB_SCK_O_s1),
      .cpu_0_data_master_granted_USB_SCS_O_s1                                        (cpu_0_data_master_granted_USB_SCS_O_s1),
      .cpu_0_data_master_granted_USB_SDI_O_s1                                        (cpu_0_data_master_granted_USB_SDI_O_s1),
      .cpu_0_data_master_granted_USB_SDO_I_s1                                        (cpu_0_data_master_granted_USB_SDO_I_s1),
      .cpu_0_data_master_granted_cpu_0_jtag_debug_module                             (cpu_0_data_master_granted_cpu_0_jtag_debug_module),
      .cpu_0_data_master_granted_epcs_flash_controller_0_epcs_control_port           (cpu_0_data_master_granted_epcs_flash_controller_0_epcs_control_port),
      .cpu_0_data_master_granted_sdram_0_s1                                          (cpu_0_data_master_granted_sdram_0_s1),
      .cpu_0_data_master_granted_sysid_0_control_slave                               (cpu_0_data_master_granted_sysid_0_control_slave),
      .cpu_0_data_master_granted_timer_0_s1                                          (cpu_0_data_master_granted_timer_0_s1),
      .cpu_0_data_master_granted_timer_1_s1                                          (cpu_0_data_master_granted_timer_1_s1),
      .cpu_0_data_master_granted_uart_0_s1                                           (cpu_0_data_master_granted_uart_0_s1),
      .cpu_0_data_master_irq                                                         (cpu_0_data_master_irq),
      .cpu_0_data_master_latency_counter                                             (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_ADC_DATA_s1                               (cpu_0_data_master_qualified_request_ADC_DATA_s1),
      .cpu_0_data_master_qualified_request_BUZZER_DATA_s1                            (cpu_0_data_master_qualified_request_BUZZER_DATA_s1),
      .cpu_0_data_master_qualified_request_DAC_DATA_s1                               (cpu_0_data_master_qualified_request_DAC_DATA_s1),
      .cpu_0_data_master_qualified_request_ETH_CLKOUT_I_s1                           (cpu_0_data_master_qualified_request_ETH_CLKOUT_I_s1),
      .cpu_0_data_master_qualified_request_ETH_CS_O_s1                               (cpu_0_data_master_qualified_request_ETH_CS_O_s1),
      .cpu_0_data_master_qualified_request_ETH_INT_I_s1                              (cpu_0_data_master_qualified_request_ETH_INT_I_s1),
      .cpu_0_data_master_qualified_request_ETH_RESET_O_s1                            (cpu_0_data_master_qualified_request_ETH_RESET_O_s1),
      .cpu_0_data_master_qualified_request_ETH_SCK_O_s1                              (cpu_0_data_master_qualified_request_ETH_SCK_O_s1),
      .cpu_0_data_master_qualified_request_ETH_SI_O_s1                               (cpu_0_data_master_qualified_request_ETH_SI_O_s1),
      .cpu_0_data_master_qualified_request_ETH_SO_I_s1                               (cpu_0_data_master_qualified_request_ETH_SO_I_s1),
      .cpu_0_data_master_qualified_request_ETH_WOL_I_s1                              (cpu_0_data_master_qualified_request_ETH_WOL_I_s1),
      .cpu_0_data_master_qualified_request_IR_DATA_s1                                (cpu_0_data_master_qualified_request_IR_DATA_s1),
      .cpu_0_data_master_qualified_request_KEY_FOCUS_s1                              (cpu_0_data_master_qualified_request_KEY_FOCUS_s1),
      .cpu_0_data_master_qualified_request_LCD_CS_s1                                 (cpu_0_data_master_qualified_request_LCD_CS_s1),
      .cpu_0_data_master_qualified_request_LCD_DATA_s1                               (cpu_0_data_master_qualified_request_LCD_DATA_s1),
      .cpu_0_data_master_qualified_request_LCD_RD_s1                                 (cpu_0_data_master_qualified_request_LCD_RD_s1),
      .cpu_0_data_master_qualified_request_LCD_RST_s1                                (cpu_0_data_master_qualified_request_LCD_RST_s1),
      .cpu_0_data_master_qualified_request_LCD_RS_s1                                 (cpu_0_data_master_qualified_request_LCD_RS_s1),
      .cpu_0_data_master_qualified_request_LCD_WR_s1                                 (cpu_0_data_master_qualified_request_LCD_WR_s1),
      .cpu_0_data_master_qualified_request_LED_DATA_s1                               (cpu_0_data_master_qualified_request_LED_DATA_s1),
      .cpu_0_data_master_qualified_request_PS2_DATA_REC_s1                           (cpu_0_data_master_qualified_request_PS2_DATA_REC_s1),
      .cpu_0_data_master_qualified_request_RTC_DATA_s1                               (cpu_0_data_master_qualified_request_RTC_DATA_s1),
      .cpu_0_data_master_qualified_request_SCL_s1                                    (cpu_0_data_master_qualified_request_SCL_s1),
      .cpu_0_data_master_qualified_request_SDA_s1                                    (cpu_0_data_master_qualified_request_SDA_s1),
      .cpu_0_data_master_qualified_request_SD_CLK_s1                                 (cpu_0_data_master_qualified_request_SD_CLK_s1),
      .cpu_0_data_master_qualified_request_SD_CS_s1                                  (cpu_0_data_master_qualified_request_SD_CS_s1),
      .cpu_0_data_master_qualified_request_SD_DI_s1                                  (cpu_0_data_master_qualified_request_SD_DI_s1),
      .cpu_0_data_master_qualified_request_SD_DO_s1                                  (cpu_0_data_master_qualified_request_SD_DO_s1),
      .cpu_0_data_master_qualified_request_TEMP_DATA_s1                              (cpu_0_data_master_qualified_request_TEMP_DATA_s1),
      .cpu_0_data_master_qualified_request_TUBE_EN_s1                                (cpu_0_data_master_qualified_request_TUBE_EN_s1),
      .cpu_0_data_master_qualified_request_UART_RX_DATA_s1                           (cpu_0_data_master_qualified_request_UART_RX_DATA_s1),
      .cpu_0_data_master_qualified_request_USB_INT_I_s1                              (cpu_0_data_master_qualified_request_USB_INT_I_s1),
      .cpu_0_data_master_qualified_request_USB_PC_I_s1                               (cpu_0_data_master_qualified_request_USB_PC_I_s1),
      .cpu_0_data_master_qualified_request_USB_RST_O_s1                              (cpu_0_data_master_qualified_request_USB_RST_O_s1),
      .cpu_0_data_master_qualified_request_USB_SCK_O_s1                              (cpu_0_data_master_qualified_request_USB_SCK_O_s1),
      .cpu_0_data_master_qualified_request_USB_SCS_O_s1                              (cpu_0_data_master_qualified_request_USB_SCS_O_s1),
      .cpu_0_data_master_qualified_request_USB_SDI_O_s1                              (cpu_0_data_master_qualified_request_USB_SDI_O_s1),
      .cpu_0_data_master_qualified_request_USB_SDO_I_s1                              (cpu_0_data_master_qualified_request_USB_SDO_I_s1),
      .cpu_0_data_master_qualified_request_cpu_0_jtag_debug_module                   (cpu_0_data_master_qualified_request_cpu_0_jtag_debug_module),
      .cpu_0_data_master_qualified_request_epcs_flash_controller_0_epcs_control_port (cpu_0_data_master_qualified_request_epcs_flash_controller_0_epcs_control_port),
      .cpu_0_data_master_qualified_request_sdram_0_s1                                (cpu_0_data_master_qualified_request_sdram_0_s1),
      .cpu_0_data_master_qualified_request_sysid_0_control_slave                     (cpu_0_data_master_qualified_request_sysid_0_control_slave),
      .cpu_0_data_master_qualified_request_timer_0_s1                                (cpu_0_data_master_qualified_request_timer_0_s1),
      .cpu_0_data_master_qualified_request_timer_1_s1                                (cpu_0_data_master_qualified_request_timer_1_s1),
      .cpu_0_data_master_qualified_request_uart_0_s1                                 (cpu_0_data_master_qualified_request_uart_0_s1),
      .cpu_0_data_master_read                                                        (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_ADC_DATA_s1                                 (cpu_0_data_master_read_data_valid_ADC_DATA_s1),
      .cpu_0_data_master_read_data_valid_BUZZER_DATA_s1                              (cpu_0_data_master_read_data_valid_BUZZER_DATA_s1),
      .cpu_0_data_master_read_data_valid_DAC_DATA_s1                                 (cpu_0_data_master_read_data_valid_DAC_DATA_s1),
      .cpu_0_data_master_read_data_valid_ETH_CLKOUT_I_s1                             (cpu_0_data_master_read_data_valid_ETH_CLKOUT_I_s1),
      .cpu_0_data_master_read_data_valid_ETH_CS_O_s1                                 (cpu_0_data_master_read_data_valid_ETH_CS_O_s1),
      .cpu_0_data_master_read_data_valid_ETH_INT_I_s1                                (cpu_0_data_master_read_data_valid_ETH_INT_I_s1),
      .cpu_0_data_master_read_data_valid_ETH_RESET_O_s1                              (cpu_0_data_master_read_data_valid_ETH_RESET_O_s1),
      .cpu_0_data_master_read_data_valid_ETH_SCK_O_s1                                (cpu_0_data_master_read_data_valid_ETH_SCK_O_s1),
      .cpu_0_data_master_read_data_valid_ETH_SI_O_s1                                 (cpu_0_data_master_read_data_valid_ETH_SI_O_s1),
      .cpu_0_data_master_read_data_valid_ETH_SO_I_s1                                 (cpu_0_data_master_read_data_valid_ETH_SO_I_s1),
      .cpu_0_data_master_read_data_valid_ETH_WOL_I_s1                                (cpu_0_data_master_read_data_valid_ETH_WOL_I_s1),
      .cpu_0_data_master_read_data_valid_IR_DATA_s1                                  (cpu_0_data_master_read_data_valid_IR_DATA_s1),
      .cpu_0_data_master_read_data_valid_KEY_FOCUS_s1                                (cpu_0_data_master_read_data_valid_KEY_FOCUS_s1),
      .cpu_0_data_master_read_data_valid_LCD_CS_s1                                   (cpu_0_data_master_read_data_valid_LCD_CS_s1),
      .cpu_0_data_master_read_data_valid_LCD_DATA_s1                                 (cpu_0_data_master_read_data_valid_LCD_DATA_s1),
      .cpu_0_data_master_read_data_valid_LCD_RD_s1                                   (cpu_0_data_master_read_data_valid_LCD_RD_s1),
      .cpu_0_data_master_read_data_valid_LCD_RST_s1                                  (cpu_0_data_master_read_data_valid_LCD_RST_s1),
      .cpu_0_data_master_read_data_valid_LCD_RS_s1                                   (cpu_0_data_master_read_data_valid_LCD_RS_s1),
      .cpu_0_data_master_read_data_valid_LCD_WR_s1                                   (cpu_0_data_master_read_data_valid_LCD_WR_s1),
      .cpu_0_data_master_read_data_valid_LED_DATA_s1                                 (cpu_0_data_master_read_data_valid_LED_DATA_s1),
      .cpu_0_data_master_read_data_valid_PS2_DATA_REC_s1                             (cpu_0_data_master_read_data_valid_PS2_DATA_REC_s1),
      .cpu_0_data_master_read_data_valid_RTC_DATA_s1                                 (cpu_0_data_master_read_data_valid_RTC_DATA_s1),
      .cpu_0_data_master_read_data_valid_SCL_s1                                      (cpu_0_data_master_read_data_valid_SCL_s1),
      .cpu_0_data_master_read_data_valid_SDA_s1                                      (cpu_0_data_master_read_data_valid_SDA_s1),
      .cpu_0_data_master_read_data_valid_SD_CLK_s1                                   (cpu_0_data_master_read_data_valid_SD_CLK_s1),
      .cpu_0_data_master_read_data_valid_SD_CS_s1                                    (cpu_0_data_master_read_data_valid_SD_CS_s1),
      .cpu_0_data_master_read_data_valid_SD_DI_s1                                    (cpu_0_data_master_read_data_valid_SD_DI_s1),
      .cpu_0_data_master_read_data_valid_SD_DO_s1                                    (cpu_0_data_master_read_data_valid_SD_DO_s1),
      .cpu_0_data_master_read_data_valid_TEMP_DATA_s1                                (cpu_0_data_master_read_data_valid_TEMP_DATA_s1),
      .cpu_0_data_master_read_data_valid_TUBE_EN_s1                                  (cpu_0_data_master_read_data_valid_TUBE_EN_s1),
      .cpu_0_data_master_read_data_valid_UART_RX_DATA_s1                             (cpu_0_data_master_read_data_valid_UART_RX_DATA_s1),
      .cpu_0_data_master_read_data_valid_USB_INT_I_s1                                (cpu_0_data_master_read_data_valid_USB_INT_I_s1),
      .cpu_0_data_master_read_data_valid_USB_PC_I_s1                                 (cpu_0_data_master_read_data_valid_USB_PC_I_s1),
      .cpu_0_data_master_read_data_valid_USB_RST_O_s1                                (cpu_0_data_master_read_data_valid_USB_RST_O_s1),
      .cpu_0_data_master_read_data_valid_USB_SCK_O_s1                                (cpu_0_data_master_read_data_valid_USB_SCK_O_s1),
      .cpu_0_data_master_read_data_valid_USB_SCS_O_s1                                (cpu_0_data_master_read_data_valid_USB_SCS_O_s1),
      .cpu_0_data_master_read_data_valid_USB_SDI_O_s1                                (cpu_0_data_master_read_data_valid_USB_SDI_O_s1),
      .cpu_0_data_master_read_data_valid_USB_SDO_I_s1                                (cpu_0_data_master_read_data_valid_USB_SDO_I_s1),
      .cpu_0_data_master_read_data_valid_cpu_0_jtag_debug_module                     (cpu_0_data_master_read_data_valid_cpu_0_jtag_debug_module),
      .cpu_0_data_master_read_data_valid_epcs_flash_controller_0_epcs_control_port   (cpu_0_data_master_read_data_valid_epcs_flash_controller_0_epcs_control_port),
      .cpu_0_data_master_read_data_valid_sdram_0_s1                                  (cpu_0_data_master_read_data_valid_sdram_0_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register                   (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_read_data_valid_sysid_0_control_slave                       (cpu_0_data_master_read_data_valid_sysid_0_control_slave),
      .cpu_0_data_master_read_data_valid_timer_0_s1                                  (cpu_0_data_master_read_data_valid_timer_0_s1),
      .cpu_0_data_master_read_data_valid_timer_1_s1                                  (cpu_0_data_master_read_data_valid_timer_1_s1),
      .cpu_0_data_master_read_data_valid_uart_0_s1                                   (cpu_0_data_master_read_data_valid_uart_0_s1),
      .cpu_0_data_master_readdata                                                    (cpu_0_data_master_readdata),
      .cpu_0_data_master_readdatavalid                                               (cpu_0_data_master_readdatavalid),
      .cpu_0_data_master_requests_ADC_DATA_s1                                        (cpu_0_data_master_requests_ADC_DATA_s1),
      .cpu_0_data_master_requests_BUZZER_DATA_s1                                     (cpu_0_data_master_requests_BUZZER_DATA_s1),
      .cpu_0_data_master_requests_DAC_DATA_s1                                        (cpu_0_data_master_requests_DAC_DATA_s1),
      .cpu_0_data_master_requests_ETH_CLKOUT_I_s1                                    (cpu_0_data_master_requests_ETH_CLKOUT_I_s1),
      .cpu_0_data_master_requests_ETH_CS_O_s1                                        (cpu_0_data_master_requests_ETH_CS_O_s1),
      .cpu_0_data_master_requests_ETH_INT_I_s1                                       (cpu_0_data_master_requests_ETH_INT_I_s1),
      .cpu_0_data_master_requests_ETH_RESET_O_s1                                     (cpu_0_data_master_requests_ETH_RESET_O_s1),
      .cpu_0_data_master_requests_ETH_SCK_O_s1                                       (cpu_0_data_master_requests_ETH_SCK_O_s1),
      .cpu_0_data_master_requests_ETH_SI_O_s1                                        (cpu_0_data_master_requests_ETH_SI_O_s1),
      .cpu_0_data_master_requests_ETH_SO_I_s1                                        (cpu_0_data_master_requests_ETH_SO_I_s1),
      .cpu_0_data_master_requests_ETH_WOL_I_s1                                       (cpu_0_data_master_requests_ETH_WOL_I_s1),
      .cpu_0_data_master_requests_IR_DATA_s1                                         (cpu_0_data_master_requests_IR_DATA_s1),
      .cpu_0_data_master_requests_KEY_FOCUS_s1                                       (cpu_0_data_master_requests_KEY_FOCUS_s1),
      .cpu_0_data_master_requests_LCD_CS_s1                                          (cpu_0_data_master_requests_LCD_CS_s1),
      .cpu_0_data_master_requests_LCD_DATA_s1                                        (cpu_0_data_master_requests_LCD_DATA_s1),
      .cpu_0_data_master_requests_LCD_RD_s1                                          (cpu_0_data_master_requests_LCD_RD_s1),
      .cpu_0_data_master_requests_LCD_RST_s1                                         (cpu_0_data_master_requests_LCD_RST_s1),
      .cpu_0_data_master_requests_LCD_RS_s1                                          (cpu_0_data_master_requests_LCD_RS_s1),
      .cpu_0_data_master_requests_LCD_WR_s1                                          (cpu_0_data_master_requests_LCD_WR_s1),
      .cpu_0_data_master_requests_LED_DATA_s1                                        (cpu_0_data_master_requests_LED_DATA_s1),
      .cpu_0_data_master_requests_PS2_DATA_REC_s1                                    (cpu_0_data_master_requests_PS2_DATA_REC_s1),
      .cpu_0_data_master_requests_RTC_DATA_s1                                        (cpu_0_data_master_requests_RTC_DATA_s1),
      .cpu_0_data_master_requests_SCL_s1                                             (cpu_0_data_master_requests_SCL_s1),
      .cpu_0_data_master_requests_SDA_s1                                             (cpu_0_data_master_requests_SDA_s1),
      .cpu_0_data_master_requests_SD_CLK_s1                                          (cpu_0_data_master_requests_SD_CLK_s1),
      .cpu_0_data_master_requests_SD_CS_s1                                           (cpu_0_data_master_requests_SD_CS_s1),
      .cpu_0_data_master_requests_SD_DI_s1                                           (cpu_0_data_master_requests_SD_DI_s1),
      .cpu_0_data_master_requests_SD_DO_s1                                           (cpu_0_data_master_requests_SD_DO_s1),
      .cpu_0_data_master_requests_TEMP_DATA_s1                                       (cpu_0_data_master_requests_TEMP_DATA_s1),
      .cpu_0_data_master_requests_TUBE_EN_s1                                         (cpu_0_data_master_requests_TUBE_EN_s1),
      .cpu_0_data_master_requests_UART_RX_DATA_s1                                    (cpu_0_data_master_requests_UART_RX_DATA_s1),
      .cpu_0_data_master_requests_USB_INT_I_s1                                       (cpu_0_data_master_requests_USB_INT_I_s1),
      .cpu_0_data_master_requests_USB_PC_I_s1                                        (cpu_0_data_master_requests_USB_PC_I_s1),
      .cpu_0_data_master_requests_USB_RST_O_s1                                       (cpu_0_data_master_requests_USB_RST_O_s1),
      .cpu_0_data_master_requests_USB_SCK_O_s1                                       (cpu_0_data_master_requests_USB_SCK_O_s1),
      .cpu_0_data_master_requests_USB_SCS_O_s1                                       (cpu_0_data_master_requests_USB_SCS_O_s1),
      .cpu_0_data_master_requests_USB_SDI_O_s1                                       (cpu_0_data_master_requests_USB_SDI_O_s1),
      .cpu_0_data_master_requests_USB_SDO_I_s1                                       (cpu_0_data_master_requests_USB_SDO_I_s1),
      .cpu_0_data_master_requests_cpu_0_jtag_debug_module                            (cpu_0_data_master_requests_cpu_0_jtag_debug_module),
      .cpu_0_data_master_requests_epcs_flash_controller_0_epcs_control_port          (cpu_0_data_master_requests_epcs_flash_controller_0_epcs_control_port),
      .cpu_0_data_master_requests_sdram_0_s1                                         (cpu_0_data_master_requests_sdram_0_s1),
      .cpu_0_data_master_requests_sysid_0_control_slave                              (cpu_0_data_master_requests_sysid_0_control_slave),
      .cpu_0_data_master_requests_timer_0_s1                                         (cpu_0_data_master_requests_timer_0_s1),
      .cpu_0_data_master_requests_timer_1_s1                                         (cpu_0_data_master_requests_timer_1_s1),
      .cpu_0_data_master_requests_uart_0_s1                                          (cpu_0_data_master_requests_uart_0_s1),
      .cpu_0_data_master_waitrequest                                                 (cpu_0_data_master_waitrequest),
      .cpu_0_data_master_write                                                       (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                                   (cpu_0_data_master_writedata),
      .cpu_0_jtag_debug_module_readdata_from_sa                                      (cpu_0_jtag_debug_module_readdata_from_sa),
      .d1_ADC_DATA_s1_end_xfer                                                       (d1_ADC_DATA_s1_end_xfer),
      .d1_BUZZER_DATA_s1_end_xfer                                                    (d1_BUZZER_DATA_s1_end_xfer),
      .d1_DAC_DATA_s1_end_xfer                                                       (d1_DAC_DATA_s1_end_xfer),
      .d1_ETH_CLKOUT_I_s1_end_xfer                                                   (d1_ETH_CLKOUT_I_s1_end_xfer),
      .d1_ETH_CS_O_s1_end_xfer                                                       (d1_ETH_CS_O_s1_end_xfer),
      .d1_ETH_INT_I_s1_end_xfer                                                      (d1_ETH_INT_I_s1_end_xfer),
      .d1_ETH_RESET_O_s1_end_xfer                                                    (d1_ETH_RESET_O_s1_end_xfer),
      .d1_ETH_SCK_O_s1_end_xfer                                                      (d1_ETH_SCK_O_s1_end_xfer),
      .d1_ETH_SI_O_s1_end_xfer                                                       (d1_ETH_SI_O_s1_end_xfer),
      .d1_ETH_SO_I_s1_end_xfer                                                       (d1_ETH_SO_I_s1_end_xfer),
      .d1_ETH_WOL_I_s1_end_xfer                                                      (d1_ETH_WOL_I_s1_end_xfer),
      .d1_IR_DATA_s1_end_xfer                                                        (d1_IR_DATA_s1_end_xfer),
      .d1_KEY_FOCUS_s1_end_xfer                                                      (d1_KEY_FOCUS_s1_end_xfer),
      .d1_LCD_CS_s1_end_xfer                                                         (d1_LCD_CS_s1_end_xfer),
      .d1_LCD_DATA_s1_end_xfer                                                       (d1_LCD_DATA_s1_end_xfer),
      .d1_LCD_RD_s1_end_xfer                                                         (d1_LCD_RD_s1_end_xfer),
      .d1_LCD_RST_s1_end_xfer                                                        (d1_LCD_RST_s1_end_xfer),
      .d1_LCD_RS_s1_end_xfer                                                         (d1_LCD_RS_s1_end_xfer),
      .d1_LCD_WR_s1_end_xfer                                                         (d1_LCD_WR_s1_end_xfer),
      .d1_LED_DATA_s1_end_xfer                                                       (d1_LED_DATA_s1_end_xfer),
      .d1_PS2_DATA_REC_s1_end_xfer                                                   (d1_PS2_DATA_REC_s1_end_xfer),
      .d1_RTC_DATA_s1_end_xfer                                                       (d1_RTC_DATA_s1_end_xfer),
      .d1_SCL_s1_end_xfer                                                            (d1_SCL_s1_end_xfer),
      .d1_SDA_s1_end_xfer                                                            (d1_SDA_s1_end_xfer),
      .d1_SD_CLK_s1_end_xfer                                                         (d1_SD_CLK_s1_end_xfer),
      .d1_SD_CS_s1_end_xfer                                                          (d1_SD_CS_s1_end_xfer),
      .d1_SD_DI_s1_end_xfer                                                          (d1_SD_DI_s1_end_xfer),
      .d1_SD_DO_s1_end_xfer                                                          (d1_SD_DO_s1_end_xfer),
      .d1_TEMP_DATA_s1_end_xfer                                                      (d1_TEMP_DATA_s1_end_xfer),
      .d1_TUBE_EN_s1_end_xfer                                                        (d1_TUBE_EN_s1_end_xfer),
      .d1_UART_RX_DATA_s1_end_xfer                                                   (d1_UART_RX_DATA_s1_end_xfer),
      .d1_USB_INT_I_s1_end_xfer                                                      (d1_USB_INT_I_s1_end_xfer),
      .d1_USB_PC_I_s1_end_xfer                                                       (d1_USB_PC_I_s1_end_xfer),
      .d1_USB_RST_O_s1_end_xfer                                                      (d1_USB_RST_O_s1_end_xfer),
      .d1_USB_SCK_O_s1_end_xfer                                                      (d1_USB_SCK_O_s1_end_xfer),
      .d1_USB_SCS_O_s1_end_xfer                                                      (d1_USB_SCS_O_s1_end_xfer),
      .d1_USB_SDI_O_s1_end_xfer                                                      (d1_USB_SDI_O_s1_end_xfer),
      .d1_USB_SDO_I_s1_end_xfer                                                      (d1_USB_SDO_I_s1_end_xfer),
      .d1_cpu_0_jtag_debug_module_end_xfer                                           (d1_cpu_0_jtag_debug_module_end_xfer),
      .d1_epcs_flash_controller_0_epcs_control_port_end_xfer                         (d1_epcs_flash_controller_0_epcs_control_port_end_xfer),
      .d1_sdram_0_s1_end_xfer                                                        (d1_sdram_0_s1_end_xfer),
      .d1_sysid_0_control_slave_end_xfer                                             (d1_sysid_0_control_slave_end_xfer),
      .d1_timer_0_s1_end_xfer                                                        (d1_timer_0_s1_end_xfer),
      .d1_timer_1_s1_end_xfer                                                        (d1_timer_1_s1_end_xfer),
      .d1_uart_0_s1_end_xfer                                                         (d1_uart_0_s1_end_xfer),
      .epcs_flash_controller_0_epcs_control_port_irq_from_sa                         (epcs_flash_controller_0_epcs_control_port_irq_from_sa),
      .epcs_flash_controller_0_epcs_control_port_readdata_from_sa                    (epcs_flash_controller_0_epcs_control_port_readdata_from_sa),
      .reset_n                                                                       (clk_0_reset_n),
      .sdram_0_s1_readdata_from_sa                                                   (sdram_0_s1_readdata_from_sa),
      .sdram_0_s1_waitrequest_from_sa                                                (sdram_0_s1_waitrequest_from_sa),
      .sysid_0_control_slave_readdata_from_sa                                        (sysid_0_control_slave_readdata_from_sa),
      .timer_0_s1_irq_from_sa                                                        (timer_0_s1_irq_from_sa),
      .timer_0_s1_readdata_from_sa                                                   (timer_0_s1_readdata_from_sa),
      .timer_1_s1_irq_from_sa                                                        (timer_1_s1_irq_from_sa),
      .timer_1_s1_readdata_from_sa                                                   (timer_1_s1_readdata_from_sa),
      .uart_0_s1_irq_from_sa                                                         (uart_0_s1_irq_from_sa),
      .uart_0_s1_readdata_from_sa                                                    (uart_0_s1_readdata_from_sa)
    );

  cpu_0_instruction_master_arbitrator the_cpu_0_instruction_master
    (
      .clk                                                                                  (clk_0),
      .cpu_0_instruction_master_address                                                     (cpu_0_instruction_master_address),
      .cpu_0_instruction_master_address_to_slave                                            (cpu_0_instruction_master_address_to_slave),
      .cpu_0_instruction_master_dbs_address                                                 (cpu_0_instruction_master_dbs_address),
      .cpu_0_instruction_master_granted_cpu_0_jtag_debug_module                             (cpu_0_instruction_master_granted_cpu_0_jtag_debug_module),
      .cpu_0_instruction_master_granted_epcs_flash_controller_0_epcs_control_port           (cpu_0_instruction_master_granted_epcs_flash_controller_0_epcs_control_port),
      .cpu_0_instruction_master_granted_sdram_0_s1                                          (cpu_0_instruction_master_granted_sdram_0_s1),
      .cpu_0_instruction_master_latency_counter                                             (cpu_0_instruction_master_latency_counter),
      .cpu_0_instruction_master_qualified_request_cpu_0_jtag_debug_module                   (cpu_0_instruction_master_qualified_request_cpu_0_jtag_debug_module),
      .cpu_0_instruction_master_qualified_request_epcs_flash_controller_0_epcs_control_port (cpu_0_instruction_master_qualified_request_epcs_flash_controller_0_epcs_control_port),
      .cpu_0_instruction_master_qualified_request_sdram_0_s1                                (cpu_0_instruction_master_qualified_request_sdram_0_s1),
      .cpu_0_instruction_master_read                                                        (cpu_0_instruction_master_read),
      .cpu_0_instruction_master_read_data_valid_cpu_0_jtag_debug_module                     (cpu_0_instruction_master_read_data_valid_cpu_0_jtag_debug_module),
      .cpu_0_instruction_master_read_data_valid_epcs_flash_controller_0_epcs_control_port   (cpu_0_instruction_master_read_data_valid_epcs_flash_controller_0_epcs_control_port),
      .cpu_0_instruction_master_read_data_valid_sdram_0_s1                                  (cpu_0_instruction_master_read_data_valid_sdram_0_s1),
      .cpu_0_instruction_master_read_data_valid_sdram_0_s1_shift_register                   (cpu_0_instruction_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_instruction_master_readdata                                                    (cpu_0_instruction_master_readdata),
      .cpu_0_instruction_master_readdatavalid                                               (cpu_0_instruction_master_readdatavalid),
      .cpu_0_instruction_master_requests_cpu_0_jtag_debug_module                            (cpu_0_instruction_master_requests_cpu_0_jtag_debug_module),
      .cpu_0_instruction_master_requests_epcs_flash_controller_0_epcs_control_port          (cpu_0_instruction_master_requests_epcs_flash_controller_0_epcs_control_port),
      .cpu_0_instruction_master_requests_sdram_0_s1                                         (cpu_0_instruction_master_requests_sdram_0_s1),
      .cpu_0_instruction_master_waitrequest                                                 (cpu_0_instruction_master_waitrequest),
      .cpu_0_jtag_debug_module_readdata_from_sa                                             (cpu_0_jtag_debug_module_readdata_from_sa),
      .d1_cpu_0_jtag_debug_module_end_xfer                                                  (d1_cpu_0_jtag_debug_module_end_xfer),
      .d1_epcs_flash_controller_0_epcs_control_port_end_xfer                                (d1_epcs_flash_controller_0_epcs_control_port_end_xfer),
      .d1_sdram_0_s1_end_xfer                                                               (d1_sdram_0_s1_end_xfer),
      .epcs_flash_controller_0_epcs_control_port_readdata_from_sa                           (epcs_flash_controller_0_epcs_control_port_readdata_from_sa),
      .reset_n                                                                              (clk_0_reset_n),
      .sdram_0_s1_readdata_from_sa                                                          (sdram_0_s1_readdata_from_sa),
      .sdram_0_s1_waitrequest_from_sa                                                       (sdram_0_s1_waitrequest_from_sa)
    );

  cpu_0 the_cpu_0
    (
      .clk                                   (clk_0),
      .d_address                             (cpu_0_data_master_address),
      .d_byteenable                          (cpu_0_data_master_byteenable),
      .d_irq                                 (cpu_0_data_master_irq),
      .d_read                                (cpu_0_data_master_read),
      .d_readdata                            (cpu_0_data_master_readdata),
      .d_readdatavalid                       (cpu_0_data_master_readdatavalid),
      .d_waitrequest                         (cpu_0_data_master_waitrequest),
      .d_write                               (cpu_0_data_master_write),
      .d_writedata                           (cpu_0_data_master_writedata),
      .i_address                             (cpu_0_instruction_master_address),
      .i_read                                (cpu_0_instruction_master_read),
      .i_readdata                            (cpu_0_instruction_master_readdata),
      .i_readdatavalid                       (cpu_0_instruction_master_readdatavalid),
      .i_waitrequest                         (cpu_0_instruction_master_waitrequest),
      .jtag_debug_module_address             (cpu_0_jtag_debug_module_address),
      .jtag_debug_module_begintransfer       (cpu_0_jtag_debug_module_begintransfer),
      .jtag_debug_module_byteenable          (cpu_0_jtag_debug_module_byteenable),
      .jtag_debug_module_debugaccess         (cpu_0_jtag_debug_module_debugaccess),
      .jtag_debug_module_debugaccess_to_roms (cpu_0_data_master_debugaccess),
      .jtag_debug_module_readdata            (cpu_0_jtag_debug_module_readdata),
      .jtag_debug_module_resetrequest        (cpu_0_jtag_debug_module_resetrequest),
      .jtag_debug_module_select              (cpu_0_jtag_debug_module_chipselect),
      .jtag_debug_module_write               (cpu_0_jtag_debug_module_write),
      .jtag_debug_module_writedata           (cpu_0_jtag_debug_module_writedata),
      .reset_n                               (cpu_0_jtag_debug_module_reset_n)
    );

  epcs_flash_controller_0_epcs_control_port_arbitrator the_epcs_flash_controller_0_epcs_control_port
    (
      .clk                                                                                  (clk_0),
      .cpu_0_data_master_address_to_slave                                                   (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_epcs_flash_controller_0_epcs_control_port                  (cpu_0_data_master_granted_epcs_flash_controller_0_epcs_control_port),
      .cpu_0_data_master_latency_counter                                                    (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_epcs_flash_controller_0_epcs_control_port        (cpu_0_data_master_qualified_request_epcs_flash_controller_0_epcs_control_port),
      .cpu_0_data_master_read                                                               (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_epcs_flash_controller_0_epcs_control_port          (cpu_0_data_master_read_data_valid_epcs_flash_controller_0_epcs_control_port),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register                          (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_epcs_flash_controller_0_epcs_control_port                 (cpu_0_data_master_requests_epcs_flash_controller_0_epcs_control_port),
      .cpu_0_data_master_write                                                              (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                                          (cpu_0_data_master_writedata),
      .cpu_0_instruction_master_address_to_slave                                            (cpu_0_instruction_master_address_to_slave),
      .cpu_0_instruction_master_granted_epcs_flash_controller_0_epcs_control_port           (cpu_0_instruction_master_granted_epcs_flash_controller_0_epcs_control_port),
      .cpu_0_instruction_master_latency_counter                                             (cpu_0_instruction_master_latency_counter),
      .cpu_0_instruction_master_qualified_request_epcs_flash_controller_0_epcs_control_port (cpu_0_instruction_master_qualified_request_epcs_flash_controller_0_epcs_control_port),
      .cpu_0_instruction_master_read                                                        (cpu_0_instruction_master_read),
      .cpu_0_instruction_master_read_data_valid_epcs_flash_controller_0_epcs_control_port   (cpu_0_instruction_master_read_data_valid_epcs_flash_controller_0_epcs_control_port),
      .cpu_0_instruction_master_read_data_valid_sdram_0_s1_shift_register                   (cpu_0_instruction_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_instruction_master_requests_epcs_flash_controller_0_epcs_control_port          (cpu_0_instruction_master_requests_epcs_flash_controller_0_epcs_control_port),
      .d1_epcs_flash_controller_0_epcs_control_port_end_xfer                                (d1_epcs_flash_controller_0_epcs_control_port_end_xfer),
      .epcs_flash_controller_0_epcs_control_port_address                                    (epcs_flash_controller_0_epcs_control_port_address),
      .epcs_flash_controller_0_epcs_control_port_chipselect                                 (epcs_flash_controller_0_epcs_control_port_chipselect),
      .epcs_flash_controller_0_epcs_control_port_dataavailable                              (epcs_flash_controller_0_epcs_control_port_dataavailable),
      .epcs_flash_controller_0_epcs_control_port_dataavailable_from_sa                      (epcs_flash_controller_0_epcs_control_port_dataavailable_from_sa),
      .epcs_flash_controller_0_epcs_control_port_endofpacket                                (epcs_flash_controller_0_epcs_control_port_endofpacket),
      .epcs_flash_controller_0_epcs_control_port_endofpacket_from_sa                        (epcs_flash_controller_0_epcs_control_port_endofpacket_from_sa),
      .epcs_flash_controller_0_epcs_control_port_irq                                        (epcs_flash_controller_0_epcs_control_port_irq),
      .epcs_flash_controller_0_epcs_control_port_irq_from_sa                                (epcs_flash_controller_0_epcs_control_port_irq_from_sa),
      .epcs_flash_controller_0_epcs_control_port_read_n                                     (epcs_flash_controller_0_epcs_control_port_read_n),
      .epcs_flash_controller_0_epcs_control_port_readdata                                   (epcs_flash_controller_0_epcs_control_port_readdata),
      .epcs_flash_controller_0_epcs_control_port_readdata_from_sa                           (epcs_flash_controller_0_epcs_control_port_readdata_from_sa),
      .epcs_flash_controller_0_epcs_control_port_readyfordata                               (epcs_flash_controller_0_epcs_control_port_readyfordata),
      .epcs_flash_controller_0_epcs_control_port_readyfordata_from_sa                       (epcs_flash_controller_0_epcs_control_port_readyfordata_from_sa),
      .epcs_flash_controller_0_epcs_control_port_reset_n                                    (epcs_flash_controller_0_epcs_control_port_reset_n),
      .epcs_flash_controller_0_epcs_control_port_write_n                                    (epcs_flash_controller_0_epcs_control_port_write_n),
      .epcs_flash_controller_0_epcs_control_port_writedata                                  (epcs_flash_controller_0_epcs_control_port_writedata),
      .reset_n                                                                              (clk_0_reset_n)
    );

  epcs_flash_controller_0 the_epcs_flash_controller_0
    (
      .address       (epcs_flash_controller_0_epcs_control_port_address),
      .chipselect    (epcs_flash_controller_0_epcs_control_port_chipselect),
      .clk           (clk_0),
      .dataavailable (epcs_flash_controller_0_epcs_control_port_dataavailable),
      .endofpacket   (epcs_flash_controller_0_epcs_control_port_endofpacket),
      .irq           (epcs_flash_controller_0_epcs_control_port_irq),
      .read_n        (epcs_flash_controller_0_epcs_control_port_read_n),
      .readdata      (epcs_flash_controller_0_epcs_control_port_readdata),
      .readyfordata  (epcs_flash_controller_0_epcs_control_port_readyfordata),
      .reset_n       (epcs_flash_controller_0_epcs_control_port_reset_n),
      .write_n       (epcs_flash_controller_0_epcs_control_port_write_n),
      .writedata     (epcs_flash_controller_0_epcs_control_port_writedata)
    );

  sdram_0_s1_arbitrator the_sdram_0_s1
    (
      .clk                                                                (clk_0),
      .cpu_0_data_master_address_to_slave                                 (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_byteenable                                       (cpu_0_data_master_byteenable),
      .cpu_0_data_master_byteenable_sdram_0_s1                            (cpu_0_data_master_byteenable_sdram_0_s1),
      .cpu_0_data_master_dbs_address                                      (cpu_0_data_master_dbs_address),
      .cpu_0_data_master_dbs_write_16                                     (cpu_0_data_master_dbs_write_16),
      .cpu_0_data_master_granted_sdram_0_s1                               (cpu_0_data_master_granted_sdram_0_s1),
      .cpu_0_data_master_latency_counter                                  (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_sdram_0_s1                     (cpu_0_data_master_qualified_request_sdram_0_s1),
      .cpu_0_data_master_read                                             (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_sdram_0_s1                       (cpu_0_data_master_read_data_valid_sdram_0_s1),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register        (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_requests_sdram_0_s1                              (cpu_0_data_master_requests_sdram_0_s1),
      .cpu_0_data_master_write                                            (cpu_0_data_master_write),
      .cpu_0_instruction_master_address_to_slave                          (cpu_0_instruction_master_address_to_slave),
      .cpu_0_instruction_master_dbs_address                               (cpu_0_instruction_master_dbs_address),
      .cpu_0_instruction_master_granted_sdram_0_s1                        (cpu_0_instruction_master_granted_sdram_0_s1),
      .cpu_0_instruction_master_latency_counter                           (cpu_0_instruction_master_latency_counter),
      .cpu_0_instruction_master_qualified_request_sdram_0_s1              (cpu_0_instruction_master_qualified_request_sdram_0_s1),
      .cpu_0_instruction_master_read                                      (cpu_0_instruction_master_read),
      .cpu_0_instruction_master_read_data_valid_sdram_0_s1                (cpu_0_instruction_master_read_data_valid_sdram_0_s1),
      .cpu_0_instruction_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_instruction_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_instruction_master_requests_sdram_0_s1                       (cpu_0_instruction_master_requests_sdram_0_s1),
      .d1_sdram_0_s1_end_xfer                                             (d1_sdram_0_s1_end_xfer),
      .reset_n                                                            (clk_0_reset_n),
      .sdram_0_s1_address                                                 (sdram_0_s1_address),
      .sdram_0_s1_byteenable_n                                            (sdram_0_s1_byteenable_n),
      .sdram_0_s1_chipselect                                              (sdram_0_s1_chipselect),
      .sdram_0_s1_read_n                                                  (sdram_0_s1_read_n),
      .sdram_0_s1_readdata                                                (sdram_0_s1_readdata),
      .sdram_0_s1_readdata_from_sa                                        (sdram_0_s1_readdata_from_sa),
      .sdram_0_s1_readdatavalid                                           (sdram_0_s1_readdatavalid),
      .sdram_0_s1_reset_n                                                 (sdram_0_s1_reset_n),
      .sdram_0_s1_waitrequest                                             (sdram_0_s1_waitrequest),
      .sdram_0_s1_waitrequest_from_sa                                     (sdram_0_s1_waitrequest_from_sa),
      .sdram_0_s1_write_n                                                 (sdram_0_s1_write_n),
      .sdram_0_s1_writedata                                               (sdram_0_s1_writedata)
    );

  sdram_0 the_sdram_0
    (
      .az_addr        (sdram_0_s1_address),
      .az_be_n        (sdram_0_s1_byteenable_n),
      .az_cs          (sdram_0_s1_chipselect),
      .az_data        (sdram_0_s1_writedata),
      .az_rd_n        (sdram_0_s1_read_n),
      .az_wr_n        (sdram_0_s1_write_n),
      .clk            (clk_0),
      .reset_n        (sdram_0_s1_reset_n),
      .za_data        (sdram_0_s1_readdata),
      .za_valid       (sdram_0_s1_readdatavalid),
      .za_waitrequest (sdram_0_s1_waitrequest),
      .zs_addr        (zs_addr_from_the_sdram_0),
      .zs_ba          (zs_ba_from_the_sdram_0),
      .zs_cas_n       (zs_cas_n_from_the_sdram_0),
      .zs_cke         (zs_cke_from_the_sdram_0),
      .zs_cs_n        (zs_cs_n_from_the_sdram_0),
      .zs_dq          (zs_dq_to_and_from_the_sdram_0),
      .zs_dqm         (zs_dqm_from_the_sdram_0),
      .zs_ras_n       (zs_ras_n_from_the_sdram_0),
      .zs_we_n        (zs_we_n_from_the_sdram_0)
    );

  sysid_0_control_slave_arbitrator the_sysid_0_control_slave
    (
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_sysid_0_control_slave             (cpu_0_data_master_granted_sysid_0_control_slave),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_sysid_0_control_slave   (cpu_0_data_master_qualified_request_sysid_0_control_slave),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_read_data_valid_sysid_0_control_slave     (cpu_0_data_master_read_data_valid_sysid_0_control_slave),
      .cpu_0_data_master_requests_sysid_0_control_slave            (cpu_0_data_master_requests_sysid_0_control_slave),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .d1_sysid_0_control_slave_end_xfer                           (d1_sysid_0_control_slave_end_xfer),
      .reset_n                                                     (clk_0_reset_n),
      .sysid_0_control_slave_address                               (sysid_0_control_slave_address),
      .sysid_0_control_slave_readdata                              (sysid_0_control_slave_readdata),
      .sysid_0_control_slave_readdata_from_sa                      (sysid_0_control_slave_readdata_from_sa),
      .sysid_0_control_slave_reset_n                               (sysid_0_control_slave_reset_n)
    );

  sysid_0 the_sysid_0
    (
      .address  (sysid_0_control_slave_address),
      .clock    (sysid_0_control_slave_clock),
      .readdata (sysid_0_control_slave_readdata),
      .reset_n  (sysid_0_control_slave_reset_n)
    );

  timer_0_s1_arbitrator the_timer_0_s1
    (
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_timer_0_s1                        (cpu_0_data_master_granted_timer_0_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_timer_0_s1              (cpu_0_data_master_qualified_request_timer_0_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_read_data_valid_timer_0_s1                (cpu_0_data_master_read_data_valid_timer_0_s1),
      .cpu_0_data_master_requests_timer_0_s1                       (cpu_0_data_master_requests_timer_0_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_timer_0_s1_end_xfer                                      (d1_timer_0_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n),
      .timer_0_s1_address                                          (timer_0_s1_address),
      .timer_0_s1_chipselect                                       (timer_0_s1_chipselect),
      .timer_0_s1_irq                                              (timer_0_s1_irq),
      .timer_0_s1_irq_from_sa                                      (timer_0_s1_irq_from_sa),
      .timer_0_s1_readdata                                         (timer_0_s1_readdata),
      .timer_0_s1_readdata_from_sa                                 (timer_0_s1_readdata_from_sa),
      .timer_0_s1_reset_n                                          (timer_0_s1_reset_n),
      .timer_0_s1_write_n                                          (timer_0_s1_write_n),
      .timer_0_s1_writedata                                        (timer_0_s1_writedata)
    );

  timer_0 the_timer_0
    (
      .address    (timer_0_s1_address),
      .chipselect (timer_0_s1_chipselect),
      .clk        (clk_0),
      .irq        (timer_0_s1_irq),
      .readdata   (timer_0_s1_readdata),
      .reset_n    (timer_0_s1_reset_n),
      .write_n    (timer_0_s1_write_n),
      .writedata  (timer_0_s1_writedata)
    );

  timer_1_s1_arbitrator the_timer_1_s1
    (
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_timer_1_s1                        (cpu_0_data_master_granted_timer_1_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_timer_1_s1              (cpu_0_data_master_qualified_request_timer_1_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_read_data_valid_timer_1_s1                (cpu_0_data_master_read_data_valid_timer_1_s1),
      .cpu_0_data_master_requests_timer_1_s1                       (cpu_0_data_master_requests_timer_1_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_timer_1_s1_end_xfer                                      (d1_timer_1_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n),
      .timer_1_s1_address                                          (timer_1_s1_address),
      .timer_1_s1_chipselect                                       (timer_1_s1_chipselect),
      .timer_1_s1_irq                                              (timer_1_s1_irq),
      .timer_1_s1_irq_from_sa                                      (timer_1_s1_irq_from_sa),
      .timer_1_s1_readdata                                         (timer_1_s1_readdata),
      .timer_1_s1_readdata_from_sa                                 (timer_1_s1_readdata_from_sa),
      .timer_1_s1_reset_n                                          (timer_1_s1_reset_n),
      .timer_1_s1_write_n                                          (timer_1_s1_write_n),
      .timer_1_s1_writedata                                        (timer_1_s1_writedata)
    );

  timer_1 the_timer_1
    (
      .address    (timer_1_s1_address),
      .chipselect (timer_1_s1_chipselect),
      .clk        (clk_0),
      .irq        (timer_1_s1_irq),
      .readdata   (timer_1_s1_readdata),
      .reset_n    (timer_1_s1_reset_n),
      .write_n    (timer_1_s1_write_n),
      .writedata  (timer_1_s1_writedata)
    );

  uart_0_s1_arbitrator the_uart_0_s1
    (
      .clk                                                         (clk_0),
      .cpu_0_data_master_address_to_slave                          (cpu_0_data_master_address_to_slave),
      .cpu_0_data_master_granted_uart_0_s1                         (cpu_0_data_master_granted_uart_0_s1),
      .cpu_0_data_master_latency_counter                           (cpu_0_data_master_latency_counter),
      .cpu_0_data_master_qualified_request_uart_0_s1               (cpu_0_data_master_qualified_request_uart_0_s1),
      .cpu_0_data_master_read                                      (cpu_0_data_master_read),
      .cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register (cpu_0_data_master_read_data_valid_sdram_0_s1_shift_register),
      .cpu_0_data_master_read_data_valid_uart_0_s1                 (cpu_0_data_master_read_data_valid_uart_0_s1),
      .cpu_0_data_master_requests_uart_0_s1                        (cpu_0_data_master_requests_uart_0_s1),
      .cpu_0_data_master_write                                     (cpu_0_data_master_write),
      .cpu_0_data_master_writedata                                 (cpu_0_data_master_writedata),
      .d1_uart_0_s1_end_xfer                                       (d1_uart_0_s1_end_xfer),
      .reset_n                                                     (clk_0_reset_n),
      .uart_0_s1_address                                           (uart_0_s1_address),
      .uart_0_s1_begintransfer                                     (uart_0_s1_begintransfer),
      .uart_0_s1_chipselect                                        (uart_0_s1_chipselect),
      .uart_0_s1_dataavailable                                     (uart_0_s1_dataavailable),
      .uart_0_s1_dataavailable_from_sa                             (uart_0_s1_dataavailable_from_sa),
      .uart_0_s1_irq                                               (uart_0_s1_irq),
      .uart_0_s1_irq_from_sa                                       (uart_0_s1_irq_from_sa),
      .uart_0_s1_read_n                                            (uart_0_s1_read_n),
      .uart_0_s1_readdata                                          (uart_0_s1_readdata),
      .uart_0_s1_readdata_from_sa                                  (uart_0_s1_readdata_from_sa),
      .uart_0_s1_readyfordata                                      (uart_0_s1_readyfordata),
      .uart_0_s1_readyfordata_from_sa                              (uart_0_s1_readyfordata_from_sa),
      .uart_0_s1_reset_n                                           (uart_0_s1_reset_n),
      .uart_0_s1_write_n                                           (uart_0_s1_write_n),
      .uart_0_s1_writedata                                         (uart_0_s1_writedata)
    );

  uart_0 the_uart_0
    (
      .address       (uart_0_s1_address),
      .begintransfer (uart_0_s1_begintransfer),
      .chipselect    (uart_0_s1_chipselect),
      .clk           (clk_0),
      .dataavailable (uart_0_s1_dataavailable),
      .irq           (uart_0_s1_irq),
      .read_n        (uart_0_s1_read_n),
      .readdata      (uart_0_s1_readdata),
      .readyfordata  (uart_0_s1_readyfordata),
      .reset_n       (uart_0_s1_reset_n),
      .rxd           (rxd_to_the_uart_0),
      .txd           (txd_from_the_uart_0),
      .write_n       (uart_0_s1_write_n),
      .writedata     (uart_0_s1_writedata)
    );

  //reset is asserted asynchronously and deasserted synchronously
  RC_2C8V3_Nios_CPU_reset_clk_0_domain_synch_module RC_2C8V3_Nios_CPU_reset_clk_0_domain_synch
    (
      .clk      (clk_0),
      .data_in  (1'b1),
      .data_out (clk_0_reset_n),
      .reset_n  (reset_n_sources)
    );

  //reset sources mux, which is an e_mux
  assign reset_n_sources = ~(~reset_n |
    0 |
    cpu_0_jtag_debug_module_resetrequest_from_sa |
    cpu_0_jtag_debug_module_resetrequest_from_sa);

  //sysid_0_control_slave_clock of type clock does not connect to anything so wire it to default (0)
  assign sysid_0_control_slave_clock = 0;


endmodule


//synthesis translate_off



// <ALTERA_NOTE> CODE INSERTED BETWEEN HERE

// AND HERE WILL BE PRESERVED </ALTERA_NOTE>


// If user logic components use Altsync_Ram with convert_hex2ver.dll,
// set USE_convert_hex2ver in the user comments section above

// `ifdef USE_convert_hex2ver
// `else
// `define NO_PLI 1
// `endif

`include "c:/altera/12.0/quartus/eda/sim_lib/altera_mf.v"
`include "c:/altera/12.0/quartus/eda/sim_lib/220model.v"
`include "c:/altera/12.0/quartus/eda/sim_lib/sgate.v"
`include "ETH_WOL_I.v"
`include "timer_0.v"
`include "ETH_SCK_O.v"
`include "IR_DATA.v"
`include "cpu_0_test_bench.v"
`include "cpu_0_mult_cell.v"
`include "cpu_0_oci_test_bench.v"
`include "cpu_0_jtag_debug_module_tck.v"
`include "cpu_0_jtag_debug_module_sysclk.v"
`include "cpu_0_jtag_debug_module_wrapper.v"
`include "cpu_0.v"
`include "TUBE_EN.v"
`include "SDA.v"
`include "USB_SDO_I.v"
`include "PS2_DATA_REC.v"
`include "sysid_0.v"
`include "uart_0.v"
`include "BUZZER_DATA.v"
`include "USB_SCS_O.v"
`include "LCD_DATA.v"
`include "SCL.v"
`include "sdram_0.v"
`include "LCD_RS.v"
`include "epcs_flash_controller_0.v"
`include "LCD_CS.v"
`include "SD_CS.v"
`include "ADC_DATA.v"
`include "ETH_CS_O.v"
`include "ETH_RESET_O.v"
`include "SD_DO.v"
`include "LCD_RD.v"
`include "DAC_DATA.v"
`include "USB_INT_I.v"
`include "timer_1.v"
`include "LED_DATA.v"
`include "SD_DI.v"
`include "KEY_FOCUS.v"
`include "USB_SCK_O.v"
`include "ETH_INT_I.v"
`include "ETH_SI_O.v"
`include "ETH_CLKOUT_I.v"
`include "TEMP_DATA.v"
`include "USB_PC_I.v"
`include "LCD_RST.v"
`include "RTC_DATA.v"
`include "UART_RX_DATA.v"
`include "LCD_WR.v"
`include "SD_CLK.v"
`include "ETH_SO_I.v"
`include "USB_SDI_O.v"
`include "USB_RST_O.v"

`timescale 1ns / 1ps

module test_bench 
;


  wire             bidir_port_to_and_from_the_SDA;
  wire             clk;
  reg              clk_0;
  wire             epcs_flash_controller_0_epcs_control_port_dataavailable_from_sa;
  wire             epcs_flash_controller_0_epcs_control_port_endofpacket_from_sa;
  wire             epcs_flash_controller_0_epcs_control_port_readyfordata_from_sa;
  wire    [  7: 0] in_port_to_the_ADC_DATA;
  wire             in_port_to_the_BUZZER_DATA;
  wire    [  7: 0] in_port_to_the_DAC_DATA;
  wire             in_port_to_the_ETH_CLKOUT_I;
  wire    [  7: 0] in_port_to_the_ETH_INT_I;
  wire             in_port_to_the_ETH_SO_I;
  wire             in_port_to_the_ETH_WOL_I;
  wire    [ 31: 0] in_port_to_the_IR_DATA;
  wire    [  3: 0] in_port_to_the_KEY_FOCUS;
  wire    [  5: 0] in_port_to_the_LED_DATA;
  wire    [ 15: 0] in_port_to_the_PS2_DATA_REC;
  wire    [ 23: 0] in_port_to_the_RTC_DATA;
  wire             in_port_to_the_SD_DO;
  wire    [ 15: 0] in_port_to_the_TEMP_DATA;
  wire    [  7: 0] in_port_to_the_UART_RX_DATA;
  wire             in_port_to_the_USB_INT_I;
  wire             in_port_to_the_USB_PC_I;
  wire             in_port_to_the_USB_SDO_I;
  wire             out_port_from_the_ETH_CS_O;
  wire             out_port_from_the_ETH_RESET_O;
  wire             out_port_from_the_ETH_SCK_O;
  wire             out_port_from_the_ETH_SI_O;
  wire             out_port_from_the_LCD_CS;
  wire    [ 15: 0] out_port_from_the_LCD_DATA;
  wire             out_port_from_the_LCD_RD;
  wire             out_port_from_the_LCD_RS;
  wire             out_port_from_the_LCD_RST;
  wire             out_port_from_the_LCD_WR;
  wire             out_port_from_the_SCL;
  wire             out_port_from_the_SD_CLK;
  wire             out_port_from_the_SD_CS;
  wire             out_port_from_the_SD_DI;
  wire    [  3: 0] out_port_from_the_TUBE_EN;
  wire             out_port_from_the_USB_RST_O;
  wire             out_port_from_the_USB_SCK_O;
  wire             out_port_from_the_USB_SCS_O;
  wire             out_port_from_the_USB_SDI_O;
  reg              reset_n;
  wire             rxd_to_the_uart_0;
  wire             sysid_0_control_slave_clock;
  wire             txd_from_the_uart_0;
  wire             uart_0_s1_dataavailable_from_sa;
  wire             uart_0_s1_readyfordata_from_sa;
  wire    [ 12: 0] zs_addr_from_the_sdram_0;
  wire    [  1: 0] zs_ba_from_the_sdram_0;
  wire             zs_cas_n_from_the_sdram_0;
  wire             zs_cke_from_the_sdram_0;
  wire             zs_cs_n_from_the_sdram_0;
  wire    [ 15: 0] zs_dq_to_and_from_the_sdram_0;
  wire    [  1: 0] zs_dqm_from_the_sdram_0;
  wire             zs_ras_n_from_the_sdram_0;
  wire             zs_we_n_from_the_sdram_0;


// <ALTERA_NOTE> CODE INSERTED BETWEEN HERE
//  add your signals and additional architecture here
// AND HERE WILL BE PRESERVED </ALTERA_NOTE>

  //Set us up the Dut
  RC_2C8V3_Nios_CPU DUT
    (
      .bidir_port_to_and_from_the_SDA (bidir_port_to_and_from_the_SDA),
      .clk_0                          (clk_0),
      .in_port_to_the_ADC_DATA        (in_port_to_the_ADC_DATA),
      .in_port_to_the_BUZZER_DATA     (in_port_to_the_BUZZER_DATA),
      .in_port_to_the_DAC_DATA        (in_port_to_the_DAC_DATA),
      .in_port_to_the_ETH_CLKOUT_I    (in_port_to_the_ETH_CLKOUT_I),
      .in_port_to_the_ETH_INT_I       (in_port_to_the_ETH_INT_I),
      .in_port_to_the_ETH_SO_I        (in_port_to_the_ETH_SO_I),
      .in_port_to_the_ETH_WOL_I       (in_port_to_the_ETH_WOL_I),
      .in_port_to_the_IR_DATA         (in_port_to_the_IR_DATA),
      .in_port_to_the_KEY_FOCUS       (in_port_to_the_KEY_FOCUS),
      .in_port_to_the_LED_DATA        (in_port_to_the_LED_DATA),
      .in_port_to_the_PS2_DATA_REC    (in_port_to_the_PS2_DATA_REC),
      .in_port_to_the_RTC_DATA        (in_port_to_the_RTC_DATA),
      .in_port_to_the_SD_DO           (in_port_to_the_SD_DO),
      .in_port_to_the_TEMP_DATA       (in_port_to_the_TEMP_DATA),
      .in_port_to_the_UART_RX_DATA    (in_port_to_the_UART_RX_DATA),
      .in_port_to_the_USB_INT_I       (in_port_to_the_USB_INT_I),
      .in_port_to_the_USB_PC_I        (in_port_to_the_USB_PC_I),
      .in_port_to_the_USB_SDO_I       (in_port_to_the_USB_SDO_I),
      .out_port_from_the_ETH_CS_O     (out_port_from_the_ETH_CS_O),
      .out_port_from_the_ETH_RESET_O  (out_port_from_the_ETH_RESET_O),
      .out_port_from_the_ETH_SCK_O    (out_port_from_the_ETH_SCK_O),
      .out_port_from_the_ETH_SI_O     (out_port_from_the_ETH_SI_O),
      .out_port_from_the_LCD_CS       (out_port_from_the_LCD_CS),
      .out_port_from_the_LCD_DATA     (out_port_from_the_LCD_DATA),
      .out_port_from_the_LCD_RD       (out_port_from_the_LCD_RD),
      .out_port_from_the_LCD_RS       (out_port_from_the_LCD_RS),
      .out_port_from_the_LCD_RST      (out_port_from_the_LCD_RST),
      .out_port_from_the_LCD_WR       (out_port_from_the_LCD_WR),
      .out_port_from_the_SCL          (out_port_from_the_SCL),
      .out_port_from_the_SD_CLK       (out_port_from_the_SD_CLK),
      .out_port_from_the_SD_CS        (out_port_from_the_SD_CS),
      .out_port_from_the_SD_DI        (out_port_from_the_SD_DI),
      .out_port_from_the_TUBE_EN      (out_port_from_the_TUBE_EN),
      .out_port_from_the_USB_RST_O    (out_port_from_the_USB_RST_O),
      .out_port_from_the_USB_SCK_O    (out_port_from_the_USB_SCK_O),
      .out_port_from_the_USB_SCS_O    (out_port_from_the_USB_SCS_O),
      .out_port_from_the_USB_SDI_O    (out_port_from_the_USB_SDI_O),
      .reset_n                        (reset_n),
      .rxd_to_the_uart_0              (rxd_to_the_uart_0),
      .txd_from_the_uart_0            (txd_from_the_uart_0),
      .zs_addr_from_the_sdram_0       (zs_addr_from_the_sdram_0),
      .zs_ba_from_the_sdram_0         (zs_ba_from_the_sdram_0),
      .zs_cas_n_from_the_sdram_0      (zs_cas_n_from_the_sdram_0),
      .zs_cke_from_the_sdram_0        (zs_cke_from_the_sdram_0),
      .zs_cs_n_from_the_sdram_0       (zs_cs_n_from_the_sdram_0),
      .zs_dq_to_and_from_the_sdram_0  (zs_dq_to_and_from_the_sdram_0),
      .zs_dqm_from_the_sdram_0        (zs_dqm_from_the_sdram_0),
      .zs_ras_n_from_the_sdram_0      (zs_ras_n_from_the_sdram_0),
      .zs_we_n_from_the_sdram_0       (zs_we_n_from_the_sdram_0)
    );

  initial
    clk_0 = 1'b0;
  always
    #10 clk_0 <= ~clk_0;
  
  initial 
    begin
      reset_n <= 0;
      #200 reset_n <= 1;
    end

endmodule


//synthesis translate_on
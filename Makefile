TOPNAME = Top
SBT = sbt
MILL = mill

VERILATOR = verilator

VERILATOR_CFLAGS += --cc --exe --build --trace \
					-O3 --x-assign fast --x-initial fast --noassert

VERILATOR_INPUT = generated/Top.sv sim/main.cc sim/sim.cc


OBJ_DIR = ./obj_dir
BIN = $(OBJ_DIR)/V$(TOPNAME)


#generate verilog file.
verilog:
	$(SBT) "runMain led.TopMain"

#simulation
sim:
	@rm -rf logs 
	@rm -rf $(OBJ_DIR)
	@echo "--------VERILATE & COMPILE(BUILD)--------"
	@$(VERILATOR) $(VERILATOR_CFLAGS) $(VERILATOR_INPUT) 
	@echo "--------DONE------------"
	$(BIN)


wave: logs/waveform.vcd 
	@gtkwave logs/waveform.vcd

clean:
	@rm -rf $(OBJ_DIR) generated/ logs/

.PHONY: sim clean verilog


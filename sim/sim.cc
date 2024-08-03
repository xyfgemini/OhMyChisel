#include <memory> 
#include <cstdio>
#include <verilated.h> 
#include "VTop.h"  //generated from Verilating "Top.sv"
#include <verilated_vcd_c.h>

#define MAX_SIM_TIME 200

const std::unique_ptr<VerilatedContext> contextp{new VerilatedContext}; //hold simulation time

const std::unique_ptr<VTop> top{new VTop{contextp.get(), "TOP"}}; 

static VerilatedVcdC *tfp = new VerilatedVcdC;

void sim_init(int argc,char *argv[]){
    Verilated::commandArgs(argc,argv);
    Verilated::mkdir("logs");  //trace to put under it
    contextp->traceEverOn(true); //compute traced signals
    contextp->debug(0);

    top->reset = 1;
    top->clock = 0;
    top->eval();

    VL_PRINTF("Enabling waves...\n");
    
    top->trace(tfp,99);
    tfp->open("logs/waveform.vcd");
    tfp->dump(0);
}

void sim_exit(){
    top->final();
    tfp->close();
    delete tfp;
    printf("simulation completed!\n");
}

void single_cycle()
{
    contextp->timeInc(1);
    top->clock = 0;
    top->eval();  //update
    tfp->dump(contextp->time()); //dump wave
    
    contextp->timeInc(1);
    top->clock = 1;
    top->eval();
    tfp->dump(contextp->time());
}


//拉高复位值10个周期
void reset_n(int n){
    top->reset = 1;
    while(n-- > 0) single_cycle();
    top->reset = 0;  
}


void execute_sim(){
    while(!(contextp->time() == MAX_SIM_TIME)){
        single_cycle();
    }
}

void sim_main(int argc , char *argv[])
{
    sim_init(argc,argv);

    reset_n(1);

    execute_sim();

    sim_exit();
}




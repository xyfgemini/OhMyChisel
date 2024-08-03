#ifndef __SIM_H__
#define __SIM_H__

void sim_init(int argc,char *argv[]);
void sim_exit();
void reset_n(int n);
void single_cycle();
void sim_main(int argc,char *argv[]);

#endif
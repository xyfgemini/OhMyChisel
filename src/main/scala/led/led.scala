package led

import chisel3._
import chisel3.util._

class LedIO extends Bundle {
    val y = Output(UInt(16.W))
}

class Top extends Module {
    val io = IO(new LedIO())

    val MAX_COUNT = 500000.U

    val count = RegInit(0.U(32.W))

    count := count + 1.U

    when(count === MAX_COUNT){
        count := 0.U
    }
    
    io.y := count
}

object TopMain extends App{
    println("generating the verilog file!")
    emitVerilog(new Top(),Array("--target-dir","generated"))
}
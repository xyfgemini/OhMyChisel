import chisel3._
import chisel3.testers._
import org.scalatest.flatspec.AnyFlatSpec

class DeviceUnderTest extends Module {
    val io = IO(new Bundle {
        val a = Input(UInt(2.W))
        val b = Input(UInt(2.W))
        val out = Output(UInt(2.W))
    })
    
    io.out := io.a & io.b
}

class SimpleTest extends AnyFlatSpec with ChiselScalatestTester {
    "DUT" should "pass" in {
        test(new DeviceUnderTest) { dut =>
            dut.io.a.poke(0.U)
            dut.io.b.poke(1.U)
            dut.clock.step()
            dut.io.out.expect(0.U)
            dut.io.a.poke(3.U)
            dut.io.b.poke(2.U)
            dut.clock.step()
            dut.io.out.expect(2.U)
        }
    }
}

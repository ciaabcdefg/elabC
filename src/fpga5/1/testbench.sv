module tb;
  logic clk, load, clear;
  logic [70] out1, out2, out3, regOut;
  logic [10] func;

  logic sel1, sel2;
  mux mux1(8'b10000000, 8'b00000001, sel1, out1);
  mux mux2(out1, regOut, sel2, out2);
  shifter shift(func, out2, out3);
  register regi(clk, load, clear, out3, regOut);
  
  initial begin
    sel1 = 0;
    sel2 = 0;
    func = 0;
    
    clear = 1;
    load = 1;
    
    #5 sel1 = 1;
    #5 clear = 0; func = 1;
   	#5 sel2 = 1;
    #10 func = 2'b11;
    
   	#5 clear = 1;
    #1 clear = 0;
    
    #5 sel1 = 0;
    #5 sel2 = 0;
    #5 sel2 = 1;
    #5 func = 0;
    
    #10 $finish;
  end

  initial begin
    clk = 0;
    forever #2 clk = ~clk;
  end

  initial begin
    $dumpfile(dump.vcd);
    $dumpvars(1);
  end
  
endmodule
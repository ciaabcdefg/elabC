module tb;
  logic clk, load, clear;
  logic [7:0] out1, out2, out3, LED;
  logic [1:0] func;

  logic sel1, sel2;
  mux mux1(8'b10000000, 8'b00000001, sel1, out1);
  mux mux2(out1, LED, sel2, out2);
  shifter shift(func, out2, out3);
  register regi(clk, load, clear, out3, LED);
  
  initial begin
    sel1 = 0;
    sel2 = 0;
    func = 0;
    
    clear = 1;
    load = 1;
   	
    #2 clear = 0;
   	#2 sel2 = 1; func = 2'b11;
    
    #30 $finish;
  end

  initial begin
    clk = 0;
    forever #1 clk = ~clk;
  end

  initial begin
    $dumpfile("dump.vcd");
    $dumpvars(1);
  end
  
endmodule
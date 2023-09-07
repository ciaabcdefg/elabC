module tb;
  
  logic clk, reset, forward;
  logic [2:0] n;
  
  //ffCounter counter(clk, reset, n);
  ffCounter_posedge counter_posedge(clk, reset, n, forward);
  
  always begin
    #5 clk = ~clk;
  end
  
  initial begin
    $dumpfile("dump.vcd"); $dumpvars;
    $monitor($time,,"ns: %b", n);
  end
  
  initial begin

    clk <= 0;
    reset <= 1;
    #5 reset <= 0;
    
    #180 reset <= 1;
    #5 $finish; 
  end
  
endmodule
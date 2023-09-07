module ffCounter(input logic clk, reset, output logic [2:0] n);
  
  always_ff @(negedge clk, negedge reset) begin
    
    if (reset) begin
      n <= 0;
    end
    else begin
      n <= n + 1;
    end
      
  end
    
endmodule

module ffCounter_posedge(input logic clk, reset, output logic [2:0] n, output logic forward);
  
  always_ff @(posedge clk, posedge reset) begin
    if (reset) begin
      n <= 0;
      forward <= 1;
    end
    else begin
      
      if (forward == 1)
        n <= n + 1;
      else
        n <= n - 1;
      
      if (n == 3'd7) begin
        forward <= 0;
      	n <= 3'd6;
      end
      else if (n == 3'd0) begin
        forward <= 1;
      	n <= 3'd1;
      end
    end
  end
    
endmodule

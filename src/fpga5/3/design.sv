module mux(input logic [7:0] a, input logic [7:0] b, input logic sel, output logic [7:0] out);
  always_comb begin
    if (!sel) begin
      out = a;
    end
    else begin
      out = b;
    end
  end
endmodule

module register(input logic clk, load, clear, input logic [7:0] data, output logic [7:0] out);
  always_ff @(posedge clk) begin
    if (clear) begin
      out <= 0;
    end
    else if (load && !clear) begin
      out <= data;
    end
  end
endmodule

module setFunc(input logic [1:0] cycle, output logic [1:0] func);
  always_comb begin
    if (cycle == 2'b00 || cycle == 2'b01) begin
      func = 2'b11;
    end
    else if (cycle == 2'b10 || cycle == 2'b11) begin
      func = 2'b01;
    end
    else begin
      func = 0;
    end
  end
endmodule

module shifter(input logic [1:0] func, cycle, input logic [7:0] data, output logic [7:0] out, output logic [1:0] cycleOut);
  always_comb begin
    if (func == 0) begin
      out = data;
      cycleOut = cycle;
    end
    else if (func == 1) begin
      if (data[7] == 1) begin
        if (cycle == 2'b11) begin
          out = 8'b10000000;
        end
        else begin
          out = 8'b00000001;
        end
        
        cycleOut = cycle + 1;
      end
      else begin
      	out = data << 1;
        cycleOut = cycle;
      end
    end
    else begin
      if (data[0] == 1) begin
        if (cycle == 2'b01) begin
          out = 8'b00000001;
        end
        else begin
          out = 8'b10000000;
        end
        
        cycleOut = cycle + 1;
      end
      else begin
        out = data >> 1;
        cycleOut = cycle;
      end
    end
  end
endmodule
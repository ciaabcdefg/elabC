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

module shifter(input logic [1:0] func, input logic [7:0] data, output logic [7:0] out);
  always_comb begin
    if (func == 0) begin
      out = data;
    end
    else if (func == 1) begin
      out = data << 1;
    end
    else begin
      out = data >> 1;
    end
  end
endmodule
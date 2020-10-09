module circuit_5 (

input [63:0] a,
input [63:0] b,
input [63:0] c,
input [63:0] d,
input [63:0] zero,

output [63:0] z
);

wire [63:0] e;
wire [63:0] f;
wire [63:0] g;
wire [63:0] zwire;
wire gEQz;  

// e = a / b
DIV #(64) u_div(a,b,e);

// f = c / d
DIV #(64) u_div2(c,d,f);

// g = a % b 
MOD #(64) u_mod(a,b,g);

// gEQz = (g == zero)
COMP #(64) u_comp(
	.a(g),
	.b(zero),
	.gt(),
	.lt(),
	.eq(gEQz)
	);

// zwire = gEQz ? e : f 
MUX2x1 #(64) u_mux(e,f,gEQz,zwire);

// z = zwire
assign z = zwire;

endmodule

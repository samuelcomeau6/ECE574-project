module circuit_6 (

input [63:0] a,
input [63:0] b,
input [63:0] c,
input [63:0] zero,

output [63:0] z
);

wire [63:0] e;
wire [63:0] f;
wire [63:0] g;
wire [63:0] zwire;
wire gEQz;  

// e = a - 1
DEC #(64) u_sub(a,e);

// f = c + 1
INC #(64) u_add(c,f);

// g = a % c
MOD #(64) u_mod(a,c,g);

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

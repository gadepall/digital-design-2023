module helloworldfpga(output reg LCD_RS,output reg LCD_E,output reg[7:4] DATA);

wire clk;
qlal4s3b_cell_macro u_qlal4s3b_cell_macro (
	.Sys_Clk0 (clk),
);//20Mhz clock
integer i = 1;
reg [25:0] count=0;
reg [3:0] Datas [1:41];
	//code for sum of two numbers
integer a1=2;//20
integer a0=0;
integer b1=4;//40
integer b0=0;
integer sum0,sum1,b,a00,a01,b10,b11;
assign sum0=a0+b0;
assign sum1=a1+b1;
initial begin
	if (sum0>=10)begin
		a00=4;
		a01=sum0-10;end
	else begin
		a00=3;
		a01=sum0;
		end
	if (sum0>=10) begin
		b=sum1+1;
		if (b>=10)begin
			b10=4;
			b11=10-b;end
		else begin
			b10=3;
			b11=b;end
		end	
	else begin
		b=sum1;
		if (b>=10)begin
			b10=4;                                 b11=10-b;end
		else begin
			b10=3;                                 b11=b;end
end
	//end of code for sum of two numbers
end
always @(posedge clk) begin
Datas[1]   =  4'h3;   	//-- initializing controller--
Datas[2]   =  4'h3;   
Datas[3]   =  4'h3;   	//-- set to 4-bit input mode --
Datas[4]   =  4'h2;   	
Datas[5]   =  4'h2;   	//--2 line, 5x7 matrix  --
Datas[6]   =  4'h8;   	
Datas[7]   =  4'h0;   	//--turn cursor off (0x0E to enable) --
Datas[8]   =  4'hC;   	
Datas[9]   =  4'h0;   	//-- cursor direction = right --
Datas[10]  =  4'h6;   	
Datas[11]  =  4'h0;   	//--  start with clear display  --
Datas[12]  =  4'h1;
Datas[13]  =  4'h8; //starting from line 1
Datas[14]  =  4'h0;
Datas[15]  =  1'b1;
Datas[16]  =  4'h5;//T=0X54
Datas[17]  =  4'h4;   
Datas[18]  =  4'h4;//H==0X48
Datas[19]  =  4'h8;
Datas[20]  =  4'h4;//E=0X45;       
Datas[21]  =  4'h5;
Datas[22]  =  4'h2;//SPACE=0X20
Datas[23]  =  4'h0;
Datas[24]  =  4'h5;//S=0X53
Datas[25]  =  4'h3;
Datas[26]  =  4'h5;//U=0X55
Datas[27]  =  4'h5;
Datas[28]  =  4'h4;//M=0X4D
Datas[29]  =  4'hD;
Datas[30]  =  4'h2;//SPACE=0X20
Datas[31]  =  4'h0;
Datas[32]  =  4'h4;//I=0X49
Datas[33]  =  4'h9;
Datas[34]  =  4'h5;//S=0X53
Datas[35]  =  4'h3;
	Datas[36]  =  4'h2;//space=0x20
Datas[37]  =  4'h0;
Datas[38]  =b10;
Datas[39]  =b11;
Datas[40]  =a00;
Datas[41]  =a10;
end
always @(posedge clk) begin
if (i<=14)begin
	LCD_RS<=1'b0;
	DATA=Datas[i];
	LCD_E<=1'b1;
	if (count==800)begin //waiting 40us
   		LCD_E<=1'b0;
   		count<=0;
   		i <= i + 1;
   		end
	else
   		count<=count+1;

	end
if (i==15) begin
	if (count==60000)begin//waiting 3ms
     		count<=0;
     		i<=i+1;
     		end
	else
     		count<=count+1;
	end
if (i>15 & i<=41) begin 
	LCD_RS<=1'b1;
	DATA=Datas[i];
        LCD_E<=1'b1;
	if (count==800)begin //waiting 40us
	    LCD_E<=1'b0;
	    count<=0;
            i <= i + 1;
    	    end
        else
		count<=count+1;       
        end
if (i>41) 
	i<=13;
	
end
endmodule

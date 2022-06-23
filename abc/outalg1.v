// Benchmark "top" written by ABC on Fri Jun 24 02:30:33 2022

module top ( 
    \in1[0] , \in1[1] , \in1[2] , \in1[3] , \in2[0] , \in2[1] , \in2[2] ,
    \in2[3] , \in3[0] , \in3[1] , \in3[2] , \in3[3] ,
    \out1[0] , \out1[1] , \out1[2] , \out1[3]   );
  input  \in1[0] , \in1[1] , \in1[2] , \in1[3] , \in2[0] , \in2[1] ,
    \in2[2] , \in2[3] , \in3[0] , \in3[1] , \in3[2] , \in3[3] ;
  output \out1[0] , \out1[1] , \out1[2] , \out1[3] ;
  wire new_n17_, new_n18_, new_n19_, new_n20_, new_n21_, new_n23_, new_n24_,
    new_n25_, new_n26_, new_n27_, new_n28_, new_n29_, new_n30_, new_n31_,
    new_n33_, new_n34_, new_n35_, new_n36_, new_n37_, new_n38_, new_n39_,
    new_n40_, new_n41_, new_n42_, new_n43_, new_n44_, new_n46_, new_n47_,
    new_n48_, new_n49_, new_n50_, new_n51_, new_n52_, new_n53_, new_n54_,
    new_n55_, new_n56_, new_n57_, new_n58_;
  assign new_n17_ = \in1[0]  & \in2[0] ;
  assign new_n18_ = ~\in1[0]  & ~\in2[0] ;
  assign new_n19_ = ~new_n17_ & ~new_n18_;
  assign new_n20_ = \in3[0]  & new_n19_;
  assign new_n21_ = ~\in3[0]  & ~new_n19_;
  assign \out1[0]  = ~new_n20_ & ~new_n21_;
  assign new_n23_ = \in1[1]  & \in3[1] ;
  assign new_n24_ = ~\in1[1]  & ~\in3[1] ;
  assign new_n25_ = ~new_n23_ & ~new_n24_;
  assign new_n26_ = \in2[1]  & new_n25_;
  assign new_n27_ = ~\in2[1]  & ~new_n25_;
  assign new_n28_ = ~new_n26_ & ~new_n27_;
  assign new_n29_ = ~new_n17_ & ~new_n20_;
  assign new_n30_ = new_n28_ & new_n29_;
  assign new_n31_ = ~new_n28_ & ~new_n29_;
  assign \out1[1]  = new_n30_ | new_n31_;
  assign new_n33_ = \in2[2]  & \in3[2] ;
  assign new_n34_ = ~\in2[2]  & ~\in3[2] ;
  assign new_n35_ = ~new_n33_ & ~new_n34_;
  assign new_n36_ = \in1[2]  & new_n35_;
  assign new_n37_ = ~\in1[2]  & ~new_n35_;
  assign new_n38_ = ~new_n36_ & ~new_n37_;
  assign new_n39_ = new_n23_ & new_n38_;
  assign new_n40_ = ~new_n23_ & ~new_n38_;
  assign new_n41_ = ~new_n39_ & ~new_n40_;
  assign new_n42_ = ~new_n27_ & ~new_n30_;
  assign new_n43_ = new_n41_ & ~new_n42_;
  assign new_n44_ = ~new_n41_ & new_n42_;
  assign \out1[2]  = new_n43_ | new_n44_;
  assign new_n46_ = ~new_n40_ & ~new_n43_;
  assign new_n47_ = ~new_n33_ & ~new_n36_;
  assign new_n48_ = \in1[3]  & \in2[3] ;
  assign new_n49_ = ~\in1[3]  & ~\in2[3] ;
  assign new_n50_ = ~new_n48_ & ~new_n49_;
  assign new_n51_ = \in3[3]  & ~new_n50_;
  assign new_n52_ = ~\in3[3]  & new_n50_;
  assign new_n53_ = ~new_n51_ & ~new_n52_;
  assign new_n54_ = ~new_n47_ & ~new_n53_;
  assign new_n55_ = new_n47_ & new_n53_;
  assign new_n56_ = ~new_n54_ & ~new_n55_;
  assign new_n57_ = ~new_n46_ & ~new_n56_;
  assign new_n58_ = new_n46_ & new_n56_;
  assign \out1[3]  = ~new_n57_ & ~new_n58_;
endmodule



/*
 * tb.cpp
 *
 *  Created on: Feb 22, 2016
 *      Author: lexy
 */

#include <systemc-ams>
#include "comparator.hpp"
#include "sin_src.hpp"
#include "constant_voltage_tdf.hpp"
#include "non_blocking.cpp"

int sc_main (int argc, char* argv[])

{
     
    
    uint32_t i;
    sca_tdf::sca_signal<double> vp;
    sca_tdf::sca_signal<double> vn;
    sc_core::sc_signal<bool> z;
    sc_core::sc_time time_step(10.0, sc_core::SC_NS);

    comparator comp0("comp0");
    comp0.vplus(vp);
    comp0.vminus(vn);
    comp0.comp(z);


    sin_src sin0("sin0",3.3,10000,time_step);
    sin0.out(vp);
    constant_voltage_tdf ref("ref",1.2);
    ref.out(vn);

    //sc_core::sc_signal<bool> *temp;
    //temp = &z; 
    TLM *tlm;
    tlm = new TLM("tlm");
    tlm->IO_request(z);
    
    sca_util::sca_trace_file *vcdfile= sca_util::sca_create_vcd_trace_file("comparator-tdf.vcd");
    sca_trace(vcdfile, vp, "vp");
    sca_trace(vcdfile, vn, "vn");
    sca_trace(vcdfile, z, "z");
    sca_trace(vcdfile, tlm->IO_request, "IO_request");



    sc_start(5, sc_core::SC_MS);

    sca_util::sca_close_vcd_trace_file(vcdfile);



	return 0;
}

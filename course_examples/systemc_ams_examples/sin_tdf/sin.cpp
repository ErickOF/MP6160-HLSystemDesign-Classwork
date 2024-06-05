#include "systemc.h"
#include "systemc-ams.h"


SCA_TDF_MODULE (sine) {
    sca_tdf::sca_out<double> out; // output port

    sine( sc_core::sc_module_name nm, double ampl_= 1.0, double freq_ = 1.0e3,
             sca_core::sca_time Tm_ = sca_core::sca_time(0.125, sc_core::SC_MS))
        : out("out"), ampl(ampl_), freq(freq_), Tm(Tm_) {}
    void set_attributes() {
        set_timestep(Tm);
    }
    void processing() {
        double t = get_time().to_seconds(); // actual time
        out.write( ampl * std::sin( 2.0 * M_PI * freq * t ) );
    }
private:
    double ampl; // amplitude
    double freq; // frequency
    sca_core::sca_time Tm; // module time step
};
   
int sc_main (int argc, char* argv[])

{
    uint32_t i;
    sca_tdf::sca_signal<double> vp;
    sca_tdf::sca_signal<double> vn;
    sc_core::sc_time time_step(10.0, sc_core::SC_NS);

    sine sin0("sin0",3.3,10000,time_step);
    sin0.out(vp);
    
    sca_util::sca_trace_file *vcdfile= sca_util::sca_create_vcd_trace_file("sine-tdf.vcd");
    sca_trace(vcdfile, vp, "vp");

    sc_start(5, sc_core::SC_MS);

    sca_util::sca_close_vcd_trace_file(vcdfile);



	return 0;
}
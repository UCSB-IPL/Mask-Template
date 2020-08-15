#include <pdk_demo.h>


LOAD_PDK(PDK_DEMO);

void mask(int);



/* DO NOT MODIFY */
int main(int argc, char **argv) {
	setfont((char *)"caps.plf");
	msk_init();
    msk_add_sublayout(MASK_NAME, mask);
	msk_export(GDS_FILENAME);
	update_KLayout((char *)("KLayout 0.25.9 - " GDS_FILENAME " [" MASK_NAME "]"));
}




/* Your mask design */
void mask(int){

    layer(L_Documentation);
    var2window(MASK_NAME, 20000e-6, 20000e-6, 0,
               500e-6, 250e-6, 750e-6, 0.8, 100e-6, 1000e-6);
    
    
    layer(L_waveguides);

    org(0_um, 20000_um,0,NOFLIP);
    // Ring resonators
    // offset(17 * 127_um);
    BLOCK
    {
        std::vector gaps = {0.4_um, 0.45_um, 0.5_um, 0.55_um, 0.6_um, 0.65_um, 0.7_um};
        for (var gap : gaps)
        {
            BLOCK
            {
                var FA = NEW(FiberArrayCoupler, 2, 2 * 127_um, 0_deg, 150_um, 10_um).place();
                var orr = NEW(AllPassRingResonator, 80_um, gap, 0_um);
                FA.O_PORTS["out0"] >> NEW(SW, 200_um) >> orr >> NEW(SW, 100_um) >> NEW(CONNECTOR_U) >> FA.O_PORTS["out1"];
            }
            BLOCK
            {
                 move(420_um, -150_um, 0_deg, NOFLIP);
                textout(PNAME("G" << int(round(gap / 1_nm))<<"nm"), 60_um);
            }
            offset(4 * 127_um);
        }
    }

    // org(4950_um,5000_um,0,NOFLIP);
    // var mmi1 = NEW(MMI);
    // var mmi2 = NEW(MMI);
    // NEW_O_PORT()
        // >> mmi1.O_PORTS["in1"] >> "out1"
        // >> NEW(SINE_BEND, 100_um, -100_um)
        // >> NEW(SW, 1_mm)
        // >> NEW(SINE_BEND, 100_um, 100_um)
        // >> mmi2.O_PORTS["in1"] >> "in2" >> FLIP_Y
        // >> NEW(SINE_BEND, 100_um, 100_um)
        // >> NEW(SW, 1_mm)
        // >> NEW(CONNECTOR_SINE_BEND)
        // >> mmi1.O_PORTS["out2"]
        // ;
        
    //textout("test", 10);
    //printf(PNAME("test"<<" in"));
}


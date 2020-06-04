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
    layer(L_waveguides);

    org(4950_um,5000_um,0,NOFLIP);
    var mmi1 = NEW(MMI);
    var mmi2 = NEW(MMI);
    NEW_O_PORT()
        // >> mmi1.O_PORTS["in1"] >> "out1"
        >> NEW(SINE_BEND, 100_um, -100_um)
        // >> NEW(SW, 1_mm)
        // >> NEW(SINE_BEND, 100_um, 100_um)
        // >> mmi2.O_PORTS["in1"] >> "in2" >> FLIP_Y
        // >> NEW(SINE_BEND, 100_um, 100_um)
        // >> NEW(SW, 1_mm)
        // >> NEW(CONNECTOR_SINE_BEND)
        // >> mmi1.O_PORTS["out2"]
        ;
        
    //textout("test", 10);
    //printf(PNAME("test"<<" in"));
}


#include "FuelModelKitral.h"
#include "Cells.h"
#include "ReadArgs.h"
#include <cmath>
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

/*
        Global coefficients
*/
std::unordered_map<int, std::vector<float>> fmcs;
std::unordered_map<int, std::vector<float>> cbhs;
std::unordered_map<int, std::vector<float>> fls_david;
std::unordered_map<int, std::vector<float>> hs;
std::unordered_map<int, std::vector<float>> cbds;

/*
        Functions
*/

void
setup_const()
{
    // printf("dlw debug, enter fuel_coefs\n");
    /*   fuel type 1 */
    int PCH1 = 1;
    std::vector<float> fmc_pch1;
    std::vector<float> cbh_pch1;
    std::vector<float> fl_pch1;
    std::vector<float> h_pch1;
    std::vector<float> cbd_pch1;
    fmc_pch1.push_back(0.018880);
    cbh_pch1.push_back(0);
    fl_pch1.push_back(0.918);
    h_pch1.push_back(16434);
    cbd_pch1.push_back(0);
    fmcs.insert(std::make_pair(PCH1, fmc_pch1));
    cbhs.insert(std::make_pair(PCH1, cbh_pch1));
    fls_david.insert(std::make_pair(PCH1, fl_pch1));
    hs.insert(std::make_pair(PCH1, h_pch1));
    cbds.insert(std::make_pair(PCH1, cbd_pch1));

    int PCH2 = 2;
    std::vector<float> fmc_pch2;
    std::vector<float> cbh_pch2;
    std::vector<float> fl_pch2;
    std::vector<float> h_pch2;
    std::vector<float> cbd_pch2;
    fmc_pch2.push_back(0.016027);
    cbh_pch2.push_back(0);
    fl_pch2.push_back(0.617);
    h_pch2.push_back(16434);
    cbd_pch2.push_back(0);
    fmcs.insert(std::make_pair(PCH2, fmc_pch2));
    cbhs.insert(std::make_pair(PCH2, cbh_pch2));
    fls_david.insert(std::make_pair(PCH2, fl_pch2));
    hs.insert(std::make_pair(PCH2, h_pch2));
    cbds.insert(std::make_pair(PCH2, cbd_pch2));

    int PCH3 = 3;
    std::vector<float> fmc_pch3;
    std::vector<float> cbh_pch3;
    std::vector<float> fl_pch3;
    std::vector<float> h_pch3;
    std::vector<float> cbd_pch3;
    fmc_pch3.push_back(0.010235);
    cbh_pch3.push_back(0);
    fl_pch3.push_back(0.684);
    h_pch3.push_back(16434);
    cbd_pch3.push_back(0);
    fmcs.insert(std::make_pair(PCH3, fmc_pch3));
    cbhs.insert(std::make_pair(PCH3, cbh_pch3));
    fls_david.insert(std::make_pair(PCH3, fl_pch3));
    hs.insert(std::make_pair(PCH3, h_pch3));
    cbds.insert(std::make_pair(PCH3, cbd_pch3));

    int PCH4 = 4;
    std::vector<float> fmc_pch4;
    std::vector<float> cbh_pch4;
    std::vector<float> fl_pch4;
    std::vector<float> h_pch4;
    std::vector<float> cbd_pch4;
    fmc_pch4.push_back(0.008690);
    cbh_pch4.push_back(0);
    fl_pch4.push_back(0.527);
    h_pch4.push_back(16434);
    cbd_pch4.push_back(0);
    fmcs.insert(std::make_pair(PCH4, fmc_pch4));
    cbhs.insert(std::make_pair(PCH4, cbh_pch4));
    fls_david.insert(std::make_pair(PCH4, fl_pch4));
    hs.insert(std::make_pair(PCH4, h_pch4));
    cbds.insert(std::make_pair(PCH4, cbd_pch4));

    int PCH5 = 5;
    std::vector<float> fmc_pch5;
    std::vector<float> cbh_pch5;
    std::vector<float> fl_pch5;
    std::vector<float> h_pch5;
    std::vector<float> cbd_pch5;
    fmc_pch5.push_back(0.001009);
    cbh_pch5.push_back(0);
    fl_pch5.push_back(0.649);
    h_pch5.push_back(15899);
    cbd_pch5.push_back(0);
    fmcs.insert(std::make_pair(PCH5, fmc_pch5));
    cbhs.insert(std::make_pair(PCH5, cbh_pch5));
    fls_david.insert(std::make_pair(PCH5, fl_pch5));
    hs.insert(std::make_pair(PCH5, h_pch5));
    cbds.insert(std::make_pair(PCH5, cbd_pch5));

    int MT01 = 6;
    std::vector<float> fmc_mt01;
    std::vector<float> cbh_mt01;
    std::vector<float> fl_mt01;
    std::vector<float> h_mt01;
    std::vector<float> cbd_mt01;
    fmc_mt01.push_back(0.007603);
    cbh_mt01.push_back(0);
    fl_mt01.push_back(2.923);
    h_mt01.push_back(19635);
    cbd_mt01.push_back(0);
    fmcs.insert(std::make_pair(MT01, fmc_mt01));
    cbhs.insert(std::make_pair(MT01, cbh_mt01));
    fls_david.insert(std::make_pair(MT01, fl_mt01));
    hs.insert(std::make_pair(MT01, h_mt01));
    cbds.insert(std::make_pair(MT01, cbd_mt01));

    int MT02 = 7;
    std::vector<float> fmc_mt02;
    std::vector<float> cbh_mt02;
    std::vector<float> fl_mt02;
    std::vector<float> h_mt02;
    std::vector<float> cbd_mt02;
    fmc_mt02.push_back(0.008147);
    cbh_mt02.push_back(0);
    fl_mt02.push_back(1.910);
    h_mt02.push_back(19635);
    cbd_mt02.push_back(0);
    fmcs.insert(std::make_pair(MT02, fmc_mt02));
    cbhs.insert(std::make_pair(MT02, cbh_mt02));
    fls_david.insert(std::make_pair(MT02, fl_mt02));
    hs.insert(std::make_pair(MT02, h_mt02));
    cbds.insert(std::make_pair(MT02, cbd_mt02));

    int MT03 = 8;
    std::vector<float> fmc_mt03;
    std::vector<float> cbh_mt03;
    std::vector<float> fl_mt03;
    std::vector<float> h_mt03;
    std::vector<float> cbd_mt03;
    fmc_mt03.push_back(0.001672);
    cbh_mt03.push_back(0);
    fl_mt03.push_back(3.308);
    h_mt03.push_back(19129);
    cbd_mt03.push_back(0);
    fmcs.insert(std::make_pair(MT03, fmc_mt03));
    cbhs.insert(std::make_pair(MT03, cbh_mt03));
    fls_david.insert(std::make_pair(MT03, fl_mt03));
    hs.insert(std::make_pair(MT03, h_mt03));
    cbds.insert(std::make_pair(MT03, cbd_mt03));

    int MT04 = 9;
    std::vector<float> fmc_mt04;
    std::vector<float> cbh_mt04;
    std::vector<float> fl_mt04;
    std::vector<float> h_mt04;
    std::vector<float> cbd_mt04;
    fmc_mt04.push_back(0.004886);
    cbh_mt04.push_back(0);
    fl_mt04.push_back(1.383);
    h_mt04.push_back(19129);
    cbd_mt04.push_back(0);
    fmcs.insert(std::make_pair(MT04, fmc_mt04));
    cbhs.insert(std::make_pair(MT04, cbh_mt04));
    fls_david.insert(std::make_pair(MT04, fl_mt04));
    hs.insert(std::make_pair(MT04, h_mt04));
    cbds.insert(std::make_pair(MT04, cbd_mt04));

    int MT05 = 10;
    std::vector<float> fmc_mt05;
    std::vector<float> cbh_mt05;
    std::vector<float> fl_mt05;
    std::vector<float> h_mt05;
    std::vector<float> cbd_mt05;
    fmc_mt05.push_back(0.010321);
    cbh_mt05.push_back(0);
    fl_mt05.push_back(3.029);
    h_mt05.push_back(20920);
    cbd_mt05.push_back(0);
    fmcs.insert(std::make_pair(MT05, fmc_mt05));
    cbhs.insert(std::make_pair(MT05, cbh_mt05));
    fls_david.insert(std::make_pair(MT05, fl_mt05));
    hs.insert(std::make_pair(MT05, h_mt05));
    cbds.insert(std::make_pair(MT05, cbd_mt05));

    int MT06 = 11;
    std::vector<float> fmc_mt06;
    std::vector<float> cbh_mt06;
    std::vector<float> fl_mt06;
    std::vector<float> h_mt06;
    std::vector<float> cbd_mt06;
    fmc_mt06.push_back(0.009234);
    cbh_mt06.push_back(0);
    fl_mt06.push_back(3.529);
    h_mt06.push_back(21284);
    cbd_mt06.push_back(0);
    fmcs.insert(std::make_pair(MT06, fmc_mt06));
    cbhs.insert(std::make_pair(MT06, cbh_mt06));
    fls_david.insert(std::make_pair(MT06, fl_mt06));
    hs.insert(std::make_pair(MT06, h_mt06));
    cbds.insert(std::make_pair(MT06, cbd_mt06));

    int MT07 = 12;
    std::vector<float> fmc_mt07;
    std::vector<float> cbh_mt07;
    std::vector<float> fl_mt07;
    std::vector<float> h_mt07;
    std::vector<float> cbd_mt07;
    fmc_mt07.push_back(0.001787);
    cbh_mt07.push_back(0);
    fl_mt07.push_back(3.189);
    h_mt07.push_back(18828);
    cbd_mt07.push_back(0);
    fmcs.insert(std::make_pair(MT07, fmc_mt07));
    cbhs.insert(std::make_pair(MT07, cbh_mt07));
    fls_david.insert(std::make_pair(MT07, fl_mt07));
    hs.insert(std::make_pair(MT07, h_mt07));
    cbds.insert(std::make_pair(MT07, cbd_mt07));

    int MT08 = 13;
    std::vector<float> fmc_mt08;
    std::vector<float> cbh_mt08;
    std::vector<float> fl_mt08;
    std::vector<float> h_mt08;
    std::vector<float> cbd_mt08;
    fmc_mt08.push_back(0.004342);
    cbh_mt08.push_back(0);
    fl_mt08.push_back(1.903);
    h_mt08.push_back(18828);
    cbd_mt08.push_back(0);
    fmcs.insert(std::make_pair(MT08, fmc_mt08));
    cbhs.insert(std::make_pair(MT08, cbh_mt08));
    fls_david.insert(std::make_pair(MT08, fl_mt08));
    hs.insert(std::make_pair(MT08, h_mt08));
    cbds.insert(std::make_pair(MT08, cbd_mt08));

    int BN01 = 14;
    std::vector<float> fmc_bn01;
    std::vector<float> cbh_bn01;
    std::vector<float> fl_bn01;
    std::vector<float> h_bn01;
    std::vector<float> cbd_bn01;
    fmc_bn01.push_back(0.002249);
    cbh_bn01.push_back(0);
    fl_bn01.push_back(2.624);
    h_bn01.push_back(19246);
    cbd_bn01.push_back(0);
    fmcs.insert(std::make_pair(BN01, fmc_bn01));
    cbhs.insert(std::make_pair(BN01, cbh_bn01));
    fls_david.insert(std::make_pair(BN01, fl_bn01));
    hs.insert(std::make_pair(BN01, h_bn01));
    cbds.insert(std::make_pair(BN01, cbd_bn01));

    int BN02 = 15;
    std::vector<float> fmc_bn02;
    std::vector<float> cbh_bn02;
    std::vector<float> fl_bn02;
    std::vector<float> h_bn02;
    std::vector<float> cbd_bn02;
    fmc_bn02.push_back(0.001441);
    cbh_bn02.push_back(0);
    fl_bn02.push_back(2.310);
    h_bn02.push_back(19037);
    cbd_bn02.push_back(0);
    fmcs.insert(std::make_pair(BN02, fmc_bn02));
    cbhs.insert(std::make_pair(BN02, cbh_bn02));
    fls_david.insert(std::make_pair(BN02, fl_bn02));
    hs.insert(std::make_pair(BN02, h_bn02));
    cbds.insert(std::make_pair(BN02, cbd_bn02));

    int BN03 = 16;
    std::vector<float> fmc_bn03;
    std::vector<float> cbh_bn03;
    std::vector<float> fl_bn03;
    std::vector<float> h_bn03;
    std::vector<float> cbd_bn03;
    fmc_bn03.push_back(0.000979);
    cbh_bn03.push_back(0);
    fl_bn03.push_back(3.544);
    h_bn03.push_back(19045);
    cbd_bn03.push_back(0);
    fmcs.insert(std::make_pair(BN03, fmc_bn03));
    cbhs.insert(std::make_pair(BN03, cbh_bn03));
    fls_david.insert(std::make_pair(BN03, fl_bn03));
    hs.insert(std::make_pair(BN03, h_bn03));
    cbds.insert(std::make_pair(BN03, cbd_bn03));

    int BN04 = 17;
    std::vector<float> fmc_bn04;
    std::vector<float> cbh_bn04;
    std::vector<float> fl_bn04;
    std::vector<float> h_bn04;
    std::vector<float> cbd_bn04;
    fmc_bn04.push_back(0.001556);
    cbh_bn04.push_back(0);
    fl_bn04.push_back(2.164);
    h_bn04.push_back(19045);
    cbd_bn04.push_back(0);
    fmcs.insert(std::make_pair(BN04, fmc_bn04));
    cbhs.insert(std::make_pair(BN04, cbh_bn04));
    fls_david.insert(std::make_pair(BN04, fl_bn04));
    hs.insert(std::make_pair(BN04, h_bn04));
    cbds.insert(std::make_pair(BN04, cbd_bn04));

    int BN05 = 18;
    std::vector<float> fmc_bn05;
    std::vector<float> cbh_bn05;
    std::vector<float> fl_bn05;
    std::vector<float> h_bn05;
    std::vector<float> cbd_bn05;
    fmc_bn05.push_back(0.002365);
    cbh_bn05.push_back(0);
    fl_bn05.push_back(1.954);
    h_bn05.push_back(19045);
    cbd_bn05.push_back(0);
    fmcs.insert(std::make_pair(BN05, fmc_bn05));
    cbhs.insert(std::make_pair(BN05, cbh_bn05));
    fls_david.insert(std::make_pair(BN05, fl_bn05));
    hs.insert(std::make_pair(BN05, h_bn05));
    cbds.insert(std::make_pair(BN05, cbd_bn05));

    int PL01 = 19;
    std::vector<float> fmc_pl01;
    std::vector<float> cbh_pl01;
    std::vector<float> fl_pl01;
    std::vector<float> h_pl01;
    std::vector<float> cbd_pl01;
    fmc_pl01.push_back(0.013174);
    cbh_pl01.push_back(0.93);
    fl_pl01.push_back(0.838);
    h_pl01.push_back(18405);
    cbd_pl01.push_back(0.03);
    fmcs.insert(std::make_pair(PL01, fmc_pl01));
    cbhs.insert(std::make_pair(PL01, cbh_pl01));
    fls_david.insert(std::make_pair(PL01, fl_pl01));
    hs.insert(std::make_pair(PL01, h_pl01));
    cbds.insert(std::make_pair(PL01, cbd_pl01));

    int PL02 = 20;
    std::vector<float> fmc_pl02;
    std::vector<float> cbh_pl02;
    std::vector<float> fl_pl02;
    std::vector<float> h_pl02;
    std::vector<float> cbd_pl02;
    fmc_pl02.push_back(0.005973);
    cbh_pl02.push_back(7.59);
    fl_pl02.push_back(3.019);
    h_pl02.push_back(20376);
    cbd_pl02.push_back(0.125);
    fmcs.insert(std::make_pair(PL02, fmc_pl02));
    cbhs.insert(std::make_pair(PL02, cbh_pl02));
    fls_david.insert(std::make_pair(PL02, fl_pl02));
    hs.insert(std::make_pair(PL02, h_pl02));
    cbds.insert(std::make_pair(PL02, cbd_pl02));

    int PL03 = 21;
    std::vector<float> fmc_pl03;
    std::vector<float> cbh_pl03;
    std::vector<float> fl_pl03;
    std::vector<float> h_pl03;
    std::vector<float> cbd_pl03;
    fmc_pl03.push_back(0.002481);
    cbh_pl03.push_back(11.05);
    fl_pl03.push_back(3.333);
    h_pl03.push_back(20376);
    cbd_pl03.push_back(0.218);
    fmcs.insert(std::make_pair(PL03, fmc_pl03));
    cbhs.insert(std::make_pair(PL03, cbh_pl03));
    fls_david.insert(std::make_pair(PL03, fl_pl03));
    hs.insert(std::make_pair(PL03, h_pl03));
    cbds.insert(std::make_pair(PL03, cbd_pl03));

    int PL04 = 22;
    std::vector<float> fmc_pl04;
    std::vector<float> cbh_pl04;
    std::vector<float> fl_pl04;
    std::vector<float> h_pl04;
    std::vector<float> cbd_pl04;
    fmc_pl04.push_back(0.002712);
    cbh_pl04.push_back(12.1);
    fl_pl04.push_back(3.249);
    h_pl04.push_back(20376);
    cbd_pl04.push_back(0.274);
    fmcs.insert(std::make_pair(PL04, fmc_pl04));
    cbhs.insert(std::make_pair(PL04, cbh_pl04));
    fls_david.insert(std::make_pair(PL04, fl_pl04));
    hs.insert(std::make_pair(PL04, h_pl04));
    cbds.insert(std::make_pair(PL04, cbd_pl04));

    int PL05 = 23;
    std::vector<float> fmc_pl05;
    std::vector<float> cbh_pl05;
    std::vector<float> fl_pl05;
    std::vector<float> h_pl05;
    std::vector<float> cbd_pl05;
    fmc_pl05.push_back(0.006516);
    cbh_pl05.push_back(0);
    fl_pl05.push_back(4.087);
    h_pl05.push_back(20376);
    cbd_pl05.push_back(0);
    fmcs.insert(std::make_pair(PL05, fmc_pl05));
    cbhs.insert(std::make_pair(PL05, cbh_pl05));
    fls_david.insert(std::make_pair(PL05, fl_pl05));
    hs.insert(std::make_pair(PL05, h_pl05));
    cbds.insert(std::make_pair(PL05, cbd_pl05));

    int PL06 = 24;
    std::vector<float> fmc_pl06;
    std::vector<float> cbh_pl06;
    std::vector<float> fl_pl06;
    std::vector<float> h_pl06;
    std::vector<float> cbd_pl06;
    fmc_pl06.push_back(0.003255);
    cbh_pl06.push_back(0);
    fl_pl06.push_back(3.714);
    h_pl06.push_back(20376);
    cbd_pl06.push_back(0);
    fmcs.insert(std::make_pair(PL06, fmc_pl06));
    cbhs.insert(std::make_pair(PL06, cbh_pl06));
    fls_david.insert(std::make_pair(PL06, fl_pl06));
    hs.insert(std::make_pair(PL06, h_pl06));
    cbds.insert(std::make_pair(PL06, cbd_pl06));

    int PL07 = 25;
    std::vector<float> fmc_pl07;
    std::vector<float> cbh_pl07;
    std::vector<float> fl_pl07;
    std::vector<float> h_pl07;
    std::vector<float> cbd_pl07;
    fmc_pl07.push_back(0.002596);
    cbh_pl07.push_back(0);
    fl_pl07.push_back(4.063);
    h_pl07.push_back(20376);
    cbd_pl07.push_back(0);
    fmcs.insert(std::make_pair(PL07, fmc_pl07));
    cbhs.insert(std::make_pair(PL07, cbh_pl07));
    fls_david.insert(std::make_pair(PL07, fl_pl07));
    hs.insert(std::make_pair(PL07, h_pl07));
    cbds.insert(std::make_pair(PL07, cbd_pl07));

    int PL08 = 26;
    std::vector<float> fmc_pl08;
    std::vector<float> cbh_pl08;
    std::vector<float> fl_pl08;
    std::vector<float> h_pl08;
    std::vector<float> cbd_pl08;
    fmc_pl08.push_back(0.009777);
    cbh_pl08.push_back(0);
    fl_pl08.push_back(0.905);
    h_pl08.push_back(18292);
    cbd_pl08.push_back(0);
    fmcs.insert(std::make_pair(PL08, fmc_pl08));
    cbhs.insert(std::make_pair(PL08, cbh_pl08));
    fls_david.insert(std::make_pair(PL08, fl_pl08));
    hs.insert(std::make_pair(PL08, h_pl08));
    cbds.insert(std::make_pair(PL08, cbd_pl08));

    int PL09 = 27;
    std::vector<float> fmc_pl09;
    std::vector<float> cbh_pl09;
    std::vector<float> fl_pl09;
    std::vector<float> h_pl09;
    std::vector<float> cbd_pl09;
    fmc_pl09.push_back(0.005429);
    cbh_pl09.push_back(0);
    fl_pl09.push_back(3.164);
    h_pl09.push_back(20150);
    cbd_pl09.push_back(0);
    fmcs.insert(std::make_pair(PL09, fmc_pl09));
    cbhs.insert(std::make_pair(PL09, cbh_pl09));
    fls_david.insert(std::make_pair(PL09, fl_pl09));
    hs.insert(std::make_pair(PL09, h_pl09));
    cbds.insert(std::make_pair(PL09, cbd_pl09));

    int PL10 = 28;
    std::vector<float> fmc_pl10;
    std::vector<float> cbh_pl10;
    std::vector<float> fl_pl10;
    std::vector<float> h_pl10;
    std::vector<float> cbd_pl10;
    fmc_pl10.push_back(0.003799);
    cbh_pl10.push_back(0);
    fl_pl10.push_back(2.742);
    h_pl10.push_back(20150);
    cbd_pl10.push_back(0);
    fmcs.insert(std::make_pair(PL10, fmc_pl10));
    cbhs.insert(std::make_pair(PL10, cbh_pl10));
    fls_david.insert(std::make_pair(PL10, fl_pl10));
    hs.insert(std::make_pair(PL10, h_pl10));
    cbds.insert(std::make_pair(PL10, cbd_pl10));

    int PL11 = 29;
    std::vector<float> fmc_pl11;
    std::vector<float> cbh_pl11;
    std::vector<float> fl_pl11;
    std::vector<float> h_pl11;
    std::vector<float> cbd_pl11;
    fmc_pl11.push_back(0.001325);
    cbh_pl11.push_back(0);
    fl_pl11.push_back(2.464);
    h_pl11.push_back(19597);
    cbd_pl11.push_back(0);
    fmcs.insert(std::make_pair(PL11, fmc_pl11));
    cbhs.insert(std::make_pair(PL11, cbh_pl11));
    fls_david.insert(std::make_pair(PL11, fl_pl11));
    hs.insert(std::make_pair(PL11, h_pl11));
    cbds.insert(std::make_pair(PL11, cbd_pl11));

    int DX01 = 30;
    std::vector<float> fmc_dx01;
    std::vector<float> cbh_dx01;
    std::vector<float> fl_dx01;
    std::vector<float> h_dx01;
    std::vector<float> cbd_dx01;
    fmc_dx01.push_back(0.002134);
    cbh_dx01.push_back(0);
    fl_dx01.push_back(8.25);
    h_dx01.push_back(19857);
    cbd_dx01.push_back(0);
    fmcs.insert(std::make_pair(DX01, fmc_dx01));
    cbhs.insert(std::make_pair(DX01, cbh_dx01));
    fls_david.insert(std::make_pair(DX01, fl_dx01));
    hs.insert(std::make_pair(DX01, h_dx01));
    cbds.insert(std::make_pair(DX01, cbd_dx01));

    int DX02 = 31;
    std::vector<float> fmc_dx02;
    std::vector<float> cbh_dx02;
    std::vector<float> fl_dx02;
    std::vector<float> h_dx02;
    std::vector<float> cbd_dx02;
    fmc_dx02.push_back(0.001903);
    cbh_dx02.push_back(0);
    fl_dx02.push_back(7.125);
    h_dx02.push_back(19463);
    cbd_dx02.push_back(0);
    fmcs.insert(std::make_pair(DX02, fmc_dx02));
    cbhs.insert(std::make_pair(DX02, cbh_dx02));
    fls_david.insert(std::make_pair(DX02, fl_dx02));
    hs.insert(std::make_pair(DX02, h_dx02));
    cbds.insert(std::make_pair(DX02, cbd_dx02));
}

// TODO: citation needed
float
rate_of_spread_k(inputs* data,
                 fuel_coefs* ptr,
                 main_outs* at)  // incluir efecto pendiente aqui y no afuera
{
    float p1, p2, p3, ws, tmp, rh, ch, fmc, fch, fv, ps, fp;

    // se = slope_effect(inp) ;
    ws = data->ws;
    tmp = data->tmp;
    rh = data->rh;
    ps = at->se;  // hacerlo con elevaciones
    p1 = -12.86;
    p2 = 0.04316;
    p3 = 13.8;
    float midpoint = 57.09;
    float steepness = 0.081;
    float sigmoid = 1.0 / (1.0 + exp(-steepness * (rh - midpoint)));
    ch = 4 + 16 * sigmoid - 0.00982 * tmp;
    fmc = fmcs[data->nftype][0] * 60;  // factor de propagacion en m/min
    fch = min(51.43, 52.3342 * pow(ch, -1.3035));
    fv = p1 * exp(-p2 * ws) + p3;
    if (ps == 0)
    {
        at->rss = fmc * fch * (fv);
    }
    else
    {
        at->rss = fmc * fch * (fv + ps);
    }

    // fp = 1.0 + 0.023322 * data->ps + 0.00013585 * pow(data->ps, 2.0);
    // at->rss = fmc*fch*(fv);
    return at->rss * (at->rss >= 0);
}

// TODO: citation needed
float
flankfire_ros_k(float ros, float bros, float lb)
{
    return ((ros + bros) / (lb * 2.0));
}

/* ----------------- Length-to-Breadth --------------------------*/
// TODO: citation needed
float
l_to_b(float ws, fuel_coefs* ptr)
{
    float l1, l2, lb;
    l1 = 2.233;     // 1.411; // ptr->l1 ;
    l2 = -0.01031;  // 0.01745; // ptr->l2 ;
    lb = 1.0 + pow(l1 * exp(-l2 * ws) - l1, 2.0);
    return lb;
}

/* ----------------- Back Rate of Spread --------------------------*/
// TODO: citation needed
float
backfire_ros_k(main_outs* at, snd_outs* sec)
{
    float hb, bros, lb;
    // lb = l_to_b(data->fueltype,at->wsv) ;
    lb = sec->lb;
    hb = (lb + sqrt(pow(lb, 2) - 1.0)) / (lb - sqrt(pow(lb, 2) - 1.0));

    bros = at->rss / hb;

    return bros * (bros >= 0);
}

// TODO: citation needed
float
slope_effect(float elev_i, float elev_j, int cellsize)
{
    float ps_ij = (elev_j - elev_i) / (cellsize / 4.);  // cellsize corresponds to the perimeter of the cell
    float se;
    se = 1. + 0.023322 * ps_ij + 0.00013585 * std::pow(ps_ij, 2);

    return se;
}

// TODO: citation needed
float
flame_length(inputs* data, main_outs* at)  // REVISAR ESTA ECUACI�N
{
    float ib, fl;

    ib = at->sfi;

    fl = 0.0775 * pow(ib, 0.46);
    return fl;
}

// TODO: citation needed
float
angleFL(inputs* data, main_outs* at)
{
    float angle, fl, y, ws;
    ws = data->ws;
    fl = at->fl;
    y = 10.0 / 36.0 * ws;

    angle = atan(2.24 * sqrt(fl / pow(y, 2)));
    return angle;
}

// TODO: citation needed
float
flame_height(inputs* data, main_outs* at)
{
    float fh, phi;
    phi = angleFL(data, at);
    fh = at->fl * sin(phi);
    return fh;
}

// TODO: citation needed
float
byram_intensity(inputs* data, main_outs* at)
{
    float ros, H, wa, ib;
    ros = at->rss;
    H = hs[data->nftype][0];
    wa = fls_david[data->nftype][0];
    ib = H * wa * ros / 60;
    ib = std::ceil(ib * 100.0) / 100.0;
    return ib;  // unidad de medida
}

/**
 * Calculates byram fire intensity when there is active crown fire.
 * In order for this to be calculated, the input folder must contain
 * files with CBD, CBH and tree height data for each cell.
 * @param at Structure containing the cell's output data.
 * @param data Structure containing the cell's input data.
 * @return Fire intensity.
 */

float
crown_byram_intensity_k(main_outs* at, inputs* data)
{
    float cbd, cbh;
    if (std::isnan(data->cbh))
    {
        cbh = cbhs[data->nftype][0];
    }
    else
    {
        cbh = data->cbh;
    }
    // CBH is 0,1012 * Height^(1,4822)
    float canopy_height = std::pow(cbh / 0.1012, 1 / 1.4822) - cbh;
    if (canopy_height < 0)
    {
        throw std::runtime_error("Tree height is lower than canopy base height, "
                                 "please provide valid files.");
    }
    if (std::isnan(data->cbd))
    {
        cbd = cbds[data->nftype][0];
    }
    else
    {
        cbd = data->cbd;
    }
    return std::ceil((hs[data->nftype][0] / 60) * cbd * canopy_height * at->ros_active * 100.0) / 100.0;
}

/**
 * @brief Calculates the flame length of a cell when there is crown fire.
 * @param intensity Byram intensity for crown fires
 * @return the flame length
 */

float
crown_flame_length_k(float intensity)
{
    float fl = 0.1 * pow(intensity, 0.5);
    if (fl < 0.01)
    {
        return 0;
    }
    else
    {
        return std::ceil(fl * 100.0) / 100.0;
    }
}

bool
fire_type(inputs* data, main_outs* at, int FMC)
{
    float intensity, critical_intensity, cbh;
    bool crownFire = false;
    intensity = at->sfi;
    if (std::isnan(data->cbh))
    {
        cbh = cbhs[data->nftype][0];
    }
    else
    {
        cbh = data->cbh;
    }
    // cbh = data->cbh;
    // TODO: citation needed
    critical_intensity = pow((0.01 * cbh * (460 + 25.9 * FMC)), 1.5);
    if ((intensity > critical_intensity) && cbh != 0)
        crownFire = true;
    return crownFire;
}

// TODO: citation needed
float
crownfractionburn(inputs* data, main_outs* at, int FMC)
{  // generar output de cfb
    float a, cbd, ros, ros0, H, wa, i0, cbh, cfb;
    if (std::isnan(data->cbh))
    {
        cbh = cbhs[data->nftype][0];
    }
    else
    {
        cbh = data->cbh;
    }
    i0 = pow((0.01 * cbh * (460 + 25.9 * FMC)), 1.5);
    H = hs[data->nftype][0];
    wa = fls_david[data->nftype][0];
    if (std::isnan(data->cbd))
    {
        cbd = cbds[data->nftype][0];
    }
    else
    {
        cbd = data->cbd;
    }

    ros0 = 60 * i0 / (H * wa);
    ros = at->rss;
    if (cbd != 0)
    {
        a = -log(0.1) / (0.9 * (3.0 / cbd - ros0));
    }
    else
    {
        a = 0.23;
    }
    cfb = 1 - exp(-a * (ros - ros0));

    return cfb;
}

// TODO: citation needed
float
active_rate_of_spreadPL04(inputs* data,
                          main_outs* at)  // En KITRAL SE USA PL04
{
    float p1, p2, p3, ws, tmp, rh, ch, fmc, fch, fv, ps, ros_active, rospl04, fp, ros_final, ros;

    // se = slope_effect(inp) ;
    ws = data->ws;
    tmp = data->tmp;
    rh = data->rh;
    ps = at->se;
    p1 = -12.86;
    p2 = 0.04316;
    p3 = 13.8;

    ch = (-2.97374 + 0.262 * rh - 0.00982 * tmp);
    fmc = 0.002712 * 60;  // factor de propagacion en m/min de PL04
    fch = (389.1624 + 14.3 * ch + 0.02 * pow(ch, 2.0))
          / (3.559 + 1.6615 * ch + 2.62392 * pow(ch, 2.0));  // es -14.3 segun el libro
    fv = p1 * exp(-p2 * ws * 0.4) + p3;
    // fp = 1.0 + 0.023322 * data->ps + 0.00013585 * pow(data->ps, 2.0);
    if (ps == 0)
    {
        rospl04 = fmc * fch * (fv);
    }
    else
    {
        rospl04 = fmc * fch * (fv + ps);
    }
    ros_active = 3.34 * rospl04;  // if rac*cbd>3.0, aplicar
                                  // ros_final=3.34*rospl04
    return ros_active;
}

// TODO: citation needed
float
final_rate_of_spreadPL04(main_outs* at)  // En KITRAL SE USA PL04
{
    float ros_active, ros_final, ros;
    ros = at->rss;
    ros_active = at->ros_active;
    ros_final = ros + at->cfb * (ros_active - ros);
    return ros_final;
}

bool
checkActive(inputs* data, main_outs* at, int FMC)  // En KITRAL SE USA PL04
{
    float ros_critical, cbd, H, wa, i0, cbh;
    bool active;
    if (std::isnan(data->cbh))
    {
        cbh = cbhs[data->nftype][0];
    }
    else
    {
        cbh = data->cbh;
    }
    i0 = pow((0.01 * cbh * (460 + 25.9 * FMC)), 1.5);
    H = hs[data->nftype][0];
    wa = fls_david[data->nftype][0];
    ros_critical = 60 * i0 / (H * wa);
    if (std::isnan(data->cbd))
    {
        cbd = cbds[data->nftype][0];
    }
    else
    {
        cbd = data->cbd;
    }
    active = cbd * ros_critical >= 3;
    return active;
}

// TODO: citation needed
float
backfire_ros10_k(fire_struc* hptr, snd_outs* sec)
{
    float hb, bros, lb;
    lb = sec->lb;
    hb = (lb + sqrt(pow(lb, 2) - 1.0)) / (lb - sqrt(pow(lb, 2) - 1.0));

    bros = hptr->ros / hb;

    return bros;
}

/***
 * fire_struc *hptr: headstruct
 * fire_struc *fptr: flankstruct
 * fire_struc *bptr: backstruct
 */
void
calculate_k(inputs* data,
            inputs* head,
            int cellsize,
            fuel_coefs* ptr,
            arguments* args,
            main_outs* at,
            snd_outs* sec,
            fire_struc* hptr,
            fire_struc* fptr,
            fire_struc* bptr,
            bool& activeCrown)
{
    // Hack: Initialize coefficients
    setup_const();

    // Aux
    float ros, bros, lb, fros;
    int FMC;
    bool crownFire = false;
    at->cfb = 0;
    // Populate fuel coefs struct
    if (args->verbose)
    {
        std::cout << "Populate fuel types " << std::endl;
        std::cout << "NfTypes:" << data->nftype << std::endl;
    }
    // FMC = Fuel Moisture Content
    FMC = args->FMC;
    ptr->nftype = data->nftype;
    ptr->fmc = fmcs[data->nftype][0];
    if (isnan(data->cbh))
    {
        ptr->cbh = cbhs[data->nftype][0];
    }
    else
    {
        ptr->cbh = data->cbh;
    }
    // cout << "   cbh " << ptr->cbh << "\n";

    ptr->fl = fls_david[data->nftype][0];
    // cout << "   fl " << ptr->fl << "\n";

    ptr->h = hs[data->nftype][0];
    // cout << "   h " << ptr->h << "\n";
    float elevation_origin = data->elev;
    float elevation_destiny = head->elev;
    at->se = slope_effect(elevation_origin, elevation_destiny, cellsize);
    // Step 1: Calculate HROS (surface)
    at->rss = rate_of_spread_k(data, ptr, at);
    hptr->rss = at->rss;
    // Step 2: Calculate Length-to-breadth
    sec->lb = l_to_b(data->ws, ptr);

    // Step 3: Calculate BROS (surface)
    bptr->rss = backfire_ros_k(at, sec);

    // Step 4: Calculate central FROS (surface)
    fptr->rss = flankfire_ros_k(hptr->rss, bptr->rss, sec->lb);

    // Step 5: Ellipse components
    at->a = (hptr->rss + bptr->rss) / 2.;
    at->b = (hptr->rss + bptr->rss) / (2. * sec->lb);
    at->c = (hptr->rss - bptr->rss) / 2.;

    // Step 6: Byram Intensity
    at->sfi = byram_intensity(data, at);

    // Step 7: Flame Length
    at->fl = flame_length(data, at);

    // Step 8: Flame angle
    at->angle = angleFL(data, at);

    // Step 9: Flame Height
    at->fh = flame_height(data, at);

    // Step 10: Criterion for Crown Fire Initiation (no init if user does not
    // want to include it)
    if (args->AllowCROS && (data->cbh > 0 || cbhs[data->nftype][0] != 0))
    {
        if (activeCrown)
        {  // si el fuego esta activo en copas chequeamos condiciones
            at->ros_active = active_rate_of_spreadPL04(data, at);
            if (!checkActive(data, at, FMC))
            {
                activeCrown = false;
            }
        }
        else
        {
            crownFire = fire_type(data, at, FMC);
            if (args->verbose)
            {
                cout << "Checking crown Fire conditions " << crownFire << "\n";
            }
        }
    }
    else
    {
        crownFire = false;
        activeCrown = false;
    }
    // If we have Crown fire, update the ROSs
    if (crownFire)
    {
        at->ros_active = active_rate_of_spreadPL04(data, at);
        at->cfb = crownfractionburn(data, at, FMC);

        hptr->ros = final_rate_of_spreadPL04(at);
        at->rss = hptr->ros;
        bptr->ros = backfire_ros10_k(hptr, sec);
        fptr->ros = flankfire_ros_k(hptr->ros, bptr->ros, sec->lb);
        at->crown_intensity = crown_byram_intensity_k(at, data);
        at->crown_flame_length = crown_flame_length_k(at->crown_intensity);

        if (args->verbose)
        {
            cout << "hptr->ros = " << hptr->ros << "\n";
            cout << "bptr->ros = " << bptr->ros << "\n";
            cout << "fptr->ros = " << fptr->ros << "\n";
        }

        at->a = (hptr->ros + bptr->ros) / 2.;
        at->b = (hptr->ros + bptr->ros) / (2. * sec->lb);
        at->c = (hptr->ros - bptr->rss) / 2;
        at->crown = 1;
        activeCrown = true;
    }
    else if (activeCrown)
    {
        at->cfb = crownfractionburn(data, at,
                                    FMC);  // lo calculamos igual porque lo necesitamos para el output
        hptr->ros = at->ros_active;
        at->rss = hptr->ros;
        bptr->ros = backfire_ros10_k(hptr, sec);
        fptr->ros = flankfire_ros_k(hptr->ros, bptr->ros, sec->lb);
        at->crown_intensity = crown_byram_intensity_k(at, data);
        at->crown_flame_length = crown_flame_length_k(at->crown_intensity);

        if (args->verbose)
        {
            cout << "hptr->ros = " << hptr->ros << "\n";
            cout << "bptr->ros = " << bptr->ros << "\n";
            cout << "fptr->ros = " << fptr->ros << "\n";
        }

        at->a = (hptr->ros + bptr->ros) / 2.;
        at->b = (hptr->ros + bptr->ros) / (2. * sec->lb);
        at->c = (hptr->ros - bptr->rss) / 2;
        at->crown = 1;
        // std::cout  << "ros_activo: "  <<hptr->ros <<  std::endl;
    }

    // Otherwise, use the surface values
    else
    {
        at->crown = 0;
        hptr->ros = hptr->rss;
        bptr->ros = bptr->rss;
        fptr->ros = fptr->rss;
        if (args->verbose)
        {
            cout << "hptr->ros = " << hptr->ros << "\n";
            cout << "bptr->ros = " << bptr->ros << "\n";
            cout << "fptr->ros = " << fptr->ros << "\n";
        }
    }

    if (args->verbose)
    {
        cout << "--------------- Inputs --------------- \n";
        cout << "ws = " << data->ws << "\n";
        cout << "coef data->cbh = " << data->cbh << "\n";
        cout << "coef ptr->fmc = " << ptr->fmc << "\n";
        cout << "coef ptr->cbh = " << ptr->cbh << "\n";
        cout << "coef ptr->fl = " << ptr->fl << "\n";
        cout << "coef ptr->h = " << ptr->h << "\n";
        // cout << "coef ptr->q2 = " << ptr->q2 << "\n" ;
        // cout << "coef ptr->q3 = " << ptr->q3 << "\n" ;
        cout << "\n";

        cout << "---------------- Outputs --------------- \n";
        cout << "at->rss = " << at->rss << "\n";
        cout << "hptr->rss = " << hptr->rss << "\n";
        cout << "lb = " << sec->lb << "\n";
        cout << "bptr->rss = " << bptr->rss << "\n";
        cout << "fptr->rss = " << fptr->rss << "\n";
        cout << "axis a = " << at->a << "\n";
        cout << "axis b = " << at->b << "\n";
        cout << "axis c = " << at->c << "\n";
        cout << "fl = " << at->fl << "\n";
        cout << "angle = " << at->angle << "\n";
        cout << "fh = " << at->fh << "\n";
        cout << "Crown Fire = " << crownFire << "\n";
    }
}

void
determine_destiny_metrics_k(inputs* data, fuel_coefs* ptr, arguments* args, main_outs* metrics)
{
    // Hack: Initialize coefficients
    setup_const();

    // Aux
    float ros = 0, bros = 0, lb = 0, fros = 0;
    int FMC = args->FMC;
    bool crownFire = false;
    metrics->cfb = 0;
    // ptr->q1 = q_coeff[data->nftype][0];
    // ptr->q2 = q_coeff[data->nftype][1];
    // ptr->q3 = q_coeff[data->nftype][2];
    ptr->nftype = data->nftype;
    // Step 6: Byram Intensity
    metrics->sfi = byram_intensity(data, metrics);
    // Step 7: Flame Length
    metrics->fl = flame_length(data, metrics);
    // Step 10: Criterion for Crown Fire Initiation (no init if user does not
    // want to include it)
    if (args->AllowCROS)
    {
        crownFire = fire_type(data, metrics, FMC);
        if (crownFire)
        {
            metrics->cfb = crownfractionburn(data, metrics, FMC);
            metrics->crown_intensity = crown_byram_intensity_k(metrics, data);
            metrics->crown_flame_length = crown_flame_length_k(metrics->crown_intensity);
        }
        if (args->verbose)
        {
            cout << "Checking crown Fire conditions " << crownFire << "\n";
        }
    }
    else
    {
        crownFire = false;
    }

    metrics->crown = int(crownFire);
}

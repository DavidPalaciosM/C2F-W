#include "FuelModelSpain.h"
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

/**
 * Global coefficients
 */
std::unordered_map<int, std::vector<float>> p_coeff;
std::unordered_map<int, std::vector<float>> q_coeff;
std::unordered_map<int, std::vector<float>> fm_parameters;
int16_t HEAT_YIELD = 18000;  // unidad kJ/kg

/**
 *
 * @param scenario Weather scenario used in the simulation. It determines the
 * fuel model coefficients.
 */
void
initialize_coeff(int scenario)
{
    if (scenario == 1)
    {
        // Populate them
        // FM101
        int F101 = 101;
        std::vector<float> p_101;
        p_101.push_back(2.575);
        p_101.push_back(0.6665);
        p_101.push_back(0.1096);

        std::vector<float> q_101;
        q_101.push_back(-0.516);
        q_101.push_back(0.288);
        q_101.push_back(0.8972);

        p_coeff.insert(std::make_pair(F101, p_101));
        q_coeff.insert(std::make_pair(F101, q_101));

        // FM 102
        int F102 = 102;
        std::vector<float> p_102;
        p_102.push_back(0.4218);
        p_102.push_back(0.2915);
        p_102.push_back(0.01212);

        std::vector<float> q_102;
        q_102.push_back(-1.307);
        q_102.push_back(0.1322);
        q_102.push_back(1.887);

        p_coeff.insert(std::make_pair(F102, p_102));
        q_coeff.insert(std::make_pair(F102, q_102));

        // FM 103
        int F103 = 103;
        std::vector<float> p_103;
        p_103.push_back(0.1638);
        p_103.push_back(0.2095);
        p_103.push_back(0.007809);

        std::vector<float> q_103;
        q_103.push_back(-1.572);
        q_103.push_back(0.1068);
        q_103.push_back(2.409);

        p_coeff.insert(std::make_pair(F103, p_103));
        q_coeff.insert(std::make_pair(F103, q_103));

        // FM 104
        int F104 = 104;
        std::vector<float> p_104;
        p_104.push_back(0.07138);
        p_104.push_back(0.1417);
        p_104.push_back(0.002243);

        std::vector<float> q_104;
        q_104.push_back(-2.391);
        q_104.push_back(0.05973);
        q_104.push_back(3.334);

        p_coeff.insert(std::make_pair(F104, p_104));
        q_coeff.insert(std::make_pair(F104, q_104));

        // FM 105
        int F105 = 105;
        std::vector<float> p_105;
        p_105.push_back(0.03548);
        p_105.push_back(0.07829);
        p_105.push_back(0.001524);

        std::vector<float> q_105;
        q_105.push_back(-3.075);
        q_105.push_back(0.03373);
        q_105.push_back(4.391);

        p_coeff.insert(std::make_pair(F105, p_105));
        q_coeff.insert(std::make_pair(F105, q_105));

        // FM 106
        int F106 = 106;
        std::vector<float> p_106;
        p_106.push_back(0.02469);
        p_106.push_back(0.08049);
        p_106.push_back(0.0008245);

        std::vector<float> q_106;
        q_106.push_back(-4.006);
        q_106.push_back(0.03019);
        q_106.push_back(5.463);

        p_coeff.insert(std::make_pair(F106, p_106));
        q_coeff.insert(std::make_pair(F106, q_106));

        // FM 107
        int F107 = 107;
        std::vector<float> p_107;
        p_107.push_back(0.02329);
        p_107.push_back(0.09086);
        p_107.push_back(0.0009262);

        std::vector<float> q_107;
        q_107.push_back(-3.979);
        q_107.push_back(0.03746);
        q_107.push_back(5.587);

        p_coeff.insert(std::make_pair(F107, p_107));
        q_coeff.insert(std::make_pair(F107, q_107));

        // FM 108
        int F108 = 108;
        std::vector<float> p_108;
        p_108.push_back(0.02111);
        p_108.push_back(0.07793);
        p_108.push_back(0.001174);

        std::vector<float> q_108;
        q_108.push_back(-3.842);
        q_108.push_back(0.03855);
        q_108.push_back(5.817);

        p_coeff.insert(std::make_pair(F108, p_108));
        q_coeff.insert(std::make_pair(F108, q_108));

        // FM 121
        int F121 = 121;
        std::vector<float> p_121;
        p_121.push_back(0.613);
        p_121.push_back(0.2139);
        p_121.push_back(0.0187);

        std::vector<float> q_121;
        q_121.push_back(-1.267);
        q_121.push_back(0.0922);
        q_121.push_back(1.845);

        p_coeff.insert(std::make_pair(F121, p_121));
        q_coeff.insert(std::make_pair(F121, q_121));

        // FM 122
        int F122 = 122;
        std::vector<float> p_122;
        p_122.push_back(0.195);
        p_122.push_back(0.1243);
        p_122.push_back(0.006478);

        std::vector<float> q_122;
        q_122.push_back(-1.939);
        q_122.push_back(0.05084);
        q_122.push_back(2.706);

        p_coeff.insert(std::make_pair(F122, p_122));
        q_coeff.insert(std::make_pair(F122, q_122));

        // FM 123
        int F123 = 123;
        std::vector<float> p_123;
        p_123.push_back(0.06515);
        p_123.push_back(0.07833);
        p_123.push_back(0.002831);

        std::vector<float> q_123;
        q_123.push_back(-2.646);
        q_123.push_back(0.03365);
        q_123.push_back(3.788);

        p_coeff.insert(std::make_pair(F123, p_123));
        q_coeff.insert(std::make_pair(F123, q_123));

        // FM 124
        int F124 = 124;
        std::vector<float> p_124;
        p_124.push_back(0.07867);
        p_124.push_back(0.07788);
        p_124.push_back(0.003431);

        std::vector<float> q_124;
        q_124.push_back(-3.508);
        q_124.push_back(0.03246);
        q_124.push_back(5.098);

        p_coeff.insert(std::make_pair(F124, p_124));
        q_coeff.insert(std::make_pair(F124, q_124));

        // FM 142
        int F142 = 142;
        std::vector<float> p_142;
        p_142.push_back(0.3505);
        p_142.push_back(0.07768);
        p_142.push_back(0.01498);

        std::vector<float> q_142;
        q_142.push_back(-1.959);
        q_142.push_back(0.0322);
        q_142.push_back(2.819);

        p_coeff.insert(std::make_pair(F142, p_142));
        q_coeff.insert(std::make_pair(F142, q_142));

        // FM 143
        int F143 = 143;
        std::vector<float> p_143;
        p_143.push_back(1.748);
        p_143.push_back(0.1589);
        p_143.push_back(0.08249);

        std::vector<float> q_143;
        q_143.push_back(-0.938);
        q_143.push_back(0.07674);
        q_143.push_back(1.479);

        p_coeff.insert(std::make_pair(F143, p_143));
        q_coeff.insert(std::make_pair(F143, q_143));

        // FM 144
        int F144 = 144;
        std::vector<float> p_144;
        p_144.push_back(0.08116);
        p_144.push_back(0.07849);
        p_144.push_back(0.003353);

        std::vector<float> q_144;
        q_144.push_back(-2.452);
        q_144.push_back(0.03347);
        q_144.push_back(3.486);

        p_coeff.insert(std::make_pair(F144, p_144));
        q_coeff.insert(std::make_pair(F144, q_144));

        // FM 145
        int F145 = 145;
        std::vector<float> p_145;
        p_145.push_back(0.0483);
        p_145.push_back(0.0781);
        p_145.push_back(0.002783);

        std::vector<float> q_145;
        q_145.push_back(-2.796);
        q_145.push_back(0.04029);
        q_145.push_back(4.24);

        p_coeff.insert(std::make_pair(F145, p_145));
        q_coeff.insert(std::make_pair(F145, q_145));

        // FM 146
        int F146 = 146;
        std::vector<float> p_146;
        p_146.push_back(0.1248);
        p_146.push_back(0.07783);
        p_146.push_back(0.007999);

        std::vector<float> q_146;
        q_146.push_back(-2.121);
        q_146.push_back(0.04111);
        q_146.push_back(3.327);

        p_coeff.insert(std::make_pair(F146, p_146));
        q_coeff.insert(std::make_pair(F146, q_146));

        // FM 146
        int F147 = 147;
        std::vector<float> p_147;
        p_147.push_back(0.07431);
        p_147.push_back(0.07791);
        p_147.push_back(0.004384);

        std::vector<float> q_147;
        q_147.push_back(-2.668);
        q_147.push_back(0.04027);
        q_147.push_back(4.089);

        p_coeff.insert(std::make_pair(F147, p_147));
        q_coeff.insert(std::make_pair(F147, q_147));

        // FM 148
        int F148 = 148;
        std::vector<float> p_148;
        p_148.push_back(0.1238);
        p_148.push_back(0.07772);
        p_148.push_back(0.00647);

        std::vector<float> q_148;
        q_148.push_back(-2.506);
        q_148.push_back(0.03664);
        q_148.push_back(3.756);

        p_coeff.insert(std::make_pair(F148, p_148));
        q_coeff.insert(std::make_pair(F148, q_148));

        // FM 149
        int F149 = 149;
        std::vector<float> p_149;
        p_149.push_back(0.0667);
        p_149.push_back(0.07779);
        p_149.push_back(0.003506);

        std::vector<float> q_149;
        q_149.push_back(-3.209);
        q_149.push_back(0.03641);
        q_149.push_back(4.839);

        p_coeff.insert(std::make_pair(F149, p_149));
        q_coeff.insert(std::make_pair(F149, q_149));

        // FM 161
        int F161 = 161;
        std::vector<float> p_161;
        p_161.push_back(2.616);
        p_161.push_back(0.1744);
        p_161.push_back(0.1004);

        std::vector<float> q_161;
        q_161.push_back(-0.867);
        q_161.push_back(0.08398);
        q_161.push_back(1.326);

        p_coeff.insert(std::make_pair(F161, p_161));
        q_coeff.insert(std::make_pair(F161, q_161));

        // FM 162
        int F162 = 162;
        std::vector<float> p_162;
        p_162.push_back(0.6444);
        p_162.push_back(0.1574);
        p_162.push_back(0.02134);

        std::vector<float> q_162;
        q_162.push_back(-1.347);
        q_162.push_back(0.0649);
        q_162.push_back(1.958);

        p_coeff.insert(std::make_pair(F162, p_162));
        q_coeff.insert(std::make_pair(F162, q_162));

        // FM 163
        int F163 = 163;
        std::vector<float> p_163;
        p_163.push_back(0.08987);
        p_163.push_back(0.07819);
        p_163.push_back(0.003927);

        std::vector<float> q_163;
        q_163.push_back(-2.419);
        q_163.push_back(0.03439);
        q_163.push_back(3.493);

        p_coeff.insert(std::make_pair(F163, p_163));
        q_coeff.insert(std::make_pair(F163, q_163));

        // FM 164
        int F164 = 164;
        std::vector<float> p_164;
        p_164.push_back(0.1843);
        p_164.push_back(0.07912);
        p_164.push_back(0.005477);

        std::vector<float> q_164;
        q_164.push_back(-2.661);
        q_164.push_back(0.0271);
        q_164.push_back(3.579);

        p_coeff.insert(std::make_pair(F164, p_164));
        q_coeff.insert(std::make_pair(F164, q_164));

        // FM 165
        int F165 = 165;
        std::vector<float> p_165;
        p_165.push_back(0.3291);
        p_165.push_back(0.07679);
        p_165.push_back(0.02046);

        std::vector<float> q_165;
        q_165.push_back(-1.891);
        q_165.push_back(0.03665);
        q_165.push_back(3.027);

        p_coeff.insert(std::make_pair(F165, p_165));
        q_coeff.insert(std::make_pair(F165, q_165));

        // FM 181
        int F181 = 181;
        std::vector<float> p_181;
        p_181.push_back(14.96);
        p_181.push_back(0.401);
        p_181.push_back(1.983);

        std::vector<float> q_181;
        q_181.push_back(-0.1525);
        q_181.push_back(0.4018);
        q_181.push_back(0.4484);

        p_coeff.insert(std::make_pair(F181, p_181));
        q_coeff.insert(std::make_pair(F181, q_181));

        // FM 182
        int F182 = 182;
        std::vector<float> p_182;
        p_182.push_back(11.01);
        p_182.push_back(0.3366);
        p_182.push_back(0.7639);

        std::vector<float> q_182;
        q_182.push_back(-0.3704);
        q_182.push_back(0.202);
        q_182.push_back(0.6365);

        p_coeff.insert(std::make_pair(F182, p_182));
        q_coeff.insert(std::make_pair(F182, q_182));

        // FM 183
        int F183 = 183;
        std::vector<float> p_183;
        p_183.push_back(10.09);
        p_183.push_back(0.3454);
        p_183.push_back(0.584);

        std::vector<float> q_183;
        q_183.push_back(-0.4398);
        q_183.push_back(0.1448);
        q_183.push_back(0.7804);

        p_coeff.insert(std::make_pair(F183, p_183));
        q_coeff.insert(std::make_pair(F183, q_183));

        // FM 185
        int F185 = 185;
        std::vector<float> p_185;
        p_185.push_back(2.195);
        p_185.push_back(0.1807);
        p_185.push_back(0.07939);

        std::vector<float> q_185;
        q_185.push_back(-0.8838);
        q_185.push_back(0.08234);
        q_185.push_back(1.368);

        p_coeff.insert(std::make_pair(F185, p_185));
        q_coeff.insert(std::make_pair(F185, q_185));

        // FM 186
        int F186 = 186;
        std::vector<float> p_186;
        p_186.push_back(0.9183);
        p_186.push_back(0.1224);
        p_186.push_back(0.02969);

        std::vector<float> q_186;
        q_186.push_back(-1.306);
        q_186.push_back(0.04578);
        q_186.push_back(1.908);

        p_coeff.insert(std::make_pair(F186, p_186));
        q_coeff.insert(std::make_pair(F186, q_186));

        // FM 188
        int F188 = 188;
        std::vector<float> p_188;
        p_188.push_back(0.4789);
        p_188.push_back(0.07735);
        p_188.push_back(0.0195);

        std::vector<float> q_188;
        q_188.push_back(-1.68);
        q_188.push_back(0.02617);
        q_188.push_back(2.451);

        p_coeff.insert(std::make_pair(F188, p_188));
        q_coeff.insert(std::make_pair(F188, q_188));

        // FM 189
        int F189 = 189;
        std::vector<float> p_189;
        p_189.push_back(0.3229);
        p_189.push_back(0.07716);
        p_189.push_back(0.01346);

        std::vector<float> q_189;
        q_189.push_back(-1.916);
        q_189.push_back(0.02961);
        q_189.push_back(2.816);

        p_coeff.insert(std::make_pair(F189, p_189));
        q_coeff.insert(std::make_pair(F189, q_189));
    }

    if (scenario == 2)
    {
        // Populate them
        // FM 101
        int F101 = 101;
        std::vector<float> p_101;
        p_101.push_back(4.941);
        p_101.push_back(0.7086);
        p_101.push_back(0.2124);

        std::vector<float> q_101;
        q_101.push_back(-0.4535);
        q_101.push_back(0.2682);
        q_101.push_back(0.777);

        p_coeff.insert(std::make_pair(F101, p_101));
        q_coeff.insert(std::make_pair(F101, q_101));

        // FM 102
        int F102 = 102;
        std::vector<float> p_102;
        p_102.push_back(0.8112);
        p_102.push_back(0.3045);
        p_102.push_back(0.02528);

        std::vector<float> q_102;
        q_102.push_back(-1.036);
        q_102.push_back(0.1385);
        q_102.push_back(1.561);

        p_coeff.insert(std::make_pair(F102, p_102));
        q_coeff.insert(std::make_pair(F102, q_102));

        // FM 103
        int F103 = 103;
        std::vector<float> p_103;
        p_103.push_back(0.3609);
        p_103.push_back(0.2318);
        p_103.push_back(0.01738);

        std::vector<float> q_103;
        q_103.push_back(-1.273);
        q_103.push_back(0.1135);
        q_103.push_back(1.966);

        p_coeff.insert(std::make_pair(F103, p_103));
        q_coeff.insert(std::make_pair(F103, q_103));

        // FM 104
        int F104 = 104;
        std::vector<float> p_104;
        p_104.push_back(0.1486);
        p_104.push_back(0.153);
        p_104.push_back(0.004652);

        std::vector<float> q_104;
        q_104.push_back(-1.98);
        q_104.push_back(0.06712);
        q_104.push_back(2.744);

        p_coeff.insert(std::make_pair(F104, p_104));
        q_coeff.insert(std::make_pair(F104, q_104));

        // FM 105
        int F105 = 105;
        std::vector<float> p_105;
        p_105.push_back(0.0681);
        p_105.push_back(0.07832);
        p_105.push_back(0.002926);

        std::vector<float> q_105;
        q_105.push_back(-2.578);
        q_105.push_back(0.03345);
        q_105.push_back(3.694);

        p_coeff.insert(std::make_pair(F105, p_105));
        q_coeff.insert(std::make_pair(F105, q_105));

        // FM 106
        int F106 = 106;
        std::vector<float> p_106;
        p_106.push_back(0.04896);
        p_106.push_back(0.07908);
        p_106.push_back(0.001631);

        std::vector<float> q_106;
        q_106.push_back(-3.334);
        q_106.push_back(0.03012);
        q_106.push_back(4.525);

        p_coeff.insert(std::make_pair(F106, p_106));
        q_coeff.insert(std::make_pair(F106, q_106));

        // FM 107
        int F107 = 107;
        std::vector<float> p_107;
        p_107.push_back(0.03528);
        p_107.push_back(0.07869);
        p_107.push_back(0.001315);

        std::vector<float> q_107;
        q_107.push_back(-3.658);
        q_107.push_back(0.03158);
        q_107.push_back(5.09);

        p_coeff.insert(std::make_pair(F107, p_107));
        q_coeff.insert(std::make_pair(F107, q_107));

        // FM 108
        int F108 = 108;
        std::vector<float> p_108;
        p_108.push_back(0.04173);
        p_108.push_back(0.07796);
        p_108.push_back(0.002318);

        std::vector<float> q_108;
        q_108.push_back(-3.209);
        q_108.push_back(0.03823);
        q_108.push_back(4.86);

        p_coeff.insert(std::make_pair(F108, p_108));
        q_coeff.insert(std::make_pair(F108, q_108));

        // FM 121

        int F121 = 121;
        std::vector<float> p_121;
        p_121.push_back(1.64);
        p_121.push_back(0.2795);
        p_121.push_back(0.05015);

        std::vector<float> q_121;
        q_121.push_back(-0.9854);
        q_121.push_back(0.1202);
        q_121.push_back(1.392);

        p_coeff.insert(std::make_pair(F121, p_121));
        q_coeff.insert(std::make_pair(F121, q_121));

        // FM 122

        int F122 = 122;
        std::vector<float> p_122;
        p_122.push_back(0.4834);
        p_122.push_back(0.1577);
        p_122.push_back(0.01499);

        std::vector<float> q_122;
        q_122.push_back(-1.486);
        q_122.push_back(0.06882);
        q_122.push_back(2.084);

        p_coeff.insert(std::make_pair(F122, p_122));
        q_coeff.insert(std::make_pair(F122, q_122));

        // FM 123

        int F123 = 123;
        std::vector<float> p_123;
        p_123.push_back(0.1385);
        p_123.push_back(0.08614);
        p_123.push_back(0.005977);

        std::vector<float> q_123;
        q_123.push_back(-2.108);
        q_123.push_back(0.03642);
        q_123.push_back(3.029);

        p_coeff.insert(std::make_pair(F123, p_123));
        q_coeff.insert(std::make_pair(F123, q_123));

        // FM 124

        int F124 = 124;
        std::vector<float> p_124;
        p_124.push_back(0.1333);
        p_124.push_back(0.07794);
        p_124.push_back(0.005812);

        std::vector<float> q_124;
        q_124.push_back(-2.963);
        q_124.push_back(0.03259);
        q_124.push_back(4.318);

        p_coeff.insert(std::make_pair(F124, p_124));
        q_coeff.insert(std::make_pair(F124, q_124));

        // FM 142

        int F142 = 142;
        std::vector<float> p_142;
        p_142.push_back(3.016);
        p_142.push_back(0.1405);
        p_142.push_back(0.117);

        std::vector<float> q_142;
        q_142.push_back(-0.8923);
        q_142.push_back(0.06068);
        q_142.push_back(1.351);

        p_coeff.insert(std::make_pair(F142, p_142));
        q_coeff.insert(std::make_pair(F142, q_142));

        // FM 143

        int F143 = 143;
        std::vector<float> p_143;
        p_143.push_back(3.263);
        p_143.push_back(0.1853);
        p_143.push_back(0.1567);

        std::vector<float> q_143;
        q_143.push_back(-0.7716);
        q_143.push_back(0.08453);
        q_143.push_back(1.244);

        p_coeff.insert(std::make_pair(F143, p_143));
        q_coeff.insert(std::make_pair(F143, q_143));

        // FM 144

        int F144 = 144;
        std::vector<float> p_144;
        p_144.push_back(0.2209);
        p_144.push_back(0.1077);
        p_144.push_back(0.00858);

        std::vector<float> q_144;
        q_144.push_back(-1.841);
        q_144.push_back(0.04621);
        q_144.push_back(2.634);

        p_coeff.insert(std::make_pair(F144, p_144));
        q_coeff.insert(std::make_pair(F144, q_144));

        // FM 145

        int F145 = 145;
        std::vector<float> p_145;
        p_145.push_back(0.07661);
        p_145.push_back(0.07807);
        p_145.push_back(0.004418);

        std::vector<float> q_145;
        q_145.push_back(-2.425);
        q_145.push_back(0.03922);
        q_145.push_back(3.681);

        p_coeff.insert(std::make_pair(F145, p_145));
        q_coeff.insert(std::make_pair(F145, q_145));

        // FM 146

        int F146 = 146;
        std::vector<float> p_146;
        p_146.push_back(0.1924);
        p_146.push_back(0.07805);
        p_146.push_back(0.01232);

        std::vector<float> q_146;
        q_146.push_back(-1.864);
        q_146.push_back(0.04114);
        q_146.push_back(2.908);

        p_coeff.insert(std::make_pair(F146, p_146));
        q_coeff.insert(std::make_pair(F146, q_146));

        // FM 146

        int F147 = 147;
        std::vector<float> p_147;
        p_147.push_back(0.118);
        p_147.push_back(0.07792);
        p_147.push_back(0.006965);

        std::vector<float> q_147;
        q_147.push_back(-2.312);
        q_147.push_back(0.03944);
        q_147.push_back(3.548);

        p_coeff.insert(std::make_pair(F147, p_147));
        q_coeff.insert(std::make_pair(F147, q_147));

        // FM 148

        int F148 = 148;
        std::vector<float> p_148;
        p_148.push_back(0.1863);
        p_148.push_back(0.07774);
        p_148.push_back(0.009734);

        std::vector<float> q_148;
        q_148.push_back(-2.218);
        q_148.push_back(0.03714);
        q_148.push_back(3.323);

        p_coeff.insert(std::make_pair(F148, p_148));
        q_coeff.insert(std::make_pair(F148, q_148));

        // FM 149

        int F149 = 149;
        std::vector<float> p_149;
        p_149.push_back(0.1014);
        p_149.push_back(0.07776);
        p_149.push_back(0.005332);

        std::vector<float> q_149;
        q_149.push_back(-2.845);
        q_149.push_back(0.03678);
        q_149.push_back(4.283);

        p_coeff.insert(std::make_pair(F149, p_149));
        q_coeff.insert(std::make_pair(F149, q_149));

        // FM 161

        int F161 = 161;
        std::vector<float> p_161;
        p_161.push_back(5.028);
        p_161.push_back(0.2037);
        p_161.push_back(0.1978);

        std::vector<float> q_161;
        q_161.push_back(-0.7292);
        q_161.push_back(0.08708);
        q_161.push_back(1.115);

        p_coeff.insert(std::make_pair(F161, p_161));
        q_coeff.insert(std::make_pair(F161, q_161));

        // FM 162

        int F162 = 162;
        std::vector<float> p_162;
        p_162.push_back(1.128);
        p_162.push_back(0.1848);
        p_162.push_back(0.03716);

        std::vector<float> q_162;
        q_162.push_back(-1.119);
        q_162.push_back(0.07944);
        q_162.push_back(1.645);

        p_coeff.insert(std::make_pair(F162, p_162));
        q_coeff.insert(std::make_pair(F162, q_162));

        // FM 163

        int F163 = 163;
        std::vector<float> p_163;
        p_163.push_back(0.1554);
        p_163.push_back(0.08058);
        p_163.push_back(0.006821);

        std::vector<float> q_163;
        q_163.push_back(-2.03);
        q_163.push_back(0.03518);
        q_163.push_back(2.943);

        p_coeff.insert(std::make_pair(F163, p_163));
        q_coeff.insert(std::make_pair(F163, q_163));

        // FM 164

        int F164 = 164;
        std::vector<float> p_164;
        p_164.push_back(0.272);
        p_164.push_back(0.07915);
        p_164.push_back(0.008083);

        std::vector<float> q_164;
        q_164.push_back(-2.345);
        q_164.push_back(0.02613);
        q_164.push_back(3.187);

        p_coeff.insert(std::make_pair(F164, p_164));
        q_coeff.insert(std::make_pair(F164, q_164));

        // FM 165

        int F165 = 165;
        std::vector<float> p_165;
        p_165.push_back(0.4786);
        p_165.push_back(0.0766);
        p_165.push_back(0.02979);

        std::vector<float> q_165;
        q_165.push_back(-1.676);
        q_165.push_back(0.03638);
        q_165.push_back(2.685);

        p_coeff.insert(std::make_pair(F165, p_165));
        q_coeff.insert(std::make_pair(F165, q_165));

        // FM 181

        int F181 = 181;
        std::vector<float> p_181;
        p_181.push_back(21.49);
        p_181.push_back(0.5351);
        p_181.push_back(3.327);

        std::vector<float> q_181;
        q_181.push_back(-0.1561);
        q_181.push_back(0.1462);
        q_181.push_back(0.4506);

        p_coeff.insert(std::make_pair(F181, p_181));
        q_coeff.insert(std::make_pair(F181, q_181));

        // FM 182

        int F182 = 182;
        std::vector<float> p_182;
        p_182.push_back(11.87);
        p_182.push_back(0.3804);
        p_182.push_back(1.424);

        std::vector<float> q_182;
        q_182.push_back(-0.2634);
        q_182.push_back(0.2267);
        q_182.push_back(0.55);

        p_coeff.insert(std::make_pair(F182, p_182));
        q_coeff.insert(std::make_pair(F182, q_182));

        // FM 183

        int F183 = 183;
        std::vector<float> p_183;
        p_183.push_back(16.14);
        p_183.push_back(0.4104);
        p_183.push_back(0.9961);

        std::vector<float> q_183;
        q_183.push_back(-0.3704);
        q_183.push_back(0.2021);
        q_183.push_back(0.6365);

        p_coeff.insert(std::make_pair(F183, p_183));
        q_coeff.insert(std::make_pair(F183, q_183));

        // FM 185

        int F185 = 185;
        std::vector<float> p_185;
        p_185.push_back(4.008);
        p_185.push_back(0.2228);
        p_185.push_back(0.1393);

        std::vector<float> q_185;
        q_185.push_back(-0.7146);
        q_185.push_back(0.09259);
        q_185.push_back(1.158);

        p_coeff.insert(std::make_pair(F185, p_185));
        q_coeff.insert(std::make_pair(F185, q_185));

        // FM 186

        int F186 = 186;
        std::vector<float> p_186;
        p_186.push_back(1.783);
        p_186.push_back(0.1537);
        p_186.push_back(0.05478);

        std::vector<float> q_186;
        q_186.push_back(-1.056);
        q_186.push_back(0.06279);
        q_186.push_back(1.538);

        p_coeff.insert(std::make_pair(F186, p_186));
        q_coeff.insert(std::make_pair(F186, q_186));

        // FM 188

        int F188 = 188;
        std::vector<float> p_188;
        p_188.push_back(0.8048);
        p_188.push_back(0.09159);
        p_188.push_back(0.03249);

        std::vector<float> q_188;
        q_188.push_back(-1.364);
        q_188.push_back(0.03338);
        q_188.push_back(2.04);

        p_coeff.insert(std::make_pair(F188, p_188));
        q_coeff.insert(std::make_pair(F188, q_188));

        // FM 189

        int F189 = 189;
        std::vector<float> p_189;
        p_189.push_back(0.4263);
        p_189.push_back(0.07714);
        p_189.push_back(0.01775);

        std::vector<float> q_189;
        q_189.push_back(-1.758);
        q_189.push_back(0.03012);
        q_189.push_back(2.544);

        p_coeff.insert(std::make_pair(F189, p_189));
        q_coeff.insert(std::make_pair(F189, q_189));
    }

    if (scenario == 3)
    {

        // Populate them
        // FM 101
        int F101 = 101;
        std::vector<float> p_101;
        p_101.push_back(10.54);
        p_101.push_back(0.9248);
        p_101.push_back(0.6665);

        std::vector<float> q_101;
        q_101.push_back(-0.2781);
        q_101.push_back(0.4427);
        q_101.push_back(0.5494);

        p_coeff.insert(std::make_pair(F101, p_101));
        q_coeff.insert(std::make_pair(F101, q_101));

        // FM 102
        int F102 = 102;
        std::vector<float> p_102;
        p_102.push_back(9.046);
        p_102.push_back(0.6935);
        p_102.push_back(0.6243);

        std::vector<float> q_102;
        q_102.push_back(-0.2777);
        q_102.push_back(0.4381);
        q_102.push_back(0.5495);

        p_coeff.insert(std::make_pair(F102, p_102));
        q_coeff.insert(std::make_pair(F102, q_102));

        // FM 103
        int F103 = 103;
        std::vector<float> p_103;
        p_103.push_back(1.101);
        p_103.push_back(0.2945);
        p_103.push_back(0.05263);

        std::vector<float> q_103;
        q_103.push_back(-0.864);
        q_103.push_back(0.1465);
        q_103.push_back(1.422);

        p_coeff.insert(std::make_pair(F103, p_103));
        q_coeff.insert(std::make_pair(F103, q_103));

        // FM 104
        int F104 = 104;
        std::vector<float> p_104;
        p_104.push_back(2.828);
        p_104.push_back(0.4191);
        p_104.push_back(0.1083);

        std::vector<float> q_104;
        q_104.push_back(-0.6279);
        q_104.push_back(0.2175);
        q_104.push_back(1.004);

        p_coeff.insert(std::make_pair(F104, p_104));
        q_coeff.insert(std::make_pair(F104, q_104));

        // FM 105
        int F105 = 105;
        std::vector<float> p_105;
        p_105.push_back(0.2066);
        p_105.push_back(0.09646);
        p_105.push_back(0.008649);

        std::vector<float> q_105;
        q_105.push_back(-1.891);
        q_105.push_back(0.04173);
        q_105.push_back(2.707);

        p_coeff.insert(std::make_pair(F105, p_105));
        q_coeff.insert(std::make_pair(F105, q_105));

        // FM 106
        int F106 = 106;
        std::vector<float> p_106;
        p_106.push_back(0.1252);
        p_106.push_back(0.07909);
        p_106.push_back(0.004167);

        std::vector<float> q_106;
        q_106.push_back(-2.484);
        q_106.push_back(0.0302);
        q_106.push_back(3.375);

        p_coeff.insert(std::make_pair(F106, p_106));
        q_coeff.insert(std::make_pair(F106, q_106));

        // FM 107
        int F107 = 107;
        std::vector<float> p_107;
        p_107.push_back(0.2693);
        p_107.push_back(0.1079);
        p_107.push_back(0.009412);

        std::vector<float> q_107;
        q_107.push_back(-1.823);
        q_107.push_back(0.04448);
        q_107.push_back(2.545);

        p_coeff.insert(std::make_pair(F107, p_107));
        q_coeff.insert(std::make_pair(F107, q_107));

        // FM 108
        int F108 = 108;
        std::vector<float> p_108;
        p_108.push_back(0.09611);
        p_108.push_back(0.07795);
        p_108.push_back(0.005342);

        std::vector<float> q_108;
        q_108.push_back(-2.517);
        q_108.push_back(0.03868);
        q_108.push_back(3.788);

        p_coeff.insert(std::make_pair(F108, p_108));
        q_coeff.insert(std::make_pair(F108, q_108));

        // FM 121

        int F121 = 121;
        std::vector<float> p_121;
        p_121.push_back(25.52);
        p_121.push_back(0.7635);
        p_121.push_back(1.428);

        std::vector<float> q_121;
        q_121.push_back(-0.1525);
        q_121.push_back(0.4017);
        q_121.push_back(0.4484);

        p_coeff.insert(std::make_pair(F121, p_121));
        q_coeff.insert(std::make_pair(F121, q_121));

        // FM 122

        int F122 = 122;
        std::vector<float> p_122;
        p_122.push_back(8.922);
        p_122.push_back(0.4899);
        p_122.push_back(0.3328);

        std::vector<float> q_122;
        q_122.push_back(-0.4465);
        q_122.push_back(0.1749);
        q_122.push_back(0.7789);

        p_coeff.insert(std::make_pair(F122, p_122));
        q_coeff.insert(std::make_pair(F122, q_122));

        // FM 123

        int F123 = 123;
        std::vector<float> p_123;
        p_123.push_back(5.884);
        p_123.push_back(0.3888);
        p_123.push_back(0.2259);

        std::vector<float> q_123;
        q_123.push_back(-0.5876);
        q_123.push_back(0.1976);
        q_123.push_back(0.8988);

        p_coeff.insert(std::make_pair(F123, p_123));
        q_coeff.insert(std::make_pair(F123, q_123));

        // FM 124

        int F124 = 124;
        std::vector<float> p_124;
        p_124.push_back(0.6756);
        p_124.push_back(0.07785);
        p_124.push_back(0.02949);

        std::vector<float> q_124;
        q_124.push_back(-1.518);
        q_124.push_back(0.03362);
        q_124.push_back(2.179);

        p_coeff.insert(std::make_pair(F124, p_124));
        q_coeff.insert(std::make_pair(F124, q_124));

        // FM 142

        int F142 = 142;
        std::vector<float> p_142;
        p_142.push_back(10.39);
        p_142.push_back(0.2182);
        p_142.push_back(0.3807);

        std::vector<float> q_142;
        q_142.push_back(-0.5648);
        q_142.push_back(0.1069);
        q_142.push_back(0.9037);

        p_coeff.insert(std::make_pair(F142, p_142));
        q_coeff.insert(std::make_pair(F142, q_142));

        // FM 143

        int F143 = 143;
        std::vector<float> p_143;
        p_143.push_back(5.59);
        p_143.push_back(0.2107);
        p_143.push_back(0.254);

        std::vector<float> q_143;
        q_143.push_back(-0.6817);
        q_143.push_back(0.1007);
        q_143.push_back(1.064);

        p_coeff.insert(std::make_pair(F143, p_143));
        q_coeff.insert(std::make_pair(F143, q_143));

        // FM 144

        int F144 = 144;
        std::vector<float> p_144;
        p_144.push_back(5.257);
        p_144.push_back(0.3809);
        p_144.push_back(0.1807);

        std::vector<float> q_144;
        q_144.push_back(-0.6294);
        q_144.push_back(0.1919);
        q_144.push_back(0.9523);

        p_coeff.insert(std::make_pair(F144, p_144));
        q_coeff.insert(std::make_pair(F144, q_144));

        // FM 145

        int F145 = 145;
        std::vector<float> p_145;
        p_145.push_back(0.1073);
        p_145.push_back(0.0781);
        p_145.push_back(0.00619);

        std::vector<float> q_145;
        q_145.push_back(-2.173);
        q_145.push_back(0.04044);
        q_145.push_back(3.293);

        p_coeff.insert(std::make_pair(F145, p_145));
        q_coeff.insert(std::make_pair(F145, q_145));

        // FM 146

        int F146 = 146;
        std::vector<float> p_146;
        p_146.push_back(0.2664);
        p_146.push_back(0.07788);
        p_146.push_back(0.01707);

        std::vector<float> q_146;
        q_146.push_back(-1.698);
        q_146.push_back(0.03934);
        q_146.push_back(2.652);

        p_coeff.insert(std::make_pair(F146, p_146));
        q_coeff.insert(std::make_pair(F146, q_146));

        // FM 146

        int F147 = 147;
        std::vector<float> p_147;
        p_147.push_back(0.1651);
        p_147.push_back(0.07791);
        p_147.push_back(0.009743);

        std::vector<float> q_147;
        q_147.push_back(-2.084);
        q_147.push_back(0.03998);
        q_147.push_back(3.193);

        p_coeff.insert(std::make_pair(F147, p_147));
        q_coeff.insert(std::make_pair(F147, q_147));

        // FM 148

        int F148 = 148;
        std::vector<float> p_148;
        p_148.push_back(0.2704);
        p_148.push_back(0.07765);
        p_148.push_back(0.0141);

        std::vector<float> q_148;
        q_148.push_back(-1.978);
        q_148.push_back(0.03601);
        q_148.push_back(2.975);

        p_coeff.insert(std::make_pair(F148, p_148));
        q_coeff.insert(std::make_pair(F148, q_148));

        // FM 149

        int F149 = 149;
        std::vector<float> p_149;
        p_149.push_back(0.1391);
        p_149.push_back(0.07771);
        p_149.push_back(0.007329);

        std::vector<float> q_149;
        q_149.push_back(-2.626);
        q_149.push_back(0.03657);
        q_149.push_back(3.945);

        p_coeff.insert(std::make_pair(F149, p_149));
        q_coeff.insert(std::make_pair(F149, q_149));

        // FM 161

        int F161 = 161;
        std::vector<float> p_161;
        p_161.push_back(3180);
        p_161.push_back(1.235);
        p_161.push_back(3.332);

        std::vector<float> q_161;
        q_161.push_back(-0.1562);
        q_161.push_back(0.1467);
        q_161.push_back(0.4505);

        p_coeff.insert(std::make_pair(F161, p_161));
        q_coeff.insert(std::make_pair(F161, q_161));

        // FM 162

        int F162 = 162;
        std::vector<float> p_162;
        p_162.push_back(1.631);
        p_162.push_back(0.2024);
        p_162.push_back(0.05519);

        std::vector<float> q_162;
        q_162.push_back(-0.9908);
        q_162.push_back(0.08943);
        q_162.push_back(1.472);

        p_coeff.insert(std::make_pair(F162, p_162));
        q_coeff.insert(std::make_pair(F162, q_162));

        // FM 163

        int F163 = 163;
        std::vector<float> p_163;
        p_163.push_back(0.3075);
        p_163.push_back(0.09702);
        p_163.push_back(0.01307);

        std::vector<float> q_163;
        q_163.push_back(-1.705);
        q_163.push_back(0.04277);
        q_163.push_back(2.452);

        p_coeff.insert(std::make_pair(F163, p_163));
        q_coeff.insert(std::make_pair(F163, q_163));

        // FM 164

        int F164 = 164;
        std::vector<float> p_164;
        p_164.push_back(0.4047);
        p_164.push_back(0.0793);
        p_164.push_back(0.01199);

        std::vector<float> q_164;
        q_164.push_back(-2.052);
        q_164.push_back(0.02663);
        q_164.push_back(2.765);

        p_coeff.insert(std::make_pair(F164, p_164));
        q_coeff.insert(std::make_pair(F164, q_164));

        // FM 165

        int F165 = 165;
        std::vector<float> p_165;
        p_165.push_back(0.6448);
        p_165.push_back(0.07668);
        p_165.push_back(0.03998);

        std::vector<float> q_165;
        q_165.push_back(-1.521);
        q_165.push_back(0.03838);
        q_165.push_back(2.417);

        p_coeff.insert(std::make_pair(F165, p_165));
        q_coeff.insert(std::make_pair(F165, q_165));

        // FM 181

        int F181 = 181;
        std::vector<float> p_181;
        p_181.push_back(1800);
        p_181.push_back(1.178);
        p_181.push_back(4.999);

        std::vector<float> q_181;
        q_181.push_back(0.0);
        q_181.push_back(0.0);
        q_181.push_back(0.0);

        p_coeff.insert(std::make_pair(F181, p_181));
        q_coeff.insert(std::make_pair(F181, q_181));

        // FM 182

        int F182 = 182;
        std::vector<float> p_182;
        p_182.push_back(38.8);
        p_182.push_back(0.5491);
        p_182.push_back(1.989);

        std::vector<float> q_182;
        q_182.push_back(-0.2492);
        q_182.push_back(0.1422);
        q_182.push_back(0.5509);

        p_coeff.insert(std::make_pair(F182, p_182));
        q_coeff.insert(std::make_pair(F182, q_182));

        // FM 183

        int F183 = 183;
        std::vector<float> p_183;
        p_183.push_back(11.37);
        p_183.push_back(0.3397);
        p_183.push_back(1.244);

        std::vector<float> q_183;
        q_183.push_back(-0.3582);
        q_183.push_back(0.1543);
        q_183.push_back(0.6369);

        p_coeff.insert(std::make_pair(F183, p_183));
        q_coeff.insert(std::make_pair(F183, q_183));

        // FM 185

        int F185 = 185;
        std::vector<float> p_185;
        p_185.push_back(5.163);
        p_185.push_back(0.2396);
        p_185.push_back(0.1943);

        std::vector<float> q_185;
        q_185.push_back(-0.6817);
        q_185.push_back(0.1007);
        q_185.push_back(1.064);

        p_coeff.insert(std::make_pair(F185, p_185));
        q_coeff.insert(std::make_pair(F185, q_185));

        // FM 186

        int F186 = 186;
        std::vector<float> p_186;
        p_186.push_back(2.555);
        p_186.push_back(0.171);
        p_186.push_back(0.07786);

        std::vector<float> q_186;
        q_186.push_back(-0.9478);
        q_186.push_back(0.07391);
        q_186.push_back(1.375);

        p_coeff.insert(std::make_pair(F186, p_186));
        q_coeff.insert(std::make_pair(F186, q_186));

        // FM 188

        int F188 = 188;
        std::vector<float> p_188;
        p_188.push_back(1.294);
        p_188.push_back(0.1085);
        p_188.push_back(0.04999);

        std::vector<float> q_188;
        q_188.push_back(-1.184);
        q_188.push_back(0.04144);
        q_188.push_back(1.768);

        p_coeff.insert(std::make_pair(F188, p_188));
        q_coeff.insert(std::make_pair(F188, q_188));

        // FM 189

        int F189 = 189;
        std::vector<float> p_189;
        p_189.push_back(0.534);
        p_189.push_back(0.07749);
        p_189.push_back(0.02216);

        std::vector<float> q_189;
        q_189.push_back(-1.624);
        q_189.push_back(0.02893);
        q_189.push_back(2.369);

        p_coeff.insert(std::make_pair(F189, p_189));
        q_coeff.insert(std::make_pair(F189, q_189));
    }

    if (scenario == 4)
    {
        // Populate them
        // FM 101
        int F101 = 101;
        std::vector<float> p_101;
        std::vector<float> q_101;
        p_101.push_back(0.);
        p_101.push_back(0.);
        p_101.push_back(-1.);
        q_101.push_back(0.);
        q_101.push_back(0.);
        q_101.push_back(0.);
        p_coeff.insert(std::make_pair(F101, p_101));
        q_coeff.insert(std::make_pair(F101, q_101));

        // FM 102
        int F102 = 102;
        std::vector<float> p_102;
        std::vector<float> q_102;
        p_102.push_back(0.);
        p_102.push_back(0.);
        p_102.push_back(-1.);
        q_102.push_back(0.);
        q_102.push_back(0.);
        q_102.push_back(0.);
        p_coeff.insert(std::make_pair(F102, p_102));
        q_coeff.insert(std::make_pair(F102, q_102));

        // FM 103
        int F103 = 103;
        std::vector<float> p_103;
        p_103.push_back(1.02e+04);
        p_103.push_back(2.51);
        p_103.push_back(10);

        std::vector<float> q_103;
        q_103.push_back(-0.3984);
        q_103.push_back(0.6339);
        q_103.push_back(0.3173);

        p_coeff.insert(std::make_pair(F103, p_103));
        q_coeff.insert(std::make_pair(F103, q_103));

        // FM 104
        int F104 = 104;
        std::vector<float> p_104;
        p_104.push_back(1706);
        p_104.push_back(5.835);
        p_104.push_back(4.999);

        std::vector<float> q_104;
        q_104.push_back(-0.3984);
        q_104.push_back(0.6331);
        q_104.push_back(0.3173);

        p_coeff.insert(std::make_pair(F104, p_104));
        q_coeff.insert(std::make_pair(F104, q_104));

        // FM 105
        int F105 = 105;
        std::vector<float> p_105;
        p_105.push_back(24.51);
        p_105.push_back(0.6818);
        p_105.push_back(1.665);

        std::vector<float> q_105;
        q_105.push_back(-0.1528);
        q_105.push_back(0.4083);
        q_105.push_back(0.4483);

        p_coeff.insert(std::make_pair(F105, p_105));
        q_coeff.insert(std::make_pair(F105, q_105));

        // FM 106
        int F106 = 106;
        std::vector<float> p_106;
        std::vector<float> q_106;
        p_106.push_back(0.);
        p_106.push_back(0.);
        p_106.push_back(-1.);
        q_106.push_back(0.);
        q_106.push_back(0.);
        q_106.push_back(0.);
        p_coeff.insert(std::make_pair(F106, p_106));
        q_coeff.insert(std::make_pair(F106, q_106));

        // FM 107
        int F107 = 107;
        std::vector<float> p_107;
        p_107.push_back(8.706);
        p_107.push_back(0.397);
        p_107.push_back(0.3983);

        std::vector<float> q_107;
        q_107.push_back(-0.5259);
        q_107.push_back(0.19);
        q_107.push_back(0.7787);

        p_coeff.insert(std::make_pair(F107, p_107));
        q_coeff.insert(std::make_pair(F107, q_107));

        // FM 108
        int F108 = 108;
        std::vector<float> p_108;
        p_108.push_back(29.63);
        p_108.push_back(0.6425);
        p_108.push_back(1.246);

        std::vector<float> q_108;
        q_108.push_back(-0.2634);
        q_108.push_back(0.2268);
        q_108.push_back(0.55);

        p_coeff.insert(std::make_pair(F108, p_108));
        q_coeff.insert(std::make_pair(F108, q_108));

        // FM 121

        int F121 = 121;
        std::vector<float> p_121;
        p_121.push_back(1.02e+04);
        p_121.push_back(2.505);
        p_121.push_back(10);

        std::vector<float> q_121;
        q_121.push_back(-0.3942);
        q_121.push_back(0.6206);
        q_121.push_back(0.3174);

        p_coeff.insert(std::make_pair(F121, p_121));
        q_coeff.insert(std::make_pair(F121, q_121));

        // FM 122

        int F122 = 122;
        std::vector<float> p_122;
        p_122.push_back(25.02);
        p_122.push_back(0.7935);
        p_122.push_back(2);

        std::vector<float> q_122;
        q_122.push_back(-0.153);
        q_122.push_back(0.4129);
        q_122.push_back(0.4483);

        p_coeff.insert(std::make_pair(F122, p_122));
        q_coeff.insert(std::make_pair(F122, q_122));

        // FM 123

        int F123 = 123;
        std::vector<float> p_123;
        p_123.push_back(2423);
        p_123.push_back(5.898);
        p_123.push_back(3.333);

        std::vector<float> q_123;
        q_123.push_back(-0.271);
        q_123.push_back(0.2323);
        q_123.push_back(0.4489);

        p_coeff.insert(std::make_pair(F123, p_123));
        q_coeff.insert(std::make_pair(F123, q_123));

        // FM 124

        int F124 = 124;
        std::vector<float> p_124;
        p_124.push_back(3.313);
        p_124.push_back(0.1361);
        p_124.push_back(0.1345);

        std::vector<float> q_124;
        q_124.push_back(-0.8735);
        q_124.push_back(0.06301);
        q_124.push_back(1.305);

        p_coeff.insert(std::make_pair(F124, p_124));
        q_coeff.insert(std::make_pair(F124, q_124));

        // FM 142

        int F142 = 142;
        std::vector<float> p_142;
        p_142.push_back(23.95);
        p_142.push_back(0.3007);
        p_142.push_back(0.9045);

        std::vector<float> q_142;
        q_142.push_back(-0.4438);
        q_142.push_back(0.1155);
        q_142.push_back(0.7152);

        p_coeff.insert(std::make_pair(F142, p_142));
        q_coeff.insert(std::make_pair(F142, q_142));

        // FM 143

        int F143 = 143;
        std::vector<float> p_143;
        p_143.push_back(8.823);
        p_143.push_back(0.2347);
        p_143.push_back(0.3672);

        std::vector<float> q_143;
        q_143.push_back(-0.602);
        q_143.push_back(0.1209);
        q_143.push_back(0.9543);

        p_coeff.insert(std::make_pair(F143, p_143));
        q_coeff.insert(std::make_pair(F143, q_143));

        // FM 144

        int F144 = 144;
        std::vector<float> p_144;
        p_144.push_back(6.334);
        p_144.push_back(0.3903);
        p_144.push_back(0.2486);

        std::vector<float> q_144;
        q_144.push_back(-0.5751);
        q_144.push_back(0.1717);
        q_144.push_back(0.8994);

        p_coeff.insert(std::make_pair(F144, p_144));
        q_coeff.insert(std::make_pair(F144, q_144));

        // FM 145

        int F145 = 145;
        std::vector<float> p_145;
        p_145.push_back(0.7965);
        p_145.push_back(0.168);
        p_145.push_back(0.04058);

        std::vector<float> q_145;
        q_145.push_back(-1.156);
        q_145.push_back(0.08584);
        q_145.push_back(1.756);

        p_coeff.insert(std::make_pair(F145, p_145));
        q_coeff.insert(std::make_pair(F145, q_145));

        // FM 146

        int F146 = 146;
        std::vector<float> p_146;
        p_146.push_back(0.3421);
        p_146.push_back(0.07793);
        p_146.push_back(0.02181);

        std::vector<float> q_146;
        q_146.push_back(-1.558);
        q_146.push_back(0.0402);
        q_146.push_back(2.452);

        p_coeff.insert(std::make_pair(F146, p_146));
        q_coeff.insert(std::make_pair(F146, q_146));

        // FM 146

        int F147 = 147;
        std::vector<float> p_147;
        p_147.push_back(0.9702);
        p_147.push_back(0.1314);
        p_147.push_back(0.05167);

        std::vector<float> q_147;
        q_147.push_back(-1.118);
        q_147.push_back(0.0653);
        q_147.push_back(1.746);

        p_coeff.insert(std::make_pair(F147, p_147));
        q_coeff.insert(std::make_pair(F147, q_147));

        // FM 148

        int F148 = 148;
        std::vector<float> p_148;
        p_148.push_back(1.44);
        p_148.push_back(0.1175);
        p_148.push_back(0.07096);

        std::vector<float> q_148;
        q_148.push_back(-1.079);
        q_148.push_back(0.05247);
        q_148.push_back(1.652);

        p_coeff.insert(std::make_pair(F148, p_148));
        q_coeff.insert(std::make_pair(F148, q_148));

        // FM 149

        int F149 = 149;
        std::vector<float> p_149;
        p_149.push_back(0.4281);
        p_149.push_back(0.07778);
        p_149.push_back(0.02246);

        std::vector<float> q_149;
        q_149.push_back(-1.631);
        q_149.push_back(0.03661);
        q_149.push_back(2.479);

        p_coeff.insert(std::make_pair(F149, p_149));
        q_coeff.insert(std::make_pair(F149, q_149));

        // FM 161

        int F161 = 161;
        std::vector<float> p_161;
        p_161.push_back(1819);
        p_161.push_back(1.18);
        p_161.push_back(4.999);

        std::vector<float> q_161;
        q_161.push_back(-0.3084);
        q_161.push_back(6.721);
        q_161.push_back(0.3162);

        p_coeff.insert(std::make_pair(F161, p_161));
        q_coeff.insert(std::make_pair(F161, q_161));

        // FM 162

        int F162 = 162;
        std::vector<float> p_162;
        p_162.push_back(2.199);
        p_162.push_back(0.2162);
        p_162.push_back(0.07223);

        std::vector<float> q_162;
        q_162.push_back(-0.9267);
        q_162.push_back(0.09552);
        q_162.push_back(1.36);

        p_coeff.insert(std::make_pair(F162, p_162));
        q_coeff.insert(std::make_pair(F162, q_162));

        // FM 163

        int F163 = 163;
        std::vector<float> p_163;
        p_163.push_back(4.902);
        p_163.push_back(0.2927);
        p_163.push_back(0.1805);

        std::vector<float> q_163;
        q_163.push_back(-0.6625);
        q_163.push_back(0.1263);
        q_163.push_back(1.058);

        p_coeff.insert(std::make_pair(F163, p_163));
        q_coeff.insert(std::make_pair(F163, q_163));

        // FM 164

        int F164 = 164;
        std::vector<float> p_164;
        std::vector<float> q_164;
        p_164.push_back(0.);
        p_164.push_back(0.);
        p_164.push_back(-1.);
        q_164.push_back(0.);
        q_164.push_back(0.);
        q_164.push_back(0.);
        p_coeff.insert(std::make_pair(F164, p_164));
        q_coeff.insert(std::make_pair(F164, q_164));

        // FM 165

        int F165 = 165;
        std::vector<float> p_165;
        p_165.push_back(0.817);
        p_165.push_back(0.07709);
        p_165.push_back(0.05013);

        std::vector<float> q_165;
        q_165.push_back(-1.425);
        q_165.push_back(0.03706);
        q_165.push_back(2.275);

        p_coeff.insert(std::make_pair(F165, p_165));
        q_coeff.insert(std::make_pair(F165, q_165));

        // FM 181

        int F181 = 181;
        std::vector<float> p_181;
        p_181.push_back(1804);
        p_181.push_back(1.178);
        p_181.push_back(4.999);

        std::vector<float> q_181;
        q_181.push_back(0.0);
        q_181.push_back(0.0);
        q_181.push_back(0.0);

        p_coeff.insert(std::make_pair(F181, p_181));
        q_coeff.insert(std::make_pair(F181, q_181));

        // FM 182

        int F182 = 182;
        std::vector<float> p_182;
        p_182.push_back(26.13);
        p_182.push_back(0.5009);
        p_182.push_back(2.488);

        std::vector<float> q_182;
        q_182.push_back(-0.1525);
        q_182.push_back(0.4025);
        q_182.push_back(0.4484);

        p_coeff.insert(std::make_pair(F182, p_182));
        q_coeff.insert(std::make_pair(F182, q_182));

        // FM 183

        int F183 = 183;
        std::vector<float> p_183;
        p_183.push_back(19.31);
        p_183.push_back(0.4546);
        p_183.push_back(1.428);

        std::vector<float> q_183;
        q_183.push_back(-0.2634);
        q_183.push_back(0.2268);
        q_183.push_back(0.55);

        p_coeff.insert(std::make_pair(F183, p_183));
        q_coeff.insert(std::make_pair(F183, q_183));

        // FM 185

        int F185 = 185;
        std::vector<float> p_185;
        p_185.push_back(5.518);
        p_185.push_back(0.2432);
        p_185.push_back(0.2307);

        std::vector<float> q_185;
        q_185.push_back(-0.6166);
        q_185.push_back(0.1085);
        q_185.push_back(1.011);

        p_coeff.insert(std::make_pair(F185, p_185));
        q_coeff.insert(std::make_pair(F185, q_185));

        // FM 186

        int F186 = 186;
        std::vector<float> p_186;
        p_186.push_back(2.956);
        p_186.push_back(0.1765);
        p_186.push_back(0.09361);

        std::vector<float> q_186;
        q_186.push_back(-0.8538);
        q_186.push_back(0.07918);
        q_186.push_back(1.292);

        p_coeff.insert(std::make_pair(F186, p_186));
        q_coeff.insert(std::make_pair(F186, q_186));

        // FM 188

        int F188 = 188;
        std::vector<float> p_188;
        p_188.push_back(1.736);
        p_188.push_back(0.1188);
        p_188.push_back(0.06593);

        std::vector<float> q_188;
        q_188.push_back(-1.076);
        q_188.push_back(0.04976);
        q_188.push_back(1.599);

        p_coeff.insert(std::make_pair(F188, p_188));
        q_coeff.insert(std::make_pair(F188, q_188));

        // FM 189

        int F189 = 189;
        std::vector<float> p_189;
        p_189.push_back(0.6251);
        p_189.push_back(0.07753);
        p_189.push_back(0.02607);

        std::vector<float> q_189;
        q_189.push_back(-1.505);
        q_189.push_back(0.03052);
        q_189.push_back(2.216);

        p_coeff.insert(std::make_pair(F189, p_189));
        q_coeff.insert(std::make_pair(F189, q_189));
    }

    // Fuel Model Parameters for Crown Fire
    std::vector<float> fp_101;
    fp_101.push_back(0.1 + 0.0 + 0.0 + 0.3 + 0.0);
    fp_101.push_back(8000);
    fm_parameters.insert(std::make_pair(101, fp_101));

    std::vector<float> fp_102;
    fp_102.push_back(0.1 + 0.0 + 0.0 + 1.0 + 0.0);
    fp_102.push_back(8000);
    fm_parameters.insert(std::make_pair(102, fp_102));

    std::vector<float> fp_103;
    fp_103.push_back(0.1 + 0.4 + 0.0 + 1.5 + 0.0);
    fp_103.push_back(8000);
    fm_parameters.insert(std::make_pair(103, fp_103));

    std::vector<float> fp_104;
    fp_104.push_back(0.25 + 0.0 + 0.0 + 1.9 + 0.0);
    fp_104.push_back(8000);
    fm_parameters.insert(std::make_pair(104, fp_104));

    std::vector<float> fp_105;
    fp_105.push_back(0.4 + 0.0 + 0.0 + 2.5 + 0.0);
    fp_105.push_back(8000);
    fm_parameters.insert(std::make_pair(105, fp_105));

    std::vector<float> fp_106;
    fp_106.push_back(0.1 + 0.0 + 0.0 + 3.4 + 0.0);
    fp_106.push_back(9000);
    fm_parameters.insert(std::make_pair(106, fp_106));

    std::vector<float> fp_107;
    fp_107.push_back(1.0 + 0.0 + 0.0 + 5.4 + 0.0);
    fp_107.push_back(8000);
    fm_parameters.insert(std::make_pair(107, fp_107));

    std::vector<float> fp_108;
    fp_108.push_back(0.5 + 1.0 + 0.0 + 7.3 + 0.0);
    fp_108.push_back(8000);
    fm_parameters.insert(std::make_pair(108, fp_108));

    std::vector<float> fp_121;
    fp_121.push_back(0.2 + 0.0 + 0.0 + 0.5 + 0.65);
    fp_121.push_back(8000);
    fm_parameters.insert(std::make_pair(121, fp_121));

    std::vector<float> fp_122;
    fp_122.push_back(0.5 + 0.5 + 0.0 + 0.6 + 1.0);
    fp_122.push_back(8000);
    fm_parameters.insert(std::make_pair(122, fp_122));

    std::vector<float> fp_123;
    fp_123.push_back(0.3 + 0.25 + 0.0 + 1.45 + 1.25);
    fp_123.push_back(8000);
    fm_parameters.insert(std::make_pair(123, fp_123));

    std::vector<float> fp_124;
    fp_124.push_back(1.9 + 0.3 + 0.1 + 3.4 + 7.1);
    fp_124.push_back(8000);
    fm_parameters.insert(std::make_pair(124, fp_124));

    std::vector<float> fp_142;
    fp_142.push_back(1.35 + 2.4 + 0.75 + 0.0 + 3.85);
    fp_142.push_back(8000);
    fm_parameters.insert(std::make_pair(142, fp_142));

    std::vector<float> fp_143;
    fp_143.push_back(0.45 + 3.0 + 0.0 + 0.0 + 6.2);
    fp_143.push_back(8000);
    fm_parameters.insert(std::make_pair(143, fp_143));

    std::vector<float> fp_144;
    fp_144.push_back(0.85 + 1.15 + 0.2 + 0.0 + 2.55);
    fp_144.push_back(8000);
    fm_parameters.insert(std::make_pair(144, fp_144));

    std::vector<float> fp_145;
    fp_145.push_back(3.6 + 2.1 + 0.0 + 0.0 + 2.9);
    fp_145.push_back(8000);
    fm_parameters.insert(std::make_pair(145, fp_145));

    std::vector<float> fp_146;
    fp_146.push_back(2.9 + 1.45 + 0.0 + 0.0 + 1.4);
    fp_146.push_back(8000);
    fm_parameters.insert(std::make_pair(146, fp_146));

    std::vector<float> fp_147;
    fp_147.push_back(3.5 + 5.3 + 2.2 + 0.0 + 3.4);
    fp_147.push_back(8000);
    fm_parameters.insert(std::make_pair(147, fp_147));

    std::vector<float> fp_148;
    fp_148.push_back(2.05 + 3.4 + 0.85 + 0.0 + 4.35);
    fp_148.push_back(8000);
    fm_parameters.insert(std::make_pair(148, fp_148));

    std::vector<float> fp_149;
    fp_149.push_back(4.5 + 2.45 + 0.0 + 1.55 + 7.0);
    fp_149.push_back(8000);
    fm_parameters.insert(std::make_pair(149, fp_149));

    std::vector<float> fp_161;
    fp_161.push_back(0.2 + 0.9 + 1.5 + 0.2 + 0.9);
    fp_161.push_back(8000);
    fm_parameters.insert(std::make_pair(161, fp_161));

    std::vector<float> fp_162;
    fp_162.push_back(0.95 + 1.8 + 1.25 + 0.0 + 0.2);
    fp_162.push_back(8000);
    fm_parameters.insert(std::make_pair(162, fp_162));

    std::vector<float> fp_163;
    fp_163.push_back(1.1 + 0.15 + 0.25 + 0.65 + 1.1);
    fp_163.push_back(8000);
    fm_parameters.insert(std::make_pair(163, fp_163));

    std::vector<float> fp_164;
    fp_164.push_back(4.5 + 0.0 + 0.0 + 0.0 + 2.0);
    fp_164.push_back(8000);
    fm_parameters.insert(std::make_pair(164, fp_164));

    std::vector<float> fp_165;
    fp_165.push_back(4.0 + 4.0 + 3.0 + 0.0 + 3.0);
    fp_165.push_back(8000);
    fm_parameters.insert(std::make_pair(165, fp_165));

    std::vector<float> fp_181;
    fp_181.push_back(1.0 + 2.2 + 3.6 + 0.0 + 0.0);
    fp_181.push_back(8000);
    fm_parameters.insert(std::make_pair(181, fp_181));

    std::vector<float> fp_182;
    fp_182.push_back(1.4 + 2.3 + 2.2 + 0.0 + 0.0);
    fp_182.push_back(8000);
    fm_parameters.insert(std::make_pair(182, fp_182));

    std::vector<float> fp_183;
    fp_183.push_back(0.5 + 2.2 + 2.8 + 0.0 + 0.0);
    fp_183.push_back(8000);
    fm_parameters.insert(std::make_pair(183, fp_183));

    std::vector<float> fp_185;
    fp_185.push_back(1.15 + 2.5 + 4.4 + 0.0 + 0.0);
    fp_185.push_back(8000);
    fm_parameters.insert(std::make_pair(185, fp_185));

    std::vector<float> fp_186;
    fp_186.push_back(2.4 + 1.2 + 1.2 + 0.0 + 0.0);
    fp_186.push_back(8000);
    fm_parameters.insert(std::make_pair(186, fp_186));

    std::vector<float> fp_188;
    fp_188.push_back(5.8 + 1.4 + 1.1 + 0.0 + 0.0);
    fp_188.push_back(8000);
    fm_parameters.insert(std::make_pair(188, fp_188));

    std::vector<float> fp_189;
    fp_189.push_back(6.65 + 3.3 + 4.15 + 0.0 + 0.0);
    fp_189.push_back(8000);
    fm_parameters.insert(std::make_pair(189, fp_189));
}

float
rate_of_spread_s(inputs* data, fuel_coefs* ptr, main_outs* at)
{
    float p1, p2, p3, ws;

    p1 = p_coeff[data->nftype][0];
    p2 = p_coeff[data->nftype][1];
    p3 = p_coeff[data->nftype][2];
    // se = slope_effect(inp);
    ws = data->ws;
    at->rss = 1.0 / (p1 * exp(-p2 * ws) + p3);

    return at->rss * (at->rss >= 0);
}

float
flankfire_ros_s(float ros, float bros, float lb)
{
    return ((ros + bros) / (lb * 2.0));
}

/* ----------------- Length-to-Breadth --------------------------*/
float
l_to_b(float ws)
{
    // if(strncmp(ft,"O1",2)==0)return( ws<1.0 ? 1.0 : (1.1*pow(ws,0.464)));
    float alpha, beta, factor;
    alpha = 0.2566;
    beta = -0.1548;
    factor = 1000.0 / 3600.0;
    return pow((0.936 * exp(alpha * factor * ws) + 0.461 * exp(beta * factor * ws) - 0.397), 0.45);
}

/* ----------------- Back Rate of Spread --------------------------*/
float
backfire_ros_s(main_outs* at, snd_outs* sec)
{
    float hb, bros, lb;
    // lb = l_to_b(data->fueltype,at->wsv);
    lb = sec->lb;
    hb = (lb + sqrt(pow(lb, 2) - 1.0)) / (lb - sqrt(pow(lb, 2) - 1.0));

    bros = at->rss / hb;

    return bros * (bros >= 0);
}

float
flame_length(inputs* data, fuel_coefs* ptr)
{
    float q1, q2, q3, fl, ws;

    ws = data->ws;
    q1 = q_coeff[data->nftype][0];
    q2 = q_coeff[data->nftype][1];
    q3 = q_coeff[data->nftype][2];

    fl = pow(q1 * exp(-q2 * ws) + q3, 2);
    return fl;
}

/**
 * @brief Calculates the flame length of a cell when there is crown fire.
 * @param intensity Byram intensity for crown fires
 * @return the flame length
 */

float
crown_flame_length(float intensity)
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

float
angleFL(inputs* data, fuel_coefs* ptr)
{
    float angle, fl, y, ws;
    ws = data->ws;
    fl = flame_length(data, ptr);
    y = 10.0 / 36.0 * ws;

    angle = atan(2.24 * sqrt(fl / pow(y, 2)));
    return angle;
}

float
flame_height(inputs* data, fuel_coefs* ptr)
{
    float fh, phi;
    phi = angleFL(data, ptr);
    fh = flame_length(data, ptr) * sin(phi);
    return fh;
}

float
byram_intensity(main_outs* at, fuel_coefs* ptr)
{
    float fl, ib;
    fl = at->fl;
    ib = 259.833 * pow(fl, 2.174);
    ib = std::ceil(ib * 100.0) / 100.0;
    return ib;
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
crown_byram_intensity(main_outs* at, inputs* data)
{
    float canopy_height = data->tree_height - data->cbh;
    if (canopy_height < 0)
    {
        throw std::runtime_error("Tree height is lower than canopy base height, "
                                 "please provide valid files.");
    }
    return std::ceil((HEAT_YIELD / 60) * data->cbd * canopy_height * at->ros_active * 100.0) / 100.0;
}

int
fmc_scen(inputs* data)
{
    int fmc;
    fmc = data->FMC;
    return fmc;
}

bool
fire_type(inputs* data, main_outs* at)
{
    float intensity, critical_intensity, cbh;
    int fmc;
    bool crownFire = false;

    intensity = at->sfi;
    cbh = data->cbh;
    fmc = fmc_scen(data);
    critical_intensity = pow((0.01 * cbh * (460 + 25.9 * fmc)), 1.5);

    if ((intensity > critical_intensity) && cbh != 0)
        crownFire = true;

    return crownFire;
}

float
rate_of_spread10(inputs* data, arguments* args)
{
    // FM 10 coef
    float p1 = 0.2802, p2 = 0.07786, p3 = 0.01123;
    float ros, ros10, ws, ffros, fcbd, fccf;

    ffros = args->ROS10Factor;
    fcbd = args->CBDFactor;
    fccf = args->CCFFactor;

    ws = data->ws;
    ros10 = 1. / (p1 * exp(-p2 * ws * 0.4) + p3);

    ros = ffros * ros10 + fccf * data->ccf + fcbd * data->cbd;

    return (ros);
}

float
final_rate_of_spread10(inputs* data, main_outs* at)
{
    float ros_active, ros_final, ros;
    ros = at->rss;
    ros_active = at->ros_active;
    ros_final = ros + at->cfb * (ros_active - ros);
    return (ros_final);
}

float
backfire_ros10_s(fire_struc* hptr, snd_outs* sec)
{
    float hb, bros, lb;
    lb = sec->lb;
    hb = (lb + sqrt(pow(lb, 2) - 1.0)) / (lb - sqrt(pow(lb, 2) - 1.0));

    bros = hptr->ros / hb;

    return bros;
}

float
crownfractionburn(inputs* data, main_outs* at)
{  // generar output de cfb
    float a, cbd, ros, ros0, H, wa, i0, cbh, FMC, cfb;
    FMC = fmc_scen(data);
    ;  // modificar para ingresar manualmente
    cbh = data->cbh;
    i0 = pow((0.01 * cbh * (460 + 25.9 * FMC)), 1.5);
    wa = fm_parameters[data->nftype][0];
    H = fm_parameters[data->nftype][1];
    cbd = data->cbd;
    ros0 = 60 * i0 / (H * wa);
    ros = at->rss;
    if (cbd != 0)
    {
        a = -log(0.1) / (0.9 * (3.0 / cbd - ros0));
        // a=0.23;
    }
    else
    {
        a = 0.23;
    }
    cfb = 1 - exp(-a * (ros - ros0));
    if (cfb < 0)
    {
        cfb = 0;
    }
    return cfb;
}

bool
checkActive(inputs* data, main_outs* at)  // En s&b se usa fm10
{
    float rac, cbd, H, wa, i0, cbh, fmc;
    bool active;
    // rac = at->ros_active;
    fmc = fmc_scen(data);
    ;  // modificar para ingresar manualmente
    cbh = data->cbh;
    i0 = pow((0.01 * cbh * (460 + 25.9 * fmc)), 1.5);
    wa = fm_parameters[data->nftype][0];
    H = fm_parameters[data->nftype][1];
    cbd = data->cbd;
    rac = 60 * i0 / (H * wa);  // rate active crown

    active = cbd * rac >= 3;
    return active;
}

void
calculate_s(inputs* data,
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
    initialize_coeff(args->scenario);

    // Aux
    float ros, bros, lb, fros;
    bool crownFire = false;
    // Populate fuel coefs struct
    // ptr->fueltype = data->fueltype;
    if (args->verbose)
    {
        std::cout << "Populate fuel types " << std::endl;
        std::cout << "NfTypes:" << data->nftype << std::endl;
        std::cout << "scen:" << args->scenario << std::endl;
    }
    ptr->p1 = p_coeff[data->nftype][0];
    ptr->p2 = p_coeff[data->nftype][1];
    ptr->p3 = p_coeff[data->nftype][2];
    ptr->q1 = q_coeff[data->nftype][0];
    ptr->q2 = q_coeff[data->nftype][1];
    ptr->q3 = q_coeff[data->nftype][2];
    ptr->nftype = data->nftype;

    // Step 1: Calculate HROS (surface)
    at->rss = rate_of_spread_s(data, ptr, at);
    hptr->rss = at->rss;

    // Step 2: Calculate Length-to-breadth
    sec->lb = l_to_b(data->ws);

    // Step 3: Calculate BROS (surface)
    bptr->rss = backfire_ros_s(at, sec);

    // Step 4: Calculate central FROS (surface)
    fptr->rss = flankfire_ros_s(hptr->rss, bptr->rss, sec->lb);

    // Step 5: Ellipse components
    at->a = (hptr->rss + bptr->rss) / 2.;
    at->b = (hptr->rss + bptr->rss) / (2. * sec->lb);
    at->c = (hptr->rss - bptr->rss) / 2.;

    // Step 6: Flame Length
    at->fl = flame_length(data, ptr);

    // Step 7: Flame angle
    at->angle = angleFL(data, ptr);

    // Step 8: Flame Height
    at->fh = flame_height(data, ptr);

    // Step 9: Byram Intensity
    at->sfi = byram_intensity(at, ptr);

    // Step 10: Criterion for Crown Fire Initiation (no init if user does not
    // want to include it)
    if (args->AllowCROS && data->cbh != 0 && data->cbd != 0)
    {
        if (activeCrown)
        {
            at->ros_active = rate_of_spread10(data, args);
            if (!checkActive(data, at))
            {
                activeCrown = false;
            }
        }
        else
        {
            crownFire = fire_type(data, at);
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
        at->ros_active = rate_of_spread10(data, args);
        at->cfb = crownfractionburn(data, at);

        hptr->ros = final_rate_of_spread10(data, at);
        at->rss = hptr->ros;
        bptr->ros = backfire_ros10_s(hptr, sec);
        fptr->ros = flankfire_ros_s(hptr->ros, bptr->ros, sec->lb);
        if (args->verbose)
        {
            cout << "hptr->ros = " << hptr->ros << "\n";
            cout << "bptr->ros = " << bptr->ros << "\n";
            cout << "fptr->ros = " << fptr->ros << "\n";
        }
        at->crown_intensity = crown_byram_intensity(at, data);
        at->crown_flame_length = crown_flame_length(at->crown_intensity);

        at->a = (hptr->ros + bptr->ros) / 2.;
        at->b = (hptr->ros + bptr->ros) / (2. * sec->lb);
        at->c = (hptr->ros - bptr->rss) / 2;
        at->crown = 1;
        activeCrown = true;
    }
    else if (activeCrown)
    {
        at->cfb = crownfractionburn(data,
                                    at);  // lo calculamos igual porque lo necesitamos para el output
        hptr->ros = at->ros_active;
        at->rss = hptr->ros;
        bptr->ros = backfire_ros10_s(hptr, sec);
        fptr->ros = flankfire_ros_s(hptr->ros, bptr->ros, sec->lb);
        at->crown_intensity = crown_byram_intensity(at, data);
        at->crown_flame_length = crown_flame_length(at->crown_intensity);

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
        at->cfb = 0;
        at->crown_flame_length = 0;
        at->crown_intensity = 0;
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
    // if (hptr->ros>100){
    // cout << "hptr->rss = " << hptr->ros << "\n";

    //}

    if (args->verbose)
    {
        cout << "--------------- Inputs --------------- \n";
        cout << "ws = " << data->ws << "\n";
        cout << "coef data->cbh = " << data->cbh << "\n";
        cout << "coef ptr->p1 = " << ptr->p1 << "\n";
        cout << "coef ptr->p2 = " << ptr->p2 << "\n";
        cout << "coef ptr->p3 = " << ptr->p3 << "\n";
        cout << "coef ptr->q1 = " << ptr->q1 << "\n";
        cout << "coef ptr->q2 = " << ptr->q2 << "\n";
        cout << "coef ptr->q3 = " << ptr->q3 << "\n";
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
determine_destiny_metrics_s(inputs* data, fuel_coefs* ptr, arguments* args, main_outs* metrics)
{
    // Hack: Initialize coefficients
    initialize_coeff(args->scenario);

    // Aux
    float ros = 0, bros = 0, lb = 0, fros = 0;
    bool crownFire = false;
    ptr->q1 = q_coeff[data->nftype][0];
    ptr->q2 = q_coeff[data->nftype][1];
    ptr->q3 = q_coeff[data->nftype][2];
    ptr->nftype = data->nftype;
    // Step 6: Flame Length
    metrics->fl = flame_length(data, ptr);
    // Step 9: Byram Intensity
    metrics->sfi = byram_intensity(metrics, ptr);
    // Set cfb value for no crown fire scenario
    metrics->cfb = 0;
    // Step 10: Criterion for Crown Fire Initiation (no init if user does not
    // want to include it)
    if (args->AllowCROS)
    {
        crownFire = fire_type(data, metrics);
        if (crownFire)
        {
            metrics->cfb = crownfractionburn(data, metrics);
            metrics->crown_intensity = crown_byram_intensity(metrics, data);
            metrics->crown_flame_length = crown_flame_length(metrics->crown_intensity);
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

    metrics->crown = crownFire;
}

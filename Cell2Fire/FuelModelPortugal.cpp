#include "FuelModelPortugal.h"
#include "ReadArgs.h"
#include "Cells.h"
#include <iostream>
#include <math.h>
#include <cmath>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <unordered_map>
#include <string>
#include <vector>

using namespace std;

/*
	Global coefficients
*/  
std::unordered_map<int, std::vector<float>> p_coeff_p;
std::unordered_map<int, std::vector<float>> q_coeff_p;
std::unordered_map<int, std::vector<float>> fm_parameters_p;
 
/*
	Functions
*/

void initialize_coeff_p(int scenario)
{
	if (scenario == 1){
		// Populate them
		// FM211
		int F211 = 211;
		std::vector<float> p_211;
		p_211.push_back(0.275);
		p_211.push_back(0.078);
		p_211.push_back(0.016);

		std::vector<float> q_211;
		q_211.push_back(-1.637);
		q_211.push_back(0.037);
		q_211.push_back(2.514);

		p_coeff_p.insert(std::make_pair(F211, p_211));
		q_coeff_p.insert(std::make_pair(F211, q_211));
		
		
		// FM 212
		int F212 = 212;
		  std::vector<float> p_212;
		  p_212.push_back(0.57);
		  p_212.push_back(0.078);
		  p_212.push_back(0.03);

		  std::vector<float> q_212;
		  q_212.push_back(-1.315);
		  q_212.push_back(0.037);
		  q_212.push_back(1.956);

		  p_coeff_p.insert(std::make_pair(F212, p_212));
		  q_coeff_p.insert(std::make_pair(F212, q_212));

		  // FM 213
		  int F213 = 213;
		  std::vector<float> p_213;
		  p_213.push_back(0.385);
		  p_213.push_back(0.078);
		  p_213.push_back(0.017);

		  std::vector<float> q_213;
		  q_213.push_back(-1.683);
		  q_213.push_back(0.031);
		  q_213.push_back(2.468);

		  p_coeff_p.insert(std::make_pair(F213, p_213));
		  q_coeff_p.insert(std::make_pair(F213, q_213));


		  // FM 214
		  int F214 = 214;
		  std::vector<float> p_214;
		  p_214.push_back(6.464);
		  p_214.push_back(0.2);
		  p_214.push_back(0.219);

		  std::vector<float> q_214;
		  q_214.push_back(-0.662);
		  q_214.push_back(0.084);
		  q_214.push_back(1.068);

		  p_coeff_p.insert(std::make_pair(F214, p_214));
		  q_coeff_p.insert(std::make_pair(F214, q_214));

		  // FM 221
		  int F221 = 221;
		  std::vector<float> p_221;
		  p_221.push_back(0.133);
		  p_221.push_back(0.078);
		  p_221.push_back(0.006);

		  std::vector<float> q_221;
		  q_221.push_back(-2.522);
		  q_221.push_back(0.032);
		  q_221.push_back(3.64);

		  p_coeff_p.insert(std::make_pair(F221, p_221));
		  q_coeff_p.insert(std::make_pair(F221, q_221));

		  // FM 222
		  int F222 = 222;
		  std::vector<float> p_222;
		  p_222.push_back(0.159);
		  p_222.push_back(0.078);
		  p_222.push_back(0.007);

		  std::vector<float> q_222;
		  q_222.push_back(-2.416);
		  q_222.push_back(0.033);
		  q_222.push_back(3.508);

		  p_coeff_p.insert(std::make_pair(F222, p_222));
		  q_coeff_p.insert(std::make_pair(F222, q_222));

		  // FM 223
		  int F223 = 223;
		  std::vector<float> p_223;
		  p_223.push_back(0.087);
		  p_223.push_back(0.078);
		  p_223.push_back(0.004);

		  std::vector<float> q_223;
		  q_223.push_back(-2.816);
		  q_223.push_back(0.034);
		  q_223.push_back(4.103);

		  p_coeff_p.insert(std::make_pair(F223, p_223));
		  q_coeff_p.insert(std::make_pair(F223, q_223));

		  // FM 224
		  int F224 = 224;
		  std::vector<float> p_224;
		  p_224.push_back(0.394);
		  p_224.push_back(0.078);
		  p_224.push_back(0.021);

		  std::vector<float> q_224;
		  q_224.push_back(-1.324);
		  q_224.push_back(0.038);
		  q_224.push_back(1.983);

		  p_coeff_p.insert(std::make_pair(F224, p_224));
		  q_coeff_p.insert(std::make_pair(F224, q_224));

		  // FM 225
		  int F225 = 225;
		  std::vector<float> p_225;
		  p_225.push_back(0.109);
		  p_225.push_back(0.079);
		  p_225.push_back(0.004);

		  std::vector<float> q_225;
		  q_225.push_back(-2.649);
		  q_225.push_back(0.029);
		  q_225.push_back(3.63);

		  p_coeff_p.insert(std::make_pair(F225, p_225));
		  q_coeff_p.insert(std::make_pair(F225, q_225));

		  // FM 226
		  int F226 = 226;
		  std::vector<float> p_226;
		  p_226.push_back(0.36);
		  p_226.push_back(0.078);
		  p_226.push_back(0.014);

		  std::vector<float> q_226;
		  q_226.push_back(-1.625);
		  q_226.push_back(0.031);
		  q_226.push_back(2.278);

		  p_coeff_p.insert(std::make_pair(F226, p_226));
		  q_coeff_p.insert(std::make_pair(F226, q_226));

		  // FM 227
		  int F227 = 227;
		  std::vector<float> p_227;
		  p_227.push_back(0.123);
		  p_227.push_back(0.078);
		  p_227.push_back(0.005);

		  std::vector<float> q_227;
		  q_227.push_back(-2.76);
		  q_227.push_back(0.032);
		  q_227.push_back(3.932);

		  p_coeff_p.insert(std::make_pair(F227, p_227));
		  q_coeff_p.insert(std::make_pair(F227, q_227));

		  // FM 231
		  int F231 = 231;
		  std::vector<float> p_231;
		  p_231.push_back(0.06);
		  p_231.push_back(0.078);
		  p_231.push_back(0.003);

		  std::vector<float> q_231;
		  q_231.push_back(-2.007);
		  q_231.push_back(0.037);
		  q_231.push_back(2.864);

		  p_coeff_p.insert(std::make_pair(F231, p_231));
		  q_coeff_p.insert(std::make_pair(F231, q_231));

		  // FM 232
		  int F232 = 232;
		  std::vector<float> p_232;
		  p_232.push_back(2.012);
		  p_232.push_back(0.707);
		  p_232.push_back(0.05);

		  std::vector<float> q_232;
		  q_232.push_back(-0.648);
		  q_232.push_back(0.317);
		  q_232.push_back(1.098);

		  p_coeff_p.insert(std::make_pair(F232, p_232));
		  q_coeff_p.insert(std::make_pair(F232, q_232));

		  // FM 233
		  int F233 = 233;
		  std::vector<float> p_233;
		  p_233.push_back(0.101);
		  p_233.push_back(0.078);
		  p_233.push_back(0.006);

		  std::vector<float> q_233;
		  q_233.push_back(-2.656);
		  q_233.push_back(0.041);
		  q_233.push_back(4.177);

		  p_coeff_p.insert(std::make_pair(F233, p_233));
		  q_coeff_p.insert(std::make_pair(F233, q_233));

		  // FM 234
		  int F234 = 234;
		  std::vector<float> p_234;
		  p_234.push_back(0.152);
		  p_234.push_back(0.078);
		  p_234.push_back(0.008);

		  std::vector<float> q_234;
		  q_234.push_back(-2.316);
		  q_234.push_back(0.036);
		  q_234.push_back(3.491);

		  p_coeff_p.insert(std::make_pair(F234, p_234));
		  q_coeff_p.insert(std::make_pair(F234, q_234));

		  // FM 235
		  int F235 = 235;
		  std::vector<float> p_235;
		  p_235.push_back(0.152);
		  p_235.push_back(0.083);
		  p_235.push_back(0.006);

		  std::vector<float> q_235;
		  q_235.push_back(-2.093);
		  q_235.push_back(0.034);
		  q_235.push_back(2.997);

		  p_coeff_p.insert(std::make_pair(F235, p_235));
		  q_coeff_p.insert(std::make_pair(F235, q_235));

		  // FM 236
		  int F236 = 236;
		  std::vector<float> p_236;
		  p_236.push_back(0.113);
		  p_236.push_back(0.079);
		  p_236.push_back(0.01);

		  std::vector<float> q_236;
		  q_236.push_back(-1.974);
		  q_236.push_back(0.049);
		  q_236.push_back(3.298);

		  p_coeff_p.insert(std::make_pair(F236, p_236));
		  q_coeff_p.insert(std::make_pair(F236, q_236));

		  // FM 237
		  int F237 = 237;
		  std::vector<float> p_237;
		  p_237.push_back(0.208);
		  p_237.push_back(0.096);
		  p_237.push_back(0.016);

		  std::vector<float> q_237;
		  q_237.push_back(-1.571);
		  q_237.push_back(0.055);
		  q_237.push_back(2.572);

		  p_coeff_p.insert(std::make_pair(F237, p_237));
		  q_coeff_p.insert(std::make_pair(F237, q_237));

	}
	
	if (scenario == 2){
		  // Populate them
		  // FM 211
		  int F211 = 211;
		  std::vector<float> p_211;
		  p_211.push_back(0.246);
		  p_211.push_back(0.078);
		  p_211.push_back(0.014);

		  std::vector<float> q_211;
		  q_211.push_back(-1.694);
		  q_211.push_back(0.038);
		  q_211.push_back(2.604);

		  p_coeff_p.insert(std::make_pair(F211, p_211));
		  q_coeff_p.insert(std::make_pair(F211, q_211));

		  // FM 212
		  int F212 = 212;
		  std::vector<float> p_212;
		  p_212.push_back(0.512);
		  p_212.push_back(0.077);
		  p_212.push_back(0.027);

		  std::vector<float> q_212;
		  q_212.push_back(-1.356);
		  q_212.push_back(0.036);
		  q_212.push_back(2.033);

		  p_coeff_p.insert(std::make_pair(F212, p_212));
		  q_coeff_p.insert(std::make_pair(F212, q_212));

		  // FM 213
		  int F213 = 213;
		  std::vector<float> p_213;
		  p_213.push_back(0.316);
		  p_213.push_back(0.078);
		  p_213.push_back(0.014);

		  std::vector<float> q_213;
		  q_213.push_back(-1.814);
		  q_213.push_back(0.03);
		  q_213.push_back(2.667);

		  p_coeff_p.insert(std::make_pair(F213, p_213));
		  q_coeff_p.insert(std::make_pair(F213, q_213));


		  // FM 214
		  int F214 = 214;
		  std::vector<float> p_214;
		  p_214.push_back(5.26);
		  p_214.push_back(0.186);
		  p_214.push_back(0.173);

		  std::vector<float> q_214;
		  q_214.push_back(-0.723);
		  q_214.push_back(0.082);
		  q_214.push_back(1.117);

		  p_coeff_p.insert(std::make_pair(F214, p_214));
		  q_coeff_p.insert(std::make_pair(F214, q_214));

		  // FM 221
		  int F221 = 221;
		  std::vector<float> p_221;
		  p_221.push_back(0.124);
		  p_221.push_back(0.078);
		  p_221.push_back(0.005);

		  std::vector<float> q_221;
		  q_221.push_back(-2.584);
		  q_221.push_back(0.034);
		  q_221.push_back(3.724);

		  p_coeff_p.insert(std::make_pair(F221, p_221));
		  q_coeff_p.insert(std::make_pair(F221, q_221));

		  // FM 222
		  int F222 = 222;
		  std::vector<float> p_222;
		  p_222.push_back(0.149);
		  p_222.push_back(0.078);
		  p_222.push_back(0.007);

		  std::vector<float> q_222;
		  q_222.push_back(-2.484);
		  q_222.push_back(0.033);
		  q_222.push_back(3.596);

		  p_coeff_p.insert(std::make_pair(F222, p_222));
		  q_coeff_p.insert(std::make_pair(F222, q_222));

		  // FM 223
		  int F223 = 223;
		  std::vector<float> p_223;
		  p_223.push_back(0.078);
		  p_223.push_back(0.078);
		  p_223.push_back(0.004);

		  std::vector<float> q_223;
		  q_223.push_back(-2.89);
		  q_223.push_back(0.036);
		  q_223.push_back(4.215);

		  p_coeff_p.insert(std::make_pair(F223, p_223));
		  q_coeff_p.insert(std::make_pair(F223, q_223));

		  // FM 224
		  int F224 = 224;
		  std::vector<float> p_224;
		  p_224.push_back(0.364);
		  p_224.push_back(0.078);
		  p_224.push_back(0.019);

		  std::vector<float> q_224;
		  q_224.push_back(-1.39);
		  q_224.push_back(0.036);
		  q_224.push_back(2.081);

		  p_coeff_p.insert(std::make_pair(F224, p_224));
		  q_coeff_p.insert(std::make_pair(F224, q_224));

		  // FM 225

		  int F225 = 225;
		  std::vector<float> p_225;
		  p_225.push_back(0.098);
		  p_225.push_back(0.079);
		  p_225.push_back(0.003);

		  std::vector<float> q_225;
		  q_225.push_back(-2.79);
		  q_225.push_back(0.028);
		  q_225.push_back(3.817);

		  p_coeff_p.insert(std::make_pair(F225, p_225));
		  q_coeff_p.insert(std::make_pair(F225, q_225));

		  // FM 226

		  int F226 = 226;
		  std::vector<float> p_226;
		  p_226.push_back(0.318);
		  p_226.push_back(0.078);
		  p_226.push_back(0.012);

		  std::vector<float> q_226;
		  q_226.push_back(-1.67);
		  q_226.push_back(0.031);
		  q_226.push_back(2.372);

		  p_coeff_p.insert(std::make_pair(F226, p_226));
		  q_coeff_p.insert(std::make_pair(F226, q_226));

		  // FM 227

		  int F227 = 227;
		  std::vector<float> p_227;
		  p_227.push_back(0.112);
		  p_227.push_back(0.078);
		  p_227.push_back(0.005);

		  std::vector<float> q_227;
		  q_227.push_back(-2.888);
		  q_227.push_back(0.031);
		  q_227.push_back(4.115);

		  p_coeff_p.insert(std::make_pair(F227, p_227));
		  q_coeff_p.insert(std::make_pair(F227, q_227));

		  // FM 231

		  int F231 = 231;
		  std::vector<float> p_231;
		  p_231.push_back(0.052);
		  p_231.push_back(0.078);
		  p_231.push_back(0.002);

		  std::vector<float> q_231;
		  q_231.push_back(-2.111);
		  q_231.push_back(0.035);
		  q_231.push_back(3.033);

		  p_coeff_p.insert(std::make_pair(F231, p_231));
		  q_coeff_p.insert(std::make_pair(F231, q_231));

		  // FM 232

		  int F232 = 232;
		  std::vector<float> p_232;
		  p_232.push_back(5363.193);
		  p_232.push_back(1.825);
		  p_232.push_back(0.039);

		  std::vector<float> q_232;
		  q_232.push_back(-0.735);
		  q_232.push_back(0.262);
		  q_232.push_back(1.229);

		  p_coeff_p.insert(std::make_pair(F232, p_232));
		  q_coeff_p.insert(std::make_pair(F232, q_232));

		  // FM 233

		  int F233 = 233;
		  std::vector<float> p_233;
		  p_233.push_back(0.094);
		  p_233.push_back(0.078);
		  p_233.push_back(0.006);

		  std::vector<float> q_233;
		  q_233.push_back(-2.73);
		  q_233.push_back(0.04);
		  q_233.push_back(4.301);

		  p_coeff_p.insert(std::make_pair(F233, p_233));
		  q_coeff_p.insert(std::make_pair(F233, q_233));

		  // FM 234

		  int F234 = 234;
		  std::vector<float> p_234;
		  p_234.push_back(0.14);
		  p_234.push_back(0.078);
		  p_234.push_back(0.007);

		  std::vector<float> q_234;
		  q_234.push_back(-2.39);
		  q_234.push_back(0.037);
		  q_234.push_back(3.601);

		  p_coeff_p.insert(std::make_pair(F234, p_234));
		  q_coeff_p.insert(std::make_pair(F234, q_234));

		  // FM 235

		  int F235 = 235;
		  std::vector<float> p_235;
		  p_235.push_back(0.122);
		  p_235.push_back(0.078);
		  p_235.push_back(0.005);

		  std::vector<float> q_235;
		  q_235.push_back(-2.252);
		  q_235.push_back(0.033);
		  q_235.push_back(3.216);

		  p_coeff_p.insert(std::make_pair(F235, p_235));
		  q_coeff_p.insert(std::make_pair(F235, q_235));

		  // FM 236

		  int F236 = 236;
		  std::vector<float> p_236;
		  p_236.push_back(0.105);
		  p_236.push_back(0.079);
		  p_236.push_back(0.009);

		  std::vector<float> q_236;
		  q_236.push_back(-2.049);
		  q_236.push_back(0.049);
		  q_236.push_back(3.397);

		  p_coeff_p.insert(std::make_pair(F236, p_236));
		  q_coeff_p.insert(std::make_pair(F236, q_236));

		  // FM 237

		  int F237 = 237;
		  std::vector<float> p_237;
		  p_237.push_back(0.163);
		  p_237.push_back(0.085);
		  p_237.push_back(0.013);

		  std::vector<float> q_237;
		  q_237.push_back(-1.68);
		  q_237.push_back(0.049);
		  q_237.push_back(2.768);

		  p_coeff_p.insert(std::make_pair(F237, p_237));
		  q_coeff_p.insert(std::make_pair(F237, q_237));

	}

	if (scenario == 3){
		
		// Populate them
	  // FM 211
		int F211 = 211;
		std::vector<float> p_211;
		p_211.push_back(0.206);
		p_211.push_back(0.078);
		p_211.push_back(0.012);

		std::vector<float> q_211;
		q_211.push_back(-1.815);
		q_211.push_back(0.037);
		q_211.push_back(2.804);

		p_coeff_p.insert(std::make_pair(F211, p_211));
		q_coeff_p.insert(std::make_pair(F211, q_211));

	  // FM 212
	  int F212 = 212;
	  std::vector<float> p_212;
	  p_212.push_back(0.462);
	  p_212.push_back(0.079);
	  p_212.push_back(0.024);

	  std::vector<float> q_212;
	  q_212.push_back(-1.424);
	  q_212.push_back(0.037);
	  q_212.push_back(2.151);

	  p_coeff_p.insert(std::make_pair(F212, p_212));
	  q_coeff_p.insert(std::make_pair(F212, q_212));

	  // FM 213
	  int F213 = 213;
	  std::vector<float> p_213;
	  p_213.push_back(0.247);
	  p_213.push_back(0.078);
	  p_213.push_back(0.011);

	  std::vector<float> q_213;
	  q_213.push_back(-1.975);
	  q_213.push_back(0.031);
	  q_213.push_back(2.894);

	  p_coeff_p.insert(std::make_pair(F213, p_213));
	  q_coeff_p.insert(std::make_pair(F213, q_213));


	  // FM 214
	  int F214 = 214;
	  std::vector<float> p_214;
	  p_214.push_back(3.671);
	  p_214.push_back(0.165);
	  p_214.push_back(0.122);

	  std::vector<float> q_214;
	  q_214.push_back(-0.805);
	  q_214.push_back(0.072);
	  q_214.push_back(1.256);

	  p_coeff_p.insert(std::make_pair(F214, p_214));
	  q_coeff_p.insert(std::make_pair(F214, q_214));

	  // FM 221
	  int F221 = 221;
	  std::vector<float> p_221;
	  p_221.push_back(0.113);
	  p_221.push_back(0.078);
	  p_221.push_back(0.005);

	  std::vector<float> q_221;
	  q_221.push_back(-2.674);
	  q_221.push_back(0.034);
	  q_221.push_back(3.86);

	  p_coeff_p.insert(std::make_pair(F221, p_221));
	  q_coeff_p.insert(std::make_pair(F221, q_221));

	  // FM 222
	  int F222 = 222;
	  std::vector<float> p_222;
	  p_222.push_back(0.136);
	  p_222.push_back(0.078);
	  p_222.push_back(0.006);

	  std::vector<float> q_222;
	  q_222.push_back(-2.596);
	  q_222.push_back(0.033);
	  q_222.push_back(3.777);

	  p_coeff_p.insert(std::make_pair(F222, p_222));
	  q_coeff_p.insert(std::make_pair(F222, q_222));

	  // FM 223
	  int F223 = 223;
	  std::vector<float> p_223;
	  p_223.push_back(0.067);
	  p_223.push_back(0.078);
	  p_223.push_back(0.003);

	  std::vector<float> q_223;
	  q_223.push_back(-3.121);
	  q_223.push_back(0.034);
	  q_223.push_back(4.542);

	  p_coeff_p.insert(std::make_pair(F223, p_223));
	  q_coeff_p.insert(std::make_pair(F223, q_223));

	  // FM 224
	  int F224 = 224;
	  std::vector<float> p_224;
	  p_224.push_back(0.325);
	  p_224.push_back(0.078);
	  p_224.push_back(0.017);

	  std::vector<float> q_224;
	  q_224.push_back(-1.48);
	  q_224.push_back(0.036);
	  q_224.push_back(2.186);

	  p_coeff_p.insert(std::make_pair(F224, p_224));
	  q_coeff_p.insert(std::make_pair(F224, q_224));

	  // FM 225

	  int F225 = 225;
	  std::vector<float> p_225;
	  p_225.push_back(0.086);
	  p_225.push_back(0.079);
	  p_225.push_back(0.003);

	  std::vector<float> q_225;
	  q_225.push_back(-2.925);
	  q_225.push_back(0.029);
	  q_225.push_back(4.016);

	  p_coeff_p.insert(std::make_pair(F225, p_225));
	  q_coeff_p.insert(std::make_pair(F225, q_225));

	  // FM 226

	  int F226 = 226;
	  std::vector<float> p_226;
	  p_226.push_back(0.267);
	  p_226.push_back(0.078);
	  p_226.push_back(0.01);

	  std::vector<float> q_226;
	  q_226.push_back(-1.805);
	  q_226.push_back(0.031);
	  q_226.push_back(2.531);

	  p_coeff_p.insert(std::make_pair(F226, p_226));
	  q_coeff_p.insert(std::make_pair(F226, q_226));

	  // FM 227

	  int F227 = 227;
	  std::vector<float> p_227;
	  p_227.push_back(0.1);
	  p_227.push_back(0.078);
	  p_227.push_back(0.004);

	  std::vector<float> q_227;
	  q_227.push_back(-3.018);
	  q_227.push_back(0.032);
	  q_227.push_back(4.303);

	  p_coeff_p.insert(std::make_pair(F227, p_227));
	  q_coeff_p.insert(std::make_pair(F227, q_227));

	  // FM 231

	  int F231 = 231;
	  std::vector<float> p_231;
	  p_231.push_back(0.042);
	  p_231.push_back(0.078);
	  p_231.push_back(0.002);

	  std::vector<float> q_231;
	  q_231.push_back(-2.278);
	  q_231.push_back(0.035);
	  q_231.push_back(3.275);

	  p_coeff_p.insert(std::make_pair(F231, p_231));
	  q_coeff_p.insert(std::make_pair(F231, q_231));

	  // FM 232

	  int F232 = 232;
	  std::vector<float> p_232;
	  p_232.push_back(0.712);
	  p_232.push_back(0.532);
	  p_232.push_back(0.024);

	  std::vector<float> q_232;
	  q_232.push_back(-0.894);
	  q_232.push_back(0.224);
	  q_232.push_back(1.419);

	  p_coeff_p.insert(std::make_pair(F232, p_232));
	  q_coeff_p.insert(std::make_pair(F232, q_232));

	  // FM 233

	  int F233 = 233;
	  std::vector<float> p_233;
	  p_233.push_back(0.086);
	  p_233.push_back(0.078);
	  p_233.push_back(0.005);

	  std::vector<float> q_233;
	  q_233.push_back(-2.836);
	  q_233.push_back(0.041);
	  q_233.push_back(4.457);

	  p_coeff_p.insert(std::make_pair(F233, p_233));
	  q_coeff_p.insert(std::make_pair(F233, q_233));

	  // FM 234

	  int F234 = 234;
	  std::vector<float> p_234;
	  p_234.push_back(0.126);
	  p_234.push_back(0.078);
	  p_234.push_back(0.007);

	  std::vector<float> q_234;
	  q_234.push_back(-2.497);
	  q_234.push_back(0.037);
	  q_234.push_back(3.768);

	  p_coeff_p.insert(std::make_pair(F234, p_234));
	  q_coeff_p.insert(std::make_pair(F234, q_234));

	  // FM 235

	  int F235 = 235;
	  std::vector<float> p_235;
	  p_235.push_back(0.111);
	  p_235.push_back(0.078);
	  p_235.push_back(0.005);

	  std::vector<float> q_235;
	  q_235.push_back(-2.35);
	  q_235.push_back(0.034);
	  q_235.push_back(3.339);

	  p_coeff_p.insert(std::make_pair(F235, p_235));
	  q_coeff_p.insert(std::make_pair(F235, q_235));

	  // FM 236

	  int F236 = 236;
	  std::vector<float> p_236;
	  p_236.push_back(0.098);
	  p_236.push_back(0.079);
	  p_236.push_back(0.008);

	  std::vector<float> q_236;
	  q_236.push_back(-2.102);
	  q_236.push_back(0.049);
	  q_236.push_back(3.513);

	  p_coeff_p.insert(std::make_pair(F236, p_236));
	  q_coeff_p.insert(std::make_pair(F236, q_236));

	  // FM 237

	  int F237 = 237;
	  std::vector<float> p_237;
	  p_237.push_back(0.139);
	  p_237.push_back(0.079);
	  p_237.push_back(0.011);

	  std::vector<float> q_237;
	  q_237.push_back(-1.765);
	  q_237.push_back(0.046);
	  q_237.push_back(2.907);

	  p_coeff_p.insert(std::make_pair(F237, p_237));
	  q_coeff_p.insert(std::make_pair(F237, q_237));
		
	}
	

//Fuel Model Parameters for Crown Fire
std::vector<float> fp_211;
fp_211.push_back(0.1+0.0+0.0+0.3+0.0);
fp_211.push_back(8000);
fm_parameters_p.insert(std::make_pair(211,fp_211));

std::vector<float> fp_212;
fp_212.push_back(0.1+0.0+0.0+1.0+0.0);
fp_212.push_back(8000);
fm_parameters_p.insert(std::make_pair(212,fp_212));

std::vector<float> fp_213;
fp_213.push_back(0.1+0.4+0.0+1.5+0.0);
fp_213.push_back(8000);
fm_parameters_p.insert(std::make_pair(213,fp_213));

std::vector<float> fp_214;
fp_214.push_back(0.25+0.0+0.0+1.9+0.0);
fp_214.push_back(8000);
fm_parameters_p.insert(std::make_pair(214,fp_214));

std::vector<float> fp_221;
fp_221.push_back(0.4+0.0+0.0+2.5+0.0);
fp_221.push_back(8000);
fm_parameters_p.insert(std::make_pair(221,fp_221));

std::vector<float> fp_222;
fp_222.push_back(0.1+0.0+0.0+3.4+0.0);
fp_222.push_back(9000);
fm_parameters_p.insert(std::make_pair(222,fp_222));

std::vector<float> fp_223;
fp_223.push_back(1.0+0.0+0.0+5.4+0.0);
fp_223.push_back(8000);
fm_parameters_p.insert(std::make_pair(223,fp_223));

std::vector<float> fp_224;
fp_224.push_back(0.5+1.0+0.0+7.3+0.0);
fp_224.push_back(8000);
fm_parameters_p.insert(std::make_pair(224,fp_224));

std::vector<float> fp_225;
fp_225.push_back(0.2+0.0+0.0+0.5+0.65);
fp_225.push_back(8000);
fm_parameters_p.insert(std::make_pair(225,fp_225));

std::vector<float> fp_226;
fp_226.push_back(0.5+0.5+0.0+0.6+1.0);
fp_226.push_back(8000);
fm_parameters_p.insert(std::make_pair(226,fp_226));

std::vector<float> fp_227;
fp_227.push_back(0.3+0.25+0.0+1.45+1.25);
fp_227.push_back(8000);
fm_parameters_p.insert(std::make_pair(227,fp_227));

std::vector<float> fp_231;
fp_231.push_back(1.9+0.3+0.1+3.4+7.1);
fp_231.push_back(8000);
fm_parameters_p.insert(std::make_pair(231,fp_231));

std::vector<float> fp_232;
fp_232.push_back(1.35+2.4+0.75+0.0+3.85);
fp_232.push_back(8000);
fm_parameters_p.insert(std::make_pair(232,fp_232));

std::vector<float> fp_233;
fp_233.push_back(0.45+3.0+0.0+0.0+6.2);
fp_233.push_back(8000);
fm_parameters_p.insert(std::make_pair(233,fp_233));

std::vector<float> fp_234;
fp_234.push_back(0.85+1.15+0.2+0.0+2.55);
fp_234.push_back(8000);
fm_parameters_p.insert(std::make_pair(234,fp_234));

std::vector<float> fp_235;
fp_235.push_back(3.6+2.1+0.0+0.0+2.9);
fp_235.push_back(8000);
fm_parameters_p.insert(std::make_pair(235,fp_235));

std::vector<float> fp_236;
fp_236.push_back(2.9+1.45+0.0+0.0+1.4);
fp_236.push_back(8000);
fm_parameters_p.insert(std::make_pair(236,fp_236));

std::vector<float> fp_237;
fp_237.push_back(3.5+5.3+2.2+0.0+3.4);
fp_237.push_back(8000);
fm_parameters_p.insert(std::make_pair(237,fp_237));

}



float rate_of_spread_p(inputs *data, fuel_coefs *ptr, main_outs *at)
   {
   float p1, p2, p3, ws  ;
   
   p1 = p_coeff_p[data->nftype][0] ;
   p2 = p_coeff_p[data->nftype][1] ;
   p3 = p_coeff_p[data->nftype][2];
   //se = slope_effect(inp) ;
   ws = data->ws ;
   at->rss = 1.0 / (p1 * exp(-p2 * ws) + p3) ;
   
   return at->rss * (at->rss >= 0) ;
	
   }

float flankfire_ros_p(float ros,float bros,float lb)
   {
      return  ((ros + bros) / ( lb * 2.0)) ;
   }

/* ----------------- Length-to-Breadth --------------------------*/

float l_to_b_p(float ws)
  {
    //if(strncmp(ft,"O1",2)==0)return( ws<1.0 ? 1.0 : (1.1*pow(ws,0.464)));
    float alpha, beta, factor ;
    alpha = 0.2566 ;
    beta = -0.1548 ;
    factor = 1000.0 / 3600.0;
    return pow((0.936 * exp(alpha * factor * ws) + 0.461 * exp(beta * factor * ws) - 0.397), 0.45);
  }



/* ----------------- Back Rate of Spread --------------------------*/

float backfire_ros_p(main_outs *at, snd_outs *sec)
  {
    float hb, bros, lb ;
    //lb = l_to_b(data->fueltype,at->wsv) ;
    lb = sec->lb ;
    hb = (lb + sqrt(pow(lb,2) - 1.0)) /  (lb - sqrt(pow(lb, 2) - 1.0)) ;

    bros = at->rss / hb ;
    
    return bros * (bros >= 0);
  }


float flame_length_p(inputs *data, fuel_coefs *ptr)
   {
       float q1, q2, q3, fl, ws ;

       ws = data->ws ;
       q1 = q_coeff_p[data->nftype][0] ;
       q2 = q_coeff_p[data->nftype][1] ;
       q3 = q_coeff_p[data->nftype][2] ; 

       fl = pow(q1 * exp(-q2 * ws) + q3, 2) ;
       return fl; 
   }

float angleFL_p(inputs *data, fuel_coefs *ptr)
   {
       float angle, fl, y, ws ;
       ws = data->ws ;
       fl = flame_length_p(data, ptr) ;
       y = 10.0 / 36.0 * ws ;

       angle = atan(2.24 * sqrt(fl / pow(y, 2)))  ;
       return angle;
   }

float flame_height_p(inputs *data, fuel_coefs *ptr)
  {
      float fh, phi ;
      phi = angleFL_p(data, ptr) ;
      fh = flame_length_p(data, ptr) * sin(phi) ;
      return fh ;
  }


float byram_intensity_p(main_outs* at, fuel_coefs* ptr) {
	float fl, ib;
	fl = at->fl;
	ib = 259.833 * pow(fl, 2.174);
	ib=std::ceil(ib * 100.0) / 100.0;
	return ib;
}

int fmc_scen_p(inputs* data) {
	int fmc;
	fmc= data->FMC;
	return fmc;

}

bool fire_type_p(inputs* data, main_outs* at)
{
	float intensity, critical_intensity, cbh;
	int fmc;
	bool crownFire = false;

	intensity = at->sfi;
	cbh = data->cbh;
	fmc = fmc_scen_p(data);
	critical_intensity = pow((0.01 * cbh * (460 + 25.9 * fmc)), 1.5);

	if ((intensity > critical_intensity) && cbh != 0) crownFire = true;

	return crownFire;
}


float rate_of_spread10_p(inputs *data, arguments *args)
   {
   // FM 10 coef
   float p1 = 0.2802, p2 = 0.07786, p3 = 0.01123 ;
   float ros, ros10, ws, ffros, fcbd, fccf;

   ffros = args->ROS10Factor ;
   fcbd  = args->CBDFactor ;
   fccf  = args->CCFFactor ;
   
   ws = data->ws ;
   ros10 = 1. / (p1 * exp(-p2 * ws) + p3) ;
   ros = ffros * ros10 + fccf * data->ccf + fcbd * args->CBDFactor ;
   
   return(ros);
   }


float final_rate_of_spread10_p(inputs *data,  main_outs* at)
   {
 	float  ros_active, ros_final, ros;
    ros = at->rss;
    ros_active=at->ros_active;
    ros_final = ros + at->cfb * (ros_active - ros); 
   return(ros_final);
   }
 

float backfire_ros10_p(fire_struc *hptr, snd_outs *sec)
  {
    float hb, bros, lb ;
    lb = sec->lb ;
    hb = (lb + sqrt(pow(lb, 2) - 1.0)) /  (lb - sqrt(pow(lb, 2) - 1.0)) ;

    bros = hptr->ros / hb ;
    
    return bros;
  }

float crownfractionburn_p(inputs* data, main_outs* at) { //generar output de cfb
    float a, cbd, ros, ros0, H, wa, i0, cbh, FMC, cfb;
    FMC = fmc_scen_p(data);; //modificar para ingresar manualmente
    cbh = data->cbh;
    i0 = pow((0.01 * cbh * (460 + 25.9 * FMC)), 1.5);
    wa = fm_parameters_p[data->nftype][0];
	H = fm_parameters_p[data->nftype][1];
    cbd = data->cbd;
    ros0 = 60 * i0 / (H * wa);
    ros = at->rss;
    if (cbd != 0) {
        a = -log(0.1) / (0.9 * (3.0 / cbd - ros0));
		//a=0.23;
    }
    else {
        a=0.23;
    }
    cfb=1 - exp(-a * (ros - ros0));
	if (cfb<0){
		cfb=0;
	}
    return cfb;
}


bool checkActive_p(inputs * data,main_outs* at) //En s&b se usa fm10
{
    float  rac, cbd,H,wa,i0,cbh,fmc;
    bool active;
    //rac = at->ros_active;
    fmc = fmc_scen_p(data);; //modificar para ingresar manualmente
    cbh = data->cbh;
    i0 = pow((0.01 * cbh * (460 + 25.9 * fmc)), 1.5);
    wa = fm_parameters_p[data->nftype][0];
	H = fm_parameters_p[data->nftype][1];
    cbd = data->cbd;
    rac = 60 * i0 / (H * wa);

    active=cbd*rac>=3;
    return active;
}
  
 void calculate_p(inputs *data,  fuel_coefs * ptr,arguments *args ,main_outs *at, snd_outs *sec, fire_struc *hptr, fire_struc *fptr,fire_struc *bptr,bool & activeCrown)
{
	
    // Hack: Initialize coefficients 
	initialize_coeff_p(args->scenario);
	
	// Aux
	float  ros, bros, lb, fros;
	bool crownFire=false;
    // Populate fuel coefs struct
	//ptr->fueltype = data->fueltype;
	if (args->verbose){
		std::cout  << "Populate fuel types " <<  std::endl;
		std::cout  << "NfTypes:"  << data->nftype <<  std::endl;
		std::cout  << "scen:"  << args->scenario <<  std::endl;
	}
	ptr->p1 = p_coeff_p[data->nftype][0] ;
    ptr->p2 = p_coeff_p[data->nftype][1] ;
    ptr->p3 = p_coeff_p[data->nftype][2] ;
    ptr->q1 = q_coeff_p[data->nftype][0] ;
    ptr->q2 = q_coeff_p[data->nftype][1] ;
    ptr->q3 = q_coeff_p[data->nftype][2] ;
	ptr->nftype = data->nftype;

    // Step 1: Calculate HROS (surface)
    at->rss = rate_of_spread_p(data, ptr, at);
    hptr->rss = at->rss ;
    
    // Step 2: Calculate Length-to-breadth
    sec->lb = l_to_b_p(data->ws) ;
    
    // Step 3: Calculate BROS (surface)
    bptr->rss = backfire_ros_p(at, sec) ;
    
    // Step 4: Calculate central FROS (surface)
    fptr->rss = flankfire_ros_p(hptr->rss, bptr->rss, sec->lb);
    
    // Step 5: Ellipse components
    at->a = (hptr->rss + bptr->rss) / 2. ;
    at->b = (hptr->rss + bptr->rss) / (2. * sec->lb) ; 
    at->c = (hptr->rss - bptr->rss) / 2. ; 
	
	// Step 6: Flame Length
    at->fl = flame_length_p(data, ptr);

	//std::cout << "hasta aqui todo bien" << std::endl;
    
    // Step 7: Flame angle
    at->angle = angleFL_p(data, ptr) ;

	// Step 8: Flame Height
    at->fh = flame_height_p(data, ptr) ;
    
	// Step 9: Byram Intensity
	at->sfi = byram_intensity_p(at, ptr);

	// Step 10: Criterion for Crown Fire Initiation (no init if user does not want to include it)
	if (args->AllowCROS && data->cbh!=0 && data->cbd!=0) {
		if (activeCrown){
		at->ros_active=rate_of_spread10_p(data,args);
		if (!checkActive(data,at)) {
			activeCrown=false;
			}
		}
		else{
			crownFire=fire_type_p(data,at);
			if(args->verbose){
				cout << "Checking crown Fire conditions " << crownFire << "\n";

			}
		}
	}
	else {
		crownFire = false;
		activeCrown=false;
	}


	// If we have Crown fire, update the ROSs
    if (crownFire){
            at->ros_active=rate_of_spread10_p(data,args);
            at->cfb = crownfractionburn_p(data, at);

            hptr->ros = final_rate_of_spread10_p(data,at) ;
            at->rss=hptr->ros;
            bptr->ros = backfire_ros10_p(hptr,sec) ;
            fptr->ros = flankfire_ros_p(hptr->ros, bptr->ros, sec->lb) ;
			if (args->verbose){
				cout << "hptr->ros = " << hptr->ros << "\n" ;
				cout << "bptr->ros = " << bptr->ros << "\n" ;
				cout << "fptr->ros = " << fptr->ros << "\n" ;
			}

            at->a = (hptr->ros + bptr->ros) / 2. ;
            at->b = (hptr->ros + bptr->ros) / (2. * sec->lb) ; 
            at->c = (hptr->ros - bptr->rss) / 2 ; 
			at->crown = 1;
            activeCrown=true;


    }
    else if (activeCrown){
            at->cfb = crownfractionburn_p(data, at); //lo calculamos igual porque lo necesitamos para el output
            hptr->ros = at->ros_active ;
            at->rss=hptr->ros;
            bptr->ros = backfire_ros10_p(hptr,sec) ;
            fptr->ros = flankfire_ros_p(hptr->ros, bptr->ros, sec->lb) ;
            
			if (args->verbose){
				cout << "hptr->ros = " << hptr->ros << "\n" ;
				cout << "bptr->ros = " << bptr->ros << "\n" ;
				cout << "fptr->ros = " << fptr->ros << "\n" ;
			}

            at->a = (hptr->ros + bptr->ros) / 2. ;
            at->b = (hptr->ros + bptr->ros) / (2. * sec->lb) ; 
            at->c = (hptr->ros - bptr->rss) / 2 ; 
			at->crown = 1;
            //std::cout  << "ros_activo: "  <<hptr->ros <<  std::endl;



    }
	
	// Otherwise, use the surface alues
    else{
        at->crown=0;
		at->cfb=0;
        hptr->ros = hptr->rss ;
        bptr->ros = bptr->rss ; 
        fptr->ros = fptr->rss ;
		if (args->verbose){
			cout << "hptr->ros = " << hptr->ros << "\n" ;
			cout << "bptr->ros = " << bptr->ros << "\n" ;
			cout << "fptr->ros = " << fptr->ros << "\n" ;
		}

    }
	//if (hptr->ros>100){
	//cout << "hptr->rss = " << hptr->ros << "\n" ;

	//}

	if (args->verbose){
		cout << "--------------- Inputs --------------- \n" ;
		cout << "ws = " << data->ws << "\n" ;
		cout << "coef data->cbh = " << data->cbh << "\n" ;
		cout << "coef ptr->p1 = " << ptr->p1 << "\n" ;
		cout << "coef ptr->p2 = " << ptr->p2 << "\n" ;
		cout << "coef ptr->p3 = " << ptr->p3 << "\n" ;
		cout << "coef ptr->q1 = " << ptr->q1 << "\n" ;
		cout << "coef ptr->q2 = " << ptr->q2 << "\n" ;
		cout << "coef ptr->q3 = " << ptr->q3 << "\n" ;
		cout << "\n" ;

		cout << "---------------- Outputs --------------- \n" ;
		cout << "at->rss = " << at->rss << "\n" ;
		cout << "hptr->rss = " << hptr->rss << "\n" ;
		cout << "lb = " << sec->lb << "\n" ;
		cout << "bptr->rss = " << bptr->rss << "\n" ;
		cout << "fptr->rss = " << fptr->rss << "\n" ;
		cout << "axis a = " << at->a << "\n" ;
		cout << "axis b = " << at->b << "\n" ;
		cout << "axis c = " << at->c << "\n" ;
		cout << "fl = " << at->fl << "\n";
		cout << "angle = " << at->angle << "\n";
		cout << "fh = " << at->fh << "\n";
		cout << "Crown Fire = " << crownFire << "\n";
	}
}

void determine_destiny_metrics_p(inputs* data, fuel_coefs* ptr,arguments *args, main_outs* metrics) {
	// Hack: Initialize coefficients 
	initialize_coeff_p(args->scenario);

	// Aux
	float  ros=0, bros=0, lb=0, fros=0;
	bool crownFire = false;
	ptr->q1 = q_coeff_p[data->nftype][0];
	ptr->q2 = q_coeff_p[data->nftype][1];
	ptr->q3 = q_coeff_p[data->nftype][2];
	ptr->nftype = data->nftype;
	// Step 6: Flame Length
	metrics->fl = flame_length_p(data, ptr);
	// Step 9: Byram Intensity
	metrics->sfi = byram_intensity_p(metrics, ptr);
	//Set cfb value for no crown fire scenario
	metrics->cfb =0;
    // Step 10: Criterion for Crown Fire Initiation (no init if user does not want to include it)
    if (args->AllowCROS) {
        crownFire = fire_type_p(data, metrics);
        if (crownFire){
            metrics->cfb = crownfractionburn_p(data, metrics);

        }
        if (args->verbose) {
            cout << "Checking crown Fire conditions " << crownFire << "\n";
        }
    }
    else {
        crownFire = false;
    }

	


	metrics->crown = crownFire;
}

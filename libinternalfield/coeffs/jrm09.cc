const int _model_coeff_jrm09_len = 440;
const int _model_coeff_jrm09_nmax = 20;
const int _model_coeff_jrm09_ndef = 10;
const double _model_coeff_jrm09_rscale = 1.000000;
const int _model_coeff_jrm09_n[] = {1,1,2,2,2,3,3,3,3,4,4,4,4,4,5,5,5,5,
	5,5,6,6,6,6,6,6,6,7,7,7,7,7,7,7,7,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,
	9,9,10,10,10,10,10,10,10,10,10,10,10,11,11,11,11,11,11,11,11,11,11,
	11,11,12,12,12,12,12,12,12,12,12,12,12,12,12,13,13,13,13,13,13,13,
	13,13,13,13,13,13,13,14,14,14,14,14,14,14,14,14,14,14,14,14,14,14,
	15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,15,16,16,16,16,16,16,
	16,16,16,16,16,16,16,16,16,16,16,17,17,17,17,17,17,17,17,17,17,17,
	17,17,17,17,17,17,17,18,18,18,18,18,18,18,18,18,18,18,18,18,18,18,
	18,18,18,18,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,
	19,19,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,20,
	20};
const int _model_coeff_jrm09_m[] = {0,1,0,1,2,0,1,2,3,0,1,2,3,4,0,1,2,3,
	4,5,0,1,2,3,4,5,6,0,1,2,3,4,5,6,7,0,1,2,3,4,5,6,7,8,0,1,2,3,4,5,6,7,
	8,9,0,1,2,3,4,5,6,7,8,9,10,0,1,2,3,4,5,6,7,8,9,10,11,0,1,2,3,4,5,6,
	7,8,9,10,11,12,0,1,2,3,4,5,6,7,8,9,10,11,12,13,0,1,2,3,4,5,6,7,8,9,
	10,11,12,13,14,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0,1,2,3,4,5,6,
	7,8,9,10,11,12,13,14,15,16,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,
	17,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,0,1,2,3,4,5,6,7,8,
	9,10,11,12,13,14,15,16,17,18,19,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,
	15,16,17,18,19,20};
const double _model_coeff_jrm09_g[] = {410244.700000,-71498.300000,
	11670.400000,-56835.800000,48689.500000,4018.600000,-37791.100000,
	15926.300000,-2710.500000,-34645.400000,-8247.600000,-2406.100000,
	-11083.800000,-17837.200000,-18023.600000,4683.900000,16160.000000,
	-16402.000000,-2600.700000,-3660.700000,-20819.600000,9992.900000,
	11791.800000,-12574.700000,2669.700000,1113.200000,7584.900000,
	598.400000,4665.900000,-6495.700000,-2516.500000,-6448.500000,
	1855.300000,-2892.900000,2968.000000,10059.200000,1934.400000,
	-6702.900000,153.700000,-4124.200000,-867.200000,-3740.600000,
	-732.400000,-2433.200000,9671.800000,-3046.200000,260.900000,
	2071.300000,3329.600000,-2523.100000,1787.100000,-1148.200000,
	1276.500000,-1976.800000,-2299.500000,2009.700000,2127.800000,
	3498.300000,2967.600000,16.300000,1806.500000,-46.500000,
	2897.800000,574.500000,1298.900000,2304.000000,2861.700000,
	-969.500000,2984.400000,769.100000,-277.100000,-1145.800000,
	-947.300000,496.900000,-130.600000,-531.800000,1298.600000,
	2462.600000,2517.700000,-830.700000,193.900000,-360.200000,
	-539.100000,-825.300000,-1628.100000,1817.300000,-874.100000,
	-1357.700000,-216.500000,-1199.300000,531.200000,442.000000,
	910.800000,-1571.800000,-124.700000,612.300000,48.100000,261.500000,
	415.900000,-779.200000,83.800000,-257.100000,473.500000,-445.800000,
	1390.200000,-838.600000,212.900000,-1626.900000,-242.500000,
	605.300000,-346.300000,104.600000,394.000000,233.900000,277.700000,
	177.300000,1259.300000,525.500000,1320.400000,764.300000,
	-803.200000,-141.200000,-750.400000,-420.600000,383.800000,
	-729.800000,444.900000,-884.100000,107.600000,-319.200000,
	358.000000,-637.900000,-194.000000,-280.600000,-41.300000,
	-359.200000,-395.100000,-653.100000,-242.000000,-388.000000,
	-279.000000,-461.000000,-53.800000,-1211.900000,315.400000,
	-767.300000,25.600000,-790.900000,249.900000,-340.300000,
	-515.600000,-247.400000,-566.400000,88.800000,-480.600000,95.000000,
	-43.400000,-310.200000,177.200000,-155.400000,-820.300000,
	272.600000,-88.500000,-137.000000,-101.200000,237.400000,279.800000,
	-3.400000,551.200000,-85.900000,-171.300000,194.500000,612.200000,
	280.700000,471.100000,-101.900000,486.500000,192.200000,11.700000,
	119.600000,404.900000,-96.000000,90.800000,358.900000,123.800000,
	164.900000,-15.600000,40.600000,297.500000,-157.100000,415.500000,
	436.600000,371.000000,258.500000,-248.500000,302.200000,-262.300000,
	279.000000,-109.900000,-57.700000,-282.300000,-171.100000,42.200000,
	-88.300000,200.400000,-171.500000,21.100000,-81.900000,-14.100000,
	-205.200000,222.600000,-297.100000,241.200000,-286.400000,
	-13.700000,-133.200000,-234.200000,118.000000,-397.000000,
	-123.300000,-217.200000,-95.300000,-164.000000,32.200000,110.100000,
	-107.200000,-49.700000,-107.300000,-17.100000,-172.800000};
const double _model_coeff_jrm09_h[] = {0.000000,21330.500000,0.000000,
	-42027.300000,19353.200000,0.000000,-32957.300000,42084.500000,
	-27544.200000,0.000000,31994.500000,27811.200000,-926.100000,
	367.100000,0.000000,45347.900000,-749.000000,6268.500000,
	10859.600000,9608.400000,0.000000,14533.100000,-10592.900000,
	568.600000,12871.700000,-4147.800000,3604.400000,0.000000,
	-7626.300000,-10948.400000,2633.300000,5394.200000,-6050.800000,
	-1526.000000,-5684.200000,0.000000,-2409.700000,-11614.600000,
	9287.000000,-911.900000,2754.500000,-2446.100000,1207.300000,
	-2887.300000,0.000000,-8467.400000,-1383.800000,5697.700000,
	-2056.300000,3081.500000,-721.200000,1352.500000,-210.100000,
	1567.600000,0.000000,-4692.600000,4445.800000,-2378.600000,
	-2204.300000,164.100000,-1361.600000,-2031.500000,1411.800000,
	-714.300000,1676.500000,0.000000,246.000000,4100.400000,
	-3942.600000,-2078.200000,-324.400000,-1703.300000,-715.800000,
	-1400.800000,-2105.700000,-143.600000,-941.400000,0.000000,
	3918.700000,2545.400000,-2112.600000,-294.500000,1060.400000,
	-429.800000,774.800000,-837.000000,185.500000,449.400000,438.100000,
	-1132.500000,0.000000,3437.400000,133.500000,-838.300000,
	1179.400000,-120.000000,1369.200000,1291.900000,533.200000,
	-1.400000,1339.700000,1654.200000,35.200000,1516.200000,0.000000,
	186.200000,-44.600000,54.700000,802.400000,8.200000,658.800000,
	-273.600000,340.300000,-230.600000,1202.900000,-643.500000,
	-6.400000,-282.700000,143.600000,0.000000,-1159.500000,-270.000000,
	34.700000,179.100000,4.200000,311.300000,9.300000,-36.000000,
	-8.600000,1084.700000,-694.700000,-142.200000,-517.700000,
	-353.300000,-747.700000,0.000000,-928.100000,-397.000000,222.700000,
	-143.400000,231.000000,161.600000,312.000000,177.800000,778.700000,
	307.900000,-306.700000,301.600000,474.300000,43.200000,601.700000,
	638.300000,0.000000,194.100000,103.700000,743.500000,181.200000,
	467.700000,33.500000,358.700000,353.800000,799.900000,179.600000,
	267.800000,556.400000,28.400000,102.400000,531.000000,-108.700000,
	371.400000,0.000000,617.900000,-37.700000,176.300000,-18.700000,
	-174.300000,-219.000000,-85.600000,158.500000,342.700000,
	-153.600000,-34.100000,220.000000,-352.100000,107.600000,19.100000,
	-317.900000,-116.500000,22.900000,0.000000,-98.000000,-151.900000,
	-407.900000,-229.000000,-416.400000,-108.700000,-173.600000,
	129.000000,-295.400000,-221.700000,-317.600000,-54.200000,
	-329.200000,75.200000,-91.900000,-38.100000,-161.800000,-84.500000,
	-207.600000,0.000000,-417.400000,162.900000,-160.200000,116.100000,
	26.700000,150.200000,119.200000,254.800000,-488.300000,216.400000,
	-66.000000,71.500000,163.400000,-68.200000,-27.600000,129.000000,
	-42.600000,31.400000,58.600000,78.500000};
coeffStruct _model_coeff_jrm09 ={_model_coeff_jrm09_len,
								_model_coeff_jrm09_nmax,
								_model_coeff_jrm09_ndef,
								_model_coeff_jrm09_rscale,
								_model_coeff_jrm09_n,
								_model_coeff_jrm09_m,
								_model_coeff_jrm09_g,
								_model_coeff_jrm09_h};


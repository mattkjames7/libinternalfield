# libinternalfield

This is a C++ library for various internal magnetic field models which use spherical harmonics.

## Dependencies

The following things are required for building this library:

- Python 3

- numpy

- make

- g++

- binutils

## Building

Clone the repo and build in Linux or Mac OS:

```bash
git clone https://github.com/mattkjames7/libinternalfield.git
cd libinternalfield
make

#optionally install system wide
sudo make install
```

This will create a library file ```libinternalfield.so``` (`.dylib` in Mac, `.dll` in Windows). Installing system wide will place the library file in `/usr/local/lib` and the header files `internalfield.h` (for both C and C++) in `/usr/local/include` by default.

## Supported Models

Model coefficients are stored in `libinternalfield/coeffs/` as `name.dat` files, where `name` is the name of the model. Each file contains for columns:

1. Parameter string ("*g*" or "*h*")

2. Polynomial degree (*n*, integer)

3. Polynomial order (*m*, integer)

4. Magnitude (in nT, float or integer)

Any correctly formatted `.dat` file place within this folder will automatically be included within the library when it is compiled. Any additional models will be accessible using the `name` from the `.dat` file as the model string.



Here is a list of the currently supported models (more will most likely be added):

### Mercury

| Model                           | C String            | Maximum Degree | Default Degree | Reference             |
| ------------------------------- | ------------------- | -------------- | -------------- | --------------------- |
| Ness 1975                       | `ness1975`          | 1              | 1              | Ness et al., 1975     |
| Anderson 2010 Dipole            | `anderson2010d`     | 1              | 1              | Anderson et al., 2010 |
| Anderson 2010 Dipole + SHA      | `anderson2010dsha`  | 1              | 1              | Anderson et al., 2010 |
| Anderson 2010 Dipole + TS04     | `anderson2010dts04` | 1              | 1              | Anderson et al., 2010 |
| Anderson 2010 Quadrupole        | `anderson2010q`     | 2              | 2              | Anderson et al., 2010 |
| Anderson 2010 Quadrupole + SHA  | `anderson2010qsha`  | 2              | 2              | Anderson et al., 2010 |
| Anderson 2010 Quadrupole + TS04 | `anderson2010qts04` | 2              | 2              | Anderson et al., 2010 |
| Uno 2009                        | `uno2009`           | 8              | 8              | Uno et al., 2009      |
| Uno 2009 SVD                    | `uno2009svd`        | 2              | 2              | Uno et al., 2009      |
| Thebault 2018 M1                | `thebault2018m1`    | 5              | 5              | Thebault et al., 2018 |
| Thebault 2018 M2                | `thebault2018m2`    | 5              | 5              | Thebault et al., 2018 |
| Thebault 2018 M3                | `thebault2018m3`    | 5              | 5              | Thebault et al., 2018 |

### Earth

There is an IGRF model for Earth's magnetic field for every 5 years, starting in 1900 and ending 2025. A new  object will be created soon which will allow the interpolation between each of the IGRF models.

| Model                 | C String                 | Maximum Degree | Default Degree | Reference          |
| --------------------- | ------------------------ | -------------- | -------------- | ------------------ |
| IGRF 1900 - IGRF 2025 | `igrf1900` to `igrf2025` | 13             | 13             | Alken et al., 2021 |

### Mars

| Model               | C String       | Maximum Degree | Default Degree | Reference                |
| ------------------- | -------------- | -------------- | -------------- | ------------------------ |
| Gau 2021            | `gau2021`      | 110            | 110            | Gau et al., 2021         |
| Langlais et al 2019 | `langlais2019` | 134            | 134            | Langlais et al., 2019    |
| Morschhauser 2014   | `mh2014`       | 110            | 110            | Morchhauser et al., 2014 |
| Cain 2003           | `cain2003`     | 90             | 90             | Cain et al., 2003        |

### Jupiter

| Model          | C String    | Maximum Degree | Default Degree | Reference              |
| -------------- | ----------- | -------------- | -------------- | ---------------------- |
| JRM33          | `jrm33`     | 30             | 13             | Connerney et al., 2022 |
| JRM09          | `jrm09`     | 20             | 10             | Connerney et al., 2018 |
| ISaAC          | `isaac`     | 10             | 10             | Hess et al., 2017      |
| VIPAL          | `vipal`     | 5              | 5              | Hess et al., 2011      |
| VIP4           | `vip4`      | 4              | 4              | Connerney 2007         |
| VIT4           | `vit4`      | 4              | 4              | Connerney 2007         |
| O4             | `o4`        | 3              | 3              | Connerney 1981         |
| O6             | `o6`        | 3              | 3              | Connerney 2007         |
| GSFC15evs      | `gsfc15evs` | 3              | 3              | Connerney 1981         |
| GSFC15ev       | `gsfc15ev`  | 3              | 3              | Connerney 1981         |
| GSFC13ev       | `gsfc13ev`  | 3              | 3              | Connerney 1981         |
| Ulysses 17ev   | `u17ev`     | 3              | 3              | Connerney 2007         |
| SHA            | `sha`       | 3              | 3              | Connerney 2007         |
| Voyager 1 17ev | `v117ev`    | 3              | 3              | Connerney 2007         |
| JPL15ev        | `jpl15ev`   | 3              | 3              | Connerney 1981         |
| JPL15evs       | `jpl15evs`  | 3              | 3              | Connerney 1981         |
| P11A           | `p11a`      | 3              | 3              |                        |

### Saturn

| Model            | C String     | Maximum Degree | Default Degree | Reference              |
| ---------------- | ------------ | -------------- | -------------- | ---------------------- |
| Burton 2009      | `burton2009` | 3              | 3              | Burton et al., 2009    |
| Cassini 3        | `cassini3`   | 3              | 3              | Cao et al., 2011       |
| Cassini 5        | `cassini5`   | 5              | 5              | Cao et al., 2012       |
| Cassini 11        | `cassini11`   | 12            | 11            | Dougherty et al., 2018 |
| P11A             | `p11as` *    | 3              | 3              | Connerney 2007         |
| P<sub>11</sub>84 | `p1184`      | 3              | 3              | Davis and Smith 1986   |
| SOI              | `soi`        | 3              | 3              | Dougherty et al., 2007 |
| SPV              | `spv`        | 3              | 3              | Davis and Smith 1990   |
| V1               | `v1`         | 3              | 3              | Connerney et al., 1982 |
| V2               | `v2`         | 3              | 3              | Connerney et al., 1982 |
| Z3               | `z3`         | 3              | 3              | Connerney et al., 1982 |

### Uranus

| Model                   | C String     | Maximum Degree | Default Degree | Reference              |
| ----------------------- | ------------ | -------------- | -------------- | ---------------------- |
| AH5                     | `ah5`        | 4              | 4              | Herbert 2009           |
| GSFC Q3                 | `gsfcq3`     | 2              | 2              | Connerney et al., 1987 |
| GSFC Q3 (unconstrained) | `gsfcq3full` | 3              | 2              | Connerney et al., 1987 |
| Umoh                    | `umoh`       | 16             | 16             | Holme and Bloxham 1996 |

### Neptune

| Model                   | C String     | Maximum Degree | Default Degree | Reference              |
| ----------------------- | ------------ | -------------- | -------------- | ---------------------- |
| GSFC O8                 | `gsfco8`     | 3              | 3              | Connerney et al., 1991 |
| GSFC O8 (unconstrained) | `gsfco8full` | 8              | 3              | Connerney et al., 1991 |
| Nmoh                    | `nmoh`       | 16             | 16             | Holme and Bloxham 1996 |

### Ganymede

| Model                   | C String     | Maximum Degree | Default Degree | Reference              |
| ----------------------- | ------------ | -------------- | -------------- | ---------------------- |
| Kivelson et al., 2002   | `kivelson2002a` <br /> `kivelson2002b` <br /> `kivelson2002c`  | 2 <br /> 1 <br />  1   | 2  <br />  1 <br />  1  | Kivelson et al., 2002 |
| Weber et al., 2022       | `weber2022dip` <br /> `weber2022quad` | 1 <br /> 2 | 1 <br /> 2 | Weber et al., 2022 |


### Time varying models

For models which vary with time (e.g. IGRF) a chronological list of model names with associated dates and times should be provided in `libinternalfield/variable/planet/nameofmodellist.dat`

with the following columns:

1. Model C-strings

2. Integer date, in the format yyyymmdd

3. Floating point time of day in hours (e.g. 15:45 = 15.75 UT)



## Accessing Via C++

When using C++, the models field can be obtained using the ```InternalModel``` class. An instance of this class is initialized with the library called `internalModel`.

```cpp
#include <internal.h>


int main() {
    /* set current model */
    internalModel.SetModel("jrm09");

    /* set intput and output coordinates to Cartesian */
    internalModel.SetCartIn(true);
    internalModel.SetCartOut(true);

    /* input position (cartesian)*/
    double x = 35.0;
    double y = 10.0;
    double z = -4.0;

    /* output field */
    double Bx, By, Bz;
    internalModel.Field(x,y,z,&Bx,&By,&Bz);    
}
```

## Accessing Via Python

...and probably other languages. Wrapper functions are included  which can be accessed from other languages without directly interacting with the `internalModel` object:

```cpp
/* calculate the magnetic field at some sets of coordinates (p0,p1,p2) */
void InternalField(int n, double *p0, double *p1, double *p2,
                        double *B0, double *B1, double *B2);

/* same as above, with a custom maximum model degree */
void InternalFieldDeg(int n, double *p0, double *p1, double *p2,
                        int MaxDeg, double *B0, double *B1, double *B2);

/* Set the model and its input and output coordinates */ 
void SetInternalCFG(char *Model, bool CartIn, bool CartOut);

/* return the current configuration */
void GetInternalCFG(char *Model, bool *CartIn, bool *CartOut);
```

## Accessing Via C

This the header included with this project is C-compatible and includes prototypes for the wrapper functions mentioned in the Python section above. It also includes wrapper functions for every single model included in the library, where each function is named with the format `XXXXXField`, where `XXXXX` can be replaced with the lower-case name of the model (identical to the C string in the table above). The `getModelFieldPtr` function returns a pointer to a model wrapper function when given a string, see below for an example.

```c
/* contents of ctest.c */
#include <stdio.h>
#include <stdbool.h>
#include <internalfield.h>

int main() {

	printf("Testing C\n");
	
	/* try getting a model function */
	modelFieldPtr model = getModelFieldPtr("jrm33");
	double x = 10.0;
	double y = 10.0;
	double z = 0.0;
	double Bx, By, Bz;
	model(x,y,z,&Bx,&By,&Bz);

	printf("B = [%6.1f,%6.1f,%6.1f] nT at [%4.1f,%4.1f,%4.1f]\n",Bx,By,Bz,x,y,z);

	printf("C test done\n");


}

```
which can be compiled, then run using
```bash
gcc ctest.c -o ctest -lm -linternalfield
./ctest
```

## References

International Geomagnetic Reference Field: the 13th generation, Alken, P., Thébault, E., Beggan, C.D. et al. International Geomagnetic Reference Field: the thirteenth generation. Earth Planets Space 73, 49 (2021). https://doi.org/10.1186/s40623-020-01288-x

Anderson, B.J., Acuña, M.H., Korth, H. et al. The Magnetic Field of Mercury. Space Sci Rev 152, 307–339 (2010). https://doi.org/10.1007/s11214-009-9544-3

Burton, M.E., Dougherty, M.K., Russell, C.T. (2009) Model of Saturn's internal planetary magnetic field based on Cassini observations. Planetary and Space Science, 57 (14). 1706-1713 doi:10.1016/j.pss.2009.04.008

Cain, J. C., B. B. Ferguson, and D. Mozzoni, An n = 90 internal potential function of the Martian crustal magnetic field, J. Geophys. Res., 108(E2), 5008, doi:10.1029/2000JE001487, 2003.

Cao, Hao, Russell, Christopher T., Christensen, Ulrich R., Dougherty, Michele K., Burton, Marcia E. (2011) Saturn's very axisymmetric magnetic field: No detectable secular variation or tilt. Earth and Planetary Science Letters, 304 (1). 22-28 doi:10.1016/j.epsl.2011.02.035

Cao, Hao, Russell, Christopher T., Wicht, Johannes, Christensen, Ulrich R., Dougherty, Michele K. (2012) Saturn’s high degree magnetic moments: Evidence for a unique planetary dynamo. Icarus, 221 (1). 388-394 doi:10.1016/j.icarus.2012.08.007

Connerney, J. E. P. (1981), The magnetic field of Jupiter: A generalized inverse approach, *J. Geophys. Res.*, 86( A9), 7679– 7693, doi:[10.1029/JA086iA09p07679](https://doi.org/10.1029/JA086iA09p07679 "Link to external resource: 10.1029/JA086iA09p07679").

Connerney, J. E. P., Acuña, M. H., and Ness, N. F. (1982), Voyager 1 assessment of Jupiter's planetary magnetic field, *J. Geophys. Res.*, 87( A5), 3623– 3627, doi:[10.1029/JA087iA05p03623](https://doi.org/10.1029/JA087iA05p03623 "Link to external resource: 10.1029/JA087iA05p03623").

Connerney, J. E. P., Acuña, M. H., and Ness, N. F. (1987), The magnetic field of Uranus, J. Geophys. Res., 92( A13), 15329– 15336, doi:10.1029/JA092iA13p15329.

Connerney, J. E. P., Acuña, M. H., and Ness, N. F. (1991), The magnetic field of Neptune, J. Geophys. Res., 96( S01), 19023– 19042, doi:10.1029/91JA01165.

Connerney, J.E.P.. (2007). Planetary Magnetism. Treatise on Geophysics. 10. 243-280. 10.1016/B978-044452748-6.00159-0. 

Connerney, J. E. P., Kotsiaros, S., Oliversen, R. J., Espley, J. R., Joergensen, J. L., Joergensen, P. S., et al. (2018). A new model of Jupiter's magnetic field from Juno's first nine orbits. Geophysical Research Letters, 45, 2590– 2596. https://doi.org/10.1002/2018GL077312

Connerney, J. E. P., Timmins, S., Oliversen, R. J., Espley, J. R., Joergensen, J. L., Kotsiaros, S., et al. (2022). A new model of Jupiter's magnetic field at the completion of Juno's Prime Mission. Journal of Geophysical Research: Planets, 127, e2021JE007055. https://doi.org/10.1029/2021JE007055

Davis, L., and Smith, E. J. (1986), New models of Saturn's magnetic field using Pioneer 11 vector helium magnetometer data, J. Geophys. Res., 91( A2), 1373– 1380, doi:10.1029/JA091iA02p01373.

Davis, L., and Smith, E. J. (1990), A model of Saturn's magnetic field based on all available data, J. Geophys. Res., 95( A9), 15257– 15261, doi:10.1029/JA095iA09p15257.

Dougherty MK, Achilleos N, Andre N, Arridge CS, Balogh A, Bertucci C, Burton ME, Cowley SW, Erdos G, Giampieri G, Glassmeier KH, Khurana KK, Leisner J, Neubauer FM, Russell CT, Smith EJ, Southwood DJ, Tsurutani BT. Cassini magnetometer observations during Saturn orbit insertion. Science. 2005 Feb 25;307(5713):1266-70. doi: 10.1126/science.1106098. PMID: 15731444.

Dougherty, M., Cao, H., Khurana, K., Hunt, G., Provan, G., Kellock, S., et al. (2018). Saturn's magnetic field revealed by the Cassini grand finale. Science, 362, eaat5434. https://doi.org/10.1126/science.aat5434

Gao, J. W., Rong, Z. J., Klinger, L., Li, X. Z., Liu, D., & Wei, Y. (2021). A spherical harmonic Martian crustal magnetic field model combining data sets of MAVEN and MGS. Earth and Space Science, 8, e2021EA001860. https://doi.org/10.1029/2021EA001860

Herbert, F. (2009), Aurora and magnetic field of Uranus, J. Geophys. Res., 114, A11206, doi:10.1029/2009JA014394.

Hess, S. L. G., Bonfond, B., Zarka, P., and Grodent, D. (2011), Model of the Jovian magnetic field topology constrained by the Io auroral emissions, *J. Geophys. Res.*, 116, A05217, doi:[10.1029/2010JA016262](https://doi.org/10.1029/2010JA016262 "Link to external resource: 10.1029/2010JA016262").

Hess, S., Bonfond, B., Bagenal, F., & Lamy, L. (2017). A model of the Jovian internal field derived from in-situ and auroral constraints, doi:[10.1553/PRE8s157](https://doi.org/10.1553/PRE8s157)

Holme, R., and Bloxham, J. (1996), The magnetic fields of Uranus and Neptune: Methods and models, *J. Geophys. Res.*, 101( E1), 2177– 2200, doi:[10.1029/95JE03437](https://doi.org/10.1029/95JE03437 "Link to external resource: 10.1029/95JE03437").

M.G. Kivelson, K.K. Khurana, M. Volwerk, The Permanent and Inductive Magnetic Moments of Ganymede, Icarus, Volume 157, Issue 2, 2002, Pages 507-522, ISSN 0019-1035, https://doi.org/10.1006/icar.2002.6834.

Langlais, B., Thébault, E., Houliez, A., Purucker, M. E., & Lillis, R. J. (2019). A new model of the crustal magnetic field of Mars using MGS and MAVEN. *Journal of Geophysical Research: Planets*, 124, 1542– 1569. [A New Model of the Crustal Magnetic Field of Mars Using MGS and MAVEN - Langlais - 2019 - Journal of Geophysical Research: Planets - Wiley Online Library](https://doi.org/10.1029/2018JE005854)

Morschhauser, A., V. Lesur, and M. Grott (2014), A spherical harmonic model of the lithospheric magnetic field of Mars, J. Geophys. Res. Planets, 119, 1162–1188, doi:10.1002/2013JE004555.

Ness, N. F., Behannon, K. W., Lepping, R. P., and Whang, Y. C. (1975), The magnetic field of Mercury, 1, *J. Geophys. Res.*, 80( 19), 2708– 2716, doi:[10.1029/JA080i019p02708](https://doi.org/10.1029/JA080i019p02708 "Link to external resource: 10.1029/JA080i019p02708").

Thebault, E., Langlais, B., Oliveira, J.S., et al., 2018. A time-averaged regional model of the Hermean magnetic field. Phys. Earth Planet. In. 276, 93–105. https://doi.org/10.1016/j.pepi.2017.07.001.

Uno, H., Johnson, C.L., Anderson, B.J., Korth, H., Solomon, S.C., 2009. Modeling Mercury’s internal magnetic field with smooth inversions. Earth Planet. Sci. Lett. 285, 328–339. http://dx.doi.org/10.1016/j.epsl.2009.02.032

Weber, T., Moore, K., Connerney, J., Espley, J., DiBraccio, G., & Romanelli, N. (2022). Updated spherical harmonic magnetic field moments of Ganymede from the Juno flyby. Geophysical Research Letters, 49, e2022GL098633. https://doi.org/10.1029/2022GL098633
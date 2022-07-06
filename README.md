# libinternalfield

This is a C++ library for various internal magnetic field models which us spherical harmonics.

## Dependencies

The following things are required for building this library:

- Python 3

- numpy

- make

- g++

- binutils

## Building

Clone the repo and build:

```bash
git clone https://github.com/mattkjames7/libinternalfield.git
cd libinternalfield
make
```

This will create a shared object file ```libinternalfield.so``` with a symbolic link in the current working directory.

## Supported Models

Here is a list of the currently supported models (more will most likely be added):

| Model               | C String       | Maximum Degree | Default Degree | Planet  | Reference              |
| ------------------- | -------------- | -------------- | -------------- | ------- | ---------------------- |
| Ness 1975           | `ness1975`     | 1              | 1              | Mercury | Ness et al., 1975      |
| Langlais et al 2019 | `langlais2019` | 134            | 134            | Mars    | Langlais et al., 2019  |
| JRM33               | `jrm33`        | 30             | 13             | Jupiter | Connerney et al., 2022 |
| JRM09               | `jrm09`        | 20             | 10             | Jupiter | Connerney et al., 2018 |
| ISaAC               | `isaac`        | 10             | 10             | Jupiter | Hess et al., 2017      |
| VIPAL               | `vipal`        | 5              | 5              | Jupiter | Hess et al., 2011      |
| VIP4                | `vip4`         | 4              | 4              | Jupiter | Connerney 2007         |
| VIT4                | `vit4`         | 4              | 4              | Jupiter | Connerney 2007         |
| O4                  | `o4`           | 3              | 3              | Jupiter | Connerney 1981         |
| O6                  | `o6`           | 3              | 3              | Jupiter | Connerney 2007         |
| GSFC15evs           | `gsfc15evs`    | 3              | 3              | Jupiter | Connerney 1981         |
| GSFC15ev            | `gsfc15ev`     | 3              | 3              | Jupiter | Connerney 1981         |
| GSFC13ev            | `gsfc13ev`     | 3              | 3              | Jupiter | Connerney 1981         |
| Ulysses 17ev        | `u17ev`        | 3              | 3              | Jupiter | Connerney 2007         |
| SHA                 | `sha`          | 3              | 3              | Jupiter | Connerney 2007         |
| Voyager 1 17ev      | `v117ev`       | 3              | 3              | Jupiter | Connerney 2007         |
| JPL15ev             | `jpl15ev`      | 3              | 3              | Jupiter | Connerney 1981         |
| JPL15evs            | `jpl15evs`     | 3              | 3              | Jupiter | Connerney 1981         |

Model coefficients are stored in `libinternalfield/coeffs/` as `name.dat` files, where `name` is the name of the model. Each file contains for columns: 

1. Parameter string ("*g*" or "*h*")

2. Polynomial degree (*n*, integer)

3. Polynomial order (*m*, integer)

4. Magnitude (in nT, float or integer)

Any correctly formatted `.dat` file place within this folder will automatically be included within the library when it is compiled. Any additional models will be accessible using the `name` from the `.dat` file as the model string.

## Accessing Via C++

When using C++, the models field can be obtained using the ```InternalModel``` class. An instance of this class is initialized with the library called `internalModel`.

```cpp
#include "libinternal.h"


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

## References

Connerney, J. E. P. (1981), The magnetic field of Jupiter: A generalized inverse approach, *J. Geophys. Res.*, 86( A9), 7679– 7693, doi:[10.1029/JA086iA09p07679](https://doi.org/10.1029/JA086iA09p07679 "Link to external resource: 10.1029/JA086iA09p07679").

Connerney, J. E. P., Acuña, M. H., and Ness, N. F. (1982), Voyager 1 assessment of Jupiter's planetary magnetic field, *J. Geophys. Res.*, 87( A5), 3623– 3627, doi:[10.1029/JA087iA05p03623](https://doi.org/10.1029/JA087iA05p03623 "Link to external resource: 10.1029/JA087iA05p03623").

Connerney, J.E.P.. (2007). Planetary Magnetism. Treatise on Geophysics. 10. 243-280. 10.1016/B978-044452748-6.00159-0. 

Connerney, J. E. P., Kotsiaros, S., Oliversen, R. J., Espley, J. R., Joergensen, J. L., Joergensen, P. S., et al. (2018). A new model of Jupiter's magnetic field from Juno's first nine orbits. Geophysical Research Letters, 45, 2590– 2596. https://doi.org/10.1002/2018GL077312

Connerney, J. E. P., Timmins, S., Oliversen, R. J., Espley, J. R., Joergensen, J. L., Kotsiaros, S., et al. (2022). A new model of Jupiter's magnetic field at the completion of Juno's Prime Mission. Journal of Geophysical Research: Planets, 127, e2021JE007055. https://doi.org/10.1029/2021JE007055

Hess, S. L. G., Bonfond, B., Zarka, P., and Grodent, D. (2011), Model of the Jovian magnetic field topology constrained by the Io auroral emissions, *J. Geophys. Res.*, 116, A05217, doi:[10.1029/2010JA016262](https://doi.org/10.1029/2010JA016262 "Link to external resource: 10.1029/2010JA016262").

Hess, S., Bonfond, B., Bagenal, F., & Lamy, L. (2017). A model of the Jovian internal field derived from in-situ and auroral constraints, doi:[10.1553/PRE8s157](https://doi.org/10.1553/PRE8s157)

Langlais, B., Thébault, E., Houliez, A., Purucker, M. E., & Lillis, R. J. (2019). A new model of the crustal magnetic field of Mars using MGS and MAVEN. *Journal of Geophysical Research: Planets*, 124, 1542– 1569. [A New Model of the Crustal Magnetic Field of Mars Using MGS and MAVEN - Langlais - 2019 - Journal of Geophysical Research: Planets - Wiley Online Library](https://doi.org/10.1029/2018JE005854)

Ness, N. F., Behannon, K. W., Lepping, R. P., and Whang, Y. C. (1975), The magnetic field of Mercury, 1, *J. Geophys. Res.*, 80( 19), 2708– 2716, doi:[10.1029/JA080i019p02708](https://doi.org/10.1029/JA080i019p02708 "Link to external resource: 10.1029/JA080i019p02708").

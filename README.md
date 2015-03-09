cpp_rg_benchmark
================

This contains some speed benchmarks for generating random numbers following a number
of different distributions using `std::random` and `boost::random`.

Testing
-------
Use the commands
```
make
./benchmark
```
to run the benchmark. You need to install boost and a recent version g++.


Results
-------
In short, the results which may be specific to my system and the tested
distribution are:

- `boost::random` is consistently faster than `std::random`
- Doing the quantile transformations myself is consistently faster than using the
  distributions build in the library.


Dist,Lib,Mechanism,Time,Avg
Unif,C++11,mt32,1.86187e-08,0.499966
Unif,C++11,mt64,1.52674e-08,0.500028
Unif,boost,mt,6.29142e-09,0.499998
Expo,C++11,native,8.16604e-08,1.00006
Expo,C++11,quantile,7.87812e-08,0.99994
Expo,C++11,quantile fastlog,3.09441e-08,1.00007
Expo,boost,native,7.49275e-08,0.999757
Expo,boost,quantile,7.31967e-08,1.00012
Expo,boost,quantile fastlog,1.59732e-08,1.0002
UINT,C++11,native,4.19813e-08,3.50008
UINT,C++11,quantile,2.67119e-08,3.49985
UINT,boost,native,3.71464e-08,3.49992
UINT,boost,quantile,1.2339e-08,3.49994

#include <ctime>
#include <random>
#include <iostream>
#include <cmath>

#include <boost/random.hpp>

#include "fastfunc.h"

std::mt19937 mt_(17); 
std::mt19937_64 mt_64(17); 
std::uniform_real_distribution<> unif_(0, 1);
std::exponential_distribution<> expo_(1);
std::uniform_int_distribution<> uint_(1, 6);

clock_t begin;
clock_t end;
double elapsed_secs;
double sum = 0;
size_t n = std::pow(10,8);
FastFunc ff;

boost::mt19937 boost_rng;   
boost::uniform_01<> boost_unif;
boost::variate_generator<boost::mt19937&, boost::uniform_01<> > boost_smpl(boost_rng, boost_unif);

boost::exponential_distribution<> boost_expo(1);
boost::variate_generator<boost::mt19937&, boost::exponential_distribution<> > boost_expo_smpl(boost_rng, boost_expo);
  
boost::uniform_int<> six(1,6);
boost::variate_generator<boost::mt19937&, boost::uniform_int<> >boost_uint_smpl(boost_rng, six);

int main() {
  std::cout << "Dist,Lib,Mechanism,Time,Avg" << std::endl;
  begin = std::clock();
  for (size_t i = 0; i < n; ++i) sum += unif_(mt_);  
  end = std::clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / n;
  std::cout << "Unif,C++11,mt32," << elapsed_secs << "," << sum / n << std::endl;
  
  sum = 0;
  begin = std::clock();
  for (size_t i = 0; i < n; ++i) sum += unif_(mt_64);  
  end = std::clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / n;
  std::cout << "Unif,C++11,mt64," << elapsed_secs << "," << sum / n << std::endl;

  sum = 0;
  begin = std::clock();
  for (size_t i = 0; i < n; ++i) sum += boost_smpl();  
  end = std::clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / n;
  std::cout << "Unif,boost,mt," << elapsed_secs << "," << sum / n << std::endl;

  sum = 0;
  begin = std::clock();
  for (size_t i = 0; i < n; ++i) sum += expo_(mt_);  
  end = std::clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / n;
  std::cout << "Expo,C++11,native," << elapsed_secs << "," << sum / n << std::endl;

  sum = 0;
  begin = std::clock();
  for (size_t i = 0; i < n; ++i) sum += -std::log(unif_(mt_));  
  end = std::clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / n;
  std::cout << "Expo,C++11,quantile," << elapsed_secs << "," << sum / n << std::endl;

  sum = 0;
  begin = std::clock();
  for (size_t i = 0; i < n; ++i) sum += -ff.fastlog(unif_(mt_));  
  end = std::clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / n;
  std::cout << "Expo,C++11,quantile fastlog," << elapsed_secs << "," << sum / n << std::endl;

  sum = 0;
  begin = std::clock();
  for (size_t i = 0; i < n; ++i) sum += boost_expo_smpl();  
  end = std::clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / n;
  std::cout << "Expo,boost,native," << elapsed_secs << "," << sum / n << std::endl;

  sum = 0;
  begin = std::clock();
  for (size_t i = 0; i < n; ++i) sum += -std::log(boost_smpl());  
  end = std::clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / n;
  std::cout << "Expo,boost,quantile," << elapsed_secs << "," << sum / n << std::endl;

  sum = 0;
  begin = std::clock();
  for (size_t i = 0; i < n; ++i) sum += -ff.fastlog(boost_smpl());  
  end = std::clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / n;
  std::cout << "Expo,boost,quantile fastlog," << elapsed_secs << "," << sum / n << std::endl;

  sum = 0;
  begin = std::clock();
  for (size_t i = 0; i < n; ++i) sum += uint_(mt_);  
  end = std::clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / n;
  std::cout << "UINT,C++11,native," << elapsed_secs << "," << sum / n << std::endl;

  sum = 0;
  begin = std::clock();
  for (size_t i = 0; i < n; ++i) sum += static_cast<int>(unif_(mt_)*6)+1;  
  end = std::clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / n;
  std::cout << "UINT,C++11,quantile," << elapsed_secs << "," << sum / n << std::endl;
  
  sum = 0;
  begin = std::clock();
  for (size_t i = 0; i < n; ++i) sum += boost_uint_smpl();
  end = std::clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / n;
  std::cout << "UINT,boost,native," << elapsed_secs << "," << sum / n << std::endl;

  sum = 0;
  begin = std::clock();
  for (size_t i = 0; i < n; ++i) sum += static_cast<int>(boost_smpl()*6)+1;  
  end = std::clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / n;
  std::cout << "UINT,boost,quantile," << elapsed_secs << "," << sum / n << std::endl;

  return 0;
}

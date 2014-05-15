#include <ctime>
#include <random>
#include <iostream>
#include <cmath>

#include "fastfunc.h"

std::mt19937 mt_(17); 
std::uniform_real_distribution<> unif_(0, 1);
std::exponential_distribution<> expo_(1);
std::uniform_int_distribution<> uint_(0, 6);

clock_t begin;
clock_t end;
double elapsed_secs;
double sum = 0;
size_t n = std::pow(10,8);
FastFunc ff;

int main() {
  begin = std::clock();
  for (size_t i = 0; i < n; ++i) sum += unif_(mt_);  
  end = std::clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / n;
  std::cout << "Unif C11: " << elapsed_secs << " " << sum / n << std::endl;
  
  sum = 0;
  begin = std::clock();
  for (size_t i = 0; i < n; ++i) sum += expo_(mt_);  
  end = std::clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / n;
  std::cout << "Expo C11: " << elapsed_secs << " " << sum / n << std::endl;
  
  sum = 0;
  begin = std::clock();
  for (size_t i = 0; i < n; ++i) sum += -std::log(unif_(mt_));  
  end = std::clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / n;
  std::cout << "Expo QUA: " << elapsed_secs << " " << sum / n << std::endl;

  sum = 0;
  begin = std::clock();
  for (size_t i = 0; i < n; ++i) sum += -ff.fastlog(unif_(mt_));  
  end = std::clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / n;
  std::cout << "Expo QFF: " << elapsed_secs << " " << sum / n << std::endl;

  sum = 0;
  begin = std::clock();
  for (size_t i = 2; i < n+2; ++i) sum += uint_(mt_);  
  end = std::clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / n;
  std::cout << "UINT C11: " << elapsed_secs << " " << sum / n << std::endl;

  sum = 0;
  begin = std::clock();
  for (size_t i = 2; i < n+2; ++i) sum += std::uniform_int_distribution<>(1, i)(mt_);  
  end = std::clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / n;
  std::cout << "UINT C11: " << elapsed_secs << " " << sum / n << std::endl;

  sum = 0;
  begin = std::clock();
  for (size_t i = 2; i < n+2; ++i) sum += static_cast<int>(unif_(mt_)*i);  
  end = std::clock();
  elapsed_secs = double(end - begin) / CLOCKS_PER_SEC / n;
  std::cout << "UINT QUA: " << elapsed_secs << " " << sum / n << std::endl;

  return 0;
}

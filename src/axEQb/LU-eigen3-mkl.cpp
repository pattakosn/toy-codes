// // g++ -Wall -Wextra --std=gnu++14 -O3 -mtune=native -DNDEBUG -fopenmp
//
// // g++ -Wall -Wextra --std=gnu++14 -O3 -mtune=native -DNDEBUG -fopenmp axEQb.cpp   -m64 -I${MKLROOT}/include  -Wl,--start-group
// ${MKLROOT}/lib/intel64/libmkl_intel_lp64.a ${MKLROOT}/lib/intel64/libmkl_gnu_thread.a ${MKLROOT}/lib/intel64/libmkl_core.a -Wl,--end-group -lgomp -lpthread
// -lm -ldl
// //#define EIGEN_USE_MKL_ALL
//
// #include <eigen3/Eigen/LU>
// #include <eigen3/Eigen/Dense>
// #include <iostream>
// using namespace Eigen;
// const size_t DIM = 16 * 1024;
// int main( void )
// {
// 	MatrixXd A = MatrixXd::Random(DIM,DIM);
// 	VectorXd b = VectorXd::Random(DIM);
// 	VectorXd x;
// 	x = A.lu().solve(b);
// //	std::cout << "A=" << A << std::endl << std::endl;
// //	std::cout << "x=" << x << std::endl << std::endl;
// //	std::cout << "b=" << b << std::endl << std::endl;
// 	std::cout << "b( " << DIM/2 << " )=" << b(DIM / 2) << std::endl << std::endl;
// }
#include <benchmark/benchmark.h>
#define EIGEN_USE_MKL_ALL
#include <eigen3/Eigen/Dense>
#include <eigen3/Eigen/LU>

using namespace Eigen;

// NIKOS TODO: possibly compare LU implementations? eg mkl, openblas, etc
static void LU_IMKL(benchmark::State &state) {
  for (auto _ : state) {
    // omp_set_num_threads(state.range(1));
    omp_set_num_threads(6);
    size_t DIM = state.range(0);
    MatrixXd A = MatrixXd::Random(DIM, DIM);
    VectorXd b = VectorXd::Random(DIM);
    VectorXd x;
    x = A.lu().solve(b);
  }
}
// BENCHMARK(AxEQb_LU)->RangeMultiplier(2)->DenseRange(64, 4*1024, 64)->UseRealTime()->Unit(benchmark::kMillisecond)->Threads(4);
BENCHMARK(LU_IMKL)->RangeMultiplier(2)->Range(2 * 1024, 8 * 1024)->UseRealTime()->Unit(benchmark::kMillisecond);
// BENCHMARK(AxEQb_LU)->RangeMultiplier(2)->Range(1024, 8*1024)->Unit(benchmark::kMillisecond);
// BENCHMARK(AxEQb_LU)->RangeMultiplier(2)->Range(1024, 8*1024)->Unit(benchmark::kMillisecond);
// BENCHMARK(AxEQb_LU)->RangeMultiplier(2)->Range(1024, 8*1024)->Unit(benchmark::kMillisecond);

BENCHMARK_MAIN();

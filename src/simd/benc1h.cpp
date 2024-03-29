int main() {
  int A[4] = {1,2,3,4};
  int B[4] = {4,3,2,1};

  // now we create two 128-bit vectors storing A and B
  
  __m128i vec_a = _mm_set_epi32(A[3], A[2], A[1], A[0]);
  __m128i vec_b = _mm_set_epi32(B[3], B[2], B[1], B[0]);
  
  // now we add the two vectors and store them in vec_c.
  // note that this happens by just using one instruction 
  // in assembly level.

  __m128i vec_c = _mm_add_epi32(vec_a, vec_b);

  // now we cast back the vector to an integer pointer.
  int *C = (int*)(&vec_c);
  for (int i = 0; i < 4; i++) {
    std::cout << C[i] << std::endl;
  }

  return 0;
}



__m128i add4(__m128i a, __m128i b) {
  return _mm_add_epi32(a, b);
}
__m128i loadu_si128(void *m) {
  return _mm_loadu_si128((const __m128i*) m);
}
void sum_arrays(int *A, int *B, int *C, int len) {
  for (int i = 0; i < len; i += 4) {
    __m128i v1 = loadu_si128(&A[i]);
    __m128i v2 = loadu_si128(&B[i]);
    __m128i res = add4(v1, v2);
    store_si128(&C[i], res);
  }
}

// handles tail scalarly
void sum_arrays(int *A, int *B, int *C, int len) {
  int end = (len % 4 == 4) ? len : len - 4;
  int end = len & -4;
  int i =0;
  for (; i < end; i += 4) {
    __m128i v1 = loadu_si128(&A[i]);
    __m128i v2 = loadu_si128(&B[i]);
    __m128i res = add4(v1, v2);
    store_si128(&C[i], res);
  }
  for (; i < len; ++i) {
    C[i] = A[i] + B[i];
  }
}
// handles tail vectorizedly but computes some items 2 times
void sum_arrays(int *A, int *B, int *C, int len) {
  int end = (len % 4 == 4) ? len : len - 4;
  int i = 0;
  for (; i < end; i += 4) {
    __m128i v1 = loadu_si128(&A[i]);
    __m128i v2 = loadu_si128(&B[i]);
    __m128i res = add4(v1, v2);
    store_si128(&C[i], res);
  }
  // Last 4 iterations and we may repeat some.
  int index = len - 4;
  __m128i v1 = loadu_si128(&A[index]);
  __m128i v2 = loadu_si128(&B[index]);
  __m128i res = add4(v1, v2);
  store_si128(&C[index], res);
}


float a[VECTOR_WIDTH];
float b[VECTOR_WIDTH];
float out[VECTOR_WIDTH];
// B
// Fill the arrays
if (cond) {
	A
  for (int i = 0; i < VECTOR_WIDTH; ++i)
    out[i] = a[i] + b[i];
}
__m128 a_vector = _mm_loadu_ps(&a[0]);
__m128 b_vector = _mm_loadu_ps(&b[0]);
if (cond) {
  __m128 res = _mm_add_ps(a_vector, b_vector)
  _mm_storeu_ps(&out[0], res);
}

for (int i = 0; i < N; ++i) {
  if (cond[i]) {  // Divergent condition (and hence divergent branch) 
    value[i] = some computation;
  } else {
    value[i] = some other computation;
  }
}
#include <immintrin.h>
#include <stdio.h>
#include <string.h>

float a[4] = {1.0, 2.0, 3.0, 4.0};
float b[4] = {5.0, 6.0, 7.0, 8.0};
float cond[4] = {0.0, 0.0, 1.0, 0.0};
float out[4] = {100.0, 200.0, 300.0, 400.0};

// Don't inline this so that the vectorized part of the code
// stays clean in assembly.
void __attribute__ ((noinline)) print_out() {
  printf("%f %f %f %f\n", out[0], out[1], out[2], out[3]);
}

int main(void) {
  // Load the two vectors to be summed.
  __m128 av = _mm_loadu_ps((const float *)a);
  __m128 bv = _mm_loadu_ps((const float *)b);

  // Load the vector that has the previous values of `out`
  __m128 prev = _mm_loadu_ps((const float *)out);
  // Sum the two input vectors
  __m128 sum = _mm_add_ps(av, bv);

  // Load the condition
  __m128 cond_v = _mm_loadu_ps((const float *)cond);
  // Create a vector filled with zeroes.
  __m128 zero = _mm_set_ps1(0.0);
  // Fill a lane of `mask` with 1s if the corresponding lane
  // of `cond_v` is _not_ zero.
  __m128 mask = _mm_cmp_ps(cond_v, zero, _CMP_EQ_OQ);

  // Blend the result; `res` will get from `sum` if the corresponding
  // lane of `cond_v` was _not_ zero, otherwise it will get from `prev`.
  __m128 res = _mm_blendv_ps(sum, prev, mask);
  // Store the final result.
  _mm_storeu_ps((float *)out, res);

  print_out();

  return 0;
}


addition reduction:
int get_low_32_bits_si128(__m128i v) {
  return _mm_cvtsi128_si32(v);
}
int add_all_lanes_epi32(__m128i v) {
  v = _mm_hadd_epi32(v, v);
  v = _mm_hadd_epi32(v, v);
  return get_low_32_bits_si128(v);
}
int sum_of_array(int *A, int len) {
  int end = (len % 4 == 0) ? len : len - 4;
  int i = ;
  __m128i acc = // Register with all lanes equal to 0;
  for (int i = 0; i < end; i += 4) {
    __m128i v = loadu_si128(&A[i]);
    acc = add4(v);
  }
  int final_result = add_all_lanes_epi32(acc);
  for (; i < len; ++i) {
    final_result += a[i];
  }
  return final_result;
}

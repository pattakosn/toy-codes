// Benchmark remove leading and trailing spaces from strings
// Implementations found here:
//     https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
//     https://duckduckgo.com/?q=std+string+trim+leading+and+end+space&t=ffab&atb=v203-1&ia=web

#include <benchmark/benchmark.h>
#include "trim_leading_trailing_white_space_from_strings.h"


string s1 {"\n\tHello World  \r\n" };


static void string_trim_with_first_last_not_of_n_substr(benchmark::State &state)
{
	first_last_not_of_n_substr trim;
	for (auto _ : state)
		trim( s1 );
}
BENCHMARK(string_trim_with_first_last_not_of_n_substr);


static void string_trim_with_find_if_and_erase(benchmark::State &state)
{
	find_if_and_erase trim;
	for (auto _ : state)
		trim(s1);
}
BENCHMARK(string_trim_with_find_if_and_erase);

static void string_trim_with_hand_written_code(benchmark::State &state)
{
	hand_written_code trim;
	for (auto _ : state)
		trim(s1);
}
BENCHMARK(string_trim_with_hand_written_code);

static void string_trim_with_cpp11_regex(benchmark::State &state)
{
	cpp11_regex trim;
	for (auto _ : state)
		trim(s1);
}
BENCHMARK(string_trim_with_cpp11_regex);

static void string_trim_with_using_boost(benchmark::State &state)
{
	using_boost trim;
	for (auto _ : state)
		trim(s1);
}
BENCHMARK(string_trim_with_using_boost);

BENCHMARK_MAIN();

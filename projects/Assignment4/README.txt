TEST: 1  PASS: 1.0 = 1.0
TEST: 2  PASS: 10.0 = 10.0
TEST: 3  PASS: 5.5 = 5.5
TEST: 4  PASS: 8.0 = 8.0
TEST: 5  PASS: 6.8 = 6.8
TEST: 6  FAIL: 5.5 != 5.6 rounding
TEST: 7  PASS: 5.5 = 5.5
TEST: 8  PASS: 5.8 = 5.8
TEST: 9  FAIL: 6.8 != 6.9 expected rounding error
TEST: 10  PASS: 7.1 = 7.1
TEST: 11  PASS: 10.0 = 10.0
TEST: 12  PASS: 10.0 = 10.0

I passed 10 out of 12.

using level 1 optimization (my default):

using fixed point calculation the calc_average takes 460 states
using float point calculation the calc_average takes 549 states

using level 3 optimization:

using fixed point calculation the calc_average takes 460 states 44679 - 44219
using float point calculation the calc_average takes 548 states 44662 - 44114

my conclusion hereby is that while fixed point calculation is slightly more efficient,
unless it is called thousents or millions of times, the difference is minimal and rounding of floats is more accurate (even if 11 of 12 passed).


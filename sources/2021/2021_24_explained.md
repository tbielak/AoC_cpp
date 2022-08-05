## 2021/24 solution explained

Implementing virtual CPU to execute ALU program provided on input is a bad idea. It would be far too slow. Much better approach is to analyze the input and process it somehow...

ALU program (puzzle input) has 252 instructions. The program can be divided into 14 blocks of 18 instructions. Each block starts with `inp w` instruction, which reads an input value (n<sup>th</sup> digit of the submarine's model number, `n=1..14`) and stores it in `w` register.

All blocks are almost the same, they differ only in three places: numeric arguments of 5<sup>th</sup>, 6<sup>th</sup> and 16<sup>th</sup> instruction of the block. Let's name these arguments `A`, `B` and `C`. Now each block looks like shown below:

```C++
ins#   -code---    C/C++ equivalent
-----------------------------------------------------------
 1.    inp w       w = get_next_digit_from_model_number();
 2.    mul x 0     x *= 0;
 3.    add x z     x += z;
 4.    mod x 26    x %= 26;
 5.    div z A     z /= A;
 6.    add x B     x += B;
 7.    eql x w     x = (x == w) ? 1 : 0;
 8.    eql x 0     x = (x == 0) ? 1 : 0;
 9.    mul y 0     y *= 0;
10.    add y 25    y += 25;
11.    mul y x     y *= x;
12.    add y 1     y += 1;
13.    mul z y     z *= y;
14.    mul y 0     y *= 0;
15.    add y w     y += w;
16.    add y C     y += C;
17.    mul y x     y *= x;
18.    add z y     z += y;
```

__Note:__ Input shall follow this pattern. The solution strongly relies on it, but the code does not check it!

Quote from puzzle description:
>The ALU is a four-dimensional processing unit: it has integer variables `w`, `x`, `y`, and `z`. These variables all start with the value `0`.

The block shown above uses variable `w` to transport digit from input, variables `x` and `y` are zeroed when processing each digit (see 2<sup>nd</sup> and 9<sup>th</sup> instruction), only `z` value is preserved and modified during subsequent execution of the code (subsequent digits).

>Then, after MONAD has finished running all of its instructions, it will indicate that the model number was __valid__ by leaving a `0` in variable `z` - this is the goal.

Let's transform C/C++ equivalent code a bit:

```C++
ins#   -code---           C/C++ equivalent
------------------------------------------------------------------
 1.    inp w     -------> w = get_next_digit_from_model_number();
 2.    mul x 0   ---+
 3.    add x z      |
 4.    mod x 26  ---+---> x = z % 26;
 5.    div z A   -------> z /= A;
 6.    add x B   ---+
 7.    eql x w      |
 8.    eql x 0   ---+---> x = (x + B == w) ? 0 : 1;
 9.    mul y 0   ---+
10.    add y 25     |
11.    mul y x      |
12.    add y 1   ---+---> y = 25 * x + 1;
13.    mul z y   -------> z *= y;
14.    mul y 0   ---+
15.    add y w      |
16.    add y C      |
17.    mul y x   ---+---> y = (w + C) * x;
18.    add z y   -------> z += y;
```

Let's assume that `A`, `B` and `C` are arrays containing numbers for each i<sup>th</sup> block from input (`i=0..13`), and that `w` is 14-element array containing digits of submarine's model number being validated - see `Solver` class private members:

```C++
vector<int> _A, _B, _C, _w;
```

Now we can take the code above and write `Solver::execute_block` method which updates `z` variable executing i<sup>th</sup> block of input:

```C++
int64_t Solver::execute_block(int64_t z, size_t i)
{
    int64_t x = z % 26;
    z /= _A[i];
    x = (x + _B[i] == _w[i]) ? 0 : 1;
    int y = 25 * x + 1;
    z *= y;
    y = (_w[i] + _C[i]) * x;
    z += y;
    return z;
}
```

Let's simplify it!

Take a look at the comparison:

```C++
x + _B[i] == _w[i]
```

When it is `true` we've got the following situation:

```C++
int64_t Solver::execute_block(int64_t z, size_t i)
{
    int64_t x = z % 26;
    z /= _A[i];
    x = (x + _B[i] == _w[i]) ? 0 : 1;     // x = 0
    int y = 25 * x + 1;                   // y = 1
    z *= y;                               // z is not changed (multiplied by 1)
    y = (_w[i] + _C[i]) * x;              // y is zeroed (by x = 0)
    z += y;                               // z is not changed (zero is added)
    return z;
}
```

When it is `false`:

```C++
int64_t Solver::execute_block(int64_t z, size_t i)
{
    int64_t x = z % 26;
    z /= _A[i];
    x = (x + _B[i] == _w[i]) ? 0 : 1;     // x = 1
    int y = 25 * x + 1;                   // y = 26
    z *= y;                               // z is multiplied by 26
    y = (_w[i] + _C[i]) * x;              // y is set to _w[i] + _C[i]
    z += y;                               // y is added to z
    return z;
}
```

Taking these observations into account, we can transform `Solver::execute_block` method to:

```C++
int64_t Solver::execute_block(int64_t z, size_t i)
{
    int64_t x = z % 26;
    z /= _A[i];

    if (x + _B[i] == _w[i])
        return z;

    return z * 26 + _w[i] + _C[i];
}
```

It is much clearer now what happens there, and this method is quite fast to execute! To check any submarine's model number we need to call `Solver::execute_block` 14 times and if returned value of last call is zero than we found a valid number.

--------

Now, let's consider a trivial, brute-force solution:
- for part one (finding highest valid number): start from 99999999999999, check if it's valid, if not - decrease the number and check again; repeat until you succeed;
- for part two (finding lowest valid number): start from 11111111111111, check if it's valid, if not - increase the number and check again; repeat until you succeed.

Unfortunatelly, in the worst case scenario (when both numbers are near the middle of 11111111111111..99999999999999 range) we need to check almost 9<sup>14</sup> numbers... Not possible in our __lifespan__!

Assuming we are not so clever to find O(1)-class algorithm to solve it, we need to find anything which allows to safely skip bunches of numbers in brute-force solution.

Let's take a closer look at `A`, `B` and `C` arrays.

`Solver` class constructor reads these values from input, assuming that the input is valid (follows already mentioned pattern):

```C++
Solver::Solver(const vector<string>& input, int w_init)
{
	for (int i = 0; i < 14; i++)
	{
		_A.push_back(stoi(input[i * 18 + 4].substr(6)));
		_B.push_back(stoi(input[i * 18 + 5].substr(6)));
		_C.push_back(stoi(input[i * 18 + 15].substr(6)));
	}
	...
}
```
Here are the arrays from my input:

```C++
A = {   1,   1,   1,  26,   1,  26,   1,   1,   1,  26,  26,  26,  26,  26 }
B = {  12,  10,  10,  -6,  11, -12,  11,  12,  12,  -2,  -5,  -4,  -4, -12 }
C = {   6,   2,  13,   8,  13,   8,   3,  11,  10,   8,  14,   6    8,   2 }
```

Observations/assumptions made:
- `A` array has exactly seven elements = `1` and seven elements = `26`
- when `A == 1` then `B` is positive, otherwise it is negative
- `abs(B[i]) + 9` is less than `26`
- `C[i]` is always positive and `C[i] + 9` is less than `26`

Number `9` mentioned above is the highest digit used in submarine's model number and `26` is very important number, which is clearly visible when you look at `Solver::execute_block` implementation and `A` array values.

__Note:__ Input shall meet these assumptions. The solution strongly relies on them, but the code does not check the input!

--------

Now, let's see what happens with `z` value when executing `Solver::execute_block` method with `A[i] == 1`:

```C++
int64_t Solver::execute_block(int64_t z, size_t i)
{
    int x = z % 26;                    // [1]
    z /= _A[i];                        // [2]

    if (x + _B[i] == _w[i])            // [3]
        return z;                      // [4]

    return z * 26 + _w[i] + _C[i];     // [5]
}
```

At: <br />
[1] `x` becomes a number in 0..25 range. <br />
[2] `z` is divided by 1 (not changed). <br />
[3] `x` is updated and now there is a chance it will match digit on input (`w[i]`) <br />
[4] if so: `z` is returned (not changed). <br />
[5] otherwise: `z` is multiplied by 26 and some number less than 26 is added.

In other words:
- operations [2] and [4] leave `z` unchanged
- operations [2] and [5] can increase `z` at least 26 times

Looking at `z` as a number in numeral system with 26 as its base you can say that:
- operations [2] and [4] leave `z` in the same order of magnitude
- operations [2] and [4] increase `z` number by one order of magnitude

--------

And what happens with `z` value when executing `Solver::execute_block` method with `A[i] == 26`?

```C++
int64_t Solver::execute_block(int64_t z, size_t i)
{
    int x = z % 26;                    // [1]
    z /= _A[i];                        // [2]

    if (x + _B[i] == _w[i])            // [3]
        return z;                      // [4]

    return z * 26 + _w[i] + _C[i];     // [5]
}
```

At: <br />
[1] `x` becomes a number in 0..25 range. <br />
[2] Then `z` is divided by 26. <br />
[3] `x` is updates and now there is a chance it will match digit on input (`w[i]`) <br />
[4] if so: `z` is returned (divided previously by 26 at [2]). <br />
[5] otherwise: `z` is multiplied by 26 (which "cancels" division at [2]) and some number less than 26 is added.

In other words:
- operations [2] and [4] can lower `z` at least 26 times
- operations [2] and [5] leave `z` with *almost the same* value

Looking at `z` as a number in numeral system with 26 as its base you can say that:
- operations [2] and [4] lower `z` number by one order of magnitude
- operations [2] and [5] leave `z` in the same order of magnitude

--------

Summarizing the most important observations made so far:
- on validating submarine's model number variable `z` starts with zero value, then its value is increased or decreased during 14 executions of `Solver::execute_block` method (14 digits of submarine's model number) and we're looking for `z == 0` after 14<sup>th</sup> execution;
- when `A[i]` is `1` there is a chance of increasing by one order of magnitude of z<sub>26</sub> number;
- when `A[i]` is `26` there is a chance of decreasing by one order of magnitude of z<sub>26</sub> number;
- in `A` array there are exactly seven elements = `1` and seven elements = `26`.


__Conclusion:__
Increasing/decreasing the order of magnitude of z<sub>26</sub> number has to be correlated to `1`/`26` numbers in `A` array. This is the only chance to finish 14-digit validation with `z` in 0..25 range, and - finally - find `z == 0` numbers. In other words: we can calculate the maximum `z` value after checking i<sup>th</sup> digit of submarine's model number; when `z` value exceeds this number - there is no need to check the whole set of numbers starting with the same i<sup>th</sup> digits as the number being validated, because they all cannot lead to `z == 0`.


__Example:__

Let's start with the highest number = 99999999999999 and the arrays from my input:

```C++
A = {   1,   1,   1,  26,   1,  26,   1,   1,   1,  26,  26,  26,  26,  26 }
B = {  12,  10,  10,  -6,  11, -12,  11,  12,  12,  -2,  -5,  -4,  -4, -12 }
C = {   6,   2,  13,   8,  13,   8,   3,  11,  10,   8,  14,   6    8,   2 }
```

`A[0] = 1`, so the `max_z == 26` after first digit.
After calling `Solver::execute_block` with first digit `z == 15`. So far so good.

`A[1] = 1`, multiply `max_z` by `26`, now `max_z == 676` after 2<sup>nd</sup> digit.
After calling `Solver::execute_block` with second digit `z == 401`. So far so good.

`A[2] = 1`, multiply `max_z` by `26`, now `max_z == 17576` after 3<sup>rd</sup> digit.
After calling `Solver::execute_block` with third digit `z == 10448`. Still good.

`A[3] = 26`, divide `max_z` by `26`, now `max_z == 676` after 4<sup>th</sup> digit.
After calling `Solver::execute_block` with 4th digit `z == 10443`. Too much!

It means that all numbers starting with four nines cannot reach `z == 0`. We can skip all these numbers and check 99989999999999 next.


Simple and effective optimization! Enough to obtain correct results of both parts of the puzzle in __one second__ (or less) on modern CPU. Problem solved.

--------

Now, let's take a look at important pieces of code.

As mentioned above `Solver` class constructor reads values of `A`, `B` and `C` arrays:

```C++
Solver::Solver(const vector<string>& input, int w_init)
{
	for (int i = 0; i < 14; i++)
	{
		_A.push_back(stoi(input[i * 18 + 4].substr(6)));
		_B.push_back(stoi(input[i * 18 + 5].substr(6)));
		_C.push_back(stoi(input[i * 18 + 15].substr(6)));
	}
	...
}
```

Then - initializes `w` array and prepares `max_z` values according to `A` array values:

```C++
Solver::Solver(const vector<string>& input, int w_init)
{
	...
	_w = vector<int>(14, w_init);

	int64_t z = 1;
	for (int i = 0; i < 14; i++)
	{
		if (_A[i] == 1)
			z *= 26;
		else
			z /= 26;

		_max_z.push_back(z);
	}
}
```

`Main::part_one` looks for the highest number, `Main::part_two` looks for the lowest number. `Solver::execute` does the job:

```C++
AoC::Output Main::part_one(const vector<string>& input)
{
	return Solver(input, 9).execute();
}

AoC::Output Main::part_two(const vector<string>& input)
{
	return Solver(input, 1).execute();
}
```

`Solver::execute` validates numbers in `while` loop, and puts digits of the number found (when `z == 0`) into `result` and returns it:

```C++
string Solver::execute()
{
	int64_t z = -1;
	while (z != 0)
	{
		...
	}

	string result;
	for (auto v : _w)
		result += to_string(v);

	return result;
}
```

`while` loop checks if `z` is not too big after processing i<sup>th</sup> digit by `Solver::execute_block`. If not: `for` examines all 14 digits and `while` ends with `z == 0` (which produces the `result`):

```C++
	while (z != 0)
	{
		z = 0;
		for (size_t i = 0; i < _w.size(); i++)
		{
			z = execute_block(z, i);
			if (z > _max_z[i])
			{
				...
			}
		}
	}

	string result;
	for (auto v : _w)
		result += to_string(v);

	return result;
```

When `z` is too big then the appropriate digit of `w` number is fixed by adding `_step` to it (which equals -1 for part one and 1 for part two - see `Solver` class constructor) and then - the other digits are corrected in `while` and `for` loops to skip bunch of numbers. `break` starts validating a new serial number:

```C++
			if (z > _max_z[i])
			{
				_w[i] += _step;
				while ((_w[i] % 10) == 0)
				{
					_w[i--] = _w_init;
					_w[i] += _step;
				}

				for (size_t j = i + 1; j < _w.size(); j++)
					_w[j] = _w_init;

				break;
			}
```

And... that's all folks! :)

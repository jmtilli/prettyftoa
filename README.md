# Pretty floating-point-to-ASCII (ftoa)

Sometimes, you may want to convert a floating point number to an ASCII string.
How to do it?

You could use the format specifier `"%.17g"` which with the IEEE double
precision numbers has the nice property that every number converted to string
with this format specifier converts back to the same number. However, you
will note a number of suboptimalities with the format specifier:

* The floating point number `2` converts to the string `"2"`. Why is this a problem? It is a problem because the string `"2"` could be an integer too. It does not tell that it is a floating point number.
* The floating point number `0.2` converts to the string `"0.20000000000000001"` due to the base 2 numbers being unable to represent `0.2` accurately. Why is this a problem? It is a problem because the shorter string `"0.2"` would convert to the same floating point number. Thus, there is a shorter string representation that should be preferred.

The pretty ftoa library finds the shortest string representation of the
floating point number that still has the property that the string converts to
the same number. It also enforces that there must be an exponent sign or a
period in the string representation so that it is clear the string represents a
floating point number and not an integer.

## Caveats

The pretty ftoa library has been designed to work with IEEE double precision
numbers and standards-conforming `snprintf` floating point support. In
particular, if the `double` data type of the machine can support exponents
larger than `999` or smaller than `-999`, then the library may `abort()`.

If the `snprintf` library uses unnecessarily large amounts of space, i.e. wants
to format `-5.3000000000000021e-150` with `"%.17g"` using the excessively long
string `"-5.3000000000000021e-0150"` then the library may `abort()`. Similarly,
if the library wants to format `2.0000200000000001` with `"%.17g"` using the
excessively long string `"2.00002000000000013102408047416"` then the library
may `abort()`.

## How to build

Pretty ftoa is built using Stirmake. How to install it:

```
git clone https://github.com/Aalto5G/stirmake
cd stirmake
git submodule init
git submodule update
cd stirc
make
./install.sh
```

This installs stirmake to `~/.local`. If you want to install to `/usr/local`,
run `./install.sh` by typing `sudo ./install.sh /usr/local` (and you may want
to run `sudo mandb` also).

If the installation told `~/.local` is missing, create it with `mkdir` and try
again. If the installation needed to create `~/.local/bin`, you may need to
re-login for the programs to appear in your `PATH`.

Then build pretty ftoa by:

```
cd prettyftoa
smka
```

and test it by:

```
./test
```

## License

All of the material related to pretty ftoa is licensed under the following
MIT license:

Copyright (C) 2020 Juha-Matti Tilli

Permission is hereby granted, free of charge, to any person obtaining a copy of
this software and associated documentation files (the "Software"), to deal in
the Software without restriction, including without limitation the rights to
use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
of the Software, and to permit persons to whom the Software is furnished to do
so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

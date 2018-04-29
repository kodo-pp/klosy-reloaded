# Coding style

Klosy style guide for the C lanuage.

## TL;DR
- Indentation: 4 spaces, no tabs

- Braces and spaces:
[Linux style](https://www.kernel.org/doc/html/v4.13/process/coding-style.html#placing-braces-and-spaces)
with some exceptions, see section 'Braces'

- Naming: variable_name, function_name(arg_name), CONST_OR_DEFINE_NAME

- Empty lines are OK, if necessary

- `++i` is better than `i++`

- `/* Comment */` is better than `// Comment`

- Wrap lines at 80-100 chars

## Indentation and whitespace

### Indentation
4 spaces. **Never** use tabs except for Makefiles (if so, assume
tab length is equal to 4).

Case or other labels are not indented. Example:
```
switch (value) {
case 1:
    do_something();
    break;
case 2:
    do_something_different();
    /* fallthrough */
case 3: case 4: case 5:
    do_something_even_more_different(value);
    break;
default:
    report_error();
    break;
}
```

If using C++, access modifiers are not indented.

### Whitespace
One space (exception: alignment, see below):

- after `if`, `else`, `for`, `while`, `switch`, etc.

- around arithmetic, logic and bitwise operators, if it doesn't worsen the readability
(e.g. `double f(double x) { return 5*x*x + 8*x - 1 + (123 / x); }`)

- after closing brace if it doesn't end the line (e.g. `} else {`)

- inside *curly braces* if the function is a one-liner (see example of `f(x)` above)

No space:

- after function names (declaration and calling), e.g. `int foo(int bar);`, `foo(5);`

- inside *brackets and parentheses*, e.g. `if (x + 3 < y)` is OK, `if ( x + 3 < y )` is bad

### Alignment
Vertical alignment is permitted, but use it only when it improves readability. Example:

w/o alignment:
```
foo(x, y[2], z(3));
foo(63, y[11], x);
foo(444, y[x+14], 0);
```

w/ alignment:
```
foo(x,   y[2],    z(3));
foo(63,  y[11],   x);
foo(444, y[x+14], 0);
```

## Braces
Use Linux-style braces:

```
int foo(int x)
{
    if (bar(x) < 0) {
        return do_something(x);
    } else {
        return -1;
    }
}
```

One-liners are OK if they improve the readability. Example:
`int foo(x) { return bar(x + 5); }`

Empty bodies should be denoted like this:
```
while (foo() > 5) { }
```
OR like this:
```
while (foo() > 5) {
    /* empty */
}
```

Use braces even if the body of a statement contains only one line. Example:

OK:
```
if (foo(5)) {
    bar();
}
```
Bad:
```
if (foo(5))
    bar();
```

## Naming
Use `underscore_naming` for variables and functions,
`ALL_CAPS_WITH_UNDERSCORES` for macros and constants.

## Comments
Not necessary, but highly recommended

Use them to briefly describe function purpose right above its *declaration* (perhaps in
the header file) and to clarify some ugly and confusing code (the code will still
remain ugly and confusing, but at least I will know what (and maybe why) it does)

Prefer `/* comment */` to `// comment`.

Use this style to describe functions:
```
/**
 * Returns a random value
 */
int rand()
{
    return 4;
}
```

Of course, comments should say the same things that code does.
So that example is good from the point of view of formatting, but not from
the point of view of meaning.

## Other stuff
- Prefer `++i` to `i++`

- Try to avoid `goto`s, but use them if it is the only/best possible option

- Try to avoid do-while loops, but again, use them if you think it is the best option

- Try to avoid increment and decrement in expressions (e.g. `while (*ptr++ != 0)` is bad)

- Use `break`s in switch-case statements if it is necessary, leave a `/* fallthrough */` comment
on non-trivial fallthrough ocassions (see example in the beginning)

- Lines should be wrapped at 80-100 chars

- Functions should not be longer than 40-50 lines, but can be if *absolutely* necessary.
Exception: long if - else if chains or switch-case statements, which can be longer than 40-50 lines.

- Never forget about zero byte terminator in the strings$8!1]"?‰.:H)Ol^Segmentation fault

- Keep in mind that most of this code runs in kernel mode, so be triple-careful when
dealing with things like arrays and pointers

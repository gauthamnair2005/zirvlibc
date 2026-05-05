# zirvlibc

`zirvlibc` is a small freestanding C library extracted from Zirvium kernel usage.

Implemented surfaces:

- `string.h`: memory and string primitives used by Zirvium.
- `ctype.h`: character classification/transformation helpers used by Zirvium shell parsing.
- `stdio.h`: minimal `snprintf`/`vsnprintf` formatter with Zirvium-compatible specifiers:
  `%s %d %u %x %p %c %%`.

## Build

```bash
make
```

Produces:

- `libzirvlibc.a`

## Test

```bash
make test
```

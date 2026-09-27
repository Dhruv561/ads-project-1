# ads-project-1

A C program that loads a CSV of Victorian street addresses into a linked list and looks up addresses by their `EZI_ADD` string (e.g. `18 PROFESSORS WALK PARKVILLE 3052`). Each query is compared against every record bit by bit, and the program reports how many comparisons it took.

## Build

Needs `gcc` and `make`.

```bash
make
```

`make clean` removes the build files.

## Run

```bash
./dict1 1 <address_file.csv> <output_file> < queries.txt
```

- `1` is the stage number. It is the only stage implemented.
- `queries.txt` has one `EZI_ADD` per line. Matching is exact and case-sensitive.

Example:

```bash
./dict1 1 tests/dataset_22.csv out.txt < tests/test22.in
```

Matching records are written to `out.txt`, or `--> NOTFOUND` if there are none. A summary of each search goes to stdout:

```
230 GRATTAN STREET PARKVILLE 3052 --> 20 records found - comparisons: b5453 n22 s22
```

`b` is bits compared, `n` is list nodes visited, `s` is strings compared.

## Tests

The sample datasets and queries are in `tests/`. Compare stdout with the expected output:

```bash
./dict1 1 tests/dataset_22.csv out.txt < tests/test22.in | diff - matching_results/test22.stdout.out
```

## Limitations

The CSV parser only splits on commas, so quoted fields are not supported. Every query scans the whole list.

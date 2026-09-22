## Custom wc

### Misc
1. File size requires using `ifstream` in `std::ios::binary` mode to get accurate byte counts with `seekg(0, std::ios::end)` and `tellg()`, since `wifstream` returns non-deterministic logical offsets and expands bytes into platform-dependent `wchar_t` sizes (4 bytes on Linux UTF-32, 2 bytes on Windows UTF-16).
2. The POSIX `wc -w` command delimits words based on the C standard library's `isspace()` function, which includes space (`' '`), horizontal tab (`'\t'`), newline (`'\n'`), vertical tab (`'\v'`), form-feed (`'\f'`), and carriage return (`'\r'`).
3. Reading a file sets flags `eofbit` or `failbit` true according to the flags' condition, which locks the stream and prevents `seekg()` from working until you explicitly call `file.clear()` to reset the error state.
4. Imbuing a `std::locale` (such as "en_US.UTF-8") applies specific environmental encoding rules to a stream, utilizing its `codecvt` facet to translate the file's raw bytes into the expanded `wchar_t` buffer.

# Unit Tests

This directory contains unit tests using Catch2 that covers most of the basic functionality of the code.

For the full suite of tests, ensure you compile in `Test` mode or with the `-DJTX_TEST` flag. This is because some tests
will purposefully fail debug assertions, which terminate the program. In Test mode, assertions will
still fail (will still `cerr`), but will not terminate the program.
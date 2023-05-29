#!/bin/bash
find -name '*.[ch]pp' -exec clang-format -i {} \;

#!/usr/bin/env python3

import sys

with open(sys.stdin, "rb") as stdin:
    with open(sys.stdout, "wb") as stdout:
        sample = stdin.read(2)
        converted = []
        while sample:
            converted[0] = ((sample[0] >> 4) | (sample[1] << 4)) & 255
            converted[1] = sample[1] >> 4
            stdout.write(bytes(converted))
            sample = stdin.read(2)

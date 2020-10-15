import sys

with open(sys.argv[1], "rb") as stdin:
    with open(sys.argv[2], "wb") as stdout:
        sample = stdin.read(2)
        converted = []
        while sample:
            converted[0] = ((sample[0] >> 4) | (sample[1] << 4)) & 255
            converted[1] = sample[1] >> 4
            stdout.write(bytes(converted))
            sample = stdin.read(2)

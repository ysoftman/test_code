import time
import sys

for i in range(10):
    # print(f"\rtesting...{i}")
    sys.stdout.write(f"\rtesting...{i}")
    sys.stdout.flush()
    time.sleep(1)

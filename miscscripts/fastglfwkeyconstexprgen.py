import sys;

#Script that was written hastily to quickly generate the constexpr's for kWindow.

while True:
    v = input().strip().split()
    if len(v) != 3:
        continue
    x = v[1][5:]
    print("constexpr key_t " + x + ";");#" = " + v[1] + ";");

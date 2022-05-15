import sys


cnt = 0
ts = 0


new_file = sys.argv[1].replace("raw/", "")
f = open("{0}_{1}.csv".format(new_file, cnt), "w")
f.write("timestamp,accX,accY,accZ\n")

for line in open(sys.argv[1]):
    if line.strip() == "********":
        cnt += 1
        f.close()
        new_file = sys.argv[1].replace("raw/", "")
        f = open("{0}_{1}.csv".format(new_file, cnt), "w")
        f.write("timestamp,accX,accY,accZ\n")
        ts = 0

    else:
        accel = line.split("\t")
        f.write("{0},{1},{2},{3}".format(ts, accel[0], accel[1], accel[2]))
        ts += 16

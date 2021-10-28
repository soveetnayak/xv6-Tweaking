import matplotlib.pyplot as plt

# use PLOT as 1 in types.h to get data,  refer README for details

with open("./iobound.txt") as f:
    s = map(lambda x: [int(x[0]), int(x[1]), int(x[2])], map(lambda x: x.split(" "), f.read().split("\n")))

data = list(s)
procs = 10   # number of procs defined in benchmark program
procs = procs + 4
start = 4     # this will include init, sh, load if 1 ,
# put 4 to get only the forked ones...
plt.yticks([0, 1, 2, 3, 4])
plt.xlabel("Ticks")
plt.ylabel("Queue No")
for pid in range(start, procs):
    plotx = []
    ploty = []
    for line in data:
        if(line[1] == pid):
            plotx.append(line[0])
            ploty.append(line[2])
    plt.plot(plotx, ploty, linestyle='--', marker='o', label=str(pid))

plt.legend()
plt.show()

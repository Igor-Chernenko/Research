import random

M = 200000
N = 180000
Q_succ = 200000
Q_fail = 200000

seed = 1
path = f"./Tests/case_M{M}_N{N}_alpha{N/M}.txt"


rng = random.Random(seed)

# make N unique insert keys
ins_keys = set()
while len(ins_keys) < N:
    ins_keys.add(rng.randrange(1, 10**12))
ins_keys = list(ins_keys)

# make fail keys that are guaranteed not inserted (use a disjoint range)
fail_keys = set()
while len(fail_keys) < Q_fail:
    k = rng.randrange(10**12, 2 * 10**12)
    fail_keys.add(k)
fail_keys = list(fail_keys)

#successful queries: sample from inserted keys
succ_keys = [ins_keys[rng.randrange(0, N)] for _ in range(Q_succ)]

out = []
out.append(str(M))
out.append(f"# Case: M={M}, N={N} (alpha={N/M}), Q_succ={Q_succ}, Q_fail={Q_fail}, seed=1")
out.append("R")  # baseline totals (should be 0,0)

out.append("# BUILD: insert N keys")
for i, k in enumerate(ins_keys):
    out.append(f"I {k} {i+1}")
out.append("R")

out.append("# QUERIES: successful finds")
for k in succ_keys:
    out.append(f"F {k}")
out.append("R")

out.append("# QUERIES: unsuccessful finds")
for k in fail_keys:
    out.append(f"F {k}")
out.append("R")

with open(path, "w") as f:
    f.write("\n".join(out) + "\n")

print("Completed, Enter this into the path of runner.cpp:")
print(path)
import random

#settings
V_COUNT = 50
DENSITIES = [0.1,0.2,0.3,0.4,0.5,0.6]
K_VALUES = [45,50] 
SEED = 1
rng = random.Random(SEED)

out = []

for d in DENSITIES:
    for k in K_VALUES:
        out.append("R")
        
        max_edges = V_COUNT * (V_COUNT - 1)
        num_edges = int(d * max_edges)
        out.append(f"# Testing V={V_COUNT}, d={d}, k={k}")
        out.append(f"N {V_COUNT}")

        edges = set()
        while len(edges) < num_edges:
            u, v = rng.randrange(V_COUNT), rng.randrange(V_COUNT)
            if u != v: edges.add((u, v))
        
        for (u, v) in edges:
            w = rng.randint(1, 100)
            out.append(f"E {u} {v} {w}")

        sources = rng.sample(range(V_COUNT), k)
        for s in sources:
            out.append(f"S {s}")
        out.append("RUN")

test_location = f"./Tests/test_case_V{V_COUNT}"
with open(test_location, "w") as f:
    f.write("\n".join(out) + "\n")
print(f"Enter into runner.cpp: {test_location}")

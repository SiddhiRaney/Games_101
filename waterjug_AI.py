def g(s):
    return s[0] == 2 or s[1] == 2

def n(s):
    a,b = s
    nxt = []
    nxt.append(((4,b), "Fill 4 gallon jug"))
    nxt.append(((a,3), "Fill 3 gallon jug"))
    nxt.append(((0, b), "empty 4 gallon jug"))
    nxt.append(((a, 0), "empty 3 gallon jug"))

    p = min(b, 4-a)
    nxt.append(((a+p, b-p), "Pour from 3 to 4"))

    p = min(a, 3-b)
    nxt.append(((a - p, b + p), "Pour from 4 to 3"))

    return nxt


def bfs():
    st = (0,0)
    q = [(st,[])]
    v =[]
    while q:
        cs, path = q.pop(0)
        if cs in v:
            continue
        v.append(cs)

        if g(cs):
            return path + [(cs, 'goal')]

        for ns, act in n(cs):
            if ns not in v:
                q.append((ns, path + [(cs,act)]))
    return None

def d(a,b):
    def s(g,c):
        if g == 0:
            return "0"

        elif g == c:
            return str(c)

        elif g == 2:
            return "2"

        else:
            return "X"

    ad = s(a,4)
    bd = s(b,3)

    print("\n")
    print("| |  ")
    print("| |  | |")
    print("| |  | |")
    print(f"({ad}) , ({bd})")
    print("\n")

print("AI SOLN of WATER JUG")
sol = bfs()
if sol:
    step = 1
    for s,a in sol:
        x,y = s
        d(x,y)
        print(f"Step {step}:{a}")
        step += 1

    print("Sol is exec")
else:
    print("No sol")







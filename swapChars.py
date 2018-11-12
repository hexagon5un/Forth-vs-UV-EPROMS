

o = file("foo", "w")
f = file("romstrings").readlines()
for l in f:
    l=l.strip()
    for i in range(0, len(l), 2):
        try:
            o.write(l[i+1])
        except:
            pass
        o.write(l[i])
    o.write("\n")
o.close()






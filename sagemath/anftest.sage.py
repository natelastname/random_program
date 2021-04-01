from sage.crypto.boolean_function import BooleanFunction

# this is the cleanest ANF poly code I have written.

# should be a power of two because it's a BF of BFs.
n = 6
B = BooleanPolynomialRing(n, "x")
Bvars = [B.variable(i) for i in range(0,n)]

Sierpinski = [B.variable(i) + B.variable(i+1) for i in range(0, n-1)]
Sierpinski.append(B.variable(n-1))

# the kth sierpinski row poly
def sierpinski(k):
    P = Bvars[0]
    for i in range(0, k):
        P = P(*Sierpinski)
    return P

# returns the truth table of ANF poly P
def get_tt(P):
    ret = []
    for i in range(0, 2**n):
        j = list(map(lambda x: int(x), list(bin(i))[2:]))
        j = ([0]*(n-len(j)))+j
        j.reverse()
        ret.append(P(*j))

    return ret
    
# returns the coefficient vector of ANF poly P
# This function is very slow
def get_cv(P):
    monos = P.monomials()
    ret = [0]*(2**n)
    for i in range(0,len(monos)):
        m = monos[i]
        m_index = 0
        place_val = 1
        for j in range(0, n):
            if(Bvars[j] in m):
                m_index += place_val
            place_val += place_val
        ret[m_index] = 1
    return ret

# Joins the array (used to prevent line breaks after each element)
def join_arr(arr):
    return ",".join(list(map(lambda x: str(x), arr)))
    
    
# Set P to the product of sierpinski rows
P = B.one() 
for i in range(0,n):
    P = P * sierpinski(i)
   
# print the TT and CV
tt = get_tt(P)
for i in range(0, len(tt)):
    if(tt[i] == 1):
        print(i)

#print(join_arr(get_cv(p)))

f = open("input","r")
arr = f.readlines()
f.close()
arr = arr[2:]


print(arr)

bfs = []
for i in range(0, len(arr)):
    print(len(arr[i][:-1]))
    bfs.append(BooleanFunction(arr[i][:-1]))














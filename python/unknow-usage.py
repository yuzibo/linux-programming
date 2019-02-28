'''
The problem with this implementation is that it recalculates the results for 
n > 1 over and over again. You construct that nice lookup table and then you 
don't use it.

Compare:

$ cat rfib.py
'''
fibs={0:0,1:1}

def rfib(n):
      if n == 0 or n == 1:
          return fibs[n]
      else:
        fibs[n]=rfib(n-2)+rfib(n-1)
        return fibs[n]

sfibs = {0: 0, 1: 1}

def sfib(n):
    try:
        return sfibs[n]
    except KeyError:
        pass
    result = sfibs[n] = sfib(n-1) + sfib(n-2)
    return result

for i in range(10):
    assert rfib(i) == sfib(i)

'''
$ python3 -m timeit -s 'import rfib' 'rfib.rfib(25)'
10 loops, best of 3: 102 msec per loop
$ python3 -m timeit -s 'import rfib' 'rfib.sfib(25)'
1000000 loops, best of 3: 0.371 usec per loop
'''
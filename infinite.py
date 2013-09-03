#!/usr/bin/python

import random

def trial():
  i = 1
  while random.randint(0,1) == 0:
    i = i*2
  return i

trials = 10000000

s = 0.0
for i in xrange(trials):
  s += trial()

print "Average winnings: %s" % (s/trials,)

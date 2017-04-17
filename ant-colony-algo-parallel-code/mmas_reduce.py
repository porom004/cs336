from operator import itemgetter
import sys
import pyspark


# input comes from STDIN
for line in sys.stdin:

    edge, currentPheromone = line.split('\t', 1)
    take(edge)

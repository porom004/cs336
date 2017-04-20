from operator import itemgetter
import sys
import pyspark

for line in sys.stdin:

    edge, currentPheromone = line.split('\t', 1)
    take(edge)

#!/usr/bin/env python

import sys
import pyspark

for line in sys.stdin:
    
    p_vector = sc.parallelize(line)
    
    for ele in p_vector:
         map(mmas())
         
        
def mmas() :
    for ant in colony
        tour = ant.getTour();
        pheromoneToAdd = getParam('Q') / tour.distance();
        for cityIndex in tour 
            if lastCity(cityIndex) 
                edge = getEdge(cityIndex, 0)
            else 
                edge = getEdge(cityIndex, cityIndex+1)
            
            currentPheromone = edge.getPheromone();
            edge.setPheromone(currentPheromone + pheromoneToAdd)
            
            return edge, currentPheromone

Make sure you have Apache Spark's MapReduce framework installed. 

The instructions are given in this. 
http://www.michael-noll.com/tutorials/running-hadoop-on-ubuntu-linux-single-node-cluster/

If your system is ready with Apache Spark and Hadoop,
Download this source code and run the following command.

$ bin/hadoop jar contrib/streaming/hadoop-*streaming*.jar \
-file /home/sb/mapper.py    -mapper /home/sb/mmas_mapper.py \
-file /home/sb/reducer.py   -reducer /home/sb/mmas_reducer.py \
-input /user/sb/cs336/* -output /user/sb/cs336

3


Output : 

Mapper Input : <Edge, Pheromone>
Reducer Output : <BestEdge, Its Pheromone>
Code output : BestEdge 

Output when code is run, 

3    8 (Reducer Output)
3       (Code output) [Best Edge]

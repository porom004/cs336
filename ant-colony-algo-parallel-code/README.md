Make sure you have Apache MapReduce framework installed. 

The instructions are given in this. 
http://www.michael-noll.com/tutorials/running-hadoop-on-ubuntu-linux-single-node-cluster/

If your system is ready with Apache Spark,
Download this source code and run the following command.

$ bin/hadoop jar contrib/streaming/hadoop-*streaming*.jar \
-file /home/sb/mapper.py    -mapper /home/sb/mapper.py \
-file /home/sb/reducer.py   -reducer /home/sb/reducer.py \
-input /user/sb/cs336/* -output /user/sb/cs336



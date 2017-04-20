/* 
   14CS336 - Parallel Computing Course
   This code is Pregel Implementation in Scala run Apache Spark GraphX framework 
   See the blog for more info :  
*/

// Importing relevant libraries.
import org.apache.spark._
import org.apache.spark.graphx._
import org.apache.spark.rdd.RDD

/* Graph set up */
println("The Graph Initiliasation : ")
val graph = GraphLoader.edgeListFile(sc, "nodes.txt") // sc refers to the Spark Context. The default variable is 'sc'


// The out degrees are linked 
val temp = graph.outerJoinVertices(graph.outDegrees) { (vid, vdata, deg) => deg.getOrElse(0) }
println("The outdegrees <VertexID, OuterVertexID> : ")
temp.vertices.take(5) // Displays the first five outdegrees in the pairs <VertexID, OuterVertexID>


// The edge values are defined using mapTriplets() function to initialise the weights of every edge
val et = temp.mapTriplets(edge => 1.0/edge.srcAttr) // Each edge is initially defined to 1/(num of vertices)
println("The edge values : ")
et.triplets.take(5) // Displays five such triplet instances 


// Each vertex in the PageRank graph is set to 1 initially
val primaryGraph = et.mapVertices((id, value) => 1.0)
println("The Initial PageRank graph <VertexID, PageRank of that Vertex>  : ")
primaryGraph.vertices.take(10) // The output is, <VertexID, PageRank of that Vertex> and 10 such instances are displayed.



// The graph should now consist of all the outdegrees and its edge values. The below code simply does that.
val primaryGraph: Graph[Double, Double] = graph.outerJoinVertices(graph.outDegrees) { (vid, vdata, deg) => deg.getOrElse(0)}.mapTriplets(edge => 1.0 / edge.srcAttr).mapVertices((id, value) => 1.0)


/* Pregel Setup */

val primaryMessage = 0.0  // The initial message value
val numberOfIterations = 120 // Number of times the page rank has to run
val probability = 0.15 // The pivot probability assumed to be 0.15 when assigned unknown random vertex else 0.85 when assigned from the same vertex

// The Pregel() function params are based on the callback of following functions. 

def vertex(id: VertexId, value: Double, sumValue: Double): Double = probability + (1.0 - probability) * sumValue
def outgoingMessage(edge: EdgeTriplet[Double, Double]): Iterator[(VertexId, Double)] = Iterator((edge.dstId, edge.srcAttr * edge.attr))
def combineMessages(a: Double, b: Double): Double = a + b

// The following code calls the Pregel() function and does the BSP of PageRank for every superstep

val pagerankGraph = Pregel(primaryGraph, primaryMessage, numberOfIterations)(vertex, outgoingMessage, combineMessages)
println("The Final PageRank graph : <VertexID, Final PageRank of that Vertex> ")
primaryGraph.vertices.take(10) 

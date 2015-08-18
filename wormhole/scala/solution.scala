import scala.collection._

object Solution {
  def main(args : Array[String]) {
    val numTestCases = scala.io.StdIn.readInt
    runTests(numTestCases)
  }

  def runTests(numTests:Int):Unit = {
    def runTest(curTest : Int):Unit = {
      val curGraph = new GalaxyGraph
      val numberOfPlanets = scala.io.StdIn.readInt

      Range(0, numberOfPlanets).foreach(_ => {
        val curLine = scala.io.StdIn.readLine.split(" ")
        val planetName = curLine.head
        val coordinates = curLine.drop(1).map(_.toInt)
        val planetVertex = new PlanetVertex(planetName, coordinates(0), coordinates(1), coordinates(2))
        curGraph.addPlanet(planetVertex)
      })

      val numWormholes = scala.io.StdIn.readInt

      Range(0, numWormholes).foreach(_ => {
        val curLine = scala.io.StdIn.readLine.split(" ")
        curGraph.addWormhole(curLine(0), curLine(1))
      })

      val shortestPaths = curGraph.getAllPairsShortestPath

      val travelTimes = scala.io.StdIn.readInt

      println("Case " + (curTest + 1) + ":")
      Range(0, travelTimes).foreach(_ => {
        val curLine = scala.io.StdIn.readLine.split(" ")
        val start = curLine(0)
        val end = curLine(1)

        println("The distance from " + start + " to " + end + " is " + shortestPaths(start)(end) + " parsecs.")
      })
    }
    Range(0,numTests).foreach(runTest)
  }

}

class GalaxyGraph {
  private val planets = mutable.ArrayBuffer[PlanetVertex]()
  private val planetMap = mutable.Map[String, PlanetVertex]()

  def addPlanet(planet: PlanetVertex):Unit = {
    planets.append(planet)
    planetMap += (planet.name -> planet)
  }

  def addWormhole(planet1: String, planet2: String):Unit = {
    val planetOneVertex = planetMap(planet1)
    val planetTwoVertex = planetMap(planet2)
    planetOneVertex.wormHoles += planetTwoVertex
  }

  def getAllPairsShortestPath():mutable.Map[String, mutable.Map[String, Long]] = {
    val numVertices = planets.size
    val dist = Array.fill[Double](numVertices, numVertices){ Double.PositiveInfinity }


    for(i <- 0 until numVertices) {
      for(j <- 0 until numVertices) {
        dist(i)(j) = planets(i) distanceTo planets(j)
      }
    }

    for(k <- 0 until numVertices) {
      for(i <- 0 until numVertices) {
        for(j <- 0 until numVertices) {
          if(dist(i)(j) > dist(i)(k) + dist(k)(j)) {
            dist(i)(j) = dist(i)(k) + dist(k)(j)
          }
        }
      }
    }

    //convert to map so we can easily identify the planets by name
    val map = mutable.Map[String, mutable.Map[String, Long]]()

    for(i <- 0 until numVertices) {

      val curPlanet = planets(i).name
      map.update(curPlanet, mutable.Map[String, Long]())
      val curMap = map(curPlanet)

      for(j <- 0 until numVertices) {
        val otherPlanet = planets(j).name
        curMap.update(otherPlanet, Math.round(dist(i)(j)))
      }
    }
    map
  }
}

class PlanetVertex(val name: String, val x:Long, val y:Long, val z:Long){ 
  val wormHoles = mutable.Set[PlanetVertex]()
  
  def distanceTo(otherPlanet: PlanetVertex): Double = {
    if(otherPlanet == this || wormHoles.contains(otherPlanet) || otherPlanet.name == this.name) 0 
    else Util.getEuclideanDistance(this, otherPlanet)
  }

  override def toString = name
}

object Util {
  def getEuclideanDistance(first: PlanetVertex, second: PlanetVertex):Double = {
    val x = (first.x - second.x) * (first.x - second.x)
    val y = (first.y - second.y) * (first.y - second.y)
    val z = (first.z - second.z) * (first.z - second.z)
    Math.sqrt(x + y + z)
  }
}


import scala.collection._

object Solution {
  def main(args : Array[String]) {
    val numTestCases = scala.io.StdIn.readInt
  }

  def runTests(numTests:Int):Unit = {
    def runTest(curTest : Int) = {

    }
  }

}

class GalaxyGraph {
  val planets = mutable.ArrayBuffer[PlanetVertex]()

  def addPlanet(planet: PlanetVertex):Unit = planets.append(planet)

  def getAllPairsShortestPath():mutable.Map[String, mutable.Map[String, Long]] = {
    val numVertices = planets.size
    val dist = Array.fill[Double](numVertices, numVertices){ 0 }

    for(i <- 0 until numVertices) {
      for(j <- 0 until numVertices) {
        dist(i)(j) = planets(i).distanceTo(planets(j))
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


class PlanetVertex(val name: String, val x: Int, val y: Int, val z:Int){ 
  val wormHoles = Set[PlanetVertex]()
  
  def distanceTo(otherPlanet: PlanetVertex): Double = 
    if(otherPlanet == this || wormHoles.contains(otherPlanet)) 0 
    else Util.getEuclideanDistance(this, otherPlanet)

  override def toString = name
}

object Util {
  def getEuclideanDistance(first: PlanetVertex, second: PlanetVertex):Double = 
    Math.sqrt(first.x * second.x + first.y * second.y + first.z * second.z)
}


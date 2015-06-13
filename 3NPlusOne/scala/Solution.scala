import scala.io.Source

object Solution{

  val chainLength = scala.collection.mutable.Map[Int,Int]()

  def getLongestChainLength(low:Int, high:Int):Int = {
    (low to high)
      .foldLeft(0)((longest, current) => 
      if (getChainLength(current) > longest) getChainLength(current) 
      else longest)
  }

  def getChainLength(num:Int):Int = {
    var n = num
    var length = 0
    while(n != 1){
      length += 1
      if(chainLength.contains(n)) {
        length += chainLength(n) - 1
        n = 1
      }
      else if (n % 2 != 0) n = 3*n + 1
      else n = n/2
    }
    chainLength += (num -> length)
    length+1
  }

  def main(args: Array[String]){
    if (args.length == 0) {
      println("You must enter a file on the command line")
      return
    }
    val fileLines = Source.fromFile(args(0)).getLines.toList

    val inputs = 
      fileLines
        .map(n => n.split(" ")
          .map(m => m.toInt)
          .toList)

    inputs.foreach(n => 
      println(n(0) + " " + n(1) + " " + getLongestChainLength(n(0),n(1))))
  }
}
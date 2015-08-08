import qualified Data.Set as Set

data Rune = Rune { leftNum :: String, operation :: Operation, rightNum :: String, answer :: String }
instance Functor Rune where
  fmap f (Rune right op left ans) = Rune (fmap f right) op (fmap f left) (fmap f ans)

type Runes = [Rune]
data Operation = Operation Char

getNums = Set.fromList ['0','1','2','3','4','5','6','7','8','9']

getOperation :: (Num a) => Operation -> (a -> a -> a)
getOperation (Operation '*') = (*)
getOperation (Operation '+') = (+)
getOperation (Operation '-') = (-)
getOperation _ = error "Unknown operation"
  
solveRune (Rune right op left ans) =
  let possibleNums = Set.toList $ Set.intersection getNums (Set.fromList (right ++ left ++ ans))
  in if null possibleNums
     then -1
     else 0

isSolution num (Rune right op left ans) =
  let dog = "dog"
  in "dog"




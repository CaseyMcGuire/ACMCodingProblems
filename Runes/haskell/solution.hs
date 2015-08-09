import qualified Data.Set as Set
import Data.List
import Data.Char

data Rune = Rune { leftNum :: String, operation :: Operation, rightNum :: String, answer :: String }

data Operation = Operation Char

getNums = Set.fromList ['0','1','2','3','4','5','6','7','8','9']

getOperation :: (Num a) => Operation -> (a -> a -> a)
getOperation (Operation '*') = (*)
getOperation (Operation '+') = (+)
getOperation (Operation '-') = (-)
getOperation _ = error "Unknown operation"

--Given a rune, return the character that corresponds to its solution.
--Note: This will return a null terminator instead of -1 if a solution is not found because
-- -1 is not a character :)
solveRune :: Rune -> Char
solveRune (Rune left op right ans) =
  let possibleNums = Set.toList $ Set.difference getNums (Set.fromList (right ++ left ++ ans))
      getLowestPossibleSolution acc x = if acc /= '\0'
                                        then acc
                                        else if isValidSolution x (Rune left op right ans)
                                             then x
                                             else acc
  in if null possibleNums
     then '\0'
     else foldl' (\acc x -> getLowestPossibleSolution acc x) '\0' possibleNums

--Return whether the given number (as a Char) is a valid solution for the given rune
isValidSolution :: Char -> Rune -> Bool
isValidSolution num (Rune left op right ans) =
  let strToInt str = read str::Integer
      replaceQuestionMarks = map (\x -> if x == '?' then num else x)
      leftNum = replaceQuestionMarks left
      operand = getOperation op
      rightNum = replaceQuestionMarks right
      answer = replaceQuestionMarks ans
  in strToInt leftNum `operand` strToInt rightNum == strToInt answer
     && validNumber rightNum
     && validNumber leftNum
     && validNumber answer

--Returns true if the given string is a valid number (assuming that all the characters are digits)
validNumber :: String -> Bool
validNumber [_] = True
validNumber ('0':_) = False
validNumber _ = True

--Converts a valid string to a rune
--e.g. 123*45?=5?088
strToRune :: String -> Rune
strToRune ('-':line) = let (Rune a b c d) = strToRune line in Rune ('-':a) b c d
strToRune line =
  let allowedOperations = ['+', '-', '*']
      (firstNum, rest) = break (\x -> elem x allowedOperations) line
      op = head rest
      (secondNum,_:answer) = span (/='=') (tail rest)
  in Rune firstNum (Operation op) secondNum answer

test = isValidSolution '0' (Rune "123?45" (Operation '-') "?" "123?45")

main::IO()
main = do
  _ <- getLine --ignore number of test cases
  lines <- fmap lines getContents 
  let runes = map (\x -> if x == '\0' then -1 else digitToInt x) $ map solveRune $ map strToRune lines
  mapM_ print $ runes

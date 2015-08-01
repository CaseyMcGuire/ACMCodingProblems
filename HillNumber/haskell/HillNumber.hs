import Data.Char

isHillNumber :: Int -> Bool
isHillNumber x = null . descending . ascending $ zip (drop 1 listOfDigits) listOfDigits
                      where
                        listOfDigits =  map (digitToInt) $ show x
                        ascending = dropWhile (\(x,y) -> x >= y)
                        descending = dropWhile (\(x,y) -> x <= y)
                        
--brute force solution
numHillNumbersLessThan n = length $ filter (isHillNumber) [0..(n-1)]

mapDouble = map(2*) [1,5,-18,99]

filterEven = filter even(list_1 100)
list_1 n = [x | x <- [1..n], x `mod` 2 == 0]

mapTriple = map(3*) (list_2 77)
list_2 n = [x | x <- [1..n], x `mod` 2 /= 0]


sumFilter = sum(filter odd(mapSquare))
mapSquare = map(^2) ([1,2,3,4,5,7,8,1,43,25,65,22])

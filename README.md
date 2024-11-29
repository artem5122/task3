# Параллельное программирование. Лабораторная работа 3. Варыпаев Артем. м2-ИФСТ-11

Немного про структуру проекта.

`NumbersGenerator` и `EratosthenesSieve` генерируют и находят «базовые» числа соответственно.

Есть абстрактный класс `PartitionAbstract`. Его потомки: `RangePartition`, `BasePartition` и `PartitionThreadPoolAbstract`. 

Потомки абстрактного класса `PartitionThreadPoolAbstract`: `RangePartitionThreadPool` и `BasePartitionThreadPool`.

`RangePartition`, `BasePartition`, `RangePartitionThreadPool`, `BasePartitionThreadPool` это параллельные алгоритмы №1, №2, №3, №4 соответственно из условия лабораторной. 

* `RangePartition` - разбиение чисел от sqrt(n) до n на потоки.
* `BasePartition` - разбиение «базовых» чисел до sqrt(n) на потоки.
* `RangePartitionThreadPool` - то же самое, что и `RangePartition`, только с использованием тред пула.
* `BasePartitionThreadPool` - то же самое, что и `BasePartition`, только с использованием тред пула.

Как вы и просили на паре, я создал интерфейс `FoundPrimes`, хранящий все полученные простые числа, которые с помощью двух методов могут быть выведены либо на экран, либо в файл. В конструкторе я решил объединить «базовые» и найденные простые числа.  

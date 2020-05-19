# Optimization Hash Table

I will try to optimize work of my hash-table. Let's start.

# Analyze Before

For analyzing I used ordinary dictionary-type .txt file (words.txt) which consist of not many words. But I found one word "world" a lot of times for the most accurate results.

I used callgrind for analyzing "the worst" function. And I found two at once! But it was so expected that in hash-table the slowest function is searching. These functions be rewritten!  

![](https://github.com/shugaley/2_semestr/blob/master/optimization_hash_table/valgrind.png)

# Analyze After






























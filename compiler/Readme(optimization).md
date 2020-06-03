# A Few Words About Compiler Optimization 

Ok. I did it. Compiler has been finished. This year of endless proga has been finished. 

I measured the average acceleration. lang_input_test.txt was used for this (there are calculations of 8! N-times).
There are results:

![](https://github.com/shugaley/2_semestr/blob/master/compiler/img/General1.png)

Not bad (acceleration is about 900).
But it became obvious that this can be done even faster after analyzing the resulting code in edb.

# Optimization

I made some optimizations. There are comparisons of first version and optimized version:

1)

![](https://github.com/shugaley/2_semestr/blob/master/compiler/img/1.png)
![](https://github.com/shugaley/2_semestr/blob/master/compiler/img/1_opt.png)


2)

![](https://github.com/shugaley/2_semestr/blob/master/compiler/img/2.png)
![](https://github.com/shugaley/2_semestr/blob/master/compiler/img/2_opt.png)

3)

![](https://github.com/shugaley/2_semestr/blob/master/compiler/img/3.png)
![](https://github.com/shugaley/2_semestr/blob/master/compiler/img/3_opt.png)

# Final Results

I could speed up my code by about 10%. Not bad for a few hours of work.

There are final results:

![](https://github.com/shugaley/2_semestr/blob/master/compiler/img/General_final_final.png)

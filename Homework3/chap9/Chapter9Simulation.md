# Homework Simulation Chapter 9, Scheduling

## Question 1

> Compute the solutions for simulations with 3 jobs and random seeds of 1, 2, and 3.

**Answer:**

`./lottery.py -j 3 -s 1 -c`
`./lottery.py -j 3 -s 2 -c`
`./lottery.py -j 3 -s 3 -c`

## Question 2

> Now run with two specific jobs: each of length 10, but one (job 0) with just 1 ticket and the other (job 1) with 100 (e.g., -l 10:1,10:100). What happens when the number of tickets is so imbalanced? Will
job 0 ever run before job 1 completes? How often? In general, what does such a ticket imbalance do to the behavior of lottery scheduling?

**Answer:**

`./lottery.py -l 10:1,10:100 -c`

When the ticket is imbalanced, it is hard to achieve fairness.

Job 0 is extremely unlikely to run before job 1 completes. (1% chance)

Ticket imbalance will make lottery scheduling focus on only the tasks who have a lot of tickets and neglect the ones with few tickets.

## Question 3

> When running with two jobs of length 100 and equal ticket allocations of 100 (-l 100:100,100:100), how unfair is the scheduler? Run with some different random seeds to determine the (probabilis- tic) answer; let unfairness be determined by how much earlier one job finishes than the other

**Answer:**

`./lottery.py -l 100:100,100:100 -c -s 1` -> job 1 done at 196, job 0 done at 200
`./lottery.py -l 100:100,100:100 -c -s 2` -> job 1 done at 190, job 0 done at 200
`./lottery.py -l 100:100,100:100 -c -s 3` -> job 1 done at 200, job 0 done at 196

The fairnewss F is pretty close to 1.


## Question 4

>  How does your answer to the previous question changeas the quantum size (-q) gets larger?

**Answer:**

Larger quantum will worsen the fairness. For example, if we set `-q 100`, then we always will get one job finishes at 100ms and another finishes at 200ms.

## Question 5

> Can you make a version of the graph that is found in the chapter? What else would be worth exploring? How would the graph look with a stride scheduler?

**Answer:**

`./lottery.py -q 12 -l 108:108,108:108,24:24,24:24 -c`

With some tuning of `-s` shall be able to achieve figure 9.4
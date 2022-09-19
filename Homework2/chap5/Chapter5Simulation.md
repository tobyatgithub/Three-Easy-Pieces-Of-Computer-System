# Homework Simulation

## Question 1

> Run./fork.py -s 10 and see which actions are taken. Can you predict what the process tree looks like at each step? Use the -c flag to check your answers. Try some different random seeds (-s) or add more actions (-a) to get the hang of it.

**Answer**:

Fairly straightforward: each fork will be a new child to the parent. Result of `./fork.py -s 10`:

```
                           Process Tree:
                               a

Action: a forks b
                               a
                               └── b
Action: a forks c
                               a
                               ├── b
                               └── c
Action: c EXITS
                               a
                               └── b
Action: a forks d
                               a
                               ├── b
                               └── d
Action: a forks e
                               a
                               ├── b
                               ├── d
                               └── e
```

## Question 2

> One control the simulator gives you is the fork percentage,controlled by the -f flag. The higher it is, the more likely the next action is a fork; the lower it is, the more likely the action is an exit. Run the simulator with a large number of actions (e.g., -a 100) and vary the fork percentage from 0.1 to 0.9. What do you think the resulting final process trees will look like as the percentage changes? Check your answer with -c.

**Answer**:

The more fork we have, the bigger and deeper the tree will be. Example to use:
`./fork.py -s 10 -a 100 -f 0.8 -c`
`./fork.py -s 10 -a 100 -f 0.2 -c`

## Question 3

> Now, switch the output by using the -t flag (e.g., run `./fork.py -t`). Given a set of process trees, can you tell which actions were taken?

**Answer**:
Yes, whenever we get a new child node, it means a fork() is called on the parent node. Whenever we have a leaf gone, it means that node EXITS.

## Question 4

> One interesting thing to note is what happens when a child exits; what happens to its children in the process tree? To study this, let’s create a specific example: `./fork.py -A a+b,b+c,c+d,c+e,c-`. This example has process ’a’ create ’b’, which in turn creates ’c’, which then creates ’d’ and ’e’. However, then, ’c’ exits. What do you think the process tree should like after the exit? What if you use the -R flag? Learn more about what happens to orphaned processes on your own to add more context.

**Answer**:

Interesting indeed! `-R` == whether the child process will re-parent to local parent if parent exits. So, without re-parent, when c EXITS, the two child processes of c will be moved up to be child of the root node/process A,

```
Action: c EXITS without -R
                               a
                               ├── b
                               ├── d
                               └── e
```

and with the re-parent, these two processes will be moved to be the child of the parent of the parent (i.e. the parent of c, which is b in this case.)

```
Action: c EXITS with -R
                               a
                               └── b
                                   ├── d
                                   └── e
```

## Question 5

> One last flag to explore is the -F flag, which skips intermediate steps and only asks to fill in the final process tree. Run ./fork.py -F and see if you can write down the final tree by looking at the series of actions generated. Use different random seeds to try this a few times.

**Answer**:

`./fork.py -F -s 20 -c`
`./fork.py -F -s 35 -c`

## Question 6

> Finally, use both -t and -F together. This shows the final process tree, but then asks you to fill in the actions that took place. By look- ing at the tree, can you determine the exact actions that took place? In which cases can you tell? In which can’t you tell? Try some different random seeds to delve into this question.

**Answer**:

`./fork.py -F -t -s 20 -c`
`./fork.py -F -t -s 35 -c`

I think in most cases we can not tell, and the main separation condition is whether we have EXITS.

The reason being, if we have no EXITS, then it is easy and clear to see who forked whom.
However, if we have EXITS, then there will be more than 1 possibilities of how to reach the final status. For example, in the example `./fork.py -F -t -s 20 -c`, we can have at least two ways to construct the final tree:

1. -A a+b,b-,a+c,c+d,a+e
2. -A a+b,b+e,a+c,c+d,b-

Here we have no way to tell whether a forked e or b forked e.

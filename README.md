*This project has been created as partof the 42 curriculum by dvidal*

--Philosophers--

## Description

The Philosophers is project that simulates the famous dining philosophers problem, proposed by Edsger Dijkstra.
The goal is to learn and implement fundamental concepts of threads, mutexes, and process synchronization.

An N amount of philosophers sit around a table with a bowl of spaghetti.
Between each pair of philosophers there is a fork. To eat, a philosopher needs two forks (the left one and the right one).
Philosophers have to alternate between three states: eating, sleeping and thinking.

The challenge is to prevent philosophers from starving while waiting to eat.

- - - - - - -

## Instructions

### Compilation :
```bash
make 
```

### Parameters :

- `number_of_philosophers`: Number of philosophers
- `time_to_die`: Time a philosopher can go without eating before dying
- `time_to_eat`: Time it takes for a philosopher to eat
- `time_to_sleep`: Time a philosopher spends sleeping
- `number_of_times_each_philosopher_must_eat`: (Optional) Number of times each philosopher must eat

### Usage :
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_repeats]
```
- - - - - - -

## Resources
- [Dining Philosophers problem - Wikipedia](https://www.youtube.com/watch?v=d9s_d28yJq0&list=PLfqABt5AS4FmuQf70psXrsMLEDQXNkLq2)
- [Unix Threads in C](https://en.wikipedia.org/wiki/Dining_philosophers_problem)

### AI usage

I used AI in this project to help resolve some errors that I couldn’t fix on my own.

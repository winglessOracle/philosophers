# Philosphers | CODAM Amsterdam

## Introduction
This CODAM assignment to master the fundamentals of multithreading and avoiding race conditions and deadlocks. It involves writing a program in C to simulate a version of the "dining philosophers problem": 
This scenario involves a group of philosophers sitting around a circular table with a bowl of spagetti in the center and a single fork placed between each pair of adjacent philosophers. 
The philosophers alternate between thinking, eating and sleeping. However, each philosopher requires two forks to eat. The dilemma arises when each philosopher tries to pick up the forks simultaneously. 
If they all reach out at the same time, they will end up in a deadlock situation where none of them can proceed. This deadlock occurs because each philosopher holds one fork and is waiting for the other one to become available, 
resulting in a standstill.

## Requirements
The program should take the following command-line arguments:
  - number_of_philosophers: The number of philosophers and forks.
  - time_to_die: The time (in milliseconds) after which a philosopher dies if not eating.
  - time_to_eat: The time (in milliseconds) it takes for a philosopher to eat.
  - time_to_sleep: The time (in milliseconds) a philosopher spends sleeping.
  - number_of_times_each_philosopher_must_eat: Optional argument; the simulation stops if all philosophers have eaten this number of times.
- Each philosopher should be implemented as a thread.
- Forks should be protected using mutexes to prevent duplication.
- Logging messages for state changes should be displayed with timestamps.
- A philosopher's death should be announced within 10 ms of the actual event.
- Data races should be avoided.

## Installation
Clone the repository
Compile: 
	make 
	make thread: to compile with fsanitizer=threads to check for race conditions
	make address: to compile with fsanitizer=address to check for memory leaks
Run the executable: ./philo

## Testing
Here are a few test cases:

	./philo 100 800 200 200
	./philo 105 800 200 200
	./philo 200 800 200 200
	./philo 5 800 200 200
	./philo 5 600 150 150
	./philo 4 410 200 200
	./philo 5 800 200 200 7
	./philo 4 410 200 200 10
Note that with the high philo numbers (100+) you might not be able to keep all philosophers alive due to resourse limitations. 

A philo should die:

	./philo 1 800 200 200
	./philo 4 310 200 100
	./philo 4 200 205 200
	./philo 4 400 200 200
	./philo 3 400 400 100

Input checks that should be handeled without breaking the program:
- non integer values
- negative values
- exceding max int and max threads:
		./philo 4 200 200 2147483648

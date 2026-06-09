*This project has been created as part of the 42 curriculum by mahmmous.*

# Philosophers

## Description
This project is an implementation of the classic "Dining Philosophers Problem" in C. The main goal is to learn the basics of threading a process and working with mutexes. It introduces complex multithreading concepts, teaching how to prevent **deadlocks**, avoid **data races**, and manage **resource starvation** when multiple threads (philosophers) share the same resources (forks) concurrently.

## Instructions

### Compilation
The project uses a `Makefile` for compilation. Navigate to the `philo` directory and run:
```bash
cd philo
make
```

### Execution
Run the simulation with the following arguments:
```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
```
*   `number_of_philosophers`: The number of philosophers and also the number of forks.
*   `time_to_die` (in milliseconds): If a philosopher didn’t start eating `time_to_die` milliseconds since the beginning of their last meal or the beginning of the simulation, they die.
*   `time_to_eat` (in milliseconds): The time it takes for a philosopher to eat. During that time, they will need to hold two forks.
*   `time_to_sleep` (in milliseconds): The time a philosopher will spend sleeping.
*   `number_of_times_each_philosopher_must_eat` (optional): If all philosophers have eaten at least this many times, the simulation stops. If not specified, the simulation stops when a philosopher dies.

**Example Usage:**
```bash
./philo 5 800 200 200 7
```

## Technical Choices
*   **Deadlock Prevention:** Implemented an even/odd fork acquisition order to break the circular wait condition.
*   **Starvation Avoidance:** Used micro-sleep adjustments (`ft_usleep(1)`) for odd numbers of philosophers to ensure fair CPU scheduling and fork distribution.
*   **Data Race Free:** Strict protection of shared variables (`sim_stop`, `last_meal_time`) using dedicated mutexes (`print_mutex`, `meal_mutex`, `stop_mutex`). Verified with `-fsanitize=thread` and Helgrind.
*   **Precise Timing:** Built a custom `ft_usleep` using `gettimeofday` to avoid the inaccuracies of the standard `usleep` function.

## Resources
*   [POSIX Threads (pthreads) Documentation](https://computing.llnl.gov/tutorials/pthreads/)
*   [Dining Philosophers Problem Overview (Wikipedia)](https://en.wikipedia.org/wiki/Dining_philosophers_problem)
*   [Coffman Conditions for Deadlocks](https://en.wikipedia.org/wiki/Deadlock#Necessary_conditions)

### AI Usage
During the development of this project, an AI assistant was utilized as a pair-programming partner. AI was specifically used for:
1. Understanding theoretical concepts regarding multithreading, context switching, and the POSIX threads API.
2. Debugging complex data races highlighted by `Helgrind` and `ThreadSanitizer`.
3. Generating documentation and evaluation guidelines to better structure the project's logic and architecture.
# Multi-Threading: Compute Statistics

> [!NOTE]
> This is not a marked exercise and is not required to be submitted for credit. The purpose of the exercise is to practice concepts from the course material.
>
> At the end of the exercise, you are instructed to write a reflection: this will help you put into words what you have learned and make you think at the new concepts and explain them.  Explaining something to another person is one of the best ways to reveal concepts that are not clear to you and require further investigation.

In this exercise, you calculate the average of values stored in a file and use multiple threads to compute some statistics on the data loaded from file.


## Learning Outcomes

Upon successful completion of this exercise, you will have demonstrated the abilities to:

- process partitioned data on two or more threads
- write a set of numbers to a file in binary mode
- read a set of numbers from a file in binary mode
- bind a function to its arguments



## Compiling and Testing Your Program

All your code should be compiled using this command on `matrix`:

```bash
/usr/local/gcc/10.2.0/bin/g++ -Wall -pthread -std=c++17 -g -o ws file1.cpp file2.cpp ...
```

- `-Wall`: compiler will report all warnings
- `-pthread`: enable multithreading support
- `-std=c++17`: the code will be compiled using the C++17 standard
- `-g`: the executable file will contain debugging symbols, allowing *valgrind* to create better reports
- `-o ws`: the compiled application will be named `ws`

After compiling and testing your code, run your program as following to check for possible memory leaks (assuming your executable name is `ws`):

```bash
valgrind --show-error-list=yes --leak-check=full --show-leak-kinds=all --track-origins=yes ws
```

- `--show-error-list=yes`: show the list of detected errors
- `--leak-check=full`: check for all types of memory problems
- `--show-leak-kinds=all`: show all types of memory leaks identified (enabled by the previous flag)
- `--track-origins=yes`: tracks the origin of uninitialized values (`g++` must use `-g` flag for compilation, so the information displayed here is meaningful).

To check the output, use a program that can compare text files.  Search online for such a program for your platform, or use *diff* available on `matrix`.




## Calculate Statistics

In this exercise you are going to load numbers stored in a binary file and calculate some statistics on them.

The three source files provided for this exercise are

- `ProcessData.h`   -- fully implemented, **do not modify**
- `ProcessData.cpp` -- partially implemented
- `tester_1.cpp`    -- already implemented, **do not modify**

A data file provided for this exercise is `data_int.bin`; First 4 bytes in the file represent an integer with the total number of data items. The remaining bytes in the file contain the data-item values, where each data-item is a 4-byte integer.

The `computeAvgFactor` and `computeVarVactor` functions, implemented in `ProcessData.cpp`, compute the average-factor and variance-factor from the data supplied in the first parameter. These functions are described as comments in the `ProcessData.cpp` file, read carefully and understand. These functions are fully implemented, do not change them.

The `ProcessData` constructor function, in the file `ProcessData.cpp` receives a filename as `std::string`, opens the file in binary mode and reads the total number of data items (first 4 bytes) followed by the data-item values. Detailed description is included as comment in `ProcessData.cpp`, read carefully and understand.

Your **first task** is to complete the definition of the constructor in class `ProcessData` to load the data from the binary file whose name is received as a parameter. See above info about the structure of the file. Do not modify existing code in this function, only add what is missing.

Your **second task** is to write definition of the `operator()` function in `ProcessData.cpp`. The prototype of this function is in the header file `ProcessData.h`. The first parameter of this function receives target-filename to which the data is to be written in binary format. The second parameter is a reference to a floating point in double precision variable for holding computed average value. The third parameter is another reference to a floating point in double precision variable for holding computed variance value. To read more about *average* of a set of numbers, read the Wikipedia entry [https://en.wikipedia.org/wiki/Average](https://en.wikipedia.org/wiki/Average); more information about *variance* can also be found on Wikipedia [https://en.wikipedia.org/wiki/Variance](https://en.wikipedia.org/wiki/Variance).

- compute the average value by calling `computeAvgFactor` with the following parameters: `data`, `total_items` as the size of the array, and again `total_items` as divisor. The fourth argument is going to be a variable in which the computed average value is to be stored.
- compute variance value by calling `computeVarFactor` with first, second and third arguments same as before, i.e., in the case of `computeAvgFactor`. The fourth argument is the average value computed by `computeAvgFactor` and fifth argument is the variable in which the computed variance is to be stored.
- open the target data file and write the data (`total_items`, and `data`) in the format of the input data file `data_int.bin`.
  
Once you confirm that the calculation produces the correct values, enhance the `operator()` to use multiple threads to calculate the average and variance:

- to compute the average, call the function `computeAvgFactor` in different threads with different parts of the `data` items divided by partition-indices.
  - bind `total_items` to the function `computeAvgFactor` as the divisor parameter.
  - create threads by passing the following arguments to the function: address of the first element of each partition as `arr`, number of elements in the partition as `size`, and an element of the resource variable created to hold average-factors as `avg`.
  - join the threads.
  - add all the average-factors into the variable to hold total average; this should be one of the parameters of the `operator()` function.
- to compute variance, call the function `computeVarFactor` in different threads with different parts of the `data` items divided by partition-indices. You follow a procedure similar to the one you followed while computing the average, with following exceptions:  
  - use the average value computed in the previous step as the 4th parameter.
  - bind `total_items` and the computed average as `divisor` and `avg`, respectively, to the function ,before creating the threads.
  - the last parameter should be an element of the resource variable created to store variance-factors.
  - add the variance-factors computed by threads to compute the total variance.
- open the target data file and write the data (`total_items`, and `data`) in the format of the input data file `data_int.bin`.


Your code must be free from memory leak.

When binding an argument to a function, consider the following reference:

- [std::bind(...)](https://en.cppreference.com/w/cpp/utility/functional/bind)


### `tester_1` Module (supplied)

The tester module has been supplied. **Do not modify the existing code!**

When doing the exercise, you are encouraged to write your own tests, focusing on a single implemented feature at the time, until you get all functionality in place.



### Sample Output


When the program is started with the command (the input file is provided):

```bash
ws data_int.bin data_int_target.bin
```

the output should look like the one from the `sample_output.txt` file.


### Computational Complexity (experiments)

Insert the following statement inside the `for` loop in both the functions `computeAvgFactor` and `computeVarFactor`.

```cpp
std::this_thread::sleep_for(std::chrono::nanoseconds(1));
```

Run your code with three different values of the argument in this statement, e.g.:

```cpp
std::this_thread::sleep_for(std::chrono::nanoseconds(1));  // or
std::this_thread::sleep_for(std::chrono::nanoseconds(10)); // or
std::this_thread::sleep_for(std::chrono::nanoseconds(50));
```

In your reflection, include discussion on your observation of the computation times with three different values of the above parameters.


### Reflection

Study your final solution, reread the related parts of the course notes, and make sure that you have understood the concepts covered by this exercise. **This should take no less than 30 minutes of your time and the result is suggested to be at least 150 words in length.**

Create a **text** file named `reflect.txt` that contains your detailed description of the topics that you have learned in completing this particular exercise and mention any issues that caused you difficulty and how you solved them. Include in your explanation—**but do not limit it to**—the following points:

- was there any benefit from using binary files in this exercise?
- why would be important to bind a function to its arguments, and how was it useful in this exercise?
- the advantages of using multiple threads, and how did you accomplis multi-threading in this exercise?

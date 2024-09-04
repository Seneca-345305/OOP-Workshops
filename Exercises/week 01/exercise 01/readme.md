# Across Translation Units: Food Orders

> [!NOTE]
> This is not a marked exercise and is not required to be submitted for credit. The purpose of the exercise is to practice concepts from the course material.
>
> At the end of the exercise, you are instructed to write a reflection: this will help you put into words what you have learned and make you think at the new concepts and explain them.  Explaining something to another person is one of the best ways to reveal concepts that are not clear to you and require further investigation.

In this exercise, you implement aspects of linkage, storage duration, namespaces, header guards, and operating system interfaces.

## Learning Outcomes

Upon successful completion of this exercise, you will have demonstrated the abilities to:

- receive program arguments from the command line
- guard a class definition from duplication in a translation unit
- access a variable defined in a different translation unit
- declare a local variable that resides in memory throughout the lifetime of the program
- manage a resource in a class to avoid memory leaks



## Compiling and Testing Your Program

All your code should be compiled using this command on `matrix`:

```bash
/usr/local/gcc/10.2.0/bin/g++ -Wall -std=c++17 -g -o ws file1.cpp file2.cpp ...
```

- `-Wall`: compiler will report all warnings
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

To check the output, use a program that can compare text files.  Search online for such a program for your platform, or use `diff` available on `matrix`.






## Food Orders

This application records food orders made by customers and calculates the price with relation to the current tax rate and special daily discounts on certain items.

The application loads the order information from multiple files. Each file read represents orders taken from a certain day. The orders are handled somewhat differently depending if they are an *In-House* order or *Delivery* order.

### `tester_1` Module (partially supplied)

Study the code supplied and make sure you understand it.

Finish the implementation of the `main` function, by completing the parts marked with `TODO`:

- write the prototype of the `main` function to receive a set of standard command line arguments
- echo the set of arguments to standard output in the following format:

  ```txt
  1: first argument
  2: second argument
  3: third argument
  4: ...
  ```

**Do not modify this module in any other place!**

### `FoodOrder` Module

The `FoodOrder` module defines the current tax rate and daily special discount, as two global variables named `g_taxrate` and `g_dailydiscount` that stores in floating point numbers in double precision.  The value of the tax rate and daily discount may change from day to day. These two variables will be accessed when a new day of orders starts from the `main` function.

This module also defines a class named `FoodOrder` in the namespace `seneca` that stores some information about an order of food:

- a C-style null-terminated string of up to 10 characters *including the null byte terminator* representing the name of the customer ordering the food.
- a C-style null-terminated string of *any length* representing the description of the food.  **Make sure your program does not have memory leaks.**
- the price of the food represented by a floating point number in double precision.
- a Boolean flag indicating whether the order is a daily special.


#### Public Members

- default constructor
- `read()`: a modifier that receives an `istream` reference.

  - if the `istream` is in a good state, this function will attempt to read from the `istream` and store the information read into current object. The data read in will be in the following format:

    ```txt
    <Customer Name>,<Order Description>,<Price>,<Daily Special Status>[newline]
    ```

    The daily special status can be of two values: `'Y'` for it is a special and `'N'` for it is not.
  - if the `istream` object is not in a good state then this function will do nothing.

  When implementing this function, it may be advisable to review the Input/Output Objects chapter from the 200/244 [Course Notes](http://intro2oop.sdds.ca/C-Encapsulation/input-and-output-operators).

  Also, consider the use of these `std::string` related functions:

  - [std::getline](https://en.cppreference.com/w/cpp/string/basic_string/getline)
  - [std::string::c_str](https://en.cppreference.com/w/cpp/string/basic_string/c_str)
  - [std::string::length](https://en.cppreference.com/w/cpp/string/char_traits/length)

- `display()`: a query that displays to the screen the content of an `FoodOrder` instance in the following format:

  ```txt
  COUNTER. Name          |Order Description        |Price w/Tax |Special Price
  ```

  If no customer name has been stored in the current object, this query should print:

  ```txt
  COUNTER. No Order
  ```

  where

  - `COUNTER` is a *left aligned* field of size 2, that holds the number of times that this function has been called (use a local-to-function variable that remains in memory for the lifetime of the program) **Do not use global/member variables to store the counter!**
  - `Name` is a  *left aligned* field of size 10 that represents the name of the customer that made the order.
  - `Order Description` is a *left aligned* field of size 25 that represents the description of the food ordered.
  - `Price w/Tax` is a *left aligned* field of size 12 with 2 decimal point precision that represents the price of the food ordered with tax calculated based on the current tax rate.
  - `Special Price` is a *right aligned* field of size 13 that represents the taxed price of the food ordered with the daily discount applied on top if the order was a daily special. If the order is not a daily special then nothing is printed here.

Add any other **private** members that your design requires (without changing the specs above)!


### Sample Output

The input files `day1.txt` and `day2.txt` are already provided; the main module contains a description of the structure for these files.

When the program is started with the command:

  ```bash
  ws day1.txt missing.txt day2.txt
  ```

the output should look like the one from the `sample_output.txt` file.

> [!CAUTION]
> Please note that a matching output is not a guarantee that the program is bug-free; it only means that in the specific tests this tester performed, no bugs/issues were identified. It is possible to write a tester that looks at other aspects of your code that will reveal bugs.



### Reflection

Study your final solution, reread the related parts of the course notes, and make sure that you have understood the concepts covered by this exercise. **This should take no less than 30 minutes of your time and the result is suggested to be at least 150 words in length.**

Create a **text** file named `reflect.txt` that contains your ***detailed*** description of the topics that you have learned in completing this exercise and mention any issues that caused you difficulty and how you solved them. Include in your explanation—**but do not limit it to**—the following points:

- the difference between internal and external linkage citing examples from your code
- what are `static` variables and how are they useful in your solution.
- what members (not mentioned in the specs above) you had to add to your `FoodOrder` class to avoid memory leaks when dealing with the description of the food.

Refer to code snippets in your solution as examples to support your explanations.

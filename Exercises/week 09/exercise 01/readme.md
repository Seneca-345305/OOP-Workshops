# Smart Pointers: An Encrypted Database

> [!NOTE]
> This is not a marked exercise and is not required to be submitted for credit. The purpose of the exercise is to practice concepts from the course material.
>
> At the end of the exercise, you are instructed to write a reflection: this will help you put into words what you have learned and make you think at the new concepts and explain them.  Explaining something to another person is one of the best ways to reveal concepts that are not clear to you and require further investigation.

In this exercise, you will use smart pointers to manage a memory resource.



## Learning Outcomes

Upon successful completion of this workshop, you will have demonstrated the abilities to:

- create a program component of quadratic complexity
- use a smart pointer to move an object


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

To check the output, use a program that can compare text files.  Search online for such a program for your platform, or use *diff* available on `matrix`.




## An Encrypted Database

**Your task is to create** the `Database` module according to the specs below.  This module will load data from a file and stored it in some attributes; the data in the file is organized on two columns, separated by a number of blanks.  For simplicity purposes, you can assume that the text on each column contains no spaces. See the provided input file for more details on the structure of the file.

The values stored in the file (second column) are encrypted; your application must decrypt them when loading data from file, and encrypt them before saving them into a file.

Enclose all your source code within the `seneca` namespace and include the necessary guards in each header file.



### `database` Module

This modules defines a class named `Database` that manages two parallel arrays: an array of `keys` (for the first column in the input file) and an array of `values` (for the second column in the input file).

Your task is to design and code a templated class named `Database`; this class has only one template parameter `T` representing the type of a value.

Add to this module the enumeration (will be used to signal that an operation finished with success, or some error occurred):

```cpp
enum class Err_Status
{
  Err_Success,
  Err_NotFound,
  Err_OutOfMemory,
};
```


#### Private Members

**This class can be instantiated only once.**  To accomplish this, the class will **NOT** have any public constructors (this will prevent clients to create instances).

- a variable representing the number of entries in the database.
- a statically-allocated array of strings representing the keys. The size of this array is 20.
- a statically-allocated array of objects of type `T` representing the values. The size of this array is 20.
- a string representing the database file name.
- a class variable (a `static` attribute) that will store the address of the one-and-only instance of type `Database`.  Use an STL smart pointer as a datatype for this attribute (*HINT*: use `std::shared_ptr`; explain in the reflection why `std::unique_ptr` is not a good choice).
- `Database(const std::string& filename)`: a private constructor to prevent client from instantiating this class. This constructor:
  - prints to the screen the address of the current instance and the prototype of the constructor (see sample output for details)
  - opens the file and read the key/value pairs into the attributes. Assume that the file is correct and exists (no need to check for errors).
  - replaces any underscore character (`_`) that appears in the keys with a single space before storing it into attributes.
  - decrypts the `value` loaded from the database file by calling the `encryptDecrypt()` function and passing the `value` as a parameter.
- `void encryptDecrypt(T& value) { /* nothing */ }`: an empty body function (does nothing, you will specialize it later).

Add any other **private** members that your design requires (without changing the specs)!



#### Public Members

- `std::shared_ptr<Database<T>> getInstance(const std::string& dbFileName)`: a class function that will provide to the client the one-and-only object of this type that is allowed to exist.  This function:
  - receives as a parameter a string representing the filename of the database file
  - if the class `Database` has already been instantiated (the `static` attribute is not null), then this function returns the static attribute and does nothing else.
  - if the class `Database` has not been instantiated (the `static` attribute is null), then this function creates an instance of type `Database` (using the private constructor) and stores it in the static attribute. Return the `static` attribute to the client.
- `Err_Status GetValue(const std::string& key, T& value)`: a query that searches in the array of keys for the first parameter:
  - if the key is found, store in the second parameter the corresponding value from the array of values and return `Err_Status::Err_Success`.
  - if the key is not found, return `Err_Status::Err_NotFound`.
- `Err_Status SetValue(const std::string& key, const T& value)`: a modifier that receives as parameters a key and a value. If there is space in the database (the capacity of the array not been reached), the key/value pair is added and the function returns `Err_Success`. Otherwise, it returns `Err_OutOfMemory`.
- a destructor that:
  - prints to the screen the address of the current instance and the prototype of the destructor (see sample output for details)
  - iterates over the database content and creates a database backup in a separate file. The backup file name will be the input file name with the string `.bkp.txt` appended to it. For example if the input file is `data.txt` the backup file should be `data.txt.bkp.txt`.
  - before saving a `value` into the backup database file, call the `encryptDecrypt()` function, passing the `value` as a parameter (the `value` stored in memory is decrypted, this function will encrypt it).
  - the format of this file is (see `sample_data.txt.bkp.txt`):

  ```txt
  KEY -> ENCRYPTED_VALUE
  KEY -> ENCRYPTED_VALUE
  KEY -> ENCRYPTED_VALUE
  ...
  ```

  where `KEY` should be printed on a field of size 25 characters, aligned to the left.



#### Specializations

- specialize the `encryptDecrypt()` for the type `std::string` as following (pseudocode):

  ```pseudocode
  encryptDecrypt(value)
  {
    const char secret[]{ "secret encryption key" };

    foreach character C in the parameter
      foreach character K in the secret
        C = C ^ K
  }
  ```

- specialize the `encryptDecrypt()` for the type `long long` as following (pseudocode):

  ```pseudocode
  encryptDecrypt(value)
  {
    const char secret[]{ "super secret encryption key" };

    foreach byte B in the parameter
      foreach character K in the secret
        B = B ^ K
  }
  ```

  To access the individual bytes in the parameter use the conversion operator (`reinterpret_cast<char*>(&value)`).  The number of bytes in a `long long` object can be found using `sizeof` operator.

This is a simple encryption procedure (not to be used for security since is very easy to break by modern computers); more details at [https://kylewbanks.com/blog/Simple-XOR-Encryption-Decryption-in-Cpp](https://kylewbanks.com/blog/Simple-XOR-Encryption-Decryption-in-Cpp).



### `tester_1` module

The tester module has been supplied. **Do not modify the existing code!**

When doing the exercise, you are encouraged to write your own tests, focusing on a single implemented feature at the time, until you get all functionality in place.



### Sample Output

When the program is started with the command:

```bash
ws data_str.txt data_num.txt
```

the output should look like the one from the `sample_output_run_1.txt` and `sample_output_run_2.txt` files in two consecutive runs.





### Reflection

Study your final solution, reread the related parts of the course notes, and make sure that you have understood the concepts covered by this workshop. **This should take no less than 30 minutes of your time and the result is suggested to be at least 150 words in length.**

Create a **text** file named `reflect.txt` that contains your detailed description of the topics that you have learned in completing this workshop and mention any issues that caused you difficulty and how you solved them. Include in your explanation-**but do not limit it to**-the following points:

- why could we not use a `unique_ptr` in your `Database` class?
- a class that allows only one instance to be created is called a *singleton*. Can you think of another way to create a singleton without using static members? How would that object be managed?
- the class `Database` has a resource attribute (the database instance), yet no copy/move operations were implemented. Is that a bug (justify your answer)?
- the class `Database` can be instantied only once, yet in the output we see that the custom constructor is called twice (same for the destructor). Explain.

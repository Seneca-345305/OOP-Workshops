# Templates: Collections and Sets

> [!NOTE]
> This is not a marked exercise and is not required to be submitted for credit. The purpose of the exercise is to practice concepts from the course material.
>
> At the end of the exercise, you are instructed to write a reflection: this will help you put into words what you have learned and make you think at the new concepts and explain them.  Explaining something to another person is one of the best ways to reveal concepts that are not clear to you and require further investigation.

In this exercise, you design and code several class templates and test them on different instantiations.



## Learning Outcomes

Upon successful completion of this workshop, you will have demonstrated the abilities to:

- design and code a class template
- template a class variable
- specialize a templated class variable for a particular type
- instantiate a template class
- specialize a member function of a templated class to process a particular type
- derive a templated class from another templated class



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




## Collections and Sets

In this application you create a class that manages a collection of objects of any type. Based on this class, then you create another class that doesn't allow duplicated objects.

Enclose all your source code within the `seneca` namespace and include the necessary guards in each header file.

The `Collection` and `Set` modules **you create** in this workshop must have only a header file. *🗎 Explain in the reflection why we do not split a module into `*.h` and `*.cpp` like you did in the previous workshops.*

In all classes that you create, you are allowed to add any **private** members that your design requires (without changing the specs)!



### `tester` Module (supplied)


**Do not modify this module!**  Look at the code and make sure you understand how to instantiate a templated class.



### `Pair` Module

This module represents a *value-key* pair (like the words and their definition in a dictionary).

```cpp
class Pair
{
	std::string m_key{};
	std::string m_value{};
public:
	const std::string& getKey() { return m_key; }
	const std::string& getValue() { return m_value; }
	Pair(const std::string& key, const std::string& value) : m_key{ key }, m_value{ value }{};

	// TODO: Add here the missing prototypes for the members
	//           that are necessary if this class is to be used
	//           with the template classes described below.
	//       Implement them in the Pair.cpp file.
}
```

Two objects of type `Pair` are considered to be equal if they have the same key.

*🗎 In the reflection **justify** why it was necessary to add each one of the members you have decided to add.*

### `Collection` Module

This module represents a family of collections of elements of any data type (for example, collection of `int`s, or collection of `Pair`s, etc.).

Design and code a class template named `Collection`. Your template manages a statically allocated array of any datatype. The template parameters in order of their specification are:

- `T`: the type of any element in the collection.
- `CAPACITY`: the capacity of the collection (a non-type parameter; an integer without sign). This is the maximum number of elements that can be added to the collection.

Your design keeps track of the current number of elements stored in the collection (which may differ from the capacity of the collection). Initially the collection has no elements.

Add any **private** members that your design requires (without changing the specs)!

> [!WARNING]
> All data-members in this class must be **private**! The client will access the collection elements through the public interface.

#### Class Members (or Type Members)

These are the `static` members that your class should define:

- an object of type `T` stat stores the default value of an element in the collection. This object will be returned by member-functions when the client requests an object that doesn't exist in the collection.

#### Public Members

- `size()`: a query that returns the current number of elements in the collection
- `display()`: a query that receives as the parameter an output stream (with default value `std::cout`) and inserts into the stream all items from the collection (see the sample output for formatting hints).
- `bool add(const T& item)`: a mutator that adds a copy of the parameter to the collection if there still is capacity. If the item has been successfully added, this function returns `true`; `false` otherwise. Enable inclusion polymorphism on this function (make it `virtual`).
- `operator[]`: a query that receives an index as parameter and returns a copy of the element stored in the collection at the specified index. If the index is not valid (outside the boundaries of the collection), this query returns the default object (the `static` member mentioned above).
- a destructor with inclusion polymorphism enabled.


#### Specializations

**Specialize** the definition of the default object when type `T = Pair` and `CAPACITY = 100` so the key is `"No Key"` and the value is `"No Value"`.

> [!WARNING]
> Do not specialize the constructor or, worse, the class itself.



### `Set` Module

The module `Set` represents a `Collection` where no item appears more than once.

Derive the `Set` class template from `Collection<T, 100>` (the `Set` will always have a capacity of 100 items).  The `Set` will have only one template parameter `T`.

#### Public Members

- **override** the inherited function `add` to prevent adding an item if it already exists in the `Set`.

No other members need to be added to this class.

#### Specializations

- for `T = double`, the function `add()` should consider that two numbers are the same if their difference in the absolute value is smaller or equal to `0.01`.

  When implementing this specialization, consider the function [std::fabs()](https://en.cppreference.com/w/cpp/numeric/math/fabs).






### Sample Output

When the program is started with the command:

  ```bash
  ws
  ```

  the output should look like the one from the `sample_output.txt` file.

> [!CAUTION]
> Please note that a matching output is not a guarantee that the program is bug-free; it only means that in the specific tests this tester performed, no bugs/issues were identified. It is possible to write a tester that looks at other aspects of your code that will reveal bugs.



### 🗎 Reflection

Study your final solution, reread the related parts of the course notes, and make sure that you have understood the concepts covered by this workshop. **This should take no less than 30 minutes of your time and the result is suggested to be at least 150 words in length.**

Create a **text** file named `reflect.txt` that contains your detailed description of the topics that you have learned in completing this workshop and mention any issues that caused you difficulty and how you solved them. Include in your explanation—**but do not limit it to**—the following points:

- the reason for specializing the `add()` member function.
- the reason for defining the class variable outside the class definition.
- answers to the other questions in these specifications.

Refer to code in your solution as examples to support your explanations.

# Workshop 3: Templates

In this workshop, you design and code several class templates and test them on different instantiations.



## Learning Outcomes

Upon successful completion of this workshop, you will have demonstrated the abilities to:

- design and code a class template
- template a class variable
- specialize a templated class variable for a particular type
- instantiate a template class
- specialize a member function of a templated class to process a particular type
- derive a templated class from another templated class



## Submission Policy

The workshop is divided into two coding parts and one non-coding part:

- *Part 1*: worth 0% of the workshop's total mark, is optional and designed to assist you in completing the second part.
- *Part 2*: worth 100% of the workshop's total mark, is due on **Sunday at 23:59:59** of the week of your scheduled lab.  Submissions of *Part 2* that do not contain the *reflection* are not considered valid submissions and are ignored.
- *reflection*: non-coding part, to be submitted together with *Part 2*. The reflection does not have marks associated to it, but can incur a **penalty of max 40% of the whole workshop's mark** if your professor deems it insufficient (you make your marks from the code, but you can lose some on the reflection).

The workshop should contain ***only work done by you this term*** or provided by your professor.  Work done in another term (by you or somebody else), or work done by somebody else and not **clearly identified/cited** is considered plagiarism, in violation of the Academic Integrity Policy.

Every file that you submit must contain (as a comment) at the top **your name**, **your Seneca email**, **Seneca Student ID** and the **date** when you completed the work.

- If the file contains only your work, or work provided to you by your professor, add the following message as a comment at the top of the file:

    > I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.

- If the file contains work that is not yours (you found it online or somebody provided it to you), **write exactly which parts of the assignment are given to you as help, who gave it to you, or which source you received it from.**  By doing this you will only lose the mark for the parts you got help for, and the person helping you will be clear of any wrong doing.



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
valgrind ws
```

To check the output, use a program that can compare text files.  Search online for such a program for your platform, or use *diff* available on `matrix`.



## Part 1 (0%)

This workshop consists of the following modules:
- `w3` (supplied)
- `Pair` (partially supplied)
- `Collection`
- `Set`

The solution to Part 1 invokes the first three modules. 

Enclose all your source code within the `seneca` namespace and include the necessary guards in each header file.

The `Collection` and `Set` modules **you create** in this workshop must have only a header file. *🗎 Explain in the reflection why we do not split a module into `*.h` and `*.cpp` like you did in the previous workshops.*

In all classes that you create, you are allowed to add any **private** members that your design requires (without changing the specs)!



### `w3` Module (supplied)


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

- `T`: the type of any element in the collection
- `CAPACITY`: the capacity of the collection (a non-type parameter; an integer without sign). This is the maximum number of elements that can be added to the collection

Your design keeps track of the current number of elements stored in the collection (which may differ from the capacity of the collection). Initially the collection has no elements.

***Class Members***

- An object of type `T` (a dummy object). This object will be returned by member-functions when the client requests an object that is not in the collection.

***Public Members***

- `size()`: a query that returns the current number of elements in the collection
- `display()`: a query that receives as the parameter an output stream (with default value `std::cout`) and inserts into the stream all items from the collection (see the sample output for formatting hints).
- `bool add(const T& item)`: a mutator that adds a copy of the parameter to the collection if there still is capacity. If the item has been added, this function return `true`; `false` otherwise.
- `operator[]`: a query that receives an index as parameter and returns a copy of the element stored in the collection at the specified index. If the index is not valid (outside the boundaries of the collection), this query returns the dummy object.


Add any other **private** members that your design requires (without changing the specs above)!

**Specialize** the dummy object when type `T = Pair` and `CAPACITY = 100` so the key is `"No Key"` and the value is `"No Value"`. 

### Sample Output

When the program is started with the command:
```
ws
```
the output should look like the one from the `sample_output.txt` file.




### Test Your Code

To test the execution of your program, use the same data as shown in the output example above.

Upload your source code to your `matrix` account. Compile and run your code using the latest version of the `g++` compiler (available at `/usr/local/gcc/10.2.0/bin/g++`) and make sure that everything works properly.

Then, run the following command from your account (replace `profname.proflastname` with your professor’s Seneca userid):
```
~profname.proflastname/submit 345_w3_p1
```
and follow the instructions.

***This part represents a milestone in completing the workshop and is not marked!***










## Part 2 (100%)

The second part of this workshop upgrades your Part 1 solution by adding a collection named `Set` that doesn't allow duplicates.



### `Collection` Module

Modify the `add()` member function in the `Collection` module to enable inclusion polymorphism on the hierarchy. For the same purpose, add an empty body destructor.

No other changes are necessary to this module.





### `Set` Module

Add to your project a new module called `Set` that represents a `Collection` where no item appears more than once.

Derive the `Set` class template from `Collection<T, 100>` (the `Set` will always have a capacity of 100 items).  The `Set` will have only one template parameter `T`.

***Public Members***

- **override** the inherited function `add` to prevent adding an item if it already exists in the `Set`.

No other members need to be added to this class.

***Specializations***

- for `T = double`, the function `add()` should consider that two numbers are the same if their difference in the absolute value is smaller or equal to `0.01`.

  When implementing this specialization, consider the function [std::fabs()](https://en.cppreference.com/w/cpp/numeric/math/fabs).



### Sample Output

When the program is started with the command:
```
ws
```
the output should look like the one from the `sample_output.txt` file.




### 🗎 Reflection

Study your final solution, reread the related parts of the course notes, and make sure that you have understood the concepts covered by this workshop. **This should take no less than 30 minutes of your time and the result is suggested to be at least 150 words in length.**

Create a **text** file named `reflect.txt` that contains your detailed description of the topics that you have learned in completing this workshop and mention any issues that caused you difficulty and how you solved them. Include in your explanation—**but do not limit it to**—the following points:
- the reason for specializing the `add()` member function.
- the reason for defining the class variable outside the class definition.
- answers to the other questions in these specifications.

To avoid deductions, refer to code in your solution as examples to support your explanations.





### Submission

To test and demonstrate execution of your program use the same data as shown in the output example above.

Upload the source code and the reflection file to your `matrix` account. Compile and run your code using the latest version of the `g++` compiler (available at `/usr/local/gcc/10.2.0/bin/g++`) and make sure that everything works properly.

Then, run the following command from your account (replace `profname.proflastname` with your professor’s Seneca userid):
```
~profname.proflastname/submit 345_w3_p2
```
and follow the instructions.

**:warning:Important:** Please note that a successful submission does not guarantee full credit for this workshop. If the professor is not satisfied with your implementation, your professor may ask you to resubmit. Resubmissions will attract a penalty.

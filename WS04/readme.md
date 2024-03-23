# Workshop 4: Containers

In this workshop, you will code three classes that are in composition and aggregation relations. The classes will simulate an order system for children's toys. The child will manage a collection of toys (composition) and an order system will send confirmations for the toys.



## Learning Outcomes

Upon successful completion of this workshop, you will have demonstrated the abilities to:

- design and code composition and aggregation class relationships
- use member functions of the string class to parse a string into tokens based on simple rules
- design and code a class that manages a dynamically allocated array of pointers to objects (double pointers)


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

The first portion of this workshop consists of modules:
- `w4` (supplied)
- `Toy`

Enclose all your source code within the `seneca` namespace and include the necessary guards in each header file.


### `w4` Module (supplied)


**Do not modify this module!**  Look at the code and make sure you understand it.



### `Toy` Module

This module includes the definition of a class that manages information about a single toy. A multiple number of this toy can be ordered.

Design and code a class named `Toy` that can store the following information (for each attribute, choose any type that you think is appropriate--you must be able to justify the decisions you make):

- **order id** the order id of the toy (a positive number)
- **the name** the name of the toy
- **the number of items** the number of toys of this type to be ordered
- **the price** the price of this toy
- **the harmonized sales tax** assume the HST is equal to 13%

***Private Members***

- Add as many private members as your design requires


***Public Members***
- a default constructor
- `void update(int numItems)`: a modifier that receives as a parameter the number of toys of this type to be ordered and updates the number of items attribute with the received value. Assume the parameter is correct and doesn't require validation.
- `Toy(const std::string& toy)`: A constructor that receives the toy attributes as a string; this constructor is responsible for extracting information about the toy from the string and storing the tokens in the instance's attributes. The string will always have the following format:
  ```
  ID:NAME:NUM:PRICE
  ```
  This constructor should remove all leading and trailing spaces from the **beginning and end** of any token extracted from the string.

  When implementing the constructor, consider this following functions:
  - [std::string::substr()](https://en.cppreference.com/w/cpp/string/basic_string/substr)
  - [std::string::find()](https://en.cppreference.com/w/cpp/string/basic_string/find)
  - [std::string::erase()](https://en.cppreference.com/w/cpp/string/basic_string/erase)
  - [std::stoi()](https://en.cppreference.com/w/cpp/string/basic_string/stol)


***Friend Helpers***
- overload the insertion operator to insert the contents of a toy object into an `ostream` object:
  - The word Toy ("Toy")
  - the ID of the toy should display on a field of size 8 followed by a colon (':')
  - The name of the toy should display on a field of size 18, aligned to the right
  - The number of items should display on a field of size 3,
  - The word items preceded by a space (" items"),
  - The price of the toy should display on a field of size 8
  - The words "/item  subtotal:" should follow
  - The subtotal should display on a field of size 7 (the price times the number of items)
  - The word tax: should follow preceded by a space (" tax:")
  - The tax should display on a field of size 6 (the amount of tax paid on the subtotal)
  - The word total: should follow preceded by a space (" total:")
  - The total should display on a field of size 7 (the subtotal plus the tax)
- Look in the sample output file for hints about formatting

### Sample Output

When the program is started with the command (the file `data.txt` is provided):
```
ws data.txt
```
the output should look like the one from the `sample_output.txt` file.





### Test Your Code

To test the execution of your program, use the same data as shown in the output example above.

Upload your source code to your `matrix` account. Compile and run your code using the latest version of the `g++` compiler (available at `/usr/local/gcc/10.2.0/bin/g++`) and make sure that everything works properly.

Then, run the following command from your account (replace `profname.proflastname` with your professor’s Seneca userid):
```
~profname.proflastname/submit 305_w4_p1
```
and follow the instructions.

***This part represents a milestone in completing the workshop and is not marked!***










## Part 2 (100%)

The second part of this workshop upgrades your solution to include two more modules:
- `Child`
- `ConfirmOrder`

The module `Toy` doesn't need any change.



### `Child` Module

Add a `Child` module to your project that defines a class named `Child`. This class should have attributes to store a name and an age, and maintain a dynamically allocated array of pointers of type `Toy`: `const seneca::Toy**` (each element of the array points to an object of type `Toy`).

***Private Members***

- An attribute of type `const seneca::Toy**` representing the dynamically allocated array of pointers
- Add as many private members as your design requires
- *🗎 Explain in the reflection what is the relationship between `Child` and `Toy`, and what is the relationship between `Child` and the **array** of pointers.*

***Public Members***

- `Child(std::string name, int age, const Toy* toys[], size_t count)`: a constructor that receives as a parameter a name and an age, and an array of pointers to objects of  type `Toy` (i.e., each element of the array is a pointer). If you need a refresh on arrays of pointers, re-read the material from the last term (chapter **Abstract Base Classes**, section **Array of Pointers**).
  - this constructor should store **copies** of all toys
  
- add any other special members that are necessary to manage the toys stored

- `size_t size() const`: a query that returns the number of toys stored in the array attribute.

***Friend Helpers***

- overload the insertion operator to insert the content of a `Child` object into an `ostream` object. This operator should use a local to function variable to count how many times this operator has been called (`CALL_CNT` below). It should also insert the child's name (`NAME` below) and the child's age (`AGE` below):
  - if there are no toys:
  ```
  --------------------------
  Child CALL_CNT: NAME AGE years old:
  --------------------------
  This child has no toys!
  --------------------------
  ```
  - if there are toys:
  ```
  --------------------------
  Child CALL_CNT: NAME AGE years old:
  --------------------------
  TOY
  TOY
  ...
  --------------------------
  ```





### `ConfirmOrder` Module

Add a `ConfirmOrder` module to your project. The purpose of this module is to receive all the toys from multiple children, and contact the recipients with a confirmation message.

This module should maintain a dynamically allocated array of **pointers** to objects of type `Toy`: `const seneca::Toy**` (each element of the array is a pointer to an object of type `Toy`).

This class should have attributes to store and manage a **dynamically-allocated array of pointers** to objects of type `Toy`: `const sdds::Toy**` (each element of the array points to an object of type `Toy`). ***Very Important***: This class is responsible for managing the array of pointers but is not managing the life of `Toy` objects.

![Toys and Child & Confirmation Order](toys.svg)

***Private Members***

- An attribute of type `const seneca::Toy**` representing the dynamically allocated array of pointers
- Add as many private members as your design requires
- *🗎 Explain in the reflection what is the relationship between `ConfirmOrder` and `Toy`, and what is the relationship between `ConfirmOrder` and the **array** of pointers.*

***Public Members***

- add any special members that are necessary to manage the resource (the resource is an **array of pointers**; your class must manage this array, but the objects at the addresses stored in the array are managed outside this class)

- `ConfirmOrder& operator+=(const Toy& toy)`: adds the toy `toy` to the array by adding its address.
  - if the address of `toy` is already in the array, this operator does nothing
  - resizes the array to make room for `toy` if necessary
  - stores the **address** of `toy` in the array (your function should not make copies of the toy itself)

- `ConfirmOrder& operator-=(const Toy& toy)`: removes the toy `toy` from the array by removing its address
  - if the address of `toy` is not in the array, this operator does nothing
  - searches the array for the address of `toy`, sets the pointer in the array to `nullptr` if `toy` is found.
  
  **To challenge yourself, try to actually resize the array.**

- add any other **special members** that are necessary to manage the resource.



***Friend Helpers*** 

- overload the insertion operator to insert the content of a `ConfirmOrder` object into an **ostream** object:
  - if there are no toys to confirm:
  ```cpp
  --------------------------
  Confirmations to Send
  --------------------------
  There are no confirmations to send!
  --------------------------
  ```
  - if there are toys to confirm
  ```cpp
  --------------------------
  Confirmations to Send
  --------------------------
  TOY
  TOY
  ...
  --------------------------
  ```

Add any **private** members that your design requires (without changing the specs above)!



### Sample Output

When the program is started with the command (the file `data.txt` is provided):
```
ws data.txt
```
the output should look like the one from the `sample_output.txt` file.




### Reflection

Study your final solution, reread the related parts of the course notes, and make sure that you have understood the concepts covered by this workshop. **This should take no less than 30 minutes of your time and the result is suggested to be at least 150 words in length.**

Create a **text** file named `reflect.txt` that contains your detailed description of the topics that you have learned in completing this particular workshop and mention any issues that caused you difficulty and how you solved them. Include in your explanation—**but do not limit it to**—the following points:
- the difference between the implementations of a composition and an aggregation. Note that both classes `Child` and `ConfirmOrder` have an attribute of type `const Toy**` and yet they are in different relationships with class `Toy`.  *Discuss!*
- the difference between the implementations of move and copy functions in a composition and an aggregation.

Identify places in your code where you have used **association**, **aggregation** and **composition** relations.

To avoid deductions, refer to code in your solution as examples to support your explanations.





### Submission

To test and demonstrate execution of your program use the same data as shown in the output example above.

Upload the source code and the reflection file to your `matrix` account. Compile and run your code using the latest version of the `g++` compiler (available at `/usr/local/gcc/10.2.0/bin/g++`) and make sure that everything works properly.

Then, run the following command from your account (replace `profname.proflastname` with your professor’s Seneca userid):
```
~profname.proflastname/submit 305_w4_p2
```
and follow the instructions.

**:warning:Important:** Please note that a successful submission does not guarantee full credit for this workshop. If the professor is not satisfied with your implementation, your professor may ask you to resubmit. Resubmissions will attract a penalty.


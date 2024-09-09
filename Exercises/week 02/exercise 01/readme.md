# Move and Copy Semantics: Protein Sequences

> [!NOTE]
> This is not a marked exercise and is not required to be submitted for credit. The purpose of the exercise is to practice concepts from the course material.
>
> At the end of the exercise, you are instructed to write a reflection: this will help you put into words what you have learned and make you think at the new concepts and explain them.  Explaining something to another person is one of the best ways to reveal concepts that are not clear to you and require further investigation.

In this exercise, you work with a large dynamically allocated array of C++ Standard Library strings and compare the performance of copy and move operations on that collection.



## Learning Outcomes

Upon successful completion of this exercise, you will have demonstrated the abilities to:

- retrieve records from a text file using an input file stream object
- count the number of records in a text file
- monitor the time spent on a particular task using the `std::chrono` library
- implement **copy semantics** for a class with a resource
- implement **move semantics** for a class with a resource
- identify the processing-intensive operations in copy and move assignments



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




## Protein Sequences

This application loads a set of proteins from a file in *UniProtKB* format (UniProt KnowledgeBase), stores them in memory, and performs some operations on them.

A protein is a linear sequence of amino acids. This program will use the one-letter representation of each amino acid; thus a protein will be represented as a string where each letter identifies an amino acid.  To read more about proteins, the amino acids that form them, or the one-letter representation for each amino acid you can consult the [Wikipedia page](https://en.wikipedia.org/wiki/Protein_primary_structure).

Each entry in the *UniProtKB* file has a header containing information about the protein, folowed by the sequence of letters representing the amino acids. The structure of the header is:

```txt
>db|UniqueIdentifier|EntryName ProteinName OS=OrganismName OX=OrganismIdentifier [GN=GeneName ]PE=ProteinExistence SV=SequenceVersion
```

Where:

- `db` is `sp` for *UniProtKB/Swiss-Prot* and `tr` for *UniProtKB/TrEMBL*.
- `UniqueIdentifier` is the primary accession number of the *UniProtKB* entry.
- `EntryName` is the entry name of the *UniProtKB* entry.
- `ProteinName` is the recommended name of the *UniProtKB* entry as annotated in the *RecName* field.
- `OrganismName` is the scientific name of the organism of the *UniProtKB* entry.
- `OrganismIdentifier` is the unique identifier of the source organism, assigned by the NCBI.
- `GeneName` is the first gene name of the *UniProtKB* entry. If there is no gene name, the `GN` field is not listed.
- `ProteinExistence` is the numerical value describing the evidence for the existence of the protein.
- `SequenceVersion` is the version number of the sequence.

The protein sequence will begin on the next line after the header line for some number of lines. Each line (except the last one) will contain exactly **60** characters.



### `tester_1` Module (supplied)


**Do not modify this module!**  Study the code supplied and make sure you understand it.



### `TimedTask` Module

Design and code a class named `TimedTask` that manages a **statically**-allocated array of `Task` objects.  Your class predefines the maximum number of event objects at 10. The **instance variables** for your class should include:

- the number of records currently stored
- the start time for the current task (an object of type `std::chrono::steady_clock::time_point`; see documentation [here](https://en.cppreference.com/w/cpp/chrono/time_point)). This is set when the clock starts.
- the end time for the current task (an object of type `std::chrono::steady_clock::time_point`). This is set when the clock stops.
- an array of `Task` of structure type. The structure should contain the following fields:
  - a string with the task name.
  - a string with the units of time
  - the duration of the task (an object of type `std::chrono::steady_clock::duration`; see documentation [here](https://en.cppreference.com/w/cpp/chrono/duration))


Your class includes the following member functions:

- a default constructor
- `startClock()`: a modifier that starts the timer for an event
- `stopClock()`: a modifier that stops the timer for an event
- `addTask()`: a modifier that receives the address of a C-style null-terminated string that holds the name of the task.  This function will update the next time-record in the array:
  - stores into the name attribute the C-style string received as parameter
  - stores `"nanoseconds"` as the units of time
  - calculates and stores the duration of the event (use `std::chrono::duration_cast<std::chrono::nanoseconds>()`, see documentation [here](https://en.cppreference.com/w/cpp/chrono/duration/duration_cast))
- a **friend insertion operator** that receives a reference to an `std::ostream` object and a `TimedTask`object. This operator should insert in the `std::ostream` object the records from the array in the following format:

  ```txt
  Execution Times:
  --------------------------
  TASK_NAME DURATION UNITS
  TASK_NAME DURATION UNITS
  ...
  --------------------------
  ```

  The **name** of the task should be in a field of size 21, aligned on the left; the **duration** should be in a field of size 13, aligned on the right.

Starting and stopping the timer means getting the current time (use `std::chrono::steady_clock::now()`; see documentation [here](https://en.cppreference.com/w/cpp/chrono/steady_clock/now)) and store it into the relevant attributes.



### `ProteinDatabase` Module


Design and code a class named `ProteinDatabase` that manages two paralel **dynamically**-allocated arrays of elements of type `std::string`: one array will store the Unique IDs of the proteins while the second array will store the sequence of amino acids making the protein. Your class keeps track of the number of proteins currently stored.


#### Public Members

- a no-argument default constructor
- a 1-argument constructor that receives as parameter a string containing the name of a file from which this member function populates the current object. This function
  1. reads the file to count the number of **protein sequences** present in the file.
  2. allocates memory for that number of **protein sequences** in the arrays
  3. re-reads the file and loads the protein sequences (i.e., string of characters not sequence names) and IDs into the arrays.
- rule-of-5
- `size_t size()`: a query that returns the number of protein sequences stored in the current object.
- `std::string operator[](size_t)`: a query that returns a copy of the protein sequence at the index received as the function parameter. If the index is invalid, this function should return an empty string.
- `std::string getUID(size_t)`: a query that returns a copy of the protein ID at the index received as the function parameter. If the index is invalid, this function should return `"None"`.

To review the syntax for reading from a text file using an `std::ifstream` object see the chapter in your notes entitled [Input and Output Operators](http://intro2oop.sdds.ca/C-Encapsulation/input-and-output-operators).

Add any other members that your design requires (without changing the specs above)!



### Sample Output

The input file `protein_sequences.txt` is already provided.

When the program is started with the command:

```bash
ws protein_sequences.txt
```

the output should look like the one from the `sample_output.txt` file.

> [!NOTE]
> The execution times will be different every time you run the program! Everything else should match.
>
> See that in the sample output the *move operations* are **many orders of magnitude** faster than the *copy operations*.  If your output doesn't have such a significant difference in times, keep working on your implementation (the actual numbers will be different every time you run the application).


> [!CAUTION]
> Please note that a matching output is not a guarantee that the program is bug-free; it only means that in the specific tests this tester performed, no bugs/issues were identified. It is possible to write a tester that looks at other aspects of your code that will reveal bugs.





### Reflection

Study your final solution, reread the related parts of the course notes, and make sure that you have understood the concepts covered by this exercise. **This should take no less than 30 minutes of your time and the result is suggested to be at least 150 words in length.**

Create a **text** file named `reflect.txt` that contains your ***detailed*** description of the topics that you have learned in completing this exercise and mention any issues that caused you difficulty and how you solved them. Include in your explanation—**but do not limit it to**—the following points:

- the reason for the significant time difference between the copy and move operations

Refer to code snippets in your solution as examples to support your explanations.

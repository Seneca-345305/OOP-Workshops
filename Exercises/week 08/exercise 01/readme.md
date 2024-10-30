# STL Algorithms: A Collection of Songs

> [!NOTE]
> This is not a marked exercise and is not required to be submitted for credit. The purpose of the exercise is to practice concepts from the course material.
>
> At the end of the exercise, you are instructed to write a reflection: this will help you put into words what you have learned and make you think at the new concepts and explain them.  Explaining something to another person is one of the best ways to reveal concepts that are not clear to you and require further investigation.

In this exercise, you use the Algorithm category of the Standard Template Library.

You are going to create an application that manages a collection of songs.


## Learning Outcomes

Upon successful completion of this workshop, you will have demonstrated the abilities to:

- copy data from a file into a sequential container
- use the numeric library to accumulate data values
- use a lambda expression to specify an operation on each value in a data set
- use the algorithm library to sort data values



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




## A Collection of Songs

In this exercise you are going to create an application that loads from a file information about an unknown number of songs, store the songs in an STL container and then perform some operations on the collection:

- display all the songs to screen in an easy-to-read format
- sort the collection using various criteria
- check if there are any songs of an artist
- create a new collection containing the songs of an artist
- update the information about the songs

Enclose all your source code within the `seneca` namespace and include the necessary guards in each header file.

In the specs below, functions marked with `DO NOT USE MANUAL LOOPS` should not use `for` or `while` in the implementation; these functions should use STL Algorithms.  The STL Algorithms you choose should use lambda expressions to process the collection; the lambdas should **capture the necessary variables from context only by value** (the stream object is the only one allowed to be captured by reference). Check course notes to identify which algorithm is appropriate in each situation.

> [!WARNING]
> **:Important:** Your solution should not use the same algorithm twice.  The purpose of this exercise is to explore and practice multiple STL algorithms.


### `SongCollection` module

This module defines a simple structure called `Song`, capable of storing the following information about a single song:

- artist
- title
- album
- price
- release year
- length of the song

No need to add any member functions to this structure. Choose appropriate types for each attribute.

Also, define a class called `SongCollection` that manages a collection of objects of type `Song` (use an STL container).


#### Public Members

- a custom constructor that receives as a parameter the name of the file containing the information about the songs to be added to the collection. This function should load into the attributes all the songs in the file.

  If the filename is incorrect, this constructor should raise an exception to inform the client.

  Each line from the file contains information about a single song in the following format:

  ```txt
  TITLE ARTIST ALBUM YEAR LENGTH PRICE
  ```

  The fields are not separated by delimiters; each field has a fixed size: `TITLE`, `ARTIST` and `ALBUM` have **exactly** 25 characters; while `YEAR`, `LENGTH` and `PRICE` have **exactly** 5 characters.

  The length of a song in the input file is stored in seconds.

  Any blank space at the beginning/end of a token is not part of the token and should be removed.

- `void SongCollection::display(std::ostream& out) const`: print the content of the collection into the parameter (one song / line). Use the insertion operator (see below). At the end of the collection list, display the playtime of the entire collection (the total playtime is the sum of the length attribute of all songs). See the sample output for the format. ***DO NOT USE MANUAL LOOPS!***

- `void sort()`: receives as a parameter the name of the field used to sort the collection of songs in ascending order. The parameter can have one of the values `title`, `album`, or `length`.  ***DO NOT USE MANUAL LOOPS!***

- `void cleanAlbum()`: removes the token `[None]` from the album field of the songs that do not have a valid album.  ***DO NOT USE MANUAL LOOPS!***

- `bool inCollection() const`: receives the name of an artist as a parameter and returns `true` if the collection contains any song by that artist.  ***DO NOT USE MANUAL LOOPS!***

- `std::list<Song> getSongsForArtist() const`: receives the name of an artist as a parameter, and returns the list of songs of that artist available in the collection.  ***DO NOT USE MANUAL LOOPS!***


#### Free Helpers

- `std::ostream& operator<<(std::ostream& out, const Song& theSong)`: inserts one song into the first parameter, using the following format (the width of each field is specified in brackets):

  ```txt
  | TITLE(20) | ARTIST(15) | ALBUM(20) | YEAR(6) | LENGTH | PRICE |
  ```

  Look in the sample output to see how the numbers should be formatted and the alignment of each field.

**Add any other member that is required by your design!**





### `tester_1` module

The tester module has been supplied. **Do not modify the existing code!**

When doing the workshop, you are encouraged to write your own tests, focusing on a single implemented feature at the time, until you get all functionality in place.





### Sample Output

When the program is started with the command (the files are provided):

```bash
ws songs.txt
```

the output should look like the one from the `sample_output.txt` file.






### Reflection

Study your final solution, reread the related parts of the course notes, and make sure that you have understood the concepts covered by this workshop. **This should take no less than 30 minutes of your time, and the result is suggested to be at least 150 words in length.**

Create a **text** file named `reflect.txt` that contains your detailed description of the topics that you have learned in completing this particular workshop and mention any issues that caused you difficulty and how you solved them. Include in your explanation—**but do not limit it to**—the following points:

- list all the STL functions that you have used in this workshop; explain your reasoning for choosing each one, and not another.
- present the advantages of using STL algorithms vs. implementing the functionality by yourself using loops.
- the function that sorts the collection of songs receives as a parameter the field name to use; this can create errors if the client specifies an invalid field (or misspells it). How would you redesign that function to prevent the client to specify an invalid string, allowing any error to be detected by the compiler?

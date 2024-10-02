# Functions and Error Handling: A Mailing System


> [!NOTE]
> This is not a marked exercise and is not required to be submitted for credit. The purpose of the exercise is to practice concepts from the course material.
>
> At the end of the exercise, you are instructed to write a reflection: this will help you put into words what you have learned and make you think at the new concepts and explain them.  Explaining something to another person is one of the best ways to reveal concepts that are not clear to you and require further investigation.

In this exercise, you will simulate a mailing system. The mail server will store the emails of a user and will report errors when the email is addressed to a different user. To accomplish the task, you code a function object and a lambda expression, and handle exceptions.

To process incoming emails, your design should allow the utilization of plugins that will check for spam or validate the identity of some senders as trusted people.


## Learning Outcomes

Upon successful completion of this workshop, you will have demonstrated the abilities to:

- design and code a function object
- design and code a lambda expression
- code a member function that receives the address of a callback function to execute
- throw exceptions of different types
- distinguish exception types from one another



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
x
To check the output, use a program that can compare text files.  Search online for such a program for your platform, or use *diff* available on `matrix`.




## A Mailing System

???

Enclose all your source code within the `seneca` namespace and include the necessary guards in each header file.





### `message` Module

This module contains the definition of a custom type that represents an email. Look in the `message.h` file for a description of member.

**Do not modify this module!**  Look at the code and make sure you understand it.



### `plugin` Module

This module contains the interface that every plugin must implement. This class sits at the top of the *plugins* hierarchy. Look in the `plugin.h` file to see a description of each function available.


**Do not modify this module!**  Look at the code and make sure you understand it.



### `spamFilterPlugin` Module

This module contains the definition of a class named `SpamFilterPlugin` derived from `Plugin` representing a plugin that simulates classification of an email as spam or not. For simplicity, the rules used in classification are very simple: it is considered that if the email contains a certain substring in the subject, then it's a spam. The substrings identifying the spam message are loaded from a file; each substring is on a line.

#### Private Members

This class will store the strings that identifies an email as spam (loaded from a file; for simplicity you can use a statically allocated array of `std::string`), and the total number of emails found to be spam.

Add any private members that your design requires.

#### Public Members

- `SpamFilterPlugin(const char* filename)`: loads from the file specified as parameter the strings that identifies an email as spam (each string is on a line). If the input file cannot be opened, raise an exception to inform the client.

- `void operator()(Message& msg)`: checks if the subject line of the message contains any of the strings loaded from the file; if one is found, adds `"[SPAM] "` at the beginning of the subject line and increments the counter with number of spam emails found.

- `void showStats() const`: prints to screen the message `[Spam Filter Plugin] Identified COUNTER spam messages.<endl>`, where `COUNTER` is the number of spam emails identified.




### `verifyIdentityPlugin` Module

This module contains the definition of a class named `VerifyIdentityPlugin` derived from `Plugin` representing a plugin that simulates the verification of the sender as a trusted person.  For simplicity, the collection of trusted senders is loaded from a file.

#### Private Members

This class will store in a statically allocated array a collection of email addresses loaded from a file; emails coming from these addresses are considered *trusted*.

Add any private members that your design requires.

#### Public Members

- `VerifyIdentityPlugin(const char* filename)`: loads from the file specified as parameter a collection of email addresses. The input file contains one trusted email address per line. If the input file cannot be opened, raise an exception to inform the client.

- `void operator()(Message& msg)`: checks if the email comes from a trusted source; if it does, adds `"[TRUSTED] "` at the beginning of the subject line.

- `void showStats() const`: prints to screen the message `[Identity Checker Plugin] can validate identity for TRUSTED_EMAIL_1, TRUSTED_EMAIL_2, ...<endl>`, where `TRUSTED_EMAIL_*` are the emails extracted from the file.



### `mailServer` Module

This module contains the definition of a class named `MailServer` which manages the inbox of a single user. This class will be able to utilize up to two plugins to further process any incoming email (plugins come in the form of *functors*, and will implement the interface `Plugin`). The server will also allow clients to register an *observer* to receive notification when a new email arrives (the observer is a callback function). You can read more about the *observer pattern* [here](https://en.wikipedia.org/wiki/Observer_pattern).

#### Private Members

- `std::string m_userName`: stores the name of the person who owns this server/inbox
- `std::string m_userAddres`: sores the email address of the person who owns this server/inbox.
- `Message* m_inbox`: stores the address of a dynamically allocated array of messages received by the user. The `Message` objects are in *composition* relation with `MailServer`.
- `size_t m_cnt`: the number of messages in the inbox.
- `void (*onNewMailArrived)(const Message&)`: stores the address of a callback function, that the clients can register to receive notification when a new email has arrived. This is the *observer*.

> [!TIP]
> To simplify the syntax, you can create an alias to the type of the observer:
>
> ```cpp
> using Observer_fn  = void(const Message&);    // the function type
> using Observer_pfn = void(*)(const Message&); // the pointer-to-function type
> ```
>
> then you can use the alias:
>
> ```cpp
> Observer_fn* onNewMailArrived = nullptr;
> ```
>
> or
>
> ```cpp
> Observer_pfn onNewMailArrived = nullptr;
> ```

- `Plugin* m_plugins[2]`: a statically allocated array of two plugins. This class is in *aggregation* relation with the plugin objects.

Add any other *private* members that your design requires.

#### Public Members

- `MailServer(const char* name, const char* address)`: a constructor that initializes a new object for the user specified as a parameter. The new object will contain no messages, no observer, and no plugins.
- rule-of-5
- `void receiveMail(Message msg)`: adds to the inbox the message received as parameter if it's addressed to the current user (the `to` address of the message is the same as the email address of the inbox owner):
  - resize the inbox array if necessary and store this message in the array
  - for every plugin, call the `operator()` on it and pass this new message for further processing
  - if an observer is registered, call the registered callback function and pass this new message.

  If the message is addressed to a different user, raise an exception to inform the client, and do nothing else.

- `void addPlugin(Plugin* thePlugin)`: stores the address of the plugin received as parameter into the array of plugins on the first available position.
- `void setObserver(void(*observer)(const Message&))`: sets the observer pointer to the value of the parameter.
- `Message& operator[](size_t idx)`: returns the message at the index specified as parameter. If the index is outside the boundaries of the array, raise an exception of type `std::out_of_range` with the message `Index IDX is out of bounds`. For more information about [`std::out_of_range`](https://en.cppreference.com/w/cpp/error/out_of_range) exception, consult the documentation page: [https://en.cppreference.com/w/cpp/error/out_of_range](https://en.cppreference.com/w/cpp/error/out_of_range).
- `size_t getInboxSize()`: a query that returns the number of emails in the inbox.
- `void showInbox()`: a query that prints to screen all the emails stored in the inbox using the format:

  ```txt
  SENDER_NAME  SENDER_ADDRESS  DATE  EMAIL_SUBJECT<endl>
  SENDER_NAME  SENDER_ADDRESS  DATE  EMAIL_SUBJECT<endl>
  SENDER_NAME  SENDER_ADDRESS  DATE  EMAIL_SUBJECT<endl>
  ...
  ```

  where:

  - `SENDER_NAME` is a field of 20 characters aligned to the right
  - `SENDER_ADDRESS` is a field of 40 characters aligned to the left
  - `DATE` is a field of 15 characters aligned to the left (not that only the date is printed, without the time)

Add any other *special public member* that your design requires.



### `tester_1` Module

This module has some missing statements. The missing parts are marked with `TODO`, which describes the code that you should add and where to add it. **Do not modify the existing code, only add the code that is missing!**





### Sample Output

When the program is started with the command (the files `emails.csv`, `identities.txt`, `spam.txt` is provided):

  ```bash
  ws emails.csv identities.txt spam.txt
  ```

  the output should look like that is the `sample_output.txt` file.




### Reflection

Study your final solution, reread the related parts of the course notes, and make sure that you have understood the concepts covered by this workshop. **This should take no less than 30 minutes of your time and the result is suggested to be at least 150 words in length.**

Create a **text** file named `reflect.txt` that contains your detailed description of the topics that you have learned in completing this particular workshop and mention any issues that caused you difficulty and how you solved them. Include in your explanation—**but do not limit it to**—the following points:

- the difference between the implementations/utilizations of a functor and a lambda expression.  When is appropriate to use each one?
- what changes would you have to make to expand the mail server to handle multiple users?
- how would you change the application to allow multiple observers to be registered for the "new email arrived" event?

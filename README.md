# C++ Pipes and Filter project

## About

This is a sample C++ project for "Pipes and Filters" architecture in Software Engineering.

- Pipes: Simply send data from filter to filter. Pipes are  independent to types of filter they are connected to. Pipes can be connected to multiple filters.
- Filters: Process some kind of data got from input pipe and output the data through output pipe. Filters do not know about previous filters nor the next filters.

For simplicity, I only used pipes that pass through `vector<string>`s.

From `IPipe` interface, all pipes should implement these two methods. `PutData()` sends data into the pipe, `GetData()` is the data that came out from the pipe.

From `IFilter` interface, all fiters should implement `Process()` method(member function) so that the filter can process input data from the input pipe and then feed the processed data into the output pipe.

I think real world example is way different from this, but this sample project explains the concept of this architecture well enough.

## How to build

> CMake version 3.26 above required.

```
git clone <this_repo>
cd <this_repo>
mkdir build
cd build
cmake ..
```

For `GCC/Clang...` users can use `make` command to build after `cmake ..`

For `Windows MSVC` users, the command above will create `.sln` file so you can use that for building instead. (Open with Visual Studio IDE)

## Usage

`./cxx-pipe-and-filter {textfile.txt}`

For default, the program will print words per line, and total words in the text file. Sample lorem ipsum text is in `/src/file.txt`. CMake will copy to build directory when building the project.

In `main.cpp`, you can edit the filters, pipes or even implement your own types in `Filter.hpp/Pipe.hpp`.
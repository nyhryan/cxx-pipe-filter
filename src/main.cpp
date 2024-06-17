#include "Pipe.hpp"
#include "Filter.hpp"

// Vector that holds filters
// so that you can process the input data sequentially,
// simply just iterating through this vector, calling Process()
struct VectorFilters
{
    // This vector holds "Pointers to the filter"
    // So properly deallocating them in the destructor
    ~VectorFilters()
    {
        for (auto v : vec)
            delete v;
    }

    void push_back(IFilter *f) { vec.push_back(f); }

    auto operator()() { return vec; }
    auto operator()() const { return vec; }

private:
    std::vector<IFilter *> vec;
};

int main(int argc, const char *argv[])
{
    if (argc != 2)
    {
        std::cout << "Usage : <executable> {input.txt}";
        exit(EXIT_FAILURE);
    }

    StringPipe pipe_File2Filter;
    StringPipe pipe_Filter2Console;

    VectorFilters filters;
    // Create filters
    // Corresponding pipes should be given as filter constructor arguments.
    filters.push_back(new ReadFileFilter{ argv[1], pipe_File2Filter });
    // filters.push_back(new SortWordFilter{ pipe_File2Filter, pipe_Filter2Console });
    filters.push_back(new CountWordFilter{ pipe_File2Filter, pipe_Filter2Console });
    filters.push_back(new WriteToConsoleFilter{ pipe_Filter2Console });

    // sequentially process data using pipes and filters
    for (auto f : filters())
    {
        f->Process();
    }
}
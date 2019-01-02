// Author.h

#ifndef EX2_AUTHOR_H
#define EX2_AUTHOR_H

#include <unordered_map>
#include <vector>

/**
 * class of specific author
 */
class Author
{
public:
    /**
     * Constructor
     * @param wordCount map with all of the words in author text
     * @param frequentWords list of frequent words to look at
     */
    Author(const std::unordered_map<std::string, int> &wordCount,
           const std::vector<std::string> &frequentWords)
    {
        _wordCount = wordCount;
        for (auto &frequentWord : frequentWords)
        {
            _frequentWordNum.push_back(_wordCount[frequentWord]);
        }
    }

    /**
     * return the distance between vectors
     * @param other other author to calculate distance from
     * @return distance as double
     */
    double distFrom(Author other) const;

private:
    std::unordered_map<std::string, int> _wordCount;
    std::vector<int> _frequentWordNum;
};

#endif

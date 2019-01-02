#include <iostream>
#include <vector>
#include <unordered_map>
#include <iostream>
#include <fstream>
#include "Author.h"
#include <boost/algorithm/string.hpp>

#define DELIMITERS ", !:;\"\n"
#define FREQUENT_WORDS 1
#define UNKNOWN 2
#define SPACE " "
#define BEST_MATCH "Best matching author is "
#define SCORE " score "
#define MIN_NUM_OF_ARGS 4
#define FAILURE 1
#define ERR_MSG "Wrong num of args"
#define SUCCESS 0


/**
 * contains functions regarding files parsing
 */
namespace fileReader
{
    /**
     * read frequent words file format
     * @param file file path
     * @return vector with all of the frequent words
     */
    std::vector<std::string> readFrequentWords(std::string const &file)
    {
        std::vector<std::string> frequentWords;
        std::ifstream frequentWordsFile(file);
        std::string word;
        if (frequentWordsFile.is_open())
        {
            while (getline(frequentWordsFile, word))
            {
                frequentWords.push_back(word);
            }
            frequentWordsFile.close();
        }
        return frequentWords;
    }

    /**
     * read a text file
     * @param file file path
     * @return map with all of the words and their number of appearance
     */
    std::unordered_map<std::string, int> parseText(std::string const &file)
    {
        std::string delimiters(DELIMITERS);
        std::unordered_map<std::string, int> wordCount;
        std::vector<std::string> lineWords;
        std::ifstream textFile(file);
        std::string line;
        if (textFile.is_open())
        {
            while (getline(textFile, line))
            {
                boost::algorithm::to_lower(line);
                boost::split(lineWords, line, boost::is_any_of(delimiters));
                for (auto &lineWord : lineWords)
                {
                    wordCount[lineWord] ++;
                }
            }
            textFile.close();
        }
        return wordCount;
    }
}

/**
 * main func
 * @param argc num of arguments
 * @param argv arguments
 * @return 0 if success
 */
int main(int argc, char *argv[])
{
    if (argc < MIN_NUM_OF_ARGS)
    {
        std::cerr << ERR_MSG;
        return FAILURE;
    }
    std::vector<std::string> frequentWords = fileReader::readFrequentWords(argv[FREQUENT_WORDS]);
    std::vector<Author> authors;
    double bestDist = 0;
    int bestAuthor = - 1;
    for (int i = UNKNOWN; i < argc; i ++)
    {
        Author currAuthor = Author(fileReader::parseText(argv[i]), frequentWords);
        authors.push_back(currAuthor);
        if (i > UNKNOWN)
        {
            double tempDist = currAuthor.distFrom(authors[0]);
            std::cout << argv[i] << SPACE << tempDist << std::endl;
            if (tempDist > bestDist)
            {
                bestDist = tempDist;
                bestAuthor = i;
            }
        }
    }
    std::cout << BEST_MATCH << argv[bestAuthor] << SCORE << bestDist<<std::endl;
    return SUCCESS;
}

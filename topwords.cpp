#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>
#include <sstream>
#include <functional>

struct WordArray  {
    std::string word;
    mutable int frequency=0;
    bool operator > (const WordArray& str) const
    {
        return (frequency > str.frequency);
    }
} ;

int ASCIItranslate(char ch) {
    return ch;
}

void opt_dict()
{
    std::stringstream ss;
    std::string filename;
    for (int i=ASCIItranslate('a');i<=ASCIItranslate('z');i++)
    {
        ss.str("");
        ss << static_cast<char>(i);
        filename = "./dict/";
        filename += ss.str();
        filename += ".txt";
        std::ofstream myfile;
        myfile.open(filename,std::ofstream::out | std::ofstream::trunc);
        std::ifstream dict("dict.txt");
        for(std::string word; dict >> word; )
            if (word.at(0) == static_cast<char>(i))
                myfile << word << '\n';
        myfile.close();
    }
}

void clean_word(std::string * word)
{
    std::transform((*word).begin(), (*word).end(), (*word).begin(), ::tolower);

    //TODO: remove extensions
    char temp_word[100];
    int position=0;
    int count=0;
    if ( (*word).size() != 0)
    {
    for(auto i=(*word).begin();i < (*word).end() ;i++)
    {
        if ( (ASCIItranslate((*word).at(position)) >=  97 && ASCIItranslate((*word).at(position)) <= 172 ))
        {
            temp_word[count++]=(*word).at(position);
            //std::cout << (*word).at(position) << std::endl;

        }
        //std::cout << (*word).at(position) << std::endl;
        position++;

    }
    if (count !=0 )
    {
    temp_word[count] = '\0';
    * word = temp_word;
    //std::cout << temp_word << count << std::endl;
    }
    }

}

void top_words()
{
    std::ifstream is("test1.txt");
    WordArray unique;
    bool flag=0;
    std::stringstream ss;
    std::string dictfile;
    std::vector<WordArray> words;
    for(std::string * word = new std::string(); is >> *word; )
    {
//        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        clean_word(word);

        for(int i=ASCIItranslate('a');i<=ASCIItranslate('z');i++)
        {
            if ((*word).at(0) == static_cast<char>(i))
            {
                ss.str("");
                ss << static_cast<char>(i);
                dictfile = "./dict/";
                dictfile += ss.str();
                dictfile += ".txt";
                std::ifstream dict(dictfile);
                for(std::string word1; dict >> word1; )
                {
                    if ( (*word).compare(word1) == 0 )
                    {
                        flag = 0;
                        for (std::vector<WordArray>::const_iterator iter = words.begin();
                               iter != words.end(); ++iter)
                        {
                            if (iter->word == word1)
                            {
                                iter->frequency+=1;
                                flag=1;
                                break;
                            }

                        }
                        if(flag == 0)
                        {
                            unique.word=word1;
                            unique.frequency=1;
                            words.push_back(unique);
                        }

                     }
                  }
                }

            }
     }
    std::sort(words.begin(),words.end(),std::greater<WordArray>());
    std::ofstream result;
    result.open("result.txt",std::ofstream::out | std::ofstream::trunc);

    for (std::vector<WordArray>::const_iterator iter = words.begin();
           iter != words.end(); ++iter)
        result << iter->word << " " << iter->frequency << '\n';
    result.close();
}

int main(int argc, char *argv[])
{
//    opt_dict();
    //std::vector<std::string> dictpath;
    top_words();
    return 0;
}



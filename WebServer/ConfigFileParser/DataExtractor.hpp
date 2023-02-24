#ifndef DATA_EXTRACTOR_HPP
# define DATA_EXTRACTOR_HPP

# include "../../Includes/Header.hpp"

class DataExtractor
{
    private:
    
    public:
        DataExtractor();
        DataExtractor(const DataExtractor &d);
        DataExtractor& operator=(const DataExtractor &d);
        ~DataExtractor();
} ;

#endif
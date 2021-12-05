#ifndef __ZEROMQ_H
#define __ZEROMQ_H
#include <string>

/**
 * getDataset
 * Function that takes a string for the word we want a dataset for,
 * passes it to our golang server, and waits for a response. 
 * @param  term     -   The term we want a dataset of
 * @return          -   String containing path to file with dataset
 */
void getDataset(std::string term);

#endif
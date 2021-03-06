/************************************+
 * Prompter.c                        *
 * Author : Alexander Parella        *
 * CLI RSS feed reader, source       *
 * available at github.com/aaparella *
 * Usage : prompter --help           *
 +************************************/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <curl/curl.h>

#include "argparse.h"
#include "feedparse.h"
#include "get.h"
 
int main(int argc, char* argv[]) {
	
    // Parse command line arguments, use defaults when needed
    ArgumentStruct* args;
    args = parseArguments(argc, argv);
    
    // Struct to store response from CURL
    MessageStruct response;
    
    // Get RSS feed from server
    if (args->update) {
        if(get(&response, args->url)) {
            printf("Error in performing CURL\n");
            return 1;
        }
    
        // Write result out to file
        if(storeFeed(response, args->dataFile, args->tempDirectory)) {
            printf("Error writing response to file\n");
            return 1;
        }
    }
    
    // Create array of article sturctures
    ArticleStruct** articles = NULL;
    articles = parseFeed(args);
    
    freeArticles(articles);
    
    // Args is dynamically allocated, free it!
    free(args);
    return 0;
}

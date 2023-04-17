#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "map.h"

#define MAP_SIZE (1 << 14)
#define BUFFER_SIZE 2048
//
// Represents the sentiment value for a single word/term.
typedef struct sentiment_t {
  double pos; // mean positive sentiment for the term
  double neg; // mean negative sentiment for the term
  int count;  // number of times the term appears
} sentiment_t;

// Map from string words/terms to sentiment_t values.
map_t *sentiments = NULL;

// Convert a string to lower case and strip whitespace and punctuation.
//
// Resizes string by nulling the unused suffix.
void lower_and_strip(char *str) {
  char *t = str; // insert point
  char *c = str; // current char
  for (; *c; c++) {
    if (isalnum(*c)) {
      // convert to lowercase; append at insert point.
      *t = tolower(*c); // t <= c
      t++;
    }
  }
  // c is null terminator; cut end of string after alnum chars.
  while (t < c) {
    *(t++) = '\0';
  }
}

// Print a single entry in a map string -> sentiment_t.
void *print_map_entry(const char *key, void *value) {
  sentiment_t *v = value;
  printf("%s : +%f -%f (%d)\n", key, v->pos, v->neg, v->count);
  return value;
}

// Free a single value from a map.
void *free_map_value(const char *key, void *value) {
  free(value);
  return NULL;
}

// Free all values in a map.
void free_map_values() { map_apply(sentiments, free_map_value); }

// Print all sentiments in a map string -> sentiment_t.
void dump_sentiments() { map_apply(sentiments, print_map_entry); }

// Build a map string -> sentiment_t by parsing input file.
//
// Modifies sentiments map.
void build_sentiment_map(FILE *f) {
  if (sentiments) {
    free_map_values();
    map_free(&sentiments);
  }
  sentiments = map_create(MAP_SIZE);

  char buff[BUFFER_SIZE];
  int line_no = -1;
  while (fgets(buff, BUFFER_SIZE, f) != NULL) {
    line_no++;
    // clang-format off
    //
    // Line is ether:
    // POS<TAB>ID<TAB>PosScore<TAB>NegScore<TAB>Word#n Word#n Word#n ...<TAB>Definition
    // OR
    // # this line is a comment since it starts with #
    //
    //clang-format on


    //If the file line is a comment, skip to next line.
    if (buff[0] == '#') {
      continue;
    }

    // Tokenize the file line (which is buff):
    char *token;
    char buffCopy[1000];
    strcpy(buffCopy, buff);
    token = strtok(buffCopy, "\t");
    char *tokens[1059]; // Array of tokens (i.e. parts
                        // of the file line).   
    tokens[0] = token;
    int c = 1;

    while (token != NULL) {
      token = strtok(NULL, "\t");
      
      //If we're looking at the list of terms, we need to split them up:
      if (c == 4) {
        char *term;
        char token_terms[512]; // the list of terms we need to split.
        strcpy(token_terms, token);
        term = strtok(token_terms, " "); 
        while (term != NULL) {
          tokens[c] = term;
          term = strtok(NULL, " ");
          c++;
        }
        break; //We don't care about keeping track of the description.
      }

      tokens[c] = token;
      c++;
    }


    // Check if EACH of the terms in the list of terms is in the 
    // map already (If the term is in the map, update it's sentiment.
    // If term is not in the map, add it):
    // *NOTE*: in_map = 0 if the term is NOT in present in the map. 
    for (int i = 0; i < c - 4; i++) {
      sentiment_t *senti;
      lower_and_strip(tokens[4+i]);
      int len = strlen(tokens[4+i]);

      //Get rid of extranious number at the end of the terms
      for (int j = 0; j < len; j++) {
        if (isdigit(tokens[4+i][len-1])) {
          tokens[4+i][len-1] = '\0';
          len--;
        } 
      }

      int in_map = map_get(sentiments, tokens[4+i], (void**) &senti);

      //If a new word/term:
      if (!in_map) {
        //Memory needs to be allocated for senti if it's not in the map.
        senti = malloc(sizeof(sentiment_t));
        
        //Put in the values for senti.
        senti->count = 1;
        senti->neg = atof(tokens[3]);
        senti->pos = atof(tokens[2]);

        //Put the term into the map along with its sentiments
        map_put(sentiments, tokens[4+i], senti);
      }

      //If not a new word, update values in senti.
      else {
        senti->count++;
        senti->neg = senti->neg + (atof(tokens[3]) - senti->neg) / senti->count;
        senti->pos = senti->pos + (atof(tokens[2]) - senti->pos) / senti->count; 
      }

    } //End of for-loop

  }
}

void sentiment_stdin() {
  char buffer[BUFFER_SIZE];
  char input[BUFFER_SIZE];
  while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
    strncpy(input, buffer, BUFFER_SIZE);
    input[strlen(input) - 1] = '\0';
    

    //Parse input into a list of words:
    char *word;
    char inputCopy[1000];
    strcpy(inputCopy, input); 
    word = strtok(inputCopy, " ");
    char *words[1059];

    words[0] = word;
    int wc = 1; //word count.

    while (word != NULL) {
      word = strtok(NULL, " ");
      words[wc] = word;
      wc++;
     }


    //Calculate the sentiments:
    sentiment_t *senti;
    double sum = 0; //sum of sentiments.

    for(int i = 0; i < wc - 1; i++) {
      lower_and_strip(words[i]);
      int in_map = map_get(sentiments, words[i], (void**) &senti); 
      // ^ sets senti to the correct sentiment values for the word.

      if (in_map) {
        sum += ( senti->pos - senti->neg);     
        senti = NULL;
      }  
    }

    //Print sentiment result: 
    printf("%s : %f\n", input, sum);

  }
}

void usage(char *name) {
  printf("Usage: %s <sentiment_file.txt>\n", name);
  exit(1);
}

int main(int argc, char **argv) {
  if (argc < 2) {
    printf("Must supply filename.\n");
    usage(argv[0]);
  }

  FILE *f = fopen(argv[1], "r");
  if (!f) {
    perror("fopen");
    exit(1);
  }
  fprintf(stderr, "loading sentiment map...");
  // Build the map of sentiments...
  build_sentiment_map(f);
  fprintf(stderr, "loaded.\n");
  // if you want to get sentiments out of your map in order to debug:
  // dump_sentiments();
  // Read sentiments from standard in...
  sentiment_stdin();
}

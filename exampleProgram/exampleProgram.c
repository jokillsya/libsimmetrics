#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <libgen.h>
#include "utlist.h"
#include "utarray.h"
#include "uthash.h"
#include "tokenizer.h"
#include "qgrams_distance.h"
#include "block_distance.h"
#include "cosine_similarity.h"
#include "dice_similarity.h"
#include "euclidean_distance.h"
#include "jaccard_similarity.h"
#include "jaro.h"
#include "jaro_winkler.h"
#include "levenshtein.h"
#include "matching_coefficient.h"
#include "simmetrics.h"
#include "cost.h"
#include "monge_elkan.h"
#include "needleman_wunch.h"
#include "overlap_coefficient.h"
#include "smith_waterman.h"
#include "smith_waterman_gotoh.h"
#include "soundex.h"

const int SIMMETC = 31;

const char *SIMMETS[31] = {"block","block_distance","cos","cosine","dice","eucli","euclidean_distance","jac","jaccard","jar","jaro","wink","jaro_winkler","leven","levenshtein","match","matching_coefficient","monge","monge_elkan","need","needleman_wunch","ol","overlap_coefficient","qg","qgrams_distance","smith","smith_waterman","gotoh","smith_waterman_gotoh","snd","soundex"};

int which_type(char *simtype) 
{
    int i;
    for (i=0; i < SIMMETC; i++) {
        if (strcmp(SIMMETS[i], simtype) == 0)
            return i;
    }
    return -1;
}

int main(int argc, char *argv[])
{
    if (argc != 4) 
    {
        printf("usage: \n\t$ %s <SimMetric> <string1> <string2>\n", basename(argv[0]));
        printf("\nWhere SimMetric is one of:\n");
        int i;
        for (i=0; i < SIMMETC; i++) {
            if (i > 0)
                printf(",");
            printf(" %s", SIMMETS[i]);
        }
        printf("\n");
        return 1;
    }
    else 
    {
        float similarity;

    	switch (which_type(argv[1])) {
            case 0:
            case 1:
                similarity = block_distance_similarity(argv[2], argv[3]);
                break;
            case 2:
            case 3:
                similarity = cosine_similarity(argv[2], argv[3]);
                break;
            case 4:
                similarity = dice_similarity(argv[2], argv[3]);
                break;
            case 5:
            case 6:
                similarity = euclidean_distance_similarity(argv[2], argv[3]);
                break;
            case 7:
            case 8:
                similarity = jaccard_similarity(argv[2], argv[3]);
                break;
            case 9:
            case 10:
                similarity = jaro_similarity(argv[2], argv[3]);
                break;
            case 11:
            case 12:
                similarity = jaro_winkler_similarity(argv[2], argv[3]);
                break;
            case 13:
            case 14:
                similarity = levenshtein_similarity(argv[2], argv[3]);
                break;
            case 15:
            case 16:
                similarity = matching_coefficient_similarity(argv[2], argv[3]);
                break;
            case 17:
            case 18:
                similarity = monge_elkan_similarity(argv[2], argv[3]);
                break;
            case 19:
            case 20:
                similarity = needleman_wunch_similarity(argv[2], argv[3]);
                break;
            case 21:
            case 22:
                similarity = overlap_coefficient_similarity(argv[2], argv[3]);
                break;
            case 23:
            case 24:
                similarity = qgrams_distance_similarity(argv[2], argv[3]);
                break;
            case 25:
            case 26:
                similarity = smith_waterman_similarity(argv[2], argv[3]);
                break;
            case 27:
            case 28:
                similarity = smith_waterman_gotoh_similarity(argv[2], argv[3]);
                break;
            case 29:
            case 30:
                similarity = soundex_similarity(argv[2], argv[3]);
                break;
    	default:
    	   printf("Unknown SimMetric %s, not found.", argv[1]);
    	   return 1;
    	}        
    	
        printf("%s SimMetrics between %s & %s yields a %3.0f%% similarity\n", argv[1], argv[2], argv[3], similarity * 100);

	    return EXIT_SUCCESS;
    }
}

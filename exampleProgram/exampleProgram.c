#include "simmetrics.h"

const int SIMMETC = 33;

const char *SIMMETS[33] = {"block", "block_distance", "cos", "cosine", "dice", "eucli",
        "euclidean_distance", "jac", "jaccard", "jar", "jaro", "wink", "jaro_winkler",
        "leven", "levenshtein", "match", "matching_coefficient", "monge", "monge_elkan",
        "need", "needleman_wunch", "ol", "overlap_coefficient", "qg", "qgrams_distance",
        "smith", "smith_waterman", "gotoh", "smith_waterman_gotoh", "snd", "soundex",
        "meta", "metaphone"};

int which_type(char *simtype) 
{
    int i;
    for (i=0; i < SIMMETC; i++) {
        if (strcmp(SIMMETS[i], simtype) == 0)
            return i;
    }
    return -1;
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
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
    else if (strcmp(argv[1], "all") == 0) {
        argv[1] = "block_distance"; main(argc, argv);
        argv[1] = "cosine"; main(argc, argv);
        argv[1] = "dice"; main(argc, argv);
        argv[1] = "euclidean_distance"; main(argc, argv);
        argv[1] = "jaccard"; main(argc, argv);
        argv[1] = "jaro"; main(argc, argv);
        argv[1] = "jaro_winkler"; main(argc, argv);
        argv[1] = "levenshtein"; main(argc, argv);
        argv[1] = "matching_coefficient"; main(argc, argv);
        argv[1] = "monge_elkan"; main(argc, argv);
        argv[1] = "needleman_wunch"; main(argc, argv);
        argv[1] = "overlap_coefficient"; main(argc, argv);
        argv[1] = "qgrams_distance"; main(argc, argv);
        argv[1] = "smith_waterman"; main(argc, argv);
        argv[1] = "smith_waterman_gotoh"; main(argc, argv);
        argv[1] = "soundex"; main(argc, argv);
        argv[1] = "metaphone"; main(argc, argv);
    }
    else {
        float similarity = 0;
        char *sm_name, metrics[50], compare[50];

        sprintf(compare, "%10s & %-10s", argv[2], argv[3]);
        switch (which_type(argv[1])) {
            case 0:
            case 1:
                sm_name = "Block Distance";
                sprintf(metrics, "%d", block_distance(argv[2], argv[3]));
                similarity = block_distance_similarity(argv[2], argv[3]);
                break;
            case 2:
            case 3:
                sm_name = "Cosine Similarity";
                sprintf(metrics, "not applicable");
                similarity = cosine_similarity(argv[2], argv[3]);
                break;
            case 4:
                sm_name = "Dice Similarity";
                sprintf(metrics, "not applicable");
                similarity = dice_similarity(argv[2], argv[3]);
                break;
            case 5:
            case 6:
                sm_name = "Euclidean Distance";
                sprintf(metrics, "%3.2f", euclidean_distance(argv[2], argv[3]));
                similarity = euclidean_distance_similarity(argv[2], argv[3]);
                break;
            case 7:
            case 8:
                sm_name = "Jaccard Similarity";
                sprintf(metrics, "not applicable");
                similarity = jaccard_similarity(argv[2], argv[3]);
                break;
            case 9:
            case 10:
                sm_name = "Jaro Similarity";
                sprintf(metrics, "not applicable");
                similarity = jaro_similarity(argv[2], argv[3]);
                break;
            case 11:
            case 12:
                sm_name = "Jaro Winkler Similarity";
                sprintf(metrics, "not applicable");
                similarity = jaro_winkler_similarity(argv[2], argv[3]);
                break;
            case 13:
            case 14:
                sm_name = "Levenshtein Distance";
                sprintf(metrics, "%d", levenshtein(argv[2], argv[3]));
                similarity = levenshtein_similarity(argv[2], argv[3]);
                break;
            case 15:
            case 16:
                sm_name = "Matching Coefficient SimMetrics";
                sprintf(metrics, "%3.2f", matching_coefficient(argv[2], argv[3]));
                similarity = matching_coefficient_similarity(argv[2], argv[3]);
                break;
            case 17:
            case 18:
                sm_name = "Monge Elkan Similarity";
                sprintf(metrics, "not applicable");
                similarity = monge_elkan_similarity(argv[2], argv[3]);
                break;
            case 19:
            case 20:
                sm_name = "Needleman Wunch SimMetrics";
                sprintf(metrics, "%3.2f", needleman_wunch(argv[2], argv[3]));
                similarity = needleman_wunch_similarity(argv[2], argv[3]);
                break;
            case 21:
            case 22:
                sm_name = "Overlap Coefficient Similarity";
                sprintf(metrics, "not applicable");
                similarity = overlap_coefficient_similarity(argv[2], argv[3]);
                break;
            case 23:
            case 24:
                sm_name = "QGrams Distance";
                sprintf(metrics, "%d", qgrams_distance(argv[2], argv[3]));
                similarity = qgrams_distance_similarity(argv[2], argv[3]);
                break;
            case 25:
            case 26:
                sm_name = "Smith Waterman SimMetrics";
                sprintf(metrics, "%3.2f", smith_waterman(argv[2], argv[3]));
                similarity = smith_waterman_similarity(argv[2], argv[3]);
                break;
            case 27:
            case 28:
                sm_name = "Smith Waterman Gotoh SimMetrics";
                sprintf(metrics, "%3.2f", smith_waterman_gotoh(argv[2], argv[3]));
                similarity = smith_waterman_gotoh_similarity(argv[2], argv[3]);
                break;
            case 29:
            case 30:
                sm_name = "Soundex Phonetics";
                sprintf(metrics, "normalized to %s & %s", soundex(argv[2]), soundex(argv[3]));
                similarity = soundex_similarity(argv[2], argv[3]);
                break;
            case 31:
            case 32:
                sm_name = "Metaphone Phonetics";
                sprintf(metrics, "normalized to %s & %s", metaphone(argv[2]), metaphone(argv[3]));
                similarity = metaphone_similarity(argv[2], argv[3]);
                break;
            default:
               printf("Unknown SimMetric %s, not found.\n", argv[1]);
               return 1;
        }

        printf("%-31s between %-25s is %25s ", sm_name, compare, metrics);
        printf("and yields a %3.0f%% similarity\n", similarity * 100);

        return EXIT_SUCCESS;
    }
}
